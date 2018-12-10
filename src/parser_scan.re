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

#include "parser.h"
#include "plist.h"
#include "debug.h"

/*!max:re2c*/
#ifndef YYMAXFILL
# define YYMAXFILL 256
#endif

size_t psi_parser_maxfill(void) {
	return YYMAXFILL;
}

#define NEWLINE() \
	eol = cur; \
	++lines

#define NEWTOKEN(t) do { \
	if (t == PSI_T_COMMENT || t == PSI_T_WHITESPACE) { \
		token = psi_token_init(t, "", 0, tok - eol + 1, lines, I->file); \
	} else { \
		token = psi_token_init(t, tok, cur - tok, tok - eol + 1, lines, I->file); \
	} \
	tokens = psi_plist_add(tokens, &token); \
	PSI_DEBUG_LOCK(P, \
			PSI_DEBUG_PRINT(P, "PSI: scanned < "); \
			PSI_DEBUG_DUMP(P, psi_token_dump, token); \
	); \
} while(0)

#define CHECKEOF() if (cur >= lim - YYMAXFILL) goto done

struct psi_plist *psi_parser_scan(struct psi_parser *P, struct psi_parser_input *I)
{
	struct psi_plist *tokens;
	struct psi_token *token;
	const char *tok, *cur, *lim, *mrk, *eol, *ctxmrk;
	unsigned char_width, parens, lines = 1;
	bool escaped;

	PSI_DEBUG_PRINT(P, "PSI: scanning %s\n", I->file->val);

	tok = mrk = eol = cur = I->buffer;
	lim = I->buffer + I->length + YYMAXFILL;
	tokens = psi_plist_init((psi_plist_dtor) psi_token_free);

	start: ;
		char_width = 1;
		ctxmrk = NULL;
		tok = cur;

		(void) ctxmrk;

