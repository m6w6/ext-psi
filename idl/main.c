#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "validator.h"

static int TRACE;

static void loop(PSI_Lexer *L, void *P)
{
	token_t t;
	PSI_Token *T = NULL;

	if (TRACE) {
		PSI_ParserTrace(stdout, "> ");
	}

	while (-1 != (t = PSI_LexerScan(L))) {
		if (!(T = PSI_TokenAlloc(L, t))) {
			break;
		}

		if (TRACE) {
			printf("# Token: <%s>(%d)\n", T->text, t);
		}

		PSI_Parser(P, t, T, L);
	}
	PSI_Parser(P, 0, T, L);
}

int main(int argc, char *argv[])
{
	PSI_Lexer L;
	PSI_Validator V;
	void *P = PSI_ParserAlloc(malloc);

	TRACE = !!getenv("TRACE");

	if (!PSI_LexerInit(&L, argv[1])) {
		perror("Failed to init lexer");
		return 1;
	}

	loop(&L, P);

	PSI_ParserFree(P, free);

	if (!PSI_ValidatorInit(&V, &L)) {
		perror("Failed to init validator");
		return 2;
	}

	PSI_LexerDtor(&L);

	if (PSI_ValidatorValidate(&V)) {
		printf("Whoa! VALID.\n");
	}
	PSI_ValidatorDtor(&V);

	return 0;
}
