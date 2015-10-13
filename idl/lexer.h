#ifndef _PSI_LEXER_H
#define _PSI_LEXER_H

#ifndef BSIZE
# define BSIZE 256
#endif

typedef struct PSI_Lexer {

} PSI_Lexer;

size_t PSI_LexerFill(PSI_Lexer *L, size_t n);
void PSI_LexerDtor(PSI_Lexer *L);
void PSI_LexerFree(PSI_Lexer **L);
PSI_Lexer *PSI_LexerInit(PSI_Lexer *L, const char *filename);
token_t PSI_LexerScan(PSI_Lexer *L);

#endif
