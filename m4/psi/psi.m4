
dnl PSI_CONFIG_INIT()
dnl Creates stubs of the headers with pre-defined types etc.
dnl These headers are included by src/context.c.
dnl This macro must be called prior any checks for a type, struct, decl etc.
AC_DEFUN(PSI_CONFIG_INIT, [
	psi_save_LIBS=$LIBS
	LIBS=

	ac_includes_default="AC_INCLUDES_DEFAULT"
	
	AC_PROG_AWK
	AC_PATH_PROG(NM, nm)
	AC_CACHE_CHECK(for libc start main symbol, psi_cv_libc_main, [
		psi_libc_main=
		AC_TRY_LINK(PSI_INCLUDES, [(void)0;], [
			psi_libc_main=`nm -g conftest$ac_exeext | $AWK -F ' *|@' '/^@<:@@<:@:space:@:>@@:>@+U / {print$[]3; exit}'`
		])
		psi_cv_libc_main=$psi_libc_main
	])
	
	AC_MSG_CHECKING(for preprocessor defaults)
	psi_cpp_predef=`$CPP -Wp,-dM $CPPFLAGS -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64 - </dev/null`
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
		$AWK '{
			if (i) printf ":";
			gsub(/^@<:@@<:@:space:@:>@@:>@+/,"");
			gsub(/@<:@@<:@:space:@:>@@:>@+$/,"");
			printf "%s", $[]0;
			++i
		}' \
	`

	if test "$PHP_PSI_MAINTAINER_MODE" = "yes"; then
		PSI_FAST_CONFIG=true
		PSI_DEPS=true
		PSI_EXTRA_REDIRS=true
		
		PHP_SUBST(PSI_DEPS)
		
		PSI_CONFIG_TMP=$(mktemp -d)
	else
		PSI_FAST_CONFIG=false
		PSI_DEPS=false
		if test "$PHP_DEBUG" = "1"; then
			PSI_EXTRA_REDIRS=true
		else
			PSI_EXTRA_REDIRS=false
		fi
	fi
	
	PSI_STDTYPES=
	PSI_TYPES=
	PSI_COMPOSITES=
	PSI_CONSTS=
	PSI_REDIRS=
	PSI_MACROS=
	PSI_DECLS=
	
	AC_CONFIG_FILES(
		[$PHP_PSI_BUILDDIR/php_psi_stdinc.h:$PHP_PSI_SRCDIR/php_psi_stdinc.h.in]
		[$PHP_PSI_BUILDDIR/php_psi_posix.h:$PHP_PSI_SRCDIR/php_psi_posix.h.in]
		[$PHP_PSI_BUILDDIR/php_psi_cpp.h:$PHP_PSI_SRCDIR/php_psi_cpp.h.in]
	)

])

dnl PSI_CONFIG_WAIT()
dnl Internal: waits for sub configures in maintainer mode
AC_DEFUN(PSI_CONFIG_WAIT, [
	wait
	if test $? -gt 0; then
		cat $PSI_CONFIG_TMP/*/stderr.log >&2
		exit 1
	fi
])

dnl PSI_CONFIG_DONE()
dnl Finish the headers with the pre-defined types etc.
AC_DEFUN(PSI_CONFIG_DONE, [
	PSI_CONFIG_WAIT
	
	if $PSI_FAST_CONFIG; then
		for conf_env in $PSI_CONFIG_TMP/*/conf.env; do
			source $conf_env
		done
	fi
	
	psi_eval_LIBS=$LIBS
	LIBS=$psi_save_LIBS
	PHP_EVAL_LIBLINE($psi_eval_LIBS, PSI_SHARED_LIBADD)
	
	[PSI_INCLUDES]="PSI_INCLUDES"
	AC_SUBST([PSI_INCLUDES])
	AC_SUBST([PSI_STDTYPES])
	AC_SUBST([PSI_TYPES])
	AC_SUBST([PSI_COMPOSITES])
	AC_SUBST([PSI_CONSTS])
	AC_SUBST([PSI_REDIRS])
	AC_SUBST([PSI_MACROS])
	AC_SUBST([PSI_DECLS])
	AC_SUBST([PSI_CPP_SEARCH])
	AC_SUBST([PSI_CPP_PREDEF])
])

