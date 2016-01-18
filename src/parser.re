#include <stdio.h>
#include <assert.h>

#include "parser.h"
#include "parser_proc.h"

void *PSI_ParserProcAlloc(void*(unsigned long));
void PSI_ParserProcFree(void*, void(*)(void*));
void PSI_ParserProc(void *, token_t, PSI_Token *, PSI_Parser *);
void PSI_ParserProcTrace(FILE *, const char*);

PSI_Parser *PSI_ParserInit(PSI_Parser *P, const char *filename, psi_error_cb error, unsigned flags)
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

	P->psi.file.fn = strdup(filename);
	P->fp = fp;
	P->col = 1;
	P->line = 1;
	P->error = error;
	P->flags = flags;

	P->proc = PSI_ParserProcAlloc(malloc);
	if (flags & PSI_PARSER_DEBUG) {
		PSI_ParserProcTrace(stderr, "PSI> ");
	}

	PSI_ParserFill(P, 0);

	return P;
}

size_t PSI_ParserFill(PSI_Parser *P, size_t n)
{
	if (P->flags & PSI_PARSER_DEBUG) {
		fprintf(stderr, "PSI> Fill: n=%zu\n", n);
	}
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

		if (P->flags & PSI_PARSER_DEBUG) {
			fprintf(stderr, "PSI> Fill: consumed=%zu reserved=%zu available=%zu didread=%zu\n",
				consumed, reserved, available, didread);
		}
	}
	if (P->flags & PSI_PARSER_DEBUG) {
		fprintf(stderr, "PSI> Fill: avail=%zu\n", P->lim - P->cur);
	}
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

#define PSI_T(n) \
(n) == PSI_T_NAME ? "NAME" : \
(n) == PSI_T_PLUS ? "PLUS" : \
(n) == PSI_T_MINUS ? "MINUS" : \
(n) == PSI_T_SLASH ? "SLASH" : \
(n) == PSI_T_ASTERISK ? "ASTERISK" : \
(n) == PSI_T_TEMP ? "TEMP" : \
(n) == PSI_T_FREE ? "FREE" : \
(n) == PSI_T_SET ? "SET" : \
(n) == PSI_T_LET ? "LET" : \
(n) == PSI_T_RETURN ? "RETURN" : \
(n) == PSI_T_LIB ? "LIB" : \
(n) == PSI_T_INT ? "INT" : \
(n) == PSI_T_UNSIGNED ? "UNSIGNED" : \
(n) == PSI_T_EOF ? "EOF" : \
(n) == PSI_T_QUOTED_STRING ? "QUOTED_STRING" : \
(n) == PSI_T_EOS ? "EOS" : \
(n) == PSI_T_STRUCT ? "STRUCT" : \
(n) == PSI_T_LBRACE ? "LBRACE" : \
(n) == PSI_T_RBRACE ? "RBRACE" : \
(n) == PSI_T_COLON ? "COLON" : \
(n) == PSI_T_LPAREN ? "LPAREN" : \
(n) == PSI_T_NUMBER ? "NUMBER" : \
(n) == PSI_T_RPAREN ? "RPAREN" : \
(n) == PSI_T_BOOL ? "BOOL" : \
(n) == PSI_T_FLOAT ? "FLOAT" : \
(n) == PSI_T_STRING ? "STRING" : \
(n) == PSI_T_CONST ? "CONST" : \
(n) == PSI_T_NSNAME ? "NSNAME" : \
(n) == PSI_T_EQUALS ? "EQUALS" : \
(n) == PSI_T_TYPEDEF ? "TYPEDEF" : \
(n) == PSI_T_VOID ? "VOID" : \
(n) == PSI_T_LBRACKET ? "LBRACKET" : \
(n) == PSI_T_RBRACKET ? "RBRACKET" : \
(n) == PSI_T_COMMA ? "COMMA" : \
(n) == PSI_T_ELLIPSIS ? "ELLIPSIS" : \
(n) == PSI_T_DOUBLE ? "DOUBLE" : \
(n) == PSI_T_INT8 ? "INT8" : \
(n) == PSI_T_UINT8 ? "UINT8" : \
(n) == PSI_T_INT16 ? "INT16" : \
(n) == PSI_T_UINT16 ? "UINT16" : \
(n) == PSI_T_INT32 ? "INT32" : \
(n) == PSI_T_UINT32 ? "UINT32" : \
(n) == PSI_T_INT64 ? "INT64" : \
(n) == PSI_T_UINT64 ? "UINT64" : \
(n) == PSI_T_FUNCTION ? "FUNCTION" : \
(n) == PSI_T_NULL ? "NULL" : \
(n) == PSI_T_TRUE ? "TRUE" : \
(n) == PSI_T_FALSE ? "FALSE" : \
(n) == PSI_T_DOLLAR ? "DOLLAR" : \
(n) == PSI_T_CALLOC ? "CALLOC" : \
(n) == PSI_T_OBJVAL ? "OBJVAL" : \
(n) == PSI_T_ARRVAL ? "ARRVAL" : \
(n) == PSI_T_PATHVAL ? "PATHVAL" : \
(n) == PSI_T_STRLEN ? "STRLEN" : \
(n) == PSI_T_STRVAL ? "STRVAL" : \
(n) == PSI_T_FLOATVAL ? "FLOATVAL" : \
(n) == PSI_T_INTVAL ? "INTVAL" : \
(n) == PSI_T_BOOLVAL ? "BOOLVAL" : \
(n) == PSI_T_TO_OBJECT ? "TO_OBJECT" : \
(n) == PSI_T_TO_ARRAY ? "TO_ARRAY" : \
(n) == PSI_T_TO_STRING ? "TO_STRING" : \
(n) == PSI_T_TO_INT ? "TO_INT" : \
(n) == PSI_T_TO_FLOAT ? "TO_FLOAT" : \
(n) == PSI_T_TO_BOOL ? "TO_BOOL" : \
(n) == PSI_T_MIXED ? "MIXED" : \
(n) == PSI_T_ARRAY ? "ARRAY" : \
(n) == PSI_T_OBJECT ? "OBJECT" : \
(n) == PSI_T_AMPERSAND ? "AMPERSAND" : \
<UNKNOWN>

