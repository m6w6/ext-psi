#ifndef _PSI_ENGINE_H
#define _PSI_ENGINE_H

int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

ZEND_RESULT_CODE psi_call(zend_execute_data *execute_data, zval *return_value, impl *impl);
ZEND_RESULT_CODE psi_callback(let_callback *cb, void *retval, unsigned argc, void **argv);

#endif
