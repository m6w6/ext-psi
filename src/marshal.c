#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_psi.h"

#include "marshal.h"
#include "calc.h"

void psi_to_void(zval *return_value, set_value *set, impl_val *ret_val)
{
	RETVAL_NULL();
}

void psi_to_bool(zval *return_value, set_value *set, impl_val *ret_val)
{
	psi_to_int(return_value, set, ret_val);
	convert_to_boolean(return_value);
}

void psi_to_int(zval *return_value, set_value *set, impl_val *ret_val)
{
	decl_var *var = set->vars->vars[0];
	token_t t = real_decl_type(var->arg->type)->type;
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		convert_to_long(return_value);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		convert_to_long(return_value);
		break;
	case PSI_T_INT8:
		RETVAL_LONG(v->i8);
		break;
	case PSI_T_UINT8:
		RETVAL_LONG(v->u8);
		break;
	case PSI_T_INT16:
		RETVAL_LONG(v->i16);
		break;
	case PSI_T_UINT16:
		RETVAL_LONG(v->u16);
		break;
	case PSI_T_INT32:
		RETVAL_LONG(v->i32);
		break;
	case PSI_T_UINT32:
#if UINT32_MAX >= ZEND_LONG_MAX
		if (v->u32 > ZEND_LONG_MAX) {
			char d[12] = {0};

			RETVAL_STRING(zend_print_ulong_to_buf(&d[10], v->u32));
		} else {
#endif
			RETVAL_LONG(v->u32);
#if UINT32_MAX >= ZEND_LONG_MAX
		}
#endif
		break;
	case PSI_T_INT64:
		RETVAL_LONG(v->i64);
		break;
	case PSI_T_UINT64:
		if (v->u64 > ZEND_LONG_MAX) {
			char d[24] = {0};

			RETVAL_STRING(zend_print_ulong_to_buf(&d[22], v->u64));
		} else {
			RETVAL_LONG(v->u64);
		}
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

void psi_to_double(zval *return_value, set_value *set, impl_val *ret_val)
{
	decl_var *var = set->vars->vars[0];
	token_t t = real_decl_type(var->arg->type)->type;
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		RETVAL_DOUBLE((double) v->ldval);
		break;
#endif
	case PSI_T_INT8:
		RETVAL_DOUBLE((double) v->i8);
		break;
	case PSI_T_UINT8:
		RETVAL_DOUBLE((double) v->u8);
		break;
	case PSI_T_INT16:
		RETVAL_DOUBLE((double) v->i16);
		break;
	case PSI_T_UINT16:
		RETVAL_DOUBLE((double) v->u16);
		break;
	case PSI_T_INT32:
		RETVAL_DOUBLE((double) v->i32);
		break;
	case PSI_T_UINT32:
		RETVAL_DOUBLE((double) v->u32);
		break;
	case PSI_T_INT64:
		RETVAL_DOUBLE((double) v->i64);
		break;
	case PSI_T_UINT64:
		RETVAL_DOUBLE((double) v->u64);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

void psi_to_string(zval *return_value, set_value *set, impl_val *ret_val)
{
	char *str;
	decl_var *var = set->vars->vars[0];
	token_t t = real_decl_type(var->arg->type)->type;

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) deref_impl_val(ret_val, var)->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref_impl_val(ret_val, var)->dval);
		break;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		RETVAL_DOUBLE((double) deref_impl_val(ret_val, var)->ldval);
		break;
#endif
	default:
		if (!var->arg->var->pointer_level) {
			RETVAL_STRINGL(&ret_val->cval, 1);
		} else {
			ret_val = deref_impl_val(ret_val, var);
			if (var->arg->var->array_size) {
				str = (char *) ret_val;
			} else {
				str = ret_val->ptr;
			}
			if (str) {
				if (set->num) {
					zend_long n = psi_long_num_exp(set->num, set->outer.val);
					RETVAL_STRINGL(str, n);
				} else {
					RETVAL_STRING(str);
				}
			} else {
				RETVAL_EMPTY_STRING();
			}
		}
		return;
	}
	convert_to_string(return_value);
}


static impl_val *iterate(impl_val *val, size_t size, unsigned i, impl_val *tmp)
{
	memset(tmp, 0, sizeof(*tmp));
	memcpy(tmp, ((void*) val) + size * i, size);
	return tmp;
}

void psi_from_zval(impl_val *mem, decl_arg *spec, zval *zv, void **tmp)
{
	decl_type *type = real_decl_type(spec->type);

	switch (type->type) {
	case PSI_T_FLOAT:
		mem->fval = (float) zval_get_double(zv);
		break;
	case PSI_T_DOUBLE:
		mem->dval = zval_get_double(zv);
		break;
	case PSI_T_VOID:
	case PSI_T_INT8:
	case PSI_T_UINT8:
		if (spec->var->pointer_level) {
			zend_string *zs = zval_get_string(zv);
			*tmp = mem->ptr = estrndup(zs->val, zs->len);
			zend_string_release(zs);
			break;
		}
		/* no break */
	default:
		mem->zend.lval = zval_get_long(zv);
		break;
	}
}

