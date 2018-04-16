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

struct psi_set_func *psi_set_func_init(token_t type, const char *name,
		struct psi_decl_var *var)
{
	struct psi_set_func *func = calloc(1, sizeof(*func));

	func->type = type;
	func->name = strdup(name);
	func->var = var;

	return func;
}

void psi_set_func_free(struct psi_set_func **func_ptr)
{
	if (*func_ptr) {
		struct psi_set_func *func = *func_ptr;

		*func_ptr = NULL;
		if (func->token) {
			free(func->token);
		}
		psi_decl_var_free(&func->var);
		free(func->name);
		free(func);
	}
}

void psi_set_func_dump(int fd, struct psi_set_func *func, unsigned level)
{
	dprintf(fd, "%s(", func->name);
	psi_decl_var_dump(fd, func->var);
	dprintf(fd, "\t/* fqn=%s */", func->var->fqn);
	if (func->inner && !func->recursive) {
		size_t i = 0, count = psi_plist_count(func->inner);
		struct psi_set_exp *inner;

		dprintf(fd, ",");
		++level;
		while (psi_plist_get(func->inner, i++, &inner)) {
			dprintf(fd, "\n");
			psi_set_exp_dump(fd, inner, level, i == count);
		}
		--level;
	}
	if (func->recursive) {
		dprintf(fd, ", ...");
	}
	if (func->inner && !func->recursive) {
		dprintf(fd, "\n%s", psi_t_indent(level));
	}
	dprintf(fd, ")");
}

static inline bool psi_set_func_validate_to_string(struct psi_data *data,
		struct psi_set_func *func, struct psi_set_exp *set,
		struct psi_impl *impl)
{
	struct psi_set_exp *sub_exp;

	psi_plist_get(func->inner, 0, &sub_exp);

	switch (psi_plist_count(func->inner)) {
	default:
		data->error(data, **(struct psi_token ***) &sub_exp->data, PSI_WARNING,
				"Unexpected sub-expressions");
		return false;

	case 1:
		if (sub_exp->kind != PSI_SET_NUMEXP) {
			data->error(data, **(struct psi_token ***) &sub_exp->data,
					PSI_WARNING, "Expected numeric expression");
			return false;
		}
		func->handler = psi_set_to_stringl;
		return true;

	case 0:
		func->handler = psi_set_to_string;
		return true;
	}
}

static inline bool psi_set_func_validate_to_array(struct psi_data *data,
		struct psi_set_func *func, struct psi_set_exp *set,
		struct psi_impl *impl)
{
	struct psi_set_exp *sub_exp;
	struct psi_decl_var *set_var = psi_set_exp_get_decl_var(set);

	switch (psi_plist_count(set->inner)) {
	case 0:
		if (func->recursive) {
			func->handler = psi_set_to_recursive;
			set->inner = func->inner = set->outer->inner;
			return true;
		}
		data->error(data, func->token, PSI_WARNING,
				"Expected sub-expressions in to_array() cast expression");
		return false;

	case 1:
		psi_plist_get(set->inner, 0, &sub_exp);
		if (sub_exp->kind != PSI_SET_FUNC) {
			data->error(data, **(struct psi_token ***) &sub_exp->data,
					PSI_WARNING, "Expected to_type() cast expression");
			return false;
		}
		if (strcmp(set_var->name, psi_set_exp_get_decl_var(sub_exp)->name)) {
			/* no warning, because of ambiguity with a one-field-struct monstrosity */
			goto complex;
		}
		func->handler = psi_set_to_array_simple;
		return true;

	case 2:
		psi_plist_get(set->inner, 0, &sub_exp);
		if (sub_exp->kind != PSI_SET_NUMEXP) {
			goto complex;
		}
		psi_plist_get(set->inner, 1, &sub_exp);
		if (sub_exp->kind != PSI_SET_FUNC) {
			data->error(data, **(struct psi_token ***) &sub_exp->data,
					PSI_WARNING, "Expected to_type() cast expression");
			return false;
		}
		if (strcmp(set_var->name, psi_set_exp_get_decl_var(sub_exp)->name)) {
			data->error(data, **(struct psi_token ***) &sub_exp->data,
					PSI_WARNING,
					"Expected %s(%s) cast expression to reference the same"
					" variable like the outer `set` statement, '%s'",
					sub_exp->data.func->name,
					psi_set_exp_get_decl_var(sub_exp)->name, set_var);
			return false;
		}
		func->handler = psi_set_to_array_counted;
		return true;

	default:
		complex:
		switch (psi_decl_type_get_real(set_var->arg->type)->type) {
		case PSI_T_UNION:
		case PSI_T_STRUCT:
			break;
		default:
			data->error(data, func->token, PSI_WARNING,
					"Expected struct or union type for complex to_array()"
					" cast expression, got '%s'",
					set_var->arg->type->name);
			return false;
		}
		func->handler = psi_set_to_array;
		return true;
	}
}

