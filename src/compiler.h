#ifndef _PSI_COMPILER_H
#define _PSI_COMPILER_H

#include "validator.h"

typedef struct PSI_Compiler {
	PSI_DATA_MEMBERS;
	void *context;
} PSI_Compiler;

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V, void *context);
void PSI_CompilerDtor(PSI_Compiler *C);
void PSI_CompilerFree(PSI_Compiler **C);
zend_function_entry *PSI_CompilerCompile(PSI_Compiler *C);

#endif
