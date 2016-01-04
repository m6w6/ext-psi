PSI_TYPES=
PSI_STRUCTS=
PSI_CONSTS=
PSI_REDIRS=
PSI_MACROS=
PSI_DECLS=
PSI_VA_DECLS=

psi_includes() {
	local have_
	have_=`AS_ECHO($ac_header) | $as_tr_cpp`
	cat <<EOF
#ifdef HAVE_$have_
# include <$ac_header>
#endif
EOF
}

AC_DEFUN(PSI_INCLUDES, [AC_INCLUDES_DEFAULT()
`psi_includes`])

AC_DEFUN(PSI_LEMON, [
	AC_ARG_VAR(LEMON, The lemon parser generator of the SQLite project)
	AC_PATH_PROG(LEMON, lemon, ./lemon)
	PHP_SUBST(LEMON)
])

AC_DEFUN([PSI_PKG_CONFIG], [
	if test -z "$PKG_CONFIG"
	then
		AC_PATH_PROG(PKG_CONFIG, pkg-config, false)
	fi
	export PKG_CONFIG_PATH="$PHP_PSI_LIBFFI/lib/pkgconfig:$PHP_PSI_LIBJIT/lib/pkgconfig:$PKG_CONFIG_PATH"
])

AC_DEFUN(PSI_CHECK_SIZEOF, [
	AC_CHECK_SIZEOF($1, [], $2)
	if test "$AS_TR_SH([ac_cv_sizeof_]$1)"; then
		add_int_const "AS_TR_CPP([SIZEOF_]$1)" "$AS_TR_SH([ac_cv_sizeof_]$1)"
	fi
])

AC_DEFUN(PSI_CHECK_OFFSETOF, [
	_AC_CACHE_CHECK_INT(
		[offset of $2 in $1],
		[AS_TR_SH([ac_cv_offsetof_$1_$2])],
		[(long int) (offsetof ($1, $2))],
		[PSI_INCLUDES],
		[AC_MSG_FAILURE([cannot compute offsetof ($1, $2)])]
	)
	AC_DEFINE_UNQUOTED(
		AS_TR_CPP(offsetof_$1_$2),
		$AS_TR_SH([ac_cv_offsetof_$1_$2]),
		[The offset of `$2' in `$1', as computed by offsetof.]
	)
])

AC_DEFUN(PSI_CHECK_LIBJIT, [
	PHP_ARG_WITH(psi-libjit, where to find libjit,
	[  --with-psi-libjit=DIR   PSI: path to libjit], [ ], [ ])
	AC_CACHE_CHECK(for libjit, psi_cv_libjit_dir, [
		for psi_cv_libjit_dir in $PHP_PSI_LIBJIT {/usr{,/local},/opt}{,/libjit}
		do
			if test -e $psi_cv_libjit_dir/include/jit/jit.h
			then
				break
			fi
			psi_cv_libjit_dir=
		done
	])
	if test -n "$psi_cv_libjit_dir"
	then
		PHP_ADD_INCLUDE($psi_cv_libjit_dir/include)
		PHP_ADD_LIBRARY_WITH_PATH(jit, $psi_cv_libjit_dir/$PHP_LIBDIR, PSI_SHARED_LIBADD)
		AC_DEFINE(HAVE_LIBJIT, 1, Have libjit)
	else
		AC_MSG_WARN([Could not find libjit, please provide the base install path])
	fi
])

PHP_ARG_WITH(psi-libffi, where to find libffi,
[  --with-psi-libffi=DIR   PSI: path to libffi], [ ], [ ])
AC_DEFUN(PSI_CHECK_LIBFFI, [
	AC_REQUIRE([PSI_PKG_CONFIG])dnl

	AC_CACHE_CHECK(for libffi through pkg-config, psi_cv_libffi, [
	if $PKG_CONFIG --exists libffi
	then
		psi_cv_libffi=true
	else
		psi_cv_libffi=false
	fi])
	if $psi_cv_libffi
	then
		AC_MSG_CHECKING(for libffi)
		psi_cv_libffi_dir=`$PKG_CONFIG --variable=prefix libffi`
		AC_MSG_RESULT($psi_cv_libffi_dir)
		PHP_EVAL_INCLINE(`$PKG_CONFIG --cflags libffi`)
		PHP_EVAL_LIBLINE(`$PKG_CONFIG --libs libffi`, PSI_SHARED_LIBADD)
		AC_DEFINE(HAVE_LIBFFI, 1, Have libffi)
	else
		AC_CACHE_CHECK(for libffi, psi_cv_libffi_dir, [
		for psi_cv_libffi_dir in $PHP_PSI_LIBFFI {/usr{,/local},/opt}{,/libffi}
		do
			if test -e $psi_cv_libffi_dir/include/ffi/ffi.h
			then
				break
			fi
			psi_cv_libffi_dir=
		done])
		if test -n "$psi_cv_libffi_dir"
		then
			PHP_ADD_INCLUDE($psi_cv_libffi_dir/include/ffi)
			PHP_ADD_LIBRARY_WITH_PATH(ffi, $psi_cv_libffi_dir/$PHP_LIBDIR, PSI_SHARED_LIBADD)
			AC_DEFINE(HAVE_LIBFFI, 1, Have libffi)
		else
			AC_MSG_WARN([Could not find libffi, please provide the base install path])
		fi
	fi
	PHP_CHECK_LIBRARY(ffi, ffi_closure_alloc, [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure_loc, [
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE_LOC, 1, [ ])
		], [], -L$psi_cv_libffi_dir/$PHP_LIBDIR)
		AC_DEFINE(PSI_HAVE_FFI_CLOSURE_ALLOC, 1, [ ])
	], [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure, [
			AC_CHECK_HEADERS(sys/mman.h)
			PHP_CHECK_FUNC(mmap)
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE, 1, [ ])
		], [
		], -L$psi_cv_libffi_dir/$PHP_LIBDIR)
	], -L$psi_cv_libffi_dir/$PHP_LIBDIR)
])

dnl PSI_COMPUTE_STR(variable, string or expression)
AC_DEFUN(PSI_COMPUTE_STR, [
	AC_TRY_RUN(
		PSI_INCLUDES
		[int main() {
			return EOF == fputs($2, fopen("conftest.out", "w"));
		}
	], [
		eval $1=\\\"`cat conftest.out`\\\"
	])
])
