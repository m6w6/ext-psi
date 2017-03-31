/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "php_psi_stdinc.h"
#include "context.h"
#include "call.h"
#include "php.h"

#ifdef HAVE_LIBFFI

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
	assert(*closure != NULL);

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

static void psi_ffi_prep_va(ffi_cif *base, ffi_cif *signature, size_t argc, size_t va_count,
		ffi_type **param_types) {
	ffi_status rc;

#ifdef PSI_HAVE_FFI_PREP_CIF_VAR
	rc = ffi_prep_cif_var(signature, base->abi, argc, argc + va_count,
			base->rtype, param_types);
#else
	/* FIXME: test in config.m4; assume we can just call anyway */
	rc = ffi_prep_cif(signature, base->abi, argc + va_count, base->rtype, param_types);
#endif

	assert(FFI_OK == rc);
}

static inline ffi_type *psi_ffi_decl_arg_type(struct psi_decl_arg *darg);

struct psi_ffi_context {
	ffi_cif signature;
	ffi_type *params[2];
};

struct psi_ffi_call {
	struct psi_context *context;
	union {
		struct {
			struct psi_impl *impl;
			struct psi_call_frame *frame;
		} fn;
		struct  {
			struct psi_let_exp *let_exp;
			struct psi_ffi_call *impl_call;
		} cb;
	} impl;
	void *code;
	ffi_closure *closure;
	ffi_cif signature;
	ffi_type *params[1]; /* [type1, type2, ... ] */
};

static void psi_ffi_handler(ffi_cif *sig, void *result, void **args, void *data)
{
	struct psi_ffi_call *call = data;

	psi_context_call(call->context, *(zend_execute_data **)args[0], *(zval **)args[1], call->impl.fn.impl);
}

static void psi_ffi_callback(ffi_cif *sig, void *result, void **args, void *data)
{
	struct psi_ffi_call *call = data, *impl_call = call->impl.cb.impl_call;

	if (impl_call->impl.fn.frame) {
		struct psi_call_frame_callback cbdata;

		cbdata.cb = call->impl.cb.let_exp;
		cbdata.argc = sig->nargs;
		cbdata.argv = args;
		cbdata.rval = result;

		psi_call_frame_do_callback(impl_call->impl.fn.frame, &cbdata);
	} else {
		assert(0);
	}
}

static inline ffi_abi psi_ffi_abi(const char *convention) {
	if (FFI_LAST_ABI - 2 != FFI_FIRST_ABI) {
#ifdef HAVE_FFI_STDCALL
		if (!strcasecmp(convention, "stdcall")) {
			return FFI_STDCALL;
		}
#endif
#ifdef HAVE_FFI_FASTCALL
		if (!strcasecmp(convention, "fastcall")) {
			return FFI_FASTCALL;
		}
#endif
	}
	return FFI_DEFAULT_ABI;
}

static inline struct psi_ffi_call *psi_ffi_call_alloc(struct psi_context *C, struct psi_decl *decl) {
	int rc;
	size_t i, c = psi_plist_count(decl->args);
	struct psi_ffi_call *call = calloc(1, sizeof(*call) + 2 * c * sizeof(void *));
	struct psi_decl_arg *arg;

	decl->info = call;
	call->context = C;

	for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
		call->params[i] = psi_ffi_decl_arg_type(arg);
	}
	call->params[c] = NULL;

	rc = ffi_prep_cif(&call->signature, psi_ffi_abi(decl->abi->convention),
			c, psi_ffi_decl_arg_type(decl->func), call->params);
	assert(FFI_OK == rc);

	return call;
}

static inline ffi_status psi_ffi_call_init_closure(struct psi_context *C, struct psi_ffi_call *call, struct psi_impl *impl) {
	struct psi_ffi_context *context = C->context;

	call->impl.fn.impl = impl;
	return psi_ffi_prep_closure(&call->closure, &call->code, &context->signature, psi_ffi_handler, call);
}

static inline ffi_status psi_ffi_call_init_callback_closure(struct psi_context *C,
		struct psi_ffi_call *call, struct psi_ffi_call *impl_call,
		struct psi_let_exp *cb) {
	call->impl.cb.let_exp = cb;
	call->impl.cb.impl_call = impl_call;
	return psi_ffi_prep_closure(&call->closure, &call->code, &call->signature, psi_ffi_callback, call);
}

static inline void psi_ffi_call_free(struct psi_ffi_call *call) {
	if (call->closure) {
		psi_ffi_closure_free(call->closure);
	}
	free(call);
}

