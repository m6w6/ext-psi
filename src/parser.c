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
#include <sys/mman.h>
#include <assert.h>
#include <errno.h>
#include <stdarg.h>

#include <Zend/zend_smart_str.h>

#include "parser.h"

struct psi_parser *psi_parser_init(struct psi_parser *P, psi_error_cb error,
		unsigned flags)
{
	if (!P) {
		P = pemalloc(sizeof(*P), 1);
	}
	memset(P, 0, sizeof(*P));

	psi_data_ctor_with_dtors(PSI_DATA(P), error, flags);

	P->preproc = psi_cpp_init(P);

	return P;
}

struct psi_parser_input *psi_parser_open_file(struct psi_parser *P,
		const char *filename, bool report_errors)
{
	struct stat sb;
	FILE *fp;
	struct psi_parser_input *fb;

	if (stat(filename, &sb)) {
		if (report_errors) {
			P->error(PSI_DATA(P), NULL, PSI_WARNING,
					"Could not stat '%s': %s",
					filename, strerror(errno));
		}
		return NULL;
	}

	if (!(fb = pemalloc(sizeof(*fb) + sb.st_size + psi_parser_maxfill(), 1))) {
		if (report_errors) {
			P->error(PSI_DATA(P), NULL, PSI_WARNING,
					"Could not allocate %zu bytes for reading '%s': %s",
					sb.st_size + psi_parser_maxfill(), filename, strerror(errno));
		}
		return NULL;
	}

	if (!(fp = fopen(filename, "r"))) {
		free(fb);
		if (report_errors) {
			P->error(PSI_DATA(P), NULL, PSI_WARNING,
					"Could not open '%s' for reading: %s",
					filename, strerror(errno));
		}
		return NULL;
	}

	if (sb.st_size != fread(fb->buffer, 1, sb.st_size, fp)) {
		free(fb);
		fclose(fp);
		if (report_errors) {
			P->error(PSI_DATA(P), NULL, PSI_WARNING,
					"Could not read %zu bytes from '%s': %s",
					sb.st_size + psi_parser_maxfill(), filename, strerror(errno));
		}
		return NULL;
	}
	fclose(fp);

	memset(fb->buffer + sb.st_size, 0, psi_parser_maxfill());

	fb->length = sb.st_size;
	fb->file = zend_string_init_interned(filename, strlen(filename), 1);

	return fb;
}

struct psi_parser_input *psi_parser_open_string(struct psi_parser *P,
		const char *string, size_t length)
{
	struct psi_parser_input *sb;

	if (!(sb = pemalloc(sizeof(*sb) + length + psi_parser_maxfill(), 1))) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not allocate %zu bytes: %s",
				length + psi_parser_maxfill(), strerror(errno));
		return NULL;
	}

	memcpy(sb->buffer, string, length);
	memset(sb->buffer + length, 0, psi_parser_maxfill());

	sb->length = length;
	sb->file = zend_string_init_interned("<stdin>", strlen("<stdin>"), 1);

	return sb;
}

struct psi_plist *psi_parser_preprocess(struct psi_parser *P,
		struct psi_plist **tokens)
{
	if (psi_cpp_process(P->preproc, tokens)) {
		return *tokens;
	}
	return NULL;
}

bool psi_parser_process(struct psi_parser *P, struct psi_plist *tokens,
		size_t *processed)
{
	if (psi_plist_count(tokens)) {
		return 0 == psi_parser_proc_parse(P, tokens, processed);
	}
	return true;
}

static inline zend_string *macro_to_constant(struct psi_parser *parser,
		zend_string *name, struct psi_validate_scope *scope)
{
	smart_str str = {0};

	size_t i = 0;
	struct psi_token *tok;

	smart_str_append_printf(&str, "const psi\\%s = ", name->val);
	if (scope->macro->exp) {
		struct psi_dump dump = {{.hn = &str},
				.fun = (psi_dump_cb) smart_str_append_printf};

		psi_num_exp_dump(&dump, scope->macro->exp);
	} else while (psi_plist_get(scope->macro->tokens, i++, &tok)) {
		if (tok->type == PSI_T_QUOTED_STRING) {
			smart_str_appendc(&str, '"');
		}
		smart_str_append(&str, tok->text);
		if (tok->type == PSI_T_QUOTED_STRING) {
			smart_str_appendc(&str, '"');
		}
		smart_str_appendc(&str, ' ');
	}
	smart_str_appendl(&str, ";\n", 2);
	return smart_str_extract(&str);
}

void psi_parser_postprocess(struct psi_parser *P)
{
	unsigned flags;
	zend_string *name;
	struct psi_validate_scope scope = {0};

	psi_validate_scope_ctor(&scope);
	scope.cpp = P->preproc;

	flags = P->flags;
	P->flags |= PSI_SILENT;

	ZEND_HASH_FOREACH_STR_KEY_PTR(&P->preproc->defs, name, scope.macro)
	{
		bool parsed;
		size_t processed = 0;
		struct psi_plist *scanned, *preproc;
		struct psi_parser_input *I;
		zend_string *cnst;

		if (scope.macro->sig) {
			continue;
		} else if (!scope.macro->exp) {
			struct psi_token *tok;
			if (psi_plist_count(scope.macro->tokens) != 1) {
				continue;
			} else if (!psi_plist_get(scope.macro->tokens, 0, &tok)) {
				continue;
			} else if (tok->type != PSI_T_QUOTED_STRING) {
				continue;
			}
		} else if (!psi_num_exp_validate(PSI_DATA(P), scope.macro->exp, &scope)) {
			continue;
		}

		cnst = macro_to_constant(P, name, &scope);
		if (!cnst) {
			continue;
		}
//fprintf(stderr, "PARSE: %s", ZSTR_VAL(cnst));
		I = psi_parser_open_string(P, ZSTR_VAL(cnst), ZSTR_LEN(cnst));
		zend_string_release(cnst);

		if (!(scanned = psi_parser_scan(P, I))) {
			psi_parser_input_free(&I);
			continue;
		}
		psi_parser_input_free(&I);

		if (!(preproc = psi_parser_preprocess(P, &scanned))) {
			psi_plist_free(scanned);
			continue;
		}

		parsed = psi_parser_process(P, preproc, &processed);
		PSI_DEBUG_PRINT(PSI_DATA(P), "PSI: processed=%zu success=%d\n",
				processed, (int) parsed);
		psi_plist_free(preproc);
	}
	ZEND_HASH_FOREACH_END();

	P->flags = flags;

	psi_validate_scope_dtor(&scope);
}

bool psi_parser_parse(struct psi_parser *P, struct psi_parser_input *I)
{
	struct psi_plist *scanned, *preproc;
	size_t processed = 0;

	if (!(scanned = psi_parser_scan(P, I))) {
		return false;
	}

	if (!(preproc = psi_parser_preprocess(P, &scanned))) {
		psi_plist_free(scanned);
		return false;
	}

	if (!psi_parser_process(P, preproc, &processed)) {
		psi_plist_free(preproc);
		return false;
	}

	psi_parser_postprocess(P);

	psi_plist_free(preproc);
	return true;
}

void psi_parser_dtor(struct psi_parser *P)
{
	psi_cpp_free(&P->preproc);
	psi_data_dtor(PSI_DATA(P));

	memset(P, 0, sizeof(*P));
}

void psi_parser_free(struct psi_parser **P)
{
	if (*P) {
		psi_parser_dtor(*P);
		free(*P);
		*P = NULL;
	}
}

