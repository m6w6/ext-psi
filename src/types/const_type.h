#ifndef _PSI_TYPES_CONST_TYPE_H
#define _PSI_TYPES_CONST_TYPE_H

typedef struct const_type {
	token_t type;
	char *name;
} const_type;

static inline const_type *init_const_type(token_t type, const char *name) {
	const_type *ct = calloc(1, sizeof(*ct));
	ct->type = type;
	ct->name = strdup(name);
	return ct;
}

static inline void free_const_type(const_type *type) {
	free(type->name);
	free(type);
}

#endif
