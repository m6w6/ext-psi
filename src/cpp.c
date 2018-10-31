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

#include <libgen.h>

#include "cpp.h"
#include "parser.h"

#define PSI_CPP_SEARCH
#define PSI_CPP_PREDEF
#include "php_psi_cpp.h"

#include "php_psi.h"

static void free_cpp_def(zval *p)
{
	if (Z_TYPE_P(p) == IS_PTR) {
		psi_cpp_macro_decl_free((void *) &Z_PTR_P(p));
	}
}

struct psi_cpp *psi_cpp_init(struct psi_parser *P)
{
	struct psi_cpp *cpp = calloc(1, sizeof(*cpp));

	cpp->parser = P;
	zend_hash_init(&cpp->defs, 0, NULL, free_cpp_def, 1);
	zend_hash_init(&cpp->once, 0, NULL, NULL, 1);

	return cpp;
}

bool psi_cpp_load_defaults(struct psi_cpp *cpp)
{
	struct psi_parser_input *predef;

	if ((predef = psi_parser_open_string(cpp->parser, psi_cpp_predef, sizeof(psi_cpp_predef) - 1))) {
		bool parsed = psi_parser_parse(cpp->parser, predef);
		psi_parser_input_free(&predef);
		return parsed;
	}

	return false;
}

#if PSI_CPP_DEBUG
static int dump_def(zval *p)
{
	struct psi_cpp_macro_decl *decl = Z_PTR_P(p);

	if (decl) {
		dprintf(2, "#define ");
		psi_cpp_macro_decl_dump(2, decl);
		dprintf(2, "\n");
	}
	return ZEND_HASH_APPLY_KEEP;
}
#endif

void psi_cpp_free(struct psi_cpp **cpp_ptr)
{
	if (*cpp_ptr) {
		struct psi_cpp *cpp = *cpp_ptr;

#if PSI_CPP_DEBUG
		fprintf(stderr, "PSI: CPP decls:\n");
		zend_hash_apply(&cpp->defs, dump_def);
#endif
		*cpp_ptr = NULL;
		zend_hash_destroy(&cpp->defs);
		zend_hash_destroy(&cpp->once);
		free(cpp);
	}
}

