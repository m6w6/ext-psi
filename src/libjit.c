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

#if HAVE_INT128
static jit_type_t jit_type_llong;
static jit_type_t jit_type_ullong;
#endif

struct psi_jit_context {
	jit_context_t jit;
	jit_type_t signature;
};

struct psi_jit_callback_info {
	struct psi_jit_impl_info *impl_info;
	struct psi_let_exp *let_exp;

	void *closure;
};

struct psi_jit_decl_info {
	jit_type_t signature;
	struct psi_jit_struct_info *rv_array;
	void *params[1];
};

struct psi_jit_extvar_info {
	struct {
		jit_type_t signature;
		void *closure;
	} get;
	struct {
		jit_type_t signature;
		jit_type_t params[1];
		void *closure;
	} set;
};

struct psi_jit_impl_info {
	struct psi_context *context;
	struct psi_call_frame *frame;

	void *closure;
};

struct psi_jit_struct_info {
	jit_type_t strct;
	struct psi_plist *eles;
};

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
#if HAVE_INT128
	case PSI_T_INT128:
		return jit_type_llong;
	case PSI_T_UINT128:
		return jit_type_ullong;
#endif
	case PSI_T_BOOL:
		return jit_type_sys_bool;
	case PSI_T_ENUM:
		return jit_type_sys_int;
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
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return NULL;
}

static void psi_jit_type_free(jit_type_t *typ_ptr)
{
	jit_type_free(*typ_ptr);
}

static inline jit_abi_t psi_jit_abi(zend_string *convention)
{
	if (zend_string_equals_literal(convention, "stdcall")) {
		return jit_abi_stdcall;
	}
	if (zend_string_equals_literal(convention, "fastcall")) {
		return jit_abi_fastcall;
	}
	return jit_abi_cdecl;
}

static void psi_jit_handler(jit_type_t sig, void *result, void **args, void *data)
{
	struct psi_impl *impl = data;
	struct psi_jit_impl_info *info = impl->info;

	psi_context_call(info->context, *(zend_execute_data **)args[0], *(zval **) args[1], impl);
}

static void psi_jit_callback(jit_type_t sig, void *result, void **args, void *data)
{
	struct psi_jit_callback_info *cb_info = data;
	struct psi_call_frame_callback cb_data;

	assert(cb_info->impl_info->frame);

	cb_data.cb = cb_info->let_exp;
	cb_data.argc = jit_type_num_params(sig);
	cb_data.argv = args;
	cb_data.rval = result;

	psi_call_frame_do_callback(cb_info->impl_info->frame, &cb_data);
}

static bool psi_jit_load(void)
{
#if HAVE_INT128
	jit_type_t ll_fields[2], ull_fields[2];

	ll_fields[0] = ll_fields[1] = jit_type_long;
	jit_type_llong = jit_type_create_struct(ll_fields, 2, 1);

	ull_fields[0] = ull_fields[1] = jit_type_ulong;
	jit_type_ullong = jit_type_create_struct(ull_fields, 2, 1);
#endif
	return true;
}

static void psi_jit_free(void)
{
#if HAVE_INT128
	jit_type_free(jit_type_llong);
	jit_type_free(jit_type_ullong);
#endif
}

static bool psi_jit_init(struct psi_context *C)
{
	struct psi_jit_context *context = pecalloc(1, sizeof(*context), 1);
	jit_type_t params[] = {jit_type_void_ptr, jit_type_void_ptr};

	context->jit = jit_context_create();
	if (!context->jit) {
		pefree(context, 1);
		return false;
	}

	context->signature = jit_type_create_signature(jit_abi_cdecl, jit_type_void,
			params, 2, 1);
	if (!context->signature) {
		jit_context_destroy(context->jit);
		pefree(context, 1);
		return false;
	}

	C->context = context;
	return true;
}

static void psi_jit_dtor(struct psi_context *C)
{
	if (C->context) {
		struct psi_jit_context *context = C->context;

		jit_type_free(context->signature);
		jit_context_destroy(context->jit);

		pefree(C->context, 1);
		C->context = NULL;
	}
}


static bool psi_jit_composite_init(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	struct psi_jit_struct_info *info;

	if (darg->engine.type) {
		return true;
	}

	info = pecalloc(1, sizeof(*info), 1);
	info->eles = psi_plist_init((psi_plist_dtor) psi_jit_type_free);
	info->strct = jit_type_create_struct((jit_type_t *)
			psi_context_composite_type_elements(C, darg, &info->eles),
			psi_plist_count(info->eles), 0);

	darg->engine.info = info;
	darg->engine.type = info->strct;

	return true;
}

static void psi_jit_composite_dtor(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	struct psi_jit_struct_info *info = darg->engine.info;

	if (info) {
		darg->engine.info = NULL;
		darg->engine.type = NULL;

		jit_type_free(info->strct);
		psi_plist_free(info->eles);
		pefree(info, 1);
	}
}

