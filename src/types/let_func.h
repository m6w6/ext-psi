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

#ifndef PSI_TYPES_LET_FUNC_H
#define PSI_TYPES_LET_FUNC_H

#include "token.h"

struct psi_data;
struct psi_impl;
struct psi_decl_arg;
struct psi_impl_var;
struct psi_let_exp;
struct psi_call_frame;

struct psi_let_func {
	struct psi_token *token;
	token_t type;
	char *name;
	struct psi_impl_var *var;
	struct psi_plist *inner;
};

struct psi_let_func *psi_let_func_init(token_t type, const char *name, struct psi_impl_var *var);
void psi_let_func_free(struct psi_let_func **func_ptr);
void psi_let_func_dump(int fd, struct psi_let_func *func, unsigned level);

void *psi_let_func_exec(struct psi_let_exp *func_val, struct psi_let_func *func, struct psi_decl_arg *darg, struct psi_call_frame *frame);
bool psi_let_func_validate(struct psi_data *data, struct psi_let_func *func, struct psi_validate_scope *scope);

#include "marshal.h"

static inline psi_marshal_let locate_let_func_fn(token_t type) {
	psi_marshal_let let_fn;

	switch (type) {
		case PSI_T_BOOLVAL:		let_fn = psi_let_boolval;	break;
		case PSI_T_INTVAL:		let_fn = psi_let_intval;	break;
		case PSI_T_FLOATVAL:	let_fn = psi_let_floatval;	break;
		case PSI_T_STRVAL:		let_fn = psi_let_strval;	break;
		case PSI_T_STRLEN:		let_fn = psi_let_strlen;	break;
		case PSI_T_PATHVAL:		let_fn = psi_let_pathval;	break;
		case PSI_T_OBJVAL:		let_fn = psi_let_objval;	break;
		case PSI_T_ZVAL:		let_fn = psi_let_zval;		break;
		case PSI_T_VOID:		let_fn = psi_let_void;		break;
		case PSI_T_COUNT:		let_fn = psi_let_count;		break;
		default:				let_fn = NULL;				break;
	}
	return let_fn;
}

#endif
