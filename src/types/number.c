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
#include <math.h>

#include "data.h"
#include "calc.h"
#include "call.h"
#include "parser.h"

#include "Zend/zend_constants.h"
#include "Zend/zend_operators.h"


struct psi_number *psi_number_init(token_t t, void *num, unsigned flags)
{
	struct psi_number *exp = pecalloc(1, sizeof(*exp), 1);

	exp->flags = flags;
	switch (exp->type = t) {
	case PSI_T_INT8:
		exp->data.ival.i8 = *(int8_t *) num;
		break;
	case PSI_T_DEFINED:
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
		exp->data.ival.fval = *(float *) num;
		break;
	case PSI_T_DOUBLE:
		exp->data.ival.dval = *(double *) num;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		exp->data.ival.ldval = *(long double *) num;
		break;
#endif
	case PSI_T_NULL:
		break;
	case PSI_T_QUOTED_CHAR:
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_DEFINE:
	case PSI_T_CPP_HEADER:
		exp->data.numb = zend_string_copy(num);
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
	struct psi_number *num = pecalloc(1, sizeof(*num), 1);

	*num = *exp;

	if (num->token) {
		num->token = psi_token_copy(num->token);
	}
	switch (num->type) {
	case PSI_T_INT8:
	case PSI_T_DEFINED:
	case PSI_T_UINT8:
	case PSI_T_INT16:
	case PSI_T_UINT16:
	case PSI_T_INT32:
	case PSI_T_UINT32:
	case PSI_T_INT64:
	case PSI_T_UINT64:
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
#endif
	case PSI_T_ENUM:
	case PSI_T_CONST:
	case PSI_T_NULL:
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_DEFINE:
	case PSI_T_QUOTED_CHAR:
	case PSI_T_CPP_HEADER:
		num->data.numb = zend_string_copy(num->data.numb);
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
		psi_token_free(&exp->token);
		switch (exp->type) {
		case PSI_T_INT8:
		case PSI_T_DEFINED:
		case PSI_T_UINT8:
		case PSI_T_INT16:
		case PSI_T_UINT16:
		case PSI_T_INT32:
		case PSI_T_UINT32:
		case PSI_T_INT64:
		case PSI_T_UINT64:
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
#endif
		case PSI_T_ENUM:
		case PSI_T_CONST:
		case PSI_T_NULL:
			break;
		case PSI_T_FUNCTION:
			psi_cpp_macro_call_free(&exp->data.call);
			break;
		case PSI_T_NSNAME:
		case PSI_T_NUMBER:
		case PSI_T_DEFINE:
		case PSI_T_QUOTED_CHAR:
		case PSI_T_CPP_HEADER:
			zend_string_release(exp->data.numb);
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

struct psi_plist *psi_number_tokens(struct psi_number *exp,
		struct psi_plist *list)
{
	struct psi_token *ntoken;
	size_t i;

	if (!list) {
		list = psi_plist_init((psi_plist_dtor) psi_token_free);
	}

	switch (exp->type) {
	case PSI_T_NAME:
		/* decl_var */
		ntoken = psi_token_copy(exp->data.dvar->token);

		if (exp->data.dvar->pointer_level > 1 || !exp->data.dvar->array_size) {
			struct psi_token *temp = ntoken;
			unsigned pl = exp->data.dvar->pointer_level - !!exp->data.dvar->array_size;

			while (pl--) {
				ntoken = psi_token_init(PSI_T_POINTER, "*", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
				list = psi_plist_add(list, &ntoken);
			}
			ntoken = temp;
		}

		list = psi_plist_add(list, &ntoken);

		if (exp->data.dvar->array_size) {
			char buf[0x20], *ptr;

			ntoken = psi_token_init(PSI_T_LBRACKET, "[", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
			list = psi_plist_add(list, &ntoken);
			ptr = zend_print_ulong_to_buf(&buf[sizeof(buf) - 1], exp->data.dvar->array_size);

			ntoken = psi_token_init(PSI_T_NUMBER, ptr, strlen(ptr), ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
			list = psi_plist_add(list, &ntoken);
		}
		break;

	case PSI_T_SIZEOF:
		/* decl_type */
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_init(PSI_T_LPAREN, "(", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_copy(exp->data.dtyp->token);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_init(PSI_T_RPAREN, ")", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		break;

	case PSI_T_FUNCTION:
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_init(PSI_T_LPAREN, "(", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		for (i = 0; i < psi_plist_count(exp->data.call->args); ++i) {
			struct psi_num_exp *tmp_exp;

			if (i) {
				ntoken = psi_token_init(PSI_T_COMMA, ",", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
				list = psi_plist_add(list, &ntoken);
			}
			if (psi_plist_get(exp->data.call->args, i, &tmp_exp)) {
				struct psi_plist *tmp = psi_num_exp_tokens(tmp_exp, NULL);
				list = psi_plist_add_r(list, psi_plist_count(tmp), psi_plist_eles(tmp));
				psi_plist_top(list, &ntoken);
				free(tmp);
			}
		}
		ntoken = psi_token_init(PSI_T_RPAREN, ")", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		break;

	case PSI_T_DEFINED:
		ntoken = psi_token_init(PSI_T_DEFINED, "defined", sizeof("defined")-1, exp->token->col, exp->token->line, exp->token->file);
		list = psi_plist_add(list, &ntoken);
		/* no break */
	default:
		assert(exp->token);
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		break;
	}

	return list;
}

void psi_number_dump(struct psi_dump *dump, struct psi_number *exp)
{
	switch (exp->type) {
	case PSI_T_DEFINED:
	CASE_IMPLVAL_NUM_DUMP(dump, exp->data.ival, true);
	case PSI_T_NULL:
		PSI_DUMP(dump, "NULL");
		break;
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
	case PSI_T_QUOTED_CHAR:
	case PSI_T_CPP_HEADER:
		PSI_DUMP(dump, "%s", exp->data.numb->val);
		break;
	case PSI_T_DEFINE:
		PSI_DUMP(dump, "%s /* DEFINE */", exp->data.numb->val);
		break;
	case PSI_T_FUNCTION:
		psi_cpp_macro_call_dump(dump, exp->data.call);
		break;
	case PSI_T_CONST:
		PSI_DUMP(dump, "%s", exp->data.cnst->name->val);
		break;
	case PSI_T_ENUM:
		PSI_DUMP(dump, "%s /* ENUM */ ", exp->data.enm->name->val);
		break;
	case PSI_T_NAME:
		psi_decl_var_dump(dump, exp->data.dvar);
		break;
	case PSI_T_SIZEOF:
		PSI_DUMP(dump, "sizeof(");
		psi_decl_type_dump(dump, exp->data.dtyp, 0);
		PSI_DUMP(dump, ")");
		break;
	default:
		assert(0);
	}
#if 0
	PSI_DUMP(dump, "\t/* number.type=%d */ ", exp->type);
#endif
}

static inline bool psi_number_validate_enum(struct psi_data *data,
		struct psi_number *exp, struct psi_validate_scope *scope)
{
	if (scope && scope->current_enum) {
		size_t i = 0;
		struct psi_decl_enum_item *itm;
		struct psi_decl_enum *enm;

		enm = scope->current_enum;

		switch (exp->type) {
		case PSI_T_NAME:
			while (psi_plist_get(enm->items, i++, &itm)) {
				if (zend_string_equals(itm->name, exp->data.dvar->name)) {
					psi_decl_var_free(&exp->data.dvar);
					exp->type = PSI_T_ENUM;
					exp->data.enm = itm;
					return psi_number_validate(data, exp, scope);
				}
			}
			break;

		case PSI_T_DEFINE:
			while (psi_plist_get(enm->items, i++, &itm)) {
				if (zend_string_equals(itm->name, exp->data.numb)) {
					zend_string_release(exp->data.numb);
					exp->type = PSI_T_ENUM;
					exp->data.enm = itm;
					return psi_number_validate(data, exp, scope);
				}
			}
			break;

		default:
			assert(0);
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
	token_t typ = validate_char(exp->data.numb->val, &val, &lvl);

	if (!typ) {
		return false;
	}

	zend_string_release(exp->data.numb);
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
				tmp.i64 = strtol(exp->data.numb->val, NULL, 0);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_INT64;
				exp->data.ival.i64 = tmp.i64;
				break;
			case PSI_NUMBER_LL:
				tmp.i64 = strtoll(exp->data.numb->val, NULL, 0);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_INT64;
				exp->data.ival.i64 = tmp.i64;
				break;
			case PSI_NUMBER_U:
			case PSI_NUMBER_UL:
				tmp.u64 = strtoul(exp->data.numb->val, NULL, 0);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_UINT64;
				exp->data.ival.u64 = tmp.u64;
				break;
			case PSI_NUMBER_ULL:
				tmp.u64 = strtoull(exp->data.numb->val, NULL, 0);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_UINT64;
				exp->data.ival.u64 = tmp.u64;
				break;
			}
			return true;

		case PSI_NUMBER_FLT:
			switch (exp->flags & 0x0ff00) {
			case PSI_NUMBER_F:
				tmp.fval = strtof(exp->data.numb->val, NULL);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_FLOAT;
				exp->data.ival.fval = tmp.fval;
				break;
			case PSI_NUMBER_L:
			case PSI_NUMBER_DL:
#if HAVE_LONG_DOUBLE
				tmp.ldval = strtold(exp->data.numb->val, NULL);
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_LONG_DOUBLE;
				exp->data.ival.ldval = tmp.ldval;
				break;
#endif
			case PSI_NUMBER_DD:
			default:
			case PSI_NUMBER_DF:
				tmp.dval = strtod(exp->data.numb->val, NULL);
				zend_string_release(exp->data.numb);
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
		int type = is_numeric_string(exp->data.numb->val, exp->data.numb->len, (zend_long *) &tmp, (double *)&tmp, 0);
		char *stop = NULL;
		long lval;
		unsigned long ulval;

		switch (type) {
		case IS_LONG:
			zend_string_release(exp->data.numb);
			exp->type = PSI_T_INT64;
			exp->data.ival.i64 = tmp.zend.lval;
			return true;

		case IS_DOUBLE:
			zend_string_release(exp->data.numb);
			exp->type = PSI_T_DOUBLE;
			exp->data.ival.dval = tmp.dval;
			return true;

		default:

			errno = 0;

			stop = exp->data.numb->val + exp->data.numb->len;
			lval = strtol(exp->data.numb->val, &stop, 0);
			switch (lval) {
			case 0:
				assert(stop == exp->data.numb->val + exp->data.numb->len);
				/* no break */
			case LONG_MIN:
				assert(!errno);
				/* no break */
			case LONG_MAX:
				if (errno == ERANGE) {
					errno = 0;

					stop = exp->data.numb->val + exp->data.numb->len;
					ulval = strtoul(exp->data.numb->val, &stop, 0);
					switch (ulval) {
					case 0:
						assert(stop == exp->data.numb->val + exp->data.numb->len);
					case ULONG_MAX:
						assert(!errno);
					default:
						zend_string_release(exp->data.numb);
						exp->type = PSI_T_UINT64;
						exp->data.ival.u64 = ulval;
						return true;
					}
				}
				break;
			default:
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_INT64;
				exp->data.ival.i64 = lval;
				return true;
			}

			data->error(data, exp->token, PSI_WARNING, "Not a numeric string: '%s'", exp->data.numb->val);
		}
	}
	data->error(data, exp->token, PSI_WARNING, "Expected numeric entity (parser error?)");
	return false;

}
bool psi_number_validate(struct psi_data *data, struct psi_number *exp,
		struct psi_validate_scope *scope)
{
	size_t i = 0;
	struct psi_const *cnst;
	struct psi_decl_enum *enm;

	switch (exp->type) {
	case PSI_T_NULL:
		exp->type = PSI_T_UINT8;
		/* no break */
	case PSI_T_CONST:
	case PSI_T_INT8:
	case PSI_T_UINT8:
	case PSI_T_INT16:
	case PSI_T_UINT16:
	case PSI_T_INT32:
	case PSI_T_UINT32:
	case PSI_T_INT64:
	case PSI_T_UINT64:
#if HAVE_INT128
	case PSI_T_INT128:
	case PSI_T_UINT128:
#endif
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
#endif
	case PSI_T_ENUM:
	case PSI_T_DEFINED:
		return true;

	case PSI_T_NAME:
		//if (scope && scope->cpp && zend_hash_exists(&scope->cpp->defs, exp->data.dvar->name)) {
		//	exp->type = PSI_T_DEFINE;
		//	goto define;
		//}
		if (scope && scope->current_enum && psi_number_validate_enum(data, exp, scope)) {
			return true;
		}
		while (psi_plist_get(data->enums, i++, &enm)) {
			struct psi_validate_scope enum_scope = *scope;
			enum_scope.current_enum = enm;
			if (psi_number_validate_enum(data, exp, &enum_scope)) {
				return true;
			}
		}
		if (exp->data.dvar->arg) {
			return true;
		}
		if (psi_decl_var_validate(data, exp->data.dvar, scope)) {
			return true;
		}
		data->error(data, exp->token, PSI_WARNING,
				"Unknown variable '%s' in numeric expression",
				exp->data.dvar->name->val);
		return false;

	case PSI_T_FUNCTION:
		if (scope && scope->cpp && zend_hash_exists(&scope->cpp->defs, exp->data.call->name)) {
			size_t i, argc;
			struct psi_cpp_macro_call *call = exp->data.call;

			for (i = 0, argc = psi_plist_count(call->args); i < argc; ++i) {
				struct psi_num_exp *arg;

				if (!psi_plist_get(call->args, i, &arg)) {
					return false;
				}
				if (!psi_num_exp_validate(data, arg, scope)) {
					return false;
				}
			}
			return true;
		}
		if (psi_builtin_exists(exp->data.call->name)) {
			exp->data.call->builtin = psi_builtin_get(exp->data.call->name);
			return true;
		}
		return false;

	case PSI_T_DEFINE:
		if (scope && scope->cpp && zend_hash_exists(&scope->cpp->defs, exp->data.numb)) {
	define: ;
			if (!scope->macro || !zend_string_equals(scope->macro->token->text, exp->data.numb)) {
				return true;
			}
			/* #define foo foo */
		}
		while (psi_plist_get(data->enums, i++, &enm)) {
			struct psi_validate_scope enum_scope = *scope;
			enum_scope.current_enum = enm;
			if (psi_number_validate_enum(data, exp, &enum_scope)) {
				return true;
			}
		}
		return false;

	case PSI_T_SIZEOF:
		if (psi_decl_type_validate(data, exp->data.dtyp, NULL, scope)) {
			struct psi_decl_type *dtyp = exp->data.dtyp;

			exp->type = PSI_T_UINT64;
			exp->data.ival.u64 = psi_decl_type_get_size(dtyp, NULL);
			psi_decl_type_free(&dtyp);
			return true;
		} else {
			struct psi_decl_type *dtyp = exp->data.dtyp;

			data->error(data, exp->token, PSI_WARNING,
					"Cannot compute sizeof(%s) (%u)", dtyp->name->val, dtyp->type);

			exp->type = PSI_T_UINT8;
			exp->data.ival.u8 = 0;
			psi_decl_type_free(&dtyp);
		}
		break;

	case PSI_T_NSNAME:
		{
			zval *zc;

			if (exp->data.numb->val[0] == '\\') {
				zc = zend_get_constant_str(&exp->data.numb->val[1], exp->data.numb->len - 1);
			} else {
				zc = zend_get_constant(exp->data.numb);
			}

			if (zc) {
				switch (Z_TYPE_P(zc)) {
				case IS_LONG:
					zend_string_release(exp->data.numb);
					exp->type = PSI_T_INT64;
					exp->data.ival.i64 = Z_LVAL_P(zc);
					return true;

				case IS_DOUBLE:
					zend_string_release(exp->data.numb);
					exp->type = PSI_T_DOUBLE;
					exp->data.ival.dval = Z_DVAL_P(zc);
					return true;

				default:
					assert(0);
				}
			}
		}
		while (psi_plist_get(data->consts, i++, &cnst)) {
			if (zend_string_equals(cnst->name, exp->data.numb)) {
				zend_string_release(exp->data.numb);
				exp->type = PSI_T_CONST;
				exp->data.cnst = cnst;
				return true;
			}
		}
		data->error(data, exp->token, PSI_WARNING,
				"Unknown constant '%s' in numeric expression",
				exp->data.numb->val);
		return false;

	case PSI_T_NUMBER:
		return psi_number_validate_number(data, exp);

	case PSI_T_QUOTED_CHAR:
		return psi_number_validate_char(data, exp);

	case PSI_T_CPP_HEADER:
		return true;

	default:
		assert(0);
	}

	return false;
}

static inline token_t psi_number_eval_constant(struct psi_number *exp,
		impl_val *res, struct psi_call_frame *frame)
{
	token_t typ = exp->data.cnst->type ? exp->data.cnst->type->type : PSI_T_MIXED;

	switch (typ) {
	case PSI_T_INT:
		res->i64 = zend_get_constant(exp->data.cnst->name)->value.lval;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		return PSI_T_INT64;
	case PSI_T_FLOAT:
		res->dval = zend_get_constant(exp->data.cnst->name)->value.dval;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIdval, res->dval);
		return PSI_T_DOUBLE;
	default:
		if (frame) PSI_DEBUG_PRINT(frame->context, " ?(t=%u)", exp->data.cnst->type->type);
		return 0;
	}
}


static inline token_t psi_number_eval_decl_var(struct psi_number *exp,
		impl_val *res, struct psi_call_frame *frame)
{
	impl_val *ref;
	struct psi_call_frame_symbol *sym;
	struct psi_decl_type *real;
	struct psi_decl_var *var;
	size_t size;

	var = exp->data.dvar;
	real = psi_decl_type_get_real(var->arg->type);
	size = psi_decl_arg_get_size(var->arg);
	sym = psi_call_frame_fetch_symbol(frame, var);
	ref = deref_impl_val(sym->ptr, var);

	memcpy(res, ref, size);

	if (var->arg->var->pointer_level > var->pointer_level) {
		switch (SIZEOF_VOID_P) {
		case 4:
			return PSI_T_INT32;
		case 8:
			return PSI_T_INT64;
		default:
			assert(0);
		}
	}
	return real->type;
}

static inline token_t psi_number_eval_define(struct psi_number *exp,
		impl_val *res, struct psi_cpp *cpp, struct psi_num_exp *rec_guard)
{
	if (cpp) {
		struct psi_cpp_macro_decl *macro;

		macro = zend_hash_find_ptr(&cpp->defs, exp->data.numb);
		if (macro && macro->exp && macro->exp != rec_guard) {
			return psi_num_exp_exec(macro->exp, res, NULL, cpp);
		}
	}

	res->u8 = 0;
	return PSI_T_UINT8;
}

static inline token_t psi_number_eval_function(struct psi_number *exp,
		impl_val *res, struct psi_cpp *cpp, struct psi_num_exp *rec_guard)
{
	if (cpp) {
		PSI_DEBUG_PRINT(cpp->parser, "psi_number_eval(PSI_T_FUNCTION): %s\n", exp->token->text->val);
	}
	res->u8 = 0;
	return PSI_T_UINT8;
}

token_t psi_number_eval(struct psi_number *exp, impl_val *res,
		struct psi_call_frame *frame, struct psi_cpp *cpp, struct psi_num_exp *rec_guard)
{
	switch (exp->type) {
	case PSI_T_INT8:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi8, res->i8);
		return PSI_T_INT8;
	case PSI_T_DEFINED:
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
#if HAVE_INT128
	case PSI_T_INT128:
		*res = exp->data.ival;
		//if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi128, res->i128);
		return PSI_T_INT128;
	case PSI_T_UINT128:
		*res = exp->data.ival;
		//if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIu128, res->u128);
		return PSI_T_UINT128;
#endif
	case PSI_T_FLOAT:
		*res = exp->data.ival;
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIfval, res->fval);
		return exp->type;

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
		res->i64 = atol(exp->data.numb->val);
		return PSI_T_INT64;

	case PSI_T_CONST:
		return psi_number_eval_constant(exp, res, frame);

	case PSI_T_NAME:
		return psi_number_eval_decl_var(exp, res, frame);

	case PSI_T_DEFINE:
		return psi_number_eval_define(exp, res, cpp, rec_guard);

	case PSI_T_FUNCTION:
		return psi_number_eval_function(exp, res, cpp, rec_guard);

	case PSI_T_CPP_HEADER:
		res->u8 = 0;
		return PSI_T_UINT8;

	default:
		assert(0);
	}
	return 0;
}
