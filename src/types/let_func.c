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
#include "data.h"
#include "call.h"
#include "marshal.h"

#include "php.h"

#include <assert.h>

struct psi_let_func *psi_let_func_init(token_t type, zend_string *name,
		struct psi_impl_var *var)
{
	struct psi_let_func *func = pecalloc(1, sizeof(*func), 1);
	func->type = type;
	func->name = zend_string_copy(name);
	func->var = var;
	return func;
}

void psi_let_func_free(struct psi_let_func **func_ptr)
{
	if (*func_ptr) {
		struct psi_let_func *func = *func_ptr;

		*func_ptr = NULL;
		psi_token_free(&func->token);
		psi_impl_var_free(&func->var);
		zend_string_release(func->name);
		if (func->inner) {
			psi_plist_free(func->inner);
		}
		free(func);
	}
}

void psi_let_func_dump(struct psi_dump *dump, struct psi_let_func *func, unsigned level)
{
	PSI_DUMP(dump, "%s(%s\t/* fqn=%s */", func->name->val, func->var->name->val,
			func->var->fqn->val);

	if (func->inner) {
		size_t i = 0, count = psi_plist_count(func->inner);
		struct psi_let_exp *inner;

		PSI_DUMP(dump, ",");
		++level;
		while (psi_plist_get(func->inner, i++, &inner)) {
			PSI_DUMP(dump, "\n");
			psi_let_exp_dump(dump, inner, level, i == count);
		}
		--level;
		PSI_DUMP(dump, "\n");
		PSI_DUMP(dump, "%s", psi_t_indent(level));
	}
	PSI_DUMP(dump, ")");
}

static inline int validate_let_func_type(struct psi_data *data,
		struct psi_let_func *func, struct psi_validate_scope *scope)
{
	switch (func->type) {
	case PSI_T_BOOLVAL:
	case PSI_T_INTVAL:
	case PSI_T_FLOATVAL:
	case PSI_T_STRVAL:
	case PSI_T_STRLEN:
	case PSI_T_PATHVAL:
	case PSI_T_OBJVAL:
	case PSI_T_ZVAL:
	case PSI_T_VOID:
	case PSI_T_COUNT:
		return true;

	case PSI_T_ARRVAL:
		if (!func->inner) {
			data->error(data, func->token, PSI_WARNING,
					"Expected sub-expressions in `arrval` expression");
			return false;
		}
		return true;

	default:
		data->error(data, func->var->token, PSI_WARNING,
				"Unknown `let` cast function '%s' of implementation '%s'",
				func->name->val, scope->impl->func->name->val);
		return false;
	}
}

static inline bool validate_let_func_inner(struct psi_data *data,
		struct psi_let_func *func, struct psi_validate_scope *scope)
{
	struct psi_let_exp *exp = scope->current_let;

	if (func->inner) {
		struct psi_decl_var *let_var = psi_let_exp_get_decl_var(exp);
		struct psi_decl_type *var_typ;
		struct psi_plist *sub_args;

		sub_args = psi_decl_type_get_args(let_var->arg->type, &var_typ);

		if (func->type == PSI_T_ARRVAL && sub_args) {
			/* struct = arrval($array,
			 * 	member = strval($member) ...)
			 */
			size_t i = 0;
			struct psi_let_exp *inner;

			while (psi_plist_get(func->inner, i++, &inner)) {
				zend_string *name = psi_let_exp_get_decl_var_name(inner);
				struct psi_decl_arg *sub_arg;

				inner->outer = exp;

				if (name) {
					sub_arg = psi_decl_arg_get_by_name(sub_args, name);
					zend_string_release(name);
				}
				if (!name || !sub_arg) {
					/* remove expr for portability with different struct members */
					psi_plist_del(func->inner, --i, NULL);
					psi_let_exp_free(&inner);
				} else {
					scope->current_let = inner;
					if (!psi_let_exp_validate(data, inner, scope)) {
						scope->current_let = exp;
						return false;
					}
					scope->current_let = exp;
				}
			}
		} else if (func->type == PSI_T_ARRVAL
				&& psi_plist_count(func->inner) == 1
				&& let_var->arg->var->pointer_level) {
			/* array = arrval($array,
			 * 	strval($array)) // cast foreach entry
			 */
			struct psi_let_exp *inner;
			struct psi_impl_var *sub_var;
			struct psi_impl_var *sub_ref;

			psi_plist_get(func->inner, 0, &inner);
			inner->outer = exp;

			sub_var = psi_let_exp_get_impl_var(exp);
			sub_ref = psi_let_exp_get_impl_var(inner);
			if (!zend_string_equals(sub_var->name, sub_ref->name)) {
				data->error(data, sub_var->token, E_WARNING,
						"Inner `set` statement casts on pointers must"
								" reference the same variable");
				return false;
			}
			scope->current_let = inner;
			if (!psi_let_exp_validate(data, inner, scope)) {
				scope->current_let = exp;
				return false;
			}
			scope->current_let = exp;
		} else {
			data->error(data, let_var->token, PSI_WARNING,
					"Inner let statement's values must refer to a structure or"
							" array type, got '%s%s' for '%s'", var_typ->name,
					psi_t_indirection(let_var->arg->var->pointer_level),
					let_var->name->val);
			return false;
		}

		if (!psi_plist_count(func->inner)) {
			data->error(data, func->token, PSI_WARNING,
					"No valid sub-expressions left");
			return false;
		}
	}

