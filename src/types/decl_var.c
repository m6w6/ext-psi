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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif
#include "data.h"

#include <assert.h>

#include <Zend/zend_smart_str.h>

struct psi_decl_var *psi_decl_var_init(zend_string *name, unsigned pl,
		unsigned as)
{
	struct psi_decl_var *v = pecalloc(1, sizeof(*v), 1);
	if (name) {
		v->name = zend_string_copy(name);
		v->fqn = zend_string_copy(name);
	}
	v->pointer_level = pl;
	v->array_size = as;
	return v;
}

struct psi_decl_var *psi_decl_var_copy(struct psi_decl_var *src)
{
	struct psi_decl_var *dest = pecalloc(1, sizeof(*dest), 1);

	*dest = *src;

	if (dest->name) {
		dest->name = zend_string_copy(dest->name);
		dest->fqn = zend_string_copy(dest->fqn);
	}

	if (dest->token) {
		dest->token = psi_token_copy(dest->token);
	}
	return dest;
}

void psi_decl_var_free(struct psi_decl_var **var_ptr)
{
	if (*var_ptr) {
		struct psi_decl_var *var = *var_ptr;

		*var_ptr = NULL;
		psi_token_free(&var->token);
		if (var->name) {
			zend_string_release(var->name);
			zend_string_release(var->fqn);
		}
		free(var);
	}
}

void psi_decl_var_dump(struct psi_dump *dump, struct psi_decl_var *var)
{
	PSI_DUMP(dump, "%s%s",
			psi_t_indirection(var->pointer_level - !!var->array_size),
			var->name ? var->name->val : "/**/");
	if (var->array_size && var->arg->type->type != PSI_T_FUNCTION) {
		PSI_DUMP(dump, "[%u]", var->array_size);
	}
}

static inline zend_string *psi_decl_var_name_prepend(zend_string *current, zend_string *prepend) {
	smart_str name = {0};

	smart_str_alloc(&name, prepend->len + 1 + current->len, 1);
	smart_str_append_ex(&name, prepend, 1);
	smart_str_appendc_ex(&name, '.', 1);
	smart_str_append_ex(&name, current, 1);

	return smart_str_extract(&name);
}

bool psi_decl_var_validate(struct psi_data *data, struct psi_decl_var *dvar,
		struct psi_validate_scope *scope)
{
	bool okay = false;

	if (scope && scope->current_let) {
		struct psi_let_exp *current_let_exp = scope->current_let;

		/* walk up the let expression tree until found */
		while ((current_let_exp = current_let_exp->outer)) {
			struct psi_decl_var *svar = current_let_exp->var;


			if (!okay) {
				struct psi_plist *args = psi_decl_type_get_args(svar->arg->type,
						NULL);

				if (args && psi_decl_arg_get_by_var(dvar, args, NULL)) {
					okay = true;
				} else if (zend_string_equals(svar->name, dvar->name)) {
					dvar->arg = svar->arg;
					okay = true;
				}
			}
			if (okay) {
				zend_string *tmp = dvar->fqn;
				dvar->fqn = psi_decl_var_name_prepend(dvar->fqn, svar->name);
				zend_string_release(tmp);
			}
		}
	} else if (scope && scope->current_set) {
		struct psi_set_exp *current_set_exp = scope->current_set;

		/* walk up the set expression tree until found */
		while ((current_set_exp = current_set_exp->outer)) {
			struct psi_decl_var *svar = psi_set_exp_get_decl_var(
					current_set_exp);

			if (!okay) {
				struct psi_plist *args = psi_decl_type_get_args(svar->arg->type,
						NULL);

				if (args && psi_decl_arg_get_by_var(dvar, args, NULL)) {
					okay = true;
				} else if (zend_string_equals(svar->name, dvar->name)) {
					dvar->arg = svar->arg;
					okay = true;
				}
			}
			if (okay) {
				zend_string *tmp = dvar->fqn;
				dvar->fqn = psi_decl_var_name_prepend(dvar->fqn, svar->name);
				zend_string_release(tmp);
			}
		}
	}

	if (!okay && scope && scope->impl && psi_impl_get_decl_arg(scope->impl, dvar)) {
		okay = true;
	}
	if (!okay && scope && scope->cb_decl && psi_decl_get_arg(scope->cb_decl, dvar)) {
		okay = true;
	}

	return okay;
}

size_t psi_decl_var_get_size(struct psi_decl_var *var)
{
	struct psi_decl_var *decl_var = var->arg->var;
	size_t pointer_level = decl_var->pointer_level - var->pointer_level;

	if (pointer_level) {
		return SIZEOF_VOID_P;
	}

	return psi_decl_type_get_size(var->arg->type, NULL);
}
