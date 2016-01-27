#ifndef _PSI_MARSHAL_H
#define _PSI_MARSHAL_H

void psi_to_void(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_bool(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_int(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_double(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_string(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_recursive(zval *return_value, set_value *set, impl_val *r_val);
void psi_to_array(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_object(zval *return_value, set_value *set, impl_val *ret_val);

void *psi_array_to_struct(decl_struct *s, HashTable *arr);
void psi_from_zval(impl_val *mem, decl_arg *spec, zval *zv, void **tmp);

#endif
