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

impl_args *init_impl_args(impl_arg *arg) {
	impl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
	}
	return args;
}

impl_args *add_impl_arg(impl_args *args, impl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count - 1] = arg;
	return args;
}

void free_impl_args(impl_args *args) {
	size_t i;
	for (i = 0; i < args->count; ++i) {
		free_impl_arg(args->args[i]);
	}
	if (args->vararg.name) {
		free_impl_arg(args->vararg.name);
	}
	free(args->args);
	free(args);
}

int validate_impl_args(struct psi_data *data, impl *impl) {
	int def = 0;
	size_t i;

	for (i = 0; i < impl->func->args->count; ++i) {
		impl_arg *iarg = impl->func->args->args[i];

		if (iarg->def) {
			def = 1;
		} else if (def) {
			data->error(data, impl->func->token, PSI_WARNING,
					"Non-optional argument %zu '$%s' of implementation '%s'"
					" follows optional argument",
					i+1, iarg->var->name, impl->func->name);
			return 0;
		}
	}

	return 1;
}
