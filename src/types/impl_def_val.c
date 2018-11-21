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

#include "zend_smart_str.h"

#include <assert.h>
#include <math.h>

#define PSI_IMPL_DEF_VAL_DEBUG 0

struct psi_impl_def_val *psi_impl_def_val_init(token_t t, void *data)
{
	struct psi_impl_def_val *def = pecalloc(1, sizeof(*def), 1);

	switch ((def->type = t)) {
	case PSI_T_TRUE:
		def->ival.zend.bval = 1;
		/* no break */
	case PSI_T_FALSE:
		def->ityp = PSI_T_UINT8;
		/* no break */
	case PSI_T_NULL:
		break;
	case PSI_T_QUOTED_STRING:
		/* immediate upgrade */
		def->type = PSI_T_STRING;
		/* no break */
	case PSI_T_STRING:
		if (data) {
			def->ival.zend.str = zend_string_copy(data);
		}
		break;

	case PSI_T_NUMBER:
		def->data.num = data;
		break;

	default:
		assert(0);
	}

	return def;
}

void psi_impl_def_val_free(struct psi_impl_def_val **def_ptr)
{
	if (*def_ptr) {
		struct psi_impl_def_val *def = *def_ptr;

		*def_ptr = NULL;
		psi_token_free(&def->token);
		switch (def->type) {
		case PSI_T_NUMBER:
			psi_num_exp_free(&def->data.num);
			break;

		case PSI_T_STRING:
			if (def->ival.zend.str) {
				zend_string_release(def->ival.zend.str);
			}
			break;
		default:
			break;
		}
		free(def);
	}
}

void psi_impl_def_val_get_zval(struct psi_impl_def_val *val, token_t typ, zval *zv)
{
	impl_val tmp = val->ival;

	/* c->val has already been forced to the type of the containing constant or impl_arg */
	switch (typ) {
	case PSI_T_BOOL:
		ZVAL_BOOL(zv, tmp.zend.bval);
		break;
	case PSI_T_INT:
		ZVAL_LONG(zv, tmp.zend.lval);
		break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
	is_double: ;
		ZVAL_DOUBLE(zv, tmp.dval);
		break;
	case PSI_T_STRING:
	is_string: ;
		ZVAL_NEW_STR(zv, zend_string_copy(tmp.zend.str));
		if (ZSTR_IS_INTERNED(Z_STR_P(zv))) {
			Z_TYPE_FLAGS_P(zv) = 0;
		}
		break;
	case PSI_T_MIXED:
		switch (val->type) {
		case PSI_T_NULL:
			ZVAL_NULL(zv);
			break;
		case PSI_T_TRUE:
			ZVAL_TRUE(zv);
			break;
		case PSI_T_FALSE:
			ZVAL_FALSE(zv);
			break;
		case PSI_T_STRING:
			goto is_string;
			break;
		case PSI_T_NUMBER:
			switch (val->ityp) {
			case PSI_T_INT8:
			case PSI_T_UINT8:
			case PSI_T_INT16:
			case PSI_T_UINT16:
			case PSI_T_INT32:
			case PSI_T_UINT32:
				psi_calc_cast(val->ityp, &tmp, PSI_T_INT64, &tmp);
				/* no break */
			case PSI_T_INT64:
				ZVAL_LONG(zv, tmp.i64);
				break;
			case PSI_T_UINT64:
				ZVAL_LONG_DOUBLE_STR(zv, tmp.u64, is_signed=false;persistent=true);
				break;
#if HAVE_INT128
			case PSI_T_INT128:
				ZVAL_LONG_DOUBLE_STR(zv, tmp.i128, is_signed=true;persistent=true);
				break;
			case PSI_T_UINT128:
				ZVAL_LONG_DOUBLE_STR(zv, tmp.u128, is_signed=false;persistent=true);
#endif
				break;
			case PSI_T_FLOAT:
				ZVAL_DOUBLE(zv, tmp.fval);
				break;
			case PSI_T_DOUBLE:
				goto is_double;
				break;
#if HAVE_LONG_DOUBLE
			case PSI_T_LONG_DOUBLE:
				ZVAL_DOUBLE(zv, tmp.ldval);
				break;
#endif
			default:
				assert(0);
			}
			break;
		default:
			assert(0);
			break;
		}
		break;
	default:
		assert(0);
		break;
	}

}

