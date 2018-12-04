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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"

#ifdef HAVE_DIRENT_H
# include <dirent.h>
# define NAMLEN(dirent) strlen ((dirent)->d_name)
#else
# define dirent direct
# define NAMLEN(dirent) ((dirent)->d_namlen)
# ifdef HAVE_SYS_NDIR_H
#  include <sys/ndir.h>
# endif
# ifdef HAVE_SYS_DIR_H
#  include <sys/dir.h>
# endif
# ifdef HAVE_NDIR_H
#  include <ndir.h>
# endif
#endif

#include <unistd.h>
#include <fnmatch.h>

#if PSI_THREADED_PARSER
# include <pthread.h>
#endif

#include "php_scandir.h"
#include "php_psi.h"
#include "calc.h"
#include "call.h"
#include "libjit.h"
#include "libffi.h"

#include "token.h"
#include "parser.h"

PHP_MINIT_FUNCTION(psi_context);
PHP_MINIT_FUNCTION(psi_context)
{
	unsigned flags = 0;
	struct psi_context_ops *ops = NULL;

#ifdef HAVE_LIBJIT
	if (!strcasecmp(PSI_G(engine), "jit")) {
		ops = psi_libjit_ops();
	} else
#endif
#ifdef HAVE_LIBFFI
		ops = psi_libffi_ops();
#endif

	if (!ops) {
		php_error(E_WARNING, "No PSI engine found");
		return FAILURE;
	}

	PSI_G(ops) = ops;
	if (ops->load && !ops->load()) {
		return FAILURE;
	}

	if (psi_check_env("PSI_DEBUG")) {
		flags |= PSI_DEBUG;
	}
	if (psi_check_env("PSI_SILENT")) {
		flags |= PSI_SILENT;
	}

	PSI_G(context) = psi_context_init(NULL, PSI_G(ops), psi_error_wrapper, flags);
	psi_context_build(PSI_G(context), PSI_G(directory));

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(psi_context);
PHP_MSHUTDOWN_FUNCTION(psi_context)
{
	if (psi_check_env("PSI_DUMP")) {
		struct psi_dump dump = {{.hn = stdout}, (psi_dump_cb) fprintf};

		psi_context_dump(&dump, PSI_G(context));
	}

	psi_context_free(&PSI_G(context));

	if (PSI_G(ops)->free) {
		PSI_G(ops)->free();
	}

	return SUCCESS;
}

struct psi_context *psi_context_init(struct psi_context *C, struct psi_context_ops *ops, psi_error_cb error, unsigned flags)
{
	if (!C) {
		C = pemalloc(sizeof(*C), 1);
	}
	memset(C, 0, sizeof(*C));

	psi_data_ctor(PSI_DATA(C), error, flags);
	C->ops = ops;

	if (ops->init && !ops->init(C)) {
		return NULL;
	}

	return C;
}

static bool psi_context_add(struct psi_context *C, struct psi_parser *P)
{
	bool valid;
	struct psi_data *D;
	struct psi_validate_scope scope = {0};

	C->data = safe_perealloc(C->data, (C->count + 1), sizeof(*C->data), 0, 1);
	D = psi_data_exchange(&C->data[C->count++], PSI_DATA(P));

	psi_validate_scope_ctor(&scope);
	scope.cpp = P->preproc;
	valid = psi_validate(&scope, PSI_DATA(C), D);
	psi_validate_scope_dtor(&scope);

	return valid;
}

struct psi_context_build_worker {
#if PSI_THREADED_PARSER
	pthread_t tid;
#endif
	struct psi_parser parser;
	struct psi_parser_input *input;
	char psi_file[PATH_MAX];
};

static struct psi_context_build_worker *psi_context_build_worker_init(
		struct psi_context *C, const char *dir, const char *file)
{
	struct psi_context_build_worker *w = pecalloc(1, sizeof(*w), 1);

	if (PATH_MAX <= slprintf(w->psi_file, PATH_MAX, "%s/%s", dir, file)) {
		C->error(PSI_DATA(C), NULL, PSI_WARNING, "Path to PSI file too long: %s/%s",
			dir, file);
		pefree(w, 1);
		return NULL;
	}
	if (!psi_parser_init(&w->parser, C->error, C->flags)) {
		C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to init PSI parser (%s): %s",
			w->psi_file, strerror(errno));
		pefree(w, 1);
		return NULL;
	}
	return w;
}

