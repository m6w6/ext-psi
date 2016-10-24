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
#include <string.h>
#include <assert.h>

#include "data.h"
#include "marshal.h"

let_func *init_let_func(token_t type, const char *name, impl_var *var) {
	let_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	func->var = var;
	return func;
}

void free_let_func(let_func *func) {
	free_impl_var(func->var);
	free(func->name);
	if (func->inner) {
		free_let_vals(func->inner);
	}
	free(func);
}

void dump_let_func(int fd, let_func *func, unsigned level) {
	dprintf(fd, "%s(%s", func->name, func->var->name);

	if (func->inner) {
		size_t i;

		dprintf(fd, ",");
		for (i = 0; i < func->inner->count; ++i) {
			dprintf(fd, "\n");
			dump_let_val(fd, func->inner->vals[i], level+1, i+1 == func->inner->count);
		}
		dprintf(fd, "\n");
		dprintf(fd, "%s", psi_t_indent(level));
	}
	dprintf(fd, ")");
}

static inline int validate_let_func_type(struct psi_data *data, let_func *func, impl *impl) {
	switch (func->type) {
	case PSI_T_BOOLVAL:
	case PSI_T_INTVAL:
	case PSI_T_FLOATVAL:
	case PSI_T_STRVAL:
	case PSI_T_STRLEN:
	case PSI_T_PATHVAL:
	case PSI_T_ARRVAL:
	case PSI_T_OBJVAL:
	case PSI_T_ZVAL:
	case PSI_T_VOID:
	case PSI_T_COUNT:
		return 1;
	default:
		data->error(data, func->var->token, PSI_WARNING,
				"Unknown `let` cast function '%s' of implementation '%s'",
				func->name, impl->func->name);
		return 0;
	}
}

static inline int validate_let_func_inner(struct psi_data *data, let_val *val, let_func *func, decl_var *let_var, impl *impl) {

	if (func->inner) {
		size_t i;
		decl_type *var_typ;
		decl_args *sub_args = extract_decl_type_args(let_var->arg->type, &var_typ);

		if (func->type == PSI_T_ARRVAL && sub_args) {
			/* struct = arrval($array,
			 * 	member = strval($member) ...)
			 */
			size_t i;

			for (i = 0; i < func->inner->count; ++i) {
				let_val *inner = func->inner->vals[i];
				const char *name = locate_let_val_varname(inner);
				let_func *fn = locate_let_val_func(inner);
				decl_arg *sub_arg;

				if (name) {
					sub_arg = locate_decl_arg(sub_args, name);
				}
				if (!name || !sub_arg) {
					data->error(data, let_var->token, PSI_WARNING,
							"Unknown variable '%s'", name);
					return 0;
				}

				fn->outer = val;
				fn->ref = sub_arg;

				if (!validate_let_val(data, inner, sub_arg->var, impl)) {
					return 0;
				}
			}
		} else if (func->type == PSI_T_ARRVAL && func->inner->count == 1 && let_var->arg->var->pointer_level) {
			/* array = arrval($array,
			 * 	strval($array)) // cast foreach entry
			 */
			impl_var *sub_var = locate_let_val_impl_var(val);
			impl_var *sub_ref = locate_let_val_impl_var(func->inner->vals[0]);

			if (strcmp(sub_var->name, sub_ref->name)) {
				data->error(data, sub_var->token, E_WARNING, "Inner `set` statement casts on pointers must reference the same variable");
				return 0;
			}
			if (!validate_let_val(data, func->inner->vals[0], let_var, impl)) {
				return 0;
			}
		} else {
			data->error(data, let_var->token, PSI_WARNING,
					"Inner let statement's values must refer to a structure or array type, got '%s%s' for '%s'",
					var_typ->name, psi_t_indirection(let_var->arg->var->pointer_level), let_var->name);
			return 0;
		}
	}
	return 1;
}

int validate_let_func(struct psi_data *data, let_val *val, let_func *func, decl_var *let_var, impl *impl) {
	if (func->outer) {

	}
	if (impl->func->args) {
		locate_impl_var_arg(func->var, impl->func->args);
	}
	if (!func->var->arg && !func->ref) {
		data->error(data, func->var->token, PSI_WARNING,
				"Unknown variable '%s%s' of `let` statement"
				" for cast '%s' of implementation '%s'",
				*func->var->name == '$' ? "" : "$",
				func->var->name, func->name, impl->func->name);
		return 0;
	}
	if (!validate_let_func_type(data, func, impl)) {
		return 0;
	}
	if (!validate_let_func_inner(data, val, func, let_var, impl)) {
		return 0;
	}
	return 1;
}
