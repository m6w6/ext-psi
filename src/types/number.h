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

#ifndef PSI_TYPES_NUMBER_H
#define PSI_TYPES_NUMBER_H

struct psi_data;
struct psi_token;
struct psi_cpp;
struct psi_impl;
struct psi_const;
struct psi_decl_enum_item;
struct psi_let_exp;
struct psi_set_exp;
struct psi_call_frame;
struct psi_cpp_macro_call;
struct psi_validate_scope;

enum psi_number_suffix {
	PSI_NUMBER_U	= 0x0100,
	PSI_NUMBER_L	= 0x0200,
	PSI_NUMBER_UL	= 0x0300,

	PSI_NUMBER_LL	= 0x0400,
	PSI_NUMBER_ULL	= 0x0500,

	PSI_NUMBER_F	= 0x1000,
	PSI_NUMBER_D	= 0x2000,
	PSI_NUMBER_DF	= 0x3000,
	PSI_NUMBER_DD	= 0x4000,
	PSI_NUMBER_DL	= 0x2200,
};

enum psi_number_kind {
	PSI_NUMBER_INT		= 0x01,
	PSI_NUMBER_FLT		= 0x02,
};

struct psi_number {
	struct psi_token *token;
	token_t type;
	unsigned flags;
	union {
		zend_string *numb;
		impl_val ival;
		struct psi_const *cnst;
		struct psi_decl_var *dvar;
		struct psi_decl_type *dtyp;
		struct psi_decl_enum_item *enm;
		struct psi_cpp_macro_call *call;
	} data;
};

struct psi_number *psi_number_init(token_t t, void *num, unsigned flags);
struct psi_number *psi_number_copy(struct psi_number *exp);
void psi_number_free(struct psi_number **exp_ptr);
void psi_number_dump(struct psi_dump *dump, struct psi_number *exp);

bool psi_number_validate(struct psi_data *data, struct psi_number *exp,
		struct psi_validate_scope *scope);

token_t psi_number_eval(struct psi_number *exp, impl_val *res,
		struct psi_call_frame *frame, struct psi_cpp *cpp,
		struct psi_num_exp *rec_guard);

struct psi_plist *psi_number_tokens(struct psi_number *exp,
		struct psi_plist *list);

#endif
