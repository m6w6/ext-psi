#include <sys/param.h>
#include <dlfcn.h>
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_scandir.h"
#include "php_psi.h"
#include "context.h"
#include "parser.h"

#define psi_predef_count(of) ((sizeof(psi_predef ##of## s)/sizeof(psi_predef ##of))-1)
typedef struct psi_predef_type {
	token_t type_tag;
	const char *type_name;
	const char *alias;
} psi_predef_type;
static const psi_predef_type psi_predef_types[] = {
	PHP_PSI_TYPES{0}
};
#define psi_predef_type_count() psi_predef_count(_type)

typedef struct psi_predef_const {
	token_t type_tag;
	const char *type_name;
	const char *name;
	const char *val_text;
	token_t val_type_tag;
} psi_predef_const;
static const psi_predef_const psi_predef_consts[] = {
	PHP_PSI_CONSTS{0}
};
#define psi_predef_const_count() psi_predef_count(_const)

typedef struct psi_predef_struct_member {
	token_t type_tag;
	const char *type_name;
	const char *name;
	size_t off;
	size_t len;
	size_t pointer_level;
	size_t array_size;
} psi_predef_struct_member;
#define PSI_PREDEF_STRUCT_MEMBERS 32
typedef struct psi_predef_struct {
	const char *name;
	size_t size;
	psi_predef_struct_member members[PSI_PREDEF_STRUCT_MEMBERS];
} psi_predef_struct;
static const psi_predef_struct psi_predef_structs[] = {
	PHP_PSI_STRUCTS{0}
};
#define psi_predef_struct_count() psi_predef_count(_struct)

PHP_PSI_MACROS

typedef struct psi_predef_func {
	const char *name;
	void (*func)(void);
} psi_predef_func;
static psi_predef_func psi_predef_funcs[] = {
	PHP_PSI_FUNCS{0}
};
#define psi_predef_func_count() psi_predef_count(_func)

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
			data->error(PSI_WARNING, "Library name too long: '%s'", ptr);
		}
		lib[len] = 0;
		ptr = lib;
	}
	if (!(*dlopened = dlopen(ptr, RTLD_LAZY|RTLD_LOCAL))) {
		data->error(PSI_WARNING, "Could not open library '%s': %s.",
				data->psi.file.ln, dlerror());
		return 0;
	}
	return 1;
}

