#ifndef _PSI_TYPES_DECL_VAR_H
#define _PSI_TYPES_DECL_VAR_H

typedef struct decl_var {
	struct psi_token *token;
	char *name;
	unsigned pointer_level;
	unsigned array_size;
	struct decl_arg *arg;
} decl_var;

static inline decl_var *init_decl_var(const char *name, unsigned pl, unsigned as) {
	decl_var *v = calloc(1, sizeof(*v));
	v->name = (char *) strdup((const char *) name);
	v->pointer_level = pl;
	v->array_size = as;
	return v;
}

static inline decl_var *copy_decl_var(decl_var *src) {
	decl_var *dest = calloc(1, sizeof(*dest));

	memcpy(dest, src, sizeof(*dest));
	dest->name = strdup(dest->name);
	if (dest->token) {
		dest->token = psi_token_copy(dest->token);
	}
	return dest;
}

static inline void free_decl_var(decl_var *var) {
	if (var->token) {
		free(var->token);
	}
	free(var->name);
	free(var);
}

#endif
