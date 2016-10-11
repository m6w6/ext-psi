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

return_stmt *init_return_stmt(set_value *val) {
	return_stmt *ret = calloc(1, sizeof(*ret));
	ret->set = val;
	return ret;
}

void free_return_stmt(return_stmt *ret) {
	if (ret->token) {
		free(ret->token);
	}
	free_set_value(ret->set);
	free(ret);
}

void dump_return_stmt(int fd, return_stmt *ret) {
	dprintf(fd, "\treturn ");
	dump_set_value(fd, ret->set, 1, 0);
}

static inline decl *locate_impl_decl(decls *decls, return_stmt *ret) {
	if (decls) {
		size_t i;

		for (i = 0; i < decls->count; ++i) {
			if (!strcmp(decls->list[i]->func->var->name, ret->set->vars->vars[0]->name)) {
				ret->decl = decls->list[i]->func;
				return decls->list[i];
			}
		}
	}

	return NULL;
}

int validate_return_stmt(struct psi_data *data, impl *impl) {
	return_stmt *ret;

	/* we must have exactly one ret stmt delcaring the native func to call */
	/* and which type cast to apply */
	if (impl->stmts->ret.count != 1) {
		if (impl->stmts->ret.count > 1) {
			data->error(data, impl->stmts->ret.list[1]->token, PSI_WARNING,
					"Too many `return` statements for implmentation %s;"
					" found %zu, exactly one is needed",
					impl->func->name, impl->stmts->ret.count);
		} else {
			data->error(data, impl->func->token, PSI_WARNING,
					"Missing `return` statement for implementation %s",
					impl->func->name);
		}
		return 0;
	}

	ret = impl->stmts->ret.list[0];

	if (!(impl->decl = locate_impl_decl(data->decls, ret))) {
		data->error(data, ret->token, PSI_WARNING,
				"Missing declaration '%s' for `return` statment for implementation %s",
				ret->set->vars->vars[0]->name, impl->func->name);
		return 0;
	}

	if (!validate_set_value(data, ret->set, 1, &ret->decl, impl->decl->args ? (int) impl->decl->args->count : 0, impl->decl->args ? impl->decl->args->args : NULL, 0)) {
		return 0;
	}

	//impl->decl->impl = impl;

	return 1;
}
