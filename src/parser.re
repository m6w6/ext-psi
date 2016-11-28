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

/*!max:re2c*/
#ifndef YYMAXFILL
# define YYMAXFILL 256
#endif
/*!re2c

re2c:indent:top = 2;
re2c:define:YYCTYPE = "unsigned char";
re2c:define:YYCURSOR = P->cur;
re2c:define:YYLIMIT = P->lim;
re2c:define:YYMARKER = P->mrk;
re2c:define:YYFILL = "if (P->cur >= P->lim) goto done;";
re2c:yyfill:parameter = 0;

B = [^a-zA-Z0-9_];
W = [a-zA-Z0-9_];
SP = [ \t];
EOL = [\r\n];
NAME = [a-zA-Z_]W*;
NSNAME = (NAME)? ("\\" NAME)+;
DOLLAR_NAME = '$' W+;
QUOTED_STRING = "\"" ([^"])+ "\"";
NUMBER = [+-]? [0-9]* "."? [0-9]+ ([eE] [+-]? [0-9]+)?;

*/

static void free_cpp_def(zval *p)
{
	if (Z_TYPE_P(p) == IS_PTR) {
		psi_cpp_macro_decl_free((void *) &Z_PTR_P(p));
	} else if (Z_REFCOUNTED_P(p)) {
		zval_ptr_dtor(p);
	}
}

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

	zend_hash_init(&P->cpp.defs, 0, NULL, free_cpp_def, 1);
	zval tmp;
	ZVAL_ARR(&tmp, &P->cpp.defs);
	add_assoc_string(&tmp, "PHP_OS", PHP_OS);

	if (flags & PSI_DEBUG) {
		psi_parser_proc_trace(stderr, "PSI> ");
	}

	return P;
}

void psi_parser_reset(struct psi_parser *P)
{
	P->cur = P->tok = P->mrk = P->input.buffer;
	P->lim = P->input.buffer + P->input.length;
}

bool psi_parser_open_file(struct psi_parser *P, const char *filename)
{
	struct stat sb;
	FILE *fp;
	char *fb;

	if (stat(filename, &sb)) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not stat '%s': %s",
				filename, strerror(errno));
		return false;
	}

	if (!(fb = malloc(sb.st_size + YYMAXFILL))) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not allocate %zu bytes for reading '%s': %s",
				sb.st_size + YYMAXFILL, filename, strerror(errno));
		return false;
	}

	if (!(fp = fopen(filename, "r"))) {
		free(fb);
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not open '%s' for reading: %s",
				filename, strerror(errno));
		return false;
	}

	if (sb.st_size != fread(fb, 1, sb.st_size, fp)) {
		free(fb);
		fclose(fp);
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not read %zu bytes from '%s': %s",
				sb.st_size + YYMAXFILL, filename, strerror(errno));
		return false;
	}
	memset(fb + sb.st_size, 0, YYMAXFILL);

	if (P->input.buffer) {
		free(P->input.buffer);
	}
	P->input.buffer = fb;
	P->input.length = sb.st_size;

	P->file.fn = strdup(filename);

	psi_parser_reset(P);

	return true;
}

bool psi_parser_open_string(struct psi_parser *P, const char *string, size_t length)
{
	char *sb;

	if (!(sb = malloc(length + YYMAXFILL))) {
		P->error(PSI_DATA(P), NULL, PSI_WARNING,
				"Could not allocate %zu bytes: %s",
				length + YYMAXFILL, strerror(errno));
		return false;
	}

	memcpy(sb, string, length);
	memset(sb + length, 0, YYMAXFILL);

	if (P->input.buffer) {
		free(P->input.buffer);
	}
	P->input.buffer = sb;
	P->input.length = length;

	P->file.fn = strdup("<input>");

	psi_parser_reset(P);

	return true;
}

