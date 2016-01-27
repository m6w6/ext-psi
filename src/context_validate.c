#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#include <sys/param.h>
#include <dlfcn.h>

#include "php_psi.h"
#include "php_psi_stdinc.h"
#include "php_psi_stdtypes.h"
#include "php_psi_macros.h"
#include "php_psi_redirs.h"

#include "calc.h"
#include "marshal.h"
#include "engine.h"

static int validate_lib(PSI_Data *data, void **dlopened) {
	char lib[MAXPATHLEN];
	const char *ptr = data->psi.file.ln;
	size_t len;

	if (!ptr) {
		/* FIXME: assume stdlib */
		return 1;
	} else if (!strchr(ptr, '/')) {
		len = snprintf(lib, MAXPATHLEN, "lib%s.%s", ptr, PHP_PSI_SHLIB_SUFFIX);
		if (MAXPATHLEN == len) {
			data->error(NULL, PSI_WARNING, "Library name too long: '%s'", ptr);
		}
		lib[len] = 0;
		ptr = lib;
	}
	if (!(*dlopened = dlopen(ptr, RTLD_LAZY|RTLD_LOCAL))) {
		data->error(NULL, PSI_WARNING, "Could not open library '%s': %s.",
				data->psi.file.ln, dlerror());
		return 0;
	}
	return 1;
}

static inline int locate_decl_type_alias(decl_typedefs *defs, decl_type *type) {
	size_t i;
	struct psi_std_type *stdtyp;

	if (type->real) {
		return 1;
	}
	for (i = 0; i < defs->count; ++i) {
		decl_typedef *def = defs->list[i];

		if (def->type->type != type->type && !strcmp(def->alias, type->name)) {
			type->real = def->type;
			return 1;
		}
	}
	for (stdtyp = &psi_std_types[0]; stdtyp->type_tag; ++stdtyp) {
		if (!strcmp(type->name, stdtyp->alias ?: stdtyp->type_name)) {
			type->type = stdtyp->type_tag;
			return 1;
		}
	}

	return 0;
}
static inline int locate_decl_type_struct(decl_structs *structs, decl_type *type) {
	size_t i;

	if (type->strct) {
		return 1;
	}
	for (i = 0; i < structs->count; ++i) {
		if (!strcmp(structs->list[i]->name, type->name)) {
			type->strct = structs->list[i];
			return 1;
		}
	}
	return 0;
}

static inline int validate_decl_type(PSI_Data *data, decl_type *type) {
	switch (type->type) {
	case PSI_T_CHAR:
	case PSI_T_SHORT:
	case PSI_T_INT:
	case PSI_T_LONG:
	case PSI_T_NAME:
		if (!data->defs || !locate_decl_type_alias(data->defs, type)) {
			return 0;
		}
		if (type->real) {
			return validate_decl_type(data, type->real);
		}
		return 1;
	case PSI_T_STRUCT:
		if (!data->structs || !locate_decl_type_struct(data->structs, type)) {
			return 0;
		}
		break;
	}
	return 1;
}
static inline int validate_decl_typedef(PSI_Data *data, decl_typedef *def) {
	if (!validate_decl_type(data, def->type)) {
		data->error(def->token, PSI_WARNING,
			"Type '%s' cannot be aliased to %s'%s'",
			def->type->name, def->type->type == PSI_T_STRUCT?"struct ":"",def->alias);
		return 0;
	}
	/* FIXME: check def->alias */
	return 1;
}

static inline int validate_constant(PSI_Data *data, constant *c) {
	/* FIXME */
	return 1;
}

static inline int validate_decl_arg(PSI_Data *data, decl_arg *arg) {
	if (!validate_decl_type(data, arg->type)) {
		data->error(arg->type->token, PSI_WARNING,
			"Cannot use '%s'(%d) as type for decl var '%s'",
			arg->type->name, arg->type->type, arg->var->name);
		return 0;
	}
	return 1;
}

