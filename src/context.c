#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#ifdef HAVE_DIRENT_H
# include <dirent.h>
# define NAMLEN(dirent) strlen ((dirent)->d_name)
#else
# define dirent direct
# define NAMLEN(dirent) ((dirent)->d_namlen)
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif

#include <fnmatch.h>

#include "php.h"
#include "php_scandir.h"
#include "php_psi.h"
#include "calc.h"
#include "libjit.h"
#include "libffi.h"

#include "php_psi_types.h"
#include "php_psi_consts.h"
#include "php_psi_decls.h"
#include "php_psi_va_decls.h"
#include "php_psi_structs.h"


PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error, unsigned flags)
{
	PSI_Data T;
	struct psi_predef_type *predef_type;
	struct psi_predef_const *predef_const;
	struct psi_predef_struct *predef_struct;
	struct psi_predef_decl *predef_decl;

	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	C->error = error;
	C->flags = flags;
	C->ops = ops;

	if (ops->init) {
		ops->init(C);
	}

	ZEND_ASSERT(ops->call != NULL);
	ZEND_ASSERT(ops->compile != NULL);

	/* build up predefs in a temporary PSI_Data for validation */
	memset(&T, 0, sizeof(T));
	T.error = error;

	for (predef_type = &psi_predef_types[0]; predef_type->type_tag; ++predef_type) {
		decl_type *type = init_decl_type(predef_type->type_tag, predef_type->type_name);
		decl_var *var = init_decl_var(predef_type->alias, 0, 0); /* FIXME: indirection */
		decl_arg *def = init_decl_arg(type, var);

		T.defs = add_decl_typedef(T.defs, def);
	}
	for (predef_const = &psi_predef_consts[0]; predef_const->type_tag; ++predef_const) {
		impl_def_val *val = init_impl_def_val(predef_const->val_type_tag, predef_const->val_text);
		const_type *type = init_const_type(predef_const->type_tag, predef_const->type_name);
		constant *constant = init_constant(type, predef_const->var_name, val);

		T.consts = add_constant(T.consts, constant);
	}
	for (predef_struct = &psi_predef_structs[0]; predef_struct->type_tag; ++predef_struct) {
		struct psi_predef_struct *member;
		decl_args *dargs = init_decl_args(NULL);
		decl_struct *dstruct = init_decl_struct(predef_struct->var_name, dargs);

		dstruct->size = predef_struct->size;
		for (member = &predef_struct[1]; member->type_tag; ++member) {
			decl_type *type;
			decl_var *dvar;
			decl_arg *darg;

			type = init_decl_type(member->type_tag, member->type_name);
			dvar = init_decl_var(member->var_name, member->pointer_level, member->array_size);
			darg = init_decl_arg(type, dvar);
			darg->layout = init_decl_struct_layout(member->offset, member->size);
			dargs = add_decl_arg(dargs, darg);
		}

		T.structs = add_decl_struct(T.structs, dstruct);
		predef_struct = member;
	}
	for (predef_decl = &psi_predef_decls[0]; predef_decl->type_tag; ++predef_decl) {
		struct psi_predef_decl *farg;
		decl_type *ftype = init_decl_type(predef_decl->type_tag, predef_decl->type_name);
		decl_var *fname = init_decl_var(predef_decl->var_name, predef_decl->pointer_level, predef_decl->array_size);
		decl_arg *func = init_decl_arg(ftype, fname);
		decl_args *args = init_decl_args(NULL);
		decl *decl = init_decl(init_decl_abi("default"), func, args);

		for (farg = &predef_decl[1]; farg->type_tag; ++farg) {
			decl_type *arg_type = init_decl_type(farg->type_tag, farg->type_name);
			decl_var *arg_var = init_decl_var(farg->var_name, farg->pointer_level, farg->array_size);
			decl_arg *darg = init_decl_arg(arg_type, arg_var);
			args = add_decl_arg(args, darg);
		}

		T.decls = add_decl(T.decls, decl);
		predef_decl = farg;
	}

	for (predef_decl = &psi_predef_vararg_decls[0]; predef_decl->type_tag; ++predef_decl) {
		struct psi_predef_decl *farg;
		decl_type *ftype = init_decl_type(predef_decl->type_tag, predef_decl->type_name);
		decl_var *fname = init_decl_var(predef_decl->var_name, predef_decl->pointer_level, predef_decl->array_size);
		decl_arg *func = init_decl_arg(ftype, fname);
		decl_args *args = init_decl_args(NULL);
		decl *decl = init_decl(init_decl_abi("default"), func, args);

		for (farg = &predef_decl[1]; farg->type_tag; ++farg) {
			decl_type *arg_type = init_decl_type(farg->type_tag, farg->type_name);
			decl_var *arg_var = init_decl_var(farg->var_name, farg->pointer_level, farg->array_size);
			decl_arg *darg = init_decl_arg(arg_type, arg_var);
			args = add_decl_arg(args, darg);
		}
		args->varargs = 1;

		T.decls = add_decl(T.decls, decl);
		predef_decl = farg;
	}

	PSI_ContextValidateData(PSI_DATA(C), &T);

	C->count = 1;
	C->data = malloc(sizeof(*C->data));
	PSI_DataExchange(C->data, &T);

	return C;
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
					C->error(C, NULL, PSI_WARNING, "Path to PSI file too long: %s/%s",
						ptr, entries[i]->d_name);
				}
				if (!PSI_ParserInit(&P, psi, C->error, C->flags)) {
					C->error(C, NULL, PSI_WARNING, "Failed to init PSI parser (%s): %s",
						psi, strerror(errno));
					continue;
				}

				while (0 < PSI_ParserScan(&P)) {
					PSI_ParserParse(&P, PSI_TokenAlloc(&P));
					if (P.num == PSI_T_EOF) {
						break;
					}
				}

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
		C->error(C, NULL, PSI_WARNING, "Failed to register functions!");
	}

	free(cpy);

}

zend_function_entry *PSI_ContextCompile(PSI_Context *C)
{
	size_t i;
	zend_constant zc;

	zc.flags = CONST_PERSISTENT|CONST_CS;
	zc.module_number = EG(current_module)->module_number;

	if (C->consts) {
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
	if (C->enums) {
		for (i = 0; i < C->enums->count; ++i) {
			decl_enum *e = C->enums->list[i];
			size_t j;

			for (j = 0; j < e->items->count; ++j) {
				decl_enum_item *i = e->items->list[j];
				zend_string *name = strpprintf(0, "psi\\%s\\%s", e->name, i->name);

				zc.name = zend_string_dup(name, 1);
				ZVAL_LONG(&zc.value, psi_long_num_exp(i->num, NULL));
				zend_register_constant(&zc);
				zend_string_release(name);
			}
		}
	}

	return C->closures = C->ops->compile(C);
}


void PSI_ContextCall(PSI_Context *C, decl_callinfo *decl_call, impl_vararg *va)
{
	C->ops->call(C, decl_call, va);
}


void PSI_ContextDtor(PSI_Context *C)
{
	size_t i;
	zend_function_entry *zfe;

	if (C->ops->dtor) {
		C->ops->dtor(C);
	}

	free_decl_libs(&C->psi.libs);

	if (C->data) {
		for (i = 0; i < C->count; ++i) {
			PSI_DataDtor(&C->data[i]);
		}
		free(C->data);
	}

	if (C->closures) {
		for (zfe = C->closures; zfe->fname; ++zfe) {
			free((void *) zfe->arg_info);
		}
		free(C->closures);
	}

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
	if (C->enums) {
		if (C->enums->list) {
			free(C->enums->list);
		}
		free(C->enums);
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
