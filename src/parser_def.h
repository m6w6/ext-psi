/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#define CONCAT2(x,y) x##y
#define CONCAT1(x,y) CONCAT2(x,y)
#define COUNTED(x) CONCAT1(parse_ ##x## _, __LINE__)

#define TOKEN_PREFIX PSI_T
#define TOKEN_STRUCT struct psi_token *

#ifdef GENERATE
# define DEF(dn, dv) dn dv
# define PASS(nt, rule) nt ::= rule.
# define PARSE(nt, rule) nt ::= rule.
# define PARSE_NAMED(nt, nt_name, rule) NAMED(nt, nt_name) ::= rule.
# define PARSE_TYPED(nt, nt_name, rule) TYPED(nt, nt_name) ::= rule.
# define TOKEN(t) t
# define NAMED(t, name) t(name)
# define TYPED(t, name) t(name)
# define TOKEN_TYPE(token, type_) %type token {type_}
# define TOKEN_DTOR(token, dtor) %destructor token {dtor}
# define T(token) token
# define TOKEN_CLASS(type, tokens) DEF(%token_class, type##_token tokens .)
#else
# ifndef TEST
#  include "parser.h"
#  include "plist.h"
# endif
# define DEF(dn, dv)
# define PASS(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P) { \
		(void) #rule; \
	}
# define PARSE(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P rule)
# define PARSE_NAMED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P NAMED(nt, nt_name) rule)
# define PARSE_TYPED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P TYPED(nt, nt_name) rule)
# define TOKEN(t)
# define NAMED(t, name) , struct psi_token *name
# define TYPED(t, name) , TOKEN_TYPE_NAME(t) name
# define TOKEN_TYPE_NAME(token) token##_parse_t
# define TOKEN_TYPE(token, type) typedef type TOKEN_TYPE_NAME(token);
# define TOKEN_DTOR(token, dtor)
# define T(token) CONCAT1(TOKEN_PREFIX, _ ##token ),
# define TOKEN_CLASS(type, tokens) static token_t type##_token[] = { tokens 0 };
#endif

DEF(%token_prefix, CONCAT1(TOKEN_PREFIX,_))
DEF(%token_type, {TOKEN_STRUCT})
DEF(%token_destructor, {free($$);})
DEF(%default_destructor, {(void)P;})
DEF(%extra_argument, {struct psi_parser *P})

/* TOKEN is defined inside syntax_error */
DEF(%syntax_error, {
	++P->errors;
	if (TOKEN && TOKEN->type != PSI_T_EOF) {
		psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col);
	} else {
		psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input");
	}
})

TOKEN_CLASS(const_type, T(BOOL) T(INT) T(FLOAT) T(STRING))
TOKEN_CLASS(decl_type, T(FLOAT) T(DOUBLE) T(INT8) T(UINT8) T(INT16) T(UINT16) T(INT32) T(UINT32) T(INT64) T(UINT64) T(NAME))
TOKEN_CLASS(impl_def_val, T(NULL) T(NUMBER) T(TRUE) T(FALSE) T(QUOTED_STRING))
TOKEN_CLASS(number, T(NUMBER) T(NSNAME))
TOKEN_CLASS(binary_op, T(PIPE) T(CARET) T(AMPERSAND) T(LSHIFT) T(RSHIFT) T(PLUS) T(MINUS) T(ASTERISK) T(SLASH) T(MODULO) T(RCHEVR) T(LCHEVR) T(CMP_GE) T(CMP_LE) T(OR) T(AND) T(CMP_EQ) T(CMP_NE))
TOKEN_CLASS(unary_op, T(TILDE) T(NOT) T(PLUS) T(MINUS))
TOKEN_CLASS(let_func, T(ZVAL) T(OBJVAL) T(ARRVAL) T(PATHVAL) T(STRLEN) T(STRVAL) T(FLOATVAL) T(INTVAL) T(BOOLVAL) T(COUNT))
TOKEN_CLASS(set_func, T(TO_OBJECT) T(TO_ARRAY) T(TO_STRING) T(TO_INT) T(TO_FLOAT) T(TO_BOOL) T(ZVAL) T(VOID))
TOKEN_CLASS(impl_type, T(VOID) T(MIXED) T(BOOL) T(INT) T(FLOAT) T(STRING) T(ARRAY) T(OBJECT) T(CALLABLE))

DEF(%nonassoc, NAME.)
DEF(%right, NOT TILDE.)
DEF(%left, AND OR.)
DEF(%left, PIPE.)
DEF(%left, CARET.)
DEF(%left, AMPERSAND.)
DEF(%left, CMP_EQ CMP_NE.)
DEF(%left, LCHEVR CMP_LE RCHEVR CMP_GE.)
DEF(%left, LSHIFT RSHIFT.)
DEF(%left, PLUS MINUS.)
DEF(%left, ASTERISK SLASH MODULO.)

DEF(%fallback, NAME TEMP FREE SET LET RETURN CALLOC CALLBACK ZVAL LIB STRING COUNT.)

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
TOKEN_TYPE(reference, bool)
TOKEN_TYPE(indirection, unsigned)
TOKEN_TYPE(pointers, unsigned)

PASS(file, blocks)
PASS(blocks, block)
PASS(blocks, blocks block)

PASS(block, EOF)
PASS(block, EOS)

/*
 * lib: LIB "soname" ;
 */
PARSE(block, NAMED(LIB, token) NAMED(QUOTED_STRING, libname) TOKEN(EOS)) {
	if (P->file.ln) {
		P->error(PSI_DATA(P), token, PSI_WARNING, "Extra 'lib %s' statement has no effect", libname->text);
	} else {
		P->file.ln = strndup(libname->text + 1, libname->size - 2);
	}
	free(libname);
	free(token);
}

