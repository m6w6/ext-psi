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

	psi_type_pair() { # (type, size)
		local psi_type_name=`tr -cd A-Za-z <<<$1`
		local psi_type_lower=`tr A-Z a-z <<<$psi_type_name`
		case $psi_type_lower in
		int*|uint*)
			local psi_type_upper=`tr a-z A-Z <<<$1`
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
		ifdef(AC_TYPE_[]patsubst(translit($1,a-z,A-Z),\W,_),AC_TYPE_[]patsubst(translit($1,a-z,A-Z),\W,_))
		AC_CHECK_SIZEOF($1, [], PSI_INCLUDES_DEFAULT($3))
		if test "$2" && test "$ac_cv_sizeof_[]$1" -gt 0; then
			PSI_TYPES="{`psi_type_pair $2 $ac_cv_sizeof_[]$1`, \""$1"\"}, $PSI_TYPES"
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

	dnl PSI_STRUCT(name, members, member type cases, includes)
	PSI_STRUCTS=
	AC_DEFUN(PSI_STRUCT, [
		AC_CHECK_SIZEOF(struct $1, [], PSI_INCLUDES_DEFAULT($4))
		psi_struct_size=$ac_cv_sizeof_struct_$1
		psi_struct_members=
		m4_foreach(member, [$2], [
			AC_CHECK_MEMBER(struct $1.member, [
				psi_member_name=member
				AC_CHECK_SIZEOF(struct_$1[_]member, [], PSI_INCLUDES_DEFAULT($4,
					[#define struct_$1_]member ((struct $1 *)0)->member
				))
				psi_member_size=$ac_cv_sizeof_struct_$1[]_[]member
				PSI_CHECK_OFFSETOF(struct $1, member, PSI_INCLUDES_DEFAULT($4))
				psi_member_offset=$ac_cv_offsetof_struct_$1[]_[]member
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
		PSI_STRUCTS="{\"$1\", $psi_struct_size, {$psi_struct_members}}, $PSI_STRUCTS"
	])

	PSI_INCLUDES=
	AC_PROG_NM
	AC_PROG_AWK
	PSI_FUNCS=
	dnl PSI_FUNC(fn)
	AC_DEFUN(PSI_FUNC, [
		psi_symbol=$1
		AC_CACHE_CHECK(for $1, psi_cv_fn_$1, [
			psi_symbol_redirect=
			AC_TRY_LINK_FUNC($1, [
				psi_symbol_redirect=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/ U .*$1.*/ {print$[]3}'`
			])
			case "$psi_symbol_redirect" in
			"_$psi_symbol"|"$psi_symbol"|"")
				psi_cv_fn_$1=$psi_symbol
				;;
			*)
				psi_cv_fn_$1=$psi_symbol_redirect
				;;
			esac
		])
		if test "$psi_cv_fn_$1" != "$psi_symbol"
		then
			PSI_FUNCS="{\"$psi_symbol\", (void *) $psi_symbol}, $PSI_FUNCS"
		fi
	])

	PSI_MACROS=
	dnl PSI_MACRO(macro, return type, decl args, call args, include)
	AC_DEFUN(PSI_MACRO, [
		AC_CHECK_DECL($1$3, [
			PSI_MACROS="static $2 psi_macro_$1$3 {return $1$4;} $PSI_MACROS"
			PSI_FUNCS="{\"$1\", (void *) psi_macro_$1}, $PSI_FUNCS"
		], [], PSI_INCLUDES_DEFAULT($5))
	])

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

	dnl errno.h
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
	dnl stdint.h
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
	AC_CHECK_TYPE(wchar_t, [
		AX_CHECK_SIGN(wchar_t, psi_wchar_t=int, psi_wchar_t=uint)
		PSI_TYPE(wchar_t, $psi_wchar_t)
		PSI_CONST(WCHAR_MIN, int)
		PSI_CONST(WCHAR_MAX, int)
	])

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
	PSI_FUNC(clearerr)
	PSI_FUNC(ctermid)
	PSI_FUNC(dprintf)
	PSI_FUNC(fclose)
	PSI_FUNC(fdopen)
	PSI_FUNC(feof)
	PSI_FUNC(ferror)
	PSI_FUNC(fflush)
	PSI_FUNC(fgetc)
	PSI_FUNC(fgetpos)
	PSI_FUNC(fgets)
	PSI_FUNC(fileno)
	PSI_FUNC(flockfile)
	PSI_FUNC(fmemopen)
	PSI_FUNC(fopen)
	PSI_FUNC(fprintf)
	PSI_FUNC(fputc)
	PSI_FUNC(fputs)
	PSI_FUNC(fread)
	PSI_FUNC(freopen)
	PSI_FUNC(fscanf)
	PSI_FUNC(fseek)
	PSI_FUNC(fseeko)
	PSI_FUNC(fsetpos)
	PSI_FUNC(ftell)
	PSI_FUNC(ftello)
	PSI_FUNC(ftrylockfile)
	PSI_FUNC(funlockfile)
	PSI_FUNC(fwrite)
	PSI_FUNC(getc)
	PSI_FUNC(getchar)
	PSI_FUNC(getc_unlocked)
	PSI_FUNC(getchar_unlocked)
	PSI_FUNC(getdelim)
	PSI_FUNC(getline)
	PSI_FUNC(gets)
	PSI_FUNC(open_memstream)
	PSI_FUNC(pclose)
	PSI_FUNC(perror)
	PSI_FUNC(popen)
	PSI_FUNC(printf)
	PSI_FUNC(putc)
	PSI_FUNC(putchar)
	PSI_FUNC(putc_unlocked)
	PSI_FUNC(putchar_unlocked)
	PSI_FUNC(puts)
	PSI_FUNC(remove)
	PSI_FUNC(rename)
	PSI_FUNC(renameat)
	PSI_FUNC(rewind)
	PSI_FUNC(scanf)
	PSI_FUNC(setbuf)
	PSI_FUNC(setvbuf)
	PSI_FUNC(snprintf)
	PSI_FUNC(sprintf)
	PSI_FUNC(sscanf)
	PSI_FUNC(tempnam)
	PSI_FUNC(tmpfile)
	PSI_FUNC(tmpnam)
	PSI_FUNC(ungetc)
	PSI_FUNC(vdprintf)
	PSI_FUNC(vfprintf)
	PSI_FUNC(vfscanf)
	PSI_FUNC(vprintf)
	PSI_FUNC(vscanf)
	PSI_FUNC(vsnprintf)
	PSI_FUNC(vsprintf)
	PSI_FUNC(vsscanf)

	dnl stdlib.h
	PSI_CONST(EXIT_FAILURE, int)
	PSI_CONST(EXIT_SUCCESS, int)
	PSI_CONST(RAND_MAX, int)
	PSI_CONST(MB_CUR_MAX, int)
	dnl sys/stat.h
	PSI_FUNC(chmod)
	PSI_FUNC(fchmod)
	PSI_FUNC(fchmodat)
	PSI_FUNC(fstat)
	PSI_FUNC(fstatat)
	PSI_FUNC(futimens)
	PSI_FUNC(lstat)
	PSI_FUNC(mkdir)
	PSI_FUNC(mkdirat)
	PSI_FUNC(mkfifo)
	PSI_FUNC(mkfifoat)
	PSI_FUNC(mknod)
	PSI_FUNC(mknodat)
	PSI_FUNC(stat)
	PSI_FUNC(umask)
	PSI_FUNC(utimensat)
	PSI_STRUCT(stat, [
		[st_dev],
		[st_ino],
		[st_mode],
		[st_nlink],
		[st_uid],
		[st_gid],
		[st_rdev],
		[st_size],
		[st_atim], [st_atimespec],
		[st_mtim], [st_mtimespec],
		[st_ctim], [st_ctimespec],
		[st_birthtimespec],
		[st_blksize],
		[st_blocks],
		[st_flags],
		[st_gen]], [
		st_?tim) psi_member_type="struct timespec" ;;
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
	PSI_MACRO(S_TYPEISMQ, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_TYPEISSEM, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_TYPEISSHM, int, [(mode_t m)], [(m)], sys/stat.h)
	PSI_MACRO(S_TYPEISTMO, int, [(mode_t m)], [(m)], sys/stat.h)
	dnl sys/time.h
	PSI_STRUCT(timeval, [
		[tv_sec],
		[tv_usec]], [
	], sys/time.h)
	PSI_STRUCT(itimerval, [
		[it_interval],
		[it_value]], [
		it_*) psi_member_type="struct timeval" ;;
	], sys/time.h)
	PSI_STRUCT(timezone, [
		[tz_minuteswest],
		[tz_dsttime]], [
	], sys/time.h)
	PSI_CONST(ITIMER_REAL, int, sys/time.h)
	PSI_CONST(ITIMER_VIRTUAL, int, sys/time.h)
	PSI_CONST(ITIMER_PROF, int, sys/time.h)
	dnl sys/times.h
	PSI_FUNC(times)
	PSI_STRUCT(tms, [
		[tms_utime],
		[tms_stime],
		[tms_cutime],
		[tms_cstime]], [
	], sys/times.h)
	dnl sys/types.h
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
	PSI_TYPE(uid_t)
	dnl sys/utsname.h
	PSI_FUNC(uname)
	PSI_STRUCT(utsname, [
		[sysname],
		[nodename],
		[release],
		[version],
		[machine],
		[domainname]], [
		*) psi_member_type="char@<:@$psi_member_size@:>@" ;;
	], sys/utsname.h)
	dnl time.h
	PSI_STRUCT(tm, [
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
	PSI_STRUCT(timespec, [
		[tv_sec],
		[tv_nsec]], [
	], time.h)
	PSI_CONST(CLOCKS_PER_SEC, int, time.h)
	PSI_CONST(CLOCK_MONOTONIC, int, time.h)
	PSI_CONST(CLOCK_PROCESS_CPUTIME_ID, int, time.h)
	PSI_CONST(CLOCK_REALTIME, int, time.h)
	PSI_CONST(CLOCK_THREAD_CPUTIME_ID, int, time.h)
	PSI_CONST(TIMER_ABSTIME, int, time.h)
	dnl wchar.h
	AC_CHECK_TYPE(wint_t, [
		AX_CHECK_SIGN(wint_t, psi_wint_t=int, psi_wint_t=uint)
		PSI_TYPE(wint_t, $psi_wint_t, wchar.h)
		PSI_CONST(WINT_MIN, int, wchar.h)
		PSI_CONST(WINT_MAX, int, wchar.h)
		PSI_CONST(WEOF, int, wchar.h)
	], [], [
		AC_INCLUDES_DEFAULT()
		#include <wchar.h>
	])


	AC_DEFINE_UNQUOTED(PHP_PSI_FUNCS, $PSI_FUNCS, Redirected functions)
	AC_DEFINE_UNQUOTED(PHP_PSI_MACROS, $PSI_MACROS, Exported macros)
	AC_DEFINE_UNQUOTED(PHP_PSI_TYPES, $PSI_TYPES, Predefined types)
	AC_DEFINE_UNQUOTED(PHP_PSI_CONSTS, $PSI_CONSTS, Predefined constants)
	AC_DEFINE_UNQUOTED(PHP_PSI_STRUCTS, $PSI_STRUCTS, Predefined structs)

	AC_DEFINE_UNQUOTED(PHP_PSI_SHLIB_SUFFIX, $SHLIB_SUFFIX_NAME, DL suffix)

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