dnl PSI_SH_CONFIG_POSIX_ENABLED(section)
dnl Expand to $psi_config_posix_<section>
AC_DEFUN(PSI_SH_CONFIG_POSIX_ENABLED, [$AS_TR_SH([psi_config_posix_]$1)])

dnl PSI_CONFIG_POSIX_ENABLED(section, action-if-yes, action-if-not)
dnl Internal. Used to check if --enable-psi-posix=section was given.
AC_DEFUN(PSI_CONFIG_POSIX_ENABLED, [
	AS_TR_SH([psi_config_posix_]$1)=false
	case "$PHP_PSI_POSIX" in
	yes|all)
		AS_TR_SH([psi_config_posix_]$1)=true
		;;
	*)
		if expr "$PHP_PSI_POSIX" : '.*\b$1\b' >/dev/null; then
			AS_TR_SH([psi_config_posix_]$1)=true
		fi
		;;
	esac
	if $AS_TR_SH([psi_config_posix_]$1); then
		ifelse([$2],,:,[$2])
	else
		ifelse([$3],,:,[$3])
	fi
])

dnl PSI_TEST_POSIX_ENABLED(section, action-if-yes, action-if-not)
dnl Shell-if test if PSI POSIX section was configured.
AC_DEFUN(PSI_SH_TEST_POSIX_ENABLED, [
	if test "PSI_SH_CONFIG_POSIX_ENABLED([$1])" && $PSI_SH_CONFIG_POSIX_ENABLED([$1]); then
		ifelse([$2],,:,[$2])
	else
		ifelse([$3],,:,[$3])
	fi
])

dnl PSI_CONFIG_POSIX(section, headers, dependents)
AC_DEFUN(PSI_CONFIG_POSIX, [
	PSI_CONFIG_POSIX_ENABLED($1, [
		if $PSI_FAST_CONFIG; then
			PSI_CONFIG_POSIX_PARALLEL($1, $2, [$3])
		else
			ifelse([$2],,:,[AC_CHECK_HEADERS($2)])
			AS_TR_CPP([PSI_CHECK_$1])
			$3
		fi 
	])
])

AC_DEFUN([PSI_CONFIG_POSIX_PARALLEL], [
	(
		dnl chaway
		mkdir $PSI_CONFIG_TMP/AS_TR_SH([$1])
		cd $PSI_CONFIG_TMP/AS_TR_SH([$1])
		
		dnl AC_DEFINEs 
		ln -s $abs_builddir/confdefs.h confdefs.h
		
		dnl STDOUT, STDERR
		exec {PSI_MESSAGE_FD}>&AS_MESSAGE_FD {PSI_ERROR_FD}>&2
		exec AS_MESSAGE_FD>stdout.log 2>stderr.log
		
		dnl check for headers?
		ifelse([$2],,:,[AC_CHECK_HEADERS($2)])
		
		dnl run checks
		PSI_TYPES=
		PSI_CONSTS=
		PSI_COMPOSITES=
		PSI_REDIRS=
		PSI_MACROS=
		PSI_DECLS=
		AS_TR_CPP([PSI_CHECK_$1])
		
		dnl save env
		cat >conf.env <<EOF
LIBS="$LIBS \$LIBS"
EOF
		for env in TYPES CONSTS COMPOSITES MACROS REDIRS DECLS; do
			eval var=\$PSI_$env
			if test -n "$var"; then
				cat >>conf.env <<EOF
PSI_$env='$var'"
\$PSI_$env"
EOF
			fi
		done
		
		_AC_CACHE_DUMP >>conf.env
		dnl restore STDOUT,STDERR
		exec AS_MESSAGE_FD>&$PSI_MESSAGE_FD 2>&$PSI_ERROR_FD
		
		dnl done
		AS_ECHO_N(["$1 "])
		cd - >/dev/null
		
		dnl run dependents
		$3
		
		PSI_CONFIG_WAIT
	) &
])

AC_DEFUN(PSI_PTHREAD_ONCE, [
	AX_PTHREAD([
		LIBS="$PTHREAD_LIBS $LIBS"
		CFLAGS="$CFLAGS $PTHREAD_CFLAGS"
	])
])
AC_DEFUN(PSI_PTHREAD, [
	AC_REQUIRE([PSI_PTHREAD_ONCE])
])

