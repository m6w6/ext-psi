#ifndef _PSI_TYPES_DECL_STRUCT_H
#define _PSI_TYPES_DECL_STRUCT_H

typedef struct decl_struct {
	struct psi_token *token;
	char *name;
	decl_args *args;
	size_t size;
	size_t align;
	struct {
		void *type;
		void (*dtor)(void *type);
	} engine;
} decl_struct;

static inline decl_struct *init_decl_struct(const char *name, decl_args *args) {
	decl_struct *s = calloc(1, sizeof(*s));
	s->name = strdup(name);
	s->args = args;
	return s;
}

static inline void free_decl_struct(decl_struct *s) {
	if (s->token) {
		free(s->token);
	}
	if (s->args) {
		free_decl_args(s->args);
	}
	if (s->engine.type && s->engine.dtor) {
		s->engine.dtor(s->engine.type);
	}
	free(s->name);
	free(s);
}

#endif
