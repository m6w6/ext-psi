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

#ifndef PSI_TYPES_IMPL_VAL_H
#define PSI_TYPES_IMPL_VAL_H

#include "Zend/zend_types.h"
#include "Zend/zend_API.h"

typedef struct zend_fcall {
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
} zend_fcall;

typedef union impl_val {
	int8_t i8;
	uint8_t u8;
	int16_t i16;
	uint16_t u16;
	int32_t i32;
	uint32_t u32;
	int64_t i64;
	uint64_t u64;
#if HAVE_INT128
	int128_t i128;
	uint128_t u128;
#endif
	float fval;
	double dval;
#ifdef HAVE_LONG_DOUBLE
	long double ldval;
#endif
	union {
		zend_bool bval;
		zend_long lval;
		zend_string *str;
		zend_fcall *cb;
	} zend;
	void *ptr;
#ifdef PHP_DEBUG
	char _dbg[sizeof(void *)];
#endif
} impl_val;

#ifndef linux
#	define isinfl isinf
#	define isnanl isnan
#endif
#if HAVE_LONG_DOUBLE
#	define CASE_IMPLVAL_LD_DUMP(dump, ival, with_suffix) \
	case PSI_T_LONG_DOUBLE: \
		if (isinfl(ival.ldval)) { \
			PSI_DUMP(dump, "\\INF"); \
		} else if (isnanl(ival.ldval)) { \
			PSI_DUMP(dump, "\\NAN"); \
		} else { \
			/* bug in long double formatting of xbuf_fmt_conv? */ \
			char buf[0x100] = {0}; \
			snprintf(buf, sizeof(buf) - 1, "%" PRIldval, ival.ldval); \
			PSI_DUMP(dump, "%s%s", buf, (with_suffix) ? "L" : ""); \
		} \
		break
#else
#	define CASE_IMPLVAL_LD_DUMP(dump, ival, with_suffix)
#endif

#define CASE_IMPLVAL_FLOAT_DUMP(dump, ival, with_suffix) \
	CASE_IMPLVAL_LD_DUMP(dump, ival, with_suffix); \
	case PSI_T_FLOAT: \
		if (isinf(ival.dval)) { \
			PSI_DUMP(dump, "\\INF"); \
		} else if (isnan(ival.dval)) { \
			PSI_DUMP(dump, "\\NAN"); \
		} else { \
			PSI_DUMP(dump, "%" PRIfval "%s", ival.fval, (with_suffix) ? "F" : ""); \
		} \
		break; \
	case PSI_T_DOUBLE: \
		if (isinf(ival.dval)) { \
			PSI_DUMP(dump, "\\INF"); \
		} else if (isnan(ival.dval)) { \
			PSI_DUMP(dump, "\\NAN"); \
		} else { \
			PSI_DUMP(dump, "%" PRIdval, ival.dval); \
		} \
		break

#define CASE_IMPLVAL_INT_DUMP(dump, ival, with_suffix) \
	case PSI_T_INT8: \
		PSI_DUMP(dump, "%" PRId8, ival.i8); \
		break; \
	case PSI_T_UINT8: \
		PSI_DUMP(dump, "%" PRIu8, ival.u8); \
		break; \
	case PSI_T_INT16: \
		PSI_DUMP(dump, "%" PRId16, ival.i16); \
		break; \
	case PSI_T_UINT16: \
		PSI_DUMP(dump, "%" PRIu16, ival.u16); \
		break; \
	case PSI_T_INT32: \
		PSI_DUMP(dump, "%" PRId32, ival.i32); \
		break; \
	case PSI_T_UINT32: \
		PSI_DUMP(dump, "%" PRIu32 "%s", ival.u32, (with_suffix) ? "U" : ""); \
		break; \
	case PSI_T_INT64: \
		PSI_DUMP(dump, "%" PRId64 "%s", ival.i64, (with_suffix) ? "L" : ""); \
		break; \
	case PSI_T_UINT64: \
		PSI_DUMP(dump, "%" PRIu64 "%s", ival.u64, (with_suffix) ? "UL" : ""); \
		break

#define CASE_IMPLVAL_NUM_DUMP(dump, ival, with_suffix) \
	CASE_IMPLVAL_INT_DUMP(dump, ival, with_suffix); \
	CASE_IMPLVAL_FLOAT_DUMP(dump, ival, with_suffix)

#endif
