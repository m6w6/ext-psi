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

#ifndef PSI_TYPES_LET_CALLBACK_H
#define PSI_TYPES_LET_CALLBACK_H

struct psi_data;
struct psi_impl;
struct psi_decl;
struct psi_plist;
struct psi_let_exp;
struct psi_let_func;

struct psi_let_callback {
	struct psi_token *token;
	struct psi_let_func *func;
	struct psi_plist *args;
	struct psi_plist *cb_args;
	struct psi_decl *decl;
	void *info;
};

struct psi_let_callback *psi_let_callback_init(struct psi_let_func *func, struct psi_plist *args, struct psi_plist *cb_args);
void psi_let_callback_free(struct psi_let_callback **cb_ptr);
void psi_let_callback_dump(struct psi_dump *dump, struct psi_let_callback *cb, unsigned level);
bool psi_let_callback_validate(struct psi_data *data, struct psi_let_callback *cb, struct psi_validate_scope *scope);

#endif