static inline ffi_type *psi_ffi_token_type(token_t t) {
	switch (t) {
	default:
		assert(0);
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

static ffi_type **psi_ffi_struct_type_elements(struct psi_decl_struct *strct) {
	size_t i = 0, argc = psi_plist_count(strct->args), nels = 0, offset = 0, maxalign = 0, last_arg_pos = -1;
	ffi_type **tmp, **els = calloc(argc + 1, sizeof(*els));
	struct psi_decl_arg *darg;

	while (psi_plist_get(strct->args, i++, &darg)) {
		ffi_type *type;
		size_t padding;

		if (darg->layout->pos == last_arg_pos) {
			/* skip bit fields */
			continue;
		}
		last_arg_pos = darg->layout->pos;

		type = malloc(sizeof(*type));
		*type = *psi_ffi_decl_arg_type(darg);

		if (type->alignment > maxalign) {
			maxalign = type->alignment;
		}

		assert(type->size == darg->layout->len);
		if ((padding = psi_offset_padding(darg->layout->pos - offset, type->alignment))) {
			if (nels + padding + 1 > argc) {
				argc += padding;
				tmp = realloc(els, (argc + 1) * sizeof(*els));
				if (tmp) {
					els = tmp;
				} else {
					free(els);
					return NULL;
				}
				els[argc] = NULL;
			}
			psi_ffi_struct_type_pad(&els[nels], padding);
			nels += padding;
			offset += padding;
		}
		assert(offset == darg->layout->pos);

		offset = (offset + darg->layout->len + type->alignment - 1) & ~(type->alignment - 1);
		els[nels++] = type;
	}

	/* apply struct alignment padding */
	offset = (offset + maxalign - 1) & ~(maxalign - 1);

	assert(offset <= strct->size);
	if (offset < strct->size) {
		psi_ffi_struct_type_pad(&els[nels], strct->size - offset);
	}

	return els;
}
static inline ffi_type *psi_ffi_decl_type(struct psi_decl_type *type) {
	struct psi_decl_type *real = psi_decl_type_get_real(type);

	switch (real->type) {
	case PSI_T_STRUCT:
		if (!real->real.strct->engine.type) {
			ffi_type *strct = calloc(1, sizeof(ffi_type));

			strct->type = FFI_TYPE_STRUCT;
			strct->size = 0;
			strct->elements = psi_ffi_struct_type_elements(real->real.strct);

			real->real.strct->engine.type = strct;
			real->real.strct->engine.dtor = psi_ffi_struct_type_dtor;
		}

		return real->real.strct->engine.type;

	case PSI_T_UNION:
		{
			struct psi_decl_arg *arg;
			psi_plist_get(real->real.unn->args, 0, &arg);
			return psi_ffi_decl_arg_type(arg);
		}

	default:
		return psi_ffi_token_type(real->type);
	}
}
static inline ffi_type *psi_ffi_decl_arg_type(struct psi_decl_arg *darg) {
	if (darg->var->pointer_level) {
		return &ffi_type_pointer;
	} else {
		return psi_ffi_decl_type(darg->type);
	}
}


static inline struct psi_ffi_context *psi_ffi_context_init(struct psi_ffi_context *L) {
	ffi_status rc;

	if (!L) {
		L = malloc(sizeof(*L));
	}
	memset(L, 0, sizeof(*L));

	L->params[0] = &ffi_type_pointer;
	L->params[1] = &ffi_type_pointer;
	rc = ffi_prep_cif(&L->signature, FFI_DEFAULT_ABI, 2, &ffi_type_void, L->params);
	assert(rc == FFI_OK);

	return L;
}

static inline void psi_ffi_context_free(struct psi_ffi_context **L) {
	if (*L) {
		free(*L);
		*L = NULL;
	}
}

static void psi_ffi_init(struct psi_context *C)
{
	C->context = psi_ffi_context_init(NULL);
}

static inline void psi_ffi_destroy_callbacks(struct psi_context *C, struct psi_let_exp *let_exp) {
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;

		if (cb->decl && cb->decl->info) {
			psi_ffi_call_free(cb->decl->info);
		}
		fn = cb->func;
		/* no break */
	case PSI_LET_FUNC:
		if (!fn) {
			fn = let_exp->data.func;
		}

		if (fn->inner) {
			size_t i = 0;
			struct psi_let_exp *cb;

			while (psi_plist_get(fn->inner, i++, &cb)) {
				psi_ffi_destroy_callbacks(C, cb);
			}
		}
		break;
	default:
		break;
	}
}

static void psi_ffi_dtor(struct psi_context *C)
{
	if (C->decls) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(C->decls, i++, &decl)) {
			if (decl->info) {
				psi_ffi_call_free(decl->info);
			}
		}

	}
	if (C->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(C->impls, i++, &impl)) {
			size_t j = 0;
			struct psi_let_stmt *let;

			while (psi_plist_get(impl->stmts.let, j++, &let)) {
				psi_ffi_destroy_callbacks(C, let->exp);
			}
		}
	}
	psi_ffi_context_free((void *) &C->context);
}

