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

#ifndef PSI_TYPES_SET_FUNC_H
#define PSI_TYPES_SET_FUNC_H

#include "token.h"
#include "marshal.h"

struct psi_plist;
struct psi_decl_var;

struct psi_set_func {
	struct psi_token *token;
	token_t type;
	char *name;
	struct psi_decl_var *var;
	psi_marshal_set handler;
	struct psi_plist *inner;
	unsigned recursive:1;
};

struct psi_set_func *psi_set_func_init(token_t type, const char *name, struct psi_decl_var *var);
void psi_set_func_free(struct psi_set_func **func_ptr);
void psi_set_func_dump(int fd, struct psi_set_func *func, unsigned level);
bool psi_set_func_validate(struct psi_data *data, struct psi_set_func *func,
		struct psi_set_exp *set, struct psi_impl *impl, struct psi_decl *cb_decl);

#endif