PARSE(block, TYPED(decl, decl)) {
	if (!P->decls) {
		P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
	}
	P->decls = psi_plist_add(P->decls, &decl);
}

PARSE(block, TYPED(impl, impl)) {
	if (!P->impls) {
		P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	P->impls = psi_plist_add(P->impls, &impl);
}

PARSE(block, TYPED(decl_typedef, def)) {
	if (!P->types) {
		P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	P->types = psi_plist_add(P->types, &def);

	switch (def->type->type) {
	case PSI_T_STRUCT:
		if (def->type->real.strct) {
			if (!P->structs) {
				P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
			}
			P->structs = psi_plist_add(P->structs, &def->type->real.strct);
		}
		break;
	case PSI_T_UNION:
		if (def->type->real.unn) {
			if (!P->unions) {
				P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
			}
			P->unions = psi_plist_add(P->unions, &def->type->real.unn);
		}
		break;
	case PSI_T_ENUM:
		if (def->type->real.enm) {
			if (!P->enums) {
				P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
			}
			P->enums = psi_plist_add(P->enums, &def->type->real.enm);
		}
		break;
	}
}

PARSE(block, TYPED(constant, constant)) {
	if (!P->consts) {
		P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
	}
	P->consts = psi_plist_add(P->consts, &constant);
}

PARSE(block, TYPED(decl_struct, strct)) {
	if (!P->structs) {
		P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
	}
	P->structs = psi_plist_add(P->structs, &strct);
}

PARSE(block, TYPED(decl_union, u)) {
	if (!P->unions) {
		P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
	}
	P->unions = psi_plist_add(P->unions, &u);
}

PARSE(block, TYPED(decl_enum, e)) {
	if (!P->enums) {
		P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
	}
	P->enums = psi_plist_add(P->enums, &e);
}

/*
 * optional_name: <empty>
 */
PARSE_NAMED(optional_name, n, ) {
	n = NULL;
}

/*
 * optional_name: NAME
 */
PARSE_NAMED(optional_name, n,
		NAMED(NAME, N)) {
	n = N;
}

/*
 * align_and_size: <empty>
 */
PARSE_TYPED(align_and_size, as, ) {
	as.pos = 0;
	as.len = 0;
}

/*
 * align_and_size: :: ( NUMBER , NUMBER )
 */
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

/*
 * enum_name: ENUM optional_name
 */
PARSE_NAMED(enum_name, n,
		NAMED(ENUM, E)
		NAMED(optional_name, N)) {
	if (N) {
		n = N;
		free(E);
	} else {
		char digest[17];

		psi_token_hash(E, digest);
		n = psi_token_translit(psi_token_append(E, 1, digest), " ", "@");
	}
}

/*
 * struct_name: STRUCT optional_name
 */
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

/*
 * union_name: UNION optional_name
 */
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

/*
 * decl_enum: enum_name { items }
 */
PARSE_TYPED(decl_enum, e,
		NAMED(enum_name, N)
		TOKEN(LBRACE)
		TYPED(decl_enum_items, list)
		TOKEN(RBRACE)) {
	e = psi_decl_enum_init(N->text, list);
	e->token = N;
}

/*
 * decl_enum_items: item
 */
PARSE_TYPED(decl_enum_items, l,
		TYPED(decl_enum_item, i)) {
	l = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
			&i);
}

/*
 * decl_enum_items: items , item
 */
PARSE_TYPED(decl_enum_items, l,
		TYPED(decl_enum_items, l_)
		TOKEN(COMMA)
		TYPED(decl_enum_item, i)) {
	l = psi_plist_add(l_, &i);
}

/*
 * decl_enum_item: name = num_exp
 */
PARSE_TYPED(decl_enum_item, i,
		NAMED(NAME, N)
		TOKEN(EQUALS)
		TYPED(num_exp, num)) {
	i = psi_decl_enum_item_init(N->text, num);
	i->token = N;
}

/*
 * decl_enum_item: name
 */
PARSE_TYPED(decl_enum_item, i,
		NAMED(NAME, N)) {
	i = psi_decl_enum_item_init(N->text, NULL);
	i->token = N;
}


/*
 * decl_struct_args_block: { args }
 */
PARSE_TYPED(decl_struct_args_block, args_,
		TOKEN(LBRACE)
		TYPED(struct_args, args)
		TOKEN(RBRACE)) {
	args_ = args;
}

/*
 * decl_struct_args: args_block
 */
PARSE_TYPED(decl_struct_args, args_,
		TYPED(decl_struct_args_block, args)) {
	args_ = args;
}

/*
 * decl_struct_args: ;
 */
PARSE_TYPED(decl_struct_args, args_,
		TOKEN(EOS)) {
	args_ = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}

/*
 * decl_struct: STRUCT name align_and_size struct_args
 */
PARSE_TYPED(decl_struct, strct,
		TOKEN(STRUCT)
		NAMED(NAME, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args, args)) {
	strct = psi_decl_struct_init(N->text, args);
	strct->align = as.pos;
	strct->size = as.len;
	strct->token = N;
}

/*
 * decl_union: UNION name align_and_size struct_args
 */
PARSE_TYPED(decl_union, u,
		TOKEN(UNION)
		NAMED(NAME, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args, args)) {
	u = psi_decl_union_init(N->text, args);
	u->align = as.pos;
	u->size = as.len;
	u->token = N;
}

/*
 * const_type: const_type_token
 */
PARSE_TYPED(const_type, type_,
		NAMED(const_type_token, T)) {
	type_ = psi_const_type_init(T->type, T->text);
	free(T);
}

/*
 * constant: CONST const_type NSNAME = def_val ;
 */
PARSE_TYPED(constant, constant,
		TOKEN(CONST)
		TYPED(const_type, type)
		NAMED(NSNAME, T)
		TOKEN(EQUALS)
		TYPED(impl_def_val, val)
		TOKEN(EOS)) {
	constant = psi_const_init(type, T->text, val);
	constant->token = T;
}

/*
 * decl_typdef: TYPEDEF typedef_body ;
 */
PARSE_TYPED(decl_typedef, def,
		NAMED(TYPEDEF, T)
		TYPED(decl_typedef_body, def_)
		TOKEN(EOS)) {
	def = def_;
	def->token = T;
}

/*
 * decl_typedef_body_ex: struct_name align_and_size struct_args_block decl_var
 */
PARSE_TYPED(decl_typedef_body_ex, def,
		NAMED(struct_name, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args_block, args)
		TYPED(decl_var, var)) {
	def = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, N->text), var);
	def->type->token = psi_token_copy(N);
	def->type->real.strct = psi_decl_struct_init(N->text, args);
	def->type->real.strct->token = N;
	def->type->real.strct->align = as.pos;
	def->type->real.strct->size = as.len;
}