static inline bool psi_impl_def_val_validate_impl_type(struct psi_data *data,
		struct psi_impl_def_val *val, struct psi_impl_type *type,
		struct psi_validate_scope *scope)
{
	switch (type->type) {
	case PSI_T_BOOL:
		switch (val->type) {
		case PSI_T_TRUE:
		case PSI_T_FALSE:
			return true;
		case PSI_T_STRING:
			if (val->ival.zend.str) {
				zend_string *tmp = val->ival.zend.str;

				val->ival.zend.bval = (*tmp->val && *tmp->val != '0');
				zend_string_release(tmp);
			}
			val->ityp = PSI_T_UINT8;
			val->type = PSI_T_BOOL;
			return true;
		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT:
		if (val->type == PSI_T_STRING) {
			zend_string *str = val->ival.zend.str;
			switch (is_numeric_str_function(str, &val->ival.zend.lval, &val->ival.dval)) {
			case IS_DOUBLE:
				val->ival.zend.lval = zend_dval_to_lval_cap(val->ival.dval);
				/* no break */
			case IS_LONG:
				break;
			default:
				val->ival.zend.lval = 0;
			}
			zend_string_release(str);
			val->ityp = PSI_T_INT64;
			return true;
		}
		psi_calc_cast(val->ityp, &val->ival, PSI_T_INT64, &val->ival);
		val->type = PSI_T_INT;
		val->ityp = PSI_T_INT64;
		return true;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		if (val->type == PSI_T_STRING) {
			zend_string *str = val->ival.zend.str;
			switch (is_numeric_str_function(str, &val->ival.zend.lval, &val->ival.dval)) {
			case IS_LONG:
				val->ival.dval = val->ival.zend.lval;
				/* no break */
			case IS_DOUBLE:
				break;
			default:
				val->ival.dval = 0;
			}
			zend_string_release(str);
			val->type = val->ityp = PSI_T_DOUBLE;
			return true;
		}
		psi_calc_cast(val->ityp, &val->ival, PSI_T_DOUBLE, &val->ival);
		val->ityp = PSI_T_DOUBLE;
		return true;
	case PSI_T_STRING:
		if (val->type == PSI_T_STRING) {
			return true;
		} else {
			smart_str str = {0};
			struct psi_dump dump = {{.hn = &str},
					.fun = (psi_dump_cb) smart_str_append_printf};

			switch (val->ityp) {
			CASE_IMPLVAL_NUM_DUMP(&dump, val->ival, false);
			default:
				assert(0);
			}
			val->ival.zend.str = smart_str_extract(&str);
			val->type = PSI_T_STRING;
			return true;
		}
		break;
	default:
		data->error(data, val->token, PSI_WARNING,
				"Invalid default value type '%s', "
				"expected one of bool, int, float/double or string.",
				type->name->val);

	}
	return false;
}

bool psi_impl_def_val_validate(struct psi_data *data,
		struct psi_impl_def_val *val, struct psi_impl_type *type,
		struct psi_validate_scope *scope)
{
	/* NULL can be anything */
	if (val->type == PSI_T_NULL) {
		return true;
	}

	/* a number can be anything */
	if (val->type == PSI_T_NUMBER) {
		if (!psi_num_exp_validate(data, val->data.num, scope)) {
			return false;
		}
		val->ityp = psi_num_exp_exec(val->data.num, &val->ival, NULL, scope->cpp);
	}

	/* forced type, like `const <type> foo`, or function param `<type> $xyz` */
	if (type) {
		return psi_impl_def_val_validate_impl_type(data, val, type, scope);
	}

	switch (val->type) {
	case PSI_T_NUMBER:
	case PSI_T_NULL:
	case PSI_T_TRUE:
	case PSI_T_FALSE:
	case PSI_T_STRING:
		return true;
	default:
		assert(0);
		break;
	}

	return false;
}

void psi_impl_def_val_dump(struct psi_dump *dump, struct psi_impl_def_val *val) {
	switch (val->type) {
	case PSI_T_NULL:
		PSI_DUMP(dump, "NULL");
		break;
	case PSI_T_TRUE:
		PSI_DUMP(dump, "true");
		break;
	case PSI_T_FALSE:
		PSI_DUMP(dump, "false");
		break;
	case PSI_T_BOOL:
		PSI_DUMP(dump, "%s", val->ival.zend.bval ? "true" : "false");
		break;
	case PSI_T_INT:
		PSI_DUMP(dump, ZEND_LONG_FMT, val->ival.zend.lval);
		break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		if (isinf(val->ival.dval)) {
			PSI_DUMP(dump, "\\INF");
		} else if (isnan(val->ival.dval)) {
			PSI_DUMP(dump, "\\NAN");
		} else {
			PSI_DUMP(dump, "%" PRIdval, val->ival.dval);
		}
		break;
	case PSI_T_STRING:
		PSI_DUMP(dump, "\"%s\"", val->ival.zend.str->val);
		break;
	case PSI_T_NUMBER:
		psi_num_exp_dump(dump, val->data.num);
		break;
	default:
		assert(0);
	}
#if 0
	PSI_DUMP(dump, "\t/* impl_def_val.type=%d */ ", val->type);
#endif
}
