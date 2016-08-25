#ifndef _PSI_TYPES_DECL_TYPE_H
#define _PSI_TYPES_DECL_TYPE_H

#include "parser_proc.h"

typedef struct decl_type {
	struct psi_token *token;
	char *name;
	token_t type;
	union {
		struct decl_arg *def;
		struct decl_struct *strct;
		struct decl_union *unn;
		struct decl_enum *enm;
		struct decl *func;
	} real;
} decl_type;

static inline decl_type *init_decl_type(token_t type, const char *name) {
	decl_type *t = calloc(1, sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline void free_decl(struct decl *decl);
static inline void free_decl_type(decl_type *type) {
	if (type->token) {
		free(type->token);
	}
	if (type->type == PSI_T_FUNCTION) {
		free_decl(type->real.func);
	}
	free(type->name);
	free(type);
}


#endif
