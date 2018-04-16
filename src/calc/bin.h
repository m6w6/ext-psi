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

#include "php_psi_stdinc.h"
#include <assert.h>

#include "token.h"

static inline token_t psi_calc_bin_lshift(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.u64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.u64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.u64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.u64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.u64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.u64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.u64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.u64 = v1->u64;
		break;

	case PSI_T_INT128:
		i1.u64 = v1->i128;
		break;

	case PSI_T_UINT128:
		i1.u64 = v1->u128;
		break;

	case PSI_T_FLOAT:
		i1.u64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.u64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.u64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.u64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.u64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.u64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.u64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.u64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.u64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.u64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.u64 = v2->u64;
		break;
	case PSI_T_INT128:
		i2.u64 = v2->i128;
		break;
	case PSI_T_UINT128:
		i2.u64 = v2->u128;
		break;
	case PSI_T_FLOAT:
		i2.u64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.u64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.u64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u64 = i1.u64 << i2.u64;
	return PSI_T_UINT64;
}

static inline token_t psi_calc_bin_rshift(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.u64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.u64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.u64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.u64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.u64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.u64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.u64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.u64 = v1->u64;
		break;

	case PSI_T_INT128:
		i1.u64 = v1->i128;
		break;

	case PSI_T_UINT128:
		i1.u64 = v1->u128;
		break;

	case PSI_T_FLOAT:
		i1.u64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.u64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.u64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.u64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.u64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.u64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.u64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.u64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.u64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.u64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.u64 = v2->u64;
		break;
	case PSI_T_INT128:
		i2.u64 = v2->i128;
		break;
	case PSI_T_UINT128:
		i2.u64 = v2->u128;
		break;
	case PSI_T_FLOAT:
		i2.u64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.u64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.u64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u64 = i1.u64 >> i2.u64;
	return PSI_T_UINT64;
}

static inline token_t psi_calc_bin_and(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.u64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.u64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.u64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.u64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.u64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.u64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.u64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.u64 = v1->u64;
		break;

	case PSI_T_INT128:
		i1.u64 = v1->i128;
		break;

	case PSI_T_UINT128:
		i1.u64 = v1->u128;
		break;

	case PSI_T_FLOAT:
		i1.u64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.u64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.u64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.u64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.u64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.u64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.u64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.u64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.u64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.u64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.u64 = v2->u64;
		break;
	case PSI_T_INT128:
		i2.u64 = v2->i128;
		break;
	case PSI_T_UINT128:
		i2.u64 = v2->u128;
		break;
	case PSI_T_FLOAT:
		i2.u64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.u64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.u64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u64 = i1.u64 & i2.u64;
	return PSI_T_UINT64;
}

static inline token_t psi_calc_bin_xor(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.u64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.u64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.u64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.u64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.u64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.u64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.u64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.u64 = v1->u64;
		break;

	case PSI_T_INT128:
		i1.u64 = v1->i128;
		break;

	case PSI_T_UINT128:
		i1.u64 = v1->u128;
		break;

	case PSI_T_FLOAT:
		i1.u64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.u64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.u64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.u64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.u64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.u64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.u64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.u64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.u64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.u64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.u64 = v2->u64;
		break;
	case PSI_T_INT128:
		i2.u64 = v2->i128;
		break;
	case PSI_T_UINT128:
		i2.u64 = v2->u128;
		break;
	case PSI_T_FLOAT:
		i2.u64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.u64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.u64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u64 = i1.u64 ^ i2.u64;
	return PSI_T_UINT64;
}

static inline token_t psi_calc_bin_or(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.u64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.u64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.u64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.u64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.u64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.u64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.u64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.u64 = v1->u64;
		break;

	case PSI_T_INT128:
		i1.u64 = v1->i128;
		break;

	case PSI_T_UINT128:
		i1.u64 = v1->u128;
		break;

	case PSI_T_FLOAT:
		i1.u64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.u64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.u64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.u64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.u64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.u64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.u64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.u64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.u64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.u64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.u64 = v2->u64;
		break;
	case PSI_T_INT128:
		i2.u64 = v2->i128;
		break;
	case PSI_T_UINT128:
		i2.u64 = v2->u128;
		break;
	case PSI_T_FLOAT:
		i2.u64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.u64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.u64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u64 = i1.u64 | i2.u64;
	return PSI_T_UINT64;
}
