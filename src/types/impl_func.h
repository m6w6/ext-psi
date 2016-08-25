#ifndef _PSI_TYPES_IMPL_FUNC_H
#define _PSI_TYPES_IMPL_FUNC_H

typedef struct impl_func {
	struct psi_token *token;
	char *name;
	impl_args *args;
	impl_type *return_type;
	unsigned return_reference:1;
} impl_func;

static inline impl_func *init_impl_func(char *name, impl_args *args, impl_type *type, int ret_reference) {
	impl_func *func = calloc(1, sizeof(*func));
	func->name = strdup(name);
	func->args = args ? args : init_impl_args(NULL);
	func->return_type = type;
	func->return_reference = ret_reference;
	return func;
}

static inline void free_impl_func(impl_func *f) {
	if (f->token) {
		free(f->token);
	}
	free_impl_type(f->return_type);
	free_impl_args(f->args);
	free(f->name);
	free(f);
}

#endif
