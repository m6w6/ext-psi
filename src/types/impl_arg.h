#ifndef _PSI_TYPES_IMPL_ARG_H
#define _PSI_TYPES_IMPL_ARG_H

typedef struct impl_arg {
	impl_type *type;
	impl_var *var;
	impl_def_val *def;
	impl_val val;
	zval *_zv;
} impl_arg;

typedef struct impl_vararg {
	impl_arg *name;
	struct impl_args *args;
	token_t *types;
	impl_val *values;
	void **free_list;
} impl_vararg;

static inline impl_arg *init_impl_arg(impl_type *type, impl_var *var, impl_def_val *def) {
	impl_arg *arg = calloc(1, sizeof(*arg));
	arg->type = type;
	arg->var = var;
	arg->var->arg = arg;
	arg->def = def;
	return arg;
}

static inline void free_impl_arg(impl_arg *arg) {
	free_impl_type(arg->type);
	free_impl_var(arg->var);
	if (arg->def) {
		free_impl_def_val(arg->def);
	}
	free(arg);
}

#endif
