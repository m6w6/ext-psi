#ifndef _PSI_TYPES_DECL_CALLINFO_H
#define _PSI_TYPES_DECL_CALLINFO_H

typedef struct decl_callinfo {
	void *sym;
	void *info;
	size_t argc;
	void **args;
	void **rval;
} decl_callinfo;

#endif
