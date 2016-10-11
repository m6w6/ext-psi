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
#include <assert.h>

#include "data.h"

decl_arg *init_decl_arg(decl_type *type, decl_var *var) {
	decl_arg *arg = calloc(1, sizeof(*arg));
	arg->token = var->token;
	arg->type = type;
	arg->var = var;
	var->arg = arg;
	arg->ptr = &arg->val;
	arg->let = arg->ptr;
	return arg;
}

void free_decl_arg(decl_arg *arg) {
	if (arg->token && arg->token != arg->var->token) {
		free(arg->token);
	}
	free_decl_type(arg->type);
	free_decl_var(arg->var);
	if (arg->layout) {
		free_decl_struct_layout(arg->layout);
	}
	free(arg);
}

void dump_decl_arg(int fd, decl_arg *arg, unsigned level) {
	if (arg->type->type == PSI_T_FUNCTION) {
		dump_decl_type(fd, arg->type->real.func->func->type, level);
		dprintf(fd, " (*");
		dump_decl_var(fd, arg->var);
		dprintf(fd, ")(");
		if (arg->type->real.func->args) {
			size_t j;

			for (j = 0; j < arg->type->real.func->args->count; ++j) {
				if (j) {
					dprintf(fd, ", ");
				}
				dump_decl_arg(fd, arg->type->real.func->args->args[j], level+1);
			}
			if (arg->type->real.func->args->varargs) {
				dprintf(fd, ", ...");
			}
		}
		dprintf(fd, ")");
	} else {
		dump_decl_type(fd, arg->type, level);
		dprintf(fd, " ");
		dump_decl_var(fd, arg->var);
	}
}

int validate_decl_arg(struct psi_data *data, decl_arg *arg) {
	if (!validate_decl_type(data, arg->type, NULL)) {
		data->error(data, arg->type->token, PSI_WARNING,
			"Cannot use '%s' as type for '%s'",
			arg->type->name, arg->var->name);
		return 0;
	}
	return 1;
}

size_t align_decl_arg(decl_arg *darg, size_t *pos, size_t *len) {
	size_t align = alignof_decl_arg(darg);

	assert(align > 0);

	*len = sizeof_decl_arg(darg);
	*pos = psi_align(align, *pos);

	return align;
}

size_t alignof_decl_arg(decl_arg *darg) {
	size_t align;

	if (darg->var->pointer_level && (!darg->var->array_size || darg->var->pointer_level > 2)) {
		align = psi_t_alignment(PSI_T_POINTER);
	} else {
		align = alignof_decl_type(darg->type);
	}

	return align;
}

size_t sizeof_decl_arg(decl_arg *darg) {
	size_t size;
	decl_type *real = real_decl_type(darg->type);

	if (darg->var->array_size) {
		if (darg->var->pointer_level > 2) {
			size = psi_t_size(PSI_T_POINTER) * darg->var->array_size;
		} else {
			size = psi_t_size(real->type) * darg->var->array_size;
		}
	} else if (darg->var->pointer_level) {
		size = psi_t_size(PSI_T_POINTER);
	} else {
		switch (real->type) {
		case PSI_T_UNION:
			size = real->real.unn->size;
			break;
		case PSI_T_STRUCT:
			size = real->real.strct->size;
			break;
		case PSI_T_ENUM:
		default:
			size = psi_t_size(real->type);
			break;
		}
	}

	assert(size > 0);

	return size;
}
