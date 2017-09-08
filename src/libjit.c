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
	EMPTY_SWITCH_DEFAULT_CASE()
		;
	}
	return NULL;
}

struct psi_jit_struct_type {
	jit_type_t strct;
	jit_type_t *fields;
};

static void psi_jit_struct_type_dtor(void *ptr)
{
	struct psi_jit_struct_type *type = ptr;
	unsigned i, n = jit_type_num_fields(type->strct);

	for (i = 0; i < n; ++i) {
		jit_type_free(jit_type_get_field(type->strct, i));
	}
	jit_type_free(type->strct);
	free(type->fields);
	free(type);
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
			maxalign = 0, last_arg_pos = -1;
	struct psi_decl_arg *darg;
	jit_type_t *tmp;

	*fields = calloc(argc + 1, sizeof(*fields));

	while (psi_plist_get(strct->args, i++, &darg)) {
		jit_type_t type;
		size_t padding, alignment;

		if (darg->layout->pos == last_arg_pos) {
			/* skip bit fields */
			continue;
		}
		last_arg_pos = darg->layout->pos;

		type = jit_type_copy(psi_jit_decl_arg_type(darg));

		if ((alignment = jit_type_get_alignment(type)) > maxalign) {
			maxalign = alignment;
		}

		assert(jit_type_get_size(type) <= darg->layout->len);
		if ((padding = psi_offset_padding(darg->layout->pos - offset, alignment))) {
			if (nels + padding > argc) {
				argc += padding;
				tmp = realloc(*fields, (argc + 1) * sizeof(*fields));
				if (tmp) {
					*fields = tmp;
				} else {
					free(*fields);
					return 0;
				}
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
			struct psi_jit_struct_type *type = calloc(1, sizeof(*type));

			count = psi_jit_struct_type_elements(real->real.strct, &type->fields);
			type->strct = jit_type_create_struct(type->fields, count, 0);

			real->real.strct->engine.type = type;
			real->real.strct->engine.dtor = psi_jit_struct_type_dtor;
		}

		return ((struct psi_jit_struct_type *) real->real.strct->engine.type)->strct;

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

struct psi_jit_context {
	jit_context_t jit;
	jit_type_t signature;
};

struct psi_jit_impl_info {
	struct psi_context *context;
	struct psi_call_frame *frame;

	void *closure;
};

struct psi_jit_callback_info {
	struct psi_jit_impl_info *impl_info;
	struct psi_let_exp *let_exp;

	void *closure;
};

struct psi_jit_decl_info {
	jit_type_t signature;
	void *params[1];
};

static inline struct psi_jit_decl_info *psi_jit_decl_init(struct psi_decl *decl) {
	if (!decl->info) {
		size_t i, c = psi_plist_count(decl->args);
		struct psi_decl_arg *arg;
		struct psi_jit_decl_info *info = calloc(1, sizeof(*info) + 2 * c * sizeof(void *));

		for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
			info->params[i] = psi_jit_decl_arg_type(arg);
		}
		info->params[c] = NULL;

		info->signature = jit_type_create_signature(
				psi_jit_abi(decl->abi->convention),
				psi_jit_decl_arg_type(decl->func),
				(jit_type_t *) info->params,
				c, 1);

		if (!info->signature) {
			free(info);
		} else {
			decl->info = info;
		}
	}

	return decl->info;
}

static inline void psi_jit_decl_dtor(struct psi_decl *decl) {
	if (decl->info) {
		struct psi_jit_decl_info *info = decl->info;

		jit_type_free(info->signature);
		free(info);
		decl->info = NULL;
	}
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

static inline void psi_jit_callback_init(struct psi_jit_impl_info *impl_info,
		struct psi_let_exp *let_exp)
{
	struct psi_jit_context *context = impl_info->context->context;
	struct psi_jit_callback_info *cb_info;
	struct psi_jit_decl_info *decl_info;
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;
		if (cb->decl->info) {
			decl_info = cb->decl->info;
		} else {
			decl_info = psi_jit_decl_init(cb->decl);
		}

		cb_info = calloc(1, sizeof(*cb_info));
		cb_info->impl_info = impl_info;
		cb_info->let_exp = let_exp;
		cb_info->closure = jit_closure_create(context->jit, decl_info->signature,
				&psi_jit_callback, cb_info);

		if (!cb_info->closure) {
			free(cb_info);
			break;
		}
		cb->info = cb_info;

		assert(!cb->decl->sym);
		cb->decl->sym = cb_info->closure;
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
				psi_jit_callback_init(impl_info, inner_let);
			}
		}
		break;
	default:
		break;
	}
}

