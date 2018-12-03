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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif
#include "data.h"

#include <assert.h>

struct psi_layout *psi_layout_init(size_t pos, size_t len, struct psi_layout *bfw)
{
	struct psi_layout *l = pecalloc(1, sizeof(*l), 1);

	assert(pos + len + (intptr_t) bfw);

	l->pos = pos;
	l->len = len;
	l->bfw = bfw;

	return l;
}

void psi_layout_free(struct psi_layout **l_ptr)
{
	if (*l_ptr) {
		struct psi_layout *l = *l_ptr;
		*l_ptr = NULL;

		if (l->bfw) {
			psi_layout_free(&l->bfw);
		}
		free(l);
	}
}

int psi_layout_sort_cmp(const void *_a, const void *_b)
{
	struct psi_decl_arg *a = *(struct psi_decl_arg **) _a;
	struct psi_decl_arg *b = *(struct psi_decl_arg **) _b;

	if (a->layout->pos == b->layout->pos) {
		if (a->layout->len == b->layout->len) {
			return 0;
		} else if (a->layout->len > b->layout->len) {
			return -1;
		} else {
			return 1;
		}
	} else if (a->layout->pos > b->layout->pos) {
		return 1;
	} else {
		return -1;
	}
}
