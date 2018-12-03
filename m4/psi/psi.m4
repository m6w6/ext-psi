dnl PSI_CONFIG_INIT()
dnl Creates stubs of the headers with pre-defined types etc.
AC_DEFUN(PSI_CONFIG_INIT, [
	psi_save_LIBS=$LIBS
	LIBS=

	ac_includes_default="AC_INCLUDES_DEFAULT"
	
	AC_MSG_CHECKING([psi source dir])
	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	AC_MSG_RESULT([$PHP_PSI_SRCDIR])
	
	AC_MSG_CHECKING([psi build dir])
	case "PHP_EXT_BUILDDIR(psi)" in
	""|.) PHP_PSI_BUILDDIR=$PHP_PSI_SRCDIR
		;;
	*)    PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)
		;;
	esac
	AC_MSG_RESULT([$PHP_PSI_BUILDDIR])
	
	PSI_STDTYPES=
	PSI_CONSTS=
	
	AC_CONFIG_FILES(
		[$PHP_PSI_BUILDDIR/php_psi_stdinc.h:$PHP_PSI_SRCDIR/php_psi_stdinc.h.in]
		[$PHP_PSI_BUILDDIR/php_psi_posix.h:$PHP_PSI_SRCDIR/php_psi_posix.h.in]
		[$PHP_PSI_BUILDDIR/php_psi_cpp.h:$PHP_PSI_SRCDIR/php_psi_cpp.h.in]
	)

])

dnl PSI_CONFIG_DONE()
dnl Finish the headers with the pre-defined types etc.
AC_DEFUN(PSI_CONFIG_DONE, [
	psi_eval_LIBS=$LIBS
	LIBS=$psi_save_LIBS
	PHP_EVAL_LIBLINE($psi_eval_LIBS, PSI_SHARED_LIBADD)
	
	[PSI_INCLUDES]="PSI_INCLUDES"
	AC_SUBST([PSI_INCLUDES])
	AC_SUBST([PSI_STDTYPES])
	AC_SUBST([PSI_CONSTS])
	AC_SUBST([PSI_CPP_SEARCH])
	AC_SUBST([PSI_CPP_PREDEF])
	
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
	# parser_* should come first
	PHP_PSI_SOURCES=" \
		src/parser_proc.c src/parser_scan.c \
		`(cd $PHP_PSI_SRCDIR && ls src/*.c src/types/*.c \
			| $EGREP -v '^src/parser_' \
		)` \
	"
	PHP_PSI_GENERATED=" \
		src/parser_proc.c src/parser_scan.c \
		src/calc/basic.h src/calc/bin.h src/calc/bool.h src/calc/cast.h \
		src/calc/unary.h src/calc/cmp.h src/calc/oper.h \
	"

	PHP_SUBST(PHP_PSI_GENERATED)
	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)
])

dnl PSI_CHECK_GNU_SOURCE
dnl Check whether _GNU_SOURCE is already defined.
AC_DEFUN([PSI_CHECK_GNU_SOURCE], [
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
])

dnl PSI_CHECK_CPP
dnl Queries the preprocessor about predefined macros and include search paths
AC_DEFUN([PSI_CHECK_CPP], [
	AC_PROG_AWK

	AC_MSG_CHECKING(for preprocessor defaults)
	psi_cpp_predef=`$CPP -Wp,-dM $CPPFLAGS -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 -U__BLOCKS__ - </dev/null`
	psi_cpp_search=`$CPP -Wp,-v $CPPFLAGS -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 - </dev/null 2>&1 >/dev/null \
		| $AWK '
			/include.*search.*start/ { 
				capture = 1
				next
			}
			/@<:@Ee@:>@nd.*search/ {
				capture = 0
			}
			{ 
				if (capture)
					print $1
			}
		' \
	`
	psi_cpp_predef_count=`printf %s "$psi_cpp_predef" | wc -l`
	psi_cpp_search_count=`printf %s "$psi_cpp_search" | wc -l`
	
	AC_MSG_RESULT([$psi_cpp_predef_count predefined macros, and $psi_cpp_search_count search paths])
	
	PSI_CPP_PREDEF=`printf "%s\n" "$psi_cpp_predef" | \
		$AWK '{
			gsub(/"/, "\\\\\"");
			printf "\"%s\\\n\"\n", $[]0
		}' \
	`
	PSI_CPP_SEARCH=`printf %s "$psi_cpp_search" | \
		$AWK '
			{
				if (i) printf "\":\" ";
				else   printf "    ";
				gsub(/^@<:@@<:@:space:@:>@@:>@+/,"");
				gsub(/@<:@@<:@:space:@:>@@:>@+$/,"");
				printf "\"%s\"\n", $[]0;
				++i
			}' \
	`
])

