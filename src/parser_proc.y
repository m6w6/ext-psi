%include {
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

}

%name PSI_ParserProc
%token_prefix PSI_T_
%token_type {PSI_Token *}
%token_destructor {free($$);}
%default_destructor {(void)P;}
%extra_argument {PSI_Parser *P}
/* TOKEN is defined inside syntax_error */
%syntax_error {
	PSI_ParserSyntaxError(P, P->fn, P->line, "Unexpected token '%s'", TOKEN->text);
}
file ::= blocks.

blocks ::= block.
blocks ::= blocks block.

block ::= COMMENT.

block ::= LIB(T) QUOTED_STRING(libname) EOS. {
	if (P->lib) {
		PSI_ParserSyntaxError(P, P->fn, T->line, "Extra 'lib %s' statement has no effect", libname->text);
	} else {
		P->lib = strndup(libname->text + 1, libname->size - 2);
	}
	free(libname);
	free(T);
}

block ::= decl(decl). {
	P->decls = add_decl(P->decls, decl);
}
block ::= impl(impl). {
	P->impls = add_impl(P->impls, impl);
}
block ::= decl_typedef(def). {
	P->defs = add_decl_typedef(P->defs, def);
	if (def->type->strct) {
		P->structs = add_decl_struct(P->structs, def->type->strct);
	}
}
block ::= constant(constant). {
	P->consts = add_constant(P->consts, constant);
}
block ::= decl_struct(strct). {
	P->structs = add_decl_struct(P->structs, strct);
}

%type decl_struct {decl_struct*}
decl_struct(strct) ::= STRUCT NAME(N) LBRACE struct_args(args) RBRACE. {
	strct = init_decl_struct(N->text, args);
}

%type const_type {const_type*}
const_type(type_) ::= BOOL(T). {
	type_ = init_const_type(T->type, T->text);
	free(T);
}
const_type(type_) ::= INT(T). {
	type_ = init_const_type(T->type, T->text);
	free(T);
}
const_type(type_) ::= FLOAT(T). {
	type_ = init_const_type(T->type, T->text);
	free(T);
}
const_type(type_) ::= STRING(T). {
	type_ = init_const_type(T->type, T->text);
	free(T);
}
%type constant {constant*}
constant(constant) ::= CONST const_type(type) NSNAME(T) EQUALS impl_def_val(val) EOS. {
	constant = init_constant(type, T->text, val);
	free(T);
}

%type decl_typedef {decl_typedef*}
decl_typedef(def) ::= TYPEDEF decl_type(type) NAME(ALIAS) EOS. {
	def = init_decl_typedef(ALIAS->text, type);
	free(ALIAS);
}
decl_typedef(def) ::= TYPEDEF STRUCT(S) NAME(N) NAME(ALIAS) EOS. {
	def = init_decl_typedef(ALIAS->text, init_decl_type(S->type, N->text));
	free(ALIAS);
	free(S);
	free(N);
}
decl_typedef(def) ::= TYPEDEF decl_struct(s) NAME(ALIAS) EOS. {
	def = init_decl_typedef(ALIAS->text, init_decl_type(PSI_T_STRUCT, s->name));
	def->type->strct = s;
	free(ALIAS);
}

%type decl {decl*}
decl(decl) ::= decl_abi(abi) decl_arg(func) LPAREN decl_args(args) RPAREN EOS. {
	decl = init_decl(abi, func, args);
}

%type decl_abi {decl_abi*}
decl_abi(abi) ::= NAME(T). {
	abi = init_decl_abi(T->text);
	free(T);
}

%type decl_var {decl_var*}
decl_var(var) ::= NAME(T). {
	var = init_decl_var(T->text, 0, 0);
	free(T);
}
decl_var(var) ::= pointers(p) NAME(T). {
	var = init_decl_var(T->text, p, 0);
	free(T);
}
decl_var(var) ::= NAME(T) LBRACKET NUMBER(D) RBRACKET. {
	var = init_decl_var(T->text, 1, atol(D->text));
	free(T);
	free(D);
}
decl_var(var) ::= pointers(p) NAME(T) LBRACKET NUMBER(D) RBRACKET. {
	var = init_decl_var(T->text, p+1, atol(D->text));
	free(T);
	free(D);
}

