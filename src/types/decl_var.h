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

#ifndef PSI_TYPES_DECL_VAR_H
#define PSI_TYPES_DECL_VAR_H

struct psi_data;
struct psi_token;
struct psi_decl_arg;
struct psi_let_exp;
struct psi_set_exp;

struct psi_decl_var {
	struct psi_token *token;
	char *name, *fqn;
	unsigned pointer_level;
	unsigned array_size;
	struct psi_decl_arg *arg;
};

struct psi_decl_var *psi_decl_var_init(const char *name, unsigned pl, unsigned as);
struct psi_decl_var *psi_decl_var_copy(struct psi_decl_var *src);
void psi_decl_var_free(struct psi_decl_var **var_ptr);
void psi_decl_var_dump(int fd, struct psi_decl_var *var);

#include <string.h>

static inline char *psi_decl_var_name_prepend(char *current, const char *prepend) {
	size_t c_len = strlen(current);
	size_t p_len = strlen(prepend);

	current = realloc(current, p_len + 1 + c_len + 1);
	if (current) {
		memmove(current + p_len + 1, current, c_len + 1);
		current[p_len] = '.';
		memcpy(current, prepend, p_len);
	}
	return current;
}

bool psi_decl_var_validate(struct psi_data *data, struct psi_decl_var *dvar, struct psi_decl *decl,
		struct psi_let_exp *current_let_exp, struct psi_set_exp *current_set_exp);

size_t psi_decl_var_get_size(struct psi_decl_var *var);

#endif
