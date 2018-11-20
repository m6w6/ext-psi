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

struct psi_num_exp *psi_num_exp_init_ternary(token_t op,
		struct psi_num_exp *cond, struct psi_num_exp *truthy,
		struct psi_num_exp *falsy)
{
	struct psi_num_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->op = op;
	exp->data.t.cond = cond;
	exp->data.t.truthy = truthy;
	exp->data.t.falsy = falsy;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_binary(token_t op,
		struct psi_num_exp *lhs, struct psi_num_exp *rhs)
{
	struct psi_num_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->op = op;
	exp->data.b.lhs = lhs;
	exp->data.b.rhs = rhs;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_unary(token_t op,
		struct psi_num_exp *u)
{
	struct psi_num_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->op = op;
	exp->data.u = u;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_num(struct psi_number *n)
{
	struct psi_num_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->op = PSI_T_NUMBER;
	exp->data.n = n;

	return exp;
}

struct psi_num_exp *psi_num_exp_init_cast(struct psi_decl_type *typ,
		struct psi_num_exp *num)
{
	struct psi_num_exp *exp = pecalloc(1, sizeof(*exp), 1);

	exp->op = PSI_T_CAST;
	exp->data.c.typ = typ;
	exp->data.c.num = num;

	return exp;
}

struct psi_num_exp *psi_num_exp_copy(struct psi_num_exp *exp)
{
	struct psi_num_exp *cpy;

	if (!exp) {
		return NULL;
	}

	cpy = pemalloc(sizeof(*cpy), 1);
	*cpy = *exp;

	switch (exp->op) {
	case PSI_T_NUMBER:
		cpy->data.n = psi_number_copy(exp->data.n);
		break;

	case PSI_T_CAST:
		cpy->data.c.typ = psi_decl_type_copy(exp->data.c.typ);
		cpy->data.c.num = psi_num_exp_copy(exp->data.c.num);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
	case PSI_T_LPAREN:
		cpy->data.u = psi_num_exp_copy(exp->data.u);
		break;

	case PSI_T_OR:
	case PSI_T_AND:

	case PSI_T_CMP_EQ:
	case PSI_T_CMP_NE:
	case PSI_T_CMP_LE:
	case PSI_T_CMP_GE:
	case PSI_T_RCHEVR:
	case PSI_T_LCHEVR:

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

	case PSI_T_IIF:
		cpy->data.t.cond = psi_num_exp_copy(exp->data.t.cond);
		cpy->data.t.truthy = psi_num_exp_copy(exp->data.t.truthy);
		cpy->data.t.falsy = psi_num_exp_copy(exp->data.t.falsy);
		break;

	default:
		assert(0);
	}

	if (exp->token) {
		cpy->token = psi_token_copy(exp->token);
	}

	return cpy;
}

void psi_num_exp_copy_ctor(struct psi_num_exp **exp_ptr)
{
	*exp_ptr = psi_num_exp_copy(*exp_ptr);
}

void psi_num_exp_free(struct psi_num_exp **c_ptr)
{
	if (*c_ptr) {
		struct psi_num_exp *c = *c_ptr;

		*c_ptr = NULL;

		switch (c->op) {
		case PSI_T_NUMBER:
			psi_number_free(&c->data.n);
			break;

		case PSI_T_CAST:
			psi_decl_type_free(&c->data.c.typ);
			psi_num_exp_free(&c->data.c.num);
			break;

		case PSI_T_NOT:
		case PSI_T_TILDE:
		case PSI_T_LPAREN:
			psi_num_exp_free(&c->data.u);
			break;

		case PSI_T_OR:
		case PSI_T_AND:

		case PSI_T_CMP_EQ:
		case PSI_T_CMP_NE:
		case PSI_T_CMP_LE:
		case PSI_T_CMP_GE:
		case PSI_T_RCHEVR:
		case PSI_T_LCHEVR:

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

		case PSI_T_IIF:
			psi_num_exp_free(&c->data.t.cond);
			psi_num_exp_free(&c->data.t.truthy);
			psi_num_exp_free(&c->data.t.falsy);
			break;

		default:
			assert(0);
		}

		psi_token_free(&c->token);

		free(c);
	}
}

static inline const char *psi_num_exp_op_tok(token_t op)
{
	switch (op) {
	case PSI_T_NOT:
		return "!";
	case PSI_T_TILDE:
		return "~";
	case PSI_T_LPAREN:
		return "(";
	case PSI_T_CAST:
		return "(cast)";

	case PSI_T_PIPE:
		return "|";
	case PSI_T_CARET:
		return "^";
	case PSI_T_AMPERSAND:
		return "&";

	case PSI_T_LSHIFT:
		return "<<";
	case PSI_T_RSHIFT:
		return ">>";

	case PSI_T_PLUS:
		return "+";
	case PSI_T_MINUS:
		return "-";

	case PSI_T_ASTERISK:
		return "*";
	case PSI_T_SLASH:
		return "/";
	case PSI_T_MODULO:
		return "%";

	case PSI_T_OR:
		return "||";
	case PSI_T_AND:
		return "&&";

	case PSI_T_CMP_EQ:
		return "==";
	case PSI_T_CMP_NE:
		return "!=";
	case PSI_T_CMP_LE:
		return "<=";
	case PSI_T_CMP_GE:
		return ">=";
	case PSI_T_RCHEVR:
		return ">";
	case PSI_T_LCHEVR:
		return "<";

	case PSI_T_IIF:
		return "?";

	default:
		assert(0);
	}
	return 0;
}

struct psi_plist *psi_num_exp_tokens(struct psi_num_exp *exp,
		struct psi_plist *list)
{
	struct psi_token *ntoken;

