#ifndef _PSI_MARSHAL_H
#define _PSI_MARSHAL_H

typedef void (*psi_marshal_set)(zval *return_value, set_value *set, impl_val *ret_val);
typedef impl_val *(*psi_marshal_let)(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);

void psi_to_void(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_bool(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_int(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_double(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_string(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_recursive(zval *return_value, set_value *set, impl_val *r_val);
void psi_to_array(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_object(zval *return_value, set_value *set, impl_val *ret_val);
void psi_to_zval(zval *return_value, set_value *set, impl_val *ret_val);

void *psi_array_to_union(decl_union *u, HashTable *arr);
void *psi_array_to_struct(decl_struct *s, HashTable *arr);

typedef void (*psi_marshal_zval)(void *cb_ctx, impl_val **ptr, decl_arg *spec, token_t cast, zval *zv, void **tmp);

void psi_from_zval_ex(void *cb_ctx, impl_val **ptr, decl_arg *spec, token_t cast, zval *zv, void **tmp);

void *psi_array_to_struct_ex(decl_struct *s, HashTable *arr, psi_marshal_zval cb, void *cb_ctx);
void *psi_array_to_union_ex(decl_union *u, HashTable *arr, psi_marshal_zval cb, void *cb_ctx);

impl_val *psi_let_void(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_boolval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_intval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_floatval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_strval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_pathval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_strlen(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_arrval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_objval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_zval(impl_val *tmp, decl_type *decl_type, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);

#endif
