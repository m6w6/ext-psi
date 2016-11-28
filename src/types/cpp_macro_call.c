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

#include "php_psi_stdinc.h"

#include "cpp.h"
#include "data.h"

struct psi_cpp_macro_call *psi_cpp_macro_call_init(const char *name,
		struct psi_plist *args)
{
	struct psi_cpp_macro_call *call = calloc(1, sizeof(*call));
	call->name = strdup(name);
	call->args = args;
	return call;
}

struct psi_cpp_macro_call *psi_cpp_macro_call_copy(
		struct psi_cpp_macro_call *call)
{
	struct psi_cpp_macro_call *copy = calloc(1, sizeof(*copy));
	copy->name = strdup(call->name);
	if (call->token) {
		copy->token = psi_token_copy(call->token);
	}
	if (call->args) {
		copy->args = psi_plist_copy(call->args,
				(void (*)(void*)) psi_token_copy_ctor);
	}
	return copy;
}

void psi_cpp_macro_call_free(struct psi_cpp_macro_call **call_ptr)
{
	if (*call_ptr) {
		struct psi_cpp_macro_call *call = *call_ptr;

		*call_ptr = NULL;

		free(call->name);
		if (call->args) {
			psi_plist_free(call->args);
		}
		if (call->token) {
			free(call->token);
		}
		free(call);
	}
}