dnl PSI_CHECK_MAINTAINER_MODE
dnl Check for --enable-psi-maintainer-mode
dnl Enables Makefile dependencies and extra compile warnings
AC_DEFUN([PSI_CHECK_MAINTAINER_MODE], [
	if test "$PHP_PSI_MAINTAINER_MODE" = "yes"; then
		PSI_DEPS=true
		PHP_SUBST(PSI_DEPS)
		CFLAGS="$CFLAGS -Wall -Wextra"
	else
		PSI_DEPS=false
	fi
])

dnl PSI_CHECK_THREADED_PARSER
dnl Check for --enable-psi-threaded-parser
dnl Enables threaded parser if HAVE_PTHREAD && HAVE_ASPRINTF
AC_DEFUN([PSI_CHECK_THREADED_PARSER], [
	if test "$PHP_PSI_THREADED_PARSER" = "yes"; then
		AC_DEFINE([PSI_THREADED_PARSER], [HAVE_PTHREAD && HAVE_ASPRINTF],
			[whether to enable the threaded parser])
	fi
])

AC_DEFUN(PSI_PTHREAD_ONCE, [
	AX_PTHREAD([
		LIBS="$PTHREAD_LIBS $LIBS"
		CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
		AC_DEFINE([HAVE_PTHREAD],[1],
			[Define if you have POSIX threads libraries and header files.])
	])
])
AC_DEFUN(PSI_CHECK_PTHREAD, [
	AC_REQUIRE([PSI_PTHREAD_ONCE])
])

dnl PSI_INCLUDES()
dnl Expands to a complete list of include statements including
dnl autoconf defaults.
AC_DEFUN(PSI_INCLUDES, [
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#ifndef _REENTRANT
# define _REENTRANT
#endif
$ac_includes_default
#ifdef HAVE_STDBOOL_H
# include <stdbool.h>
#else
# ifndef HAVE__BOOL
#  ifdef __cplusplus
typedef bool _Bool;
#  else
#   define _Bool signed char
#  endif
# endif
# define bool _Bool
# define false 0
# define true 1
# define __bool_true_false_are_defined 1
#endif
#ifdef HAVE_ERRNO_H
# include <errno.h>
#endif
#ifdef HAVE_GLOB_H
# include <glob.h>
#endif
#ifdef HAVE_LOCALE_H
# include <locale.h>
#endif
#ifdef HAVE_XLOCALE_H
# include <xlocale.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#ifdef HAVE_NETINET_TCP_H
# include <netinet/tcp.h>
#endif
#ifdef HAVE_ARPA_NAMESER_H
# include <arpa/nameser.h>
#endif
#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif
#ifdef HAVE_RELIC_H
# include <relic.h>
#elif HAVE_NDBM_H
# include <ndbm.h>
#elif HAVE_GDBM_NDBM_H
# include <gdbm-ndbm.h>
#endif
#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif
#ifdef HAVE_POLL_H
# include <poll.h>
#endif
#ifdef HAVE_RESOLV_H
# include <resolv.h>
#endif
#ifdef HAVE_SYS_SELECT_H
# include <sys/select.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif
#ifdef HAVE_SYS_TIMES_H
# include <sys/times.h>
#endif
#ifdef HAVE_SYS_UIO_H
# include <sys/uio.h>
#endif
#ifdef HAVE_SYS_UTSNAME_H
# include <sys/utsname.h>
#endif
#ifdef HAVE_TIME_H
# include <time.h>
#endif
#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif
#ifdef HAVE_SYSLOG_H
# include <syslog.h>
#endif
#ifdef HAVE_WCHAR_H
# include <wchar.h>
#endif
#ifdef HAVE_WCTYPE_H
# include <wctype.h>
#endif
])

