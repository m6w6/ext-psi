/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "php_psi_stdinc.h"

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

#include "php_scandir.h"
#include "php_psi.h"
#include "calc.h"
#include "call.h"
#include "libjit.h"
#include "libffi.h"

#include "token.h"
#include "parser.h"

#define PSI_PREDEF_TYPES
#define PSI_PREDEF_CONSTS
#define PSI_PREDEF_COMPOSITES
#define PSI_PREDEF_DECLS
#include "php_psi_posix.h"

struct psi_context *psi_context_init(struct psi_context *C, struct psi_context_ops *ops, psi_error_cb error, unsigned flags)
{
	struct psi_data T;
	struct psi_predef_type *predef_type;
	struct psi_predef_const *predef_const;
	struct psi_predef_composite *predef_composite;
	struct psi_predef_decl *predef_decl;

	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	psi_data_ctor(PSI_DATA(C), error, flags);
	C->ops = ops;

	if (ops->init) {
		ops->init(C);
	}

	assert(ops->call != NULL);
	assert(ops->compile != NULL);

	/* build up predefs in a temporary PSI_Data for validation */
	memset(&T, 0, sizeof(T));
	psi_data_ctor_with_dtors(&T, error, flags);

	for (predef_type = &psi_predef_types[0]; predef_type->type_tag; ++predef_type) {
		struct psi_decl_type *type = psi_decl_type_init(predef_type->type_tag, predef_type->type_name);
		struct psi_decl_var *var = psi_decl_var_init(predef_type->alias, 0, 0); /* FIXME: indirection */
		struct psi_decl_arg *def = psi_decl_arg_init(type, var);

		T.types = psi_plist_add(T.types, &def);
	}
	for (predef_const = &psi_predef_consts[0]; predef_const->type_tag; ++predef_const) {
		struct psi_const_type *type = psi_const_type_init(predef_const->type_tag, predef_const->type_name);
		struct psi_impl_def_val *val;
		struct psi_const *constant;

		switch (type->type) {
		case PSI_T_INT:
			val = psi_impl_def_val_init(PSI_T_INT, NULL);
			val->ival.zend.lval = predef_const->value.lval;
			break;
		case PSI_T_STRING:
			val = psi_impl_def_val_init(PSI_T_STRING, NULL);
			val->ival.zend.str = zend_string_init(predef_const->value.ptr, strlen(predef_const->value.ptr), 1);
			break;
		default:
			assert(0);
			break;
		}

		constant = psi_const_init(type, predef_const->var_name, val);
		T.consts = psi_plist_add(T.consts, &constant);
	}
	for (predef_composite = &psi_predef_composites[0]; predef_composite->type_tag; ++predef_composite) {
		struct psi_predef_composite *member;
		struct psi_decl_struct *dstruct;
		struct psi_decl_union *dunion;
		struct psi_plist *dargs = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);

		switch (predef_composite->type_tag) {
		case PSI_T_STRUCT:
			dstruct = psi_decl_struct_init(predef_composite->var_name, dargs);
			dstruct->size = predef_composite->size;
			dstruct->align = predef_composite->offset;
			break;
		case PSI_T_UNION:
			dunion = psi_decl_union_init(predef_composite->var_name, dargs);
			dunion->size = predef_composite->size;
			dunion->align = predef_composite->offset;
			break;
		default:
			assert(0);
		}
		for (member = &predef_composite[1]; member->type_tag; ++member) {
			struct psi_decl_type *type;
			struct psi_decl_var *dvar;
			struct psi_decl_arg *darg;

			type = psi_decl_type_init(member->type_tag, member->type_name);
			dvar = psi_decl_var_init(member->var_name, member->pointer_level, member->array_size);
			darg = psi_decl_arg_init(type, dvar);
			darg->layout = psi_layout_init(member->offset, member->size);

			switch (predef_composite->type_tag) {
			case PSI_T_STRUCT:
				dstruct->args = psi_plist_add(dstruct->args, &darg);
				break;
			case PSI_T_UNION:
				dunion->args = psi_plist_add(dunion->args, &darg);
				break;
			default:
				assert(0);
			}
		}
		switch (predef_composite->type_tag) {
		case PSI_T_STRUCT:
			T.structs = psi_plist_add(T.structs, &dstruct);
			break;
		case PSI_T_UNION:
			T.unions = psi_plist_add(T.unions, &dunion);
			break;
		default:
			assert(0);
		}

