#ifndef _PSI_PARSER_H
#define _PSI_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "parser_proc.h"

#define BSIZE 256

#include "token.h"
#include "types.h"
#include "data.h"

struct psi_parser {
	PSI_DATA_MEMBERS;
	FILE *fp;
	token_t num;
	void *proc;
	unsigned line, col;
	char *cur, *tok, *lim, *eof, *ctx, *mrk, buf[BSIZE];
};

#define PSI_PARSER_DEBUG 0x1
#define PSI_PARSER_SILENT 0x2

struct psi_parser *psi_parser_init(struct psi_parser *P, const char *filename, psi_error_cb error, unsigned flags);
void psi_parser_syntax_error(struct psi_parser *P, const char *fn, size_t ln, const char *msg, ...);
size_t psi_parser_fill(struct psi_parser *P, size_t n);
token_t psi_parser_scan(struct psi_parser *P);
void psi_parser_parse(struct psi_parser *P, struct psi_token *src);
void psi_parser_dtor(struct psi_parser *P);
void psi_parser_free(struct psi_parser **P);

#endif
