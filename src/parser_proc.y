%include {
#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "parser.h"

void psi_error(int, const char *, int, const char *, ...);
}

%name PSI_ParserProc
%token_prefix PSI_T_
%token_type {PSI_Token *}
%token_destructor {free($$);}
%default_destructor {(void)P;}
%extra_argument {PSI_Parser *P}
/* TOKEN is defined inside syntax_error */
%syntax_error {
	++P->errors;
	if (TOKEN && TOKEN->type != PSI_T_EOF) {
		psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s'", TOKEN->text);
	} else {
		psi_error(PSI_WARNING, P->psi.file.fn, P->line, "PSI syntax error: Unexpected end of input");
	}
}

%nonassoc NAME.
%left PLUS MINUS.
%left SLASH ASTERISK.
%fallback NAME TEMP FREE SET LET RETURN LIB STRING.

file ::= blocks.

blocks ::= block.
blocks ::= blocks block.

block ::= EOF.
block ::= EOS.

block ::= LIB(T) QUOTED_STRING(libname) EOS. {
	if (P->psi.file.ln) {
		P->error(T, PSI_WARNING, "Extra 'lib %s' statement has no effect", libname->text);
	} else {
		P->psi.file.ln = strndup(libname->text + 1, libname->size - 2);
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

struct_name(n) ::= STRUCT NAME(N). {
	n = N;
}

%type decl_struct_args {decl_args*}
%destructor decl_struct_args {free_decl_args($$);}
decl_struct_args(args_) ::= LBRACE struct_args(args) RBRACE. {
	args_ = args;
}
decl_struct_args(args_) ::= EOS. {
	args_ = init_decl_args(NULL);
}


%type decl_struct {decl_struct*}
%destructor decl_struct {free_decl_struct($$);}
decl_struct(strct) ::= struct_name(N) struct_size(size_) decl_struct_args(args). {
	strct = init_decl_struct(N->text, args);
	strct->size = size_;
	strct->token = N;
}

%type struct_size {size_t}
struct_size(size) ::= . {
	size = 0;
}
struct_size(size) ::= COLON COLON LPAREN NUMBER(SIZ) RPAREN. {
	size = atol(SIZ->text);
	free(SIZ);
}

%token_class const_type_token BOOL INT FLOAT STRING.
%type const_type {const_type*}
%destructor const_type {free_const_type($$);}
const_type(type_) ::= const_type_token(T). {
	type_ = init_const_type(T->type, T->text);
	free(T);
}
%type constant {constant*}
%destructor constant {free_constant($$);}
constant(constant) ::= CONST const_type(type) NSNAME(T) EQUALS impl_def_val(val) EOS. {
	constant = init_constant(type, T->text, val);
	free(T);
}

%type decl_typedef {decl_typedef*}
%destructor decl_typedef {free_decl_typedef($$);}
decl_typedef(def) ::= TYPEDEF decl_typedef_body(def_) EOS. {
	def = def_;
}
%type decl_typedef_body {decl_typedef*}
%destructor decl_typedef_body {free_decl_typedef($$);}
decl_typedef_body(def) ::= decl_type(type) NAME(ALIAS). {
	def = init_decl_typedef(ALIAS->text, type);
	def->token = ALIAS;
}

/* support opaque types */
decl_typedef_body(def) ::= VOID(V) indirection(i) NAME(ALIAS). {
	def = init_decl_typedef(ALIAS->text, init_decl_type(i?PSI_T_POINTER:V->type, V->text));
	def->token = ALIAS;
	def->type->token = V;
}

%type decl {decl*}
%destructor decl {free_decl($$);}
decl(decl) ::= decl_abi(abi) decl_func(func) LPAREN decl_args(args) RPAREN EOS. {
	decl = init_decl(abi, func, args);
}

%type decl_func {decl_arg*}
%destructor decl_func {free_decl_arg($$);}
decl_func(func) ::= decl_arg(arg). {
	func = arg;
}
/* special case for void functions */
decl_func(func) ::= VOID(T) NAME(N). {
	func = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, 0, 0)
	);
	func->type->token = T;
	//free(T);
	free(N);
}

%type decl_abi {decl_abi*}
%destructor decl_abi {free_decl_abi($$);}
decl_abi(abi) ::= NAME(T). {
	abi = init_decl_abi(T->text);
	abi->token = T;
}

%type decl_var {decl_var*}
%destructor decl_var {free_decl_var($$);}
decl_var(var) ::= indirection(p) NAME(T). {
	var = init_decl_var(T->text, p, 0);
	var->token = T;
}
decl_var(var) ::= indirection(p) NAME(T) LBRACKET NUMBER(D) RBRACKET. {
	var = init_decl_var(T->text, p+1, atol(D->text));
	var->token = T;
	free(D);
}