/*
 * decl_typedef_body_ex: union_name align_and_size struct_args_block decl_var
 */
PARSE_TYPED(decl_typedef_body_ex, def,
		NAMED(union_name, N)
		TYPED(align_and_size, as)
		TYPED(decl_struct_args_block, args)
		TYPED(decl_var, var)) {
	def = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, N->text), var);
	def->type->token = psi_token_copy(N);
	def->type->real.unn = psi_decl_union_init(N->text, args);
	def->type->real.unn->token = N;
	def->type->real.unn->align = as.pos;
	def->type->real.unn->size = as.len;
}

/*
 * decl_typedef_body_ex: decl_enum NAME
 */
PARSE_TYPED(decl_typedef_body_ex, def,
		TYPED(decl_enum, e)
		NAMED(NAME, ALIAS)) {
	def = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, e->name), psi_decl_var_init(ALIAS->text, 0, 0));
	def->var->token = ALIAS;
	def->type->token = psi_token_copy(e->token);
	def->type->real.enm = e;
}

/*
 * decl_typedef_body: decl_typedef_body_ex
 */
PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_typedef_body_ex, def_)) {
	def = def_;
}

/*
 * decl_typedef_body_fn_args: ( decl_args )
 */
PARSE_TYPED(decl_typedef_body_fn_args, args,
		TOKEN(LPAREN)
		TYPED(decl_args, args_)
		TOKEN(RPAREN)) {
	args = args_;
}

/*
 * decl_typedef_body: decl_func decl_typedef_body_fn_args
 */
PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_func, func_)
		TYPED(decl_typedef_body_fn_args, args)) {
	def = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, func_->var->name), psi_decl_var_copy(func_->var));
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, args);
}

/*
 * decl_typedef_body: decl_arg
 */
PARSE_TYPED(decl_typedef_body, def,
		TYPED(decl_arg, arg)) {
	def = arg;
}

/*
 * decl: decl_abi decl_func ( decl_args ) ;
 */
PARSE_TYPED(decl, decl,
		TYPED(decl_abi, abi)
		TYPED(decl_func, func)
		TOKEN(LPAREN)
		TYPED(decl_args, args)
		TOKEN(RPAREN)
		TOKEN(EOS)) {
	decl = psi_decl_init(abi, func, args);
}

/*
 * decl: decl_abi decl_func ( decl_args , ... ) ;
 */
PARSE_TYPED(decl, decl,
		TYPED(decl_abi, abi)
		TYPED(decl_func, func)
		TOKEN(LPAREN)
		TYPED(decl_args, args)
		TOKEN(COMMA)
		TOKEN(ELLIPSIS)
		TOKEN(RPAREN)
		TOKEN(EOS)) {
	decl = psi_decl_init(abi, func, args);
	decl->varargs = 1;
}

/*
 * decl_func: decl_arg
 */
PARSE_TYPED(decl_func, func,
		TYPED(decl_arg, arg)) {
	func = arg;
}

/* special case for void functions */
/*
 * decl_func: VOID NAME
 */
PARSE_TYPED(decl_func, func,
		NAMED(VOID, T)
		NAMED(NAME, N)) {
	func = psi_decl_arg_init(
		psi_decl_type_init(T->type, T->text),
		psi_decl_var_init(N->text, 0, 0)
	);
	func->type->token = T;
	func->var->token = N;
	func->token = N;
}

/*
 * decl_typedef_body: VOID indirection ( indirection NAME ) decl_typedef_body_fn_args
 */
