#ifndef _PSI_ENGINE_H
#define _PSI_ENGINE_H

size_t psi_t_alignment(token_t t);
size_t psi_t_size(token_t t);

static inline size_t psi_align(size_t s, size_t a) {
	return ((s - 1) | (a - 1)) + 1;
}

static inline size_t psi_offset_padding(size_t diff, size_t alignment) {
	if (diff && diff <= psi_align(diff, alignment)) {
		diff = 0;
	}

	return diff;
}

int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

void psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl);

#endif