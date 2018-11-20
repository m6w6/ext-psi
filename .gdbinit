define psi_assert_stmt_dump
	call psi_assert_stmt_dump((void*)0, $arg0)
	echo \n
end
define psi_const_dump
	call psi_const_dump((void*)0, $arg0)
	echo \n
end
define psi_const_type_dump
	call psi_const_type_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_abi_dump
	call psi_decl_abi_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_arg_dump
	call psi_decl_arg_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_decl_enum_dump
	call psi_decl_enum_dump((void*)0, $arg0, 0)
	echo \n
end
define psi_decl_enum_item_dump
	call psi_decl_enum_item_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_dump
	call psi_decl_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_struct_dump
	call psi_decl_struct_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_type_dump
	call psi_decl_type_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_decl_type_dump_args_with_layout
	call psi_decl_type_dump_args_with_layout((void*)0, $arg0, 0)
	echo \n
end
define psi_decl_union_dump
	call psi_decl_union_dump((void*)0, $arg0)
	echo \n
end
define psi_decl_var_dump
	call psi_decl_var_dump((void*)0, $arg0)
	echo \n
end
define psi_free_exp_dump
	call psi_free_exp_dump((void*)0, $arg0)
	echo \n
end
define psi_free_stmt_dump
	call psi_free_stmt_dump((void*)0, $arg0)
	echo \n
end
define psi_impl_arg_dump
	call psi_impl_arg_dump((void*)0, $arg0)
	echo \n
end
define psi_impl_def_val_dump
	call psi_impl_def_val_dump((void*)0, $arg0)
	echo \n
end
define psi_impl_func_dump
	call psi_impl_func_dump((void*)0, $arg0)
	echo \n
end
define psi_impl_dump
	call psi_impl_dump((void*)0, $arg0)
	echo \n
end
define psi_let_callback_dump
	call psi_let_callback_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_let_calloc_dump
	call psi_let_calloc_dump((void*)0, $arg0)
	echo \n
end
define psi_let_exp_dump
	call psi_let_exp_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_let_func_dump
	call psi_let_func_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_let_stmt_dump
	call psi_let_stmt_dump((void*)0, $arg0)
	echo \n
end
define psi_number_dump
	call psi_number_dump((void*)0, $arg0)
	echo \n
end
define psi_num_exp_dump
	call psi_num_exp_dump((void*)0, $arg0)
	echo \n
end
define psi_return_stmt_dump
	call psi_return_stmt_dump((void*)0, $arg0)
	echo \n
end
define psi_set_exp_dump
	call psi_set_exp_dump((void*)0, $arg0, 0, 0)
	 echo \n
end
define psi_set_func_dump
	call psi_set_func_dump((void*)0, $arg0, 0)
	 echo \n
end
define psi_set_stmt_dump
	call psi_set_stmt_dump((void*)0, $arg0)
	echo \n
end
define psi_token_dump
	call psi_token_dump((void*)0, $arg0)
end
define psi_token_list_dump
	set $i = 0
	while $i < $arg0->count
		call psi_token_dump((void*)0, ((struct psi_token **)$arg0->list)[$i++])
	end
end
define psi_plist_dump
	set $i = 0
	while $i < $arg0->count
		set $arg = ((void **) $arg0->list)[$i++]
		$arg1 $arg
	end
end
define psi_decl_type_dump_all
	if $argc > 0
		set $context = $arg0
	else
		set $context = psi_globals.context
	end
	set $i = 0
	set $c = psi_plist_count($context->types)
	while $i < $c
		set $type = *(struct psi_decl_type **) ($context->types->list[$i++])
		psi_decl_type_dump $type
		echo
	end
end
