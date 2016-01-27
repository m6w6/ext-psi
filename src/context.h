#ifndef _PSI_CONTEXT_H
#define _PSI_CONTEXT_H

#include "parser.h"

#define PSI_ERROR 16
#define PSI_WARNING 32
typedef void (*PSI_ContextErrorFunc)(PSI_Token *token, int type, const char *msg, ...);

typedef struct PSI_Context PSI_Context;
typedef struct PSI_ContextOps PSI_ContextOps;

struct PSI_ContextOps {
	void (*init)(PSI_Context *C);
	void (*dtor)(PSI_Context *C);
	zend_function_entry *(*compile)(PSI_Context *C);
	void (*call)(PSI_Context *C, decl_callinfo *decl_call, impl_vararg *va);
};

struct PSI_Context {
	PSI_DATA_MEMBERS;
	void *context;
	struct PSI_ContextOps *ops;
	zend_function_entry *closures;
	PSI_Data *data;
	size_t count;
};

PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error);
void PSI_ContextBuild(PSI_Context *C, const char *path);
int PSI_ContextValidate(PSI_Context *C, PSI_Parser *P);
int PSI_ContextValidateData(PSI_Data *C, PSI_Data *D);
zend_function_entry *PSI_ContextCompile(PSI_Context *C);
void PSI_ContextCall(PSI_Context *C, decl_callinfo *decl_call, impl_vararg *va);
void PSI_ContextDump(PSI_Context *C, int fd);
void PSI_ContextDtor(PSI_Context *C);
void PSI_ContextFree(PSI_Context **C);

#endif
