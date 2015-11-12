
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_psi.h"
#include "parser.h"

#include "libjit.h"
#include "libffi.h"

ZEND_DECLARE_MODULE_GLOBALS(psi);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("psi.engine", "ffi", PHP_INI_SYSTEM, OnUpdateString, engine, zend_psi_globals, psi_globals)
	STD_PHP_INI_ENTRY("psi.directory", "psis", PHP_INI_SYSTEM, OnUpdateString, directory, zend_psi_globals, psi_globals)
PHP_INI_END();

void psi_error(int type, const char *msg, ...)
{
	char buf[0x1000];
	va_list argv;

	va_start(argv, msg);
	vslprintf(buf, 0x1000, msg, argv);
	va_end(argv);

	php_error(type, buf);
}

size_t psi_t_alignment(token_t t)
{
	size_t align;
#define PSI_TAS_D(T) struct PSI_TAS_ ##T { \
	char c; \
	T x; \
}
#define PSI_TAS_P(T) struct PSI_TAS_ ## T ## _pointer { \
	char c; \
	T *x; \
}
#define PSI_TAS_C(T) align = offsetof(struct PSI_TAS_ ##T, x)
#define PSI_TAS_CASE(T) { \
	PSI_TAS_D(T); \
	PSI_TAS_C(T); \
}
	switch (t) {
	case PSI_T_INT8:
		PSI_TAS_CASE(int8_t);
		break;
	case PSI_T_UINT8:
		PSI_TAS_CASE(uint8_t);
		break;
	case PSI_T_INT16:
		PSI_TAS_CASE(int16_t);
		break;
	case PSI_T_UINT16:
		PSI_TAS_CASE(uint16_t);
		break;
	case PSI_T_INT32:
		PSI_TAS_CASE(int32_t);
		break;
	case PSI_T_UINT32:
		PSI_TAS_CASE(uint32_t);
		break;
	case PSI_T_INT64:
		PSI_TAS_CASE(int64_t);
		break;
	case PSI_T_UINT64:
		PSI_TAS_CASE(uint64_t);
		break;
	case PSI_T_FLOAT:
		PSI_TAS_CASE(float);
		break;
	case PSI_T_DOUBLE:
		PSI_TAS_CASE(double);
		break;
	case PSI_T_POINTER:
		{
			PSI_TAS_P(char);
			PSI_TAS_C(char_pointer);
		}
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}

	return align;
}

size_t psi_t_size(token_t t)
{
	size_t size;

	switch (t) {
	case PSI_T_INT8:
	case PSI_T_UINT8:
		size = 1;
		break;
	case PSI_T_INT16:
	case PSI_T_UINT16:
		size = 2;
		break;
	case PSI_T_INT:
		size = sizeof(int);
		break;
	case PSI_T_INT32:
	case PSI_T_UINT32:
		size = 4;
		break;
	case PSI_T_INT64:
	case PSI_T_UINT64:
		size = 8;
		break;
	case PSI_T_FLOAT:
		size = sizeof(float);
		break;
	case PSI_T_DOUBLE:
		size = sizeof(double);
		break;
	case PSI_T_POINTER:
		size = sizeof(char *);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return size;
}

size_t psi_t_align(token_t t, size_t s)
{
	size_t a = psi_t_alignment(t);
	return ((s - 1) | (a - 1)) + 1;
}

int psi_internal_type(impl_type *type)
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

zend_internal_arg_info *psi_internal_arginfo(impl *impl)
{
	size_t i;
	zend_internal_arg_info *aip;
	zend_internal_function_info *fi;

	aip = calloc(impl->func->args->count + 1, sizeof(*aip));

	fi = (zend_internal_function_info *) &aip[0];
	fi->required_num_args = psi_num_min_args(impl);
	fi->return_reference = impl->func->return_reference;
	fi->type_hint = psi_internal_type(impl->func->return_type);

	for (i = 0; i < impl->func->args->count; ++i) {
		impl_arg *iarg = impl->func->args->args[i];
		zend_internal_arg_info *ai = &aip[i+1];

		ai->name = iarg->var->name;
		ai->type_hint = psi_internal_type(iarg->type);
		if (iarg->var->reference) {
			ai->pass_by_reference = 1;
		}
		if (iarg->var->reference || (iarg->def && iarg->def->type == PSI_T_NULL)) {
			ai->allow_null = 1;
		}
	}

	return aip;
}

size_t psi_num_min_args(impl *impl)
{
	size_t i, n = impl->func->args->count;

	for (i = 0; i < impl->func->args->count; ++i) {
		if (impl->func->args->args[i]->def) {
			--n;
		}
	}
	return n;
}

void psi_to_bool(zval *return_value, token_t t, impl_val *ret_val, set_value *set, decl_var *var)
{
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		break;
	default:
		RETVAL_LONG(v->lval);
		break;
	}
	convert_to_boolean(return_value);
}