		/*!re2c

		re2c:indent:top = 2;
		re2c:define:YYCTYPE = "unsigned char";
		re2c:define:YYCURSOR = cur;
		re2c:define:YYLIMIT = lim;
		re2c:define:YYMARKER = mrk;
		re2c:define:YYCTXMARKER = ctxmrk;
		re2c:define:YYFILL = "CHECKEOF();";
		re2c:yyfill:parameter = 0;

		W = [a-zA-Z0-9_\x80-\xff];
		SP = [ \t\f];
		EOL = [\r\n];
		NAME = [a-zA-Z_\x80-\xff] W*;
		NSNAME = (NAME)? ("\\" NAME)+;
		DOLLAR_NAME = '$' W+;
		CPP_HEADER = "<" [-._/a-zA-Z0-9]+ ">";
		CPP_ATTRIBUTE = "__attribute__" SP* "((";

		DEC_CONST = [1-9] [0-9]*;
		OCT_CONST = "0" [0-7]*;
		HEX_CONST = '0x' [0-9a-fA-F]+;
		INT_CONST = (DEC_CONST | OCT_CONST | HEX_CONST);

		FLT_HEX_CONST = HEX_CONST ("." [0-9a-fA-F]*)? 'p' [+-]? [0-9]+;
		FLT_DEC_NUM = "0" | DEC_CONST;
		FLT_DEC_CONST = (FLT_DEC_NUM ("." [0-9]*)? 'e' [+-]? [0-9]+) | (FLT_DEC_NUM "." [0-9]*) | ("." [0-9]+);
		FLT_CONST = (FLT_DEC_CONST | FLT_HEX_CONST);

		INT_CONST					{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_INT; goto start; }
		INT_CONST / 'u'				{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_INT | PSI_NUMBER_U; cur += 1; goto start; }
		INT_CONST / 'l'				{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_INT | PSI_NUMBER_L; cur += 1; goto start; }
		INT_CONST / ('lu' | 'ul')	{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_INT | PSI_NUMBER_UL; cur += 2; goto start; }
		INT_CONST / ('llu' | 'ull')	{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_INT | PSI_NUMBER_ULL; cur += 3; goto start; }

		FLT_CONST					{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT; goto start; }
		FLT_CONST	/ 'f'			{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT | PSI_NUMBER_F; cur += 1; goto start; }
		FLT_CONST	/ 'l'			{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT | PSI_NUMBER_L; cur += 1; goto start; }
		FLT_CONST	/ 'df'			{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT | PSI_NUMBER_DF; cur += 2; goto start; }
		FLT_CONST	/ 'dd'			{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT | PSI_NUMBER_DD; cur += 2; goto start; }
		FLT_CONST	/ 'dl'			{ NEWTOKEN(PSI_T_NUMBER); token->flags = PSI_NUMBER_FLT | PSI_NUMBER_DL; cur += 2; goto start; }

		"'"				{ escaped = false; tok += 1; goto character; }
		"\""			{ escaped = false; tok += 1; goto string; }
		"u8" / "\""		{ char_width = 1; }
		"u" / ['"]		{ char_width = 2; }
		"U" / ['"]		{ char_width = 4; }
		"L" / ['"]		{ char_width = sizeof(wchar_t); }

		"/*"			{ goto comment; }
		"//"			{ goto comment_sl; }

		"##"			{ NEWTOKEN(PSI_T_CPP_PASTE); goto start; }
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
		"."				{ NEWTOKEN(PSI_T_PERIOD); goto start; }
		"..."			{ NEWTOKEN(PSI_T_ELLIPSIS); goto start; }
		"?"				{ NEWTOKEN(PSI_T_IIF); goto start; }
		"pragma"		{ NEWTOKEN(PSI_T_PRAGMA); goto start; }
		"__"? "inline"	{ NEWTOKEN(PSI_T_CPP_INLINE); goto start; }
		"__restrict"	{ NEWTOKEN(PSI_T_CPP_RESTRICT); goto start; }
		"__extension__"	{ NEWTOKEN(PSI_T_CPP_EXTENSION); goto start; }
		"__asm" ("__")?	{ NEWTOKEN(PSI_T_CPP_ASM); goto start; }
		"volatile"		{ NEWTOKEN(PSI_T_VOLATILE); goto start; }
		"sizeof"		{ NEWTOKEN(PSI_T_SIZEOF); goto start; }
		"line"			{ NEWTOKEN(PSI_T_LINE); goto start; }
		"typedef"		{ NEWTOKEN(PSI_T_TYPEDEF); goto start; }
		"struct"		{ NEWTOKEN(PSI_T_STRUCT); goto start; }
		"union"			{ NEWTOKEN(PSI_T_UNION); goto start; }
		"enum"			{ NEWTOKEN(PSI_T_ENUM); goto start; }
		"const"			{ NEWTOKEN(PSI_T_CONST); goto start; }
		"void"			{ NEWTOKEN(PSI_T_VOID); goto start; }
		"bool"			{ NEWTOKEN(PSI_T_BOOL); goto start; }
		"char"			{ NEWTOKEN(PSI_T_CHAR); goto start; }
		"short"			{ NEWTOKEN(PSI_T_SHORT); goto start; }
		"int"			{ NEWTOKEN(PSI_T_INT); goto start; }
		"long"			{ NEWTOKEN(PSI_T_LONG); goto start; }
		"float"			{ NEWTOKEN(PSI_T_FLOAT); goto start; }
		"double"		{ NEWTOKEN(PSI_T_DOUBLE); goto start; }
		"unsigned"		{ NEWTOKEN(PSI_T_UNSIGNED); goto start; }
		"signed"		{ NEWTOKEN(PSI_T_SIGNED); goto start; }
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
		'INCLUDE'		{ NEWTOKEN(PSI_T_INCLUDE); goto start; }
		'INCLUDE_NEXT'	{ NEWTOKEN(PSI_T_INCLUDE_NEXT); goto start; }
		'TRUE'			{ NEWTOKEN(PSI_T_TRUE); goto start; }
		'FALSE'			{ NEWTOKEN(PSI_T_FALSE); goto start; }
		'NULL'			{ NEWTOKEN(PSI_T_NULL); goto start; }
		'MIXED'			{ NEWTOKEN(PSI_T_MIXED); goto start; }
		'CALLABLE'		{ NEWTOKEN(PSI_T_CALLABLE); goto start; }
		'STRING'		{ NEWTOKEN(PSI_T_STRING); goto start; }
		'ARRAY'			{ NEWTOKEN(PSI_T_ARRAY); goto start; }
		'OBJECT'		{ NEWTOKEN(PSI_T_OBJECT); goto start; }
		'CALLBACK'		{ NEWTOKEN(PSI_T_CALLBACK); goto start; }
		'STATIC'		{ NEWTOKEN(PSI_T_STATIC); goto start; }
		'FUNCTION'		{ NEWTOKEN(PSI_T_FUNCTION); goto start; }
		'LIB'			{ NEWTOKEN(PSI_T_LIB); goto start; }
		'LET'			{ NEWTOKEN(PSI_T_LET); goto start; }
		'SET'			{ NEWTOKEN(PSI_T_SET); goto start; }
		'PRE_ASSERT'	{ NEWTOKEN(PSI_T_PRE_ASSERT); goto start; }
		'POST_ASSERT'	{ NEWTOKEN(PSI_T_POST_ASSERT); goto start; }
		'RETURN'		{ NEWTOKEN(PSI_T_RETURN); goto start; }
		'AS'			{ NEWTOKEN(PSI_T_AS); goto start; }
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
		NAME			{ NEWTOKEN(PSI_T_NAME); goto start; }
		NSNAME			{ NEWTOKEN(PSI_T_NSNAME); goto start; }
		DOLLAR_NAME		{ NEWTOKEN(PSI_T_DOLLAR_NAME); goto start; }
		CPP_HEADER		{ tok += 1; cur -= 1; NEWTOKEN(PSI_T_CPP_HEADER); cur += 1; goto start; }
		CPP_ATTRIBUTE	{ parens = 2; goto cpp_attribute; }
		EOL				{ NEWTOKEN(PSI_T_EOL); NEWLINE(); goto start; }
		SP+				{ NEWTOKEN(PSI_T_WHITESPACE); goto start; }
		[^]				{ CHECKEOF(); NEWTOKEN(-2); goto error; }
		*				{ CHECKEOF(); NEWTOKEN(-1); goto error; }

		*/

