#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_psi.h"

#include "zend_exceptions.h"

#include "parser.h"
#include "engine.h"
#include "calc.h"
#include "marshal.h"

size_t psi_t_alignment(token_t t)
{
#define PSI_ALIGNOF(T) case PSI_T_## T: return ALIGNOF_## T ##_T;
	switch (t) {
	PSI_ALIGNOF(INT8);
	PSI_ALIGNOF(UINT8);
	PSI_ALIGNOF(INT16);
	PSI_ALIGNOF(UINT16);
	PSI_ALIGNOF(INT32);
	PSI_ALIGNOF(UINT32);
	PSI_ALIGNOF(INT64);
	PSI_ALIGNOF(UINT64);
	case PSI_T_FLOAT:
		return ALIGNOF_FLOAT;
	case PSI_T_DOUBLE:
		return ALIGNOF_DOUBLE;
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return ALIGNOF_VOID_P;
	case PSI_T_ENUM:
		return ALIGNOF_INT;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return 0;
}

size_t psi_t_size(token_t t)
{
#define PSI_SIZEOF(T) case PSI_T_## T : return SIZEOF_## T ##_T;
	switch (t) {
	PSI_SIZEOF(INT8);
	PSI_SIZEOF(UINT8);
	PSI_SIZEOF(INT16);
	PSI_SIZEOF(UINT16);
	PSI_SIZEOF(INT32);
	PSI_SIZEOF(UINT32);
	PSI_SIZEOF(INT64);
	PSI_SIZEOF(UINT64);
	case PSI_T_FLOAT:
		return SIZEOF_FLOAT;
	case PSI_T_DOUBLE:
		return SIZEOF_DOUBLE;
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return SIZEOF_VOID_P;
	case PSI_T_ENUM:
		return SIZEOF_INT;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return 0;
}

int psi_internal_type(impl_type *type)
{
	switch (type->type) {
	case PSI_T_BOOL:
		return _IS_BOOL;
	case PSI_T_INT:
		return IS_LONG;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:
		return IS_DOUBLE;
	case PSI_T_STRING:
		return IS_STRING;
	case PSI_T_ARRAY:
		return IS_ARRAY;
	default:
		return 0;
	}
}

zend_internal_arg_info *psi_internal_arginfo(impl *impl)
{
	size_t i;
	zend_internal_arg_info *aip;
	zend_internal_function_info *fi;

	aip = calloc(impl->func->args->count + 1 + !!impl->func->args->vararg.name, sizeof(*aip));

	fi = (zend_internal_function_info *) &aip[0];
	fi->allow_null = 1;
	fi->required_num_args = psi_num_min_args(impl);
	fi->return_reference = impl->func->return_reference;
	fi->type_hint = psi_internal_type(impl->func->return_type);

	if (impl->func->args->vararg.name) {
		impl_arg *vararg = impl->func->args->vararg.name;
		zend_internal_arg_info *ai = &aip[impl->func->args->count];

		ai->name = vararg->var->name;
		ai->allow_null = 1;
		ai->type_hint = psi_internal_type(vararg->type);
		if (vararg->var->reference) {
			ai->pass_by_reference = 1;
		}
		ai->is_variadic = 1;
	}

	for (i = 0; i < impl->func->args->count; ++i) {
		impl_arg *iarg = impl->func->args->args[i];
		zend_internal_arg_info *ai = &aip[i+1];

		ai->name = iarg->var->name;
		ai->type_hint = psi_internal_type(iarg->type);
		if (iarg->var->reference) {
			ai->pass_by_reference = 1;
		}
		//if (iarg->var->reference || (iarg->def && iarg->def->type == PSI_T_NULL)) {
			ai->allow_null = 1;
		//}
	}

	return aip;
}

size_t psi_num_min_args(impl *impl)
{
	size_t i, n = impl->func->args->count;

	for (i = 0; i < impl->func->args->count; ++i) {
		if (impl->func->args->args[i]->def) {
			--n;
		}
	}
	return n;
}


static inline ZEND_RESULT_CODE psi_parse_args(zend_execute_data *execute_data, impl *impl)
{
	size_t i;
	impl_arg *iarg;
	zend_error_handling zeh;

	zend_replace_error_handling(EH_THROW, zend_exception_get_default(), &zeh);

	if (!impl->func->args->count) {
		ZEND_RESULT_CODE rv;

		rv = zend_parse_parameters_none();
		zend_restore_error_handling(&zeh);
		return rv;
	}

	ZEND_PARSE_PARAMETERS_START(psi_num_min_args(impl), impl->func->args->vararg.name ? -1 : impl->func->args->count)
	nextarg:
		if (impl->func->args->vararg.name && _i >= impl->func->args->count) {
			impl_arg *varg = impl->func->args->vararg.name;
			iarg = init_impl_arg(
					init_impl_type(varg->type->type, varg->type->name),
					init_impl_var(varg->var->name, varg->var->reference),
					NULL);

			Z_PARAM_OPTIONAL;
			if (_i == impl->func->args->count) {
				impl->func->args->vararg.args = init_impl_args(iarg);
			} else {
				add_impl_arg(impl->func->args->vararg.args, iarg);
			}
		} else {
			iarg = impl->func->args->args[_i];
			if (iarg->def) {
				Z_PARAM_OPTIONAL;
			}
		}
		if (PSI_T_BOOL == iarg->type->type) {
			Z_PARAM_BOOL(iarg->val.zend.bval);
		} else if (PSI_T_INT == iarg->type->type) {
			Z_PARAM_LONG(iarg->val.zend.lval);
		} else if (PSI_T_FLOAT == iarg->type->type || PSI_T_DOUBLE == iarg->type->type) {
			Z_PARAM_DOUBLE(iarg->val.dval);
		} else if (PSI_T_STRING == iarg->type->type) {
			Z_PARAM_STR_EX(iarg->val.zend.str, 1, iarg->var->reference);
			if (iarg->val.zend.str) {
				zend_string_addref(iarg->val.zend.str);
			}
		} else if (PSI_T_ARRAY == iarg->type->type) {
			Z_PARAM_PROLOGUE(0);
		} else if (PSI_T_OBJECT == iarg->type->type) {
			Z_PARAM_PROLOGUE(0);
		} else if (PSI_T_MIXED == iarg->type->type) {
			Z_PARAM_PROLOGUE(0);
		} else if (PSI_T_CALLABLE == iarg->type->type) {
			zend_fcall_info fci;
			zend_fcall_info_cache fcc;

			Z_PARAM_FUNC_EX(fci, fcc, 1, 0);

			if (fci.size) {
				iarg->val.zend.cb = calloc(1, sizeof(zend_fcall));
				iarg->val.zend.cb->fci = fci;
				iarg->val.zend.cb->fcc = fcc;
			}
		} else {
			error_code = ZPP_ERROR_FAILURE;
			break;
		}
		iarg->_zv = _arg;
		ZVAL_DEREF(iarg->_zv);
		if (_i < _num_args) {
			goto nextarg;
		}
	ZEND_PARSE_PARAMETERS_END_EX(
		zend_restore_error_handling(&zeh);
		return FAILURE
	);

	/* set up defaults */
	for (i = 0; i < impl->func->args->count; ++i) {
		if (i >= EX_NUM_ARGS() && iarg->def) {
			iarg = impl->func->args->args[i];

			switch (iarg->type->type) {
			case PSI_T_BOOL:
				iarg->val.zend.bval = iarg->def->type == PSI_T_TRUE ? 1 : 0;
				break;
			case PSI_T_INT:
				iarg->val.zend.lval = zend_atol(iarg->def->text, strlen(iarg->def->text));
				break;
			case PSI_T_FLOAT:
			case PSI_T_DOUBLE:
				iarg->val.dval = zend_strtod(iarg->def->text, NULL);
				break;
			case PSI_T_STRING:
				/* FIXME */
				iarg->val.zend.str = zend_string_init(&iarg->def->text[1], strlen(iarg->def->text) - 2, 0);
				break;
			}
		}
	}

	zend_restore_error_handling(&zeh);
	return SUCCESS;
}

static inline void *psi_do_calloc(let_calloc *alloc)
{
	zend_long n = psi_long_num_exp(alloc->nmemb, NULL), s = psi_long_num_exp(alloc->size, NULL);
	void *mem = safe_emalloc(n, s, sizeof(void *));
	memset(mem, 0, n * s + sizeof(void *));
#if 0
	fprintf(stderr, "calloc: %p\n", mem);
#endif
	return mem;
}

static inline impl_val *psi_let_val(token_t let_func, impl_arg *iarg, impl_val *arg_val, decl_struct *strct, void **to_free)
{
	switch (let_func) {
	case PSI_T_BOOLVAL:
		break;
	case PSI_T_INTVAL:
		break;
	case PSI_T_FLOATVAL:
		break;
	case PSI_T_PATHVAL:
	case PSI_T_STRVAL:
		if (PSI_T_PATHVAL == let_func) {

		}
		break;
	case PSI_T_STRLEN:
		break;
	case PSI_T_ARRVAL:
		if (iarg->type->type == PSI_T_ARRAY) {
			arg_val = psi_array_to_struct(strct, HASH_OF(iarg->_zv));
			*to_free = arg_val;
		}
		break;
	case PSI_T_OBJVAL:
		if (iarg->type->type == PSI_T_OBJECT) {
			psi_object *obj;

			if (!instanceof_function(Z_OBJCE_P(iarg->_zv), psi_object_get_class_entry())) {
				return NULL;
			}

			obj = PSI_OBJ(iarg->_zv, NULL);
			arg_val->ptr = obj->data;
		}
		break;
	case PSI_T_CALLBACK:
		if (iarg->type->type == PSI_T_CALLABLE) {
			
		}
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return arg_val;
}

static inline impl_val *psi_let_func(let_func *func, decl_arg *darg) {
	return darg->ptr = func->handler(darg->ptr, darg->type, func->arg, &darg->mem);
}

static inline void *psi_do_let(let_stmt *let)
{
	decl_arg *darg = let->var->arg;
	impl_val *arg_val = darg->ptr;
	impl_arg *iarg;

	switch (let->val ? let->val->kind : PSI_LET_NULL) {
	case PSI_LET_TMP:
		memcpy(arg_val, deref_impl_val(let->val->data.var->arg->let->ptr, let->val->data.var), sizeof(*arg_val));
#if 0
		fprintf(stderr, "LET TMP: %p -> %p\n",
				let->val->data.var->arg->let->ptr,
				arg_val->ptr);
#endif
		break;
	case PSI_LET_NULL:
		if (darg->var->array_size) {
			arg_val->ptr = ecalloc(darg->var->array_size, sizeof(*arg_val));
			darg->mem = arg_val->ptr;
		} else {
			memset(arg_val, 0, sizeof(*arg_val));
		}
		break;
	case PSI_LET_CALLOC:
		arg_val->ptr = psi_do_calloc(let->val->data.alloc);
		darg->mem = arg_val->ptr;
		break;
	case PSI_LET_CALLBACK:
		arg_val->ptr = 0 /* callback closure */;
		break;
	case PSI_LET_NUMEXP:
		arg_val->zend.lval = psi_long_num_exp(let->val->data.num, NULL);
		break;
	case PSI_LET_FUNC:
		if (!psi_let_func(let->val->data.func, darg)) {
			return NULL;
		}

		iarg = let->val->data.func->arg;

		if (!(darg->ptr = psi_let_val(let->val->data.func->type, iarg, darg->ptr, real_decl_type(darg->type)->strct, &darg->mem))) {
			return NULL;
		}
	}

	if (let->val && let->val->flags.one.is_reference) {
		return let->ptr = &darg->ptr;
	} else {
		return let->ptr = darg->ptr;
	}
}

static inline void psi_do_return(zval *return_value, return_stmt *ret)
{
	ret->set->func->handler(return_value, ret->set, ret->set->vars->vars[0]->arg->ptr);
}

static inline void psi_do_free(free_stmt *fre)
{
	size_t i, j;

	for (i = 0; i < fre->calls->count; ++i) {
		free_call *f = fre->calls->list[i];

		for (j = 0; j < f->vars->count; ++j) {
			decl_var *dvar = f->vars->vars[j];
			decl_arg *darg = dvar->arg;
			impl_val *fval = darg->let ? darg->let->ptr : darg->ptr;

			f->decl->call.args[j] = deref_impl_val(fval, dvar);
		}

		/* FIXME: check in validate_* that free functions return scalar */
		PSI_ContextCall(&PSI_G(context), &f->decl->call, NULL);
	}
}

static inline void psi_clean_array_struct(decl_arg *darg) {
	if (darg->let
	&&	darg->let->val->kind == PSI_LET_FUNC
	&&	darg->let->val->data.func->type == PSI_T_ARRVAL) {
		decl_type *type = real_decl_type(darg->type);

		if (type->type == PSI_T_STRUCT) {
			void **ptr = (void **) ((char *) darg->mem + type->strct->size);

			while (*ptr) {
				efree(*ptr++);
			}
		}
	}
}

static inline void psi_do_clean(impl *impl)
{
	size_t i;

	if (impl->decl->func->ptr != &impl->decl->func->val) {
		efree(impl->decl->func->ptr);
		impl->decl->func->ptr = &impl->decl->func->val;
	}
	for (i = 0; i < impl->func->args->count; ++i ) {
		impl_arg *iarg = impl->func->args->args[i];

		switch (iarg->type->type) {
		case PSI_T_STRING:
			if (iarg->val.zend.str) {
				zend_string_release(iarg->val.zend.str);
			}
			break;
		}
	}

	if (impl->decl->args) for (i = 0; i < impl->decl->args->count; ++i) {
		decl_arg *darg = impl->decl->args->args[i];

		if (darg->mem) {
			psi_clean_array_struct(darg);
			efree(darg->mem);
			darg->mem = NULL;
		}
		darg->ptr = &darg->val;
	}

	if (impl->func->args->vararg.args) {
		free_impl_args(impl->func->args->vararg.args);
		impl->func->args->vararg.args = NULL;
	}
	if (impl->func->args->vararg.types) {
		efree(impl->func->args->vararg.types);
		impl->func->args->vararg.types = NULL;
	}
	if (impl->func->args->vararg.values) {
		efree(impl->func->args->vararg.values);
		impl->func->args->vararg.values = NULL;
	}
	if (impl->func->args->vararg.free_list) {
		void **list = impl->func->args->vararg.free_list;

		while (*list) {
			efree(*list++);
		}

		efree(impl->func->args->vararg.free_list);
		impl->func->args->vararg.free_list = NULL;
	}
}


static inline void psi_do_args(impl *impl) {
	size_t i;

	for (i = 0; i < impl->decl->args->count; ++i) {
		impl->decl->call.args[i] = impl->decl->args->args[i]->let->ptr;
	}

	if (!impl->decl->func->var->pointer_level) {
		decl_type *real = real_decl_type(impl->decl->func->type);

		switch (real->type) {
		case PSI_T_STRUCT:
			impl->decl->func->ptr = psi_array_to_struct(real->strct, NULL);
			break;
		}
	}
}

static inline impl_vararg *psi_do_varargs(impl *impl) {
	size_t i, j;
	impl_vararg *va = &impl->func->args->vararg;
	size_t vacount = va->args->count;


	if (!vacount) {
		return NULL;
	}

	va->types = ecalloc(vacount, sizeof(*va->types));
	va->values = ecalloc(vacount, sizeof(*va->values));

	for (i = 0, j = 0; i < vacount; ++i) {
		impl_arg *vaarg = va->args->args[i];
		void *to_free = NULL;
		token_t let_fn, vatype = va->name->type->type;

		if (vatype == PSI_T_MIXED) {
			switch (Z_TYPE_P(vaarg->_zv)) {
			case IS_TRUE:
			case IS_FALSE:	vatype = PSI_T_BOOL;	break;
			case IS_LONG:	vatype = PSI_T_INT;		break;
			case IS_DOUBLE:	vatype = PSI_T_FLOAT;	break;
			default:		vatype = PSI_T_STRING;	break;
			}
		}


		switch (vatype) {
		case PSI_T_BOOL:	let_fn = PSI_T_BOOLVAL;	break;
		case PSI_T_INT:		let_fn = PSI_T_INTVAL;	break;
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:	let_fn = PSI_T_FLOATVAL;break;
		case PSI_T_STRING:	let_fn = PSI_T_STRVAL;	break;
		EMPTY_SWITCH_DEFAULT_CASE();
		}

		va->types[i] = vatype;
		/* FIXME: varargs with struct-by-value :) */
		if (!psi_let_val(let_fn, vaarg, &va->values[i], NULL, &to_free)) {
			return NULL;
		}

		if (to_free) {
			if (!va->free_list) {
				va->free_list = ecalloc(vacount - i + 1, sizeof(*va->free_list));
			}
			va->free_list[j++] = to_free;
		}
	}

	return va;
}

void psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl)
{
	size_t i;
	impl_vararg *va = NULL;

	memset(impl->decl->func->ptr, 0, sizeof(impl_val));

	if (SUCCESS != psi_parse_args(execute_data, impl)) {
		return;
	}

	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];

		if (!psi_do_let(let)) {
			psi_do_return(return_value, impl->stmts->ret.list[0]);
			psi_do_clean(impl);
			return;
		}
	}

	if (impl->decl->args) {
		psi_do_args(impl);

		if (impl->func->args->vararg.args) {
			va = psi_do_varargs(impl);
		}
	}

	PSI_ContextCall(&PSI_G(context), &impl->decl->call, va);
	psi_do_return(return_value, impl->stmts->ret.list[0]);

	for (i = 0; i < impl->stmts->set.count; ++i) {
		set_stmt *set = impl->stmts->set.list[i];

		if (set->arg->_zv) {
			psi_do_set(set->arg->_zv, set->val);
		}
	}

	for (i = 0; i < impl->stmts->fre.count; ++i) {
		free_stmt *fre = impl->stmts->fre.list[i];

		psi_do_free(fre);
	}
	psi_do_clean(impl);
}