%type decl_vars {decl_vars*}
%destructor decl_vars {free_decl_vars($$);}
decl_vars(vars) ::= decl_var(var). {
	vars = init_decl_vars(var);
}
decl_vars(vars) ::= decl_vars(vars_) COMMA decl_var(var). {
	vars = add_decl_var(vars_, var);
}

%type decl_arg {decl_arg*}
%destructor decl_arg {free_decl_arg($$);}
decl_arg(arg_) ::= const_decl_type(type) decl_var(var). {
	arg_ = init_decl_arg(type, var);
}
/* void pointers need a specific rule */
decl_arg(arg_) ::= VOID(T) pointers(p) NAME(N). {
	arg_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}
decl_arg(arg_) ::= CONST VOID(T) pointers(p) NAME(N). {
	arg_ = init_decl_arg(
		init_decl_type(T->type, T->text),
		init_decl_var(N->text, p, 0)
	);
	arg_->type->token = T;
	arg_->var->token = N;
	arg_->token = N;
}

%type decl_args {decl_args*}
%destructor decl_args {free_decl_args($$);}
decl_args ::= .
decl_args ::= VOID.
decl_args(args) ::= decl_arg(arg). {
	args = init_decl_args(arg);
}
decl_args(args) ::= decl_args(args_) COMMA decl_arg(arg). {
	args = add_decl_arg(args_, arg);
}
decl_args(args) ::= decl_args(args_) COMMA ELLIPSIS. {
	args = args_;
	args->varargs = 1;
}
%type struct_args {decl_args*}
%destructor struct_args {free_decl_args($$);}
struct_args(args) ::= struct_arg(arg). {
	args = init_decl_args(arg);
}
struct_args(args) ::= struct_args(args_) struct_arg(arg). {
	args = add_decl_arg(args_, arg);
}
%type struct_arg {decl_arg*}
%destructor struct_arg {free_decl_arg($$);}
struct_arg(arg) ::= decl_arg(arg_) struct_layout(layout_) EOS. {
	arg_->layout = layout_;
	arg = arg_;
}

%type struct_layout {decl_struct_layout*}
%destructor struct_layout {free_decl_struct_layout($$);}
struct_layout(layout) ::= . {
	layout = NULL;
}
struct_layout(layout) ::= COLON COLON LPAREN NUMBER(POS) COMMA NUMBER(SIZ) RPAREN. {
	layout = init_decl_struct_layout(atol(POS->text), atol(SIZ->text));
	free(POS);
	free(SIZ);
}

/* un/signed, urgh */
decl_scalar_type(type_) ::= CHAR(C). {
	type_ = C;
}
decl_scalar_type(type_) ::= SHORT(S) decl_scalar_type_short(s). {
	if (s) {
		type_ = PSI_TokenCat(2, S, s);
		free(S);
		free(s);
	} else {
		type_ = S;
	}
}
decl_scalar_type_short(s) ::= . {
	s = NULL;
}

decl_scalar_type_short(s) ::= INT(I). {
	s = I;
}
decl_scalar_type(type_) ::= INT(I). {
	type_ = I;
}
decl_scalar_type(type_) ::= LONG(L) decl_scalar_type_long(l). {
	if (l) {
		type_ = PSI_TokenCat(2, L, l);
		free(L);
		free(l);
	} else {
		type_ = L;
	}
}
decl_scalar_type_long(l) ::= . {
	l = NULL;
}
decl_scalar_type_long(l) ::= DOUBLE(D). {
	l = D;
}
decl_scalar_type_long(l) ::= LONG(L) decl_scalar_type_long_long(ll). {
	if (ll) {
		l = PSI_TokenCat(2, L, ll);
		free(L);
		free(ll);
	} else {
		l = L;
	}
}
decl_scalar_type_long_long(ll) ::= . {
	ll = NULL;
}
decl_scalar_type_long_long(ll) ::= INT(I). {
	ll = I;
}
decl_type(type_) ::= UNSIGNED(U) decl_scalar_type(N). {
	PSI_Token *T = PSI_TokenCat(2, U, N);
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
	free(U);
	free(N);
}
decl_type(type_) ::= SIGNED(S) decl_scalar_type(N). {
	PSI_Token *T = PSI_TokenCat(2, S, N);
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
	free(S);
	free(N);
}
decl_type(type_) ::= UNSIGNED(U). {
	type_ = init_decl_type(PSI_T_NAME, U->text);
	type_->token = U;
}
decl_type(type_) ::= SIGNED(S). {
	type_ = init_decl_type(PSI_T_NAME, S->text);
	type_->token = S;
}
decl_type(type_) ::= decl_scalar_type(N). {
	type_ = init_decl_type(N->type, N->text);
	type_->token = N;
}
/* structs ! */
decl_type(type_) ::= STRUCT(S) NAME(T). {
	type_ = init_decl_type(S->type, T->text);
	type_->token = T;
	free(S);
}
%token_class decl_type_token FLOAT DOUBLE INT8 UINT8 INT16 UINT16 INT32 UINT32 INT64 UINT64 NAME.
%type decl_type {decl_type*}
%destructor decl_type {free_decl_type($$);}
decl_type(type_) ::= decl_type_token(T). {
	type_ = init_decl_type(T->type, T->text);
	type_->token = T;
}


