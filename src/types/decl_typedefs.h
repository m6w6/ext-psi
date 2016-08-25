#ifndef _PSI_TYPES_DECL_TYPEDEFS_H
#define _PSI_TYPES_DECL_TYPEDEFS_H

typedef struct decl_typedefs {
	size_t count;
	decl_arg **list;
} decl_typedefs;

static inline decl_typedefs *add_decl_typedef(decl_typedefs *defs, decl_arg *def) {
	if (!defs) {
		defs = calloc(1, sizeof(*defs));
	}
	defs->list = realloc(defs->list, ++defs->count * sizeof(*defs->list));
	defs->list[defs->count-1] = def;
	return defs;
}

static inline void free_decl_typedefs(decl_typedefs *defs) {
	size_t i;

	for (i = 0; i < defs->count; ++i) {
		free_decl_arg(defs->list[i]);
	}
	free(defs->list);
	free(defs);
}

#endif
