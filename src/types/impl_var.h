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

#ifndef PSI_TYPES_IMPL_VAR_H
#define PSI_TYPES_IMPL_VAR_H

struct psi_token;
struct psi_impl;
struct psi_impl_arg;
struct psi_validate_scope;

struct psi_impl_var {
	struct psi_token *token;
	char *name, *fqn;
	struct psi_impl_arg *arg;
	unsigned reference:1;
};

struct psi_impl_var *psi_impl_var_init(const char *name, bool is_reference);
struct psi_impl_var *psi_impl_var_copy(struct psi_impl_var *var);
void psi_impl_var_free(struct psi_impl_var **var_ptr);
void psi_impl_var_dump(int fd, struct psi_impl_var *var, bool vararg);

#include <string.h>

static inline char *psi_impl_var_name_prepend(char *current, const char *prepend) {
	size_t c_len = strlen(current);
	size_t p_len = strlen(prepend);

	current = realloc(current, p_len
			+ c_len // includes '$'
			+ 1 // connecting dot
			+ 1 // terminating 0
	);
	if (current) {
		if (c_len > 1) {
			memmove(current + p_len + 1 + 1, current + 1, c_len - 1 + 1);
			current[p_len + 1] = '.';
		} else {
			/* just '$' */
			current[p_len + 1] = '\0';
		}
		memcpy(current + 1, prepend, p_len);
	}
	return current;
}

bool psi_impl_var_validate(struct psi_data *data, struct psi_impl_var *ivar,
		struct psi_validate_scope *scope);

#endif