%type const_decl_type {decl_type*}
%destructor const_decl_type {free_decl_type($$);}
const_decl_type(type) ::= decl_type(type_). {
	type = type_;
}
const_decl_type(type) ::= CONST decl_type(type_). {
	type = type_;
}

%type impl {impl*}
%destructor impl {free_impl($$);}
impl(impl) ::= impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
	impl = init_impl(func, stmts);
}

%type impl_func {impl_func*}
%destructor impl_func {free_impl_func($$);}
impl_func(func) ::= FUNCTION reference(r) NSNAME(NAME) impl_args(args) COLON impl_type(type). {
	func = init_impl_func(NAME->text, args, type, r);
	func->token = NAME;
}

%token_class impl_def_val_token NULL NUMBER TRUE FALSE QUOTED_STRING.
%type impl_def_val {impl_def_val*}
%destructor impl_def_val {free_impl_def_val($$);}
impl_def_val(def) ::= impl_def_val_token(T). {
	def = init_impl_def_val(T->type, T->text);
	free(T);
}

%type impl_var {impl_var*}
%destructor impl_var {free_impl_var($$);}
impl_var(var) ::= reference(r) DOLLAR NAME(T). {
	var = init_impl_var(T->text, r);
	var->token = T;
}

%type impl_arg {impl_arg*}
%destructor impl_arg {free_impl_arg($$);}
impl_arg(arg) ::= impl_type(type) impl_var(var). {
	arg = init_impl_arg(type, var, NULL);
}
impl_arg(arg) ::= impl_type(type) impl_var(var) EQUALS impl_def_val(def). {
	arg = init_impl_arg(type, var, def);
}

%type impl_args {impl_args*}
%destructor impl_args {free_impl_args($$);}
impl_args(args) ::= LPAREN RPAREN. {
	args = NULL;
}
impl_args(args) ::= LPAREN impl_arg_list(args_) RPAREN. {
	args = args_;
}
impl_args(args) ::= LPAREN impl_arg_list(args_) COMMA impl_vararg(va) RPAREN. {
	args = args_;
	args->vararg.name = va;
}

%type impl_vararg {impl_arg*}
%destructor impl_vararg {free_impl_arg($$);}
impl_vararg(va) ::= impl_type(type) reference(r) ELLIPSIS DOLLAR NAME(T). {
	va = init_impl_arg(type, init_impl_var(T->text, r), NULL);
	free(T);
}

%type impl_arg_list {impl_args*}
%destructor impl_arg_list {free_impl_args($$);}
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

%token_class num_exp_token NUMBER NSNAME.
%token_class num_exp_op_token PLUS MINUS ASTERISK SLASH.
%type num_exp {num_exp*}
%destructor num_exp {free_num_exp($$);}
num_exp(exp) ::= num_exp_token(tok). {
	exp = init_num_exp(tok->type, tok->text);
	exp->token = tok;
}
num_exp(exp) ::= decl_var(var). {
	exp = init_num_exp(PSI_T_NAME, var);
	exp->token = PSI_TokenCopy(var->token);
}
num_exp(exp) ::= num_exp(exp_) num_exp_op_token(operator_) num_exp(operand_). {
	exp_->operator = operator_->type;
	exp_->operand = operand_;
	exp = exp_;
	free(operator_);
}

%type let_stmt {let_stmt*}
%destructor let_stmt {free_let_stmt($$);}
let_stmt(let) ::= LET decl_var(var) EOS. {
	let = init_let_stmt(var, init_let_val(PSI_LET_NULL, NULL));
}
let_stmt(let) ::= LET decl_var(var) EQUALS reference(r) let_val(val) EOS. {
	val->flags.one.is_reference = r ? 1 : 0;
	let = init_let_stmt(var, val);
}
let_stmt(let) ::= TEMP decl_var(var) EQUALS decl_var(val) EOS. {
	let = init_let_stmt(var, init_let_val(PSI_LET_TMP, val));
}

