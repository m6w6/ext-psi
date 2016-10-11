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

decl_union* init_decl_union(const char* name, decl_args* args) {
	decl_union* u = calloc(1, sizeof(*u));
	u->name = strdup(name);
	u->args = args;
	return u;
}

void free_decl_union(decl_union* u) {
	if (u->token) {
		free(u->token);
	}
	if (u->args) {
		free_decl_args(u->args);
	}
	free(u->name);
	free(u);
}

void dump_decl_union(int fd, decl_union *unn) {
	dprintf(fd, "union %s::(%zu, %zu)", unn->name, unn->align, unn->size);
	if (unn->args && unn->args->count) {
		dump_decl_args_with_layout(fd, unn->args, 0);
	} else {
		dprintf(fd, ";");
	}
}

decl_arg *locate_decl_union_member(decl_union *u, decl_var *var) {
	if (u->args) {
		return locate_decl_var_arg(var, u->args, NULL);
	}

	return NULL;
}

int validate_decl_union(struct psi_data *data, decl_union *u) {
	size_t i, pos, len, size = 0, align;

	if (!u->size && !u->args->count) {
		data->error(data, u->token, PSI_WARNING,
				"Cannot compute size of empty union %s",
				u->name);
		return 0;
	}

	for (i = 0; i < u->args->count; ++i) {
		decl_arg *darg = u->args->args[i];

		if (!validate_decl_arg(data, darg)) {
			return 0;
		}

		assert(!darg->var->arg || darg->var->arg == darg);

		darg->var->arg = darg;

		if (!validate_decl_arg_args(data, darg, u)) {
			return 0;
		} else if (darg->layout) {
			pos = darg->layout->pos;

			align = align_decl_arg(darg, &pos, &len);

			if (darg->layout->pos != 0) {
				data->error(data, darg->token, PSI_WARNING,
						"Offset of %s.%s should be 0",
						u->name, darg->var->name);
				darg->layout->pos = 0;
			}
			if (darg->layout->len != len) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed size %zu of %s.%s does not match"
						" pre-defined size %zu of type '%s'",
						len, u->name, darg->var->name, darg->layout->len,
						darg->type->name);
			}
		} else {
			pos = 0;

			align = align_decl_arg(darg, &pos, &len);
			darg->layout = init_decl_struct_layout(pos, len);

		}
		if (len > size) {
			size = len;
		}
		if (align > u->align) {
			u->align = align;
		}
	}

	sort_decl_args(u->args);

	if (u->size < size) {
		u->size = psi_align(size, u->align);
	}

	return 1;
}

size_t alignof_decl_union(decl_union *u) {
	if (!u->align) {
		u->align = alignof_decl_args(u->args);
	}
	return u->align;
}
