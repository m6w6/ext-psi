#ifndef _PSI_TYPES_IMPL_H
#define _PSI_TYPES_IMPL_H

typedef struct impl {
	impl_func *func;
	impl_stmts *stmts;
	decl *decl;
} impl;

static inline impl *init_impl(impl_func *func, impl_stmts *stmts) {
	impl *i = calloc(1, sizeof(*i));
	i->func = func;
	i->stmts = stmts;
	return i;
}

static inline void free_impl(impl *impl) {
	free_impl_func(impl->func);
	free_impl_stmts(impl->stmts);
	free(impl);
}

#endif
