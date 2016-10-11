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

typedef struct decl_type {
	struct psi_token *token;
	char *name;
	token_t type;
	union {
		struct decl_arg *def;
		struct decl_struct *strct;
		struct decl_union *unn;
		struct decl_enum *enm;
		struct decl *func;
	} real;
} decl_type;

#include <string.h>
#define is_anon_type(name, type) !strncmp(name, type "@", sizeof(type))

decl_type *init_decl_type(token_t type, const char *name);
void free_decl_type(decl_type *type);
void dump_decl_type(int fd, decl_type *t, unsigned level);

struct decl_args *extract_decl_type_args(decl_type *dtyp, decl_type** real_typ_ptr);
int weak_decl_type(decl_type *type);
decl_type *real_decl_type(decl_type *type);

struct decl_typedefs;
struct decl_structs;
struct decl_unions;
struct decl_enums;
struct decls;

int locate_decl_type_alias(struct decl_typedefs *defs, decl_type *type);
int locate_decl_type_struct(struct decl_structs *structs, decl_type *type);
int locate_decl_type_union(struct decl_unions *unions, decl_type *type);
int locate_decl_type_enum(struct decl_enums *enums, decl_type *type);
int locate_decl_type_decl(struct decls *decls, decl_type *type);

struct psi_data;

int validate_decl_type(struct psi_data *data, decl_type *type, struct decl_arg *def);

size_t alignof_decl_type(decl_type *t);

#endif
