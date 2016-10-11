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

#include "decl_type.h"
#include "decl_var.h"
#include "decl_struct_layout.h"
#include "impl_val.h"

typedef struct decl_arg {
	struct psi_token *token;
	decl_type *type;
	decl_var *var;
	decl_struct_layout *layout;
	impl_val val;
	void *ptr;
	void *let;
	void *mem;
} decl_arg;

decl_arg *init_decl_arg(decl_type *type, decl_var *var);
void free_decl_arg(decl_arg *arg);
void dump_decl_arg(int fd, decl_arg *arg, unsigned level);

struct psi_data;

int validate_decl_arg(struct psi_data *data, decl_arg *arg);

size_t align_decl_arg(decl_arg *darg, size_t *pos, size_t *len);
size_t alignof_decl_arg(decl_arg *darg);
size_t sizeof_decl_arg(decl_arg *darg);

#endif
