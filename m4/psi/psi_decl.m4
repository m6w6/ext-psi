# psi_add_redir(name, symbol)
# Add a function redirection to $PSI_REDIRS_H.
psi_add_redir() {
	PSI_REDIRS="$PSI_REDIRS
	{\"$1\", (psi_func_ptr) $2},"
}

# psi_add_decl(decl, options)
# Add a pre-defined decl to $PSI_VA_DECLS_H/$PSI_DECLS_H.
psi_add_decl() {
	PSI_DECLS="$PSI_DECLS
	$1, {0},"
}

dnl PSI_DECL_TYPE(type functor_name, args)
dnl Adds a pre-defined functor decl to $PSI_FN_DECLS_H.
AC_DEFUN(PSI_DECL_TYPE, [
	PSI_DECL_ARGS($1, $2, functor)
	psi_add_decl "$psi_decl_args"
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

dnl PSI_DECL_ARGS(decl func, decl args, options)
dnl INTERNAL: build psi_decl_args
AC_DEFUN(PSI_DECL_ARGS, [
	psi_decl_args=
	PSI_DECL_ARG([$1], [$3])
	m4_case([$2],
		[(void)], [],
		[()], [],
		[], [],
		[m4_map_args_sep(
			[PSI_DECL_ARG(m4_normalize(], 
			[), [0])], [], m4_bregexp([$2], [(\(.*\))], [\1]))])
])

dnl PSI_DECL_ARG(decl arg, options)
dnl INTERNAL: build psi_decl_args
AC_DEFUN(PSI_DECL_ARG, [
    m4_define([member_name], PSI_VAR_NAME([$1]))
    m4_define([member_type], PSI_VAR_TYPE([$1]))

	PSI_TYPE_INDIRECTION([$1],, pl, as)
    if test -n "$psi_decl_args"; then
        psi_decl_args="$psi_decl_args, "
    fi
    psi_decl_args="[$psi_decl_args{]ifelse([$2],,DECL_KIND_STD,[ifelse([$2],0,0,AS_TR_CPP([DECL_KIND_$2]))])[, ]PSI_TYPE_PAIR(member_type)[, \"]member_name[\",] $pl, $as[}]"
])

dnl PSI_DECL(type func, args, flags, libs)
dnl Check for a function or macro declaration and a possible asm redirection.
dnl Adds a pre-defined (vararg) decl to $PSI_VA_DECLS_H/$PSI_DECLS_H.
dnl Calls PSI_MACRO if PSI_FUNC fails.
AC_DEFUN(PSI_DECL, [
	AC_REQUIRE([PSI_FUNC_LIBC_MAIN])dnl

	PSI_DECL_ARGS($1, $2, $3)

	psi_symbol="PSI_VAR_NAME($1)"
	AC_CACHE_CHECK(for PSI_VAR_NAME($1), [psi_cv_fn_]PSI_VAR_NAME($1), [
		psi_decl_check=
		psi_symbol_redirect=
		for lib in "" $4; do
			decl_save_LIBS=$LIBS
			LIBS=$lib
			AC_TRY_LINK(PSI_INCLUDES, [
				void (*fn)(long, long, long) = (void (*)(long,long,long)) $psi_symbol;
				fn(1,2,3);
			], [
				psi_symbol_redirect=`nm -g conftest$ac_exeext | $AWK -F ' *|@' '/^@<:@@<:@:space:@:>@@:>@+U '$psi_cv_libc_main'/ {next} /^@<:@@<:@:space:@:>@@:>@+U / {print$[]3; exit}'`
			])
			LIBS=$decl_save_LIBS

			if test -n "$psi_symbol_redirect"; then
				if test -n "$lib"; then
					psi_decl_check="$psi_symbol_redirect in $lib"
				else
					psi_decl_check="$psi_symbol_redirect"
				fi
				break
			fi
		done
		[psi_cv_fn_]PSI_VAR_NAME($1)=$psi_decl_check
	])

	psi_symbol_redirect=`AS_ECHO("$[psi_cv_fn_]PSI_VAR_NAME($1)") | $AWK -F " in " '{print [$]1}'`
	psi_symbol_libflag=`AS_ECHO("$[psi_cv_fn_]PSI_VAR_NAME($1)") | $AWK -F " in " '{print [$]2}'`

	if test -n "$psi_symbol_libflag"; then
		if ! expr "X$LIBS" : "X.*\b$psi_symbol_libflag\b" >/dev/null; then
			LIBS="$psi_symbol_libflag $LIBS"
		fi
	fi

	case "$psi_symbol_redirect" in
	"$psi_symbol"|"_$psi_symbol")
		case "$PSI_EXTRA_REDIRS-$3" in
		"true-")
			PSI_MACRO($1, $2, [
				psi_add_decl "$psi_decl_args"
			])
			;;
		*)
			if test -n "$psi_symbol_libflag"
			then
				PSI_REDIR($psi_symbol)
			fi
			psi_add_decl "$psi_decl_args"
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
		psi_add_decl "$psi_decl_args"
		;;
	esac
])