		predef_composite = member;
	}
	for (predef_decl = &psi_predef_decls[0]; predef_decl->type_tag; ++predef_decl) {
		struct psi_predef_decl *farg;
		struct psi_decl_type *dtype, *ftype = psi_decl_type_init(predef_decl->type_tag, predef_decl->type_name);
		struct psi_decl_var *fname = psi_decl_var_init(predef_decl->var_name, predef_decl->pointer_level, predef_decl->array_size);
		struct psi_decl_arg *tdef, *func = psi_decl_arg_init(ftype, fname);
		struct psi_plist *args = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
		struct psi_decl *decl = psi_decl_init(psi_decl_abi_init("default"), func, args);

		for (farg = &predef_decl[1]; farg->type_tag; ++farg) {
			struct psi_decl_type *arg_type = psi_decl_type_init(farg->type_tag, farg->type_name);
			struct psi_decl_var *arg_var = psi_decl_var_init(farg->var_name, farg->pointer_level, farg->array_size);
			struct psi_decl_arg *darg = psi_decl_arg_init(arg_type, arg_var);
			decl->args = psi_plist_add(decl->args, &darg);
		}

		switch (predef_decl->kind) {
		case DECL_KIND_VARARG:
			decl->varargs = 1;
			/* no break */
		case DECL_KIND_STD:
			T.decls = psi_plist_add(T.decls, &decl);
			break;
		case DECL_KIND_FUNCTOR:
			dtype = psi_decl_type_init(PSI_T_FUNCTION, fname->name);
			dtype->real.func = decl;
			tdef = psi_decl_arg_init(dtype, psi_decl_var_copy(fname));
			T.types = psi_plist_add(T.types, &tdef);
			break;
		default:
			assert(0);
		}

		predef_decl = farg;
	}

	psi_context_add_data(C, &T);

	return C;
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
# define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}

void psi_context_build(struct psi_context *C, const char *paths)
{
	int i, n;
	char *sep = NULL, *cpy = strdup(paths), *ptr = cpy;
	struct dirent **entries;

	do {
		sep = strchr(ptr, ':');

		if (sep) {
			*sep = 0;
		}

		entries = NULL;
		n = php_scandir(ptr, &entries, psi_select_dirent, alphasort);

		if (n > 0) {
			for (i = 0; i < n; ++i) {
				char psi[MAXPATHLEN];
				struct psi_parser P;

				if (MAXPATHLEN <= slprintf(psi, MAXPATHLEN, "%s/%s", ptr, entries[i]->d_name)) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Path to PSI file too long: %s/%s",
						ptr, entries[i]->d_name);
				}
				if (!psi_parser_init(&P, C->error, C->flags)) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to init PSI parser (%s): %s",
						psi, strerror(errno));
					continue;
				}
				if (!psi_parser_open_file(&P, psi)) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to open PSI file (%s): %s",
						psi, strerror(errno));
					continue;
				}

				psi_parser_parse(&P);
				psi_context_add_data(C, PSI_DATA(&P));
				psi_parser_dtor(&P);
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


	if (psi_context_compile(C) && SUCCESS != zend_register_functions(NULL, C->closures, NULL, MODULE_PERSISTENT)) {
		C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to register functions!");
	}

	free(cpy);
}

