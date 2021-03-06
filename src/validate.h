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

#ifndef PSI_VALIDATE_H
#define PSI_VALIDATE_H

struct psi_data;

struct psi_validate_scope {
	struct psi_cpp *cpp;
	HashTable types;
	HashTable structs;
	HashTable unions;
	struct psi_impl *impl;
	struct psi_decl *cb_decl;
	struct psi_cpp_macro_decl *macro;
	struct psi_let_exp *current_let;
	struct psi_set_exp *current_set;
	struct psi_decl_enum *current_enum;
};

bool psi_validate(struct psi_validate_scope *scope, struct psi_data *dst,
		struct psi_data *src);

static inline void psi_validate_scope_ctor(struct psi_validate_scope *scope)
{
	zend_hash_init(&scope->types, 0, NULL, NULL, 0);
	zend_hash_init(&scope->structs, 0, NULL, NULL, 0);
	zend_hash_init(&scope->unions, 0, NULL, NULL, 0);
}

static inline void psi_validate_scope_dtor(struct psi_validate_scope *scope)
{
	zend_hash_destroy(&scope->types);
	zend_hash_destroy(&scope->structs);
	zend_hash_destroy(&scope->unions);
}

bool psi_validate_scope_has_builtin(struct psi_validate_scope *scope,
		zend_string *builtin);

#define psi_validate_scope_has_type(s, t) \
	((s) ? zend_hash_exists(&(s)->types, (t)) : false)
#define psi_validate_scope_has_struct(s, t) \
	((s) ? zend_hash_exists(&(s)->structs, (t)) : false)
#define psi_validate_scope_has_union(s, t) \
	((s) ? zend_hash_exists(&(s)->unions, (t)) : false)

#define psi_validate_scope_add_type(s, t, p) \
	do { if (s) zend_hash_add_ptr(&(s)->types, (t), (p)); } while(0)
#define psi_validate_scope_add_struct(s, t, p) \
	do { if (s) zend_hash_add_ptr(&(s)->structs, (t), (p)); } while(0)
#define psi_validate_scope_add_union(s, t, p) \
	do { if (s) zend_hash_add_ptr(&(s)->unions, (t), (p)); } while(0)

#define psi_validate_scope_get_type(s, t) \
	((s) ? zend_hash_find_ptr(&(s)->types, (t)) : NULL)
#define psi_validate_scope_get_struct(s, t) \
	((s) ? zend_hash_find_ptr(&(s)->structs, (t)) : NULL)
#define psi_validate_scope_get_union(s, t) \
	((s) ? zend_hash_find_ptr(&(s)->unions, (t)) : NULL)

#define psi_validate_scope_del_type(s, t) \
	do { if (s) zend_hash_del(&(s)->types, (t)); } while(0)
#define psi_validate_scope_del_struct(s, t) \
	do { if (s) zend_hash_del(&(s)->structs, (t)); } while(0)
#define psi_validate_scope_del_union(s, t) \
	do { if (s) zend_hash_del(&(s)->unions, (t)); } while(0)


#endif /* PSI_VALIDATE_H */
