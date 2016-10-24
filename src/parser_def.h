#define _CONCAT(x,y) x##y
#define CONCAT(x,y) _CONCAT(x,y)
#define COUNTED(x) CONCAT(parse_ ##x## _, __LINE__)

#ifdef GENERATE
#define DEF(dn, dv) dn dv
#define PASS(nt, rule) nt ::= rule.
#define PARSE(nt, rule) nt ::= rule.
#define PARSE_NAMED(nt, nt_name, rule) NAMED(nt, nt_name) ::= rule.
#define PARSE_TYPED(nt, nt_name, rule) TYPED(nt, nt_name) ::= rule.
#define TOKEN(t) t
#define NAMED(t, name) t(name)
#define TYPED(t, name) t(name)
#define TOKEN_TYPE(token, type_) %type token {type_}
#define TOKEN_DTOR(token, dtor) %destructor token {dtor}
#else
#ifndef TEST
#include "parser.h"
#endif
#define DEF(dn, dv)
#define PASS(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P) { \
		(void) #rule; \
	}
#define PARSE(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P rule)
#define PARSE_NAMED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P NAMED(nt, nt_name) rule)
#define PARSE_TYPED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P TYPED(nt, nt_name) rule)
#define TOKEN(t)
#define NAMED(t, name) , struct psi_token *name
#define TYPED(t, name) , TOKEN_TYPE_NAME(t) name
#define TOKEN_TYPE_NAME(token) ##token##_parse_t
#define TOKEN_TYPE(token, type) typedef type TOKEN_TYPE_NAME(token);
#define TOKEN_DTOR(token, dtor)
#endif

DEF(%name, psi_parser_proc_)
DEF(%token_prefix, PSI_T_)
DEF(%token_type, {struct psi_token *})
DEF(%token_destructor, {free($$);})
DEF(%default_destructor, {(void)P;})
DEF(%extra_argument, {struct psi_parser *P})

/* TOKEN is defined inside syntax_error */
DEF(%syntax_error, {
	++P->errors;
	if (TOKEN && TOKEN->type != PSI_T_EOF) {
		psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col);
	} else {
		psi_error(PSI_WARNING, P->psi.file.fn, P->line, "PSI syntax error: Unexpected end of input");
	}
})

DEF(%nonassoc, NAME.)
DEF(%left, PLUS MINUS.)
DEF(%left, ASTERISK SLASH.)
DEF(%nonassoc, AMPERSAND.)
DEF(%fallback, NAME TEMP FREE SET LET RETURN CALLOC CALLBACK ZVAL LIB STRING COUNT.)

DEF(%token_class, const_type_token BOOL INT FLOAT STRING.)
DEF(%token_class, decl_type_token FLOAT DOUBLE INT8 UINT8 INT16 UINT16 INT32 UINT32 INT64 UINT64 NAME.)
DEF(%token_class, impl_def_val_token NULL NUMBER TRUE FALSE QUOTED_STRING.)
DEF(%token_class, num_exp_token NUMBER NSNAME.)
DEF(%token_class, num_exp_op_token PLUS MINUS ASTERISK SLASH.)
DEF(%token_class, let_func_token ZVAL OBJVAL ARRVAL PATHVAL STRLEN STRVAL FLOATVAL INTVAL BOOLVAL COUNT.)
DEF(%token_class, set_func_token TO_OBJECT TO_ARRAY TO_STRING TO_INT TO_FLOAT TO_BOOL ZVAL VOID.)
DEF(%token_class, impl_type_token VOID MIXED BOOL INT FLOAT STRING ARRAY OBJECT CALLABLE.)

