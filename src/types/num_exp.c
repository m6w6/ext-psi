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
#include "context.h"
#include "call.h"
#include "calc.h"


struct psi_num_exp *psi_num_exp_init_binary(token_t op,
		struct psi_num_exp *lhs, struct psi_num_exp *rhs)
{
	struct psi_num_exp *exp = calloc(1, sizeof(*exp));

	exp->op = op;
	exp->data.b.lhs = lhs;
	exp->data.b.rhs = rhs;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_unary(token_t op,
		struct psi_num_exp *u)
{
	struct psi_num_exp *exp = calloc(1, sizeof(*exp));

	exp->op = op;
	exp->data.u = u;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_num(struct psi_number *n)
{
	struct psi_num_exp *exp = calloc(1, sizeof(*exp));

	exp->data.n = n;

	return exp;
}

struct psi_num_exp *psi_num_exp_copy(struct psi_num_exp *exp)
{
	struct psi_num_exp *cpy;

	if (!exp) {
		return NULL;
	}

	cpy = malloc(sizeof(*cpy));
	*cpy = *exp;

	switch (exp->op) {
	case 0:
		cpy->data.n = psi_number_copy(exp->data.n);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
	case PSI_T_LPAREN:
		cpy->data.u = psi_num_exp_copy(exp->data.u);
		break;

	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_PLUS:
	case PSI_T_MINUS:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:
	case PSI_T_MODULO:
		cpy->data.b.lhs = psi_num_exp_copy(exp->data.b.lhs);
		cpy->data.b.rhs = psi_num_exp_copy(exp->data.b.rhs);
		break;

	default:
		assert(0);
	}

	if (exp->token) {
		cpy->token = psi_token_copy(exp->token);
	}

	return cpy;
}

void psi_num_exp_free(struct psi_num_exp **c_ptr)
{
	if (*c_ptr) {
		struct psi_num_exp *c = *c_ptr;

		*c_ptr = NULL;

		switch (c->op) {
		case 0:
			psi_number_free(&c->data.n);
			break;
		case PSI_T_NOT:
		case PSI_T_TILDE:
		case PSI_T_LPAREN:
			psi_num_exp_free(&c->data.u);
			break;

		case PSI_T_PIPE:
		case PSI_T_CARET:
		case PSI_T_AMPERSAND:
		case PSI_T_LSHIFT:
		case PSI_T_RSHIFT:
		case PSI_T_PLUS:
		case PSI_T_MINUS:
		case PSI_T_ASTERISK:
		case PSI_T_SLASH:
		case PSI_T_MODULO:
			psi_num_exp_free(&c->data.b.lhs);
			psi_num_exp_free(&c->data.b.rhs);
			break;

		default:
			assert(0);
		}

		if (c->token) {
			free(c->token);
		}

		free(c);
	}
}

static inline wint_t psi_num_exp_op_tok(token_t op)
{
	switch (op) {
	case PSI_T_NOT:
		return L'!';
	case PSI_T_TILDE:
		return L'~';
	case PSI_T_LPAREN:
		return L'(';

	case PSI_T_PIPE:
		return L'|';
	case PSI_T_CARET:
		return L'^';
	case PSI_T_AMPERSAND:
		return L'&';

	case PSI_T_LSHIFT:
		return L'«';
	case PSI_T_RSHIFT:
		return L'»';

	case PSI_T_PLUS:
		return L'+';
	case PSI_T_MINUS:
		return L'-';

	case PSI_T_ASTERISK:
		return L'*';
	case PSI_T_SLASH:
		return L'/';
	case PSI_T_MODULO:
		return L'%';

	default:
		assert(0);
	}
	return 0;
}

void psi_num_exp_dump(int fd, struct psi_num_exp *exp)
{
	switch (exp->op) {
	case 0:
		psi_number_dump(fd, exp->data.n);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
		dprintf(fd, "%lc", psi_num_exp_op_tok(exp->op));
		psi_num_exp_dump(fd, exp->data.u);
		break;

	case PSI_T_LPAREN:
		dprintf(fd, "(");
		psi_num_exp_dump(fd, exp->data.u);
		dprintf(fd, ")");
		break;

	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_PLUS:
	case PSI_T_MINUS:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:
		psi_num_exp_dump(fd, exp->data.b.lhs);
		dprintf(fd, " %lc ", psi_num_exp_op_tok(exp->op));
		psi_num_exp_dump(fd, exp->data.b.rhs);
		break;

	default:
		assert(0);
	}

}

bool psi_num_exp_validate(struct psi_data *data, struct psi_num_exp *exp,
		struct psi_impl *impl, struct psi_decl *cb_decl, struct psi_let_exp *current_let,
		struct psi_set_exp *current_set, struct psi_decl_enum *current_enum)
{
	if (exp->op) {
		switch (exp->op) {
		case PSI_T_NOT:
			exp->calc = psi_calc_not;
			break;
		case PSI_T_TILDE:
			exp->calc = psi_calc_bin_not;
			break;

		case PSI_T_LPAREN:
			break;

		case PSI_T_PIPE:
			exp->calc = psi_calc_bin_or;
			break;
		case PSI_T_CARET:
			exp->calc = psi_calc_bin_xor;
			break;
		case PSI_T_AMPERSAND:
			exp->calc = psi_calc_bin_and;
			break;
		case PSI_T_LSHIFT:
			exp->calc = psi_calc_bin_lshift;
			break;
		case PSI_T_RSHIFT:
			exp->calc = psi_calc_bin_rshift;
			break;
		case PSI_T_PLUS:
			exp->calc = psi_calc_add;
			break;
		case PSI_T_MINUS:
			exp->calc = psi_calc_sub;
			break;
		case PSI_T_ASTERISK:
			exp->calc = psi_calc_mul;
			break;
		case PSI_T_SLASH:
			exp->calc = psi_calc_div;
			break;
		case PSI_T_MODULO:
			exp->calc = psi_calc_mod;
			break;
		default:
			data->error(data, exp->token, PSI_WARNING,
					"Unknown numeric operator (%d)", exp->op);
			return false;
		}
	}

