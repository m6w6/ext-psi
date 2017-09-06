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

#include "php_psi_stdinc.h"
#include "data.h"
#include "calc.h"

#include "php.h"
#include "php_psi.h"

#include "Zend/zend_interfaces.h"
#include "ext/spl/spl_iterators.h"

zend_long psi_zval_count(zval *zvalue)
{
	/* mimic PHP count() */
	zend_long count;
	zval retval;

	switch (Z_TYPE_P(zvalue)) {
	default:
		count = 1;
		break;
	case IS_NULL:
		count = 0;
		break;
	case IS_ARRAY:
		count = zend_array_count(Z_ARRVAL_P(zvalue));
		break;
	case IS_OBJECT:
		count = 1;
		if (Z_OBJ_HT_P(zvalue)->count_elements) {
			if (SUCCESS == Z_OBJ_HT_P(zvalue)->count_elements(zvalue, &count)) {
				break;
			}
		}

		if (instanceof_function(Z_OBJCE_P(zvalue), spl_ce_Countable)) {
			zend_call_method_with_0_params(zvalue, NULL, NULL, "count", &retval);
			if (Z_TYPE(retval) != IS_UNDEF) {
				count = zval_get_long(&retval);
				zval_ptr_dtor(&retval);
			}
		}
		break;
	}

	return count;
}

int psi_internal_type(struct psi_impl_type *type)
{
	switch (type->type) {
	case PSI_T_BOOL:
		return _IS_BOOL;
	case PSI_T_INT:
		return IS_LONG;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		return IS_DOUBLE;
	case PSI_T_STRING:
		return IS_STRING;
	case PSI_T_ARRAY:
		return IS_ARRAY;
	default:
		return 0;
	}
}

zend_internal_arg_info *psi_internal_arginfo(struct psi_impl *impl)
{
	size_t i = 0, argc = psi_plist_count(impl->func->args);
	zend_internal_arg_info *aip;
	zend_internal_function_info *fi;
	struct psi_impl_arg *iarg;

	aip = calloc(argc + 1 + !!impl->func->vararg, sizeof(*aip));

	fi = (zend_internal_function_info *) &aip[0];
#ifdef ZEND_TYPE_ENCODE
	fi->type = ZEND_TYPE_ENCODE(psi_internal_type(impl->func->return_type), 1);
#else
	fi->allow_null = 1;
	fi->type_hint = psi_internal_type(impl->func->return_type);
#endif
	fi->required_num_args = psi_impl_num_min_args(impl);
	fi->return_reference = impl->func->return_reference;

	if (impl->func->vararg) {
		struct psi_impl_arg *vararg = impl->func->vararg;
		zend_internal_arg_info *ai = &aip[argc];

		ai->name = vararg->var->name;
#ifdef ZEND_TYPE_ENCODE
		ai->type = ZEND_TYPE_ENCODE(psi_internal_type(vararg->type), 1);
#else
		ai->allow_null = 1;
		ai->type_hint = psi_internal_type(vararg->type);
#endif
		if (vararg->var->reference) {
			ai->pass_by_reference = 1;
		}
		ai->is_variadic = 1;
	}

	while (psi_plist_get(impl->func->args, i++, &iarg)) {
		zend_internal_arg_info *ai = &aip[i];

		ai->name = iarg->var->name;
#ifdef ZEND_TYPE_ENCODE
		ai->type = ZEND_TYPE_ENCODE(psi_internal_type(iarg->type), 1);
#else
		ai->allow_null = 1;
		ai->type_hint = psi_internal_type(iarg->type);
#endif
		if (iarg->var->reference) {
			ai->pass_by_reference = 1;
		}
	}

	return aip;
}

/*
 * return void(dvar)
 */
void psi_set_void(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	RETVAL_NULL();
}

/*
 * ?
 */
impl_val *psi_let_void(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	return tmp;
}

/*
 * set $ivar = zval(dvar)
 */
void psi_set_zval(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame) {
	RETVAL_ZVAL(ret_val->ptr, 1, 0);
}

/*
 * let dvar = zval($ivar)
 */
impl_val *psi_let_zval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	*to_free = tmp->ptr = emalloc(sizeof(zval));
	ZVAL_COPY_VALUE(tmp->ptr, zvalue);
	return tmp;
}

/*
 * return to_bool(dvar)
 */
void psi_set_to_bool(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	psi_set_to_int(return_value, set, ret_val, frame);
	convert_to_boolean(return_value);
}

