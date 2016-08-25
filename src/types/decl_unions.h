#ifndef _PSI_TYPES_DECL_UNOINS_H
#define _PSI_TYPES_DECL_UNOINS_H

typedef struct decl_unions {
	decl_union **list;
	size_t count;
} decl_unions;

static inline decl_unions *add_decl_union(decl_unions *uu, decl_union *u) {
	if (!uu) {
		uu = calloc(1, sizeof(*uu));
	}
	uu->list = realloc(uu->list, ++uu->count * sizeof(*uu->list));
	uu->list[uu->count-1] = u;
	return uu;
}

static inline void free_decl_unions(decl_unions *uu) {
	size_t i;

	for (i = 0; i < uu->count; ++i) {
		free_decl_union(uu->list[i]);
	}
	free(uu->list);
	free(uu);
}

#endif
