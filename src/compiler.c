#include <stdlib.h>

#include <jit/jit.h>

#include <php.h>
#include <Zend/Zend_API.h>

#include "compiler.h"

PSI_Compiler *PSI_CompilerInit(PSI_Compiler *C, PSI_Validator *V, void *context)
{
	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	PSI_DataExchange((PSI_Data *) C, (PSI_Data *) V);

	C->context = context;

	return C;
}

typedef struct PSI_ClosureData {
	void *context;
	impl *impl;
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

void jit_closure_handler(jit_type_t signature, void *result, void **args, void *user_data)
{
	zend_execute_data *execute_data = args[0];
	zval *return_value = args[1];
	PSI_ClosureData *data = user_data;
	impl_arg *iarg;

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
				iarg->val.lval = atol(iarg->def->text);
			}
			Z_PARAM_LONG(iarg->val.lval);
		} else if (PSI_T_FLOAT == iarg->type->type) {
			if (iarg->def) {
				iarg->val.dval = strtod(iarg->def->text, NULL);
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
		goto nextarg;
	ZEND_PARSE_PARAMETERS_END();
}

zend_function_entry *PSI_CompilerCompile(PSI_Compiler *C)
{
	size_t i, j = 0;
	jit_type_t signature, params[] = {
		jit_type_void_ptr,
		jit_type_void_ptr
	};
	zend_function_entry *zfe = calloc(C->impls->count + 1, sizeof(*zfe));

	for (i = 0; i < C->impls->count; ++i) {
		zend_function_entry *zf;
		PSI_ClosureData *data;

		if (!C->impls->list[i]->decl) {
			continue;
		}
		signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 2, 1);

		zf = &zfe[++j];
		data = PSI_ClosureDataAlloc(C->context, C->impls->list[i]);
		zf->fname = C->impls->list[i]->func->name;
		zf->handler = jit_closure_create(C->context, signature, jit_closure_handler, data);
	}

	return zfe;
}
