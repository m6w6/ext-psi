
TOKEN_TYPE(decl_enum, struct psi_decl_enum *)
TOKEN_DTOR(decl_enum, psi_decl_enum_free(&$$);)
TOKEN_TYPE(decl_enum_items, struct psi_plist*)
TOKEN_DTOR(decl_enum_items, psi_plist_free($$);)
TOKEN_TYPE(decl_enum_item, struct psi_decl_enum_item*)
TOKEN_DTOR(decl_enum_item, psi_decl_enum_item_free(&$$);)
TOKEN_TYPE(decl_struct_args_block, struct psi_plist*)
TOKEN_DTOR(decl_struct_args_block, psi_plist_free($$);) /* there was a typo */
TOKEN_TYPE(decl_struct_args, struct psi_plist*)
TOKEN_DTOR(decl_struct_args, psi_plist_free($$);)
TOKEN_TYPE(decl_struct, struct psi_decl_struct*)
TOKEN_DTOR(decl_struct, psi_decl_struct_free(&$$);)
TOKEN_TYPE(align_and_size, struct psi_layout)
TOKEN_TYPE(decl_union, struct psi_decl_union*)
TOKEN_DTOR(decl_union, psi_decl_union_free(&$$);)
TOKEN_TYPE(const_type, struct psi_const_type*)
TOKEN_DTOR(const_type, psi_const_type_free(&$$);)
TOKEN_TYPE(constant, struct psi_const*)
TOKEN_DTOR(constant, psi_const_free(&$$);)
TOKEN_TYPE(decl_typedef, struct psi_decl_arg*)
TOKEN_DTOR(decl_typedef, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_typedef_body_ex, struct psi_decl_arg*)
TOKEN_DTOR(decl_typedef_body_ex, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_typedef_body, struct psi_decl_arg*)
TOKEN_DTOR(decl_typedef_body, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_typedef_body_fn_args, struct psi_plist*)
TOKEN_DTOR(decl_typedef_body_fn_args, psi_plist_free($$);)
TOKEN_TYPE(decl, struct psi_decl*)
TOKEN_DTOR(decl, psi_decl_free(&$$);)
TOKEN_TYPE(decl_func, struct psi_decl_arg*)
TOKEN_DTOR(decl_func, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_abi, struct psi_decl_abi*)
TOKEN_DTOR(decl_abi, psi_decl_abi_free(&$$);)
TOKEN_TYPE(decl_var, struct psi_decl_var*)
TOKEN_DTOR(decl_var, psi_decl_var_free(&$$);)
TOKEN_TYPE(decl_vars, struct psi_plist*)
TOKEN_DTOR(decl_vars, psi_plist_free($$);)
TOKEN_TYPE(decl_arg, struct psi_decl_arg*)
TOKEN_DTOR(decl_arg, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_args, struct psi_plist*)
TOKEN_DTOR(decl_args, psi_plist_free($$);)
TOKEN_TYPE(struct_args, struct psi_plist*)
TOKEN_DTOR(struct_args, psi_plist_free($$);)
TOKEN_TYPE(struct_arg, struct psi_decl_arg*)
TOKEN_DTOR(struct_arg, psi_decl_arg_free(&$$);)
TOKEN_TYPE(decl_layout, struct psi_layout*)
TOKEN_DTOR(decl_layout, psi_layout_free(&$$);)
TOKEN_TYPE(decl_type, struct psi_decl_type*)
TOKEN_DTOR(decl_type, psi_decl_type_free(&$$);)
TOKEN_TYPE(const_decl_type, struct psi_decl_type*)
TOKEN_DTOR(const_decl_type, psi_decl_type_free(&$$);)
TOKEN_TYPE(impl, struct psi_impl*)
TOKEN_DTOR(impl, psi_impl_free(&$$);)
TOKEN_TYPE(impl_func, struct psi_impl_func*)
TOKEN_DTOR(impl_func, psi_impl_func_free(&$$);)
TOKEN_TYPE(impl_def_val, struct psi_impl_def_val*)
TOKEN_DTOR(impl_def_val, psi_impl_def_val_free(&$$);)
TOKEN_TYPE(impl_var, struct psi_impl_var*)
TOKEN_DTOR(impl_var, psi_impl_var_free(&$$);)
TOKEN_TYPE(impl_arg, struct psi_impl_arg*)
TOKEN_DTOR(impl_arg, psi_impl_arg_free(&$$);)
TOKEN_TYPE(impl_args, struct psi_plist*)
TOKEN_DTOR(impl_args, psi_plist_free($$);)
TOKEN_TYPE(impl_vararg, struct psi_impl_arg*)
TOKEN_DTOR(impl_vararg, psi_impl_arg_free(&$$);)
TOKEN_TYPE(impl_stmts, struct psi_plist*)
TOKEN_DTOR(impl_stmts, psi_plist_free($$);)
TOKEN_TYPE(impl_stmt, struct psi_token**)
TOKEN_DTOR(impl_stmt, psi_impl_stmt_free(&$$);)
TOKEN_TYPE(number, struct psi_number*)
TOKEN_DTOR(number, psi_number_free(&$$);)
TOKEN_TYPE(num_exp, struct psi_num_exp*)
TOKEN_DTOR(num_exp, psi_num_exp_free(&$$);)
TOKEN_TYPE(let_stmt, struct psi_let_stmt*)
TOKEN_DTOR(let_stmt, psi_let_stmt_free(&$$);)
TOKEN_TYPE(let_calloc, struct psi_let_calloc*)
TOKEN_DTOR(let_calloc, psi_let_calloc_free(&$$);)
TOKEN_TYPE(let_func, struct psi_let_func*)
TOKEN_DTOR(let_func, psi_let_func_free(&$$);)
TOKEN_TYPE(callback_arg_list, struct psi_plist *)
TOKEN_DTOR(callback_arg_list, psi_plist_free($$);)
TOKEN_TYPE(callback_args, struct psi_plist *)
TOKEN_DTOR(callback_args, psi_plist_free($$);)
TOKEN_TYPE(let_callback, struct psi_let_callback*)
TOKEN_DTOR(let_callback, psi_let_callback_free(&$$);)
TOKEN_TYPE(let_exp, struct psi_let_exp*)
TOKEN_DTOR(let_exp, psi_let_exp_free(&$$);)
TOKEN_TYPE(let_exps, struct psi_plist*)
TOKEN_DTOR(let_exps, psi_plist_free($$);)
TOKEN_TYPE(assert_stmt, struct psi_assert_stmt*)
TOKEN_DTOR(assert_stmt, psi_assert_stmt_free(&$$);)
TOKEN_TYPE(set_stmt, struct psi_set_stmt*)
TOKEN_DTOR(set_stmt, psi_set_stmt_free(&$$);)
TOKEN_TYPE(set_exp, struct psi_set_exp*)
TOKEN_DTOR(set_exp, psi_set_exp_free(&$$);)
TOKEN_TYPE(set_exps, struct psi_plist*)
TOKEN_DTOR(set_exps, psi_plist_free($$);)
TOKEN_TYPE(set_func, struct psi_set_func*)
TOKEN_DTOR(set_func, psi_set_func_free(&$$);)
TOKEN_TYPE(return_stmt, struct psi_return_stmt*)
TOKEN_DTOR(return_stmt, psi_return_stmt_free(&$$);)
TOKEN_TYPE(free_stmt, struct psi_free_stmt*)
TOKEN_DTOR(free_stmt, psi_free_stmt_free(&$$);)
TOKEN_TYPE(free_exps, struct psi_plist*)
TOKEN_DTOR(free_exps, psi_plist_free($$);)
TOKEN_TYPE(free_exp, struct psi_free_exp*)
TOKEN_DTOR(free_exp, psi_free_exp_free(&$$);)
TOKEN_TYPE(impl_type, struct psi_impl_type*)
TOKEN_DTOR(impl_type, psi_impl_type_free(&$$);)
TOKEN_TYPE(cpp_exp, struct psi_cpp_exp*)
TOKEN_DTOR(cpp_exp, psi_cpp_exp_free(&$$);)
TOKEN_TYPE(cpp_macro_decl, struct psi_cpp_macro_decl*)
TOKEN_DTOR(cpp_macro_decl, psi_cpp_macro_decl_free(&$$);)
TOKEN_TYPE(cpp_macro_decl_tokens, struct psi_plist*)
TOKEN_DTOR(cpp_macro_decl_tokens, psi_plist_free($$);)
TOKEN_TYPE(cpp_macro_exp, struct psi_num_exp*)
TOKEN_DTOR(cpp_macro_exp, psi_num_exp_free(&$$);)
TOKEN_TYPE(cpp_macro_sig, struct psi_plist*)
TOKEN_DTOR(cpp_macro_sig, psi_plist_free($$);)
TOKEN_TYPE(cpp_macro_sig_args, struct psi_plist*)
TOKEN_DTOR(cpp_macro_sig_args, psi_plist_free($$);)
TOKEN_TYPE(cpp_macro_call, struct psi_plist*)
TOKEN_DTOR(cpp_macro_call, psi_plist_free($$);)
TOKEN_TYPE(cpp_macro_call_args, struct psi_plist*)
TOKEN_DTOR(cpp_macro_call_args, psi_plist_free($$);)

TOKEN_TYPE(reference, bool)
TOKEN_TYPE(indirection, unsigned)
TOKEN_TYPE(pointers, unsigned)


PARSE(block, TYPED(impl, impl)) {
	if (!P->impls) {
		P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	P->impls = psi_plist_add(P->impls, &impl);
}



/*
 * decl_vars: decl_var
 */
PARSE_TYPED(decl_vars, vars,
		TYPED(decl_var, var)) {
	vars = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
			&var);
}

/*
 * decl_vars: decl_vars , decl_var
 */
PARSE_TYPED(decl_vars, vars,
		TYPED(decl_vars, vars_)
		TOKEN(COMMA)
		TYPED(decl_var, var)) {
	vars = psi_plist_add(vars_, &var);
}



