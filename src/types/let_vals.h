#ifndef _PSI_TYPES_LET_VALS_H
#define _PSI_TYPES_LET_VALS_H

struct let_val;

typedef struct let_vals {
	struct let_val **vals;
	size_t count;
} let_vals;

static inline let_vals *init_let_vals(struct let_val *val) {
	let_vals *vals = calloc(1, sizeof(*vals));
	if (val) {
		vals->count = 1;
		vals->vals = calloc(1, sizeof(val));
		vals->vals[0] = val;
	}
	return vals;
}

static inline let_vals *add_let_val(let_vals *vals, struct let_val *val) {
	if (!vals) {
		vals = calloc(1, sizeof(*vals));
	}
	vals->vals = realloc(vals->vals, ++vals->count * sizeof(val));
	vals->vals[vals->count-1] = val;
	return vals;
}

static inline void free_let_vals(let_vals *vals) {
	if (vals->vals) {
		size_t i;

		for (i = 0; i < vals->count; ++i) {
			free_let_val(vals->vals[i]);
		}
		free(vals->vals);
	}
	free(vals);
}

#endif
