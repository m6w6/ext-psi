#ifndef _PSI_TYPES_DECL_ENUM_ITEMS_H
#define _PSI_TYPES_DECL_ENUM_ITEMS_H

typedef struct decl_enum_items {
	decl_enum_item **list;
	size_t count;
} decl_enum_items;

static inline decl_enum_items *init_decl_enum_items(decl_enum_item *i) {
	decl_enum_items *l = calloc(1, sizeof(*l));

	if (i) {
		l->count = 1;
		l->list = calloc(1, sizeof(*l->list));
		l->list[0] = i;
	}
	return l;
}

static inline decl_enum_items *add_decl_enum_item(decl_enum_items *l, decl_enum_item *i) {
	l->list = realloc(l->list, sizeof(*l->list) * (l->count + 1));
	l->list[l->count] = i;
	if (l->count) {
		i->prev = l->list[l->count - 1];
	}
	++l->count;
	return l;
}

static inline void free_decl_enum_items(decl_enum_items *l) {
	if (l->list) {
		size_t j;

		for (j = 0; j < l->count; ++j) {
			free_decl_enum_item(l->list[j]);
		}
		free(l->list);
	}
	free(l);
}

#endif