#if 0
static void psi_parser_register_constants(struct psi_parser *P)
{
	zend_string *key;
	zval *val;

	ZEND_HASH_FOREACH_STR_KEY_VAL(&P->cpp.defs, key, val)
	{
		struct psi_impl_def_val *iv;
		struct psi_const_type *ct;
		struct psi_const *c;
		const char *ctn;
		token_t ctt;
		impl_val tmp;
		zend_string *str;

		ZVAL_DEREF(val);
		switch (Z_TYPE_P(val)) {
		case IS_TRUE:
		case IS_FALSE:
			ctt = PSI_T_BOOL;
			ctn = "bool";
			tmp.zend.bval = Z_TYPE_P(val) == IS_TRUE;
			break;
		case IS_LONG:
			ctt = PSI_T_INT;
			ctn = "int";
			tmp.zend.lval = Z_LVAL_P(val);
			break;
		case IS_DOUBLE:
			ctt = PSI_T_FLOAT;
			ctn = "float";
			tmp.dval = Z_DVAL_P(val);
			break;
		default:
			ctt = PSI_T_STRING;
			ctn = "string";
			str = zval_get_string(val);
			tmp.zend.str = zend_string_dup(str, 1);
			zend_string_release(str);
			break;
		}

		iv = psi_impl_def_val_init(ctt, NULL);
		iv->ival = tmp;
		ct = psi_const_type_init(ctt, ctn);
		c = psi_const_init(ct, key->val, iv);
		if (!P->consts) {
			P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
		}
		P->consts = psi_plist_add(P->consts, &c);
	}
	ZEND_HASH_FOREACH_END();
}
#endif

void psi_parser_parse(struct psi_parser *P)
{
	size_t i = 0;
	struct psi_token *T;

	P->cpp.tokens = psi_parser_scan(P);

	psi_cpp_preprocess(P, &P->cpp);

	if (psi_plist_count(P->cpp.tokens)) {
		while (psi_plist_get(P->cpp.tokens, i++, &T)) {
			if (P->flags & PSI_DEBUG) {
				fprintf(stderr, "PSI> ");
				psi_token_dump(2, T);
			}
			psi_parser_proc_parse(P->proc, T->type, T, P);
		}
		psi_parser_proc_parse(P->proc, 0, NULL, P);
	}

	psi_plist_free(P->cpp.tokens);
	P->cpp.tokens = NULL;
}

