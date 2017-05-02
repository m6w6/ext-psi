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
#include "data.h"

struct psi_let_callback *psi_let_callback_init(struct psi_let_func *func,
		struct psi_plist *args)
{
	struct psi_let_callback *cb = calloc(1, sizeof(*cb));
	cb->func = func;
	cb->args = args;
	return cb;
}

void psi_let_callback_free(struct psi_let_callback **cb_ptr)
{
	if (*cb_ptr) {
		struct psi_let_callback *cb = *cb_ptr;

		*cb_ptr = NULL;
		psi_let_func_free(&cb->func);
		psi_plist_free(cb->args);
		if (cb->token) {
			free(cb->token);
		}
		free(cb);
	}
}

bool psi_let_callback_validate(struct psi_data *data, struct psi_let_exp *exp,
		struct psi_let_callback *cb, struct psi_impl *impl)
{
	size_t i = 0;
	struct psi_decl *cb_func;
	struct psi_decl_type *cb_type;
	struct psi_decl_var *cb_var = exp->var;
	struct psi_set_exp *set_exp;

	cb_type = psi_decl_type_get_real(cb_var->arg->type);
	if (cb_type->type != PSI_T_FUNCTION) {
		data->error(data, cb_var->token, PSI_WARNING,
				"Expected a function: %s",
				cb_var->name);
		return false;
	}
	cb_func = cb_type->real.func;

	while (psi_plist_get(cb->args, i++, &set_exp)) {
		if (!psi_set_exp_validate(data, set_exp, impl, cb_func)) {
			return false;
		}
	}

	if (!psi_decl_validate_nodl(data, cb_func,  NULL /* FIXME type_stack */)) {
		return false;
	}

	cb->decl = cb_func;

	return true;
}

void psi_let_callback_dump(int fd, struct psi_let_callback *callback,
		unsigned level)
{
	dprintf(fd, "callback %s(%s(",
			callback->func->name,
			callback->func->var->name);

	if (callback->args) {
		size_t i = 0, last = psi_plist_count(callback->args);
		struct psi_set_exp *set;

		dprintf(fd, "\n");
		++level;
		while (psi_plist_get(callback->args, i++, &set)) {
			psi_set_exp_dump(fd, set, level, i == last);
			dprintf(fd, "\n");
		}
		--level;
		dprintf(fd, "%s", psi_t_indent(level));
	}
	dprintf(fd, "))");
}
