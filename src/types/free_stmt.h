#ifndef _PSI_TYPES_FREE_STMT_H
#define _PSI_TYPES_FREE_STMT_H

typedef struct free_stmt {
	free_calls *calls;
} free_stmt;

static inline free_stmt *init_free_stmt(free_calls *calls) {
	free_stmt *f = calloc(1, sizeof(*f));
	f->calls = calls;
	return f;
}

static inline void free_free_stmt(free_stmt *f) {
	free_free_calls(f->calls);
	free(f);
}

#endif
