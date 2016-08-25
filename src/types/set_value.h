#ifndef _PSI_TYPES_SET_VALUE_H
#define _PSI_TYPES_SET_VALUE_H

typedef struct set_value {
	set_func *func;
	decl_vars *vars;
	num_exp *num;
	struct {
		struct set_value *set;
		impl_val *val;
	} outer;
	struct set_values *inner;
} set_value;

static inline set_value *init_set_value(set_func *func, decl_vars *vars) {
	set_value *val = calloc(1, sizeof(*val));
	val->func = func;
	val->vars = vars;
	return val;
}

static inline struct set_values *add_set_value(struct set_values *vals, struct set_value *val);
static inline set_value *add_inner_set_value(set_value *val, set_value *inner) {
	val->inner = add_set_value(val->inner, inner);
	inner->outer.set = val;
	return val;
}

static inline void free_set_value(set_value *val) {
	if (val->func) {
		free_set_func(val->func);
	}
	if (val->vars) {
		free_decl_vars(val->vars);
	}
	if (val->inner && (!val->outer.set || val->outer.set->inner != val->inner)) {
		free_set_values(val->inner);
	}
	if (val->num) {
		free_num_exp(val->num);
	}
	free(val);
}

#endif
