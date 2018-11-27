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

#ifndef PSI_CONTEXT_H
#define PSI_CONTEXT_H

#include "token.h"

/* zend_function_entry */
#include "Zend/zend_API.h"

struct psi_context;
struct psi_token;
struct psi_parser;
struct psi_call_frame;
struct psi_decl;
struct psi_impl;
struct psi_decl_arg;
struct psi_decl_extvar;
struct psi_let_exp;

struct psi_context_ops {
	/* library */
	const char *name;
	/* called once */
	bool (*load)(void);
	void (*free)(void);
	/* called for each new context */
	bool (*init)(struct psi_context *C);
	void (*dtor)(struct psi_context *C);
	/* compiler */
	bool (*composite_init)(struct psi_context *C, struct psi_decl_arg *darg);
	void (*composite_dtor)(struct psi_context *C, struct psi_decl_arg *darg);
	bool (*extvar_init)(struct psi_context *C, struct psi_decl_extvar *evar);
	void (*extvar_dtor)(struct psi_context *C, struct psi_decl_extvar *evar);
	bool (*decl_init)(struct psi_context *C, struct psi_decl *decl);
	void (*decl_dtor)(struct psi_context *C, struct psi_decl *decl);
	bool (*impl_init)(struct psi_context *C, struct psi_impl *impl, zif_handler *zh);
	void (*impl_dtor)(struct psi_context *C, struct psi_impl *impl);
	bool (*cb_init)(struct psi_context *C, struct psi_let_exp *cb, struct psi_impl *impl);
	void (*cb_dtor)(struct psi_context *C, struct psi_let_exp *cb, struct psi_impl *impl);
	/* calls */
	void (*call)(struct psi_call_frame *frame);
	void (*call_va)(struct psi_call_frame *frame);
	/* types */
	void *(*typeof_impl)(struct psi_context *C, token_t impl_type);
	void *(*typeof_decl)(struct psi_context *C, token_t decl_type);
	void *(*copyof_type)(struct psi_context *C, void *orig_type);
	void (*layoutof_type)(struct psi_context *C, void *orig_type, struct psi_layout *l);
};

#include "data.h"

struct psi_context {
	PSI_DATA_MEMBERS;
	void *context;
	struct psi_context_ops *ops;
	zend_function_entry *closures;
	struct psi_data *data;
	size_t count;
};

struct psi_context_call_data {
	struct psi_context *context;
	union {
		struct psi_impl *fn;
		struct psi_let_callback *cb;
	} impl;
};

struct psi_context *psi_context_init(struct psi_context *C, struct psi_context_ops *ops, psi_error_cb error, unsigned flags);
void psi_context_build(struct psi_context *C, const char *path);
void psi_context_compile(struct psi_context *C);

void **psi_context_composite_type_elements(struct psi_context *C,
		struct psi_decl_arg *darg, struct psi_plist **eles);
void *psi_context_decl_arg_call_type(struct psi_context *C, struct psi_decl_arg *arg);
void *psi_context_decl_arg_full_type(struct psi_context *C, struct psi_decl_arg *arg);

ZEND_RESULT_CODE psi_context_call(struct psi_context *C, zend_execute_data *execute_data, zval *return_value, struct psi_impl *impl);
void psi_context_dump(struct psi_dump *dump, struct psi_context *C);
void psi_context_dtor(struct psi_context *C);
void psi_context_free(struct psi_context **C);

#endif