TOKEN_TYPE(decl_enum, decl_enum *)
TOKEN_DTOR(decl_enum, free_decl_enum($$);)
TOKEN_TYPE(decl_enum_items, decl_enum_items*)
TOKEN_DTOR(decl_enum_items, free_decl_enum_items($$);)
TOKEN_TYPE(decl_enum_item, decl_enum_item*)
TOKEN_DTOR(decl_enum_item, free_decl_enum_item($$);)
TOKEN_TYPE(decl_struct_args_block, decl_args*)
TOKEN_DTOR(decl_struct_args_block, free_decl_args($$);) /* there was a typo */
TOKEN_TYPE(decl_struct_args, decl_args*)
TOKEN_DTOR(decl_struct_args, free_decl_args($$);)
TOKEN_TYPE(decl_struct, decl_struct*)
TOKEN_DTOR(decl_struct, free_decl_struct($$);)
TOKEN_TYPE(align_and_size, decl_struct_layout)
TOKEN_TYPE(decl_union, decl_union*)
TOKEN_DTOR(decl_union, free_decl_union($$);)
TOKEN_TYPE(const_type, const_type*)
TOKEN_DTOR(const_type, free_const_type($$);)
TOKEN_TYPE(constant, constant*)
TOKEN_DTOR(constant, free_constant($$);)
TOKEN_TYPE(decl_typedef, decl_arg*)
TOKEN_DTOR(decl_typedef, free_decl_arg($$);)
TOKEN_TYPE(decl_typedef_body_ex, decl_arg*)
TOKEN_DTOR(decl_typedef_body_ex, free_decl_arg($$);)
TOKEN_TYPE(decl_typedef_body, decl_arg*)
TOKEN_DTOR(decl_typedef_body, free_decl_arg($$);)
TOKEN_TYPE(decl_typedef_body_fn_args, decl_args *)
TOKEN_DTOR(decl_typedef_body_fn_args, free_decl_args($$);)
TOKEN_TYPE(decl, decl*)
TOKEN_DTOR(decl, free_decl($$);)
TOKEN_TYPE(decl_func, decl_arg*)
TOKEN_DTOR(decl_func, free_decl_arg($$);)
TOKEN_TYPE(decl_abi, decl_abi*)
TOKEN_DTOR(decl_abi, free_decl_abi($$);)
TOKEN_TYPE(decl_var, decl_var*)
TOKEN_DTOR(decl_var, free_decl_var($$);)
TOKEN_TYPE(decl_vars, decl_vars*)
TOKEN_DTOR(decl_vars, free_decl_vars($$);)
TOKEN_TYPE(decl_arg, decl_arg*)
TOKEN_DTOR(decl_arg, free_decl_arg($$);)
TOKEN_TYPE(decl_args, decl_args*)
TOKEN_DTOR(decl_args, free_decl_args($$);)
TOKEN_TYPE(struct_args, decl_args*)
TOKEN_DTOR(struct_args, free_decl_args($$);)
TOKEN_TYPE(struct_arg, decl_arg*)
TOKEN_DTOR(struct_arg, free_decl_arg($$);)
TOKEN_TYPE(struct_layout, decl_struct_layout*)
TOKEN_DTOR(struct_layout, free_decl_struct_layout($$);)
TOKEN_TYPE(decl_type, decl_type*)
TOKEN_DTOR(decl_type, free_decl_type($$);)
TOKEN_TYPE(const_decl_type, decl_type*)
TOKEN_DTOR(const_decl_type, free_decl_type($$);)
TOKEN_TYPE(impl, impl*)
TOKEN_DTOR(impl, free_impl($$);)
TOKEN_TYPE(impl_func, impl_func*)
TOKEN_DTOR(impl_func, free_impl_func($$);)
TOKEN_TYPE(impl_def_val, impl_def_val*)
TOKEN_DTOR(impl_def_val, free_impl_def_val($$);)
TOKEN_TYPE(impl_var, impl_var*)
TOKEN_DTOR(impl_var, free_impl_var($$);)
TOKEN_TYPE(impl_arg, impl_arg*)
TOKEN_DTOR(impl_arg, free_impl_arg($$);)
TOKEN_TYPE(impl_args, impl_args*)
TOKEN_DTOR(impl_args, free_impl_args($$);)
TOKEN_TYPE(impl_vararg, impl_arg*)
TOKEN_DTOR(impl_vararg, free_impl_arg($$);)
TOKEN_TYPE(impl_arg_list, impl_args*)
TOKEN_DTOR(impl_arg_list, free_impl_args($$);)
TOKEN_TYPE(impl_stmts, impl_stmts*)
TOKEN_DTOR(impl_stmts, free_impl_stmts($$);)
TOKEN_TYPE(impl_stmt, impl_stmt*)
TOKEN_DTOR(impl_stmt, free_impl_stmt($$);)
TOKEN_TYPE(num_exp, num_exp*)
TOKEN_DTOR(num_exp, free_num_exp($$);)
TOKEN_TYPE(let_stmt, let_stmt*)
TOKEN_DTOR(let_stmt, free_let_stmt($$);)
TOKEN_TYPE(let_calloc, let_calloc*)
TOKEN_DTOR(let_calloc, free_let_calloc($$);)
TOKEN_TYPE(let_func, let_func*)
TOKEN_DTOR(let_func, free_let_func($$);)
TOKEN_TYPE(callback_arg_list, set_values *)
TOKEN_DTOR(callback_arg_list, free_set_values($$);)
TOKEN_TYPE(callback_args, set_values *)
TOKEN_DTOR(callback_args, free_set_values($$);)
TOKEN_TYPE(let_val, let_val*)
TOKEN_DTOR(let_val, free_let_val($$);)
TOKEN_TYPE(let_vals, let_vals*)
TOKEN_DTOR(let_vals, free_let_vals($$);)
TOKEN_TYPE(set_stmt, set_stmt*)
TOKEN_DTOR(set_stmt, free_set_stmt($$);)
TOKEN_TYPE(set_value, set_value*)
TOKEN_DTOR(set_value, free_set_value($$);)
TOKEN_TYPE(set_vals, set_value*)
TOKEN_DTOR(set_vals, free_set_value($$);)
TOKEN_TYPE(set_func, set_func*)
TOKEN_DTOR(set_func, free_set_func($$);)
TOKEN_TYPE(return_stmt, return_stmt*)
TOKEN_DTOR(return_stmt, free_return_stmt($$);)
TOKEN_TYPE(free_stmt, free_stmt*)
TOKEN_DTOR(free_stmt, free_free_stmt($$);)
TOKEN_TYPE(free_calls, free_calls*)
TOKEN_DTOR(free_calls, free_free_calls($$);)
TOKEN_TYPE(free_call, free_call*)
TOKEN_DTOR(free_call, free_free_call($$);)
TOKEN_TYPE(impl_type, impl_type*)
TOKEN_DTOR(impl_type, free_impl_type($$);)
TOKEN_TYPE(reference, char)
TOKEN_TYPE(indirection, unsigned)
TOKEN_TYPE(pointers, unsigned)

PASS(file, blocks)
PASS(blocks, block)
PASS(blocks, blocks block)

PASS(block, EOF)
PASS(block, EOS)

