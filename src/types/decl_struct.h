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

#ifndef PSI_TYPES_DECL_STRUCT_H
#define PSI_TYPES_DECL_STRUCT_H

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_decl_var;
struct psi_validate_stack;

struct psi_decl_struct {
	struct psi_token *token;
	char *name;
	struct psi_plist *args;
	size_t size;
	size_t align;
	struct {
		void *type;
		void (*dtor)(void *type);
	} engine;
};

struct psi_decl_struct *psi_decl_struct_init(const char *name, struct psi_plist *args);
void psi_decl_struct_free(struct psi_decl_struct **s_ptr);
void psi_decl_struct_dump(int fd, struct psi_decl_struct *strct);

bool psi_decl_struct_validate(struct psi_data *data, struct psi_decl_struct *s, struct psi_validate_stack *type_stack);

struct psi_decl_arg *psi_decl_struct_get_arg(struct psi_decl_struct *s, struct psi_decl_var *var);
size_t psi_decl_struct_get_align(struct psi_decl_struct *s);

#endif
