%include {
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "lexer.h"
#include "parser.h"
#include "types.h"

static void syntax_error(const char *fn, size_t ln, const char *msg, ...) {
	fprintf(stderr, "WARNING: Syntax error on line %zu in '%s'%s", ln, fn, msg ? ": ": "\n");
	if (msg) {
		va_list argv;

		va_start(argv, msg);
		vfprintf(stderr, msg, argv);
		va_end(argv);
	}
}

}

%name PSI_Parser
%token_prefix PSI_T_
%token_type {PSI_Token *}
%token_destructor {free($$);}
%extra_argument {PSI_Lexer *L}
/* TOKEN is defined inside syntax_error */
%syntax_error {
	syntax_error(L->fn, L->line, "Unexpected token '%s'.\n", TOKEN->text);
}
file ::= blocks.

blocks ::= block.
blocks ::= blocks block.

block ::= COMMENT.

block ::= LIB(T) QUOTED_STRING(libname) EOS. {
	if (L->lib) {
		syntax_error(L->fn, T->line, "Extra 'lib %s' statement has no effect.\n", libname->text);
	} else {
		L->lib = strndup(libname->text + 1, libname->size - 2);
	}
	free(libname);
	free(T);
}

block ::= decl(decl). {
	L->decls = add_decl(L->decls, decl);
}
block ::= impl(impl). {
	L->impls = add_impl(L->impls, impl);
}
block ::= decl_typedef(def). {
	L->defs = add_decl_typedef(L->defs, def);
}

%type decl_typedef {decl_typedef*}
decl_typedef(def) ::= TYPEDEF NAME(ALIAS) decl_type(type) EOS. {
	def = init_decl_typedef(ALIAS->text, type);
	free(ALIAS);
}

%type decl {decl*}
decl(decl) ::= decl_arg(func) LPAREN decl_args(args) RPAREN EOS. {
	decl = init_decl(func, args);
}
%type decl_var {decl_var*}
decl_var(var) ::= NAME(T). {
	var = init_decl_var(T->text, 0);
	free(T);
}
decl_var(var) ::= pointers(p) NAME(T). {
	var = init_decl_var(T->text, p);
	free(T);
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
decl_args(args) ::= decl_arg(arg). {
	args = init_decl_args(arg);
}
decl_args(args) ::= decl_args(args_) COMMA decl_arg(arg). {
	args = add_decl_arg(args_, arg);
}

%type decl_type {decl_type*}
decl_type(type_) ::= VOID(T). {
	type_ = init_decl_type(T->type, T->text);
	free(T);
}
decl_type(type_) ::= INT(T). {
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
impl(impl) ::= impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
	impl = init_impl(func, stmts);
}

%type impl_func {impl_func*}
impl_func(func) ::= FUNCTION NSNAME(NAME) LPAREN impl_args(args) RPAREN COLON impl_type(type). {
	func = init_impl_func(NAME->text, args, type);
	free(NAME);
}
impl_func(func) ::= FUNCTION NSNAME(NAME) LPAREN RPAREN COLON impl_type(type). {
	func = init_impl_func(NAME->text, NULL, type);
	free(NAME);
}

%type impl_def_val {impl_def_val*}
impl_def_val(def) ::= NULL. {
	/* FIXME */
	def = init_impl_def_val();
}
impl_def_val(def) ::= number. {
	/* FIXME */
	def = init_impl_def_val();
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
impl_args(args) ::= impl_arg(arg). {
	args = init_impl_args(arg);
}
impl_args(args) ::= impl_args(args_) COMMA impl_arg(arg). {
	args = add_impl_arg(args_, arg);
}

%type impl_stmts {impl_stmts*}
impl_stmts(stmts) ::= impl_stmt(stmt). {
	stmts = init_impl_stmts(stmt);
}
impl_stmts(stmts) ::= impl_stmts(stmts_) impl_stmt(stmt). {
	stmts = add_impl_stmt(stmts_, stmt);
}

%type impl_stmt {impl_stmt*}
impl_stmt(stmt) ::= let_stmt(let). {
	stmt = init_impl_stmt(PSI_T_LET, let);
}
impl_stmt(stmt) ::= set_stmt(set). {
	stmt = init_impl_stmt(PSI_T_SET, set);
}
impl_stmt(stmt) ::= ret_stmt(ret). {
	stmt = init_impl_stmt(PSI_T_RET, ret);
}

%type let_stmt {let_stmt*}
let_stmt(let) ::= LET decl_var(var) EQUALS let_value(val) EOS. {
	let = init_let_stmt(var, val);
}

%type let_value {let_value*}
let_value(val) ::= let_func(func) LPAREN impl_var(var) RPAREN. {
	val = init_let_value(func, var, 0);
}
let_value(val) ::= REFERENCE NULL. {
	val = init_let_value(NULL, NULL, 1);
}
let_value(val) ::= NULL. {
	val = init_let_value(NULL, NULL, 0);
}

%type let_func {let_func*}
let_func(func) ::= STRVAL(T). {
	func = init_let_func(T->type, T->text);
	free(T);
}
let_func(func) ::= INTVAL(T). {
	func = init_let_func(T->type, T->text);
	free(T);
}
let_func(func) ::= FLOATVAL(T). {
	func = init_let_func(T->type, T->text);
	free(T);
}
let_func(func) ::= BOOLVAL(T). {
	func = init_let_func(T->type, T->text);
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

%type ret_stmt {ret_stmt*}
ret_stmt(ret) ::= RET set_func(func) LPAREN decl_var(var) RPAREN EOS. {
	ret = init_ret_stmt(func, var);
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

digits ::= DIGIT.
digits ::= digits DIGIT.
decimals ::= digits DOT digits.
decimals ::= DOT digits.
decimals ::= digits DOT.
number ::= digits.
number ::= PLUS digits.
number ::= MINUS digits.
number ::= decimals.
number ::= MINUS decimals.
number ::= PLUS decimals.

%type pointers {unsigned}
pointers(p) ::= POINTER. {++p;}
pointers(p) ::= pointers(P) POINTER. {p = ++P;}
