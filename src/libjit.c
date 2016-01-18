#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#ifdef HAVE_LIBJIT

#include "php_psi.h"
#include "libjit.h"

#include <jit/jit.h>

static void psi_jit_handler(jit_type_t _sig, void *result, void **_args, void *_data);

static inline jit_abi_t psi_jit_abi(const char *convention) {
	return jit_abi_cdecl;
}
static inline jit_type_t psi_jit_token_type(token_t t) {
	switch (t) {
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
	case PSI_T_FLOAT:
		return jit_type_sys_float;
	case PSI_T_DOUBLE:
		return jit_type_sys_double;
	case PSI_T_POINTER:
		return jit_type_void_ptr;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}
static inline jit_type_t psi_jit_impl_type(token_t impl_type) {
	switch (impl_type) {
	case PSI_T_BOOL:
		return jit_type_sbyte;
	case PSI_T_INT:
		return jit_type_long;
	case PSI_T_STRING:
		return jit_type_void_ptr;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		return jit_type_sys_double;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}
static inline jit_type_t psi_jit_decl_type(decl_type *type) {
	return psi_jit_token_type(real_decl_type(type)->type);
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

typedef struct PSI_LibjitCall {
	void *closure;
	jit_type_t signature;
	void *params[1]; /* [type1, type2, NULL, arg1, arg2] ... */
} PSI_LibjitCall;

typedef struct PSI_LibjitData {
	PSI_LibjitContext *context;
	impl *impl;
	zend_internal_arg_info *arginfo;
} PSI_LibjitData;

static inline PSI_LibjitCall *PSI_LibjitCallAlloc(PSI_Context *C, decl *decl) {
	size_t i, c = decl->args ? decl->args->count : 0;
	PSI_LibjitCall *call = calloc(1, sizeof(*call) + 2 * c * sizeof(void *));

	for (i = 0; i < c; ++i) {
		call->params[i] = psi_jit_decl_arg_type(decl->args->args[i]);
	}
	call->params[c] = NULL;

	decl->call.info = call;
	decl->call.rval = decl->func->ptr;
	decl->call.argc = c;
	decl->call.args = (void **) &call->params[c+1];

	call->signature = jit_type_create_signature(
			psi_jit_abi(decl->abi->convention),
			psi_jit_decl_arg_type(decl->func),
			(jit_type_t *) call->params, c, 1);
	return call;
}

static inline void PSI_LibjitCallInitClosure(PSI_Context *C, PSI_LibjitCall *call, impl *impl) {
	PSI_LibjitContext *context = C->context;
	call->closure = jit_closure_create(context->jit, context->signature,
			&psi_jit_handler, impl);
}

static inline void PSI_LibjitCallFree(PSI_LibjitCall *call) {
	jit_type_free(call->signature);
	free(call);
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
	L->signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void,
			params, 2, 1);

	return L;
}

static inline void PSI_LibjitContextDtor(PSI_LibjitContext *L) {
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
	psi_call(*(zend_execute_data **)_args[0], *(zval **)_args[1], _data);
}

static void psi_jit_init(PSI_Context *C)
{
	C->context = PSI_LibjitContextInit(NULL);
}

static void psi_jit_dtor(PSI_Context *C)
{
	if (C->decls) {
		size_t i;

		for (i = 0; i < C->decls->count; ++i) {
			decl *decl = C->decls->list[i];

			PSI_LibjitCallFree(decl->call.info);
		}
	}
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
		PSI_LibjitCall *call;
		impl *impl = C->impls->list[i];

		if (!impl->decl) {
			continue;
		}

		call = PSI_LibjitCallAlloc(C, impl->decl);
		PSI_LibjitCallInitClosure(C, call, impl);

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->num_args = impl->func->args->count;
		zf->handler = call->closure;
		zf->arg_info = psi_internal_arginfo(impl);
		++j;
	}

	for (i = 0; i < C->decls->count; ++i) {
		decl *decl = C->decls->list[i];

		if (decl->impl) {
			continue;
		}

		PSI_LibjitCallAlloc(C, decl);
	}

	jit_context_build_end(ctx->jit);

	return zfe;
}

static void psi_jit_call(PSI_Context *C, decl_callinfo *decl_call, impl_vararg *va) {
	PSI_LibjitCall *call = decl_call->info;

	if (va) {
		jit_type_t signature;
		size_t i, nfixedargs = decl_call->argc, ntotalargs = nfixedargs + va->args->count;
		void **params = calloc(2 * ntotalargs + 2, sizeof(void *));

		for (i = 0; i < nfixedargs; ++i) {
			params[i] = call->params[i];
			params[i + ntotalargs + 1] = call->params[i + nfixedargs + 1];
		}
		for (i = 0; i < va->args->count; ++i) {
			params[nfixedargs + i] = psi_jit_impl_type(va->types[i]);
			params[nfixedargs + i + ntotalargs + 1] = &va->values[i];
		}

		signature = jit_type_create_signature(
				jit_type_get_abi(call->signature),
				jit_type_get_return(call->signature),
				(jit_type_t *) params, ntotalargs, 1);
		ZEND_ASSERT(signature);

		jit_apply(signature, decl_call->sym, &params[ntotalargs + 1],
						nfixedargs, decl_call->rval);
		jit_type_free(signature);
		free(params);
	} else {
		jit_apply(call->signature, decl_call->sym, decl_call->args,
				decl_call->argc, decl_call->rval);
	}
}

static PSI_ContextOps ops = {
	psi_jit_init,
	psi_jit_dtor,
	psi_jit_compile,
	psi_jit_call,
};

PSI_ContextOps *PSI_Libjit(void)
{
	return &ops;
}

#endif /* HAVE_LIBJIT */
