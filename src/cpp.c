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

#include "php_psi.h"

#include <libgen.h>

#include "cpp.h"
#include "parser.h"
#include "debug.h"

#define PSI_CPP_SEARCH
#define PSI_CPP_PREDEF
#include "php_psi_predef.h"

static HashTable psi_cpp_defaults;
static HashTable psi_cpp_pragmas;

typedef bool (*psi_cpp_pragma_func)(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl);

static bool psi_cpp_pragma_once(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	return NULL != zend_hash_add_empty_element(&cpp->once, decl->token->file);
}

static bool psi_cpp_pragma_lib(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	struct psi_token *lib = NULL;
	zend_string *libname;

	if (!psi_plist_get(decl->tokens, 0, &lib)
			|| !lib || lib->type != PSI_T_QUOTED_STRING) {
		return false;
	}

	libname = zend_string_copy(lib->text);
	cpp->parser->file.libnames = psi_plist_add(cpp->parser->file.libnames,
			&libname);
	return true;
}

static bool psi_cpp_pragma_blacklist_decl(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	struct psi_token *name;

	if (!psi_plist_get(decl->tokens, 0, &name)
			|| !name || name->type != PSI_T_QUOTED_STRING) {
		return false;
	}

	psi_blacklist_add_decl(name->text->val, name->text->len);
	return true;
}

static bool psi_cpp_pragma_blacklist_var(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	struct psi_token *name;

	if (!psi_plist_get(decl->tokens, 0, &name)
			|| !name || name->type != PSI_T_QUOTED_STRING) {
		return false;
	}

	psi_blacklist_add_var(name->text->val, name->text->len);
	return true;
}

PHP_MINIT_FUNCTION(psi_cpp);
PHP_MINIT_FUNCTION(psi_cpp)
{
	struct psi_parser parser;
	struct psi_parser_input *predef;

	PSI_G(search_path) = pemalloc(strlen(PSI_G(directory)) + strlen(psi_cpp_search) + 1 + 1, 1);
	sprintf(PSI_G(search_path), "%s:%s", PSI_G(directory), psi_cpp_search);

	if (!psi_parser_init(&parser, psi_error_wrapper, PSI_SILENT)) {
		return FAILURE;
	}

	if (!(predef = psi_parser_open_string(&parser, psi_cpp_predef, sizeof(psi_cpp_predef) - 1))) {
		psi_parser_dtor(&parser);
		return FAILURE;
	}

	if (!psi_parser_parse(&parser, predef)) {
		psi_parser_input_free(&predef);
		psi_parser_dtor(&parser);
		return FAILURE;
	}
	psi_parser_input_free(&predef);

	zend_hash_init(&psi_cpp_defaults, 0, NULL, NULL, 1);
	zend_hash_copy(&psi_cpp_defaults, &parser.preproc->defs, NULL);

	psi_parser_dtor(&parser);

#define PSI_CPP_PRAGMA(name) \
	zend_hash_str_add_ptr(&psi_cpp_pragmas, #name, strlen(#name), psi_cpp_pragma_ ## name)
	zend_hash_init(&psi_cpp_pragmas, 0, NULL, NULL, 1);
	PSI_CPP_PRAGMA(once);
	PSI_CPP_PRAGMA(lib);
	PSI_CPP_PRAGMA(blacklist_decl);
	PSI_CPP_PRAGMA(blacklist_var);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(psi_cpp);
PHP_MSHUTDOWN_FUNCTION(psi_cpp)
{
	struct psi_cpp_macro_decl *macro;

	ZEND_HASH_FOREACH_PTR(&psi_cpp_defaults, macro)
	{
		psi_cpp_macro_decl_free(&macro);
	}
	ZEND_HASH_FOREACH_END();

	zend_hash_destroy(&psi_cpp_defaults);

	return SUCCESS;
}

static void free_cpp_def(zval *p)
{
	if (Z_TYPE_P(p) == IS_PTR) {
		struct psi_cpp_macro_decl *macro = Z_PTR_P(p);

		if (!zend_hash_exists(&psi_cpp_defaults, macro->token->text)) {
			psi_cpp_macro_decl_free(&macro);
		}
	}
}

struct psi_cpp *psi_cpp_init(struct psi_parser *P)
{
	struct psi_cpp *cpp = pecalloc(1, sizeof(*cpp), 1);

	cpp->parser = P;
	zend_hash_init(&cpp->once, 0, NULL, NULL, 1);
	zend_hash_init(&cpp->defs, 0, NULL, free_cpp_def, 1);
	zend_hash_copy(&cpp->defs, &psi_cpp_defaults, NULL);
	zend_hash_init(&cpp->expanding, 0, NULL, NULL, 1);

	return cpp;
}

static char *include_flavor[] = {
		"include",
		"include next",
		"include once"
};

void psi_cpp_free(struct psi_cpp **cpp_ptr)
{
	if (*cpp_ptr) {
		struct psi_cpp *cpp = *cpp_ptr;

		*cpp_ptr = NULL;
		zend_hash_destroy(&cpp->defs);
		zend_hash_destroy(&cpp->once);
		zend_hash_destroy(&cpp->expanding);
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
				psi_cpp_tokiter_del_prev(cpp, true);
				psi_cpp_tokiter_del_cur(cpp, true);
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
					no_ws->text = psi_string_init_interned("\xA0", 1, 1);
					psi_cpp_tokiter_add(cpp, no_ws);
					continue;
				}
			}
			/* no break */
		default:
			name = define = hash = eol = false;
			break;
		}

		ws = false;
		psi_cpp_tokiter_add_cur(cpp);
		psi_cpp_tokiter_next(cpp);
	}

	return true;
}

