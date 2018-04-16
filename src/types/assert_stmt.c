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

struct psi_assert_stmt *psi_assert_stmt_init(enum psi_assert_kind kind, struct psi_num_exp *exp)
{
	struct psi_assert_stmt *stmt = calloc(1, sizeof(*stmt));

	stmt->kind = kind;
	stmt->exp = exp;

	return stmt;
}

void psi_assert_stmt_free(struct psi_assert_stmt **stmt_ptr)
{
	if (*stmt_ptr) {
		struct psi_assert_stmt *stmt = *stmt_ptr;

		psi_num_exp_free(&stmt->exp);
		if (stmt->token) {
			free(stmt->token);
		}
		free(stmt);
		*stmt_ptr = NULL;
	}
}

void psi_assert_stmt_dump(int fd, struct psi_assert_stmt *stmt)
{
	dprintf(fd, "\t%s_assert ", stmt->kind == PSI_ASSERT_PRE ? "pre" : "post");
	psi_num_exp_dump(fd, stmt->exp);
	dprintf(fd, ";\n");
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

char *psi_assert_stmt_message(struct psi_assert_stmt *stmt)
{
	/* FIXME */
	struct stat sb;
	char *message, template[] = "psi.assert.XXXXXX";
	int fd = mkstemp(template);

	dprintf(fd, "Failed asserting that ");
	psi_num_exp_dump(fd, stmt->exp);
	fstat(fd, &sb);
	message = malloc(sb.st_size + 1);
	lseek(fd, 0, SEEK_SET);
	read(fd, message, sb.st_size);
	close(fd);
	message[sb.st_size] = '\0';
	return message;
}
