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

#include "decl_var.h"
#include "num_exp.h"
#include "let_calloc.h"
#include "let_callback.h"
#include "let_func.h"

enum let_val_kind {
	PSI_LET_NULL,
	PSI_LET_NUMEXP,
	PSI_LET_CALLOC,
	PSI_LET_CALLBACK,
	PSI_LET_FUNC,
	PSI_LET_TMP,
};

#define PSI_LET_REFERENCE 0x1;

typedef struct let_val {
	enum let_val_kind kind;
	decl_var *var;
	union {
		num_exp *num;
		let_calloc *alloc;
		let_callback *callback;
		let_func *func;
		decl_var *var;
	} data;
	unsigned is_reference:1;
} let_val;


let_val* init_let_val(enum let_val_kind kind, void* data);
let_val* init_let_val_ex(decl_var *var, enum let_val_kind kind, void* data);
void free_let_val(let_val* let);
void dump_let_val(int fd, let_val *val, unsigned level, int last);

struct psi_data;
struct impl;

int validate_let_val(struct psi_data *data, let_val *val, decl_var *let_var, struct impl *impl);

static inline let_func *locate_let_val_func(let_val *val) {
	if (val) {
		switch (val->kind) {
		case PSI_LET_CALLBACK:
			return val->data.callback->func;
		case PSI_LET_FUNC:
			return val->data.func;
		default:
			break;
		}
	}

	return NULL;
}

static inline decl_arg *locate_let_val_inner_ref(let_val *val) {
	let_func *fn = locate_let_val_func(val);
	return fn ? fn->ref: NULL;
}

static inline impl_var *locate_let_val_impl_var(let_val *val) {
	let_func *fn = locate_let_val_func(val);
	return fn ? fn->var : NULL;
}

static inline const char *locate_let_val_varname(let_val *val) {
	impl_var *var;

	if (val->var) {
		return val->var->name;
	}

	var = locate_let_val_impl_var(val);

	if (var) {
		return &var->name[1];
	}
	return NULL;
}
#endif
