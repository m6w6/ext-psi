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
	local psi_macro
	psi_macro=`gen_macro "$1" "$2" "$3"`
	PSI_MACROS="$psi_macro $PSI_MACROS"
	PSI_REDIR([$2], [psi_macro_$2])
}

dnl PSI_MACRO(macro, decl args, action-if-true)
AC_DEFUN(PSI_MACRO, [
	AC_CHECK_DECL($1$2, $3, [], PSI_INCLUDES)
])

dnl PSI_EXTVAR(var, type)
AC_DEFUN(PSI_EXTVAR, [
	AC_CHECK_DECL($1, [
		add_macro "$2" "$1"
	], [], PSI_INCLUDES)
])
