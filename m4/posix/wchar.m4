PSI_CHECK_WCHAR() {

	PSI_TYPE(wint_t, int)
	PSI_STRUCT(mbstate_t)

	PSI_CONST(WINT_MIN, int)
	PSI_CONST(WINT_MAX, int)
	PSI_CONST(WEOF, int)

	PSI_DECL(wint_t btowc, [(int c)])
	PSI_DECL(wint_t fgetwc, [(FILE *stream)])
	PSI_DECL(wchar_t *fgetws, [(wchar_t *ws, int n, FILE *stream)])
	PSI_DECL(wint_t fputwc, [(wchar_t c, FILE *stream)])
	PSI_DECL(int fputws, [(const wchar_t *ws, FILE *stream)])
	PSI_DECL(int fwide, [(FILE *stream, int mode)])
	PSI_DECL(int fwprintf, [(FILE *stream, const wchar_t *format)], vararg)
	PSI_DECL(int fwscanf, [(FILE *stream, const wchar_t *format)], vararg)
	PSI_DECL(wint_t getwc, [(FILE *stream)])
	PSI_DECL(wint_t getwchar, [(void)])
	PSI_DECL(size_t mbrlen, [(const char *s, size_t n, mbstate_t *ps)])
	PSI_DECL(size_t mbrtowc, [(wchar_t *pwc, const char *s, size_t n, mbstate_t *ps)])
	PSI_DECL(int mbsinit, [(const mbstate_t *ps)])
	PSI_DECL(size_t mbsnrtowcs, [(wchar_t *dst, const char **src, size_t nms, size_t len, mbstate_t *ps)])
	PSI_DECL(size_t mbsrtowcs, [(wchar_t *dst, const char **src, size_t len, mbstate_t *ps)])
	PSI_DECL(FILE *open_wmemstream, [(wchar_t **ptr, size_t *size)])
	PSI_DECL(wint_t putwc, [(wchar_t wc, FILE *stream)])
	PSI_DECL(wint_t putwchar, [(wchar_t wc)])
	PSI_DECL(int swprintf, [(wchar_t *wcs, size_t maxlen, const wchar_t *format)], vararg)
	PSI_DECL(int swscanf, [(const wchar_t *ws, const wchar_t *format)], vararg)
	PSI_DECL(wint_t ungetwc, [(wint_t wc, FILE *stream)])
	PSI_DECL(wchar_t *wcpcpy, [(wchar_t *dest, const wchar_t *src)])
	PSI_DECL(wchar_t *wcpncpy, [(wchar_t *dest, const wchar_t *src, size_t n)])
	PSI_DECL(size_t wcrtomb, [(char *s, wchar_t wc, mbstate_t *ps)])
	PSI_DECL(int wcscasecmp, [(const wchar_t *s1, const wchar_t *s2)])
	PSI_DECL(int wcscasecmp_l, [(const wchar_t *s1, const wchar_t *s2, locale_t loc)])
	PSI_DECL(wchar_t *wcscat, [(wchar_t *dest, const wchar_t *src)])
	PSI_DECL(wchar_t *wcschr, [(const wchar_t *wcs, wchar_t wc)])
	PSI_DECL(int wcscmp, [(const wchar_t *s1, const wchar_t *s2)])
	PSI_DECL(int wcscoll, [(const wchar_t *s1, const wchar_t *s2)])
	PSI_DECL(int wcscoll_l, [(const wchar_t *s1, const wchar_t *s2, locale_t loc)])
	PSI_DECL(wchar_t *wcscpy, [(wchar_t *dest, const wchar_t *src)])
	PSI_DECL(size_t wcscspn, [(const wchar_t *wcs, const wchar_t *reject)])
	PSI_DECL(wchar_t *wcsdup, [(const wchar_t *s)])
	PSI_DECL(size_t wcsftime, [(wchar_t *wcs, size_t maxsize, const wchar_t *format, const struct tm *timeptr)])
	PSI_DECL(size_t wcslen, [(const wchar_t *s)])
	PSI_DECL(int wcsncasecmp, [(const wchar_t *s1, const wchar_t *s2, size_t n)])
	PSI_DECL(int wcsncasecmp_l, [(const wchar_t *s1, const wchar_t *s2, size_t n, locale_t loc)])
	PSI_DECL(wchar_t *wcsncat, [(wchar_t *dest, const wchar_t *src, size_t n)])
	PSI_DECL(int wcsncmp, [(const wchar_t *s1, const wchar_t *s2, size_t n)])
	PSI_DECL(wchar_t *wcsncpy, [(wchar_t *dest, const wchar_t *src, size_t n)])
	PSI_DECL(size_t wcsnlen, [(const wchar_t *s, size_t maxlen)])
	PSI_DECL(size_t wcsnrtombs, [(char *dest, const wchar_t **src, size_t nwc, size_t len, mbstate_t *ps)])
	PSI_DECL(wchar_t *wcspbrk, [(const wchar_t *wcs, const wchar_t *accept)])
	PSI_DECL(wchar_t *wcsrchr, [(const wchar_t *wcs, wchar_t wc)])
	PSI_DECL(size_t wcsrtombs, [(char *dest, const wchar_t **src, size_t n, mbstate_t *ps)])
	PSI_DECL(size_t wcsspn, [(const wchar_t *wcs, const wchar_t *accept)])
	PSI_DECL(wchar_t *wcsstr, [(const wchar_t *haystack, const wchar_t *needle)])
	PSI_DECL(double wcstod, [(const wchar_t *nptr, wchar_t **endptr)])
	PSI_DECL(float wcstof, [(const wchar_t *nptr, wchar_t **endptr)])
	PSI_DECL(wchar_t *wcstok, [(wchar_t *wcs, const wchar_t *delim, wchar_t **ptr)])
	PSI_DECL(long wcstol, [(const wchar_t *nptr, wchar_t **endptr, int base)])
	PSI_DECL(long double wcstold, [(const wchar_t *nptr, wchar_t **endptr)])
	PSI_DECL(long long wcstoll, [(const wchar_t *nptr, wchar_t **endptr, int base)])
	PSI_DECL(unsigned long wcstoul, [(const wchar_t *nptr, wchar_t **endptr, int base)])
	PSI_DECL(unsigned long long wcstoull, [(const wchar_t *nptr, wchar_t **endptr, int base)])
	PSI_DECL(int wcswidth, [(const wchar_t *s, size_t n)])
	PSI_DECL(size_t wcsxfrm, [(wchar_t *ws1, const wchar_t *ws2, size_t n)])
	PSI_DECL(size_t wcsxfrm_l, [(wchar_t *ws1, const wchar_t *ws2, size_t n, locale_t loc)])
	PSI_DECL(int wctob, [(wint_t c)])
	PSI_DECL(int wcwidth, [(wchar_t c)])
	PSI_DECL(wchar_t *wmemchr, [(const wchar_t *s, wchar_t c, size_t n)])
	PSI_DECL(int wmemcmp, [(const wchar_t *s1, const wchar_t *s2, size_t n)])
	PSI_DECL(wchar_t *wmemcpy, [(wchar_t *dest, const wchar_t *src, size_t n)])
	PSI_DECL(wchar_t *wmemmove, [(wchar_t *dest, const wchar_t *src, size_t n)])
	PSI_DECL(wchar_t *wmemset, [(wchar_t *wcs, wchar_t wc, size_t n)])
	PSI_DECL(int wprintf, [(const wchar_t *format)], vararg)
	PSI_DECL(int wscanf, [(const wchar_t *format)], vararg)
}
