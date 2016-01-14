PSI_CHECK_STDDEF() {
    AC_CHECK_HEADERS(stddef.h)
    PSI_TYPE(ptrdiff_t, int)
    PSI_CONST(PTRDIFF_MIN, int)
    PSI_CONST(PTRDIFF_MAX, int)
    PSI_TYPE(size_t, uint)
    PSI_CONST(SIZE_MAX, int)
    PSI_TYPE(wchar_t, int)
    PSI_CONST(WCHAR_MIN, int)
    PSI_CONST(WCHAR_MAX, int)
}