PARSE(block, NAMED(LIB, token) NAMED(QUOTED_STRING, libname) TOKEN(EOS)) {
	if (P->psi.file.ln) {
		P->error(P, token, PSI_WARNING, "Extra 'lib %s' statement has no effect", libname->text);
	} else {
		P->psi.file.ln = strndup(libname->text + 1, libname->size - 2);
	}
	free(libname);
	free(token);
}
PARSE(block, TYPED(decl, decl)) {
	P->decls = add_decl(P->decls, decl);
}

PARSE(block, TYPED(impl, impl)) {
	P->impls = add_impl(P->impls, impl);
}

PARSE(block, TYPED(decl_typedef, def)) {
	P->defs = add_decl_typedef(P->defs, def);
	switch (def->type->type) {
	case PSI_T_STRUCT:
		if (def->type->real.strct) {
			P->structs = add_decl_struct(P->structs, def->type->real.strct);
		}
		break;
	case PSI_T_UNION:
		if (def->type->real.unn) {
			P->unions = add_decl_union(P->unions, def->type->real.unn);
		}
		break;
	case PSI_T_ENUM:
		if (def->type->real.enm) {
			P->enums = add_decl_enum(P->enums, def->type->real.enm);
		}
		break;
	}
}

PARSE(block, TYPED(constant, constant)) {
	P->consts = add_constant(P->consts, constant);
}

PARSE(block, TYPED(decl_struct, strct)) {
	P->structs = add_decl_struct(P->structs, strct);
}

PARSE(block, TYPED(decl_union, u)) {
	P->unions = add_decl_union(P->unions, u);
}

PARSE(block, TYPED(decl_enum, e)) {
	P->enums = add_decl_enum(P->enums, e);
}

PARSE_NAMED(optional_name, n, ) {
	n = NULL;
}

PARSE_NAMED(optional_name, n,
		NAMED(NAME, N)) {
	n = N;
}

PARSE_NAMED(enum_name, n,
		NAMED(ENUM, E) NAMED(optional_name, N)) {
	if (N) {
		n = N;
		free(E);
	} else {
		char digest[17];

		psi_token_hash(E, digest);
		n = psi_token_translit(psi_token_append(E, 1, digest), " ", "@");
	}
}

PARSE_TYPED(decl_enum, e,
		NAMED(enum_name, N)
		TOKEN(LBRACE)
		TYPED(decl_enum_items, list)
		TOKEN(RBRACE)) {
	e = init_decl_enum(N->text, list);
	e->token = N;
}

PARSE_TYPED(decl_enum_items, l,
		TYPED(decl_enum_item, i)) {
	l = init_decl_enum_items(i);
}
PARSE_TYPED(decl_enum_items, l,
		TYPED(decl_enum_items, l_)
		TOKEN(COMMA)
		TYPED(decl_enum_item, i)) {
	l = add_decl_enum_item(l_, i);
}

PARSE_TYPED(decl_enum_item, i,
		NAMED(NAME, N)
		TOKEN(EQUALS)
		TYPED(num_exp, num)) {
	i = init_decl_enum_item(N->text, num);
	i->token = N;
}
PARSE_TYPED(decl_enum_item, i,
		NAMED(NAME, N)) {
	i = init_decl_enum_item(N->text, NULL);
	i->token = N;
}

PARSE_NAMED(union_name, n,
		NAMED(UNION, U)
		NAMED(optional_name, N)) {
	if (N) {
		n = N;
		free(U);
	} else {
		char digest[17];

		psi_token_hash(U, digest);
		n = psi_token_translit(psi_token_append(U, 1, digest), " ", "@");
	}
}

PARSE_NAMED(struct_name, n,
		NAMED(STRUCT, S)
		NAMED(optional_name, N)) {
	if (N) {
		n = N;
		free(S);
	} else {
		char digest[17];

		psi_token_hash(S, digest);
		n = psi_token_translit(psi_token_append(S, 1, digest), " ", "@");
	}
}

PARSE_TYPED(decl_struct_args_block, args_,
		TOKEN(LBRACE)
		TYPED(struct_args, args)
		TOKEN(RBRACE)) {
	args_ = args;
}

PARSE_TYPED(decl_struct_args, args_,
		TYPED(decl_struct_args_block, args)) {
	args_ = args;
}
PARSE_TYPED(decl_struct_args, args_,
		TOKEN(EOS)) {
	args_ = init_decl_args(NULL);
}

PARSE_TYPED(decl_struct, strct,
		TOKEN(STRUCT)
		NAMED(NAME, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args, args)) {
	strct = init_decl_struct(N->text, args);
	strct->align = as.pos;
	strct->size = as.len;
	strct->token = N;
}

PARSE_TYPED(align_and_size, as, ) {
	as.pos = 0;
	as.len = 0;
}
PARSE_TYPED(align_and_size, as,
		TOKEN(COLON)
		TOKEN(COLON)
		TOKEN(LPAREN)
		NAMED(NUMBER, A)
		TOKEN(COMMA)
		NAMED(NUMBER, S)
		TOKEN(RPAREN)) {
	as.pos = atol(A->text);
	as.len = atol(S->text);
	free(A);
	free(S);
}

PARSE_TYPED(decl_union, u,
		TOKEN(UNION)
		NAMED(NAME, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args, args)) {
	u = init_decl_union(N->text, args);
	u->align = as.pos;
	u->size = as.len;
	u->token = N;
}

