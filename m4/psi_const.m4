# psi_add_str_const(name, value)
# Add a pre-defined string constant to $PSI_CONSTS
psi_add_str_const() {
	grep -q "\"psi\\\\\\\\$1\"" $PSI_CONSTS \
		|| cat >>$PSI_CONSTS <<EOF
	{PSI_T_STRING, "string", "psi\\$1", $2, PSI_T_QUOTED_STRING},
EOF 
}

# psi_add_int_const(name, value)
# Add a pre-defined int constant to $PSI_CONSTS
psi_add_int_const() {
	grep -q "\"psi\\\\\\\\$1\"" $PSI_CONSTS \
		|| cat >>$PSI_CONSTS <<EOF
	{PSI_T_INT, "int", "psi\\$1", "$2", PSI_T_NUMBER}, 
EOF
}

dnl PSI_CONST(const name, type)
dnl Check the value of a str/int constant and add it to the list of pre-defined
dnl constants.
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
			psi_add_str_const "$1" "$psi_cv_const_$1"
			;;
		int)
			psi_add_int_const "$1" "$psi_cv_const_$1"
			;;
		esac
	fi
])