#if PSI_THREADED_PARSER
static void *psi_context_build_worker_thread(void *thread_ptr)
{
	struct psi_context_build_worker *thread = thread_ptr;
	psi_parser_parse(&thread->parser, thread->input);
	return NULL;
}

static bool psi_context_build_worker_thread_start(
		struct psi_context_build_worker *w)
{
	unsigned tries = 0;
	int rc;

again: ;
	rc = pthread_create(&w->tid, NULL, psi_context_build_worker_thread, w);

	switch (rc) {
	case 0:
		return true;
	case EAGAIN:
		if (tries++ < 10) {
			goto again;
		}
		/* no break */
	default:
		w->parser.error(PSI_DATA(&w->parser), NULL, PSI_WARNING,
				"Failed to start parser thread: %s", strerror(rc));
		w->tid = 0;
		return false;
	}
}
#endif

static bool psi_context_build_worker_exec(struct psi_context_build_worker *w)
{
	if (!(w->input = psi_parser_open_file(&w->parser, w->psi_file, true))) {
		w->parser.error(PSI_DATA(&w->parser), NULL, PSI_WARNING,
				"Failed to open PSI file (%s): %s", w->psi_file, strerror(errno));
		return false;
	}
#if PSI_THREADED_PARSER
	return psi_context_build_worker_thread_start(w);
#else
	return psi_parser_parse(&w->parser, w->input);
#endif
}

static bool psi_context_build_worker_done(struct psi_context_build_worker *w)
{
#if PSI_THREADED_PARSER
	void *rval = NULL;

	if (!w->tid) {
		return true;
	}

# if HAVE_PTHREAD_TRYJOIN_NP
	if (0 == pthread_tryjoin_np(w->tid, &rval)) {
		w->tid = 0;
		return true;
	}
# else
	if (0 == pthread_join(w->tid, &rval)) {
		w->tid = 0;
		return true;
	}
# endif
	return false;
#else
	return true;
#endif
}

static void psi_context_build_worker_dtor(struct psi_context_build_worker *w)
{
#if PSI_THREADED_PARSER
	if (w->tid) {
		void *rval;
		int rc = pthread_join(w->tid, &rval);

		if (rc) {
			w->parser.error(PSI_DATA(&w->parser), NULL, PSI_WARNING,
					"Failed to finish parser thread: %s", strerror(errno));
		}
	}
#endif
	psi_parser_input_free(&w->input);
	psi_parser_dtor(&w->parser);
}

