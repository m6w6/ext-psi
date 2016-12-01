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
#include "calc.h"

#define PSI_CALC_CAST_SET(in_type, in_val, op, out_val, out_var) \
switch (in_type) { \
case PSI_T_INT8:		(out_val)->out_var op (in_val)->i8;		break; \
case PSI_T_UINT8:		(out_val)->out_var op (in_val)->u8;		break; \
case PSI_T_INT16:		(out_val)->out_var op (in_val)->i16;	break; \
case PSI_T_UINT16:		(out_val)->out_var op (in_val)->u16;	break; \
case PSI_T_INT32:		(out_val)->out_var op (in_val)->i32;	break; \
case PSI_T_UINT32:		(out_val)->out_var op (in_val)->u32;	break; \
case PSI_T_INT64:		(out_val)->out_var op (in_val)->i64;	break; \
case PSI_T_UINT64:		(out_val)->out_var op (in_val)->u64;	break; \
case PSI_T_FLOAT:		(out_val)->out_var op (in_val)->fval;	break; \
case PSI_T_DOUBLE:		(out_val)->out_var op (in_val)->dval;	break; \
case PSI_T_LONG_DOUBLE:	(out_val)->out_var op (in_val)->ldval;	break; \
default: \
	assert(0); \
}

#define PSI_CALC_CAST(in_type, in_val, op, out_type, out_val) \
switch (out_type) { \
case PSI_T_INT8:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, i8)		break; \
case PSI_T_UINT8:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, u8)		break; \
case PSI_T_INT16:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, i16)	break; \
case PSI_T_UINT16:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, u16)	break; \
case PSI_T_INT32:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, i32)	break; \
case PSI_T_UINT32:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, u32)	break; \
case PSI_T_INT64:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, i64)	break; \
case PSI_T_UINT64:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, u64)	break; \
case PSI_T_FLOAT:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, fval)	break; \
case PSI_T_DOUBLE:		PSI_CALC_CAST_SET(in_type, in_val, op, out_val, dval)	break; \
case PSI_T_LONG_DOUBLE:	PSI_CALC_CAST_SET(in_type, in_val, op, out_val, ldval)	break; \
default: \
	assert(0); \
}

#define PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, out_var) \
switch (in_type) { \
case PSI_T_INT8:		(out_val)->out_var op (in_val)->i8;		break; \
case PSI_T_UINT8:		(out_val)->out_var op (in_val)->u8;		break; \
case PSI_T_INT16:		(out_val)->out_var op (in_val)->i16;	break; \
case PSI_T_UINT16:		(out_val)->out_var op (in_val)->u16;	break; \
case PSI_T_INT32:		(out_val)->out_var op (in_val)->i32;	break; \
case PSI_T_UINT32:		(out_val)->out_var op (in_val)->u32;	break; \
case PSI_T_INT64:		(out_val)->out_var op (in_val)->i64;	break; \
case PSI_T_UINT64:		(out_val)->out_var op (in_val)->u64;	break; \
default: \
	assert(0); \
}
#define PSI_CALC_CAST_INT(in_type, in_val, op, out_type, out_val) \
switch (out_type) { \
case PSI_T_INT8:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, i8)		break; \
case PSI_T_UINT8:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, u8)		break; \
case PSI_T_INT16:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, i16)	break; \
case PSI_T_UINT16:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, u16)	break; \
case PSI_T_INT32:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, i32)	break; \
case PSI_T_UINT32:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, u32)	break; \
case PSI_T_INT64:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, i64)	break; \
case PSI_T_UINT64:		PSI_CALC_CAST_SET_INT(in_type, in_val, op, out_val, u64)	break; \
default: \
	assert(0); \
}

void psi_calc_cast(token_t in_type, impl_val *in_val, token_t out_type, impl_val *out_val)
{
	PSI_CALC_CAST(in_type, in_val, =, out_type, out_val)
}

#if 0
#define PSI_CALC_OP(var) do { \
	const char *fmt = "calc %" PRI##var ", %" PRI##var ": %" PRI##var "\n"; \
	res->var = PSI_CALC(v1->var, v2->var); \
	if (!res->var && (v1->var || v2->var)) fprintf(stderr, fmt, v1->var, v2->var, res->var); \
} while (0)
#define PSI_CALC_OP2(vres, var1, var2) do { \
	const char *fmt = "calc %" PRI##var1 ", %" PRI##var2 ": %" PRI##vres "\n"; \
	res->vres = PSI_CALC(v1->var1, v2->var2); \
	if (!res->vres && (v1->var1 || v2->var2)) fprintf(stderr, fmt, v1->var1, v2->var2, res->vres); \
} while(0)
#else
#define PSI_CALC_OP(var) res->var = PSI_CALC(v1->var, v2->var)
#define PSI_CALC_OP2(vres, var1, var2) res->vres = PSI_CALC(v1->var1, v2->var2)
#endif

