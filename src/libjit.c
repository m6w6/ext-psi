#include "php.h"
#include "libjit.h"
#include "parser_proc.h"

static void init(PSI_Context *C)
{
	C->opaque = jit_context_create();
}

static void dtor(PSI_Context *C)
{
	jit_context_destroy(C->opaque);
}

typedef struct PSI_ClosureData {
	void *context;
	impl *impl;
	jit_type_t signature;
	zval return_value;
} PSI_ClosureData;

static inline PSI_ClosureData *PSI_ClosureDataAlloc(void *context, impl *impl) {
	PSI_ClosureData *data = malloc(sizeof(*data));

	data->context = context;
	data->impl = impl;

	return data;
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
	default:
		abort();
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
static void handler(jit_type_t _sig, void *result, void **_args, void *_data)
{
	zend_execute_data *execute_data = *(zend_execute_data **)_args[0];
	zval *return_value = *(zval **)_args[1];
	PSI_ClosureData *data = _data;
	impl_arg *iarg;
	size_t i;
	void **arg_ptr = NULL, **arg_prm = NULL;
	impl_val ret_val, *arg_val = NULL;
	jit_type_t signature, *sig_prm;

	if (!data->impl->func->args->count) {
		if (SUCCESS != zend_parse_parameters_none()) {
			return;
		}
	} else
	ZEND_PARSE_PARAMETERS_START(impl_num_min_args(data->impl), data->impl->func->args->count)
	nextarg:
		iarg = data->impl->func->args->args[_i];
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
			if (iarg->def) {
				/* FIXME */
				iarg->val.str.len = strlen(iarg->def->text) - 2;
				iarg->val.str.val = &iarg->def->text[1];
			}
			Z_PARAM_STRING(iarg->val.str.val, iarg->val.str.len);
		} else {
			error_code = ZPP_ERROR_FAILURE;
			break;
		}
		iarg->_zv = _arg;
		if (_i < _max_num_args) {
			goto nextarg;
		}
	ZEND_PARSE_PARAMETERS_END();

	if (data->impl->decl->args->count) {
		arg_ptr = malloc(data->impl->decl->args->count * sizeof(*arg_ptr));
		arg_prm = malloc(data->impl->decl->args->count * sizeof(*arg_prm));
		arg_val = malloc(data->impl->decl->args->count * sizeof(*arg_val));
		sig_prm = malloc(data->impl->decl->args->count * sizeof(*sig_prm));

		for (i = 0; i < data->impl->decl->args->count; ++i) {
			decl_arg *darg = data->impl->decl->args->args[i];
			impl_arg *iarg = darg->let->arg;

			switch (darg->let->val->func->type) {
			case PSI_T_BOOLVAL:
				if (iarg->type->type == PSI_T_BOOL) {
					arg_val[i].bval = iarg->val.bval;
				} else {
					arg_val[i].bval = zend_is_true(iarg->_zv);
				}
				break;
			case PSI_T_INTVAL:
				if (iarg->type->type == PSI_T_INT) {
					arg_val[i].lval = iarg->val.lval;
				} else {
					arg_val[i].lval = zval_get_long(iarg->_zv);
				}
				break;
			case PSI_T_STRVAL:
				if (iarg->type->type == PSI_T_STRING) {
					arg_val[i].str.val = estrndup(iarg->val.str.val, iarg->val.str.len);
				} else {
					zend_string *zs = zval_get_string(iarg->_zv);
					arg_val[i].str.val = estrndup(zs->val, zs->len);
					zend_string_release(zs);
				}
				break;
			case PSI_T_STRLEN:
				if (iarg->type->type == PSI_T_STRING) {
					arg_val[i].lval =iarg->val.str.len;
				} else {
					zend_string *zs = zval_get_string(iarg->_zv);
					arg_val[i].lval = zs->len;
					zend_string_release(zs);
				}
				break;
			}
			arg_ptr[i] = &arg_val[i];
			arg_prm[i] = darg->let->val->is_reference ? &arg_ptr[i] : arg_ptr[i];
			sig_prm[i] = psi_jit_decl_arg_type(darg);
		}
	}

	signature = jit_type_create_signature(
			psi_jit_abi(data->impl->decl->abi->convention),
			psi_jit_decl_arg_type(data->impl->decl->func),
			sig_prm,
			data->impl->decl->args->count,
			1);
	jit_apply(signature, data->impl->decl->dlptr, arg_prm, data->impl->decl->args->count, &ret_val);

	switch (data->impl->stmts->ret.list[0]->func->type) {
	case PSI_T_TO_STRING:
		if (data->impl->decl->func->var->pointer_level) {
			switch (real_decl_type(data->impl->decl->func->type)->type) {
			case PSI_T_CHAR:
			case PSI_T_SINT8:
			case PSI_T_UINT8:
				RETVAL_STRING(ret_val.str.val);
				break;
			}
		}
		break;
	}
}

static zend_function_entry *compile(PSI_Context *C, PSI_Data *D)
{
	size_t i, j = 0;
	jit_type_t signature, params[] = {
		jit_type_void_ptr,
		jit_type_void_ptr
	};
	zend_function_entry *zfe = calloc(D->impls->count + 1, sizeof(*zfe));

	jit_context_build_start(C->opaque);

	for (i = 0; i < D->impls->count; ++i) {
		zend_function_entry *zf;
		PSI_ClosureData *data;

		if (!D->impls->list[i]->decl) {
			continue;
		}

		zf = &zfe[j++];
		data = PSI_ClosureDataAlloc(C, D->impls->list[i]);
		signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 2, 1);
		zf->fname = D->impls->list[i]->func->name + (D->impls->list[i]->func->name[0] == '\\');
		zf->handler = jit_closure_create(C->opaque, signature, &handler, data);
	}

	jit_context_build_end(C->opaque);

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
