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
	struct psi_cpp_macro_decl *macro = pecalloc(1, sizeof(*macro), 1);
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
		psi_token_free(&macro->token);
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

void psi_cpp_macro_decl_dump(struct psi_dump *dump, struct psi_cpp_macro_decl *macro)
{
	PSI_DUMP(dump, "%s", macro->token->text->val);

	if (macro->sig) {
		size_t i = 0;
		struct psi_token *tok;

		PSI_DUMP(dump, "(");
		while (psi_plist_get(macro->sig, i++, &tok)) {
			PSI_DUMP(dump, "%s%s", i>1?",":"", tok->text->val);
		}
		PSI_DUMP(dump, ")");
	}

	if (macro->exp) {
		PSI_DUMP(dump, " ");
		psi_num_exp_dump(dump, macro->exp);

		assert(macro->tokens);

	} else if (macro->tokens) {
		size_t i = 0;
		struct psi_token *tok;

		while (psi_plist_get(macro->tokens, i++, &tok)) {
			switch (tok->type) {
			case PSI_T_QUOTED_STRING:
				PSI_DUMP(dump, " \"%s\"", tok->text->val);
				break;
			case PSI_T_QUOTED_CHAR:
				PSI_DUMP(dump, " '%s'", tok->text->val);
				break;
			default:
				PSI_DUMP(dump, " %s", tok->text->val);
			}
		}
	}
}

static inline bool cmp_token_list(struct psi_plist *l1, struct psi_plist *l2)
{
	size_t c = psi_plist_count(l1), i;

	if (c != psi_plist_count(l2)) {
		return false;
	}

	for (i = 0; i < c; ++i) {
		struct psi_token *t1, *t2;

		psi_plist_get(l1, i, &t1);
		psi_plist_get(l2, i, &t2);

		if (!zend_string_equals(t1->text, t2->text)) {
			return false;
		}
	}

	return true;
}

bool psi_cpp_macro_decl_equal(struct psi_cpp_macro_decl *d1, struct psi_cpp_macro_decl *d2)
{
	if (d1->sig) {
		if (!d2->sig) {
			return false;
		}

		if (!cmp_token_list(d1->sig, d2->sig)) {
			return false;
		}
	} else if (d2->sig) {
		return false;
	}

	if (d1->tokens) {
		if (!d2->tokens) {
			return false;
		}

		if (!cmp_token_list(d1->tokens, d2->tokens)) {
			return false;
		}
	} else if (d2->tokens) {
		return false;
	}

	/* FIXME compare num_exps */

	return true;
}
