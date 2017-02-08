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

#ifdef HAVE_LIBJIT

#include <jit/jit.h>

static inline jit_type_t psi_jit_decl_arg_type(struct psi_decl_arg *darg);

static inline jit_abi_t psi_jit_abi(const char *convention)
{
	if (!strcasecmp(convention, "stdcall")) {
		return jit_abi_stdcall;
	}
	if (!strcasecmp(convention, "fastcall")) {
		return jit_abi_fastcall;
	}
	return jit_abi_cdecl;
}
static inline jit_type_t psi_jit_token_type(token_t t)
{
	switch (t) {
	default:
		assert(0);
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
	case PSI_T_ENUM:
		return jit_type_sys_int;
	case PSI_T_LONG:
		return jit_type_sys_long;
	case PSI_T_FLOAT:
		return jit_type_sys_float;
	case PSI_T_DOUBLE:
		return jit_type_sys_double;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		return jit_type_sys_long_double;
#endif
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return jit_type_void_ptr;
	}
}
static inline jit_type_t psi_jit_impl_type(token_t impl_type)
{
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
	EMPTY_SWITCH_DEFAULT_CASE()
		;
	}
	return NULL;
}

static void psi_jit_struct_type_dtor(void *type)
{
	jit_type_t strct = type;

	jit_type_free(strct);
}

static size_t psi_jit_struct_type_pad(jit_type_t *els, size_t padding)
{
	size_t i;

	for (i = 0; i < padding; ++i) {
		*els++ = jit_type_copy(jit_type_sys_char);
	}

	return padding;
}

static unsigned psi_jit_struct_type_elements(struct psi_decl_struct *strct,
		jit_type_t **fields)
{
	size_t i = 0, argc = psi_plist_count(strct->args), nels = 0, offset = 0,
			maxalign;
	struct psi_decl_arg *darg;

	*fields = calloc(argc + 1, sizeof(*fields));

	while (psi_plist_get(strct->args, i++, &darg)) {
		jit_type_t type = jit_type_copy(psi_jit_decl_arg_type(darg));
		size_t padding, alignment;

		if ((alignment = jit_type_get_alignment(type)) > maxalign) {
			maxalign = alignment;
		}

		assert(jit_type_get_size(type) == darg->layout->len);
		if ((padding = psi_offset_padding(darg->layout->pos - offset, alignment))) {
			if (nels + padding > argc) {
				argc += padding;
				*fields = realloc(*fields, (argc + 1) * sizeof(*fields));
			}
			psi_jit_struct_type_pad(&(*fields)[nels], padding);
			nels += padding;
			offset += padding;
		}
		assert(offset == darg->layout->pos);

		offset = (offset + darg->layout->len + alignment - 1)
				& ~(alignment - 1);
		(*fields)[nels++] = type;
	}

	/* apply struct alignment padding */
	offset = (offset + maxalign - 1) & ~(maxalign - 1);

	assert(offset <= strct->size);
	if (offset < strct->size) {
		nels += psi_jit_struct_type_pad(&(*fields)[nels], strct->size - offset);
	}

	return nels;
}
static inline jit_type_t psi_jit_decl_type(struct psi_decl_type *type)
{
	struct psi_decl_type *real = psi_decl_type_get_real(type);

	switch (real->type) {
	case PSI_T_STRUCT:
		if (!real->real.strct->engine.type) {
			unsigned count;
			jit_type_t strct, *fields = NULL;

			count = psi_jit_struct_type_elements(real->real.strct, &fields);
			strct = jit_type_create_struct(fields, count, 0);

			real->real.strct->engine.type = strct;
			real->real.strct->engine.dtor = psi_jit_struct_type_dtor;
		}

		return real->real.strct->engine.type;

	case PSI_T_UNION:
		{
			struct psi_decl_arg *arg;
			psi_plist_get(real->real.unn->args, 0, &arg);
			return psi_jit_decl_arg_type(arg);
		}

	default:
		return psi_jit_token_type(real->type);
	}
}
static inline jit_type_t psi_jit_decl_arg_type(struct psi_decl_arg *darg)
{
	if (darg->var->pointer_level) {
		return jit_type_void_ptr;
	} else {
		return psi_jit_decl_type(darg->type);
	}
}

struct psi_jit_context {
	jit_context_t jit;
	jit_type_t signature;
};

