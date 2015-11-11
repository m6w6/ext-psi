#include "php.h"
#include "php_psi.h"
#include "libjit.h"

#include <jit/jit.h>

static void psi_jit_handler(jit_type_t _sig, void *result, void **_args, void *_data);

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
	case PSI_T_INT8:
		return jit_type_sbyte;
	case PSI_T_UINT8:
		return jit_type_ubyte;
	case PSI_T_INT16:
		return jit_type_short;
	case PSI_T_UINT16:
		return jit_type_ushort;
	case PSI_T_INT32:
		return jit_type_int;
	case PSI_T_UINT32:
		return jit_type_uint;
	case PSI_T_INT64:
		return jit_type_long;
	case PSI_T_UINT64:
		return jit_type_ulong;
	case PSI_T_BOOL:
		return jit_type_sys_bool;
	case PSI_T_INT:
		return jit_type_sys_int;
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

typedef struct PSI_LibjitContext {
	jit_context_t jit;
	jit_type_t signature;
	struct {
		struct PSI_LibjitData **list;
		size_t count;
	} data;
} PSI_LibjitContext;

typedef struct PSI_LibjitData {
	PSI_LibjitContext *context;
	impl *impl;
	zend_internal_arg_info *arginfo;
	void *closure;
	jit_type_t signature;
	jit_type_t params[1];
} PSI_LibjitData;

static inline PSI_LibjitData *PSI_LibjitDataAlloc(PSI_LibjitContext *context, impl *impl) {
	size_t i, c = impl->decl->args->count;
	PSI_LibjitData *data = malloc(sizeof(*data) + (c ? c-1 : c) * sizeof(jit_type_t));

	data->context = context;
	data->impl = impl;
	data->arginfo = psi_internal_arginfo(impl);
	for (i = 0; i < c; ++i) {
		data->params[i] = psi_jit_decl_arg_type(impl->decl->args->args[i]);
	}

	data->signature = jit_type_create_signature(
		psi_jit_abi(data->impl->decl->abi->convention),
		psi_jit_decl_arg_type(data->impl->decl->func),
		data->params,
		data->impl->decl->args->count,
		1);
	data->closure = jit_closure_create(context->jit, context->signature, &psi_jit_handler, data);

	context->data.list = realloc(context->data.list, ++context->data.count * sizeof(*context->data.list));
	context->data.list[context->data.count-1] = data;

	return data;
}

static inline void PSI_LibjitDataFree(PSI_LibjitData *data) {
	free(data->arginfo);
	jit_type_free(data->signature);
	free(data);
}

static inline PSI_LibjitContext *PSI_LibjitContextInit(PSI_LibjitContext *L) {
	jit_type_t params[] = {
		jit_type_void_ptr,
		jit_type_void_ptr
	};

	if (!L) {
		L = malloc(sizeof(*L));
	}
	memset(L, 0, sizeof(*L));

	L->jit = jit_context_create();
	L->signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void, params, 2, 1);

	return L;
}

static inline void PSI_LibjitContextDtor(PSI_LibjitContext *L) {
	size_t i;

	for (i = 0; i < L->data.count; ++i) {
		PSI_LibjitDataFree(L->data.list[i]);
	}
	if (L->data.list) {
		free(L->data.list);
	}
	jit_type_free(L->signature);
	jit_context_destroy(L->jit);
}

static inline void PSI_LibjitContextFree(PSI_LibjitContext **L) {
	if (*L) {
		PSI_LibjitContextDtor(*L);
		free(*L);
		*L = NULL;
	}
}

static void psi_jit_handler(jit_type_t _sig, void *result, void **_args, void *_data)
{
	PSI_LibjitData *data = _data;
	size_t i;
	void **arg_prm = NULL;
	impl_val ret_val;

	if (SUCCESS != psi_parse_args(*(zend_execute_data **)_args[0], data->impl)) {
		return;
	}

	if (data->impl->decl->args->count) {
		arg_prm = malloc(data->impl->decl->args->count * sizeof(*arg_prm));

		for (i = 0; i < data->impl->decl->args->count; ++i) {
			decl_arg *darg = data->impl->decl->args->args[i];

			arg_prm[i] = psi_do_let(darg);
		}
	}

	jit_apply(data->signature, data->impl->decl->dlptr, arg_prm, data->impl->decl->args->count, &ret_val);

	psi_do_return(*(zval **)_args[1], data->impl->stmts->ret.list[0], &ret_val);

	for (i = 0; i < data->impl->stmts->set.count; ++i) {
		set_stmt *set = data->impl->stmts->set.list[i];

		if (set->arg->_zv) {
			psi_do_set(set->arg->_zv, set->val);
		}
	}

	for (i = 0; i < data->impl->stmts->fre.count; ++i) {
		free_stmt *fre = data->impl->stmts->fre.list[i];

		psi_do_free(fre);
	}

	psi_do_clean(data->impl);

	if (arg_prm) {
		free(arg_prm);
	}
}

static void psi_jit_init(PSI_Context *C)
{
	C->context = PSI_LibjitContextInit(NULL);
}

static void psi_jit_dtor(PSI_Context *C)
{
	PSI_LibjitContextFree((void *) &C->context);
}

static zend_function_entry *psi_jit_compile(PSI_Context *C)
{
	size_t i, j = 0;
	zend_function_entry *zfe;
	PSI_LibjitContext *ctx = C->context;

	if (!C->impls) {
		return NULL;
	}

	zfe = calloc(C->impls->count + 1, sizeof(*zfe));
	jit_context_build_start(ctx->jit);

	for (i = 0; i < C->impls->count; ++i) {
		zend_function_entry *zf = &zfe[j];
		PSI_LibjitData *data;

		if (!C->impls->list[i]->decl) {
			continue;
		}

		data = PSI_LibjitDataAlloc(ctx, C->impls->list[i]);
		zf->fname = C->impls->list[i]->func->name + (C->impls->list[i]->func->name[0] == '\\');
		zf->num_args = C->impls->list[i]->func->args->count;
		zf->handler = data->closure;
		zf->arg_info = data->arginfo;
		++j;
	}

	jit_context_build_end(ctx->jit);

	return zfe;
}

static PSI_ContextOps ops = {
	psi_jit_init,
	psi_jit_dtor,
	psi_jit_compile,
};

PSI_ContextOps *PSI_Libjit(void)
{
	return &ops;
}
