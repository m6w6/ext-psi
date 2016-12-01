#include "php_psi_stdinc.h"
#include <sys/mman.h>
#include <assert.h>

#include "parser.h"

void *psi_parser_proc_Alloc(void*(unsigned long));
void psi_parser_proc_Free(void*, void(*)(void*));
void psi_parser_proc_(void *, token_t, struct psi_token *, struct psi_parser *);
void psi_parser_proc_Trace(FILE *, const char*);

struct psi_parser *psi_parser_init(struct psi_parser *P, psi_error_cb error, unsigned flags)
{
	if (!P) {
		P = malloc(sizeof(*P));
	}
	memset(P, 0, sizeof(*P));

	psi_data_ctor_with_dtors(PSI_DATA(P), error, flags);

	P->col = 1;
	P->line = 1;
	P->proc = psi_parser_proc_Alloc(malloc);

	if (flags & PSI_DEBUG) {
		psi_parser_proc_Trace(stderr, "PSI> ");
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
		psi_parser_proc_(P->proc, T->type, T, P);
	} else {
		psi_parser_proc_(P->proc, 0, NULL, P);
	}
}

void psi_parser_dtor(struct psi_parser *P)
{
	psi_parser_proc_Free(P->proc, free);

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

#define ADDCOLS \
	P->col += P->cur - P->tok

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
		ADDCOLS;
	nextline:
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

		"/*" { goto comment; }
		("#"|"//") .* "\n" { NEWLINE(nextline); }
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

	comment:
		P->tok = P->cur;
		/*!re2c
		"\n" { NEWLINE(comment); }
		"*" "/" { continue; }
		[^] { goto comment; }
		*/
	}
	return -1;
}