static inline impl_val *psi_val_boolval(impl_val *tmp, token_t real_type, zend_bool boolval) {
	switch (real_type) {
	case PSI_T_INT8:		tmp->i8 = boolval;		break;
	case PSI_T_UINT8:		tmp->u8 = boolval;		break;
	case PSI_T_INT16:		tmp->i16 = boolval;		break;
	case PSI_T_UINT16:		tmp->u16 = boolval;		break;
	case PSI_T_INT32:		tmp->i32 = boolval;		break;
	case PSI_T_UINT32:		tmp->u32 = boolval;		break;
	case PSI_T_INT64:		tmp->i64 = boolval;		break;
	case PSI_T_UINT64:		tmp->u64 = boolval;		break;
	case PSI_T_FLOAT:		tmp->fval = boolval;	break;
	case PSI_T_DOUBLE:		tmp->dval = boolval;	break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:	tmp->ldval = boolval;	break;
#endif
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return tmp;
}

/*
 * let dvar = boolval($ivar)
 */
impl_val *psi_let_boolval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	zend_bool boolval;
	token_t real_type = spec ? psi_decl_type_get_real(spec->type)->type : PSI_T_UINT8;

	if (ival && impl_type == PSI_T_BOOL) {
		boolval = ival->zend.bval;
	} else {
		boolval = zend_is_true(zvalue);
	}

	return psi_val_boolval(tmp, real_type, boolval);
}

# define RETVAL_LONG_U64(V) \
		if (V > ZEND_LONG_MAX) { \
			char d[24] = {0}; \
			RETVAL_STRING(zend_print_ulong_to_buf(&d[22], V)); \
		} else { \
			RETVAL_LONG(V); \
		}

/*
 * set $ivar = to_int(*dvar)
 */
void psi_set_to_int(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	struct psi_decl_var *var = psi_set_exp_get_decl_var(set);
	token_t t = psi_decl_type_get_real(var->arg->type)->type;
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_INT8:		RETVAL_LONG(v->i8);					break;
	case PSI_T_UINT8:		RETVAL_LONG(v->u8);					break;
	case PSI_T_INT16:		RETVAL_LONG(v->i16);				break;
	case PSI_T_UINT16:		RETVAL_LONG(v->u16);				break;
	case PSI_T_ENUM:
	case PSI_T_INT32:		RETVAL_LONG(v->i32);				break;
	case PSI_T_UINT32:		RETVAL_LONG(v->u32);				break;
	case PSI_T_INT64:		RETVAL_LONG(v->i64);				break;
	case PSI_T_UINT64:		RETVAL_LONG_U64(v->u64);			break;
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		convert_to_long(return_value);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		convert_to_long(return_value);
		break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		RETVAL_DOUBLE((double) v->ldval);
		convert_to_long(return_value);
		break;
#endif
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

static inline impl_val *psi_val_intval(impl_val *tmp, token_t real_type, zend_long intval) {
	switch (real_type) {
	case PSI_T_INT8:		tmp->i8 = intval;		break;
	case PSI_T_UINT8:		tmp->u8 = intval;		break;
	case PSI_T_INT16:		tmp->i16 = intval;		break;
	case PSI_T_UINT16:		tmp->u16 = intval;		break;
	case PSI_T_INT32:		tmp->i32 = intval;		break;
	case PSI_T_UINT32:		tmp->u32 = intval;		break;
	case PSI_T_INT64:		tmp->i64 = intval;		break;
	case PSI_T_UINT64:		tmp->u64 = intval;		break;
	case PSI_T_ENUM:
	case PSI_T_INT:			tmp->ival = intval;		break;
	case PSI_T_LONG:		tmp->lval = intval;		break;
	case PSI_T_FLOAT:		tmp->fval = intval;		break;
	case PSI_T_DOUBLE:		tmp->dval = intval;		break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:	tmp->ldval = intval;	break;
#endif
	EMPTY_SWITCH_DEFAULT_CASE();
	}

	return tmp;
}

/*
 * let dvar = intval($ivar)
 */
impl_val *psi_let_intval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	zend_long intval;
	token_t real_type = spec ? psi_decl_type_get_real(spec->type)->type : PSI_T_LONG;

	if (ival && impl_type == PSI_T_INT) {
		intval = ival->zend.lval;
	} else {
		intval = zval_get_long(zvalue);
	}

	return psi_val_intval(tmp, real_type, intval);
}

/*
 * set $ivar = to_float(dvar)
 */