static bool psi_cpp_stage1(struct psi_cpp *cpp)
{
	bool name = false, define = false, hash = false, eol = true, esc = false, ws = false;

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s\n", "stage1");

	psi_cpp_tokiter_reset(cpp);
	while (psi_cpp_tokiter_valid(cpp)) {
		struct psi_token *token = psi_cpp_tokiter_current(cpp);

		/* strip comments and attributes */
		if (token->type == PSI_T_COMMENT
				|| token->type == PSI_T_CPP_ATTRIBUTE) {
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
			if (name) {
				name = false;
			}
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
					zend_string_release(no_ws->text);
					no_ws->text = zend_string_init("\xA0", 1, 1);
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

static bool psi_cpp_stage2(struct psi_cpp *cpp)
{
	struct psi_plist *parser_tokens = psi_plist_init((psi_plist_dtor) psi_token_free);
	bool is_eol = true, do_cpp = false, do_expansion = true, skip_paren = false, skip_all = false;

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s\n", "stage2");

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
					fprintf(stderr, "PSI: CPP do_expansion=%s, <- !skip_all\n", do_expansion?"true":"false");
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
			parser_tokens = psi_plist_add(parser_tokens, &current);

			if (is_eol) {
				size_t processed = 0;
				bool parsed = psi_parser_process(cpp->parser, parser_tokens, &processed);

				/* EOL */
				psi_plist_pop(parser_tokens, NULL);
				psi_plist_clean(parser_tokens);
				do_cpp = false;

				if (!parsed) {
					psi_plist_free(parser_tokens);
					return false;
				}
			} else {
				/* leave EOLs in the input stream, else we might end up
				 * with a hash not preceded with a new line after include */
				psi_cpp_tokiter_del_cur(cpp, false);
			}

#if PSI_CPP_DEBUG > 1
			psi_cpp_tokiter_dump(2, cpp);
#endif

			continue;
		}

		psi_cpp_tokiter_next(cpp);
	}

	psi_plist_free(parser_tokens);

	return true;
}

bool psi_cpp_process(struct psi_cpp *cpp, struct psi_plist **tokens)
{
	bool parsed = false;
	struct psi_cpp temp = *cpp;

	cpp->tokens = *tokens;
	if (psi_cpp_stage1(cpp) && psi_cpp_stage2(cpp)) {
		parsed = true;
	}
	*tokens = cpp->tokens;

	if (temp.tokens) {
		cpp->tokens = temp.tokens;
		cpp->index = temp.index;
	}

	return parsed;
}

bool psi_cpp_defined(struct psi_cpp *cpp, struct psi_token *tok)
{
	bool defined;

	if (tok->type == PSI_T_NAME) {
		defined = zend_hash_exists(&cpp->defs, tok->text);
	} else {
		defined = false;
	}

#if PSI_CPP_DEBUG
	fprintf(stderr, "PSI: CPP defined -> %s ", defined ? "true" : "false");
	if (defined) {
		struct psi_cpp_macro_decl *macro = zend_hash_find_ptr(&cpp->defs, tok->text);
		fprintf(stderr, " @ %s:%u ", macro->token->file->val, macro->token->line);
	}
	psi_token_dump(2, tok);
#endif

	return defined;
}

void psi_cpp_define(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	struct psi_cpp_macro_decl *old = zend_hash_find_ptr(&cpp->defs, decl->token->text);

	if (old && !psi_cpp_macro_decl_equal(old, decl)) {
		cpp->parser->error(PSI_DATA(cpp->parser), decl->token, PSI_WARNING,
				"'%s' redefined", decl->token->text->val);
		cpp->parser->error(PSI_DATA(cpp->parser), old->token, PSI_WARNING,
				"'%s' previously defined", old->token->text->val);
	}
#if PSI_CPP_DEBUG
	if (decl->exp) {
		fprintf(stderr, "MACRO: num_exp: ", decl->token->text);
	} else if (decl->tokens) {
		fprintf(stderr, "MACRO: decl   : ", decl->token->text);
	}
	psi_cpp_macro_decl_dump(2, decl);
	fprintf(stderr, "\n");
#endif
	zend_hash_update_ptr(&cpp->defs, decl->token->text, decl);
}

bool psi_cpp_undef(struct psi_cpp *cpp, struct psi_token *tok)
{
	return SUCCESS == zend_hash_del(&cpp->defs, tok->text);
}

bool psi_cpp_if(struct psi_cpp *cpp, struct psi_cpp_exp *exp)
{
	struct psi_validate_scope scope = {0};

	scope.defs = &cpp->defs;
	if (!psi_num_exp_validate(PSI_DATA(cpp->parser), exp->data.num, &scope)) {
		return false;
	}
	if (!psi_num_exp_get_long(exp->data.num, NULL, &cpp->defs)) {
		return false;
	}
	return true;
}

static inline bool try_include(struct psi_cpp *cpp, const char *path, bool *parsed)
{
	struct psi_parser_input *include;

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP include trying %s\n", path);

	include = psi_parser_open_file(cpp->parser, path, false);
	if (include) {
		struct psi_plist *tokens;

		PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP include scanning %s\n", path);

		tokens = psi_parser_scan(cpp->parser, include);
		if (tokens) {
			*parsed = psi_cpp_process(cpp, &tokens);

			if (*parsed) {
				size_t num_tokens = psi_plist_count(tokens);

				++cpp->expanded;
				psi_cpp_tokiter_ins_range(cpp, cpp->index,
						num_tokens, psi_plist_eles(tokens));
				/* skip already processed tokens */
				cpp->index += num_tokens;
				free(tokens);
			} else {
				psi_plist_free(tokens);
			}
		}
		psi_parser_input_free(&include);

		zend_hash_str_add_empty_element(&cpp->once, path, strlen(path));
		return true;
	}
	return false;
}

static inline void include_path(const struct psi_token *file, char **path)
{
	if (file->text->val[0] == '/') {
		*path = file->text->val;
	} else {
		char *dir;
		size_t len;

		strncpy(*path, file->file->val, PATH_MAX);

		dir = dirname(*path);
		len = strlen(dir);

		assert(len + file->text->len + 1 < PATH_MAX);

		memmove(*path, dir, len);
		(*path)[len] = '/';
		memcpy(&(*path)[len + 1], file->text->val, file->text->len + 1);
	}
}

bool psi_cpp_include(struct psi_cpp *cpp, const struct psi_token *file, unsigned flags)
{
	bool parsed = false;

	if (file->type == PSI_T_QUOTED_STRING && (!(flags & PSI_CPP_INCLUDE_NEXT) || file->text->val[0] == '/')) {
		/* first try as is, full or relative path */
		char temp[PATH_MAX], *path = temp;

		include_path(file, &path);

		if ((flags & PSI_CPP_INCLUDE_ONCE) && zend_hash_str_exists(&cpp->once, path, strlen(path))) {
			return true;
		}
		if (try_include(cpp, path, &parsed)) {
			/* found */
			return parsed;
		}
	}

	/* look through search paths */
	if (file->text->val[0] != '/') {
		char path[PATH_MAX];
		const char *sep;
		int p_len;

		if ((flags & PSI_CPP_INCLUDE_NEXT) && cpp->search) {
			if ((sep = strchr(cpp->search, ':'))) {
				cpp->search = sep + 1;
			} else {
				/* point to end of string */
				cpp->search += strlen(cpp->search);
			}
		}

		if (!(flags & PSI_CPP_INCLUDE_NEXT)) {
			cpp->search = PSI_G(search_path);
		}

		do {
			int d_len;

			sep = strchr(cpp->search, ':');
			d_len = sep ? sep - cpp->search : strlen(cpp->search);

			if (PATH_MAX > (p_len = snprintf(path, PATH_MAX, "%.*s/%.*s", d_len, cpp->search, (int) file->text->len, file->text->val))) {
				if ((flags & PSI_CPP_INCLUDE_ONCE) && zend_hash_str_exists(&cpp->once, path, p_len)) {
					return true;
				}
				if (try_include(cpp, path, &parsed)) {
					break;
				}
			}

			if (sep) {
				cpp->search = sep + 1;
			}
		} while (sep);
	}

	return parsed;
}