static inline bool psi_set_func_validate_to_recursive(struct psi_data *data,
		struct psi_set_func *func, struct psi_set_exp *set,
		struct psi_impl *impl)
{
	if (!set->outer
			|| set->outer->kind != PSI_SET_FUNC
			|| set->outer->data.func->type != PSI_T_TO_ARRAY) {
		data->error(data, func->token, PSI_WARNING,
				"Expected to_array() as parent to recursion in `set` statement"
				" of implementation '%s'",
				impl->func->name);
		return false;
	}

	func->handler = psi_set_to_recursive;
	set->inner = set->outer->inner;
	// FIXME validate recursive type
	return true;
}

bool psi_set_func_validate(struct psi_data *data, struct psi_set_func *func,
		struct psi_validate_scope *scope)
{
	struct psi_set_exp *set = scope->current_set;

	if (!psi_decl_var_validate(data, func->var, scope)
			&& !psi_impl_get_temp_let_arg(scope->impl, func->var)) {
		data->error(data, func->var->token, PSI_WARNING,
				"Unknown variable '%s' in implementation %s",
				func->var->name, scope->impl->func->name);
		return false;
	}

	if (set->outer) {
		if (set->outer->kind != PSI_SET_FUNC) {
			data->error(data, func->token, PSI_WARNING,
					"Unexpected sub-expression, expected to_type() cast");
			return false;
		}
	}

	if (func->inner && (!set->outer || set->outer->inner != func->inner)) {
		size_t i = 0;
		struct psi_set_exp *inner;

		while (psi_plist_get(func->inner, i++, &inner)) {
			struct psi_decl_var *sub_var;
			struct psi_plist *sub_args;

			inner->outer = set;
			scope->current_set = inner;

			/* skip to "fail:" if field does not exists */
			sub_var = psi_set_exp_get_decl_var(inner);
			sub_args = psi_decl_type_get_args(func->var->arg->type, NULL);
			if (sub_var && sub_args) {
				if (!psi_decl_arg_get_by_var(sub_var, sub_args, NULL)) {
					goto fail;
				}
			}

			if (psi_set_exp_validate(data, inner, scope)) {
				scope->current_set = set;
				continue;
			}
		fail:
			scope->current_set = set;
			/* remove expr for portability with different struct members */
			psi_plist_del(func->inner, --i, NULL);
			psi_set_exp_free(&inner);
		}
	}

	switch (func->type) {
	case PSI_T_VOID:
		func->handler = psi_set_void;
		break;
	case PSI_T_ZVAL:
		func->handler = psi_set_zval;
		break;
	case PSI_T_TO_BOOL:
		func->handler = psi_set_to_bool;
		break;
	case PSI_T_TO_INT:
		func->handler = psi_set_to_int;
		break;
	case PSI_T_TO_FLOAT:
		func->handler = psi_set_to_float;
		break;
	case PSI_T_TO_OBJECT:
		func->handler = psi_set_to_object;
		break;
	case PSI_T_TO_STRING:
		if (!psi_set_func_validate_to_string(data, func, set, scope->impl)) {
			return false;
		}
		break;
	case PSI_T_TO_ARRAY:
		if (!psi_set_func_validate_to_array(data, func, set, scope->impl)) {
			return false;
		}
		break;
	default:
		data->error(data, func->token, PSI_WARNING,
				"Unknown cast '%s' in `set` statement of implementation '%s'",
				func->name, scope->impl->func->name);
		return false;
	}

	return true;
}
