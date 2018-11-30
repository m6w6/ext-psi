psi_add_stdtype() {
	PSI_STDTYPES="$PSI_STDTYPES
	$1,"
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

AC_DEFUN(PSI_STDTYPE, [
	ifdef(AS_TR_CPP(AC_TYPE_$1), AS_TR_CPP(AC_TYPE_$1))
	PSI_CHECK_SIZEOF($1)
	if PSI_SH_TEST_SIZEOF($1); then
		m4_case(ifelse(,[$2],[$1],[$2]),
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

dnl PSI_CHECK_STD_TYPES()
dnl Checks for standard ANSI-C, stdint and stdbool types.
AC_DEFUN(PSI_CHECK_STD_TYPES, [

	AC_HEADER_STDBOOL

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
	PSI_STDTYPE(short signed, int)
	PSI_STDTYPE(short signed int, int)
	PSI_STDTYPE(unsigned short, uint)
	PSI_STDTYPE(unsigned short int, uint)
	PSI_STDTYPE(short unsigned, uint)
	PSI_STDTYPE(short unsigned int, uint)
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
	PSI_STDTYPE(long signed int, int)
	PSI_STDTYPE(unsigned long, uint)
	PSI_STDTYPE(unsigned long int, uint)
	PSI_STDTYPE(long unsigned, uint)
	PSI_STDTYPE(long unsigned int, uint)
	PSI_STDTYPE(long long, int)
	AC_CHECK_ALIGNOF(long long)
	PSI_STDTYPE(signed long long, int)
	PSI_STDTYPE(signed long long int, int)
	PSI_STDTYPE(long signed long, int)
	PSI_STDTYPE(long signed long int, int)
	PSI_STDTYPE(long long signed, int)
	PSI_STDTYPE(long long signed int, int)
	PSI_STDTYPE(unsigned long long, uint)
	PSI_STDTYPE(unsigned long long int, uint)
	PSI_STDTYPE(long unsigned long, uint)
	PSI_STDTYPE(long unsigned long int, uint)
	PSI_STDTYPE(long long unsigned, uint)
	PSI_STDTYPE(long long unsigned int, uint)
	dnl this must come after the check for "unsigned long long int"; autoconf, wth?
	PSI_STDTYPE(long long int, int)

	AC_CHECK_TYPE(__int128, [
		AC_DEFINE([HAVE_INT128], [1], [ ])
		AC_CHECK_ALIGNOF(__int128)
		PSI_STDTYPE(__int128, int)
		PSI_STDTYPE(signed __int128, int)
		PSI_STDTYPE(unsigned __int128, uint)
	])

	PSI_STDTYPE(_Float32)
	PSI_STDTYPE(_Float32x)
	PSI_STDTYPE(_Float64)
	PSI_STDTYPE(_Float64x)
	PSI_STDTYPE(_Float128)
])
