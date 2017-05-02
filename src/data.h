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

#ifndef PSI_DATA_H
#define PSI_DATA_H

#include "types.h"
#include "error.h"
#include "plist.h"

#define PSI_DEBUG 0x1
#define PSI_SILENT 0x2

#include <stdarg.h>

#define PSI_DEBUG_PRINT(ctx, msg, ...) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		fprintf(stderr, msg, __VA_ARGS__); \
	} \
} while(0)


#define PSI_DATA(D) ((struct psi_data *) (D))

#define PSI_DATA_MEMBERS \
	struct psi_decl_file file; \
	struct psi_plist *consts; \
	struct psi_plist *types; \
	struct psi_plist *structs; \
	struct psi_plist *unions; \
	struct psi_plist *enums; \
	struct psi_plist *decls; \
	struct psi_plist *impls; \
	struct psi_plist *libs; \
	psi_error_cb error; \
	char last_error[0x1000]; \
	unsigned errors; \
	unsigned flags

struct psi_data {
	PSI_DATA_MEMBERS;
};

struct psi_data *psi_data_ctor(struct psi_data *data, psi_error_cb error, unsigned flags);
struct psi_data *psi_data_ctor_with_dtors(struct psi_data *data, psi_error_cb error, unsigned flags);
struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src);
bool psi_data_validate(struct psi_data *dst, struct psi_data *src);
void psi_data_dtor(struct psi_data *data);
void psi_data_dump(int fd, struct psi_data *data);

struct psi_validate_stack {
	HashTable types;
	HashTable structs;
	HashTable unions;
};

static inline void psi_validate_stack_ctor(struct psi_validate_stack *stack)
{
	zend_hash_init(&stack->types, 0, NULL, NULL, 0);
	zend_hash_init(&stack->structs, 0, NULL, NULL, 0);
	zend_hash_init(&stack->unions, 0, NULL, NULL, 0);
}

static inline void psi_validate_stack_dtor(struct psi_validate_stack *stack)
{
	zend_hash_destroy(&stack->types);
	zend_hash_destroy(&stack->structs);
	zend_hash_destroy(&stack->unions);
}

#define psi_validate_stack_has_type(s, t) \
	((s) ? zend_hash_str_exists(&(s)->types, (t), strlen(t)) : false)
#define psi_validate_stack_has_struct(s, t) \
	((s) ? zend_hash_str_exists(&(s)->structs, (t), strlen(t)) : false)
#define psi_validate_stack_has_union(s, t) \
	((s) ? zend_hash_str_exists(&(s)->unions, (t), strlen(t)) : false)

#define psi_validate_stack_add_type(s, t, p) \
	do { if (s) zend_hash_str_add_ptr(&(s)->types, (t), strlen(t), (p)); } while(0)
#define psi_validate_stack_add_struct(s, t, p) \
	do { if (s) zend_hash_str_add_ptr(&(s)->structs, (t), strlen(t), (p)); } while(0)
#define psi_validate_stack_add_union(s, t, p) \
	do { if (s) zend_hash_str_add_ptr(&(s)->unions, (t), strlen(t), (p)); } while(0)

#define psi_validate_stack_get_type(s, t) \
	((s) ? zend_hash_str_find_ptr(&(s)->types, (t), strlen(t)) : NULL)
#define psi_validate_stack_get_struct(s, t) \
	((s) ? zend_hash_str_find_ptr(&(s)->structs, (t), strlen(t)) : NULL)
#define psi_validate_stack_get_union(s, t) \
	((s) ? zend_hash_str_find_ptr(&(s)->unions, (t), strlen(t)) : NULL)

#define psi_validate_stack_del_type(s, t) \
	do { if (s) zend_hash_str_del(&(s)->types, (t), strlen(t)); } while(0)
#define psi_validate_stack_del_struct(s, t) \
	do { if (s) zend_hash_str_del(&(s)->structs, (t), strlen(t)); } while(0)
#define psi_validate_stack_del_union(s, t) \
	do { if (s) zend_hash_str_del(&(s)->unions, (t), strlen(t)); } while(0)

#endif