PARSE_TYPED(decl_typedef_body, def,
		NAMED(VOID, T)
		TYPED(indirection, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	struct psi_decl_arg *func_ = psi_decl_arg_init(
		psi_decl_type_init(T->type, T->text),
		psi_decl_var_init(N->text, decl_i, 0)
	);
	func_->type->token = T;
	func_->var->token = N;
	func_->token = N;

	def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
		psi_decl_var_copy(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, args);
}

/*
 * decl_typedef_body: CONST VOID pointers ( indirection NAME ) decl_typdef_body_fn_args
 */
PARSE_TYPED(decl_typedef_body, def,
		TOKEN(CONST)
		NAMED(VOID, T)
		TYPED(pointers, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	struct psi_decl_arg *func_ = psi_decl_arg_init(
		psi_decl_type_init(T->type, T->text),
		psi_decl_var_init(N->text, decl_i, 0)
	);
	func_->type->token = T;
	func_->var->token = N;
	func_->token = N;

	def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
		psi_decl_var_copy(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, args);
}

/*
 * decl_abi: NAME
 */
PARSE_TYPED(decl_abi, abi,
		NAMED(NAME, T)) {
	abi = psi_decl_abi_init(T->text);
	abi->token = T;
}

/*
 * decl_var_array_size: <empty>
 */
PARSE_NAMED(decl_var_array_size, as, ) {
	as = NULL;
}

/*
 * decl_var_array_size: [ NUMBER ]
 */
PARSE_NAMED(decl_var_array_size, as,
		TOKEN(LBRACKET)
		NAMED(NUMBER, D)
		TOKEN(RBRACKET)) {
	as = D;
}

/*
 * decl_var: NAME decl_var_array_size
 */
PARSE_TYPED(decl_var, var,
		NAMED(NAME, T)
		NAMED(decl_var_array_size, as)) {
	var = psi_decl_var_init(T->text, 0, as?atol(as->text):0);
	var->token = T;
	if (as) {
		free(as);
	}
}

/*
 * decl_var: pointers NAME
 */
PARSE_TYPED(decl_var, var,
		TYPED(pointers, p)
		NAMED(NAME, T)
		NAMED(decl_var_array_size, as)) {
	var = psi_decl_var_init(T->text, p+!!as, as?atol(as->text):0);
	var->token = T;
	if (as) {
		free(as);
	}
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

/*
 * decl_arg: const_decl_type decl_var
 */
PARSE_TYPED(decl_arg, arg_,
		TYPED(const_decl_type, type)
		TYPED(decl_var, var)) {
	arg_ = psi_decl_arg_init(type, var);
}

/*
 * decl_typedef_body: const_decl_type indirection ( indirection NAME ) decl_typedef_body_fn_args
 */
PARSE_TYPED(decl_typedef_body, def,
		TYPED(const_decl_type, type_)
		TYPED(indirection, decl_i)
		TOKEN(LPAREN)
		TYPED(indirection, type_i)
		NAMED(NAME, N)
		TOKEN(RPAREN)
		TYPED(decl_typedef_body_fn_args, args)) {
	struct psi_decl_arg *func_ = psi_decl_arg_init(
		type_,
		psi_decl_var_init(N->text, decl_i, 0)
	);
	func_->var->token = N;
	func_->token = N;

	def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
		psi_decl_var_copy(func_->var)
	);
	def->var->pointer_level = type_i;
	def->type->token = psi_token_copy(func_->token);
	def->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, args);
}

/* void pointers need a specific rule */
/*
 * decl_arg: VOID pointers NAME
 */
PARSE_TYPED(decl_arg, arg_,
		NAMED(VOID, T)
		TYPED(pointers, p)
		NAMED(NAME, N)) {
	arg_ = psi_decl_arg_init(
		psi_decl_type_init(T->type, T->text),
		psi_decl_var_init(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}

/*
 * decl_args: CONST VOID pointers NAME
 */
PARSE_TYPED(decl_arg, arg_,
		TOKEN(CONST)
		NAMED(VOID, T)
		TYPED(pointers, p)
		NAMED(NAME, N)) {
	arg_ = psi_decl_arg_init(
		psi_decl_type_init(T->type, T->text),
		psi_decl_var_init(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}

/*
 * decl_args: <empty>
 */
PARSE_TYPED(decl_args, args, ) {
	args = NULL;
}

/*
 * decl_args: VOID
 */
PARSE_TYPED(decl_args, args,
		TOKEN(VOID)) {
	args = NULL;
}

/*
 * decl_args: decl_arg
 */
PARSE_TYPED(decl_args, args,
		TYPED(decl_arg, arg)) {
	args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
			&arg);
}

/*
 * decl_args: decl_args , decl_arg
 */
PARSE_TYPED(decl_args, args,
		TYPED(decl_args, args_)
		TOKEN(COMMA)
		TYPED(decl_arg, arg)) {
	args = psi_plist_add(args_, &arg);
}

/*
 * struct_args: struct_arg
 */
PARSE_TYPED(struct_args, args,
		TYPED(struct_arg, arg)) {
	args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
			&arg);
}

/*
 * struct_args: struct_args , struct_arg
 */
PARSE_TYPED(struct_args, args,
		TYPED(struct_args, args_)
		TYPED(struct_arg, arg)) {
	args = psi_plist_add(args_, &arg);
}

/*
 * struct_arg: decl_typedef_body_ex ;
 */
PARSE_TYPED(struct_arg, arg_,
		TYPED(decl_typedef_body_ex, def)
		TOKEN(EOS)) {
	arg_ = def;
	switch (def->type->type) {
	case PSI_T_STRUCT:
		if (def->type->real.strct) {
			if (!P->structs) {
				P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
			}
			P->structs = psi_plist_add(P->structs, &def->type->real.strct);
		}
		break;
	case PSI_T_UNION:
		if (def->type->real.unn) {
			if (!P->unions) {
				P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
			}
			P->unions = psi_plist_add(P->unions, &def->type->real.unn);
		}
		break;
	case PSI_T_ENUM:
		if (def->type->real.enm) {
			if (!P->enums) {
				P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
			}
			P->enums = psi_plist_add(P->enums, &def->type->real.enm);
		}
		break;
	}
}

/*
 * struct_arg: decl_arg decl_layout ;
 */
PARSE_TYPED(struct_arg, arg,
		TYPED(decl_arg, arg_)
		TYPED(decl_layout, layout_)
		TOKEN(EOS)) {
	arg_->layout = layout_;
	arg = arg_;
}

/*
 * decl_layout: <empty>
 */
PARSE_TYPED(decl_layout, layout, ) {
	layout = NULL;
}

/*
 * decl_layout: :: ( NUMBER , NUMBER )
 */
PARSE_TYPED(decl_layout, layout,
		TOKEN(COLON)
		TOKEN(COLON)
		TOKEN(LPAREN)
		NAMED(NUMBER, POS)
		TOKEN(COMMA)
		NAMED(NUMBER, SIZ)
		TOKEN(RPAREN)) {
	layout = psi_layout_init(atol(POS->text), atol(SIZ->text));
	free(POS);
	free(SIZ);
}

/* un/signed, urgh */
/*
 * decl_scalar_type: CHAR
 */
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(CHAR, C)) {
	type_ = C;
}

/*
 * decl_scalar_type: SHORT decl_scalar_type_short
 */
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

/*
 * decl_scalar_type_short: <empty>
 */
PARSE_NAMED(decl_scalar_type_short, s, ) {
	s = NULL;
}

/*
 * decl_scalar_type_short: INT
 */
PARSE_NAMED(decl_scalar_type_short, s,
		NAMED(INT, I)) {
	s = I;
}

/*
 * decl_sclara_type: INT
 */
PARSE_NAMED(decl_scalar_type, type_,
		NAMED(INT, I)) {
	type_ = I;
}

/*
 * decl_scalar_type: LONG decl_scalar_type_long
 */
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

/*
 * decl_scalar_type_long: <empty>
 */
PARSE_NAMED(decl_scalar_type_long, l, ) {
	l = NULL;
}

/*
 * decl_scalar_type_long: DOUBLE
 */
PARSE_NAMED(decl_scalar_type_long, l,
		NAMED(DOUBLE, D)) {
	l = D;
}

/*
 * decl_scalar_type_long: LONG decl_scalar_type_long_long
 */
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

/*
 * decl_scalar_type_long_long: <empty>
 */
PARSE_NAMED(decl_scalar_type_long_long, ll, ) {
	ll = NULL;
}

/*
 * decl_scalar_type_long_long: INT
 */
PARSE_NAMED(decl_scalar_type_long_long, ll,
		NAMED(INT, I)) {
	ll = I;
}

/*
 * decl_type: UNSIGNED decl_scalar_type
 */
PARSE_TYPED(decl_type, type_,
		NAMED(UNSIGNED, U)
		NAMED(decl_scalar_type, N)) {
	struct psi_token *T = psi_token_cat(2, U, N);
	type_ = psi_decl_type_init(T->type, T->text);
	type_->token = T;
	free(U);
	free(N);
}

/*
 * decl_type: SIGNED decl_scalar_type
 */
PARSE_TYPED(decl_type, type_,
		NAMED(SIGNED, S)
		NAMED(decl_scalar_type, N)) {
	struct psi_token *T = psi_token_cat(2, S, N);
	type_ = psi_decl_type_init(T->type, T->text);
	type_->token = T;
	free(S);
	free(N);
}

/*
 * decl_type: UNSIGNED
 */
PARSE_TYPED(decl_type, type_,
		NAMED(UNSIGNED, U)) {
	type_ = psi_decl_type_init(PSI_T_NAME, U->text);
	type_->token = U;
}

/*
 * decl_type: SIGNED
 */
PARSE_TYPED(decl_type, type_,
		NAMED(SIGNED, S)) {
	type_ = psi_decl_type_init(PSI_T_NAME, S->text);
	type_->token = S;
}

/*
 * decl_type: decl_scalar_type
 */
PARSE_TYPED(decl_type, type_,
		NAMED(decl_scalar_type, N)) {
	type_ = psi_decl_type_init(N->type, N->text);
	type_->token = N;
}

/* structs ! */
/*
 * decl_type: STRUCT NAME
 */
PARSE_TYPED(decl_type, type_,
		NAMED(STRUCT, S)
		NAMED(NAME, T)) {
	type_ = psi_decl_type_init(S->type, T->text);
	type_->token = T;
	free(S);
}

/*
 * decl_type: UNION NAME
 */
PARSE_TYPED(decl_type, type_,
		NAMED(UNION, U)
		NAMED(NAME, T)) {
	type_ = psi_decl_type_init(U->type, T->text);
	type_->token = T;
	free(U);
}

/*
 * decl_type: ENUM NAME
 */
PARSE_TYPED(decl_type, type_,
		NAMED(ENUM, E)
		NAMED(NAME, T)) {
	type_ = psi_decl_type_init(E->type, T->text);
	type_->token = T;
	free(E);
}

/*
 * decl_type: decl_type_token
 */
PARSE_TYPED(decl_type, type_,
		NAMED(decl_type_token, T)) {
	type_ = psi_decl_type_init(T->type, T->text);
	type_->token = T;
}

/*
 * const_decl_type: decl_type
 */
PARSE_TYPED(const_decl_type, type,
		TYPED(decl_type, type_)) {
	type = type_;
}

/*
 * const_decl_type: CONST decl_type
 */
PARSE_TYPED(const_decl_type, type,
		TOKEN(CONST)
		TYPED(decl_type, type_)) {
	type = type_;
}

/*
 * impl: impl_func { impl_stmts }
 */
PARSE_TYPED(impl, impl,
		TYPED(impl_func, func)
		TOKEN(LBRACE)
		TYPED(impl_stmts, stmts)
		TOKEN(RBRACE)) {
	impl = psi_impl_init(func, stmts);
}

/*
 * impl: STATIC impl_func { impl_stmts }
 */
PARSE_TYPED(impl, impl,
		TOKEN(STATIC)
		TYPED(impl_func, func)
		TOKEN(LBRACE)
		TYPED(impl_stmts, stmts)
		TOKEN(RBRACE)) {
	func->static_memory = 1;
	impl = psi_impl_init(func, stmts);
}

/*
 * impl_func: FUNCTION reference NSNAME ( ) : impl_type
 */
PARSE_TYPED(impl_func, func,
		TOKEN(FUNCTION)
		TYPED(reference, r)
		NAMED(NSNAME, NAME)
		TOKEN(LPAREN)
		TOKEN(RPAREN)
		TOKEN(COLON)
		TYPED(impl_type, type)) {
	func = psi_impl_func_init(NAME->text, NULL, type);
	func->token = NAME;
	func->return_reference = r;
}

/*
 * impl_func: FUNCTION reference NSNAME ( impl_args ) : impl_type
 */
PARSE_TYPED(impl_func, func,
		TOKEN(FUNCTION)
		TYPED(reference, r)
		NAMED(NSNAME, NAME)
		TOKEN(LPAREN)
		TYPED(impl_args, args)
		TOKEN(RPAREN)
		TOKEN(COLON)
		TYPED(impl_type, type)) {
	func = psi_impl_func_init(NAME->text, args, type);
	func->token = NAME;
	func->return_reference = r;
}

/*
 * impl_func: FUNCTION reference NSNAME ( impl_args , impl_type reference ... DOLLAR_NAME ) : impl_type
 */
PARSE_TYPED(impl_func, func,
		TOKEN(FUNCTION)
		TYPED(reference, func_r)
		NAMED(NSNAME, NAME)
		TOKEN(LPAREN)
		TYPED(impl_args, args)
		TOKEN(COMMA)
		TYPED(impl_type, va_type)
		TYPED(reference, va_r)
		TOKEN(ELLIPSIS)
		NAMED(DOLLAR_NAME, T)
		TOKEN(RPAREN)
		TOKEN(COLON)
		TYPED(impl_type, func_type)) {
	func = psi_impl_func_init(NAME->text, args, func_type);
	func->token = NAME;
	func->return_reference = func_r;
	func->vararg = psi_impl_arg_init(va_type, psi_impl_var_init(T->text, va_r), NULL);
	free(T);
}

/*
 * impl_def_val: impl_def_val_token
 */
PARSE_TYPED(impl_def_val, def,
		NAMED(impl_def_val_token, T)) {
	def = psi_impl_def_val_init(T->type, T->text);
	def->token = T;
}

/*
 * impl_var: reference DOLLAR_NAME
 */
PARSE_TYPED(impl_var, var,
		TYPED(reference, r)
		NAMED(DOLLAR_NAME, T)) {
	var = psi_impl_var_init(T->text, r);
	var->token = T;
}

/*
 * impl_type: impl_type_token
 */
PARSE_TYPED(impl_type, type_,
		NAMED(impl_type_token, T)) {
	type_ = psi_impl_type_init(T->type, T->text);
	free(T);
}

/*
 * impl_arg: impl_type impl_var
 */
PARSE_TYPED(impl_arg, arg,
		TYPED(impl_type, type)
		TYPED(impl_var, var)) {
	arg = psi_impl_arg_init(type, var, NULL);
}

/*
 * impl_arg: impl_type impl_var = impl_def_val
 */
PARSE_TYPED(impl_arg, arg,
		TYPED(impl_type, type)
		TYPED(impl_var, var)
		TOKEN(EQUALS)
		TYPED(impl_def_val, def)) {
	arg = psi_impl_arg_init(type, var, def);
}

/*
 * impl_args: impl_arg
 */
PARSE_TYPED(impl_args, args,
		TYPED(impl_arg, arg)) {
	args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
			&arg);
}

/*
 * impl_args: impl_args , impl_arg
 */
PARSE_TYPED(impl_args, args,
		TYPED(impl_args, args_)
		TOKEN(COMMA)
		TYPED(impl_arg, arg)) {
	args = psi_plist_add(args_, &arg);
}

/*
 * impl_stmts: impl_stmt
 */
PARSE_TYPED(impl_stmts, stmts,
		TYPED(impl_stmt, stmt)) {
	stmts = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
			&stmt);
}

