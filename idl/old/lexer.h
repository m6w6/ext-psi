#ifndef _PSI_LEXER_H
#define _PSI_LEXER_H

#include "types.h"

#define BSIZE 256


PSI_Lexer *PSI_LexerInit(PSI_Lexer *L, const char *filename);
size_t PSI_LexerFill(PSI_Lexer *L, size_t n);
token_t PSI_LexerScan(PSI_Lexer *L);
void PSI_LexerDtor(PSI_Lexer *L);
void PSI_LexerFree(PSI_Lexer **L);

PSI_Token *PSI_TokenAlloc(PSI_Lexer *L, token_t t);

#endif
