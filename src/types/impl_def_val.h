#ifndef _PSI_TYPES_IMPL_DEF_VAL_H
#define _PSI_TYPES_IMPL_DEF_VAL_H

typedef struct impl_def_val {
	token_t type;
	char *text;
} impl_def_val;

static inline impl_def_val *init_impl_def_val(token_t t, const char *text) {
	impl_def_val *def = calloc(1, sizeof(*def));
	def->type = t;
	def->text = strdup(text);
	return def;
}

static inline void free_impl_def_val(impl_def_val *def) {
	free(def->text);
	free(def);
}

#endif
