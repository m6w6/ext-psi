#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include "lexer.h"
#include "parser.h"
#include "types.h"

#ifndef BSIZE
/*!max:re2c*/
#define BSIZE 256
#endif
#if BSIZE < YYMAXFILL
# error BSIZE must be greater than YYMAXFILL
#endif

PSI_Token *PSI_TokenAlloc(PSI_Lexer *L, token_t t)
{
	PSI_Token *T;
	size_t token_len;

	if (L->cur <= L->tok) {
		return NULL;
	}

	token_len = L->cur - L->tok;

	T = malloc(sizeof(*T) + token_len);
	T->type = t;
	T->line = L->line;
	T->size = token_len;
	T->text[token_len] = 0;
	memcpy(T->text, L->tok, token_len);

	return T;
}

size_t PSI_LexerFill(PSI_Lexer *L, size_t n)
{
	// printf("+ Fill: n=%zu\n", n);
	if (!n) {
		L->cur = L->tok = L->lim = L->mrk = L->buf;
		L->eof = NULL;
	}

	if (!L->eof) {
		size_t consumed = L->tok - L->buf;
		size_t reserved = L->lim - L->tok;
		size_t available = BSIZE - reserved;
		size_t didread;

		if (consumed) {
			memmove(L->buf, L->tok, reserved);
			L->tok -= consumed;
			L->cur -= consumed;
			L->lim -= consumed;
			L->mrk -= consumed;
		}

		didread = fread(L->lim, 1, available, L->fp);
		L->lim += didread;
		if (didread < available) {
			L->eof = L->lim;
		}

		// printf("+ Fill: consumed=%zu reserved=%zu available=%zu didread=%zu\n",
			// consumed, reserved, available, didread);
	}
	// printf("+ Fill: avail=%zu\n", L->lim - L->cur);
	return L->lim - L->cur;
}

void PSI_LexerDtor(PSI_Lexer *L)
{
	if (L->fp) {
		fclose(L->fp);
	}
	if (L->fn) {
		free(L->fn);
	}
	if (L->lib) {
		free(L->lib);
	}
	if (L->defs) {
		free_decl_typedefs(L->defs);
	}
	if (L->decls) {
		free_decls(L->decls);
	}
	if (L->impls) {
		free_impls(L->impls);
	}
	memset(L, 0, sizeof(*L));
}

void PSI_LexerFree(PSI_Lexer **L)
{
	if (*L) {
		PSI_LexerDtor(*L);
		free(*L);
		*L = NULL;
	}
}

PSI_Lexer *PSI_LexerInit(PSI_Lexer *L, const char *filename)
{
	FILE *fp = fopen(filename, "r");

	if (!fp) {
		perror(filename);
		return NULL;
	}

	if (!L) {
		L = malloc(sizeof(*L));
	}
	memset(L, 0, sizeof(*L));

	L->fp = fp;
	L->fn = strdup(filename);
	L->line = 1;

	PSI_LexerFill(L, 0);

	return L;
}


token_t PSI_LexerScan(PSI_Lexer *L)
{
	for (;;) {
		L->tok = L->cur;
		/*!re2c
		re2c:indent:top = 2;
		re2c:define:YYCTYPE = "unsigned char";
		re2c:define:YYCURSOR = L->cur;
		re2c:define:YYLIMIT = L->lim;
		re2c:define:YYMARKER = L->mrk;
		re2c:define:YYFILL = "{ if (!PSI_LexerFill(L,@@)) return -1; }";
		re2c:yyfill:parameter = 0;

		B = [^a-zA-Z0-9_];
		W = [a-zA-Z0-9_];
		NAME = W+;
		NSNAME = (NAME)? ("\\" NAME)+;
		QUOTED_STRING = "\"" ([^\"])+ "\"";
		NULL = 'NULL';
		MIXED = 'mixed';
		VOID = 'void';
		BOOL = 'bool';
		INT = 'int';
		FLOAT = 'float';
		DOUBLE = 'double';
		SINT8 = 'sint8';
		UINT8 = 'uint8';
		SINT16 = 'sint16';
		UINT16 = 'uint16';
		SINT32 = 'sint32';
		UINT32 = 'uint32';
		SINT64 = 'sint64';
		UINT64 = 'uint64';
		STRING = 'string';
		ARRAY = 'array';
		FUNCTION = 'function';
		TYPEDEF = 'typedef';
		LIB = 'lib';
		LET = 'let';
		SET = 'set';
		RET = 'ret';
		STRVAL = 'strval';
		INTVAL = 'intval';
		FLOATVAL = 'floatval';
		BOOLVAL = 'boolval';
		TO_STRING = 'to_string';
		TO_INT = 'to_int';
		TO_FLOAT = 'to_float';
		TO_BOOL = 'to_bool';

		"#" .* "\n" { ++L->line; return PSI_T_COMMENT;}
		"(" {return PSI_T_LPAREN;}
		")" {return PSI_T_RPAREN;}
		";" {return PSI_T_EOS;}
		"," {return PSI_T_COMMA;}
		":" {return PSI_T_COLON;}
		"{" {return PSI_T_LBRACE;}
		"}" {return PSI_T_RBRACE;}
		"." {return PSI_T_DOT;}
		"=" {return PSI_T_EQUALS;}
		"$" {return PSI_T_DOLLAR;}
		"*" {return PSI_T_POINTER;}
		"&" {return PSI_T_REFERENCE;}
		[\r\n] { ++L->line; continue; }
		[\t ]+ { continue; }
		NULL {return PSI_T_NULL;}
		MIXED {return PSI_T_MIXED;}
		VOID {return PSI_T_VOID;}
		BOOL {return PSI_T_BOOL;}
		INT {return PSI_T_INT;}
		FLOAT {return PSI_T_FLOAT;}
		DOUBLE {return PSI_T_DOUBLE;}
		SINT8 {return PSI_T_SINT8;}
		UINT8 {return PSI_T_UINT8;}
		SINT16 {return PSI_T_SINT16;}
		UINT16 {return PSI_T_UINT16;}
		SINT32 {return PSI_T_SINT32;}
		UINT32 {return PSI_T_UINT32;}
		SINT64 {return PSI_T_SINT64;}
		UINT64 {return PSI_T_UINT64;}
		STRING {return PSI_T_STRING;}
		ARRAY {return PSI_T_ARRAY;}
		FUNCTION {return PSI_T_FUNCTION;}
		TYPEDEF {return PSI_T_TYPEDEF;}
		LIB {return PSI_T_LIB;}
		LET {return PSI_T_LET;}
		SET {return PSI_T_SET;}
		RET {return PSI_T_RET;}
		STRVAL {return PSI_T_STRVAL;}
		INTVAL {return PSI_T_INTVAL;}
		FLOATVAL {return PSI_T_FLOATVAL;}
		BOOLVAL {return PSI_T_BOOLVAL;}
		TO_STRING {return PSI_T_TO_STRING;}
		TO_INT {return PSI_T_TO_INT;}
		TO_FLOAT {return PSI_T_TO_FLOAT;}
		TO_BOOL {return PSI_T_TO_BOOL;}
		[0-9] {return PSI_T_DIGIT;}
		NAME {return PSI_T_NAME;}
		NSNAME {return PSI_T_NSNAME;}
		QUOTED_STRING {return PSI_T_QUOTED_STRING;}
		*/
	}
	return -1;
}
