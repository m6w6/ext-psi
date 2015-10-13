#include <stdio.h>
#include <assert.h>

#include "parser.h"
#include "parser_proc.h"

void *PSI_ParserProcAlloc(void*(unsigned long));
void PSI_ParserProcFree(void*, void(*)(void*));
void PSI_ParserProc(void *, token_t, PSI_Token *, PSI_Parser *);

PSI_Parser *PSI_ParserInit(PSI_Parser *P, const char *filename)
{
	FILE *fp;

	if (!P) {
		P = malloc(sizeof(*P));
	}
	memset(P, 0, sizeof(*P));

	fp = fopen(filename, "r");

	if (!fp) {
		perror(filename);
		return NULL;
	}

	if (!P) {
		P = malloc(sizeof(*P));
	}
	memset(P, 0, sizeof(*P));

	P->fp = fp;
	P->fn = strdup(filename);
	P->line = 1;

	P->proc = PSI_ParserProcAlloc(malloc);

	PSI_ParserFill(P, 0);

	return P;
}

size_t PSI_ParserFill(PSI_Parser *P, size_t n)
{
	// printf("+ Fill: n=%zu\n", n);
	if (!n) {
		P->cur = P->tok = P->lim = P->mrk = P->buf;
		P->eof = NULL;
	}

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

		// printf("+ Fill: consumed=%zu reserved=%zu available=%zu didread=%zu\n",
			// consumed, reserved, available, didread);
	}
	// printf("+ Fill: avail=%zu\n", P->lim - P->cur);
	return P->lim - P->cur;
}

void PSI_ParserParse(PSI_Parser *P, PSI_Token *T)
{
	if (T) {
		PSI_ParserProc(P->proc, T->type, T, P);
	} else {
		PSI_ParserProc(P->proc, 0, NULL, P);
	}
}

void PSI_ParserDtor(PSI_Parser *P)
{
	PSI_ParserProcFree(P->proc, free);

	if (P->fp) {
		fclose(P->fp);
	}

	PSI_DataDtor((PSI_Data *) P);

	memset(P, 0, sizeof(*P));
}

void PSI_ParserFree(PSI_Parser **P)
{
	if (*P) {
		PSI_ParserDtor(*P);
		free(*P);
		*P = NULL;
	}
}

/*!max:re2c*/
#define BSIZE 256

#if BSIZE < YYMAXFILL
# error BSIZE must be greater than YYMAXFILL
#endif

#define RETURN(t) do { \
	P->num = t; \
	return t; \
} while(1)

token_t PSI_ParserScan(PSI_Parser *P)
{
	for (;;) {
		P->tok = P->cur;
		/*!re2c
		re2c:indent:top = 2;
		re2c:define:YYCTYPE = "unsigned char";
		re2c:define:YYCURSOR = P->cur;
		re2c:define:YYLIMIT = P->lim;
		re2c:define:YYMARKER = P->mrk;
		re2c:define:YYFILL = "{ if (!PSI_ParserFill(P,@@)) RETURN(-1); }";
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

		"#" .* "\n" { ++P->line; RETURN(PSI_T_COMMENT);}
		"(" {RETURN(PSI_T_LPAREN);}
		")" {RETURN(PSI_T_RPAREN);}
		";" {RETURN(PSI_T_EOS);}
		"," {RETURN(PSI_T_COMMA);}
		":" {RETURN(PSI_T_COLON);}
		"{" {RETURN(PSI_T_LBRACE);}
		"}" {RETURN(PSI_T_RBRACE);}
		"." {RETURN(PSI_T_DOT);}
		"=" {RETURN(PSI_T_EQUALS);}
		"$" {RETURN(PSI_T_DOLLAR);}
		"*" {RETURN(PSI_T_POINTER);}
		"&" {RETURN(PSI_T_REFERENCE);}
		[\r\n] { ++P->line; continue; }
		[\t ]+ { continue; }
		NULL {RETURN(PSI_T_NULL);}
		MIXED {RETURN(PSI_T_MIXED);}
		VOID {RETURN(PSI_T_VOID);}
		BOOL {RETURN(PSI_T_BOOL);}
		INT {RETURN(PSI_T_INT);}
		FLOAT {RETURN(PSI_T_FLOAT);}
		DOUBLE {RETURN(PSI_T_DOUBLE);}
		SINT8 {RETURN(PSI_T_SINT8);}
		UINT8 {RETURN(PSI_T_UINT8);}
		SINT16 {RETURN(PSI_T_SINT16);}
		UINT16 {RETURN(PSI_T_UINT16);}
		SINT32 {RETURN(PSI_T_SINT32);}
		UINT32 {RETURN(PSI_T_UINT32);}
		SINT64 {RETURN(PSI_T_SINT64);}
		UINT64 {RETURN(PSI_T_UINT64);}
		STRING {RETURN(PSI_T_STRING);}
		ARRAY {RETURN(PSI_T_ARRAY);}
		FUNCTION {RETURN(PSI_T_FUNCTION);}
		TYPEDEF {RETURN(PSI_T_TYPEDEF);}
		LIB {RETURN(PSI_T_LIB);}
		LET {RETURN(PSI_T_LET);}
		SET {RETURN(PSI_T_SET);}
		RET {RETURN(PSI_T_RET);}
		STRVAL {RETURN(PSI_T_STRVAL);}
		INTVAL {RETURN(PSI_T_INTVAL);}
		FLOATVAL {RETURN(PSI_T_FLOATVAL);}
		BOOLVAL {RETURN(PSI_T_BOOLVAL);}
		TO_STRING {RETURN(PSI_T_TO_STRING);}
		TO_INT {RETURN(PSI_T_TO_INT);}
		TO_FLOAT {RETURN(PSI_T_TO_FLOAT);}
		TO_BOOL {RETURN(PSI_T_TO_BOOL);}
		[0-9] {RETURN(PSI_T_DIGIT);}
		NAME {RETURN(PSI_T_NAME);}
		NSNAME {RETURN(PSI_T_NSNAME);}
		QUOTED_STRING {RETURN(PSI_T_QUOTED_STRING);}
		*/
	}
	return -1;
}
