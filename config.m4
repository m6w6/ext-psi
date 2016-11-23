PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

m4_foreach(incfile, [
	[ax/ax_check_sign.m4],
	[ax/ax_pthread.m4],
	[psi/psi.m4],
	[psi/psi_type.m4],
	[psi/psi_const.m4],
	[psi/psi_decl.m4],
	[psi/psi_macro.m4],
	[psi/psi_struct.m4],
	[posix/errno.m4],
	[posix/fcntl.m4],
	[posix/glob.m4],
	[posix/locale.m4],
	[posix/stddef.m4],
	[posix/stdio.m4],
	[posix/stdint.m4],
	[posix/stdlib.m4],
	[posix/sys_select.m4],
	[posix/sys_socket.m4],
	[posix/sys_stat.m4],
	[posix/sys_time.m4],
	[posix/sys_times.m4],
	[posix/sys_types.m4],
	[posix/sys_uio.m4],
	[posix/sys_utsname.m4],
	[posix/ndbm.m4],
	[posix/netdb.m4],
	[posix/netinet_in.m4],
	[posix/netinet_tcp.m4],
	[posix/poll.m4],
	[posix/signal.m4],
	[posix/syslog.m4],
	[posix/time.m4],
	[posix/unistd.m4],
	[posix/wchar.m4],
	[posix/wctype.m4]], [
	dnl pecl build
	sinclude([m4/]incfile)
	dnl php-src build
	sinclude([ext/psi/m4/]incfile)
])

PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PHP System Interface support])

if test "$PHP_PSI" != no; then
	PHP_CONFIGURE_PART(Configuring PSI)

	PHP_ARG_ENABLE(psi-posix, whether to pre-define POSIX decls,
	[  --enable-psi-posix=...  PSI: pre-define POSIX decls], [ ], [ ])

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
		AC_DEFINE([_GNU_SOURCE], [], [ ])
	], [
		AC_MSG_RESULT([already defined])
	])

	psi_save_LIBS=$LIBS
	LIBS=

	PSI_LEMON
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	AC_PATH_PROG(NM, nm)
	AC_FUNC_FNMATCH

	PSI_CONFIG_INIT
	PSI_CHECK_STD_TYPES
	PSI_CHECK_STDINT
	PSI_CHECK_SYS_TYPES
	PSI_CHECK_STDDEF
	PSI_CHECK_ERRNO
	PSI_CHECK_FCNTL
	PSI_CHECK_GLOB
	PSI_CHECK_LOCALE
	PSI_CHECK_STDIO
	PSI_CHECK_STDLIB
	PSI_CHECK_UNISTD
	PSI_CHECK_TIME
	PSI_CHECK_SYS_SELECT
	PSI_CHECK_SYS_SOCKET
	PSI_CHECK_SYS_TIME
	PSI_CHECK_SYS_TIMES
	PSI_CHECK_SYS_STAT
	PSI_CHECK_SYS_UIO
	PSI_CHECK_SYS_UTSNAME
	PSI_CHECK_NDBM
	PSI_CHECK_NETDB
	PSI_CHECK_NETINET_IN
	PSI_CHECK_NETINET_TCP
	PSI_CHECK_POLL
	PSI_CHECK_SIGNAL
	PSI_CHECK_SYSLOG
	PSI_CHECK_WCHAR
	PSI_CHECK_WCTYPE
	PSI_CONFIG_DONE

	psi_eval_LIBS=$LIBS
	LIBS=$psi_save_LIBS
	PHP_EVAL_LIBLINE($psi_eval_LIBS, PSI_SHARED_LIBADD)
	PHP_SUBST(PSI_SHARED_LIBADD)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["$SHLIB_SUFFIX_NAME"], DL suffix)

	AC_DEFINE_UNQUOTED([PSI_STDINC], ["$PSI_STDINC"], [Standard includes])
	AC_DEFINE_UNQUOTED([PSI_TYPES], ["$PSI_TYPES"], [Predefined types])
	AC_DEFINE_UNQUOTED([PSI_STRUCTS], ["$PSI_STRUCTS"], [Predefined structs])
	AC_DEFINE_UNQUOTED([PSI_UNIONS], ["$PSI_UNIONS"], [Predefined structs])
	AC_DEFINE_UNQUOTED([PSI_CONSTS], ["$PSI_CONSTS"], [Predefined constants])
	AC_DEFINE_UNQUOTED([PSI_MACROS], ["$PSI_MACROS"], [Redirected Macros])
	AC_DEFINE_UNQUOTED([PSI_REDIRS], ["$PSI_REDIRS"], [Redirected functions])
	AC_DEFINE_UNQUOTED([PSI_DECLS], ["$PSI_DECLS"], [Predefined functions])
	AC_DEFINE_UNQUOTED([PSI_VA_DECLS], ["$PSI_VA_DECLS"], [Predefined vararg functions])

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src/types)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src/types)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && ls *.h types/*.h)`
	# parser* should come first
	PHP_PSI_SOURCES=" \
		src/parser_proc.c \
		src/parser.c \
		`(cd $PHP_PSI_SRCDIR && ls src/*.c src/types/*.c | $EGREP -v '^src/parser')` \
	"

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT
	AC_MSG_RESULT()
fi
