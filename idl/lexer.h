#define BSIZE 256

typedef int token_t;
typedef unsigned char text;

typedef struct PSI_Token {
	token_t type;
	unsigned line;
	text text[1];
} PSI_Token;

typedef struct impl impl;
typedef struct decl decl;

typedef struct PSI_Lexer {
	FILE *fp;
	char *fn;
	struct {
		size_t count;
		decl **list;
	} decl;
	struct {
		size_t count;
		impl **list;
	} impl;
	size_t line;
	text *cur, *tok, *lim, *eof, *ctx, *mrk, buf[BSIZE];
} PSI_Lexer;

PSI_Lexer *PSI_LexerInit(PSI_Lexer *L, const char *filename);
size_t PSI_LexerFill(PSI_Lexer *L, size_t n);
token_t PSI_LexerScan(PSI_Lexer *L);
void PSI_LexerDtor(PSI_Lexer *L);
void PSI_LexerFree(PSI_Lexer **L);

PSI_Token *PSI_TokenAlloc(PSI_Lexer *L, token_t t);
