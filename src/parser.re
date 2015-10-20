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

	P->fp = fp;
	P->fn = strdup(filename);
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

void PSI_ParserSyntaxError(PSI_Parser *P, const char *fn, size_t ln, const char *msg, ...) {
	char buf[0x1000] = {0};
	va_list argv;

	va_start(argv, msg);
	vsnprintf(buf, 0x1000-1, msg, argv);
	va_end(argv);

	P->error(PSI_WARNING, "PSI syntax error on line %zu in '%s'%s%s",
			ln, fn, msg ? ": ": "", buf);

	++P->errors;
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

#define RETURN(t) do { \
	P->num = t; \
	return t; \
} while(1)

/*		DIGIT = [0-9]
		DIGITS = DIGIT+
		DECIMALS = (+|-)? DIGIT* "."
		digits ::= digits DIGIT.
		decimals ::= digits DOT digits.
		decimals ::= DOT digits.
		decimals ::= digits DOT.
		number ::= digits.
		number ::= PLUS digits.
		number ::= MINUS digits.
		number ::= decimals.
		number ::= MINUS decimals.
		number ::= PLUS decimals.

*/
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
		NAME = [a-zA-Z_]W*;
		NSNAME = (NAME)? ("\\" NAME)+;
		QUOTED_STRING = "\"" ([^\"])+ "\"";
		TRUE = 'TRUE';
		FALSE = 'FALSE';
		NULL = 'NULL';
		MIXED = 'mixed';
		VOID = 'void';
		BOOL = 'bool';
		CHAR = 'char';
		SHORT = 'short';
		INT = 'int';
		LONG = 'long';
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
		CONST = 'const';
		LIB = 'lib';
		LET = 'let';
		SET = 'set';
		RETURN = 'return';
		FREE = 'free';
		STRLEN = 'strlen';
		STRVAL = 'strval';
		INTVAL = 'intval';
		FLOATVAL = 'floatval';
		BOOLVAL = 'boolval';
		TO_STRING = 'to_string';
		TO_INT = 'to_int';
		TO_FLOAT = 'to_float';
		TO_BOOL = 'to_bool';
		NUMBER = [+-]? [0-9]* "."? [0-9]+ ([eE] [+-]? [0-9]+)?;

		"#" .* "\n" { ++P->line; RETURN(PSI_T_COMMENT);}
		"(" {RETURN(PSI_T_LPAREN);}
		")" {RETURN(PSI_T_RPAREN);}
		";" {RETURN(PSI_T_EOS);}
		"," {RETURN(PSI_T_COMMA);}
		":" {RETURN(PSI_T_COLON);}
		"{" {RETURN(PSI_T_LBRACE);}
		"}" {RETURN(PSI_T_RBRACE);}
		"=" {RETURN(PSI_T_EQUALS);}
		"$" {RETURN(PSI_T_DOLLAR);}
		"*" {RETURN(PSI_T_POINTER);}
		"&" {RETURN(PSI_T_REFERENCE);}
		[\r\n] { ++P->line; continue; }
		[\t ]+ { continue; }
		TRUE {RETURN(PSI_T_TRUE);}
		FALSE {RETURN(PSI_T_FALSE);}
		NULL {RETURN(PSI_T_NULL);}
		MIXED {RETURN(PSI_T_MIXED);}
		VOID {RETURN(PSI_T_VOID);}
		BOOL {RETURN(PSI_T_BOOL);}
		CHAR {RETURN(PSI_T_CHAR);}
		SHORT {RETURN(PSI_T_SHORT);}
		INT {RETURN(PSI_T_INT);}
		LONG {RETURN(PSI_T_LONG);}
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
		CONST {RETURN(PSI_T_CONST);}
		LIB {RETURN(PSI_T_LIB);}
		LET {RETURN(PSI_T_LET);}
		SET {RETURN(PSI_T_SET);}
		RETURN {RETURN(PSI_T_RETURN);}
		FREE {RETURN(PSI_T_FREE);}
		STRLEN {RETURN(PSI_T_STRLEN);}
		STRVAL {RETURN(PSI_T_STRVAL);}
		INTVAL {RETURN(PSI_T_INTVAL);}
		FLOATVAL {RETURN(PSI_T_FLOATVAL);}
		BOOLVAL {RETURN(PSI_T_BOOLVAL);}
		TO_STRING {RETURN(PSI_T_TO_STRING);}
		TO_INT {RETURN(PSI_T_TO_INT);}
		TO_FLOAT {RETURN(PSI_T_TO_FLOAT);}
		TO_BOOL {RETURN(PSI_T_TO_BOOL);}
		NUMBER {RETURN(PSI_T_NUMBER);}
		NAME {RETURN(PSI_T_NAME);}
		NSNAME {RETURN(PSI_T_NSNAME);}
		QUOTED_STRING {RETURN(PSI_T_QUOTED_STRING);}
		[^] {break;}
		*/
	}
	return -1;
}
