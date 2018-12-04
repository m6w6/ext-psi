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
#include "calc.h"

#include <assert.h>

#include <Zend/zend_smart_str.h>

struct psi_let_exp *psi_let_exp_init_ex(struct psi_decl_var *var,
		enum psi_let_exp_kind kind, void *data)
{
	struct psi_let_exp *val = psi_let_exp_init(kind, data);
	val->var = var;
	return val;
}

struct psi_let_exp *psi_let_exp_init(enum psi_let_exp_kind kind, void *data)
{
	struct psi_let_exp *let = pecalloc(1, sizeof(*let), 1);
	switch (let->kind = kind) {
	case PSI_LET_NULL:
		assert(!data);
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

void psi_let_exp_free(struct psi_let_exp **let_ptr)
{
	if (*let_ptr) {
		struct psi_let_exp *let = *let_ptr;

		*let_ptr = NULL;
		switch (let->kind) {
		case PSI_LET_NULL:
			break;
		case PSI_LET_NUMEXP:
			psi_num_exp_free(&let->data.num);
			break;
		case PSI_LET_CALLOC:
			psi_let_calloc_free(&let->data.alloc);
			break;
		case PSI_LET_CALLBACK:
			psi_let_callback_free(&let->data.callback);
			break;
		case PSI_LET_FUNC:
			psi_let_func_free(&let->data.func);
			break;
		case PSI_LET_TMP:
			psi_decl_var_free(&let->data.var);
			break;
		default:
			assert(0);
		}
		if (let->var) {
			psi_decl_var_free(&let->var);
		}
		free(let);
	}
}

void psi_let_exp_dump(struct psi_dump *dump, struct psi_let_exp *val, unsigned level, int last)
{
	if (level > 1) {
		/* only if not directly after `set ...` */
		PSI_DUMP(dump, "%s", psi_t_indent(level));
	}

	if (val->var) {
		if (val->var->token) {
			psi_decl_var_dump(dump, val->var);
			PSI_DUMP(dump, " = ");
		}
	}
	if (val->is_reference) {
		PSI_DUMP(dump, "&");
	}

	switch (val->kind) {
	case PSI_LET_NULL:
		PSI_DUMP(dump, "NULL");
		break;
	case PSI_LET_TMP:
		psi_decl_var_dump(dump, val->data.var);
		PSI_DUMP(dump, "\t/* fqn=%s */", val->data.var->fqn->val);
		break;
	case PSI_LET_CALLOC:
		psi_let_calloc_dump(dump, val->data.alloc);
		break;
	case PSI_LET_CALLBACK:
		psi_let_callback_dump(dump, val->data.callback, level);
		break;
	case PSI_LET_FUNC:
		psi_let_func_dump(dump, val->data.func, level);
		break;
	case PSI_LET_NUMEXP:
		psi_num_exp_dump(dump, val->data.num);
		break;

	default:
		assert(0);
	}

	if (val->var) {
		PSI_DUMP(dump, "\t/* fqn=%s */", val->var->fqn->val);
	}

	if (level > 1) {
		if (!last) {
			PSI_DUMP(dump, ",");
		}
	} else {
		PSI_DUMP(dump, ";");
	}
}

bool psi_let_exp_validate(struct psi_data *data, struct psi_let_exp *val,
		struct psi_validate_scope *scope)
{
	struct psi_decl_var *dvar = psi_let_exp_get_decl_var(val);

	switch (val->kind) {
	case PSI_LET_TMP:
		if (!psi_decl_var_validate(data, val->data.var, scope)) {
			data->error(data, dvar->token ? : **(struct psi_token ***) &val->data,
					PSI_WARNING, "Unknown variable '%s' in temp let statment of implementation '%s'",
					dvar->name->val, scope->impl->func->name->val);
			return false;
		}
		break;

	default:
		if (!psi_decl_var_validate(data, dvar, scope)) {
			data->error(data, dvar->token ? : **(struct psi_token ***) &val->data,
					PSI_WARNING, "Unknown variable '%s' in let statement of implementation '%s'",
					dvar->name->val, scope->impl->func->name->val);
			return false;
		}
		break;
	}
	switch (val->kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_TMP:
		/* e.g. let bar = &strval($bar); // decl_arg(char **bar) */
		/* e.g. let foo = *bar;  */
		val->var->pointer_level = val->data.var->pointer_level;
		val->var->arg = val->data.var->arg;
		break;
	case PSI_LET_NUMEXP:
		if (!psi_num_exp_validate(data, val->data.num, scope)) {
			return false;
		}
		break;
	case PSI_LET_CALLOC:
		if (!psi_num_exp_validate(data, val->data.alloc->nmemb, scope)) {
			return false;
		}
		if (!psi_num_exp_validate(data, val->data.alloc->size, scope)) {
			return false;
		}
		break;
	case PSI_LET_CALLBACK:
		if (!psi_let_func_validate(data, val->data.callback->func, scope)) {
			return false;
		}
		if (!psi_let_callback_validate(data, val->data.callback, scope)) {
			return false;
		}
		break;
	case PSI_LET_FUNC:
		if (!psi_let_func_validate(data, val->data.func, scope)) {
			return false;
		}
		break;
	}

	return true;
}

void *psi_let_exp_exec(struct psi_let_exp *val, struct psi_decl_arg *darg,
		void *actual_location, size_t actual_size, struct psi_call_frame *frame)
{
	struct psi_call_frame_symbol *frame_sym;

	frame_sym = psi_call_frame_fetch_symbol(frame, val->var);

	switch (val->kind) {
	case PSI_LET_NULL:
		/* FIXME: sizeof_decl_arg */
		if (darg && darg->var->array_size) {
			frame_sym->temp_val.ptr = ecalloc(1, psi_decl_arg_get_size(darg));
		} else {
			memset(&frame_sym->temp_val, 0, sizeof(frame_sym->temp_val));
		}
		break;

	case PSI_LET_TMP:
		{
			struct psi_impl *impl = psi_call_frame_get_impl(frame);
			struct psi_let_stmt *let_temp = psi_impl_get_let(impl, val->data.var);
			struct psi_call_frame_symbol *temp_arg;
			impl_val *src;

			temp_arg = psi_call_frame_fetch_symbol(frame, let_temp->exp->var);
			src = deref_impl_val(temp_arg->ptr, val->data.var);
			memcpy(&frame_sym->temp_val, src, psi_decl_var_get_size(let_temp->exp->var));
		}
		break;

	case PSI_LET_CALLOC:
		{
			zend_long n = psi_num_exp_get_long(val->data.alloc->nmemb, frame, NULL);
			zend_long s = psi_num_exp_get_long(val->data.alloc->size, frame, NULL);
			void *tmp;

			if (val->data.alloc->static_memory) {
				tmp = safe_pemalloc(n, s, sizeof(void *), 1);
			} else {
				tmp = *psi_call_frame_push_auto(frame, safe_emalloc(n, s, sizeof(void *)));
			}

			memset(tmp, 0, n * s + sizeof(void *));
			frame_sym->temp_val.ptr = tmp;
		}
		break;

	case PSI_LET_NUMEXP:
		{
			impl_val res;
			token_t val_type = psi_decl_type_get_real(val->var->arg->type)->type;
			token_t res_type = psi_num_exp_exec(val->data.num, &res, frame, NULL);

			if (val_type == res_type) {
				frame_sym->temp_val = res;
			} else {
				psi_calc_cast(res_type, &res, val_type, &frame_sym->temp_val);
			}
		}
		break;

	case PSI_LET_CALLBACK:
		frame_sym->temp_val.ptr = val->data.callback->decl->sym;
		break;

	case PSI_LET_FUNC:
		if (!psi_let_func_exec(val, val->data.func, darg, frame)) {
			return NULL;
		}
		break;
	}

	if (val->is_reference) {
		frame_sym->ptr = &frame_sym->ival_ptr;
	} else {
		frame_sym->ptr = frame_sym->ival_ptr;
	}

	if (actual_location) {
		assert(!val->is_reference || actual_size == SIZEOF_VOID_P);
		memcpy(actual_location, frame_sym->ptr, actual_size);
		frame_sym->ptr = actual_location;
	}

	return frame_sym->ptr;
}

struct psi_let_func* psi_let_exp_get_func(struct psi_let_exp* exp)
{
	if (exp) {
		switch (exp->kind) {
		case PSI_LET_CALLBACK:
			return exp->data.callback->func;
		case PSI_LET_FUNC:
			return exp->data.func;
		default:
			break;
		}
	}
	return NULL;
}

struct psi_decl_var *psi_let_exp_get_decl_var(struct psi_let_exp *val)
{
	if (!val->var) {
		zend_string *name = psi_let_exp_get_decl_var_name(val);

		if (name) {
			val->var = psi_decl_var_init(name, 0, 0);
			zend_string_release(name);
		}
	}
	return val->var;
}

struct psi_impl_var *psi_let_exp_get_impl_var(struct psi_let_exp *val)
{
	struct psi_let_func* fn = psi_let_exp_get_func(val);
	return fn ? fn->var : NULL;
}

zend_string *psi_let_exp_get_decl_var_name(struct psi_let_exp* val)
{
	struct psi_impl_var* var;

	if (val->var) {
		return zend_string_copy(val->var->name);
	}

	var = psi_let_exp_get_impl_var(val);
	if (var) {
		smart_str name = {0};

		smart_str_appendl_ex(&name, &var->name->val[1], var->name->len - 1, 1);

		return smart_str_extract(&name);
	}

	return NULL;
}
