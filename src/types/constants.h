#ifndef _PSI_TYPES_CONSTANTS_H
#define _PSI_TYPES_CONSTANTS_H

typedef struct constants {
	size_t count;
	constant **list;
} constants;

static inline constants *add_constant(constants *constants, constant *constant) {
	if (!constants) {
		constants = calloc(1, sizeof(*constants));
	}
	constants->list = realloc(constants->list, ++constants->count * sizeof(*constants->list));
	constants->list[constants->count-1] = constant;
	return constants;
}

static inline void free_constants(constants *c) {
	size_t i;

	for (i = 0; i < c->count; ++i) {
		free_constant(c->list[i]);
	}
	free(c->list);
	free(c);
}

#endif
