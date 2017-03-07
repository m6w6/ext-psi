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

#ifndef PSI_TYPES_CPP_MACRO_DECL_H
#define PSI_TYPES_CPP_MACRO_DECL_H

struct psi_token;
struct psi_plist;
struct psi_num_exp;

struct psi_cpp_macro_decl {
	struct psi_token *token;
	struct psi_num_exp *exp;
	struct psi_plist *sig;
	struct psi_plist *tokens;
};

struct psi_cpp_macro_decl *psi_cpp_macro_decl_init(struct psi_plist *sig,
		struct psi_plist *tokens, struct psi_num_exp *exp);
void psi_cpp_macro_decl_free(struct psi_cpp_macro_decl **macro_ptr);
void psi_cpp_macro_decl_dump(int fd, struct psi_cpp_macro_decl *decl);
bool psi_cpp_macro_decl_equal(struct psi_cpp_macro_decl *d1, struct psi_cpp_macro_decl *d2);

#endif