	character: ;
		/*!re2c

		EOL		{ NEWLINE(); goto character; }
		"\\"	{ escaped = !escaped;  goto character; }
		"'"		{
			if (escaped) {
				escaped = false;
				goto character;
			}
			cur -= 1;
			NEWTOKEN(PSI_T_QUOTED_CHAR);
			cur += 1;
			token->flags = char_width;
			goto start;
		}
		*		{ escaped = false; goto character; }

		*/

	string: ;
		/*!re2c

		EOL		{ NEWLINE(); goto string; }
		"\\" 	{ escaped = !escaped; goto string; }
		"\""	{
			if (escaped) {
				escaped = false;
				goto string;
			}
			cur -= 1;
			NEWTOKEN(PSI_T_QUOTED_STRING);
			cur += 1;
			token->flags = char_width;
			goto start;
		}
		*		{ escaped = false; goto string; }

		*/

	comment: ;
		/*!re2c

		EOL		{ NEWLINE(); goto comment; }
		"*" "/"	{ NEWTOKEN(PSI_T_COMMENT); goto start; }
		 *		{ goto comment; }

		*/

	comment_sl: ;
		/*!re2c

		EOL	{ NEWTOKEN(PSI_T_COMMENT); tok = cur - 1; NEWTOKEN(PSI_T_EOL); NEWLINE(); goto start; }
		*	{ goto comment_sl; }

		*/

	cpp_attribute: ;

		/*!re2c

		"("	{ ++parens; goto cpp_attribute; }
		")" { if (parens == 1) { NEWTOKEN(PSI_T_CPP_ATTRIBUTE); goto start; } else { --parens; goto cpp_attribute; } }
		EOL	{ NEWLINE(); goto cpp_attribute; }
		 *	{ goto cpp_attribute; }

		*/
error: ;

	P->error(PSI_DATA(P), token, PSI_WARNING, "PSI syntax error: unexpected input (%d) '%.*s' at col %tu",
			token->type, token->text->len, token->text->val, tok - eol + 1);
	psi_plist_free(tokens);
	return NULL;

done: ;

	PSI_DEBUG_PRINT(P, "PSI: EOF cur=%p lim=%p\n", cur, lim);

	return tokens;
}
