%include {
#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include <stddef.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "parser.h"
}
%name psi_parser_proc_
%token_prefix PSI_T_
%token_type {struct psi_token *}
%token_destructor {free($$);}
%default_destructor {(void)P;}
%extra_argument {struct psi_parser *P}
%syntax_error { ++P->errors; if (TOKEN && TOKEN->type != PSI_T_EOF) { psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col); } else { psi_error(PSI_WARNING, P->psi.file.fn, P->line, "PSI syntax error: Unexpected end of input"); } }
%nonassoc NAME.
%left PLUS MINUS.
%left SLASH ASTERISK.
%fallback NAME TEMP FREE SET LET RETURN CALLOC CALLBACK ZVAL LIB STRING.
%token_class const_type_token BOOL INT FLOAT STRING.
%token_class decl_type_token FLOAT DOUBLE INT8 UINT8 INT16 UINT16 INT32 UINT32 INT64 UINT64 NAME.
%token_class impl_def_val_token NULL NUMBER TRUE FALSE QUOTED_STRING.
%token_class num_exp_token NUMBER NSNAME.
%token_class num_exp_op_token PLUS MINUS ASTERISK SLASH.
%token_class let_func_token ZVAL OBJVAL ARRVAL PATHVAL STRLEN STRVAL FLOATVAL INTVAL BOOLVAL.
%token_class set_func_token TO_OBJECT TO_ARRAY TO_STRING TO_INT TO_FLOAT TO_BOOL ZVAL VOID.
%token_class impl_type_token VOID MIXED BOOL INT FLOAT STRING ARRAY OBJECT CALLABLE.
%type decl_enum {decl_enum *}
%destructor decl_enum {free_decl_enum($$);}
%type decl_enum_items {decl_enum_items*}
%destructor decl_enum_items {free_decl_enum_items($$);}
%type decl_enum_item {decl_enum_item*}
%destructor decl_enum_item {free_decl_enum_item($$);}
%type decl_struct_args_block {decl_args*}
%destructor decl_struct_args_block {free_decl_args($$);}
%type decl_struct_args {decl_args*}
%destructor decl_struct_args {free_decl_args($$);}
%type decl_struct {decl_struct*}
%destructor decl_struct {free_decl_struct($$);}
%type align_and_size {decl_struct_layout}
%type decl_union {decl_union*}
%destructor decl_union {free_decl_union($$);}
%type const_type {const_type*}
%destructor const_type {free_const_type($$);}
%type constant {constant*}
%destructor constant {free_constant($$);}
%type decl_typedef {decl_arg*}
%destructor decl_typedef {free_decl_arg($$);}
%type decl_typedef_body_ex {decl_arg*}
%destructor decl_typedef_body_ex {free_decl_arg($$);}
%type decl_typedef_body {decl_arg*}
%destructor decl_typedef_body {free_decl_arg($$);}
%type decl_typedef_body_fn_args {decl_args *}
%destructor decl_typedef_body_fn_args {free_decl_args($$);}
%type decl {decl*}
%destructor decl {free_decl($$);}
%type decl_func {decl_arg*}
%destructor decl_func {free_decl_arg($$);}
%type decl_abi {decl_abi*}
%destructor decl_abi {free_decl_abi($$);}
%type decl_var {decl_var*}
%destructor decl_var {free_decl_var($$);}
%type decl_vars {decl_vars*}
%destructor decl_vars {free_decl_vars($$);}
%type decl_arg {decl_arg*}
%destructor decl_arg {free_decl_arg($$);}
%type decl_args {decl_args*}
%destructor decl_args {free_decl_args($$);}
%type struct_args {decl_args*}
%destructor struct_args {free_decl_args($$);}
%type struct_arg {decl_arg*}
%destructor struct_arg {free_decl_arg($$);}
%type struct_layout {decl_struct_layout*}
%destructor struct_layout {free_decl_struct_layout($$);}
%type decl_type {decl_type*}
%destructor decl_type {free_decl_type($$);}
%type const_decl_type {decl_type*}
%destructor const_decl_type {free_decl_type($$);}
%type impl {impl*}
%destructor impl {free_impl($$);}
%type impl_func {impl_func*}
%destructor impl_func {free_impl_func($$);}
%type impl_def_val {impl_def_val*}
%destructor impl_def_val {free_impl_def_val($$);}
%type impl_var {impl_var*}
%destructor impl_var {free_impl_var($$);}
%type impl_arg {impl_arg*}
%destructor impl_arg {free_impl_arg($$);}
%type impl_args {impl_args*}
%destructor impl_args {free_impl_args($$);}
%type impl_vararg {impl_arg*}
%destructor impl_vararg {free_impl_arg($$);}
%type impl_arg_list {impl_args*}
%destructor impl_arg_list {free_impl_args($$);}
%type impl_stmts {impl_stmts*}
%destructor impl_stmts {free_impl_stmts($$);}
%type impl_stmt {impl_stmt*}
%destructor impl_stmt {free_impl_stmt($$);}
%type num_exp {num_exp*}
%destructor num_exp {free_num_exp($$);}
%type let_stmt {let_stmt*}
%destructor let_stmt {free_let_stmt($$);}
%type let_calloc {let_calloc*}
%destructor let_calloc {free_let_calloc($$);}
%type let_func {let_func*}
%destructor let_func {free_let_func($$);}
%type callback_arg_list {set_values *}
%destructor callback_arg_list {free_set_values($$);}
%type callback_args {set_values *}
%destructor callback_args {free_set_values($$);}
%type let_val {let_val*}
%destructor let_val {free_let_val($$);}
%type let_vals {let_vals*}
%destructor let_vals {free_let_vals($$);}
%type set_stmt {set_stmt*}
%destructor set_stmt {free_set_stmt($$);}
%type set_value {set_value*}
%destructor set_value {free_set_value($$);}
%type set_vals {set_value*}
%destructor set_vals {free_set_value($$);}
%type set_func {set_func*}
%destructor set_func {free_set_func($$);}
%type return_stmt {return_stmt*}
%destructor return_stmt {free_return_stmt($$);}
%type free_stmt {free_stmt*}
%destructor free_stmt {free_free_stmt($$);}
%type free_calls {free_calls*}
%destructor free_calls {free_free_calls($$);}
%type free_call {free_call*}
%destructor free_call {free_free_call($$);}
%type impl_type {impl_type*}
%destructor impl_type {free_impl_type($$);}
%type reference {char}
%type indirection {unsigned}
%type pointers {unsigned}
file ::= blocks.
blocks ::= block.
blocks ::= blocks block.
block ::= EOF.
block ::= EOS.
block ::= LIB(token) QUOTED_STRING(libname) EOS. {
 if (P->psi.file.ln) {
  P->error(P, token, PSI_WARNING, "Extra 'lib %s' statement has no effect", libname->text);
 } else {
  P->psi.file.ln = strndup(libname->text + 1, libname->size - 2);
 }
 free(libname);
 free(token);
}
block ::= decl(decl). {
 P->decls = add_decl(P->decls, decl);
}
block ::= impl(impl). {
 P->impls = add_impl(P->impls, impl);
}
block ::= decl_typedef(def). {
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
block ::= constant(constant). {
 P->consts = add_constant(P->consts, constant);
}
block ::= decl_struct(strct). {
 P->structs = add_decl_struct(P->structs, strct);
}
block ::= decl_union(u). {
 P->unions = add_decl_union(P->unions, u);
}
block ::= decl_enum(e). {
 P->enums = add_decl_enum(P->enums, e);
}
optional_name(n) ::= . {
 n = NULL;
}
optional_name(n) ::= NAME(N). {
 n = N;
}
enum_name(n) ::= ENUM(E) optional_name(N). {
 if (N) {
  n = N;
  free(E);
 } else {
  char digest[17];
  psi_token_hash(E, digest);
  n = psi_token_translit(psi_token_append(E, 1, digest), " ", "@");
 }
}
decl_enum(e) ::= enum_name(N) LBRACE decl_enum_items(list) RBRACE. {
 e = init_decl_enum(N->text, list);
 e->token = N;
}
decl_enum_items(l) ::= decl_enum_item(i). {
 l = init_decl_enum_items(i);
}
decl_enum_items(l) ::= decl_enum_items(l_) COMMA decl_enum_item(i). {
 l = add_decl_enum_item(l_, i);
}
decl_enum_item(i) ::= NAME(N) EQUALS num_exp(num). {
 i = init_decl_enum_item(N->text, num);
 i->token = N;
}
decl_enum_item(i) ::= NAME(N). {
 i = init_decl_enum_item(N->text, NULL);
 i->token = N;
}
union_name(n) ::= UNION(U) optional_name(N). {
 if (N) {
  n = N;
  free(U);
 } else {
  char digest[17];
  psi_token_hash(U, digest);
  n = psi_token_translit(psi_token_append(U, 1, digest), " ", "@");
 }
}
struct_name(n) ::= STRUCT(S) optional_name(N). {
 if (N) {
  n = N;
  free(S);
 } else {
  char digest[17];
  psi_token_hash(S, digest);
  n = psi_token_translit(psi_token_append(S, 1, digest), " ", "@");
 }
}
decl_struct_args_block(args_) ::= LBRACE struct_args(args) RBRACE. {
 args_ = args;
}
decl_struct_args(args_) ::= decl_struct_args_block(args). {
 args_ = args;
}
decl_struct_args(args_) ::= EOS. {
 args_ = init_decl_args(NULL);
}
decl_struct(strct) ::= STRUCT NAME(N) align_and_size(as) decl_struct_args(args). {
 strct = init_decl_struct(N->text, args);
 strct->align = as.pos;
 strct->size = as.len;
 strct->token = N;
}
align_and_size(as) ::= . {
 as.pos = 0;
 as.len = 0;
}
align_and_size(as) ::= COLON COLON LPAREN NUMBER(A) COMMA NUMBER(S) RPAREN. {
 as.pos = atol(A->text);
 as.len = atol(S->text);
 free(A);
 free(S);
}
decl_union(u) ::= UNION NAME(N) align_and_size(as) decl_struct_args(args). {
 u = init_decl_union(N->text, args);
 u->align = as.pos;
 u->size = as.len;
 u->token = N;
}
const_type(type_) ::= const_type_token(T). {
 type_ = init_const_type(T->type, T->text);
 free(T);
}
constant(constant) ::= CONST const_type(type) NSNAME(T) EQUALS impl_def_val(val) EOS. {
 constant = init_constant(type, T->text, val);
 free(T);
}
decl_typedef(def) ::= TYPEDEF(T) decl_typedef_body(def_) EOS. {
 def = def_;
 def->token = T;
}
decl_typedef_body_ex(def) ::= struct_name(N) align_and_size(as) decl_struct_args_block(args) decl_var(var). {
 def = init_decl_arg(init_decl_type(PSI_T_STRUCT, N->text), var);
 def->type->token = psi_token_copy(N);
 def->type->real.strct = init_decl_struct(N->text, args);
 def->type->real.strct->token = N;
 def->type->real.strct->align = as.pos;
 def->type->real.strct->size = as.len;
}
decl_typedef_body_ex(def) ::= union_name(N) align_and_size(as) decl_struct_args_block(args) decl_var(var). {
 def = init_decl_arg(init_decl_type(PSI_T_UNION, N->text), var);
 def->type->token = psi_token_copy(N);
 def->type->real.unn = init_decl_union(N->text, args);
 def->type->real.unn->token = N;
 def->type->real.unn->align = as.pos;
 def->type->real.unn->size = as.len;
}
decl_typedef_body_ex(def) ::= decl_enum(e) NAME(ALIAS). {
 def = init_decl_arg(init_decl_type(PSI_T_ENUM, e->name), init_decl_var(ALIAS->text, 0, 0));
 def->var->token = ALIAS;
 def->type->token = psi_token_copy(e->token);
 def->type->real.enm = e;
}
decl_typedef_body(def) ::= decl_typedef_body_ex(def_). {
 def = def_;
}
decl_typedef_body_fn_args(args) ::= LPAREN decl_args(args_) RPAREN. {
 args = args_;
}
decl_typedef_body(def) ::= decl_func(func_) decl_typedef_body_fn_args(args). {
 def = init_decl_arg(init_decl_type(PSI_T_FUNCTION, func_->var->name), copy_decl_var(func_->var));
 def->type->token = psi_token_copy(func_->token);
 def->type->real.func = init_decl(init_decl_abi("default"), func_, args);
}
decl_typedef_body(def) ::= decl_arg(arg). {
 def = arg;
}
decl(decl) ::= decl_abi(abi) decl_func(func) LPAREN decl_args(args) RPAREN EOS. {
 decl = init_decl(abi, func, args);
}
decl_func(func) ::= decl_arg(arg). {
 func = arg;
}
decl_func(func) ::= VOID(T) NAME(N). {
 func = init_decl_arg(
  init_decl_type(T->type, T->text),
  init_decl_var(N->text, 0, 0)
 );
 func->type->token = T;
 func->var->token = N;
 func->token = N;
}
decl_typedef_body(def) ::= VOID(T) indirection(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
decl_typedef_body(def) ::= CONST VOID(T) pointers(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
decl_abi(abi) ::= NAME(T). {
 abi = init_decl_abi(T->text);
 abi->token = T;
}
decl_var(var) ::= indirection(p) NAME(T). {
 var = init_decl_var(T->text, p, 0);
 var->token = T;
}
decl_var(var) ::= indirection(p) NAME(T) LBRACKET NUMBER(D) RBRACKET. {
 var = init_decl_var(T->text, p+1, atol(D->text));
 var->token = T;
 free(D);
}
decl_vars(vars) ::= decl_var(var). {
 vars = init_decl_vars(var);
}
decl_vars(vars) ::= decl_vars(vars_) COMMA decl_var(var). {
 vars = add_decl_var(vars_, var);
}
decl_arg(arg_) ::= const_decl_type(type) decl_var(var). {
 arg_ = init_decl_arg(type, var);
}
decl_typedef_body(def) ::= const_decl_type(type_) indirection(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
struct_args(args) ::= struct_arg(arg). {
 args = init_decl_args(arg);
}
struct_args(args) ::= struct_args(args_) struct_arg(arg). {
 args = add_decl_arg(args_, arg);
}
struct_arg(arg_) ::= decl_typedef_body_ex(def) EOS. {
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
struct_arg(arg) ::= decl_arg(arg_) struct_layout(layout_) EOS. {
 arg_->layout = layout_;
 arg = arg_;
}
struct_layout(layout) ::= . {
 layout = NULL;
}
struct_layout(layout) ::= COLON COLON LPAREN NUMBER(POS) COMMA NUMBER(SIZ) RPAREN. {
 layout = init_decl_struct_layout(atol(POS->text), atol(SIZ->text));
 free(POS);
 free(SIZ);
}
decl_scalar_type(type_) ::= CHAR(C). {
 type_ = C;
}
decl_scalar_type(type_) ::= SHORT(S) decl_scalar_type_short(s). {
 if (s) {
  type_ = psi_token_cat(2, S, s);
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
  type_ = psi_token_cat(2, L, l);
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
  l = psi_token_cat(2, L, ll);
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
 struct psi_token *T = psi_token_cat(2, U, N);
 type_ = init_decl_type(T->type, T->text);
 type_->token = T;
 free(U);
 free(N);
}
decl_type(type_) ::= SIGNED(S) decl_scalar_type(N). {
 struct psi_token *T = psi_token_cat(2, S, N);
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
decl_type(type_) ::= STRUCT(S) NAME(T). {
 type_ = init_decl_type(S->type, T->text);
 type_->token = T;
 free(S);
}
decl_type(type_) ::= UNION(U) NAME(T). {
 type_ = init_decl_type(U->type, T->text);
 type_->token = T;
 free(U);
}
decl_type(type_) ::= ENUM(E) NAME(T). {
 type_ = init_decl_type(E->type, T->text);
 type_->token = T;
 free(E);
}
decl_type(type_) ::= decl_type_token(T). {
 type_ = init_decl_type(T->type, T->text);
 type_->token = T;
}
const_decl_type(type) ::= decl_type(type_). {
 type = type_;
}
const_decl_type(type) ::= CONST decl_type(type_). {
 type = type_;
}
impl(impl) ::= impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
 impl = init_impl(func, stmts);
}
impl_func(func) ::= FUNCTION reference(r) NSNAME(NAME) impl_args(args) COLON impl_type(type). {
 func = init_impl_func(NAME->text, args, type, r);
 func->token = NAME;
}
impl_def_val(def) ::= impl_def_val_token(T). {
 def = init_impl_def_val(T->type, T->text);
 free(T);
}
impl_var(var) ::= reference(r) DOLLAR_NAME(T). {
 var = init_impl_var(T->text, r);
 var->token = T;
}
impl_arg(arg) ::= impl_type(type) impl_var(var). {
 arg = init_impl_arg(type, var, NULL);
}
impl_arg(arg) ::= impl_type(type) impl_var(var) EQUALS impl_def_val(def). {
 arg = init_impl_arg(type, var, def);
}
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
impl_vararg(va) ::= impl_type(type) reference(r) ELLIPSIS DOLLAR_NAME(T). {
 va = init_impl_arg(type, init_impl_var(T->text, r), NULL);
 free(T);
}
impl_arg_list(args) ::= impl_arg(arg). {
 args = init_impl_args(arg);
}
impl_arg_list(args) ::= impl_arg_list(args_) COMMA impl_arg(arg). {
 args = add_impl_arg(args_, arg);
}
impl_stmts(stmts) ::= impl_stmt(stmt). {
 stmts = init_impl_stmts(stmt);
}
impl_stmts(stmts) ::= impl_stmts(stmts_) impl_stmt(stmt). {
 stmts = add_impl_stmt(stmts_, stmt);
}
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
num_exp(exp) ::= num_exp_token(tok). {
 exp = init_num_exp(tok->type, tok->text);
 exp->token = tok;
}
num_exp(exp) ::= decl_var(var). {
 exp = init_num_exp(PSI_T_NAME, var);
 exp->token = psi_token_copy(var->token);
}
num_exp(exp) ::= num_exp(exp_) num_exp_op_token(operator_) num_exp(operand_). {
 exp_->operator = operator_->type;
 exp_->operand = operand_;
 exp = exp_;
 free(operator_);
}
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
let_calloc(alloc) ::= num_exp(nmemb) COMMA num_exp(size). {
 alloc = init_let_calloc(nmemb, size);
}
let_func(func) ::= let_func_token(T) LPAREN impl_var(var) RPAREN. {
 func = init_let_func(T->type, T->text, var);
 free(T);
}
let_vals(vals) ::= let_val(val). {
 vals = init_let_vals(val);
}
let_vals(vals) ::= let_vals(vals_) COMMA let_val(val). {
 vals = add_let_val(vals_, val);
}
let_func(func) ::= let_func_token(T) LPAREN impl_var(var) COMMA let_vals(vals) RPAREN. {
 func = init_let_func(T->type, T->text, var);
 func->inner = vals;
 free(T);
}
callback_arg_list ::= .
callback_arg_list(args) ::= callback_args(args_). {
 args = args_;
}
callback_args(args) ::= set_value(val). {
 args = init_set_values(val);
}
callback_args(args) ::= callback_args(args_) COMMA set_value(val). {
 args = add_set_value(args_, val);
}
callback_rval(rval) ::= let_func_token(F). {
 rval = F;
}
callback_rval(rval) ::= VOID(V). {
 rval = V;
}
let_val(val) ::= NULL. {
 val = init_let_val(PSI_LET_NULL, NULL);
}
let_val(val) ::= num_exp(exp). {
 val = init_let_val(PSI_LET_NUMEXP, exp);
}
let_val(val) ::= CALLOC LPAREN let_calloc(alloc) RPAREN. {
 val = init_let_val(PSI_LET_CALLOC, alloc);
}
let_val(val) ::= let_func(func_). {
 val = init_let_val(PSI_LET_FUNC, func_);
}
let_val(val) ::= CALLBACK callback_rval(F) LPAREN impl_var(var) LPAREN callback_arg_list(args_) RPAREN RPAREN. {
 val = init_let_val(PSI_LET_CALLBACK, init_let_callback(
  init_let_func(F->type, F->text, var), args_));
 free(F);
}
set_stmt(set) ::= SET impl_var(var) EQUALS set_value(val) EOS. {
 set = init_set_stmt(var, val);
}
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
set_vals(vals) ::= set_value(val). {
 vals = add_inner_set_value(init_set_value(NULL, NULL), val);
}
set_vals(vals) ::= set_vals(vals_) COMMA set_value(val). {
 vals = add_inner_set_value(vals_, val);
}
set_func(func) ::= set_func_token(T). {
 func = init_set_func(T->type, T->text);
 func->token = T;
}
return_stmt(ret) ::= RETURN(T) set_value(val) EOS. {
 ret = init_return_stmt(val);
 ret->token = T;
}
free_stmt(free) ::= FREE free_calls(calls) EOS. {
 free = init_free_stmt(calls);
}
free_calls(calls) ::= free_call(call). {
 calls = init_free_calls(call);
}
free_calls(calls) ::= free_calls(calls_) COMMA free_call(call). {
 calls = add_free_call(calls_, call);
}
free_call(call) ::= NAME(F) LPAREN decl_vars(vars) RPAREN. {
 call = init_free_call(F->text, vars);
 call->token = F;
}
impl_type(type_) ::= impl_type_token(T). {
 type_ = init_impl_type(T->type, T->text);
 free(T);
}
reference(r) ::= . {
 r = 0;
}
reference(r) ::= AMPERSAND. {
 r = 1;
}
indirection(i) ::= .{
 i = 0;
}
indirection(i) ::= pointers(p). {
 i = p;
}
pointers(p) ::= ASTERISK. {
 p = 1;
}
pointers(p) ::= pointers(p_) ASTERISK. {
 p = p_+1;
}
