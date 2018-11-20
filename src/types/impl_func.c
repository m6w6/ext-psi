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

struct psi_impl_func *psi_impl_func_init(zend_string *name,
		struct psi_plist *args, struct psi_impl_type *type)
{
	struct psi_impl_func *func = pecalloc(1, sizeof(*func), 1);

	func->name = zend_string_copy(name);
	func->args = args ? : psi_plist_init((psi_plist_dtor) psi_impl_arg_free);

	func->return_type = type;

	return func;
}

void psi_impl_func_free(struct psi_impl_func **f_ptr)
{
	if (*f_ptr) {
		struct psi_impl_func *f = *f_ptr;

		*f_ptr = NULL;
		psi_token_free(&f->token);

		psi_impl_type_free(&f->return_type);
		psi_plist_free(f->args);

		if (f->vararg) {
			psi_impl_arg_free(&f->vararg);
		}

		zend_string_release(f->name);
		free(f);
	}
}

bool psi_impl_func_validate(struct psi_data *data, struct psi_impl_func *func,
		struct psi_validate_scope *scope)
{
	int def = 0;
	size_t i = 0;
	struct psi_impl_arg *iarg;

	while (psi_plist_get(func->args, i++, &iarg)) {
		if (iarg->def) {
			def = 1;
			if (!psi_impl_def_val_validate(data, iarg->def, iarg->type, scope)) {
				return 0;
			}
		} else if (def) {
			data->error(data, func->token, PSI_WARNING,
					"Non-optional argument %zu '$%s' of implementation '%s'"
					" follows optional argument",
					i + 1,
					iarg->var->name->val, func->name->val);
			return false;
		}
	}

	return true;
}

void psi_impl_func_dump(struct psi_dump *dump, struct psi_impl_func *func)
{
	PSI_DUMP(dump, "function %s(", func->name->val);
	if (func->args) {
		size_t i = 0;
		struct psi_impl_arg *iarg;

		while (psi_plist_get(func->args, i++, &iarg)) {
			if (i > 1) {
				PSI_DUMP(dump, ", ");
			}
			psi_impl_arg_dump(dump, iarg, false);
		}

		if (func->vararg) {
			PSI_DUMP(dump, ", ");
			psi_impl_arg_dump(dump, func->vararg, true);
		}
	}
	PSI_DUMP(dump, ") : %s%s", func->return_reference ? "&" : "",
			func->return_type->name->val);
}
