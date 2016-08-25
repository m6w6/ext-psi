#ifndef _PSI_TYPES_IMPL_VAR_H
#define _PSI_TYPES_IMPL_VAR_H

typedef struct impl_var {
	struct psi_token *token;
	char *name;
	struct impl_arg *arg;
	unsigned reference:1;
} impl_var;

static inline impl_var *init_impl_var(const char *name, int is_reference) {
	impl_var *var = calloc(1, sizeof(*var));
	var->name = strdup(name);
	var->reference = is_reference;
	return var;
}

static inline impl_var *copy_impl_var(impl_var *var) {
	impl_var *cpy = malloc(sizeof(*cpy));

	memcpy(cpy, var, sizeof(*cpy));
	cpy->name = strdup(cpy->name);
	if (cpy->token) {
		cpy->token = psi_token_copy(cpy->token);
	}
	return cpy;
}

static inline void free_impl_var(impl_var *var) {
	if (var->token) {
		free(var->token);
	}
	free(var->name);
	free(var);
}

#endif
