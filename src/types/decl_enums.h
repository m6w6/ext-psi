#ifndef _PSI_TYPES_DECL_ENUMS_H
#define _PSI_TYPES_DECL_ENUMS_H

typedef struct decl_enums {
	decl_enum **list;
	size_t count;
} decl_enums;

static inline decl_enums* add_decl_enum(decl_enums *es, decl_enum *e) {
	if (!es) {
		es = calloc(1, sizeof(*es));
	}
	es->list = realloc(es->list, ++es->count * sizeof(*es->list));
	es->list[es->count-1] = e;
	return es;
}

static inline void free_decl_enums(decl_enums *es) {
	if (es->list) {
		size_t j;

		for (j = 0; j < es->count; ++j) {
			free_decl_enum(es->list[j]);
		}
	}
	free(es->list);
	free(es);
}

#endif
