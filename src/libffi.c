#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#ifdef HAVE_LIBFFI

#include "php_psi.h"
#include "libffi.h"
#include "engine.h"

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
# error "Neither ffi_closure_alloc() nor mmap() available"
#endif
}

static ffi_status psi_ffi_prep_closure(ffi_closure **closure, void **code, ffi_cif *sig, void (*handler)(ffi_cif*,void*,void**,void*), void *data) {
	*closure = psi_ffi_closure_alloc(sizeof(ffi_closure), code);
	ZEND_ASSERT(*closure != NULL);

#if PSI_HAVE_FFI_PREP_CLOSURE_LOC
	return ffi_prep_closure_loc(*closure, sig, handler, data, *code);

#elif PSI_HAVE_FFI_PREP_CLOSURE
	return ffi_prep_closure(*code, sig, handler, data);
#else
# error "Neither ffi_prep_closure() nor ffi_prep_closure_loc() is available"
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

static void psi_ffi_handler(ffi_cif *_sig, void *_result, void **_args, void *_data)
{
	psi_call(*(zend_execute_data **)_args[0], *(zval **)_args[1], _data);
}

static void psi_ffi_callback(ffi_cif *_sig, void *_result, void **_args, void *_data)
{
	size_t i;
	unsigned argc = _sig->nargs;
	void **argv = _args;
	let_callback *cb = _data;
	decl *decl_cb = cb->decl;
	impl_arg *iarg = cb->func->var->arg;
	zval return_value, *zargv = calloc(argc, sizeof(*zargv));
	void *result, *to_free = NULL;

	ZEND_ASSERT(argc == cb->decl->args->count);

	/* prepare args for the userland call */
	for (i = 0; i < argc; ++i) {
		cb->decl->args->args[i]->ptr = argv[i];
	}
	for (i = 0; i < cb->args->count; ++i) {
		psi_do_set(&zargv[i], cb->args->vals[i]);
	}
	zend_fcall_info_argp(&iarg->val.zend.cb->fci, cb->args->count, zargv);

	/* callback into userland */
	ZVAL_UNDEF(&return_value);
	iarg->_zv = &return_value;
	zend_fcall_info_call(&iarg->val.zend.cb->fci, &iarg->val.zend.cb->fcc, iarg->_zv, NULL);

	/* marshal return value of the userland call */
	switch (iarg->type->type) {
	case PSI_T_BOOL:	zend_parse_arg_bool(iarg->_zv, &iarg->val.zend.bval, NULL, 0);		break;
	case PSI_T_LONG:	zend_parse_arg_long(iarg->_zv, &iarg->val.zend.lval, NULL, 0, 1);	break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:	zend_parse_arg_double(iarg->_zv, &iarg->val.dval, NULL, 0);			break;
	case PSI_T_STRING:	zend_parse_arg_str(iarg->_zv, &iarg->val.zend.str, 0);				break;
	}
	result = cb->func->handler(_result, decl_cb->func->type, iarg, &to_free);

	if (result != _result) {
		*(void **)_result = result;
	}
}

static inline ffi_type *psi_ffi_decl_arg_type(decl_arg *darg);

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

static inline ffi_abi psi_ffi_abi(const char *convention) {
	return FFI_DEFAULT_ABI;
}

static inline PSI_LibffiCall *PSI_LibffiCallAlloc(PSI_Context *C, decl *decl) {
	int rc;
	size_t i, c = decl->args ? decl->args->count : 0;
	PSI_LibffiCall *call = calloc(1, sizeof(*call) + 2 * c * sizeof(void *));

	for (i = 0; i < c; ++i) {
		call->params[i] = psi_ffi_decl_arg_type(decl->args->args[i]);
	}
	call->params[c] = NULL;

	decl->call.info = call;
	decl->call.rval = &decl->func->ptr;
	decl->call.argc = c;
	decl->call.args = (void **) &call->params[c+1];

	rc = ffi_prep_cif(&call->signature, psi_ffi_abi(decl->abi->convention),
			c, psi_ffi_decl_arg_type(decl->func), (ffi_type **) call->params);
	ZEND_ASSERT(FFI_OK == rc);

	return call;
}

static inline ffi_status PSI_LibffiCallInitClosure(PSI_Context *C, PSI_LibffiCall *call, impl *impl) {
	PSI_LibffiContext *context = C->context;

	return psi_ffi_prep_closure(&call->closure, &call->code, &context->signature, psi_ffi_handler, impl);
}

static inline ffi_status PSI_LibffiCallInitCallbackClosure(PSI_Context *C, PSI_LibffiCall *call, let_callback *cb) {
	return psi_ffi_prep_closure(&call->closure, &call->code, &call->signature, psi_ffi_callback, cb);
}

static inline void PSI_LibffiCallFree(PSI_LibffiCall *call) {
	if (call->closure) {
		psi_ffi_closure_free(call->closure);
	}
	free(call);
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
	case PSI_T_ENUM:
		return &ffi_type_sint;
	case PSI_T_LONG:
		return &ffi_type_slong;
	case PSI_T_FLOAT:
		return &ffi_type_float;
	case PSI_T_DOUBLE:
		return &ffi_type_double;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		return &ffi_type_longdouble;
#endif
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return &ffi_type_pointer;
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
	return NULL;
}
static void psi_ffi_struct_type_dtor(void *type) {
	ffi_type *strct = type;

	if (strct->elements) {
		ffi_type **ptr;

		for (ptr = strct->elements; *ptr; ++ptr) {
			free(*ptr);
		}
		free(strct->elements);
	}
	free(strct);
}

static size_t psi_ffi_struct_type_pad(ffi_type **els, size_t padding) {
	size_t i;

	for (i = 0; i < padding; ++i) {
		ffi_type *pad = malloc(sizeof(*pad));

		memcpy(pad, &ffi_type_schar, sizeof(*pad));
		*els++ = pad;
	}

	return padding;
}

static ffi_type **psi_ffi_struct_type_elements(decl_struct *strct) {
	size_t i, argc = strct->args->count, nels = 0, offset = 0, maxalign = 0;
	ffi_type **els = calloc(argc + 1, sizeof(*els));

	for (i = 0; i < strct->args->count; ++i) {
		decl_arg *darg = strct->args->args[i];
		ffi_type *type = malloc(sizeof(*type));
		size_t padding;

		memcpy(type, psi_ffi_decl_arg_type(darg), sizeof(*type));

		ZEND_ASSERT(type->size == darg->layout->len);

		if (type->alignment > maxalign) {
			maxalign = type->alignment;
		}

		if ((padding = psi_offset_padding(darg->layout->pos - offset, type->alignment))) {
			if (nels + padding + 1 > argc) {
				argc += padding;
				els = realloc(els, (argc + 1) * sizeof(*els));
				els[argc] = NULL;
			}
			psi_ffi_struct_type_pad(&els[nels], padding);
			nels += padding;
			offset += padding;
		}
		ZEND_ASSERT(offset == darg->layout->pos);

		offset = (offset + darg->layout->len + type->alignment - 1) & ~(type->alignment - 1);
		els[nels++] = type;
	}

	/* apply struct alignment padding */
	offset = (offset + maxalign - 1) & ~(maxalign - 1);

	ZEND_ASSERT(offset <= strct->size);
	if (offset < strct->size) {
		psi_ffi_struct_type_pad(&els[nels], strct->size - offset);
	}

	return els;
}
static inline ffi_type *psi_ffi_decl_type(decl_type *type) {
	decl_type *real = real_decl_type(type);

	switch (real->type) {
	case PSI_T_FUNCTION:
		return &ffi_type_pointer;

	case PSI_T_STRUCT:
		if (!real->strct->engine.type) {
			ffi_type *strct = calloc(1, sizeof(ffi_type));

			strct->type = FFI_TYPE_STRUCT;
			strct->size = 0;
			strct->elements = psi_ffi_struct_type_elements(real->strct);

			real->strct->engine.type = strct;
			real->strct->engine.dtor = psi_ffi_struct_type_dtor;
		}

		return real->strct->engine.type;

	case PSI_T_UNION:
		return psi_ffi_decl_arg_type(real->unn->args->args[0]);

	default:
		return psi_ffi_token_type(real->type);
	}
}
static inline ffi_type *psi_ffi_decl_arg_type(decl_arg *darg) {
	if (darg->var->pointer_level) {
		return &ffi_type_pointer;
	} else {
		return psi_ffi_decl_type(darg->type);
	}
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
	size_t c, i, j = 0;
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
		if (FFI_OK != PSI_LibffiCallInitClosure(C, call, impl)) {
			PSI_LibffiCallFree(call);
			continue;
		}

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->num_args = impl->func->args->count;
		zf->handler = call->code;
		zf->arg_info = psi_internal_arginfo(impl);
		++j;

		for (c = 0; c < impl->stmts->let.count; ++c) {
			let_stmt *let = impl->stmts->let.list[c];

			if (let->val->kind == PSI_LET_CALLBACK) {
				let_callback *cb = let->val->data.callback;

				call = PSI_LibffiCallAlloc(C, cb->decl);
				if (FFI_OK != PSI_LibffiCallInitCallbackClosure(C, call, cb)) {
					PSI_LibffiCallFree(call);
					continue;
				}

				cb->decl->call.sym = call->code;
			}
		}
	}

	for (i = 0; i < C->decls->count; ++i) {
		decl *decl = C->decls->list[i];

//		if (decl->impl) {
//			continue;
//		}
		if (decl->call.info) {
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
#ifdef PSI_HAVE_FFI_PREP_CIF_VAR
		rc = ffi_prep_cif_var(&signature, call->signature.abi,
				nfixedargs, ntotalargs,
				call->signature.rtype, (ffi_type **) params);
#else
		/* FIXME: test in config.m4; assume we can just call anyway */
		rc = ffi_prep_cif(&signature, call->signature.abi, ntotalargs,
				call->signature.rtype, (ffi_type **) params);
#endif
		ZEND_ASSERT(FFI_OK == rc);
		ffi_call(&signature, FFI_FN(decl_call->sym), *decl_call->rval, &params[ntotalargs + 1]);
		free(params);
	} else {
		ffi_call(&call->signature, FFI_FN(decl_call->sym), *decl_call->rval, decl_call->args);
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
