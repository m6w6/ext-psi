#ifndef _PSI_COMPILER_H
#define _PSI_COMPILER_H

#include "types.h"
#include "validator.h"

typedef struct PSI_Compiler {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
} PSI_Compiler;

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V);
void PSI_CompilerDtor(PSI_Compiler *C);
void PSI_CompilerFree(PSI_Compiler **C);

#endif
