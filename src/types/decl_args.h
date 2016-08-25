#ifndef _PSI_TYPES_DECL_ARGS_H
#define _PSI_TYPES_DECL_ARGS_H

typedef struct decl_args {
	decl_arg **args;
	size_t count;
	unsigned varargs:1;
} decl_args;

static inline decl_args *init_decl_args(decl_arg *arg) {
	decl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
	}
	return args;
}

static inline decl_args *add_decl_arg(decl_args *args, decl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count-1] = arg;
	return args;
}

static inline void free_decl_args(decl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		free_decl_arg(args->args[i]);
	}
	free(args->args);
	free(args);
}

#endif
