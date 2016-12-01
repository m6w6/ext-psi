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

#include <assert.h>

#include "data.h"
#include "calc.h"
#include "call.h"


struct psi_number *psi_number_init(token_t t, void *num)
{
	struct psi_number *exp = calloc(1, sizeof(*exp));

	switch (exp->type = t) {
	case PSI_T_INT8:
		exp->data.ival.i64 = *(int8_t *) num;
		break;
	case PSI_T_UINT8:
		exp->data.ival.i64 = *(uint8_t *) num;
		break;
	case PSI_T_INT16:
		exp->data.ival.i64 = *(int16_t *) num;
		break;
	case PSI_T_UINT16:
		exp->data.ival.i64 = *(uint16_t *) num;
		break;
	case PSI_T_INT32:
		exp->data.ival.i64 = *(int32_t *) num;
		break;
	case PSI_T_UINT32:
		exp->data.ival.i64 = *(uint32_t *) num;
		break;
	case PSI_T_INT64:
		exp->data.ival.i64 = *(int64_t *) num;
		break;
	case PSI_T_UINT64:
		exp->data.ival.i64 = *(uint64_t *) num;
		break;
	case PSI_T_FLOAT:
		exp->data.ival.dval = *(float *) num;
		break;
	case PSI_T_DOUBLE:
		exp->data.ival.dval = *(double *) num;
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		exp->data.numb = strdup(num);
		break;
	case PSI_T_NAME:
		exp->data.dvar = num;
		break;
	default:
		assert(0);
	}

	return exp;
}

struct psi_number *psi_number_copy(struct psi_number *exp)
{
	struct psi_number *num = calloc(1, sizeof(*num));

	*num = *exp;

	if (num->token) {
		num->token = psi_token_copy(num->token);
	}
	switch (num->type) {
	case PSI_T_INT64:
	case PSI_T_DOUBLE:
	case PSI_T_ENUM:
	case PSI_T_CONST:
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		num->data.numb = strdup(num->data.numb);
		break;
	case PSI_T_NAME:
		num->data.dvar = psi_decl_var_copy(num->data.dvar);
		break;
	default:
		assert(0);
	}
	return num;
}

void psi_number_free(struct psi_number **exp_ptr)
{
	if (*exp_ptr) {
		struct psi_number *exp = *exp_ptr;

		*exp_ptr = NULL;
		if (exp->token) {
			free(exp->token);
		}
		switch (exp->type) {
		case PSI_T_INT64:
		case PSI_T_DOUBLE:
		case PSI_T_ENUM:
		case PSI_T_CONST:
			break;
		case PSI_T_NSNAME:
		case PSI_T_NUMBER:
			free(exp->data.numb);
			break;
		case PSI_T_NAME:
			psi_decl_var_free(&exp->data.dvar);
			break;
		default:
			assert(0);
		}
		free(exp);
	}
}

void psi_number_dump(int fd, struct psi_number *exp)
{
	switch (exp->type) {
	case PSI_T_INT64:
		dprintf(fd, "%" PRId64, exp->data.ival.i64);
		break;
	case PSI_T_DOUBLE:
		dprintf(fd, "%F", exp->data.ival.dval);
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		dprintf(fd, "%s", exp->data.numb);
		break;
	case PSI_T_CONST:
		dprintf(fd, "%s", exp->data.cnst->name);
		break;
	case PSI_T_ENUM:
		dprintf(fd, "%s", exp->data.enm->name);
		break;
	case PSI_T_NAME:
		psi_decl_var_dump(fd, exp->data.dvar);
		break;
	default:
		assert(0);
	}
}

static inline bool psi_number_validate_enum(struct psi_data *data, struct psi_number *exp,
		struct psi_decl_enum *enm)
{
	size_t i = 0;
	struct psi_decl_enum_item *itm;

	while (psi_plist_get(enm->items, i++, &itm)) {
		if (!strcmp(itm->name, exp->data.dvar->name)) {
			psi_decl_var_free(&exp->data.dvar);
			exp->type = PSI_T_ENUM;
			exp->data.enm = itm;
			return psi_number_validate(data, exp, NULL, NULL, NULL, NULL, enm);
		}
	}

	return false;
}

