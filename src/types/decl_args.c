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

#include "data.h"

decl_args *init_decl_args(decl_arg *arg) {
	decl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
	}
	return args;
}

decl_args *add_decl_arg(decl_args *args, decl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count - 1] = arg;
	return args;
}

void free_decl_args(decl_args *args) {
	size_t i;
	for (i = 0; i < args->count; ++i) {
		free_decl_arg(args->args[i]);
	}
	free(args->args);
	free(args);
}

void dump_decl_args(int fd, decl_args *args, unsigned level) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		if (i) {
			dprintf(fd, ", ");
		}
		dump_decl_arg(fd, args->args[i], level);
	}
	if (args->varargs) {
		dprintf(fd, ", ...");
	}
}

void dump_decl_args_with_layout(int fd, decl_args *args, unsigned level) {
	size_t j;

	dprintf(fd, " {\n");
	if (args) {
		++level;
		for (j = 0; j < args->count; ++j) {
			decl_arg *sarg = args->args[j];

			dprintf(fd, "%s", psi_t_indent(level));
			dump_decl_arg(fd, sarg, level);
			dprintf(fd, "::(%zu, %zu);\n", sarg->layout->pos, sarg->layout->len);
		}
		--level;
	}
	dprintf(fd, "%s", psi_t_indent(level));
	dprintf(fd, "}");
}

decl_arg *locate_decl_arg(decl_args *args, const char *name) {
	size_t i;

	if (args) for (i = 0; i < args->count; ++i) {
		decl_arg *arg = args->args[i];

		if (!strcmp(name, arg->var->name)) {
			return arg;
		}
	}

	return NULL;
}

size_t alignof_decl_args(decl_args *args) {
	size_t i, maxalign = 0;

	for (i = 0; i < args->count; ++i) {
		decl_arg *darg = args->args[i];
		size_t align = alignof_decl_arg(darg);

		if (align > maxalign) {
			maxalign = align;
		}
	}

	return maxalign;
}

int validate_decl_arg_args(struct psi_data *data, decl_arg *darg, void *current) {
	decl_type *real = real_decl_type(darg->type);

	/* pre-validate any structs/unions/enums */
	switch (real->type) {
	case PSI_T_STRUCT:
		if (current && current == real->real.strct) {
			return 1;
		}
		if (!locate_decl_type_struct(data->structs, real)) {
			return 0;
		}
		if (!validate_decl_struct(data, real->real.strct)) {
			return 0;
		}
		break;
	case PSI_T_UNION:
		if (current && current == real->real.unn) {
			return 1;
		}
		if (!locate_decl_type_union(data->unions, real)) {
			return 0;
		}
		if (!validate_decl_union(data, real->real.unn)) {
			return 0;
		}
		break;
	case PSI_T_ENUM:
		if (current && current == real->real.enm) {
			return 1;
		}
		if (!locate_decl_type_enum(data->enums, real)) {
			return 0;
		}
		if (!validate_decl_enum(data, real->real.enm)) {
			return 0;
		}
		break;
	}

	return 1;
}

static int sort_args_cmp(const void *_a, const void *_b) {
	decl_arg *a = *(decl_arg **)_a, *b = *(decl_arg **)_b;

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

static void sort_args_swp(void *a, void *b) {
	decl_arg **_a = a, **_b = b, *_c;

	_c = *_b;
	*_b = *_a;
	*_a = _c;
}

#include "Zend/zend_sort.h"

void sort_decl_args(decl_args *args) {
	zend_insert_sort((void *) args->args, args->count,
			sizeof(args), sort_args_cmp, sort_args_swp);
}