PARSE_TYPED(const_type, type_,
		NAMED(const_type_token, T)) {
	type_ = init_const_type(T->type, T->text);
	free(T);
}

PARSE_TYPED(constant, constant,
		TOKEN(CONST)
		TYPED(const_type, type)
		NAMED(NSNAME, T)
		TOKEN(EQUALS)
		TYPED(impl_def_val, val)
		TOKEN(EOS)) {
	constant = init_constant(type, T->text, val);
	free(T);
}

PARSE_TYPED(decl_typedef, def,
		NAMED(TYPEDEF, T)
		TYPED(decl_typedef_body, def_)
		TOKEN(EOS)) {
	def = def_;
	def->token = T;
}

PARSE_TYPED(decl_typedef_body_ex, def,
		NAMED(struct_name, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args_block, args)
		TYPED(decl_var, var)) {
	def = init_decl_arg(init_decl_type(PSI_T_STRUCT, N->text), var);
	def->type->token = psi_token_copy(N);
	def->type->real.strct = init_decl_struct(N->text, args);
	def->type->real.strct->token = N;
	def->type->real.strct->align = as.pos;
	def->type->real.strct->size = as.len;
}
PARSE_TYPED(decl_typedef_body_ex, def,
		NAMED(union_name, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args_block, args)
		TYPED(decl_var, var)) {
	def = init_decl_arg(init_decl_type(PSI_T_UNION, N->text), var);
	def->type->token = psi_token_copy(N);
	def->type->real.unn = init_decl_union(N->text, args);
	def->type->real.unn->token = N;
	def->type->real.unn->align = as.pos;
	def->type->real.unn->size = as.len;
}
PARSE_TYPED(decl_typedef_body_ex, def,
		TYPED(decl_enum, e)
		NAMED(NAME, ALIAS)) {
	def = init_decl_arg(init_decl_type(PSI_T_ENUM, e->name), init_decl_var(ALIAS->text, 0, 0));
	def->var->token = ALIAS;
	def->type->token = psi_token_copy(e->token);
	def->type->real.enm = e;
}

PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_typedef_body_ex, def_)) {
	def = def_;
}

PARSE_TYPED(decl_typedef_body_fn_args, args,
		TOKEN(LPAREN)
		TYPED(decl_args, args_)
		TOKEN(RPAREN)) {
	args = args_;
}
PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_func, func_)
		TYPED(decl_typedef_body_fn_args, args)) {
	def = init_decl_arg(init_decl_type(PSI_T_FUNCTION, func_->var->name), copy_decl_var(func_->var));
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = init_decl(init_decl_abi("default"), func_, args);
}
PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_arg, arg)) {
	def = arg;
}

PARSE_TYPED(decl, decl,
		TYPED(decl_abi, abi)
		TYPED(decl_func, func)
		TOKEN(LPAREN)
		TYPED(decl_args, args)
		TOKEN(RPAREN)
		TOKEN(EOS)) {
	decl = init_decl(abi, func, args);
}

