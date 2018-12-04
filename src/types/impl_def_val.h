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

#ifndef PSI_TYPES_IMPL_DEF_VAL_H
#define PSI_TYPES_IMPL_DEF_VAL_H

#include "token.h"
#include "types/impl_val.h"

struct psi_data;
struct psi_impl_type;
struct psi_dump;

struct psi_impl_def_val {
	struct psi_token *token;
	token_t type;
	union {
		struct psi_num_exp *num;
	} data;
	token_t ityp;
	impl_val ival;
};

struct psi_impl_def_val *psi_impl_def_val_init(token_t t, void *data);
void psi_impl_def_val_free(struct psi_impl_def_val **def_ptr);
void psi_impl_def_val_dump(struct psi_dump *dump, struct psi_impl_def_val *val);
bool psi_impl_def_val_validate(struct psi_data *data, struct psi_impl_def_val *def,
		struct psi_impl_type *cmp, struct psi_validate_scope *scope);
void psi_impl_def_val_get_zval(struct psi_impl_def_val *val, token_t typ, zval *z);
#endif
