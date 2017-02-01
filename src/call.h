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

#ifndef PSI_CALL_H
#define PSI_CALL_H

#include "Zend/zend_types.h"

#include "data.h"

struct psi_call_frame_symbol {
	impl_val *ival_ptr; /* marshaled */
	void *ptr; /* possibly indirect (pointer to ival_ptr) */
	impl_val temp_val;
};

struct psi_call_frame_argument {
	impl_val ival; /* input */
	impl_val temp_val; /* va */
	impl_val *ival_ptr; /* marshaled, pointer to ival or temp_val */
	zval *zval_ptr; /* input */
	struct psi_impl_arg *spec;
	token_t va_type;
};

struct psi_call_frame_callback {
	struct psi_let_exp *cb;
	size_t argc;
	void **argv;
	void *rval;
};

struct psi_call_frame_argument *psi_call_frame_argument_init(struct psi_impl_arg *spec, impl_val *ival, zval *zptr, int is_vararg);
void psi_call_frame_argument_free(struct psi_call_frame_argument *arg);

struct psi_call_frame_symbol *psi_call_frame_symbol_init();
void psi_call_frame_symbol_free(struct psi_call_frame_symbol *arg);

struct psi_call_frame {
	struct psi_context *context;
	struct psi_decl *decl;
	struct psi_impl *impl;
	HashTable arguments;
	HashTable symbols;
	void **pointers;
	void *rpointer;
	zend_llist temp;
};

struct psi_call_frame *psi_call_frame_init(struct psi_context *context, struct psi_decl *decl, struct psi_impl *impl);

ZEND_RESULT_CODE psi_call_frame_parse_args(struct psi_call_frame *frame, zend_execute_data *execute_data);

size_t psi_call_frame_num_var_args(struct psi_call_frame *frame);
size_t psi_call_frame_num_fixed_args(struct psi_call_frame *frame);

zval *psi_call_frame_new_argument(struct psi_call_frame *frame, struct psi_call_frame_argument *frame_arg);
zval *psi_call_frame_sub_argument(struct psi_call_frame *frame, struct psi_impl_var *inner_var, zval *outer_zval, const char *name);

struct psi_call_frame_argument *psi_call_frame_get_argument(struct psi_call_frame *frame, const char *name);
struct psi_call_frame_argument *psi_call_frame_get_var_argument(struct psi_call_frame *frame, zend_long index);

struct psi_call_frame_symbol *psi_call_frame_fetch_symbol(struct psi_call_frame *frame, struct psi_decl_var *dvar);

void psi_call_frame_enter(struct psi_call_frame *frame);

void **psi_call_frame_get_arg_pointers(struct psi_call_frame *frame);

ZEND_RESULT_CODE psi_call_frame_do_let(struct psi_call_frame *frame);
void psi_call_frame_do_call(struct psi_call_frame *frame);
void psi_call_frame_do_callback(struct psi_call_frame *frame, struct psi_call_frame_callback *cb);
void psi_call_frame_do_return(struct psi_call_frame *frame, zval *return_value);
void psi_call_frame_do_set(struct psi_call_frame *frame);
void psi_call_frame_do_free(struct psi_call_frame *frame);

void **psi_call_frame_push_auto_ex(struct psi_call_frame *frame, void *auto_free, void (*dtor)(void*));
void **psi_call_frame_push_auto(struct psi_call_frame *frame, void *auto_free);

void psi_call_frame_free(struct psi_call_frame *frame);

#endif
