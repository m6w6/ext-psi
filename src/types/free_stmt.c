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

struct psi_free_stmt *psi_free_stmt_init(struct psi_plist *exps)
{
	struct psi_free_stmt *f = calloc(1, sizeof(*f));
	f->exps = exps;
	return f;
}

void psi_free_stmt_free(struct psi_free_stmt **f_ptr)
{
	if (*f_ptr) {
		struct psi_free_stmt *f = *f_ptr;

		*f_ptr = NULL;
		if (f->token) {
			free(f->token);
		}
		psi_plist_free(f->exps);
		free(f);
	}
}

void psi_free_stmt_dump(int fd, struct psi_free_stmt *fre)
{
	size_t i;
	struct psi_free_exp *exp;

	dprintf(fd, "\tfree ");
	for (i = 0; psi_plist_get(fre->exps, i, &exp); ++i) {
		if (i) {
			dprintf(fd, ", ");
		}
		psi_free_exp_dump(fd, exp);
	}
	dprintf(fd, ";\n");
}

bool psi_free_stmts_validate(struct psi_data *data, struct psi_impl *impl)
{
	size_t i;
	struct psi_free_stmt *fre;

	/* we can have any count of free stmts; freeing any out vars */
	for (i = 0; psi_plist_get(impl->stmts.fre, i, &fre); ++i) {
		size_t j;
		struct psi_free_exp *exp;

		for (j = 0; psi_plist_get(fre->exps, j, &exp); ++j) {
			if (!psi_free_exp_validate(data, exp, impl)) {
				return false;
			}
		}
	}
	return true;
}

void psi_free_stmt_exec(struct psi_free_stmt *fre, struct psi_call_frame *frame)
{
	size_t i = 0;
	struct psi_free_exp *exp;

	while (psi_plist_get(fre->exps, i++, &exp)) {
		psi_free_exp_exec(exp, frame);
	}
}
