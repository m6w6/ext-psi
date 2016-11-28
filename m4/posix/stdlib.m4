PSI_CHECK_STDLIB() {
	AC_CHECK_HEADERS(stdlib.h)

	PSI_STRUCT(div_t, [
		int quot,
		int rem
	])
	PSI_STRUCT(ldiv_t, [
		long quot,
		long rem
	])
	PSI_STRUCT(lldiv_t, [
		long long quot,
		long long rem
	])

	PSI_CONST(EXIT_FAILURE, int)
	PSI_CONST(EXIT_SUCCESS, int)
	PSI_CONST(RAND_MAX, int)
	
	PSI_MACRO(int MB_CUR_MAX)

	PSI_DECL(void _Exit, [(int status)])
	PSI_DECL(void abort, [()])
	PSI_DECL(int abs, [(int n)])
	PSI_DECL(double atof, [(char *str)])
	PSI_DECL(int atoi, [(char *str)])
	PSI_DECL(long atol, [(char *str)])
	PSI_DECL(div_t div, [(int numerator, int denominator)])
	PSI_DECL(double drand48, [()])
	PSI_DECL(double erand48, [(unsigned short xsubi@<:@3@:>@)])
	PSI_DECL(void exit, [(int status)])
	PSI_DECL(void free, [(void *ptr)])
	PSI_DECL(char *getenv, [(char *var)])
	PSI_DECL(int grantpt, [(int fd)])
	PSI_DECL(char *initstate, [(unsigned int seed, char *state, size_t n)])
	PSI_DECL(long jrand48, [(unsigned short xsubi@<:@3@:>@)])
	PSI_DECL(long labs, [(long l)])
	PSI_DECL(void lcong48, [(unsigned short param@<:@7@:>@)])
	PSI_DECL(ldiv_t ldiv, [(long numerator, long denominator)])
	PSI_DECL(lldiv_t lldiv, [(long long numerator, long long denominator)])
	PSI_DECL(long lrand48, [()])
	PSI_DECL(int mblen, [(const char *s, size_t n)])
	PSI_DECL(size_t mbstowcs, [(wchar_t *dest, char *src, size_t n)])
	PSI_DECL(int mbtowc, [(wchar_t *pwc, char *s, size_t n)])
	PSI_DECL(char *mkdtemp, [(char *template)])
	PSI_DECL(char *mkdstemp, [(char *template)])
	PSI_DECL(long mrand48, [()])
	PSI_DECL(long nrand48, [(unsigned short xsubi@<:@3@:>@)])
	PSI_DECL(int posix_openpt, [(int flags)])
	PSI_DECL(char *ptsname, [(int fd)])
	PSI_DECL(char *pstname_r, [(int fd, char *buf, size_t buflen)])
	PSI_DECL(int putenv, [(char *var)])
	PSI_DECL(int rand, [()])
	PSI_DECL(int rand_r, [(unsigned *seed_p)])
	PSI_DECL(long random, [()])
	PSI_DECL(char *realpath, [(char *path, char *resolved)])
	PSI_DECL(unsigned short *seed48, [(unsigned short seed16v@<:@3@:>@)])
	PSI_DECL(int setenv, [(char *var, char *val, int overwrite)])
	PSI_DECL(void setkey, [(char *key)], [], [-lcrypt])
	PSI_DECL(char *setstate, [(char *state)])
	PSI_DECL(void srand, [(unsigned seed)])
	PSI_DECL(void srand48, [(long seed)])
	PSI_DECL(void srandom, [(unsigned seed)])
	PSI_DECL(double strtod, [(char *nptr, char **endptr)])
	PSI_DECL(float strtof, [(char *nptr, char **endptr)])
	PSI_DECL(long strtol, [(char *nptr, char **endptr, int base)])
	PSI_DECL(long double strtold, [(const char *nptr, char **endptr)])
	PSI_DECL(unsigned long strtoul, [(char *nptr, char **endptr, int base)])
	PSI_DECL(int system, [(char *command)])
	PSI_DECL(int unlockpt, [(int fd)])
	PSI_DECL(int unsetenv, [(char *var)])
	PSI_DECL(size_t wcstombs, [(char *dest, wchar_t *src, size_t n)])
	PSI_DECL(int wctomb, [(char *s, wchar_t wc)])
}