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

#include "impl_func.h"

impl_func *init_impl_func(char *name, impl_args *args, impl_type *type,
		int ret_reference) {
	impl_func *func = calloc(1, sizeof(*func));
	func->name = strdup(name);
	func->args = args ? args : init_impl_args(NULL);
	func->return_type = type;
	func->return_reference = ret_reference;
	return func;
}

void free_impl_func(impl_func *f) {
	if (f->token) {
		free(f->token);
	}
	free_impl_type(f->return_type);
	free_impl_args(f->args);
	free(f->name);
	free(f);
}

void dump_impl_func(int fd, impl_func *func) {
	size_t j;

	dprintf(fd, "function %s(", func->name);
	if (func->args) {
		for (j = 0; j < func->args->count; ++j) {
			impl_arg *iarg = func->args->args[j];

			dprintf(fd, "%s%s %s%s",
					j ? ", " : "",
					iarg->type->name,
					iarg->var->reference ? "&" : "",
					iarg->var->name);
			if (iarg->def) {
				dprintf(fd, " = %s", iarg->def->text);
			}
		}
		if (func->args->vararg.name) {
			impl_arg *vararg = func->args->vararg.name;

			dprintf(fd, ", %s %s...%s",
					vararg->type->name,
					vararg->var->reference ? "&" : "",
					vararg->var->name);
		}
	}
	dprintf(fd, ") : %s%s",
			func->return_reference ? "&":"",
			func->return_type->name);
}
