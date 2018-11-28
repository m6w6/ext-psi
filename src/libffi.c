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

#include "libffi_compat.h"

#if HAVE_INT128
static ffi_type *ffi_type_sint128;
static ffi_type *ffi_type_uint128;
#endif

struct psi_ffi_context {
	ffi_cif signature;
	ffi_type *params[2];
};

struct psi_ffi_callback_info {
	struct psi_ffi_impl_info *impl_info;
	struct psi_let_exp *let_exp;

	void *code;
	ffi_closure *closure;
};

struct psi_ffi_decl_info {
	ffi_cif signature;
	struct psi_ffi_struct_info *rv_array;
	ffi_type *params[1];
};

struct psi_ffi_extvar_info {
	struct {
		ffi_cif signature;
		void *code;
		ffi_closure *closure;
	} get;
	struct {
		ffi_cif signature;
		ffi_type *params[1];
		void *code;
		ffi_closure *closure;
	} set;
};

struct psi_ffi_impl_info {
	struct psi_context *context;
	struct psi_call_frame *frame;

	void *code;
	ffi_closure *closure;
};

struct psi_ffi_struct_info {
	ffi_type strct;
	struct psi_plist *eles;
};

static inline ffi_type *psi_ffi_token_type(token_t t)
{
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
#if HAVE_INT128
	case PSI_T_INT128:
		return ffi_type_sint128;
	case PSI_T_UINT128:
		return ffi_type_uint128;
#endif
	case PSI_T_BOOL:
		return &ffi_type_uchar;
	case PSI_T_ENUM:
		return &ffi_type_sint;
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
static inline ffi_type *psi_ffi_impl_type(token_t impl_type)
{
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

static void psi_ffi_type_free(ffi_type **typ_ptr)
{
	pefree(*typ_ptr, 1);
}

static inline ffi_abi psi_ffi_abi(zend_string *convention) {
	if (FFI_LAST_ABI - 2 != FFI_FIRST_ABI) {
#ifdef HAVE_FFI_STDCALL
		if (zend_string_equals_literal(convention, "stdcall")) {
			return FFI_STDCALL;
		}
#endif
#ifdef HAVE_FFI_FASTCALL
		if (zend_string_equals_literal(convention, "fastcall")) {
			return FFI_FASTCALL;
		}
#endif
	}
	return FFI_DEFAULT_ABI;
}

static void psi_ffi_handler(ffi_cif *sig, void *result, void **args, void *data)
{
	struct psi_impl *impl = data;
	struct psi_ffi_impl_info *info = impl->info;

	psi_context_call(info->context, *(zend_execute_data **)args[0], *(zval **)args[1], impl);
}

static void psi_ffi_callback(ffi_cif *sig, void *result, void **args, void *data)
{
	struct psi_ffi_callback_info *cb_info = data;
	struct psi_call_frame_callback cb_data;

	assert(cb_info->impl_info->frame);

	cb_data.cb = cb_info->let_exp;
	cb_data.argc = sig->nargs;
	cb_data.argv = args;
	cb_data.rval = result;

	psi_call_frame_do_callback(cb_info->impl_info->frame, &cb_data);
}

static bool psi_ffi_load()
{
#if HAVE_INT128
	ffi_type *i128, *u128;

	i128 = pecalloc(1, 3*sizeof(ffi_type), 1);
	i128->type = FFI_TYPE_STRUCT;
	i128->size = 0;
	i128->elements = (ffi_type **) (i128 + 1);
	i128->elements[0] = &ffi_type_sint64;
	i128->elements[1] = &ffi_type_sint64;

	ffi_type_sint128 = i128;

	u128 = pecalloc(1, 3*sizeof(ffi_type), 1);
	u128->type = FFI_TYPE_STRUCT;
	u128->size = 0;
	u128->elements = (ffi_type **) (u128 + 1);
	u128->elements[0] = &ffi_type_uint64;
	u128->elements[1] = &ffi_type_uint64;

	ffi_type_uint128 = u128;
#endif
	return true;
}

static void psi_ffi_free()
{
#if HAVE_INT128
	free(ffi_type_sint128);
	free(ffi_type_uint128);
#endif
}

static bool psi_ffi_init(struct psi_context *C)
{
	ffi_status rc;
	struct psi_ffi_context *context = pecalloc(1, sizeof(*context), 1);
	ffi_abi abi = FFI_DEFAULT_ABI;

#if HAVE_FFI_FASTCALL
	abi = FFI_FASTCALL;
#endif

	context->params[0] = &ffi_type_pointer;
	context->params[1] = &ffi_type_pointer;
	rc = ffi_prep_cif(&context->signature, abi, 2, &ffi_type_void,
			context->params);

	if (FFI_OK != rc) {
		pefree(context, 1);
		return false;
	}

	C->context = context;
	return true;
}

static void psi_ffi_dtor(struct psi_context *C)
{
	if (C->context) {
		pefree(C->context, 1);
		C->context = NULL;
	}
}

static bool psi_ffi_composite_init(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	struct psi_ffi_struct_info *info;

	if (darg->engine.type) {
		return true;
	}

	info = pecalloc(1, sizeof(*info), 1);
	info->eles = psi_plist_init((psi_plist_dtor) psi_ffi_type_free);

	psi_context_composite_type_elements(C, darg, &info->eles);

	/* add terminating NULL; libffi structs do not have an element count */
	{
		void *null_ptr = NULL;
		info->eles = psi_plist_add(info->eles, &null_ptr);
	}

	info->strct.type = FFI_TYPE_STRUCT;
	info->strct.alignment = 0;
	info->strct.size = 0;
	info->strct.elements = (ffi_type **) psi_plist_eles(info->eles);

	darg->engine.info = info;
	darg->engine.type = &info->strct;

	return true;
}

static void psi_ffi_composite_dtor(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	struct psi_ffi_struct_info *info = darg->engine.info;

	if (info) {
		darg->engine.info = NULL;
		darg->engine.type = NULL;

		psi_plist_free(info->eles);
		pefree(info, 1);
	}
}

static void psi_ffi_extvar_get(ffi_cif *sig, void *result, void **args, void *data) {
	struct psi_decl_extvar *evar = data;

	psi_decl_extvar_get(evar, result);
}

static void psi_ffi_extvar_set(ffi_cif *sig, void *result, void **args, void *data) {
	struct psi_decl_extvar *evar = data;

	psi_decl_extvar_set(evar, args[0]);
}

static bool psi_ffi_decl_init(struct psi_context *, struct psi_decl *);

static bool psi_ffi_extvar_init(struct psi_context *C,
		struct psi_decl_extvar *evar)
{
	struct psi_ffi_extvar_info *info = pecalloc(1, sizeof(*info), 1);
	ffi_status rc;

	evar->info = info;

	psi_ffi_decl_init(C, evar->getter);
	psi_ffi_decl_init(C, evar->setter);

	rc = ffi_prep_cif(&info->get.signature, FFI_DEFAULT_ABI, 0,
			psi_context_decl_arg_call_type(C, evar->getter->func), NULL);
	if (FFI_OK != rc) {
		return false;
	}
	rc = psi_ffi_prep_closure(&info->get.closure, &info->get.code,
			&info->get.signature, psi_ffi_extvar_get, evar);
	if (FFI_OK != rc) {
		return false;
	}

	info->set.params[0] = psi_context_decl_arg_call_type(C, evar->arg);
	rc = ffi_prep_cif(&info->set.signature, FFI_DEFAULT_ABI, 1,
			&ffi_type_void, info->set.params);
	if (FFI_OK != rc) {
		return false;
	}
	rc = psi_ffi_prep_closure(&info->set.closure, &info->set.code,
			&info->set.signature, psi_ffi_extvar_set, evar);
	if (FFI_OK != rc) {
		return false;
	}

	evar->getter->sym = info->get.code;
	evar->setter->sym = info->set.code;

	return true;
}

static void psi_ffi_extvar_dtor(struct psi_context *C,
		struct psi_decl_extvar *evar) {
	if (evar->info) {
		pefree(evar->info, 1);
		evar->info = NULL;
	}
}

static bool psi_ffi_decl_init(struct psi_context *C, struct psi_decl *decl)
{
	if (!decl->info) {
		int rc;
		size_t i, c = psi_plist_count(decl->args);
		struct psi_decl_arg *arg;
		struct psi_ffi_decl_info *info = pecalloc(1,
				sizeof(*info) + 2 * c * sizeof(void *), 1);

		decl->info = info;

		for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
			info->params[i] = psi_context_decl_arg_call_type(C, arg);
		}
		info->params[c] = NULL;

		rc = ffi_prep_cif(&info->signature, psi_ffi_abi(decl->abi->convention),
				c, psi_context_decl_arg_call_type(C, decl->func), info->params);

		if (FFI_OK != rc) {
			pefree(info, 1);
			decl->info = NULL;
			return false;
		}
	}

	return true;
}

static void psi_ffi_decl_dtor(struct psi_context *C,
		struct psi_decl *decl)
{
	if (decl->info) {
		pefree(decl->info, 1);
		decl->info = NULL;
	}
}

static bool psi_ffi_impl_init(struct psi_context *C,
		struct psi_impl *impl, zif_handler *zh)
{
	struct psi_ffi_context *context = C->context;
	struct psi_ffi_impl_info *info = pecalloc(1, sizeof(*info), 1);
	ffi_status rc;

	impl->info = info;
	info->context = C;

	rc = psi_ffi_prep_closure(&info->closure, &info->code,
			&context->signature, psi_ffi_handler, impl);

	if (FFI_OK != rc) {
		goto failure;
	}

	*zh = info->code;
	return true;

failure: ;
	impl->info = NULL;
	free(info);
	return false;
}

static void psi_ffi_impl_dtor(struct psi_context *C, struct psi_impl *impl)
{
	struct psi_ffi_impl_info *info = impl->info;

	if (info) {
		if (info->closure) {
			psi_ffi_closure_free(info->closure);
		}
		free(info);
		impl->info = NULL;
	}
}

static bool psi_ffi_cb_init(struct psi_context *C,
		struct psi_let_exp *exp, struct psi_impl *impl)
{
	struct psi_ffi_callback_info *cb_info;
	struct psi_ffi_decl_info *decl_info;
	ffi_status rc;

	assert(exp->kind == PSI_LET_CALLBACK);

	if (!psi_ffi_decl_init(C, exp->data.callback->decl)) {
		return false;
	}

	cb_info = pecalloc(1, sizeof(*cb_info), 1);
	cb_info->impl_info = impl->info;
	cb_info->let_exp = exp;

	decl_info = exp->data.callback->decl->info;
	rc = psi_ffi_prep_closure(&cb_info->closure, &cb_info->code,
			&decl_info->signature, psi_ffi_callback, cb_info);

	if (FFI_OK != rc) {
		free(cb_info);
		return false;
	}

	assert(!exp->data.callback->decl->sym);
	exp->data.callback->info = cb_info;
	exp->data.callback->decl->sym = cb_info->code;

	return true;
}

static void psi_ffi_cb_dtor(struct psi_context *C,
		struct psi_let_exp *let_exp, struct psi_impl *impl)
{
	assert(let_exp->kind == PSI_LET_CALLBACK);

	psi_ffi_decl_dtor(C, let_exp->data.callback->decl);

	if (let_exp->data.callback->info) {
		struct psi_ffi_callback_info *info = let_exp->data.callback->info;

		if (info->closure) {
			psi_ffi_closure_free(info->closure);
		}
		pefree(info, 1);
		let_exp->data.callback->info = NULL;
	}
}

static void psi_ffi_call(struct psi_call_frame *frame) {
	struct psi_decl *decl = psi_call_frame_get_decl(frame);
	struct psi_impl *impl = psi_call_frame_get_impl(frame);
	struct psi_ffi_decl_info *decl_info = decl->info;
	struct psi_ffi_impl_info *impl_info;
	struct psi_call_frame *prev;

	if (impl) {
		impl_info = impl->info;
		prev = impl_info->frame;
		impl_info->frame = frame;
	}
	ffi_call(&decl_info->signature, FFI_FN(decl->sym),
			psi_call_frame_get_rpointer(frame),
			psi_call_frame_get_arg_pointers(frame));
	if (impl) {
		impl_info->frame = prev;
	}
}

static void psi_ffi_call_va(struct psi_call_frame *frame) {
	ffi_cif signature;
	struct psi_call_frame *prev;
	struct psi_decl *decl = psi_call_frame_get_decl(frame);
	struct psi_impl *impl = psi_call_frame_get_impl(frame);
	struct psi_ffi_decl_info *decl_info = decl->info;
	struct psi_ffi_impl_info *impl_info;
	size_t i, va_count, argc;
	ffi_type **param_types;

	argc = psi_plist_count(decl->args);
	va_count = psi_call_frame_num_var_args(frame);
	param_types = ecalloc(argc + va_count + 1, sizeof(ffi_type *));
	memcpy(param_types, decl_info->params, argc * sizeof(ffi_type *));
	for (i = 0; i < va_count; ++i) {
		struct psi_call_frame_argument *frame_arg;

		frame_arg = psi_call_frame_get_var_argument(frame, i);
		param_types[argc + i] = psi_ffi_impl_type(frame_arg->va_type);
	}

	psi_ffi_prep_va(&decl_info->signature, &signature, argc, va_count, param_types);

	if (impl) {
		impl_info = impl->info;
		prev = impl_info->frame;
		impl_info->frame = frame;
	}
	ffi_call(&signature, FFI_FN(decl->sym),
			psi_call_frame_get_rpointer(frame),
			psi_call_frame_get_arg_pointers(frame));
	if (impl) {
		impl_info->frame = prev;
	}

	efree(param_types);
}

static void *psi_ffi_typeof_impl(struct psi_context *C, token_t impl_type)
{
	return psi_ffi_impl_type(impl_type);
}

static void *psi_ffi_typeof_decl(struct psi_context *C, token_t decl_type)
{
	return psi_ffi_token_type(decl_type);
}

static void *psi_ffi_copyof_type(struct psi_context *C, void *orig_type)
{
	ffi_type *type = pemalloc(sizeof(*type), 1);

	*type = *(ffi_type *) orig_type;
	return type;
}

static void psi_ffi_layoutof_type(struct psi_context *C, void *orig_type,
		struct psi_layout *l)
{
	ffi_type *type = orig_type;

	if (!type->size || !type->alignment) {
		ffi_cif tmp;
		ffi_prep_cif(&tmp, FFI_DEFAULT_ABI, 0, type, NULL);
	}

	l->pos = type->alignment;
	l->len = type->size;
}

static struct psi_context_ops ops = {
	"libffi",
	psi_ffi_load,
	psi_ffi_free,
	psi_ffi_init,
	psi_ffi_dtor,
	psi_ffi_composite_init,
	psi_ffi_composite_dtor,
	psi_ffi_extvar_init,
	psi_ffi_extvar_dtor,
	psi_ffi_decl_init,
	psi_ffi_decl_dtor,
	psi_ffi_impl_init,
	psi_ffi_impl_dtor,
	psi_ffi_cb_init,
	psi_ffi_cb_dtor,
	psi_ffi_call,
	psi_ffi_call_va,
	psi_ffi_typeof_impl,
	psi_ffi_typeof_decl,
	psi_ffi_copyof_type,
	psi_ffi_layoutof_type,
};

struct psi_context_ops *psi_libffi_ops(void)
{
	return &ops;
}

#endif /* HAVE_LIBFFI */