static void psi_jit_extvar_get(jit_type_t sig, void *result, void **args, void *data)
{
	struct psi_decl_extvar *evar = data;

	psi_decl_extvar_get(evar, result);
}

static void psi_jit_extvar_set(jit_type_t sig, void *result, void **args, void *data)
{
	struct psi_decl_extvar *evar = data;

	psi_decl_extvar_set(evar, args[0]);
}

static bool psi_jit_decl_init(struct psi_context *, struct psi_decl *);

static bool psi_jit_extvar_init(struct psi_context *C,
		struct psi_decl_extvar *evar)
{
	struct psi_jit_context *ctx = C->context;
	struct psi_jit_extvar_info *info = pecalloc(1, sizeof(*info), 1);

	evar->info = info;

	psi_jit_decl_init(C, evar->getter);
	psi_jit_decl_init(C, evar->setter);

	jit_context_build_start(ctx->jit);

	info->get.signature = jit_type_create_signature(jit_abi_cdecl,
			psi_context_decl_arg_full_type(C, evar->getter->func), NULL, 0, 1);
	if (!info->get.signature) {
		goto failure;
	}
	info->get.closure = jit_closure_create(ctx->jit, info->get.signature,
			psi_jit_extvar_get, evar);
	if (!info->get.closure) {
		goto failure;
	}

	info->set.params[0] = psi_context_decl_arg_call_type(C, evar->arg);
	info->set.signature = jit_type_create_signature(jit_abi_cdecl,
			psi_context_decl_arg_full_type(C, evar->setter->func),
			info->set.params, 1, 1);
	if (!info->set.signature) {
		goto failure;
	}
	info->set.closure = jit_closure_create(ctx->jit, info->set.signature,
			psi_jit_extvar_set, evar);
	if (!info->set.closure) {
		goto failure;
	}

	evar->getter->sym = info->get.closure;
	evar->setter->sym = info->set.closure;

	jit_context_build_end(ctx->jit);
	return true;
failure: ;
	jit_context_build_end(ctx->jit);
	return false;
}

static void psi_jit_extvar_dtor(struct psi_context *C,
		struct psi_decl_extvar *evar) {
	if (evar->info) {
		pefree(evar->info, 1);
		evar->info = NULL;
	}
}

static bool psi_jit_decl_init(struct psi_context *C, struct psi_decl *decl)
{
	if (!decl->info) {
		struct psi_jit_context *ctx = C->context;
		size_t i, c = psi_plist_count(decl->args);
		struct psi_decl_arg *arg;
		struct psi_jit_decl_info *info = pecalloc(1,
				sizeof(*info) + 2 * c * sizeof(void *), 1);

		decl->info = info;

		jit_context_build_start(ctx->jit);

		for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
			info->params[i] = psi_context_decl_arg_call_type(C, arg);
		}
		info->params[c] = NULL;

		info->signature = jit_type_create_signature(
				psi_jit_abi(decl->abi->convention),
				psi_context_decl_arg_full_type(C, decl->func),
				(jit_type_t *) info->params, c, 1);

		jit_context_build_end(ctx->jit);

		if (!info->signature) {
			pefree(info, 1);
			decl->info = NULL;
			return false;
		}
	}

	return true;
}

static void psi_jit_decl_dtor(struct psi_context *C, struct psi_decl *decl) {
	if (decl->info) {
		struct psi_jit_decl_info *info = decl->info;

		jit_type_free(info->signature);
		pefree(info, 1);
		decl->info = NULL;
	}
}

static bool psi_jit_impl_init(struct psi_context *C,
		struct psi_impl *impl, zif_handler *zh)
{
	struct psi_jit_context *context = C->context;
	struct psi_jit_impl_info *info = calloc(1, sizeof(*info));

	impl->info = info;
	info->context = C;

	info->closure = jit_closure_create(context->jit, context->signature,
			&psi_jit_handler, impl);

	if (!info->closure) {
		goto failure;
	}

	*zh = info->closure;
	return true;

failure: ;
	impl->info = NULL;
	pefree(info, 1);
	return false;
}


static void psi_jit_impl_dtor(struct psi_context *C, struct psi_impl *impl) {
	struct psi_jit_impl_info *info = impl->info;

	if (info) {
		/* The memory for the closure will be reclaimed
		 * when the context is destroyed.
		 */
		pefree(info, 1);
		impl->info = NULL;
	}
}

static bool psi_jit_cb_init(struct psi_context *C,
		struct psi_let_exp *exp, struct psi_impl *impl)
{
	struct psi_jit_context *context = C->context;
	struct psi_jit_callback_info *cb_info;
	struct psi_jit_decl_info *decl_info;

	assert(exp->kind == PSI_LET_CALLBACK);

	if (!psi_jit_decl_init(C, exp->data.callback->decl)) {
		return false;
	}

