#ifndef _PSI_TYPES_IMPL_TYPE_H
#define _PSI_TYPES_IMPL_TYPE_H

typedef struct impl_type {
	char *name;
	token_t type;
} impl_type;

static inline impl_type *init_impl_type(token_t type, const char *name) {
	impl_type *t = calloc(1, sizeof(*t));

	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline void free_impl_type(impl_type *type) {
	free(type->name);
	free(type);
}

#endif
