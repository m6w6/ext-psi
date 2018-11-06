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

#ifndef PSI_TYPES_NUM_EXP_H
#define PSI_TYPES_NUM_EXP_H

#include "token.h"
#include "Zend/zend_types.h"

struct psi_data;
struct psi_token;
struct psi_impl;
struct psi_const;
struct psi_decl_enum_item;
struct psi_let_exp;
struct psi_set_exp;
struct psi_call_frame;
struct psi_validate_scope;

struct psi_num_exp {
	struct psi_token *token;
	token_t op;
	union {
		struct {
			struct psi_num_exp *lhs;
			struct psi_num_exp *rhs;
		} b;
		struct {
			struct psi_decl_type *typ;
			struct psi_num_exp *num;
		} c;
		struct {
			struct psi_num_exp *cond;
			struct psi_num_exp *truthy;
			struct psi_num_exp *falsy;
		} t;
		struct psi_num_exp *u;
		struct psi_number *n;
	} data;
	token_t (*calc)(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
};

struct psi_num_exp *psi_num_exp_init_ternary(token_t op,
		struct psi_num_exp *cond, struct psi_num_exp *truthy,
		struct psi_num_exp *falsy);
struct psi_num_exp *psi_num_exp_init_binary(token_t op,
		struct psi_num_exp *lhs, struct psi_num_exp *rhs);
struct psi_num_exp *psi_num_exp_init_unary(token_t op,
		struct psi_num_exp *u);
struct psi_num_exp *psi_num_exp_init_num(struct psi_number *n);
struct psi_num_exp *psi_num_exp_init_cast(struct psi_decl_type *typ,
		struct psi_num_exp *num);
void psi_num_exp_free(struct psi_num_exp **c_ptr);

struct psi_num_exp *psi_num_exp_copy(struct psi_num_exp *exp);
void psi_num_exp_copy_ctor(struct psi_num_exp **exp_ptr);

void psi_num_exp_dump(int fd, struct psi_num_exp *exp);
bool psi_num_exp_validate(struct psi_data *data, struct psi_num_exp *exp,
		struct psi_validate_scope *scope);

token_t psi_num_exp_exec(struct psi_num_exp *exp, impl_val *res,
		struct psi_call_frame *frame, struct psi_cpp *cpp);

struct psi_plist *psi_num_exp_tokens(struct psi_num_exp *exp,
		struct psi_plist *list);


#include "calc.h"
static inline zend_long psi_num_exp_get_long(struct psi_num_exp *exp,
		struct psi_call_frame *frame, struct psi_cpp *cpp) {
	impl_val res = {0};

	psi_calc_cast(psi_num_exp_exec(exp, &res, frame, cpp), &res,
			PSI_T_INT64, &res);

	return res.i64;
}
static inline double psi_num_exp_get_double(struct psi_num_exp *exp,
		struct psi_call_frame *frame, struct psi_cpp *cpp) {
	impl_val res = {0};

	psi_calc_cast(psi_num_exp_exec(exp, &res, frame, cpp), &res,
			PSI_T_DOUBLE, &res);

	return res.dval;
}

#endif