static bool psi_cpp_stage2(struct psi_cpp *cpp)
{
	bool is_eol = true, do_expansion = true, skip_paren = false, skip_all = false;

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s\n", "stage2");

	psi_cpp_tokiter_reset(cpp);
	while (psi_cpp_tokiter_valid(cpp)) {
		struct psi_token *current = psi_cpp_tokiter_current(cpp);

		if (current->type == PSI_T_HASH) {
			if (is_eol) {
				cpp->do_cpp = true;
				is_eol = false;
			}
		} else if (current->type == PSI_T_EOL) {
#if PSI_CPP_DEBUG
			PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP do_expansion=true, PSI_T_EOL\n");
#endif
			is_eol = true;
			skip_all = false;
			do_expansion = true;
			if (!cpp->do_cpp) {
				psi_cpp_tokiter_del_cur(cpp, true);
				continue;
			}
		} else {
			is_eol = false;

			if (cpp->do_cpp) {
				switch (current->type) {
				case PSI_T_DEFINE:
#if PSI_CPP_DEBUG
					PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP do_expansion=false, PSI_T_DEFINE, skip_all\n");
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
					PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP do_expansion=false, PSI_T_{IF{,N},UN}DEF\n");
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
							PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP do_expansion=true, PSI_T_LPAREN, !skip_all, !skip_paren\n");
#endif
						}
					}
					break;
				case PSI_T_NAME:
					break;
				default:
					do_expansion = !skip_all;
#if PSI_CPP_DEBUG
					PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP do_expansion=%s, <- !skip_all\n", do_expansion?"true":"false");
#endif
				}
			}
		}

		if (cpp->skip) {
			if (!cpp->do_cpp) {
#if PSI_CPP_DEBUG
				PSI_DEBUG_LOCK(cpp->parser,
					PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP skip ");
					PSI_DEBUG_DUMP(cpp->parser, psi_token_dump, current);
				);
#endif
				psi_cpp_tokiter_del_cur(cpp, true);
				continue;
			}
		}

		if (do_expansion && psi_cpp_defined(cpp, current)) {
			if (psi_cpp_tokiter_expand(cpp)) {
				continue;
			}
		}

		psi_cpp_tokiter_add_cur(cpp);

		if (cpp->do_cpp && is_eol) {
			size_t processed = 0;
			bool parsed;

			cpp->do_cpp = false;
			parsed = psi_parser_process(cpp->parser, cpp->tokens.exec, &processed);
			psi_plist_clean(cpp->tokens.exec);

			if (!parsed) {
				psi_plist_free(cpp->tokens.exec);
				return false;
			}

#if PSI_CPP_DEBUG > 1
			PSI_DEBUG_DUMP(cpp->parser, psi_cpp_tokiter_dump, cpp);
#endif
		}

		psi_cpp_tokiter_next(cpp);
	}

	psi_plist_free(cpp->tokens.exec);
	cpp->tokens.exec = NULL;

	return true;
}

bool psi_cpp_process(struct psi_cpp *cpp, struct psi_plist **tokens,
		struct psi_token *expanding)
{
	bool parsed = false;
	struct psi_cpp temp = *cpp;

	cpp->tokens.iter = *tokens;
	cpp->tokens.next = NULL;
	cpp->tokens.exec = NULL;

	if (expanding) {
		zend_hash_add_empty_element(&cpp->expanding, expanding->text);
	}
	if (psi_cpp_stage1(cpp) && psi_cpp_stage2(cpp)) {
		parsed = true;
	}
	if (expanding) {
		zend_hash_del(&cpp->expanding, expanding->text);
	}

	*tokens = cpp->tokens.next;
	psi_plist_free(cpp->tokens.iter);
	if (cpp->tokens.exec) {
		assert(!psi_plist_count(cpp->tokens.exec));
		psi_plist_free(cpp->tokens.exec);
	}

	cpp->tokens = temp.tokens;
	cpp->index = temp.index;
	cpp->skip = temp.skip;
	cpp->level = temp.level;
	cpp->seen = temp.seen;
	cpp->do_cpp = temp.do_cpp;

	return parsed;
}

