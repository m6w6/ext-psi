#include <stdlib.h>

#include <jit/jit.h>

#include <php.h>
#include <Zend/zend_API.h>

#include "compiler.h"

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V, void *context)
{
	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	PSI_DataExchange((PSI_Data *) C, (PSI_Data *) V);

	C->context = context;

	return C;
}

void PSI_CompilerDtor(PSI_Compiler *C)
{
	PSI_DataDtor((PSI_Data *) C);
}

void PSI_Compiler_Free(PSI_Compiler **C)
{
	if (*C) {
		PSI_CompilerDtor(*C);
		free(*C);
		*C = NULL;
	}
}


zend_function_entry *PSI_CompilerCompile(PSI_Compiler *C)
{
}
