PSI_STRUCTS=
# add_struct(name, size, members)
add_struct() {
    local members="$3"
    if test -z "$members"; then
        members="{0}"
    else
        members="$members, {0}"
    fi
    PSI_STRUCTS="{\"$1\", $2, {$members}}, $PSI_STRUCTS"
}

AC_DEFUN(PSI_STRUCT_MEMBER, [
	m4_define([member_name], PSI_VAR_NAME($2))
	m4_define([member_type], PSI_TYPE_NAME($2))
	AC_CHECK_SIZEOF(AS_TR_SH($1)[_]member_name, [], PSI_INCLUDES
		[#define ]AS_TR_SH($1)[_]member_name (($1 *)0)->member_name
	)
	PSI_CHECK_OFFSETOF($1, member_name)
	m4_define([pointer_level], m4_len(m4_bpatsubst($2, [[^*]])))
	m4_define([array_size], m4_bregexp($2, [\[\([0-9]+\)\]], [\1]))
	ifelse(array_size, [],
		[m4_define([array_size], 0)],
		[m4_define([pointer_level], m4_incr(pointer_level))]
	)
	m4_define([member_size], PSI_TYPE_SIZE(member_type, pointer_level, array_size))
	if test -n "$psi_struct_members"; then
		psi_struct_members="$psi_struct_members, "
	fi
	psi_struct_members="[$psi_struct_members{]PSI_TYPE_PAIR(member_type)[, \"]member_name[\", $]AS_TR_SH([ac_cv_offsetof_]$1[_]member_name)[, ]member_size, pointer_level, array_size[}]"
])

AC_DEFUN(PSI_STRUCT, [
	AC_CHECK_SIZEOF($1, [], PSI_INCLUDES)
	psi_struct_members=
	ifelse([$2],[],[],[m4_map_args_sep([PSI_STRUCT_MEMBER($1,], [)], [], $2)])
	add_struct "$1" $AS_TR_SH([ac_cv_sizeof_]$1) "$psi_struct_members"
])
