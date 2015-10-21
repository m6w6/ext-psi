
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

int psi_internal_type(impl_type *type)
{
	switch (type->type) {
	case PSI_T_BOOL:
		return _IS_BOOL;
	case PSI_T_INT:
	case PSI_T_LONG:
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

void psi_to_int(impl_val *ret_val, decl_arg *func, zval *return_value)
{
	switch (real_decl_type(func->type)->type) {
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref_impl_val(0, ret_val, func)->dval);
		convert_to_long(return_value);
		break;
	default:
		RETVAL_LONG(deref_impl_val(0, ret_val, func)->lval);
	}
}

void psi_to_string(impl_val *ret_val, decl_arg *func, zval *return_value)
{
	switch (real_decl_type(func->type)->type) {
	case PSI_T_CHAR:
	case PSI_T_SINT8:
	case PSI_T_UINT8:
		if (!func->var->pointer_level) {
			char chr = ret_val->lval;
			RETVAL_STRINGL(&chr, 1);
		} else {
			ret_val = deref_impl_val(1, ret_val, func);
			if (ret_val->ptr) {
				RETVAL_STRING(ret_val->ptr);
			} else {
				RETVAL_EMPTY_STRING();
			}
		}
		break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref_impl_val(0, ret_val, func)->dval);
		convert_to_string(return_value);
		break;
	default:
		RETVAL_LONG(deref_impl_val(0, ret_val, func)->lval);
		convert_to_string(return_value);
		break;
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
				iarg->val.bval = iarg->def->type == PSI_T_TRUE ? 1 : 0;
			}
			Z_PARAM_BOOL(iarg->val.bval);
		} else if (PSI_T_INT == iarg->type->type) {
			if (iarg->def) {
				iarg->val.lval = zend_atol(iarg->def->text, strlen(iarg->def->text));
			}
			Z_PARAM_LONG(iarg->val.lval);
		} else if (PSI_T_FLOAT == iarg->type->type) {
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
			Z_PARAM_STR_EX(iarg->val.str, 1, 0);
			if (iarg->val.str) {
				zend_string_addref(iarg->val.str);
			} else if (iarg->def) {
				iarg->val.str = zend_string_init(str.val, str.len, 0);
			}
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

impl_val *psi_do_let(decl_arg *darg)
{
	impl_val *arg_val = &darg->let->out;
	impl_arg *iarg = darg->let->arg;

	if (!iarg) {
		/* let foo = NULL */
		memset(arg_val, 0, sizeof(*arg_val));
		return arg_val;
	}
	switch (darg->let->val->func->type) {
	case PSI_T_BOOLVAL:
		if (iarg->type->type == PSI_T_BOOL) {
			arg_val->cval = iarg->val.cval;
		} else {
			arg_val->cval = zend_is_true(iarg->_zv);
		}
		break;
	case PSI_T_INTVAL:
		if (iarg->type->type == PSI_T_INT) {
			arg_val->lval = iarg->val.lval;
		} else {
			arg_val->lval = zval_get_long(iarg->_zv);
		}
		break;
	case PSI_T_STRVAL:
		if (iarg->type->type == PSI_T_STRING) {
			arg_val->ptr = estrdup(iarg->val.str->val);
			darg->let->mem = arg_val->ptr;
			zend_string_release(iarg->val.str);
		} else {
			zend_string *zs = zval_get_string(iarg->_zv);
			arg_val->ptr = estrdup(zs->val);
			darg->let->mem = arg_val->ptr;
			zend_string_release(zs);
		}
		break;
	case PSI_T_STRLEN:
		if (iarg->type->type == PSI_T_STRING) {
			arg_val->lval = iarg->val.str->len;
			zend_string_release(iarg->val.str);
		} else {
			zend_string *zs = zval_get_string(iarg->_zv);
			arg_val->lval = zs->len;
			zend_string_release(zs);
		}
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}

	return arg_val;
}

void psi_do_set(zval *return_value, set_func *func, decl_vars *vars)
{
	impl_val *val = (impl_val *) &vars->vars[0]->arg->let->ptr;

	ZVAL_DEREF(return_value);
	zval_dtor(return_value);

	switch (func->type) {
	case PSI_T_TO_STRING:
		psi_to_string(val, vars->vars[0]->arg, return_value);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

void psi_do_return(impl *impl, impl_val *ret_val, zval *return_value)
{
	switch (impl->stmts->ret.list[0]->func->type) {
	case PSI_T_TO_STRING:
		psi_to_string(ret_val, impl->decl->func, return_value);
		break;
	case PSI_T_TO_INT:
		psi_to_int(ret_val, impl->decl->func, return_value);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
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
			if (iarg->val.str) {
				zend_string_release(iarg->val.str);
			}
			break;
		}
	}

	for (i = 0; i < impl->decl->args->count; ++i) {
		decl_arg *darg = impl->decl->args->args[i];

		if (darg->let && darg->let->mem) {
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
