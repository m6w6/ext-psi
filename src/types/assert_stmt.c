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

#include "php_psi_stdinc.h"

#include "data.h"
#include "calc.h"

#include "zend_smart_str.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

struct psi_assert_stmt *psi_assert_stmt_init(enum psi_assert_kind kind, struct psi_num_exp *exp)
{
	struct psi_assert_stmt *stmt = pecalloc(1, sizeof(*stmt), 1);

	stmt->kind = kind;
	stmt->exp = exp;

	return stmt;
}

void psi_assert_stmt_free(struct psi_assert_stmt **stmt_ptr)
{
	if (*stmt_ptr) {
		struct psi_assert_stmt *stmt = *stmt_ptr;

		*stmt_ptr = NULL;
		psi_num_exp_free(&stmt->exp);
		psi_token_free(&stmt->token);
		free(stmt);
	}
}

void psi_assert_stmt_dump(struct psi_dump *dump, struct psi_assert_stmt *stmt)
{
	PSI_DUMP(dump, "\t%s_assert ", stmt->kind == PSI_ASSERT_PRE ? "pre" : "post");
	psi_num_exp_dump(dump, stmt->exp);
	PSI_DUMP(dump, ";\n");
}

bool psi_assert_stmt_exec(struct psi_assert_stmt *stmt, struct psi_call_frame *frame)
{
	impl_val res, chk;
	token_t res_type = psi_num_exp_exec(stmt->exp, &res, frame, NULL);

	psi_calc_cast(res_type, &res, PSI_T_UINT8, &chk);
	return chk.u8;
}

bool psi_assert_stmts_validate(struct psi_data *data, struct psi_validate_scope *scope)
{
	size_t i = 0;
	struct psi_assert_stmt *ass;

	/* we can have multiple assert stmts */
	while (psi_plist_get(scope->impl->stmts.ass, i++, &ass)) {
		if (!psi_num_exp_validate(data, ass->exp, scope)) {
			return false;
		}
	}

	return true;
}

void psi_assert_stmt_throw(struct psi_assert_stmt *stmt)
{
	struct psi_dump dump;
	smart_str str = {0};
	zend_string *message;

	dump.ctx.hn = &str;
	dump.fun = (psi_dump_cb) smart_str_append_printf;

	PSI_DUMP(&dump, "Failed asserting that ");
	psi_num_exp_dump(&dump, stmt->exp);
	smart_str_0(&str);
	zend_throw_exception(stmt->kind == PSI_ASSERT_PRE
			? spl_ce_InvalidArgumentException
			: spl_ce_UnexpectedValueException, str.s->val, 0);
	smart_str_free(&str);
}