void psi_set_to_float(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	struct psi_decl_var *var = psi_set_exp_get_decl_var(set);
	token_t t = psi_decl_type_get_real(var->arg->type)->type;
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:		RETVAL_DOUBLE((double) v->fval);	break;
	case PSI_T_DOUBLE:		RETVAL_DOUBLE(v->dval);				break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:	RETVAL_DOUBLE((double) v->ldval);	break;
#endif
	case PSI_T_INT8:		RETVAL_DOUBLE((double) v->i8);		break;
	case PSI_T_UINT8:		RETVAL_DOUBLE((double) v->u8);		break;
	case PSI_T_INT16:		RETVAL_DOUBLE((double) v->i16);		break;
	case PSI_T_UINT16:		RETVAL_DOUBLE((double) v->u16);		break;
	case PSI_T_INT32:		RETVAL_DOUBLE((double) v->i32);		break;
	case PSI_T_UINT32:		RETVAL_DOUBLE((double) v->u32);		break;
	case PSI_T_INT64:		RETVAL_DOUBLE((double) v->i64);		break;
	case PSI_T_UINT64:		RETVAL_DOUBLE((double) v->u64);		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

static inline impl_val *psi_val_floatval(impl_val *tmp, token_t real_type, double floatval) {
	switch (real_type) {
	case PSI_T_INT8:		tmp->i8 = floatval;		break;
	case PSI_T_UINT8:		tmp->u8 = floatval;		break;
	case PSI_T_INT16:		tmp->i16 = floatval;	break;
	case PSI_T_UINT16:		tmp->u16 = floatval;	break;
	case PSI_T_INT32:		tmp->i32 = floatval;	break;
	case PSI_T_UINT32:		tmp->u32 = floatval;	break;
	case PSI_T_INT64:		tmp->i64 = floatval;	break;
	case PSI_T_UINT64:		tmp->u64 = floatval;	break;
	case PSI_T_FLOAT:		tmp->fval = floatval;	break;
	case PSI_T_DOUBLE:		tmp->dval = floatval;	break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:	tmp->ldval = floatval;	break;
#endif
	EMPTY_SWITCH_DEFAULT_CASE();
	}

	return tmp;
}

/*
 * let dvar = floatval($ivar)
 */
impl_val *psi_let_floatval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	double floatval;
	token_t real_type = spec ? psi_decl_type_get_real(spec->type)->type : PSI_T_DOUBLE;

	if (ival && (impl_type == PSI_T_FLOAT || impl_type == PSI_T_DOUBLE)) {
		floatval = ival->dval;
	} else {
		floatval = zval_get_double(zvalue);
	}

	return psi_val_floatval(tmp, real_type, floatval);
}

/*
 * set $ivar = to_string(dvar)
 */
void psi_set_to_string(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	struct psi_decl_var *var = psi_set_exp_get_decl_var(set);
	impl_val *ptr = deref_impl_val(ret_val, var);
	char *str;

	if (var->arg->var->array_size) {
		str = (char *) ptr;
	} else {
		str = ptr->ptr;
	}

	if (str) {
		RETVAL_STRING(str);
	} else {
		RETVAL_EMPTY_STRING();
	}
}

/*
 * set $ivar = to_string(dvar, num_exp)
 */
void psi_set_to_stringl(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame)
{
	struct psi_decl_var *var = psi_set_exp_get_decl_var(set);
	char *str = deref_impl_val(ret_val, var)->ptr;

	if (str) {
		struct psi_set_exp *sub_exp;

		psi_plist_get(set->inner, 0, &sub_exp);
		RETVAL_STRINGL(str, psi_long_num_exp(sub_exp->data.num, frame, NULL));
	} else {
		RETVAL_EMPTY_STRING();
	}
}

/*
 * let dvar = strval($ivar)
 */
impl_val *psi_let_strval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	if (ival && impl_type == PSI_T_STRING) {
		if (ival->zend.str) {
			tmp->ptr = ival->zend.str->val;
		} else {
			tmp->ptr = "";
		}
	} else {
		zend_string *zs = zval_get_string(zvalue);
		tmp->ptr = estrdup(zs->val);
		*to_free = tmp->ptr;
		zend_string_release(zs);
	}

	return tmp;
}

/*
 * let dvar = pathval($ivar)
 */
impl_val *psi_let_pathval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	tmp = psi_let_strval(tmp, spec, impl_type, ival, zvalue, to_free);
	if (SUCCESS != php_check_open_basedir(tmp->ptr)) {
		efree(tmp->ptr);
		tmp->ptr = NULL;
		return *to_free = NULL;
	}
	return tmp;
}

/*
 * let dvar = strlen($ivar)
 */
impl_val *psi_let_strlen(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	if (ival && impl_type == PSI_T_STRING) {
		if (ival->zend.str) {
			tmp->lval = ival->zend.str->len;
		} else {
			tmp->lval = 0;
		}
	} else {
		zend_string *zs = zval_get_string(zvalue);
		tmp->lval = zs->len;
		zend_string_release(zs);
	}

	return tmp;
}

#if 0
static impl_val *iterate(impl_val *val, size_t size, unsigned i, impl_val *tmp)
{
	memset(tmp, 0, sizeof(*tmp));
	memcpy(tmp, ((char *) val) + size * i, size);
	return tmp;
}
#endif

