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
#include "data.h"

struct psi_decl_enum *psi_decl_enum_init(zend_string *name, struct psi_plist *l)
{
	struct psi_decl_enum *e = pecalloc(1, sizeof(*e), 1);
	e->name = zend_string_copy(name);
	e->items = l;
	return e;
}

void psi_decl_enum_free(struct psi_decl_enum **e_ptr)
{
	if (*e_ptr) {
		struct psi_decl_enum *e = *e_ptr;

		*e_ptr = NULL;
		psi_token_free(&e->token);
		if (e->items) {
			psi_plist_free(e->items);
		}
		zend_string_release(e->name);
		free(e);
	}
}

void psi_decl_enum_dump(int fd, struct psi_decl_enum *e, unsigned level)
{
	dprintf(fd, "enum %s {\n", e->name->val);
	if (e->items) {
		size_t i = 0;
		struct psi_decl_enum_item *item;

		while (psi_plist_get(e->items, i++, &item)) {
			if (i > 1) {
				dprintf(fd, ",\n");
			}
			dprintf(fd, "%s", psi_t_indent(level + 1));
			psi_decl_enum_item_dump(fd, item);
		}
	}
	dprintf(fd, "\n}");
}

bool psi_decl_enum_validate(struct psi_data *data, struct psi_decl_enum *e)
{
	size_t seq;
	struct psi_decl_enum_item *i, *p = NULL;

	if (!psi_plist_count(e->items)) {
		data->error(data, e->token, PSI_WARNING, "Empty enum '%s'", e->name->val);
		return false;
	}

	for (seq = 0; psi_plist_get(e->items, seq, &i); ++seq) {
		i->prev = p;
		if (!psi_decl_enum_item_validate(data, e, i, seq)) {
			return false;
		}
		p = i;
	}

	return true;
}
