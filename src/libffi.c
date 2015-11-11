#include "php.h"
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
static inline ffi_type *psi_ffi_type(token_t t) {
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
static inline ffi_type *psi_ffi_decl_type(decl_type *type) {
	return psi_ffi_type(real_decl_type(type)->type);
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
	struct {
		struct PSI_LibffiData **list;
		size_t count;
	} data;
} PSI_LibffiContext;

typedef struct PSI_LibffiData {
	PSI_LibffiContext *context;
	impl *impl;
	zend_internal_arg_info *arginfo;
	void *code;
	ffi_closure *closure;
	ffi_cif signature;
	ffi_type *params[1];
} PSI_LibffiData;

static inline PSI_LibffiData *PSI_LibffiDataAlloc(PSI_LibffiContext *context, impl *impl) {
	ffi_status rc;
	size_t i, c = impl->decl->args ? impl->decl->args->count : 0;
	PSI_LibffiData *data = malloc(sizeof(*data) + c * sizeof(ffi_type *));

	data->context = context;
	data->impl = impl;
	data->arginfo = psi_internal_arginfo(impl);
	for (i = 0; i < c; ++i) {
		data->params[i] = psi_ffi_decl_arg_type(impl->decl->args->args[i]);
	}
	data->params[c] = NULL;

	rc = ffi_prep_cif(
			&data->signature,
			psi_ffi_abi(data->impl->decl->abi->convention),
			c,
			psi_ffi_decl_arg_type(data->impl->decl->func),
			data->params);
	ZEND_ASSERT(FFI_OK == rc);

	data->closure = psi_ffi_closure_alloc(sizeof(ffi_closure), &data->code);
	ZEND_ASSERT(data->closure != NULL);
#if PSI_HAVE_FFI_PREP_CLOSURE_LOC
	rc = ffi_prep_closure_loc(
			data->closure,
			&context->signature,
			psi_ffi_handler,
			data,
			data->code);
	ZEND_ASSERT(FFI_OK == rc);
#elif PSI_HAVE_FFI_PREP_CLOSURE
	rc = ffi_prep_closure(data->code, &context->signature, psi_ffi_handler, data);
	ZEND_ASSERT(FFI_OK == rc);
#else
# error "Neither ffi_prep_closure() nor ffi_prep_closure_loc() available"
#endif

	context->data.list = realloc(context->data.list, ++context->data.count * sizeof(*context->data.list));
	context->data.list[context->data.count-1] = data;

	return data;
}

static inline void PSI_LibffiDataFree(PSI_LibffiData *data) {
	psi_ffi_closure_free(data->closure);
	free(data->arginfo);
	free(data);
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

static inline void PSI_LibffiContextDtor(PSI_LibffiContext *L) {
	size_t i;

	for (i = 0; i < L->data.count; ++i) {
		PSI_LibffiDataFree(L->data.list[i]);
	}
	if (L->data.list) {
		free(L->data.list);
	}
}

static inline void PSI_LibffiContextFree(PSI_LibffiContext **L) {
	if (*L) {
		PSI_LibffiContextDtor(*L);
		free(*L);
		*L = NULL;
	}
}

static void psi_ffi_handler(ffi_cif *_sig, void *_result, void **_args, void *_data)
{
	PSI_LibffiData *data = _data;
	size_t i;
	void **arg_prm = NULL;
	impl_val ret_val;

	if (SUCCESS != psi_parse_args(*(zend_execute_data **)_args[0], data->impl)) {
		return;
	}

	if (data->impl->decl->args) {
		arg_prm = malloc(data->impl->decl->args->count * sizeof(*arg_prm));

		for (i = 0; i < data->impl->decl->args->count; ++i) {
			decl_arg *darg = data->impl->decl->args->args[i];

			arg_prm[i] = psi_do_let(darg);
		}
	}

	ffi_call(&data->signature, FFI_FN(data->impl->decl->dlptr), &ret_val, arg_prm);

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

static void psi_ffi_init(PSI_Context *C)
{
	C->context = PSI_LibffiContextInit(NULL);
}

static void psi_ffi_dtor(PSI_Context *C)
{
	PSI_LibffiContextFree((void *) &C->context);
}

static zend_function_entry *psi_ffi_compile(PSI_Context *C)
{
	size_t i, j = 0;
	zend_function_entry *zfe;
	PSI_LibffiContext *ctx = C->context;

	if (!C->impls) {
		return NULL;
	}

	zfe = calloc(C->impls->count + 1, sizeof(*zfe));
	for (i = 0; i < C->impls->count; ++i) {
		zend_function_entry *zf = &zfe[j];
		PSI_LibffiData *data;

		if (!C->impls->list[i]->decl) {
			continue;
		}

		data = PSI_LibffiDataAlloc(ctx, C->impls->list[i]);
		zf->fname = C->impls->list[i]->func->name + (C->impls->list[i]->func->name[0] == '\\');
		zf->num_args = C->impls->list[i]->func->args->count;
		zf->handler = data->code;
		zf->arg_info = data->arginfo;
		++j;
	}

	return zfe;
}

static PSI_ContextOps ops = {
	psi_ffi_init,
	psi_ffi_dtor,
	psi_ffi_compile,
};

PSI_ContextOps *PSI_Libffi(void)
{
	return &ops;
}