#ifdef HAVE_LONG_DOUBLE
# define PSI_CALC_NO_LD
# define PSI_CALC_OP_LD PSI_CALC_OP(ldval)
# define PSI_CALC_OP2_LD2(var1) PSI_CALC_OP2(ldval, var1, ldval)
# define PSI_CALC_OP2_LD1(var2) PSI_CALC_OP2(ldval, ldval, var2)
#else
# define PSI_CALC_NO_LD abort()
# define PSI_CALC_OP_LD PSI_CALC_NO_LD
# define PSI_CALC_OP2_LD2(var) PSI_CALC_NO_LD
# define PSI_CALC_OP2_LD1(var) PSI_CALC_NO_LD
#endif

#define PSI_CALC_FN(op) token_t psi_calc_##op(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res) \
{ \
	if (t1 == t2) { \
		switch (t1) { \
		case PSI_T_FLOAT:	PSI_CALC_OP(fval);	break; \
		case PSI_T_DOUBLE:	PSI_CALC_OP(dval);	break; \
		case PSI_T_LONG_DOUBLE: PSI_CALC_OP_LD;	break; \
		case PSI_T_INT8:	PSI_CALC_OP(i8);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP(u8);	break; \
		case PSI_T_INT16:	PSI_CALC_OP(i16);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP(u16);	break; \
		case PSI_T_INT32:	PSI_CALC_OP(i32);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP(u32);	break; \
		case PSI_T_INT64:	PSI_CALC_OP(i64);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP(u64);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t1; \
	} else if (t1 == PSI_T_DOUBLE) { \
		switch (t2) { \
		case PSI_T_LONG_DOUBLE: PSI_CALC_OP2_LD2(dval);		return t2; \
		case PSI_T_FLOAT:	PSI_CALC_OP2(dval, dval, fval);	break; \
		case PSI_T_INT8:	PSI_CALC_OP2(dval, dval, i8);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2(dval, dval, u8);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2(dval, dval, i16);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2(dval, dval, u16);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2(dval, dval, i32);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2(dval, dval, u32);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2(dval, dval, i64);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2(dval, dval, u64);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t1; \
	} else if (t2 == PSI_T_DOUBLE) { \
		switch (t1) { \
		case PSI_T_LONG_DOUBLE: PSI_CALC_OP2_LD1(dval);		return t1; \
		case PSI_T_FLOAT:	PSI_CALC_OP2(dval, fval, dval);	break; \
		case PSI_T_INT8:	PSI_CALC_OP2(dval, i8, dval);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2(dval, u8, dval);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2(dval, i16, dval);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2(dval, u16, dval);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2(dval, i32, dval);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2(dval, u32, dval);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2(dval, i64, dval);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2(dval, u64, dval);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t2; \
	} else if (t1 == PSI_T_LONG_DOUBLE) { \
		PSI_CALC_NO_LD; \
		switch (t2) { \
		case PSI_T_DOUBLE:	PSI_CALC_OP2_LD1(dval);	break; \
		case PSI_T_FLOAT:	PSI_CALC_OP2_LD1(fval);	break; \
		case PSI_T_INT8:	PSI_CALC_OP2_LD1(i8);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2_LD1(u8);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2_LD1(i16);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2_LD1(u16);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2_LD1(i32);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2_LD1(u32);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2_LD1(i64);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2_LD1(u64);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t1; \
	} else if (t2 == PSI_T_LONG_DOUBLE) { \
		PSI_CALC_NO_LD; \
		switch (t1) { \
		case PSI_T_DOUBLE:	PSI_CALC_OP2_LD2(dval);	break; \
		case PSI_T_FLOAT:	PSI_CALC_OP2_LD2(fval);	break; \
		case PSI_T_INT8:	PSI_CALC_OP2_LD2(i8);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2_LD2(u8);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2_LD2(i16);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2_LD2(u16);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2_LD2(i32);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2_LD2(u32);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2_LD2(i64);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2_LD2(u64);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t2; \
	} else if (t1 == PSI_T_FLOAT) { \
		switch (t2) { \
		case PSI_T_LONG_DOUBLE: PSI_CALC_OP2_LD2(fval);		return t2; \
		case PSI_T_DOUBLE:	PSI_CALC_OP2(dval, fval, dval);	return t2; \
		case PSI_T_INT8:	PSI_CALC_OP2(fval, fval, i8);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2(fval, fval, u8);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2(fval, fval, i16);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2(fval, fval, u16);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2(fval, fval, i32);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2(fval, fval, u32);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2(fval, fval, i64);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2(fval, fval, u64);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t1; \
	} else if (t2 == PSI_T_FLOAT) { \
		switch (t1) { \
		case PSI_T_LONG_DOUBLE: PSI_CALC_OP2_LD1(fval);		return t1; \
		case PSI_T_DOUBLE:	PSI_CALC_OP2(dval, dval, fval);	return t1; \
		case PSI_T_INT8:	PSI_CALC_OP2(fval, i8, fval);	break; \
		case PSI_T_UINT8:	PSI_CALC_OP2(fval, u8, fval);	break; \
		case PSI_T_INT16:	PSI_CALC_OP2(fval, i16, fval);	break; \
		case PSI_T_UINT16:	PSI_CALC_OP2(fval, u16, fval);	break; \
		case PSI_T_INT32:	PSI_CALC_OP2(fval, i32, fval);	break; \
		case PSI_T_UINT32:	PSI_CALC_OP2(fval, u32, fval);	break; \
		case PSI_T_INT64:	PSI_CALC_OP2(fval, i64, fval);	break; \
		case PSI_T_UINT64:	PSI_CALC_OP2(fval, u64, fval);	break; \
		EMPTY_SWITCH_DEFAULT_CASE(); \
		} \
		return t2; \
	} else { \
		int64_t sval1 = v1->i64, sval2 = v2->i64; \
		uint64_t uval1 = v1->u64, uval2 = v2->u64; \
		switch (t1) { \
		case PSI_T_INT8:	sval1 >>= 8; \
		case PSI_T_INT16:	sval1 >>= 8; \
		case PSI_T_INT32:	sval1 >>= 8; \
		case PSI_T_INT64: \
			switch (t2) { \
			case PSI_T_INT8:	sval2 >>= 8; \
			case PSI_T_INT16:	sval2 >>= 8; \
			case PSI_T_INT32:	sval2 >>= 8; \
			case PSI_T_INT64: \
				res->i64 = PSI_CALC(sval1 , sval2); \
				return PSI_T_INT64; \
			case PSI_T_UINT8:	uval2 >>= 8; \
			case PSI_T_UINT16:	uval2 >>= 8; \
			case PSI_T_UINT32:	uval2 >>= 8; \
			case PSI_T_UINT64: \
				res->i64 = PSI_CALC(sval1, uval2); \
				return PSI_T_INT64; \
			} \
			break; \
		case PSI_T_UINT8:	uval1 >>= 8; \
		case PSI_T_UINT16:	uval1 >>= 8; \
		case PSI_T_UINT32:	uval1 >>= 8; \
		case PSI_T_UINT64: \
			switch (t2) { \
			case PSI_T_INT8:	sval2 >>= 8; \
			case PSI_T_INT16:	sval2 >>= 8; \
			case PSI_T_INT32:	sval2 >>= 8; \
			case PSI_T_INT64: \
				res->i64 = PSI_CALC(uval1, sval2); \
				return PSI_T_INT64; \
			case PSI_T_UINT8:	uval2 >>= 8; \
			case PSI_T_UINT16:	uval2 >>= 8; \
			case PSI_T_UINT32:	uval2 >>= 8; \
			case PSI_T_UINT64: \
				res->u64 = PSI_CALC(uval1, uval2); \
				return PSI_T_UINT64; \
			} \
			break; \
		} \
	} \
	assert(0); \
	return 0; \
}

#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) + (var2)
PSI_CALC_FN(add)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) * (var2)
PSI_CALC_FN(mul)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) - (var2)
PSI_CALC_FN(sub)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) / (var2)
PSI_CALC_FN(div)
#undef PSI_CALC

token_t psi_calc_mod(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1, i2;

	PSI_CALC_CAST(t1, v1, =, PSI_T_INT64, &i1);
	PSI_CALC_CAST(t2, v2, =, PSI_T_INT64, &i2);

	res->i64 = i1.i64 % i2.i64;

	return PSI_T_INT64;
}

#define PSI_CALC_BIT_FN(op) token_t psi_calc_##op(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res) \
{ \
	impl_val i1, i2; \
	PSI_CALC_CAST(t1, v1, =, PSI_T_UINT64, &i1); \
	PSI_CALC_CAST(t2, v2, =, PSI_T_UINT64, &i2); \
	res->u64 = PSI_CALC(i1.u64, i2.u64); \
	return PSI_T_UINT64; \
}

#define PSI_CALC(var1, var2) (var1) << (var2)
PSI_CALC_BIT_FN(bin_lshift)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) >> (var2)
PSI_CALC_BIT_FN(bin_rshift)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) & (var2)
PSI_CALC_BIT_FN(bin_and)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) ^ (var2)
PSI_CALC_BIT_FN(bin_xor)
#undef PSI_CALC
#define PSI_CALC(var1, var2) (var1) | (var2)
PSI_CALC_BIT_FN(bin_or)
#undef PSI_CALC

token_t psi_calc_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	(void) t2;
	(void) v2;

	PSI_CALC_CAST(t1, v1, =!, t1, res);
	return t1;
}

token_t psi_calc_bin_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res)
{
	impl_val i1;

	(void) t2;
	(void) v2;

	PSI_CALC_CAST(t1, v1, =, PSI_T_UINT64, &i1);
	PSI_CALC_CAST_INT(t1, &i1, =~, t1, res);
	return t1;
}
