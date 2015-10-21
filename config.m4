PHP_ARG_ENABLE(psi, whether to enable psi support,
[  --enable-psi            Enable PHP System Interface support])
PHP_ARG_WITH(psi-libjit, where to find libjit,
[  --with-psi-libjit=DIR   PSI: path to libjit])
PHP_ARG_WITH(psi-libffi, where to find libjit,
[  --with-psi-libffi=DIR   PSI: path to libffi])

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
			PHP_CHECK_LIBRARY(ffi, ffi_closure_alloc, [
				AC_DEFINE(PSI_HAVE_FFI_CLOSURE_ALLOC, 1, [ ])
			], [
			], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
			PHP_CHECK_LIBRARY(ffi, ffi_closure_free, [
				AC_DEFINE(PSI_HAVE_FFI_CLOSURE_FREE, 1, [ ])
			], [
			], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
			PHP_CHECK_LIBRARY(ffi, ffi_prep_closure, [
				AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE, 1, [ ])
			], [
			], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
			PHP_ADD_INCLUDE($PSI_cv_LIBFFI_DIR/include/ffi)
			PHP_ADD_LIBRARY_WITH_PATH(ffi, $PSI_cv_LIBFFI_DIR/$PHP_LIBDIR, PSI_SHARED_LIBADD)
		else
			AC_MSG_WARN([Could not find libffi, please provide the base install path])
		fi
	fi

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
