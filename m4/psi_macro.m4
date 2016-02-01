# psi_add_macro(macro)
# Add a pre-defined macro function to $PSI_MACROS.
psi_add_macro() {
	cat >>$PSI_MACROS <<<"$1"
}

dnl PSI_MACRO(macro, decl args, action-if-true)
AC_DEFUN(PSI_MACRO, [
	AC_CHECK_DECL(PSI_VAR_NAME($1)$2, [
		$3
		macro_type="PSI_VAR_TYPE($1)"
		macro_name="PSI_VAR_NAME($1)"
		m4_case([$2],
			[(void)], [
				macro_decl="(void)"
				macro_call="()"
			],
			[()], [
				macro_decl="()"
				macro_call="()"
			],
			[], [
				macro_decl="()"
				macro_call=""
			],
			[
				macro_decl="$2"
				macro_call="(m4_map_args_sep([PSI_VAR_NAME(], [)], [, ], m4_bregexp($2, [(\(.*\))], [\1])))"
			]
		)
		ifelse(PSI_VAR_TYPE($1), [void], [
			macro_body="$macro_name$macro_call;"
		], [
			macro_body="return $macro_name$macro_call;"
		])
		psi_add_macro "$macro_type _psi_redir_$macro_name$macro_decl { $macro_body }"
		PSI_REDIR($macro_name, _psi_redir_$macro_name)
	], [], PSI_INCLUDES)
])

dnl PSI_EXTVAR(type var)
AC_DEFUN(PSI_EXTVAR, [PSI_MACRO($1)])
