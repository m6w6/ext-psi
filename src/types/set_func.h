#ifndef _PSI_TYPES_SET_FUNC_H
#define _PSI_TYPES_SET_FUNC_H

struct set_value;

typedef struct set_func {
	struct psi_token *token;
	token_t type;
	char *name;
	void (*handler)(zval *, struct set_value *set, impl_val *ret_val);
} set_func;

static inline set_func *init_set_func(token_t type, const char *name) {
	set_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	return func;
}

static inline void free_set_func(set_func *func) {
	if (func->token) {
		free(func->token);
	}
	free(func->name);
	free(func);
}

#endif
