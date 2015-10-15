PHP_ARG_WITH(psi, whether to enable psi support,
[  --with-psi[[=path to libjit]]
                          Enable PHP System Interface support])

if test "$PHP_PSI" != "no"; then
	AC_ARG_VAR(LEMON, The lemon parser generator of the SQLite project)
	AC_PATH_PROG(LEMON, lemon, ./lemon)
	PHP_SUBST(LEMON)

	AC_CACHE_CHECK(for libjit install root, PSI_cv_LIBJIT_DIR, [
	for PSI_cv_LIBJIT_DIR in {/usr{,/local},/opt}{,libjit}
	do
		if test -e $PSI_cv_LIBJIT_DIR/include/jit/jit.h
		then
			break
		fi
		PSI_cv_LIBJIT_DIR=
	done])
	if test -z "$PSI_cv_LIBJIT_DIR"
	then
		AC_MSG_ERROR([Could not find libjit, please provide the base install path])
	fi

	PHP_ADD_INCLUDE($PSI_cv_LIBJIT_DIR/include)
	PHP_ADD_LIBRARY_WITH_PATH(jit, $PSI_cv_LIBJIT_DIR/$PHP_LIBDIR, PSI_SHARED_LIBADD)
	PHP_SUBST(PSI_SHARED_LIBADD)

	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && echo *.h)`
	PHP_PSI_SOURCES=`(cd $PHP_PSI_SRCDIR && echo src/*.c)`
	PHP_PSI_SOURCES=`(echo $PHP_PSI_SOURCES src/parser.c src/parser_proc.c | xargs -n1 | sort | uniq)`

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT
fi
