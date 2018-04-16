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

#ifndef PSI_TYPES_IMPL_H
#define PSI_TYPES_IMPL_H

struct psi_data;
struct psi_token;
struct psi_plist;
struct psi_decl;
struct psi_decl_var;
struct psi_impl_var;
struct psi_impl_func;

struct psi_impl {
	struct psi_impl_func *func;
	struct psi_decl *decl;
	void *info;
	struct {
		struct psi_plist *ret;
		struct psi_plist *let;
		struct psi_plist *set;
		struct psi_plist *fre;
		struct psi_plist *ass;
	} stmts;
};

struct psi_impl *psi_impl_init(struct psi_impl_func *func, struct psi_plist *stmts);
void psi_impl_free(struct psi_impl **impl_ptr);
void psi_impl_dump(int fd, struct psi_impl *impl);
bool psi_impl_validate(struct psi_data *data, struct psi_impl *impl,
		struct psi_validate_scope *scope);

size_t psi_impl_num_min_args(struct psi_impl *impl);

void psi_impl_stmt_free(struct psi_token ***abstract_stm);

struct psi_let_stmt *psi_impl_get_let(struct psi_impl *impl, struct psi_decl_var *var);
struct psi_impl_arg *psi_impl_get_arg(struct psi_impl *impl, struct psi_impl_var *var);

struct psi_decl_arg *psi_impl_get_temp_let_arg(struct psi_impl *impl,
		struct psi_decl_var *var);

struct psi_decl_arg *psi_impl_get_decl_arg(struct psi_impl *impl,
		struct psi_decl_var *var);

#endif