zend_function_entry *psi_context_compile(struct psi_context *C)
{
	zend_constant zc;

	zc.flags = CONST_PERSISTENT|CONST_CS;
	zc.module_number = EG(current_module)->module_number;

	if (C->consts) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(C->consts, i++, &c)) {

			if (zend_get_constant_str(c->name, strlen(c->name))) {
				continue;
			}

			zc.name = zend_string_init(c->name, strlen(c->name), 1);

			switch (c->type->type) {
			case PSI_T_BOOL:
				ZVAL_BOOL(&zc.value, c->val->ival.zend.bval);
				break;
			case PSI_T_INT:
				ZVAL_LONG(&zc.value, c->val->ival.zend.lval);
				break;
			case PSI_T_FLOAT:
				ZVAL_DOUBLE(&zc.value, c->val->ival.dval);
				break;
			case PSI_T_STRING:
			case PSI_T_QUOTED_STRING:
				ZVAL_NEW_STR(&zc.value, zend_string_copy(c->val->ival.zend.str));
				break;
			default:
				assert(0);
				break;
			}

			zend_register_constant(&zc);
		}
	}

	if (C->enums) {
		size_t i = 0;
		struct psi_decl_enum *e;

		while (psi_plist_get(C->enums, i++, &e)) {
			size_t j = 0;
			struct psi_decl_enum_item *item;

			while (psi_plist_get(e->items, j++, &item)) {
				zend_string *name = strpprintf(0, "psi\\%s\\%s", e->name, item->name);

				zc.name = zend_string_dup(name, 1);
				ZVAL_LONG(&zc.value, psi_long_num_exp(item->num, NULL, NULL));
				zend_register_constant(&zc);
				zend_string_release(name);
			}
		}
	}

	return C->closures = C->ops->compile(C);
}


ZEND_RESULT_CODE psi_context_call(struct psi_context *C, zend_execute_data *execute_data, zval *return_value, struct psi_impl *impl)
{
	struct psi_call_frame *frame;

	frame = psi_call_frame_init(C, impl->decl, impl);

	if (SUCCESS != psi_call_frame_parse_args(frame, execute_data)) {
		psi_call_frame_free(frame);

		return FAILURE;
	}

	psi_call_frame_enter(frame);

	if (SUCCESS != psi_call_frame_do_let(frame)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return FAILURE;
	}

	if (SUCCESS != psi_call_frame_do_assert(frame, PSI_ASSERT_PRE)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return FAILURE;
	}

	psi_call_frame_do_call(frame);

	if (SUCCESS != psi_call_frame_do_assert(frame, PSI_ASSERT_POST)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return FAILURE;
	}

	psi_call_frame_do_return(frame, return_value);
	psi_call_frame_do_set(frame);
	psi_call_frame_do_free(frame);
	psi_call_frame_free(frame);

	return SUCCESS;
}


void psi_context_dtor(struct psi_context *C)
{
	size_t i;
	zend_function_entry *zfe;

	if (C->ops->dtor) {
		C->ops->dtor(C);
	}

	psi_data_dtor(PSI_DATA(C));

	if (C->data) {
		for (i = 0; i < C->count; ++i) {
			psi_data_dtor(&C->data[i]);
		}
		free(C->data);
	}

	if (C->closures) {
		for (zfe = C->closures; zfe->fname; ++zfe) {
			free((void *) zfe->arg_info);
		}
		free(C->closures);
	}
}

void psi_context_free(struct psi_context **C)
{
	if (*C) {
		psi_context_dtor(*C);
		free(*C);
		*C = NULL;
	}
}

bool psi_context_add_data(struct psi_context *C, struct psi_data *P)
{
	struct psi_data *D;

	C->data = realloc(C->data, (C->count + 1) * sizeof(*C->data));
	D = psi_data_exchange(&C->data[C->count++], P);

	return psi_data_validate(PSI_DATA(C), D);
}

void psi_context_dump(struct psi_context *C, int fd)
{

	dprintf(fd, "// psi.engine=%s\n",
			(char *) C->ops->query(C, PSI_CONTEXT_QUERY_SELF, NULL));

	psi_data_dump(fd, PSI_DATA(C));

//	size_t i;
//	dprintf(fd, "/* parsed\n");
//	for (i = 0; i < C->count; ++i) {
//		psi_data_dump(fd, &C->data[i]);
//	}
//	dprintf(fd, "*/\n");

}