%type let_val {let_val*}
%destructor let_val {free_let_val($$);}
let_val(val) ::= NULL. {
	val = init_let_val(PSI_LET_NULL, NULL);
}
let_val(val) ::= num_exp(exp). {
	val = init_let_val(PSI_LET_NUMEXP, exp);
}
let_val(val) ::= CALLOC LPAREN let_calloc(alloc) RPAREN. {
	val = init_let_val(PSI_LET_CALLOC, alloc);
}
let_val(val) ::= let_func(func). {
	val = init_let_val(PSI_LET_FUNC, func);
}

%type let_calloc {let_calloc*}
%destructor let_calloc {free_let_calloc($$);}
let_calloc(alloc) ::= num_exp(nmemb) COMMA num_exp(size). {
	alloc = init_let_calloc(nmemb, size);
}
%token_class let_func_token OBJVAL ARRVAL PATHVAL STRLEN STRVAL FLOATVAL INTVAL BOOLVAL.
%type let_func {let_func*}
%destructor let_func {free_let_func($$);}
let_func(func) ::= let_func_token(T) LPAREN impl_var(var) RPAREN. {
	func = init_let_func(T->type, T->text, var);
	free(T);
}


%type set_stmt {set_stmt*}
%destructor set_stmt {free_set_stmt($$);}
set_stmt(set) ::= SET impl_var(var) EQUALS set_value(val) EOS. {
	set = init_set_stmt(var, val);
}

%type set_value {set_value*}
%destructor set_value {free_set_value($$);}
set_value(val) ::= set_func(func) LPAREN decl_var(var) RPAREN. {
	val = init_set_value(func, init_decl_vars(var));
}
set_value(val) ::= set_func(func) LPAREN decl_var(var) COMMA num_exp(num_) RPAREN. {
	val = init_set_value(func, init_decl_vars(var));
	val->num = num_;
}
set_value(val) ::= set_func(func_) LPAREN decl_var(var) COMMA ELLIPSIS(T) RPAREN. {
	free_set_func(func_);
	val = init_set_value(init_set_func(T->type, T->text), init_decl_vars(var));
	val->func->token = T;
}
set_value(val) ::= set_func(func_) LPAREN decl_var(var) COMMA set_vals(vals) RPAREN. {
	val = vals;
	val->func = func_;
	val->vars = init_decl_vars(var);
}
set_value(val) ::= set_func(func_) LPAREN decl_var(var) COMMA num_exp(num_) COMMA set_vals(vals) RPAREN. {
	val = vals;
	val->func = func_;
	val->num = num_;
	val->vars = init_decl_vars(var);
}
%type set_vals {set_value*}
%destructor set_vals {free_set_value($$);}
set_vals(vals) ::= set_value(val). {
	vals = add_inner_set_value(init_set_value(NULL, NULL), val);
}
set_vals(vals) ::= set_vals(vals_) COMMA set_value(val). {
	vals = add_inner_set_value(vals_, val);
}

%token_class set_func_token TO_OBJECT TO_ARRAY TO_STRING TO_INT TO_FLOAT TO_BOOL VOID.
%type set_func {set_func*}
%destructor set_func {free_set_func($$);}
set_func(func) ::= set_func_token(T). {
	func = init_set_func(T->type, T->text);
	func->token = T;
}

%type return_stmt {return_stmt*}
%destructor return_stmt {free_return_stmt($$);}
return_stmt(ret) ::= RETURN(T) set_value(val) EOS. {
	ret = init_return_stmt(val);
	ret->token = T;
}

%type free_stmt {free_stmt*}
%destructor free_stmt {free_free_stmt($$);}
free_stmt(free) ::= FREE free_calls(calls) EOS. {
	free = init_free_stmt(calls);
}

%type free_calls {free_calls*}
%destructor free_calls {free_free_calls($$);}
free_calls(calls) ::= free_call(call). {
	calls = init_free_calls(call);
}
free_calls(calls) ::= free_calls(calls_) COMMA free_call(call). {
	calls = add_free_call(calls_, call);
}

%type free_call {free_call*}
%destructor free_call {free_free_call($$);}
free_call(call) ::= NAME(F) LPAREN decl_vars(vars) RPAREN. {
	call = init_free_call(F->text, vars);
	call->token = F;
}

%token_class impl_type_token VOID MIXED BOOL INT FLOAT STRING ARRAY OBJECT.
%type impl_type {impl_type*}
%destructor impl_type {free_impl_type($$);}
impl_type(type_) ::= impl_type_token(T). {
	type_ = init_impl_type(T->type, T->text);
	free(T);
}

%type reference {char}
reference(r) ::= . {r = 0;}
reference(r) ::= AMPERSAND. {r = 1;}

%type indirection {unsigned}
indirection(i) ::= . {i = 0;}
indirection(i) ::= pointers(p). {i = p;}

%type pointers {unsigned}
pointers(p) ::= ASTERISK. {p = 1;}
pointers(p) ::= pointers(P) ASTERISK. {p = P+1;}
