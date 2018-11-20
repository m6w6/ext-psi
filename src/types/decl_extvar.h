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

#ifndef PSI_TYPES_DECL_EXTVAR_H
#define PSI_TYPES_DECL_EXTVAR_H

struct psi_data;
struct psi_token;
struct psi_decl;
struct psi_decl_arg;

struct psi_decl_extvar {
	struct psi_token *token;
	struct psi_decl_arg *arg;
	struct psi_decl *getter;
	struct psi_decl *setter;
	size_t size;
	zend_string *redir;
	void *sym;
	void *info;
};

struct psi_decl_extvar *psi_decl_extvar_init(struct psi_decl_arg *arg);
void psi_decl_extvar_free(struct psi_decl_extvar **evar);
bool psi_decl_extvar_validate(struct psi_data *data, struct psi_decl_extvar *evar,
		struct psi_validate_scope *scope);
void psi_decl_extvar_dump(struct psi_dump *dump, struct psi_decl_extvar *evar);

bool psi_decl_extvar_is_blacklisted(const char *name);

struct psi_decl *psi_decl_extvar_setter(struct psi_decl_extvar *evar);
void psi_decl_extvar_set(struct psi_decl_extvar *evar, void *ptr);
struct psi_decl *psi_decl_extvar_getter(struct psi_decl_extvar *evar);
void psi_decl_extvar_get(struct psi_decl_extvar *evar, void *ptr);

#endif /* PSI_TYPES_DECL_EXTVAR_H */
