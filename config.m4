m4_foreach(incfile, [
	[ax/ax_check_compile_flag.m4],
	[ax/ax_check_sign.m4],
	[ax/ax_pthread.m4],
	[psi/psi.m4],
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
                           . make dependencies], [no], [no])
    PHP_ARG_ENABLE(psi-threaded-parser, whether to enable threaded parser,
    [  --enable-psi-threaded-parser
                          PSI: enable threads for startup parsing], [yes], [no])

	PHP_ARG_WITH(psi-libjit, where to find libjit,
	[  --with-psi-libjit=DIR   PSI: path to libjit], [ ], [ ])

	PHP_ARG_WITH(psi-libffi, where to find libffi,
	[  --with-psi-libffi=DIR   PSI: path to libffi], [ ], [ ])

	AC_HEADER_ASSERT dnl # adds --disable-assert to define NDEBUG

	PSI_CONFIG_INIT
	
	PSI_CHECK_MAINTAINER_MODE
	PSI_CHECK_THREADED_PARSER

	dnl we cannot use AC_USE_SYSTEM_EXTENSIONS here, because we're way too late
	dnl in the game, and we're currently only targeting _GNU_SOURCE for now
	PSI_CHECK_GNU_SOURCE
	PSI_CHECK_CPP
	PSI_CHECK_STD_TYPES
	
	AC_HEADER_DIRENT
	AC_FUNC_FNMATCH
	AC_FUNC_MMAP
	AC_CHECK_FUNCS([mknodat eaccess])

	PSI_CHECK_PTHREAD
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	PSI_CONFIG_DONE

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["$SHLIB_SUFFIX_NAME"], DL suffix)

	PHP_SUBST(PSI_SHARED_LIBADD)
	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_ADD_MAKEFILE_FRAGMENT
	AC_MSG_RESULT()
fi
