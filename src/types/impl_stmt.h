#ifndef _PSI_TYPES_IMPL_STMT_H
#define _PSI_TYPES_IMPL_STMT_H

typedef struct impl_stmt {
	token_t type;
	union {
		let_stmt *let;
		set_stmt *set;
		return_stmt *ret;
		free_stmt *fre;
		void *ptr;
	} s;
} impl_stmt;

static inline impl_stmt *init_impl_stmt(token_t type, void *ptr) {
	impl_stmt *stmt = calloc(1, sizeof(*stmt));
	stmt->type = type;
	stmt->s.ptr = ptr;
	return stmt;
}

static inline void free_impl_stmt(impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_LET:
		free_let_stmt(stmt->s.let);
		break;
	case PSI_T_SET:
		free_set_stmt(stmt->s.set);
		break;
	case PSI_T_RETURN:
		free_return_stmt(stmt->s.ret);
		break;
	case PSI_T_FREE:
		free_free_stmt(stmt->s.fre);
		break;
	}
	free(stmt);
}

#endif
