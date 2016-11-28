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
#include "parser.h"

static inline bool psi_cpp_level_skipped(struct psi_cpp_data *cpp)
{
	return cpp->skip == cpp->level;
}
static inline void psi_cpp_level_skip(struct psi_cpp_data *cpp)
{
	assert(!cpp->skip);
	cpp->skip = cpp->level;
}
static inline void psi_cpp_level_unskip(struct psi_cpp_data *cpp)
{
	if (psi_cpp_level_skipped(cpp)) {
		cpp->skip = 0;
	}
}
static inline bool psi_cpp_level_masked(struct psi_cpp_data *cpp)
{
	return cpp->seen & (1 << cpp->level);
}
static inline void psi_cpp_level_mask(struct psi_cpp_data *cpp)
{
	assert(!psi_cpp_level_masked(cpp));
	cpp->seen |= (1 << cpp->level);
}
static inline void psi_cpp_level_unmask(struct psi_cpp_data *cpp)
{
	cpp->seen &= ~(1 << cpp->level);
}

static void psi_cpp_eval(struct psi_data *D, struct psi_cpp_data *cpp)
{
	assert(cpp->exp);

	PSI_DEBUG_PRINT(D, "PSI: CPP EVAL < %s (level=%u, skip=%u)\n",
			cpp->exp->token->text, cpp->level, cpp->skip);

#if PSI_CPP_DEBUG
	psi_cpp_exp_dump(2, cpp->exp);
#endif

	switch (cpp->exp->type) {
	case PSI_T_ERROR:
		if (!cpp->skip) {
			D->error(D, cpp->exp->token, PSI_ERROR, "%s",
					cpp->exp->data.tok->text);
		}
		break;
	case PSI_T_WARNING:
		if (!cpp->skip) {
			D->error(D, cpp->exp->token, PSI_WARNING, "%s",
					cpp->exp->data.tok->text);
		}
		break;
	case PSI_T_UNDEF:
		if (!cpp->skip) {
			psi_cpp_undef(cpp, cpp->exp->data.tok);
		}
		break;
	case PSI_T_DEFINE:
		if (!cpp->skip) {
			psi_cpp_define(cpp, cpp->exp->data.decl);
			/* FIXME: copy */
			cpp->exp->data.decl = NULL;
		}
		break;
	case PSI_T_IFDEF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_defined(cpp, cpp->exp->data.tok)) {
				psi_cpp_level_mask(cpp);
			} else {
				psi_cpp_level_skip(cpp);
			}
		}
		break;
	case PSI_T_IFNDEF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_defined(cpp, cpp->exp->data.tok)) {
				psi_cpp_level_skip(cpp);
			} else {
				psi_cpp_level_mask(cpp);
			}
		}
		break;
	case PSI_T_IF:
		++cpp->level;
		if (!cpp->skip) {
			if (psi_cpp_if(cpp->exp, &cpp->defs, D)) {
				psi_cpp_level_mask(cpp);
			} else {
				psi_cpp_level_skip(cpp);
			}
		}
		break;
	case PSI_T_ENDIF:
		if (!cpp->level) {
			D->error(D, cpp->exp->token, PSI_WARNING, "Ingoring lone #endif");
		} else {
			psi_cpp_level_unskip(cpp);
			psi_cpp_level_unmask(cpp);
			--cpp->level;
		}
		break;
	case PSI_T_ELSE:
		/* FIXME: catch "else" after "else" */
		if (!cpp->level) {
			D->error(D, cpp->exp->token, PSI_WARNING, "Ingoring lone #else");
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
			assert(cpp->skip < cpp->level);
		}
		break;
	case PSI_T_ELIF:
		if (!cpp->level) {
			D->error(D, cpp->exp->token, PSI_WARNING, "Ingoring lone #elif");
		} else if (psi_cpp_level_skipped(cpp) && !psi_cpp_level_masked(cpp)) {
			/*
			 * if skip is set on this level and the level has
			 * not been masked yet, then unskip and mask this
			 * level, if the condition evals truthy
			 */
			if (psi_cpp_if(cpp->exp, &cpp->defs, D)) {
				psi_cpp_level_unskip(cpp);
				psi_cpp_level_mask(cpp);
			}
		} else if (!cpp->skip && psi_cpp_level_masked(cpp)) {
			/*
			 * previous block masked this level
			 */
			psi_cpp_level_skip(cpp);
		} else {
			assert(cpp->skip < cpp->level);
		}
		break;
	default:
		assert(0);
		break;
	}

	PSI_DEBUG_PRINT(D, "PSI: CPP EVAL > %s (level=%u, skip=%u)\n",
			cpp->exp->token->text, cpp->level, cpp->skip);

	psi_cpp_exp_free(&cpp->exp);
}

