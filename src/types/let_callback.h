#ifndef _PSI_TYPES_LET_CALLBACK_H
#define _PSI_TYPES_LET_CALLBACK_H

typedef struct let_callback {
	struct let_func *func;
	struct set_values *args;
	decl *decl;
} let_callback;

static inline void free_let_func(struct let_func *func);
static inline void free_set_values(struct set_values *vals);
static inline let_callback *init_let_callback(struct let_func *func, struct set_values *args) {
	let_callback *cb = calloc(1, sizeof(*cb));

	cb->func = func;
	cb->args = args;
	return cb;
}

static inline void free_let_callback(let_callback *cb) {
	free_let_func(cb->func);
	free_set_values(cb->args);
	free(cb);
}

#endif
