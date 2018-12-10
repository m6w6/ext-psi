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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include <assert.h>

#include "data.h"
#include "cpp.h"
#include "debug.h"

struct psi_cpp_exp *psi_cpp_exp_init(token_t type, void *data)
{
	struct psi_cpp_exp *exp = pecalloc(1, sizeof(*exp), 1);

	switch ((exp->type = type)) {
	case PSI_T_WARNING:
	case PSI_T_ERROR:
	case PSI_T_UNDEF:
	case PSI_T_IFDEF:
	case PSI_T_IFNDEF:
	case PSI_T_IMPORT:
	case PSI_T_INCLUDE:
	case PSI_T_INCLUDE_NEXT:
		exp->data.tok = data;
		break;
	case PSI_T_DEFINE:
	case PSI_T_PRAGMA:
		exp->data.decl = data;
		break;
	case PSI_T_IF:
	case PSI_T_ELIF:
		exp->data.num = data;
		break;
	case PSI_T_ENDIF:
	case PSI_T_ELSE:
		break;
	default:
		assert(0);
		break;
	}

	return exp;
}

void psi_cpp_exp_free(struct psi_cpp_exp **exp_ptr)
{
	if (*exp_ptr) {
		struct psi_cpp_exp *exp = *exp_ptr;

		*exp_ptr = NULL;
		switch (exp->type) {
		case PSI_T_WARNING:
		case PSI_T_ERROR:
		case PSI_T_UNDEF:
		case PSI_T_IFDEF:
		case PSI_T_IFNDEF:
		case PSI_T_IMPORT:
		case PSI_T_INCLUDE:
		case PSI_T_INCLUDE_NEXT:
			psi_token_free(&exp->data.tok);
			break;
		case PSI_T_DEFINE:
		case PSI_T_PRAGMA:
			psi_cpp_macro_decl_free(&exp->data.decl);
			break;
		case PSI_T_IF:
		case PSI_T_ELIF:
			psi_num_exp_free(&exp->data.num);
			break;
		case PSI_T_ENDIF:
		case PSI_T_ELSE:
			break;
		default:
			assert(0);
			break;
		}
		psi_token_free(&exp->token);
		free(exp);
	}
}

void psi_cpp_exp_dump(struct psi_dump *dump, struct psi_cpp_exp *exp)
{
	PSI_DUMP(dump, "#%s ", exp->token->text->val);
	switch (exp->type) {
	case PSI_T_WARNING:
	case PSI_T_ERROR:
		if (!exp->data.tok) {
			break;
		}
		/* no break */
	case PSI_T_UNDEF:
	case PSI_T_IFDEF:
	case PSI_T_IFNDEF:
		PSI_DUMP(dump, "%s", exp->data.tok->text->val);
		break;
	case PSI_T_IMPORT:
	case PSI_T_INCLUDE:
	case PSI_T_INCLUDE_NEXT:
		if (exp->data.tok->type == PSI_T_CPP_HEADER) {
			PSI_DUMP(dump, "<%s>", exp->data.tok->text->val);
		} else {
			PSI_DUMP(dump, "\"%s\"", exp->data.tok->text->val);
		}
		break;
	case PSI_T_DEFINE:
	case PSI_T_PRAGMA:
		psi_cpp_macro_decl_dump(dump, exp->data.decl);
		break;
	case PSI_T_IF:
	case PSI_T_ELIF:
		psi_num_exp_dump(dump, exp->data.num);
		break;
	case PSI_T_ENDIF:
	case PSI_T_ELSE:
		break;
	default:
		assert(0);
		break;
	}
	PSI_DUMP(dump, "\n");
}


static inline bool psi_cpp_level_skipped(struct psi_cpp *cpp)
{
	return cpp->skip == cpp->level;
}

static inline void psi_cpp_level_skip(struct psi_cpp *cpp)
{
	assert(!cpp->skip);
	cpp->skip = cpp->level;
}

static inline void psi_cpp_level_unskip(struct psi_cpp *cpp)
{
	if (psi_cpp_level_skipped(cpp)) {
		cpp->skip = 0;
	}
}

static inline bool psi_cpp_level_masked(struct psi_cpp *cpp)
{
	return cpp->seen & (1 << cpp->level);
}

static inline void psi_cpp_level_mask(struct psi_cpp *cpp)
{
	assert(!psi_cpp_level_masked(cpp));
	cpp->seen |= (1 << cpp->level);
}

static inline void psi_cpp_level_unmask(struct psi_cpp *cpp)
{
	cpp->seen &= ~(1 << cpp->level);
}

