#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "validator.h"

static int TRACE;

int main(int argc, char *argv[])
{
	PSI_Parser P;
	PSI_Validator V;

	TRACE = !!getenv("TRACE");

	if (!PSI_ParserInit(&P, argv[1])) {
		perror("Failer to init parser");
		return 1;
	}

	while (-1 != PSI_ParserScan(&P)) {
		PSI_ParserParse(&P, PSI_TokenAlloc(&P));
	};
	PSI_ParserParse(&P, NULL);

	if (!PSI_ValidatorInit(&V, &P)) {
		perror("Failed to init validator");
		return 2;
	}

	PSI_ParserDtor(&P);

	if (PSI_ValidatorValidate(&V)) {
		printf("Whoa! VALID.\n");
	}
	PSI_ValidatorDtor(&V);

	return 0;
}