static inline int locate_decl_type_alias(decl_typedefs *defs, decl_type *type) {
	size_t i;

	if (type->real) {
		return 1;
	}
	for (i = 0; i < defs->count; ++i) {
		if (!strcmp(defs->list[i]->alias, type->name)) {
			type->real = defs->list[i]->type;
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
	case PSI_T_NAME:
		if (!data->defs || !locate_decl_type_alias(data->defs, type)) {
			return 0;
		}
		return validate_decl_type(data, type->real);
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
		data->error(PSI_WARNING, "Type '%s' cannot be aliased to '%s'",
			def->type->name, def->alias);
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
		data->error(PSI_WARNING, "Cannot use '%s' as type for '%s'",
			arg->type->name, arg->var->name);
		return 0;
	}
	return 1;
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

		if (!darg->layout) {
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
	return 1;
}

static const char * const abi_ccs[] = {
		"default", /* \                 */
		"extern",  /*  > - all the same */
		"cdecl",   /* /                 */
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
	data->error(PSI_WARNING, "Invalid calling convention: '%s'", abi->convention);
	return 0;
}
static inline int validate_decl_func(PSI_Data *data, void *dl, decl *decl, decl_arg *func)
{
	if (!strcmp(func->var->name, "dlsym")) {
		data->error(PSI_WARNING, "Cannot dlsym dlsym (sic!)");
		return 0;
	}

	if (!validate_decl_arg(data, func)) {
		return 0;
	}
#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
	decl->dlptr = dlsym(dl ?: RTLD_NEXT, func->var->name);
	if (!decl->dlptr) {
		size_t i;

		for (i = 0; i < psi_predef_func_count(); ++i) {
			psi_predef_func *pre = &psi_predef_funcs[i];

			if (!strcmp(func->var->name, pre->name)) {
				decl->dlptr = pre->func;
				break;
			}
		}
		if (!decl->dlptr) {
			data->error(PSI_WARNING, "Failed to locate symbol '%s': %s",
				func->var->name, dlerror());
		}
	}
	return 1;
}

static inline int validate_decl(PSI_Data *data, void *dl, decl *decl) {
	if (!validate_decl_abi(data, decl->abi)) {
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

static inline decl_arg *locate_struct_member(decl_struct *s, decl_var *var) {
	size_t i;

	ZEND_ASSERT(s);
	for (i = 0; i < s->args->count; ++i) {
		decl_arg *darg = s->args->args[i];

		if (!strcmp(var->name, darg->var->name)) {
			return var->arg = darg;
		}
	}

	return NULL;
}
static inline int validate_set_value(PSI_Data *data, set_value *set, decl_arg *ref) {
	size_t i;
	decl_type *ref_type = real_decl_type(ref->type);
	decl_var *set_var = set->vars->vars[0];

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
	EMPTY_SWITCH_DEFAULT_CASE();
	}

	if (strcmp(set_var->name, ref->var->name)) {
		return 0;
	}

	if (set->count && (set->func->type != PSI_T_TO_ARRAY || ref_type->type != PSI_T_STRUCT)) {
		data->error(E_WARNING, "Inner `set` statement casts only work with to_array() casts on structs");
		return 0;
	}
	for (i = 0; i < set->count; ++i) {
		decl_var *sub_var = set->inner[i]->vars->vars[0];
		decl_arg *sub_ref = locate_struct_member(ref_type->strct, sub_var);

		if (sub_ref) {
			if (!validate_set_value(data, set->inner[i], sub_ref)) {
				return 0;
			}
		}
	}

	return 1;
}
static inline decl *locate_impl_decl(decls *decls, return_stmt *ret) {
	size_t i;

	for (i = 0; i < decls->count; ++i) {
		if (!strcmp(decls->list[i]->func->var->name, ret->set->vars->vars[0]->name)) {
			ret->decl = decls->list[i]->func;
			return decls->list[i];
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
			data->error(PSI_WARNING, "Too many `return` statements for implmentation %s;"
					" found %zu, exactly one is needed",
					impl->func->name, impl->stmts->ret.count);
		} else {
			data->error(PSI_WARNING, "Missing `return` statement for implementation %s",
					impl->func->name);
		}
		return 0;
	}

	ret = impl->stmts->ret.list[0];

	if (!(impl->decl = locate_impl_decl(data->decls, ret))) {
		data->error(PSI_WARNING, "Missing declaration for implementation %s",
				impl->func->name);
		return 0;
	}
	if (!validate_set_value(data, ret->set, ret->decl)) {
		return 0;
	}

	return 1;
}
static inline int validate_impl_let_stmts(PSI_Data *data, impl *impl) {
	size_t i, j;
	/* we can have multiple let stmts */
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
			data->error(PSI_WARNING, "Missing `let` statement for arg '%s %.*s%s'"
					" of declaration '%s' for implementation '%s'",
					darg->type->name, (int) darg->var->pointer_level, "*****",
					darg->var->name, impl->decl->func->var->name, impl->func->name);
			return 0;
		}
	}
	/* check that the let_value references a known variable or NULL */
	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];
		int check = 0;

		if (let->val && let->val->func && let->val->func->alloc) {
			if (!validate_decl_type(data, let->val->func->alloc->type)) {
				data->error(PSI_WARNING, "Cannot use '%s' as type for calloc in `let` statement",
					let->val->func->alloc->type->name);
				return 0;
			}
		}
		if (let->val && let->val->var) {
			if (impl->func->args) for (j = 0; j < impl->func->args->count; ++j) {
				impl_arg *iarg = impl->func->args->args[j];

				if (!strcmp(let->val->var->name, iarg->var->name)) {
					let->arg = iarg;
					check = 1;
					break;
				}
			}
			if (!check) {
				data->error(PSI_WARNING, "Unknown value '$%s' of `let` statement"
						" for variable '%s' of implementation '%s'",
						let->val->var->name, let->var->name, impl->func->name);
				return 0;
			}
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
			data->error(PSI_WARNING, "Unknown variable '$%s' of `set` statement"
					" of implementation '%s'",
					set->var->name, impl->func->name);
			return 0;
		}

		for (j = 0; j < set->val->vars->count; ++j) {
			decl_var *set_var = set->val->vars->vars[j];

			check = 0;
			if (impl->decl->args) for (k = 0; k < impl->decl->args->count; ++k) {
				decl_arg *set_arg = impl->decl->args->args[k];

				if (!strcmp(set_var->name, set_arg->var->name)) {
					check = 1;
					if (!validate_set_value(data, set->val, set_arg)) {
						return 0;
					}
					set_var->arg = set_arg;
					break;
				}
			}

			if (!check) {
				data->error(PSI_WARNING, "Unknown value '%s' of `set` statement"
						" for variable '$%s' of implementation '%s'",
						set_var->name, set->arg->var->name, impl->func->name);
				return 0;
			}
		}
	}
	return 1;
}
static inline decl *locate_free_decl(decls *decls, free_call *f) {
	size_t i;

	for (i = 0; i < decls->count; ++i) {
		if (!strcmp(decls->list[i]->func->var->name, f->func)) {
			f->decl = decls->list[i];
			return decls->list[i];
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
				data->error(PSI_WARNING, "Unknown function '%s' in `free` statement"
						" of implementation '%s'", free_call->func, impl->func->name);
				return 0;
			}
			if (!impl->decl->args) {
				data->error(PSI_WARNING, "Declaration '%s' of implementation '%s'"
						" does not have any arguments to free",
						impl->decl->func->var->name, impl->func->name);
			}

			/* now check for known vars */
			for (l = 0; l < free_call->vars->count; ++l) {
				int check = 0;
				decl_var *free_var = free_call->vars->vars[l];

				for (k = 0; k < impl->decl->args->count; ++k) {
					decl_arg *free_arg = impl->decl->args->args[k];

					if (!strcmp(free_var->name, free_arg->var->name)) {
						check = 1;
						free_var->arg = free_arg;
						break;
					}
				}

				if (!check) {
					data->error(PSI_WARNING, "Unknown variable '%s' of `free` statement"
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
 		data->error(PSI_WARNING, "Missing body for implementation %s!",
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

PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error)
{
	size_t i, j;
	PSI_Data T;

	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	C->error = error;
	C->ops = ops;
	ops->init(C);

	/* build up predefs in a temporary PSI_Data for validation */
	memset(&T, 0, sizeof(T));
	T.error = error;

	for (i = 0; i < psi_predef_type_count(); ++i) {
		const psi_predef_type *pre = &psi_predef_types[i];
		decl_type *type = init_decl_type(pre->type_tag, pre->type_name);
		decl_typedef *def = init_decl_typedef(pre->alias, type);

		T.defs = add_decl_typedef(T.defs, def);
	}
	for (i = 0; i < psi_predef_const_count(); ++i) {
		const psi_predef_const *pre = &psi_predef_consts[i];
		impl_def_val *val = init_impl_def_val(pre->val_type_tag, pre->val_text);
		const_type *type = init_const_type(pre->type_tag, pre->type_name);
		constant *constant = init_constant(type, pre->name, val);

		T.consts = add_constant(T.consts, constant);
	}
	for (i = 0; i < psi_predef_struct_count(); ++i) {
		const psi_predef_struct *pre = &psi_predef_structs[i];
		decl_args *dargs = init_decl_args(NULL);
		decl_struct *dstruct;

		for (j = 0; j < PSI_PREDEF_STRUCT_MEMBERS; ++j) {
			const psi_predef_struct_member *member = &pre->members[j];
			decl_type *type;
			decl_var *dvar;
			decl_arg *darg;

			if (!member->name) {
				break;
			}

			type = init_decl_type(member->type_tag, member->type_name);
			dvar = init_decl_var(member->name, member->pointer_level, member->array_size);
			darg = init_decl_arg(type, dvar);
			darg->layout = init_decl_struct_layout(member->off, member->len);
			dargs = add_decl_arg(dargs, darg);
		}

		dstruct = init_decl_struct(pre->name, dargs);
		dstruct->size = pre->size;
		T.structs = add_decl_struct(T.structs, dstruct);
	}

	for (i = 0; i < psi_predef_type_count(); ++i) {
		decl_typedef *def = T.defs->list[i];

		if (validate_decl_typedef(&T, def)) {
			C->defs = add_decl_typedef(C->defs, def);
		}
	}

	for (i = 0; i < psi_predef_const_count(); ++i) {
		constant *constant = T.consts->list[i];

		if (validate_constant(&T, constant)) {
			C->consts = add_constant(C->consts, constant);
		}
	}

	for (i = 0; i < psi_predef_struct_count(); ++i) {
		decl_struct *dstruct = T.structs->list[i];

		if (validate_decl_struct(&T, dstruct)) {
			C->structs = add_decl_struct(C->structs, dstruct);
		}
	}

	C->count = 1;
	C->data = malloc(sizeof(*C->data));
	PSI_DataExchange(C->data, &T);

	return C;
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
			if (validate_impl_stmts(PSI_DATA(C), D->impls->list[i])) {
				C->impls = add_impl(C->impls, D->impls->list[i]);
			}
		}
	}

	return 1;
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
#define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}

void PSI_ContextBuild(PSI_Context *C, const char *paths)
{
	int i, n;
	char *sep = NULL, *cpy = strdup(paths), *ptr = cpy;
	struct dirent **entries = NULL;


	do {
		sep = strchr(ptr, ':');

		if (sep) {
			*sep = 0;
		}

		n = php_scandir(ptr, &entries, psi_select_dirent, alphasort);

		if (n > 0) {
			for (i = 0; i < n; ++i) {
				char psi[MAXPATHLEN];
				PSI_Parser P;

				if (MAXPATHLEN <= slprintf(psi, MAXPATHLEN, "%s/%s", ptr, entries[i]->d_name)) {
					C->error(PSI_WARNING, "Path to PSI file too long: %s/%s",
						ptr, entries[i]->d_name);
				}
				if (!PSI_ParserInit(&P, psi, C->error, 0)) {
					C->error(PSI_WARNING, "Failed to init PSI parser (%s): %s",
						psi, strerror(errno));
					continue;
				}

				while (-1 != PSI_ParserScan(&P)) {
					PSI_ParserParse(&P, PSI_TokenAlloc(&P));
				};
				PSI_ParserParse(&P, NULL);
				PSI_ContextValidate(C, &P);
				PSI_ParserDtor(&P);
			}
		}

		if (entries) {
			for (i = 0; i < n; ++i) {
				free(entries[i]);
			}
			free(entries);
		}

		ptr = sep + 1;
	} while (sep);


	if (PSI_ContextCompile(C) && SUCCESS != zend_register_functions(NULL, C->closures, NULL, MODULE_PERSISTENT)) {
		C->error(PSI_WARNING, "Failed to register functions!");
	}

	free(cpy);

}

zend_function_entry *PSI_ContextCompile(PSI_Context *C)
{
	size_t i;

	if (C->consts) {
		zend_constant zc;

		zc.flags = CONST_PERSISTENT|CONST_CS;
		zc.module_number = EG(current_module)->module_number;

		for (i = 0; i < C->consts->count; ++i) {
			constant *c = C->consts->list[i];

			zc.name = zend_string_init(c->name + (c->name[0] == '\\'), strlen(c->name) - (c->name[0] == '\\'), 1);
			ZVAL_NEW_STR(&zc.value, zend_string_init(c->val->text, strlen(c->val->text), 1));

			switch (c->type->type) {
			case PSI_T_BOOL:
				convert_to_boolean(&zc.value);
				break;
			case PSI_T_INT:
				convert_to_long(&zc.value);
				break;
			case PSI_T_FLOAT:
				convert_to_double(&zc.value);
				break;
			}
			zend_register_constant(&zc);
		}
	}


	return C->closures = C->ops->compile(C);
}


void PSI_ContextCall(PSI_Context *C, impl_val *ret_val, decl *decl, impl_val **args)
{
	C->ops->call(C, ret_val, decl, args);
}

void PSI_ContextDtor(PSI_Context *C)
{
	size_t i;

	C->ops->dtor(C);

	free_decl_libs(&C->psi.libs);

	for (i = 0; i < C->count; ++i) {
		PSI_DataDtor(&C->data[i]);
	}

	free(C->data);
	free(C->closures);

	if (C->consts) {
		if (C->consts->list) {
			free(C->consts->list);
		}
		free(C->consts);
	}
	if (C->defs) {
		if (C->defs->list) {
			free(C->defs->list);
		}
		free(C->defs);
	}
	if (C->structs) {
		if (C->structs->list) {
			free(C->structs->list);
		}
		free(C->structs);
	}
	if (C->decls) {
		if (C->decls->list) {
			free(C->decls->list);
		}
		free(C->decls);
	}
	if (C->impls) {
		if (C->impls->list) {
			free(C->impls->list);
		}
		free(C->impls);
	}

	memset(C, 0, sizeof(*C));
}

void PSI_ContextFree(PSI_Context **C)
{
	if (*C) {
		PSI_ContextDtor(*C);
		free(*C);
		*C = NULL;
	}
}
