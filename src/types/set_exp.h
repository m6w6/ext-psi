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

#ifndef PSI_TYPES_SET_EXP_H
#define PSI_TYPES_SET_EXP_H

struct psi_data;
struct psi_plist;
struct psi_call_frame;
struct psi_let_exp;
struct psi_set_func;
struct psi_num_exp;
struct psi_impl;
struct psi_decl;
struct psi_validate_scope;

enum psi_set_exp_kind {
	PSI_SET_FUNC,
	PSI_SET_NUMEXP,
};

struct psi_set_exp {
	enum psi_set_exp_kind kind;
	struct psi_impl_var *var;
	struct psi_set_exp *outer;
	struct psi_plist *inner;
	union {
		struct psi_set_func *func;
		struct psi_num_exp *num;
	} data;
};

struct psi_set_exp *psi_set_exp_init(enum psi_set_exp_kind kind, void *data);
void psi_set_exp_free(struct psi_set_exp **exp_ptr);
void psi_set_exp_dump(int fd, struct psi_set_exp *set, unsigned level, int last);
void psi_set_exp_exec(struct psi_set_exp *val, struct psi_call_frame *frame);
void psi_set_exp_exec_ex(struct psi_set_exp *val, zval *zv, impl_val *iv, struct psi_call_frame *frame);
bool psi_set_exp_validate(struct psi_data *data, struct psi_set_exp *set, struct psi_validate_scope *scope);

struct psi_impl_var *psi_set_exp_get_impl_var(struct psi_set_exp *exp);
struct psi_decl_var *psi_set_exp_get_decl_var(struct psi_set_exp *exp);

#endif