bool psi_number_validate(struct psi_data *data, struct psi_number *exp,
		struct psi_impl *impl, struct psi_decl *cb_decl, struct psi_let_exp *current_let,
		struct psi_set_exp *current_set, struct psi_decl_enum *current_enum)
{
	size_t i = 0;
	impl_val tmp = {0};
	struct psi_const *cnst;
	struct psi_decl_enum *enm;

	switch (exp->type) {
	case PSI_T_CONST:
	case PSI_T_INT64:
	case PSI_T_DOUBLE:
	case PSI_T_ENUM:
		return true;

	case PSI_T_NAME:
		if (current_enum && psi_number_validate_enum(data, exp, current_enum)) {
			return true;
		}
		while (psi_plist_get(data->enums, i++, &enm)) {
			if (psi_number_validate_enum(data, exp, enm)) {
				return true;
			}
		}
		if (exp->data.dvar->arg) {
			return true;
		}
		if (psi_decl_var_validate(data, exp->data.dvar, impl ? impl->decl : NULL,
				current_let, current_set)) {
			return true;
		}
		if (cb_decl && psi_decl_var_validate(data, exp->data.dvar, cb_decl, NULL, NULL)) {
			return true;
		}
		data->error(data, exp->token, PSI_WARNING,
				"Unknown variable '%s' in numeric expression",
				exp->data.dvar->name);
		return false;

	case PSI_T_NSNAME:
		while (psi_plist_get(data->consts, i++, &cnst)) {
			if (!strcmp(cnst->name, exp->data.numb)) {
				free(exp->data.numb);
				exp->type = PSI_T_CONST;
				exp->data.cnst = cnst;
				return true;
			}
		}
		data->error(data, exp->token, PSI_WARNING,
				"Unknown constant '%s' in numeric expression",
				exp->data.numb);
		return false;

	case PSI_T_NUMBER:
		switch (is_numeric_string(exp->data.numb, strlen(exp->data.numb), (zend_long *) &tmp, (double *) &tmp, 0)) {
		case IS_LONG:
			free(exp->data.numb);
			exp->type = PSI_T_INT64;
			exp->data.ival.i64 = tmp.zend.lval;
			return true;

		case IS_DOUBLE:
			free(exp->data.numb);
			exp->type = PSI_T_DOUBLE;
			exp->data.ival.dval = tmp.dval;
			return true;
		}
		data->error(data, exp->token, PSI_WARNING, "Expected numeric entity (parser error?)");
		return false;

	default:
		assert(0);
	}

	return false;
}

#include "Zend/zend_constants.h"

static inline token_t psi_number_eval_constant(struct psi_number *exp,
		impl_val *res, struct psi_call_frame *frame)
{
	switch (exp->data.cnst->type->type) {
	case PSI_T_INT:
		res->i64 = zend_get_constant_str(exp->data.cnst->name,
				strlen(exp->data.cnst->name))->value.lval;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;
	case PSI_T_FLOAT:
		res->dval = zend_get_constant_str(exp->data.cnst->name,
				strlen(exp->data.cnst->name))->value.dval;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIdval, res->dval);
		return PSI_T_DOUBLE;
	default:
		if (frame) PSI_DEBUG_PRINT(frame->context, " ?(t=%d)", exp->data.cnst->type->type);
		return 0;
	}
}


static inline token_t psi_number_eval_decl_var(struct psi_number *exp,
		impl_val *res, struct psi_call_frame *frame)
{
	impl_val *ref;
	struct psi_call_frame_symbol *sym;
	struct psi_decl_type *real;
	size_t size;

	real = psi_decl_type_get_real(exp->data.dvar->arg->type);
	size = psi_decl_arg_get_size(exp->data.dvar->arg);
	sym = psi_call_frame_fetch_symbol(frame, exp->data.dvar);
	ref = deref_impl_val(sym->ptr, exp->data.dvar);

	memcpy(res, ref, size);

	return real->type;
}

token_t psi_number_eval(struct psi_number *exp, impl_val *res, struct psi_call_frame *frame)
{
	switch (exp->type) {
	case PSI_T_INT64:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;

	case PSI_T_DOUBLE:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIdval, res->dval);
		return exp->type;

	case PSI_T_ENUM:
		res->i64 = exp->data.enm->val;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;

	case PSI_T_CONST:
		return psi_number_eval_constant(exp, res, frame);
		break;

	case PSI_T_NAME:
		return psi_number_eval_decl_var(exp, res, frame);
		break;

	default:
		assert(0);
	}
	return 0;
}
