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

#ifndef PSI_CPP_H
#define PSI_CPP_H

#include "data.h"

#ifndef PSI_CPP_DEBUG
# define PSI_CPP_DEBUG 1
#endif

struct psi_cpp {
	HashTable defs;
	HashTable once;
	struct psi_parser *parser;
	struct {
		struct psi_plist *iter;
		struct psi_plist *next;
		struct psi_plist *exec;
	} tokens;
	HashTable expanding;
	const char *search;
	size_t index;
	unsigned level;
	unsigned skip;
	unsigned seen;
	unsigned expanded;
	unsigned counter;
	bool do_cpp;
};

struct psi_cpp *psi_cpp_init(struct psi_parser *parser);
bool psi_cpp_process(struct psi_cpp *cpp, struct psi_plist **tokens,
		struct psi_token *expanding);
void psi_cpp_free(struct psi_cpp **cpp_ptr);

bool psi_cpp_if(struct psi_cpp *cpp, struct psi_cpp_exp *exp);
bool psi_cpp_defined(struct psi_cpp *cpp, struct psi_token *tok);
void psi_cpp_define(struct psi_cpp *cpp, struct psi_cpp_macro_decl *decl);
bool psi_cpp_undef(struct psi_cpp *cpp, struct psi_token *tok);

#define PSI_CPP_INCLUDE 0x0
#define PSI_CPP_INCLUDE_NEXT 0x1
#define PSI_CPP_INCLUDE_ONCE 0x2

bool psi_cpp_has_include(struct psi_cpp *cpp, const struct psi_token *file, unsigned flags, char *path);
bool psi_cpp_include(struct psi_cpp *cpp, const struct psi_token *file, unsigned flags);

void psi_cpp_tokiter_reset(struct psi_cpp *cpp);
bool psi_cpp_tokiter_seek(struct psi_cpp *cpp, size_t index);
#if PSI_CPP_DEBUG > 1
void psi_cpp_tokiter_dump(struct psi_dump *dump, struct psi_cpp *cpp);
#endif
struct psi_token *psi_cpp_tokiter_current(struct psi_cpp *cpp);
size_t psi_cpp_tokiter_index(struct psi_cpp *cpp);
void psi_cpp_tokiter_next(struct psi_cpp *cpp);
void psi_cpp_tokiter_prev(struct psi_cpp *cpp);
bool psi_cpp_tokiter_valid(struct psi_cpp *cpp);
bool psi_cpp_tokiter_del_cur(struct psi_cpp *cpp, bool free_token);
bool psi_cpp_tokiter_del_prev(struct psi_cpp *cpp, bool free_token);
bool psi_cpp_tokiter_del_range(struct psi_cpp *cpp, size_t offset,
		size_t num_eles, bool free_tokens);
bool psi_cpp_tokiter_add(struct psi_cpp *cpp, struct psi_token *tok);
bool psi_cpp_tokiter_add_cur(struct psi_cpp *cpp);
bool psi_cpp_tokiter_add_range(struct psi_cpp *cpp,
		size_t num_eles, void **eles);
bool psi_cpp_tokiter_ins_range(struct psi_cpp *cpp,
		size_t num_eles, void **eles);
bool psi_cpp_tokiter_defined(struct psi_cpp *cpp);
bool psi_cpp_tokiter_expand(struct psi_cpp *cpp);

#endif