static int psi_sort_struct_arg_cmp(const void *_a, const void *_b) {
	decl_arg *a = *(decl_arg **)_a, *b = *(decl_arg **)_b;

	if (a->layout->pos == b->layout->pos) {
		if (a->layout->len == b->layout->len) {
			return 0;
		} else if (a->layout->len > b->layout->len) {
			return -1;
		} else {
			return 1;
		}
	} else if (a->layout->pos > b->layout->pos) {
		return 1;
	} else {
		return -1;
	}
}
static void psi_sort_struct_arg_swp(void *a, void *b) {
	decl_arg **_a = a, **_b = b, *_c;

	_c = *_b;
	*_b = *_a;
	*_a = _c;
}
static inline void psi_sort_struct_args(decl_struct *s) {
	zend_insert_sort(s->args->args, s->args->count, sizeof(*s->args->args),
			psi_sort_struct_arg_cmp, psi_sort_struct_arg_swp);
}

static inline int validate_decl_struct(PSI_Data *data, decl_struct *s) {
	size_t i;

	for (i = 0; i < s->args->count; ++i) {
		if (!validate_decl_arg(data, s->args->args[i])) {
			return 0;
		}
	}

	for (i = 0; i < s->args->count; ++i) {
		decl_arg *darg = s->args->args[i];

		if (!validate_decl_arg(data, darg)) {
			return 0;
		}

		ZEND_ASSERT(!darg->var->arg || darg->var->arg == darg);
		darg->var->arg = darg;

		if (darg->layout) {
			size_t size;

			if (darg->var->array_size) {
				size = psi_t_size(real_decl_type(darg->type)->type) * darg->var->array_size;
			} else if (darg->var->pointer_level) {
				size = psi_t_size(PSI_T_POINTER);
			} else {
				decl_type *real = real_decl_type(darg->type);

				if (real->type == PSI_T_STRUCT) {
					size = real->strct->size;
				} else {
					size = psi_t_size(real->type);
				}
			}
			if (darg->layout->len != size) {
				data->error(darg->token, PSI_WARNING,
						"Computed length %zu of %s.%s does not match"
						" pre-defined length %zu of type '%s'",
						darg->layout->len, s->name, darg->var->name, size,
						darg->type->name);
				return 0;
			}
		} else {
			token_t t;

			if (darg->var->pointer_level && (!darg->var->array_size || darg->var->pointer_level == 1)) {
				t = PSI_T_POINTER;
			} else {
				t = real_decl_type(darg->type)->type;
			}

			if (i) {
				decl_arg *last = s->args->args[i-1];
				darg->layout = init_decl_struct_layout(
						psi_t_align(t, last->layout->pos + last->layout->len),
						psi_t_size(t) * darg->var->array_size);
			} else {
				darg->layout = init_decl_struct_layout(0, psi_t_size(t));
			}
		}
		if (s->size < darg->layout->pos + darg->layout->len) {
			s->size = darg->layout->pos + darg->layout->len;
		}
	}

	psi_sort_struct_args(s);

	return 1;
}

static const char * const abi_ccs[] = {
		"default", /* \                 */
		"extern",  /*  > - all the same */
		"cdecl",   /* /                 */
		"mscdecl",
		"stdcall",
		"fastcall",
};
static inline int validate_decl_abi(PSI_Data *data, decl_abi *abi) {
	size_t i;

	for (i = 0; i < sizeof(abi_ccs)/sizeof(char*); ++i) {
		if (strcasecmp(abi->convention, abi_ccs[i])) {
			return 1;
		}
	}
	return 0;
}
static inline int validate_decl_func(PSI_Data *data, void *dl, decl *decl, decl_arg *func)
{
	struct psi_func_redir *redir;

	if (!strcmp(func->var->name, "dlsym")) {
		data->error(func->token, PSI_WARNING, "Cannot dlsym dlsym (sic!)");
		return 0;
	}

	if (!validate_decl_arg(data, func)) {
		return 0;
	}
	for (redir = &psi_func_redirs[0]; redir->name; ++redir) {
		if (!strcmp(func->var->name, redir->name)) {
			decl->call.sym = redir->func;
		}
	}
	if (!decl->call.sym) {
#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
		decl->call.sym = dlsym(dl ?: RTLD_NEXT, func->var->name);
		if (!decl->call.sym) {
			data->error(func->token, PSI_WARNING,
				"Failed to locate symbol '%s': %s",
				func->var->name, dlerror());
		}
	}
	return 1;
}

