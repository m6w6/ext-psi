PHP_ARG_ENABLE(psi, whether to enable PHP System Interface support,
[  --enable-psi            Enable PHP System Interface support])
PHP_ARG_WITH(psi-libjit, where to find libjit,
[  --with-psi-libjit=DIR   PSI: path to libjit], [], no)
PHP_ARG_WITH(psi-libffi, where to find libjit,
[  --with-psi-libffi=DIR   PSI: path to libffi], [], no)

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
		AC_MSG_CHECKING(for libffi)
		PSI_cv_LIBFFI_DIR=`$PKG_CONFIG --variable=prefix libffi`
		AC_MSG_RESULT($PSI_cv_LIBFFI_DIR)
		PHP_EVAL_INCLINE(`$PKG_CONFIG --cflags libffi`)
		PHP_EVAL_LIBLINE(`$PKG_CONFIG --libs libffi`, PSI_SHARED_LIBADD)
		AC_DEFINE(HAVE_LIBFFI, 1, Have libffi)
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
			PHP_ADD_INCLUDE($PSI_cv_LIBFFI_DIR/include/ffi)
			PHP_ADD_LIBRARY_WITH_PATH(ffi, $PSI_cv_LIBFFI_DIR/$PHP_LIBDIR, PSI_SHARED_LIBADD)
			AC_DEFINE(HAVE_LIBFFI, 1, Have libffi)
		else
			AC_MSG_WARN([Could not find libffi, please provide the base install path])
		fi
	fi
	PHP_CHECK_LIBRARY(ffi, ffi_closure_alloc, [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure_loc, [
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE_LOC, 1, [ ])
		], [], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
		AC_DEFINE(PSI_HAVE_FFI_CLOSURE_ALLOC, 1, [ ])
	], [
		PHP_CHECK_LIBRARY(ffi, ffi_prep_closure, [
			AC_CHECK_HEADERS(sys/mman.h)
			PHP_CHECK_FUNC(mmap)
			AC_DEFINE(PSI_HAVE_FFI_PREP_CLOSURE, 1, [ ])
		], [
		], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)
	], -L$PSI_cv_LIBFFI_DIR/$PHP_LIBDIR)

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
		AC_DEFINE(HAVE_LIBJIT, 1, Have libjit)
	else
		AC_MSG_WARN([Could not find libjit, please provide the base install path])
	fi

	PHP_SUBST(PSI_SHARED_LIBADD)

	dnl PSI_INCLUDES_DEFAULT(include, defines)
	AC_DEFUN(PSI_INCLUDES_DEFAULT, [
		AC_INCLUDES_DEFAULT()
		$2
		m4_ifnblank($1,
			m4_expand([#include <]$1[>])
		)
	])

	AC_DEFUN([AX_CHECK_SIGN], [
		typename=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g"`
		AC_CACHE_CHECK([whether $1 is signed], ax_cv_decl_${typename}_signed, [
				AC_TRY_COMPILE([$4],
						[ int foo @<:@ 1 - 2 * !((($1) -1) < 0) @:>@ ],
						[ eval "ax_cv_decl_${typename}_signed=\"yes\"" ],
						[ eval "ax_cv_decl_${typename}_signed=\"no\"" ])])
		symbolname=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g" | tr "a-z" "A-Z"`
		if eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"yes\""; then
				$2
		elif eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"no\""; then
				$3
		fi
	])

	psi_type_pair() { # (type, size)
		local psi_type_name=`tr -cd A-Za-z <<<$1`
		local psi_type_lower=`tr A-Z a-z <<<$psi_type_name`
		case $psi_type_lower in
		int*|uint*)
			local psi_type_upper=`tr a-z A-Z <<<$psi_type_name`
			local psi_type_bits=`expr $2 \* 8`
			echo "PSI_T_${psi_type_upper}${psi_type_bits}, \"${psi_type_lower}${psi_type_bits}_t\""
			;;
		struct*)
			echo "PSI_T_STRUCT, \"$2\""
			;;
		*)
			echo "PSI_T_NAME, \"$psi_type_name\""
			;;
		esac
	}

	PSI_TYPES=""
	dnl PSI_TYPE(type name, basic type, includes)
	AC_DEFUN(PSI_TYPE, [
		ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
		ifdef(AC_TYPE_[]patsubst(translit($1,a-z,A-Z),\W,_),AC_TYPE_[]patsubst(translit($1,a-z,A-Z),\W,_))
		AC_CHECK_SIZEOF($1, [], PSI_INCLUDES_DEFAULT($3))
		psi_basic_type=$2
		case $psi_basic_type in
		int)
			AX_CHECK_SIGN($1, :, [
				psi_basic_type=uint
			], PSI_INCLUDES_DEFAULT($3))
			;;
		sint)
			psi_basic_type=int
			;;
		esac
		if test "$2" && test "$ac_cv_sizeof_[]$1" -gt 0; then
			AS_TR_SH(psi_basic_type_$1)=$psi_basic_type
			PSI_TYPES="{`psi_type_pair $psi_basic_type $ac_cv_sizeof_[]$1`, \""$1"\"}, $PSI_TYPES"
		fi
	])


	dnl PSI_COMPUTE_STR(variable, string or expression, includes)
	AC_DEFUN(PSI_COMPUTE_STR, [
		AC_TRY_RUN([
			$3
			int main() {
				return EOF == fputs($2, fopen("conftest.out", "w"));
			}
		], [
			eval $1=\\\"`cat conftest.out`\\\"
		])
	])

	PSI_CONSTS=""
	dnl PSI_CONST(const name, type, headers to include)
	AC_DEFUN(PSI_CONST, [
		AC_CACHE_CHECK(value of $1, psi_cv_const_$1, [
			psi_const_val=
			case $2 in
			str*|quoted_str*)
				if test "$cross_compiling" = "yes"
				then
					AC_TRY_CPP(PSI_INCLUDES_DEFAULT($3)$1, psi_const_val=`eval "$ac_try|tail -n1"`, psi_const_val=)
				else
					PSI_COMPUTE_STR(psi_const_val, $1, PSI_INCLUDES_DEFAULT($3))
				fi
				;;
			*)
				AC_COMPUTE_INT(psi_const_val, $1, PSI_INCLUDES_DEFAULT($3))
				;;
			esac
			psi_cv_const_$1=$psi_const_val
		])
		if test "$psi_cv_const_$1"
		then
			case $2 in
			str*|quoted_str*)
				PSI_CONSTS="{PSI_T_STRING, \"string\", \"psi\\\\$1\", $psi_cv_const_$1, PSI_T_QUOTED_STRING}, $PSI_CONSTS"
				;;
			*)
				PSI_CONSTS="{PSI_T_INT, \"int\", \"psi\\\\$1\", \"$psi_cv_const_$1\", PSI_T_NUMBER}, $PSI_CONSTS"
				;;
			esac
		fi
	])

	dnl PSI_CHECK_OFFSETOF(struct, member, include)
	dnl[AS_LITERAL_IF([$1], [], [m4_fatal([$0: requires literal arguments])])]dnl
	dnl[AS_LITERAL_IF([$2], [], [m4_fatal([$0: requires literal arguments])])]dnl
	AC_DEFUN(PSI_CHECK_OFFSETOF, [
		_AC_CACHE_CHECK_INT(
			[offset of $2 in $1],
			[AS_TR_SH([ac_cv_offsetof_$1_$2])],
			[(long int) (offsetof ($1, $2))],
			[AC_INCLUDES_DEFAULT([$3])],
			[AC_MSG_FAILURE([cannot compute offsetof ($1, $2)])]
		)
		AC_DEFINE_UNQUOTED(
			AS_TR_CPP(offsetof_$1_$2),
			$AS_TR_SH([ac_cv_offsetof_$1_$2]),
			[The offset of `$2' in `$1', as computed by offsetof.]
		)
	])

	dnl PSI_STRUCT(struct name, members, member type cases, includes)
	PSI_STRUCTS=
	AC_DEFUN(PSI_STRUCT, [
		AC_CHECK_SIZEOF($1, [], PSI_INCLUDES_DEFAULT($4))
		psi_struct_name=`echo $1 | cut -d" " -f2`
		psi_struct_size=$AS_TR_SH(ac_cv_sizeof_$1)
		psi_struct_members=
		m4_foreach(member, [$2], [
			AC_CHECK_MEMBER($1.member, [
				psi_member_name=member
				AC_CHECK_SIZEOF(AS_TR_SH($1)[_]member, [], PSI_INCLUDES_DEFAULT($4,
					[#define ]AS_TR_SH($1)[_]member (($1 *)0)->member
				))
				psi_member_size=$AS_TR_SH(ac_cv_sizeof_$1[]_[]member)
				PSI_CHECK_OFFSETOF($1, member, PSI_INCLUDES_DEFAULT($4))
				psi_member_offset=$AS_TR_SH(ac_cv_offsetof_$1[]_[]member)
				# type
				case member in
				$3
				*) psi_member_type=int ;;
				esac
				# pointer level
				psi_struct_member_pl=`echo $psi_member_type | tr -cd '*' | wc -c`
				# array size
				psi_struct_member_as=`echo $psi_member_type | $AWK -F'@<:@@:>@@<:@@:>@' 'END {if(!found)print 0} /\@<:@@<:@@<:@:digit:@:>@@:>@+\@:>@/ {found=1; print$[]2}'`
				if test $psi_struct_member_as -gt 0
				then
					psi_struct_member_pl=`expr $psi_struct_member_pl + 1`
				fi
				psi_struct_member="{`psi_type_pair $psi_member_type $psi_member_size`, \"$psi_member_name\", $psi_member_offset, $psi_member_size, $psi_struct_member_pl, $psi_struct_member_as}"
				if test "$psi_struct_members"
				then
					psi_struct_members="$psi_struct_members, $psi_struct_member"
				else
					psi_struct_members="$psi_struct_member"
				fi
			], [], PSI_INCLUDES_DEFAULT($4))
		])
		if test "$1" = "$psi_struct_name"
		then
			PSI_TYPES="{PSI_T_STRUCT, \"$psi_struct_name\", \"$psi_struct_name\"}, $PSI_TYPES"
		fi
		PSI_STRUCTS="{\"$psi_struct_name\", $psi_struct_size, {$psi_struct_members}}, $PSI_STRUCTS"
	])

	PSI_INCLUDES=
	AC_PROG_NM
	AC_PROG_AWK
	PSI_FUNCS=
	dnl PSI_FUNC(fn, include)
	AC_DEFUN(PSI_FUNC, [
		psi_symbol=$1
		AC_CACHE_CHECK(for $1, psi_cv_fn_$1, [
			psi_symbol_redirect=
			AC_TRY_LINK(PSI_INCLUDES_DEFAULT($2), [
				void (*fn)(void) = (void (*)(void)) $psi_symbol;
			], [
				psi_symbol_redirect=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/ U .*$1.*/ {print$[]3}'`
			])
			psi_cv_fn_$1=$psi_symbol_redirect
		])
		case "$psi_cv_fn_$1" in
		"$psi_symbol"|"_$psi_symbol"|"")
			;;
		*)
			PSI_FUNCS="{\"$psi_symbol\", (void (*)(void)) $psi_symbol}, $PSI_FUNCS"
			;;
		esac
	])

	PSI_MACROS=
	dnl PSI_MACRO(macro, return type, decl args, call args, include)
	AC_DEFUN(PSI_MACRO, [
		AC_CHECK_DECL($1$3, [
			PSI_MACROS="static $2 psi_macro_$1$3 { ifelse($2,void,,return) $1$4;} $PSI_MACROS"
			PSI_FUNCS="{\"$1\", (void (*)(void)) psi_macro_$1}, $PSI_FUNCS"
		], [], PSI_INCLUDES_DEFAULT($5))
	])

	dnl PSI_DECL(var, type, include)
	AC_DEFUN(PSI_DECL, [
		AC_CHECK_DECL($1, [
			PSI_MACROS="static $2 psi_macro_$1(void) {return $1;} $PSI_MACROS"
			PSI_FUNCS="{\"$1\", (void (*)(void)) psi_macro_$1}, $PSI_FUNCS"
		], [], PSI_INCLUDES_DEFAULT($3))
	])

	CPPFLAGS="$CPPFLAGS -D_DARWIN_USE_64_BIT_INODE"
	AC_FUNC_FNMATCH
	AC_HEADER_DIRENT

	AC_TYPE_INT8_T
	AC_CHECK_ALIGNOF(int8_t)
	AC_TYPE_UINT8_T
	AC_CHECK_ALIGNOF(uint8_t)
	AC_TYPE_INT16_T
	AC_CHECK_ALIGNOF(int16_t)
	AC_TYPE_UINT16_T
	AC_CHECK_ALIGNOF(uint16_t)
	AC_TYPE_INT32_T
	AC_CHECK_ALIGNOF(int32_t)
	AC_TYPE_UINT32_T
	AC_CHECK_ALIGNOF(uint32_t)
	AC_TYPE_INT64_T
	AC_CHECK_ALIGNOF(int64_t)
	AC_TYPE_UINT64_T
	AC_CHECK_ALIGNOF(uint64_t)

	PSI_TYPE(char, int)
	PSI_TYPE(short, int)
	PSI_TYPE(int, int)
	PSI_TYPE(long, int)
	PSI_TYPE(float)
	PSI_TYPE(double)
	PSI_TYPE(void *)

	dnl sys/types.h
	AC_CHECK_HEADERS(sys/types.h)
	PSI_TYPE(blkcnt_t, int)
	PSI_TYPE(blksize_t, int)
	PSI_TYPE(clock_t, int)
	PSI_TYPE(clockid_t, int)
	PSI_TYPE(dev_t, int)
	PSI_TYPE(fsblkcnt_t, uint)
	PSI_TYPE(fsfilcnt_t, uint)
	PSI_TYPE(gid_t, int)
	PSI_TYPE(id_t, int)
	PSI_TYPE(ino_t, uint)
	PSI_TYPE(key_t, int)
	PSI_TYPE(mode_t, int)
	PSI_TYPE(nlink_t, int)
	PSI_TYPE(off_t, int)
	PSI_TYPE(pid_t, int)
	PSI_TYPE(ssize_t, int)
	PSI_TYPE(suseconds_t, int)
	PSI_TYPE(time_t, int)
	PSI_TYPE(timer_t, int)
	PSI_TYPE(uid_t, int)

	dnl stdint.h
	AC_CHECK_HEADERS(stdint.h)
	PSI_TYPE(int_least8_t, int)
	PSI_TYPE(int_least16_t, int)
	PSI_TYPE(int_least32_t, int)
	PSI_TYPE(int_least64_t, int)
	PSI_TYPE(uint_least8_t, uint)
	PSI_TYPE(uint_least16_t, uint)
	PSI_TYPE(uint_least32_t, uint)
	PSI_TYPE(uint_least64_t, uint)
	PSI_TYPE(int_fast8_t, int)
	PSI_TYPE(int_fast16_t, int)
	PSI_TYPE(int_fast32_t, int)
	PSI_TYPE(int_fast64_t, int)
	PSI_TYPE(uint_fast8_t, uint)
	PSI_TYPE(uint_fast16_t, uint)
	PSI_TYPE(uint_fast32_t, uint)
	PSI_TYPE(uint_fast64_t, uint)
	PSI_TYPE(intptr_t, int)
	PSI_TYPE(uintptr_t, uint)
	PSI_TYPE(intmax_t, int)
	PSI_TYPE(uintmax_t, uint)

	PSI_CONST(INT8_MIN, int)
	PSI_CONST(INT8_MAX, int)
	PSI_CONST(UINT8_MAX, int)
	PSI_CONST(INT16_MIN, int)
	PSI_CONST(INT16_MAX, int)
	PSI_CONST(UINT16_MAX, int)
	PSI_CONST(INT32_MIN, int)
	PSI_CONST(INT32_MAX, int)
	PSI_CONST(UINT32_MAX, int)
	PSI_CONST(INT64_MIN, int)
	PSI_CONST(INT64_MAX, int)
	PSI_CONST(UINT64_MAX, int)

	PSI_CONST(INT_LEAST8_MIN, int)
	PSI_CONST(INT_LEAST8_MAX, int)
	PSI_CONST(UINT_LEAST8_MAX, int)
	PSI_CONST(INT_LEAST16_MIN, int)
	PSI_CONST(INT_LEAST16_MAX, int)
	PSI_CONST(UINT_LEAST16_MAX, int)
	PSI_CONST(INT_LEAST32_MIN, int)
	PSI_CONST(INT_LEAST32_MAX, int)
	PSI_CONST(UINT_LEAST32_MAX, int)
	PSI_CONST(INT_LEAST64_MIN, int)
	PSI_CONST(INT_LEAST64_MAX, int)
	PSI_CONST(UINT_LEAST64_MAX, int)

	PSI_CONST(INT_FAST8_MIN, int)
	PSI_CONST(INT_FAST8_MAX, int)
	PSI_CONST(UINT_FAST8_MAX, int)
	PSI_CONST(INT_FAST16_MIN, int)
	PSI_CONST(INT_FAST16_MAX, int)
	PSI_CONST(UINT_FAST16_MAX, int)
	PSI_CONST(INT_FAST32_MIN, int)
	PSI_CONST(INT_FAST32_MAX, int)
	PSI_CONST(UINT_FAST32_MAX, int)
	PSI_CONST(INT_FAST64_MIN, int)
	PSI_CONST(INT_FAST64_MAX, int)
	PSI_CONST(UINT_FAST64_MAX, int)

	PSI_CONST(INTPTR_MIN, int)
	PSI_CONST(INTPTR_MAX, int)
	PSI_CONST(UINTPTR_MAX, int)
	PSI_CONST(INTMAX_MIN, int)
	PSI_CONST(INTMAX_MAX, int)
	PSI_CONST(UINTMAX_MAX, int)

	dnl stddef.h
	PSI_TYPE(ptrdiff_t, int)
	PSI_CONST(PTRDIFF_MIN, int)
	PSI_CONST(PTRDIFF_MAX, int)
	PSI_TYPE(size_t, uint)
	PSI_CONST(SIZE_MAX, int)
	PSI_TYPE(wchar_t, int)
	PSI_CONST(WCHAR_MIN, int)
	PSI_CONST(WCHAR_MAX, int)

	dnl errno.h
	AC_CHECK_HEADERS(errno.h)
	PSI_MACRO(errno, int, [()], [], errno.h)
	PSI_CONST(E2BIG, int, errno.h)
	PSI_CONST(EACCES, int, errno.h)
	PSI_CONST(EADDRINUSE, int, errno.h)
	PSI_CONST(EADDRNOTAVAIL, int, errno.h)
	PSI_CONST(EAFNOSUPPORT, int, errno.h)
	PSI_CONST(EAGAIN, int, errno.h)
	PSI_CONST(EALREADY, int, errno.h)
	PSI_CONST(EBADF, int, errno.h)
	PSI_CONST(EBADMSG, int, errno.h)
	PSI_CONST(EBUSY, int, errno.h)
	PSI_CONST(ECANCELED, int, errno.h)
	PSI_CONST(ECHILD, int, errno.h)
	PSI_CONST(ECONNABORTED, int, errno.h)
	PSI_CONST(ECONNREFUSED, int, errno.h)
	PSI_CONST(ECONNRESET, int, errno.h)
	PSI_CONST(EDEADLK, int, errno.h)
	PSI_CONST(EDESTADDRREQ, int, errno.h)
	PSI_CONST(EDOM, int, errno.h)
	PSI_CONST(EDQUOT, int, errno.h)
	PSI_CONST(EEXIST, int, errno.h)
	PSI_CONST(EFAULT, int, errno.h)
	PSI_CONST(EFBIG, int, errno.h)
	PSI_CONST(EHOSTUNREACH, int, errno.h)
	PSI_CONST(EIDRM, int, errno.h)
	PSI_CONST(EILSEQ, int, errno.h)
	PSI_CONST(EINPROGRESS, int, errno.h)
	PSI_CONST(EINTR, int, errno.h)
	PSI_CONST(EINVAL, int, errno.h)
	PSI_CONST(EIO, int, errno.h)
	PSI_CONST(EISCONN, int, errno.h)
	PSI_CONST(EISDIR, int, errno.h)
	PSI_CONST(ELOOP, int, errno.h)
	PSI_CONST(EMFILE, int, errno.h)
	PSI_CONST(EMLINK, int, errno.h)
	PSI_CONST(EMSGSIZE, int, errno.h)
	PSI_CONST(EMULTIHOP, int, errno.h)
	PSI_CONST(ENAMETOOLONG, int, errno.h)
	PSI_CONST(ENETDOWN, int, errno.h)
	PSI_CONST(ENETRESET, int, errno.h)
	PSI_CONST(ENETUNREACH, int, errno.h)
	PSI_CONST(ENFILE, int, errno.h)
	PSI_CONST(ENOBUFS, int, errno.h)
	PSI_CONST(ENODATA, int, errno.h)
	PSI_CONST(ENODEV, int, errno.h)
	PSI_CONST(ENOENT, int, errno.h)
	PSI_CONST(ENOEXEC, int, errno.h)
	PSI_CONST(ENOLCK, int, errno.h)
	PSI_CONST(ENOLINK, int, errno.h)
	PSI_CONST(ENOMEM, int, errno.h)
	PSI_CONST(ENOMSG, int, errno.h)
	PSI_CONST(ENOPROTOOPT, int, errno.h)
	PSI_CONST(ENOSPC, int, errno.h)
	PSI_CONST(ENOSR, int, errno.h)
	PSI_CONST(ENOSTR, int, errno.h)
	PSI_CONST(ENOSYS, int, errno.h)
	PSI_CONST(ENOTCONN, int, errno.h)
	PSI_CONST(ENOTDIR, int, errno.h)
	PSI_CONST(ENOTEMPTY, int, errno.h)
	PSI_CONST(ENOTRECOVERABLE, int, errno.h)
	PSI_CONST(ENOTSOCK, int, errno.h)
	PSI_CONST(ENOTSUP, int, errno.h)
	PSI_CONST(ENOTTY, int, errno.h)
	PSI_CONST(ENXIO, int, errno.h)
	PSI_CONST(EOPNOTSUPP, int, errno.h)
	PSI_CONST(EOVERFLOW, int, errno.h)
	PSI_CONST(EOWNERDEAD, int, errno.h)
	PSI_CONST(EPERM, int, errno.h)
	PSI_CONST(EPIPE, int, errno.h)
	PSI_CONST(EPROTO, int, errno.h)
	PSI_CONST(EPROTONOSUPPORT, int, errno.h)
	PSI_CONST(EPROTOTYPE, int, errno.h)
	PSI_CONST(ERANGE, int, errno.h)
	PSI_CONST(EROFS, int, errno.h)
	PSI_CONST(ESPIPE, int, errno.h)
	PSI_CONST(ESRCH, int, errno.h)
	PSI_CONST(ESTALE, int, errno.h)
	PSI_CONST(ETIME, int, errno.h)
	PSI_CONST(ETIMEDOUT, int, errno.h)
	PSI_CONST(ETXTBSY, int, errno.h)
	PSI_CONST(EWOULDBLOCK, int, errno.h)
	PSI_CONST(EXDEV, int, errno.h)

	dnl glob.h
	AC_CHECK_HEADERS(glob.h)
	PSI_FUNC(glob, glob.h)
	PSI_FUNC(globfree, glob.h)
	PSI_STRUCT(glob_t, [
		[gl_pathc], [gl_matchc],
		[gl_pathv],
		[gl_offs],
		[gl_flags]], [
		gl_matchc|gl_pathc|gloffs) psi_member_type=uint ;;
		gl_pathv)  psi_member_type="char**" ;;
	], glob.h)
	PSI_CONST(GLOB_APPEND, int, glob.h)
	PSI_CONST(GLOB_BRACE, int, glob.h)
	PSI_CONST(GLOB_DOOFFS, int, glob.h)
	PSI_CONST(GLOB_ERR, int, glob.h)
	PSI_CONST(GLOB_MARK, int, glob.h)
	PSI_CONST(GLOB_NOCHECK, int, glob.h)
	PSI_CONST(GLOB_NOESCAPE, int, glob.h)
	PSI_CONST(GLOB_NOMAGIC, int, glob.h)
	PSI_CONST(GLOB_NOSORT, int, glob.h)
	PSI_CONST(GLOB_ONLYDIR, int, glob.h)
	PSI_CONST(GLOB_PERIOD, int, glob.h)
	PSI_CONST(GLOB_TILDE, int, glob.h)
	PSI_CONST(GLOB_TILDE_CHECK, int, glob.h)
	PSI_CONST(GLOB_ABORTED, int, glob.h)
	PSI_CONST(GLOB_NOMATCH, int, glob.h)
	PSI_CONST(GLOB_NOSPACE, int, glob.h)

	dnl stdio.h
	PSI_CONST(BUFSIZ, int)
	PSI_CONST(_IOFBF, int)
	PSI_CONST(_IOLBF, int)
	PSI_CONST(_IONBF, int)
	PSI_CONST(SEEK_CUR, int)
	PSI_CONST(SEEK_END, int)
	PSI_CONST(SEEK_SET, int)
	PSI_CONST(FILENAME_MAX, int)
	PSI_CONST(FOPEN_MAX, int)
	PSI_CONST(TMP_MAX, int)
	PSI_CONST(EOF, int)
	PSI_CONST(P_tmpdir, string)
	PSI_CONST(L_ctermid, int)
	PSI_CONST(L_tmpnam, int)
	PSI_FUNC(clearerr, stdio.h)
	PSI_FUNC(ctermid, stdio.h)
	PSI_FUNC(dprintf, stdio.h)
	PSI_FUNC(fclose, stdio.h)
	PSI_FUNC(fdopen, stdio.h)
	PSI_FUNC(feof, stdio.h)
	PSI_FUNC(ferror, stdio.h)
	PSI_FUNC(fflush, stdio.h)
	PSI_FUNC(fgetc, stdio.h)
	PSI_FUNC(fgetpos, stdio.h)
	PSI_FUNC(fgets, stdio.h)
	PSI_FUNC(fileno, stdio.h)
	PSI_FUNC(flockfile, stdio.h)
	PSI_FUNC(fmemopen, stdio.h)
	PSI_FUNC(fopen, stdio.h)
	PSI_FUNC(fprintf, stdio.h)
	PSI_FUNC(fputc, stdio.h)
	PSI_FUNC(fputs, stdio.h)
	PSI_FUNC(fread, stdio.h)
	PSI_FUNC(freopen, stdio.h)
	PSI_FUNC(fscanf, stdio.h)
	PSI_FUNC(fseek, stdio.h)
	PSI_FUNC(fseeko, stdio.h)
	PSI_FUNC(fsetpos, stdio.h)
	PSI_FUNC(ftell, stdio.h)
	PSI_FUNC(ftello, stdio.h)
	PSI_FUNC(ftrylockfile, stdio.h)
	PSI_FUNC(funlockfile, stdio.h)
	PSI_FUNC(fwrite, stdio.h)
	PSI_FUNC(getc, stdio.h)
	PSI_FUNC(getchar, stdio.h)
	PSI_FUNC(getc_unlocked, stdio.h)
	PSI_FUNC(getchar_unlocked, stdio.h)
	PSI_FUNC(getdelim, stdio.h)
	PSI_FUNC(getline, stdio.h)
	PSI_FUNC(gets, stdio.h)
	PSI_FUNC(open_memstream, stdio.h)
	PSI_FUNC(pclose, stdio.h)
	PSI_FUNC(perror, stdio.h)
	PSI_FUNC(popen, stdio.h)
	PSI_FUNC(printf, stdio.h)
	PSI_FUNC(putc, stdio.h)
	PSI_FUNC(putchar, stdio.h)
	PSI_FUNC(putc_unlocked, stdio.h)
	PSI_FUNC(putchar_unlocked, stdio.h)
	PSI_FUNC(puts, stdio.h)
	PSI_FUNC(remove, stdio.h)
	PSI_FUNC(rename, stdio.h)
	PSI_FUNC(renameat, stdio.h)
	PSI_FUNC(rewind, stdio.h)
	PSI_FUNC(scanf, stdio.h)
	PSI_FUNC(setbuf, stdio.h)
	PSI_FUNC(setvbuf, stdio.h)
	PSI_FUNC(snprintf, stdio.h)
	PSI_FUNC(sprintf, stdio.h)
	PSI_FUNC(sscanf, stdio.h)
	PSI_FUNC(tempnam, stdio.h)
	PSI_FUNC(tmpfile, stdio.h)
	PSI_FUNC(tmpnam, stdio.h)
	PSI_FUNC(ungetc, stdio.h)
	PSI_FUNC(vdprintf, stdio.h)
	PSI_FUNC(vfprintf, stdio.h)
	PSI_FUNC(vfscanf, stdio.h)
	PSI_FUNC(vprintf, stdio.h)
	PSI_FUNC(vscanf, stdio.h)
	PSI_FUNC(vsnprintf, stdio.h)
	PSI_FUNC(vsprintf, stdio.h)
	PSI_FUNC(vsscanf, stdio.h)

	dnl stdlib.h
	PSI_FUNC(_Exit, stdlib.h)
    PSI_FUNC(a64l, stdlib.h)
    PSI_FUNC(abort, stdlib.h)
    PSI_FUNC(abs, stdlib.h)
    PSI_FUNC(atexit, stdlib.h)
    PSI_FUNC(atof, stdlib.h)
    PSI_FUNC(atoi, stdlib.h)
    PSI_FUNC(atol, stdlib.h)
    PSI_FUNC(atoll, stdlib.h)
    PSI_FUNC(div, stdlib.h)
    PSI_FUNC(drand48, stdlib.h)
    PSI_FUNC(erand48, stdlib.h)
    PSI_FUNC(exit, stdlib.h)
    PSI_FUNC(free, stdlib.h)
    PSI_FUNC(getsubopt, stdlib.h)
    PSI_FUNC(grantpt, stdlib.h)
    PSI_FUNC(jrand48, stdlib.h)
    PSI_FUNC(labs, stdlib.h)
    PSI_FUNC(lcong48, stdlib.h)
    PSI_FUNC(ldiv, stdlib.h)
    PSI_FUNC(llabs, stdlib.h)
    PSI_FUNC(lldiv, stdlib.h)
    PSI_FUNC(lrand48, stdlib.h)
    PSI_FUNC(mblen, stdlib.h)
    PSI_FUNC(mbstowcs, stdlib.h)
    PSI_FUNC(mbtowc, stdlib.h)
    PSI_FUNC(mkstemp, stdlib.h)
    PSI_FUNC(mrand48, stdlib.h)
    PSI_FUNC(nrand48, stdlib.h)
    PSI_FUNC(posix_memalign, stdlib.h)
    PSI_FUNC(posix_openpt, stdlib.h)
    PSI_FUNC(putenv, stdlib.h)
    PSI_FUNC(qsort, stdlib.h)
    PSI_FUNC(rand, stdlib.h)
    PSI_FUNC(rand_r, stdlib.h)
    PSI_FUNC(random, stdlib.h)
    PSI_FUNC(setenv, stdlib.h)
    PSI_FUNC(setkey, stdlib.h)
    PSI_FUNC(srand, stdlib.h)
    PSI_FUNC(srand48, stdlib.h)
    PSI_FUNC(srandom, stdlib.h)
    PSI_FUNC(strtod, stdlib.h)
    PSI_FUNC(strtof, stdlib.h)
    PSI_FUNC(strtol, stdlib.h)
    PSI_FUNC(strtold, stdlib.h)
    PSI_FUNC(strtoll, stdlib.h)
    PSI_FUNC(strtoul, stdlib.h)
    PSI_FUNC(system, stdlib.h)
    PSI_FUNC(unlockpt, stdlib.h)
    PSI_FUNC(unsetenv, stdlib.h)
    PSI_FUNC(wcstombs, stdlib.h)
    PSI_FUNC(wctomb, stdlib.h)
	PSI_CONST(EXIT_FAILURE, int)
	PSI_CONST(EXIT_SUCCESS, int)
	PSI_CONST(RAND_MAX, int)
	PSI_CONST(MB_CUR_MAX, int)

	dnl sys/stat.h
	AC_CHECK_HEADERS(sys/stat.h)
	PSI_FUNC(chmod, sys/stat.h)
	PSI_FUNC(fchmod, sys/stat.h)
	PSI_FUNC(fchmodat, sys/stat.h)
	PSI_FUNC(fstat, sys/stat.h)
	PSI_FUNC(fstatat, sys/stat.h)
	PSI_FUNC(futimens, sys/stat.h)
	PSI_FUNC(lstat, sys/stat.h)
	PSI_FUNC(mkdir, sys/stat.h)
	PSI_FUNC(mkdirat, sys/stat.h)
	PSI_FUNC(mkfifo, sys/stat.h)
	PSI_FUNC(mkfifoat, sys/stat.h)
	PSI_FUNC(mknod, sys/stat.h)
	PSI_FUNC(mknodat, sys/stat.h)
	PSI_FUNC(stat, sys/stat.h)
	PSI_FUNC(umask, sys/stat.h)
	PSI_FUNC(utimensat, sys/stat.h)
	PSI_STRUCT(struct stat, [
		[st_dev],
		[st_ino],
		[st_mode],
		[st_nlink],
		[st_uid],
		[st_gid],
		[st_rdev],
		[st_size],
		[st_atim], [st_atimespec], [st_atime],
		[st_mtim], [st_mtimespec], [st_mtime],
		[st_ctim], [st_ctimespec], [st_ctime],
		[st_birthtimespec], [st_birthtime],
		[st_blksize],
		[st_blocks],
		[st_flags],
		[st_gen],
		[st_lspare]], [
		st_dev) psi_member_type=$psi_basic_type_dev_t ;;
		st_ino) psi_member_type=$psi_basic_type_ino_t ;;
		st_mode) psi_member_type=$psi_basic_type_mode_t ;;
		st_nlink) psi_member_type=$psi_basic_type_nlink_t ;;
		st_uid) psi_member_type=$psi_basic_type_uid_t ;;
		st_gid) psi_member_type=$psi_basic_type_gid_t ;;
		st_rdev) psi_member_type=$psi_basic_type_dev_t ;;
		st_size) psi_member_type=$psi_basic_type_off_t ;;
		st_blksize) psi_member_type=$psi_basic_type_blksize_t ;;
		st_blkcnt) psi_member_type=$psi_basic_type_blkcnt_t ;;
		st_?tim) psi_member_type="struct timespec" ;;
		st_*time) psi_member_type=$psi_basic_type_time_t ;;
		st_*timespec) psi_member_type="struct timespec" ;;
	], sys/stat.h)
	PSI_CONST(S_IFMT, int, sys/stat.h)
	PSI_CONST(S_IFBLK, int, sys/stat.h)
	PSI_CONST(S_IFCHR, int, sys/stat.h)
	PSI_CONST(S_IFIFO, int, sys/stat.h)
	PSI_CONST(S_IFREG, int, sys/stat.h)
	PSI_CONST(S_IFDIR, int, sys/stat.h)
	PSI_CONST(S_IFLNK, int, sys/stat.h)
	PSI_CONST(S_IFSOCK, int, sys/stat.h)
	PSI_CONST(S_IRWXU, int, sys/stat.h)
	PSI_CONST(S_IRUSR, int, sys/stat.h)
	PSI_CONST(S_IWUSR, int, sys/stat.h)
	PSI_CONST(S_IXUSR, int, sys/stat.h)
	PSI_CONST(S_IRWXG, int, sys/stat.h)
	PSI_CONST(S_IRGRP, int, sys/stat.h)
	PSI_CONST(S_IWGRP, int, sys/stat.h)
	PSI_CONST(S_IXGRP, int, sys/stat.h)
	PSI_CONST(S_IRWXO, int, sys/stat.h)
	PSI_CONST(S_IROTH, int, sys/stat.h)
	PSI_CONST(S_IWOTH, int, sys/stat.h)
	PSI_CONST(S_IXOTH, int, sys/stat.h)
	PSI_CONST(S_ISUID, int, sys/stat.h)
	PSI_CONST(S_ISGID, int, sys/stat.h)
	PSI_CONST(UTIME_NOW, int, sys/stat.h)
	PSI_CONST(UTIME_OMIT, int, sys/stat.h)
	PSI_MACRO(S_ISBLK, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISCHR, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISDIR, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISFIFO, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISREG, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISLNK, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_ISSOCK, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_TYPEISMQ, int, [(struct stat *s)], [(s)], sys/stat.h)
	PSI_MACRO(S_TYPEISSEM, int, [(struct stat *s)], [(s)], sys/stat.h)
	PSI_MACRO(S_TYPEISSHM, int, [(struct stat *s)], [(s)], sys/stat.h)
	PSI_MACRO(S_TYPEISTMO, int, [(struct stat *s)], [(s)], sys/stat.h)

	dnl sys/time.h
	AC_CHECK_HEADERS(sys/time.h)
	PSI_STRUCT(struct timeval, [
		[tv_sec],
		[tv_usec]], [
		tv_sec) psi_member_type=$psi_basic_type_time_t ;;
		tv_usec) psi_member_type=$psi_basic_type_suseconds_t ;;
	], sys/time.h)
	PSI_STRUCT(struct itimerval, [
		[it_interval],
		[it_value]], [
		it_*) psi_member_type="struct timeval" ;;
	], sys/time.h)
	PSI_STRUCT(struct timezone, [
		[tz_minuteswest],
		[tz_dsttime]], [
	], sys/time.h)
	PSI_FUNC(getitimer, sys/time.h)
	PSI_FUNC(gettimeofday, sys/time.h)
	PSI_FUNC(setitimer, sys/time.h)
	PSI_FUNC(utimes, sys/time.h)
	PSI_CONST(ITIMER_REAL, int, sys/time.h)
	PSI_CONST(ITIMER_VIRTUAL, int, sys/time.h)
	PSI_CONST(ITIMER_PROF, int, sys/time.h)

	dnl sys/select.h
	AC_CHECK_HEADERS(sys/select.h)
	PSI_STRUCT(fd_set, [], [], sys/select.h)
	PSI_FUNC(select, sys/select.h)
	PSI_FUNC(pselect, sys/select.h)
	PSI_CONST(FD_SETSIZE, int, sys/select.h)
	PSI_MACRO(FD_CLEAR, void, [(int fd, fd_set *s)], [(fd, s)], sys/select.h)
	PSI_MACRO(FD_COPY, void, [(fd_set *s1, fd_set *s2)], [(s1, s2)], sys/select.h)
	PSI_MACRO(FD_CLR, void, [(int fd, fd_set *s)], [(fd, s)], sys/select.h)
	PSI_MACRO(FD_SET, void, [(int fd, fd_set *s)], [(fd, s)], sys/select.h)
	PSI_MACRO(FD_ISSET, int, [(int fd, fd_set *s)], [(fd, s)], sys/select.h)
	PSI_MACRO(FD_ZERO, void, [(fd_set *s)], [(s)], sys/select.h)

	dnl sys/times.h
	AC_CHECK_HEADERS(sys/times.h)
	PSI_FUNC(times, sys/times.h)
	PSI_STRUCT(struct tms, [
		[tms_utime],
		[tms_stime],
		[tms_cutime],
		[tms_cstime]], [
		tms_*) psi_member_type=$psi_basic_type_clock_t ;;
	], sys/times.h)

	dnl sys/utsname.h
	AC_CHECK_HEADERS(sys/utsname.h)
	PSI_FUNC(uname, sys/utsname.h)
	PSI_STRUCT(struct utsname, [
		[sysname],
		[nodename],
		[release],
		[version],
		[machine],
		[domainname]], [
		*) psi_member_type="char@<:@$psi_member_size@:>@" ;;
	], sys/utsname.h)

	dnl time.h
	AC_CHECK_HEADERS(time.h)
	PSI_STRUCT(struct tm, [
		[tm_sec],
		[tm_min],
		[tm_hour],
		[tm_mday],
		[tm_mon],
		[tm_year],
		[tm_wday],
		[tm_yday],
		[tm_isdst]], [
	], time.h)
	PSI_STRUCT(struct timespec, [
		[tv_sec],
		[tv_nsec]], [
		tv_sec) psi_member_type=$psi_basic_type_time_t ;;
	], time.h)
	PSI_FUNC(clock, time.h)
    PSI_FUNC(clock_getcpuclockid, time.h)
    PSI_FUNC(clock_getres, time.h)
    PSI_FUNC(clock_gettime, time.h)
    PSI_FUNC(clock_settime, time.h)
    PSI_FUNC(difftime, time.h)
    PSI_FUNC(mktime, time.h)
    PSI_FUNC(nanosleep, time.h)
    PSI_FUNC(time, time.h)
    PSI_FUNC(timer_delete, time.h)
    PSI_FUNC(timer_getoverrun, time.h)
    PSI_FUNC(timer_gettime, time.h)
    PSI_FUNC(tzset, time.h)
	PSI_CONST(CLOCKS_PER_SEC, int, time.h)
	PSI_CONST(CLOCK_MONOTONIC, int, time.h)
	PSI_CONST(CLOCK_PROCESS_CPUTIME_ID, int, time.h)
	PSI_CONST(CLOCK_REALTIME, int, time.h)
	PSI_CONST(CLOCK_THREAD_CPUTIME_ID, int, time.h)
	PSI_CONST(TIMER_ABSTIME, int, time.h)

	dnl unistd.h
	AC_CHECK_HEADERS(unistd.h)
	PSI_CONST(F_LOCK, int, unistd.h)
	PSI_CONST(F_OK, int, unistd.h)
	PSI_CONST(F_TEST, int, unistd.h)
	PSI_CONST(F_TLOCK, int, unistd.h)
	PSI_CONST(F_ULOCK, int, unistd.h)
	PSI_CONST(R_OK, int, unistd.h)
	PSI_CONST(STDERR_FILENO, int, unistd.h)
	PSI_CONST(STDIN_FILENO, int, unistd.h)
	PSI_CONST(STDOUT_FILENO, int, unistd.h)
	PSI_CONST(W_OK, int, unistd.h)
	PSI_CONST(X_OK, int, unistd.h)
	PSI_CONST(_CS_PATH, int, unistd.h)
	PSI_CONST(_PC_ALLOC_SIZE_MIN, int, unistd.h)
	PSI_CONST(_PC_ASYNC_IO, int, unistd.h)
	PSI_CONST(_PC_CHOWN_RESTRICTED, int, unistd.h)
	PSI_CONST(_PC_FILESIZEBITS, int, unistd.h)
	PSI_CONST(_PC_LINK_MAX, int, unistd.h)
	PSI_CONST(_PC_MAX_CANON, int, unistd.h)
	PSI_CONST(_PC_MAX_INPUT, int, unistd.h)
	PSI_CONST(_PC_NAME_MAX, int, unistd.h)
	PSI_CONST(_PC_NO_TRUNC, int, unistd.h)
	PSI_CONST(_PC_PATH_MAX, int, unistd.h)
	PSI_CONST(_PC_PIPE_BUF, int, unistd.h)
	PSI_CONST(_PC_PRIO_IO, int, unistd.h)
	PSI_CONST(_PC_REC_INCR_XFER_SIZE, int, unistd.h)
	PSI_CONST(_PC_REC_MAX_XFER_SIZE, int, unistd.h)
	PSI_CONST(_PC_REC_MIN_XFER_SIZE, int, unistd.h)
	PSI_CONST(_PC_REC_XFER_ALIGN, int, unistd.h)
	PSI_CONST(_PC_SYMLINK_MAX, int, unistd.h)
	PSI_CONST(_PC_SYNC_IO, int, unistd.h)
	PSI_CONST(_PC_TIMESTAMP_RESOLUTION, int, unistd.h)
	PSI_CONST(_PC_VDISABLE, int, unistd.h)
	PSI_CONST(_POSIX_ADVISORY_INFO, int, unistd.h)
	PSI_CONST(_POSIX_ASYNCHRONOUS_IO, int, unistd.h)
	PSI_CONST(_POSIX_ASYNC_IO, int, unistd.h)
	PSI_CONST(_POSIX_BARRIERS, int, unistd.h)
	PSI_CONST(_POSIX_CHOWN_RESTRICTED, int, unistd.h)
	PSI_CONST(_POSIX_CLOCK_SELECTION, int, unistd.h)
	PSI_CONST(_POSIX_CPUTIME, int, unistd.h)
	PSI_CONST(_POSIX_FSYNC, int, unistd.h)
	PSI_CONST(_POSIX_JOB_CONTROL, int, unistd.h)
	PSI_CONST(_POSIX_MAPPED_FILES, int, unistd.h)
	PSI_CONST(_POSIX_MEMLOCK, int, unistd.h)
	PSI_CONST(_POSIX_MEMLOCK_RANGE, int, unistd.h)
	PSI_CONST(_POSIX_MEMORY_PROTECTION, int, unistd.h)
	PSI_CONST(_POSIX_MESSAGE_PASSING, int, unistd.h)
	PSI_CONST(_POSIX_MONOTONIC_CLOCK, int, unistd.h)
	PSI_CONST(_POSIX_NO_TRUNC, int, unistd.h)
	PSI_CONST(_POSIX_PRIORITIZED_IO, int, unistd.h)
	PSI_CONST(_POSIX_PRIORITY_SCHEDULING, int, unistd.h)
	PSI_CONST(_POSIX_PRIO_IO, int, unistd.h)
	PSI_CONST(_POSIX_RAW_SOCKETS, int, unistd.h)
	PSI_CONST(_POSIX_READER_WRITER_LOCKS, int, unistd.h)
	PSI_CONST(_POSIX_REALTIME_SIGNALS, int, unistd.h)
	PSI_CONST(_POSIX_REGEXP, int, unistd.h)
	PSI_CONST(_POSIX_SAVED_IDS, int, unistd.h)
	PSI_CONST(_POSIX_SEMAPHORES, int, unistd.h)
	PSI_CONST(_POSIX_SHARED_MEMORY_OBJECTS, int, unistd.h)
	PSI_CONST(_POSIX_SHELL, int, unistd.h)
	PSI_CONST(_POSIX_SPAWN, int, unistd.h)
	PSI_CONST(_POSIX_SPIN_LOCKS, int, unistd.h)
	PSI_CONST(_POSIX_SPORADIC_SERVER, int, unistd.h)
	PSI_CONST(_POSIX_SYNCHRONIZED_IO, int, unistd.h)
	PSI_CONST(_POSIX_SYNC_IO, int, unistd.h)
	PSI_CONST(_POSIX_THREADS, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_ATTR_STACKADDR, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_ATTR_STACKSIZE, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_CPUTIME, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_PRIORITY_SCHEDULING, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_PRIO_INHERIT, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_PRIO_PROTECT, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_PROCESS_SHARED, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_ROBUST_PRIO_INHERIT, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_ROBUST_PRIO_PROTECT, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_SAFE_FUNCTIONS, int, unistd.h)
	PSI_CONST(_POSIX_THREAD_SPORADIC_SERVER, int, unistd.h)
	PSI_CONST(_POSIX_TIMEOUTS, int, unistd.h)
	PSI_CONST(_POSIX_TIMERS, int, unistd.h)
	PSI_CONST(_POSIX_TIMESTAMP_RESOLUTION, int, unistd.h)
	PSI_CONST(_POSIX_TRACE, int, unistd.h)
	PSI_CONST(_POSIX_TRACE_EVENT_FILTER, int, unistd.h)
	PSI_CONST(_POSIX_TRACE_INHERIT, int, unistd.h)
	PSI_CONST(_POSIX_TRACE_LOG, int, unistd.h)
	PSI_CONST(_POSIX_TYPED_MEMORY_OBJECTS, int, unistd.h)
	PSI_CONST(_POSIX_VDISABLE, int, unistd.h)
	PSI_CONST(_POSIX_VERSION, int, unistd.h)
	PSI_CONST(_SC_ADVISORY_INFO, int, unistd.h)
	PSI_CONST(_SC_AIO_LISTIO_MAX, int, unistd.h)
	PSI_CONST(_SC_AIO_MAX, int, unistd.h)
	PSI_CONST(_SC_AIO_PRIO_DELTA_MAX, int, unistd.h)
	PSI_CONST(_SC_ARG_MAX, int, unistd.h)
	PSI_CONST(_SC_ASYNCHRONOUS_IO, int, unistd.h)
	PSI_CONST(_SC_ATEXIT_MAX, int, unistd.h)
	PSI_CONST(_SC_BARRIERS, int, unistd.h)
	PSI_CONST(_SC_BC_BASE_MAX, int, unistd.h)
	PSI_CONST(_SC_BC_DIM_MAX, int, unistd.h)
	PSI_CONST(_SC_BC_SCALE_MAX, int, unistd.h)
	PSI_CONST(_SC_BC_STRING_MAX, int, unistd.h)
	PSI_CONST(_SC_CHILD_MAX, int, unistd.h)
	PSI_CONST(_SC_CLK_TCK, int, unistd.h)
	PSI_CONST(_SC_CLOCK_SELECTION, int, unistd.h)
	PSI_CONST(_SC_COLL_WEIGHTS_MAX, int, unistd.h)
	PSI_CONST(_SC_CPUTIME, int, unistd.h)
	PSI_CONST(_SC_DELAYTIMER_MAX, int, unistd.h)
	PSI_CONST(_SC_EXPR_NEST_MAX, int, unistd.h)
	PSI_CONST(_SC_FSYNC, int, unistd.h)
	PSI_CONST(_SC_GETGR_R_SIZE_MAX, int, unistd.h)
	PSI_CONST(_SC_GETPW_R_SIZE_MAX, int, unistd.h)
	PSI_CONST(_SC_HOST_NAME_MAX, int, unistd.h)
	PSI_CONST(_SC_IOV_MAX, int, unistd.h)
	PSI_CONST(_SC_JOB_CONTROL, int, unistd.h)
	PSI_CONST(_SC_LINE_MAX, int, unistd.h)
	PSI_CONST(_SC_LOGIN_NAME_MAX, int, unistd.h)
	PSI_CONST(_SC_MAPPED_FILES, int, unistd.h)
	PSI_CONST(_SC_MEMLOCK, int, unistd.h)
	PSI_CONST(_SC_MEMLOCK_RANGE, int, unistd.h)
	PSI_CONST(_SC_MEMORY_PROTECTION, int, unistd.h)
	PSI_CONST(_SC_MESSAGE_PASSING, int, unistd.h)
	PSI_CONST(_SC_MONOTONIC_CLOCK, int, unistd.h)
	PSI_CONST(_SC_MQ_OPEN_MAX, int, unistd.h)
	PSI_CONST(_SC_MQ_PRIO_MAX, int, unistd.h)
	PSI_CONST(_SC_NGROUPS_MAX, int, unistd.h)
	PSI_CONST(_SC_OPEN_MAX, int, unistd.h)
	PSI_CONST(_SC_PAGESIZE, int, unistd.h)
	PSI_CONST(_SC_PAGE_SIZE, int, unistd.h)
	PSI_CONST(_SC_PRIORITIZED_IO, int, unistd.h)
	PSI_CONST(_SC_PRIORITY_SCHEDULING, int, unistd.h)
	PSI_CONST(_SC_RAW_SOCKETS, int, unistd.h)
	PSI_CONST(_SC_READER_WRITER_LOCKS, int, unistd.h)
	PSI_CONST(_SC_REALTIME_SIGNALS, int, unistd.h)
	PSI_CONST(_SC_REGEXP, int, unistd.h)
	PSI_CONST(_SC_RE_DUP_MAX, int, unistd.h)
	PSI_CONST(_SC_RTSIG_MAX, int, unistd.h)
	PSI_CONST(_SC_SAVED_IDS, int, unistd.h)
	PSI_CONST(_SC_SEMAPHORES, int, unistd.h)
	PSI_CONST(_SC_SEM_NSEMS_MAX, int, unistd.h)
	PSI_CONST(_SC_SEM_VALUE_MAX, int, unistd.h)
	PSI_CONST(_SC_SHARED_MEMORY_OBJECTS, int, unistd.h)
	PSI_CONST(_SC_SHELL, int, unistd.h)
	PSI_CONST(_SC_SIGQUEUE_MAX, int, unistd.h)
	PSI_CONST(_SC_SPAWN, int, unistd.h)
	PSI_CONST(_SC_SPIN_LOCKS, int, unistd.h)
	PSI_CONST(_SC_SPORADIC_SERVER, int, unistd.h)
	PSI_CONST(_SC_SS_REPL_MAX, int, unistd.h)
	PSI_CONST(_SC_STREAM_MAX, int, unistd.h)
	PSI_CONST(_SC_SYMLOOP_MAX, int, unistd.h)
	PSI_CONST(_SC_SYNCHRONIZED_IO, int, unistd.h)
	PSI_CONST(_SC_THREADS, int, unistd.h)
	PSI_CONST(_SC_THREAD_ATTR_STACKADDR, int, unistd.h)
	PSI_CONST(_SC_THREAD_ATTR_STACKSIZE, int, unistd.h)
	PSI_CONST(_SC_THREAD_CPUTIME, int, unistd.h)
	PSI_CONST(_SC_THREAD_DESTRUCTOR_ITERATIONS, int, unistd.h)
	PSI_CONST(_SC_THREAD_KEYS_MAX, int, unistd.h)
	PSI_CONST(_SC_THREAD_PRIORITY_SCHEDULING, int, unistd.h)
	PSI_CONST(_SC_THREAD_PRIO_INHERIT, int, unistd.h)
	PSI_CONST(_SC_THREAD_PRIO_PROTECT, int, unistd.h)
	PSI_CONST(_SC_THREAD_PROCESS_SHARED, int, unistd.h)
	PSI_CONST(_SC_THREAD_ROBUST_PRIO_INHERIT, int, unistd.h)
	PSI_CONST(_SC_THREAD_ROBUST_PRIO_PROTECT, int, unistd.h)
	PSI_CONST(_SC_THREAD_SAFE_FUNCTIONS, int, unistd.h)
	PSI_CONST(_SC_THREAD_SPORADIC_SERVER, int, unistd.h)
	PSI_CONST(_SC_THREAD_STACK_MIN, int, unistd.h)
	PSI_CONST(_SC_THREAD_THREADS_MAX, int, unistd.h)
	PSI_CONST(_SC_TIMEOUTS, int, unistd.h)
	PSI_CONST(_SC_TIMERS, int, unistd.h)
	PSI_CONST(_SC_TIMER_MAX, int, unistd.h)
	PSI_CONST(_SC_TRACE, int, unistd.h)
	PSI_CONST(_SC_TRACE_EVENT_FILTER, int, unistd.h)
	PSI_CONST(_SC_TRACE_EVENT_NAME_MAX, int, unistd.h)
	PSI_CONST(_SC_TRACE_INHERIT, int, unistd.h)
	PSI_CONST(_SC_TRACE_LOG, int, unistd.h)
	PSI_CONST(_SC_TRACE_NAME_MAX, int, unistd.h)
	PSI_CONST(_SC_TRACE_SYS_MAX, int, unistd.h)
	PSI_CONST(_SC_TRACE_USER_EVENT_MAX, int, unistd.h)
	PSI_CONST(_SC_TTY_NAME_MAX, int, unistd.h)
	PSI_CONST(_SC_TYPED_MEMORY_OBJECTS, int, unistd.h)
	PSI_CONST(_SC_TZNAME_MAX, int, unistd.h)
	PSI_CONST(_SC_VERSION, int, unistd.h)
	PSI_CONST(_SC_XOPEN_CRYPT, int, unistd.h)
	PSI_CONST(_SC_XOPEN_REALTIME, int, unistd.h)
	PSI_CONST(_SC_XOPEN_REALTIME_THREADS, int, unistd.h)
	PSI_CONST(_SC_XOPEN_SHM, int, unistd.h)
	PSI_CONST(_SC_XOPEN_STREAMS, int, unistd.h)
	PSI_CONST(_SC_XOPEN_UNIX, int, unistd.h)
	PSI_CONST(_SC_XOPEN_UUCP, int, unistd.h)
	PSI_CONST(_SC_XOPEN_VERSION, int, unistd.h)
	PSI_CONST(_XOPEN_CRYPT, int, unistd.h)
	PSI_CONST(_XOPEN_REALTIME, int, unistd.h)
	PSI_CONST(_XOPEN_REALTIME_THREADS, int, unistd.h)
	PSI_CONST(_XOPEN_SHM, int, unistd.h)
	PSI_CONST(_XOPEN_STREAMS, int, unistd.h)
	PSI_CONST(_XOPEN_UNIX, int, unistd.h)
	PSI_CONST(_XOPEN_UUCP, int, unistd.h)
	PSI_CONST(_XOPEN_VERSION, int, unistd.h)
	PSI_FUNC(access, unistd.h)
    PSI_FUNC(alarm, unistd.h)
    PSI_FUNC(chdir, unistd.h)
    PSI_FUNC(chown, unistd.h)
    PSI_FUNC(close, unistd.h)
    PSI_FUNC(confstr, unistd.h)
    PSI_FUNC(dup, unistd.h)
    PSI_FUNC(dup2, unistd.h)
    PSI_FUNC(_exit, unistd.h)
    PSI_FUNC(faccessat, unistd.h)
    PSI_FUNC(fchdir, unistd.h)
    PSI_FUNC(fchown, unistd.h)
    PSI_FUNC(fchownat, unistd.h)
    PSI_FUNC(fdatasync, unistd.h)
    PSI_FUNC(fork, unistd.h)
    PSI_FUNC(fpathconf, unistd.h)
    PSI_FUNC(fsync, unistd.h)
    PSI_FUNC(ftruncate, unistd.h)
    PSI_FUNC(getegid, unistd.h)
    PSI_FUNC(geteuid, unistd.h)
    PSI_FUNC(getgid, unistd.h)
    PSI_FUNC(gethostid, unistd.h)
    PSI_FUNC(gethostname, unistd.h)
    PSI_FUNC(getlogin_r, unistd.h)
    PSI_FUNC(getpgid, unistd.h)
    PSI_FUNC(getpgrp, unistd.h)
    PSI_FUNC(getpid, unistd.h)
    PSI_FUNC(getppid, unistd.h)
    PSI_FUNC(getsid, unistd.h)
    PSI_FUNC(getuid, unistd.h)
    PSI_FUNC(isatty, unistd.h)
    PSI_FUNC(lchown, unistd.h)
    PSI_FUNC(link, unistd.h)
    PSI_FUNC(linkat, unistd.h)
    PSI_FUNC(lockf, unistd.h)
    PSI_FUNC(lseek, unistd.h)
    PSI_FUNC(nice, unistd.h)
    PSI_FUNC(pathconf, unistd.h)
    PSI_FUNC(pause, unistd.h)
    PSI_FUNC(pread, unistd.h)
    PSI_FUNC(pwrite, unistd.h)
    PSI_FUNC(read, unistd.h)
    PSI_FUNC(readlink, unistd.h)
    PSI_FUNC(readlinkat, unistd.h)
    PSI_FUNC(rmdir, unistd.h)
    PSI_FUNC(setegid, unistd.h)
    PSI_FUNC(seteuid, unistd.h)
    PSI_FUNC(setgid, unistd.h)
    PSI_FUNC(setpgid, unistd.h)
    PSI_FUNC(setpgrp, unistd.h)
    PSI_FUNC(setregid, unistd.h)
    PSI_FUNC(setreuid, unistd.h)
    PSI_FUNC(setsid, unistd.h)
    PSI_FUNC(setuid, unistd.h)
    PSI_FUNC(sleep, unistd.h)
    PSI_FUNC(swab, unistd.h)
    PSI_FUNC(symlink, unistd.h)
    PSI_FUNC(symlinkat, unistd.h)
    PSI_FUNC(sync, unistd.h)
    PSI_FUNC(sysconf, unistd.h)
    PSI_FUNC(tcgetpgrp, unistd.h)
    PSI_FUNC(tcsetpgrp, unistd.h)
    PSI_FUNC(truncate, unistd.h)
    PSI_FUNC(ttyname_r, unistd.h)
    PSI_FUNC(unlink, unistd.h)
    PSI_FUNC(unlinkat, unistd.h)
    PSI_FUNC(write, unistd.h)
	PSI_DECL(optarg, char *, unistd.h)
	PSI_DECL(opterr, int, unistd.h)
	PSI_DECL(optind, int, unistd.h)
	PSI_DECL(optopt, int, unistd.h)

	dnl wchar.h
	AC_CHECK_HEADERS(wchar.h)
	PSI_TYPE(wint_t, int, wchar.h)
	PSI_CONST(WINT_MIN, int, wchar.h)
	PSI_CONST(WINT_MAX, int, wchar.h)
	PSI_CONST(WEOF, int, wchar.h)

	AC_DEFINE_UNQUOTED(PHP_PSI_FUNCS, $PSI_FUNCS, Redirected functions)
	AC_DEFINE_UNQUOTED(PHP_PSI_MACROS, $PSI_MACROS, Exported macros)
	AC_DEFINE_UNQUOTED(PHP_PSI_TYPES, $PSI_TYPES, Predefined types)
	AC_DEFINE_UNQUOTED(PHP_PSI_CONSTS, $PSI_CONSTS, Predefined constants)
	AC_DEFINE_UNQUOTED(PHP_PSI_STRUCTS, $PSI_STRUCTS, Predefined structs)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, ["]$SHLIB_SUFFIX_NAME["], DL suffix)

	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

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
fi
