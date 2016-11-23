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
#include <stdarg.h>

#include "parser.h"

void *psi_parser_proc_init(void);
void psi_parser_proc_free(void **parser_proc);
void psi_parser_proc_parse(void *parser_proc, token_t r, struct psi_token *token, struct psi_parser *parser);
void psi_parser_proc_trace(FILE *out, char *prefix);

struct psi_parser *psi_parser_init(struct psi_parser *P, psi_error_cb error, unsigned flags)
{
	if (!P) {
		P = malloc(sizeof(*P));
	}
	memset(P, 0, sizeof(*P));

	psi_data_ctor_with_dtors(PSI_DATA(P), error, flags);

	P->col = 1;
	P->line = 1;
	P->proc = psi_parser_proc_init();

	ZEND_INIT_SYMTABLE(&P->cpp.defs);
	zval tmp;
	ZVAL_ARR(&tmp, &P->cpp.defs);
	add_assoc_string(&tmp, "PHP_OS", PHP_OS);

	if (flags & PSI_DEBUG) {
		psi_parser_proc_trace(stderr, "PSI> ");
	}

	return P;
}

bool psi_parser_open_file(struct psi_parser *P, const char *filename)
{
	FILE *fp = fopen(filename, "r");

	if (!fp) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not open '%s' for reading: %s",
				filename, strerror(errno));
		return false;
	}

	P->input.type = PSI_PARSE_FILE;
	P->input.data.file.handle = fp;

#if HAVE_MMAP
	struct stat sb;
	int fd = fileno(fp);

	if (fstat(fd, &sb)) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not stat '%s': %s",
				filename, strerror(errno));
		return false;
	}

	P->input.data.file.buffer = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (MAP_FAILED == P->input.data.file.buffer) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not map '%s' for reading: %s",
				filename, strerror(errno));
		return false;
	}
	P->input.data.file.length = sb.st_size;
#else
	P->input.data.file.buffer = malloc(BSIZE);
#endif

	P->file.fn = strdup(filename);

	return true;
}

bool psi_parser_open_string(struct psi_parser *P, const char *string, size_t length)
{
	P->input.type = PSI_PARSE_STRING;
	P->input.data.string.length = length;
	if (!(P->input.data.string.buffer = strndup(string, length))) {
		return false;
	}

	P->file.fn = strdup("<input>");

	return true;
}

static ssize_t psi_parser_fill(struct psi_parser *P, size_t n)
{
	PSI_DEBUG_PRINT(P, "PSI< Fill: n=%zu (input.type=%d)\n", n, P->input.type);

	/* init if n==0 */
	if (!n) {
		switch (P->input.type) {
		case PSI_PARSE_FILE:
			P->cur = P->tok = P->mrk = P->input.data.file.buffer;
#if HAVE_MMAP
			P->eof = P->input.data.file.buffer + P->input.data.file.length;
			P->lim = P->eof;
#else
			P->eof = NULL;
			P->lim = P->input.data.file.buffer;
#endif
			break;

		case PSI_PARSE_STRING:
			P->cur = P->tok = P->mrk = P->input.data.string.buffer;
			P->eof = P->input.data.string.buffer + P->input.data.string.length;
			P->lim = P->eof;
			break;
		}

		PSI_DEBUG_PRINT(P, "PSI< Fill: cur=%p lim=%p eof=%p\n", P->cur, P->lim, P->eof);
	}

	switch (P->input.type) {
	case PSI_PARSE_STRING:
		break;

	case PSI_PARSE_FILE:
#if !HAVE_MMAP
		if (!P->eof) {
			size_t consumed = P->tok - P->buf;
			size_t reserved = P->lim - P->tok;
			size_t available = BSIZE - reserved;
			size_t didread;

			if (consumed) {
				memmove(P->buf, P->tok, reserved);
				P->tok -= consumed;
				P->cur -= consumed;
				P->lim -= consumed;
				P->mrk -= consumed;
			}

			didread = fread(P->lim, 1, available, P->fp);
			P->lim += didread;
			if (didread < available) {
				P->eof = P->lim;
			}
			PSI_DEBUG_PRINT(P, "PSI< Fill: consumed=%zu reserved=%zu available=%zu didread=%zu\n",
					consumed, reserved, available, didread);
		}
#endif
		break;
	}

	PSI_DEBUG_PRINT(P, "PSI< Fill: avail=%td\n", P->lim - P->cur);

	return P->lim - P->cur;
}