static void psi_context_build_worker_free(struct psi_context_build_worker **w)
{
	if (*w) {
		psi_context_build_worker_dtor(*w);
		pefree(*w, 1);
		*w = NULL;
	}
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
# define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}

void psi_context_build(struct psi_context *C, const char *paths)
{
	char *sep = NULL, *cpy = strdup(paths), *ptr = cpy;
	struct psi_context_build_worker *worker;
	struct psi_plist *workers = psi_plist_init(
			(psi_plist_dtor) psi_context_build_worker_free);

	do {
		struct dirent **entries = NULL;
		int i, n;

		if ((sep = strchr(ptr, ':'))) {
			*sep = 0;
		}

		n = php_scandir(ptr, &entries, psi_select_dirent, alphasort);

		if (n < 0) {
			char cwd[PATH_MAX];
			C->error(PSI_DATA(C), NULL, PSI_WARNING,
					"Failed to scan PSI directory '%s%s%s': %s",
					*ptr == '/' ? "" : getcwd(cwd, PATH_MAX),
					*ptr != '/' && *ptr != '.' ? "/" : "",
					ptr, strerror(errno));
		} else {
			for (i = 0; i < n; ++i) {
				worker = psi_context_build_worker_init(C, ptr, entries[i]->d_name);
				PSI_DEBUG_PRINT(C, "PSI: init worker(%p) for %s/%s\n",
						worker, ptr, entries[i]->d_name);
				if (worker) {
					workers = psi_plist_add(workers, &worker);
				}
				free(entries[i]);
			}
			free(entries);
		}
		ptr = sep + 1;
	} while (sep);

	free(cpy);

	if (psi_plist_count(workers)) {
		struct psi_plist *running = psi_plist_init(
				(psi_plist_dtor) psi_context_build_worker_free);
		long active = 0;
#ifdef _SC_NPROCESSORS_ONLN
		long pool = sysconf(_SC_NPROCESSORS_ONLN);
#else
		long pool = 4;
#endif

		while (psi_plist_count(workers) && active < pool) {
			if (psi_plist_pop(workers, &worker)) {
				PSI_DEBUG_PRINT(C, "PSI: starting worker %p\n", worker);
				if (psi_context_build_worker_exec(worker)) {
					running = psi_plist_add(running, &worker);
					++active;
				}
			}
		}
		while (active) {
			size_t i = 0;

			while (psi_plist_get(running, i++, &worker)) {
				if (psi_context_build_worker_done(worker)) {
					PSI_DEBUG_PRINT(C, "PSI: collecting worker %p\n", worker);
					psi_context_add(C, &worker->parser);

					psi_plist_del(running, --i, NULL);
					psi_context_build_worker_free(&worker);

					if (psi_plist_pop(workers, &worker)) {
						PSI_DEBUG_PRINT(C, "PSI: starting worker %p\n", worker);
						if (psi_context_build_worker_exec(worker)) {
							running = psi_plist_add(running, &worker);
						}
					} else {
						--active;
					}
				}
			}
		}
		psi_plist_free(running);
	}
	psi_plist_free(workers);

	psi_context_compile(C);
}

#include <ctype.h>
static inline bool prefix_match(zend_string *a, zend_string *b)
{
	size_t i;

	for (i = 0; i < a->len && i < b->len; ++i) {
		if (tolower(a->val[i]) != tolower(b->val[i])) {
			return false;
		}
		if (i && a->val[i] == '_') {
			break;
		}
	}

	return true;
}

static inline void psi_context_consts_init(struct psi_context *C)
{
	zend_constant zc;

	ZEND_CONSTANT_SET_FLAGS(&zc, CONST_CS|CONST_PERSISTENT, EG(current_module)->module_number);

	if (C->consts) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(C->consts, i++, &c)) {

			if (zend_get_constant(c->name)) {
				continue;
			}

			zc.name = zend_string_copy(c->name);
			psi_impl_def_val_get_zval(c->val, c->type ? c->type->type : PSI_T_MIXED, &zc.value);

			zend_register_constant(&zc);
		}
	}
	if (C->enums) {
		size_t i = 0;
		struct psi_decl_enum *e;

		while (psi_plist_get(C->enums, i++, &e)) {
			size_t j = 0;
			struct psi_decl_enum_item *item;

			while (psi_plist_get(e->items, j++, &item)) {
				zend_string *name;

				if (psi_decl_type_is_anon(e->name, "enum")
						|| prefix_match(e->name, item->name)) {
					name = strpprintf(0, "psi\\%s", item->name->val);
				} else {

					name = strpprintf(0, "psi\\%s\\%s", e->name->val, item->name->val);
				}

				if (zend_get_constant(name)) {
					zend_string_release(name);
					continue;
				}

				zc.name = zend_string_dup(name, 1);
				ZVAL_LONG(&zc.value, psi_num_exp_get_long(item->num, NULL, NULL));
				zend_register_constant(&zc);
				zend_string_release(name);
			}
		}
	}
}

