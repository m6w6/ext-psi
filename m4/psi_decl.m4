AC_DEFUN(PSI_REDIR, [psi_symbol=ifelse([$2],[],[$1],[$2])
	PSI_REDIRS="{\"$1\", (void(*)(void))$psi_symbol}, $PSI_REDIRS"])

AC_DEFUN(PSI_FUNC_LIBC_MAIN, [
	AC_REQUIRE([AC_PROG_NM])
	AC_REQUIRE([AC_PROG_AWK])
	AC_CACHE_CHECK(for libc start main symbol, psi_cv_libc_main, [
		psi_libc_main=
		AC_TRY_LINK(PSI_INCLUDES, [(void)0;], [
			psi_libc_main=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/^\s+U / {print$[]3; exit}'`
		])
		psi_cv_libc_main=$psi_libc_main
	])
])

dnl PSI_FUNC(fn, action-if-yes, action-if-no)
AC_DEFUN(PSI_FUNC, [
	AC_REQUIRE([PSI_FUNC_LIBC_MAIN])
	psi_symbol=$1
	AC_CACHE_CHECK(for $1, psi_cv_fn_$1, [
		psi_symbol_redirect=
		AC_TRY_LINK(PSI_INCLUDES, [
			void (*fn)(void) = (void (*)(void)) $psi_symbol;
		], [
			psi_symbol_redirect=`$NM -g conftest$ac_exeext | $AWK -F" *|@" '/^\s+U '$psi_cv_libc_main'/ {next} /^\s+U / {print$[]3; exit}'`
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
    m4_define([member_type], PSI_VAR_TYPE($1))

	PSI_TYPE_INDIRECTION([$1],, pl, as)
    if test -n "$psi_decl_args"; then
        psi_decl_args="$psi_decl_args, "
    fi
    psi_decl_args="[$psi_decl_args{]PSI_TYPE_PAIR(member_type)[, \"]member_name[\",] $pl, $as[}]"
])

dnl PSI_DECL(type func, args)
AC_DEFUN(PSI_DECL, [
	psi_decl_args=
	PSI_DECL_ARG($1)
	m4_case([$2],
		[(void)], [],
		[()], [],
		[m4_map_args_sep([PSI_DECL_ARG(m4_normalize(], [))], [], m4_bregexp([$2], [(\(.*\))], [\1]))])
	PSI_FUNC(PSI_VAR_NAME($1), [
		PSI_DECLS="$psi_decl_args, {0}, $PSI_DECLS"
	], [
		PSI_MACRO($1, $2, [
			PSI_DECLS="$psi_decl_args, {0}, $PSI_DECLS"
		])
	])
])
