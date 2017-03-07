/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "php_psi_stdinc.h"

#include "plist.h"

struct psi_plist {
	size_t size;
	size_t count;
	void (*dtor)(void *);
	void *list[0];
};

#define PLIST_ELE(l, i) (((char *)(l)->list) + (l)->size * (i))
#define PLIST_CPY(list, dest, src) do { \
	if (list->size == sizeof(void *)) { \
		*(void **)(dest) = *(void **)(src); \
	} else { \
		memcpy(dest, src, list->size); \
	} \
} while (0)
/* !!! adjust list->count prior reduction */
#define PLIST_MOV_REDUCE(l, i) PLIST_MOV_REDUCE_EX(l, i, 1)
#define PLIST_MOV_REDUCE_EX(l, i, n) memmove(PLIST_ELE(l, i), PLIST_ELE(l, i + n), (l)->size * ((l)->count - i))
/* !!! adjust list->count after expansion */
#define PLIST_MOV_EXPAND(l, i) PLIST_MOV_EXPAND_EX(l, i, 1)
#define PLIST_MOV_EXPAND_EX(l, i, n) memmove(PLIST_ELE(l, i + n), PLIST_ELE(l, i), (l)->size * ((l)->count - i))

struct psi_plist *psi_plist_init(void (*dtor)(void *)) {
	return psi_plist_init_ex(0, dtor);
}
struct psi_plist *psi_plist_init_ex(size_t size, void (*dtor)(void *)) {
	struct psi_plist *list;

	if (!size) {
		size = sizeof(void*);
	}

	list = calloc(1, sizeof(*list) + size);
	list->size = size;
	list->dtor = dtor;

	return list;
}

void psi_plist_clean(struct psi_plist *list) {
	size_t i;

	if (list->dtor) for (i = 0; i < list->count; ++i) {
		list->dtor(PLIST_ELE(list, i));
	}
	list->count = 0;
}

void psi_plist_free(struct psi_plist *list) {
	psi_plist_clean(list);
	free(list);
}

struct psi_plist *psi_plist_copy(struct psi_plist *list, void (*ctor)(void *))
{
	size_t i;
	struct psi_plist *copy = calloc(1, sizeof(*list) + list->size + list->count * list->size);

	*copy = *list;
	if (list->count) {
		memcpy(copy->list, list->list, list->size * list->count);
	}
	if (ctor) {
		for (i = 0; i < list->count; ++i) {
			void *ptr = PLIST_ELE(copy, i);
			ctor(ptr);
		}
	}
	return copy;
}

size_t psi_plist_count(struct psi_plist *list) {
	return list ? list->count : 0;
}

void **psi_plist_eles(struct psi_plist *list) {
	return list ? list->list : NULL;
}

struct psi_plist *psi_plist_add(struct psi_plist *list, void *ptr) {
	if (list && list->count) {
		list = realloc(list, sizeof(*list) + list->size + list->count * list->size);
	}
	if (list) {
		PLIST_CPY(list, PLIST_ELE(list, list->count++), ptr);
	}
	return list;
}

struct psi_plist *psi_plist_add_r(struct psi_plist *list, size_t num_eles, void **eles) {
	if (list && list->count) {
		list = realloc(list, sizeof(*list) + list->size + (num_eles + list->count) * list->size);
	}
	if (list) {
		memcpy(PLIST_ELE(list, list->count), eles, num_eles * list->size);
		list->count += num_eles;
	}
	return list;
}

bool psi_plist_get(struct psi_plist *list, size_t index, void *ptr) {
	if (list && list->count > index) {
		PLIST_CPY(list, ptr, PLIST_ELE(list, index));
		return true;
	}
	return false;
}

bool psi_plist_del(struct psi_plist *list, size_t index, void *ptr) {
	if (list && list->count > index) {
		if (ptr) {
			PLIST_CPY(list, ptr, PLIST_ELE(list, index));
		}
		if (--list->count > index) {
			PLIST_MOV_REDUCE(list, index);
		}
		return true;
	}
	return false;
}

bool psi_plist_del_r(struct psi_plist *list, size_t offset_start, size_t num_eles, void **eles) {
	if (list) {
		size_t offset_end = offset_start + num_eles - 1;

		if (list->count <= offset_end) {
			offset_end = list->count - 1;
		}
		if (offset_end >= offset_start) {
			num_eles = 1 + offset_end - offset_start;

			if (eles) {
				memcpy(eles, PLIST_ELE(list, offset_start), num_eles * list->size);
			}
			assert(list->count >= num_eles);
			if ((list->count -= num_eles)) {
				PLIST_MOV_REDUCE_EX(list, offset_start, num_eles);
			}
			return true;
		}
	}
	return false;
}

struct psi_plist *psi_plist_ins(struct psi_plist *list, size_t index, void *ptr) {
	size_t new_count;

	if (list) {
		new_count = MAX(list->count + 1, index);
		if (new_count) {
			list = realloc(list, sizeof(*list) + list->size + new_count * list->size);
		}
		if (list) {
			PLIST_MOV_EXPAND(list, index);
			PLIST_CPY(list, PLIST_ELE(list, index), ptr);
			list->count = new_count;
		}
	}
	return list;
}

struct psi_plist *psi_plist_ins_r(struct psi_plist *list, size_t offset_start, size_t num_eles, void **eles) {
	size_t new_count;

	if (list) {
		new_count = MAX(offset_start + 1, list->count) + num_eles;
		if (new_count) {
			list = realloc(list, sizeof(*list) + list->size + new_count * list->size);
		}
		if (list) {
			size_t e;

			PLIST_MOV_EXPAND_EX(list, offset_start, num_eles);
			for (e = 0; e < num_eles; ++e) {
				PLIST_CPY(list, PLIST_ELE(list, offset_start + e), &eles[e]);
			}
			list->count = new_count;
		}
	}
	return list;
}

bool psi_plist_shift(struct psi_plist *list, void *ptr) {
	if (list && list->count) {
		if (ptr) {
			PLIST_CPY(list, ptr, PLIST_ELE(list, 0));
		}
		if (--list->count) {
			PLIST_MOV_REDUCE(list, 0);
		}
		return true;
	}
	return false;
}

bool psi_plist_pop(struct psi_plist *list, void *ptr) {
	if (list && list->count) {
		--list->count;
		if (ptr) {
			PLIST_CPY(list, ptr, PLIST_ELE(list, list->count));
		}
		return true;
	}
	return false;
}

bool psi_plist_top(struct psi_plist *list, void *ptr) {
	if (list && list->count) {
		PLIST_CPY(list, ptr, PLIST_ELE(list, list->count - 1));
		return true;
	}
	return false;
}


static void swp_ptr(void *a, void *b) {
	void **_a = a, **_b = b, *_c;

	_c = *_b;
	*_b = *_a;
	*_a = _c;
}

void psi_plist_sort(struct psi_plist *list, compare_func_t cmp, swap_func_t swp) {
	if (!swp && list->size == sizeof(void *)) {
		swp = swp_ptr;
	}
	assert(swp);
	zend_insert_sort((void *) list->list, list->count, list->size, cmp, swp);
}