void psi_parser_parse(struct psi_parser *P, struct psi_token *T)
{
	if (T) {
		psi_parser_proc_parse(P->proc, T->type, T, P);
	} else {
		psi_parser_proc_parse(P->proc, 0, NULL, P);
	}
}

void psi_parser_dtor(struct psi_parser *P)
{
	psi_parser_proc_free(&P->proc);

	switch (P->input.type) {
	case PSI_PARSE_FILE:
		if (P->input.data.file.buffer) {
#if HAVE_MMAP
			munmap(P->input.data.file.buffer, P->input.data.file.length);
#else
			free(P->input.data.file.buffer);
#endif
		}
		if (P->input.data.file.handle) {
			fclose(P->input.data.file.handle);
		}
		break;

	case PSI_PARSE_STRING:
		if (P->input.data.string.buffer) {
			free(P->input.data.string.buffer);
		}
		break;
	}

	psi_data_dtor(PSI_DATA(P));

	zend_hash_destroy(&P->cpp.defs);

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

static bool cpp_truth(struct psi_parser *P);
static bool cpp_defined(struct psi_parser *P);
static zval *cpp_define_var(struct psi_parser *P);
static void cpp_define_val(struct psi_parser *P, token_t typ, zval *val);
static void cpp_undefine(struct psi_parser *P);
static void cpp_error(struct psi_parser *P, const char *msg, ...);

/*!max:re2c*/
#if BSIZE < YYMAXFILL
# error BSIZE must be greater than YYMAXFILL
#endif

#define RETURN(t) do { \
	P->num = t; \
	PSI_DEBUG_PRINT(P, "PSI< TOKEN: %d %.*s (EOF=%d %s:%u:%u)\n", \
				P->num, (int) (P->cur-P->tok), P->tok, P->num == PSI_T_EOF, \
				P->file.fn, P->line, P->col); \
	return t; \
} while(1)

#define NEWLINE(label) \
	P->col = 1; \
	++P->line; \
	goto label

