#ifndef _PSI_TYPES_DECL_STRUCTS_H
#define _PSI_TYPES_DECL_STRUCTS_H

typedef struct decl_structs {
	size_t count;
	decl_struct **list;
} decl_structs;

static inline decl_structs *add_decl_struct(decl_structs *ss, decl_struct *s) {
	if (!ss) {
		ss = calloc(1, sizeof(*ss));
	}
	ss->list = realloc(ss->list, ++ss->count * sizeof(*ss->list));
	ss->list[ss->count-1] = s;
	return ss;
}

static inline void free_decl_structs(decl_structs *ss) {
	size_t i;

	for (i = 0; i < ss->count; ++i) {
		free_decl_struct(ss->list[i]);
	}
	free(ss->list);
	free(ss);
}

#endif