bool psi_cpp_defined(struct psi_cpp *cpp, struct psi_token *tok)
{
	bool defined = false;

	if (tok->type == PSI_T_NAME) {
		if (psi_builtin_exists(tok->text)) {
			defined = true;
		} else if (!zend_hash_exists(&cpp->expanding, tok->text)) {
			defined = zend_hash_exists(&cpp->defs, tok->text);
		}
#if PSI_CPP_DEBUG
		PSI_DEBUG_LOCK(cpp->parser,
				PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP defined -> %s ", defined ? "true" : "false");
				if (defined) {
					struct psi_cpp_macro_decl *macro = zend_hash_find_ptr(&cpp->defs, tok->text);
					if (macro) {
						PSI_DEBUG_PRINT(cpp->parser, " @ %s:%u ", macro->token->file->val, macro->token->line);
					}
				} else {
					zend_string *key;

					PSI_DEBUG_PRINT(cpp->parser, " expanding=");
					ZEND_HASH_FOREACH_STR_KEY(&cpp->expanding, key)
					{
						PSI_DEBUG_PRINT(cpp->parser, "%s,", key->val);
					}
					ZEND_HASH_FOREACH_END();
					PSI_DEBUG_PRINT(cpp->parser, "\t");
				}
				PSI_DEBUG_DUMP(cpp->parser, psi_token_dump, tok);
		);
#endif
	}

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
	PSI_DEBUG_LOCK(cpp->parser,
			if (decl->exp) {
				PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP MACRO num_exp -> ");
			} else {
				PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP MACRO decl    -> ");
			}
			PSI_DEBUG_DUMP(cpp->parser, psi_cpp_macro_decl_dump, decl);
			PSI_DEBUG_PRINT(cpp->parser, "\n");
	);
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
	unsigned flags = cpp->parser->flags;

	scope.cpp = cpp;
	cpp->parser->flags |= PSI_SILENT;
	if (!psi_num_exp_validate(PSI_DATA(cpp->parser), exp->data.num, &scope)) {
		cpp->parser->flags = flags;
		return false;
	}
	cpp->parser->flags = flags;
	if (!psi_num_exp_get_long(exp->data.num, NULL, cpp)) {
		return false;
	}
	return true;
}

bool psi_cpp_pragma(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl)
{
	psi_cpp_pragma_func fn;

	fn = zend_hash_find_ptr(&psi_cpp_pragmas, decl->token->text);
	if (!fn) {
		return false;
	}

	return fn(cpp, decl);
}

bool psi_cpp_include(struct psi_cpp *cpp, const struct psi_token *file, unsigned flags)
{
	bool parsed = false;
	char path[PATH_MAX];
	struct psi_plist *tokens;
	struct psi_parser_input *include;

	if (!psi_cpp_has_include(cpp, file, flags, path)) {
		return false;
	}

	if (flags & PSI_CPP_INCLUDE_ONCE) {
		if (zend_hash_str_exists(&cpp->once, path, strlen(path))) {
			return true;
		}
	}

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s opening %s\n",
			include_flavor[flags], path);

	include = psi_parser_open_file(cpp->parser, path, false);
	if (!include) {
		return false;
	}

	zend_hash_str_add_empty_element(&cpp->once, path, strlen(path));

	PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP include scanning %s\n", path);

	tokens = psi_parser_scan(cpp->parser, include);
	psi_parser_input_free(&include);

	if (!tokens) {
		return false;
	}

	++cpp->include_level;
	parsed = psi_cpp_process(cpp, &tokens, NULL);
	--cpp->include_level;

	if (!parsed) {
		psi_plist_free(tokens);
		return false;
	}

	psi_cpp_tokiter_add_range(cpp, psi_plist_count(tokens), psi_plist_eles(tokens));
	free(tokens);

	++cpp->expanded;
	return true;
}

#ifndef HAVE_EACCESS
#	define eaccess access
#endif
bool psi_cpp_has_include(struct psi_cpp *cpp, const struct psi_token *file, unsigned flags, char *path)
{
	char temp[PATH_MAX];

	if (!path) {
		path = temp;
	}

	if (file->type == PSI_T_QUOTED_STRING && (!(flags & PSI_CPP_INCLUDE_NEXT) || file->text->val[0] == '/')) {
		/* first try as is, full or relative path */
		if (file->text->val[0] == '/') {
			path = file->text->val;
		} else {
			char *dir;
			size_t len;

			strncpy(path, file->file->val, PATH_MAX);

			dir = dirname(path);
			len = strlen(dir);

			assert(len + file->text->len + 1 < PATH_MAX);

			memmove(path, dir, len);
			path[len] = '/';
			memcpy(&(path)[len + 1], file->text->val, file->text->len + 1);
		}

		PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s trying %s\n",
				include_flavor[flags], path);
		if (0 == eaccess(path, R_OK)) {
			return true;
		}
	}

	/* look through search paths */
	if (file->text->val[0] != '/') {
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
				PSI_DEBUG_PRINT(cpp->parser, "PSI: CPP %s trying %s\n",
						include_flavor[flags], path);
				if (0 == eaccess(path, R_OK)) {
					 return true;
				 }
			}

			if (sep) {
				cpp->search = sep + 1;
			}
		} while (sep);
	}

	return false;
}