#define RETURN(t) do { \
	P->num = t; \
	if (P->flags & PSI_PARSER_DEBUG) { \
		fprintf(stderr, "PSI> TOKEN: %d %.*s (EOF=%d %s:%u:%u)\n", \
				P->num, (int) (P->cur-P->tok), P->tok, P->num == PSI_T_EOF, \
				P->psi.file.fn, P->line, P->col); \
	} \
	return t; \
} while(1)

#define ADDCOLS \
	P->col += P->cur - P->tok

#define NEWLINE \
	P->col = 1; \
	++P->line; \
	goto nextline

token_t PSI_ParserScan(PSI_Parser *P)
{
	for (;;) {
		ADDCOLS;
	nextline:
		P->tok = P->cur;
		/*!re2c
		re2c:indent:top = 2;
		re2c:define:YYCTYPE = "unsigned char";
		re2c:define:YYCURSOR = P->cur;
		re2c:define:YYLIMIT = P->lim;
		re2c:define:YYMARKER = P->mrk;
		re2c:define:YYFILL = "{ if (!PSI_ParserFill(P,@@)) RETURN(PSI_T_EOF); }";
		re2c:yyfill:parameter = 0;

		B = [^a-zA-Z0-9_];
		W = [a-zA-Z0-9_];
		NAME = [a-zA-Z_]W*;
		NSNAME = (NAME)? ("\\" NAME)+;
		QUOTED_STRING = "\"" ([^\"])+ "\"";
		NUMBER = [+-]? [0-9]* "."? [0-9]+ ([eE] [+-]? [0-9]+)?;

		("#"|"//") .* "\n" { NEWLINE; }
		"(" {RETURN(PSI_T_LPAREN);}
		")" {RETURN(PSI_T_RPAREN);}
		";" {RETURN(PSI_T_EOS);}
		"," {RETURN(PSI_T_COMMA);}
		":" {RETURN(PSI_T_COLON);}
		"{" {RETURN(PSI_T_LBRACE);}
		"}" {RETURN(PSI_T_RBRACE);}
		"[" {RETURN(PSI_T_LBRACKET);}
		"]" {RETURN(PSI_T_RBRACKET);}
		"=" {RETURN(PSI_T_EQUALS);}
		"$" {RETURN(PSI_T_DOLLAR);}
		"*" {RETURN(PSI_T_ASTERISK);}
		"&" {RETURN(PSI_T_AMPERSAND);}
		"+" {RETURN(PSI_T_PLUS);}
		"-" {RETURN(PSI_T_MINUS);}
		"/" {RETURN(PSI_T_SLASH);}
		"..." {RETURN(PSI_T_ELLIPSIS);}
		[\r\n] { NEWLINE; }
		[\t ]+ { continue; }
		'TRUE' {RETURN(PSI_T_TRUE);}
		'FALSE' {RETURN(PSI_T_FALSE);}
		'NULL' {RETURN(PSI_T_NULL);}
		'MIXED' {RETURN(PSI_T_MIXED);}
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
		'FUNCTION' {RETURN(PSI_T_FUNCTION);}
		'TYPEDEF' {RETURN(PSI_T_TYPEDEF);}
		'STRUCT' {RETURN(PSI_T_STRUCT);}
		'CONST' {RETURN(PSI_T_CONST);}
		'LIB' {RETURN(PSI_T_LIB);}
		'LET' {RETURN(PSI_T_LET);}
		'SET' {RETURN(PSI_T_SET);}
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
		QUOTED_STRING {RETURN(PSI_T_QUOTED_STRING);}
		[^] {break;}
		*/
	}
	return -1;
}
