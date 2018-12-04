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

#ifndef PSI_MARSHAL_H
#define PSI_MARSHAL_H

#include "types/impl_val.h"
#include "Zend/zend_types.h"

struct psi_let_exp;
struct psi_set_exp;
struct psi_decl_arg;
struct psi_call_frame;
struct psi_impl;
struct psi_impl_type;

#if HAVE_INT128
static inline char *psi_u128_to_buf(char *buf, unsigned __int128 u128)
{
	for (*buf = 0; u128 > 0; u128 /= 10) {
		*--buf = ((u128 % 10) + '0') & 0xff;
	}
	return buf;
}

static inline char *psi_i128_to_buf(char *buf, __int128 i128)
{
	if (i128 < 0) {
		char *res = psi_u128_to_buf(buf, ~((unsigned __int128) i128) + 1);

		*--res = '-';
		return res;
	}
	return psi_u128_to_buf(buf, i128);
}
#else
# define psi_u128_to_buf(b,u) zend_print_ulong_to_buf(b,u)
# define psi_i128_to_buf(b,i) zend_print_long_to_buf(b,i)
#endif


#define RETVAL_LONG_DOUBLE_STR(V, flags) ZVAL_LONG_DOUBLE_STR(return_value, V, flags)
# define ZVAL_LONG_DOUBLE_STR(z, V, flags) do { \
	char buf[0x20] = {0}; \
	bool is_signed = false, persistent = false; \
	flags; \
	if (is_signed) { \
		if (V >= ZEND_LONG_MIN && V <= ZEND_LONG_MAX) { \
			ZVAL_LONG(z, V); \
		} else if (V >= -(1L<<52) && V <= (1L<<53)) { \
			ZVAL_DOUBLE(z, V); \
		} else if (V < ZEND_LONG_MIN || V > ZEND_LONG_MAX) { \
			char *str = psi_i128_to_buf(&buf[sizeof(buf) - 1], V); \
			if (persistent) { \
				ZVAL_PSTRING(z, str); \
			} else { \
				ZVAL_STRING(z, str); \
			} \
		} else { \
			char *str = zend_print_long_to_buf(&buf[sizeof(buf) - 1], V); \
			if (persistent) { \
				ZVAL_PSTRING(z, str); \
			} else { \
				ZVAL_STRING(z, str); \
			} \
		} \
	} else { \
		if (V <= ZEND_LONG_MAX) { \
			ZVAL_LONG(z, V); \
		} else if (V <= (1L<<53)) { \
			ZVAL_DOUBLE(z, V); \
		} else if (V > ZEND_ULONG_MAX) { \
			char *str = psi_u128_to_buf(&buf[sizeof(buf) - 1], V); \
			if (persistent) { \
				ZVAL_PSTRING(z, str); \
			} else { \
				ZVAL_STRING(z, str); \
			} \
		} else { \
			char *str = zend_print_ulong_to_buf(&buf[sizeof(buf) - 1], V); \
			if (persistent) { \
				ZVAL_PSTRING(z, str); \
			} else { \
				ZVAL_STRING(z, str); \
			} \
		} \
	} \
} while (0)


zend_long psi_zval_count(zval *zvalue);
zend_internal_arg_info *psi_internal_arginfo(struct psi_impl *impl);
int psi_internal_type(struct psi_impl_type *type);

typedef void (*psi_marshal_set)(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
typedef impl_val *(*psi_marshal_let)(impl_val *tmp, struct psi_decl_arg *type_spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);

void psi_set_void(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_bool(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_int(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_float(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_string(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_stringl(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_recursive(zval *return_value, struct psi_set_exp *set, impl_val *r_val, struct psi_call_frame *frame);
void psi_set_to_array_simple(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_array_counted(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_array(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_to_object(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);
void psi_set_zval(zval *return_value, struct psi_set_exp *set, impl_val *ret_val, struct psi_call_frame *frame);

impl_val *psi_let_void(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_boolval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_intval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_floatval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_strval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_pathval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_strlen(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_objval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_zval(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ivalue, zval *zvalue, void **to_free);
impl_val *psi_let_count(impl_val *tmp, struct psi_decl_arg *spec, token_t impl_type, impl_val *ival, zval *zvalue, void **to_free);

#endif
