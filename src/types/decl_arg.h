#ifndef _PSI_TYPES_DECL_ARG_H
#define _PSI_TYPES_DECL_ARG_H

typedef struct decl_arg {
	struct psi_token *token;
	decl_type *type;
	decl_var *var;
	decl_struct_layout *layout;
	impl_val val;
	void *ptr;
	void *let;
	void *mem;
} decl_arg;

static inline decl_arg *init_decl_arg(decl_type *type, decl_var *var) {
	decl_arg *arg = calloc(1, sizeof(*arg));
	arg->token = var->token;
	arg->type = type;
	arg->var = var;
	var->arg = arg;
	arg->ptr = &arg->val;
	arg->let = arg->ptr;
	return arg;
}

static inline void free_decl_arg(decl_arg *arg) {
	if (arg->token && arg->token != arg->var->token) {
		free(arg->token);
	}
	free_decl_type(arg->type);
	free_decl_var(arg->var);
	if (arg->layout) {
		free_decl_struct_layout(arg->layout);
	}
	free(arg);
}

#endif
