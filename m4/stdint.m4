PSI_CHECK_STDINT() {
	AC_CHECK_HEADERS(stdint.h)

	PSI_TYPE(int_least8_t, int)
	PSI_TYPE(int_least16_t, int)
	PSI_TYPE(int_least32_t, int)
	PSI_TYPE(int_least64_t, int)
	PSI_TYPE(uint_least8_t, uint)
	PSI_TYPE(uint_least16_t, uint)
	PSI_TYPE(uint_least32_t, uint)
	PSI_TYPE(uint_least64_t, uint)
	PSI_TYPE(int_fast8_t, int)
	PSI_TYPE(int_fast16_t, int)
	PSI_TYPE(int_fast32_t, int)
	PSI_TYPE(int_fast64_t, int)
	PSI_TYPE(uint_fast8_t, uint)
	PSI_TYPE(uint_fast16_t, uint)
	PSI_TYPE(uint_fast32_t, uint)
	PSI_TYPE(uint_fast64_t, uint)
	PSI_TYPE(intptr_t, int)
	PSI_TYPE(uintptr_t, uint)
	PSI_TYPE(intmax_t, int)
	PSI_TYPE(uintmax_t, uint)

	PSI_CONST(INT8_MIN, int)
	PSI_CONST(INT8_MAX, int)
	PSI_CONST(UINT8_MAX, int)
	PSI_CONST(INT16_MIN, int)
	PSI_CONST(INT16_MAX, int)
	PSI_CONST(UINT16_MAX, int)
	PSI_CONST(INT32_MIN, int)
	PSI_CONST(INT32_MAX, int)
	PSI_CONST(UINT32_MAX, int)
	PSI_CONST(INT64_MIN, int)
	PSI_CONST(INT64_MAX, int)
	PSI_CONST(UINT64_MAX, int)

	PSI_CONST(INT_LEAST8_MIN, int)
	PSI_CONST(INT_LEAST8_MAX, int)
	PSI_CONST(UINT_LEAST8_MAX, int)
	PSI_CONST(INT_LEAST16_MIN, int)
	PSI_CONST(INT_LEAST16_MAX, int)
	PSI_CONST(UINT_LEAST16_MAX, int)
	PSI_CONST(INT_LEAST32_MIN, int)
	PSI_CONST(INT_LEAST32_MAX, int)
	PSI_CONST(UINT_LEAST32_MAX, int)
	PSI_CONST(INT_LEAST64_MIN, int)
	PSI_CONST(INT_LEAST64_MAX, int)
	PSI_CONST(UINT_LEAST64_MAX, int)

	PSI_CONST(INT_FAST8_MIN, int)
	PSI_CONST(INT_FAST8_MAX, int)
	PSI_CONST(UINT_FAST8_MAX, int)
	PSI_CONST(INT_FAST16_MIN, int)
	PSI_CONST(INT_FAST16_MAX, int)
	PSI_CONST(UINT_FAST16_MAX, int)
	PSI_CONST(INT_FAST32_MIN, int)
	PSI_CONST(INT_FAST32_MAX, int)
	PSI_CONST(UINT_FAST32_MAX, int)
	PSI_CONST(INT_FAST64_MIN, int)
	PSI_CONST(INT_FAST64_MAX, int)
	PSI_CONST(UINT_FAST64_MAX, int)

	PSI_CONST(INTPTR_MIN, int)
	PSI_CONST(INTPTR_MAX, int)
	PSI_CONST(UINTPTR_MAX, int)
	PSI_CONST(INTMAX_MIN, int)
	PSI_CONST(INTMAX_MAX, int)
	PSI_CONST(UINTMAX_MAX, int)
}