token_t psi_parser_scan(struct psi_parser *P)
{
	if (!P->cur) {
		psi_parser_fill(P, 0);
	}
	for (;;) {
		if (P->cpp.skip) {
			/* we might come from EOL, so just go to cpp instead of cpp_skip */
			goto cpp;
		}

		P->col += P->cur - P->tok;

	nextline: ;
		P->tok = P->cur;
		/*!re2c
		re2c:indent:top = 2;
		re2c:define:YYCTYPE = "unsigned char";
		re2c:define:YYCURSOR = P->cur;
		re2c:define:YYLIMIT = P->lim;
		re2c:define:YYMARKER = P->mrk;
		re2c:define:YYFILL = "{ if (!psi_parser_fill(P,@@)) RETURN(PSI_T_EOF); }";
		re2c:yyfill:parameter = 0;

		B = [^a-zA-Z0-9_];
		W = [a-zA-Z0-9_];
		NAME = [a-zA-Z_]W*;
		NSNAME = (NAME)? ("\\" NAME)+;
		DOLLAR_NAME = '$' W+;
		QUOTED_STRING = "\"" ([^\"])+ "\"";
		NUMBER = [+-]? [0-9]* "."? [0-9]+ ([eE] [+-]? [0-9]+)?;

		"#" { --P->cur; goto cpp; }
		"/*" { goto comment; }
		"//" .* "\n" { NEWLINE(nextline); }
		"(" {RETURN(PSI_T_LPAREN);}
		")" {RETURN(PSI_T_RPAREN);}
		";" {RETURN(PSI_T_EOS);}
		"," {RETURN(PSI_T_COMMA);}
		":" {RETURN(PSI_T_COLON);}
		"{" {RETURN(PSI_T_LBRACE);}
		"}" {RETURN(PSI_T_RBRACE);}
		"[" {RETURN(PSI_T_LBRACKET);}
		"]" {RETURN(PSI_T_RBRACKET);}
		"!=" {RETURN(PSI_T_CMP_NE);}
		"==" {RETURN(PSI_T_CMP_EQ);}
		"&&" {RETURN(PSI_T_AND);}
		"||" {RETURN(PSI_T_OR);}
		"=" {RETURN(PSI_T_EQUALS);}
		"*" {RETURN(PSI_T_ASTERISK);}
		"~" {RETURN(PSI_T_TILDE);}
		"!" {RETURN(PSI_T_NOT);}
		"%" {RETURN(PSI_T_MODULO);}
		"&" {RETURN(PSI_T_AMPERSAND);}
		"+" {RETURN(PSI_T_PLUS);}
		"-" {RETURN(PSI_T_MINUS);}
		"/" {RETURN(PSI_T_SLASH);}
		"|" {RETURN(PSI_T_PIPE);}
		"^" {RETURN(PSI_T_CARET);}
		"<<" {RETURN(PSI_T_LSHIFT);}
		">>" {RETURN(PSI_T_RSHIFT);}
		"<=" {RETURN(PSI_T_CMP_LE);}
		">=" {RETURN(PSI_T_CMP_GE);}
		"<" {RETURN(PSI_T_LCHEVR);}
		">" {RETURN(PSI_T_RCHEVR);}
		"..." {RETURN(PSI_T_ELLIPSIS);}
		[\r\n] { NEWLINE(nextline); }
		[\t ]+ { continue; }
		'TRUE' {RETURN(PSI_T_TRUE);}
		'FALSE' {RETURN(PSI_T_FALSE);}
		'NULL' {RETURN(PSI_T_NULL);}
		'MIXED' {RETURN(PSI_T_MIXED);}
		'CALLABLE' {RETURN(PSI_T_CALLABLE);}
		'VOID' {RETURN(PSI_T_VOID);}
		'BOOL' {RETURN(PSI_T_BOOL);}
		'CHAR' {RETURN(PSI_T_CHAR);}
		'SHORT' {RETURN(PSI_T_SHORT);}
		'INT' {RETURN(PSI_T_INT);}
		'LONG' {RETURN(PSI_T_LONG);}
		'FLOAT' {RETURN(PSI_T_FLOAT);}
		'DOUBLE' {RETURN(PSI_T_DOUBLE);}
		'INT8_T' {RETURN(PSI_T_INT8);}
		'UINT8_T' {RETURN(PSI_T_UINT8);}
		'INT16_T' {RETURN(PSI_T_INT16);}
		'UINT16_T' {RETURN(PSI_T_UINT16);}
		'INT32_T' {RETURN(PSI_T_INT32);}
		'UINT32_T' {RETURN(PSI_T_UINT32);}
		'INT64_T' {RETURN(PSI_T_INT64);}
		'UINT64_T' {RETURN(PSI_T_UINT64);}
		'UNSIGNED' {RETURN(PSI_T_UNSIGNED);}
		'SIGNED' {RETURN(PSI_T_SIGNED);}
		'STRING' {RETURN(PSI_T_STRING);}
		'ARRAY' {RETURN(PSI_T_ARRAY);}
		'OBJECT' {RETURN(PSI_T_OBJECT);}
		'CALLBACK' {RETURN(PSI_T_CALLBACK);}
		'STATIC' {RETURN(PSI_T_STATIC);}
		'FUNCTION' {RETURN(PSI_T_FUNCTION);}
		'TYPEDEF' {RETURN(PSI_T_TYPEDEF);}
		'STRUCT' {RETURN(PSI_T_STRUCT);}
		'UNION' {RETURN(PSI_T_UNION);}
		'ENUM' {RETURN(PSI_T_ENUM);}
		'CONST' {RETURN(PSI_T_CONST);}
		'LIB' {RETURN(PSI_T_LIB);}
		'LET' {RETURN(PSI_T_LET);}
		'SET' {RETURN(PSI_T_SET);}
		'PRE_ASSERT' {RETURN(PSI_T_PRE_ASSERT);}
		'POST_ASSERT' {RETURN(PSI_T_POST_ASSERT);}
		'RETURN' {RETURN(PSI_T_RETURN);}
		'FREE' {RETURN(PSI_T_FREE);}
		'TEMP' {RETURN(PSI_T_TEMP);}
		'STRLEN' {RETURN(PSI_T_STRLEN);}
		'STRVAL' {RETURN(PSI_T_STRVAL);}
		'PATHVAL' {RETURN(PSI_T_PATHVAL);}
		'INTVAL' {RETURN(PSI_T_INTVAL);}
		'FLOATVAL' {RETURN(PSI_T_FLOATVAL);}
		'BOOLVAL' {RETURN(PSI_T_BOOLVAL);}
		'ARRVAL' {RETURN(PSI_T_ARRVAL);}
		'OBJVAL' {RETURN(PSI_T_OBJVAL);}
		'ZVAL' {RETURN(PSI_T_ZVAL);}
		'COUNT' {RETURN(PSI_T_COUNT);}
		'CALLOC' {RETURN(PSI_T_CALLOC);}
		'TO_OBJECT' {RETURN(PSI_T_TO_OBJECT);}
		'TO_ARRAY' {RETURN(PSI_T_TO_ARRAY);}
		'TO_STRING' {RETURN(PSI_T_TO_STRING);}
		'TO_INT' {RETURN(PSI_T_TO_INT);}
		'TO_FLOAT' {RETURN(PSI_T_TO_FLOAT);}
		'TO_BOOL' {RETURN(PSI_T_TO_BOOL);}
		NUMBER {RETURN(PSI_T_NUMBER);}
		NAME {RETURN(PSI_T_NAME);}
		NSNAME {RETURN(PSI_T_NSNAME);}
		DOLLAR_NAME {RETURN(PSI_T_DOLLAR_NAME);}
		QUOTED_STRING {RETURN(PSI_T_QUOTED_STRING);}
		[^] {break;}
		*/

	comment: ;
		P->tok = P->cur;
		/*!re2c
		"\n"	{ NEWLINE(comment); }
		"*" "/"	{ continue; }
		[^]		{ goto comment; }
		*/

#define PSI_DEBUG_CPP(P, msg, ...) do { \
	if (PSI_DATA(P)->flags & PSI_DEBUG) { \
		fprintf(stderr, "PSI> CPP %.*s line=%u level=%u skip=%u ", \
				(int) strcspn(P->tok, "\r\n"), P->tok, \
				P->line, P->cpp.level, P->cpp.skip); \
		fprintf(stderr, msg, __VA_ARGS__); \
	} \
} while(0)

	cpp: ;
		P->tok = P->cur;
		/*!re2c
		[\t ] 				{goto cpp;}
		"#" [\t ]* "if"		{ goto cpp_if; }
		"#" [\t ]* "ifdef"	{ goto cpp_ifdef; }
		"#" [\t ]* "ifndef"	{ goto cpp_ifndef; }
		"#" [\t ]* "else"	{ goto cpp_else; }
		"#" [\t ]* "endif"	{ goto cpp_endif; }
		"#" [\t ]* "define"	{ goto cpp_define; }
		"#" [\t ]* "undef"	{ goto cpp_undef; }
		"#" [\t ]* "error"	{ goto cpp_error; }
		[^] 				{ goto cpp_default; }
		*/

	cpp_default: ;
		if (P->cpp.skip) {
			goto cpp_skip;
		} else {
			assert(0);
			break;
		}

	cpp_skip: ;
		P->tok = P->cur;
		/*!re2c
		[\r\n]	{ goto cpp_skip_eol; }
		[^]		{ goto cpp_skip; }
		*/

	cpp_skip_eol:
		PSI_DEBUG_PRINT(P, "PSI> CPP skip line %u\n", P->line);
		NEWLINE(cpp);

	cpp_if: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		++P->cpp.level;

	cpp_if_cont: ;
		if (P->cpp.skip) {
			goto cpp_skip;
		}

		P->tok = P->cur;

		/*!re2c
		[\t ]+								{ goto cpp_if_cont; }
		"!" [\t ]* "defined" [\t ]* "("?	{ goto cpp_ifndef_cont; }
		"defined" [ \t]* "("?				{ goto cpp_ifdef_cont; }
		NAME [\t ]* [\r\n]					{ goto cpp_if_name_eol; }
		[^]									{ goto cpp_if_default;  }
		*/

	cpp_if_default: ;
		cpp_error(P, "PSI syntax error: invalid #if");
		continue;

	cpp_if_name_eol: ;
		if (cpp_truth(P)) {
			NEWLINE(nextline);
		} else {
			P->cpp.skip = P->cpp.level;
			NEWLINE(cpp);
		}

	cpp_ifdef: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		++P->cpp.level;

	cpp_ifdef_cont: ;
		if (P->cpp.skip) {
			goto cpp_skip;
		}

		P->tok = P->cur;

		/*!re2c
		[\t ]+							{ goto cpp_ifdef_cont; }
		NAME [\t ]* ")"? [\t ]* [\r\n]	{ goto cpp_ifdef_name_eol; }
		[^]								{ goto cpp_ifdef_default; }
		*/

	cpp_ifdef_default: ;
		cpp_error(P, "PSI syntax error: invalid #ifdef");
		continue;

	cpp_ifdef_name_eol: ;
		if (cpp_defined(P)) {
			NEWLINE(nextline);
		} else {
			P->cpp.skip = P->cpp.level;
			NEWLINE(cpp);
		}

	cpp_ifndef: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		++P->cpp.level;

	cpp_ifndef_cont:
		if (P->cpp.skip) {
			goto cpp_skip;
		}

		P->tok = P->cur;

		/*!re2c
		[\t ]+							{ goto cpp_ifndef_cont; }
		NAME [\t ]* ")"? [\t ]* [\r\n]	{ goto cpp_ifndef_name_eol; }
		[^]								{ goto cpp_ifndef_default; }
		*/

	cpp_ifndef_default: ;
		cpp_error(P, "PSI syntax error: invalid #ifndef");
		continue;

	cpp_ifndef_name_eol: ;
		if (!cpp_defined(P)) {
			NEWLINE(nextline);
		} else {
			P->cpp.skip = P->cpp.level;
			NEWLINE(cpp_skip);
		}

	cpp_else: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		P->tok = P->cur;

		if (!P->cpp.level) {
			cpp_error(P, "PSI syntax error: ignoring lone #else");
			continue;
		}
		if (!P->cpp.skip) {
			P->cpp.skip = P->cpp.level;
			goto cpp_skip;
		} else if (P->cpp.skip == P->cpp.level) {
			P->cpp.skip = 0;
		}
		continue;

	cpp_endif: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		P->tok = P->cur;
		if (!P->cpp.level) {
			cpp_error(P, "PSI syntax_error: ignoring lone #endif");
			continue;
		} else if (P->cpp.skip == P->cpp.level) {
			P->cpp.skip = 0;
		}
		--P->cpp.level;
		continue;

	cpp_define: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		zval *val = NULL;

		if (P->cpp.skip) {
			goto cpp_skip;
		}

	cpp_define_cont: ;
		P->tok = P->cur;

		/*!re2c
		[\t ]+			{ goto cpp_define_cont; }
		[\r\n]			{ goto cpp_define_eol; }
		NAME			{ goto cpp_define_name; }
		QUOTED_STRING	{ goto cpp_define_quoted_string; }
		NUMBER			{ goto cpp_define_number; }
		[^]				{ goto cpp_define_default; }
		*/

	cpp_define_default: ;
		cpp_error(P, "PSI syntax error: invalid #ifndef");
		continue;

	cpp_define_eol: ;
		if (!val) {
			cpp_error(P, "PSI syntax error: ignoring lone #define");
			continue;
		}
		NEWLINE(nextline);

	cpp_define_name: ;
		if (val) {
			if (Z_TYPE_P(val) != IS_TRUE) {
				cpp_error(P, "PSI syntax error: invalid #define");
				continue;
			}
			cpp_define_val(P, PSI_T_NAME, val);
		} else {
			val = cpp_define_var(P);
		}
		goto cpp_define_cont;

	cpp_define_quoted_string: ;
		if (!val) {
			cpp_error(P, "PSI syntax error: invalid quoted string in #define");
			continue;
		} else {
			cpp_define_val(P, PSI_T_QUOTED_STRING, val);
		}
		goto cpp_define_cont;

	cpp_define_number: ;
		if (!val) {
			cpp_error(P, "PSI syntax error: invalid quoted string in #define");
			continue;
		} else {
			cpp_define_val(P, PSI_T_NUMBER, val);
		}
		goto cpp_define_cont;

	cpp_undef: ;
		PSI_DEBUG_CPP(P, "%s\n", "");

		if (P->cpp.skip) {
			goto cpp_skip;
		}

	cpp_undef_cont: ;
		P->tok = P->cur;

		/*!re2c
		[\t ]+				{ goto cpp_undef_cont; }
		NAME [\t ]* [\r\n]	{ goto cpp_undef_name_eol; }
		[^]					{ goto cpp_undef_default; }
		*/

	cpp_undef_default: ;
		cpp_error(P, "PSI syntax error: invalid #undef");
		continue;

	cpp_undef_name_eol: ;
		cpp_undefine(P);
		NEWLINE(nextline);

	cpp_error: ;
		size_t len = strcspn(P->cur, "\r\n");

		if (P->cpp.skip) {
			P->tok = P->cur + len;
			NEWLINE(cpp_skip);
		} else {
			cpp_error(P, "%.*s", (int) len, P->cur);
			break;
		}
	}
	return -1;
}

