#ifndef _PSI_TYPES_CONSTANT_H
#define _PSI_TYPES_CONSTANT_H

typedef struct constant {
	const_type *type;
	char *name;
	impl_def_val *val;
} constant;

static inline constant *init_constant(const_type *type, const char *name, impl_def_val *val) {
	constant *c = calloc(1, sizeof(*c));
	c->type = type;
	c->name = strdup(name);
	c->val = val;
	return c;
}

static inline void free_constant(constant *constant) {
	free_const_type(constant->type);
	free(constant->name);
	free_impl_def_val(constant->val);
	free(constant);
}

#endif