/*
 * impl_stmts: impl_stmts , impl_stmt
 */
PARSE_TYPED(impl_stmts, stmts,
		TYPED(impl_stmts, stmts_)
		TYPED(impl_stmt, stmt)) {
	stmts = psi_plist_add(stmts_, &stmt);
}

/*
 * impl_stmt: return_stmt
 */
PARSE_TYPED(impl_stmt, i,
		TYPED(return_stmt, r)) {
	i = (struct psi_token**) r;
}

/*
 * impl_stmt: let_stmt
 */
PARSE_TYPED(impl_stmt, i,
		TYPED(let_stmt, l)) {
	i = (struct psi_token**) l;
}

/*
 * impl_stmt: set_stmt
 */
PARSE_TYPED(impl_stmt, i,
		TYPED(set_stmt, s)) {
	i = (struct psi_token**) s;
}

/*
 * impl_stmt: free_stmt
 */
PARSE_TYPED(impl_stmt, i,
		TYPED(free_stmt, f)) {
	i = (struct psi_token**) f;
}

/*
 * number: number_token
 */
PARSE_TYPED(number, exp,
		NAMED(number_token, tok)) {
	exp = psi_number_init(tok->type, tok->text);
	exp->token = tok;
}

/*
 * number: decl_var
 */
PARSE_TYPED(number, exp,
		TYPED(decl_var, var)) {
	exp = psi_number_init(PSI_T_NAME, var);
	exp->token = psi_token_copy(var->token);
}