static inline int validate_decl(PSI_Data *data, void *dl, decl *decl) {
	if (!validate_decl_abi(data, decl->abi)) {
		data->error(decl->abi->token, PSI_WARNING,
				"Invalid calling convention: '%s'", decl->abi->token->text);
		return 0;
	}
	if (!validate_decl_func(data, dl, decl, decl->func)) {
		return 0;
	}
	if (decl->args) {
		size_t i;

		for (i = 0; i < decl->args->count; ++i) {
			if (!validate_decl_arg(data, decl->args->args[i])) {
				return 0;
			}
		}
	}
	return 1;
}
static inline decl_arg *locate_decl_var_arg(decl_var *var, decl_args *args, decl_arg *func) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		decl_arg *arg = args->args[i];

		if (!strcmp(var->name, arg->var->name)) {
			ZEND_ASSERT(!var->arg || var->arg == arg);
			return var->arg = arg;
		}
	}
	if (func && !strcmp(var->name, func->var->name)) {
		return var->arg = func;
	}

	return NULL;
}
static inline decl_arg *locate_struct_member(decl_struct *s, decl_var *var) {
	if (s->args) {
		return locate_decl_var_arg(var, s->args, NULL);
	}

	return NULL;
}
static inline constant *locate_num_exp_constant(num_exp *exp, constants *consts) {
	size_t i;

	for (i = 0; i < consts->count; ++i) {
		constant *cnst = consts->list[i];

		if (!strcmp(cnst->name, exp->u.numb)) {
			free(exp->u.numb);
			return exp->u.cnst = cnst;
		}
	}

	return NULL;
}
static inline int validate_num_exp(PSI_Data *data, decl_args *dargs, decl_arg *func, num_exp *exp) {
	if (exp->operand) {
		switch (exp->operator) {
		case PSI_T_PLUS:
			exp->calculator = psi_calc_add;
			break;
		case PSI_T_MINUS:
			exp->calculator = psi_calc_sub;
			break;
		case PSI_T_ASTERISK:
			exp->calculator = psi_calc_mul;
			break;
		case PSI_T_SLASH:
			exp->calculator = psi_calc_div;
			break;
		EMPTY_SWITCH_DEFAULT_CASE();
		}
		if (!validate_num_exp(data, dargs, func, exp->operand)) {
			return 0;
		}
	}
	switch (exp->t) {
	case PSI_T_NAME:
		if (!locate_decl_var_arg(exp->u.dvar, dargs, func)) {
			data->error(exp->token, PSI_WARNING, "Unknown variable '%s' in numeric expression",
					exp->u.dvar->name);
			return 0;
		}
		return 1;
	case PSI_T_NSNAME:
		if (!locate_num_exp_constant(exp, data->consts)) {
			data->error(exp->token, PSI_WARNING, "Unknown constant '%s' in numeric expression",
					exp->u.numb);
			return 0;
		}
		return 1;
	case PSI_T_NUMBER:
		return 1;
	default:
		return 0;
	}
}
static inline int validate_set_value_handler(set_value *set) {
	switch (set->func->type) {
	case PSI_T_TO_BOOL:
		set->func->handler = psi_to_bool;
		break;
	case PSI_T_TO_INT:
		set->func->handler = psi_to_int;
		break;
	case PSI_T_TO_FLOAT:
		set->func->handler = psi_to_double;
		break;
	case PSI_T_TO_STRING:
		set->func->handler = psi_to_string;
		break;
	case PSI_T_TO_ARRAY:
		set->func->handler = psi_to_array;
		break;
	case PSI_T_TO_OBJECT:
		set->func->handler = psi_to_object;
		break;
	case PSI_T_VOID:
		set->func->handler = psi_to_void;
		break;
	case PSI_T_ELLIPSIS:
		if (set->outer.set && set->outer.set->func->type == PSI_T_TO_ARRAY) {
			set->func->handler = psi_to_recursive;
			set->inner = set->outer.set->inner;
			set->count = set->outer.set->count;
			break;
		}
		/* no break */
	default:
		return 0;
	}
	return 1;
}
static inline void decl_var_arg_v(decl_args *args, va_list argp) {
	int argc;
	decl_arg **argv;

	memset(args, 0, sizeof(*args));

	while ((argc = va_arg(argp, int))) {
		argv = va_arg(argp, decl_arg **);
		while (argc--) {
			add_decl_arg(args, *argv++);
		}
	}
}
static inline int validate_set_value_ex(PSI_Data *data, set_value *set, decl_arg *ref, decl_args *ref_list) {
	size_t i;
	decl_type *ref_type;
	decl_var *set_var = set->vars->vars[0];

	if (!validate_set_value_handler(set)) {
		data->error(set->func->token, PSI_WARNING, "Invalid cast '%s' in `set` statement", set->func->name);
		return 0;
	}

	for (i = 0; i < set->vars->count; ++i) {
		decl_var *svar = set->vars->vars[i];
		if (!svar->arg && !locate_decl_var_arg(svar, ref_list, NULL)) {
			data->error(svar->token, PSI_WARNING, "Unknown variable '%s' in `set` statement", svar->name);
			return 0;
		}
	}

	if (!ref) {
		ref = set_var->arg;
	}
	ref_type = real_decl_type(ref->type);

	if (set->count) {
		int is_to_array = (set->func->type == PSI_T_TO_ARRAY);
		int is_pointer_to_struct = (ref_type->type == PSI_T_STRUCT && ref->var->pointer_level);

		if (!is_to_array && !is_pointer_to_struct) {
			data->error(set->func->token, E_WARNING, "Inner `set` statement casts only work with "
					"to_array() casts on structs or pointers: %s(%s...", set->func->name, set->vars->vars[0]->name);
			return 0;
		}
	}
	if (set->num) {
		if (!validate_num_exp(data, ref_list, ref, set->num)) {
			return 0;
		}
	}

	if (ref_type->type == PSI_T_STRUCT) {
		/* to_array(struct, to_...) */
		if (!set->outer.set || set->outer.set->inner != set->inner) {
			for (i = 0; i < set->count; ++i) {
				decl_var *sub_var = set->inner[i]->vars->vars[0];
				decl_arg *sub_ref = locate_struct_member(ref_type->strct, sub_var);

				if (sub_ref) {
					if (!validate_set_value_ex(data, set->inner[i], sub_ref, ref_type->strct->args)) {
						return 0;
					}
				}
			}
		}
	} else if (set->count == 1) {
		/* to_array(ptr, to_string(*ptr)) */
		decl_var *sub_var = set->inner[0]->vars->vars[0];
		decl_arg *sub_ref = locate_decl_var_arg(sub_var, ref_list, ref);

		if (sub_ref) {
			if (strcmp(sub_var->name, set_var->name)) {
				data->error(sub_var->token, E_WARNING, "Inner `set` statement casts on pointers must reference the same variable");
				return 0;
			}
			if (!validate_set_value_ex(data, set->inner[0], sub_ref, ref_list)) {
				return 0;
			}
		}
	} else if (set->count > 1) {
		data->error(set->func->token, E_WARNING, "Inner `set` statement casts on pointers may only occur once");
		return 0;
	}

	return 1;
}
static inline int validate_set_value(PSI_Data *data, set_value *set, ...) {
	va_list argp;
	decl_args args = {0};
	int check;

	va_start(argp, set);
	decl_var_arg_v(&args, argp);
	va_end(argp);

	check = validate_set_value_ex(data, set, NULL, &args);
	if (args.args) {
		free(args.args);
	}
	return check;
}
static inline decl *locate_impl_decl(decls *decls, return_stmt *ret) {
	if (decls) {
		size_t i;

		for (i = 0; i < decls->count; ++i) {
			if (!strcmp(decls->list[i]->func->var->name, ret->set->vars->vars[0]->name)) {
				ret->decl = decls->list[i]->func;
				return decls->list[i];
			}
		}
	}

	return NULL;
}
static inline int validate_impl_ret_stmt(PSI_Data *data, impl *impl) {
	return_stmt *ret;

	/* we must have exactly one ret stmt delcaring the native func to call */
	/* and which type cast to apply */
	if (impl->stmts->ret.count != 1) {
		if (impl->stmts->ret.count > 1) {
			data->error(impl->stmts->ret.list[1]->token, PSI_WARNING,
					"Too many `return` statements for implmentation %s;"
					" found %zu, exactly one is needed",
					impl->func->name, impl->stmts->ret.count);
		} else {
			data->error(impl->func->token, PSI_WARNING,
					"Missing `return` statement for implementation %s",
					impl->func->name);
		}
		return 0;
	}

	ret = impl->stmts->ret.list[0];

	if (!(impl->decl = locate_impl_decl(data->decls, ret))) {
		data->error(ret->token, PSI_WARNING,
				"Missing declaration '%s' for `return` statment for implementation %s",
				ret->set->vars->vars[0]->name, impl->func->name);
		return 0;
	}

	if (!validate_set_value(data, ret->set, 1, &ret->decl, impl->decl->args ? (int) impl->decl->args->count : 0, impl->decl->args ? impl->decl->args->args : NULL, 0)) {
		return 0;
	}

	impl->decl->impl = impl;

	return 1;
}

