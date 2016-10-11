#ifndef _PSI_TYPES_H
#define _PSI_TYPES_H

#include "token.h"

#include "types/impl_val.h"
#include "types/decl_type.h"
#include "types/decl_var.h"
#include "types/decl_struct_layout.h"
#include "types/decl_arg.h"
#include "types/decl_typedefs.h"
#include "types/decl_vars.h"
#include "types/decl_args.h"
#include "types/decl_abi.h"
#include "types/decl_callinfo.h"
#include "types/decl.h"
#include "types/decls.h"
#include "types/decl_struct.h"
#include "types/decl_structs.h"
#include "types/decl_union.h"
#include "types/decl_unions.h"
#include "types/impl_type.h"
#include "types/impl_var.h"
#include "types/impl_def_val.h"
#include "types/const_type.h"
#include "types/constant.h"
#include "types/constants.h"
#include "types/impl_arg.h"
#include "types/impl_args.h"
#include "types/impl_func.h"
#include "types/num_exp.h"
#include "types/decl_enum_item.h"
#include "types/decl_enum_items.h"
#include "types/decl_enum.h"
#include "types/decl_enums.h"
#include "types/let_calloc.h"
#include "types/let_callback.h"
#include "types/let_func.h"
#include "types/let_val.h"
#include "types/let_vals.h"
#include "types/let_stmt.h"
#include "types/set_func.h"
#include "types/set_value.h"
#include "types/set_values.h"
#include "types/set_stmt.h"
#include "types/return_stmt.h"
#include "types/free_call.h"
#include "types/free_calls.h"
#include "types/free_stmt.h"
#include "types/impl_stmt.h"
#include "types/impl_stmts.h"
#include "types/impl.h"
#include "types/impls.h"
#include "types/decl_file.h"
#include "types/decl_libs.h"

static inline impl_val *deref_impl_val(impl_val *ret_val, decl_var *var) {
	unsigned i;

	ZEND_ASSERT(var->arg->var != var);
#if 0
	fprintf(stderr, "deref: %s pl=%u:%u as=%u:%u %p\n",
			var->name, var->pointer_level, var->arg->var->pointer_level,
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

static inline impl_val *enref_impl_val(void *ptr, decl_var *var) {
	impl_val *val, *val_ptr;
	unsigned i;

	ZEND_ASSERT(var->arg->var == var);
#if 0
	fprintf(stderr, "enref: %s pl=%u:%u as=%u:%u\n",
			var->name, var->pointer_level, var->arg->var->pointer_level,
			var->array_size, var->arg->var->array_size);
#endif
	if (!var->pointer_level ){//&& real_decl_type(var->arg->type)->type != PSI_T_STRUCT) {
		return ptr;
	}

	val = val_ptr = calloc(var->pointer_level + 1, sizeof(void *));
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

static inline impl_val *struct_member_ref(decl_arg *set_arg, impl_val *struct_ptr, impl_val **to_free) {
	void *ptr = (char *) struct_ptr + set_arg->layout->pos;
#if 0
	fprintf(stderr, "struct member %s: %p\n", set_arg->var->name, ptr);
#endif
	return ptr;
}

#endif
