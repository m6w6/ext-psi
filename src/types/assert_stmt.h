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

#ifndef PSI_TYPES_ASSERT_STMT_H
#define PSI_TYPES_ASSERT_STMT_H

struct psi_token;
struct psi_data;
struct psi_impl;
struct psi_num_exp;
struct psi_call_frame;

struct psi_assert_stmt {
	struct psi_token *token;
	struct psi_num_exp *exp;
	enum psi_assert_kind {
		PSI_ASSERT_PRE = PSI_T_PRE_ASSERT,
		PSI_ASSERT_POST = PSI_T_POST_ASSERT
	} kind;
};

struct psi_assert_stmt *psi_assert_stmt_init(enum psi_assert_kind kind, struct psi_num_exp *exp);
bool psi_assert_stmt_exec(struct psi_assert_stmt *stmt, struct psi_call_frame *frame);

void psi_assert_stmt_dump(int fd, struct psi_assert_stmt *stmt);
void psi_assert_stmt_free(struct psi_assert_stmt **stmt);

bool psi_assert_stmts_validate(struct psi_data *data, struct psi_impl *impl);

char *psi_assert_stmt_message(struct psi_assert_stmt *stmt);

#endif