static inline void psi_context_extvars_init(struct psi_context *C)
{
	if (C->vars) {
		size_t v = 0;
		struct psi_decl_extvar *evar;

		while (psi_plist_get(C->vars, v++, &evar)) {
			C->ops->extvar_init(C, evar);
		}
	}
}

static inline void psi_context_callback_init(struct psi_context *C,
		struct psi_let_exp *let_exp, struct psi_impl *impl)
{
	struct psi_let_func *fn = let_exp->data.func;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		C->ops->cb_init(C, let_exp, impl);
		/* override fn */
		fn = let_exp->data.callback->func;
		/* no break */
	case PSI_LET_FUNC:
		if (fn->inner) {
			size_t i = 0;
			struct psi_let_exp *inner_let;

			while (psi_plist_get(fn->inner, i++, &inner_let)) {
				psi_context_callback_init(C, inner_let, impl);
			}
		}
		break;
	default:
		break;
	}
}

static inline void psi_context_callback_dtor(struct psi_context *C,
		struct psi_let_exp *let_exp, struct psi_impl *impl)
{
	struct psi_let_func *fn = let_exp->data.func;

	switch (let_exp->kind) {
	case PSI_LET_CALLBACK:
		C->ops->cb_dtor(C, let_exp, impl);
		/* override func */
		fn = let_exp->data.callback->func;
		/* no break */
	case PSI_LET_FUNC:
		if (fn->inner) {
			size_t i = 0;
			struct psi_let_exp *cb;

			while (psi_plist_get(fn->inner, i++, &cb)) {
				psi_context_callback_dtor(C, cb, impl);
			}
		}
		break;
	default:
		break;
	}
}

static inline void psi_context_impls_init(struct psi_context *C)
{
	size_t nf = 0;
	zend_function_entry *zfe = NULL;

	if (C->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		zfe = pecalloc(psi_plist_count(C->impls) + 1, sizeof(*zfe), 1);

		while (psi_plist_get(C->impls, i++, &impl)) {
			zend_function_entry *zf = &zfe[nf];
			struct psi_let_stmt *let;
			size_t l = 0;

			if (!impl->decl) {
				continue;
			}
			if (!C->ops->decl_init(C, impl->decl)) {
				continue;
			}
			if (!C->ops->impl_init(C, impl, &zf->handler)) {
				continue;
			}
			while (psi_plist_get(impl->stmts.let, l++, &let)) {
				psi_context_callback_init(C, let->exp, impl);
			}

			zf->fname = impl->func->name->val + (impl->func->name->val[0] == '\\');
			zf->num_args = psi_plist_count(impl->func->args);
			zf->arg_info = psi_internal_arginfo(impl);
			++nf;
		}
	}

	C->closures = zfe;
}

static inline void psi_context_decls_init(struct psi_context *C)
{
	if (C->decls) {
		size_t d = 0;
		struct psi_decl *decl;

		while (psi_plist_get(C->decls, d++, &decl)) {
			if (!decl->info) {
				C->ops->decl_init(C, decl);
			}
		}
	}
}

struct psi_struct_type_data {
	struct psi_plist *els;
	size_t offset;
	size_t max_align;
};

static inline void psi_struct_type_pad(struct psi_context *C,
		struct psi_struct_type_data *data, size_t padding)
{
	void *ele = C->ops->typeof_decl(C, PSI_T_INT8);

	while (padding--) {
		void *pad = C->ops->copyof_type(C, ele);
		data->els = psi_plist_add(data->els, &pad);
	}
}

static inline void psi_struct_type_element(struct psi_context *C,
		struct psi_struct_type_data *data, struct psi_decl_arg *darg)
{
	void *type, *copy;
	size_t i;
	struct psi_layout type_layout;

	if (darg->layout->pos) {
		assert(data->offset <= darg->layout->pos);
		psi_struct_type_pad(C, data, darg->layout->pos - data->offset);
		data->offset = darg->layout->pos;
	}