static inline int validate_impl_let_stmts(PSI_Data *data, impl *impl) {
	size_t i, j;
	/* we can have multiple let stmts */

	/* check that we have a decl arg for every let stmt */
	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];
		decl_var *let_var;
		int check = 0;

		if (let->val && let->val->kind == PSI_LET_TMP) {
			let_var = let->val->data.var;
		} else {
			let_var = let->var;
		}

		if (!locate_decl_var_arg(let_var, impl->decl->args, impl->decl->func)) {
			data->error(let_var->token, PSI_WARNING, "Unknown variable '%s' in `let` statement"
					" of implementation '%s'", let_var->name, impl->func->name);
			return 0;
		}

		switch (let->val->kind) {
		case PSI_LET_NULL:
			break;
		case PSI_LET_TMP:
			/* e.g. let bar = &strval($bar); // decl_arg(char **bar) */
			/* e.g. let foo = *bar;  */
			let->var->pointer_level = let->val->data.var->pointer_level;
			let->var->arg = init_decl_arg(
					init_decl_type(
							real_decl_type(let->val->data.var->arg->type)->type,
							real_decl_type(let->val->data.var->arg->type)->name),
					init_decl_var(
							let->var->name,
							let->var->pointer_level,
							let->var->array_size));
			break;
		case PSI_LET_NUMEXP:
			if (!validate_num_exp(data, impl->decl->args, impl->decl->func, let->val->data.num)) {
				return 0;
			}
			break;
		case PSI_LET_CALLOC:
			if (!validate_num_exp(data, impl->decl->args, impl->decl->func, let->val->data.alloc->nmemb)) {
				return 0;
			}
			if (!validate_num_exp(data, impl->decl->args, impl->decl->func, let->val->data.alloc->size)) {
				return 0;
			}
			break;
		case PSI_LET_FUNC:
			if (impl->func->args) {
				for (j = 0; j < impl->func->args->count; ++j) {
					impl_arg *iarg = impl->func->args->args[j];

					if (!strcmp(let->val->data.func->var->name, iarg->var->name)) {
						let->val->data.func->arg = iarg;
						check = 1;
						break;
					}
				}
			}
			if (!check) {
				data->error(let->var->token, PSI_WARNING, "Unknown value '$%s' of `let` statement"
						" for variable '%s' of implementation '%s'",
						let->val->data.func->var->name, let->var->name, impl->func->name);
				return 0;
			}
			break;
		}
	}

	/* check that we have a let stmt for every decl arg */
	if (impl->decl->args) for (i = 0; i < impl->decl->args->count; ++i) {
		decl_arg *darg = impl->decl->args->args[i];
		int check = 0;

		for (j = 0; j < impl->stmts->let.count; ++j) {
			let_stmt *let = impl->stmts->let.list[j];

			if (!strcmp(let->var->name, darg->var->name)) {
				darg->let = let;
				check = 1;
				break;
			}
		}
		if (!check) {
			data->error(impl->func->token, PSI_WARNING,
					"Missing `let` statement for arg '%s %.*s%s'"
					" of declaration '%s' for implementation '%s'",
					darg->type->name, (int) darg->var->pointer_level, "*****",
					darg->var->name, impl->decl->func->var->name, impl->func->name);
			return 0;
		}
	}

	return 1;
}
static inline int validate_impl_set_stmts(PSI_Data *data, impl *impl) {
	size_t i, j, k;
	/* we can have any count of set stmts; processing out vars */
	/* check that set stmts reference known variables */
	for (i = 0; i < impl->stmts->set.count; ++i) {
		set_stmt *set = impl->stmts->set.list[i];
		int check = 0;

		if (impl->func->args) for (j = 0; j < impl->func->args->count; ++j) {
			impl_arg *iarg = impl->func->args->args[j];

			if (!strcmp(set->var->name, iarg->var->name)) {
				set->arg = iarg;
				check = 1;
				break;
			}
		}
		if (!check) {
			data->error(set->var->token, PSI_WARNING, "Unknown variable '$%s' of `set` statement"
					" of implementation '%s'",
					set->var->name, impl->func->name);
			return 0;
		}

		for (j = 0; j < set->val->vars->count; ++j) {
			decl_var *set_var = set->val->vars->vars[j];

			check = 0;
			if (impl->decl->args) {
				for (k = 0; k < impl->decl->args->count; ++k) {
					decl_arg *set_arg = impl->decl->args->args[k];

					if (!strcmp(set_var->name, set_arg->var->name)) {
						check = 1;
						set_var->arg = set_arg;
						if (!validate_set_value(data, set->val, 1, &set_arg, 1, &impl->decl->func, impl->decl->args->count, impl->decl->args->args, 0)) {
							return 0;
						}
						break;
					}
				}
			}
			if (!check) {
				for (k = 0; k < impl->stmts->let.count; ++k) {
					let_stmt *let = impl->stmts->let.list[k];

					/* check temp vars */
					if (let->val && let->val->kind == PSI_LET_TMP) {
						if (!strcmp(set_var->name, let->var->name)) {
							check = 1;
							set_var->arg = let->var->arg;
							if (!validate_set_value(data, set->val, 1, &set_var->arg, 1, &impl->decl->func, impl->decl->args->count, impl->decl->args->args, 0)) {
								return 0;
							}
							break;
						}
					}
				}
			}

			if (!check) {
				data->error(set_var->token, PSI_WARNING, "Unknown value '%s' of `set` statement"
						" for variable '$%s' of implementation '%s'",
						set_var->name, set->arg->var->name, impl->func->name);
				return 0;
			}
		}
	}
	return 1;
}
static inline decl *locate_free_decl(decls *decls, free_call *f) {
	if (decls)  {
		size_t i;

		for (i = 0; i < decls->count; ++i) {
			if (!strcmp(decls->list[i]->func->var->name, f->func)) {
				f->decl = decls->list[i];
				return decls->list[i];
			}
		}
	}

	return NULL;
}
static inline int validate_impl_free_stmts(PSI_Data *data, impl *impl) {
	size_t i, j, k, l;
	/* we can have any count of free stmts; freeing any out vars */
	for (i = 0; i < impl->stmts->fre.count; ++i) {
		free_stmt *fre = impl->stmts->fre.list[i];

		for (j = 0; j < fre->calls->count; ++j) {
			free_call *free_call = fre->calls->list[j];

			/* first find the decl of the free func */
			if (!locate_free_decl(data->decls, free_call)) {
				data->error(free_call->token, PSI_WARNING,
						"Missing declaration '%s' in `free` statement"
						" of implementation '%s'",
						free_call->func, impl->func->name);
				return 0;
			}



			/* now check for known vars */
			for (l = 0; l < free_call->vars->count; ++l) {
				int check = 0;
				decl_var *free_var = free_call->vars->vars[l];

				if (!strcmp(free_var->name, impl->decl->func->var->name)) {
					check = 1;
					free_var->arg = impl->decl->func;
				} else if (impl->decl->args) {
					for (k = 0; k < impl->decl->args->count; ++k) {
						decl_arg *free_arg = impl->decl->args->args[k];

						if (!strcmp(free_var->name, free_arg->var->name)) {
							check = 1;
							free_var->arg = free_arg;
							break;
						}
					}
				}

				if (!check) {
					data->error(free_var->token, PSI_WARNING,
							"Unknown variable '%s' of `free` statement"
							" of implementation '%s'",
							free_var->name, impl->func->name);
					return 0;
				}
			}
		}
	}
	return 1;
}
static inline int validate_impl_stmts(PSI_Data *data, impl *impl) {
	if (!impl->stmts) {
 		data->error(impl->func->token, PSI_WARNING,
 				"Missing body for implementation %s!",
 				impl->func->name);
 		return 0;
 	}

	if (!validate_impl_ret_stmt(data, impl)) {
		return 0;
	}

	if (!validate_impl_let_stmts(data, impl)) {
		return 0;
	}
	if (!validate_impl_set_stmts(data, impl)) {
		return 0;
	}
	if (!validate_impl_free_stmts(data, impl)) {
		return 0;
	}

	return 1;
}