void psi_parser_dtor(struct psi_parser *P)
{
	psi_parser_proc_free(&P->proc);

	if (P->input.buffer) {
		free(P->input.buffer);
		P->input.buffer = NULL;
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

#define NEWLINE() \
	P->col = 1; \
	++P->line

#define NEWTOKEN(t) \
	P->num = t; \
	token = psi_token_alloc(P); \
	tokens = psi_plist_add(tokens, &token); \
	P->col += P->cur - P->tok; \
	if (P->flags & PSI_DEBUG) { \
		fprintf(stderr, "PSI< "); \
		psi_token_dump(2, token); \
	} \
	token = NULL


struct psi_plist *psi_parser_scan(struct psi_parser *P)
{
	struct psi_plist *tokens;
	struct psi_token *token;

	if (!P->cur) {
		return NULL;
	}

	tokens = psi_plist_init(NULL);

	start: ;
		P->tok = P->cur;

		/*!re2c

		"/*"			{ goto comment; }
		"//"			{ goto comment_sl; }
		"#"				{ NEWTOKEN(PSI_T_HASH); goto start; }
		"("				{ NEWTOKEN(PSI_T_LPAREN); goto start; }
		")"				{ NEWTOKEN(PSI_T_RPAREN); goto start; }
		";"				{ NEWTOKEN(PSI_T_EOS); goto start; }
		","				{ NEWTOKEN(PSI_T_COMMA); goto start; }
		":"				{ NEWTOKEN(PSI_T_COLON); goto start; }
		"{"				{ NEWTOKEN(PSI_T_LBRACE); goto start; }
		"}"				{ NEWTOKEN(PSI_T_RBRACE); goto start; }
		"["				{ NEWTOKEN(PSI_T_LBRACKET); goto start; }
		"]"				{ NEWTOKEN(PSI_T_RBRACKET); goto start; }
		"!=" 			{ NEWTOKEN(PSI_T_CMP_NE); goto start; }
		"=="			{ NEWTOKEN(PSI_T_CMP_EQ); goto start; }
		"&&"			{ NEWTOKEN(PSI_T_AND); goto start; }
		"||"			{ NEWTOKEN(PSI_T_OR); goto start; }
		"="				{ NEWTOKEN(PSI_T_EQUALS); goto start; }
		"*"				{ NEWTOKEN(PSI_T_ASTERISK); goto start; }
		"~"				{ NEWTOKEN(PSI_T_TILDE); goto start; }
		"!"				{ NEWTOKEN(PSI_T_NOT); goto start; }
		"%"				{ NEWTOKEN(PSI_T_MODULO); goto start; }
		"&"				{ NEWTOKEN(PSI_T_AMPERSAND); goto start; }
		"+"				{ NEWTOKEN(PSI_T_PLUS); goto start; }
		"-"				{ NEWTOKEN(PSI_T_MINUS); goto start; }
		"/"				{ NEWTOKEN(PSI_T_SLASH); goto start; }
		"\\"			{ NEWTOKEN(PSI_T_BSLASH); goto start; }
		"|"				{ NEWTOKEN(PSI_T_PIPE); goto start; }
		"^"				{ NEWTOKEN(PSI_T_CARET); goto start; }
		"<<"			{ NEWTOKEN(PSI_T_LSHIFT); goto start; }
		">>"			{ NEWTOKEN(PSI_T_RSHIFT); goto start; }
		"<="			{ NEWTOKEN(PSI_T_CMP_LE); goto start; }
		">="			{ NEWTOKEN(PSI_T_CMP_GE); goto start; }
		"<"				{ NEWTOKEN(PSI_T_LCHEVR); goto start; }
		">"				{ NEWTOKEN(PSI_T_RCHEVR); goto start; }
		"..."			{ NEWTOKEN(PSI_T_ELLIPSIS); goto start; }
		'IF'			{ NEWTOKEN(PSI_T_IF); goto start; }
		'IFDEF'			{ NEWTOKEN(PSI_T_IFDEF); goto start; }
		'IFNDEF'		{ NEWTOKEN(PSI_T_IFNDEF); goto start; }
		'ELSE'			{ NEWTOKEN(PSI_T_ELSE); goto start; }
		'ELIF'			{ NEWTOKEN(PSI_T_ELIF); goto start; }
		'ENDIF'			{ NEWTOKEN(PSI_T_ENDIF); goto start; }
		'DEFINE'		{ NEWTOKEN(PSI_T_DEFINE); goto start; }
		'DEFINED'		{ NEWTOKEN(PSI_T_DEFINED); goto start; }
		'UNDEF'			{ NEWTOKEN(PSI_T_UNDEF); goto start; }
		'WARNING'		{ NEWTOKEN(PSI_T_WARNING); goto start; }
		'ERROR'			{ NEWTOKEN(PSI_T_ERROR); goto start; }
		'TRUE'			{ NEWTOKEN(PSI_T_TRUE); goto start; }
		'FALSE'			{ NEWTOKEN(PSI_T_FALSE); goto start; }
		'NULL'			{ NEWTOKEN(PSI_T_NULL); goto start; }
		'MIXED'			{ NEWTOKEN(PSI_T_MIXED); goto start; }
		'CALLABLE'		{ NEWTOKEN(PSI_T_CALLABLE); goto start; }
		'VOID'			{ NEWTOKEN(PSI_T_VOID); goto start; }
		'BOOL'			{ NEWTOKEN(PSI_T_BOOL); goto start; }
		'CHAR'			{ NEWTOKEN(PSI_T_CHAR); goto start; }
		'SHORT'			{ NEWTOKEN(PSI_T_SHORT); goto start; }
		'INT'			{ NEWTOKEN(PSI_T_INT); goto start; }
		'LONG'			{ NEWTOKEN(PSI_T_LONG); goto start; }
		'FLOAT'			{ NEWTOKEN(PSI_T_FLOAT); goto start; }
		'DOUBLE'		{ NEWTOKEN(PSI_T_DOUBLE); goto start; }
		'INT8_T'		{ NEWTOKEN(PSI_T_INT8); goto start; }
		'UINT8_T'		{ NEWTOKEN(PSI_T_UINT8); goto start; }
		'INT16_T'		{ NEWTOKEN(PSI_T_INT16); goto start; }
		'UINT16_T'		{ NEWTOKEN(PSI_T_UINT16); goto start; }
		'INT32_T'		{ NEWTOKEN(PSI_T_INT32); goto start; }
		'UINT32_T'		{ NEWTOKEN(PSI_T_UINT32); goto start; }
		'INT64_T'		{ NEWTOKEN(PSI_T_INT64); goto start; }
		'UINT64_T'		{ NEWTOKEN(PSI_T_UINT64); goto start; }
		'UNSIGNED'		{ NEWTOKEN(PSI_T_UNSIGNED); goto start; }
		'SIGNED'		{ NEWTOKEN(PSI_T_SIGNED); goto start; }
		'STRING'		{ NEWTOKEN(PSI_T_STRING); goto start; }
		'ARRAY'			{ NEWTOKEN(PSI_T_ARRAY); goto start; }
		'OBJECT'		{ NEWTOKEN(PSI_T_OBJECT); goto start; }
		'CALLBACK'		{ NEWTOKEN(PSI_T_CALLBACK); goto start; }
		'STATIC'		{ NEWTOKEN(PSI_T_STATIC); goto start; }
		'FUNCTION'		{ NEWTOKEN(PSI_T_FUNCTION); goto start; }
		'TYPEDEF'		{ NEWTOKEN(PSI_T_TYPEDEF); goto start; }
		'STRUCT'		{ NEWTOKEN(PSI_T_STRUCT); goto start; }
		'UNION'			{ NEWTOKEN(PSI_T_UNION); goto start; }
		'ENUM'			{ NEWTOKEN(PSI_T_ENUM); goto start; }
		'CONST'			{ NEWTOKEN(PSI_T_CONST); goto start; }
		'LIB'			{ NEWTOKEN(PSI_T_LIB); goto start; }
		'LET'			{ NEWTOKEN(PSI_T_LET); goto start; }
		'SET'			{ NEWTOKEN(PSI_T_SET); goto start; }
		'PRE_ASSERT'	{ NEWTOKEN(PSI_T_PRE_ASSERT); goto start; }
		'POST_ASSERT'	{ NEWTOKEN(PSI_T_POST_ASSERT); goto start; }
		'RETURN'		{ NEWTOKEN(PSI_T_RETURN); goto start; }
		'FREE'			{ NEWTOKEN(PSI_T_FREE); goto start; }
		'TEMP'			{ NEWTOKEN(PSI_T_TEMP); goto start; }
		'STRLEN'		{ NEWTOKEN(PSI_T_STRLEN); goto start; }
		'STRVAL'		{ NEWTOKEN(PSI_T_STRVAL); goto start; }
		'PATHVAL'		{ NEWTOKEN(PSI_T_PATHVAL); goto start; }
		'INTVAL'		{ NEWTOKEN(PSI_T_INTVAL); goto start; }
		'FLOATVAL'		{ NEWTOKEN(PSI_T_FLOATVAL); goto start; }
		'BOOLVAL'		{ NEWTOKEN(PSI_T_BOOLVAL); goto start; }
		'ARRVAL'		{ NEWTOKEN(PSI_T_ARRVAL); goto start; }
		'OBJVAL'		{ NEWTOKEN(PSI_T_OBJVAL); goto start; }
		'ZVAL'			{ NEWTOKEN(PSI_T_ZVAL); goto start; }
		'COUNT'			{ NEWTOKEN(PSI_T_COUNT); goto start; }
		'CALLOC'		{ NEWTOKEN(PSI_T_CALLOC); goto start; }
		'TO_OBJECT'		{ NEWTOKEN(PSI_T_TO_OBJECT); goto start; }
		'TO_ARRAY'		{ NEWTOKEN(PSI_T_TO_ARRAY); goto start; }
		'TO_STRING'		{ NEWTOKEN(PSI_T_TO_STRING); goto start; }
		'TO_INT'		{ NEWTOKEN(PSI_T_TO_INT); goto start; }
		'TO_FLOAT'		{ NEWTOKEN(PSI_T_TO_FLOAT); goto start; }
		'TO_BOOL'		{ NEWTOKEN(PSI_T_TO_BOOL); goto start; }
		NUMBER			{ NEWTOKEN(PSI_T_NUMBER); goto start; }
		NAME			{ NEWTOKEN(PSI_T_NAME); goto start; }
		NSNAME			{ NEWTOKEN(PSI_T_NSNAME); goto start; }
		DOLLAR_NAME		{ NEWTOKEN(PSI_T_DOLLAR_NAME); goto start; }
		QUOTED_STRING	{ NEWTOKEN(PSI_T_QUOTED_STRING); goto start; }
		EOL				{ NEWTOKEN(PSI_T_EOL); NEWLINE(); goto start; }
		SP+				{ NEWTOKEN(PSI_T_WHITESPACE); goto start; }
		*				{ goto error; }

		*/

	comment: ;
		/*!re2c

		EOL		{ NEWLINE(); goto comment; }
		"*" "/"	{ NEWTOKEN(PSI_T_COMMENT); goto start; }
		 *		{ goto comment; }

		*/

	comment_sl: ;
		/*!re2c

		EOL	{ NEWTOKEN(PSI_T_COMMENT); NEWLINE(); goto start; }
		*	{ goto comment_sl; }

		*/
error:
	psi_plist_free(tokens);
	return NULL;
done:
	return tokens;
}