	type = psi_context_decl_arg_full_type(C, darg);
	C->ops->layoutof_type(C, type, &type_layout);

	if (type_layout.pos > data->max_align) {
		data->max_align = type_layout.pos;
	}

	assert(type_layout.len <= darg->layout->len);

	for (i = 0; i < (darg->var->array_size ?: 1); ++i) {
		copy = C->ops->copyof_type(C, type);
		data->els = psi_plist_add(data->els, &copy);
	}
	assert(darg->layout->len == type_layout.len * (darg->var->array_size ?: 1));
	data->offset += darg->layout->len;
}

static inline void psi_context_decl_struct_type_elements(struct psi_context *C,
		struct psi_decl_struct *strct, struct psi_plist **els)
{
	size_t i = 0;
	struct psi_decl_arg *darg, *prev = NULL;
	struct psi_struct_type_data data = {0};

	data.els = *els;
	while (psi_plist_get(strct->args, i++, &darg)) {
		if (prev && prev->layout->pos == darg->layout->pos) {
			/* skip bit fields */
			continue;
		}
		psi_struct_type_element(C, &data, darg);
	}

	data.offset = (data.offset + data.max_align - 1) & ~(data.max_align - 1);
	assert(data.offset <= strct->size);
	psi_struct_type_pad(C, &data, strct->size - data.offset);

	*els = data.els;
}

static inline void *psi_context_decl_arg_type(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	struct psi_decl_type *real = psi_decl_type_get_real(darg->type);

	if (real != darg->type && darg->type->real.def->var->pointer_level) {
		return C->ops->typeof_decl(C, PSI_T_POINTER);
	}

	if (real->type == PSI_T_UNION) {
		struct psi_decl_arg *arg;
		psi_plist_get(real->real.unn->args, 0, &arg);
		return psi_context_decl_arg_full_type(C, arg);
	}

	if (real->type == PSI_T_STRUCT) {
		C->ops->composite_init(C, darg);
		return darg->engine.type;
	}

	return C->ops->typeof_decl(C, real->type);
}

void *psi_context_decl_arg_call_type(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	if (darg->var->pointer_level) {
		return C->ops->typeof_decl(C, PSI_T_POINTER);
	}

	return psi_context_decl_arg_type(C, darg);
}

void *psi_context_decl_arg_full_type(struct psi_context *C,
		struct psi_decl_arg *darg)
{
	if (darg->var->array_size) {
		C->ops->composite_init(C, darg);
		return darg->engine.type;
	}
	if (darg->var->pointer_level) {
		return C->ops->typeof_decl(C, PSI_T_POINTER);
	}

	return psi_context_decl_arg_type(C, darg);
}

void **psi_context_composite_type_elements(struct psi_context *C,
		struct psi_decl_arg *darg, struct psi_plist **eles)
{
	struct psi_decl_type *dtype;
	struct psi_decl_arg *tmp;
	void *type, *copy;

	dtype = psi_decl_type_get_real(darg->type);

	switch (dtype->type) {
	case PSI_T_STRUCT:
		psi_context_decl_struct_type_elements(C, dtype->real.strct, eles);
		break;
	case PSI_T_UNION:
		if (psi_plist_bottom(dtype->real.unn->args, &tmp)) {
			type = psi_context_decl_arg_full_type(C, tmp);
			copy = C->ops->copyof_type(C, type);
			*eles = psi_plist_add(*eles, &copy);
		}
		break;
	default:
		type = psi_context_decl_arg_type(C, darg);
		for (size_t i = 0; i < darg->var->array_size; ++i) {
			copy = C->ops->copyof_type(C, type);
			*eles = psi_plist_add(*eles, &copy);
		}
	}

	return psi_plist_eles(*eles);
}

