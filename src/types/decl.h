#ifndef _PSI_TYPES_DECL_H
#define _PSI_TYPES_DECL_H

typedef struct decl {
	decl_abi *abi;
	decl_arg *func;
	decl_args *args;
	struct impl *impl;
	decl_callinfo call;
} decl;

static inline decl* init_decl(decl_abi *abi, decl_arg *func, decl_args *args) {
	decl *d = calloc(1, sizeof(*d));
	d->abi = abi;
	d->func = func;
	d->args = args;
	return d;
}

static inline void free_decl(decl *d) {
	free_decl_abi(d->abi);
	free_decl_arg(d->func);
	if (d->args) {
		free_decl_args(d->args);
	}
	free(d);
}

#endif