%type decl_vars {decl_vars*}
decl_vars(vars) ::= decl_var(var). {
	vars = init_decl_vars(var);
}
decl_vars(vars) ::= decl_vars(vars_) COMMA decl_var(var). {
	vars = add_decl_var(vars_, var);
}

%type decl_arg {decl_arg*}
decl_arg(arg) ::= decl_type(type) decl_var(var). {
	arg = init_decl_arg(type, var);
}

%type decl_args {decl_args*}
decl_args ::= VOID.
decl_args(args) ::= decl_arg(arg). {
	args = init_decl_args(arg);
}
decl_args(args) ::= decl_args(args_) COMMA decl_arg(arg). {
	args = add_decl_arg(args_, arg);
}
%type struct_args {decl_args*}
struct_args(args) ::= decl_arg(arg) EOS. {
	args = init_decl_args(arg);
}
struct_args(args) ::= struct_args(args_) decl_arg(arg) EOS. {
	args = add_decl_arg(args_, arg);
}

%type decl_type {decl_type*}
decl_type(type_) ::= VOID(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= CHAR(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SHORT(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= INT(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= LONG(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= FLOAT(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= DOUBLE(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SIZE_T(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SINT8(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= UINT8(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SINT16(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= UINT16(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SINT32(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= UINT32(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= SINT64(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= UINT64(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= NAME(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}

%type impl {impl*}
%destructor impl {free_impl($$);}
impl(impl) ::= impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
	impl = init_impl(func, stmts);
}

%type impl_func {impl_func*}
impl_func(func) ::= FUNCTION NSNAME(NAME) impl_args(args) COLON impl_type(type). {
	func = init_impl_func(NAME->text, args, type, 0);
	free(NAME);
}
impl_func(func) ::= FUNCTION REFERENCE NSNAME(NAME) impl_args(args) COLON impl_type(type). {
	func = init_impl_func(NAME->text, args, type, 1);
	free(NAME);
}

%type impl_def_val {impl_def_val*}
impl_def_val(def) ::= NULL(T). {
	def = init_impl_def_val(T);
	free(T);
}
impl_def_val(def) ::= NUMBER(T). {
	def = init_impl_def_val(T);
	free(T);
}
impl_def_val(def) ::= TRUE(T). {
	def = init_impl_def_val(T);
	free(T);
}
impl_def_val(def) ::= FALSE(T). {
	def = init_impl_def_val(T);
	free(T);
}
impl_def_val(def) ::= QUOTED_STRING(T). {
	def = init_impl_def_val(T);
	free(T);
}

%type impl_var {impl_var*}
impl_var(var) ::= DOLLAR NAME(T). {
	var = init_impl_var(T->text, 0);
	free(T);
}
impl_var(var) ::= REFERENCE DOLLAR NAME(T). {
	var = init_impl_var(T->text, 1);
	free(T);
}

%type impl_arg {impl_arg*}
impl_arg(arg) ::= impl_type(type) impl_var(var). {
	arg = init_impl_arg(type, var, NULL);
}
impl_arg(arg) ::= impl_type(type) impl_var(var) EQUALS impl_def_val(def). {
	arg = init_impl_arg(type, var, def);
}

%type impl_args {impl_args*}
impl_args(args) ::= LPAREN RPAREN. {
	args = NULL;
}
impl_args(args) ::= LPAREN impl_arg_list(args_) RPAREN. {
	args = args_;
}
%type impl_arg_list {impl_args*}
impl_arg_list(args) ::= impl_arg(arg). {
	args = init_impl_args(arg);
}
impl_arg_list(args) ::= impl_arg_list(args_) COMMA impl_arg(arg). {
	args = add_impl_arg(args_, arg);
}

%type impl_stmts {impl_stmts*}
%destructor impl_stmts {free_impl_stmts($$);}
impl_stmts(stmts) ::= impl_stmt(stmt). {
	stmts = init_impl_stmts(stmt);
}
impl_stmts(stmts) ::= impl_stmts(stmts_) impl_stmt(stmt). {
	stmts = add_impl_stmt(stmts_, stmt);
}

%type impl_stmt {impl_stmt*}
%destructor impl_stmt {free_impl_stmt($$);}
impl_stmt(stmt) ::= let_stmt(let). {
	stmt = init_impl_stmt(PSI_T_LET, let);
}
impl_stmt(stmt) ::= set_stmt(set). {
	stmt = init_impl_stmt(PSI_T_SET, set);
}
impl_stmt(stmt) ::= return_stmt(ret). {
	stmt = init_impl_stmt(PSI_T_RETURN, ret);
}
impl_stmt(stmt) ::= free_stmt(free). {
	stmt = init_impl_stmt(PSI_T_FREE, free);
}

%type let_stmt {let_stmt*}
let_stmt(let) ::= LET decl_var(var) EOS. {
	let = init_let_stmt(var, NULL);
}
let_stmt(let) ::= LET decl_var(var) EQUALS let_value(val) EOS. {
	let = init_let_stmt(var, val);
}

%type let_value {let_value*}
let_value(val) ::= CALLOC(F) LPAREN NUMBER(N) COMMA decl_type(t) RPAREN. {
	val = init_let_value(
		init_let_func(F->type, F->text,
			atol(N->text) * psi_t_size(real_decl_type(t)->type)
		), NULL, 0
	);
	free_decl_type(t);
	free(F);
	free(N);
}
let_value(val) ::= let_func(func) LPAREN impl_var(var) RPAREN. {
	val = init_let_value(func, var, 0);
}
let_value(val) ::= REFERENCE let_func(func) LPAREN impl_var(var) RPAREN. {
	val = init_let_value(func, var, 1);
}
let_value(val) ::= REFERENCE NULL. {
	val = init_let_value(NULL, NULL, 1);
}
let_value(val) ::= NULL. {
	val = init_let_value(NULL, NULL, 0);
}

%type let_func {let_func*}
let_func(func) ::= STRLEN(T). {
	func = init_let_func(T->type, T->text, 0);
	free(T);
}
let_func(func) ::= STRVAL(T). {
	func = init_let_func(T->type, T->text, 0);
	free(T);
}
let_func(func) ::= INTVAL(T). {
	func = init_let_func(T->type, T->text, 0);
	free(T);
}
let_func(func) ::= FLOATVAL(T). {
	func = init_let_func(T->type, T->text, 0);
	free(T);
}
let_func(func) ::= BOOLVAL(T). {
	func = init_let_func(T->type, T->text, 0);
	free(T);
}

%type set_stmt {set_stmt*}
set_stmt(set) ::= SET impl_var(var) EQUALS set_value(val) EOS. {
	set = init_set_stmt(var, val);
}

%type set_value {set_value*}
set_value(val) ::= set_func(func) LPAREN decl_vars(vars) RPAREN. {
	val = init_set_value(func, vars);
}

%type set_func {set_func*}
set_func(func) ::= TO_ARRAY(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}
set_func(func) ::= TO_STRING(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}
set_func(func) ::= TO_INT(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}
set_func(func) ::= TO_FLOAT(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}
set_func(func) ::= TO_BOOL(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}
set_func(func) ::= VOID(T). {
	func = init_set_func(T->type, T->text);
	free(T);
}

%type return_stmt {return_stmt*}
return_stmt(ret) ::= RETURN set_func(func) LPAREN decl_var(var) RPAREN EOS. {
	ret = init_return_stmt(func, var);
}

%type free_stmt {free_stmt*}
free_stmt(free) ::= FREE decl_vars(vars) EOS. {
	free = init_free_stmt(vars);
}

%type impl_type {impl_type*}
impl_type(type_) ::= VOID(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= MIXED(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= BOOL(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= INT(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= FLOAT(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= STRING(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}
impl_type(type_) ::= ARRAY(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}

%type pointers {unsigned}
pointers(p) ::= POINTER. {++p;}
pointers(p) ::= pointers(P) POINTER. {p = P+1;}
