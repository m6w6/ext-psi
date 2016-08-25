#ifndef _PSI_TYPES_LET_STMT_H
#define _PSI_TYPES_LET_STMT_H

typedef struct let_stmt {
	decl_var *var;
	let_val *val;
} let_stmt;

static inline let_stmt *init_let_stmt(decl_var *var, let_val *val) {
	let_stmt *let = calloc(1, sizeof(*let));
	let->var = var;
	let->val = val;
	return let;
}

static inline void free_let_stmt(let_stmt *stmt) {
	if (stmt->val) {
		if (stmt->val->kind == PSI_LET_TMP && stmt->var->arg) {
			free_decl_arg(stmt->var->arg);
		}
		free_let_val(stmt->val);
	}
	free_decl_var(stmt->var);
	free(stmt);
}

#endif
