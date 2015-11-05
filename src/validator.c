#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/param.h>
#include <dlfcn.h>

#include <jit/jit.h>

#include "php.h"
#include "php_psi.h"
#include "validator.h"

PSI_Validator *PSI_ValidatorInit(PSI_Validator *V, PSI_Parser *P)
{
	if (!V) {
		V = malloc(sizeof(*V));
	}
	memset(V, 0, sizeof(*V));

	PSI_DataExchange((PSI_Data *) V, (PSI_Data *) P);

	return V;
}

void PSI_ValidatorDtor(PSI_Validator *V)
{
	PSI_DataDtor((PSI_Data *) V);
	memset(V, 0, sizeof(*V));
}

void PSI_ValidatorFree(PSI_Validator **V)
{
	if (*V) {
		PSI_ValidatorDtor(*V);
		free(*V);
		*V = NULL;
	}
}

static int validate_lib(PSI_Validator *V) {
	char lib[MAXPATHLEN];
	const char *ptr = V->lib;
	size_t len;

	if (!ptr) {
		/* FIXME: assume stdlib */
		return 1;
	} else if (!strchr(ptr, '/')) {
#ifdef DARWIN
		len = snprintf(lib, MAXPATHLEN, "lib%s.dylib", ptr);
#else
		len = snprintf(lib, MAXPATHLEN, "lib%s.so", ptr);
#endif
		if (MAXPATHLEN == len) {
			V->error(PSI_WARNING, "Library name too long: '%s'", ptr);
		}
		lib[len] = 0;
		ptr = lib;
	}
	if (!(V->dlopened = dlopen(ptr, RTLD_LAZY|RTLD_LOCAL))) {
		V->error(PSI_WARNING, "Could not open library '%s': %s.", V->lib, dlerror());
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
static inline int validate_decl_type(PSI_Validator *V, decl_type *type) {
	switch (type->type) {
	case PSI_T_NAME:
		if (!V->defs || !locate_decl_type_alias(V->defs, type)) {
			return 0;
		}
		return validate_decl_type(V, type->real);
	case PSI_T_STRUCT:
		if (!V->structs || !locate_decl_type_struct(V->structs, type)) {
			return 0;
		}
		break;
	}
	return 1;
}
static inline int validate_typedef(PSI_Validator *V, decl_typedef *def) {
	/* FIXME: check def->alias */
	if (def->type->type == PSI_T_NAME) {
		V->error(PSI_WARNING, "Type '%s' cannot be aliased to '%s'",
			def->type->name, def->alias);
		return 0;
	}
	return 1;
}
static inline int validate_typedefs(PSI_Validator *V) {
	size_t i;

	for (i = 0; i < V->defs->count; ++i) {
		if (!validate_typedef(V, V->defs->list[i])) {
			return 0;
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
static inline int validate_decl_abi(PSI_Validator *V, decl_abi *abi) {
	size_t i;

	for (i = 0; i < sizeof(abi_ccs)/sizeof(char*); ++i) {
		if (strcasecmp(abi->convention, abi_ccs[i])) {
			return 1;
		}
	}
	V->error(PSI_WARNING, "Invalid calling convention: '%s'", abi->convention);
	return 0;
}
static inline int validate_decl_arg(PSI_Validator *V, decl_arg *arg) {
	if (!validate_decl_type(V, arg->type)) {
		V->error(PSI_WARNING, "Cannot use '%s' as type for '%s'",
			arg->type->name, arg->var->name);
		return 0;
	}
	return 1;
}
static inline int validate_decl_args(PSI_Validator *V, decl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		if (!validate_decl_arg(V, args->args[i])) {
			return 0;
		}
	}
	return 1;
}
static inline int validate_decl_func(PSI_Validator *V, decl *decl, decl_arg *func)
{
	if (!strcmp(func->var->name, "dlsym")) {
		V->error(PSI_WARNING, "Cannot dlsym dlsym (sic!)");
		return 0;
	}

	if (!validate_decl_arg(V, func)) {
		return 0;
	}
#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
	decl->dlptr = dlsym(V->dlopened ?: RTLD_NEXT, func->var->name);
	if (!decl->dlptr) {
		V->error(PSI_WARNING, "Failed to located symbol '%s': %s",
			func->var->name, dlerror());
	}
	return 1;
}
static inline int validate_decl(PSI_Validator *V, decl *decl) {
	if (!validate_decl_abi(V, decl->abi)) {
		return 0;
	}
	if (!validate_decl_func(V, decl, decl->func)) {
		return 0;
	}
	if (decl->args && !validate_decl_args(V, decl->args)) {
		return 0;
	}
	return 1;
}
static inline int validate_decls(PSI_Validator *V) {
	size_t i;

	for (i = 0; i < V->decls->count; ++i) {
		if (!validate_decl(V, V->decls->list[i])) {
			return 0;
		}
	}
	return 1;
}
static inline int validate_struct(PSI_Validator *V, decl_struct *s) {
	size_t i;

	if (!validate_decl_args(V, s->args)) {
		return 0;
	}

	s->layout = calloc(s->args->count, sizeof(*s->layout));
	for (i = 0; i < s->args->count; ++i) {
		decl_arg *darg = s->args->args[i];
		decl_type *type = real_decl_type(darg->type);
		token_t t = darg->var->pointer_level ? PSI_T_POINTER : type->type;

		if (i) {
			decl_struct_layout *l = &s->layout[i-1];
			s->layout[i].pos = psi_t_align(t, l->pos + l->len);
		} else {
			s->layout[i].pos = 0;
		}
		s->layout[i].len = psi_t_size(t);
	}
	return 1;
}
static inline int validate_structs(PSI_Validator *V) {
	size_t i;

	for (i = 0; i < V->structs->count; ++i) {
		if (!validate_struct(V, V->structs->list[i])) {
			return 0;
		}
	}
	return 1;
}

static inline int validate_impl_type(PSI_Validator *V, impl *impl, impl_type *type) {
	/* FIXME */
	return 1;
}
static inline int validate_impl_arg(PSI_Validator *V, impl *impl, impl_arg *arg) {
	return 1;
}
static inline int validate_impl_args(PSI_Validator *V, impl *impl, impl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		if (!validate_impl_arg(V, impl, args->args[i])) {
			return 0;
		}
	}
	return 1;
}
static inline int validate_impl_func(PSI_Validator *V, impl *impl, impl_func *func) {
	/* FIXME: does name need any validation? */
	if (!validate_impl_type(V, impl, func->return_type)) {
		return 0;
	}
	if (func->args && !validate_impl_args(V, impl, func->args)) {
		return 0;
	}
	return 1;
}

static inline decl *locate_impl_decl(decls *decls, return_stmt *ret) {
	size_t i;

	for (i = 0; i < decls->count; ++i) {
		if (!strcmp(decls->list[i]->func->var->name, ret->decl->name)) {
			ret->decl->arg = decls->list[i]->func;
			return decls->list[i];
		}
	}
	return NULL;
}

static inline int validate_impl_stmts(PSI_Validator *V, impl *impl, impl_stmts *stmts) {
	/* okay,
	 * - we must have exactly one ret stmt delcaring the native func to call and which type cast to apply
	 * - we can have multiple let stmts; every arg of the ret stmts var (the function to call) must have one
	 * - we can have any count of set stmts; processing out vars
	 * - we can have any count of free stmts; freeing any out vars
	 */
	size_t i, j, k;
	return_stmt *ret;
	decl *decl;

	 if (!stmts) {
 		V->error(PSI_WARNING, "Missing body for implementation %s!",
 				impl->func->name);
 		return 0;
 	}
	if (stmts->ret.count != 1) {
		if (stmts->ret.count > 1) {
			V->error(PSI_WARNING, "Too many `ret` statements for implmentation %s;"
					" found %zu, exactly one is needed",
					impl->func->name, stmts->ret.count);
		} else {
			V->error(PSI_WARNING, "Missing `ret` statement for implementation %s",
					impl->func->name);
		}
		return 0;
	}

	ret = stmts->ret.list[0];
	decl = locate_impl_decl(V->decls, ret);
	if (!decl) {
		V->error(PSI_WARNING, "Missing declaration for implementation %s",
				impl->func->name);
		return 0;
	}

	/* check that we have a let stmt for every decl arg */
	if (decl->args) for (i = 0; i < decl->args->count; ++i) {
		decl_arg *darg = decl->args->args[i];
		int check = 0;

		for (j = 0; j < stmts->let.count; ++j) {
			let_stmt *let = stmts->let.list[j];

			if (!strcmp(let->var->name, darg->var->name)) {
				darg->let = let;
				check = 1;
				break;
			}
		}
		if (!check) {
			V->error(PSI_WARNING, "Missing `let` statement for arg '%s %.*s%s'"
					" of declaration '%s' for implementation '%s'",
					darg->type->name, (int) darg->var->pointer_level, "*****",
					darg->var->name, decl->func->var->name, impl->func->name);
			return 0;
		}
	}
	/* check that the let_value references a known variable or NULL */
	for (i = 0; i < stmts->let.count; ++i) {
		let_stmt *let = stmts->let.list[i];
		int check = 0;

		if (let->val && let->val->func && let->val->func->alloc) {
			if (!validate_decl_type(V, let->val->func->alloc->type)) {
				V->error(PSI_WARNING, "Cannot use '%s' as type for calloc in `let` statement",
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
				V->error(PSI_WARNING, "Unknown value '$%s' of `let` statement"
						" for variable '%s' of implementation '%s'",
						let->val->var->name, let->var->name, impl->func->name);
				return 0;
			}
		}
	}
	/* check that set stmts reference known variables */
	for (i = 0; i < stmts->set.count; ++i) {
		set_stmt *set = stmts->set.list[i];
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
			V->error(PSI_WARNING, "Unknown variable '$%s' of `set` statement"
					" of implementation '%s'",
					set->var->name, impl->func->name);
			return 0;
		}

		for (j = 0; j < set->val->vars->count; ++j) {
			decl_var *set_var = set->val->vars->vars[j];

			check = 0;
			if (decl->args) for (k = 0; k < decl->args->count; ++k) {
				decl_arg *set_arg = decl->args->args[k];

				if (!strcmp(set_var->name, set_arg->var->name)) {
					check = 1;
					set_var->arg = set_arg;
					break;
				}
			}

			if (!check) {
				V->error(PSI_WARNING, "Unknown value '%s' of `set` statement"
						" for variable '$%s' of implementation '%s'",
						set_var->name, set->arg->var->name, impl->func->name);
				return 0;
			}
		}
	}
	/* check free stmts */
	for (i = 0; i < stmts->fre.count; ++i) {
		free_stmt *fre = stmts->fre.list[i];

		for (j = 0; j < fre->vars->count; ++j) {
			decl_var *free_var = fre->vars->vars[j];
			int check = 0;

			if (!strcmp(free_var->name, decl->func->var->name)) {
				continue;
			}
			if (decl->args) for (k = 0; k < decl->args->count; ++k) {
				decl_arg *free_arg = decl->args->args[k];

				if (!strcmp(free_var->name, free_arg->var->name)) {
					check = 1;
					free_var->arg = free_arg;
					break;
				}
			}

			if (!check) {
				V->error(PSI_WARNING, "Unknown variable '%s' of `free` statement"
						" of implementation '%s'",
						free_var->name, impl->func->name);
				return 0;
			}
		}
	}

	impl->decl = decl;

	return 1;
}

static inline int validate_impl(PSI_Validator *V, impl *impl) {
	if (!validate_impl_func(V, impl, impl->func)) {
		return 0;
	}
	if (!validate_impl_stmts(V, impl, impl->stmts)) {
		return 0;
	}
	return 1;
}
static inline int validate_impls(PSI_Validator *V) {
	size_t i;

	for (i = 0; i < V->impls->count; ++i) {
		if (!validate_impl(V, V->impls->list[i])) {
			return 0;
		}
	}
	return 1;
}

int PSI_ValidatorValidate(PSI_Validator *V)
{
	if (!validate_lib(V)) {
		return 0;
	}
	if (V->defs && !validate_typedefs(V)) {
		return 0;
	}
	if (V->structs && !validate_structs(V)) {
		return 0;
	}
	if (V->decls && !validate_decls(V)) {
		return 0;
	}
	if (!V->impls || !validate_impls(V)) {
		return 0;
	}
	return 1;
}