static inline int validate_impl_args(PSI_Data *data, impl *impl) {
	int def = 0;
	size_t i;

	for (i = 0; i < impl->func->args->count; ++i) {
		impl_arg *iarg = impl->func->args->args[i];

		if (iarg->def) {
			def = 1;
		} else if (def) {
			data->error(impl->func->token, PSI_WARNING,
					"Non-optional argument %zu '$%s' of implementation '%s'"
					" follows optional argument",
					i+1, iarg->var->name, impl->func->name);
			return 0;
		}
	}

	return 1;
}
static inline int validate_impl(PSI_Data *data, impl *impl) {
	if (!validate_impl_args(data, impl)) {
		return 0;
	}
	return validate_impl_stmts(data, impl);
}


int PSI_ContextValidate(PSI_Context *C, PSI_Parser *P)
{
	PSI_Data *D;
	void *dlopened = NULL;
	size_t count = C->count++;

	C->data = realloc(C->data, C->count * sizeof(*C->data));
	D = PSI_DataExchange(&C->data[count], PSI_DATA(P));

	if (D->defs) {
		size_t i;

		for (i = 0; i < D->defs->count; ++i) {
			if (validate_decl_typedef(PSI_DATA(C), D->defs->list[i])) {
				C->defs = add_decl_typedef(C->defs, D->defs->list[i]);
			}
		}
	}
	if (D->structs) {
		size_t i;

		for (i = 0; i < D->structs->count; ++i) {
			if (validate_decl_struct(PSI_DATA(C), D->structs->list[i])) {
				C->structs = add_decl_struct(C->structs, D->structs->list[i]);
			}
		}
	}
	if (D->consts) {
		size_t i;

		for (i = 0; i < D->consts->count; ++i) {
			if (validate_constant(PSI_DATA(C), D->consts->list[i])) {
				C->consts = add_constant(C->consts, D->consts->list[i]);
			}
		}
	}

	if (!validate_lib(D, &dlopened)) {
		return 0;
	}

	add_decl_lib(&C->psi.libs, dlopened);

	if (D->decls) {
		size_t i;

		for (i = 0; i < D->decls->count; ++i) {
			if (validate_decl(PSI_DATA(C), dlopened, D->decls->list[i])) {
				C->decls = add_decl(C->decls, D->decls->list[i]);
			}
		}
	}
	if (D->impls) {
		size_t i;

		for (i = 0; i < D->impls->count; ++i) {
			if (validate_impl(PSI_DATA(C), D->impls->list[i])) {
				C->impls = add_impl(C->impls, D->impls->list[i]);
			}
		}
	}

	return 1;
}