/*
 * num_exp: number
 */
PARSE_TYPED(num_exp, exp,
		TYPED(number, num)) {
	exp = psi_num_exp_init_num(num);
	exp->token = psi_token_copy(num->token);
}

/*
 * num_exp: ( num_exp )
 */
PARSE_TYPED(num_exp, exp,
		NAMED(LPAREN, L)
		TYPED(num_exp, exp_)
		TOKEN(RPAREN)) {
	exp = psi_num_exp_init_unary(PSI_T_LPAREN, exp_);
	exp->token = L;
}

/*
 * num_exp: num_exp binary_op_token num_exp
 */
PARSE_TYPED(num_exp, exp,
		TYPED(num_exp, lhs_)
		NAMED(binary_op_token, OP)
		TYPED(num_exp, rhs_)) {
	exp = psi_num_exp_init_binary(OP->type, lhs_, rhs_);
	exp->token = OP;
}

/*
 * num_exp: unary_op_token num_exp
 */
PARSE_TYPED(num_exp, exp,
		NAMED(unary_op_token, OP)
		TYPED(num_exp, exp_)) {
	exp = psi_num_exp_init_unary(OP->type, exp_);
	exp->token = OP;
}

/*
 * let_exp: NULL
 */
PARSE_TYPED(let_exp, val,
		TOKEN(NULL)) {
	val = psi_let_exp_init(PSI_LET_NULL, NULL);
}

