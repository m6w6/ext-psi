#ifndef _PSI_TYPES_DECL_ENUM_H
#define _PSI_TYPES_DECL_ENUM_H

typedef struct decl_enum {
	struct psi_token *token;
	char *name;
	decl_enum_items *items;
} decl_enum;

static inline decl_enum *init_decl_enum(const char *name, decl_enum_items *l) {
	decl_enum *e = calloc(1, sizeof(*e));

	e->name = strdup(name);
	e->items = l;
	return e;
}

static inline void free_decl_enum(decl_enum *e) {
	if (e->token) {
		free(e->token);
	}
	if (e->items) {
		free_decl_enum_items(e->items);
	}
	free(e->name);
	free(e);
}

#endif
