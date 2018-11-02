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
#include "data.h"
#include "call.h"

#include "php.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

struct psi_call_frame_argument *psi_call_frame_argument_init(struct psi_impl_arg *spec,
		impl_val *ival, zval *zptr, int is_vararg) {
	struct psi_call_frame_argument *frame_arg = ecalloc(1, sizeof(*frame_arg));


	if ((frame_arg->zval_ptr = zptr)) {
		ZVAL_DEREF(frame_arg->zval_ptr);

		/* use userland type if the declared type of the vararg is mixed */
		if (is_vararg) {
			if (spec->type->type == PSI_T_MIXED) {
				switch (Z_TYPE_P(zptr)) {
				case IS_TRUE:
					frame_arg->va_type = PSI_T_BOOL;
					ival->zend.bval = 1;
					break;
				case IS_FALSE:
					frame_arg->va_type = PSI_T_BOOL;
					ival->zend.bval = 0;
					break;
				case IS_LONG:
					frame_arg->va_type = PSI_T_INT;
					ival->zend.lval = Z_LVAL_P(zptr);
					break;
				case IS_DOUBLE:
					frame_arg->va_type = PSI_T_FLOAT;
					ival->dval = Z_DVAL_P(zptr);
					break;
				default:
					frame_arg->va_type = PSI_T_STRING;
					ival->zend.str = zval_get_string(zptr);
					break;
				}
			} else {
				frame_arg->va_type = spec->type->type;
			}
		}
	}

	frame_arg->ival = *ival;
	frame_arg->ival_ptr = &frame_arg->ival;
	frame_arg->spec = spec;

	return frame_arg;
}

void psi_call_frame_argument_free(struct psi_call_frame_argument *arg) {
	switch (arg->spec->type->type) {
	case PSI_T_STRING:
		if (arg->ival.zend.str) {
			zend_string_release(arg->ival.zend.str);
		}
		break;
	case PSI_T_CALLABLE:
		if (arg->ival.zend.cb) {
			if (arg->ival.zend.cb->fci.size) {
				zend_fcall_info_args_clear(&arg->ival.zend.cb->fci, 1);
			}
			efree(arg->ival.zend.cb);
		}
		break;
	default:
		break;
	}
	if (arg->ival_ptr && arg->ival_ptr != &arg->temp_val && arg->ival_ptr != &arg->ival) {
		efree(arg->ival_ptr);
	}
	efree(arg);
}

struct psi_call_frame_symbol *psi_call_frame_symbol_init(struct psi_decl_var *dvar) {
	struct psi_call_frame_symbol *frame_sym;
	size_t size = psi_decl_type_get_size(dvar->arg->type, NULL);

	frame_sym = ecalloc(1, sizeof(*frame_sym) + size);
	frame_sym->ptr = frame_sym->ival_ptr = &frame_sym->temp_val;

	return frame_sym;
}

void psi_call_frame_symbol_free(struct psi_call_frame_symbol *sym) {
	efree(sym);
}

static void psi_call_frame_free_argument(zval *zptr) {
	psi_call_frame_argument_free(Z_PTR_P(zptr));
}

static void psi_call_frame_free_symbol(zval *zptr) {
	psi_call_frame_symbol_free(Z_PTR_P(zptr));
}

struct psi_call_frame_auto_free {
	void *data;
	void (*dtor)(void *);
};

static void psi_call_frame_free_temp(void *ptr) {
	struct psi_call_frame_auto_free *f = ptr;

	if (f->data) {
		if (f->dtor) {
			f->dtor(&f->data);
		} else {
			efree(f->data);
		}
	}
}

struct psi_call_frame *psi_call_frame_init(struct psi_context *C, struct psi_decl *decl, struct psi_impl *impl) {
	struct psi_call_frame *frame = ecalloc(1, sizeof(*frame));

	frame->context = C;
	frame->decl = decl;
	frame->impl = impl;

