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

#ifndef PSI_TYPES_IMPL_FUNC_H
#define PSI_TYPES_IMPL_FUNC_H

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_impl;
struct psi_impl_arg;
struct psi_impl_type;

struct psi_impl_func {
	struct psi_token *token;
	zend_string *name;
	struct psi_plist *args;
	struct psi_impl_arg *vararg;
	struct psi_impl_type *return_type;
	unsigned return_reference:1;
	unsigned static_memory:1;
};

struct psi_impl_func *psi_impl_func_init(zend_string *name,
		struct psi_plist *args, struct psi_impl_type *return_type);
void psi_impl_func_free(struct psi_impl_func **f_ptr);
void psi_impl_func_dump(int fd, struct psi_impl_func *func);
bool psi_impl_func_validate(struct psi_data *data, struct psi_impl_func *func,
		struct psi_validate_scope *scope);

#endif