static bool psi_cpp_stage1(struct psi_parser *P, struct psi_cpp_data *cpp)
{
	bool name = false, define = false, hash = false, eol = true, esc = false, ws = false;

	psi_cpp_tokiter_reset(cpp);
	while (psi_cpp_tokiter_valid(cpp)) {
		struct psi_token *token = psi_cpp_tokiter_current(cpp);

		/* strip comments */
		if (token->type == PSI_T_COMMENT) {
			psi_cpp_tokiter_del_cur(cpp, true);
			continue;
		}

		/* line continuations */
		if (token->type == PSI_T_EOL) {
			if (esc) {
				psi_cpp_tokiter_del_range(cpp, psi_cpp_tokiter_index(cpp) - 1, 2, true);
				psi_cpp_tokiter_prev(cpp);
				esc = false;
				continue;
			}
		} else if (token->type == PSI_T_BSLASH) {
			esc = !esc;
		} else {
			esc = false;
		}

		/* this whole turf is needed to distinct between:
		 * #define foo (1,2,3)
		 * #define foo(a,b,c)
		 */

		if (token->type == PSI_T_WHITESPACE) {
			ws = true;
			psi_cpp_tokiter_del_cur(cpp, true);
			continue;
		}

		switch (token->type) {
		case PSI_T_EOL:
			eol = true;
			break;
		case PSI_T_HASH:
			if (eol) {
				hash = true;
				eol = false;
			}
			break;
		case PSI_T_DEFINE:
			if (hash) {
				define = true;
				hash = false;
			}
			break;
		case PSI_T_NAME:
			if (define) {
				name = true;
				define = false;
			}
			break;
		case PSI_T_LPAREN:
			if (name) {
				name = false;
				if (!ws) {
					/* mask special token for parser */
					struct psi_token *no_ws = psi_token_copy(token);

					no_ws->type = PSI_T_NO_WHITESPACE;
					no_ws->text[0] = '\xA0';
					psi_cpp_tokiter_ins_cur(cpp, no_ws);
					continue;
				}
			}
			/* no break */
		default:
			name = define = hash = eol = false;
			break;
		}

		ws = false;
		psi_cpp_tokiter_next(cpp);
	}

	return true;
}