	switch (exp->op) {
	case 0:
		return psi_number_validate(data, exp->data.n, impl, cb_decl, current_let, current_set, current_enum);

	case PSI_T_NOT:
	case PSI_T_TILDE:
	case PSI_T_LPAREN:
		return psi_num_exp_validate(data, exp->data.u, impl, cb_decl, current_let, current_set, current_enum);
		break;

	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_PLUS:
	case PSI_T_MINUS:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:
	case PSI_T_MODULO:
		return psi_num_exp_validate(data, exp->data.b.lhs, impl, cb_decl, current_let, current_set, current_enum)
				&& psi_num_exp_validate(data, exp->data.b.rhs, impl, cb_decl, current_let, current_set, current_enum);
	default:
		assert(0);
	}

	return false;
}

static inline void psi_impl_val_dump(token_t t, impl_val *res,
		struct psi_call_frame *frame)
{
	switch (t) {
	case PSI_T_INT8:
	case PSI_T_UINT8:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi8, res->i8);
		break;
	case PSI_T_INT16:
	case PSI_T_UINT16:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi16, res->i16);
		break;
	case PSI_T_INT32:
	case PSI_T_UINT32:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi32, res->i32);
		break;
	case PSI_T_INT64:
	case PSI_T_UINT64:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIi64, res->i64);
		break;
	case PSI_T_FLOAT:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIfval, res->fval);
		break;
	case PSI_T_DOUBLE:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIdval, res->dval);
		break;
	default:
		assert(0);
	}
}
static inline void psi_num_exp_verify_result(token_t t, impl_val *res, struct psi_call_frame *frame)
{
	if (frame) PSI_DEBUG_PRINT(frame->context, "%s", " = ");
	psi_impl_val_dump(t, res, frame);
	if (frame) PSI_DEBUG_PRINT(frame->context, "%s", "\n");
}

