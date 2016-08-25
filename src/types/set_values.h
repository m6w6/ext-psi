#ifndef _PSI_TYPES_SET_VALUES_H
#define _PSI_TYPES_SET_VALUES_H

typedef struct set_values {
	struct set_value **vals;
	size_t count;
} set_values;

static inline set_values *init_set_values(struct set_value *val) {
	set_values *vals = calloc(1, sizeof(*vals));
	if (val) {
		vals->count = 1;
		vals->vals = calloc(1, sizeof(val));
		vals->vals[0] = val;
	}
	return vals;
}

static inline set_values *add_set_value(set_values *vals, struct set_value *val) {
	if (!vals) {
		vals = calloc(1, sizeof(*vals));
	}
	vals->vals = realloc(vals->vals, ++vals->count * sizeof(val));
	vals->vals[vals->count-1] = val;
	return vals;
}

static inline void free_set_values(set_values *vals) {
	if (vals->vals) {
		size_t i;

		for (i = 0; i < vals->count; ++i) {
			free_set_value(vals->vals[i]);
		}
		free(vals->vals);
	}
	free(vals);
}

#endif
