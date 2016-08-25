#ifndef _PSI_TYPES_DECL_VARS_H
#define _PSI_TYPES_DECL_VARS_H

typedef struct decl_vars {
	decl_var **vars;
	size_t count;
} decl_vars;

static inline decl_vars *init_decl_vars(decl_var *var) {
	decl_vars *vars = calloc(1, sizeof(*vars));
	if (var) {
		vars->count = 1;
		vars->vars = calloc(1, sizeof(*vars->vars));
		vars->vars[0] = var;
	}
	return vars;
}

static inline decl_vars *add_decl_var(decl_vars *vars, decl_var *var) {
	vars->vars = realloc(vars->vars, ++vars->count * sizeof(*vars->vars));
	vars->vars[vars->count-1] = var;
	return vars;
}

static inline void free_decl_vars(decl_vars *vars) {
	size_t i;

	for (i = 0; i < vars->count; ++i) {
		free_decl_var(vars->vars[i]);
	}
	free(vars->vars);
	free(vars);
}

#endif
