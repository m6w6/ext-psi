# psi_add_type(type triplet)
# Add a pre-defined type to $PSI_TYPES.
psi_add_type() {
	cat >>$PSI_TYPES <<EOF
	$1,
EOF
}

psi_add_stdtype() {
	cat >>$PSI_STDTYPES <<EOF
	$1,
EOF
}

# psi_type_pair(type, size)
# Output a PSI_T_<TYPE>, \"<TYPENAME>\" tuple.
# Uses stdint types when possible.
psi_type_pair() {
	local psi_type_name=`printf "%s" "$1" | tr -cd A-Za-z0-9_`
	local psi_type_lower=`printf "%s" "$1" | tr A-Z a-z`
	while expr "$psi_type_lower" : const >/dev/null; do
		psi_type_lower=`printf "%s" "$psi_type_lower" | cut -d " " -f2-`
	done
	case $psi_type_lower in
	int*|uint*)
		local psi_type_upper=`printf "%s" "$psi_type_name" | tr a-z A-Z`
		local psi_type_bits=`expr $2 \* 8`
		echo "PSI_T_${psi_type_upper}${psi_type_bits}, \"${psi_type_lower}${psi_type_bits}_t\""
		;;
	struct*)
		echo "PSI_T_STRUCT, \"$2\""
		;;
	union*)
		echo "PSI_T_UNION, \"$2\""
		;;
	void)
		echo "PSI_T_VOID, \"void\""
		;;
	*)
		echo "PSI_T_NAME, \"$psi_type_name\""
		;;
	esac
}

dnl PSI_TYPE(type name, basic type)
dnl Check for a specific type, optionally referring to a basic type.
dnl Calls AC_TYPE_<TYPE> (if defined) and PSI_CHECK_SIZEOF.
dnl If the basic type is just specified as "int" (in contrast to "sint" or
dnl "uint"), AX_CHECK_SIGN is used to discover signedness of the type.
dnl Defines a pre-defined type in $PSI_TYPES.
AC_DEFUN(PSI_TYPE, [
	ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
	PSI_CHECK_SIZEOF($1)
	psi_basic_type=AS_TR_SH($2)
	case $psi_basic_type in
	int)
		AX_CHECK_SIGN($1, :, [psi_basic_type=uint], PSI_INCLUDES)
		;;
	sint)
		psi_basic_type=int
		;;
	esac
	if test "$2" && PSI_SH_TEST_SIZEOF($1); then
		AS_TR_SH(psi_basic_type_$1)=$psi_basic_type
		psi_add_type "{`psi_type_pair $psi_basic_type PSI_SH_SIZEOF($1)`, \"$1\"}"
	fi
])

AC_DEFUN(PSI_STDTYPE, [
	ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
	PSI_CHECK_SIZEOF($1)
	if PSI_SH_TEST_SIZEOF($1); then
		m4_case([$1],
		[bool],[psi_add_stdtype "{PSI_T_BOOL, \"bool\", NULL}"],
		[float],[psi_add_stdtype "{PSI_T_FLOAT, \"float\", NULL}"],
		[double],[psi_add_stdtype "{PSI_T_DOUBLE, \"double\", NULL}"],
		[long double],[psi_add_stdtype "{PSI_T_LONG_DOUBLE, \"long double\", NULL}"],
		[
			AX_CHECK_SIGN($1, psi_basic_type=int, psi_basic_type=uint, PSI_INCLUDES)
			AS_TR_SH(psi_basic_type_$1)=$psi_basic_type
			psi_add_stdtype "{`psi_type_pair $psi_basic_type PSI_SH_SIZEOF($1)`, \"$1\"}"
		])
	fi
])

dnl PSI_SH_BASIC_TYPE(type)
dnl Expand to the basic type (int/uint) of a distinct type
AC_DEFUN(PSI_SH_BASIC_TYPE, [$AS_TR_SH([psi_basic_type_]$1)])

