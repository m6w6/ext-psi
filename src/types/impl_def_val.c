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

#include <assert.h>
#include <math.h>

#define PSI_IMPL_DEF_VAL_DEBUG 0

struct psi_impl_def_val *psi_impl_def_val_init(token_t t, void *data)
{
	struct psi_impl_def_val *def = pecalloc(1, sizeof(*def), 1);

	switch ((def->type = t)) {
	case PSI_T_TRUE:
	case PSI_T_FALSE:
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

bool psi_impl_def_val_validate(struct psi_data *data,
		struct psi_impl_def_val *val, struct psi_impl_type *type,
		struct psi_validate_scope *scope)
{
	if (val->type == PSI_T_NULL) {
		return true;
	} else if (val->type == PSI_T_NUMBER) {
		if (!psi_num_exp_validate(data, val->data.num, scope)) {
			return false;
		}
	}

	switch (type ? type->type : PSI_T_MIXED) {
	case PSI_T_BOOL:
		val->ival.zend.bval = val->type == PSI_T_TRUE ? 1 : 0;
		return true;
		break;

	/* macros */
	case PSI_T_NUMBER:
		if (val->type == PSI_T_NUMBER) {
			token_t typ = psi_num_exp_exec(val->data.num, &val->ival, NULL, scope->cpp);

			switch (typ) {
			case PSI_T_FLOAT:
				val->ival.dval = val->ival.fval;
				/* no break */
			case PSI_T_DOUBLE:
				val->type = PSI_T_FLOAT;
				type->type = PSI_T_FLOAT;
				zend_string_release(type->name);
				type->name = zend_string_init_interned(ZEND_STRL("float"), 1);
				break;
			case PSI_T_UINT64:
				if (val->ival.u64 > ZEND_LONG_MAX) {
					data->error(data, val->token, PSI_WARNING,
							"Integer too big for signed representation: '%" PRIu64 "'",
							val->ival.u64);
				}
			default:
				/* FIXME big integers */
				val->type = PSI_T_INT;
				type->type = PSI_T_INT;
				zend_string_release(type->name);
				type->name = zend_string_init_interned(ZEND_STRL("int"), 1);
				break;
			}
			psi_num_exp_free(&val->data.num);
			return true;
		}
		break;

	case PSI_T_INT:
		if (val->type == PSI_T_NUMBER) {
			val->type = PSI_T_INT;
			val->ival.zend.lval = psi_num_exp_get_long(val->data.num, NULL, scope->cpp);
#if PSI_IMPL_DEF_VAL_DEBUG
			PSI_DEBUG_PRINT(data, "PSI: NUMBER (long) %" PRIi64 " from ", val->ival.zend.lval);
			PSI_DEBUG_DUMP(data, psi_num_exp_dump, val->data.num);
			PSI_DEBUG_PRINT(data, "\n");
#endif
			psi_num_exp_free(&val->data.num);
		}
		if (val->type == PSI_T_INT) {
			return true;
		}
		break;

	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		if (val->type == PSI_T_NUMBER) {
			val->type = PSI_T_DOUBLE;
			val->ival.dval = psi_num_exp_get_double(val->data.num, NULL, scope->cpp);
#if PSI_IMPL_DEF_VAL_DEBUG
			PSI_DEBUG_PRINT(data, "PSI: NUMBER (double) %" PRIdval " from ", val->ival.dval);
			PSI_DEBUG_DUMP(data, psi_num_exp_dump, val->data.num);
			PSI_DEBUG_PRINT(data, "\n");
#endif
			psi_num_exp_free(&val->data.num);
		}
		if (val->type == PSI_T_DOUBLE) {
			return true;
		}
		break;

	case PSI_T_STRING:
		if (val->type == PSI_T_STRING) {
			return true;
		}
		break;

	case PSI_T_MIXED:
		switch (val->type) {
		case PSI_T_TRUE:
		case PSI_T_FALSE:
		case PSI_T_NULL:
		case PSI_T_STRING:
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
		case PSI_T_INT:
			return true;
		default:
			break;
		}
		if (val->type == PSI_T_NUMBER) {
			token_t typ = psi_num_exp_exec(val->data.num, &val->ival, NULL, scope->cpp);

			switch (typ) {
			case PSI_T_FLOAT:
#if HAVE_LONG_DOUBLE
			case PSI_T_LONG_DOUBLE:
#endif
			promote_double: ;
				psi_calc_cast(typ, &val->ival, PSI_T_DOUBLE, &val->ival);
				/* no break */
			case PSI_T_DOUBLE:
				val->type = PSI_T_DOUBLE;
				return true;
			case PSI_T_UINT64:
				if (val->ival.u64 > (uint64_t) ZEND_LONG_MAX) {
					if (val->ival.u64 > (1LU<<53)) {
						char buf[0x20];

						/* convert to string */
						char *res = zend_print_ulong_to_buf(buf + sizeof(buf) - 1, val->ival.u64);
						val->type = PSI_T_STRING;
						val->ival.zend.str = zend_string_init(res, buf + sizeof(buf) - 1 - res, 1);

						return true;
					}
					goto promote_double;
				}
				/* no break */
			default:
				psi_calc_cast(typ, &val->ival, PSI_T_INT64, &val->ival);
				/* no break */
			case PSI_T_INT64:
				val->type = PSI_T_INT;
				return true;
			}
		}
		/* no break */
	default:
		data->error(data, val->token, PSI_WARNING,
				"Invalid default value type '%s', "
				"expected one of bool, int, float, string.",
				type ? type->name->val : "mixed");
	}

	return false;
}

void psi_impl_def_val_dump(int fd, struct psi_impl_def_val *val) {
	switch (val->type) {
	case PSI_T_NULL:
		dprintf(fd, "NULL");
		break;
	case PSI_T_TRUE:
		dprintf(fd, "true");
		break;
	case PSI_T_FALSE:
		dprintf(fd, "false");
		break;
	case PSI_T_BOOL:
		dprintf(fd, "%s", val->ival.zend.bval ? "true" : "false");
		break;
	case PSI_T_INT:
		dprintf(fd, ZEND_LONG_FMT, val->ival.zend.lval);
		break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		if (isinf(val->ival.dval)) {
			dprintf(fd, "\\INF");
		} else if (isnan(val->ival.dval)) {
			dprintf(fd, "\\NAN");
		} else {
			dprintf(fd, "%" PRIdval, val->ival.dval);
		}
		break;
	case PSI_T_STRING:
		dprintf(fd, "\"%s\"", val->ival.zend.str->val);
		break;
	case PSI_T_NUMBER:
		psi_num_exp_dump(fd, val->data.num);
		break;
	default:
		assert(0);
	}
}
