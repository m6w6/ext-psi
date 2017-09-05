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
#include "parser.h"

struct psi_number *psi_number_init(token_t t, void *num, unsigned flags)
{
	struct psi_number *exp = calloc(1, sizeof(*exp));

	exp->flags = flags;
	switch (exp->type = t) {
	case PSI_T_INT8:
		exp->data.ival.i8 = *(int8_t *) num;
		break;
	case PSI_T_UINT8:
		exp->data.ival.u8 = *(uint8_t *) num;
		break;
	case PSI_T_INT16:
		exp->data.ival.i16 = *(int16_t *) num;
		break;
	case PSI_T_UINT16:
		exp->data.ival.u16 = *(uint16_t *) num;
		break;
	case PSI_T_INT32:
		exp->data.ival.i32 = *(int32_t *) num;
		break;
	case PSI_T_UINT32:
		exp->data.ival.u32 = *(uint32_t *) num;
		break;
	case PSI_T_INT64:
		exp->data.ival.i64 = *(int64_t *) num;
		break;
	case PSI_T_UINT64:
		exp->data.ival.u64 = *(uint64_t *) num;
		break;
	case PSI_T_FLOAT:
		exp->data.ival.dval = *(float *) num;
		exp->type = PSI_T_DOUBLE;
		break;
	case PSI_T_DOUBLE:
		exp->data.ival.dval = *(double *) num;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		exp->data.ival.ldval = *(long double *) num;
		break;
#endif
	case PSI_T_QUOTED_CHAR:
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_DEFINE:
		exp->data.numb = strdup(num);
		break;
	case PSI_T_NAME:
		exp->data.dvar = num;
		break;
	case PSI_T_FUNCTION:
		exp->data.call = num;
		break;
	case PSI_T_SIZEOF:
		exp->data.dtyp = num;
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
	case PSI_T_INT8:
	case PSI_T_UINT8:
	case PSI_T_INT16:
	case PSI_T_UINT16:
	case PSI_T_INT32:
	case PSI_T_UINT32:
	case PSI_T_INT64:
	case PSI_T_UINT64:
	case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
#endif
	case PSI_T_ENUM:
	case PSI_T_CONST:
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_DEFINE:
	case PSI_T_QUOTED_CHAR:
		num->data.numb = strdup(num->data.numb);
		break;
	case PSI_T_NAME:
		num->data.dvar = psi_decl_var_copy(num->data.dvar);
		break;
	case PSI_T_FUNCTION:
		num->data.call = psi_cpp_macro_call_copy(num->data.call);
		break;
	case PSI_T_SIZEOF:
		num->data.dtyp = psi_decl_type_copy(num->data.dtyp);
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
		case PSI_T_INT8:
		case PSI_T_UINT8:
		case PSI_T_INT16:
		case PSI_T_UINT16:
		case PSI_T_INT32:
		case PSI_T_UINT32:
		case PSI_T_INT64:
		case PSI_T_UINT64:
		case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
#endif
		case PSI_T_ENUM:
		case PSI_T_CONST:
			break;
		case PSI_T_FUNCTION:
			psi_cpp_macro_call_free(&exp->data.call);
			break;
		case PSI_T_NSNAME:
		case PSI_T_NUMBER:
		case PSI_T_DEFINE:
		case PSI_T_QUOTED_CHAR:
			free(exp->data.numb);
			break;
		case PSI_T_NAME:
			psi_decl_var_free(&exp->data.dvar);
			break;
		case PSI_T_SIZEOF:
			psi_decl_type_free(&exp->data.dtyp);
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
	case PSI_T_INT8:
		dprintf(fd, "%" PRId8, exp->data.ival.i8);
		break;
	case PSI_T_UINT8:
		dprintf(fd, "%" PRIu8, exp->data.ival.u8);
		break;
	case PSI_T_INT16:
		dprintf(fd, "%" PRId16, exp->data.ival.i16);
		break;
	case PSI_T_UINT16:
		dprintf(fd, "%" PRIu16, exp->data.ival.u16);
		break;
	case PSI_T_INT32:
		dprintf(fd, "%" PRId32, exp->data.ival.i32);
		break;
	case PSI_T_UINT32:
		dprintf(fd, "%" PRIu32, exp->data.ival.u32);
		break;
	case PSI_T_INT64:
		dprintf(fd, "%" PRId64, exp->data.ival.i64);
		break;
	case PSI_T_UINT64:
		dprintf(fd, "%" PRIu64, exp->data.ival.u64);
		break;
	case PSI_T_FLOAT:
		dprintf(fd, "%" PRIfval, exp->data.ival.dval);
		break;
	case PSI_T_DOUBLE:
		dprintf(fd, "%" PRIdval, exp->data.ival.dval);
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		dprintf(fd, "%" PRIldval, exp->data.ival.ldval);
		break;
#endif
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_DEFINE:
	case PSI_T_QUOTED_CHAR:
		dprintf(fd, "%s", exp->data.numb);
		break;
	case PSI_T_FUNCTION:
		psi_cpp_macro_call_dump(fd, exp->data.call);
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
	case PSI_T_SIZEOF:
		psi_decl_type_dump(fd, exp->data.dtyp, 0);
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

static inline token_t validate_char(char *numb, impl_val *res, unsigned *lvl)
{
	char *endptr;
	token_t typ = PSI_T_INT8;

	res->i8 = numb[0];
	endptr = &numb[1];

	switch(res->i8) {
	case '\\':
		res->i8 = numb[1];
		endptr = &numb[2];

		switch(res->i8) {
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7':
			res->i8 = strtol(&numb[1], &endptr, 8);
			break;

		case 'x':
			res->i8 = strtol(&numb[2], &endptr, 16);
			break;

		case 'a':
			res->i8 = '\a';
			break;
		case 'b':
			res->i8 = '\b';
			break;
		case 'f':
			res->i8 = '\f';
			break;
		case 'n':
			res->i8 = '\n';
			break;
		case 'r':
			res->i8 = '\r';
			break;
		case 't':
			res->i8 = '\t';
			break;
		case 'v':
			res->i8 = '\v';
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	/* more to grok? */
	if (*endptr) {
		impl_val tmp_val = {0};
		token_t tmp_typ = validate_char(endptr, &tmp_val, lvl);

		if (!tmp_typ) {
			return 0;
		}

		res->i32 = res->i8 << (8 * *lvl);
		typ = psi_calc_add(PSI_T_INT32, res, tmp_typ, &tmp_val, res);
	}

	++(*lvl);

	return typ;
}
static inline bool psi_number_validate_char(struct psi_data *data, struct psi_number *exp)
{
	impl_val val = {0};
	unsigned lvl = 1;
	token_t typ = validate_char(exp->data.numb, &val, &lvl);

	if (!typ) {
		return false;
	}

	free(exp->data.numb);
	exp->type = typ;
	exp->data.ival = val;
	return true;
}

static inline bool psi_number_validate_number(struct psi_data *data, struct psi_number *exp)
{
	impl_val tmp = {0};

	if (exp->flags) {
		switch (exp->flags & 0x0f) {
		case PSI_NUMBER_INT:
			switch (exp->flags & 0x0f00) {
			case PSI_NUMBER_L:
			default:
				tmp.i64 = strtol(exp->data.numb, NULL, 0);
				free(exp->data.numb);
				exp->type = PSI_T_INT64;
				exp->data.ival.i64 = tmp.i64;
				break;
			case PSI_NUMBER_LL:
				tmp.i64 = strtoll(exp->data.numb, NULL, 0);
				free(exp->data.numb);
				exp->type = PSI_T_INT64;
				exp->data.ival.i64 = tmp.i64;
				break;
			case PSI_NUMBER_U:
			case PSI_NUMBER_UL:
				tmp.u64 = strtoul(exp->data.numb, NULL, 0);
				free(exp->data.numb);
				exp->type = PSI_T_UINT64;
				exp->data.ival.u64 = tmp.u64;
				break;
			case PSI_NUMBER_ULL:
				tmp.u64 = strtoull(exp->data.numb, NULL, 0);
				free(exp->data.numb);
				exp->type = PSI_T_UINT64;
				exp->data.ival.u64 = tmp.u64;
				break;
			}
			return true;

		case PSI_NUMBER_FLT:
			switch (exp->flags & 0x0ff00) {
			case PSI_NUMBER_F:
			case PSI_NUMBER_DF:
				tmp.fval = strtof(exp->data.numb, NULL);
				free(exp->data.numb);
				exp->type = PSI_T_FLOAT;
				exp->data.ival.fval = tmp.fval;
				break;
			case PSI_NUMBER_L:
			case PSI_NUMBER_DL:
#if HAVE_LONG_DOUBLE
				tmp.ldval = strtold(exp->data.numb, NULL);
				free(exp->data.numb);
				exp->type = PSI_T_LONG_DOUBLE;
				exp->data.ival.ldval = tmp.ldval;
				break;
#endif
			case PSI_NUMBER_DD:
			default:
				tmp.dval = strtod(exp->data.numb, NULL);
				free(exp->data.numb);
				exp->type = PSI_T_DOUBLE;
				exp->data.ival.dval = tmp.dval;
				break;
			}
			return true;
		default:
			assert(0);
			break;
		}
	} else {
		switch (is_numeric_string(exp->data.numb, strlen(exp->data.numb), (zend_long *) &tmp, (double *) &tmp, 1)) {
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
	}
	data->error(data, exp->token, PSI_WARNING, "Expected numeric entity (parser error?)");
	return false;

}
bool psi_number_validate(struct psi_data *data, struct psi_number *exp,
		struct psi_impl *impl, struct psi_decl *cb_decl, struct psi_let_exp *current_let,
		struct psi_set_exp *current_set, struct psi_decl_enum *current_enum)
{
	size_t i = 0;
	struct psi_const *cnst;
	struct psi_decl_enum *enm;

	switch (exp->type) {
	case PSI_T_CONST:
	case PSI_T_INT8:
	case PSI_T_UINT8:
	case PSI_T_INT16:
	case PSI_T_UINT16:
	case PSI_T_INT32:
	case PSI_T_UINT32:
	case PSI_T_INT64:
	case PSI_T_UINT64:
	case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
#endif
	case PSI_T_ENUM:
	case PSI_T_DEFINE:
	case PSI_T_FUNCTION:
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

	case PSI_T_SIZEOF:
		if (psi_decl_type_validate(data, exp->data.dtyp, 0, NULL)) {
			struct psi_decl_type *dtyp = exp->data.dtyp;

			exp->type = PSI_T_UINT64;
			exp->data.ival.u64 = psi_decl_type_get_size(dtyp, NULL);
			return true;
		}
		break;

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
		return psi_number_validate_number(data, exp);

	case PSI_T_QUOTED_CHAR:
		return psi_number_validate_char(data, exp);

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

static inline token_t psi_number_eval_define(struct psi_number *exp,
		impl_val *res, HashTable *defs)
{
	struct psi_cpp_macro_decl *macro = zend_hash_str_find_ptr(defs, exp->data.numb, strlen(exp->data.numb));

	assert(!macro);

	res->u8 = 0;
	return PSI_T_UINT8;
}

token_t psi_number_eval(struct psi_number *exp, impl_val *res, struct psi_call_frame *frame, HashTable *defs)
{
	switch (exp->type) {
	case PSI_T_INT8:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi8, res->i8);
		return PSI_T_INT8;
	case PSI_T_UINT8:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIu8, res->u8);
		return PSI_T_UINT8;
	case PSI_T_INT16:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi16, res->i16);
		return PSI_T_INT16;
	case PSI_T_UINT16:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIu16, res->u16);
		return PSI_T_UINT16;
	case PSI_T_INT32:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi32, res->i32);
		return PSI_T_INT32;
	case PSI_T_UINT32:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIu32, res->u32);
		return PSI_T_UINT32;
	case PSI_T_INT64:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;
	case PSI_T_UINT64:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIu64, res->u64);
		return PSI_T_UINT64;

	case PSI_T_DOUBLE:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIdval, res->dval);
		return exp->type;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIldval, res->ldval);
		return exp->type;
#endif

	case PSI_T_ENUM:
		res->i64 = exp->data.enm->val;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;

	case PSI_T_NUMBER:
		res->i64 = atol(exp->data.numb);
		return PSI_T_INT64;

	case PSI_T_CONST:
		return psi_number_eval_constant(exp, res, frame);

	case PSI_T_NAME:
		return psi_number_eval_decl_var(exp, res, frame);

	case PSI_T_DEFINE:
		return psi_number_eval_define(exp, res, defs);

	case PSI_T_FUNCTION:
		res->u8 = 0;
		return PSI_T_UINT8;

	default:
		assert(0);
	}
	return 0;
}
