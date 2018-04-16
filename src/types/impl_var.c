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

struct psi_impl_var *psi_impl_var_init(const char *name, bool is_reference)
{
	struct psi_impl_var *var = calloc(1, sizeof(*var));

	var->name = strdup(name);
	var->fqn = strdup(name);

	var->reference = is_reference;
	return var;
}

struct psi_impl_var *psi_impl_var_copy(struct psi_impl_var *var)
{
	struct psi_impl_var *cpy = malloc(sizeof(*cpy));

	*cpy = *var;

	cpy->name = strdup(cpy->name);
	cpy->fqn = strdup(cpy->fqn);

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
		if (var->token) {
			free(var->token);
		}
		free(var->name);
		free(var->fqn);
		free(var);
	}
}

void psi_impl_var_dump(int fd, struct psi_impl_var *var, bool vararg)
{
	dprintf(fd, "%s%s%s",
		var->reference ? "&" : "",
		vararg ? "..." : "",
		var->name);
}

bool psi_impl_var_validate(struct psi_data *data, struct psi_impl_var *ivar,
		struct psi_validate_scope *scope)
{
	if (scope && scope->current_let) {
		struct psi_let_exp *current_let_exp = scope->current_let;

		while ((current_let_exp = current_let_exp->outer)) {
			struct psi_impl_var *svar = psi_let_exp_get_impl_var(current_let_exp);

			ivar->fqn = psi_impl_var_name_prepend(ivar->fqn, svar->name + 1);
		}
	} else if (scope && scope->current_set) {
		struct psi_set_exp *current_set_exp = scope->current_set;
		while ((current_set_exp = current_set_exp->outer)) {
			struct psi_impl_var *svar = psi_set_exp_get_impl_var(current_set_exp);

			ivar->fqn = psi_impl_var_name_prepend(ivar->fqn, svar->name + 1);
		}
	}

	return true;
}