int PSI_ContextValidateData(PSI_Data *dest, PSI_Data *source)
{
	size_t i;
	int errors = 0;

	if (source->defs) for (i = 0; i < source->defs->count; ++i) {
		decl_typedef *def = source->defs->list[i];

		if (validate_decl_typedef(source, def)) {
			if (dest) {
				dest->defs = add_decl_typedef(dest->defs, def);
			}
		} else {
			++errors;
		}
	}

	if (source->consts) for (i = 0; i < source->consts->count; ++i) {
		constant *constant = source->consts->list[i];

		if (validate_constant(source, constant)) {
			if (dest) {
				dest->consts = add_constant(dest->consts, constant);
			}
		} else {
			++errors;
		}
	}

	if (source->structs) for (i = 0; i < source->structs->count; ++i) {
		decl_struct *dstruct = source->structs->list[i];

		if (validate_decl_struct(source, dstruct)) {
			if (dest) {
				dest->structs = add_decl_struct(dest->structs, dstruct);
			}
		} else {
			++errors;
		}
	}

	if (source->decls) for (i = 0; i < source->decls->count; ++i) {
		decl *decl = source->decls->list[i];

		if (validate_decl(source, NULL, decl)) {
			if (dest) {
				dest->decls = add_decl(dest->decls, decl);
			}
		} else {
			++errors;
		}
	}

	if (source->impls) for (i = 0; i < source->impls->count; ++i) {
		impl *impl = source->impls->list[i];

		if (validate_impl(source, impl)) {
			if (dest) {
				dest->impls = add_impl(dest->impls, impl);
			}
		} else {
			++errors;
		}
	}

	return errors;
}