dnl PSI_INCLUDES()
dnl Expands to a complete list of include statements including
dnl autoconf's defaults.
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

dnl PSI_LEMON()
dnl Declare $LEMON precious, and check for a `lemon` in $PATH.
AC_DEFUN(PSI_LEMON, [
	AC_ARG_VAR(LEMON, The lemon parser generator of the SQLite project)
	if test -z "$LEMON"
	then
		AC_PATH_PROG(LEMON, lemon, $PHP_PSI_BUILDDIR/lemon)
		if expr + "$LEMON" : "/" >/dev/null; then
			LEMON_PATH=
		else
			LEMON_PATH=$abs_builddir/
		fi
	fi
	PHP_SUBST(LEMON_PATH)
	PHP_SUBST(LEMON)
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

dnl PSI_SH_OFFSETOF(type)
dnl Expand to shell variable $ac_cv_offsetof_<TYPE>
AC_DEFUN([PSI_SH_OFFSETOF], [$AS_TR_SH([ac_cv_offsetof_]$1)])

dnl PSI_SH_ALIGNOF(type)
dnl Expand to shell variable $ac_cv_offsetof_<TYPE>
AC_DEFUN([PSI_SH_ALIGNOF], [$AS_TR_SH([ac_cv_alignof_]$1)])

dnl PSI_SH_TEST_SIZEOF(type)
dnl `if` condition to test if $ac_cv_sizeof_$1 is greater than 0.
AC_DEFUN([PSI_SH_TEST_SIZEOF], [test -n "$AS_TR_SH([ac_cv_sizeof_]$1)" && test "$AS_TR_SH([ac_cv_sizeof_]$1)" -gt 0])

dnl PSI_SH_TEST_ALIGNOF(type)
dnl `if` condition to test if $ac_cv_alignof_$1 is greater than 0.
AC_DEFUN([PSI_SH_TEST_ALIGNOF], [test -n "$AS_TR_SH([ac_cv_alignof_]$1)" && test "$AS_TR_SH([ac_cv_alignof_]$1)" -gt 0])

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

dnl PSI_CHECK_ALIGNOF(type, special-includes)
dnl AC_CHECK_ALIGNOF wrapper with PSI_INCLUDES
dnl Defines psi\\ALIGNOF_<TYPE> pre-defined constant in $PSI_CONSTS_H.
AC_DEFUN(PSI_CHECK_ALIGNOF, [
	AC_CHECK_ALIGNOF($1, PSI_INCLUDES
		$2)
	if PSI_SH_TEST_ALIGNOF($1); then
		psi_add_int_const "AS_TR_CPP([ALIGNOF_]$1)" "$AS_TR_SH([ac_cv_alignof_]$1)"
	fi
])

dnl PSI_CHECK_OFFSETOF(struct, element)
dnl Check the offset of a struct element, implemented in the similar manner
dnl like AC_CHECK_SIZEOF.
dnl AC_DEFINEs OFFSETOF_<STRUCT>_<ELEMENT>.
AC_DEFUN(PSI_CHECK_OFFSETOF, [
	_AC_CACHE_CHECK_INT(
		[offset of $2 in $1],
		[AS_TR_SH([ac_cv_offsetof_$1_$2])],
		[(long int) (offsetof ($1, $2))],
		PSI_INCLUDES,
		[AC_MSG_FAILURE([cannot compute offsetof ($1, $2)])]
	)
	AC_DEFINE_UNQUOTED(
		AS_TR_CPP(offsetof_$1_$2),
		$AS_TR_SH([ac_cv_offsetof_$1_$2]),
		[The offset of `$2' in `$1', as computed by offsetof.]
	)
])


dnl PSI_COMPUTE_STR(variable, string or expression)
dnl Compute a string constant value in a similar manner like AC_COMPUTE_INT.
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
		PHP_EVAL_INCLINE(`$PKG_CONFIG --cflags libffi`)
		PHP_EVAL_LIBLINE(`$PKG_CONFIG --libs libffi`, PSI_SHARED_LIBADD)
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
