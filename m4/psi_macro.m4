dnl PSI_MACRO(macro, decl args, action-if-true)
AC_DEFUN(PSI_MACRO, [
	AC_CHECK_DECL(PSI_VAR_NAME($1)$2, [
		$3
		macro_type="PSI_VAR_TYPE($1)"
		macro_name="PSI_VAR_NAME($1)"
		ifelse([$2], [], [
			macro_decl="()"
			macro_call=""
		], [
			macro_decl="$2"
			macro_call="(m4_map_args_sep([PSI_VAR_NAME(], [)], [, ], m4_bregexp($2, [(\(.*\))], [\1])))"
		])
		ifelse(PSI_VAR_TYPE($1), [void], [
			macro_body="$macro_name$macro_call;"
		], [
			macro_body="return $macro_name$macro_call;"
		])
		psi_macro="$macro_type psi_macro_$macro_name$macro_decl { $macro_body }"
		PSI_MACROS="$PSI_MACROS $psi_macro"
		PSI_REDIR($macro_name, psi_macro_$macro_name)
	], [], PSI_INCLUDES)
])

dnl PSI_EXTVAR(type var)
AC_DEFUN(PSI_EXTVAR, [PSI_MACRO($1)])
