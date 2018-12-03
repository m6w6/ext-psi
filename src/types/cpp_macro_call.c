/*******************************************************************************
 Copyright (c) 2017, Michael Wallner <mike@php.net>.
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

#include "cpp.h"
#include "data.h"

struct psi_cpp_macro_call *psi_cpp_macro_call_init(zend_string *name,
		struct psi_plist *args)
{
	struct psi_cpp_macro_call *call = pecalloc(1, sizeof(*call), 1);
	call->name = zend_string_copy(name);
	call->args = args;
	return call;
}

struct psi_cpp_macro_call *psi_cpp_macro_call_copy(
		struct psi_cpp_macro_call *call)
{
	struct psi_cpp_macro_call *copy = pecalloc(1, sizeof(*copy), 1);
	copy->name = zend_string_copy(call->name);
	if (call->token) {
		copy->token = psi_token_copy(call->token);
	}
	if (call->args) {
		copy->args = psi_plist_copy(call->args,
				(void (*)(void*)) psi_num_exp_copy_ctor);
	}
	return copy;
}

void psi_cpp_macro_call_free(struct psi_cpp_macro_call **call_ptr)
{
	if (*call_ptr) {
		struct psi_cpp_macro_call *call = *call_ptr;

		*call_ptr = NULL;

		zend_string_release(call->name);
		if (call->args) {
			psi_plist_free(call->args);
		}
		psi_token_free(&call->token);
		free(call);
	}
}

void psi_cpp_macro_call_dump(struct psi_dump *dump, struct psi_cpp_macro_call *call)
{
	size_t i = 0;
	struct psi_num_exp *num;

	PSI_DUMP(dump, "%s(", call->name->val);
	while (psi_plist_get(call->args, i++, &num)) {
		if (i > 1) {
			PSI_DUMP(dump, ", ");
		}
		psi_num_exp_dump(dump, num);
	}
	PSI_DUMP(dump, ")");
}
