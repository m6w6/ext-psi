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
#include <string.h>

#include "data.h"

decl_enum *init_decl_enum(const char *name, decl_enum_items *l) {
	decl_enum *e = calloc(1, sizeof(*e));
	e->name = strdup(name);
	e->items = l;
	return e;
}

void free_decl_enum(decl_enum *e) {
	if (e->token) {
		free(e->token);
	}
	if (e->items) {
		free_decl_enum_items(e->items);
	}
	free(e->name);
	free(e);
}

void dump_decl_enum(int fd, decl_enum *e, unsigned level) {
	dprintf(fd, "enum %s {\n", e->name);
	if (e->items) {
		dump_decl_enum_items(fd, e->items, level);
	}
	dprintf(fd, "\n}");
}

int validate_decl_enum(struct psi_data *data, decl_enum *e) {
	size_t j;

	if (!e->items || !e->items->count) {
		data->error(data, e->token, PSI_WARNING, "Empty enum '%s'", e->name);
		return 0;
	}

	for (j = 0; j < e->items->count; ++j) {
		decl_enum_item *i = e->items->list[j];

		if (!i->num) {
			if (j) {
				i->inc.t = PSI_T_NUMBER;
				i->inc.u.numb = "1";
				i->inc.operator = PSI_T_PLUS;
				i->inc.operand = i->prev->num ?: &i->prev->inc;
				i->num = &i->inc;
			} else {
				i->inc.t = PSI_T_NUMBER;
				i->inc.u.numb = "0";
				i->num = &i->inc;
			}
		}
		if (!validate_num_exp(data, i->num, NULL, NULL, e)) {
			return 0;
		}
	}

	return 1;
}
