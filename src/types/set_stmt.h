#ifndef _PSI_TYPES_SET_STMT_H
#define _PSI_TYPES_SET_STMT_H

typedef struct set_stmt {
	impl_var *var;
	set_value *val;
	impl_arg *arg;
} set_stmt;

static inline set_stmt *init_set_stmt(impl_var *var, set_value *val) {
	set_stmt *set = calloc(1, sizeof(*set));
	set->var = var;
	set->val = val;
	return set;
}

static inline void free_set_stmt(set_stmt *set) {
	free_impl_var(set->var);
	free_set_value(set->val);
	free(set);
}

#endif