	if (!list) {
		list = psi_plist_init((psi_plist_dtor) psi_token_free);
	}

	switch (exp->op) {
	case PSI_T_NUMBER:
		list = psi_number_tokens(exp->data.n, list);
		break;

	case PSI_T_CAST:
		ntoken = exp->data.c.typ->token;
		ntoken = psi_token_init(PSI_T_LPAREN, "(", 1, ntoken->col-1, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_copy(exp->data.c.typ->token);
		list = psi_plist_add(list, &ntoken);
		ntoken = psi_token_init(PSI_T_RPAREN, ")", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
	unary:
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		list = psi_num_exp_tokens(exp->data.u, list);
		break;

	case PSI_T_LPAREN:
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		list = psi_num_exp_tokens(exp->data.u, list);
		psi_plist_top(list, &ntoken);
		ntoken = psi_token_init(PSI_T_RPAREN, ")", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		break;

	case PSI_T_PLUS:
	case PSI_T_MINUS:
		if (!exp->data.b.rhs) {
			goto unary;
		}
		/* no break */
	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:

	case PSI_T_OR:
	case PSI_T_AND:

	case PSI_T_CMP_EQ:
	case PSI_T_CMP_NE:
	case PSI_T_CMP_LE:
	case PSI_T_CMP_GE:
	case PSI_T_RCHEVR:
	case PSI_T_LCHEVR:

		list = psi_num_exp_tokens(exp->data.b.lhs, list);
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		list = psi_num_exp_tokens(exp->data.b.rhs, list);
		break;

	case PSI_T_IIF:
		list = psi_num_exp_tokens(exp->data.t.cond, list);
		ntoken = psi_token_copy(exp->token);
		list = psi_plist_add(list, &ntoken);
		list = psi_num_exp_tokens(exp->data.t.truthy, list);
		psi_plist_top(list, &ntoken);
		ntoken = psi_token_init(PSI_T_COLON, ":", 1, ntoken->col+ntoken->text->len, ntoken->line, ntoken->file);
		list = psi_plist_add(list, &ntoken);
		list = psi_plist_add(list, &ntoken);
		list = psi_num_exp_tokens(exp->data.t.falsy, list);
		break;

	default:
		assert(0);
	}

	return list;
}

void psi_num_exp_dump(struct psi_dump *dump, struct psi_num_exp *exp)
{
	switch (exp->op) {
	case PSI_T_NUMBER:
		psi_number_dump(dump, exp->data.n);
		break;

	case PSI_T_CAST:
		PSI_DUMP(dump, "(");
		psi_decl_type_dump(dump, exp->data.c.typ, 0);
		PSI_DUMP(dump, ")");
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
	unary:
		PSI_DUMP(dump, "%s", psi_num_exp_op_tok(exp->op));
		psi_num_exp_dump(dump, exp->data.u);
		break;

	case PSI_T_LPAREN:
		PSI_DUMP(dump, "(");
		psi_num_exp_dump(dump, exp->data.u);
		PSI_DUMP(dump, ")");
		break;

	case PSI_T_PLUS:
	case PSI_T_MINUS:
		if (!exp->data.b.rhs) {
			goto unary;
		}
		/* no break */
	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:

	case PSI_T_OR:
	case PSI_T_AND:

	case PSI_T_CMP_EQ:
	case PSI_T_CMP_NE:
	case PSI_T_CMP_LE:
	case PSI_T_CMP_GE:
	case PSI_T_RCHEVR:
	case PSI_T_LCHEVR:
		psi_num_exp_dump(dump, exp->data.b.lhs);
		PSI_DUMP(dump, " %s ", psi_num_exp_op_tok(exp->op));
		psi_num_exp_dump(dump, exp->data.b.rhs);
		break;

	case PSI_T_IIF:
		psi_num_exp_dump(dump, exp->data.t.cond);
		PSI_DUMP(dump, " ? ");
		psi_num_exp_dump(dump, exp->data.t.truthy);
		PSI_DUMP(dump, " : ");
		psi_num_exp_dump(dump, exp->data.t.falsy);
		break;

	default:
		assert(0);
	}

}

bool psi_num_exp_validate(struct psi_data *data, struct psi_num_exp *exp,
		struct psi_validate_scope *scope)
{
	if (exp->op && exp->op != PSI_T_NUMBER) {
		switch (exp->op) {
		case PSI_T_NOT:
			exp->calc = psi_calc_bool_not;
			break;
		case PSI_T_TILDE:
			exp->calc = psi_calc_bin_not;
			break;

		case PSI_T_OR:
			exp->calc = psi_calc_bool_or;
			break;
		case PSI_T_AND:
			exp->calc = psi_calc_bool_and;
			break;
		case PSI_T_CMP_EQ:
			exp->calc = psi_calc_cmp_eq;
			break;
		case PSI_T_CMP_NE:
			exp->calc = psi_calc_cmp_ne;
			break;
		case PSI_T_CMP_LE:
			exp->calc = psi_calc_cmp_le;
			break;
		case PSI_T_CMP_GE:
			exp->calc = psi_calc_cmp_ge;
			break;
		case PSI_T_LCHEVR:
			exp->calc = psi_calc_cmp_lt;
			break;
		case PSI_T_RCHEVR:
			exp->calc = psi_calc_cmp_gt;
			break;

		case PSI_T_CAST:
		case PSI_T_LPAREN:
		case PSI_T_IIF:
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
			if (exp->data.b.rhs) {
				exp->calc = psi_calc_add;
			}
			break;
		case PSI_T_MINUS:
			if (exp->data.b.rhs) {
				exp->calc = psi_calc_sub;
			} else {
				exp->calc = psi_calc_minus;
			}
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
	case PSI_T_NUMBER:
		return psi_number_validate(data, exp->data.n, scope);

	case PSI_T_CAST:
		return psi_num_exp_validate(data, exp->data.c.num, scope)
				&& psi_decl_type_validate(data, exp->data.c.typ, NULL, scope);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
	case PSI_T_LPAREN:
	unary:
		return psi_num_exp_validate(data, exp->data.u, scope);
		break;

	case PSI_T_PLUS:
	case PSI_T_MINUS:
		if (!exp->data.b.rhs) {
			goto unary;
		}
		/* no break */
	case PSI_T_PIPE:
	case PSI_T_CARET:
	case PSI_T_AMPERSAND:
	case PSI_T_LSHIFT:
	case PSI_T_RSHIFT:
	case PSI_T_ASTERISK:
	case PSI_T_SLASH:
	case PSI_T_MODULO:

	case PSI_T_OR:
	case PSI_T_AND:

	case PSI_T_CMP_EQ:
	case PSI_T_CMP_NE:
	case PSI_T_CMP_LE:
	case PSI_T_CMP_GE:
	case PSI_T_RCHEVR:
	case PSI_T_LCHEVR:
		return psi_num_exp_validate(data, exp->data.b.lhs, scope)
				&& psi_num_exp_validate(data, exp->data.b.rhs, scope);

	case PSI_T_IIF:
		return psi_num_exp_validate(data, exp->data.t.cond, scope)
				&& psi_num_exp_validate(data, exp->data.t.truthy, scope)
				&& psi_num_exp_validate(data, exp->data.t.falsy, scope);

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
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		if (frame) PSI_DEBUG_PRINT(frame->context, " %" PRIldval, res->ldval);
		break;
#endif
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
		struct psi_plist **input_ptr, struct psi_call_frame *frame, struct psi_cpp *cpp)
{
	struct psi_plist *output = *output_ptr, *input = *input_ptr;
	struct element {
		token_t type;
		union {
			impl_val value;
			psi_calc calc;
			struct psi_decl_type *cast;
		} data;
	} entry;

	switch (exp->op) {
	case PSI_T_NUMBER:
		entry.type = psi_number_eval(exp->data.n, &entry.data.value, frame, cpp, exp);
		output = psi_plist_add(output, &entry);
		break;

	case PSI_T_LPAREN:
		entry.type = exp->op;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.u, &output, &input, frame, cpp);
		while (psi_plist_pop(input, &entry)) {
			if (entry.type == PSI_T_LPAREN) {
				break;
			}
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		break;

	case PSI_T_CAST:
		while (psi_plist_top(input, &entry)) {
			/* bail out if exp->op >= entry.type */
			if (psi_calc_oper(exp->op, entry.type) != 1) {
				break;
			}
			psi_plist_pop(input, NULL);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		entry.type = exp->op;
		entry.data.cast = exp->data.c.typ;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.c.num, &output, &input, frame, cpp);
		break;

	case PSI_T_NOT:
	case PSI_T_TILDE:
		while (psi_plist_top(input, &entry)) {
			/* bail out if exp->op >= entry.type */
			if (psi_calc_oper(exp->op, entry.type) != 1) {
				break;
			}
			psi_plist_pop(input, NULL);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		entry.type = exp->op;
		entry.data.calc = exp->calc;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.u, &output, &input, frame, cpp);
		break;

	case PSI_T_IIF:
		{
			impl_val cond_val = {0};
			token_t cond_typ = psi_num_exp_exec(exp->data.t.cond, &cond_val, frame, cpp);

			psi_calc_bool_not(cond_typ, &cond_val, 0, NULL, &cond_val);
			if (cond_val.u8) {
				psi_num_exp_reduce(exp->data.t.falsy, &output, &input, frame, cpp);
			} else {
				psi_num_exp_reduce(exp->data.t.truthy, &output, &input, frame, cpp);
			}
		}
		break;

	case PSI_T_MINUS:
	case PSI_T_PLUS:
		/* unary */
		if (!exp->data.b.rhs) {
			entry.type = psi_num_exp_exec(exp->data.b.lhs, &entry.data.value, frame, cpp);

			if (exp->calc) {
				entry.type = exp->calc(entry.type, &entry.data.value, 0, NULL, &entry.data.value);
			}
			output = psi_plist_add(output, &entry);
			break;
		}
		/* no break */
	default:
		psi_num_exp_reduce(exp->data.b.lhs, &output, &input, frame, cpp);
		while (psi_plist_top(input, &entry)) {
			/* bail out if exp->op > entry.type */
			if (psi_calc_oper(exp->op, entry.type) == -1) {
				break;
			}
			psi_plist_pop(input, NULL);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			output = psi_plist_add(output, &entry);
		}
		entry.type = exp->op;
		entry.data.calc = exp->calc;
		input = psi_plist_add(input, &entry);
		psi_num_exp_reduce(exp->data.b.rhs, &output, &input, frame, cpp);
		break;
	}

	*output_ptr = output;
	*input_ptr = input;
}

token_t psi_num_exp_exec(struct psi_num_exp *exp, impl_val *res,
		struct psi_call_frame *frame, struct psi_cpp *cpp)
{
	struct psi_plist *output, *input;
	struct element {
		token_t type;
		union {
			impl_val value;
			psi_calc calc;
			struct psi_decl_type *cast;
		} data;
	} entry, lhs, rhs;

	output = psi_plist_init_ex(sizeof(entry), NULL);
	input = psi_plist_init_ex(sizeof(entry), NULL);

	psi_num_exp_reduce(exp, &output, &input, frame, cpp);

	while (psi_plist_pop(input, &entry)) {
		if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
		output = psi_plist_add(output, &entry);
	}
	if (frame) PSI_DEBUG_PRINT(frame->context, "%s", "\n");

	while (psi_plist_shift(output, &entry)) {
		switch (entry.type) {
		default:
			input = psi_plist_add(input, &entry);
			break;

		case PSI_T_CAST:
			psi_plist_pop(input, &rhs);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			psi_impl_val_dump(rhs.type, &rhs.data.value, frame);

			entry.type = psi_decl_type_get_real(entry.data.cast)->type;
			psi_calc_cast(rhs.type, &rhs.data.value, entry.type, &entry.data.value);
			input = psi_plist_add(input, &entry);
			psi_num_exp_verify_result(entry.type, &entry.data.value, frame);
			break;

		case PSI_T_NOT:
		case PSI_T_TILDE:
			psi_plist_pop(input, &rhs);
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
			psi_impl_val_dump(rhs.type, &rhs.data.value, frame);

			entry.type = entry.data.calc(rhs.type, &rhs.data.value, 0, NULL, &entry.data.value);
			input = psi_plist_add(input, &entry);
			psi_num_exp_verify_result(entry.type, &entry.data.value, frame);
			break;

		case PSI_T_OR:
		case PSI_T_AND:

		case PSI_T_CMP_EQ:
		case PSI_T_CMP_NE:
		case PSI_T_CMP_LE:
		case PSI_T_CMP_GE:
		case PSI_T_RCHEVR:
		case PSI_T_LCHEVR:

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
			if (frame) PSI_DEBUG_PRINT(frame->context, " %s", psi_num_exp_op_tok(entry.type));
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

	psi_plist_free(output);
	psi_plist_free(input);

	*res = entry.data.value;
	return entry.type;
}

