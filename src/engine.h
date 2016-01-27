#ifndef _PSI_ENGINE_H
#define _PSI_ENGINE_H

size_t psi_t_alignment(token_t t);
size_t psi_t_size(token_t t);
size_t psi_t_align(token_t t, size_t s);

size_t psi_offset_padding(size_t diff, size_t alignment);
int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

void psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl);

#endif
