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

set_stmt *init_set_stmt(impl_var *var, set_value *val) {
	set_stmt *set = calloc(1, sizeof(*set));
	set->var = var;
	set->val = val;
	return set;
}

void free_set_stmt(set_stmt *set) {
	free_impl_var(set->var);
	free_set_value(set->val);
	free(set);
}

void dump_set_stmt(int fd, set_stmt *set) {
	dprintf(fd, "\tset %s = ", set->var->name);
	dump_set_value(fd, set->val, 1, 0);
}

int validate_set_stmts(struct psi_data *data, impl *impl) {
	size_t i, j, k;
	/* we can have any count of set stmts; processing out vars */
	/* check that set stmts reference known variables */
	for (i = 0; i < impl->stmts->set.count; ++i) {
		set_stmt *set = impl->stmts->set.list[i];
		int check = 0;

		if (impl->func->args) for (j = 0; j < impl->func->args->count; ++j) {
			impl_arg *iarg = impl->func->args->args[j];

			if (!strcmp(set->var->name, iarg->var->name)) {
				set->arg = iarg;
				check = 1;
				break;
			}
		}
		if (!check) {
			data->error(data, set->var->token, PSI_WARNING, "Unknown variable '$%s' of `set` statement"
					" of implementation '%s'",
					set->var->name, impl->func->name);
			return 0;
		}

		for (j = 0; j < set->val->vars->count; ++j) {
			decl_var *set_var = set->val->vars->vars[j];

			check = 0;
			if (impl->decl->args) {
				for (k = 0; k < impl->decl->args->count; ++k) {
					decl_arg *set_arg = impl->decl->args->args[k];

					if (!strcmp(set_var->name, set_arg->var->name)) {
						check = 1;
						set_var->arg = set_arg;
						if (!validate_set_value(data, set->val, 1, &set_arg, 1, &impl->decl->func, impl->decl->args->count, impl->decl->args->args, 0)) {
							return 0;
						}
						break;
					}
				}
			}
			if (!check) {
				for (k = 0; k < impl->stmts->let.count; ++k) {
					let_stmt *let = impl->stmts->let.list[k];

					/* check temp vars */
					if (let->val && let->val->kind == PSI_LET_TMP) {
						if (!strcmp(set_var->name, let->var->name)) {
							check = 1;
							set_var->arg = let->var->arg;
							if (!validate_set_value(data, set->val, 1, &set_var->arg, 1, &impl->decl->func, impl->decl->args->count, impl->decl->args->args, 0)) {
								return 0;
							}
							break;
						}
					}
				}
			}

			if (!check) {
				data->error(data, set_var->token, PSI_WARNING, "Unknown value '%s' of `set` statement"
						" for variable '$%s' of implementation '%s'",
						set_var->name, set->arg->var->name, impl->func->name);
				return 0;
			}
		}
	}
	return 1;
}
