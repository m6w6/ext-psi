#include <stdlib.h>

#include "compiler.h"

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V)
{
	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	PSI_DataExchange((PSI_Data *) C, (PSI_Data *) V);
	return C;
}
