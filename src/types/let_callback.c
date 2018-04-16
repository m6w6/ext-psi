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
		struct psi_plist *args, struct psi_plist *cb_args)
{
	struct psi_let_callback *cb = calloc(1, sizeof(*cb));
	cb->func = func;
	cb->args = args;
	cb->cb_args = cb_args;
	return cb;
}

void psi_let_callback_free(struct psi_let_callback **cb_ptr)
{
	if (*cb_ptr) {
		struct psi_let_callback *cb = *cb_ptr;

		*cb_ptr = NULL;
		psi_let_func_free(&cb->func);
		psi_plist_free(cb->args);
		if (cb->cb_args) {
			psi_plist_free(cb->cb_args);
		}
		if (cb->token) {
			free(cb->token);
		}
		free(cb);
	}
}


static inline bool psi_let_callback_validate_decl_args(struct psi_data *data,
		struct psi_let_callback *cb, struct psi_decl *cb_decl,
		struct psi_impl *impl)
{
	size_t i;
	struct psi_decl_var *call_arg;

	if (cb->cb_args) {
		if (psi_plist_count(cb->cb_args) != psi_plist_count(cb_decl->args)) {
			data->error(data, cb->token, PSI_WARNING,
					"Argument count of callback statement of implementation '%s'"
					"does not match argument count of callback declaration '%s'",
					impl->func->name, cb_decl->func->var->name);
			return false;
		}

		for (i = 0; psi_plist_get(cb->cb_args, i, &call_arg); ++i) {
			psi_plist_get(cb_decl->args, i, &call_arg->arg);
		}
	}
	return true;
}

bool psi_let_callback_validate(struct psi_data *data, struct psi_let_callback *cb,
		struct psi_validate_scope *scope)
{
	size_t i = 0;
	struct psi_decl_type *cb_type;
	struct psi_let_exp *exp = scope->current_let;
	struct psi_decl_var *cb_var = exp->var;
	struct psi_set_exp *set_exp, *parent_set = scope->current_set;

	cb_type = psi_decl_type_get_real(cb_var->arg->type);
	if (cb_type->type != PSI_T_FUNCTION) {
		data->error(data, cb_var->token, PSI_WARNING,
				"Expected a function: %s",
				cb_var->name);
		return false;
	}
	cb->decl = cb_type->real.func;

	if (!psi_decl_validate_nodl(data, cb->decl, scope)) {
		return false;
	}
	if (!psi_let_callback_validate_decl_args(data, cb, cb->decl, scope->impl)) {
		return false;
	}
	while (psi_plist_get(cb->args, i++, &set_exp)) {
		if (cb->cb_args) {
			struct psi_decl_var *cb_var;

			if (psi_plist_get(cb->cb_args, i - 1, &cb_var)) {
				struct psi_decl_var *dvar = psi_set_exp_get_decl_var(set_exp);
				dvar->arg = cb_var->arg;
			}
		}

		scope->current_set = set_exp;
		scope->cb_decl = cb->decl;

		if (!psi_set_exp_validate(data, set_exp, scope)) {
			scope->cb_decl = NULL;
			scope->current_set = parent_set;
			return false;
		}
		scope->cb_decl = NULL;
		scope->current_set = parent_set;
	}

	return true;
}

void psi_let_callback_dump(int fd, struct psi_let_callback *callback,
		unsigned level)
{
	dprintf(fd, "callback(");
	if (callback->cb_args) {
		size_t i = 0;
		struct psi_decl_var *cb_arg;

		while (psi_plist_get(callback->cb_args, i++, &cb_arg)) {
			if (i > 1) {
				dprintf(fd, ", ");
			}
			psi_decl_var_dump(fd, cb_arg);
		}
	}
	dprintf(fd, ") as %s(%s(",
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
