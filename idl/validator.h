
typedef struct PSI_Validator {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
	void *dlopened;
} PSI_Validator;

PSI_Validator *PSI_ValidatorInit(PSI_Validator *V, PSI_Lexer *L);
int PSI_ValidatorValidate(PSI_Validator *V);
void PSI_ValidatorDtor(PSI_Validator *V);
void PSI_ValidatorFree(PSI_Validator **V);