static inline void psi_ffi_compile_callbacks(struct psi_context *C,
		struct psi_ffi_call *impl_call, struct psi_let_exp *let_exp) {
	struct psi_ffi_call *call;
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;
		if ((call = psi_ffi_call_alloc(C, cb->decl))) {
			if (FFI_OK != psi_ffi_call_init_callback_closure(C, call, impl_call, let_exp)) {
				psi_ffi_call_free(call);
				break;
			}

			cb->decl->sym = call->code;
		}
		fn = cb->func;
		/* no break */
	case PSI_LET_FUNC:
		if (!fn) {
			fn = let_exp->data.func;
		}
		if (fn->inner) {
			size_t i = 0;
			struct psi_let_exp *inner_let;

			while (psi_plist_get(fn->inner, i++, &inner_let)) {
				psi_ffi_compile_callbacks(C, impl_call, inner_let);
			}
		}
		break;
	default:
		break;
	}
}

static zend_function_entry *psi_ffi_compile(struct psi_context *C)
{
	size_t i = 0, d = 0, nf = 0;
	struct psi_impl *impl;
	struct psi_decl *decl;
	zend_function_entry *zfe;

	if (!C->impls) {
		return NULL;
	}

	zfe = calloc(psi_plist_count(C->impls) + 1, sizeof(*zfe));

	while (psi_plist_get(C->impls, i++, &impl)) {
		size_t l = 0;
		struct psi_let_stmt *let;
		struct psi_ffi_call *call;
		zend_function_entry *zf = &zfe[nf];

		if (!impl->decl) {
			continue;
		}
		if (!(call = psi_ffi_call_alloc(C, impl->decl))) {
			continue;
		}
		if (FFI_OK != psi_ffi_call_init_closure(C, call, impl)) {
			psi_ffi_call_free(call);
			continue;
		}

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->handler = call->code;
		zf->num_args = psi_plist_count(impl->func->args);
		zf->arg_info = psi_internal_arginfo(impl);
		++nf;

		while (psi_plist_get(impl->stmts.let, l++, &let)) {
			psi_ffi_compile_callbacks(C, call, let->exp);
		}
	}

	while (psi_plist_get(C->decls, d++, &decl)) {
		if (decl->info) {
			continue;
		}

		psi_ffi_call_alloc(C, decl);
	}

	return zfe;
}

static void psi_ffi_call(struct psi_context *C, struct psi_call_frame *frame, struct psi_decl *decl, void *rval, void **args) {
	struct psi_ffi_call *info = decl->info;
	struct psi_call_frame *prev = info->impl.fn.frame;

	info->impl.fn.frame = frame;
	ffi_call(&info->signature, FFI_FN(decl->sym), rval, args);
	info->impl.fn.frame = prev;
}

static void psi_ffi_call_va(struct psi_context *C, struct psi_call_frame *frame, struct psi_decl *decl, void *rval, void **args,
	size_t va_count, void **va_types) {
	ffi_cif signature;
	struct psi_ffi_call *info = decl->info;
	struct psi_call_frame *prev = info->impl.fn.frame;
	size_t argc = psi_plist_count(decl->args);
	ffi_type **param_types = ecalloc(argc + va_count + 1, sizeof(ffi_type *));

	memcpy(param_types, info->params, argc * sizeof(ffi_type *));
	memcpy(param_types + argc, va_types, va_count * sizeof(ffi_type *));

	psi_ffi_prep_va(&info->signature, &signature, argc, va_count, param_types);
	info->impl.fn.frame = frame;
	ffi_call(&signature, FFI_FN(decl->sym), rval, args);
	info->impl.fn.frame = prev;
	efree(param_types);
}

static void *psi_ffi_query(struct psi_context *C, enum psi_context_query q, void *arg) {
	switch (q) {
	case PSI_CONTEXT_QUERY_SELF:
		return "ffi";
	case PSI_CONTEXT_QUERY_TYPE:
		return psi_ffi_impl_type(*(token_t *) arg);
	}
	return NULL;
}

static struct psi_context_ops ops = {
	psi_ffi_init,
	psi_ffi_dtor,
	psi_ffi_compile,
	psi_ffi_call,
	psi_ffi_call_va,
	psi_ffi_query,
};

struct psi_context_ops *psi_libffi_ops(void)
{
	return &ops;
}

#endif /* HAVE_LIBFFI */
