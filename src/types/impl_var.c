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

#include <Zend/zend_smart_str.h>

struct psi_impl_var *psi_impl_var_init(zend_string *name, bool is_reference)
{
	struct psi_impl_var *var = pecalloc(1, sizeof(*var), 1);

	var->name = zend_string_copy(name);
	var->fqn = zend_string_copy(name);

	var->reference = is_reference;
	return var;
}

struct psi_impl_var *psi_impl_var_copy(struct psi_impl_var *var)
{
	struct psi_impl_var *cpy = pemalloc(sizeof(*cpy), 1);

	*cpy = *var;

	cpy->name = zend_string_copy(cpy->name);
	cpy->fqn = zend_string_copy(cpy->fqn);

	if (cpy->token) {
		cpy->token = psi_token_copy(cpy->token);
	}
	return cpy;
}

void psi_impl_var_free(struct psi_impl_var **var_ptr)
{
	if (*var_ptr) {
		struct psi_impl_var *var = *var_ptr;

		*var_ptr = NULL;
		psi_token_free(&var->token);
		zend_string_release(var->name);
		zend_string_release(var->fqn);
		free(var);
	}
}

void psi_impl_var_dump(struct psi_dump *dump, struct psi_impl_var *var, bool vararg)
{
	PSI_DUMP(dump, "%s%s%s",
		var->reference ? "&" : "",
		vararg ? "..." : "",
		var->name->val);
}

static inline zend_string *psi_impl_var_name_prepend(zend_string *current, zend_string *prepend) {
	smart_str name = {0};

	smart_str_append_ex(&name, prepend, 1);
	smart_str_appendc_ex(&name, '.', 1);
	smart_str_appendl_ex(&name, ZSTR_VAL(current) + 1, ZSTR_LEN(current) - 1, 1);
	return smart_str_extract(&name);
}

bool psi_impl_var_validate(struct psi_data *data, struct psi_impl_var *ivar,
		struct psi_validate_scope *scope)
{
	if (scope && scope->current_let) {
		struct psi_let_exp *current_let_exp = scope->current_let;

		while ((current_let_exp = current_let_exp->outer)) {
			struct psi_impl_var *svar = psi_let_exp_get_impl_var(current_let_exp);
			zend_string *tmp = ivar->fqn;

			ivar->fqn = psi_impl_var_name_prepend(ivar->fqn, svar->name);
			zend_string_release(tmp);
		}
	} else if (scope && scope->current_set) {
		struct psi_set_exp *current_set_exp = scope->current_set;
		while ((current_set_exp = current_set_exp->outer)) {
			struct psi_impl_var *svar = psi_set_exp_get_impl_var(current_set_exp);
			zend_string *tmp = ivar->fqn;

			ivar->fqn = psi_impl_var_name_prepend(ivar->fqn, svar->name);
			zend_string_release(tmp);
		}
	}

	return true;
}
