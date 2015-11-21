AC_DEFUN([AX_CHECK_SIGN], [
	typename=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g"`
	AC_CACHE_CHECK([whether $1 is signed], ax_cv_decl_${typename}_signed, [
			AC_TRY_COMPILE([$4],
					[ int foo @<:@ 1 - 2 * !((($1) -1) < 0) @:>@ ],
					[ eval "ax_cv_decl_${typename}_signed=\"yes\"" ],
					[ eval "ax_cv_decl_${typename}_signed=\"no\"" ])])
	symbolname=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g" | tr "a-z" "A-Z"`
	if eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"yes\""; then
			$2
	elif eval "test \"\${ax_cv_decl_${typename}_signed}\" = \"no\""; then
			$3
	fi
])
