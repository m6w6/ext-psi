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

struct psi_impl_def_val *psi_impl_def_val_init(token_t t, const char *text)
{
	struct psi_impl_def_val *def = calloc(1, sizeof(*def));

	def->type = t;
	def->text = strdup(text);

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
		case PSI_T_STRING:
			assert(0);
			/* no break */
		case PSI_T_QUOTED_STRING:
			if (def->ival.zend.str) {
				zend_string_release(def->ival.zend.str);
			}
			break;
		}
		free(def->text);
		free(def);
	}
}

bool psi_impl_def_val_validate(struct psi_data *data,
		struct psi_impl_def_val *def, token_t type_t, const char *type_name)
{
	if (def->type != PSI_T_NULL && def->text) {
		switch (type_t) {
		case PSI_T_BOOL:
			def->ival.zend.bval = def->type == PSI_T_TRUE ? 1 : 0;
			break;
		case PSI_T_INT:
			def->ival.zend.lval = zend_atol(def->text, strlen(def->text));
			break;
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
			def->ival.dval = zend_strtod(def->text, NULL);
			break;
		case PSI_T_STRING:
			/* used for consts */
			/* no break */
		case PSI_T_QUOTED_STRING:
			def->ival.zend.str = zend_string_init(&def->text[1], strlen(def->text) - 2, 1);
			break;
		default:
			data->error(data, def->token, PSI_WARNING,
					"Invalid default value type '%s', expected one of bool, int, double, string.",
					type_name);
			return false;
		}
	}
	return true;
}

void psi_impl_def_val_dump(int fd, struct psi_impl_def_val *val) {
	switch (val->type) {
	case PSI_T_STRING:
		assert(0);
		/* no break */
	case PSI_T_QUOTED_STRING:
		dprintf(fd, "\"%s\"", val->text);
		break;
	default:
		dprintf(fd, "%s", val->text);
	}
}
