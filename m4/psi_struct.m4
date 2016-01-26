# psi_add_struct(struct members)
# Add a pre-defined struct to $PSI_STRUCTS.
psi_add_struct() {
	cat >>$PSI_STRUCTS <<<"	$1, {0}, "
}

dnl PSI_STRUCT_MEMBER(struct name, decl member)
dnl INTERNAL: build $psi_struct_members
AC_DEFUN(PSI_STRUCT_MEMBER, [
	m4_define([member_name], PSI_VAR_NAME($2))
	m4_define([member_type], PSI_VAR_TYPE($2))
	PSI_CHECK_SIZEOF(AS_TR_SH($1)[_]member_name,
		[#define ]AS_TR_SH($1)[_]member_name (($1 *)0)->member_name
	)
	if PSI_SH_TEST_SIZEOF($1 member_name); then
		PSI_CHECK_OFFSETOF($1, member_name)
		PSI_TYPE_INDIRECTION($2, [PSI_SH_SIZEOF([$1 member_name])], pl, as)
		
		psi_member_sizeof=PSI_SH_SIZEOF($1 member_name)
		psi_member_offsetof=PSI_SH_OFFSETOF($1 member_name)
		
		if test $pl -gt 0 && test $as -eq 0; then
			check_size=PSI_SH_SIZEOF(void *)
		elif test $pl -eq 1 && test $as -gt 0; then
			check_size=`expr PSI_SH_SIZEOF(member_type) \* $as`
		else
			check_size=PSI_SH_SIZEOF(member_type)
		fi
		if test $psi_member_sizeof != "$check_size"; then
			psi_member_basic_type=PSI_SH_BASIC_TYPE(member_type)
			psi_member_type_pair="`psi_type_pair $psi_member_basic_type $psi_member_sizeof`"
			psi_struct_members="$psi_struct_members, {$psi_member_type_pair, \"[]member_name[]\", $psi_member_offsetof, $psi_member_sizeof, $pl, $as}"
			AC_MSG_WARN(pre-defined size $check_size of $2 in $1 does not match computed size $psi_member_sizeof; adjusting to $psi_member_type_pair)
		else
			psi_struct_members="[$psi_struct_members, {]PSI_TYPE_PAIR(member_type)[, \"]member_name[\", $psi_member_offsetof, $psi_member_sizeof, $pl, $as}]"
		fi
	fi
])

dnl PSI_STRUCT(struct name, struct members)
dnl Check a struct and its members and add a pre-defined struct and possibly a
dnl pre-defined type for this struct.
dnl Calls PSI_CHECK_SIZEOF for the struct and each member.
dnl Calls PSI_CHECK_OFFSETOF and PSI_TYPE_INDIRECTON for each member.
AC_DEFUN(PSI_STRUCT, [
	PSI_CHECK_SIZEOF($1)
	psi_struct_name=m4_bregexp([$1], [^\(struct \)?\(\w+\)], [\2])
	psi_struct_members="{PSI_T_STRUCT, \"struct\", \"$psi_struct_name\", 0, $AS_TR_SH([ac_cv_sizeof_]$1), 0, 0}"
	ifelse([$2],,,[m4_map_args_sep([PSI_STRUCT_MEMBER($1, m4_normalize(], [))], [], $2)])
	psi_add_struct "$psi_struct_members"
	if test "$1" = "$psi_struct_name"; then
		psi_add_type "{PSI_T_STRUCT, \"$1\", \"$1\"}"
	fi
])