	zend_hash_init(&frame->arguments, 8, NULL, psi_call_frame_free_argument, 0);
	zend_hash_init(&frame->symbols, 8, NULL, psi_call_frame_free_symbol, 0);
	zend_llist_init(&frame->temp, sizeof(struct psi_call_frame_auto_free), psi_call_frame_free_temp, 0);

	return frame;
}

struct psi_call_frame_symbol *psi_call_frame_fetch_symbol(
		struct psi_call_frame *frame, struct psi_decl_var *dvar) {
	struct psi_call_frame_symbol *frame_sym;

	frame_sym = zend_hash_find_ptr(&frame->symbols, dvar->fqn);
	if (!frame_sym) {
		frame_sym = zend_hash_add_ptr(&frame->symbols, dvar->fqn,
				psi_call_frame_symbol_init(dvar));
	}
	return frame_sym;
}

zval *psi_call_frame_new_argument(struct psi_call_frame *frame,
		struct psi_call_frame_argument *frame_arg) {
	if (frame_arg->va_type) {
		/* varargs are just appended with numeric indices */
		return zend_hash_next_index_insert_ptr(&frame->arguments, frame_arg);
	} else {
		return zend_hash_add_ptr(&frame->arguments,
				frame_arg->spec->var->name, frame_arg);
	}
}

zval *psi_call_frame_sub_argument(struct psi_call_frame *frame,
		struct psi_impl_var *inner_var, zval *outer_zval, zend_string *name) {
	struct psi_call_frame_argument *iarg;
	zval *inner_zval = zend_symtable_str_find(Z_ARRVAL_P(outer_zval),
			&inner_var->name->val[1], inner_var->name->len - 1);

	if (!inner_zval) {
		zval empty_zval;

		SEPARATE_ZVAL(outer_zval);
		ZVAL_NULL(&empty_zval);
		inner_zval = zend_symtable_str_update(Z_ARRVAL_P(outer_zval),
				&inner_var->name->val[1], inner_var->name->len - 1,
				&empty_zval);
	}

	iarg = psi_call_frame_get_argument(frame, name);

	if (!iarg) {
		struct psi_call_frame_argument *frame_arg;
		impl_val empty_val = {0};
		zend_string *type_str = zend_string_init_interned(ZEND_STRL("mixed"), 1);
		struct psi_impl_arg *carg_spec = psi_impl_arg_init(
				psi_impl_type_init(PSI_T_MIXED, type_str),
				psi_impl_var_copy(inner_var), NULL);

		psi_call_frame_push_auto_ex(frame, carg_spec, (void(*)(void*)) psi_impl_arg_free);
		frame_arg = psi_call_frame_argument_init(carg_spec, &empty_val, inner_zval, 0);
		zend_hash_add_ptr(&frame->arguments, name, frame_arg);
		zend_string_release(type_str);
	}

	return inner_zval;
}

struct psi_call_frame_argument *psi_call_frame_get_argument(
		struct psi_call_frame *frame, zend_string *name) {
	return zend_hash_find_ptr(&frame->arguments, name);
}

size_t psi_call_frame_num_var_args(struct psi_call_frame *frame) {
	return zend_hash_next_free_element(&frame->arguments);
}

size_t psi_call_frame_num_fixed_args(struct psi_call_frame *frame) {
	return psi_plist_count(frame->decl->args);
}

struct psi_call_frame_argument *psi_call_frame_get_var_argument(
		struct psi_call_frame *frame, zend_long index) {
	return zend_hash_index_find_ptr(&frame->arguments, index);
}

void **psi_call_frame_get_arg_pointers(struct psi_call_frame *frame) {
	return frame->pointers;
}

void *psi_call_frame_get_rpointer(struct psi_call_frame *frame) {
	return frame->rpointer;
}

struct psi_decl *psi_call_frame_get_decl(struct psi_call_frame *frame) {
	return frame->decl;
}

struct psi_impl *psi_call_frame_get_impl(struct psi_call_frame *frame) {
	return frame->impl;
}

struct psi_context *psi_call_frame_get_context(struct psi_call_frame *frame) {
	return frame->context;
}

