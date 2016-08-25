#ifndef _PSI_TYPES_DECL_STRUCT_LAYOUT_H
#define _PSI_TYPES_DECL_STRUCT_LAYOUT_H

typedef struct decl_struct_layout {
	size_t pos;
	size_t len;
} decl_struct_layout;

static inline decl_struct_layout *init_decl_struct_layout(size_t pos, size_t len) {
	decl_struct_layout *l = calloc(1, sizeof(*l));
	ZEND_ASSERT(pos+len);
	l->pos = pos;
	l->len = len;
	return l;
}

static inline void free_decl_struct_layout(decl_struct_layout *l) {
	free(l);
}

#endif
