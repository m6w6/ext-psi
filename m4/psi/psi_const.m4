# psi_add_str_const(name, value)
# Add a pre-defined string constant to $PSI_CONSTS_H
psi_add_str_const() {
	PSI_CONSTS="$PSI_CONSTS
	{PSI_T_STRING, \"string\", \"psi\\\\$1\", {.ptr = $1}},"
}

# psi_add_int_const(name, value)
# Add a pre-defined int constant to $PSI_CONSTS_H
psi_add_int_const() {
	PSI_CONSTS="$PSI_CONSTS
	{PSI_T_INT, \"int\", \"psi\\\\$1\", {.zend.lval = (zend_long) $1}},"
}

dnl PSI_CONST(const name, type)
dnl Check the value of a str/int constant and add it to the list of pre-defined
dnl constants.
AC_DEFUN(PSI_CONST, [
	AC_CHECK_DECL($1, [
		case $2 in
		str*)
			psi_add_str_const "$1"
			;;
		int)
			psi_add_int_const "$1"
			;;
		esac
	],, [PSI_INCLUDES])
])
