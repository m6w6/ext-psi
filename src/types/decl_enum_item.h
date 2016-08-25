#ifndef _PSI_TYPES_DECL_ENUM_ITEM_H
#define _PSI_TYPES_DECL_ENUM_ITEM_H

typedef struct decl_enum_item {
	struct psi_token *token;
	char *name;
	num_exp *num;
	num_exp inc;
	struct decl_enum_item *prev;
} decl_enum_item;

static inline decl_enum_item *init_decl_enum_item(const char *name, num_exp *num) {
	decl_enum_item *i = calloc(1, sizeof(*i));

	i->name = strdup(name);
	i->num = num;
	return i;
}

static inline void free_decl_enum_item(decl_enum_item *i) {
	if (i->token) {
		free(i->token);
	}
	if (i->num && i->num != &i->inc) {
		free_num_exp(i->num);
	}
	free(i->name);
	free(i);
}

#endif
