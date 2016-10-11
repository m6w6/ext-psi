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

#include "decl_structs.h"
#include "decl_type.h"

decl_structs *add_decl_struct(decl_structs *ss, decl_struct *s) {
	if (!ss) {
		ss = calloc(1, sizeof(*ss));
	}
	ss->list = realloc(ss->list, ++ss->count * sizeof(*ss->list));
	ss->list[ss->count - 1] = s;
	return ss;
}

void free_decl_structs(decl_structs *ss) {
	size_t i;
	for (i = 0; i < ss->count; ++i) {
		free_decl_struct(ss->list[i]);
	}
	free(ss->list);
	free(ss);
}

void dump_decl_structs(int fd, decl_structs *ss) {
	size_t i;

	for (i = 0; i < ss->count; ++i) {
		decl_struct *strct = ss->list[i];

		if (!is_anon_type(strct->name, "struct")) {
			dump_decl_struct(fd, strct);
			dprintf(fd, "\n");
		}
	}
}
