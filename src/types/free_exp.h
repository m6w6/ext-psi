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

#ifndef PSI_TYPES_FREE_EXP_H
#define PSI_TYPES_FREE_EXP_H

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_impl;
struct psi_decl;
struct psi_let_stmt;
struct psi_call_frame;

struct psi_free_exp {
	struct psi_token *token;
	char *func;
	struct psi_plist *vars;
	struct psi_decl *decl;
	struct psi_let_stmt **let;
};

struct psi_free_exp *psi_free_exp_init(const char *func, struct psi_plist *vars);
void psi_free_exp_free(struct psi_free_exp **f_ptr);
void psi_free_exp_dump(int fd, struct psi_free_exp *call);

bool psi_free_exp_validate(struct psi_data *data, struct psi_free_exp *fc, struct psi_validate_scope *scope);

void psi_free_exp_exec(struct psi_free_exp *f, struct psi_call_frame *frame);

#endif