void psi_context_compile(struct psi_context *C)
{
	psi_context_consts_init(C);
	psi_context_extvars_init(C);
	psi_context_impls_init(C);
	psi_context_decls_init(C);

	/* zend_register_functions depends on EG(current_module) pointing into module */
	EG(current_module) = zend_hash_str_find_ptr(&module_registry, "psi", sizeof("psi") - 1);
	if (SUCCESS != zend_register_functions(NULL, C->closures, NULL, MODULE_PERSISTENT)) {
		C->error(PSI_DATA(C), NULL, PSI_WARNING, "Failed to register functions!");
	}
	EG(current_module) = NULL;
}

bool psi_context_call(struct psi_context *C, zend_execute_data *execute_data, zval *return_value, struct psi_impl *impl)
{
	struct psi_call_frame *frame;

	frame = psi_call_frame_init(C, impl->decl, impl);

	if (!psi_call_frame_parse_args(frame, execute_data)) {
		psi_call_frame_free(frame);

		return false;
	}

	psi_call_frame_enter(frame);

	if (!psi_call_frame_do_let(frame)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return false;
	}

	if (!psi_call_frame_do_assert(frame, PSI_ASSERT_PRE)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return false;
	}

	if (psi_call_frame_num_var_args(frame)) {
		C->ops->call_va(frame);
	} else {
		C->ops->call(frame);
	}

	if (!psi_call_frame_do_assert(frame, PSI_ASSERT_POST)) {
		psi_call_frame_do_return(frame, return_value);
		psi_call_frame_free(frame);

		return false;
	}

	psi_call_frame_do_return(frame, return_value);
	psi_call_frame_do_set(frame);
	psi_call_frame_do_free(frame);
	psi_call_frame_free(frame);

	return true;
}


void psi_context_dtor(struct psi_context *C)
{
	size_t i;
	zend_function_entry *zfe;

	if (C->decls) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(C->decls, i++, &decl)) {
			size_t j = 0;
			struct psi_decl_arg *darg;

			while (psi_plist_get(decl->args, j++, &darg)) {
				C->ops->composite_dtor(C, darg);
			}
			C->ops->composite_dtor(C, decl->func);
			C->ops->decl_dtor(C, decl);
		}

	}
	if (C->vars) {
		size_t i = 0;
		struct psi_decl_extvar *evar;

		while (psi_plist_get(C->vars, i++, &evar)) {
			C->ops->composite_dtor(C, evar->getter->func);
			C->ops->composite_dtor(C, evar->arg);
			C->ops->extvar_dtor(C, evar);
		}
	}
	if (C->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(C->impls, i++, &impl)) {
			struct psi_let_stmt *let;
			size_t j = 0;

			while (psi_plist_get(impl->stmts.let, j++, &let)) {
				psi_context_callback_dtor(C, let->exp, impl);
			}

			C->ops->impl_dtor(C, impl);
		}
	}

	if (C->ops->dtor) {
		C->ops->dtor(C);
	}

	psi_data_dtor(PSI_DATA(C));

	if (C->data) {
		for (i = 0; i < C->count; ++i) {
			psi_data_dtor(&C->data[i]);
		}
		free(C->data);
	}

	if (C->closures) {
		for (zfe = C->closures; zfe->fname; ++zfe) {
			pefree((void *) zfe->arg_info, 1);
		}
		pefree(C->closures, 1);
	}
}

void psi_context_free(struct psi_context **C)
{
	if (*C) {
		psi_context_dtor(*C);
		free(*C);
		*C = NULL;
	}
}

void psi_context_dump(struct psi_dump *dump, struct psi_context *C)
{
	PSI_DUMP(dump, "// psi.engine=%s\n// %lu files\n",
			C->ops->name, C->count);

	psi_data_dump(dump, PSI_DATA(C));

#if 0
	if (C->flags & PSI_DEBUG) {
		size_t i;

		for (i = 0; i < C->count; ++i) {
			psi_data_dump(dump, &C->data[i]);
		}
	}
#endif
}
