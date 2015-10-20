#include "php.h"
#include "libjit.h"
#include "parser_proc.h"
#include "parser.h"

#include <jit/jit.h>

static void init(PSI_Context *C)
{
	C->context = jit_context_create();
}

static void dtor(PSI_Context *C)
{
	jit_context_destroy(C->context);
	C->context = NULL;
}

static inline size_t impl_num_min_args(impl *impl) {
	size_t i, n = impl->func->args->count;

	for (i = 0; i < impl->func->args->count; ++i) {
		if (impl->func->args->args[i]->def) {
			--n;
		}
	}
	return n;
}

static inline jit_abi_t psi_jit_abi(const char *convention) {
	return jit_abi_cdecl;
}
static inline jit_type_t psi_jit_type(token_t t) {
	switch (t) {
	default:
		ZEND_ASSERT(0);
		/* no break */
	case PSI_T_VOID:
		return jit_type_void;
	case PSI_T_SINT8:
		return jit_type_sbyte;
	case PSI_T_UINT8:
		return jit_type_ubyte;
	case PSI_T_SINT16:
		return jit_type_short;
	case PSI_T_UINT16:
		return jit_type_ushort;
	case PSI_T_SINT32:
		return jit_type_int;
	case PSI_T_UINT32:
		return jit_type_uint;
	case PSI_T_SINT64:
		return jit_type_long;
	case PSI_T_UINT64:
		return jit_type_ulong;
	case PSI_T_BOOL:
		return jit_type_sys_bool;
	case PSI_T_CHAR:
		return jit_type_sys_char;
	case PSI_T_SHORT:
		return jit_type_sys_short;
	case PSI_T_INT:
		return jit_type_sys_int;
	case PSI_T_LONG:
		return jit_type_sys_long;
	case PSI_T_FLOAT:
		return jit_type_sys_float;
	case PSI_T_DOUBLE:
		return jit_type_sys_double;
	}
}
static inline jit_type_t psi_jit_decl_type(decl_type *type) {
	return psi_jit_type(real_decl_type(type)->type);
}
static inline jit_type_t psi_jit_decl_arg_type(decl_arg *darg) {
	if (darg->var->pointer_level) {
		return jit_type_void_ptr;
	} else {
		return psi_jit_decl_type(darg->type);
	}
}

typedef struct PSI_ClosureData {
	void *context;
	impl *impl;
	jit_type_t signature;
	jit_type_t params[1];
} PSI_ClosureData;

static inline PSI_ClosureData *PSI_ClosureDataAlloc(void *context, impl *impl) {
	size_t i, c = impl->decl->args->count;
	PSI_ClosureData *data = malloc(sizeof(*data) + (c ? c-1 : c) * sizeof(jit_type_t));

	data->context = context;
	data->impl = impl;
	for (i = 0; i < c; ++i) {
		data->params[i] = psi_jit_decl_arg_type(impl->decl->args->args[i]);
	}
	data->signature = jit_type_create_signature(
		psi_jit_abi(data->impl->decl->abi->convention),
		psi_jit_decl_arg_type(data->impl->decl->func),
		data->params,
		data->impl->decl->args->count,
		1);
	return data;
}


static inline impl_val *deref(unsigned level, impl_val *ret_val, decl_arg *darg) {
	unsigned i;

	for (i = level; i < darg->var->pointer_level; ++i && ret_val->ptr) {
		ret_val = *(void **)ret_val;
	}

	return ret_val;
}
static void to_int(impl_val *ret_val, decl_arg *func, zval *return_value) {
	switch (real_decl_type(func->type)->type) {
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref(0, ret_val, func)->dval);
		convert_to_long(return_value);
		break;
	default:
		RETVAL_LONG(deref(0, ret_val, func)->lval);
	}
}
static void to_string(impl_val *ret_val, decl_arg *func, zval *return_value) {
	switch (real_decl_type(func->type)->type) {
	case PSI_T_CHAR:
	case PSI_T_SINT8:
	case PSI_T_UINT8:
		if (!func->var->pointer_level) {
			char chr = ret_val->lval;
			RETVAL_STRINGL(&chr, 1);
		} else {
			ret_val = deref(1, ret_val, func);
			if (ret_val->ptr) {
				RETVAL_STRING(ret_val->ptr);
			} else {
				RETVAL_EMPTY_STRING();
			}
		}
		break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		RETVAL_DOUBLE(deref(0, ret_val, func)->dval);
		convert_to_string(return_value);
		break;
	default:
		RETVAL_LONG(deref(0, ret_val, func)->lval);
		convert_to_string(return_value);
		break;
	}
}