/*
 * let_exp: & NULL
 */
PARSE_TYPED(let_exp, val,
		TOKEN(AMPERSAND)
		TOKEN(NULL)) {
	val = psi_let_exp_init(PSI_LET_NULL, NULL);
	val->is_reference = 1;
}

/*
 * let_exp: callback
 */
PARSE_TYPED(let_exp, val,
		TYPED(let_callback, cb)) {
	val = psi_let_exp_init(PSI_LET_CALLBACK, cb);
}

/*
 * let_exp: calloc
 */
PARSE_TYPED(let_exp, val,
		TYPED(let_calloc, ca)) {
	val = psi_let_exp_init(PSI_LET_CALLOC, ca);
}

/*
 * let_exp: & calloc
 */
PARSE_TYPED(let_exp, val,
		TOKEN(AMPERSAND)
		TYPED(let_calloc, ca)) {
	val = psi_let_exp_init(PSI_LET_CALLOC, ca);
	val->is_reference = 1;
}

/*
 * let_exp: func
 */
PARSE_TYPED(let_exp, val,
		TYPED(let_func, fn)) {
	val = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, fn);
}

/*
 * let_exp: & func
 */
PARSE_TYPED(let_exp, val,
		TOKEN(AMPERSAND)
		TYPED(let_func, fn)) {
	val = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, fn);
	val->is_reference = 1;
}

/*
 * let_exp: num_exp
 */
PARSE_TYPED(let_exp, val,
		TYPED(num_exp, exp)) {
	val = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, exp);
}

/*
 * let_exp: & num_exp
 */
PARSE_TYPED(let_exp, val,
		TOKEN(AMPERSAND)
		TYPED(num_exp, exp)) {
	val = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, exp);
	val->is_reference = 1;
}

/* FIXME
 * let_exp: decl_var = let_exp
 */
PARSE_TYPED(let_exp, exp,
		TYPED(decl_var, var_)
		TOKEN(EQUALS)
		TYPED(let_exp, val)) {
	exp = val;
	exp->var = var_;
}

/*
 * let_stmt: LET let_exp ;
 */
PARSE_TYPED(let_stmt, let,
		NAMED(LET, T)
		TYPED(let_exp, val)
		TOKEN(EOS)) {
	let = psi_let_stmt_init(val);
	let->token = T;
}

/*
 * let_stmt: TEMP decl_var = reference decl_var ;
 */
PARSE_TYPED(let_stmt, let,
		NAMED(TEMP, T)
		TYPED(decl_var, var)
		TOKEN(EQUALS)
		TYPED(reference, r)
		TYPED(decl_var, val_)
		TOKEN(EOS)) {
	let = psi_let_stmt_init(psi_let_exp_init_ex(var, PSI_LET_TMP, val_));
	let->token = T;
	let->exp->is_reference = r ? 1 : 0;
}

/*
 * let_callback: CALLBACK callback_rval ( impl_var ( callback_arg_lists ) )
 */
PARSE_TYPED(let_callback, cb,
		NAMED(CALLBACK, T)
		NAMED(callback_rval, F)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(LPAREN)
		TYPED(callback_arg_list, args_)
		TOKEN(RPAREN)
		TOKEN(RPAREN)) {
	cb = psi_let_callback_init(psi_let_func_init(F->type, F->text, var), args_);
	cb->token = T;
	free(F);
}

/*
 * let_calloc: CALLOC ( num_exp , num_exp )
 */
PARSE_TYPED(let_calloc, alloc,
		NAMED(CALLOC, T)
		TOKEN(LPAREN)
		TYPED(num_exp, nmemb)
		TOKEN(COMMA)
		TYPED(num_exp, size)
		TOKEN(RPAREN)) {
	alloc = psi_let_calloc_init(nmemb, size);
	alloc->token = T;
}

/*
 * let_func: let_func_token ( impl_var )
 */
PARSE_TYPED(let_func, func,
		NAMED(let_func_token, T)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(RPAREN)) {
	func = psi_let_func_init(T->type, T->text, var);
	func->token = T;
}
/*
 * let_func: let_func_token ( impl_var , let_exps )
 */
PARSE_TYPED(let_func, func,
		NAMED(let_func_token, T)
		TOKEN(LPAREN)
		TYPED(impl_var, var)
		TOKEN(COMMA)
		TYPED(let_exps, vals)
		TOKEN(RPAREN)) {
	func = psi_let_func_init(T->type, T->text, var);
	func->token = T;
	func->inner = vals;
}
/*
 * let_exps: let_exp
 */
PARSE_TYPED(let_exps, exps,
		TYPED(let_exp, exp)) {
	exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
			&exp);
}
/*
 * let_exps: let_exps , let_exp
 */
PARSE_TYPED(let_exps, exps,
		TYPED(let_exps, exps_)
		TOKEN(COMMA)
		TYPED(let_exp, exp)) {
	exps = psi_plist_add(exps_, &exp);
}

