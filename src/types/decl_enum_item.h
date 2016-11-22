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

#ifndef PSI_TYPES_DECL_ENUM_ITEM_H
#define PSI_TYPES_DECL_ENUM_ITEM_H

struct psi_data;
struct psi_token;
struct psi_num_exp;
struct psi_decl_enum;

struct psi_decl_enum_item {
	struct psi_token *token;
	char *name;
	int64_t val;
	struct psi_num_exp inc;
	struct psi_num_exp *num;
	struct psi_decl_enum_item *prev;
};

struct psi_decl_enum_item *psi_decl_enum_item_init(const char *name, struct psi_num_exp *num);
void psi_decl_enum_item_free(struct psi_decl_enum_item **i_ptr);
void psi_decl_enum_item_dump(int fd, struct psi_decl_enum_item *item);
bool psi_decl_enum_item_validate(struct psi_data *data, struct psi_decl_enum *enm, struct psi_decl_enum_item *item, size_t seq);

#endif
