#ifndef _PSI_TYPES_IMPL_STMTS_H
#define _PSI_TYPES_IMPL_STMTS_H

typedef struct impl_stmts {
	struct {
		return_stmt **list;
		size_t count;
	} ret;
	struct {
		let_stmt **list;
		size_t count;
	} let;
	struct {
		set_stmt **list;
		size_t count;
	} set;
	struct {
		free_stmt **list;
		size_t count;
	} fre;
} impl_stmts;

static inline void *add_impl_stmt_ex(void *list, size_t count, void *stmt) {
	list = realloc(list, count * sizeof(list));
	((void **)list)[count-1] = stmt;
	return list;
}

static inline impl_stmts *add_impl_stmt(impl_stmts *stmts, impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_RETURN:
		stmts->ret.list = add_impl_stmt_ex(stmts->ret.list, ++stmts->ret.count, stmt->s.ret);
		break;
	case PSI_T_LET:
		stmts->let.list = add_impl_stmt_ex(stmts->let.list, ++stmts->let.count, stmt->s.let);
		break;
	case PSI_T_SET:
		stmts->set.list = add_impl_stmt_ex(stmts->set.list, ++stmts->set.count, stmt->s.set);
		break;
	case PSI_T_FREE:
		stmts->fre.list = add_impl_stmt_ex(stmts->fre.list, ++stmts->fre.count, stmt->s.fre);
		break;
	}
	free(stmt);
	return stmts;
}

static inline impl_stmts *init_impl_stmts(impl_stmt *stmt) {
	impl_stmts *stmts = calloc(1, sizeof(*stmts));
	return add_impl_stmt(stmts, stmt);
}

static inline void free_impl_stmts(impl_stmts *stmts) {
	size_t i;

	for (i = 0; i < stmts->let.count; ++i) {
		free_let_stmt(stmts->let.list[i]);
	}
	free(stmts->let.list);
	for (i = 0; i < stmts->ret.count; ++i) {
		free_return_stmt(stmts->ret.list[i]);
	}
	free(stmts->ret.list);
	for (i = 0; i < stmts->set.count; ++i) {
		free_set_stmt(stmts->set.list[i]);
	}
	free(stmts->set.list);
	for (i = 0; i < stmts->fre.count; ++i) {
		free_free_stmt(stmts->fre.list[i]);
	}
	free(stmts->fre.list);
	free(stmts);
}

#endif
