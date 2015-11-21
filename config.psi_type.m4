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
	void)
		echo "PSI_T_VOID, \"void\""
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
	AC_CHECK_SIZEOF($1, [], PSI_INCLUDES)
	psi_basic_type=$2
	case $psi_basic_type in
	int)
		AX_CHECK_SIGN($1, :, [
			psi_basic_type=uint
		], $psi_header)
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

PSI_CONSTS=""
# add_str_const(name, value)
add_str_const() {
	PSI_CONSTS="{PSI_T_STRING, \"string\", \"psi\\\\$1\", $2, PSI_T_QUOTED_STRING}, $PSI_CONSTS"
}
# add_int_const(name, value)
add_int_const() {
	PSI_CONSTS="{PSI_T_INT, \"int\", \"psi\\\\$1\", \"$2\", PSI_T_NUMBER}, $PSI_CONSTS"
}
dnl PSI_CONST(const name, type)
AC_DEFUN(PSI_CONST, [
	AC_CACHE_CHECK(value of $1, psi_cv_const_$1, [
		psi_const_val=
		case $2 in
		str*)
			if test "$cross_compiling" = "yes"
			then
				AC_TRY_CPP(PSI_INCLUDES $1, psi_const_val=`eval "$ac_try|tail -n1"`, psi_const_val=)
			else
				PSI_COMPUTE_STR(psi_const_val, $1, PSI_INCLUDES)
			fi
			;;
		int)
			AC_COMPUTE_INT(psi_const_val, $1, PSI_INCLUDES)
			;;
		esac
		psi_cv_const_$1=$psi_const_val
	])
	if test "$psi_cv_const_$1"
	then
		case $2 in
		str*)
			add_str_const "$1" "$psi_cv_const_$1"
			;;
		int)
			add_int_const "$1" "$psi_cv_const_$1"
			;;
		esac
	fi
])

PSI_DECLS=
# add_decl(ret type, symbol, args)
add_decl() {
	local size
	eval size=\$ac_cv_sizeof_$1
	PSI_DECLS="{`psi_type_pair \"$1\" \"$size\"`, \"$2\"}, $PSI_DECLS"
}
PSI_REDIR=
# add_redir(symbol, macro=symbol)
add_redir() {
	local sym=$2
	test -z "$sym" && sym=$1
	PSI_REDIR="{\"$1\", (void (*)(void)) $sym}, $PSI_REDIR"
}
# arg_names(typed args)
arg_names() {
	AS_ECHO_N([$1]) \
		| tr -cd '()' \
		| $AWK -F, '{for (i=1;i<NF;++i) print $i ","; print $NF}' \
		| $AWK '{print $NF}' \
		| xargs
}
PSI_MACROS=
# gen_macro(ret type, symbol, args)
gen_macro() {
	local dargs="$3"
	test -z "$3" && dargs="()"
	AS_ECHO_N(["static $1 psi_macro_$2$dargs {"])
	if test "$1" != "void"; then
		AS_ECHO_N(["return "])
	fi
	arg_names "$3"
	AS_ECHO_N(["$2`arg_names \"$3\"`;}"])
}
# add_macro(ret type, symbol, args)
add_macro() {
	PSI_MACROS="`gen_macro \"$1\" \"$2\" \"$3\"` $PSI_MACROS"
	add_redir "$2" "psi_macro_$2"
}

dnl PSI_MACRO(macro, decl args, action-if-true)
AC_DEFUN(PSI_MACRO, [
	AC_CHECK_DECL($1$2, $3, [], PSI_INCLUDES)
])

dnl PSI_FUNC(fn, action-if-yes, action-if-no)
AC_DEFUN(PSI_FUNC, [
	AC_REQUIRE([AC_PROG_NM])
	AC_REQUIRE([AC_PROG_AWK])
	psi_symbol=$1
	AC_CACHE_CHECK(for $1, psi_cv_fn_$1, [
		psi_symbol_redirect=
		AC_TRY_LINK(PSI_INCLUDES, [
			void (*fn)(void) = (void (*)(void)) $psi_symbol;
		], [
			psi_symbol_redirect=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/ U .*$1.*/ {print$[]3; exit}'`
		])
		psi_cv_fn_$1=$psi_symbol_redirect
	])
	case "$psi_cv_fn_$1" in
	"") $3 ;;
	"$psi_symbol"|"_$psi_symbol") $2 ;;
	*) add_redir "$psi_symbol"; $2 ;;
	esac
])

dnl PSI_EXTVAR(var, type)
AC_DEFUN(PSI_EXTVAR, [
	AC_CHECK_DECL($1, [
		add_macro "$2" "$1"
	], [], PSI_INCLUDES)
])


dnl PSI_DECL(ret type, func, args)
AC_DEFUN(PSI_DECL, [
	PSI_FUNC($2, [
		add_decl "$1" "$2" "$3"
	], [
		PSI_MACRO($2, $3, [
			add_macro "$1" "$2" "$3"
			add_decl "$1" "$2" "$3"
		])
	])
])

AC_DEFUN(PSI_STRUCT_MEMBER, [
	psi_member_name=
	psi_member_type=
	m4_map_args_w([$1], [
		psi_member_type="$psi_member_type $psi_member_name"
		psi_member_name=], [
	])
	AC_MSG_RESULT([member=$psi_member_name - $psi_member_type])
])

AC_DEFUN(PSI_STRUCT, [
	AC_CHECK_SIZEOF($1, [], PSI_INCLUDES)
	m4_map_args([PSI_STRUCT_MEMBER], $2)
	exit
])

AC_DEFUN(PSI_CHECK_STD_TYPES, [
	AC_CHECK_HEADERS(stdint.h)

	AC_TYPE_INT8_T
	AC_CHECK_SIZEOF(int8_t)
	AC_CHECK_ALIGNOF(int8_t)
	AC_TYPE_UINT8_T
	AC_CHECK_SIZEOF(uint8_t)
	AC_CHECK_ALIGNOF(uint8_t)
	AC_TYPE_INT16_T
	AC_CHECK_SIZEOF(int16_t)
	AC_CHECK_ALIGNOF(int16_t)
	AC_TYPE_UINT16_T
	AC_CHECK_SIZEOF(uint16_t)
	AC_CHECK_ALIGNOF(uint16_t)
	AC_TYPE_INT32_T
	AC_CHECK_SIZEOF(int32_t)
	AC_CHECK_ALIGNOF(int32_t)
	AC_TYPE_UINT32_T
	AC_CHECK_SIZEOF(uint32_t)
	AC_CHECK_ALIGNOF(uint32_t)
	AC_TYPE_INT64_T
	AC_CHECK_SIZEOF(int64_t)
	AC_CHECK_ALIGNOF(int64_t)
	AC_TYPE_UINT64_T
	AC_CHECK_SIZEOF(uint64_t)
	AC_CHECK_ALIGNOF(uint64_t)

	PSI_TYPE(float)
	AC_CHECK_ALIGNOF(float)
	PSI_TYPE(double)
	AC_CHECK_ALIGNOF(double)
	PSI_TYPE(void *)
	AC_CHECK_ALIGNOF(void *)

	PSI_TYPE(char, int)
	PSI_TYPE(short, int)
	PSI_TYPE(int, int)
	PSI_TYPE(long, int)
])
