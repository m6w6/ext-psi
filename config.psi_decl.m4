PSI_REDIRS=
AC_DEFUN(PSI_REDIR, [psi_symbol=ifelse([$2],[],[$1],[$2])
	PSI_REDIRS="{\"$1\", (void(*)(void))$psi_symbol}, $PSI_REDIRS"])

dnl PSI_FUNC(fn, action-if-yes, action-if-no)
AC_DEFUN(PSI_FUNC, [
	AC_REQUIRE([AC_PROG_NM])
	AC_REQUIRE([AC_PROG_AWK])
	psi_symbol=$1
	AC_CACHE_CHECK(for $1, psi_cv_fn_$1, [
		psi_symbol_redirect=
		AC_TRY_LINK(PSI_INCLUDES, [
			void (*fn)(void) = (void (*)(void)) $psi_symbol;
		], [
			psi_symbol_redirect=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/ U .*$1.*/ {print$[]3; exit}'`
		])
		psi_cv_fn_$1=$psi_symbol_redirect
	])
	case "$psi_cv_fn_$1" in
	"")
		$3
		;;
	"$psi_symbol"|"_$psi_symbol")
		$2
		;;
	*)
		$2
		PSI_REDIR($1)
		;;
	esac
])

AC_DEFUN(PSI_DECL_ARG, [
    m4_define([member_name], PSI_VAR_NAME($1))
    m4_define([member_type], PSI_TYPE_NAME($1))
    m4_define([pointer_level], m4_len(m4_bpatsubst($1, [[^*]])))
	m4_define([array_size], m4_bregexp($1, [\[\([0-9]+\)\]], [\1]))
	ifelse(array_size, [],
		[m4_define([array_size], 0)],
		[m4_define([pointer_level], m4_incr(pointer_level))]
	)
    if test -n "$psi_decl_args"; then
        psi_decl_args="$psi_decl_args, "
    fi
    psi_decl_args="[$psi_decl_args{]PSI_TYPE_PAIR(member_type)[, \"]member_name[\",] pointer_level, array_size[}]"
])

dnl PSI_DECL(type func, args)
AC_DEFUN(PSI_DECL, [
	psi_decl_args=
	PSI_DECL_ARG($1)
	m4_case([$2],
		[(void)], [],
		[()], [],
		[m4_map_args_sep([PSI_DECL_ARG(], [)], [], m4_bregexp($2, [(\(.*\))], [\1]))])
	PSI_FUNC(PSI_VAR_NAME($1), [
		PSI_DECLS="{$psi_decl_args}, $PSI_DECLS"
	], [
		PSI_MACRO(PSI_VAR_NAME($1), $3, [
			add_macro "PSI_TYPE_NAME($1)" "PSI_VAR_NAME($1)" "$3"
			PSI_DECLS="{$psi_decl_args}, $PSI_DECLS"
		])
	])
])
