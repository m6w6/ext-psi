/*******************************************************************************
 Copyright (c) 2017, Michael Wallner <mike@php.net>.
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
#include "call.h"

struct psi_return_exp *psi_return_exp_init(struct psi_decl_var *func,
		struct psi_plist *args, struct psi_set_exp *set)
{
	struct psi_return_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->func = func;
	exp->args = args;
	exp->set = set;

	return exp;
}

void psi_return_exp_free(struct psi_return_exp **exp_ptr)
{
	if (*exp_ptr) {
		struct psi_return_exp *exp = *exp_ptr;

		*exp_ptr = NULL;
		psi_token_free(&exp->token);
		if (exp->func) {
			psi_decl_var_free(&exp->func);
		}
		if (exp->args) {
			psi_plist_free(exp->args);
			exp->args = NULL;
		}
		if (exp->set) {
			psi_set_exp_free(&exp->set);
		}
		free(exp);
	}
}

void psi_return_exp_dump(struct psi_dump *dump, struct psi_return_exp *exp)
{
	if (exp->func) {
		psi_decl_var_dump(dump, exp->func);
		PSI_DUMP(dump, "(");
		if (exp->args) {
			size_t i = 0;
			struct psi_decl_var *arg;

			while (psi_plist_get(exp->args, i++, &arg)) {
				if (i > 1) {
					PSI_DUMP(dump, ", ");
				}
				psi_decl_var_dump(dump, arg);
			}
		}
		PSI_DUMP(dump, ")");
	}
	if (exp->set) {
		if (exp->func) {
			PSI_DUMP(dump, " as ");
		}

		psi_set_exp_dump(dump, exp->set, 1, 1);
	}
}

void psi_return_exp_exec(struct psi_return_exp *exp, zval *return_value,
		struct psi_call_frame *frame)
{
	if (exp->set) {
		void *rpointer = psi_call_frame_get_rpointer(frame);

		psi_set_exp_exec_ex(exp->set, return_value, rpointer, frame);
	}
}

static inline bool psi_return_exp_validate_decl_args(struct psi_data *data,
		struct psi_return_exp *exp, struct psi_impl *impl)
{
	size_t i;
	struct psi_decl_var *call_arg;

	if (exp->args) {
		if (psi_plist_count(exp->args) != psi_plist_count(impl->decl->args)) {
			data->error(data, exp->token, PSI_WARNING,
					"Argument count of return statement of implementation '%s' "
					"does not match argument count of declaration '%s'",
					impl->func->name->val, impl->decl->func->var->name->val);
			return false;
		}

		for (i = 0; psi_plist_get(exp->args, i, &call_arg); ++i) {
			psi_plist_get(impl->decl->args, i, &call_arg->arg);
		}
	}
	return true;
}

bool psi_return_exp_validate(struct psi_data *data, struct psi_return_exp *exp,
		struct psi_validate_scope *scope)
{
	size_t i = 0;
	struct psi_decl *decl;
	zend_string *name = psi_return_exp_get_decl_name(exp);


	while (psi_plist_get(data->decls, i++, &decl)) {
		if (zend_string_equals(decl->func->var->name, name)) {
			scope->impl->decl = decl;
			if (psi_return_exp_validate_decl_args(data, exp, scope->impl)) {
				scope->current_set = exp->set;
				if (psi_set_exp_validate(data, exp->set, scope)) {
					scope->current_set = NULL;
					return true;
				}
				scope->current_set = NULL;
			}
			return false;
		}
	}

	data->error(data, exp->token, PSI_WARNING,
			"Missing declaration '%s' for `return` statement of implementation %s",
			name->val, scope->impl->func->name->val);
	return false;
}

zend_string *psi_return_exp_get_decl_name(struct psi_return_exp *exp)
{
	return exp->func ? exp->func->name : exp->set->data.func->var->name;
}

