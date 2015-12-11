
#ifndef PHP_PSI_H
#define PHP_PSI_H

extern zend_module_entry psi_module_entry;
#define phpext_psi_ptr &psi_module_entry

#define PHP_PSI_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_PSI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PSI_API __attribute__ ((visibility("default")))
#else
#	define PHP_PSI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "context.h"
#include "parser.h"

void psi_error(int type, const char *msg, ...);

static inline int psi_check_env(const char *var) {
	char *set = getenv(var);
	return (set && *set && '0' != *set);
}

typedef struct psi_object {
	void *data;
	size_t size;
	zend_object std;
} psi_object;

static inline psi_object *PSI_OBJ(zval *zv, zend_object *zo) {
	if (zv) {
		zo = Z_OBJ_P(zv);
	}
	return (void *) (((char *) zo) - zo->handlers->offset);
}

size_t psi_t_alignment(token_t t);
size_t psi_t_size(token_t t);
size_t psi_t_align(token_t t, size_t s);

int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

void psi_to_void(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_bool(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_int(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_double(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_string(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_array(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_object(zval *return_value, set_value *set, impl_val *ret_val);

void psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl);

static inline int psi_calc_num_exp_value(num_exp *exp, impl_val *val) {
	switch (exp->t) {
	case PSI_T_NUMBER:
		switch (is_numeric_string(exp->u.numb, strlen(exp->u.numb), (zend_long *) val, (double *) val, 0)) {
		case IS_LONG:
			return PSI_T_INT64;
		case IS_DOUBLE:
			return PSI_T_DOUBLE;
		}
		break;

	case PSI_T_NSNAME:
		switch (exp->u.cnst->type->type) {
		case PSI_T_INT:
			val->i64 = zend_get_constant_str(exp->u.cnst->name, strlen(exp->u.cnst->name))->value.lval;
			return PSI_T_INT64;
		case PSI_T_FLOAT:
			val->dval = zend_get_constant_str(exp->u.cnst->name, strlen(exp->u.cnst->name))->value.dval;
			return PSI_T_DOUBLE;
		default:
			return 0;
		}
		break;

	case PSI_T_NAME:
		switch (real_decl_type(exp->u.dvar->arg->type)->type) {
		case PSI_T_INT8:
		case PSI_T_UINT8:
		case PSI_T_INT16:
		case PSI_T_UINT16:
		case PSI_T_INT32:
		case PSI_T_UINT32:
		case PSI_T_INT64:
		case PSI_T_UINT64:
			memcpy(val, deref_impl_val(exp->u.dvar->arg->let->ptr, exp->u.dvar), sizeof(*val));
			return real_decl_type(exp->u.dvar->arg->type)->type;

		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
			memcpy(val, deref_impl_val(exp->u.dvar->arg->let->ptr, exp->u.dvar), sizeof(*val));
			return real_decl_type(exp->u.dvar->arg->type)->type;

		EMPTY_SWITCH_DEFAULT_CASE();
		}
		break;

	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return  0;
}

static inline int psi_calc_num_exp(num_exp *exp, impl_val *val) {
	impl_val num = {0};
	int num_type = psi_calc_num_exp_value(exp, &num);

	if (exp->operand) {
		impl_val tmp = {0};
		int tmp_type = psi_calc_num_exp(exp->operand, &tmp);

		return exp->calculator(num_type, &num, tmp_type, &tmp, val);
	}

	memcpy(val, &num, sizeof(*val));
	return num_type;
}

static inline zend_long psi_long_num_exp(num_exp *exp) {
	impl_val val = {0};

	switch (psi_calc_num_exp(exp, &val)) {
	case PSI_T_UINT8:	val.u16 = val.u8;
	case PSI_T_UINT16:	val.u32 = val.u16;
	case PSI_T_UINT32:	val.u64 = val.u32;
	case PSI_T_UINT64:	return val.u64;
	case PSI_T_INT8:	val.i16 = val.i8;
	case PSI_T_INT16:	val.i32 = val.i16;
	case PSI_T_INT32:	val.i64 = val.i32;
	case PSI_T_INT64:	return val.i64;
	case PSI_T_FLOAT:	val.dval = val.fval;
	case PSI_T_DOUBLE:	return val.dval;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

ZEND_BEGIN_MODULE_GLOBALS(psi)
	char *engine;
	char *directory;
	PSI_Context context;
ZEND_END_MODULE_GLOBALS(psi);

#define PSI_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(psi, v)

#if defined(ZTS) && defined(COMPILE_DL_PSI)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_PSI_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
