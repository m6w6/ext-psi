# psi_add_macro(macro)
# Add a pre-defined macro function to $PSI_MACROS.
psi_add_macro() {
	cat >>$PSI_MACROS <<EOF
$1
EOF
}

dnl PSI_MACRO(macro, decl args, action-if-true)
AC_DEFUN(PSI_MACRO, [
	AC_CHECK_DECL(PSI_VAR_NAME($1)$2, [
		macro_type="PSI_VAR_TYPE($1)"
		macro_name="PSI_VAR_NAME($1)"
		m4_case([$2],
			[(void)], [
				macro_decl="(void)"
				macro_call="()"
				macro_action=call
			],
			[()], [
				macro_decl="()"
				macro_call="()"
				macro_action=call
			],
			[], [
				macro_decl="()"
				macro_call=""
				macro_action=get
			],
			[
				macro_decl="$2"
				macro_call="(m4_map_args_sep([PSI_VAR_NAME(], [)], [, ], m4_bregexp($2, [(\(.*\))], [\1])))"
				macro_action=call
			]
		)
		ifelse(PSI_VAR_TYPE($1), [void], [
			macro_body="$macro_name$macro_call;"
		], [
			macro_body="return $macro_name$macro_call;"
		])
		$3
		psi_add_macro "$macro_type _psi_${macro_action}_$macro_name$macro_decl { $macro_body }"
		PSI_REDIR($macro_name, _psi_${macro_action}_$macro_name)
	], [], PSI_INCLUDES)
])

dnl PSI_EXTVAR(type var)
AC_DEFUN(PSI_EXTVAR, [
	dnl just a getter
	PSI_MACRO($1, [], [
		PSI_DECL_ARGS($1)
		psi_add_decl "$psi_decl_args"
		dnl explicit getter & setter
		PSI_REDIR([${macro_name}_get], [_psi_get_$macro_name])
		PSI_DECL_ARGS($1_get)
		psi_add_decl "$psi_decl_args"
		psi_add_macro "void _psi_set_${macro_name}($macro_type value) { memcpy(&$macro_name, &value, sizeof(value)); }"
		PSI_REDIR([${macro_name}_set], [_psi_set_${macro_name}])
		PSI_DECL_ARGS([void PSI_VAR_NAME($1)_set], [(PSI_VAR_TYPE($1) _v)])
		psi_add_decl "$psi_decl_args"
	])
])
