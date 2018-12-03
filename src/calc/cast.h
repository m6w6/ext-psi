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

static inline void psi_calc_cast(token_t in_type, impl_val *in_val, token_t out_type, impl_val *out_val)
{
	switch (out_type) {
	case PSI_T_INT8:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->i8 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->i8 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->i8 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->i8 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->i8 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->i8 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->i8 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->i8 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->i8 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->i8 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->i8 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->i8 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->i8 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->u8 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->u8 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->u8 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->u8 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->u8 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->u8 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->u8 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->u8 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->u8 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->u8 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->u8 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->u8 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->u8 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->i16 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->i16 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->i16 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->i16 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->i16 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->i16 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->i16 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->i16 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->i16 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->i16 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->i16 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->i16 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->i16 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->u16 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->u16 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->u16 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->u16 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->u16 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->u16 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->u16 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->u16 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->u16 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->u16 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->u16 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->u16 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->u16 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->i32 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->i32 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->i32 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->i32 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->i32 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->i32 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->i32 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->i32 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->i32 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->i32 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->i32 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->i32 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->i32 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->u32 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->u32 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->u32 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->u32 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->u32 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->u32 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->u32 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->u32 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->u32 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->u32 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->u32 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->u32 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->u32 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->i64 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->i64 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->i64 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->i64 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->i64 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->i64 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->i64 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->i64 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->i64 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->i64 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->i64 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->i64 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->i64 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->u64 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->u64 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->u64 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->u64 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->u64 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->u64 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->u64 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->u64 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->u64 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->u64 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->u64 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->u64 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->u64 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_INT128
	case PSI_T_INT128:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->i128 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->i128 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->i128 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->i128 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->i128 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->i128 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->i128 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->i128 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->i128 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->i128 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->i128 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->i128 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->i128 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

#if HAVE_UINT128
	case PSI_T_UINT128:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->u128 = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->u128 = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->u128 = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->u128 = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->u128 = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->u128 = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->u128 = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->u128 = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->u128 = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->u128 = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->u128 = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->u128 = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->u128 = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#endif

	case PSI_T_FLOAT:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->fval = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->fval = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->fval = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->fval = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->fval = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->fval = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->fval = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->fval = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->fval = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->fval = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->fval = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->fval = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->fval = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->dval = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->dval = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->dval = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->dval = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->dval = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->dval = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->dval = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->dval = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->dval = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->dval = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->dval = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->dval = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->dval = in_val->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
#if HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		switch (in_type) {
		case PSI_T_INT8:
			out_val->ldval = in_val->i8;
			break;
		case PSI_T_UINT8:
			out_val->ldval = in_val->u8;
			break;
		case PSI_T_INT16:
			out_val->ldval = in_val->i16;
			break;
		case PSI_T_UINT16:
			out_val->ldval = in_val->u16;
			break;
		case PSI_T_INT32:
			out_val->ldval = in_val->i32;
			break;
		case PSI_T_UINT32:
			out_val->ldval = in_val->u32;
			break;
		case PSI_T_INT64:
			out_val->ldval = in_val->i64;
			break;
		case PSI_T_UINT64:
			out_val->ldval = in_val->u64;
			break;
#	if HAVE_INT128
		case PSI_T_INT128:
			out_val->ldval = in_val->i128;
			break;
#	endif

#	if HAVE_UINT128
		case PSI_T_UINT128:
			out_val->ldval = in_val->u128;
			break;
#	endif

		case PSI_T_FLOAT:
			out_val->ldval = in_val->fval;
			break;
		case PSI_T_DOUBLE:
			out_val->ldval = in_val->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			out_val->ldval = in_val->ldval;
			break;
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
}

