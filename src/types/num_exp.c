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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "calc.h"

num_exp *init_num_exp(token_t t, void *num) {
	num_exp *exp = calloc(1, sizeof(*exp));
	switch (exp->t = t) {
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		exp->u.numb = strdup(num);
		break;
	case PSI_T_NAME:
		exp->u.dvar = num;
		break;
	default:
		assert(0);
	}
	return exp;
}

num_exp *copy_num_exp(num_exp *exp) {
	decl_var *dvar;
	num_exp *num = calloc(1, sizeof(*num));
	memcpy(num, exp, sizeof(*num));
	if (num->token) {
		num->token = psi_token_copy(num->token);
	}
	if (num->operand) {
		num->operand = copy_num_exp(num->operand);
	}
	switch (num->t) {
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		num->u.numb = strdup(num->u.numb);
		break;
	case PSI_T_NAME:
		dvar = init_decl_var(num->u.dvar->name, num->u.dvar->pointer_level,
				num->u.dvar->array_size);
		dvar->arg = num->u.dvar->arg;
		if (num->u.dvar->token) {
			dvar->token = psi_token_copy(num->u.dvar->token);
		}
		num->u.dvar = dvar;
		break;
	default:
		assert(0);
	}
	return num;
}

void free_num_exp(num_exp *exp) {
	if (exp->token) {
		free(exp->token);
	}
	switch (exp->t) {
	case PSI_T_NUMBER:
		free(exp->u.numb);
		break;
	case PSI_T_NSNAME:
		break;
	case PSI_T_NAME:
		free_decl_var(exp->u.dvar);
		break;
	case PSI_T_ENUM:
		break;
	default:
		assert(0);
	}
	if (exp->operand) {
		free_num_exp(exp->operand);
	}
	free(exp);
}

void dump_num_exp(int fd, num_exp *exp) {
	while (exp) {
		switch (exp->t) {
		case PSI_T_NUMBER:
			dprintf(fd, "%s", exp->u.numb);
			break;
		case PSI_T_NSNAME:
			dprintf(fd, "%s", exp->u.cnst->name);
			break;
		case PSI_T_NAME:
			dump_decl_var(fd, exp->u.dvar);
			break;
		case PSI_T_ENUM:
			dprintf(fd, "%s", exp->u.enm->name);
			break;
		default:
			assert(0);
		}
		if (exp->operand) {
			char op;

			switch (exp->operator) {
			case PSI_T_PLUS:	op = '+'; break;
			case PSI_T_MINUS:	op = '-'; break;
			case PSI_T_ASTERISK:op = '*'; break;
			case PSI_T_SLASH:	op = '/'; break;
			default:
				assert(0);
			}
			dprintf(fd, " %c ", op);
		}
		exp = exp->operand;
	}
}

static inline constant *locate_num_exp_constant(num_exp *exp, constants *consts) {
	size_t i;

	for (i = 0; i < consts->count; ++i) {
		constant *cnst = consts->list[i];

		if (!strcmp(cnst->name, exp->u.numb)) {
			free(exp->u.numb);
			return exp->u.cnst = cnst;
		}
	}

	return NULL;
}
static inline decl_enum_item *locate_num_exp_enum_item_ex(num_exp *exp, decl_enum *e) {
	size_t k;

	if (e) for (k = 0; k < e->items->count; ++k) {
		decl_enum_item *i = e->items->list[k];

		if (!strcmp(i->name, exp->u.dvar->name)) {
			free_decl_var(exp->u.dvar);
			exp->t = PSI_T_ENUM;
			exp->u.enm = i;
			return i;
		}
	}
	return NULL;
}
static inline decl_enum_item *locate_num_exp_enum_item(num_exp *exp, decl_enums *enums) {
	size_t j;

	if (enums) for (j = 0; j < enums->count; ++j) {
		decl_enum *e = enums->list[j];
		decl_enum_item *i = locate_num_exp_enum_item_ex(exp, e);

		if (i) {
			return i;
		}
	}
	return NULL;
}

int validate_num_exp(struct psi_data *data, num_exp *exp, decl_args *dargs, decl_arg *func, decl_enum *enm) {
	if (exp->operand) {
		switch (exp->operator) {
		case PSI_T_PLUS:
			exp->calculator = psi_calc_add;
			break;
		case PSI_T_MINUS:
			exp->calculator = psi_calc_sub;
			break;
		case PSI_T_ASTERISK:
			exp->calculator = psi_calc_mul;
			break;
		case PSI_T_SLASH:
			exp->calculator = psi_calc_div;
			break;
		default:
			assert(0);
		}
		if (!validate_num_exp(data, exp->operand, dargs, func, enm)) {
			return 0;
		}
	}
	switch (exp->t) {
	case PSI_T_NAME:
		if (!locate_decl_var_arg(exp->u.dvar, dargs, func)) {
			if (!locate_num_exp_enum_item(exp, data->enums) && !locate_num_exp_enum_item_ex(exp, enm)) {
				data->error(data, exp->token, PSI_WARNING, "Unknown variable '%s' in numeric expression",
						exp->u.dvar->name);
				return 0;
			}
		}
		return 1;
	case PSI_T_NSNAME:
		if (!locate_num_exp_constant(exp, data->consts)) {
			data->error(data, exp->token, PSI_WARNING, "Unknown constant '%s' in numeric expression",
					exp->u.numb);
			return 0;
		}
		return 1;
	case PSI_T_NUMBER:
	case PSI_T_ENUM:
		return 1;
	default:
		return 0;
	}
}
