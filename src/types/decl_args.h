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

#ifndef PSI_TYPES_DECL_ARGS_H
#define PSI_TYPES_DECL_ARGS_H

#include "decl_arg.h"

typedef struct decl_args {
	decl_arg **args;
	size_t count;
	unsigned varargs:1;
} decl_args;

decl_args *init_decl_args(decl_arg *arg);
decl_args *add_decl_arg(decl_args *args, decl_arg *arg);
void free_decl_args(decl_args *args);
void dump_decl_args(int fd, decl_args *args, unsigned level);
void dump_decl_args_with_layout(int fd, decl_args *args, unsigned level);

decl_arg *locate_decl_arg(decl_args *args, const char *name);

struct psi_data;

int validate_decl_arg_args(struct psi_data *data, decl_arg *darg, void *current);

size_t alignof_decl_args(decl_args *args);

void sort_decl_args(decl_args *args);

#endif
