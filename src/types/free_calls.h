#ifndef _PSI_TYPES_FREE_CALLS_H
#define _PSI_TYPES_FREE_CALLS_H

typedef struct free_calls {
	free_call **list;
	size_t count;
} free_calls;

static inline free_calls *init_free_calls(free_call *f) {
	free_calls *fcs = calloc(1, sizeof(*fcs));
	if (f) {
		fcs->count = 1;
		fcs->list = calloc(1, sizeof(*fcs->list));
		fcs->list[0] = f;
	}
	return fcs;
}

static inline void free_free_calls(free_calls *fcs) {
	size_t i;

	for (i = 0; i < fcs->count; ++i) {
		free_free_call(fcs->list[i]);
	}
	free(fcs->list);
	free(fcs);
}

static inline free_calls *add_free_call(free_calls *fcs, free_call *f) {
	fcs->list = realloc(fcs->list, ++fcs->count * sizeof(*fcs->list));
	fcs->list[fcs->count-1] = f;
	return fcs;
}

#endif
