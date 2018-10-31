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

#include "php_psi_posix.h"

struct psi_context *psi_context_init(struct psi_context *C, struct psi_context_ops *ops, psi_error_cb error, unsigned flags)
{
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

	return C;
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
# define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}

static bool psi_context_add(struct psi_context *C, struct psi_parser *P)
{
	bool valid;
	struct psi_data *D;
	struct psi_validate_scope scope = {0};

	C->data = realloc(C->data, (C->count + 1) * sizeof(*C->data));
	D = psi_data_exchange(&C->data[C->count++], PSI_DATA(P));

	psi_validate_scope_ctor(&scope);
	scope.defs = &P->preproc->defs;
	valid = psi_validate(&scope, PSI_DATA(C), D);
	psi_validate_scope_dtor(&scope);

	return valid;
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
				struct psi_parser_input *I;

				if (MAXPATHLEN <= slprintf(psi, MAXPATHLEN, "%s/%s", ptr, entries[i]->d_name)) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Path to PSI file too long: %s/%s",
						ptr, entries[i]->d_name);
				}
				if (!psi_parser_init(&P, C->error, C->flags)) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to init PSI parser (%s): %s",
						psi, strerror(errno));
					continue;
				}
				if (!(I = psi_parser_open_file(&P, psi, true))) {
					C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to open PSI file (%s): %s",
						psi, strerror(errno));
					continue;
				}
				psi_parser_parse(&P, I);
				psi_context_add(C, &P);
				psi_parser_dtor(&P);
				psi_parser_input_free(&I);
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

	ZEND_CONSTANT_SET_FLAGS(&zc, CONST_CS|CONST_PERSISTENT, EG(current_module)->module_number);

	if (C->consts) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(C->consts, i++, &c)) {

			if (zend_get_constant(c->name)) {
				continue;
			}

			zc.name = zend_string_copy(c->name);

			switch (c->type->type) {
			case PSI_T_BOOL:
				ZVAL_BOOL(&zc.value, c->val->ival.zend.bval);
				break;
			case PSI_T_INT:
				ZVAL_LONG(&zc.value, c->val->ival.zend.lval);
				break;
			case PSI_T_FLOAT:
			case PSI_T_DOUBLE:
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
				zend_string *name;

				if (psi_decl_type_is_anon(e->name, "enum")) {
					name = strpprintf(0, "psi\\%s", item->name->val);
				} else {
					name = strpprintf(0, "psi\\%s\\%s", e->name->val, item->name->val);
				}

				if (zend_get_constant(name)) {
					zend_string_release(name);
					continue;
				}

				zc.name = zend_string_dup(name, 1);
				ZVAL_LONG(&zc.value, psi_num_exp_get_long(item->num, NULL, NULL));
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

	C->ops->call(frame);

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

void psi_context_dump(struct psi_context *C, int fd)
{
	size_t i;

	dprintf(fd, "// psi.engine=%s\n// %lu files\n",
			(char *) C->ops->query(C, PSI_CONTEXT_QUERY_SELF, NULL),
			C->count);

	for (i = 0; i < C->count; ++i) {
		psi_data_dump(fd, &C->data[i]);
	}
}
