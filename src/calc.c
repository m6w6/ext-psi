#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include "php.h"
#include "php_psi.h"
#include "parser.h"
#include "calc.h"

static inline int psi_calc_num_exp_value(num_exp *exp, impl_val *strct, impl_val *res) {
	impl_val *ref, *tmp = NULL;

	switch (exp->t) {
	case PSI_T_NUMBER:
		switch (is_numeric_string(exp->u.numb, strlen(exp->u.numb), (zend_long *) res, (double *) res, 0)) {
		case IS_LONG:
			return PSI_T_INT64;
		case IS_DOUBLE:
			return PSI_T_DOUBLE;
		}
		break;

	case PSI_T_NSNAME:
		switch (exp->u.cnst->type->type) {
		case PSI_T_INT:
			res->i64 = zend_get_constant_str(exp->u.cnst->name, strlen(exp->u.cnst->name))->value.lval;
			return PSI_T_INT64;
		case PSI_T_FLOAT:
			res->dval = zend_get_constant_str(exp->u.cnst->name, strlen(exp->u.cnst->name))->value.dval;
			return PSI_T_DOUBLE;
		default:
			return 0;
		}
		break;

	case PSI_T_ENUM:
		return psi_calc_num_exp(exp->u.enm->num ?: &exp->u.enm->inc, NULL, res);
		break;

	case PSI_T_NAME:
		if (strct) {
			ref = struct_member_ref(exp->u.dvar->arg, strct, &tmp);
		} else {
			ref = exp->u.dvar->arg->let;
		}
		switch (real_decl_type(exp->u.dvar->arg->type)->type) {
		case PSI_T_INT8:
		case PSI_T_UINT8:
		case PSI_T_INT16:
		case PSI_T_UINT16:
		case PSI_T_INT32:
		case PSI_T_UINT32:
		case PSI_T_INT64:
		case PSI_T_UINT64:
			memcpy(res, deref_impl_val(ref, exp->u.dvar), sizeof(*res));
			if (tmp) {
				free(tmp);
			}
			return real_decl_type(exp->u.dvar->arg->type)->type;

		case PSI_T_FLOAT:
		case PSI_T_DOUBLE:
			memcpy(res, deref_impl_val(ref, exp->u.dvar), sizeof(*res));
			if (tmp) {
				free(tmp);
			}
			return real_decl_type(exp->u.dvar->arg->type)->type;

		EMPTY_SWITCH_DEFAULT_CASE();
		}
		break;

	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return  0;
}

int psi_calc_num_exp(num_exp *exp, impl_val *strct, impl_val *res) {
	impl_val num = {0};
	int num_type = psi_calc_num_exp_value(exp, strct, &num);

	if (exp->operand) {
		impl_val tmp = {0};
		int tmp_type = psi_calc_num_exp(exp->operand, strct, &tmp);

		return exp->calculator(num_type, &num, tmp_type, &tmp, res);
	}

	memcpy(res, &num, sizeof(*res));
	return num_type;
}

#define PRIfval "f"
#define PRIdval "lf"
#define PRIldval "Lf"

#define PSI_CALC_OP(var) do { \
	const char *fmt = "calc %" PRI##var ", %" PRI##var ": %" PRI##var "\n"; \
	res->var = PSI_CALC(v1->var, v2->var); \
	if (!res->var) fprintf(stderr, fmt, v1->var, v2->var, res->var); \
} while (0)
#define PSI_CALC_OP2(vres, var1, var2) do { \
	const char *fmt = "calc %" PRI##var1 ", %" PRI##var2 ": %" PRI##vres "\n"; \
	res->vres = PSI_CALC(v1->var1, v2->var2); \
	if (!res->vres) fprintf(stderr, fmt, v1->var1, v2->var2, res->vres); \
} while(0)

#ifdef HAVE_LONG_DOUBLE
#define PSI_CALC_NO_LD
#define PSI_CALC_OP_LD PSI_CALC_OP(ldval)
#define PSI_CALC_OP2_LD2(var1) PSI_CALC_OP2(ldval, var1, ldval)
#define PSI_CALC_OP2_LD1(var2) PSI_CALC_OP2(ldval, ldval, var2)
#else
#define PSI_CALC_NO_LD abort()
#define PSI_CALC_OP_LD PSI_CALC_NO_LD
#define PSI_CALC_OP2_LD2(var) PSI_CALC_NO_LD
#define PSI_CALC_OP2_LD1(var) PSI_CALC_NO_LD
#endif

#define PSI_CALC_FN(op) int psi_calc_##op(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res) \
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
	ZEND_ASSERT(0); \
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
