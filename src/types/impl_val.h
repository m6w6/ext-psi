#ifndef _PSI_TYPES_IMPL_VAL_H
#define _PSI_TYPES_IMPL_VAL_H

#include "Zend/zend_types.h"

typedef union impl_val {
	char cval;
	int8_t i8;
	uint8_t u8;
	short sval;
	int16_t i16;
	uint16_t u16;
	int ival;
	int32_t i32;
	uint32_t u32;
	long lval;
	int64_t i64;
	uint64_t u64;
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
} impl_val;


#endif
