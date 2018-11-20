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

struct psi_let_stmt *psi_let_stmt_init(struct psi_let_exp *exp)
{
	struct psi_let_stmt *let = pecalloc(1, sizeof(*let), 1);
	let->exp = exp;

	return let;
}

void psi_let_stmt_free(struct psi_let_stmt **stmt_ptr)
{
	if (*stmt_ptr) {
		struct psi_let_stmt *stmt = *stmt_ptr;

		*stmt_ptr = NULL;
		if (stmt->exp) {
			psi_let_exp_free(&stmt->exp);
		}
		psi_token_free(&stmt->token);
		free(stmt);
	}
}

void psi_let_stmt_dump(struct psi_dump *dump, struct psi_let_stmt *let)
{
	PSI_DUMP(dump, "\t%s ", let->exp->kind == PSI_LET_TMP ? "temp" : "let");
	psi_let_exp_dump(dump, let->exp, 1, 1);
	PSI_DUMP(dump, "\n");
}

bool psi_let_stmts_validate(struct psi_data *data, struct psi_validate_scope *scope)
{
	size_t i = 0;
	struct psi_let_stmt *let;

	/* we can have multiple let stmts */
	/* check that we have a decl arg and impl arg for every let stmt */
	while (psi_plist_get(scope->impl->stmts.let, i++, &let)) {
		struct psi_decl_var *let_var;
		struct psi_impl_var *let_ivar = NULL;

		if (let->exp->kind == PSI_LET_TMP) {
			let_var = let->exp->data.var;
		} else {
			let_var = let->exp->var;
		}

		if (!let->exp->var) {
			data->error(data, let->token, PSI_WARNING,
					"Missing variable in `let` statement for implementation %s",
					scope->impl->func->name->val);
			return false;
		}

		if (!psi_impl_get_decl_arg(scope->impl, let_var)) {
			data->error(data, let_var->token, PSI_WARNING,
					"Unknown variable '%s' in `let` statement  of implementation '%s'",
					let_var->name->val, scope->impl->func->name->val);
			return false;
		}
		switch (let->exp->kind) {
		case PSI_LET_CALLBACK:
			let_ivar = let->exp->data.callback->func->var;
			break;
		case PSI_LET_FUNC:
			let_ivar = let->exp->data.func->var;
			break;
		default:
			break;
		}
		if (let_ivar && !psi_impl_get_arg(scope->impl, let_ivar)) {
			data->error(data, let_var->token, PSI_WARNING,
					"Unknown variable '%s' in `let` statement of implementation '%s'",
					let_ivar->name->val, scope->impl->func->name->val);
			return false;
		}

		scope->current_let = let->exp;
		if (!psi_let_exp_validate(data, let->exp, scope)) {
			scope->current_let = NULL;
			return false;
		}
		scope->current_let = NULL;
	}
	/* check that we have a let stmt for every decl arg */
	if (scope->impl->decl->args) {
		struct psi_decl_arg *darg;

		for (i = 0; psi_plist_get(scope->impl->decl->args, i, &darg); ++i) {
			if (!psi_impl_get_let(scope->impl, darg->var)) {
				data->error(data, scope->impl->func->token, PSI_WARNING,
						"Missing `let` statement for arg '%s %s%s'"
								" of declaration '%s' for implementation '%s'",
						darg->type->name->val,
						psi_t_indirection(darg->var->pointer_level),
						darg->var->name->val,
						scope->impl->decl->func->var->name->val,
						scope->impl->func->name->val);
				return false;
			}
		}
	}

	return true;
}

void *psi_let_stmt_exec(struct psi_let_stmt *let, struct psi_call_frame *frame)
{
	return psi_let_exp_exec(let->exp, let->exp->var->arg, NULL, 0, frame);
}
