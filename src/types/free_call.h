#ifndef _PSI_TYPES_FREE_CALL_H
#define _PSI_TYPES_FREE_CALL_H

typedef struct free_call {
	struct psi_token *token;
	char *func;
	decl_vars *vars;
	decl *decl;
} free_call;

static inline free_call *init_free_call(const char *func, decl_vars *vars) {
	free_call *f = calloc(1, sizeof(*f));
	f->func = strdup(func);
	f->vars = vars;
	return f;
}

static inline void free_free_call(free_call *f) {
	if (f->token) {
		free(f->token);
	}
	free(f->func);
	free_decl_vars(f->vars);
	free(f);
}

#endif
