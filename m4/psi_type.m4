# psi_type_pair(type, size)
psi_type_pair() {
	local psi_type_name=`tr -cd A-Za-z0-9_ <<<$1`
	local psi_type_lower=`tr A-Z a-z <<<$psi_type_name`
	case $psi_type_lower in
	int*|uint*)
		local psi_type_upper=`tr a-z A-Z <<<$psi_type_name`
		local psi_type_bits=`expr $2 \* 8`
		echo "PSI_T_${psi_type_upper}${psi_type_bits}, \"${psi_type_lower}${psi_type_bits}_t\""
		#eval AS_TR_SH([psi_standard_type_]$1)="${psi_type_lower}${psi_type_bits}_t"
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

dnl PSI_TYPE(type name, basic type, includes)
AC_DEFUN(PSI_TYPE, [
	ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
	PSI_CHECK_SIZEOF($1, PSI_INCLUDES)
	psi_basic_type=$2
	case $psi_basic_type in
	int)
		AX_CHECK_SIGN($1, :, [
			psi_basic_type=uint
		], PSI_INCLUDES)
		;;
	sint)
		psi_basic_type=int
		;;
	esac
	if test "$2" && test "$AS_TR_SH([ac_cv_sizeof_]$1)" -gt 0; then
		AS_TR_SH(psi_basic_type_$1)=$psi_basic_type
		cat >>$PSI_TYPES <<<"	{`psi_type_pair $psi_basic_type $AS_TR_SH([ac_cv_sizeof_]$1)`, \"$1\"}, "
	fi
])

dnl unsigned char* buf[16] -> unsigned char*
dnl AC_DEFUN(PSI_VAR_TYPE, [m4_bregexp([$1], [\(\(struct \)?[^ ]+\)[ *]+[^ ]+$], [\1])])
AC_DEFUN(PSI_VAR_TYPE, [m4_bregexp([$1], [^\(const \)?\(.*\) \([*]*\)[^ ]+$], [\2\3])])
dnl unsigned char* buf[16] -> buf
AC_DEFUN(PSI_VAR_NAME, [m4_bregexp(m4_bregexp([$1], [\([^ ]+\)$], [\1]), [\w+], [\&])])
dnl PSI_TYPE_SIZE(type, pointer level, array size)
AC_DEFUN(PSI_TYPE_SIZE, [ifelse(
	[$3], 0,
		[ifelse([$2], 0, $AS_TR_SH([ac_cv_sizeof_]$1), $ac_cv_sizeof_void_p)],
		[ifelse([$2], 1, [`expr $3 \* $AS_TR_SH([ac_cv_sizeof_]$1)`], $ac_cv_sizeof_void_p)]
)])
dnl PSI_TYPE_BITS(type)
AC_DEFUN(PSI_TYPE_BITS, [`expr 8 \* $AS_TR_SH([ac_cv_sizeof_]$1)`])

dnl PSI_TYPE_INDIRECTION(type, size, pointer_level_var, array_size_var)
AC_DEFUN(PSI_TYPE_INDIRECTION, [
	dnl AC_MSG_CHECKING(indirection of $1)
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

	dnl AC_MSG_RESULT([[$]$3, [$]$4])
])

AC_DEFUN(PSI_TYPE_PAIR, [m4_case(m4_bregexp([$1], [^\w+], [\&]),
	[void], [PSI_T_VOID, \"void\"],
	[struct], [PSI_T_STRUCT, \"m4_bregexp([$1], [^struct \(\w+\)], [\1])\"],
	[PSI_T_NAME, \"m4_bregexp([$1], [^\(\w+ \)*\w+], [\&])\"])])

AC_DEFUN(PSI_CHECK_STD_TYPES, [
	AC_CHECK_HEADERS(stdint.h)

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

	PSI_TYPE(float)
	AC_CHECK_ALIGNOF(float)
	PSI_TYPE(double)
	AC_CHECK_ALIGNOF(double)
	PSI_TYPE(void *)
	AC_CHECK_ALIGNOF(void *)

	PSI_TYPE(char, int)
	PSI_TYPE(unsigned char, uint)
	PSI_TYPE(short, int)
	PSI_TYPE(unsigned short, uint)
	PSI_TYPE(int, int)
	PSI_TYPE(unsigned int, uint)
	PSI_TYPE(unsigned, uint)
	PSI_TYPE(long, int)
	PSI_TYPE(unsigned long, uint)
])
