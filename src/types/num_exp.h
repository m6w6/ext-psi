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

#ifndef PSI_TYPES_NUM_EXP
#define PSI_TYPES_NUM_EXP

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

struct psi_num_exp {
	struct psi_token *token;
	token_t type;
	union {
		char *numb;
		impl_val ival;
		struct psi_const *cnst;
		struct psi_decl_var *dvar;
		struct psi_decl_enum_item *enm;
	} data;
	token_t op;
	struct psi_num_exp *operand;
	token_t (*calc)(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
};

struct psi_num_exp *psi_num_exp_init(token_t t, void *num);
struct psi_num_exp *psi_num_exp_copy(struct psi_num_exp *exp);
void psi_num_exp_free(struct psi_num_exp **exp_ptr);
void psi_num_exp_dump(int fd, struct psi_num_exp *exp);

bool psi_num_exp_validate(struct psi_data *data, struct psi_num_exp *exp,
		struct psi_impl *impl, struct psi_decl *cb_decl,
		struct psi_let_exp *current_let, struct psi_set_exp *current_set,
		struct psi_decl_enum *current_enum);

token_t psi_num_exp_exec(struct psi_num_exp *exp, impl_val *res, struct psi_call_frame *frame);

#include <assert.h>

static inline zend_long psi_long_num_exp(struct psi_num_exp *exp, struct psi_call_frame *frame) {
	impl_val val = {0};

	switch (psi_num_exp_exec(exp, &val, frame)) {
	case PSI_T_UINT8:	return val.u8;
	case PSI_T_UINT16:	return val.u16;
	case PSI_T_UINT32:	return val.u32;
	case PSI_T_UINT64:	return val.u64; /* FIXME */
	case PSI_T_INT8:	return val.i8;
	case PSI_T_INT16:	return val.i16;
	case PSI_T_INT32:	return val.i32;
	case PSI_T_INT64:	return val.i64;
	case PSI_T_FLOAT:	return val.fval;
	case PSI_T_DOUBLE:	return val.dval;
	default:
		assert(0);
	}
	return 0;
}

#endif
