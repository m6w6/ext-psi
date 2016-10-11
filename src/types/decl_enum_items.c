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

#include <stdlib.h>
#include <stdio.h>

#include "decl_enum_items.h"

decl_enum_items *init_decl_enum_items(decl_enum_item *i) {
	decl_enum_items *l = calloc(1, sizeof(*l));
	if (i) {
		l->count = 1;
		l->list = calloc(1, sizeof(*l->list));
		l->list[0] = i;
	}
	return l;
}

decl_enum_items *add_decl_enum_item(decl_enum_items *l, decl_enum_item *i) {
	l->list = realloc(l->list, sizeof(*l->list) * (l->count + 1));
	l->list[l->count] = i;
	if (l->count) {
		i->prev = l->list[l->count - 1];
	}
	++l->count;
	return l;
}

void free_decl_enum_items(decl_enum_items *l) {
	if (l->list) {
		size_t j;
		for (j = 0; j < l->count; ++j) {
			free_decl_enum_item(l->list[j]);
		}
		free(l->list);
	}
	free(l);
}

void dump_decl_enum_items(int fd, decl_enum_items *items, unsigned level) {
	size_t i;
	for (i = 0; i < items->count; ++i) {
		decl_enum_item *item = items->list[i];

		if (i) {
			dprintf(fd, ",\n");
		}
		dprintf(fd, "%s", psi_t_indent(level+1));
		dprintf(fd, "%s", item->name);
		if (item->num && item->num != &item->inc) {
			dprintf(fd, " = ");
			dump_num_exp(fd, item->num);
		}
	}
}
