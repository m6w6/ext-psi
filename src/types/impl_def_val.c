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

struct psi_impl_def_val *psi_impl_def_val_init(token_t t, void *data)
{
	struct psi_impl_def_val *def = calloc(1, sizeof(*def));

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
			def->ival.zend.str = zend_string_init(data, strlen(data), 1);
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
		if (def->token) {
			free(def->token);
		}
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

	switch (type->type) {
	case PSI_T_BOOL:
		val->ival.zend.bval = val->type == PSI_T_TRUE ? 1 : 0;
		break;

	/* macros */
	case PSI_T_NUMBER:
		if (val->type == PSI_T_NUMBER) {
			token_t typ = psi_num_exp_exec(val->data.num, &val->ival, NULL, scope->defs);

			switch (typ) {
			case PSI_T_FLOAT:
				val->ival.dval = val->ival.fval;
				/* no break */
			case PSI_T_DOUBLE:
				val->type = PSI_T_FLOAT;
				type->type = PSI_T_FLOAT;
				strcpy(type->name, "float");
				break;
			default:
				val->type = PSI_T_INT;
				type->type = PSI_T_INT;
				strcpy(type->name, "int");
				break;
			}
			psi_num_exp_free(&val->data.num);
			return true;
		}
		break;

	case PSI_T_INT:
		if (val->type == PSI_T_NUMBER) {
			val->type = PSI_T_INT;
			val->ival.zend.lval = psi_num_exp_get_long(val->data.num, NULL, scope->defs);
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
			val->ival.dval = psi_num_exp_get_double(val->data.num, NULL, scope->defs);
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

	default:
		data->error(data, val->token, PSI_WARNING,
				"Invalid default value type '%s', "
				"expected one of bool, int, float, string.",
				type->name);
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
		dprintf(fd, "%ld", val->ival.zend.lval);
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
	default:
		assert(0);
	}
}
