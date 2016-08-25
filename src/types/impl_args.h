#ifndef _PSI_TYPES_IMPL_ARGS_H
#define _PSI_TYPES_IMPL_ARGS_H

typedef struct impl_args {
	impl_arg **args;
	size_t count;
	impl_vararg vararg;
} impl_args;

static inline impl_args *init_impl_args(impl_arg *arg) {
	impl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
	}
	return args;
}

static inline impl_args *add_impl_arg(impl_args *args, impl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count-1] = arg;
	return args;
}

static inline void free_impl_args(impl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		free_impl_arg(args->args[i]);
	}
	if (args->vararg.name) {
		free_impl_arg(args->vararg.name);
	}
	free(args->args);
	free(args);
}

#endif
