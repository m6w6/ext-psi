#ifndef _PSI_TYPES_IMPLS_H
#define _PSI_TYPES_IMPLS_H

typedef struct impls {
	size_t count;
	impl **list;
} impls;

static inline impls *add_impl(impls *impls, impl *impl) {
	if (!impls) {
		impls = calloc(1, sizeof(*impls));
	}
	impls->list = realloc(impls->list, ++impls->count * sizeof(*impls->list));
	impls->list[impls->count-1] = impl;
	return impls;
}

static inline void free_impls(impls *impls) {
	size_t i;

	for (i = 0; i < impls->count; ++i) {
		free_impl(impls->list[i]);
	}
	free(impls->list);
	free(impls);
}

#endif
