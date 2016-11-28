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

#include "php_psi_stdinc.h"

#include "cpp.h"
#include "data.h"

struct psi_cpp_macro_decl *psi_cpp_macro_decl_init(struct psi_plist *sig,
		struct psi_plist *tokens, struct psi_num_exp *exp)
{
	struct psi_cpp_macro_decl *macro = calloc(1, sizeof(*macro));
	macro->exp = exp;
	macro->sig = sig;
	macro->tokens = tokens;
	return macro;
}

void psi_cpp_macro_decl_free(struct psi_cpp_macro_decl **macro_ptr)
{
	if (*macro_ptr) {
		struct psi_cpp_macro_decl *macro = *macro_ptr;

		*macro_ptr = NULL;
		if (macro->token) {
			free(macro->token);
		}
		if (macro->exp) {
			psi_num_exp_free(&macro->exp);
		}
		if (macro->sig) {
			psi_plist_free(macro->sig);
		}
		if (macro->tokens) {
			psi_plist_free(macro->tokens);
		}
		free(macro);
	}
}

void psi_cpp_macro_decl_dump(int fd, struct psi_cpp_macro_decl *macro)
{
	dprintf(fd, "%s", macro->token->text);

	if (macro->sig) {
		size_t i = 0;
		struct psi_token *tok;

		dprintf(fd, "(");
		while (psi_plist_get(macro->sig, i++, &tok)) {
			dprintf(fd, "%s%s", i>1?",":"", tok->text);
		}
		dprintf(fd, ")");
	}
}
