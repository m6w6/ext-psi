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
#include "call.h"
#include "calc.h"
#include "marshal.h"

struct psi_set_exp *psi_set_exp_init(enum psi_set_exp_kind kind, void *data)
{
	struct psi_set_exp *val = calloc(1, sizeof(*val));

	switch (val->kind = kind) {
	case PSI_SET_FUNC:
		val->data.func = data;
		val->inner = val->data.func->inner;
		break;
	case PSI_SET_NUMEXP:
		val->data.num = data;
		break;
	default:
		assert(0);
	}

	return val;
}

void psi_set_exp_exec(struct psi_set_exp *val, struct psi_call_frame *frame)
{
	struct psi_call_frame_symbol *frame_sym = NULL;
	struct psi_call_frame_argument *frame_arg;
	struct psi_decl_var *set_dvar = psi_set_exp_get_decl_var(val);
	struct psi_impl_var *set_ivar = psi_set_exp_get_impl_var(val);

	assert(set_dvar);
	assert(set_ivar);

	frame_sym = psi_call_frame_fetch_symbol(frame, set_dvar);
	frame_arg = psi_call_frame_get_argument(frame, set_ivar->fqn);

	if (frame_arg && frame_arg->zval_ptr) {
		zval_dtor(frame_arg->zval_ptr);
		psi_set_exp_exec_ex(val, frame_arg->zval_ptr, frame_sym->ptr, frame);
	}
}

void psi_set_exp_exec_ex(struct psi_set_exp *val, zval *zv, impl_val *iv,
		struct psi_call_frame *frame)
{
	switch (val->kind) {
	case PSI_SET_FUNC:
		val->data.func->handler(zv, val, iv, frame);
		break;
	case PSI_SET_NUMEXP:
		switch (psi_num_exp_exec(val->data.num, iv, frame)) {
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
		case PSI_T_LONG_DOUBLE:
			psi_set_to_float(zv, val, iv, frame);
			break;
		default:
			psi_set_to_int(zv, val, iv, frame);
			break;
		}
		break;
	default:
		assert(0);
		break;
	}
}

void psi_set_exp_free(struct psi_set_exp **exp_ptr)
{
	if (*exp_ptr) {
		struct psi_set_exp *exp = *exp_ptr;

		*exp_ptr = NULL;

		if (exp->inner && (!exp->outer || exp->outer->inner != exp->inner)) {
			psi_plist_free(exp->inner);
		}

		switch (exp->kind) {
		case PSI_SET_FUNC:
			psi_set_func_free(&exp->data.func);
			break;
		case PSI_SET_NUMEXP:
			psi_num_exp_free(&exp->data.num);
			break;
		default:
			assert(0);
			break;
		}
		if (exp->var) {
			psi_impl_var_free(&exp->var);
		}
		free(exp);
	}
}

void psi_set_exp_dump(int fd, struct psi_set_exp *set, unsigned level, int last)
{
	if (level > 1) {
		/* only if not directly after `set ...` */
		dprintf(fd, "%s", psi_t_indent(level));
	}

	if (set->var) {
		/* parsed, or generated */
		if (set->var->token) {
			dprintf(fd, "%s = ", set->var->name);
		}
	}

	switch (set->kind) {
	case PSI_SET_FUNC:
		psi_set_func_dump(fd, set->data.func, level);
		break;
	case PSI_SET_NUMEXP:
		psi_num_exp_dump(fd, set->data.num);
		break;
	default:
		assert(0);
	}

	if (!last) {
		dprintf(fd, ",");
	}

	if (set->var) {
		dprintf(fd, "\t/* fqn=%s */", set->var->fqn);
	}
}

struct psi_decl_var *psi_set_exp_get_decl_var(struct psi_set_exp *exp)
{
	switch (exp->kind) {
	case PSI_SET_FUNC:
		return exp->data.func->var;
	default:
		return NULL;
	}
}

struct psi_impl_var *psi_set_exp_get_impl_var(struct psi_set_exp *exp)
{
	if (!exp->var) {
		struct psi_decl_var *dvar = psi_set_exp_get_decl_var(exp);
		char *dollar_name;

		if (!dvar) {
			return NULL;
		}

		dollar_name = psi_impl_var_name_prepend(strdup("$"), dvar->name);
		exp->var = psi_impl_var_init(dollar_name, 0);
		free(dollar_name);
	}

	return exp->var;
}

bool psi_set_exp_validate(struct psi_data *data, struct psi_set_exp *set,
		struct psi_impl *impl, struct psi_decl *cb_decl)
{
	struct psi_impl_var *ivar = psi_set_exp_get_impl_var(set);

	if (ivar && !psi_impl_var_validate(data, ivar, impl, NULL, set)) {
		data->error(data, ivar->token ? : **(struct psi_token ***) &set->data,
				PSI_WARNING, "Unknown variable '%s'", ivar->name);
		return false;
	}

	switch (set->kind) {
	case PSI_SET_NUMEXP:
		if (!psi_num_exp_validate(data, set->data.num, impl, cb_decl, NULL, set, NULL)) {
			return false;
		}
		break;
	case PSI_SET_FUNC:
		if (!psi_set_func_validate(data, set->data.func, set, impl, cb_decl)) {
			return false;
		}
		break;
	default:
		assert(0);
	}
	return true;
}