struct psi_jit_call {
	struct psi_context *context;
	union {
		struct {
			struct psi_impl *impl;
			struct psi_call_frame *frame;
		} fn;
		struct {
			struct psi_let_exp *let_exp;
			struct psi_jit_call *impl_call;
		} cb;
	} impl;
	void *closure;
	jit_type_t signature;
	void *params[1]; /* [type1, type2, ... ] */
};

static void psi_jit_handler(jit_type_t sig, void *result, void **args, void *data)
{
	struct psi_jit_call *call = data;

	psi_context_call(call->context, *(zend_execute_data **)args[0], *(zval **) args[1], call->impl.fn.impl);
}

static void psi_jit_callback(jit_type_t sig, void *result, void **args,
		void *data)
{
	struct psi_jit_call *call = data, *impl_call = call->impl.cb.impl_call;
	struct psi_call_frame_callback cbdata;

	cbdata.cb = call->impl.cb.let_exp;
	cbdata.argc = jit_type_num_params(sig);
	cbdata.argv = args;
	cbdata.rval = result;

	psi_call_frame_do_callback(impl_call->impl.fn.frame, &cbdata);
}

static inline struct psi_jit_call *psi_jit_call_alloc(struct psi_context *C,
		struct psi_decl *decl)
{
	size_t i, c = psi_plist_count(decl->args);
	struct psi_jit_call *call = calloc(1, sizeof(*call) + 2 * c * sizeof(void *));
	struct psi_decl_arg *arg;

	decl->info = call;
	call->context = C;
	for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
		call->params[i] = psi_jit_decl_arg_type(arg);
	}
	call->params[c] = NULL;

	call->signature = jit_type_create_signature(
			psi_jit_abi(decl->abi->convention),
			psi_jit_decl_arg_type(decl->func),
			(jit_type_t *) call->params,
			c, 1);
	assert(call->signature);

	return call;
}

static inline void *psi_jit_call_init_closure(struct psi_context *C,
		struct psi_jit_call *call, struct psi_impl *impl)
{
	struct psi_jit_context *context = C->context;

	call->impl.fn.impl = impl;
	return call->closure = jit_closure_create(context->jit, context->signature,
			&psi_jit_handler, call);
}

static inline void *psi_jit_call_init_callback_closure(struct psi_context *C,
		struct psi_jit_call *call, struct psi_jit_call *impl_call,
		struct psi_let_exp *cb)
{
	struct psi_jit_context *context = C->context;

	call->impl.cb.let_exp = cb;
	call->impl.cb.impl_call = impl_call;

	return call->closure = jit_closure_create(context->jit, call->signature,
			&psi_jit_callback, call);
}

static inline void psi_jit_call_free(struct psi_jit_call *call)
{
	jit_type_free(call->signature);
	free(call);
}

static inline struct psi_jit_context *psi_jit_context_init(
		struct psi_jit_context *L)
{
	jit_type_t params[] = {jit_type_void_ptr, jit_type_void_ptr};

	if (!L) {
		L = malloc(sizeof(*L));
	}
	memset(L, 0, sizeof(*L));

	L->jit = jit_context_create();
	L->signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void,
			params, 2, 1);

	return L;
}

static inline void psi_jit_context_dtor(struct psi_jit_context *L)
{
	jit_type_free(L->signature);
	jit_context_destroy(L->jit);
}

static inline void psi_jit_context_free(struct psi_jit_context **L)
{
	if (*L) {
		psi_jit_context_dtor(*L);
		free(*L);
		*L = NULL;
	}
}

static void psi_jit_init(struct psi_context *C)
{
	C->context = psi_jit_context_init(NULL);
}

static inline void psi_jit_destroy_callbacks(struct psi_context *C,
		struct psi_let_exp *let_exp)
{
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;

		if (cb->decl && cb->decl->info) {
			psi_jit_call_free(cb->decl->info);
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
				psi_jit_destroy_callbacks(C, inner_let);
			}
		}
		break;
	default:
		break;
	}
}

static void psi_jit_dtor(struct psi_context *C)
{
	if (C->decls) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(C->decls, i++, &decl)) {
			if (decl->info) {
				psi_jit_call_free(decl->info);
			}
		}
	}
	if (C->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(C->impls, i++, &impl)) {
			size_t l = 0;
			struct psi_let_stmt *let;

			while (psi_plist_get(impl->stmts.let, l++, &let)) {
				psi_jit_destroy_callbacks(C, let->exp);
			}
		}
	}
	psi_jit_context_free((void *) &C->context);
}