	return true;
}

bool psi_let_func_validate(struct psi_data *data, struct psi_let_func *func,
		struct psi_validate_scope *scope)
{
	if (scope->impl->func->args) {
		/* FIXME, func->var does not need to be referring to a func arg */
		psi_impl_get_arg(scope->impl, func->var);
	}

	if (!psi_impl_var_validate(data, func->var, scope)) {
		return false;
	}

	if (!validate_let_func_type(data, func, scope)) {
		return false;
	}
	if (!validate_let_func_inner(data, func, scope)) {
		return false;
	}
	return 1;
}

static void exec_let_func_arrval_inner(struct psi_let_func *func,
		struct psi_decl_arg *darg, struct psi_decl_arg *inner_decl_arg,
		struct psi_call_frame_argument *frame_arg,
		struct psi_let_exp *inner_let_exp, void *container,
		struct psi_call_frame *frame)
{
	struct psi_let_func *inner_func = psi_let_exp_get_func(inner_let_exp);
	struct psi_impl_var *inner_var = inner_func->var;

	if (psi_decl_type_get_real(darg->type)->type == PSI_T_UNION) {
		/* skip if there's no entry in the outer_zval;
		 * we only want to set supplied data on unions
		 */
		if (!zend_symtable_str_exists(Z_ARRVAL_P(frame_arg->zval_ptr),
				&inner_var->name->val[1], inner_var->name->len - 1)) {
			return;
		}
	}
	psi_call_frame_sub_argument(frame, inner_var, frame_arg->zval_ptr,
			inner_func->var->fqn);

	/* example from dm_store/dbm_fetch with arrval($string) conversion:
	 let key = arrval($key,
	   dptr = strval($0),
	   dsize = strlen($0)
	 );
	 # ---
	 darg = key
	 frame_arg = $key
	 inner_var = $0
	 full_func_var_name = $key.0
	 inner_decl_arg = key.dptr
	 */
	psi_let_exp_exec(inner_let_exp, inner_decl_arg,
			((char *) container) + inner_decl_arg->layout->pos,
			inner_decl_arg->layout->len, frame);
}

static void *exec_let_func_arrval(struct psi_let_exp *val,
		struct psi_let_func *func, struct psi_decl_arg *darg,
		struct psi_call_frame *frame);

static void exec_let_func_arrval_seq(struct psi_let_func *func,
		struct psi_decl_arg *darg,
		struct psi_call_frame_argument *frame_arg,
		struct psi_let_exp *inner_let_exp, void *container,
		struct psi_call_frame *frame)
{
	zval *zval_ptr = NULL;
	psi_marshal_let let_fn;
	size_t i = 0, size;
	struct psi_decl_var *dvar;

	if (inner_let_exp->var) {
		/* arrval($foo, *foo = intval($foo)); */
		dvar = inner_let_exp->var;
	} else {
		/* arrval($foo, intval($foo)); */
		dvar = psi_decl_var_copy(darg->var);
		assert(dvar->pointer_level);
		--dvar->pointer_level;
	}

	dvar->pointer_level += inner_let_exp->is_reference;
	size = psi_decl_var_get_size(dvar);
	dvar->pointer_level -= inner_let_exp->is_reference;

	let_fn = locate_let_func_fn(inner_let_exp->data.func->type);