#if PHP_VERSION_ID < 70300
#	define PARAM_PROLOGUE(separate) Z_PARAM_PROLOGUE(separate)
#else
#	define PARAM_PROLOGUE(separate) Z_PARAM_PROLOGUE(1, separate)
#endif
ZEND_RESULT_CODE psi_call_frame_parse_args(struct psi_call_frame *frame,
		zend_execute_data *execute_data) {
	size_t i, argc = psi_plist_count(frame->impl->func->args);
	zend_error_handling zeh;

	zend_replace_error_handling(EH_THROW, zend_exception_get_default(), &zeh);

	if (!argc) {
		ZEND_RESULT_CODE rv;

		rv = zend_parse_parameters_none();
		zend_restore_error_handling(&zeh);
		return rv;
	}

	ZEND_PARSE_PARAMETERS_START(
			psi_impl_num_min_args(frame->impl),
			frame->impl->func->vararg ? -1 : argc
	)
	nextarg: {

		struct psi_impl_arg *iarg;
		impl_val ival = {0};

		if (frame->impl->func->vararg && _i >= argc) {
			iarg = frame->impl->func->vararg;
			Z_PARAM_OPTIONAL;
		} else {
			psi_plist_get(frame->impl->func->args, _i, &iarg);
			if (iarg->def) {
				Z_PARAM_OPTIONAL;
			}
		}

		if (PSI_T_BOOL == iarg->type->type) {
			Z_PARAM_BOOL(ival.zend.bval);
		} else if (PSI_T_INT == iarg->type->type) {
			Z_PARAM_LONG(ival.zend.lval);
		} else if (PSI_T_FLOAT == iarg->type->type || PSI_T_DOUBLE == iarg->type->type) {
			Z_PARAM_DOUBLE(ival.dval);
		} else if (PSI_T_STRING == iarg->type->type) {
			Z_PARAM_STR_EX(ival.zend.str, 1, iarg->var->reference);
			if (ival.zend.str) {
				zend_string_addref(ival.zend.str);
			}
		} else if (PSI_T_ARRAY == iarg->type->type) {
			zval *tmp;
			Z_PARAM_ARRAY_EX(tmp, _optional || iarg->var->reference,
					iarg->var->reference);
		} else if (PSI_T_OBJECT == iarg->type->type) {
			PARAM_PROLOGUE(iarg->var->reference);
		} else if (PSI_T_MIXED == iarg->type->type) {
			PARAM_PROLOGUE(iarg->var->reference);
		} else if (PSI_T_CALLABLE == iarg->type->type) {
			zend_fcall_info fci;
			zend_fcall_info_cache fcc;

			Z_PARAM_FUNC_EX(fci, fcc, 1, 0);

			if (fci.size) {
				ival.zend.cb = ecalloc(1, sizeof(zend_fcall));
				ival.zend.cb->fci = fci;
				ival.zend.cb->fcc = fcc;
			}
		} else {
			error_code = ZPP_ERROR_FAILURE;
			break;
		}

		psi_call_frame_new_argument(frame,
				psi_call_frame_argument_init(iarg, &ival, _arg, _i > argc));

		if (_i < _num_args) {
			goto nextarg;
		}
	}
	ZEND_PARSE_PARAMETERS_END_EX(
		zend_restore_error_handling(&zeh);
		return FAILURE;
	);

	/* set up defaults */
	for (i = EX_NUM_ARGS(); i < argc; ++i) {
		struct psi_impl_arg *iarg;

		psi_plist_get(frame->impl->func->args, i, &iarg);

		assert(iarg->def);
		psi_call_frame_new_argument(frame, psi_call_frame_argument_init(iarg,
				&iarg->def->ival, NULL, 0));
	}

	zend_restore_error_handling(&zeh);
	return SUCCESS;
}

