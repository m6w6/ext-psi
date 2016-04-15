PSI_CHECK_STDDEF() {
    AC_CHECK_HEADERS(stddef.h)
    PSI_TYPE(ptrdiff_t, int)
    PSI_CONST(PTRDIFF_MIN, int)
    PSI_CONST(PTRDIFF_MAX, int)
    PSI_TYPE(size_t, uint)
    PSI_CONST(SIZE_MAX, int)
    PSI_TYPE(wchar_t, int)
    if PSI_SH_TEST_SIZEOF(wchar_t); then :; else
    	# some platforms fail to provide wchar_t in stddef.h
    	unset ac_cv_sizeof_wchar_t
    	unset ax_cv_decl_wchar_t_signed
    	AC_CHECK_HEADERS(wchar.h)
    	PSI_TYPE(wchar_t, int)
    fi
    PSI_CONST(WCHAR_MIN, int)
    PSI_CONST(WCHAR_MAX, int)
}
