# psi_add_redir(name, symbol)
# Add a function redirection to $PSI_REDIRS.
psi_add_redir() {
	cat >>$PSI_REDIRS <<EOF
	{"$1", (psi_func_ptr) $2},
EOF
}

# psi_add_decl(decl, options)
# Add a pre-defined decl to $PSI_VA_DECLS/$PSI_DECLS.
psi_add_decl() {
	case "$2" in
 *functor*)
		cat >>$PSI_FN_DECLS <<EOF
	$1, {0},
EOF
		;;
	*vararg*)
		cat >>$PSI_VA_DECLS <<EOF
	$1, {0},
EOF
		;;
	*)
		cat >>$PSI_DECLS <<EOF
	$1, {0},
EOF
		;;
	esac
}

dnl PSI_DECL_TYPE(type functor_name, args)
dnl Adds a pre-defined functor decl to $PSI_FN_DECLS.
AC_DEFUN(PSI_DECL_TYPE, [
	PSI_DECL_ARGS($1, $2)
	psi_add_decl "$psi_decl_args" functor
])
dnl PSI_REDIR(name, custom symbol)
dnl Create a function redirection to an optional custom symbol.
AC_DEFUN(PSI_REDIR, [
	psi_add_redir $1 ifelse([$2],[],[$1],[$2])
])

dnl PSI_FUNC_LIBC_MAIN()
dnl Check for the platforms default stub in executables.
AC_DEFUN(PSI_FUNC_LIBC_MAIN, [
	AC_REQUIRE([AC_PROG_AWK])
	AC_CACHE_CHECK(for libc start main symbol, psi_cv_libc_main, [
		psi_libc_main=
		AC_TRY_LINK(PSI_INCLUDES, [(void)0;], [
			psi_libc_main=`nm -g conftest$ac_exeext | $AWK -F ' *|@' '/^@<:@@<:@:space:@:>@@:>@+U / {print$[]3; exit}'`
		])
		psi_cv_libc_main=$psi_libc_main
	])
])

dnl PSI_DECL_ARGS(decl args)
dnl INTERNAL: build psi_decl_args
AC_DEFUN(PSI_DECL_ARGS, [
	psi_decl_args=
	PSI_DECL_ARG($1)
	m4_case([$2],
		[(void)], [],
		[()], [],
		[m4_map_args_sep([PSI_DECL_ARG(m4_normalize(], [))], [], m4_bregexp([$2], [(\(.*\))], [\1]))])
])

dnl PSI_DECL_ARG(decl arg)
dnl INTERNAL: build psi_decl_args
AC_DEFUN(PSI_DECL_ARG, [
    m4_define([member_name], PSI_VAR_NAME($1))
    m4_define([member_type], PSI_VAR_TYPE($1))

	PSI_TYPE_INDIRECTION([$1],, pl, as)
    if test -n "$psi_decl_args"; then
        psi_decl_args="$psi_decl_args, "
    fi
    psi_decl_args="[$psi_decl_args{]PSI_TYPE_PAIR(member_type)[, \"]member_name[\",] $pl, $as[}]"
])

dnl PSI_DECL(type func, args, flags)
dnl Check for a function or macro declaration and a possible asm redirection.
dnl Adds a pre-defined (vararg) decl to $PSI_VA_DECLS/$PSI_DECLS.
dnl Calls PSI_MACRO if PSI_FUNC fails.
AC_DEFUN(PSI_DECL, [
	AC_REQUIRE([PSI_FUNC_LIBC_MAIN])
	PSI_DECL_ARGS($1, $2)

	psi_symbol="PSI_VAR_NAME($1)"
	AC_CACHE_CHECK(for PSI_VAR_NAME($1), [psi_cv_fn_]PSI_VAR_NAME($1), [
		psi_symbol_redirect=
		AC_TRY_LINK(PSI_INCLUDES, [
			void (*fn)(void) = (void (*)(void)) $psi_symbol; (*fn)()
		], [
			psi_symbol_redirect=`nm -g conftest$ac_exeext | $AWK -F ' *|@' '/^@<:@@<:@:space:@:>@@:>@+U '$psi_cv_libc_main'/ {next} /^@<:@@<:@:space:@:>@@:>@+U / {print$[]3; exit}'`
		])
		[psi_cv_fn_]PSI_VAR_NAME($1)=$psi_symbol_redirect
	])
	case "$[psi_cv_fn_]PSI_VAR_NAME($1)" in
	"$psi_symbol"|"_$psi_symbol")
		case "$PHP_DEBUG-$3" in
		"1-")
			PSI_MACRO($1, $2, [
				psi_add_decl "$psi_decl_args"
			])
			;;
		*)
			psi_add_decl "$psi_decl_args" $3
			;;
		esac
		;;
	"")
		ifelse([$3], vararg, [
			AC_MSG_WARN(varargs macro support is not implemented)
		],[
			PSI_MACRO($1, $2, [
				psi_add_decl "$psi_decl_args"
			])
		])
		;;
	*)
		PSI_REDIR($psi_symbol)
		psi_add_decl "$psi_decl_args" $3
		;;
	esac
])