dnl PSI_OPAQUE_TYPE(type name)
dnl Checks a type for being a scalar, a struct or a pointer type.
dnl Calls AC_TYPE_<TYPE> (if defined) and PSI_CHECK_SIZEOF.
dnl Defines a pre-defined type in $PSI_TYPES and a pre-defined struct in
dnl $PSI_STRUCTS if the type is a struct.
AC_DEFUN(PSI_OPAQUE_TYPE, [
	ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
	PSI_CHECK_SIZEOF($1)
	if PSI_SH_TEST_SIZEOF($1); then
		psi_type_class=
		AC_CACHE_CHECK(kind of $1, AS_TR_SH([psi_cv_type_class_]$1), [
			AC_TRY_COMPILE(PSI_INCLUDES, [char test@<:@($1)1@:>@;], [
				psi_type_class=scalar
			], [
				AC_TRY_COMPILE(PSI_INCLUDES, [$1 test = 0;], [
					AC_TRY_COMPILE(PSI_INCLUDES, [$1 test = (($1)0)+1;], [
						psi_type_class="pointer of known type"
					], [
						psi_type_class="pointer of opaque type"
					])
				], [
					psi_type_class=struct
				])
			])
			AS_TR_SH([psi_cv_type_class_]$1)="$psi_type_class"
		])
		case "$AS_TR_SH([psi_cv_type_class_]$1)" in
		scalar)
			AX_CHECK_SIGN($1, [psi_basic_type=int], [psi_basic_type=uint], PSI_INCLUDES)
			psi_add_type "{`psi_type_pair $psi_basic_type PSI_SH_SIZEOF($1)`, \"$1\"}"
			;;
		struct)
			PSI_STRUCT($1)
			;;
		pointer*)
			psi_add_type "{PSI_T_POINTER, \"void\", \"$1\"}"
			;;
		*)
			AC_MSG_WARN(could not detect kind of $1)
			;;
		esac
	fi
])

