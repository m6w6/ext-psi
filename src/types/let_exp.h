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

#ifndef PSI_TYPES_LET_VAL_H
#define PSI_TYPES_LET_VAL_H

struct psi_data;
struct psi_call_frame;
struct psi_impl;
struct psi_decl_var;
struct psi_num_exp;
struct psi_let_calloc;
struct psi_let_callback;
struct psi_let_func;

enum psi_let_exp_kind {
	PSI_LET_NULL,
	PSI_LET_NUMEXP,
	PSI_LET_CALLOC,
	PSI_LET_CALLBACK,
	PSI_LET_FUNC,
	PSI_LET_TMP,
};

struct psi_let_exp {
	enum psi_let_exp_kind kind;
	struct psi_let_exp *outer;
	struct psi_decl_var *var;
	union {
		struct psi_num_exp *num;
		struct psi_let_calloc *alloc;
		struct psi_let_callback *callback;
		struct psi_let_func *func;
		struct psi_decl_var *var;
	} data;
	unsigned is_reference:1;
};


struct psi_let_exp *psi_let_exp_init(enum psi_let_exp_kind kind, void *data);
struct psi_let_exp *psi_let_exp_init_ex(struct psi_decl_var *var, enum psi_let_exp_kind kind, void *data);
void psi_let_exp_free(struct psi_let_exp **let_ptr);
void psi_let_exp_dump(int fd, struct psi_let_exp *exp, unsigned level, int last);

void *psi_let_exp_exec(struct psi_let_exp *exp, struct psi_decl_arg *darg, void *actual_location, size_t actual_size, struct psi_call_frame *frame);
bool psi_let_exp_validate(struct psi_data *data, struct psi_let_exp *exp, struct psi_impl *impl);

struct psi_let_func *psi_let_exp_get_func(struct psi_let_exp *exp);
struct psi_impl_var *psi_let_exp_get_impl_var(struct psi_let_exp *exp);
struct psi_decl_var *psi_let_exp_get_decl_var(struct psi_let_exp *val);
const char *psi_let_exp_get_decl_var_name(struct psi_let_exp *exp);

#endif
