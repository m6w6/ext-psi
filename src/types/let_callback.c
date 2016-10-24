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

let_callback *init_let_callback(struct let_func *func, struct set_values *args) {
	let_callback *cb = calloc(1, sizeof(*cb));
	cb->func = func;
	cb->args = args;
	return cb;
}

void free_let_callback(let_callback *cb) {
	free_let_func(cb->func);
	free_set_values(cb->args);
	free(cb);
}

int validate_let_callback(struct psi_data *data, decl_var *cb_var, let_callback *cb, impl *impl) {
	size_t i;
	decl *cb_func;
	decl_type *cb_type = real_decl_type(cb_var->arg->type);

	if (cb_type->type != PSI_T_FUNCTION) {
		data->error(data, cb_var->token, PSI_WARNING, "Not a function: %s", cb_var->name);
		return 0;
	}
	cb_func = cb_type->real.func;
	for (i = 0; i < cb->args->count; ++i) {
		if (!validate_set_value(data, cb->args->vals[i], cb_func->args->count, cb_func->args->args, 0)) {
			return 0;
		}
	}

	if (!validate_decl_nodl(data, cb_func)) {
		return 0;
	}

	cb->decl = cb_func;

	return 1;
}