static bool psi_cpp_stage2(struct psi_parser *P, struct psi_cpp_data *cpp)
{
	do {
		bool is_eol = true, do_cpp = false, do_expansion = true, skip_paren = false, skip_all = false;

		psi_cpp_tokiter_reset(cpp);

		while (psi_cpp_tokiter_valid(cpp)) {
			struct psi_token *current = psi_cpp_tokiter_current(cpp);

			if (current->type == PSI_T_HASH) {
				if (is_eol) {
					do_cpp = true;
					is_eol = false;
				}
			} else if (current->type == PSI_T_EOL) {
#if PSI_CPP_DEBUG
				fprintf(stderr, "PSI: CPP do_expansion=true, PSI_T_EOL\n");
#endif
				is_eol = true;
				skip_all = false;
				do_expansion = true;
				if (!do_cpp) {
					psi_cpp_tokiter_del_cur(cpp, true);
					continue;
				}
			} else {
				is_eol = false;

				if (do_cpp) {
					switch (current->type) {
					case PSI_T_DEFINE:
#if PSI_CPP_DEBUG
						fprintf(stderr, "PSI: CPP do_expansion=false, PSI_T_DEFINE, skip_all\n");
#endif
						do_expansion = false;
						skip_all = true;
						break;
					case PSI_T_DEFINED:
						skip_paren = true;
						/* no break */
					case PSI_T_IFDEF:
					case PSI_T_IFNDEF:
					case PSI_T_UNDEF:
#if PSI_CPP_DEBUG
						fprintf(stderr, "PSI: CPP do_expansion=false, PSI_T_{IF{,N},UN}DEF\n");
#endif
						do_expansion = false;
						break;
					case PSI_T_LPAREN:
						if (!skip_all) {
							if (skip_paren) {
								skip_paren = false;
							} else {
								do_expansion = true;
#if PSI_CPP_DEBUG
								fprintf(stderr, "PSI: CPP do_expansion=true, PSI_T_LPAREN, !skip_all, !skip_paren\n");
#endif
							}
						}
						break;
					case PSI_T_NAME:
						break;
					default:
						do_expansion = !skip_all;
#if PSI_CPP_DEBUG
						fprintf(stderr, "PSI CPP do_expansion=%s, <- !skip_all\n", do_expansion?"true":"false");
#endif
					}
				}
			}

			if (cpp->skip) {
				/* FIXME: del_range */
				if (!do_cpp) {
#if PSI_CPP_DEBUG
					fprintf(stderr, "PSI: CPP skip ");
					psi_token_dump(2, current);
#endif
					psi_cpp_tokiter_del_cur(cpp, true);
					continue;
				}
			}

			if (do_expansion && current->type == PSI_T_NAME && psi_cpp_tokiter_defined(cpp)) {
				bool expanded = false;

				while (psi_cpp_tokiter_expand(cpp)) {
					expanded = true;
				}
				if (expanded) {
					continue;
				}
			}

			if (do_cpp) {
				if (is_eol) {
					do_cpp = false;
					skip_all = false;
				}

				if (P->flags & PSI_DEBUG) {
					fprintf(stderr, "PSI> Parse (%zu) ", psi_cpp_tokiter_index(cpp));
					psi_token_dump(2, current);
				}

				psi_parser_proc_parse(P->proc, current->type, current, P);
				psi_cpp_tokiter_del_cur(cpp, false);

				if (is_eol) {
					psi_parser_proc_parse(P->proc, 0, NULL, P);
					psi_cpp_eval(PSI_DATA(P), cpp);
				}

#if PSI_CPP_DEBUG
				psi_cpp_tokiter_dump(2, cpp);
#endif

				continue;
			}

			psi_cpp_tokiter_next(cpp);
		}
	} while (cpp->expanded);

	return true;
}

bool psi_cpp_preprocess(struct psi_parser *P, struct psi_cpp_data *cpp)
{
	if (!psi_cpp_stage1(P, cpp)) {
		return false;
	}

	if (!psi_cpp_stage2(P, cpp)) {
		return false;
	}

	return true;
}

bool psi_cpp_defined(struct psi_cpp_data *cpp, struct psi_token *tok)
{
	bool defined;

	if (tok->type == PSI_T_NAME) {
		defined = zend_hash_str_exists(&cpp->defs, tok->text, tok->size);
	} else {
		defined = false;
	}

#if PSI_CPP_DEBUG
	fprintf(stderr, "PSI: CPP defined -> %s ", defined ? "true" : "false");
	psi_token_dump(2, tok);
#endif

	return defined;
}

void psi_cpp_define(struct psi_cpp_data *cpp, struct psi_cpp_macro_decl *decl)
{
	zend_hash_str_add_ptr(&cpp->defs, decl->token->text, decl->token->size, decl);
}

bool psi_cpp_undef(struct psi_cpp_data *cpp, struct psi_token *tok)
{
	return SUCCESS == zend_hash_str_del(&cpp->defs, tok->text, tok->size);
}

bool psi_cpp_if(struct psi_cpp_exp *exp, HashTable *defs, struct psi_data *D)
{
	if (!psi_num_exp_validate(D, exp->data.num, NULL, NULL, NULL, NULL, NULL)) {
		return false;
	}
	if (!psi_long_num_exp(exp->data.num, NULL, defs)) {
		return false;
	}
	return true;
}
