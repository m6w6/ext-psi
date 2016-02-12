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

impl_val *psi_let_boolval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_intval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_floatval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_strval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_pathval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_strlen(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_arrval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);
impl_val *psi_let_objval(impl_val *tmp, decl_type *type, impl_arg *iarg, void **to_free);

#endif
