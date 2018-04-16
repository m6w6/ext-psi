PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)

case "PHP_EXT_BUILDDIR(psi)" in
""|.) PHP_PSI_BUILDDIR=$PHP_PSI_SRCDIR
	;;
*)    PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)
	;;
esac

m4_foreach(incfile, [
	[ax/ax_check_sign.m4],
	[ax/ax_pthread.m4],
	[psi/psi.m4],
	[psi/psi_const.m4],
	[psi/psi_type.m4]], [
	dnl pecl build
	sinclude([m4/]incfile)
	dnl php-src build
	sinclude([ext/psi/m4/]incfile)
])

PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PSI (PHP System Interface) support])

if test "$PHP_PSI" != no; then

	PHP_ARG_ENABLE(psi-maintainer-mode, whether to enable maintainer mode,
	[  --enable-psi-maintainer-mode
                          PSI: enable maintainer mode
                           . parallel configure
                           . make dependencies
                           . extra debug wrappers], [no], [no])

	PHP_ARG_WITH(psi-libjit, where to find libjit,
	[  --with-psi-libjit=DIR   PSI: path to libjit], [ ], [ ])

	PHP_ARG_WITH(psi-libffi, where to find libffi,
	[  --with-psi-libffi=DIR   PSI: path to libffi], [ ], [ ])

	AC_HEADER_ASSERT dnl # adds --disable-assert to define NDEBUG

	dnl we cannot use AC_USE_SYSTEM_EXTENSIONS here, because we're way too late
	dnl in the game, and we're currently only targeting _GNU_SOURCE for now
	AC_MSG_CHECKING([for _GNU_SOURCE])
	AC_EGREP_CPP([gnu_source_not_defined], [
		#ifndef _GNU_SOURCE
		gnu_source_not_defined
		#endif
	], [
		AC_MSG_RESULT([needs define])
		AC_DEFINE([_GNU_SOURCE], [1], [ ])
	], [
		AC_MSG_RESULT([already defined])
	])

	AC_MSG_CHECKING([psi source dir])
	AC_MSG_RESULT([$PHP_PSI_SRCDIR])
	AC_MSG_CHECKING([psi build dir])
	AC_MSG_RESULT([$PHP_PSI_BUILDDIR])
	
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	AC_FUNC_FNMATCH
	AC_FUNC_MMAP

	PSI_CONFIG_INIT
	PSI_CHECK_STD_TYPES
	PSI_CONFIG_DONE

	PHP_SUBST(PSI_SHARED_LIBADD)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["$SHLIB_SUFFIX_NAME"], DL suffix)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src/calc)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src/types)
	PHP_ADD_INCLUDE($PHP_PSI_BUILDDIR)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src/types)

	PHP_PSI_HEADERS=" \
		src/calc/basic.h src/calc/bin.h src/calc/bool.h src/calc/cast.h \
		src/calc/unary.h src/calc/cmp.h src/calc/oper.h \
		`(cd $PHP_PSI_SRCDIR/src && ls *.h types/*.h)` \
	"
	# parser* should come first
	PHP_PSI_SOURCES=" \
		src/parser_proc.c src/parser.c \
		`(cd $PHP_PSI_SRCDIR && ls src/*.c src/types/*.c \
			| $EGREP -v '^src/parser' \
		)` \
	"
	PHP_PSI_GENERATED=" \
		src/parser_proc.c src/parser.c \
		src/calc/basic.h src/calc/bin.h src/calc/bool.h src/calc/cast.h \
		src/calc/unary.h src/calc/cmp.h src/calc/oper.h \
	"

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_GENERATED)
	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT
	AC_MSG_RESULT()
fi
