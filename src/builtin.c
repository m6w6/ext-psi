/*******************************************************************************
 Copyright (c) 2018, Michael Wallner <mike@php.net>.
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

#include "php_psi.h"
#include "builtin.h"
#include "parser.h"
#include "cpp.h"

#include <stdarg.h>

HashTable psi_builtins;

static bool has_include(struct psi_cpp *cpp, struct psi_token *target, struct psi_plist **args, struct psi_plist **res);
static bool has_include_next(struct psi_cpp *cpp, struct psi_token *target, struct psi_plist **args, struct psi_plist **res);
static bool has_feature(struct psi_cpp *cpp, struct psi_token *target, struct psi_plist **args, struct psi_plist **res);
static bool builtin_constant_p(struct psi_cpp *cpp, struct psi_token *target, struct psi_plist **args, struct psi_plist **res);
static bool COUNTER__(struct psi_cpp *cpp, struct psi_token *target, struct psi_plist **args, struct psi_plist **res);

static inline struct psi_plist *builtin_sig(token_t typ, ...)
{
	struct psi_plist *sig;
	size_t n = 0;
	va_list args;

	if (typ == (token_t) - 1) {
		return NULL;
	}

	sig  = psi_plist_init((psi_plist_dtor) psi_token_free);
	va_start(args, typ);
	while (typ) {
		char a = 'a' + n++;
		struct psi_token *arg;

		arg = psi_token_init(typ, &a, 1, 0, 0, zend_empty_string);
		sig = psi_plist_add(sig, &arg);
		typ = va_arg(args, token_t);
	}
	va_end(args);

	return sig;
}

static void free_builtin(zval *p)
{
	struct psi_builtin *b = Z_PTR_P(p);

	if (b) {
		zend_string_release(b->name);
		psi_cpp_macro_decl_free(&b->decl);
		pefree(b, 1);
	}
}

PHP_MINIT_FUNCTION(psi_builtin)
{
#define PSI_BUILTIN(builtin, ...) do { \
	struct psi_builtin entry; \
	struct psi_plist *sig = builtin_sig(__VA_ARGS__, 0); \
	struct psi_cpp_macro_decl *decl = psi_cpp_macro_decl_init(sig, NULL, NULL); \
	decl->token = psi_token_init(PSI_T_NAME, "__" #builtin, sizeof("__" #builtin)-1, \
		0, 0, zend_empty_string); \
	entry.name = zend_string_copy(decl->token->text); \
	entry.func = &builtin; \
	entry.decl = decl; \
	zend_hash_add_mem(&psi_builtins, entry.name, &entry, sizeof(entry)); \
} while(0)

	zend_hash_init(&psi_builtins, 0, NULL, free_builtin, 1);
	PSI_BUILTIN(has_include, PSI_T_CPP_HEADER);
	PSI_BUILTIN(has_include_next, PSI_T_CPP_HEADER);
	PSI_BUILTIN(has_feature, PSI_T_NAME);
	PSI_BUILTIN(builtin_constant_p, PSI_T_NAME);

	PSI_BUILTIN(COUNTER__, -1);

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(psi_builtin)
{
	zend_hash_destroy(&psi_builtins);
	return SUCCESS;
}

bool psi_builtin_exists(zend_string *name)
{
	return zend_hash_exists(&psi_builtins, name);
}

struct psi_builtin *psi_builtin_get(zend_string *name)
{
	return zend_hash_find_ptr(&psi_builtins, name);
}

static bool has_include(struct psi_cpp *cpp, struct psi_token *target,
		struct psi_plist **args, struct psi_plist **res)
{
	struct psi_plist *arg = args[0];
	struct psi_token *tok;

	switch (psi_plist_count(arg)) {
	case 1:
		if (psi_plist_get(arg, 0, &tok)) {
			const char *cpp_search = cpp->search;
			bool has = psi_cpp_has_include(cpp, tok, 0, NULL);
			cpp->search = cpp_search;
			return has;
		}
		/* no break */
	default:
		cpp->parser->error(PSI_DATA(cpp->parser), target, PSI_WARNING,
				"Erroneous usage of builtin __%s", __FUNCTION__);
	}
	return false;
}

static bool has_include_next(struct psi_cpp *cpp, struct psi_token *target,
		struct psi_plist **args, struct psi_plist **res)
{
	struct psi_plist *arg = args[0];
	struct psi_token *tok;

	switch (psi_plist_count(arg)) {
	case 1:
		if (psi_plist_get(arg, 0, &tok)) {
			const char *cpp_search = cpp->search;
			bool has = psi_cpp_has_include(cpp, tok, PSI_CPP_INCLUDE_NEXT, NULL);
			cpp->search = cpp_search;
			return has;
		}
		/* no break */
	default:
		cpp->parser->error(PSI_DATA(cpp->parser), target, PSI_WARNING,
				"Erroneous usage of builtin __%s", __FUNCTION__);
	}
	return false;
}

static bool has_feature(struct psi_cpp *cpp, struct psi_token *target,
		struct psi_plist **args, struct psi_plist **res_ptr)
{
	return false;
}

static bool builtin_constant_p(struct psi_cpp *cpp, struct psi_token *target,
		struct psi_plist **args, struct psi_plist **res_ptr)
{
	/* we want functions, not macros for e.g. htonl() */
	return false;
}

static bool COUNTER__(struct psi_cpp *cpp, struct psi_token *target,
		struct psi_plist **args, struct psi_plist **res)
{
	struct psi_token *tok;
	char buf[0x20];
	size_t len = sprintf(buf, "%u", cpp->counter++);

	tok = psi_token_init(PSI_T_NUMBER, buf, len, target->col, target->line, target->file);
	*res = psi_plist_init((psi_plist_dtor) psi_token_free);
	*res = psi_plist_add(*res, &tok);

	return true;
}

#ifdef __APPLE__
#include <libkern/OSByteOrder.h>
# define bswap_16(u) _OSSwapInt16(u)
# define bswap_32(u) _OSSwapInt32(u)
# define bswap_64(u) _OSSwapInt64(u)
#elif defined(__FreeBSD__)
# include <sys/endian.h>
# define bswap_16(u) bswap16(u)
# define bswap_32(u) bswap32(u)
# define bswap_64(u) bswap64(u)
#elif defined(__OpenBSD__)
# include <sys/types.h>
# define bswap_16(u) swap16(u)
# define bswap_32(u) swap32(u)
# define bswap_64(u) swap64(u)
#elif defined(__NetBSD__)
# include <sys/types.h>
# include <machine/bswap.h>
# define bswap_16(u) bswap16(u)
# define bswap_32(u) bswap32(u)
# define bswap_64(u) bswap64(u)
#else
# include <byteswap.h>
#endif

uint16_t psi_swap16(uint16_t u)
{
	return bswap_16(u);
}

uint32_t psi_swap32(uint32_t u)
{
	return bswap_32(u);
}

uint64_t psi_swap64(uint64_t u)
{
	return bswap_64(u);
}