/*
 * set $ivar = to_array(dvar,
 * 		$foo = to_int(d_foo),
 * 		$bar = to_string(d_bar),
 * 		$baz = to_array(*d_next, ...)
 */
void psi_set_to_recursive(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame) {
	set->outer->data.func->handler(return_value, set, r_val, frame);
}

/*
 * set $ivar = to_array(dvar, to_string(*dvar));
 */
void psi_set_to_array_simple(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame)
{
	struct psi_set_exp *sub_exp;
	struct psi_decl_var *var;
	impl_val *ret_val;
	char *ptr;
	size_t size;

	array_init(return_value);

	var = psi_set_exp_get_decl_var(set);
	ret_val = deref_impl_val(r_val, var);
	if ((intptr_t) ret_val <= (intptr_t) 0) {
		return;
	}

	psi_plist_get(set->inner, 0, &sub_exp);

	size = psi_decl_arg_get_size(var->arg);
	for (ptr = ret_val->ptr; *(void **) ptr; ptr += size) {
		zval ele;

		ZVAL_NULL(&ele);
		sub_exp->data.func->handler(&ele, sub_exp, (void *) ptr, frame);
		add_next_index_zval(return_value, &ele);
	}
}

/*
 * set $ivar = to_array(dvar, num_exp, to_string(*dvar));
 */
void psi_set_to_array_counted(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame)
{
	struct psi_set_exp *sub_exp;
	struct psi_decl_var *var;
	impl_val *ret_val;
	char *ptr;
	size_t size;
	zend_long count;

	array_init(return_value);

	var = psi_set_exp_get_decl_var(set);
	ret_val = deref_impl_val(r_val, var);
	if ((intptr_t) ret_val <= (intptr_t) 0) {
		return;
	}

	psi_plist_get(set->inner, 0, &sub_exp);
	count = psi_long_num_exp(sub_exp->data.num, frame, NULL);
	psi_plist_get(set->inner, 1, &sub_exp);

	for (ptr = (char *) ret_val; 0 < count--; ptr += size) {
	size = psi_decl_var_get_size(psi_set_exp_get_decl_var(sub_exp));
		zval ele;

		ZVAL_NULL(&ele);
		sub_exp->data.func->handler(&ele, sub_exp, (void *) &ptr, frame);
		add_next_index_zval(return_value, &ele);
	}
}

#include "call.h"

/*
 * set $ivar = to_array(dvar,
 * 		$foo = to_int(d_foo),
 * 		$bar = to_string(d_bar));
 */
void psi_set_to_array(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame)
{
	struct psi_set_exp *sub_exp;
	struct psi_decl_var *var;
	impl_val *ret_val;
	size_t i = 0;

	array_init(return_value);

	var = psi_set_exp_get_decl_var(set);
	ret_val = deref_impl_val(r_val, var);
	if ((intptr_t) ret_val <= (intptr_t) 0) {
		return;
	}

	while (psi_plist_get(set->inner, i++, &sub_exp)) {
		zval ele;
		struct psi_decl_var *dvar = psi_set_exp_get_decl_var(sub_exp);
		struct psi_impl_var *ivar = psi_set_exp_get_impl_var(sub_exp);
		struct psi_call_frame_symbol *sym;

		sym = psi_call_frame_fetch_symbol(frame, dvar);
		sym->ptr = ((char *) ret_val) + dvar->arg->layout->pos;

		ZVAL_NULL(&ele);
		psi_set_exp_exec_ex(sub_exp, &ele, sym->ptr, frame);
		add_assoc_zval(return_value, ivar->name + 1, &ele);
	}
}

/*
 * let dvar = count($ivar)
 */
impl_val *psi_let_count(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	return psi_val_intval(tmp, psi_decl_type_get_real(spec->type)->type, psi_zval_count(zvalue));
}

/*
 * set $ivar = to_object(dvar)
 */
void psi_set_to_object(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame)
{
	struct psi_decl_var *var = psi_set_exp_get_decl_var(set);
	impl_val *ret_val = deref_impl_val(r_val, var);

	if ((intptr_t) ret_val->ptr > (intptr_t) 0) {
		object_init_ex(return_value, psi_object_get_class_entry());
		PSI_OBJ(return_value, NULL)->data = ret_val->ptr;
	} else {
		RETVAL_NULL();
	}
}

/*
 * let dvar = objval($ivar)
 */
impl_val *psi_let_objval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free)
{
	psi_object *obj;

	if (Z_TYPE_P(zvalue) != IS_OBJECT
	||	!instanceof_function(Z_OBJCE_P(zvalue), psi_object_get_class_entry())) {
		return NULL;
	}

	obj = PSI_OBJ(zvalue, NULL);
	tmp->ptr = obj->data;

	return tmp;
}