void psi_cpp_exp_exec(struct psi_cpp_exp *exp, struct psi_cpp *cpp, struct psi_data *D)
{
	PSI_DEBUG_PRINT(D, "PSI: CPP EVAL < %s (level=%u, skip=%u)\n",
			exp->token->text->val, cpp->level, cpp->skip);

#if PSI_CPP_DEBUG
	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP exec -> ");
	PSI_DEBUG_DUMP(cpp->parser, psi_cpp_exp_dump, exp);
#endif

	switch (exp->type) {
	case PSI_T_ERROR:
		if (!cpp->skip) {
			D->error(D, exp->token, PSI_ERROR, "%s",
					exp->data.tok ? exp->data.tok->text->val : "");
		}
		break;
	case PSI_T_WARNING:
		if (!cpp->skip) {
			D->error(D, exp->token, PSI_WARNING, "%s",
					exp->data.tok ? exp->data.tok->text->val : "");
		}
		break;
	case PSI_T_UNDEF:
		if (!cpp->skip) {
			psi_cpp_undef(cpp, exp->data.tok);
		}
		break;
	case PSI_T_DEFINE:
		if (!cpp->skip) {
			psi_cpp_define(cpp, exp->data.decl);
			/* FIXME: copy */
			exp->data.decl = NULL;
		}
		break;
	case PSI_T_PRAGMA:
		if (!cpp->skip) {
			psi_cpp_pragma(cpp, exp->data.decl);
		}
		break;
	case PSI_T_IFDEF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_defined(cpp, exp->data.tok)) {
				psi_cpp_level_mask(cpp);
			} else {
				psi_cpp_level_skip(cpp);
			}
		}
		break;
	case PSI_T_IFNDEF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_defined(cpp, exp->data.tok)) {
				psi_cpp_level_skip(cpp);
			} else {
				psi_cpp_level_mask(cpp);
			}
		}
		break;
	case PSI_T_IF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_if(cpp, exp)) {
				psi_cpp_level_mask(cpp);
			} else {
				psi_cpp_level_skip(cpp);
			}
		}
		break;
	case PSI_T_ENDIF:
		if (!cpp->level) {
			D->error(D, exp->token, PSI_WARNING, "Ingoring lone #endif");
		} else {
			psi_cpp_level_unskip(cpp);
			psi_cpp_level_unmask(cpp);
			--cpp->level;
		}
		break;
	case PSI_T_ELSE:
		/* FIXME: catch "else" after "else" */
		if (!cpp->level) {
			D->error(D, exp->token, PSI_WARNING, "Ingoring lone #else");
		} else if (psi_cpp_level_skipped(cpp) && !psi_cpp_level_masked(cpp)) {
			/*
			 * if skip is set on this level and the level has
			 * not been masked yet, then unskip and mask this level
			 */
			psi_cpp_level_unskip(cpp);
			psi_cpp_level_mask(cpp);
		} else if (!cpp->skip && psi_cpp_level_masked(cpp)) {
			/*
			 * previous block masked this level
			 */
			psi_cpp_level_skip(cpp);
		} else {
			assert(cpp->skip <= cpp->level);
		}
		break;
	case PSI_T_ELIF:
		if (!cpp->level) {
			D->error(D, exp->token, PSI_WARNING, "Ingoring lone #elif");
		} else if (psi_cpp_level_skipped(cpp) && !psi_cpp_level_masked(cpp)) {
			/*
			 * if skip is set on this level and the level has
			 * not been masked yet, then unskip and mask this
			 * level, if the condition evals truthy
			 */
			if (psi_cpp_if(cpp, exp)) {
				psi_cpp_level_unskip(cpp);
				psi_cpp_level_mask(cpp);
			}
		} else if (!cpp->skip && psi_cpp_level_masked(cpp)) {
			/*
			 * previous block masked this level
			 */
			psi_cpp_level_skip(cpp);
		} else {
			assert(cpp->skip <= cpp->level);
		}
		break;
	case PSI_T_INCLUDE:
		if (!cpp->skip) {
			if (!psi_cpp_include(cpp, exp->data.tok, PSI_CPP_INCLUDE)) {
				D->error(D, exp->token, PSI_WARNING, "Failed to include %s: %s",
						exp->data.tok->text->val, strerror(errno));
			}
		}
		break;
	case PSI_T_INCLUDE_NEXT:
		if (!cpp->skip) {
			if (!psi_cpp_include(cpp, exp->data.tok, PSI_CPP_INCLUDE_NEXT)) {
				D->error(D, exp->token, PSI_WARNING, "Failed to include next %s: %s",
						exp->data.tok->text->val, strerror(errno));
			}
		}
		break;
	case PSI_T_IMPORT:
		if (!cpp->skip) {
			if (!psi_cpp_include(cpp, exp->data.tok, PSI_CPP_INCLUDE_ONCE)) {
				D->error(D, exp->token, PSI_WARNING, "Failed to include once %s: %s",
						exp->data.tok->text->val, strerror(errno));
			}
		}
		break;
	default:
		assert(0);
		break;
	}

	PSI_DEBUG_PRINT(D, "PSI: CPP EVAL > %s (level=%u, skip=%u)\n",
			exp->token->text->val, cpp->level, cpp->skip);
}
