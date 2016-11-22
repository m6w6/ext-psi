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
#include "call.h"

struct psi_set_stmt *psi_set_stmt_init(struct psi_set_exp *exp)
{
	struct psi_set_stmt *set = calloc(1, sizeof(*set));
	set->exp = exp;
	return set;
}

void psi_set_stmt_exec(struct psi_set_stmt *set, struct psi_call_frame *frame)
{
	psi_set_exp_exec(set->exp, frame);
}

void psi_set_stmt_free(struct psi_set_stmt **set_ptr)
{
	if (*set_ptr) {
		struct psi_set_stmt *set = *set_ptr;

		*set_ptr = NULL;
		psi_set_exp_free(&set->exp);
		if (set->token) {
			free(set->token);
		}
		free(set);
	}
}

void psi_set_stmt_dump(int fd, struct psi_set_stmt *set)
{
	dprintf(fd, "\tset ");
	psi_set_exp_dump(fd, set->exp, 1, 1);
	dprintf(fd, ";\n");
}


bool psi_set_stmts_validate(struct psi_data *data, struct psi_impl *impl)
{
	size_t i = 0;
	struct psi_set_stmt *set;

	/* we can have any count of set stmts; processing out vars */
	/* check that set stmts reference known variables */
	while (psi_plist_get(impl->stmts.set, i++, &set)) {
		if (!set->exp->var) {
			data->error(data, set->token, PSI_WARNING,
					"Missing variable of `set` statement of implementation '%s'",
					impl->func->name);
			return false;
		}
		if (!psi_impl_get_arg(impl, set->exp->var)) {
			data->error(data, set->token, PSI_WARNING,
					"Unknown variable '%s' of `set` statement of implementation '%s'",
					set->exp->var->name, impl->func->name);
			return false;
		}

		switch (set->exp->kind) {
		case PSI_SET_NUMEXP:
			break;
		case PSI_SET_FUNC:
			if (!psi_decl_get_arg(impl->decl, set->exp->data.func->var)) {
				if (!psi_impl_get_temp_let_arg(impl, set->exp->data.func->var)) {
					data->error(data, set->token, PSI_WARNING,
							"Unknown variable '%s' of `set` statement of implementation '%s'",
							set->exp->data.func->var, impl->func->name);
					return false;
				}
			}
		}
		/* validate the expression itself */
		if (!psi_set_exp_validate(data, set->exp, impl, NULL)) {
			return false;
		}
	}

	return true;
}
