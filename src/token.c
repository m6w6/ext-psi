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

#include "php_psi_stdinc.h"

#include <ctype.h>

#include <Zend/zend_smart_str.h>

#include "token.h"
#include "parser.h"

size_t psi_token_alloc_size(size_t token_len, size_t fname_len) {
	return sizeof(struct psi_token) + token_len + fname_len + 2;
}

struct psi_token *psi_token_init(token_t token_typ, const char *token_txt,
		size_t token_len, unsigned col, unsigned line, zend_string *file)
{
	struct psi_token *T;

	T = calloc(1, sizeof(*T));
	T->type = token_typ;
	T->col = col;
	T->line = line;
	T->file = zend_string_copy(file);
	T->text = zend_string_init(token_txt, token_len, 1);

	return T;
}

void psi_token_free(struct psi_token **token_ptr) {
	if (*token_ptr) {
		struct psi_token *token = *token_ptr;

		*token_ptr = NULL;
		zend_string_release(token->text);
		zend_string_release(token->file);
		free(token);
	}
}

struct psi_token *psi_token_copy(struct psi_token *src) {
	struct psi_token *ptr = malloc(sizeof(*ptr));

	*ptr = *src;

	ptr->text = zend_string_copy(ptr->text);
	ptr->file = zend_string_copy(ptr->file);

	return ptr;
}

void psi_token_copy_ctor(struct psi_token **tok) {
	*tok = psi_token_copy(*tok);
}

/* concatenate `argc` number of tokens separated by `sep` into a newly allocated token */
struct psi_token *psi_token_cat(const char *sep, unsigned argc, ...) {
	va_list argv;
	unsigned i;
	size_t sep_len = sep ? strlen(sep) : 0;
	struct psi_token *T = malloc(sizeof(*T));
	smart_str text = {0};

	va_start(argv, argc);

	*T = *(struct psi_token *) va_arg(argv, struct psi_token *);
	T->type = PSI_T_NAME;
	T->file = zend_string_copy(T->file);

	smart_str_append_ex(&text, T->text, 1);

	for (i = 1; i < argc; ++i) {
		struct psi_token *arg = va_arg(argv, struct psi_token *);

		smart_str_appendl_ex(&text, sep, sep_len, 1);
		smart_str_append_ex(&text, arg->text, 1);
	}
	va_end(argv);

	T->text = smart_str_extract(&text);

	return T;
}

/* append `argc` number of C strings separated by `sep` to token `T` */
struct psi_token *psi_token_append(const char *sep, struct psi_token *T, unsigned argc, ...) {
	va_list argv;
	unsigned i;
	size_t sep_len = sep ? strlen(sep) : 0;
	smart_str text = {0};

	smart_str_append_ex(&text, T->text, 1);

	va_start(argv, argc);
	for (i = 0; i < argc; ++i) {
		char *str = va_arg(argv, char *);
		size_t str_len = strlen(str);

		if (sep_len && text.a) {
			smart_str_appendl_ex(&text, sep, sep_len, 1);
		}

		smart_str_appendl_ex(&text, str, str_len, 1);
	}
	va_end(argv);

	zend_string_release(T->text);
	T->text = smart_str_extract(&text);

	return T;
}

char *php_strtr(char *str, size_t len, char *str_from, char *str_to, size_t trlen);
struct psi_token *psi_token_translit(struct psi_token *T, char *from, char *to) {
	zend_string *tmp = zend_string_init(T->text->val, T->text->len, 1);

	zend_string_release(T->text);
	T->text = tmp;

	php_strtr(T->text->val, T->text->len, from, to, MIN(strlen(from), strlen(to)));
	zend_string_forget_hash_val(T->text);

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
	return psi_hash(digest_buf, t->file->val, loc_buf, (char *) NULL);
}

void psi_token_dump(int fd, struct psi_token *t)
{
	size_t i;

	dprintf(fd, "TOKEN %p (%u) ", t, t->type);
	if (t->type == PSI_T_EOF) {
		dprintf(fd, "EOF");
	} else {
		dprintf(fd, "\"");
		for (i = 0; i < t->text->len; ++i) {
			switch (t->text->val[i]) {
			case '\0':
				dprintf(fd, "\\0");
				break;
			case '\a':
				dprintf(fd, "\\a");
				break;
			case '\b':
				dprintf(fd, "\\b");
				break;
			case '\f':
				dprintf(fd, "\\f");
				break;
			case '\n':
				dprintf(fd, "\\n");
				break;
			case '\r':
				dprintf(fd, "\\r");
				break;
			case '\t':
				dprintf(fd, "\\t");
				break;
			case '\v':
				dprintf(fd, "\\v");
				break;
			case '"':
				dprintf(fd, "\\\"");
				break;
			default:
				if (isprint(t->text->val[i])) {
					dprintf(fd, "%c", t->text->val[i]);
				} else {
					dprintf(fd, "\\x%02hhX", t->text->val[i]);
				}
				break;
			}
		}
		dprintf(fd, "\"");
	}
	dprintf(fd, " at col %u in %s on line %u\n", t->col, t->file->val, t->line);
}
