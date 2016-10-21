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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <sys/param.h>

#include "parser_proc.h"
#include "token.h"
#include "parser.h"

size_t psi_token_alloc_size(size_t token_len, size_t fname_len) {
	return sizeof(struct psi_token) + token_len + fname_len + 2;
}

struct psi_token *psi_token_alloc(struct psi_parser *P) {
	struct psi_token *T;
	size_t token_len, fname_len;
	token_t token_typ;

	if (P->cur < P->tok) {
		return NULL;
	}

	token_typ = P->num;
	token_len = P->cur - P->tok;
	fname_len = strlen(P->psi.file.fn);

	T = calloc(1, psi_token_alloc_size(token_len, fname_len));
	T->type = token_typ;
	T->size = token_len;
	T->text = &T->buf[0];
	T->file = &T->buf[token_len + 1];
	T->line = P->line;
	T->col = P->col;

	memcpy(T->text, P->tok, token_len);
	memcpy(T->file, P->psi.file.fn, fname_len);

	return T;
}

struct psi_token *psi_token_copy(struct psi_token *src) {
	size_t strct_len = psi_token_alloc_size(src->size, strlen(src->file));
	struct psi_token *ptr = malloc(strct_len);

	memcpy(ptr, src, strct_len);

	ptr->text = &ptr->buf[0];
	ptr->file = &ptr->buf[ptr->size + 1];

	return ptr;
}

struct psi_token *psi_token_cat(unsigned argc, ...) {
	va_list argv;
	unsigned i;
	struct psi_token *T = NULL;

	va_start(argv, argc);
	for (i = 0; i < argc; ++i) {
		struct psi_token *arg = va_arg(argv, struct psi_token *);

		if (T) {
			size_t token_len = T->size, fname_len = strlen(T->file);
			struct psi_token *tmp = realloc(T, psi_token_alloc_size(T->size += arg->size + 1, fname_len));

			if (tmp) {
				T = tmp;
			} else {
				free(T);
				va_end(argv);
				return NULL;
			}

			T->text = &T->buf[0];
			T->file = &T->buf[T->size + 1];
			T->buf[token_len] = ' ';
			memmove(&T->buf[T->size + 1], &T->buf[token_len + 1], fname_len + 1);
			memcpy(&T->buf[token_len + 1], arg->text, arg->size + 1);
		} else {
			T = psi_token_copy(arg);
			T->type = PSI_T_NAME;
		}
	}
	va_end(argv);

	return T;
}

struct psi_token *psi_token_append(struct psi_token *T, unsigned argc, ...) {
	va_list argv;
	unsigned i;

	va_start(argv, argc);
	for (i = 0; i < argc; ++i) {
		char *str = va_arg(argv, char *);
		size_t str_len = strlen(str), token_len = T->size, fname_len = strlen(T->file);

		T = realloc(T, psi_token_alloc_size(T->size += str_len + 1, fname_len));
		T->text = &T->buf[0];
		T->file = &T->buf[T->size + 1];
		T->buf[token_len] = ' ';
		memmove(&T->buf[T->size + 1], &T->buf[token_len + 1], fname_len + 1);
		memcpy(&T->buf[token_len + 1], str, str_len + 1);
	}
	va_end(argv);

	return T;
}

char *php_strtr(char *str, size_t len, char *str_from, char *str_to, size_t trlen);
struct psi_token *psi_token_translit(struct psi_token *T, char *from, char *to) {
	php_strtr(T->text, T->size, from, to, MIN(strlen(from), strlen(to)));
	return T;
}

static inline uint64_t psi_hash(char *digest_buf, ...)
{
	uint64_t hash = 5381;
	uint8_t c;
	const uint8_t *ptr;
	va_list argv;

	va_start(argv, digest_buf);
	while ((ptr = va_arg(argv, const uint8_t *))) {
		while ((c = *ptr++)) {
			hash = ((hash << 5) + hash) + c;
		}
	}
	va_end(argv);

	if (digest_buf) {
		sprintf(digest_buf, "%" PRIx64, hash);
	}

	return hash;
}

uint64_t psi_token_hash(struct psi_token *t, char *digest_buf) {
	char loc_buf[48];

	sprintf(loc_buf, "%u%u", t->line, t->col);
	return psi_hash(digest_buf, t->file, loc_buf, (char *) NULL);
}
