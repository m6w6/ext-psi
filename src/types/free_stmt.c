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

free_stmt *init_free_stmt(free_calls *calls) {
	free_stmt *f = calloc(1, sizeof(*f));
	f->calls = calls;
	return f;
}

void free_free_stmt(free_stmt *f) {
	free_free_calls(f->calls);
	free(f);
}

void dump_free_stmt(int fd, free_stmt *fre) {
	size_t k;

	dprintf(fd, "\tfree ");
	for (k = 0; k < fre->calls->count; ++k) {
		free_call *call = fre->calls->list[k];

		if (k) {
			dprintf(fd, ", ");
		}
		dump_free_call(fd, call);
		dprintf(fd, "\n");
	}
}

static inline decl *locate_free_decl(decls *decls, free_call *f) {
	if (decls)  {
		size_t i;

		for (i = 0; i < decls->count; ++i) {
			if (!strcmp(decls->list[i]->func->var->name, f->func)) {
				f->decl = decls->list[i];
				return decls->list[i];
			}
		}
	}

	return NULL;
}

int validate_free_stmts(struct psi_data *data, impl *impl) {
	size_t i, j, k, l;
	/* we can have any count of free stmts; freeing any out vars */
	for (i = 0; i < impl->stmts->fre.count; ++i) {
		free_stmt *fre = impl->stmts->fre.list[i];

		for (j = 0; j < fre->calls->count; ++j) {
			free_call *free_call = fre->calls->list[j];

			/* first find the decl of the free func */
			if (!locate_free_decl(data->decls, free_call)) {
				data->error(data, free_call->token, PSI_WARNING,
						"Missing declaration '%s' in `free` statement"
						" of implementation '%s'",
						free_call->func, impl->func->name);
				return 0;
			}



			/* now check for known vars */
			for (l = 0; l < free_call->vars->count; ++l) {
				int check = 0;
				decl_var *free_var = free_call->vars->vars[l];

				if (!strcmp(free_var->name, impl->decl->func->var->name)) {
					check = 1;
					free_var->arg = impl->decl->func;
				} else if (impl->decl->args) {
					for (k = 0; k < impl->decl->args->count; ++k) {
						decl_arg *free_arg = impl->decl->args->args[k];

						if (!strcmp(free_var->name, free_arg->var->name)) {
							check = 1;
							free_var->arg = free_arg;
							break;
						}
					}
				}

				if (!check) {
					data->error(data, free_var->token, PSI_WARNING,
							"Unknown variable '%s' of `free` statement"
							" of implementation '%s'",
							free_var->name, impl->func->name);
					return 0;
				}
			}
		}
	}
	return 1;
}