void psi_to_int(zval *return_value, token_t t, impl_val *ret_val, set_value *set, decl_var *var)
{
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		break;
	default:
		RETVAL_LONG(v->lval);
		return;
	}
	convert_to_long(return_value);
}

void psi_to_double(zval *return_value, token_t t, impl_val *ret_val, set_value *set, decl_var *var)
{
	impl_val *v = deref_impl_val(ret_val, var);

	switch (t) {
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) v->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(v->dval);
		break;
	default:
		RETVAL_DOUBLE((double) v->lval);
		break;
	}
}

void psi_to_string(zval *return_value, token_t t, impl_val *ret_val, set_value *set, decl_var *var)
{
	switch (t) {
	case PSI_T_INT8:
	case PSI_T_UINT8:
		if (!var->arg->var->pointer_level) {
			RETVAL_STRINGL(&ret_val->cval, 1);
		} else {
			ret_val = deref_impl_val(ret_val, var);
			if (ret_val && ret_val->ptr) {
				RETVAL_STRING(ret_val->ptr);
			} else {
				RETVAL_EMPTY_STRING();
			}
		}
		return;
	case PSI_T_FLOAT:
		RETVAL_DOUBLE((double) deref_impl_val(ret_val, var)->fval);
		break;
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref_impl_val(ret_val, var)->dval);
		break;
	default:
		RETVAL_LONG(deref_impl_val(ret_val, var)->lval);
		break;
	}
	convert_to_string(return_value);
}


