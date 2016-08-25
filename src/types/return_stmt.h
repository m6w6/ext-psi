#ifndef _PSI_TYPES_RETURN_STMT_H
#define _PSI_TYPES_RETURN_STMT_H

typedef struct return_stmt {
	struct psi_token *token;
	set_value *set;
	decl_arg *decl;
} return_stmt;

static inline return_stmt *init_return_stmt(set_value *val) {
	return_stmt *ret = calloc(1, sizeof(*ret));
	ret->set = val;
	return ret;
}

static inline void free_return_stmt(return_stmt *ret) {
	if (ret->token) {
		free(ret->token);
	}
	free_set_value(ret->set);
	free(ret);
}

#endif
