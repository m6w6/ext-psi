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
static inline token_t psi_calc_bool_or(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		if (v1->i8)
			goto return_true;
		break;
	case PSI_T_UINT8:
		if (v1->u8)
			goto return_true;
		break;
	case PSI_T_INT16:
		if (v1->i16)
			goto return_true;
		break;
	case PSI_T_UINT16:
		if (v1->u16)
			goto return_true;
		break;
	case PSI_T_INT32:
		if (v1->i32)
			goto return_true;
		break;
	case PSI_T_UINT32:
		if (v1->u32)
			goto return_true;
		break;
	case PSI_T_INT64:
		if (v1->i64)
			goto return_true;
		break;
	case PSI_T_UINT64:
		if (v1->u64)
			goto return_true;
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		if (v1->i128)
			goto return_true;
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		if (v1->u128)
			goto return_true;
		break;
#endif

	case PSI_T_FLOAT:
		if (v1->fval)
			goto return_true;
		break;
	case PSI_T_DOUBLE:
		if (v1->dval)
			goto return_true;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		if (v1->ldval)
			goto return_true;
		break;
#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		if (v2->i8)
			goto return_true;
		break;
	case PSI_T_UINT8:
		if (v2->u8)
			goto return_true;
		break;
	case PSI_T_INT16:
		if (v2->i16)
			goto return_true;
		break;
	case PSI_T_UINT16:
		if (v2->u16)
			goto return_true;
		break;
	case PSI_T_INT32:
		if (v2->i32)
			goto return_true;
		break;
	case PSI_T_UINT32:
		if (v2->u32)
			goto return_true;
		break;
	case PSI_T_INT64:
		if (v2->i64)
			goto return_true;
		break;
	case PSI_T_UINT64:
		if (v2->u64)
			goto return_true;
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		if (v2->i128)
			goto return_true;
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		if (v2->u128)
			goto return_true;
		break;
#endif

	case PSI_T_FLOAT:
		if (v2->fval)
			goto return_true;
		break;
	case PSI_T_DOUBLE:
		if (v2->dval)
			goto return_true;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		if (v2->ldval)
			goto return_true;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u8 = 0;
	return PSI_T_UINT8;

return_true:
	res->u8 = 1;
	return PSI_T_UINT8;
}

static inline token_t psi_calc_bool_and(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		if (!v1->i8)
			goto return_false;
		break;
	case PSI_T_UINT8:
		if (!v1->u8)
			goto return_false;
		break;
	case PSI_T_INT16:
		if (!v1->i16)
			goto return_false;
		break;
	case PSI_T_UINT16:
		if (!v1->u16)
			goto return_false;
		break;
	case PSI_T_INT32:
		if (!v1->i32)
			goto return_false;
		break;
	case PSI_T_UINT32:
		if (!v1->u32)
			goto return_false;
		break;
	case PSI_T_INT64:
		if (!v1->i64)
			goto return_false;
		break;
	case PSI_T_UINT64:
		if (!v1->u64)
			goto return_false;
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		if (!v1->i128)
			goto return_false;
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		if (!v1->u128)
			goto return_false;
		break;
#endif

	case PSI_T_FLOAT:
		if (!v1->fval)
			goto return_false;
		break;
	case PSI_T_DOUBLE:
		if (!v1->dval)
			goto return_false;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		if (!v1->ldval)
			goto return_false;
		break;
#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		if (!v2->i8)
			goto return_false;
		break;
	case PSI_T_UINT8:
		if (!v2->u8)
			goto return_false;
		break;
	case PSI_T_INT16:
		if (!v2->i16)
			goto return_false;
		break;
	case PSI_T_UINT16:
		if (!v2->u16)
			goto return_false;
		break;
	case PSI_T_INT32:
		if (!v2->i32)
			goto return_false;
		break;
	case PSI_T_UINT32:
		if (!v2->u32)
			goto return_false;
		break;
	case PSI_T_INT64:
		if (!v2->i64)
			goto return_false;
		break;
	case PSI_T_UINT64:
		if (!v2->u64)
			goto return_false;
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		if (!v2->i128)
			goto return_false;
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		if (!v2->u128)
			goto return_false;
		break;
#endif

	case PSI_T_FLOAT:
		if (!v2->fval)
			goto return_false;
		break;
	case PSI_T_DOUBLE:
		if (!v2->dval)
			goto return_false;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		if (!v2->ldval)
			goto return_false;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->u8 = 1;
	return PSI_T_UINT8;

return_false:
	res->u8 = 0;
	return PSI_T_UINT8;
}
