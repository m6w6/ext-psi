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

static inline token_t psi_calc_cmp_eq(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval == v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval == v2->ldval;
			break;
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
			res->u8 = v1->ldval == v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval == v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval == v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval == v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval == v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval == v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval == v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval == v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval == v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval == v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval == v2->ldval;
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
	return PSI_T_UINT8;
}

static inline token_t psi_calc_cmp_ne(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval != v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval != v2->ldval;
			break;
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
			res->u8 = v1->ldval != v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval != v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval != v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval != v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval != v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval != v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval != v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval != v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval != v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval != v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval != v2->ldval;
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
	return PSI_T_UINT8;
}

static inline token_t psi_calc_cmp_lt(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval < v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval < v2->ldval;
			break;
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
			res->u8 = v1->ldval < v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval < v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval < v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval < v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval < v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval < v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval < v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval < v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval < v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval < v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval < v2->ldval;
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
	return PSI_T_UINT8;
}

static inline token_t psi_calc_cmp_gt(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval > v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval > v2->ldval;
			break;
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
			res->u8 = v1->ldval > v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval > v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval > v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval > v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval > v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval > v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval > v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval > v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval > v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval > v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval > v2->ldval;
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
	return PSI_T_UINT8;
}

static inline token_t psi_calc_cmp_le(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval <= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval <= v2->ldval;
			break;
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
			res->u8 = v1->ldval <= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval <= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval <= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval <= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval <= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval <= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval <= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval <= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval <= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval <= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval <= v2->ldval;
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
	return PSI_T_UINT8;
}

static inline token_t psi_calc_cmp_ge(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	switch (t1) {
	case PSI_T_INT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i8 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i8 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i8 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i8 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i8 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i8 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i8 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i8 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i8 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i8 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i8 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT8:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u8 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u8 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u8 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u8 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u8 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u8 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u8 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u8 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u8 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u8 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u8 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i16 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i16 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i16 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i16 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i16 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i16 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i16 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i16 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i16 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i16 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i16 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT16:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u16 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u16 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u16 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u16 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u16 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u16 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u16 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u16 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u16 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u16 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u16 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i32 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i32 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i32 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i32 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i32 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i32 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i32 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i32 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i32 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i32 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i32 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT32:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u32 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u32 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u32 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u32 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u32 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u32 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u32 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u32 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u32 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u32 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u32 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_INT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->i64 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->i64 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->i64 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->i64 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->i64 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->i64 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->i64 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->i64 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->i64 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->i64 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->i64 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_UINT64:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->u64 >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->u64 >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->u64 >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->u64 >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->u64 >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->u64 >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->u64 >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->u64 >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->u64 >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->u64 >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->u64 >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_FLOAT:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->fval >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->fval >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->fval >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->fval >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->fval >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->fval >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->fval >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->fval >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->fval >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->fval >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->fval >= v2->ldval;
			break;
#	endif

		default:
			assert(0);
			break;
		}
		break;
	case PSI_T_DOUBLE:
		switch (t2) {
		case PSI_T_INT8:
			res->u8 = v1->dval >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->dval >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->dval >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->dval >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->dval >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->dval >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->dval >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->dval >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->dval >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->dval >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->dval >= v2->ldval;
			break;
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
			res->u8 = v1->ldval >= v2->i8;
			break;
		case PSI_T_UINT8:
			res->u8 = v1->ldval >= v2->u8;
			break;
		case PSI_T_INT16:
			res->u8 = v1->ldval >= v2->i16;
			break;
		case PSI_T_UINT16:
			res->u8 = v1->ldval >= v2->u16;
			break;
		case PSI_T_INT32:
			res->u8 = v1->ldval >= v2->i32;
			break;
		case PSI_T_UINT32:
			res->u8 = v1->ldval >= v2->u32;
			break;
		case PSI_T_INT64:
			res->u8 = v1->ldval >= v2->i64;
			break;
		case PSI_T_UINT64:
			res->u8 = v1->ldval >= v2->u64;
			break;
		case PSI_T_FLOAT:
			res->u8 = v1->ldval >= v2->fval;
			break;
		case PSI_T_DOUBLE:
			res->u8 = v1->ldval >= v2->dval;
			break;
#	if HAVE_LONG_DOUBLE
		case PSI_T_LONG_DOUBLE:
			res->u8 = v1->ldval >= v2->ldval;
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
	return PSI_T_UINT8;
}
