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
struct psi_validate_scope;

struct psi_decl_var {
	struct psi_token *token;
	zend_string *name, *fqn;
	unsigned pointer_level;
	unsigned array_size;
	struct psi_decl_arg *arg;
};

struct psi_decl_var *psi_decl_var_init(zend_string *name, unsigned pl, unsigned as);
struct psi_decl_var *psi_decl_var_copy(struct psi_decl_var *src);
void psi_decl_var_free(struct psi_decl_var **var_ptr);
void psi_decl_var_dump(struct psi_dump *dump, struct psi_decl_var *var);

bool psi_decl_var_validate(struct psi_data *data, struct psi_decl_var *dvar,
		struct psi_validate_scope *scope);

size_t psi_decl_var_get_size(struct psi_decl_var *var);

#endif
