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

decl_var *init_decl_var(const char *name, unsigned pl, unsigned as) {
	decl_var *v = calloc(1, sizeof(*v));
	v->name = (char *) strdup((const char *) name);
	v->pointer_level = pl;
	v->array_size = as;
	return v;
}

decl_var *copy_decl_var(decl_var *src) {
	decl_var *dest = calloc(1, sizeof(*dest));
	memcpy(dest, src, sizeof(*dest));
	dest->name = strdup(dest->name);
	if (dest->token) {
		dest->token = psi_token_copy(dest->token);
	}
	return dest;
}

void free_decl_var(decl_var *var) {
	if (var->token) {
		free(var->token);
	}
	free(var->name);
	free(var);
}

void dump_decl_var(int fd, decl_var *var) {
	dprintf(fd, "%s%s",
			psi_t_indirection(var->pointer_level-!!var->array_size), var->name);
	if (var->array_size) {
		dprintf(fd, "[%u]", var->array_size);
	}
}

decl_arg *locate_decl_var_arg(decl_var *var, decl_args *args, decl_arg *func) {
	decl_arg *arg = locate_decl_arg(args, var->name);

	if (arg) {
		assert(!var->arg || var->arg == arg);

		return var->arg = arg;
	}

	if (func && !strcmp(var->name, func->var->name)) {
		return var->arg = func;
	}

	return NULL;
}
