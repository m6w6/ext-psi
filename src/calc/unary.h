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
static inline token_t psi_calc_minus(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	(void) t2;
	(void) v2;

	switch (t1) {
	case PSI_T_INT8:
		res->i8 = -v1->i8;
		break;
	case PSI_T_UINT8:
		res->u8 = -v1->u8;
		break;
	case PSI_T_INT16:
		res->i16 = -v1->i16;
		break;
	case PSI_T_UINT16:
		res->u16 = -v1->u16;
		break;
	case PSI_T_INT32:
		res->i32 = -v1->i32;
		break;
	case PSI_T_UINT32:
		res->u32 = -v1->u32;
		break;
	case PSI_T_INT64:
		res->i64 = -v1->i64;
		break;
	case PSI_T_UINT64:
		res->u64 = -v1->u64;
		break;
	case PSI_T_INT128:
		res->i128 = -v1->i128;
		break;
	case PSI_T_UINT128:
		res->u128 = -v1->u128;
		break;
	case PSI_T_FLOAT:
		res->fval = -v1->fval;
		break;
	case PSI_T_DOUBLE:
		res->dval = -v1->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		res->ldval = -v1->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}
	return t1;
}


static inline token_t psi_calc_bool_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	(void) t2;
	(void) v2;

	switch (t1) {
	case PSI_T_INT8:
		res->u8 = !v1->i8;
		break;
	case PSI_T_UINT8:
		res->u8 = !v1->u8;
		break;
	case PSI_T_INT16:
		res->u8 = !v1->i16;
		break;
	case PSI_T_UINT16:
		res->u8 = !v1->u16;
		break;
	case PSI_T_INT32:
		res->u8 = !v1->i32;
		break;
	case PSI_T_UINT32:
		res->u8 = !v1->u32;
		break;
	case PSI_T_INT64:
		res->u8 = !v1->i64;
		break;
	case PSI_T_UINT64:
		res->u8 = !v1->u64;
		break;
	case PSI_T_INT128:
		res->u8 = !v1->i128;
		break;
	case PSI_T_UINT128:
		res->u8 = !v1->u128;
		break;
	case PSI_T_FLOAT:
		res->u8 = !v1->fval;
		break;
	case PSI_T_DOUBLE:
		res->u8 = !v1->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		res->u8 = !v1->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}
	return PSI_T_UINT8;
}


static inline token_t psi_calc_bin_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1;

	(void) t2;
	(void) v2;

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

	res->u64 = ~i1.u64;
	return PSI_T_UINT64;
}