void psi_call_frame_enter(struct psi_call_frame *frame) {
	size_t argc = psi_call_frame_num_fixed_args(frame);
	size_t va_count = psi_call_frame_num_var_args(frame);
	size_t rsize = psi_decl_arg_get_size(frame->decl->func);
	struct psi_call_frame_symbol *rv_sym;

	/* initialize ffi argument array */
	frame->pointers = ecalloc(argc + va_count + 1, sizeof(void *));

	/* initialize return value symbol */
	rv_sym = psi_call_frame_fetch_symbol(frame, frame->decl->func->var);
	if (rsize > sizeof(impl_val)) {
		rv_sym->ival_ptr = ecalloc(1, rsize);
	} else {
		rv_sym->ival_ptr = &rv_sym->temp_val;
	}
	frame->rpointer = rv_sym->ptr = rv_sym->ival_ptr;
}

ZEND_RESULT_CODE psi_call_frame_do_let(struct psi_call_frame *frame) {
	size_t i;
	struct psi_let_stmt *let;
	struct psi_decl_arg *arg;
	size_t argc = psi_call_frame_num_fixed_args(frame);
	size_t va_count = psi_call_frame_num_var_args(frame);

	for (i = 0; psi_plist_get(frame->impl->stmts.let, i, &let); ++i) {
		psi_let_stmt_exec(let, frame);
	}
	for (i = 0; psi_plist_get(frame->decl->args, i, &arg); ++i) {
		struct psi_let_stmt *let;
		struct psi_call_frame_symbol *frame_sym;

		let = psi_impl_get_let(frame->impl, arg->var);
		frame_sym = psi_call_frame_fetch_symbol(frame, let->exp->var);
		frame->pointers[i] = frame_sym->ptr;
	}
	/* varargs */
	if (va_count) {
		for (i = 0; i < va_count; ++i) {
			struct psi_call_frame_argument *frame_arg;
			psi_marshal_let let_fn;
			void *temp = NULL;

			frame_arg = psi_call_frame_get_var_argument(frame, i);
			switch (frame_arg->va_type) {
			case PSI_T_BOOL:	let_fn = psi_let_boolval;	break;
			case PSI_T_INT:		let_fn = psi_let_intval;	break;
			case PSI_T_FLOAT:
			case PSI_T_DOUBLE:	let_fn = psi_let_floatval;	break;
			case PSI_T_STRING:	let_fn = psi_let_strval;	break;
			default:
				assert(0);
			}

			frame_arg->ival_ptr = let_fn(&frame_arg->temp_val, NULL, frame_arg->va_type,
					&frame_arg->ival, frame_arg->zval_ptr, &temp);
			if (temp) {
				psi_call_frame_push_auto(frame, temp);
			}

			frame->pointers[argc + i] = frame_arg->ival_ptr;
		}
	}

	return SUCCESS;
}

ZEND_RESULT_CODE psi_call_frame_do_assert(struct psi_call_frame *frame, enum psi_assert_kind kind) {
	size_t i = 0;
	struct psi_assert_stmt *ass;

	while (psi_plist_get(frame->impl->stmts.ass, i++, &ass)) {
		if (ass->kind == kind) {
			if (!psi_assert_stmt_exec(ass, frame)) {
				char *message = psi_assert_stmt_message(ass);
				zend_throw_exception(kind == PSI_ASSERT_PRE
						? spl_ce_InvalidArgumentException
						: spl_ce_UnexpectedValueException, message, 0);
				free(message);
				return FAILURE;
			}
		}
	}

	return SUCCESS;
}

void psi_call_frame_do_call(struct psi_call_frame *frame) {
	frame->context->ops->call(frame);
}

