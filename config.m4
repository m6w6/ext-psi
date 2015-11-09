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
		local psi_type_lower=`tr A-Z a-z <<<$1`
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
			echo "PSI_T_NAME, \"$1\""
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
	

	PSI_CONSTS=""
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
	
	dnl PSI_CONST(const name, type, headers to include)
	AC_DEFUN(PSI_CONST, [
		AC_CACHE_CHECK(value of $1, psi_cv_const_$1, [
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
				PSI_CONSTS="{PSI_T_STRING, \"string\", \"$1\", $psi_cv_const_$1, PSI_T_QUOTED_STRING}, $PSI_CONSTS"
				;;
			*)
				PSI_CONSTS="{PSI_T_INT, \"int\", \"$1\", \"$psi_cv_const_$1\", PSI_T_NUMBER}, $PSI_CONSTS"
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
			[The offset of `$1' in `$2', as computed by offsetof.]
		)
	])

	dnl PSI_STRUCT(name, members, member type cases, includes)
	PSI_STRUCTS=
	AC_DEFUN(PSI_STRUCT, [
		psi_struct_members=
		m4_foreach(member, [$2], [
			AC_CHECK_MEMBER(struct $1.member, [
				case member in
				$3
				*) psi_member_type=int ;;
				esac
				AC_CHECK_SIZEOF(struct_$1[_]member, [], PSI_INCLUDES_DEFAULT($4,
					[#define struct_$1_]member ((struct $1 *)0)->member
				))
				PSI_CHECK_OFFSETOF(struct $1, member, PSI_INCLUDES_DEFAULT($4))
				# pointer level
				psi_struct_member_pl=`echo $psi_member_type | tr -cd '*' | wc -c`
				# array size
				psi_struct_member_as=`echo $psi_member_type | $AWK -F'\x5b\x5d\x5b\x5d' 'END {print 0} /\\x5b\x5b\x5b:digit:\x5d\x5d+\\x5d/ {print$[]2; exit}'`
				if test $psi_struct_member_as -gt 0
				then
					psi_struct_member_pl=`expr $psi_struct_member_pl + 1`
				fi
				psi_struct_members="{`psi_type_pair $psi_member_type $ac_cv_sizeof_struct_$1[]_[]member`, \"[]member[]\", $ac_cv_offsetof_struct_$1[]_[]member, $ac_cv_sizeof_struct_$1[]_[]member, $psi_struct_member_pl, $psi_struct_member_as}, $psi_struct_members"
			], [], PSI_INCLUDES_DEFAULT($4))
		])
		PSI_STRUCTS="{\"$1\", {$psi_struct_members}}, $PSI_STRUCTS"
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
	dnl stdlib.h
	PSI_CONST(EXIT_FAILURE, int)
	PSI_CONST(EXIT_SUCCESS, int)
	PSI_CONST(RAND_MAX, int)
	PSI_CONST(MB_CUR_MAX, int)
	dnl sys/stat.h
	PSI_STRUCT(stat, [
		[st_dev], 
		[st_ino], 
		[st_mode], 
		[st_nlink], 
		[st_uid], 
		[st_gid], 
		[st_rdev], 
		[st_size], 
		[st_atim], 
		[st_mtim], 
		[st_ctim], 
		[st_blksize], 
		[st_blocks]], [
		st_?tim) psi_member_type="struct timespec" ;;
	], sys/stat.h)
	dnl sys/time.h
	PSI_CONST(ITIMER_REAL, int, sys/time.h)
	PSI_CONST(ITIMER_VIRTUAL, int, sys/time.h)
	PSI_CONST(ITIMER_PROF, int, sys/time.h)
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
	

	AC_DEFINE_UNQUOTED(PHP_PSI_TYPES, $PSI_TYPES, Predefined types)
	AC_DEFINE_UNQUOTED(PHP_PSI_CONSTS, $PSI_CONSTS, Predefined constants)
	AC_DEFINE_UNQUOTED(PHP_PSI_STRUCTS, $PSI_STRUCTS, Predefined structs)

	PHP_PSI_SRCDIR=PHP_EXT_SRCDIR(psi)
	PHP_PSI_BUILDDIR=PHP_EXT_BUILDDIR(psi)

	PHP_ADD_INCLUDE($PHP_PSI_SRCDIR/src)
	PHP_ADD_BUILD_DIR($PHP_PSI_BUILDDIR/src)

	PHP_PSI_HEADERS=`(cd $PHP_PSI_SRCDIR/src && echo *.h)`
	PHP_PSI_SOURCES="src/parser_proc.c src/parser.c src/validator.c src/module.c src/context.c"
	PHP_PSI_SOURCES="$PHP_PSI_SOURCES src/libjit.c src/libffi.c"

	PHP_NEW_EXTENSION(psi, $PHP_PSI_SOURCES, $ext_shared)
	PHP_INSTALL_HEADERS(ext/psi, php_psi.h $PHP_PSI_HEADERS)

	PHP_SUBST(PHP_PSI_HEADERS)
	PHP_SUBST(PHP_PSI_SOURCES)

	PHP_SUBST(PHP_PSI_SRCDIR)
	PHP_SUBST(PHP_PSI_BUILDDIR)

	PHP_ADD_MAKEFILE_FRAGMENT
fi
