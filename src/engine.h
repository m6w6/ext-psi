#ifndef _PSI_ENGINE_H
#define _PSI_ENGINE_H

static inline size_t psi_align(size_t s, size_t a) {
	return ((s - 1) | (a - 1)) + 1;
}

static inline size_t psi_offset_padding(size_t diff, size_t alignment) {
	if (diff && diff <= psi_align(diff, alignment)) {
		diff = 0;
	}

	return diff;
}

static inline void psi_do_set(zval *return_value, set_value *set)
{
	decl_arg *set_arg = set->vars->vars[0]->arg;

	zval_dtor(return_value);
	set->func->handler(return_value, set, set_arg->let);
}

int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

ZEND_RESULT_CODE psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl);
ZEND_RESULT_CODE psi_callback(let_callback *cb, void *retval, unsigned argc, void **argv);

#endif
