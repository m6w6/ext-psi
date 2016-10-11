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
#include <assert.h>

#include "data.h"

decl_struct* init_decl_struct(const char* name, decl_args* args) {
	decl_struct* s = calloc(1, sizeof(*s));
	s->name = strdup(name);
	s->args = args;
	return s;
}

void free_decl_struct(decl_struct* s) {
	if (s->token) {
		free(s->token);
	}
	if (s->args) {
		free_decl_args(s->args);
	}
	if (s->engine.type && s->engine.dtor) {
		s->engine.dtor(s->engine.type);
	}
	free(s->name);
	free(s);
}

void dump_decl_struct(int fd, decl_struct *strct) {
	dprintf(fd, "struct %s::(%zu, %zu)", strct->name, strct->align, strct->size);
	if (strct->args && strct->args->count) {
		dump_decl_args_with_layout(fd, strct->args, 0);
	} else {
		dprintf(fd, ";");
	}
}

decl_arg *locate_decl_struct_member(decl_struct *s, decl_var *var) {
	if (s->args) {
		return locate_decl_var_arg(var, s->args, NULL);
	}

	return NULL;
}

int validate_decl_struct(struct psi_data *data, decl_struct *s) {
	size_t i, pos, len, size, align;

	if (!s->size && !s->args->count) {
		data->error(data, s->token, PSI_WARNING,
				"Cannot compute size of empty struct '%s'",
				s->name);
		return 0;
	}

	for (i = 0; i < s->args->count; ++i) {
		decl_arg *darg = s->args->args[i];

		if (!validate_decl_arg(data, darg)) {
			return 0;
		}

		assert(!darg->var->arg || darg->var->arg == darg);

		darg->var->arg = darg;

		if (!validate_decl_arg_args(data, darg, s)) {
			return 0;
		} else if (darg->layout) {
			pos = darg->layout->pos;

			align = align_decl_arg(darg, &pos, &len);

			if (darg->layout->len != len) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed size %zu of %s.%s does not match"
						" pre-defined size %zu of type '%s'",
						len, s->name, darg->var->name, darg->layout->len,
						darg->type->name);
			}
			if (darg->layout->pos != pos) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed offset %zu of %s.%s does not match"
						" pre-defined offset %zu",
						pos, s->name, darg->var->name, darg->layout->pos);
			}
		} else  {
			if (i) {
				pos = s->args->args[i-1]->layout->pos +
						s->args->args[i-1]->layout->len;
			} else {
				pos = 0;
			}

			align = align_decl_arg(darg, &pos, &len);
			darg->layout = init_decl_struct_layout(pos, len);
		}

		if (align > s->align) {
			s->align = align;
		}
	}

	sort_decl_args(s->args);

	if (s->args->count) {
		decl_arg *darg = s->args->args[s->args->count-1];

		size = darg->layout->pos + darg->layout->len;
		if (s->size < size) {
			s->size = psi_align(size, s->align);
		}
	}

	return 1;
}

size_t alignof_decl_struct(decl_struct *s) {
	if (!s->align) {
		s->align = alignof_decl_args(s->args);
	}
	return s->align;
}
