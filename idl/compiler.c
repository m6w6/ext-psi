#include <stdlib.h>

#include "compiler.h"

#if INTERFACE
typedef struct PSI_Compiler {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
} PSI_Compiler;
#endif

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V)
{

}