static void psi_num_exp_reduce(struct psi_num_exp *exp, struct psi_plist **output_ptr,
		struct psi_plist **input_ptr, struct psi_call_frame *frame)
{
	struct psi_plist *output = *output_ptr, *input = *input_ptr;
	struct element {
		token_t type;
		union {
			impl_val value;
			psi_calc calc;
		} data;
	} entry;

	switch (exp->op) {
	case 0:
		entry.type = psi_number_eval(exp->data.n, &entry.data.value, frame);
		output = psi_plist_add(output, &entry);
		break;

	case PSI_T_LPAREN:
		entry.type = exp->op;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.u, &output, &input, frame);
		while (psi_plist_pop(input, &entry)) {
			if (entry.type == PSI_T_LPAREN) {
				break;
			}
			if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
		while (psi_plist_top(input, &entry)) {
			/* bail out if exp->op >= entry.type */
			if (psi_num_exp_op_cmp(exp->op, entry.type) != 1) {
				break;
			}
			psi_plist_pop(input, NULL);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		entry.type = exp->op;
		entry.data.calc = exp->calc;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.u, &output, &input, frame);
		break;

	default:
		psi_num_exp_reduce(exp->data.b.lhs, &output, &input, frame);
		while (psi_plist_top(input, &entry)) {
			/* bail out if exp->op > entry.type */
			if (psi_num_exp_op_cmp(exp->op, entry.type) == -1) {
				break;
			}
			psi_plist_pop(input, NULL);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		entry.type = exp->op;
		entry.data.calc = exp->calc;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.b.rhs, &output, &input, frame);
		break;
	}

	*output_ptr = output;
	*input_ptr = input;
}

token_t psi_num_exp_exec(struct psi_num_exp *exp, impl_val *res,
		struct psi_call_frame *frame)
{
	struct psi_plist *output, *input;
	struct element {
		token_t type;
		union {
			impl_val value;
			psi_calc calc;
		} data;
	} entry, lhs, rhs;

	output = psi_plist_init_ex(sizeof(entry), NULL);
	input = psi_plist_init_ex(sizeof(entry), NULL);

	psi_num_exp_reduce(exp, &output, &input, frame);

	while (psi_plist_pop(input, &entry)) {
		if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
		output = psi_plist_add(output, &entry);
	}
	if (frame) PSI_DEBUG_PRINT(frame->context, "%s", "\n");

	while (psi_plist_shift(output, &entry)) {
		switch (entry.type) {
		default:
			input = psi_plist_add(input, &entry);
			break;

		case PSI_T_NOT:
		case PSI_T_TILDE:
			psi_plist_pop(input, &rhs);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
			psi_impl_val_dump(rhs.type, &rhs.data.value, frame);

			entry.type = entry.data.calc(rhs.type, &rhs.data.value, 0, NULL, &entry.data.value);
			input = psi_plist_add(input, &entry);
			psi_num_exp_verify_result(entry.type, &entry.data.value, frame);
			break;

		case PSI_T_PIPE:
		case PSI_T_CARET:
		case PSI_T_AMPERSAND:
		case PSI_T_LSHIFT:
		case PSI_T_RSHIFT:
		case PSI_T_MINUS:
		case PSI_T_PLUS:
		case PSI_T_ASTERISK:
		case PSI_T_SLASH:
		case PSI_T_MODULO:
			psi_plist_pop(input, &rhs);
			psi_plist_pop(input, &lhs);

			psi_impl_val_dump(lhs.type, &lhs.data.value, frame);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %lc", psi_num_exp_op_tok(entry.type));
			psi_impl_val_dump(rhs.type, &rhs.data.value, frame);

			entry.type = entry.data.calc(
					lhs.type, &lhs.data.value,
					rhs.type, &rhs.data.value,
					&entry.data.value);
			input = psi_plist_add(input, &entry);
			psi_num_exp_verify_result(entry.type, &entry.data.value, frame);
			break;
		}

		if (!psi_plist_count(output)) {
			break;
		}
	}

	*res = entry.data.value;
	return entry.type;
}

