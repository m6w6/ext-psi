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
#include <assert.h>

#include "data.h"

let_val *init_let_val(enum let_val_kind kind, void *data) {
	let_val *let = calloc(1, sizeof(*let));
	switch (let->kind = kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_NUMEXP:
		let->data.num = data;
		break;
	case PSI_LET_CALLOC:
		let->data.alloc = data;
		break;
	case PSI_LET_CALLBACK:
		let->data.callback = data;
		break;
	case PSI_LET_FUNC:
		let->data.func = data;
		break;
	case PSI_LET_TMP:
		let->data.var = data;
		break;
	default:
		assert(0);
	}
	return let;
}

void free_let_val(let_val *let) {
	switch (let->kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_NUMEXP:
		free_num_exp(let->data.num);
		break;
	case PSI_LET_CALLOC:
		free_let_calloc(let->data.alloc);
		break;
	case PSI_LET_CALLBACK:
		free_let_callback(let->data.callback);
		break;
	case PSI_LET_FUNC:
		free_let_func(let->data.func);
		break;
	case PSI_LET_TMP:
		free_decl_var(let->data.var);
		break;
	default:
		assert(0);
	}
	free(let);
}

void dump_let_val(int fd, let_val *val, unsigned level, int last) {
	if (level > 1) {
		/* only if not directly after `set ...` */
		dprintf(fd, "%s", psi_t_indent(level));
	}

	dprintf(fd, "%s", val->flags.one.is_reference ? "&" : "");

	switch (val->kind) {
	case PSI_LET_NULL:
		dprintf(fd, "NULL");
		break;
	case PSI_LET_TMP:
		dump_decl_var(fd, val->data.var);
		break;
	case PSI_LET_CALLOC:
		dprintf(fd, "calloc(");
		dump_num_exp(fd, val->data.alloc->nmemb);
		dprintf(fd, ", ");
		dump_num_exp(fd, val->data.alloc->size);
		dprintf(fd, ")");
		break;
	case PSI_LET_CALLBACK:
		dprintf(fd, "callback %s(%s(", val->data.callback->func->name,
				val->data.callback->func->var->name);
		if (val->data.callback->args) {
			size_t i, c = val->data.callback->args->count;

			dprintf(fd, "\n");
			for (i = 0; i < c; ++i) {
				set_value *set = val->data.callback->args->vals[i];
				++level;
				dump_set_value(fd, set, level, i + 1 == c);
				--level;
			}
			dprintf(fd, "%s", psi_t_indent(level));
		}
		dprintf(fd, "))");
		break;
	case PSI_LET_FUNC:
		dump_let_func(fd, val->data.func, level);
		break;
	case PSI_LET_NUMEXP:
		dump_num_exp(fd, val->data.num);
		break;

	default:
		assert(0);
	}

	if (level > 1) {
		if (!last) {
			dprintf(fd, ",");
		}
	} else {
		dprintf(fd, ";");
	}
}

int validate_let_val(struct psi_data *data, let_val *val, decl_var *let_var, impl *impl) {
	switch (val->kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_TMP:
		if (!let_var) {
			data->error(data, NULL, PSI_WARNING,
					"Ivalid let statement value of implementation '%s'",
					impl->func->name);
			return 0;
		}
		/* e.g. let bar = &strval($bar); // decl_arg(char **bar) */
		/* e.g. let foo = *bar;  */
		let_var->pointer_level = val->data.var->pointer_level;
		let_var->arg = init_decl_arg(
				init_decl_type(
						real_decl_type(val->data.var->arg->type)->type,
						real_decl_type(val->data.var->arg->type)->name),
				init_decl_var(
						let_var->name,
						let_var->pointer_level,
						let_var->array_size));
		break;
	case PSI_LET_NUMEXP:
		if (!validate_num_exp(data, val->data.num, impl->decl->args, impl->decl->func, NULL)) {
			return 0;
		}
		break;
	case PSI_LET_CALLOC:
		if (!validate_num_exp(data, val->data.alloc->nmemb, impl->decl->args, impl->decl->func, NULL)) {
			return 0;
		}
		if (!validate_num_exp(data, val->data.alloc->size, impl->decl->args, impl->decl->func, NULL)) {
			return 0;
		}
		break;
	case PSI_LET_CALLBACK:
		if (!let_var) {
			data->error(data, NULL, PSI_WARNING,
					"Ivalid let statement value of implementation '%s'",
					impl->func->name);
			return 0;
		}
		if (val->data.callback->func->inner) {
			size_t i;
			decl_type *var_typ = real_decl_type(let_var->arg->type);
			decl_args *sub_args;

			switch (var_typ->type) {
			case PSI_T_STRUCT:
				sub_args = var_typ->real.strct->args;
				break;
			case PSI_T_UNION:
				sub_args = var_typ->real.unn->args;
				break;
			default:
				data->error(data, let_var->token, PSI_WARNING,
						"Inner let statement's values must refer to a structure type, got '%s' for '%s'",
						real_decl_type(let_var->arg->type)->name, let_var->name);
				return 0;
			}
			for (i = 0; i < val->data.callback->func->inner->count; ++i) {
				let_val *inner = val->data.callback->func->inner->vals[i];
				switch (inner->kind) {
				case PSI_LET_FUNC:
					inner->data.func->outer = val;
					inner->data.func->ref = locate_decl_arg(sub_args,
							&inner->data.func->var->name[1]);
					break;

					break;
				case PSI_LET_CALLBACK:
					inner->data.callback->func->outer = val;
					inner->data.callback->func->ref = locate_decl_arg(sub_args,
							&inner->data.callback->func->var->name[1]);
					break;
				}
			}
		}
		if (!validate_let_callback(data, let_var, val->data.callback, impl)) {
			return 0;
		}
		break;
	case PSI_LET_FUNC:
		if (val->data.func->inner) {
			size_t i;
			decl_type *var_typ = real_decl_type(let_var->arg->type);
			decl_args *sub_args;

			switch (var_typ->type) {
			case PSI_T_STRUCT:
				sub_args = var_typ->real.strct->args;
				break;
			case PSI_T_UNION:
				sub_args = var_typ->real.unn->args;
				break;
			default:
				data->error(data, let_var->token, PSI_WARNING,
						"Inner let statement's values must refer to a structure type, got '%s' for '%s'",
						real_decl_type(let_var->arg->type)->name, let_var->name);
				return 0;
			}
			for (i = 0; i < val->data.func->inner->count; ++i) {
				let_val *inner = val->data.func->inner->vals[i];
				switch (inner->kind) {
				case PSI_LET_FUNC:
					inner->data.func->outer = val;
					inner->data.func->ref = locate_decl_arg(sub_args,
							&inner->data.func->var->name[1]);
					break;
				case PSI_LET_CALLBACK:
					inner->data.callback->func->outer = val;
					inner->data.callback->func->ref = locate_decl_arg(sub_args,
							&inner->data.callback->func->var->name[1]);
					break;
				}
			}
		}

		val->data.func->var;

		if (!validate_let_func(data, val->data.func, let_var, impl)) {
			return 0;
		}
		break;
	}

	return 1;
}
