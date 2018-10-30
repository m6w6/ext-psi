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

#ifndef PSI_TYPES_H
#define PSI_TYPES_H

#include "token.h"
#include "types/impl_val.h"
#include "types/decl_type.h"
#include "types/decl_var.h"
#include "types/decl_arg.h"
#include "types/decl_abi.h"
#include "types/decl.h"
#include "types/decl_extvar.h"
#include "types/decl_struct.h"
#include "types/decl_union.h"
#include "types/impl_type.h"
#include "types/impl_var.h"
#include "types/impl_def_val.h"
#include "types/const.h"
#include "types/impl_arg.h"
#include "types/impl_func.h"
#include "types/number.h"
#include "types/num_exp.h"
#include "types/decl_enum_item.h"
#include "types/decl_enum.h"
#include "types/let_calloc.h"
#include "types/let_callback.h"
#include "types/let_func.h"
#include "types/let_exp.h"
#include "types/let_stmt.h"
#include "types/set_func.h"
#include "types/set_exp.h"
#include "types/set_stmt.h"
#include "types/return_stmt.h"
#include "types/return_exp.h"
#include "types/free_stmt.h"
#include "types/impl.h"
#include "types/decl_file.h"
#include "types/free_exp.h"
#include "types/free_stmt.h"
#include "types/assert_stmt.h"
#include "types/layout.h"
#include "types/cpp_exp.h"
#include "types/cpp_macro_call.h"
#include "types/cpp_macro_decl.h"

static inline impl_val *deref_impl_val(impl_val *ret_val, struct psi_decl_var *var) {
	unsigned i;

	ZEND_ASSERT(!var->arg || var->arg->var != var);
#if 0
	fprintf(stderr, "deref: %s pl=%u:%u as=%u:%u %p\n",
			var->name->val, var->pointer_level, var->arg->var->pointer_level,
			var->array_size, var->arg->var->array_size, ret_val);
#endif
	for (i = 0; i < var->pointer_level; ++i) {
#if 0
		fprintf(stderr, "-- %p %p %p\n", ret_val, *(void**)ret_val, ret_val->ptr);
#endif
		ret_val = *(void **) ret_val;
	}
	return ret_val;
}

static inline impl_val *enref_impl_val(void *ptr, struct psi_decl_var *var) {
	impl_val *val, *val_ptr;
	unsigned i;

	ZEND_ASSERT(var->arg->var == var);
#if 0
	fprintf(stderr, "enref: %s pl=%u:%u as=%u:%u\n",
			var->name->val, var->pointer_level, var->arg->var->pointer_level,
			var->array_size, var->arg->var->array_size);
#endif
	if (!var->pointer_level ){//&& real_decl_type(var->arg->type)->type != PSI_T_STRUCT) {
		return ptr;
	}

	val = calloc(var->pointer_level + 1, sizeof(void *));
	val_ptr = val;
	for (i = !var->arg->var->array_size; i < var->pointer_level; ++i) {
#if 0
		fprintf(stderr, "++\n");
#endif
		val_ptr->ptr = (void **) val_ptr + 1;
		val_ptr = val_ptr->ptr;
	}
	val_ptr->ptr = ptr;
	return val;
}

static inline impl_val *struct_member_ref(struct psi_decl_arg *set_arg, impl_val *struct_ptr, impl_val **to_free) {
	void *ptr = (char *) struct_ptr + set_arg->layout->pos;
#if 0
	fprintf(stderr, "struct member %s: %p\n", set_arg->var->name->val, ptr);
#endif
	return ptr;
}

#endif
