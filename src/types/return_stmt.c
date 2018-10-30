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

struct psi_return_stmt *psi_return_stmt_init(struct psi_return_exp *exp)
{
	struct psi_return_stmt *ret = calloc(1, sizeof(*ret));
	ret->exp = exp;
	return ret;
}

void psi_return_stmt_exec(struct psi_return_stmt *ret, zval *return_value,
		struct psi_call_frame *frame)
{
	psi_return_exp_exec(ret->exp, return_value, frame);
}

void psi_return_stmt_free(struct psi_return_stmt **ret_ptr)
{
	if (*ret_ptr) {
		struct psi_return_stmt *ret = *ret_ptr;

		*ret_ptr = NULL;
		psi_token_free(&ret->token);
		psi_return_exp_free(&ret->exp);
		free(ret);
	}
}

void psi_return_stmt_dump(int fd, struct psi_return_stmt *ret)
{
	dprintf(fd, "\treturn ");
	psi_return_exp_dump(fd, ret->exp);
	dprintf(fd, ";\n");
}

bool psi_return_stmt_validate(struct psi_data *data,
		struct psi_validate_scope *scope)
{
	struct psi_return_stmt *ret;
	size_t count = psi_plist_count(scope->impl->stmts.ret);

	psi_plist_get(scope->impl->stmts.ret, 0, &ret);

	/*
	 * we must have exactly one ret stmt declaring the native func to call
	 * and which type cast to apply
	 */
	switch (count) {
	default:
		data->error(data, ret->token, PSI_WARNING,
				"Too many `return` statements for implementation %s;"
				" found %zu, exactly one is required",
				scope->impl->func->name->val, count);
		return false;
	case 0:
		data->error(data, scope->impl->func->token, PSI_WARNING,
				"Missing `return` statement for implementation %s",
				scope->impl->func->name->val);
		return false;
	case 1:
		break;
	}

	if (!psi_return_exp_validate(data, ret->exp, scope)) {
		return false;
	}

	return true;
}
