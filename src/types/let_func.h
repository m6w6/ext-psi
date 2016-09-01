#ifndef _PSI_TYPES_LET_FUNC_H
#define _PSI_TYPES_LET_FUNC_H

typedef impl_val *(*let_func_handler)(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);

struct let_val;
struct let_vals;
static inline void free_let_vals(struct let_vals *vals);

typedef struct let_func {
	token_t type;
	char *name;
	impl_var *var;
	let_func_handler handler;
	struct let_vals *inner;
	struct let_val *outer;
	decl_arg *ref;
} let_func;

static inline let_func *init_let_func(token_t type, const char *name, impl_var *var) {
	let_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	func->var = var;
	return func;
}

static inline void free_let_func(let_func *func) {
	free_impl_var(func->var);
	free(func->name);
	if (func->inner) {
		free_let_vals(func->inner);
	}
	free(func);
}

#endif
