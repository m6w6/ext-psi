#ifndef _PSI_CONTEXT_H
#define _PSI_CONTEXT_H

#define PSI_ERROR 16
#define PSI_WARNING 32
typedef void (*PSI_ContextErrorFunc)(int type, const char *msg, ...);

typedef struct PSI_ContextOps {
	void (*init)(struct PSI_Context *C);
	void (*dtor)(struct PSI_Context *C);
	zend_function_entry *(*compile)(struct PSI_Context *C, struct PSI_Data *D);
} PSI_ContextOps;

typedef struct PSI_Context {
	void *opaque;
	PSI_ContextErrorFunc error;
	struct PSI_ContextOps *ops;
	struct PSI_Data *data;
	zend_function_entry **closures;
	size_t count;
} PSI_Context;

PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error);
void PSI_ContextBuild(PSI_Context *C, const char *path);
zend_function_entry *PSI_ContextCompile(PSI_Context *C, PSI_Data *D);
void PSI_ContextDtor(PSI_Context *C);
void PSI_ContextFree(PSI_Context **C);

#endif
