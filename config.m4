PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PHP System Interface support])

PHP_ARG_WITH(psi-libjit, where to find libjit,
[  --with-psi-libjit=DIR   PSI: path to libjit], [ ], [ ])

PHP_ARG_WITH(psi-libffi, where to find libffi,
[  --with-psi-libffi=DIR   PSI: path to libffi], [ ], [ ])

PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

m4_foreach(incfile, [
	[ax_check_sign.m4],
	[psi.m4],
	[psi_type.m4],
	[psi_const.m4],
	[psi_decl.m4],
	[psi_macro.m4],
	[psi_struct.m4],
	[errno.m4],
	[glob.m4],
	[locale.m4],
	[stddef.m4],
	[stdio.m4],
	[stdint.m4],
	[stdlib.m4],
	[sys_select.m4],
	[sys_socket.m4],
	[sys_stat.m4],
	[sys_time.m4],
	[sys_times.m4],
	[sys_types.m4],
	[sys_uio.m4],
	[sys_utsname.m4],
	[netdb.m4],
	[netinet_in.m4],
	[netinet_tcp.m4],
	[poll.m4],
	[syslog.m4],
	[time.m4],
	[wchar.m4],
	[wctype.m4]], [
	dnl pecl build
	sinclude([m4/]incfile)
	dnl php-src build
	sinclude([ext/psi/m4/]incfile)
])

if test "$PHP_PSI" != no; then
	PHP_CONFIGURE_PART(Configuring PSI)

	PSI_LEMON
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	AC_FUNC_FNMATCH
	AC_HEADER_DIRENT

	PSI_CONFIG_INIT
	PSI_CHECK_STD_TYPES
	PSI_CHECK_STDINT
	PSI_CHECK_STDDEF
	PSI_CHECK_SYS_TYPES
	PSI_CHECK_ERRNO
	PSI_CHECK_GLOB
	PSI_CHECK_LOCALE
	PSI_CHECK_STDIO
	PSI_CHECK_STDLIB
	PSI_CHECK_TIME
	PSI_CHECK_SYS_SELECT
	PSI_CHECK_SYS_SOCKET
	PSI_CHECK_SYS_TIME
	PSI_CHECK_SYS_TIMES
	PSI_CHECK_SYS_STAT
	PSI_CHECK_SYS_UIO
	PSI_CHECK_SYS_UTSNAME
	PSI_CHECK_NETDB
	PSI_CHECK_NETINET_IN
	PSI_CHECK_NETINET_TCP
	PSI_CHECK_POLL
	PSI_CHECK_SYSLOG
	PSI_CHECK_WCHAR
	PSI_CHECK_WCTYPE
	PSI_CONFIG_DONE

	PHP_SUBST(PSI_SHARED_LIBADD)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["$SHLIB_SUFFIX_NAME"], DL suffix)

	AC_DEFINE_UNQUOTED([PSI_STDINC], [$PSI_STDINC], [Standard includes])
	AC_DEFINE_UNQUOTED([PSI_TYPES], [$PSI_TYPES], [Predefined types])
	AC_DEFINE_UNQUOTED([PSI_STRUCTS], [$PSI_STRUCTS], [Predefined structs])
	AC_DEFINE_UNQUOTED([PSI_CONSTS], [$PSI_CONSTS], [Predefined constants])
	AC_DEFINE_UNQUOTED([PSI_MACROS], [$PSI_MACROS], [Redirected Macros])
	AC_DEFINE_UNQUOTED([PSI_REDIRS], [$PSI_REDIRS], [Redirected functions])
	AC_DEFINE_UNQUOTED([PSI_DECLS], [$PSI_DECLS], [Predefined functions])
	AC_DEFINE_UNQUOTED([PSI_VA_DECLS], [$PSI_VA_DECLS], [Predefined vararg functions])

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
