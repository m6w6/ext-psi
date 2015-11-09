PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PHP System Interface support])
PHP_ARG_WITH(psi-libjit, where to find libjit,
[  --with-psi-libjit=DIR   PSI: path to libjit], [], no)
PHP_ARG_WITH(psi-libffi, where to find libjit,
[  --with-psi-libffi=DIR   PSI: path to libffi], [], no)

if test "$PHP_PSI" != "no"; then
	AC_ARG_VAR(LEMON, The lemon parser generator of the SQLite project)
	AC_PATH_PROG(LEMON, lemon, ./lemon)
	PHP_SUBST(LEMON)

	if test -z "$PKG_CONFIG"
	then
		AC_PATH_PROG(PKG_CONFIG, pkg-config, false)
	fi

	export PKG_CONFIG_PATH="$PHP_PSI_LIBFFI/lib/pkgconfig:$PHP_PSI_LIBJIT/lib/pkgconfig:$PKG_CONFIG_PATH"

	AC_CACHE_CHECK(for libffi through pkg-config, PSI_cv_LIBFFI, [
	if $PKG_CONFIG --exists libffi
	then
		PSI_cv_LIBFFI=true
	else
		PSI_cv_LIBFFI=false
	fi])
	if $PSI_cv_LIBFFI
	then
		AC_MSG_CHECKING(for libffi)
		PSI_cv_LIBFFI_DIR=`$PKG_CONFIG --variable=prefix libffi`
		AC_MSG_RESULT($PSI_cv_LIBFFI_DIR)
		PHP_EVAL_INCLINE(`$PKG_CONFIG --cflags libffi`)
		PHP_EVAL_LIBLINE(`$PKG_CONFIG --libs libffi`, PSI_SHARED_LIBADD)
	else
		AC_CACHE_CHECK(for libffi, PSI_cv_LIBFFI_DIR, [
		for PSI_cv_LIBFFI_DIR in $PHP_PSI_LIBFFI {/usr{,/local},/opt}{,/libffi}
		do
			if test -e $PSI_cv_LIBFFI_DIR/include/ffi/ffi.h
			then
				break
			fi
			PSI_cv_LIBFFI_DIR=
		done])
		if test -n "$PSI_cv_LIBFFI_DIR"
		then
			PHP_ADD_INCLUDE($PSI_cv_LIBFFI_DIR/include/ffi)
			PHP_ADD_LIBRARY_WITH_PATH(ffi, $PSI_cv_LIBFFI_DIR/$PHP_LIBDIR, PSI_SHARED_LIBADD)
		else
			AC_MSG_WARN([Could not find libffi, please provide the base install path])
		fi
	fi
	PHP_CHECK_LIBRARY(ffi, ffi_closure_alloc, [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure_loc, [
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE_LOC, 1, [ ])
		], [], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
		AC_DEFINE(PSI_HAVE_FFI_CLOSURE_ALLOC, 1, [ ])
	], [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure, [
			AC_CHECK_HEADERS(sys/mman.h)
			PHP_CHECK_FUNC(mmap)
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE, 1, [ ])
		], [
		], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
	], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)

	AC_CACHE_CHECK(for libjit, PSI_cv_LIBJIT_DIR, [
	for PSI_cv_LIBJIT_DIR in $PHP_PSI_LIBJIT {/usr{,/local},/opt}{,/libjit}
	do
		if test -e $PSI_cv_LIBJIT_DIR/include/jit/jit.h
		then
			break
		fi
		PSI_cv_LIBJIT_DIR=
	done])
	if test -n "$PSI_cv_LIBJIT_DIR"
	then
		PHP_ADD_INCLUDE($PSI_cv_LIBJIT_DIR/include)
		PHP_ADD_LIBRARY_WITH_PATH(jit, $PSI_cv_LIBJIT_DIR/$PHP_LIBDIR, PSI_SHARED_LIBADD)
	else
		AC_MSG_WARN([Could not find libjit, please provide the base install path])
	fi

	PHP_SUBST(PSI_SHARED_LIBADD)

	PSI_TYPES=""
	dnl PSI_TYPE(type name, basic type, whether to check alignmnet)
	AC_DEFUN(PSI_TYPE, [
		AC_CHECK_SIZEOF($1)
		if test "$3" && test "$3" != "no"
		then
			AC_CHECK_ALIGNOF($1)
		fi
		if test "$2" && test "$ac_cv_sizeof_[]$1" -gt 0; then
			psi_type_bits=`expr ${AS_TR_SH(ac_cv_sizeof_[]$1)} \* 8`
			PSI_TYPES="{PSI_T_[]translit($2,a-z,A-Z)[]${psi_type_bits}, \""$2[]${psi_type_bits}[]_t"\", \""$1"\"}, $PSI_TYPES"
		fi
	])
	

	PSI_CONSTS=""
	dnl PSI_COMPUTE_STR(variable, string or expression, includes)
	AC_DEFUN(PSI_COMPUTE_STR, [
		AC_TRY_RUN([
			$3
			int main() {
				return EOF == fputs($2, fopen("conftest.out", "w"));
			}
		], [
			eval $1=\\\"`cat conftest.out`\\\"
		])
	])
	
	dnl PSI_CONST(const name, type, headers to include)
	AC_DEFUN(PSI_CONST, [
		AC_MSG_CHECKING(value of $1)
		PSI_INCLUDES=
		if test "$3"
		then
			for i in $3
			do
				PSI_INCLUDES="$PSI_INCLUDES
#include <$i>"
			done
		fi
		case $2 in
		str*|quoted_str*)
			PSI_COMPUTE_STR(psi_const_val, $1, AC_INCLUDES_DEFAULT()$PSI_INCLUDES)
			if test "$psi_const_val"; then
				PSI_CONSTS="{PSI_T_STRING, \"string\", \"$1\", $psi_const_val, PSI_T_QUOTED_STRING}, $PSI_CONSTS"
			fi
			;;
		*)
			AC_COMPUTE_INT(psi_const_val, $1, AC_INCLUDES_DEFAULT()$PSI_INCLUDES)
			if test "$psi_const_val"; then
				PSI_CONSTS="{PSI_T_INT, \"int\", \"$1\", \"$psi_const_val\", PSI_T_NUMBER}, $PSI_CONSTS"
			fi
			;;
		esac

		AC_MSG_RESULT($psi_const_val)
	])

	AC_DEFUN([AX_CHECK_SIGN], [
		typename=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g"`
		AC_CACHE_CHECK([whether $1 is signed], ax_cv_decl_${typename}_signed, [
				AC_TRY_COMPILE([$4],
						[ int foo @<:@ 1 - 2 * !((($1) -1) < 0) @:>@ ],
						[ eval "ax_cv_decl_${typename}_signed=\"yes\"" ],
						[ eval "ax_cv_decl_${typename}_signed=\"no\"" ])])
		symbolname=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g" | tr "a-z" "A-Z"`
		if eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"yes\""; then
				$2
		elif eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"no\""; then
				$3
		fi
	])

	PSI_TYPE(char, int)
	PSI_TYPE(short, int)
	PSI_TYPE(int, int)
	PSI_TYPE(long, int)
	PSI_TYPE(float)
	PSI_TYPE(double)
	PSI_TYPE(void *)

	dnl stddef.h
	PSI_TYPE(ptrdiff_t, int)
	PSI_TYPE(size_t, uint)
	AC_CHECK_TYPE(wchar_t, [
		AX_CHECK_SIGN(wchar_t, psi_wchar_t=int, psi_wchar_t=uint)
		PSI_TYPE(wchar_t, $psi_wchar_t)
	])

	dnl stdio.h
	PSI_CONST(BUFSIZ, int)
	PSI_CONST(_IOFBF, int)
	PSI_CONST(_IOLBF, int)
	PSI_CONST(_IONBF, int)
	PSI_CONST(SEEK_CUR, int)
	PSI_CONST(SEEK_END, int)
	PSI_CONST(SEEK_SET, int)
	PSI_CONST(FILENAME_MAX, int)
	PSI_CONST(FOPEN_MAX, int)
	PSI_CONST(TMP_MAX, int)
	PSI_CONST(EOF, int)
	PSI_CONST(P_tmpdir, string)
	PSI_CONST(L_ctermid, int)
	PSI_CONST(L_tmpnam, int)
	dnl stdlib.h
	PSI_CONST(EXIT_FAILURE, int)
	PSI_CONST(EXIT_SUCCESS, int)
	PSI_CONST(RAND_MAX, int)
	PSI_CONST(MB_CUR_MAX, int)
	dnl sys/time.h
	PSI_CONST(ITIMER_REAL, int, sys/time.h)
	PSI_CONST(ITIMER_VIRTUAL, int, sys/time.h)
	PSI_CONST(ITIMER_PROF, int, sys/time.h)
	dnl sys/types.h
	PSI_TYPE(blkcnt_t, int)
	PSI_TYPE(blksize_t, int)
	PSI_TYPE(clock_t, int)
	PSI_TYPE(clockid_t, int)
	PSI_TYPE(dev_t, int)
	PSI_TYPE(fsblkcnt_t, uint)
	PSI_TYPE(fsfilcnt_t, uint)
	PSI_TYPE(gid_t, int)
	PSI_TYPE(id_t, int)
	PSI_TYPE(ino_t, uint)
	PSI_TYPE(key_t, int)
	PSI_TYPE(mode_t, int)
	PSI_TYPE(nlink_t, int)
	PSI_TYPE(off_t, int)
	PSI_TYPE(pid_t, int)
	PSI_TYPE(ssize_t, int)
	PSI_TYPE(suseconds_t, int)
	PSI_TYPE(time_t, int)
	PSI_TYPE(timer_t, int)
	PSI_TYPE(uid_t)

	AC_DEFINE_UNQUOTED(PHP_PSI_TYPES, $PSI_TYPES, Predefined types)
	AC_DEFINE_UNQUOTED(PHP_PSI_CONSTS, $PSI_CONSTS, Predefined constants)

	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && echo *.h)`
	PHP_PSI_SOURCES="src/parser_proc.c src/parser.c src/validator.c src/module.c src/context.c"
	PHP_PSI_SOURCES="$PHP_PSI_SOURCES src/libjit.c src/libffi.c"

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT
fi
