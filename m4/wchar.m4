AC_DEFUN(PSI_CHECK_WCHAR, [
	AC_CHECK_HEADERS(wchar.h)

	PSI_TYPE(wint_t, int)

	PSI_CONST(WINT_MIN, int)
	PSI_CONST(WINT_MAX, int)
	PSI_CONST(WEOF, int)

	PSI_DECL(int wprintf, [(wchar_t *format)], vararg)
	PSI_DECL(int fwprintf, [(FILE *stream, wchar_t *format)], vararg)
	PSI_DECL(int swprintf, [(wchar_t *wcs, size_t maxlen, wchar_t *format)], vararg)
])
