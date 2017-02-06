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
	[psi/psi_type.m4],
	[psi/psi_const.m4],
	[psi/psi_decl.m4],
	[psi/psi_macro.m4],
	[psi/psi_composite.m4],
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
[  --enable-psi            Enable PSI (PHP System Interface) support])

if test "$PHP_PSI" != no; then
	PHP_ARG_ENABLE(psi-posix, whether to pre-define POSIX decls,
	[  --enable-psi-posix=...  PSI: pre-define POSIX decls], [all], [no])
	
	PHP_ARG_ENABLE(psi-maintainer-mode, whether to enable maintainer mode,
	[  --enable-psi-maintainer-mode
                          PSI: enable maintainer mode
                           . parallel configure
                           . source dependencies
                           . extra decl wrappers], [no], [no])

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

	PSI_LEMON
	PSI_CHECK_LIBJIT
	PSI_CHECK_LIBFFI

	AC_PATH_PROG(NM, nm)
	AC_FUNC_FNMATCH
	AC_FUNC_MMAP

	PSI_CONFIG_INIT

	dnl basics, one-by-one
	PSI_CHECK_STD_TYPES
	PSI_CHECK_STDINT
	PSI_CHECK_SYS_TYPES
	PSI_CHECK_STDDEF
	
	dnl parallel
	AC_MSG_CHECKING([for POSIX modules: $PHP_PSI_POSIX])
	
	PSI_CONFIG_POSIX(signal, signal.h, [
		PSI_CONFIG_POSIX(time, time.h, [
			PSI_CONFIG_POSIX(sys/stat, sys/stat.h)
			PSI_CONFIG_POSIX(wchar, wchar.h, [
				PSI_CONFIG_POSIX(wctype, wctype.h)
			])
		])
		PSI_CONFIG_POSIX(sys/select, sys/select.h)
	])
	PSI_CONFIG_POSIX(poll, poll.h)
	PSI_CONFIG_POSIX(syslog, syslog.h)
	PSI_CONFIG_POSIX(errno, errno.h)
	PSI_CONFIG_POSIX(fcntl, fcntl.h)
	PSI_CONFIG_POSIX(glob, glob.h)
	PSI_CONFIG_POSIX(locale, locale.h xlocale.h)
	PSI_CONFIG_POSIX(stdio, stdio.h)
	PSI_CONFIG_POSIX(stdlib, stdlib.h)
	PSI_CONFIG_POSIX(unistd, unistd.h)
	PSI_CONFIG_POSIX(sys/socket, sys/socket.h, [
		PSI_CONFIG_POSIX(netinet/in, netinet/in.h)
		PSI_CONFIG_POSIX(netdb, netdb.h)
	])
	PSI_CONFIG_POSIX(netinet/tcp, netinet/tcp.h)
	PSI_CONFIG_POSIX(sys/time, sys/time.h)
	PSI_CONFIG_POSIX(sys/times, sys/times.h)
	PSI_CONFIG_POSIX(sys/uio, sys/uio.h)
	PSI_CONFIG_POSIX(sys/utsname, sys/utsname.h)
	PSI_CONFIG_POSIX(ndbm, dnl
		ndbm.h dnl posix
		relic.h dnl qdbm
		gdbm-ndbm.h dnl gdbm
	)
	
	PSI_CONFIG_DONE

	PHP_SUBST(PSI_SHARED_LIBADD)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["$SHLIB_SUFFIX_NAME"], DL suffix)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src/types)
	PHP_ADD_INCLUDE($PHP_PSI_BUILDDIR)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src/types)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && ls *.h types/*.h)`
	# parser* should come first
	PHP_PSI_SOURCES=" \
		src/parser_proc.c src/parser.c
		`(cd $PHP_PSI_SRCDIR && ls src/*.c src/types/*.c | $EGREP -v '^src/parser')` \
	"
	PHP_PSI_GENERATED="src/parser_proc.y src/parser_proc.c src/parser.c"

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
