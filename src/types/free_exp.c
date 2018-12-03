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
#include "call.h"

struct psi_free_exp *psi_free_exp_init(zend_string *func, struct psi_plist *vars)
{
	struct psi_free_exp *f = pecalloc(1, sizeof(*f), 1);
	f->func = zend_string_copy(func);
	f->vars = vars;
	return f;
}

void psi_free_exp_free(struct psi_free_exp **f_ptr)
{
	if (*f_ptr) {
		struct psi_free_exp *f = *f_ptr;

		*f_ptr = NULL;
		psi_token_free(&f->token);
		zend_string_release(f->func);
		psi_plist_free(f->vars);
		if (f->let) {
			free(f->let);
		}
		free(f);
	}
}

void psi_free_exp_dump(struct psi_dump *dump, struct psi_free_exp *call)
{
	size_t l = 0, c = psi_plist_count(call->vars);
	struct psi_decl_var *fvar;

	PSI_DUMP(dump, "%s(", call->func->val);
	while (psi_plist_get(call->vars, l++, &fvar)) {
		psi_decl_var_dump(dump, fvar);
		if (l < c) {
			PSI_DUMP(dump, ", ");
		}
	}
	PSI_DUMP(dump, ")");
}

static inline struct psi_decl *locate_free_decl(struct psi_plist *decls,
		struct psi_free_exp *f)
{
	if (decls) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(decls, i++, &decl)) {
			if (zend_string_equals(decl->func->var->name, f->func)) {
				return f->decl = decl;
			}
		}
	}

	return NULL;
}

bool psi_free_exp_validate(struct psi_data *data, struct psi_free_exp *exp,
		struct psi_validate_scope *scope)
{
	size_t i;
	struct psi_decl_var *free_var;

	/* first find the decl of the free func */
	if (!locate_free_decl(data->decls, exp)) {
		data->error(data, exp->token, PSI_WARNING,
				"Missing declaration '%s' in `free` statement"
				" of implementation '%s'", exp->func->val,
				scope->impl->func->name->val);
		return false;
	}

	/* now check for known vars */
	exp->let = pecalloc(psi_plist_count(exp->vars), sizeof(*exp->let), 1);
	for (i = 0; psi_plist_get(exp->vars, i, &free_var); ++i) {
		if (!psi_impl_get_decl_arg(scope->impl, free_var)) {
			data->error(data, free_var->token, PSI_WARNING,
					"Unknown variable '%s' of `free` statement"
					" of implementation '%s'",
					free_var->name->val, scope->impl->func->name->val);
			return false;
		}

		exp->let[i] = psi_impl_get_let(scope->impl, free_var);
		assert(exp->let[i]);
	}

	return true;
}

void psi_free_exp_exec(struct psi_free_exp *f, struct psi_call_frame *frame)
{
	size_t i;
	void **args;
	struct psi_decl_var *dvar;
	struct psi_call_frame *free_call;
	struct psi_context *ctx = psi_call_frame_get_context(frame);

	free_call = psi_call_frame_init(ctx, f->decl, NULL);
	psi_call_frame_enter(free_call);

	args = psi_call_frame_get_arg_pointers(free_call);
	for (i = 0; psi_plist_get(f->vars, i, &dvar); ++i) {
		struct psi_call_frame_symbol *frame_sym;
		struct psi_let_exp *let = f->let[i]->exp;

		frame_sym = psi_call_frame_fetch_symbol(frame, let->var);
		args[i] = deref_impl_val(frame_sym->ptr, dvar);
	}

	psi_call_frame_do_call(free_call);
	psi_call_frame_free(free_call);
}