static impl_val *iterate(impl_val *val, token_t t, unsigned i, impl_val *tmp)
{
	size_t size = psi_t_size(t);

	memset(tmp, 0, sizeof(*tmp));
	memcpy(tmp, val->ptr + size * i, size);
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

void psi_to_array(zval *return_value, token_t t, impl_val *ret_val, set_value *set, decl_var *var)
{
	zval ele;
	unsigned i;
	impl_val tmp;

	array_init(return_value);

	if (t == PSI_T_STRUCT) {
		decl_struct *s = real_decl_type(var->arg->type)->strct;
		ret_val = deref_impl_val(ret_val, var);

		ZEND_ASSERT(s);

		if (set->count) {
			/* explicit member casts */
			for (i = 0; i < set->count; ++i) {
				zval ztmp;
				impl_val *tmp_ptr;
				set_value *sub_set = set->inner[i];
				decl_var *sub_var = sub_set->vars->vars[0];
				decl_arg *sub_arg = sub_var->arg;
				token_t t = real_decl_type(sub_arg->type)->type;
				void *ptr = malloc(sub_arg->layout->len);

				memcpy(ptr, (char *) ret_val->ptr + sub_arg->layout->pos,
						sub_arg->layout->len);
				tmp_ptr = enref_impl_val(ptr, sub_arg->var);
				sub_set->func->handler(&ztmp, t, tmp_ptr, sub_set, sub_var);
				add_assoc_zval(return_value, sub_var->name, &ztmp);
				free(tmp_ptr);
				if (tmp_ptr != ptr) {
					free(ptr);
				}
			}
		}
		return;

//		for (i = 0; i < s->args->count; ++i) {
//			decl_arg *darg = s->args->args[i];
//			impl_val tmp, tmp_ptr;
//			zval ztmp;
//			char *ptr = (char *) ret_val->ptr + darg->layout->pos;
//
//			tmp_ptr.ptr = &tmp;
//			memset(&tmp, 0, sizeof(tmp));
//			memcpy(&tmp, ptr, darg->layout->len);
//			switch (real_decl_type(darg->type)->type) {
//			case PSI_T_FLOAT:
//			case PSI_T_DOUBLE:
//				psi_to_double(&ztmp, real_decl_type(darg->type)->type, &tmp, darg->var);
//				break;
//			case PSI_T_INT8:
//			case PSI_T_UINT8:
//				if (darg->var->pointer_level) {
//					psi_to_string(&ztmp, real_decl_type(darg->type)->type, &tmp_ptr, darg->var);
//					break;
//				}
//				/* no break */
//			case PSI_T_INT16:
//			case PSI_T_UINT16:
//			case PSI_T_INT32:
//			case PSI_T_UINT32:
//			case PSI_T_INT64:
//			case PSI_T_UINT64:
//				psi_to_int(&ztmp, real_decl_type(darg->type)->type, &tmp, darg->var);
//				break;
//			case PSI_T_STRUCT:
//				psi_to_array(&ztmp, real_decl_type(darg->type)->type, &tmp_ptr, darg->var);
//				break;
//			default:
//				printf("t=%d\n", real_decl_type(darg->type)->type);
//				abort();
//			}
//			add_assoc_zval(return_value, darg->var->name, &ztmp);
//		}
		return;
	}
	ret_val = deref_impl_val(ret_val, var);
	for (i = 0; i < var->arg->var->array_size; ++i) {
		impl_val *ptr = iterate(ret_val, t, i, &tmp);

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
}

ZEND_RESULT_CODE psi_parse_args(zend_execute_data *execute_data, impl *impl)
{
	impl_arg *iarg;

	if (!impl->func->args->count) {
		return zend_parse_parameters_none();
	}

	ZEND_PARSE_PARAMETERS_START(psi_num_min_args(impl), impl->func->args->count)
	nextarg:
		iarg = impl->func->args->args[_i];
		if (iarg->def) {
			Z_PARAM_OPTIONAL;
		}
		if (PSI_T_BOOL == iarg->type->type) {
			if (iarg->def) {
				iarg->val.zend.bval = iarg->def->type == PSI_T_TRUE ? 1 : 0;
			}
			Z_PARAM_BOOL(iarg->val.zend.bval);
		} else if (PSI_T_INT == iarg->type->type) {
			if (iarg->def) {
				iarg->val.zend.lval = zend_atol(iarg->def->text, strlen(iarg->def->text));
			}
			Z_PARAM_LONG(iarg->val.zend.lval);
		} else if (PSI_T_FLOAT == iarg->type->type || PSI_T_DOUBLE == iarg->type->type) {
			if (iarg->def) {
				iarg->val.dval = zend_strtod(iarg->def->text, NULL);
			}
			Z_PARAM_DOUBLE(iarg->val.dval);
		} else if (PSI_T_STRING == iarg->type->type) {
			struct {char *val; size_t len;} str;
			if (iarg->def) {
				/* FIXME */
				str.len = strlen(iarg->def->text) - 2;
				str.val = &iarg->def->text[1];
			}
			Z_PARAM_STR_EX(iarg->val.zend.str, 1, 0);
			if (iarg->val.zend.str) {
				zend_string_addref(iarg->val.zend.str);
			} else if (iarg->def) {
				iarg->val.zend.str = zend_string_init(str.val, str.len, 0);
			}
		} else if (PSI_T_ARRAY == iarg->type->type) {
			/* handled as _zv in let or set */
			Z_PARAM_PROLOGUE(0);
		} else {
			error_code = ZPP_ERROR_FAILURE;
			break;
		}
		iarg->_zv = _arg;
		if (_i < _max_num_args) {
			goto nextarg;
		}
	ZEND_PARSE_PARAMETERS_END_EX(return FAILURE);

	return SUCCESS;
}

void *psi_do_calloc(let_calloc *alloc)
{
	decl_type *type = real_decl_type(alloc->type);
	size_t size;

	if (type->type == PSI_T_STRUCT) {
		/* psi_do_clean expects at least one NULL pointer after the struct */
		size = type->strct->size + sizeof(void *);
	} else {
		size = psi_t_size(type->type);
	}

	return ecalloc(alloc->n, size);
}

void *psi_do_let(decl_arg *darg)
{
	impl_arg *iarg = darg->let->arg;
	impl_val *arg_val;

	darg->let->ptr = &darg->let->out;
	arg_val = darg->let->ptr;

	if (!iarg) {
		/* let foo = calloc(1, long);
		 * let foo = NULL;
		 * let foo;
		 */
		if (darg->let->val->func && darg->let->val->func->type == PSI_T_CALLOC) {
			arg_val->ptr = psi_do_calloc(darg->let->val->func->alloc);
			darg->let->mem = arg_val->ptr;
		} else if (darg->var->array_size) {
			arg_val->ptr = ecalloc(darg->var->array_size, sizeof(*arg_val));
			darg->let->mem = arg_val->ptr;
		} else {
			memset(arg_val, 0, sizeof(*arg_val));
		}
	} else {

		switch (darg->let->val->func->type) {
		case PSI_T_BOOLVAL:
			if (iarg->type->type == PSI_T_BOOL) {
				arg_val->cval = iarg->val.zend.bval;
			} else {
				arg_val->cval = zend_is_true(iarg->_zv);
			}
			break;
		case PSI_T_INTVAL:
			if (iarg->type->type == PSI_T_INT) {
				arg_val->lval = iarg->val.zend.lval;
			} else {
				arg_val->lval = zval_get_long(iarg->_zv);
			}
			break;
		case PSI_T_STRVAL:
			if (iarg->type->type == PSI_T_STRING) {
				arg_val->ptr = estrdup(iarg->val.zend.str->val);
				darg->let->mem = arg_val->ptr;
				zend_string_release(iarg->val.zend.str);
			} else {
				zend_string *zs = zval_get_string(iarg->_zv);
				arg_val->ptr = estrdup(zs->val);
				darg->let->mem = arg_val->ptr;
				zend_string_release(zs);
			}
			break;
		case PSI_T_STRLEN:
			if (iarg->type->type == PSI_T_STRING) {
				arg_val->lval = iarg->val.zend.str->len;
				zend_string_release(iarg->val.zend.str);
			} else {
				zend_string *zs = zval_get_string(iarg->_zv);
				arg_val->lval = zs->len;
				zend_string_release(zs);
			}
			break;
		case PSI_T_ARRVAL:
			if (iarg->type->type == PSI_T_ARRAY) {
				decl_type *type = real_decl_type(darg->type);

				switch (type->type) {
				case PSI_T_STRUCT:
					arg_val->ptr = psi_array_to_struct(type->strct, HASH_OF(iarg->_zv));
					darg->let->mem = arg_val->ptr;
					break;
				}
			}
			break;
		EMPTY_SWITCH_DEFAULT_CASE();
		}
	}

	if (darg->let->val && darg->let->val->is_reference) {
		return &darg->let->ptr;
	} else {
		return darg->let->ptr;
	}
}

void psi_do_set(zval *return_value, set_value *set)
{
	impl_val *val = (impl_val *) &set->vars->vars[0]->arg->let->ptr;
	token_t t = real_decl_type(set->vars->vars[0]->arg->type)->type;

	ZVAL_DEREF(return_value);
	zval_dtor(return_value);

	set->func->handler(return_value, t, val, set, set->vars->vars[0]);
}

void psi_do_return(zval *return_value, return_stmt *ret, impl_val *ret_val)
{
	token_t t = real_decl_type(ret->decl->type)->type;

	ret->set->func->handler(return_value, t, ret_val, ret->set, ret->decl->var);
}

void psi_do_free(free_stmt *fre)
{
	size_t i;

	for (i = 0; i < fre->vars->count; ++i) {
		decl_var *dvar = fre->vars->vars[i];

		if (dvar->arg && dvar->arg->let->out.ptr) {
			free(dvar->arg->let->out.ptr);
			dvar->arg->let->out.ptr = NULL;
		}
	}
}

void psi_do_clean(impl *impl)
{
	size_t i;

	for (i = 0; i < impl->func->args->count; ++i ) {
		impl_arg *iarg = impl->func->args->args[i];

		switch (iarg->type->type) {
		case PSI_T_STRING:
			if (iarg->val.zend.str) {
				zend_string_release(iarg->val.zend.str);
			}
			break;
		}
	}

	if (impl->decl->args) for (i = 0; i < impl->decl->args->count; ++i) {
		decl_arg *darg = impl->decl->args->args[i];

		if (darg->let && darg->let->mem) {
			decl_type *type = real_decl_type(darg->type);

			if (type->type == PSI_T_STRUCT) {
				void **ptr = (void **) ((char *) darg->let->mem + type->strct->size);

				while (*ptr) {
					efree(*ptr++);
				}
			}
			efree(darg->let->mem);
			darg->let->mem = NULL;
		}
	}
}

PHP_MINIT_FUNCTION(psi)
{
	PSI_ContextOps *ops;

	REGISTER_INI_ENTRIES();

	if (!strcasecmp(PSI_G(engine), "jit")) {
		ops = PSI_Libjit();
	} else {
		ops = PSI_Libffi();
	}

	PSI_ContextInit(&PSI_G(context), ops, psi_error);
	PSI_ContextBuild(&PSI_G(context), PSI_G(directory));

	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(psi)
{
	PSI_ContextDtor(&PSI_G(context));

	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(psi)
{
#if defined(COMPILE_DL_PSI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(psi)
{
	return SUCCESS;
}
/* }}} */

PHP_MINFO_FUNCTION(psi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psi support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
const zend_function_entry psi_functions[] = {
	PHP_FE_END
};

zend_module_entry psi_module_entry = {
	STANDARD_MODULE_HEADER,
	"psi",
	psi_functions,
	PHP_MINIT(psi),
	PHP_MSHUTDOWN(psi),
	PHP_RINIT(psi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(psi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(psi),
	PHP_PSI_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PSI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(psi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
