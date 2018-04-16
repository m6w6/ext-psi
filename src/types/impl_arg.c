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

#include "php_psi_stdinc.h"
#include "data.h"

struct psi_impl_arg *psi_impl_arg_init(struct psi_impl_type *type,
		struct psi_impl_var *var, struct psi_impl_def_val *def)
{
	struct psi_impl_arg *arg = calloc(1, sizeof(*arg));
	arg->type = type;
	arg->var = var;
	arg->var->arg = arg;
	arg->def = def;
	return arg;
}

void psi_impl_arg_free(struct psi_impl_arg **arg_ptr)
{
	if (*arg_ptr) {
		struct psi_impl_arg *arg = *arg_ptr;

		*arg_ptr = NULL;
		psi_impl_type_free(&arg->type);
		psi_impl_var_free(&arg->var);
		if (arg->def) {
			psi_impl_def_val_free(&arg->def);
		}
		free(arg);
	}
}

void psi_impl_arg_dump(int fd, struct psi_impl_arg *iarg, bool vararg)
{
	psi_impl_type_dump(fd, iarg->type);
	dprintf(fd, " ");
	psi_impl_var_dump(fd, iarg->var, vararg);
	if (iarg->def) {
		dprintf(fd, " = ");
		psi_impl_def_val_dump(fd, iarg->def);
	}

}
