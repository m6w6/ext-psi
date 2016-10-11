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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "data.h"

void *add_impl_stmt_ex(void *list, size_t count, void *stmt) {
	list = realloc(list, count * sizeof(list));
	((void**) list)[count - 1] = stmt;
	return list;
}

impl_stmts *add_impl_stmt(impl_stmts *stmts, impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_RETURN:
		stmts->ret.list = add_impl_stmt_ex(stmts->ret.list, ++stmts->ret.count,
				stmt->s.ret);
		break;
	case PSI_T_LET:
		stmts->let.list = add_impl_stmt_ex(stmts->let.list, ++stmts->let.count,
				stmt->s.let);
		break;
	case PSI_T_SET:
		stmts->set.list = add_impl_stmt_ex(stmts->set.list, ++stmts->set.count,
				stmt->s.set);
		break;
	case PSI_T_FREE:
		stmts->fre.list = add_impl_stmt_ex(stmts->fre.list, ++stmts->fre.count,
				stmt->s.fre);
		break;
	}
	free(stmt);
	return stmts;
}

impl_stmts *init_impl_stmts(impl_stmt *stmt) {
	impl_stmts *stmts = calloc(1, sizeof(*stmts));
	return add_impl_stmt(stmts, stmt);
}

void free_impl_stmts(impl_stmts *stmts) {
	size_t i;
	for (i = 0; i < stmts->let.count; ++i) {
		free_let_stmt(stmts->let.list[i]);
	}
	free(stmts->let.list);
	for (i = 0; i < stmts->ret.count; ++i) {
		free_return_stmt(stmts->ret.list[i]);
	}
	free(stmts->ret.list);
	for (i = 0; i < stmts->set.count; ++i) {
		free_set_stmt(stmts->set.list[i]);
	}
	free(stmts->set.list);
	for (i = 0; i < stmts->fre.count; ++i) {
		free_free_stmt(stmts->fre.list[i]);
	}
	free(stmts->fre.list);
	free(stmts);
}

void dump_impl_stmts(int fd, impl_stmts *stmts) {
	size_t j;

	for (j = 0; j < stmts->let.count; ++j) {
		let_stmt *let = stmts->let.list[j];
		dump_let_stmt(fd, let);
		dprintf(fd, "\n");
	}
	for (j = 0; j < stmts->ret.count; ++j) {
		return_stmt *ret = stmts->ret.list[j];
		dump_return_stmt(fd, ret);
		dprintf(fd, "\n");
	}
	for (j = 0; j < stmts->set.count; ++j) {
		set_stmt *set = stmts->set.list[j];

		dump_set_stmt(fd, set);
		dprintf(fd, "\n");
	}
	for (j = 0; j < stmts->fre.count; ++j) {
		free_stmt *fre = stmts->fre.list[j];

		dump_free_stmt(fd, fre);
		dprintf(fd, "\n");
	}
}

int validate_impl_stmts(struct psi_data *data, impl *impl) {
	if (!impl->stmts) {
 		data->error(data, impl->func->token, PSI_WARNING,
 				"Missing body for implementation %s!",
 				impl->func->name);
 		return 0;
 	}

	if (!validate_return_stmt(data, impl)) {
		return 0;
	}

	if (!validate_let_stmts(data, impl)) {
		return 0;
	}
	if (!validate_set_stmts(data, impl)) {
		return 0;
	}
	if (!validate_free_stmts(data, impl)) {
		return 0;
	}

	return 1;
}
