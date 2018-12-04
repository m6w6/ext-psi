/*******************************************************************************
 Copyright (c) 2017, Michael Wallner <mike@php.net>.
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

#ifndef PSI_TYPES_CPP_EXP_H
#define PSI_TYPES_CPP_EXP_H

#include "token.h"

struct psi_cpp;
struct psi_cpp_macro_decl;
struct psi_cpp_macro_call;
struct psi_num_exp;

struct psi_cpp_exp {
	struct psi_token *token;
	token_t type;
	union {
		struct psi_cpp_macro_decl *decl;
		struct psi_num_exp *num;
		struct psi_token *tok;
	} data;
};

struct psi_cpp_exp *psi_cpp_exp_init(token_t type, void *data);
void psi_cpp_exp_free(struct psi_cpp_exp **exp_ptr);
void psi_cpp_exp_dump(struct psi_dump *dump, struct psi_cpp_exp *exp);
void psi_cpp_exp_exec(struct psi_cpp_exp *exp, struct psi_cpp *cpp, struct psi_data *D);

#endif