dnl PSI_FUNCTOR_TYPE(type functor_name, args)
dnl Forwards to PSI_DECL_TYPE.
AC_DEFUN(PSI_FUNCTOR_TYPE, [
	dnl psi_add_type "{PSI_T_POINTER, \"void\", \"PSI_VAR_NAME($1)\"}"
	AS_TR_SH([ac_cv_sizeof_]PSI_VAR_NAME($1))=PSI_SH_SIZEOF(void *)
	PSI_DECL_TYPE([$1], [$2])
	if test "$PHP_DEBUG" = "1"; then
		AC_CHECK_TYPE(PSI_VAR_NAME($1), [], [
			psi_add_macro ["#undef ]PSI_VAR_NAME($1)["]
			psi_add_macro ["typedef ]PSI_VAR_TYPE($1)[ (*]PSI_VAR_NAME($1)[)]$2;"
		])
	fi
])

dnl PSI_VAR_TYPE(decl arg)
dnl Extracts the type of a decl arg, e.g. dnl unsigned char* buf[16] -> unsigned char*.
AC_DEFUN(PSI_VAR_TYPE, [m4_bregexp([$1], [^\(const \)?\(.*\) \([*]*\)[^ ]+$], [\2\3])])

dnl PSI_VAR_NAME(decl arg)
dnl Extracts the var name of a decl arg, e.g. unsigned char* buf[16] -> buf.
AC_DEFUN(PSI_VAR_NAME, [m4_bregexp(m4_bregexp([$1], [\([^ ]+\)$], [\1]), [\w+], [\&])])

dnl PSI_TYPE_INDIRECTION(decl arg, size, pointer_level_var, array_size_var)
dnl Calculates and assigns pointer_level and array_size of a decl arg to sh vars.
AC_DEFUN(PSI_TYPE_INDIRECTION, [
	m4_define([psi_pointer_level], m4_len(m4_bpatsubst([PSI_VAR_TYPE($1)], [[^*]])))
	m4_define([psi_array_size], [m4_bregexp([PSI_VAR_TYPE($1)], [@<:@\([0-9]+\)@:>@], [\1])])

	ifelse(psi_array_size.$2,0., [
		AC_MSG_ERROR([cannot compute dynamic array size of a non-struct member])
	], [
		ifelse(psi_pointer_level,0,[
			m4_define([psi_type_size],[$]AS_TR_SH([ac_cv_sizeof_]m4_bregexp(PSI_VAR_TYPE([$1]), [^\( \|\w\)+], [\&])))
		],[
			m4_define([psi_type_size],$ac_cv_sizeof_void_p)
		])
	])

	m4_case(psi_array_size,,[
		$3=psi_pointer_level
		$4=0]
	,0,[
		$3=m4_incr(psi_pointer_level)
		$4="`expr $2 / psi_type_size`"
	], [
		$3=m4_incr(psi_pointer_level)
		$4=psi_array_size
	])
])

dnl PSI_TYPE_PAIR(type)
dnl Expand to a PSI_T_<TYPE>, \\"<TYPENAME>\\" tuple.
dnl FIXME: There is also psi_type_pair()?
AC_DEFUN(PSI_TYPE_PAIR, [m4_case(m4_bregexp([$1], [^\w+], [\&]),
	[void], [PSI_T_VOID, \"void\"],
	[struct], [PSI_T_STRUCT, \"m4_bregexp([$1], [^struct \(\w+\)], [\1])\"],
	[union], [PSI_T_UNION, \"m4_bregexp([$1], [^union \(\w+\)], [\1])\"],
	[PSI_T_NAME, \"m4_bregexp([$1], [^\(\w+ \)*\w+], [\&])\"])])

dnl PSI_CHECK_STD_TYPES()
dnl Checks for standard ANSI-C, stdint and stdbool types.
AC_DEFUN(PSI_CHECK_STD_TYPES, [
	AC_CHECK_HEADERS(stdint.h)
	AC_HEADER_STDBOOL

	AC_TYPE_INT8_T
	PSI_CHECK_SIZEOF(int8_t)
	AC_CHECK_ALIGNOF(int8_t)
	AC_TYPE_UINT8_T
	PSI_CHECK_SIZEOF(uint8_t)
	AC_CHECK_ALIGNOF(uint8_t)
	AC_TYPE_INT16_T
	PSI_CHECK_SIZEOF(int16_t)
	AC_CHECK_ALIGNOF(int16_t)
	AC_TYPE_UINT16_T
	PSI_CHECK_SIZEOF(uint16_t)
	AC_CHECK_ALIGNOF(uint16_t)
	AC_TYPE_INT32_T
	PSI_CHECK_SIZEOF(int32_t)
	AC_CHECK_ALIGNOF(int32_t)
	AC_TYPE_UINT32_T
	PSI_CHECK_SIZEOF(uint32_t)
	AC_CHECK_ALIGNOF(uint32_t)
	AC_TYPE_INT64_T
	PSI_CHECK_SIZEOF(int64_t)
	AC_CHECK_ALIGNOF(int64_t)
	AC_TYPE_UINT64_T
	PSI_CHECK_SIZEOF(uint64_t)
	AC_CHECK_ALIGNOF(uint64_t)

	PSI_CHECK_SIZEOF(void *)
	AC_CHECK_ALIGNOF(void *)

	PSI_STDTYPE(float)
	AC_CHECK_ALIGNOF(float)
	PSI_STDTYPE(double)
	AC_CHECK_ALIGNOF(double)
	PSI_STDTYPE(long double)
	AC_CHECK_ALIGNOF(long double)

	PSI_STDTYPE(bool)
	AC_CHECK_ALIGNOF(bool, PSI_INCLUDES)

	PSI_STDTYPE(char, int)
	AC_CHECK_ALIGNOF(char)
	PSI_STDTYPE(signed char, int)
	PSI_STDTYPE(unsigned char, uint)
	PSI_STDTYPE(short, int)
	AC_CHECK_ALIGNOF(short)
	PSI_STDTYPE(short int, int)
	PSI_STDTYPE(signed short, int)
	PSI_STDTYPE(signed short int, int)
	PSI_STDTYPE(unsigned short, uint)
	PSI_STDTYPE(unsigned short int, uint)
	PSI_STDTYPE(int, int)
	AC_CHECK_ALIGNOF(int)
	PSI_STDTYPE(signed int, int)
	PSI_STDTYPE(signed, int)
	PSI_STDTYPE(unsigned int, uint)
	PSI_STDTYPE(unsigned, uint)
	PSI_STDTYPE(long, int)
	AC_CHECK_ALIGNOF(long)
	PSI_STDTYPE(long int, int)
	PSI_STDTYPE(signed long int, int)
	PSI_STDTYPE(unsigned long, uint)
	PSI_STDTYPE(unsigned long int, uint)
	PSI_STDTYPE(long long, int)
	AC_CHECK_ALIGNOF(long long)
	PSI_STDTYPE(signed long long, int)
	PSI_STDTYPE(signed long long int, int)
	PSI_STDTYPE(unsigned long long, uint)
	PSI_STDTYPE(unsigned long long int, uint)
	dnl this must come after the check for "unsigned long long int"; autoconf, wth?
	PSI_STDTYPE(long long int, int)
])
