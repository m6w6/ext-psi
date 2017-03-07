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

#ifndef PSI_TYPES_DECL_TYPE_H
#define PSI_TYPES_DECL_TYPE_H

#include "token.h"

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_decl_arg;
struct psi_decl_struct;
struct psi_decl_union;
struct psi_decl_enum;
struct psi_decl;

struct psi_decl_type {
	struct psi_token *token;
	char *name;
	token_t type;
	union {
		struct psi_decl_arg *def;
		struct psi_decl_struct *strct;
		struct psi_decl_union *unn;
		struct psi_decl_enum *enm;
		struct psi_decl *func;
	} real;
};

#include <string.h>
#define psi_decl_type_is_anon(name, type) !strncmp(name, type "@", sizeof(type))

struct psi_decl_type *psi_decl_type_init(token_t type, const char *name);
struct psi_decl_type *psi_decl_type_copy(struct psi_decl_type *src);
void psi_decl_type_free(struct psi_decl_type **type_ptr);
void psi_decl_type_dump(int fd, struct psi_decl_type *t, unsigned level);
bool psi_decl_type_validate(struct psi_data *data, struct psi_decl_type *type, struct psi_decl_arg *def);

bool psi_decl_type_validate_args(struct psi_data *data, struct psi_decl_type *decl_type, token_t type, void *current);

size_t psi_decl_type_get_size(struct psi_decl_type *dtyp, struct psi_decl_type **real_typ_ptr);
size_t psi_decl_type_get_align(struct psi_decl_type *t);
int psi_decl_type_is_weak(struct psi_decl_type *type);
struct psi_decl_type *psi_decl_type_get_real(struct psi_decl_type *type);

struct psi_plist *psi_decl_type_get_args(struct psi_decl_type *dtyp, struct psi_decl_type **real_typ_ptr);
void psi_decl_type_dump_args_with_layout(int fd, struct psi_plist *args, unsigned level);
size_t psi_decl_type_get_args_align(struct psi_plist *args);


bool psi_decl_type_get_alias(struct psi_decl_type *type, struct psi_plist *typedefs);
bool psi_decl_type_get_struct(struct psi_decl_type *type, struct psi_plist *structs);
bool psi_decl_type_get_union(struct psi_decl_type *type, struct psi_plist *unions);
bool psi_decl_type_get_enum(struct psi_decl_type *type, struct psi_plist *enums);
bool psi_decl_type_get_decl(struct psi_decl_type *type, struct psi_plist *decls);

#endif