	cb_info = pecalloc(1, sizeof(*cb_info), 1);
	cb_info->impl_info = impl->info;
	cb_info->let_exp = exp;

	decl_info = exp->data.callback->decl->info;
	cb_info->closure = jit_closure_create(context->jit, decl_info->signature,
			&psi_jit_callback, cb_info);

	if (!cb_info->closure) {
		free(cb_info);
		return false;
	}

	assert(!exp->data.callback->decl->sym);
	exp->data.callback->info = cb_info;
	exp->data.callback->decl->sym = cb_info->closure;

	return true;
}

static void psi_jit_cb_dtor(struct psi_context *C,
		struct psi_let_exp *let_exp, struct psi_impl *impl)
{
	assert(let_exp->kind == PSI_LET_CALLBACK);

	psi_jit_decl_dtor(C, let_exp->data.callback->decl);

	if (let_exp->data.callback->info) {
		struct psi_jit_callback_info *info = let_exp->data.callback->info;

		/* The memory for the closure will be reclaimed
		 * when the context is destroyed.
		 */
		pefree(info, 1);
		let_exp->data.callback->info = NULL;
	}
}

static void psi_jit_call(struct psi_call_frame *frame) {
	struct psi_decl *decl = psi_call_frame_get_decl(frame);
	struct psi_impl *impl = psi_call_frame_get_impl(frame);
	struct psi_jit_decl_info *decl_info = decl->info;
	struct psi_jit_impl_info *impl_info;
	struct psi_call_frame *prev;

	if (impl) {
		impl_info = impl->info;
		prev = impl_info->frame;
		impl_info->frame = frame;
	}
	jit_apply(decl_info->signature, decl->sym,
			psi_call_frame_get_arg_pointers(frame), psi_plist_count(decl->args),
			psi_call_frame_get_rpointer(frame));
	if (impl) {
		impl_info->frame = prev;
	}
}

static void psi_jit_call_va(struct psi_call_frame *frame) {
	jit_type_t signature;
	struct psi_call_frame *prev;
	struct psi_decl *decl = psi_call_frame_get_decl(frame);
	struct psi_impl *impl = psi_call_frame_get_impl(frame);
	struct psi_jit_decl_info *decl_info = decl->info;
	struct psi_jit_impl_info *impl_info;
	size_t i, va_count, argc;
	jit_type_t *param_types;

	argc = psi_plist_count(decl->args);
	va_count = psi_call_frame_num_var_args(frame);
	param_types = ecalloc(argc + va_count + 1, sizeof(jit_type_t));
	memcpy(param_types, decl_info->params, argc * sizeof(jit_type_t));
	for (i = 0; i < va_count; ++i) {
		struct psi_call_frame_argument *frame_arg;

		frame_arg = psi_call_frame_get_var_argument(frame, i);
		param_types[argc + i] = psi_jit_impl_type(frame_arg->va_type);
	}

	signature = jit_type_create_signature(jit_abi_vararg,
			jit_type_get_return(decl_info->signature),
			param_types, argc + va_count, 1);
	assert(signature);

	if (impl) {
		impl_info = impl->info;
		prev = impl_info->frame;
		impl_info->frame = frame;
	}
	jit_apply(signature, decl->sym,
			psi_call_frame_get_arg_pointers(frame), argc,
			psi_call_frame_get_rpointer(frame));
	if (impl) {
		impl_info->frame = prev;
	}

	jit_type_free(signature);

	efree(param_types);
}

static void *psi_jit_typeof_impl(struct psi_context *C, token_t impl_type)
{
	return psi_jit_impl_type(impl_type);
}

static void *psi_jit_typeof_decl(struct psi_context *C, token_t decl_type)
{
	return psi_jit_token_type(decl_type);
}

static void *psi_jit_copyof_type(struct psi_context *C, void *orig_type)
{
	return jit_type_copy(orig_type);
}

static void psi_jit_layoutof_type(struct psi_context *C, void *orig_type,
		struct psi_layout *l)
{
	l->pos = jit_type_get_alignment(orig_type);
	l->len = jit_type_get_size(orig_type);
}

static struct psi_context_ops ops = {
	"libjit",
	psi_jit_load,
	psi_jit_free,
	psi_jit_init,
	psi_jit_dtor,
	psi_jit_composite_init,
	psi_jit_composite_dtor,
	psi_jit_extvar_init,
	psi_jit_extvar_dtor,
	psi_jit_decl_init,
	psi_jit_decl_dtor,
	psi_jit_impl_init,
	psi_jit_impl_dtor,
	psi_jit_cb_init,
	psi_jit_cb_dtor,
	psi_jit_call,
	psi_jit_call_va,
	psi_jit_typeof_impl,
	psi_jit_typeof_decl,
	psi_jit_copyof_type,
	psi_jit_layoutof_type,
};

struct psi_context_ops *psi_libjit_ops(void)
{
	return &ops;
}

#endif /* HAVE_LIBJIT */
