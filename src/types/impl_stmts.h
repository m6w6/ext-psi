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

#ifndef PSI_TYPES_IMPL_STMTS_H
#define PSI_TYPES_IMPL_STMTS_H

#include "impl_stmt.h"

typedef struct impl_stmts {
	struct {
		return_stmt **list;
		size_t count;
	} ret;
	struct {
		let_stmt **list;
		size_t count;
	} let;
	struct {
		set_stmt **list;
		size_t count;
	} set;
	struct {
		free_stmt **list;
		size_t count;
	} fre;
} impl_stmts;

void *add_impl_stmt_ex(void *list, size_t count, void *stmt);
impl_stmts *add_impl_stmt(impl_stmts *stmts, impl_stmt *stmt);
impl_stmts *init_impl_stmts(impl_stmt *stmt);
void free_impl_stmts(impl_stmts *stmts);
void dump_impl_stmts(int fd, impl_stmts *stmts);

struct psi_data;
struct impl;

int validate_impl_stmts(struct psi_data *data, struct impl *impl);

#endif