	ZEND_HASH_FOREACH_VAL_IND(Z_ARRVAL_P(frame_arg->zval_ptr), zval_ptr)
	{
		void *temp = NULL;
		impl_val val = {0}, *ptr, *sub;

		if (let_fn) {
			ptr = let_fn(&val, darg, 0, NULL, zval_ptr, &temp);
			if (temp) {
				psi_call_frame_push_auto(frame, temp);
			}
		} else if (func->type == PSI_T_ARRVAL) {
			ptr = exec_let_func_arrval(inner_let_exp,
					inner_let_exp->data.func, darg, frame);
		} else {
			assert(0);
			return;
		}

		sub = deref_impl_val(ptr, dvar);

		memcpy(&((char *) container)[size * i++], &sub, size);
	}
	ZEND_HASH_FOREACH_END();

	if (dvar != inner_let_exp->var) {
		psi_decl_var_free(&dvar);
	}
}

static void *exec_let_func_arrval(struct psi_let_exp *val,
		struct psi_let_func *func, struct psi_decl_arg *darg,
		struct psi_call_frame *frame)
{
	void *container = NULL;
	struct psi_call_frame_argument *frame_arg;
	struct psi_plist *darg_members;

	darg_members = psi_decl_type_get_args(darg->type, NULL);
	frame_arg = psi_call_frame_get_argument(frame, func->var->fqn);

	if (frame_arg->zval_ptr && Z_TYPE_P(frame_arg->zval_ptr) != IS_ARRAY) {
		convert_to_array(frame_arg->zval_ptr);
	}

	if (darg_members && func->inner) {
		/* struct or union
		 * arrval($foo,
		 *  str = strval($str),
		 *  num = intval($num));
		 */
		size_t i = 0, size;
		struct psi_let_exp *inner;
		struct psi_decl_arg *darg_member;

		val->var->pointer_level += val->is_reference;
		size = psi_decl_var_get_size(val->var);
		container = ecalloc(1, size);
		val->var->pointer_level -= val->is_reference;

		if (frame_arg->zval_ptr) {
			while (psi_plist_get(func->inner, i++, &inner)) {
				zend_string *var_name = psi_let_exp_get_decl_var_name(inner);
				darg_member = psi_decl_arg_get_by_name(darg_members, var_name);

				exec_let_func_arrval_inner(func, darg, darg_member, frame_arg,
						inner, container, frame);
				zend_string_release(var_name);
			}
		}
	} else if (func->inner) {
		/* array
		 * arrval($foo, foo = intval($foo))
		 */
		size_t arcount;
		struct psi_let_exp *inner;

		if (!frame_arg->zval_ptr) {
			return NULL;
		}
		assert(psi_plist_count(func->inner) == 1);

		arcount = zend_array_count(Z_ARRVAL_P(frame_arg->zval_ptr));
		psi_plist_get(func->inner, 0, &inner);

		inner->var->pointer_level += inner->is_reference;
		container = ecalloc(arcount + 1, psi_decl_var_get_size(inner->var));
		inner->var->pointer_level -= inner->is_reference;

		exec_let_func_arrval_seq(func, darg, frame_arg, inner, container, frame);
	} else {
		assert(0);
	}

	return *psi_call_frame_push_auto(frame, container);
}

void *psi_let_func_exec(struct psi_let_exp *val, struct psi_let_func *func,
		struct psi_decl_arg *darg, struct psi_call_frame *frame)
{
	struct psi_call_frame_symbol *frame_sym;
	psi_marshal_let let_fn = locate_let_func_fn(func->type);

	frame_sym = psi_call_frame_fetch_symbol(frame, val->var);

	if (let_fn) {
		void *temp = NULL;
		struct psi_call_frame_argument *iarg;

		iarg = psi_call_frame_get_argument(frame, func->var->fqn);

		assert(iarg);

		frame_sym->ival_ptr = let_fn(&frame_sym->temp_val, darg,
				iarg->spec ? iarg->spec->type->type : 0, iarg->ival_ptr,
				iarg->zval_ptr, &temp);
		if (temp) {
			psi_call_frame_push_auto(frame, temp);
		}
	} else if (func->type == PSI_T_ARRVAL) {
		frame_sym->ival_ptr = exec_let_func_arrval(val, func, darg, frame);
	}

	return frame_sym->ival_ptr;
}