void psi_call_frame_do_callback(struct psi_call_frame *frame, struct psi_call_frame_callback *cbdata)
{
	size_t i;
	void *retptr;
	ZEND_RESULT_CODE rc;
	struct psi_let_callback *cb = cbdata->cb->data.callback;
	zval return_value, *zargv = ecalloc(cbdata->argc, sizeof(*zargv));
	struct psi_call_frame_argument *frame_arg;

	assert(cbdata->argc == psi_plist_count(cb->decl->args));

	/* prepare args for the userland call */
	for (i = 0; i < cbdata->argc; ++i) {
		struct psi_set_exp *set_exp;
		struct psi_decl_var *set_var;
		struct psi_call_frame_symbol *set_sym;

		psi_plist_get(cb->args, i, &set_exp);
		set_var = psi_set_exp_get_decl_var(set_exp);
		set_sym = psi_call_frame_fetch_symbol(frame, set_var);

		set_sym->ptr = cbdata->argv[i];
		psi_set_exp_exec_ex(set_exp, &zargv[i], set_sym->ptr, frame);
	}

	frame_arg = psi_call_frame_get_argument(frame, cb->func->var->fqn);

	/* callback into userland */
	ZVAL_UNDEF(&return_value);
	zend_fcall_info_argp(&frame_arg->ival_ptr->zend.cb->fci, cbdata->argc, zargv);
	rc = zend_fcall_info_call(&frame_arg->ival_ptr->zend.cb->fci,
			&frame_arg->ival_ptr->zend.cb->fcc,	&return_value, NULL);
	assert(rc == SUCCESS);

	/* marshal return value of the userland call */
	frame_arg->zval_ptr = &return_value;
	retptr = psi_let_func_exec(cbdata->cb, cb->func, cb->decl->func, frame);
	memcpy(cbdata->rval, retptr, psi_decl_arg_get_size(cb->decl->func));

	/* cleanup */
	zend_fcall_info_args_clear(&frame_arg->ival_ptr->zend.cb->fci, 0);
	for (i = 0; i < cbdata->argc; ++i) {
		zval_ptr_dtor(&zargv[i]);
	}
	efree(zargv);
}

void psi_call_frame_do_return(struct psi_call_frame *frame, zval *return_value) {
	struct psi_return_stmt *ret;

	psi_plist_get(frame->impl->stmts.ret, 0, &ret);
	psi_return_stmt_exec(ret, return_value, frame);
}

void psi_call_frame_do_set(struct psi_call_frame *frame) {
	size_t i = 0;
	struct psi_set_stmt *set;

	while (psi_plist_get(frame->impl->stmts.set, i++, &set)) {
		psi_set_stmt_exec(set, frame);
	}
}

void psi_call_frame_do_free(struct psi_call_frame *frame) {
	size_t i = 0;
	struct psi_free_stmt *fre;

	while (psi_plist_get(frame->impl->stmts.fre, i++, &fre)) {
		psi_free_stmt_exec(fre, frame);
	}
}

void **psi_call_frame_push_auto_ex(struct psi_call_frame *frame, void *auto_free, void (*dtor)(void*)) {
	struct psi_call_frame_auto_free f;

	f.data = auto_free;
	f.dtor = dtor;

	zend_llist_add_element(&frame->temp, &f);
	return &((struct psi_call_frame_auto_free *) zend_llist_get_last(&frame->temp))->data;
}

void **psi_call_frame_push_auto(struct psi_call_frame *frame, void *auto_free) {
	return psi_call_frame_push_auto_ex(frame, auto_free, NULL);
}

static void psi_call_frame_local_auto_dtor(void *auto_list)
{
	zend_llist_destroy(auto_list);
	efree(auto_list);
}

#include "php_psi.h"

void psi_call_frame_free(struct psi_call_frame *frame) {
	zend_hash_destroy(&frame->arguments);
	zend_hash_destroy(&frame->symbols);
	if (frame->impl && frame->impl->func->static_memory) {
		zend_llist *temp = emalloc(sizeof(*temp));
		zval zlocal;

		memcpy(temp, &frame->temp, sizeof(*temp));
		ZVAL_OBJ(&zlocal, psi_object_init_ex(NULL, temp, psi_call_frame_local_auto_dtor));
		zend_set_local_var(frame->impl->func->name, &zlocal, /* force */ 1);
	} else {
		zend_llist_destroy(&frame->temp);
	}
	efree(frame->pointers);
	efree(frame);
}



