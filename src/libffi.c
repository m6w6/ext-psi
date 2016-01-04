#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#ifdef HAVE_LIBFFI

#include "php_psi.h"
#include "libffi.h"

#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include <ffi.h>

#ifndef PSI_HAVE_FFI_CLOSURE_ALLOC
# if HAVE_UNISTD_H
#  include <unistd.h>
# endif
# if HAVE_SYS_MMAN_H
#  include <sys/mman.h>
#  ifndef MAP_ANONYMOUS
#   define MAP_ANONYMOUS MAP_ANON
#  endif
# endif
#endif

static void *psi_ffi_closure_alloc(size_t s, void **code)
{
#ifdef PSI_HAVE_FFI_CLOSURE_ALLOC
	return ffi_closure_alloc(s, code);
#elif HAVE_MMAP
	*code = mmap(NULL, s, PROT_EXEC|PROT_WRITE|PROT_READ,
			MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (MAP_FAILED == *code) {
		return NULL;
	}
	return *code;
#else
	return NULL;
#endif
}

static void psi_ffi_closure_free(void *c)
{
#ifdef PSI_HAVE_FFI_CLOSURE_ALLOC
	ffi_closure_free(c);
#elif HAVE_MMAP
	munmap(c, sizeof(ffi_closure));
#endif
}

static void psi_ffi_handler(ffi_cif *signature, void *_result, void **_args, void *_data);

static inline ffi_abi psi_ffi_abi(const char *convention) {
	return FFI_DEFAULT_ABI;
}
static inline ffi_type *psi_ffi_token_type(token_t t) {
	switch (t) {
	default:
		ZEND_ASSERT(0);
		/* no break */
	case PSI_T_VOID:
		return &ffi_type_void;
	case PSI_T_INT8:
		return &ffi_type_sint8;
	case PSI_T_UINT8:
		return &ffi_type_uint8;
	case PSI_T_INT16:
		return &ffi_type_sint16;
	case PSI_T_UINT16:
		return &ffi_type_uint16;
	case PSI_T_INT32:
		return &ffi_type_sint32;
	case PSI_T_UINT32:
		return &ffi_type_uint32;
	case PSI_T_INT64:
		return &ffi_type_sint64;
	case PSI_T_UINT64:
		return &ffi_type_uint64;
	case PSI_T_BOOL:
		return &ffi_type_uchar;
	case PSI_T_INT:
		return &ffi_type_sint;
	case PSI_T_FLOAT:
		return &ffi_type_float;
	case PSI_T_DOUBLE:
		return &ffi_type_double;
	}
}
static inline ffi_type *psi_ffi_impl_type(token_t impl_type) {
	switch (impl_type) {
	case PSI_T_BOOL:
		return &ffi_type_sint8;
	case PSI_T_INT:
		return &ffi_type_sint64;
	case PSI_T_STRING:
		return &ffi_type_pointer;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		return &ffi_type_double;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
}
static inline ffi_type *psi_ffi_decl_type(decl_type *type) {
	return psi_ffi_token_type(real_decl_type(type)->type);
}
static inline ffi_type *psi_ffi_decl_arg_type(decl_arg *darg) {
	if (darg->var->pointer_level) {
		return &ffi_type_pointer;
	} else {
		return psi_ffi_decl_type(darg->type);
	}
}

typedef struct PSI_LibffiContext {
	ffi_cif signature;
	ffi_type *params[2];
} PSI_LibffiContext;

typedef struct PSI_LibffiCall {
	void *code;
	ffi_closure *closure;
	ffi_cif signature;
	void *params[1]; /* [type1, type2, NULL, arg1, arg2] ... */
} PSI_LibffiCall;

static inline PSI_LibffiCall *PSI_LibffiCallAlloc(PSI_Context *C, decl *decl) {
	int rc;
	size_t i, c = decl->args ? decl->args->count : 0;
	PSI_LibffiCall *call = calloc(1, sizeof(*call) + 2 * c * sizeof(void *));

	for (i = 0; i < c; ++i) {
		call->params[i] = psi_ffi_decl_arg_type(decl->args->args[i]);
	}
	call->params[c] = NULL;

	decl->call.info = call;
	decl->call.rval = decl->func->ptr;
	decl->call.argc = c;
	decl->call.args = (void **) &call->params[c+1];

	rc = ffi_prep_cif(&call->signature, psi_ffi_abi(decl->abi->convention),
			c, psi_ffi_decl_arg_type(decl->func), (ffi_type **) call->params);
	ZEND_ASSERT(FFI_OK == rc);

	return call;
}

static inline void PSI_LibffiCallInitClosure(PSI_Context *C, PSI_LibffiCall *call, impl *impl) {
	PSI_LibffiContext *context = C->context;
	int rc;

	call->closure = psi_ffi_closure_alloc(sizeof(ffi_closure), &call->code);
	ZEND_ASSERT(call->closure != NULL);

#if PSI_HAVE_FFI_PREP_CLOSURE_LOC
	rc = ffi_prep_closure_loc(
			call->closure,
			&context->signature,
			psi_ffi_handler,
			impl,
			call->code);

#elif PSI_HAVE_FFI_PREP_CLOSURE
	rc = ffi_prep_closure(call->code, &context->signature, psi_ffi_handler, impl);
#else
# error "Neither ffi_prep_closure() nor ffi_prep_closure_loc() available"
#endif
	ZEND_ASSERT(FFI_OK == rc);
}

static inline void PSI_LibffiCallFree(PSI_LibffiCall *call) {
	if (call->closure) {
		psi_ffi_closure_free(call->closure);
	}
	free(call);
}

static inline PSI_LibffiContext *PSI_LibffiContextInit(PSI_LibffiContext *L) {
	ffi_status rc;

	if (!L) {
		L = malloc(sizeof(*L));
	}
	memset(L, 0, sizeof(*L));

	L->params[0] = &ffi_type_pointer;
	L->params[1] = &ffi_type_pointer;
	rc = ffi_prep_cif(&L->signature, FFI_DEFAULT_ABI, 2, &ffi_type_void, L->params);
	ZEND_ASSERT(rc == FFI_OK);

	return L;
}

static void psi_ffi_handler(ffi_cif *_sig, void *_result, void **_args, void *_data)
{
	psi_call(*(zend_execute_data **)_args[0], *(zval **)_args[1], _data);
}

static void psi_ffi_init(PSI_Context *C)
{
	C->context = PSI_LibffiContextInit(NULL);
}

static void psi_ffi_dtor(PSI_Context *C)
{
	if (C->decls) {
		size_t i;

		for (i = 0; i < C->decls->count; ++i) {
			decl *decl = C->decls->list[i];

			if (decl->call.info) {
				PSI_LibffiCallFree(decl->call.info);
			}
		}
	}
	free(C->context);
}

static zend_function_entry *psi_ffi_compile(PSI_Context *C)
{
	size_t i, j = 0;
	zend_function_entry *zfe;

	if (!C->impls) {
		return NULL;
	}

	zfe = calloc(C->impls->count + 1, sizeof(*zfe));
	for (i = 0; i < C->impls->count; ++i) {
		zend_function_entry *zf = &zfe[j];
		PSI_LibffiCall *call;
		impl *impl = C->impls->list[i];

		if (!impl->decl) {
			continue;
		}

		call = PSI_LibffiCallAlloc(C, impl->decl);
		PSI_LibffiCallInitClosure(C, call, impl);

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->num_args = impl->func->args->count;
		zf->handler = call->code;
		zf->arg_info = psi_internal_arginfo(impl);
		++j;
	}

	for (i = 0; i < C->decls->count; ++i) {
		decl *decl = C->decls->list[i];

		if (decl->impl) {
			continue;
		}

		PSI_LibffiCallAlloc(C, decl);
	}

	return zfe;
}

static void psi_ffi_call(PSI_Context *C, decl_callinfo *decl_call, impl_vararg *va) {
	PSI_LibffiCall *call = decl_call->info;

	if (va) {
		ffi_status rc;
		ffi_cif signature;
		size_t i, nfixedargs = decl_call->argc, ntotalargs = nfixedargs + va->args->count;
		void **params = calloc(2 * ntotalargs + 2, sizeof(void *));

		for (i = 0; i < nfixedargs; ++i) {
			params[i] = call->params[i];
			params[i + ntotalargs + 1] = call->params[i + nfixedargs + 1];
		}
		for (i = 0; i < va->args->count; ++i) {
			params[nfixedargs + i] = psi_ffi_impl_type(va->types[i]);
			params[nfixedargs + i + ntotalargs + 1] = &va->values[i];
		}

		rc = ffi_prep_cif_var(&signature, call->signature.abi,
				nfixedargs, ntotalargs,
				call->signature.rtype, (ffi_type **) params);
		ZEND_ASSERT(FFI_OK == rc);
		ffi_call(&signature, FFI_FN(decl_call->sym), decl_call->rval, &params[ntotalargs + 1]);
		free(params);
	} else {
		ffi_call(&call->signature, FFI_FN(decl_call->sym), decl_call->rval, decl_call->args);
	}
}

static PSI_ContextOps ops = {
	psi_ffi_init,
	psi_ffi_dtor,
	psi_ffi_compile,
	psi_ffi_call,
};

PSI_ContextOps *PSI_Libffi(void)
{
	return &ops;
}

#endif /* HAVE_LIBFFI */