static inline void psi_jit_compile_callbacks(struct psi_context *C,
		struct psi_jit_call *impl_call, struct psi_let_exp *let_exp)
{
	struct psi_jit_call *call;
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;
		if ((call = psi_jit_call_alloc(C, cb->decl))) {
			if (!psi_jit_call_init_callback_closure(C, call, impl_call, let_exp)) {
				psi_jit_call_free(call);
				break;
			}

			cb->decl->sym = call->closure;
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
				psi_jit_compile_callbacks(C, impl_call, inner_let);
			}
		}
		break;
	default:
		break;
	}
}

static zend_function_entry *psi_jit_compile(struct psi_context *C)
{
	size_t i = 0, d = 0, nf = 0;
	struct psi_impl *impl;
	struct psi_decl *decl;
	zend_function_entry *zfe;
	struct psi_jit_context *ctx = C->context;

	if (!C->impls) {
		return NULL;
	}

	zfe = calloc(psi_plist_count(C->impls) + 1, sizeof(*zfe));
	jit_context_build_start(ctx->jit);

	while (psi_plist_get(C->impls, i++, &impl)) {
		zend_function_entry *zf = &zfe[nf];
		struct psi_jit_call *call;
		size_t l = 0;
		struct psi_let_stmt *let;

		if (!impl->decl) {
			continue;
		}
		if (!(call = psi_jit_call_alloc(C, impl->decl))) {
			continue;
		}
		if (!psi_jit_call_init_closure(C, call, impl)) {
			psi_jit_call_free(call);
			continue;
		}

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->handler = call->closure;
		zf->num_args = psi_plist_count(impl->func->args);
		zf->arg_info = psi_internal_arginfo(impl);
		++nf;

		while (psi_plist_get(impl->stmts.let, l++, &let)) {
			psi_jit_compile_callbacks(C, call, let->exp);
		}
	}

	while (psi_plist_get(C->decls, d++, &decl)) {
		if (decl->info) {
			continue;
		}

		psi_jit_call_alloc(C, decl);
	}

	jit_context_build_end(ctx->jit);

	return zfe;
}

static void psi_jit_call(struct psi_context *C, struct psi_call_frame *frame,
		struct psi_decl *decl, void *rval, void **args)
{
	struct psi_jit_call *call = decl->info;
	struct psi_call_frame *prev = call->impl.fn.frame;

	call->impl.fn.frame = frame;
	jit_apply(call->signature, decl->sym, args, psi_plist_count(decl->args), rval);
	call->impl.fn.frame = prev;
}

static void psi_jit_call_va(struct psi_context *C, struct psi_call_frame *frame,
		struct psi_decl *decl, void *rval, void **args, size_t va_count,
		void **va_types)
{
	struct psi_jit_call *info = decl->info;
	struct psi_call_frame *prev = info->impl.fn.frame;
	size_t argc = psi_plist_count(decl->args);
	jit_type_t signature;
	jit_type_t *param_types = ecalloc(argc + va_count + 1, sizeof(jit_type_t));

	memcpy(param_types, info->params, argc * sizeof(jit_type_t));
	memcpy(param_types + argc, va_types, va_count * sizeof(jit_type_t));

	signature = jit_type_create_signature(jit_abi_vararg,
			jit_type_get_return(info->signature), param_types, argc + va_count,
			1);
	assert(signature);

	info->impl.fn.frame = frame;
	jit_apply(signature, decl->sym, args, argc, rval);
	info->impl.fn.frame = prev;
	jit_type_free(signature);
	efree(param_types);
}

static void *psi_jit_query(struct psi_context *C, enum psi_context_query q,
		void *arg)
{
	switch (q) {
	case PSI_CONTEXT_QUERY_SELF:
		return "jit";
	case PSI_CONTEXT_QUERY_TYPE:
		return psi_jit_impl_type(*(token_t *) arg);
	}
	return NULL;
}

static struct psi_context_ops ops = {psi_jit_init, psi_jit_dtor,
		psi_jit_compile, psi_jit_call, psi_jit_call_va, psi_jit_query};

struct psi_context_ops *psi_libjit_ops(void)
{
	return &ops;
}

#endif /* HAVE_LIBJIT */
