#ifndef _PSI_CONTEXT_H
#define _PSI_CONTEXT_H

struct psi_context;
struct psi_token;
struct psi_parser;
struct decl_callinfo;
struct impl_vararg;

struct psi_context_ops {
	void (*init)(struct psi_context *C);
	void (*dtor)(struct psi_context *C);
	zend_function_entry *(*compile)(struct psi_context *C);
	void (*call)(struct psi_context *C, struct decl_callinfo *decl_call, struct impl_vararg *va);
};

#include "data.h"

struct psi_context {
	PSI_DATA_MEMBERS;
	void *context;
	struct psi_context_ops *ops;
	zend_function_entry *closures;
	struct psi_data *data;
	size_t count;
};

struct psi_context *psi_context_init(struct psi_context *C, struct psi_context_ops *ops, psi_error_cb error, unsigned flags);
void psi_context_build(struct psi_context *C, const char *path);
int psi_context_validate(struct psi_context *C, struct psi_parser *P);
int psi_context_validate_data(struct psi_data *C, struct psi_data *D);
zend_function_entry *psi_context_compile(struct psi_context *C);
void psi_context_call(struct psi_context *C, struct decl_callinfo *decl_call, struct impl_vararg *va);
void psi_context_dump(struct psi_context *C, int fd);
void psi_context_dtor(struct psi_context *C);
void psi_context_free(struct psi_context **C);

#endif
