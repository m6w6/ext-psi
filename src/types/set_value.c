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
#include "marshal.h"

set_value *init_set_value(set_func *func, decl_vars *vars) {
	set_value *val = calloc(1, sizeof(*val));
	val->func = func;
	val->vars = vars;
	return val;
}

set_value *add_inner_set_value(set_value *val, set_value *inner) {
	val->inner = add_set_value(val->inner, inner);
	inner->outer.set = val;
	return val;
}

void free_set_value(set_value *val) {
	if (val->func) {
		free_set_func(val->func);
	}
	if (val->vars) {
		free_decl_vars(val->vars);
	}
	if (val->inner
			&& (!val->outer.set || val->outer.set->inner != val->inner)) {
		free_set_values(val->inner);
	}
	if (val->num) {
		free_num_exp(val->num);
	}
	free(val);
}

void dump_set_value(int fd, set_value *set, unsigned level, int last) {
	size_t i;

	if (level > 1) {
		/* only if not directly after `set ...` */
		dprintf(fd, "%s", psi_t_indent(level));
	}

	if (set->func->type == PSI_T_ELLIPSIS) {
		dprintf(fd, "%s(", set->outer.set->func->name);
	} else {
		dprintf(fd, "%s(", set->func->name);
	}

	for (i = 0; i < set->vars->count; ++i) {
		decl_var *svar = set->vars->vars[i];
		if (i) {
			dprintf(fd, ", ");
		}
		dump_decl_var(fd, svar);
	}

	if (set->func->type == PSI_T_ELLIPSIS) {
		dprintf(fd, ", ...");
	}
	if (set->num) {
		dprintf(fd, ", ");
		dump_num_exp(fd, set->num);
	}
	if (set->inner && set->inner->vals && set->func->type != PSI_T_ELLIPSIS) {
		dprintf(fd, ",\n");
		for (i = 0; i < set->inner->count; ++i) {
			dump_set_value(fd, set->inner->vals[i], level+1, i == (set->inner->count - 1));
		}
		/* only if inner stmts, i.e. with new lines, were dumped */
		dprintf(fd, "%s", psi_t_indent(level));
	}
	if (level > 1) {
		dprintf(fd, ")%s\n", last ? "" : ",");
	} else {
		dprintf(fd, ");");
	}
}

static inline void decl_var_arg_v(decl_args *args, va_list argp) {
	int argc;
	decl_arg **argv;

	memset(args, 0, sizeof(*args));

	while ((argc = va_arg(argp, int))) {
		argv = va_arg(argp, decl_arg **);
		while (argc--) {
			add_decl_arg(args, *argv++);
		}
	}
}

static inline int validate_set_value_handler(set_value *set) {
	switch (set->func->type) {
	case PSI_T_TO_BOOL:		set->func->handler = psi_to_bool;		break;
	case PSI_T_TO_INT:		set->func->handler = psi_to_int;		break;
	case PSI_T_TO_FLOAT:	set->func->handler = psi_to_double;		break;
	case PSI_T_TO_STRING:	set->func->handler = psi_to_string;		break;
	case PSI_T_TO_ARRAY:	set->func->handler = psi_to_array;		break;
	case PSI_T_TO_OBJECT:	set->func->handler = psi_to_object;		break;
	case PSI_T_VOID:		set->func->handler = psi_to_void;		break;
	case PSI_T_ZVAL:		set->func->handler = psi_to_zval;		break;
	case PSI_T_ELLIPSIS:
		if (set->outer.set && set->outer.set->func->type == PSI_T_TO_ARRAY) {
			set->func->handler = psi_to_recursive;
			set->inner = set->outer.set->inner;
			break;
		}
		/* no break */
	default:
		return 0;
	}
	return 1;
}

int validate_set_value(struct psi_data *data, set_value *set, ...) {
	va_list argp;
	decl_args args = {0};
	int check;

	va_start(argp, set);
	decl_var_arg_v(&args, argp);
	va_end(argp);

	check = validate_set_value_ex(data, set, NULL, &args);
	if (args.args) {
		free(args.args);
	}
	return check;
}

int validate_set_value_ex(struct psi_data *data, set_value *set, decl_arg *ref, decl_args *ref_list) {
	size_t i;
	decl_type *ref_type;
	decl_var *set_var = set->vars->vars[0];

	if (!validate_set_value_handler(set)) {
		data->error(data, set->func->token, PSI_WARNING, "Invalid cast '%s' in `set` statement", set->func->name);
		return 0;
	}

	for (i = 0; i < set->vars->count; ++i) {
		decl_var *svar = set->vars->vars[i];
		if (!svar->arg && !locate_decl_var_arg(svar, ref_list, NULL)) {
			data->error(data, svar->token, PSI_WARNING, "Unknown variable '%s' in `set` statement", svar->name);
			return 0;
		}
	}

	if (!ref) {
		ref = set_var->arg;
	}
	ref_type = real_decl_type(ref->type);

	if (set->inner && set->inner->count) {
		int is_to_array = (set->func->type == PSI_T_TO_ARRAY);
		int is_pointer_to_struct = (ref_type->type == PSI_T_STRUCT && ref->var->pointer_level);

		if (!is_to_array && !is_pointer_to_struct) {
			data->error(data, set->func->token, E_WARNING, "Inner `set` statement casts only work with "
					"to_array() casts on structs or pointers: %s(%s...", set->func->name, set->vars->vars[0]->name);
			return 0;
		}
	}
	if (set->num) {
		if (!validate_num_exp(data, set->num, ref_list, ref, NULL)) {
			return 0;
		}
	}

	if (set->inner && (ref_type->type == PSI_T_STRUCT || ref_type->type == PSI_T_UNION)) {
		/* to_array(struct, to_...) */
		if (!set->outer.set || set->outer.set->inner->vals != set->inner->vals) {
			for (i = 0; i < set->inner->count; ++i) {
				decl_var *sub_var = set->inner->vals[i]->vars->vars[0];
				decl_arg *sub_ref;

				switch (ref_type->type) {
				case PSI_T_STRUCT:
					sub_ref = locate_decl_struct_member(ref_type->real.strct, sub_var);
					break;
				case PSI_T_UNION:
					sub_ref = locate_decl_union_member(ref_type->real.unn, sub_var);
					break;
				}

				if (sub_ref) {
					if (!validate_set_value_ex(data, set->inner->vals[i], sub_ref, ref_type->real.strct->args)) {
						return 0;
					}
				}
			}
		}
	} else if (set->inner && set->inner->count == 1) {
		/* to_array(ptr, to_string(*ptr)) */
		decl_var *sub_var = set->inner->vals[0]->vars->vars[0];
		decl_arg *sub_ref = locate_decl_var_arg(sub_var, ref_list, ref);

		if (sub_ref) {
			if (strcmp(sub_var->name, set_var->name)) {
				data->error(data, sub_var->token, E_WARNING, "Inner `set` statement casts on pointers must reference the same variable");
				return 0;
			}
			if (!validate_set_value_ex(data, set->inner->vals[0], sub_ref, ref_list)) {
				return 0;
			}
		}
	} else if (set->inner && set->inner->count > 1) {
		data->error(data, set->func->token, E_WARNING,
				"Inner `set` statement casts on pointers may only occur once, "
				"unless the outer type is a struct or union, got '%s%s'",
				ref_type->name, psi_t_indirection(ref->var->pointer_level));
		return 0;
	}

	return 1;
}

