AC_DEFUN(PSI_STRUCT_MEMBER, [
	m4_define([member_name], PSI_VAR_NAME($2))
	m4_define([member_type], PSI_VAR_TYPE($2))
	AC_CHECK_SIZEOF(AS_TR_SH($1)[_]member_name, [], PSI_INCLUDES
		[#define ]AS_TR_SH($1)[_]member_name (($1 *)0)->member_name
	)
	if test -n "$AS_TR_SH([ac_cv_sizeof_$1][_]member_name)" \
	&& test "$AS_TR_SH([ac_cv_sizeof_$1][_]member_name)" -gt 0; then
		PSI_CHECK_OFFSETOF($1, member_name)
		PSI_TYPE_INDIRECTION($2, [$AS_TR_SH([ac_cv_sizeof_]$1[_]member_name)], pl, as)
		psi_struct_members="[$psi_struct_members, {]PSI_TYPE_PAIR(member_type)[, \"]member_name[\", $]AS_TR_SH([ac_cv_offsetof_]$1[_]member_name)[, $]AS_TR_SH([ac_cv_sizeof_]$1[_]member_name), $pl, $as[}]"
	fi
])

AC_DEFUN(PSI_STRUCT, [
	AC_CHECK_SIZEOF($1, [], PSI_INCLUDES)
	psi_struct_name=m4_bregexp([$1], [^\(struct \)?\(\w+\)], [\2])
	psi_struct_members="{PSI_T_STRUCT, \"struct\", \"$psi_struct_name\", 0, $AS_TR_SH([ac_cv_sizeof_]$1), 0, 0}"
	ifelse([$2],,,[m4_map_args_sep([PSI_STRUCT_MEMBER($1, m4_normalize(], [))], [], $2)])
	PSI_STRUCTS="$psi_struct_members, {0}, $PSI_STRUCTS"
	if test "$1" = "$psi_struct_name"; then
		PSI_TYPES="{PSI_T_STRUCT, \"$1\", \"$1\"}, $PSI_TYPES"
	fi
])