dnl PSI_PKG_CONFIG()
dnl Check for `pkg-config` and add possible libjit and libffi directories to
dnl $PKG_CONFIG_PATH, because those libs often ship with headers etc. in
dnl arch-dependent locations.
AC_DEFUN([PSI_PKG_CONFIG], [
	if test -z "$PKG_CONFIG"
	then
		AC_PATH_PROG(PKG_CONFIG, pkg-config, false)
	fi
	export PKG_CONFIG_PATH="$PHP_PSI_LIBFFI/lib/pkgconfig:$PHP_PSI_LIBJIT/lib/pkgconfig:$PKG_CONFIG_PATH"
])

dnl PSI_SH_SIZEOF(type)
dnl expand to shell variable $ac_cv_sizeof_<TYPE>
AC_DEFUN([PSI_SH_SIZEOF], [$AS_TR_SH([ac_cv_sizeof_]$1)])

dnl PSI_SH_TEST_SIZEOF(type)
dnl `if` condition to test if $ac_cv_sizeof_$1 is greater than 0.
AC_DEFUN([PSI_SH_TEST_SIZEOF], [test -n "$AS_TR_SH([ac_cv_sizeof_]$1)" && test "$AS_TR_SH([ac_cv_sizeof_]$1)" -gt 0])

dnl PSI_CHECK_SIZEOF(type, special-includes)
dnl AC_CHECK_SIZEOF wrapper with PSI_INCLUDES
dnl Defines psi\\SIZEOF_<TYPE> pre-defined constant in $PSI_CONSTS_H.
AC_DEFUN(PSI_CHECK_SIZEOF, [
	AC_CHECK_SIZEOF($1, [], PSI_INCLUDES
		$2)
	if PSI_SH_TEST_SIZEOF($1); then
		psi_add_int_const "AS_TR_CPP([SIZEOF_]$1)" "$AS_TR_SH([ac_cv_sizeof_]$1)"
	fi
])

dnl PSI_CHECK_LIBJIT()
dnl Check for libjit in $PHP_PSI_LIBJIT or standard locations
dnl AC_DEFINEs HAVE_LIBJIT.
AC_DEFUN(PSI_CHECK_LIBJIT, [
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

dnl PSI_CHECK_LIBFFI()
dnl Check for libffi with `pkg-config`. If that fails, `configure` looks into
dnl $PHP_PSI_LIBFFI or standard locations to find libjit deps.
dnl Checks for availability of recent closure API:
dnl \ffi_closure_alloc and \ffi_prep_closure.
dnl Checks for availability of recent vararg API:
dnl \ffi_prep_cif_var.
dnl AC_DEFINEs HAVE_LIBFFI, PSI_HAVE_FFI_CLOSURE_ALLOC,
dnl PSI_HAVE_FFI_PREP_CLOSURE and PSI_HAVE_FFO_PREP_VIF_VAR.
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
		PHP_EVAL_INCLINE([`$PKG_CONFIG --cflags libffi`])
		PHP_EVAL_LIBLINE([`$PKG_CONFIG --libs libffi`], PSI_SHARED_LIBADD) dnl `
		AC_DEFINE(HAVE_LIBFFI, 1, Have libffi)
		AC_DEFINE_UNQUOTED([PHP_PSI_LIBFFI_VERSION], ["`$PKG_CONFIG --modversion libffi`"], [libffi version])
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
	
	save_CFLAGS=$CFLAGS
	CFLAGS="$CFLAGS $INCLUDES"
	AC_CHECK_DECL(FFI_STDCALL,[AC_DEFINE([HAVE_FFI_STDCALL],[1],[ ])],,[#include "ffi.h"])
	AC_CHECK_DECL(FFI_FASTCALL,[AC_DEFINE([HAVE_FFI_FASTCALL],[1],[ ])],,[#include "ffi.h"])
	CFLAGS=$save_CFLAGS
	
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
	PHP_CHECK_LIBRARY(ffi, ffi_prep_cif_var, [
		AC_DEFINE(PSI_HAVE_FFI_PREP_CIF_VAR, 1, [ ])
	], [
	], -L$psi_cv_libffi_dir/$PHP_LIBDIR)
])