static inline void psi_jit_callback_dtor(struct psi_let_exp *let_exp) {
	struct psi_let_callback *cb;
	struct psi_let_func *fn = NULL;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		cb = let_exp->data.callback;

		psi_jit_decl_dtor(cb->decl);

		if (cb->info) {
			struct psi_jit_callback_info *info = cb->info;

			if (info->closure) {
				/* The memory for the closure will be reclaimed when the context is destroyed.
				free(info->closure); */
			}
			free(info);
			cb->info = NULL;
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
				psi_jit_callback_dtor(cb);
			}
		}
		break;
	default:
		break;
	}
}

static inline struct psi_jit_impl_info *psi_jit_impl_init(struct psi_impl * impl,
		struct psi_context *C)
{
	struct psi_jit_context *context = C->context;
	struct psi_jit_impl_info *info = calloc(1, sizeof(*info));
	struct psi_let_stmt *let;
	size_t l = 0;

	info->context = C;
	info->closure = jit_closure_create(context->jit, context->signature,
			&psi_jit_handler, impl);

	if (!info->closure) {
		free(info);
		return NULL;
	}

	while (psi_plist_get(impl->stmts.let, l++, &let)) {
		psi_jit_callback_init(info, let->exp);
	}

	return impl->info = info;
}


static inline void psi_jit_impl_dtor(struct psi_impl *impl) {
	struct psi_jit_impl_info *info = impl->info;
	struct psi_let_stmt *let;
	size_t j = 0;

	while (psi_plist_get(impl->stmts.let, j++, &let)) {
		psi_jit_callback_dtor(let->exp);
	}

	if (info) {
		if (info->closure) {
			/* The memory for the closure will be reclaimed when the context is destroyed.
			free(info->closure); */
		}
		free(info);
		impl->info = NULL;
	}
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

static void psi_jit_dtor(struct psi_context *C)
{
	if (C->decls) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(C->decls, i++, &decl)) {
			psi_jit_decl_dtor(decl);
		}
	}
	if (C->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(C->impls, i++, &impl)) {
			psi_jit_impl_dtor(impl);
		}
	}
	psi_jit_context_free((void *) &C->context);
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

		if (!impl->decl) {
			continue;
		}
		if (!psi_jit_decl_init(impl->decl)) {
			continue;
		}
		if (!psi_jit_impl_init(impl, C)) {
			continue;
		}

		zf->fname = impl->func->name + (impl->func->name[0] == '\\');
		zf->handler = ((struct psi_jit_impl_info *) impl->info)->closure;
		zf->num_args = psi_plist_count(impl->func->args);
		zf->arg_info = psi_internal_arginfo(impl);
		++nf;
	}

	while (psi_plist_get(C->decls, d++, &decl)) {
		if (decl->info) {
			continue;
		}

		psi_jit_decl_init(decl);
	}

	jit_context_build_end(ctx->jit);

	return zfe;
}

static inline void psi_jit_call_ex(struct psi_call_frame *frame) {
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

static inline void psi_jit_call_va(struct psi_call_frame *frame) {
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
			param_types, argc + va_count,
			1);
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

static void psi_jit_call(struct psi_call_frame *frame) {
	if (psi_call_frame_num_var_args(frame)) {
		psi_jit_call_va(frame);
	} else {
		psi_jit_call_ex(frame);
	}
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

static struct psi_context_ops ops = {
	psi_jit_init,
	psi_jit_dtor,
	psi_jit_compile,
	psi_jit_call,
	psi_jit_query
};

struct psi_context_ops *psi_libjit_ops(void)
{
	return &ops;
}

#endif /* HAVE_LIBJIT */
