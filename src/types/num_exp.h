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

#include "constant.h"
#include "decl_var.h"
#include "impl_val.h"

typedef struct num_exp {
	struct psi_token *token;
	token_t t;
	union {
		char *numb;
		constant *cnst;
		decl_var *dvar;
		struct decl_enum_item *enm;
	} u;
	token_t operator;
	int (*calculator)(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);
	struct num_exp *operand;
} num_exp;

num_exp *init_num_exp(token_t t, void *num);
num_exp *copy_num_exp(num_exp *exp);
void free_num_exp(num_exp *exp);
void dump_num_exp(int fd, num_exp *exp);

struct psi_data;
struct decl_args;
struct decl_arg;
struct decl_enum;

int validate_num_exp(struct psi_data *data, num_exp *exp, struct decl_args *dargs, struct decl_arg *func, struct decl_enum *enm);

#endif
