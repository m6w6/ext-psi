#ifndef _PSI_TYPES_DECL_UNION_H

typedef struct decl_union {
	struct psi_token *token;
	char *name;
	decl_args *args;
	size_t size;
	size_t align;
} decl_union;

static inline decl_union *init_decl_union(const char *name, decl_args *args) {
	decl_union *u = calloc(1, sizeof(*u));
	u->name = strdup(name);
	u->args = args;
	return u;
}

static inline void free_decl_union(decl_union *u) {
	if (u->token) {
		free(u->token);
	}
	if (u->args) {
		free_decl_args(u->args);
	}
	free(u->name);
	free(u);
}

#endif