PARSE_TYPED(decl_func, func,
		TYPED(decl_arg, arg)) {
	func = arg;
}
/* special case for void functions */
PARSE_TYPED(decl_func, func,
		NAMED(VOID, T)
		NAMED(NAME, N)) {
	func = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, 0, 0)
	);
	func->type->token = T;
	func->var->token = N;
	func->token = N;
}
PARSE_TYPED(decl_typedef_body, def,
		NAMED(VOID, T)
		TYPED(indirection, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	decl_arg *func_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, decl_i, 0)
	);
	func_->type->token = T;
	func_->var->token = N;
	func_->token = N;

	def = init_decl_arg(
		init_decl_type(PSI_T_FUNCTION, func_->var->name),
		copy_decl_var(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = init_decl(init_decl_abi("default"), func_, args);
}
PARSE_TYPED(decl_typedef_body, def,
		TOKEN(CONST)
		NAMED(VOID, T)
		TYPED(pointers, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	decl_arg *func_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, decl_i, 0)
	);
	func_->type->token = T;
	func_->var->token = N;
	func_->token = N;

	def = init_decl_arg(
		init_decl_type(PSI_T_FUNCTION, func_->var->name),
		copy_decl_var(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = init_decl(init_decl_abi("default"), func_, args);
}

PARSE_TYPED(decl_abi, abi,
		NAMED(NAME, T)) {
	abi = init_decl_abi(T->text);
	abi->token = T;
}

PARSE_TYPED(decl_var, var,
		NAMED(NAME, T)
		NAMED(decl_var_array_size, as)) {
	var = init_decl_var(T->text, 0, as?atol(as->text):0);
	var->token = T;
	if (as) {
		free(as);
	}
}
PARSE_TYPED(decl_var, var,
		TYPED(pointers, p)
		NAMED(NAME, T)
		NAMED(decl_var_array_size, as)) {
	var = init_decl_var(T->text, p+!!as, as?atol(as->text):0);
	var->token = T;
	if (as) {
		free(as);
	}
}
PARSE_NAMED(decl_var_array_size, as, ) {
	as = NULL;
}
PARSE_NAMED(decl_var_array_size, as,
		TOKEN(LBRACKET)
		NAMED(NUMBER, D)
		TOKEN(RBRACKET)) {
	as = D;
}

PARSE_TYPED(decl_vars, vars,
		TYPED(decl_var, var)) {
	vars = init_decl_vars(var);
}
PARSE_TYPED(decl_vars, vars,
		TYPED(decl_vars, vars_)
		TOKEN(COMMA)
		TYPED(decl_var, var)) {
	vars = add_decl_var(vars_, var);
}

PARSE_TYPED(decl_arg, arg_,
		TYPED(const_decl_type, type)
		TYPED(decl_var, var)) {
	arg_ = init_decl_arg(type, var);
}
PARSE_TYPED(decl_typedef_body, def,
		TYPED(const_decl_type, type_)
		TYPED(indirection, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	decl_arg *func_ = init_decl_arg(
		type_,
		init_decl_var(N->text, decl_i, 0)
	);
	func_->var->token = N;
	func_->token = N;

	def = init_decl_arg(
		init_decl_type(PSI_T_FUNCTION, func_->var->name),
		copy_decl_var(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = init_decl(init_decl_abi("default"), func_, args);
}

/* void pointers need a specific rule */
PARSE_TYPED(decl_arg, arg_,
		NAMED(VOID, T)
		TYPED(pointers, p)
		NAMED(NAME, N)) {
	arg_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}
PARSE_TYPED(decl_arg, arg_,
		TOKEN(CONST)
		NAMED(VOID, T)
		TYPED(pointers, p)
		NAMED(NAME, N)) {
	arg_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}

PASS(decl_args, )
PASS(decl_args, VOID)
PARSE_TYPED(decl_args, args,
		TYPED(decl_arg, arg)) {
	args = init_decl_args(arg);
}
PARSE_TYPED(decl_args, args,
		TYPED(decl_args, args_)
		TOKEN(COMMA)
		TYPED(decl_arg, arg)) {
	args = add_decl_arg(args_, arg);
}
PARSE_TYPED(decl_args, args,
		TYPED(decl_args, args_)
		TOKEN(COMMA)
		TOKEN(ELLIPSIS)) {
	args = args_;
	args->varargs = 1;
}

PARSE_TYPED(struct_args, args,
		TYPED(struct_arg, arg)) {
	args = init_decl_args(arg);
}
PARSE_TYPED(struct_args, args,
		TYPED(struct_args, args_)
		TYPED(struct_arg, arg)) {
	args = add_decl_arg(args_, arg);
}

PARSE_TYPED(struct_arg, arg_,
		TYPED(decl_typedef_body_ex, def)
		TOKEN(EOS)) {
	arg_ = def;
	switch (def->type->type) {
	case PSI_T_STRUCT:
		if (def->type->real.strct) {
			P->structs = add_decl_struct(P->structs, def->type->real.strct);
		}
		break;
	case PSI_T_UNION:
		if (def->type->real.unn) {
			P->unions = add_decl_union(P->unions, def->type->real.unn);
		}
		break;
	case PSI_T_ENUM:
		if (def->type->real.enm) {
			P->enums = add_decl_enum(P->enums, def->type->real.enm);
		}
		break;
	}
}
PARSE_TYPED(struct_arg, arg,
		TYPED(decl_arg, arg_)
		TYPED(struct_layout, layout_)
		TOKEN(EOS)) {
	arg_->layout = layout_;
	arg = arg_;
}

PARSE_TYPED(struct_layout, layout, ) {
	layout = NULL;
}
PARSE_TYPED(struct_layout, layout,
		TOKEN(COLON)
		TOKEN(COLON)
		TOKEN(LPAREN)
		NAMED(NUMBER, POS)
		TOKEN(COMMA)
		NAMED(NUMBER, SIZ)
		TOKEN(RPAREN)) {
	layout = init_decl_struct_layout(atol(POS->text), atol(SIZ->text));
	free(POS);
	free(SIZ);
}

/* un/signed, urgh */
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(CHAR, C)) {
	type_ = C;
}
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(SHORT, S)
		NAMED(decl_scalar_type_short, s)) {
	if (s) {
		type_ = psi_token_cat(2, S, s);
		free(S);
		free(s);
	} else {
		type_ = S;
	}
}
PARSE_NAMED(decl_scalar_type_short, s, ) {
	s = NULL;
}

PARSE_NAMED(decl_scalar_type_short, s,
		NAMED(INT, I)) {
	s = I;
}
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(INT, I)) {
	type_ = I;
}
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(LONG, L)
		NAMED(decl_scalar_type_long, l)) {
	if (l) {
		type_ = psi_token_cat(2, L, l);
		free(L);
		free(l);
	} else {
		type_ = L;
	}
}
PARSE_NAMED(decl_scalar_type_long, l, ) {
	l = NULL;
}
PARSE_NAMED(decl_scalar_type_long, l,
		NAMED(DOUBLE, D)) {
	l = D;
}
PARSE_NAMED(decl_scalar_type_long, l,
		NAMED(LONG, L)
		NAMED(decl_scalar_type_long_long, ll)) {
	if (ll) {
		l = psi_token_cat(2, L, ll);
		free(L);
		free(ll);
	} else {
		l = L;
	}
}
PARSE_NAMED(decl_scalar_type_long_long, ll, ) {
	ll = NULL;
}
PARSE_NAMED(decl_scalar_type_long_long, ll,
		NAMED(INT, I)) {
	ll = I;
}
PARSE_TYPED(decl_type, type_,
		NAMED(UNSIGNED, U)
		NAMED(decl_scalar_type, N)) {
	struct psi_token *T = psi_token_cat(2, U, N);
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
	free(U);
	free(N);
}
PARSE_TYPED(decl_type, type_,
		NAMED(SIGNED, S)
		NAMED(decl_scalar_type, N)) {
	struct psi_token *T = psi_token_cat(2, S, N);
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
	free(S);
	free(N);
}
PARSE_TYPED(decl_type, type_,
		NAMED(UNSIGNED, U)) {
	type_ = init_decl_type(PSI_T_NAME, U->text);
	type_->token = U;
}
PARSE_TYPED(decl_type, type_,
		NAMED(SIGNED, S)) {
	type_ = init_decl_type(PSI_T_NAME, S->text);
	type_->token = S;
}
PARSE_TYPED(decl_type, type_,
		NAMED(decl_scalar_type, N)) {
	type_ = init_decl_type(N->type, N->text);
	type_->token = N;
}
/* structs ! */
PARSE_TYPED(decl_type, type_,
		NAMED(STRUCT, S)
		NAMED(NAME, T)) {
	type_ = init_decl_type(S->type, T->text);
	type_->token = T;
	free(S);
}
PARSE_TYPED(decl_type, type_,
		NAMED(UNION, U)
		NAMED(NAME, T)) {
	type_ = init_decl_type(U->type, T->text);
	type_->token = T;
	free(U);
}
PARSE_TYPED(decl_type, type_,
		NAMED(ENUM, E)
		NAMED(NAME, T)) {
	type_ = init_decl_type(E->type, T->text);
	type_->token = T;
	free(E);
}
PARSE_TYPED(decl_type, type_,
		NAMED(decl_type_token, T)) {
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
}


PARSE_TYPED(const_decl_type, type,
		TYPED(decl_type, type_)) {
	type = type_;
}
PARSE_TYPED(const_decl_type, type,
		TOKEN(CONST)
		TYPED(decl_type, type_)) {
	type = type_;
}

PARSE_TYPED(impl, impl,
		TYPED(impl_func, func)
		TOKEN(LBRACE)
		TYPED(impl_stmts, stmts)
		TOKEN(RBRACE)) {
	impl = init_impl(func, stmts);
}

PARSE_TYPED(impl_func, func,
		TOKEN(FUNCTION)
		TYPED(reference, r)
		NAMED(NSNAME, NAME)
		TYPED(impl_args, args)
		TOKEN(COLON)
		TYPED(impl_type, type)) {
	func = init_impl_func(NAME->text, args, type, r);
	func->token = NAME;
}

PARSE_TYPED(impl_def_val, def,
		NAMED(impl_def_val_token, T)) {
	def = init_impl_def_val(T->type, T->text);
	free(T);
}

PARSE_TYPED(impl_var, var,
		TYPED(reference, r)
		NAMED(DOLLAR_NAME, T)) {
	var = init_impl_var(T->text, r);
	var->token = T;
}

PARSE_TYPED(impl_arg, arg,
		TYPED(impl_type, type)
		TYPED(impl_var, var)) {
	arg = init_impl_arg(type, var, NULL);
}
PARSE_TYPED(impl_arg, arg,
		TYPED(impl_type, type)
		TYPED(impl_var, var)
		TOKEN(EQUALS)
		TYPED(impl_def_val, def)) {
	arg = init_impl_arg(type, var, def);
}

PARSE_TYPED(impl_args, args,
		TOKEN(LPAREN)
		TOKEN(RPAREN)) {
	args = NULL;
}
PARSE_TYPED(impl_args, args,
		TOKEN(LPAREN)
		TYPED(impl_arg_list, args_)
		TOKEN(RPAREN)) {
	args = args_;
}
PARSE_TYPED(impl_args, args,
		TOKEN(LPAREN)
		TYPED(impl_arg_list, args_)
		TOKEN(COMMA)
		TYPED(impl_vararg, va)
		TOKEN(RPAREN)) {
	args = args_;
	args->vararg.name = va;
}

PARSE_TYPED(impl_vararg, va,
		TYPED(impl_type, type)
		TYPED(reference, r)
		TOKEN(ELLIPSIS)
		NAMED(DOLLAR_NAME, T)) {
	va = init_impl_arg(type, init_impl_var(T->text, r), NULL);
	free(T);
}

PARSE_TYPED(impl_arg_list, args,
		TYPED(impl_arg, arg)) {
	args = init_impl_args(arg);
}
PARSE_TYPED(impl_arg_list, args,
		TYPED(impl_arg_list, args_)
		TOKEN(COMMA)
		TYPED(impl_arg, arg)) {
	args = add_impl_arg(args_, arg);
}

PARSE_TYPED(impl_stmts, stmts,
		TYPED(impl_stmt, stmt)) {
	stmts = init_impl_stmts(stmt);
}
PARSE_TYPED(impl_stmts, stmts,
		TYPED(impl_stmts, stmts_)
		TYPED(impl_stmt, stmt)) {
	stmts = add_impl_stmt(stmts_, stmt);
}

PARSE_TYPED(impl_stmt, stmt,
		TYPED(let_stmt, let)) {
	stmt = init_impl_stmt(PSI_T_LET, let);
}
PARSE_TYPED(impl_stmt, stmt,
		TYPED(set_stmt, set)) {
	stmt = init_impl_stmt(PSI_T_SET, set);
}
PARSE_TYPED(impl_stmt, stmt,
		TYPED(return_stmt, ret)) {
	stmt = init_impl_stmt(PSI_T_RETURN, ret);
}
PARSE_TYPED(impl_stmt, stmt,
		TYPED(free_stmt, free)) {
	stmt = init_impl_stmt(PSI_T_FREE, free);
}

PARSE_TYPED(num_exp, exp,
		NAMED(num_exp_token, tok)) {
	exp = init_num_exp(tok->type, tok->text);
	exp->token = tok;
}
PARSE_TYPED(num_exp, exp,
		TYPED(decl_var, var)) {
	exp = init_num_exp(PSI_T_NAME, var);
	exp->token = psi_token_copy(var->token);
}
PARSE_TYPED(num_exp, exp,
		TYPED(num_exp, exp_)
		NAMED(num_exp_op_token, operator_)
		TYPED(num_exp, operand_)) {
	exp_->operator = operator_->type;
	exp_->operand = operand_;
	exp = exp_;
	free(operator_);
}

TOKEN_TYPE(let_exp, let_val*)
TOKEN_DTOR(let_exp, free_let_val($$);)

TOKEN_TYPE(let_callback, let_callback*)
TOKEN_DTOR(let_callback, free_let_callback($$);)

/*
 * let_val: NULL
 */
PARSE_TYPED(let_val, val,
		TOKEN(NULL)) {
	val = init_let_val(PSI_LET_NULL, NULL);
}
/*
 * let_val: &NULL
 */
PARSE_TYPED(let_val, val,
		TOKEN(AMPERSAND)
		TOKEN(NULL)) {
	val = init_let_val(PSI_LET_NULL, NULL);
	val->is_reference = 1;
}
/*
 * let_val: callback
 */
PARSE_TYPED(let_val, val,
		TYPED(let_callback, cb)) {
	val = init_let_val(PSI_LET_CALLBACK, cb);
}
/*
 * let_val: calloc
 */
PARSE_TYPED(let_val, val,
		TYPED(let_calloc, ca)) {
	val = init_let_val(PSI_LET_CALLOC, ca);
}
/*
 * let_val: &calloc
 */
PARSE_TYPED(let_val, val,
		TOKEN(AMPERSAND)
		TYPED(let_calloc, ca)) {
	val = init_let_val(PSI_LET_CALLOC, ca);
	val->is_reference = 1;
}
/*
 * let_val: func
 */
PARSE_TYPED(let_val, val,
		TYPED(let_func, fn)) {
	val = init_let_val_ex(NULL, PSI_LET_FUNC, fn);
}
/*
 * let_val: &func
 */
PARSE_TYPED(let_val, val,
		TOKEN(AMPERSAND)
		TYPED(let_func, fn)) {
	val = init_let_val_ex(NULL, PSI_LET_FUNC, fn);
	val->is_reference = 1;
}
/*
 * let_val: 1234
 */
PARSE_TYPED(let_val, val,
		TYPED(num_exp, exp)) {
	val = init_let_val_ex(NULL, PSI_LET_NUMEXP, exp);
}
/*
 * let_val: &1234
 */
PARSE_TYPED(let_val, val,
		TOKEN(AMPERSAND)
		TYPED(num_exp, exp)) {
	val = init_let_val_ex(NULL, PSI_LET_NUMEXP, exp);
	val->is_reference = 1;
}

/*
 * let_exp: var = val
 */
PARSE_TYPED(let_exp, exp,
		TYPED(decl_var, var_)
		TOKEN(EQUALS)
		TYPED(let_val, val)) {
	exp = val;
	exp->var = var_;
}

/*
 * let_stmt: LET exp ;
 */
PARSE_TYPED(let_stmt, let,
		NAMED(LET, T)
		TYPED(let_exp, val)
		TOKEN(EOS)) {
	let = init_let_stmt(val);
	let->token = T;
}

/*
 * let_stmt: TEMP foo = bar ;
 */
PARSE_TYPED(let_stmt, let,
		NAMED(TEMP, T)
		TYPED(decl_var, var)
		TOKEN(EQUALS)
		TYPED(reference, r)
		TYPED(decl_var, val_)
		TOKEN(EOS)) {
	let = init_let_stmt(init_let_val_ex(var, PSI_LET_TMP, val_));
	let->token = T;
	let->val->is_reference = r ? 1 : 0;
}

/*
 * let_callback: CALLBACK cast($var($args))
 */
PARSE_TYPED(let_callback, cb,
		TOKEN(CALLBACK)
		NAMED(callback_rval, F)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(LPAREN)
		TYPED(callback_arg_list, args_)
		TOKEN(RPAREN)
		TOKEN(RPAREN)) {
	cb = init_let_callback(init_let_func(F->type, F->text, var), args_);
	free(F);
}

/*
 * let_calloc: CALLOC ( num_exp nmemb , num_exp size )
 */
PARSE_TYPED(let_calloc, alloc,
		TOKEN(CALLOC)
		TOKEN(LPAREN)
		TYPED(num_exp, nmemb)
		TOKEN(COMMA)
		TYPED(num_exp, size)
		TOKEN(RPAREN)) {
	alloc = init_let_calloc(nmemb, size);
}

/*
 * let_func: FUNC ( $var )
 */
PARSE_TYPED(let_func, func,
		NAMED(let_func_token, T)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(RPAREN)) {
	func = init_let_func(T->type, T->text, var);
	free(T);
}
/*
 * let_func: FUNC ( $var (,exps)? )
 */
PARSE_TYPED(let_func, func,
		NAMED(let_func_token, T)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(COMMA)
		TYPED(let_vals, vals)
		TOKEN(RPAREN)) {
	func = init_let_func(T->type, T->text, var);
	func->inner = vals;
	free(T);
}
/*
 * let_vals: exps = exp
 */
PARSE_TYPED(let_vals, vals,
		TYPED(let_exp, val)) {
	vals = init_let_vals(val);
}
PARSE_TYPED(let_vals, vals,
		TYPED(let_val, val)) {
	vals = init_let_vals(val);
}
/*
 * let_vals: exps = exps, exp
 */
PARSE_TYPED(let_vals, vals,
		TYPED(let_vals, vals_)
		TOKEN(COMMA)
		TYPED(let_exp, val)) {
	vals = add_let_val(vals_, val);
}
PARSE_TYPED(let_vals, vals,
		TYPED(let_vals, vals_)
		TOKEN(COMMA)
		TYPED(let_val, val)) {
	vals = add_let_val(vals_, val);
}

PASS(callback_arg_list, )
PARSE_TYPED(callback_arg_list, args,
		TYPED(callback_args, args_)) {
	args = args_;
}

PARSE_TYPED(callback_args, args,
		TYPED(set_value, val)) {
	args = init_set_values(val);
}
PARSE_TYPED(callback_args, args,
		TYPED(callback_args, args_)
		TOKEN(COMMA)
		TYPED(set_value, val)) {
	args = add_set_value(args_, val);
}
PARSE_NAMED(callback_rval, rval,
		NAMED(let_func_token, F)) {
	rval = F;
}
PARSE_NAMED(callback_rval, rval,
		NAMED(VOID, V)) {
	rval = V;
}

PARSE_TYPED(set_stmt, set,
		TOKEN(SET)
		TYPED(impl_var, var)
		TOKEN(EQUALS)
		TYPED(set_value, val)
		TOKEN(EOS)) {
	set = init_set_stmt(var, val);
}

PARSE_TYPED(set_value, val,
		TYPED(set_func, func)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(RPAREN)) {
	val = init_set_value(func, init_decl_vars(var));
}
PARSE_TYPED(set_value, val,
		TYPED(set_func, func)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		TYPED(num_exp, num_)
		TOKEN(RPAREN)) {
	val = init_set_value(func, init_decl_vars(var));
	val->num = num_;
}
PARSE_TYPED(set_value, val,
		TYPED(set_func, func_)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		NAMED(ELLIPSIS, T)
		TOKEN(RPAREN)) {
	free_set_func(func_);
	val = init_set_value(init_set_func(T->type, T->text), init_decl_vars(var));
	val->func->token = T;
}
PARSE_TYPED(set_value, val,
		TYPED(set_func, func_)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		TYPED(set_vals, vals)
		TOKEN(RPAREN)) {
	val = vals;
	val->func = func_;
	val->vars = init_decl_vars(var);
}
PARSE_TYPED(set_value, val,
		TYPED(set_func, func_)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		TYPED(num_exp, num_)
		TOKEN(COMMA)
		TYPED(set_vals, vals)
		TOKEN(RPAREN)) {
	val = vals;
	val->func = func_;
	val->num = num_;
	val->vars = init_decl_vars(var);
}

PARSE_TYPED(set_vals, vals,
		TYPED(set_value, val)) {
	vals = add_inner_set_value(init_set_value(NULL, NULL), val);
}
PARSE_TYPED(set_vals, vals,
		TYPED(set_vals, vals_)
		TOKEN(COMMA)
		TYPED(set_value, val)) {
	vals = add_inner_set_value(vals_, val);
}

PARSE_TYPED(set_func, func,
		NAMED(set_func_token, T)) {
	func = init_set_func(T->type, T->text);
	func->token = T;
}

PARSE_TYPED(return_stmt, ret,
		NAMED(RETURN, T)
		TYPED(set_value, val)
		TOKEN(EOS)) {
	ret = init_return_stmt(val);
	ret->token = T;
}

PARSE_TYPED(free_stmt, free,
		TOKEN(FREE)
		TYPED(free_calls, calls)
		TOKEN(EOS)) {
	free = init_free_stmt(calls);
}

PARSE_TYPED(free_calls, calls,
		TYPED(free_call, call)) {
	calls = init_free_calls(call);
}
PARSE_TYPED(free_calls, calls,
		TYPED(free_calls, calls_)
		TOKEN(COMMA)
		TYPED(free_call, call)) {
	calls = add_free_call(calls_, call);
}

PARSE_TYPED(free_call, call,
		NAMED(NAME, F)
		TOKEN(LPAREN)
		TYPED(decl_vars, vars)
		TOKEN(RPAREN)) {
	call = init_free_call(F->text, vars);
	call->token = F;
}

PARSE_TYPED(impl_type, type_,
		NAMED(impl_type_token, T)) {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}

PARSE_TYPED(reference, r, ) {
	r = 0;
}
PARSE_TYPED(reference, r,
		TOKEN(AMPERSAND)) {
	r = 1;
}

PARSE_TYPED(indirection, i, ){
	i = 0;
}
PARSE_TYPED(indirection, i,
		TYPED(pointers, p)) {
	i = p;
}

PARSE_TYPED(pointers, p,
		TOKEN(ASTERISK)) {
	p = 1;
}
PARSE_TYPED(pointers, p,
		TYPED(pointers, p_)
		TOKEN(ASTERISK)) {
	p = p_+1;
}