#include <ctype.h>

static bool cpp_truth(struct psi_parser *P)
{
	size_t len = P->cur - P->tok;

	while (len && isspace(P->tok[len - 1])) {
		--len;
	}

	zval *val = zend_symtable_str_find(&P->cpp.defs, P->tok, len);
	bool truth = val ? zend_is_true(val) : false;

	PSI_DEBUG_PRINT(P, "PSI> CPP truth(%.*s)=%s\n",
			(int) len, P->tok, truth ? "true" : "false");

	return truth;
}

static bool cpp_defined(struct psi_parser *P)
{
	size_t len = P->cur - P->tok;

	while (len && isspace(P->tok[len - 1])) {
		--len;
	}


	bool defined = zend_symtable_str_exists(&P->cpp.defs, P->tok, len);
	PSI_DEBUG_PRINT(P, "PSI> CPP defined(%.*s)=%s\n",
			(int) len, P->tok, defined ? "true" : "false");
	return defined;
}

static zval *cpp_define_var(struct psi_parser *P)
{
	if (cpp_defined(P)) {
		psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input");
	}
	size_t len = P->cur - P->tok;

	while (len && isspace(P->tok[len - 1])) {
		--len;
	}

	PSI_DEBUG_PRINT(P, "PSI> CPP define %.*s\n", (int) len, P->tok);

	if (zend_symtable_str_exists(&P->cpp.defs, P->tok, len)) {
		cpp_error(P, "Redefinition of %.*s", (int) len, P->tok);
	}

	zval val;
	ZVAL_TRUE(&val);
	return zend_symtable_str_update(&P->cpp.defs, P->tok, len, &val);
}

static void cpp_define_val(struct psi_parser *P, token_t typ, zval *val) {
	size_t len = P->cur - P->tok;

	while (len && isspace(P->tok[len - 1])) {
		--len;
	}

	PSI_DEBUG_PRINT(P, "PSI> define = %.*s\n", (int) len, P->tok);

	switch (typ) {
	case PSI_T_QUOTED_STRING:
		ZVAL_STRINGL(val, P->tok + 1, len - 2);
		break;
	case PSI_T_NUMBER:
		ZVAL_STRINGL(val, P->tok, len);
		convert_scalar_to_number(val);
		break;
	default:
		assert(0);
	}
}

static void cpp_undefine(struct psi_parser *P)
{
	size_t len = P->cur - P->tok;

	while (len && isspace(P->tok[len - 1])) {
		--len;
	}

	zend_symtable_str_del(&P->cpp.defs, P->tok, len);
}

static void cpp_error(struct psi_parser *P, const char *msg, ...)
{
	va_list argv;

	va_start(argv, msg);
	psi_verror(PSI_WARNING, P->file.fn, P->line, msg, argv);
	va_end(argv);
}
