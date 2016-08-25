#ifndef _PSI_TYPES_LET_CALLOC_H
#define _PSI_TYPES_LET_CALLOC_H

typedef struct let_calloc {
	num_exp *nmemb;
	num_exp *size;
} let_calloc;

static inline let_calloc *init_let_calloc(num_exp *nmemb, num_exp *size) {
	let_calloc *alloc = calloc(1, sizeof(*alloc));
	alloc->nmemb = nmemb;
	alloc->size = size;
	return alloc;
}

static inline void free_let_calloc(let_calloc *alloc) {
	free_num_exp(alloc->nmemb);
	free_num_exp(alloc->size);
	free(alloc);
}

#endif
