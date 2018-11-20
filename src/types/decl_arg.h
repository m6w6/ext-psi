/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

      *Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
      *Redistributions in binary form must reproduce the above copyright
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

#ifndef PSI_TYPES_DECL_ARG_H
#define PSI_TYPES_DECL_ARG_H

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_decl_type;
struct psi_decl_var;
struct psi_layout;
struct psi_validate_scope;

struct psi_decl_arg {
	struct psi_token *token;
	struct psi_decl_type *type;
	struct psi_decl_var *var;
	struct psi_layout *layout;
};

struct psi_decl_arg *psi_decl_arg_init(struct psi_decl_type *type, struct psi_decl_var *var);
void psi_decl_arg_free(struct psi_decl_arg **arg_ptr);
void psi_decl_arg_dump(struct psi_dump *dump, struct psi_decl_arg *arg, unsigned level);

bool psi_decl_arg_validate(struct psi_data *data, struct psi_decl_arg *arg, struct psi_validate_scope *scope);
bool psi_decl_arg_validate_typedef(struct psi_data *data, struct psi_decl_arg *def, struct psi_validate_scope *scope);

bool psi_decl_arg_is_pointer(struct psi_decl_arg *darg);

size_t psi_decl_arg_align(struct psi_decl_arg *darg, size_t *pos, size_t *len);
size_t psi_decl_arg_get_align(struct psi_decl_arg *darg);
size_t psi_decl_arg_get_size(struct psi_decl_arg *darg);

struct psi_decl_arg *psi_decl_arg_get_by_name(struct psi_plist *args, zend_string *name);
struct psi_decl_arg *psi_decl_arg_get_by_var(struct psi_decl_var *var, struct psi_plist *args, struct psi_decl_arg *func);


#endif
