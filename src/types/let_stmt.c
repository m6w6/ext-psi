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

let_stmt *init_let_stmt(let_val *val) {
	let_stmt *let = calloc(1, sizeof(*let));
	let->val = val;

	return let;
}

void free_let_stmt(let_stmt *stmt) {
	if (stmt->val) {
		free_let_val(stmt->val);
	}
	if (stmt->token) {
		free(stmt->token);
	}
	free(stmt);
}

void dump_let_stmt(int fd, let_stmt *let) {
	dprintf(fd, "\t%s ", let->val->kind == PSI_LET_TMP ? "temp" : "let");
	dump_let_val(fd, let->val, 1, 1);
}

int validate_let_stmts(struct psi_data *data, impl *impl) {
	size_t i, j;
	/* we can have multiple let stmts */

	/* check that we have a decl arg and impl arg for every let stmt */
	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];
		decl_var *let_var;
		impl_var *let_ivar = NULL;

		if (let->val && let->val->kind == PSI_LET_TMP) {
			let_var = let->val->data.var;
		} else {
			let_var = let->val->var;
		}

		if (!locate_decl_var_arg(let_var, impl->decl->args, impl->decl->func)) {
			data->error(data, let_var->token, PSI_WARNING, "Unknown variable '%s' in `let` statement"
					" of implementation '%s'", let_var->name, impl->func->name);
			return 0;
		}
		switch (let->val->kind) {
		case PSI_LET_CALLBACK:
			let_ivar = let->val->data.callback->func->var;
			break;
		case PSI_LET_FUNC:
			let_ivar = let->val->data.func->var;
			break;
		default:
			break;
		}
		if (let_ivar && !locate_impl_var_arg(let_ivar, impl->func->args)) {
			data->error(data, let_var->token, PSI_WARNING, "Unknown variable '%s' in `let` statement"
					" of implementation '%s'", let_ivar->name, impl->func->name);
			return 0;
		}

		if (!validate_let_val(data, let->val, let->val->var, impl)) {
			return 0;
		}
	}
	/* check that we have a let stmt for every decl arg */
	if (impl->decl->args) for (i = 0; i < impl->decl->args->count; ++i) {
		decl_arg *darg = impl->decl->args->args[i];
		int check = 0;

		for (j = 0; j < impl->stmts->let.count; ++j) {
			let_stmt *let = impl->stmts->let.list[j];

			if (!strcmp(let->val->var->name, darg->var->name)) {
				check = 1;
				break;
			}
		}
		if (!check) {
			data->error(data, impl->func->token, PSI_WARNING,
					"Missing `let` statement for arg '%s %.*s%s'"
					" of declaration '%s' for implementation '%s'",
					darg->type->name, (int) darg->var->pointer_level, "*****",
					darg->var->name, impl->decl->func->var->name, impl->func->name);
			return 0;
		}
	}

	return 1;
}
