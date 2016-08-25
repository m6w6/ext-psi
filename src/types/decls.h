#ifndef _PSI_TYPES_DECLS_H
#define _PSI_TYPES_DECLS_H

typedef struct decls {
	size_t count;
	decl **list;
} decls;

static inline decls *add_decl(decls *decls, decl *decl) {
	if (!decls) {
		decls = calloc(1, sizeof(*decls));
	}
	decls->list = realloc(decls->list, ++decls->count * sizeof(*decls->list));
	decls->list[decls->count-1] = decl;
	return decls;
}

static inline void free_decls(decls *decls) {
	size_t i;

	for (i = 0; i < decls->count; ++i) {
		free_decl(decls->list[i]);
	}
	free(decls->list);
	free(decls);
}

#endif