/*
 * callback_arg_list: <empty>
 */
PARSE_TYPED(callback_arg_list, args, ) {
	args = NULL;
}

/*
 * callback_arg_list: callback_args
 */
PARSE_TYPED(callback_arg_list, args,
		TYPED(callback_args, args_)) {
	args = args_;
}

/*
 * callback_args: set_exp
 */
PARSE_TYPED(callback_args, args,
		TYPED(set_exp, val)) {
	args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
			&val);
}

/*
 * callback_args: callback_args , set_exp
 */
PARSE_TYPED(callback_args, args,
		TYPED(callback_args, args_)
		TOKEN(COMMA)
		TYPED(set_exp, val)) {
	args = psi_plist_add(args_, &val);
}

/*
 * callback_rval: let_func_token
 */
PARSE_NAMED(callback_rval, rval,
		NAMED(let_func_token, F)) {
	rval = F;
}

/*
 * callback_rval: VOID
 */
PARSE_NAMED(callback_rval, rval,
		NAMED(VOID, V)) {
	rval = V;
}


/*
 * set_func: set_func_token ( decl_var )
 */
PARSE_TYPED(set_func, func,
		NAMED(set_func_token, T)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(RPAREN)) {
	func = psi_set_func_init(T->type, T->text, var);
	func->token = T;
}

/*
 * set_func: set_func_token ( decl_var , set_exps )
 */
PARSE_TYPED(set_func, func,
		NAMED(set_func_token, T)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		TYPED(set_exps, vals)
		TOKEN(RPAREN)) {
	func = psi_set_func_init(T->type, T->text, var);
	func->token = T;
	func->inner = vals;
}

/*
 * set_func: set_func_token ( decl_var , ... )
 */
PARSE_TYPED(set_func, func,
		NAMED(set_func_token, T)
		TOKEN(LPAREN)
		TYPED(decl_var, var)
		TOKEN(COMMA)
		TOKEN(ELLIPSIS)
		TOKEN(RPAREN)) {
	func = psi_set_func_init(T->type, T->text, var);
	func->token = T;
	func->recursive = 1;
}

/*
 * set_exp: set_func
 */
PARSE_TYPED(set_exp, val,
		TYPED(set_func, fn)) {
	val = psi_set_exp_init(PSI_SET_FUNC, fn);
}

/*
 * set_exp: num_exp
 */
PARSE_TYPED(set_exp, val,
		TYPED(num_exp, num)) {
	val = psi_set_exp_init(PSI_SET_NUMEXP, num);
}

/*
 * set_exps: set_exp
 */
PARSE_TYPED(set_exps, exps,
		TYPED(set_exp, exp)) {
	exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
			&exp);
}

/*
 * set_exps: set_exps , set_exp
 */
PARSE_TYPED(set_exps, exps,
		TYPED(set_exps, exps_)
		TOKEN(COMMA)
		TYPED(set_exp, exp)) {
	exps = psi_plist_add(exps_, &exp);
}

/* FIXME
 * set_exp: impl_var = set_exp
 */
PARSE_TYPED(set_exp, exp,
		TYPED(impl_var, var_)
		TOKEN(EQUALS)
		TYPED(set_exp, val)) {
	exp = val;
	exp->var = var_;
}

/*
 * set_stmt: SET set_exp ;
 */
PARSE_TYPED(set_stmt, set,
		NAMED(SET, T)
		TYPED(set_exp, exp)
		TOKEN(EOS)) {
	set = psi_set_stmt_init(exp);
	set->token = T;
}

/*
 * return_stmt: RETURN set_exp ;
 */
PARSE_TYPED(return_stmt, ret,
		NAMED(RETURN, T)
		TYPED(set_func, func)
		TOKEN(EOS)) {
	ret = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, func));
	ret->token = T;
}

/*
 * free_stmt: FREE free_exps ;
 */
PARSE_TYPED(free_stmt, free,
		NAMED(FREE, T)
		TYPED(free_exps, calls)
		TOKEN(EOS)) {
	free = psi_free_stmt_init(calls);
	free->token = T;
}

/*
 * free_exps: free_exp
 */
PARSE_TYPED(free_exps, calls,
		TYPED(free_exp, call)) {
	calls = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
			&call);
}

/*
 * free_exps: free_exps , free_exp
 */
PARSE_TYPED(free_exps, calls,
		TYPED(free_exps, calls_)
		TOKEN(COMMA)
		TYPED(free_exp, call)) {
	calls = psi_plist_add(calls_, &call);
}

/*
 * free_exp: NAME ( decl_vars )
 */
PARSE_TYPED(free_exp, call,
		NAMED(NAME, F)
		TOKEN(LPAREN)
		TYPED(decl_vars, vars)
		TOKEN(RPAREN)) {
	call = psi_free_exp_init(F->text, vars);
	call->token = F;
}

/*
 * reference: <empty>
 */
PARSE_TYPED(reference, r, ) {
	r = false;
}

/*
 * reference: &
 */
PARSE_TYPED(reference, r,
		TOKEN(AMPERSAND)) {
	r = true;
}

/*
 * indirection: <empty>
 */
PARSE_TYPED(indirection, i, ){
	i = 0;
}

/*
 * indirection: pointers
 */
PARSE_TYPED(indirection, i,
		TYPED(pointers, p)) {
	i = p;
}

/*
 * pointers: *
 */
PARSE_TYPED(pointers, p,
		TOKEN(ASTERISK)) {
	p = 1;
}

/*
 * pointers: pointers *
 */
PARSE_TYPED(pointers, p,
		TYPED(pointers, p_)
		TOKEN(ASTERISK)) {
	p = p_+1;
}
