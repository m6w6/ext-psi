#ifndef _PSI_CALC_H
#define _PSI_CALC_H

#include "num_exp.h"
#include "impl_val.h"

int psi_calc_num_exp(num_exp *exp, impl_val *strct, impl_val *res);

static inline zend_long psi_long_num_exp(num_exp *exp, impl_val *strct) {
	impl_val val = {0};

	switch (psi_calc_num_exp(exp, strct, &val)) {
	case PSI_T_UINT8:	return val.u8;
	case PSI_T_UINT16:	return val.u16;
	case PSI_T_UINT32:	return val.u32;
	case PSI_T_UINT64:	return val.u64; /* FIXME */
	case PSI_T_INT8:	return val.i8;
	case PSI_T_INT16:	return val.i16;
	case PSI_T_INT32:	return val.i32;
	case PSI_T_INT64:	return val.i64;
	case PSI_T_FLOAT:	return val.fval;
	case PSI_T_DOUBLE:	return val.dval;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return 0;
}

int psi_calc_add(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);
int psi_calc_sub(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);
int psi_calc_mul(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);
int psi_calc_div(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);

#endif
