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

#include <assert.h>

#include "token.h"

static inline token_t psi_calc_add(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{

	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->i8 + v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->i16 = v1->i8 + v2->u8;
			return PSI_T_INT16;
		case PSI_T_INT16:
			res->i32 = v1->i8 + v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i8 + v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i8 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i8 + v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i8 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i8 + v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i8 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i8 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i8 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i8 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i8 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->u8 + v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->u16 = v1->u8 + v2->u8;
			return PSI_T_UINT16;
		case PSI_T_INT16:
			res->i32 = v1->u8 + v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u8 + v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u8 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u8 + v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u8 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u8 + v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u8 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u8 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u8 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u8 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u8 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->i16 + v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->i32 = v1->i16 + v2->u8;
			return PSI_T_INT32;
		case PSI_T_INT16:
			res->i32 = v1->i16 + v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i16 + v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i16 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i16 + v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i16 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i16 + v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i16 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i16 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i16 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i16 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i16 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->u16 + v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->u32 = v1->u16 + v2->u8;
			return PSI_T_UINT32;
		case PSI_T_INT16:
			res->i32 = v1->u16 + v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u16 + v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u16 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u16 + v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u16 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u16 + v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u16 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u16 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u16 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u16 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u16 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i32 + v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i32 + v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i32 + v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i32 + v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i32 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i32 + v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i32 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i32 + v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i32 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i32 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i32 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i32 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i32 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u32 + v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u32 + v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u32 + v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u32 + v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u32 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u32 + v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u32 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u32 + v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u32 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u32 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u32 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u32 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u32 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i64 + v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i64 + v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i64 + v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i64 + v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i64 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i64 + v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i64 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i64 + v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i64 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i64 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i64 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i64 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i64 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u64 + v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u64 + v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u64 + v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u64 + v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u64 + v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u64 + v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u64 + v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u64 + v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u64 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u64 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u64 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u64 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u64 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		switch (t2) {
		case PSI_T_INT8:
			res->i128 = v1->i128 + v2->i8;
			return PSI_T_INT128;
		case PSI_T_UINT8:
			res->i128 = v1->i128 + v2->u8;
			return PSI_T_INT128;
		case PSI_T_INT16:
			res->i128 = v1->i128 + v2->i16;
			return PSI_T_INT128;
		case PSI_T_UINT16:
			res->i128 = v1->i128 + v2->u16;
			return PSI_T_INT128;
		case PSI_T_INT32:
			res->i128 = v1->i128 + v2->i32;
			return PSI_T_INT128;
		case PSI_T_UINT32:
			res->i128 = v1->i128 + v2->u32;
			return PSI_T_INT128;
		case PSI_T_INT64:
			res->i128 = v1->i128 + v2->i64;
			return PSI_T_INT128;
		case PSI_T_UINT64:
			res->i128 = v1->i128 + v2->u64;
			return PSI_T_INT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i128 + v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i128 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i128 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i128 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i128 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		switch (t2) {
		case PSI_T_INT8:
			res->u128 = v1->u128 + v2->i8;
			return PSI_T_UINT128;
		case PSI_T_UINT8:
			res->u128 = v1->u128 + v2->u8;
			return PSI_T_UINT128;
		case PSI_T_INT16:
			res->u128 = v1->u128 + v2->i16;
			return PSI_T_UINT128;
		case PSI_T_UINT16:
			res->u128 = v1->u128 + v2->u16;
			return PSI_T_UINT128;
		case PSI_T_INT32:
			res->u128 = v1->u128 + v2->i32;
			return PSI_T_UINT128;
		case PSI_T_UINT32:
			res->u128 = v1->u128 + v2->u32;
			return PSI_T_UINT128;
		case PSI_T_INT64:
			res->u128 = v1->u128 + v2->i64;
			return PSI_T_UINT128;
		case PSI_T_UINT64:
			res->u128 = v1->u128 + v2->u64;
			return PSI_T_UINT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->u128 = v1->u128 + v2->i128;
			return PSI_T_UINT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u128 + v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u128 + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u128 + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u128 + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->fval = v1->fval + v2->i8;
			return PSI_T_FLOAT;
		case PSI_T_UINT8:
			res->fval = v1->fval + v2->u8;
			return PSI_T_FLOAT;
		case PSI_T_INT16:
			res->fval = v1->fval + v2->i16;
			return PSI_T_FLOAT;
		case PSI_T_UINT16:
			res->fval = v1->fval + v2->u16;
			return PSI_T_FLOAT;
		case PSI_T_INT32:
			res->fval = v1->fval + v2->i32;
			return PSI_T_FLOAT;
		case PSI_T_UINT32:
			res->fval = v1->fval + v2->u32;
			return PSI_T_FLOAT;
		case PSI_T_INT64:
			res->fval = v1->fval + v2->i64;
			return PSI_T_FLOAT;
		case PSI_T_UINT64:
			res->fval = v1->fval + v2->u64;
			return PSI_T_FLOAT;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->fval = v1->fval + v2->i128;
			return PSI_T_FLOAT;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->fval = v1->fval + v2->u128;
			return PSI_T_FLOAT;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->fval + v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->fval + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->fval + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->dval = v1->dval + v2->i8;
			return PSI_T_DOUBLE;
		case PSI_T_UINT8:
			res->dval = v1->dval + v2->u8;
			return PSI_T_DOUBLE;
		case PSI_T_INT16:
			res->dval = v1->dval + v2->i16;
			return PSI_T_DOUBLE;
		case PSI_T_UINT16:
			res->dval = v1->dval + v2->u16;
			return PSI_T_DOUBLE;
		case PSI_T_INT32:
			res->dval = v1->dval + v2->i32;
			return PSI_T_DOUBLE;
		case PSI_T_UINT32:
			res->dval = v1->dval + v2->u32;
			return PSI_T_DOUBLE;
		case PSI_T_INT64:
			res->dval = v1->dval + v2->i64;
			return PSI_T_DOUBLE;
		case PSI_T_UINT64:
			res->dval = v1->dval + v2->u64;
			return PSI_T_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->dval = v1->dval + v2->i128;
			return PSI_T_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->dval = v1->dval + v2->u128;
			return PSI_T_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->dval = v1->dval + v2->fval;
			return PSI_T_DOUBLE;
		case PSI_T_DOUBLE:
			res->dval = v1->dval + v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->dval + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->ldval = v1->ldval + v2->i8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT8:
			res->ldval = v1->ldval + v2->u8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT16:
			res->ldval = v1->ldval + v2->i16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT16:
			res->ldval = v1->ldval + v2->u16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT32:
			res->ldval = v1->ldval + v2->i32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT32:
			res->ldval = v1->ldval + v2->u32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT64:
			res->ldval = v1->ldval + v2->i64;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT64:
			res->ldval = v1->ldval + v2->u64;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->ldval = v1->ldval + v2->i128;
			return PSI_T_LONG_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->ldval = v1->ldval + v2->u128;
			return PSI_T_LONG_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->ldval = v1->ldval + v2->fval;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_DOUBLE:
			res->ldval = v1->ldval + v2->dval;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->ldval + v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	default:
		assert(0);
		break;
	}

	return 0;
}
static inline token_t psi_calc_sub(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{

	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->i8 - v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->i16 = v1->i8 - v2->u8;
			return PSI_T_INT16;
		case PSI_T_INT16:
			res->i32 = v1->i8 - v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i8 - v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i8 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i8 - v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i8 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i8 - v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i8 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i8 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i8 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i8 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i8 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->u8 - v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->u16 = v1->u8 - v2->u8;
			return PSI_T_UINT16;
		case PSI_T_INT16:
			res->i32 = v1->u8 - v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u8 - v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u8 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u8 - v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u8 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u8 - v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u8 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u8 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u8 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u8 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u8 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->i16 - v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->i32 = v1->i16 - v2->u8;
			return PSI_T_INT32;
		case PSI_T_INT16:
			res->i32 = v1->i16 - v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i16 - v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i16 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i16 - v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i16 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i16 - v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i16 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i16 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i16 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i16 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i16 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->u16 - v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->u32 = v1->u16 - v2->u8;
			return PSI_T_UINT32;
		case PSI_T_INT16:
			res->i32 = v1->u16 - v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u16 - v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u16 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u16 - v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u16 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u16 - v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u16 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u16 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u16 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u16 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u16 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i32 - v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i32 - v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i32 - v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i32 - v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i32 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i32 - v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i32 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i32 - v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i32 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i32 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i32 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i32 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i32 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u32 - v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u32 - v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u32 - v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u32 - v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u32 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u32 - v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u32 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u32 - v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u32 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u32 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u32 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u32 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u32 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i64 - v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i64 - v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i64 - v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i64 - v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i64 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i64 - v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i64 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i64 - v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i64 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i64 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i64 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i64 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i64 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u64 - v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u64 - v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u64 - v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u64 - v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u64 - v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u64 - v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u64 - v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u64 - v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u64 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u64 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u64 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u64 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u64 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		switch (t2) {
		case PSI_T_INT8:
			res->i128 = v1->i128 - v2->i8;
			return PSI_T_INT128;
		case PSI_T_UINT8:
			res->i128 = v1->i128 - v2->u8;
			return PSI_T_INT128;
		case PSI_T_INT16:
			res->i128 = v1->i128 - v2->i16;
			return PSI_T_INT128;
		case PSI_T_UINT16:
			res->i128 = v1->i128 - v2->u16;
			return PSI_T_INT128;
		case PSI_T_INT32:
			res->i128 = v1->i128 - v2->i32;
			return PSI_T_INT128;
		case PSI_T_UINT32:
			res->i128 = v1->i128 - v2->u32;
			return PSI_T_INT128;
		case PSI_T_INT64:
			res->i128 = v1->i128 - v2->i64;
			return PSI_T_INT128;
		case PSI_T_UINT64:
			res->i128 = v1->i128 - v2->u64;
			return PSI_T_INT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i128 - v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i128 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i128 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i128 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i128 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		switch (t2) {
		case PSI_T_INT8:
			res->u128 = v1->u128 - v2->i8;
			return PSI_T_UINT128;
		case PSI_T_UINT8:
			res->u128 = v1->u128 - v2->u8;
			return PSI_T_UINT128;
		case PSI_T_INT16:
			res->u128 = v1->u128 - v2->i16;
			return PSI_T_UINT128;
		case PSI_T_UINT16:
			res->u128 = v1->u128 - v2->u16;
			return PSI_T_UINT128;
		case PSI_T_INT32:
			res->u128 = v1->u128 - v2->i32;
			return PSI_T_UINT128;
		case PSI_T_UINT32:
			res->u128 = v1->u128 - v2->u32;
			return PSI_T_UINT128;
		case PSI_T_INT64:
			res->u128 = v1->u128 - v2->i64;
			return PSI_T_UINT128;
		case PSI_T_UINT64:
			res->u128 = v1->u128 - v2->u64;
			return PSI_T_UINT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->u128 = v1->u128 - v2->i128;
			return PSI_T_UINT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u128 - v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u128 - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u128 - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u128 - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->fval = v1->fval - v2->i8;
			return PSI_T_FLOAT;
		case PSI_T_UINT8:
			res->fval = v1->fval - v2->u8;
			return PSI_T_FLOAT;
		case PSI_T_INT16:
			res->fval = v1->fval - v2->i16;
			return PSI_T_FLOAT;
		case PSI_T_UINT16:
			res->fval = v1->fval - v2->u16;
			return PSI_T_FLOAT;
		case PSI_T_INT32:
			res->fval = v1->fval - v2->i32;
			return PSI_T_FLOAT;
		case PSI_T_UINT32:
			res->fval = v1->fval - v2->u32;
			return PSI_T_FLOAT;
		case PSI_T_INT64:
			res->fval = v1->fval - v2->i64;
			return PSI_T_FLOAT;
		case PSI_T_UINT64:
			res->fval = v1->fval - v2->u64;
			return PSI_T_FLOAT;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->fval = v1->fval - v2->i128;
			return PSI_T_FLOAT;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->fval = v1->fval - v2->u128;
			return PSI_T_FLOAT;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->fval - v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->fval - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->fval - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->dval = v1->dval - v2->i8;
			return PSI_T_DOUBLE;
		case PSI_T_UINT8:
			res->dval = v1->dval - v2->u8;
			return PSI_T_DOUBLE;
		case PSI_T_INT16:
			res->dval = v1->dval - v2->i16;
			return PSI_T_DOUBLE;
		case PSI_T_UINT16:
			res->dval = v1->dval - v2->u16;
			return PSI_T_DOUBLE;
		case PSI_T_INT32:
			res->dval = v1->dval - v2->i32;
			return PSI_T_DOUBLE;
		case PSI_T_UINT32:
			res->dval = v1->dval - v2->u32;
			return PSI_T_DOUBLE;
		case PSI_T_INT64:
			res->dval = v1->dval - v2->i64;
			return PSI_T_DOUBLE;
		case PSI_T_UINT64:
			res->dval = v1->dval - v2->u64;
			return PSI_T_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->dval = v1->dval - v2->i128;
			return PSI_T_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->dval = v1->dval - v2->u128;
			return PSI_T_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->dval = v1->dval - v2->fval;
			return PSI_T_DOUBLE;
		case PSI_T_DOUBLE:
			res->dval = v1->dval - v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->dval - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->ldval = v1->ldval - v2->i8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT8:
			res->ldval = v1->ldval - v2->u8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT16:
			res->ldval = v1->ldval - v2->i16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT16:
			res->ldval = v1->ldval - v2->u16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT32:
			res->ldval = v1->ldval - v2->i32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT32:
			res->ldval = v1->ldval - v2->u32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT64:
			res->ldval = v1->ldval - v2->i64;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT64:
			res->ldval = v1->ldval - v2->u64;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->ldval = v1->ldval - v2->i128;
			return PSI_T_LONG_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->ldval = v1->ldval - v2->u128;
			return PSI_T_LONG_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->ldval = v1->ldval - v2->fval;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_DOUBLE:
			res->ldval = v1->ldval - v2->dval;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->ldval - v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	default:
		assert(0);
		break;
	}

	return 0;
}
static inline token_t psi_calc_mul(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{

	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->i8 * v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->i16 = v1->i8 * v2->u8;
			return PSI_T_INT16;
		case PSI_T_INT16:
			res->i32 = v1->i8 * v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i8 * v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i8 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i8 * v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i8 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i8 * v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i8 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i8 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i8 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i8 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i8 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->u8 * v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->u16 = v1->u8 * v2->u8;
			return PSI_T_UINT16;
		case PSI_T_INT16:
			res->i32 = v1->u8 * v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u8 * v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u8 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u8 * v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u8 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u8 * v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u8 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u8 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u8 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u8 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u8 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->i16 * v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->i32 = v1->i16 * v2->u8;
			return PSI_T_INT32;
		case PSI_T_INT16:
			res->i32 = v1->i16 * v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i16 * v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i16 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i16 * v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i16 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i16 * v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i16 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i16 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i16 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i16 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i16 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->u16 * v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->u32 = v1->u16 * v2->u8;
			return PSI_T_UINT32;
		case PSI_T_INT16:
			res->i32 = v1->u16 * v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u16 * v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u16 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u16 * v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u16 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u16 * v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u16 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u16 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u16 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u16 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u16 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i32 * v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i32 * v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i32 * v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i32 * v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i32 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i32 * v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i32 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i32 * v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i32 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i32 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i32 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i32 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i32 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u32 * v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u32 * v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u32 * v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u32 * v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u32 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u32 * v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u32 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u32 * v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u32 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u32 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u32 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u32 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u32 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i64 * v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i64 * v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i64 * v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i64 * v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i64 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i64 * v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i64 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i64 * v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i64 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i64 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i64 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i64 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i64 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u64 * v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u64 * v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u64 * v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u64 * v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u64 * v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u64 * v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u64 * v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u64 * v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u64 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u64 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u64 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u64 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u64 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		switch (t2) {
		case PSI_T_INT8:
			res->i128 = v1->i128 * v2->i8;
			return PSI_T_INT128;
		case PSI_T_UINT8:
			res->i128 = v1->i128 * v2->u8;
			return PSI_T_INT128;
		case PSI_T_INT16:
			res->i128 = v1->i128 * v2->i16;
			return PSI_T_INT128;
		case PSI_T_UINT16:
			res->i128 = v1->i128 * v2->u16;
			return PSI_T_INT128;
		case PSI_T_INT32:
			res->i128 = v1->i128 * v2->i32;
			return PSI_T_INT128;
		case PSI_T_UINT32:
			res->i128 = v1->i128 * v2->u32;
			return PSI_T_INT128;
		case PSI_T_INT64:
			res->i128 = v1->i128 * v2->i64;
			return PSI_T_INT128;
		case PSI_T_UINT64:
			res->i128 = v1->i128 * v2->u64;
			return PSI_T_INT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i128 * v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i128 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i128 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i128 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i128 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		switch (t2) {
		case PSI_T_INT8:
			res->u128 = v1->u128 * v2->i8;
			return PSI_T_UINT128;
		case PSI_T_UINT8:
			res->u128 = v1->u128 * v2->u8;
			return PSI_T_UINT128;
		case PSI_T_INT16:
			res->u128 = v1->u128 * v2->i16;
			return PSI_T_UINT128;
		case PSI_T_UINT16:
			res->u128 = v1->u128 * v2->u16;
			return PSI_T_UINT128;
		case PSI_T_INT32:
			res->u128 = v1->u128 * v2->i32;
			return PSI_T_UINT128;
		case PSI_T_UINT32:
			res->u128 = v1->u128 * v2->u32;
			return PSI_T_UINT128;
		case PSI_T_INT64:
			res->u128 = v1->u128 * v2->i64;
			return PSI_T_UINT128;
		case PSI_T_UINT64:
			res->u128 = v1->u128 * v2->u64;
			return PSI_T_UINT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->u128 = v1->u128 * v2->i128;
			return PSI_T_UINT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u128 * v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u128 * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u128 * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u128 * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->fval = v1->fval * v2->i8;
			return PSI_T_FLOAT;
		case PSI_T_UINT8:
			res->fval = v1->fval * v2->u8;
			return PSI_T_FLOAT;
		case PSI_T_INT16:
			res->fval = v1->fval * v2->i16;
			return PSI_T_FLOAT;
		case PSI_T_UINT16:
			res->fval = v1->fval * v2->u16;
			return PSI_T_FLOAT;
		case PSI_T_INT32:
			res->fval = v1->fval * v2->i32;
			return PSI_T_FLOAT;
		case PSI_T_UINT32:
			res->fval = v1->fval * v2->u32;
			return PSI_T_FLOAT;
		case PSI_T_INT64:
			res->fval = v1->fval * v2->i64;
			return PSI_T_FLOAT;
		case PSI_T_UINT64:
			res->fval = v1->fval * v2->u64;
			return PSI_T_FLOAT;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->fval = v1->fval * v2->i128;
			return PSI_T_FLOAT;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->fval = v1->fval * v2->u128;
			return PSI_T_FLOAT;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->fval * v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->fval * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->fval * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->dval = v1->dval * v2->i8;
			return PSI_T_DOUBLE;
		case PSI_T_UINT8:
			res->dval = v1->dval * v2->u8;
			return PSI_T_DOUBLE;
		case PSI_T_INT16:
			res->dval = v1->dval * v2->i16;
			return PSI_T_DOUBLE;
		case PSI_T_UINT16:
			res->dval = v1->dval * v2->u16;
			return PSI_T_DOUBLE;
		case PSI_T_INT32:
			res->dval = v1->dval * v2->i32;
			return PSI_T_DOUBLE;
		case PSI_T_UINT32:
			res->dval = v1->dval * v2->u32;
			return PSI_T_DOUBLE;
		case PSI_T_INT64:
			res->dval = v1->dval * v2->i64;
			return PSI_T_DOUBLE;
		case PSI_T_UINT64:
			res->dval = v1->dval * v2->u64;
			return PSI_T_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->dval = v1->dval * v2->i128;
			return PSI_T_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->dval = v1->dval * v2->u128;
			return PSI_T_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->dval = v1->dval * v2->fval;
			return PSI_T_DOUBLE;
		case PSI_T_DOUBLE:
			res->dval = v1->dval * v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->dval * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->ldval = v1->ldval * v2->i8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT8:
			res->ldval = v1->ldval * v2->u8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT16:
			res->ldval = v1->ldval * v2->i16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT16:
			res->ldval = v1->ldval * v2->u16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT32:
			res->ldval = v1->ldval * v2->i32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT32:
			res->ldval = v1->ldval * v2->u32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT64:
			res->ldval = v1->ldval * v2->i64;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT64:
			res->ldval = v1->ldval * v2->u64;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->ldval = v1->ldval * v2->i128;
			return PSI_T_LONG_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->ldval = v1->ldval * v2->u128;
			return PSI_T_LONG_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->ldval = v1->ldval * v2->fval;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_DOUBLE:
			res->ldval = v1->ldval * v2->dval;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->ldval * v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	default:
		assert(0);
		break;
	}

	return 0;
}
static inline token_t psi_calc_div(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{

	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->i8 / v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->i16 = v1->i8 / v2->u8;
			return PSI_T_INT16;
		case PSI_T_INT16:
			res->i32 = v1->i8 / v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i8 / v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i8 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i8 / v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i8 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i8 / v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i8 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i8 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i8 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i8 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i8 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->i16 = v1->u8 / v2->i8;
			return PSI_T_INT16;
		case PSI_T_UINT8:
			res->u16 = v1->u8 / v2->u8;
			return PSI_T_UINT16;
		case PSI_T_INT16:
			res->i32 = v1->u8 / v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u8 / v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u8 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u8 / v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u8 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u8 / v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u8 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u8 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u8 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u8 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u8 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->i16 / v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->i32 = v1->i16 / v2->u8;
			return PSI_T_INT32;
		case PSI_T_INT16:
			res->i32 = v1->i16 / v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->i32 = v1->i16 / v2->u16;
			return PSI_T_INT32;
		case PSI_T_INT32:
			res->i64 = v1->i16 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i16 / v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i16 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i16 / v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i16 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i16 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i16 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i16 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i16 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->i32 = v1->u16 / v2->i8;
			return PSI_T_INT32;
		case PSI_T_UINT8:
			res->u32 = v1->u16 / v2->u8;
			return PSI_T_UINT32;
		case PSI_T_INT16:
			res->i32 = v1->u16 / v2->i16;
			return PSI_T_INT32;
		case PSI_T_UINT16:
			res->u32 = v1->u16 / v2->u16;
			return PSI_T_UINT32;
		case PSI_T_INT32:
			res->i64 = v1->u16 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u16 / v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u16 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u16 / v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u16 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u16 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u16 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u16 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u16 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i32 / v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i32 / v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i32 / v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i32 / v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i32 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i32 / v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i32 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i32 / v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i32 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i32 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i32 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i32 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i32 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u32 / v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u32 / v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u32 / v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u32 / v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u32 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u32 / v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u32 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u32 / v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u32 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u32 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u32 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u32 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u32 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->i64 / v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->i64 = v1->i64 / v2->u8;
			return PSI_T_INT64;
		case PSI_T_INT16:
			res->i64 = v1->i64 / v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->i64 = v1->i64 / v2->u16;
			return PSI_T_INT64;
		case PSI_T_INT32:
			res->i64 = v1->i64 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->i64 = v1->i64 / v2->u32;
			return PSI_T_INT64;
		case PSI_T_INT64:
			res->i64 = v1->i64 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->i64 = v1->i64 / v2->u64;
			return PSI_T_INT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i64 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i64 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i64 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i64 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i64 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->i64 = v1->u64 / v2->i8;
			return PSI_T_INT64;
		case PSI_T_UINT8:
			res->u64 = v1->u64 / v2->u8;
			return PSI_T_UINT64;
		case PSI_T_INT16:
			res->i64 = v1->u64 / v2->i16;
			return PSI_T_INT64;
		case PSI_T_UINT16:
			res->u64 = v1->u64 / v2->u16;
			return PSI_T_UINT64;
		case PSI_T_INT32:
			res->i64 = v1->u64 / v2->i32;
			return PSI_T_INT64;
		case PSI_T_UINT32:
			res->u64 = v1->u64 / v2->u32;
			return PSI_T_UINT64;
		case PSI_T_INT64:
			res->i64 = v1->u64 / v2->i64;
			return PSI_T_INT64;
		case PSI_T_UINT64:
			res->u64 = v1->u64 / v2->u64;
			return PSI_T_UINT64;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->u64 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u64 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u64 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u64 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u64 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		switch (t2) {
		case PSI_T_INT8:
			res->i128 = v1->i128 / v2->i8;
			return PSI_T_INT128;
		case PSI_T_UINT8:
			res->i128 = v1->i128 / v2->u8;
			return PSI_T_INT128;
		case PSI_T_INT16:
			res->i128 = v1->i128 / v2->i16;
			return PSI_T_INT128;
		case PSI_T_UINT16:
			res->i128 = v1->i128 / v2->u16;
			return PSI_T_INT128;
		case PSI_T_INT32:
			res->i128 = v1->i128 / v2->i32;
			return PSI_T_INT128;
		case PSI_T_UINT32:
			res->i128 = v1->i128 / v2->u32;
			return PSI_T_INT128;
		case PSI_T_INT64:
			res->i128 = v1->i128 / v2->i64;
			return PSI_T_INT128;
		case PSI_T_UINT64:
			res->i128 = v1->i128 / v2->u64;
			return PSI_T_INT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->i128 = v1->i128 / v2->i128;
			return PSI_T_INT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->i128 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->i128 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->i128 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->i128 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		switch (t2) {
		case PSI_T_INT8:
			res->u128 = v1->u128 / v2->i8;
			return PSI_T_UINT128;
		case PSI_T_UINT8:
			res->u128 = v1->u128 / v2->u8;
			return PSI_T_UINT128;
		case PSI_T_INT16:
			res->u128 = v1->u128 / v2->i16;
			return PSI_T_UINT128;
		case PSI_T_UINT16:
			res->u128 = v1->u128 / v2->u16;
			return PSI_T_UINT128;
		case PSI_T_INT32:
			res->u128 = v1->u128 / v2->i32;
			return PSI_T_UINT128;
		case PSI_T_UINT32:
			res->u128 = v1->u128 / v2->u32;
			return PSI_T_UINT128;
		case PSI_T_INT64:
			res->u128 = v1->u128 / v2->i64;
			return PSI_T_UINT128;
		case PSI_T_UINT64:
			res->u128 = v1->u128 / v2->u64;
			return PSI_T_UINT128;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->u128 = v1->u128 / v2->i128;
			return PSI_T_UINT128;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->u128 = v1->u128 / v2->u128;
			return PSI_T_UINT128;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->u128 / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->u128 / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->u128 / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->fval = v1->fval / v2->i8;
			return PSI_T_FLOAT;
		case PSI_T_UINT8:
			res->fval = v1->fval / v2->u8;
			return PSI_T_FLOAT;
		case PSI_T_INT16:
			res->fval = v1->fval / v2->i16;
			return PSI_T_FLOAT;
		case PSI_T_UINT16:
			res->fval = v1->fval / v2->u16;
			return PSI_T_FLOAT;
		case PSI_T_INT32:
			res->fval = v1->fval / v2->i32;
			return PSI_T_FLOAT;
		case PSI_T_UINT32:
			res->fval = v1->fval / v2->u32;
			return PSI_T_FLOAT;
		case PSI_T_INT64:
			res->fval = v1->fval / v2->i64;
			return PSI_T_FLOAT;
		case PSI_T_UINT64:
			res->fval = v1->fval / v2->u64;
			return PSI_T_FLOAT;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->fval = v1->fval / v2->i128;
			return PSI_T_FLOAT;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->fval = v1->fval / v2->u128;
			return PSI_T_FLOAT;
#	endif

		case PSI_T_FLOAT:
			res->fval = v1->fval / v2->fval;
			return PSI_T_FLOAT;
		case PSI_T_DOUBLE:
			res->dval = v1->fval / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->fval / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->dval = v1->dval / v2->i8;
			return PSI_T_DOUBLE;
		case PSI_T_UINT8:
			res->dval = v1->dval / v2->u8;
			return PSI_T_DOUBLE;
		case PSI_T_INT16:
			res->dval = v1->dval / v2->i16;
			return PSI_T_DOUBLE;
		case PSI_T_UINT16:
			res->dval = v1->dval / v2->u16;
			return PSI_T_DOUBLE;
		case PSI_T_INT32:
			res->dval = v1->dval / v2->i32;
			return PSI_T_DOUBLE;
		case PSI_T_UINT32:
			res->dval = v1->dval / v2->u32;
			return PSI_T_DOUBLE;
		case PSI_T_INT64:
			res->dval = v1->dval / v2->i64;
			return PSI_T_DOUBLE;
		case PSI_T_UINT64:
			res->dval = v1->dval / v2->u64;
			return PSI_T_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->dval = v1->dval / v2->i128;
			return PSI_T_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->dval = v1->dval / v2->u128;
			return PSI_T_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->dval = v1->dval / v2->fval;
			return PSI_T_DOUBLE;
		case PSI_T_DOUBLE:
			res->dval = v1->dval / v2->dval;
			return PSI_T_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->dval / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->ldval = v1->ldval / v2->i8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT8:
			res->ldval = v1->ldval / v2->u8;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT16:
			res->ldval = v1->ldval / v2->i16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT16:
			res->ldval = v1->ldval / v2->u16;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT32:
			res->ldval = v1->ldval / v2->i32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT32:
			res->ldval = v1->ldval / v2->u32;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_INT64:
			res->ldval = v1->ldval / v2->i64;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_UINT64:
			res->ldval = v1->ldval / v2->u64;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_INT128
		case PSI_T_INT128:
			res->ldval = v1->ldval / v2->i128;
			return PSI_T_LONG_DOUBLE;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			res->ldval = v1->ldval / v2->u128;
			return PSI_T_LONG_DOUBLE;
#	endif

		case PSI_T_FLOAT:
			res->ldval = v1->ldval / v2->fval;
			return PSI_T_LONG_DOUBLE;
		case PSI_T_DOUBLE:
			res->ldval = v1->ldval / v2->dval;
			return PSI_T_LONG_DOUBLE;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->ldval = v1->ldval / v2->ldval;
			return PSI_T_LONG_DOUBLE;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	default:
		assert(0);
		break;
	}

	return 0;
}


static inline token_t psi_calc_mod(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	switch (t1) {
	case PSI_T_INT8:
		i1.i64 = v1->i8;
		break;

	case PSI_T_UINT8:
		i1.i64 = v1->u8;
		break;

	case PSI_T_INT16:
		i1.i64 = v1->i16;
		break;

	case PSI_T_UINT16:
		i1.i64 = v1->u16;
		break;

	case PSI_T_INT32:
		i1.i64 = v1->i32;
		break;

	case PSI_T_UINT32:
		i1.i64 = v1->u32;
		break;

	case PSI_T_INT64:
		i1.i64 = v1->i64;
		break;

	case PSI_T_UINT64:
		i1.i64 = v1->u64;
		break;

#if HAVE_INT128
	case PSI_T_INT128:
		i1.i64 = v1->i128;
		break;

#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		i1.i64 = v1->u128;
		break;

#endif

	case PSI_T_FLOAT:
		i1.i64 = v1->fval;
		break;

	case PSI_T_DOUBLE:
		i1.i64 = v1->dval;
		break;

#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i1.i64 = v1->ldval;
		break;

#endif

	default:
		assert(0);
		break;
	}

	switch (t2) {
	case PSI_T_INT8:
		i2.i64 = v2->i8;
		break;
	case PSI_T_UINT8:
		i2.i64 = v2->u8;
		break;
	case PSI_T_INT16:
		i2.i64 = v2->i16;
		break;
	case PSI_T_UINT16:
		i2.i64 = v2->u16;
		break;
	case PSI_T_INT32:
		i2.i64 = v2->i32;
		break;
	case PSI_T_UINT32:
		i2.i64 = v2->u32;
		break;
	case PSI_T_INT64:
		i2.i64 = v2->i64;
		break;
	case PSI_T_UINT64:
		i2.i64 = v2->u64;
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		i2.i64 = v2->i128;
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		i2.i64 = v2->u128;
		break;
#endif

	case PSI_T_FLOAT:
		i2.i64 = v2->fval;
		break;
	case PSI_T_DOUBLE:
		i2.i64 = v2->dval;
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		i2.i64 = v2->ldval;
		break;
#endif

	default:
		assert(0);
		break;
	}

	res->i64 = i1.i64 % i2.i64;
	return PSI_T_INT64;
}