void *psi_array_to_struct(decl_struct *s, HashTable *arr)
{
	size_t i, j = 0;
	char *mem = ecalloc(1, s->size + s->args->count * sizeof(void *));

	if (arr) for (i = 0; i < s->args->count; ++i) {
		decl_arg *darg = s->args->args[i];
		zval *entry = zend_hash_str_find_ind(arr, darg->var->name, strlen(darg->var->name));

		if (entry) {
			impl_val val;
			void *tmp = NULL;

			memset(&tmp, 0, sizeof(tmp));
			psi_from_zval(&val, darg, entry, &tmp);
			memcpy(mem + darg->layout->pos, &val, darg->layout->len);
			if (tmp) {
				((void **)(mem + s->size))[j++] = tmp;
			}
		}
	}
	return mem;
}

void psi_to_recursive(zval *return_value, set_value *set, impl_val *r_val)
{
	set->outer.set->func->handler(return_value, set, r_val);
}

void psi_to_array(zval *return_value, set_value *set, impl_val *r_val)
{
	size_t i;
	decl_var *var = set->vars->vars[0];
	token_t t = real_decl_type(var->arg->type)->type;
	impl_val tmp, *ret_val = deref_impl_val(r_val, var);

	if ((intptr_t) ret_val <= (intptr_t) 0) {
		RETURN_NULL();
	}

	array_init(return_value);

	if (t == PSI_T_STRUCT) {
		// decl_struct *s = real_decl_type(var->arg->type)->strct;

		if (set->count) {
			/* explicit member casts */
			for (i = 0; i < set->count; ++i) {
				set_value *sub_set = set->inner[i];
				decl_var *sub_var = sub_set->vars->vars[0];

				sub_set->outer.val = ret_val;

				if (sub_var->arg) {
					impl_val *tmp = NULL, *val;
					zval ztmp;

					val = struct_member_ref(sub_var->arg, ret_val, &tmp);
					sub_set->func->handler(&ztmp, sub_set, val);
					add_assoc_zval(return_value, sub_var->name, &ztmp);

					if (tmp) {
						free(tmp);
					}
				}
			}
		}
		return;
	}

	if (var->arg->var->array_size) {
		/* to_array(foo[NUMBER]) */
		for (i = 0; i < var->arg->var->array_size; ++i) {
			size_t size = psi_t_size(var->arg->var->pointer_level > 1 ? PSI_T_POINTER : t);
			impl_val *ptr = iterate(ret_val, size, i, &tmp);
			zval ele;

			switch (t) {
			case PSI_T_FLOAT:
				ZVAL_DOUBLE(&ele, (double) ptr->fval);
				break;
			case PSI_T_DOUBLE:
				ZVAL_DOUBLE(&ele, ptr->dval);
				break;
			default:
				ZVAL_LONG(&ele, ptr->lval);
				break;
			}

			add_next_index_zval(return_value, &ele);
		}
		return;
	} else if (set->num) {
		/* to_array(arr_var, num_expr, to_int(*arr_var)) */
		zval ele;
		char *ptr;
		zend_long i, n = psi_long_num_exp(set->num, set->outer.val);
		size_t size = psi_t_size(var->arg->var->pointer_level ? PSI_T_POINTER : t);
		set_value *sub_set = set->inner[0];

		sub_set->outer.val = set->outer.val;
		for (i = 0; i < n; ++i) {
			ptr = (char *) ret_val->ptr + i * size;
			sub_set->func->handler(&ele, sub_set, (void *) ptr);
			add_next_index_zval(return_value, &ele);
		}
	} else {
		/* to_array(arr_var, to_int(*arr_var)) */
		zval ele;
		char *ptr = ret_val->ptr;
		size_t size = psi_t_size(var->arg->var->pointer_level ? PSI_T_POINTER : t);
		set_value *sub_set = set->inner[0];

		sub_set->outer.val = set->outer.val;
		while (*(void **) ptr) {
			sub_set->func->handler(&ele, sub_set, (void *) ptr);
			add_next_index_zval(return_value, &ele);
			ptr += size;
		}
	}
}

void psi_to_object(zval *return_value, set_value *set, impl_val *r_val)
{
	decl_var *var = set->vars->vars[0];
	impl_val *ret_val = deref_impl_val(r_val, var);
	psi_object *obj;

	if ((intptr_t) ret_val->ptr > (intptr_t) 0) {
		object_init_ex(return_value, psi_object_get_class_entry());
		obj = PSI_OBJ(return_value, NULL);
		obj->data = ret_val->ptr;
	} else {
		RETVAL_NULL();
	}
}
