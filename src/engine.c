#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include "php.h"
#include "php_psi.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "ext/spl/spl_iterators.h"

#include "parser.h"
#include "engine.h"
#include "calc.h"
#include "marshal.h"

static inline void psi_do_set(zval *return_value, set_value *set)
{
	decl_arg *set_arg = set->vars->vars[0]->arg;

	zval_dtor(return_value);
	set->func->handler(return_value, set, set_arg->let);
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

zend_long psi_zval_count(zval *zvalue)
{
	/* mimic PHP count() */
	zend_long count;
	zval retval;

	switch (Z_TYPE_P(zvalue)) {
	default:
		count = 1;
		break;
	case IS_NULL:
		count = 0;
		break;
	case IS_ARRAY:
		count = zend_array_count(Z_ARRVAL_P(zvalue));
		break;
	case IS_OBJECT:
		count = 1;
		if (Z_OBJ_HT_P(zvalue)->count_elements) {
			if (SUCCESS == Z_OBJ_HT_P(zvalue)->count_elements(zvalue, &count)) {
				break;
			}
		}

		if (instanceof_function(Z_OBJCE_P(zvalue), spl_ce_Countable)) {
			zend_call_method_with_0_params(zvalue, NULL, NULL, "count", &retval);
			if (Z_TYPE(retval) != IS_UNDEF) {
				count = zval_get_long(&retval);
				zval_ptr_dtor(&retval);
			}
		}
		break;
	}

	return count;
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
				iarg->val.zend.cb = ecalloc(1, sizeof(zend_fcall));
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

static inline impl_val *psi_let_func(let_func *func, decl_arg *darg);

static inline void *psi_let_val(let_val *val, decl_arg *darg)
{
	ZEND_ASSERT(darg);

	switch (val ? val->kind : PSI_LET_NULL) {
	case PSI_LET_TMP:
		memcpy(darg->ptr, deref_impl_val(val->data.var->arg->let, val->data.var), sizeof(impl_val));
		break;
	case PSI_LET_NULL:
		if (darg->var->array_size) {
			darg->val.ptr = ecalloc(darg->var->array_size, sizeof(impl_val));
			darg->mem = darg->val.ptr;
		} else {
			memset(&darg->val, 0, sizeof(impl_val));
		}
		break;
	case PSI_LET_CALLOC:
		darg->val.ptr = psi_do_calloc(val->data.alloc);
		darg->mem = darg->val.ptr;
		break;
	case PSI_LET_NUMEXP:
		darg->val.zend.lval = psi_long_num_exp(val->data.num, NULL);
		break;
	case PSI_LET_CALLBACK:
		darg->val.ptr = val->data.callback->decl->call.sym;
		break;
	case PSI_LET_FUNC:
		if (!psi_let_func(val->data.func, darg)) {
			return NULL;
		}
		break;
	}

	if (val && val->is_reference) {
		return darg->let = &darg->ptr;
	} else {
		return darg->let = darg->ptr;
	}
}

static inline impl_val *psi_let_func_ex(let_func *func, void *dptr, decl_type *dtype, decl_var *dvar, token_t itype, impl_val *ival, zval *zvalue, void **to_free) {
	switch (func->type) {
	case PSI_T_BOOLVAL:
		return psi_let_boolval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_INTVAL:
		return psi_let_intval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_FLOATVAL:
		return psi_let_floatval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_STRVAL:
		return psi_let_strval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_STRLEN:
		return psi_let_strlen(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_PATHVAL:
		return psi_let_pathval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_OBJVAL:
		return psi_let_objval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_ZVAL:
		return psi_let_zval(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_VOID:
		return psi_let_void(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_COUNT:
		return psi_let_count(dptr, dtype, itype, ival, zvalue, to_free);
	case PSI_T_ARRVAL:
		if (func->inner) {
			char *mem = NULL;
			size_t i, j = 0;
			decl_type *real;
			decl_args *args = extract_decl_type_args(dtype, &real);

			if (itype != PSI_T_ARRAY) {
				SEPARATE_ARG_IF_REF(zvalue);
				convert_to_array(zvalue);
			}

			if (args) {
				size_t size = extract_decl_type_size(real, NULL);

				mem = ecalloc(1, size + args->count * sizeof(void *));

				for (i = 0; i < args->count; ++i) {
					decl_arg *darg = args->args[i];
					let_val *lval = locate_let_vals_val(func->inner, darg->var->name);
					impl_val *ptr = NULL;

					if (lval) {
						if ((ptr = psi_let_val(lval, darg))) {
							memcpy(mem + darg->layout->pos, ptr, darg->layout->len);
							if (darg->mem) {
								((void **)(mem + size))[j++] = darg->mem;
							}
						}
						if (real->type == PSI_T_UNION) {
							break;
						}
					}
				}
			} else {
				zval *zv;
				let_val *inner = func->inner->vals[0];
				decl_var *sub_var;
				size_t size;

				if (inner->var) {
					sub_var = inner->var;
				} else {
					sub_var = copy_decl_var(dvar);
					assert(sub_var->pointer_level);
					--sub_var->pointer_level;
				}

				size = sub_var->pointer_level ? SIZEOF_VOID_P : extract_decl_type_size(real, NULL);
				mem = ecalloc(1, size * (1 + zend_array_count(Z_ARRVAL_P(zvalue))));

				ZEND_HASH_FOREACH_VAL_IND(Z_ARRVAL_P(zvalue), zv)
				{
					void *tmp = NULL;
					impl_val val = {0}, *ptr, *sub;

					ptr = psi_let_func_ex(inner->data.func, &val, real, dvar, 0, NULL, zv, &tmp);
					sub = deref_impl_val(ptr, sub_var);

					memcpy(&mem[size * j++], &sub, size);
				}
				ZEND_HASH_FOREACH_END();

				if (sub_var != inner->var) {
					free_decl_var(sub_var);
				}
			}
			return *to_free = mem;
		} else {
			return psi_let_arrval(dptr, dtype, dvar, itype, ival, zvalue, to_free);
		}
		break;
	default:
		assert(0);
	}
	return NULL;
}

static inline impl_val *psi_let_func(let_func *func, decl_arg *darg) {

	if (func->var->arg) {
		return darg->ptr = psi_let_func_ex(func,
				darg->ptr, darg->type, darg->var,
				func->var->arg->type->type,
				&func->var->arg->val,
				func->var->arg->_zv,
				&darg->mem);
	} else {
		impl_var *ivar = locate_let_val_impl_var(func->outer);
		zval *entry = zend_symtable_str_find(Z_ARRVAL_P(ivar->arg->_zv), func->var->name+1, strlen(func->var->name)-1);
		impl_arg *iarg = init_impl_arg(
				init_impl_type(PSI_T_MIXED, "mixed"),
				copy_impl_var(func->var), NULL);

		func->var->arg = iarg;
		if (entry) {
			iarg->_zv = entry;
		} else {
			zval ztmp;

			ZVAL_NULL(&ztmp);
			iarg->_zv = zend_symtable_str_update_ind(Z_ARRVAL_P(ivar->arg->_zv), func->var->name+1, strlen(func->var->name)-1, &ztmp);
		}

		psi_let_func(func, darg);
		free_impl_arg(iarg);
		return darg->ptr;
	}

}

static inline void *psi_do_let(let_stmt *let)
{
	return psi_let_val(let->val, let->val->var->arg);
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
			impl_val *fval = darg->let;

			f->decl->call.args[j] = deref_impl_val(fval, dvar);
		}

		/* FIXME: check in validate_* that free functions return scalar */
		psi_context_call(&PSI_G(context), &f->decl->call, NULL);
	}
}

static inline void psi_clean_array_struct(let_val *val, decl_arg *darg) {
	if (val->kind == PSI_LET_FUNC
	&&	val->data.func->type == PSI_T_ARRVAL) {
		decl_type *type = real_decl_type(darg->type);

		if (type->type == PSI_T_STRUCT) {
			void **ptr = (void **) ((char *) darg->mem + type->real.strct->size);

			while (*ptr) {
				efree(*ptr++);
			}
			// args = type->real.strct->args;
		} else if (type->type == PSI_T_UNION) {
			void **ptr = (void **) ((char *) darg->mem + type->real.unn->size);

			if (*ptr) {
				efree(*ptr);
			}
			// args = type->real.unn->args;
		}
#if 0
		if (args && val->data.func->inner) {
			size_t i;

			for (i = 0; i < val->data.func->inner->count; ++i) {
				let_val *inner = val->data.func->inner->vals[i];
				decl_var *refvar = locate_let_val_inner_ref(inner)->var;
				decl_arg *subarg = locate_decl_arg(args, refvar->name);

				if (subarg) {
					psi_clean_array_struct(val->data.func->inner->vals[i], subarg);
					if (subarg->mem) {
						efree(subarg->mem);
						subarg->mem = NULL;
					}
				}
			}
		}
#endif
	}
}

static inline void psi_clean_let_val(let_val *val) {

	let_func *func = locate_let_val_func(val);

	if (func && func->inner) {
		size_t i;

		for (i = 0; i < func->inner->count; ++i) {
			let_val *inner = func->inner->vals[i];
			psi_clean_let_val(inner);
		}
	}
	if (val->var) {
		decl_arg *darg = val->var->arg;
		if (darg) {
			if (darg->mem) {
				psi_clean_array_struct(val, darg);
				efree(darg->mem);
				darg->mem = NULL;
			}
			darg->ptr = &darg->val;
			darg->let = darg->ptr;
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
		case PSI_T_CALLABLE:
			if (iarg->val.zend.cb) {
				if (iarg->val.zend.cb->fci.size) {
					zend_fcall_info_args_clear(&iarg->val.zend.cb->fci, 1);
				}
				efree(iarg->val.zend.cb);
			}
			break;
		}
	}

	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];
		psi_clean_let_val(let->val);
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
		impl->decl->call.args[i] = impl->decl->args->args[i]->let;
	}

	if (!impl->decl->func->var->pointer_level) {
		decl_type *real;
		decl_args *args = extract_decl_type_args(impl->decl->func->type, &real);

		switch (real->type) {
		case PSI_T_STRUCT:
		case PSI_T_UNION:
			impl->decl->func->ptr = ecalloc(1,
					extract_decl_type_size(real, NULL) + args->count * sizeof(void*));
			break;
		default:
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
		token_t vatype = va->name->type->type;
		psi_marshal_let let_fn;

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
		case PSI_T_BOOL:	let_fn = psi_let_boolval;	break;
		case PSI_T_INT:		let_fn = psi_let_intval;	break;
		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:	let_fn = psi_let_floatval;	break;
		case PSI_T_STRING:	let_fn = psi_let_strval;	break;
		EMPTY_SWITCH_DEFAULT_CASE();
		}

		va->types[i] = vatype;

		/* FIXME: varargs with struct-by-value :) */
		//if (!psi_let_val(let_fn, vaarg, &va->values[i], NULL, &to_free)) {
		if (!let_fn(&va->values[i], NULL, vaarg->type->type, &vaarg->val, vaarg->_zv, &to_free)) {
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

ZEND_RESULT_CODE psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl)
{
	size_t i;
	impl_vararg *va = NULL;

	memset(impl->decl->func->ptr, 0, sizeof(impl_val));

	if (SUCCESS != psi_parse_args(execute_data, impl)) {
		return FAILURE;
	}

	for (i = 0; i < impl->stmts->let.count; ++i) {
		let_stmt *let = impl->stmts->let.list[i];

		if (!psi_do_let(let)) {
			psi_do_return(return_value, impl->stmts->ret.list[0]);
			psi_do_clean(impl);
			return FAILURE;
		}
	}

	if (impl->decl->args) {
		psi_do_args(impl);

		if (impl->func->args->vararg.args) {
			va = psi_do_varargs(impl);
		}
	}

	psi_context_call(&PSI_G(context), &impl->decl->call, va);
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

	return SUCCESS;
}

ZEND_RESULT_CODE psi_callback(let_callback *cb, void *retval, unsigned argc, void **argv)
{
	size_t i;
	decl *decl_cb = cb->decl;
	impl_arg *iarg = cb->func->var->arg;
	zval return_value, *zargv = calloc(argc, sizeof(*zargv));
	void *result, *to_free = NULL;

	ZEND_ASSERT(argc == cb->decl->args->count);

	/* prepare args for the userland call */
	for (i = 0; i < argc; ++i) {
		cb->decl->args->args[i]->let = argv[i];
	}
	for (i = 0; i < cb->args->count; ++i) {
		psi_do_set(&zargv[i], cb->args->vals[i]);
	}
	zend_fcall_info_argp(&iarg->val.zend.cb->fci, cb->args->count, zargv);

	/* callback into userland */
	ZVAL_UNDEF(&return_value);
	iarg->_zv = &return_value;
	zend_fcall_info_call(&iarg->val.zend.cb->fci, &iarg->val.zend.cb->fcc, iarg->_zv, NULL);

	/* marshal return value of the userland call
	switch (iarg->type->type) {
	case PSI_T_BOOL:	zend_parse_arg_bool(iarg->_zv, &iarg->val.zend.bval, NULL, 0);		break;
	case PSI_T_LONG:	zend_parse_arg_long(iarg->_zv, &iarg->val.zend.lval, NULL, 0, 1);	break;
	case PSI_T_FLOAT:
	case PSI_T_DOUBLE:	zend_parse_arg_double(iarg->_zv, &iarg->val.dval, NULL, 0);			break;
	case PSI_T_STRING:	zend_parse_arg_str(iarg->_zv, &iarg->val.zend.str, 0);				break;
	}
	*/
	result = psi_let_func_ex(cb->func, retval, decl_cb->func->type, decl_cb->func->var, 0, &iarg->val, iarg->_zv, &to_free);
	// result = cb->func->handler(retval, decl_cb->func->type, iarg, &to_free);

	if (result != retval) {
		*(void **)retval = result;
	}

	zend_fcall_info_args_clear(&iarg->val.zend.cb->fci, 0);
	for (i = 0; i < cb->args->count; ++i) {
		zval_ptr_dtor(&zargv[i]);
	}
	free(zargv);

	return SUCCESS;

}