static ZEND_RESULT_CODE handle_args(zend_execute_data *execute_data, impl *impl) {
	impl_arg *iarg;

	if (!impl->func->args->count) {
		return zend_parse_parameters_none();
	}

	ZEND_PARSE_PARAMETERS_START(impl_num_min_args(impl), impl->func->args->count)
	nextarg:
		iarg = impl->func->args->args[_i];
		if (iarg->def) {
			Z_PARAM_OPTIONAL;
		}
		if (PSI_T_BOOL == iarg->type->type) {
			if (iarg->def) {
				iarg->val.cval = iarg->def->type == PSI_T_TRUE ? 1 : 0;
			}
			Z_PARAM_BOOL(iarg->val.cval);
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

static impl_val *handle_let(decl_arg *darg, impl_arg *iarg) {
	impl_val *arg_val = &darg->let->out;

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

static void handle_rval(impl *impl, impl_val *ret_val, zval *return_value) {
	switch (impl->stmts->ret.list[0]->func->type) {
	case PSI_T_TO_STRING:
		to_string(ret_val, impl->decl->func, return_value);
		break;
	case PSI_T_TO_INT:
		to_int(ret_val, impl->decl->func, return_value);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

static void handle_set(zval *return_value, set_func *func, decl_vars *vars) {
	impl_val *val = &vars->vars[0]->arg->let->ptr;

	ZVAL_DEREF(return_value);
	zval_dtor(return_value);

	switch (func->type) {
	case PSI_T_TO_STRING:
		to_string(val, vars->vars[0]->arg, return_value);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}

static void handle_free(free_stmt *fre) {
	size_t i;

	for (i = 0; i < fre->vars->count; ++i) {
		decl_var *dvar = fre->vars->vars[i];

		if (dvar->arg && dvar->arg->let->out.ptr) {
			free(dvar->arg->let->out.ptr);
			dvar->arg->let->out.ptr = NULL;
		}
	}
}

static void handler(jit_type_t _sig, void *result, void **_args, void *_data)
{
	PSI_ClosureData *data = _data;
	size_t i;
	void **arg_ptr = NULL, **arg_prm = NULL;
	impl_val ret_val;

	if (SUCCESS != handle_args(*(zend_execute_data **)_args[0], data->impl)) {
		return;
	}

	if (data->impl->decl->args->count) {
		arg_ptr = malloc(data->impl->decl->args->count * sizeof(*arg_ptr));
		arg_prm = malloc(data->impl->decl->args->count * sizeof(*arg_prm));

		for (i = 0; i < data->impl->decl->args->count; ++i) {
			decl_arg *darg = data->impl->decl->args->args[i];
			impl_arg *iarg = darg->let ? darg->let->arg : NULL;

			arg_ptr[i] = handle_let(darg, iarg);
			arg_prm[i] = darg->let->val->is_reference ? &arg_ptr[i] : arg_ptr[i];

			darg->let->ptr = arg_ptr[i];
		}
	}

	jit_apply(data->signature, data->impl->decl->dlptr, arg_prm, data->impl->decl->args->count, &ret_val);

	handle_rval(data->impl, &ret_val, *(zval **)_args[1]);

	for (i = 0; i < data->impl->stmts->set.count; ++i) {
		set_stmt *set = data->impl->stmts->set.list[i];

		handle_set(set->arg->_zv, set->val->func, set->val->vars);
	}

	if (data->impl->decl->args->count) {
		for (i = 0; i < data->impl->decl->args->count; ++i) {
			decl_arg *darg = data->impl->decl->args->args[i];

			if (darg->let && darg->let->mem) {
				efree(darg->let->mem);
				darg->let->mem = NULL;
			}
		}
		free(arg_ptr);
		free(arg_prm);
	}

	for (i = 0; i < data->impl->stmts->fre.count; ++i) {
		free_stmt *fre = data->impl->stmts->fre.list[i];

		handle_free(fre);
	}
}

static inline int fill_type_hint(impl_type *type) {
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

static inline zend_internal_arg_info *fill_arginfo(impl *impl) {
	size_t i;
	zend_internal_arg_info *aip;
	zend_internal_function_info *fi;

	aip = calloc(impl->func->args->count + 1, sizeof(*aip));

	fi = (zend_internal_function_info *) &aip[0];
	fi->required_num_args = impl_num_min_args(impl);
	fi->return_reference = impl->func->return_reference;
	fi->type_hint = fill_type_hint(impl->func->return_type);

	for (i = 0; i < impl->func->args->count; ++i) {
		impl_arg *iarg = impl->func->args->args[i];
		zend_internal_arg_info *ai = &aip[i+1];

		ai->name = iarg->var->name;
		ai->type_hint = fill_type_hint(iarg->type);
		if (iarg->var->reference) {
			ai->pass_by_reference = 1;
		}
		if (iarg->var->reference || (iarg->def && iarg->def->type == PSI_T_NULL)) {
			ai->allow_null = 1;
		}
	}

	return aip;
}

static zend_function_entry *compile(PSI_Context *C, PSI_Data *D)
{
	size_t i, j = 0;
	jit_type_t signature, params[] = {
		jit_type_void_ptr,
		jit_type_void_ptr
	};
	zend_function_entry *zfe = calloc(D->impls->count + 1, sizeof(*zfe));

	jit_context_build_start(C->context);

	for (i = 0; i < D->impls->count; ++i) {
		zend_function_entry *zf = &zfe[j];
		PSI_ClosureData *data;

		if (!D->impls->list[i]->decl) {
			continue;
		}

		data = PSI_ClosureDataAlloc(C, D->impls->list[i]);
		signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 2, 1);
		zf->fname = D->impls->list[i]->func->name + (D->impls->list[i]->func->name[0] == '\\');
		zf->handler = jit_closure_create(C->context, signature, &handler, data);
		zf->num_args = D->impls->list[i]->func->args->count;
		zf->arg_info = fill_arginfo(D->impls->list[i]);
		++j;
	}

	jit_context_build_end(C->context);

	return zfe;
}

static PSI_ContextOps ops = {
	init,
	dtor,
	compile,
};

PSI_ContextOps *PSI_Libjit(void)
{
	return &ops;
}
