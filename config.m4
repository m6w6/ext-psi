PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PHP System Interface support])

if test "$PHP_PSI" != no; then
	PHP_CONFIGURE_PART(Configuring PSI)

	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

	sinclude(config.ax_check_sign.m4)
	sinclude(config.psi.m4)
	sinclude(config.psi_errno.m4)
	sinclude(config.psi_glob.m4)
	sinclude(config.psi_stddef.m4)
	sinclude(config.psi_stdint.m4)
	sinclude(config.psi_sys_types.m4)
	sinclude(config.psi_type.m4)

	PSI_LEMON
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	AC_FUNC_FNMATCH
	AC_HEADER_DIRENT

	PSI_CHECK_STD_TYPES
	PSI_CHECK_STDINT
	PSI_CHECK_STDDEF
	PSI_CHECK_SYS_TYPES
	PSI_CHECK_ERRNO
	PSI_CHECK_GLOB

	echo PSI_TYPES=$PSI_TYPES
	echo PSI_MACROS=$PSI_MACROS
	echo PSI_REDIR=$PSI_REDIR
	echo PSI_DECLS=$PSI_DECLS

	PHP_SUBST(PSI_SHARED_LIBADD)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && echo *.h)`
	PHP_PSI_SOURCES="src/parser_proc.c src/parser.c src/module.c src/context.c"
	PHP_PSI_SOURCES="$PHP_PSI_SOURCES src/libjit.c src/libffi.c"

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT

	AC_MSG_RESULT()
fi
