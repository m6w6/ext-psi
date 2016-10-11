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

#include "decl_enums.h"
#include "decl_type.h"

decl_enums *add_decl_enum(decl_enums *es, decl_enum *e) {
	if (!es) {
		es = calloc(1, sizeof(*es));
	}
	es->list = realloc(es->list, ++es->count * sizeof(*es->list));
	es->list[es->count - 1] = e;
	return es;
}

void free_decl_enums(decl_enums *es) {
	if (es->list) {
		size_t j;
		for (j = 0; j < es->count; ++j) {
			free_decl_enum(es->list[j]);
		}
	}
	free(es->list);
	free(es);
}

void dump_decl_enums(int fd, decl_enums *enums) {
	size_t i;

	for (i = 0; i < enums->count; ++i) {
		decl_enum *e = enums->list[i];

		if (!is_anon_type(e->name, "enum")) {
			dump_decl_enum(fd, e, 0);
			dprintf(fd, "\n");
		}
	}
}
