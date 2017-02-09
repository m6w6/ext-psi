%include {
#include "php_psi_stdinc.h"

#include <assert.h>
#include <stdarg.h>

#include "plist.h"
#include "parser.h"

/* rename lemon symbols, works better than DEF(%name) */
#define ParseAlloc psi_parser_proc_init_ex
#define Parse psi_parser_proc_parse
#define ParseTrace psi_parser_proc_trace
#define ParseFree psi_parser_proc_free_ex

/* fwd decls */
void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));

/* wrappers */
void *psi_parser_proc_init(void)
{
	return ParseAlloc(malloc);
}

void psi_parser_proc_free(void **parser_proc)
{
	if (*parser_proc) {
		ParseFree(*parser_proc, free);
		*parser_proc = NULL;
	}
}

}
%token_prefix PSI_T_
%token_type {struct psi_token *}
%token_destructor {free($$);}
%default_destructor {(void)P;}
%extra_argument {struct psi_parser *P}
%syntax_error { ++P->errors; if (TOKEN && TOKEN->type != PSI_T_EOF) { psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col); } else { psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input"); } }
%token_class const_type_token BOOL INT FLOAT STRING .
%token_class decl_type_token FLOAT DOUBLE INT8 UINT8 INT16 UINT16 INT32 UINT32 INT64 UINT64 NAME .
%token_class impl_def_val_token NULL NUMBER TRUE FALSE QUOTED_STRING .
%token_class number_token NUMBER NSNAME .
%token_class binary_op_token PIPE CARET AMPERSAND LSHIFT RSHIFT PLUS MINUS ASTERISK SLASH MODULO RCHEVR LCHEVR CMP_GE CMP_LE OR AND CMP_EQ CMP_NE .
%token_class unary_op_token TILDE NOT PLUS MINUS .
%token_class let_func_token ZVAL OBJVAL ARRVAL PATHVAL STRLEN STRVAL FLOATVAL INTVAL BOOLVAL COUNT .
%token_class set_func_token TO_OBJECT TO_ARRAY TO_STRING TO_INT TO_FLOAT TO_BOOL ZVAL VOID .
%token_class impl_type_token VOID MIXED BOOL INT FLOAT STRING ARRAY OBJECT CALLABLE .
%token_class assert_stmt_token PRE_ASSERT POST_ASSERT .
%nonassoc NAME.
%right NOT TILDE.
%left AND OR.
%left PIPE.
%left CARET.
%left AMPERSAND.
%left CMP_EQ CMP_NE.
%left LCHEVR CMP_LE RCHEVR CMP_GE.
%left LSHIFT RSHIFT.
%left PLUS MINUS.
%left ASTERISK SLASH MODULO.
%fallback NAME TEMP FREE SET LET RETURN CALLOC CALLBACK ZVAL LIB STRING COUNT.
%type decl_enum {struct psi_decl_enum *}
%destructor decl_enum {psi_decl_enum_free(&$$);}
%type decl_enum_items {struct psi_plist*}
%destructor decl_enum_items {psi_plist_free($$);}
%type decl_enum_item {struct psi_decl_enum_item*}
%destructor decl_enum_item {psi_decl_enum_item_free(&$$);}
%type decl_struct_args_block {struct psi_plist*}
%destructor decl_struct_args_block {psi_plist_free($$);}
%type decl_struct_args {struct psi_plist*}
%destructor decl_struct_args {psi_plist_free($$);}
%type decl_struct {struct psi_decl_struct*}
%destructor decl_struct {psi_decl_struct_free(&$$);}
%type align_and_size {struct psi_layout}
%type decl_union {struct psi_decl_union*}
%destructor decl_union {psi_decl_union_free(&$$);}
%type const_type {struct psi_const_type*}
%destructor const_type {psi_const_type_free(&$$);}
%type constant {struct psi_const*}
%destructor constant {psi_const_free(&$$);}
%type decl_typedef {struct psi_decl_arg*}
%destructor decl_typedef {psi_decl_arg_free(&$$);}
%type decl_typedef_body_ex {struct psi_decl_arg*}
%destructor decl_typedef_body_ex {psi_decl_arg_free(&$$);}
%type decl_typedef_body {struct psi_decl_arg*}
%destructor decl_typedef_body {psi_decl_arg_free(&$$);}
%type decl_typedef_body_fn_args {struct psi_plist*}
%destructor decl_typedef_body_fn_args {psi_plist_free($$);}
%type decl {struct psi_decl*}
%destructor decl {psi_decl_free(&$$);}
%type decl_func {struct psi_decl_arg*}
%destructor decl_func {psi_decl_arg_free(&$$);}
%type decl_abi {struct psi_decl_abi*}
%destructor decl_abi {psi_decl_abi_free(&$$);}
%type decl_var {struct psi_decl_var*}
%destructor decl_var {psi_decl_var_free(&$$);}
%type decl_vars {struct psi_plist*}
%destructor decl_vars {psi_plist_free($$);}
%type decl_arg {struct psi_decl_arg*}
%destructor decl_arg {psi_decl_arg_free(&$$);}
%type decl_args {struct psi_plist*}
%destructor decl_args {psi_plist_free($$);}
%type struct_args {struct psi_plist*}
%destructor struct_args {psi_plist_free($$);}
%type struct_arg {struct psi_decl_arg*}
%destructor struct_arg {psi_decl_arg_free(&$$);}
%type decl_layout {struct psi_layout*}
%destructor decl_layout {psi_layout_free(&$$);}
%type decl_type {struct psi_decl_type*}
%destructor decl_type {psi_decl_type_free(&$$);}
%type const_decl_type {struct psi_decl_type*}
%destructor const_decl_type {psi_decl_type_free(&$$);}
%type impl {struct psi_impl*}
%destructor impl {psi_impl_free(&$$);}
%type impl_func {struct psi_impl_func*}
%destructor impl_func {psi_impl_func_free(&$$);}
%type impl_def_val {struct psi_impl_def_val*}
%destructor impl_def_val {psi_impl_def_val_free(&$$);}
%type impl_var {struct psi_impl_var*}
%destructor impl_var {psi_impl_var_free(&$$);}
%type impl_arg {struct psi_impl_arg*}
%destructor impl_arg {psi_impl_arg_free(&$$);}
%type impl_args {struct psi_plist*}
%destructor impl_args {psi_plist_free($$);}
%type impl_vararg {struct psi_impl_arg*}
%destructor impl_vararg {psi_impl_arg_free(&$$);}
%type impl_stmts {struct psi_plist*}
%destructor impl_stmts {psi_plist_free($$);}
%type impl_stmt {struct psi_token**}
%destructor impl_stmt {psi_impl_stmt_free(&$$);}
%type number {struct psi_number*}
%destructor number {psi_number_free(&$$);}
%type num_exp {struct psi_num_exp*}
%destructor num_exp {psi_num_exp_free(&$$);}
%type let_stmt {struct psi_let_stmt*}
%destructor let_stmt {psi_let_stmt_free(&$$);}
%type let_calloc {struct psi_let_calloc*}
%destructor let_calloc {psi_let_calloc_free(&$$);}
%type let_func {struct psi_let_func*}
%destructor let_func {psi_let_func_free(&$$);}
%type callback_arg_list {struct psi_plist *}
%destructor callback_arg_list {psi_plist_free($$);}
%type callback_args {struct psi_plist *}
%destructor callback_args {psi_plist_free($$);}
%type let_callback {struct psi_let_callback*}
%destructor let_callback {psi_let_callback_free(&$$);}
%type let_exp {struct psi_let_exp*}
%destructor let_exp {psi_let_exp_free(&$$);}
%type let_exps {struct psi_plist*}
%destructor let_exps {psi_plist_free($$);}
%type assert_stmt {struct psi_assert_stmt*}
%destructor assert_stmt {psi_assert_stmt_free(&$$);}
%type set_stmt {struct psi_set_stmt*}
%destructor set_stmt {psi_set_stmt_free(&$$);}
%type set_exp {struct psi_set_exp*}
%destructor set_exp {psi_set_exp_free(&$$);}
%type set_exps {struct psi_plist*}
%destructor set_exps {psi_plist_free($$);}
%type set_func {struct psi_set_func*}
%destructor set_func {psi_set_func_free(&$$);}
%type return_stmt {struct psi_return_stmt*}
%destructor return_stmt {psi_return_stmt_free(&$$);}
%type free_stmt {struct psi_free_stmt*}
%destructor free_stmt {psi_free_stmt_free(&$$);}
%type free_exps {struct psi_plist*}
%destructor free_exps {psi_plist_free($$);}
%type free_exp {struct psi_free_exp*}
%destructor free_exp {psi_free_exp_free(&$$);}
%type impl_type {struct psi_impl_type*}
%destructor impl_type {psi_impl_type_free(&$$);}
%type reference {bool}
%type indirection {unsigned}
%type pointers {unsigned}
file ::= blocks.
blocks ::= block.
blocks ::= blocks block.
block ::= EOF.
block ::= EOS.
block ::= LIB(token) QUOTED_STRING(libname) EOS. {
 if (P->file.ln) {
  P->error(PSI_DATA(P), token, PSI_WARNING, "Extra 'lib %s' statement has no effect", libname->text);
 } else {
  P->file.ln = strndup(libname->text + 1, libname->size - 2);
 }
 free(libname);
 free(token);
}
block ::= decl(decl). {
 if (!P->decls) {
  P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
 }
 P->decls = psi_plist_add(P->decls, &decl);
}
block ::= impl(impl). {
 if (!P->impls) {
  P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
 }
 P->impls = psi_plist_add(P->impls, &impl);
}
block ::= decl_typedef(def). {
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
block ::= constant(constant). {
 if (!P->consts) {
  P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
 }
 P->consts = psi_plist_add(P->consts, &constant);
}
block ::= decl_struct(strct). {
 if (!P->structs) {
  P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
 }
 P->structs = psi_plist_add(P->structs, &strct);
}
block ::= decl_union(u). {
 if (!P->unions) {
  P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
 }
 P->unions = psi_plist_add(P->unions, &u);
}
block ::= decl_enum(e). {
 if (!P->enums) {
  P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
 }
 P->enums = psi_plist_add(P->enums, &e);
}
optional_name(n) ::= . {
 n = NULL;
}
optional_name(n) ::= NAME(N). {
 n = N;
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
decl_enum(e) ::= enum_name(N) LBRACE decl_enum_items(list) RBRACE. {
 e = psi_decl_enum_init(N->text, list);
 e->token = N;
}
decl_enum_items(l) ::= decl_enum_item(i). {
 l = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
   &i);
}
decl_enum_items(l) ::= decl_enum_items(l_) COMMA decl_enum_item(i). {
 l = psi_plist_add(l_, &i);
}
decl_enum_item(i) ::= NAME(N) EQUALS num_exp(num). {
 i = psi_decl_enum_item_init(N->text, num);
 i->token = N;
}
decl_enum_item(i) ::= NAME(N). {
 i = psi_decl_enum_item_init(N->text, NULL);
 i->token = N;
}
decl_struct_args_block(args_) ::= LBRACE struct_args(args) RBRACE. {
 args_ = args;
}
decl_struct_args(args_) ::= decl_struct_args_block(args). {
 args_ = args;
}
decl_struct_args(args_) ::= EOS. {
 args_ = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}
decl_struct(strct) ::= STRUCT NAME(N) align_and_size(as) decl_struct_args(args). {
 strct = psi_decl_struct_init(N->text, args);
 strct->align = as.pos;
 strct->size = as.len;
 strct->token = N;
}
decl_union(u) ::= UNION NAME(N) align_and_size(as) decl_struct_args(args). {
 u = psi_decl_union_init(N->text, args);
 u->align = as.pos;
 u->size = as.len;
 u->token = N;
}
const_type(type_) ::= const_type_token(T). {
 type_ = psi_const_type_init(T->type, T->text);
 free(T);
}
constant(constant) ::= CONST const_type(type) NSNAME(T) EQUALS impl_def_val(val) EOS. {
 constant = psi_const_init(type, T->text, val);
 constant->token = T;
}
decl_typedef(def) ::= TYPEDEF(T) decl_typedef_body(def_) EOS. {
 def = def_;
 def->token = T;
}
decl_typedef_body_ex(def) ::= struct_name(N) align_and_size(as) decl_struct_args_block(args) decl_var(var). {
 def = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, N->text), var);
 def->type->token = psi_token_copy(N);
 def->type->real.strct = psi_decl_struct_init(N->text, args);
 def->type->real.strct->token = N;
 def->type->real.strct->align = as.pos;
 def->type->real.strct->size = as.len;
}
decl_typedef_body_ex(def) ::= union_name(N) align_and_size(as) decl_struct_args_block(args) decl_var(var). {
 def = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, N->text), var);
 def->type->token = psi_token_copy(N);
 def->type->real.unn = psi_decl_union_init(N->text, args);
 def->type->real.unn->token = N;
 def->type->real.unn->align = as.pos;
 def->type->real.unn->size = as.len;
}
decl_typedef_body_ex(def) ::= decl_enum(e) NAME(ALIAS). {
 def = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, e->name), psi_decl_var_init(ALIAS->text, 0, 0));
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
 def = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, func_->var->name), psi_decl_var_copy(func_->var));
 def->type->token = psi_token_copy(func_->token);
 def->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, args);
}
decl_typedef_body(def) ::= decl_arg(arg). {
 def = arg;
}
decl(decl) ::= decl_abi(abi) decl_func(func) LPAREN decl_args(args) RPAREN EOS. {
 decl = psi_decl_init(abi, func, args);
}
decl(decl) ::= decl_abi(abi) decl_func(func) LPAREN decl_args(args) COMMA ELLIPSIS RPAREN EOS. {
 decl = psi_decl_init(abi, func, args);
 decl->varargs = 1;
}
decl_func(func) ::= decl_arg(arg). {
 func = arg;
}
decl_func(func) ::= VOID(T) NAME(N). {
 func = psi_decl_arg_init(
  psi_decl_type_init(T->type, T->text),
  psi_decl_var_init(N->text, 0, 0)
 );
 func->type->token = T;
 func->var->token = N;
 func->token = N;
}
decl_typedef_body(def) ::= VOID(T) indirection(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
decl_typedef_body(def) ::= CONST VOID(T) pointers(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
decl_abi(abi) ::= NAME(T). {
 abi = psi_decl_abi_init(T->text);
 abi->token = T;
}
decl_var_array_size(as) ::= . {
 as = NULL;
}
decl_var_array_size(as) ::= LBRACKET NUMBER(D) RBRACKET. {
 as = D;
}
decl_var(var) ::= NAME(T) decl_var_array_size(as). {
 var = psi_decl_var_init(T->text, 0, as?atol(as->text):0);
 var->token = T;
 if (as) {
  free(as);
 }
}
decl_var(var) ::= pointers(p) NAME(T) decl_var_array_size(as). {
 var = psi_decl_var_init(T->text, p+!!as, as?atol(as->text):0);
 var->token = T;
 if (as) {
  free(as);
 }
}
decl_vars(vars) ::= decl_var(var). {
 vars = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
   &var);
}
decl_vars(vars) ::= decl_vars(vars_) COMMA decl_var(var). {
 vars = psi_plist_add(vars_, &var);
}
decl_arg(arg_) ::= const_decl_type(type) decl_var(var). {
 arg_ = psi_decl_arg_init(type, var);
}
decl_typedef_body(def) ::= const_decl_type(type_) indirection(decl_i) LPAREN indirection(type_i) NAME(N) RPAREN decl_typedef_body_fn_args(args). {
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
decl_arg(arg_) ::= VOID(T) pointers(p) NAME(N). {
 arg_ = psi_decl_arg_init(
  psi_decl_type_init(T->type, T->text),
  psi_decl_var_init(N->text, p, 0)
 );
 arg_->type->token = T;
 arg_->var->token = N;
 arg_->token = N;
}
decl_arg(arg_) ::= CONST VOID(T) pointers(p) NAME(N). {
 arg_ = psi_decl_arg_init(
  psi_decl_type_init(T->type, T->text),
  psi_decl_var_init(N->text, p, 0)
 );
 arg_->type->token = T;
 arg_->var->token = N;
 arg_->token = N;
}
decl_args(args) ::= . {
 args = NULL;
}
decl_args(args) ::= VOID. {
 args = NULL;
}
decl_args(args) ::= decl_arg(arg). {
 args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &arg);
}
decl_args(args) ::= decl_args(args_) COMMA decl_arg(arg). {
 args = psi_plist_add(args_, &arg);
}
struct_args(args) ::= struct_arg(arg). {
 args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &arg);
}
struct_args(args) ::= struct_args(args_) struct_arg(arg). {
 args = psi_plist_add(args_, &arg);
}
struct_arg(arg_) ::= decl_typedef_body_ex(def) EOS. {
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
struct_arg(arg) ::= decl_arg(arg_) decl_layout(layout_) EOS. {
 arg_->layout = layout_;
 arg = arg_;
}
decl_layout(layout) ::= . {
 layout = NULL;
}
decl_layout(layout) ::= COLON COLON LPAREN NUMBER(POS) COMMA NUMBER(SIZ) RPAREN. {
 layout = psi_layout_init(atol(POS->text), atol(SIZ->text));
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
 type_ = psi_decl_type_init(T->type, T->text);
 type_->token = T;
 free(U);
 free(N);
}
decl_type(type_) ::= SIGNED(S) decl_scalar_type(N). {
 struct psi_token *T = psi_token_cat(2, S, N);
 type_ = psi_decl_type_init(T->type, T->text);
 type_->token = T;
 free(S);
 free(N);
}
decl_type(type_) ::= UNSIGNED(U). {
 type_ = psi_decl_type_init(PSI_T_NAME, U->text);
 type_->token = U;
}
decl_type(type_) ::= SIGNED(S). {
 type_ = psi_decl_type_init(PSI_T_NAME, S->text);
 type_->token = S;
}
decl_type(type_) ::= decl_scalar_type(N). {
 type_ = psi_decl_type_init(N->type, N->text);
 type_->token = N;
}
decl_type(type_) ::= STRUCT(S) NAME(T). {
 type_ = psi_decl_type_init(S->type, T->text);
 type_->token = T;
 free(S);
}
decl_type(type_) ::= UNION(U) NAME(T). {
 type_ = psi_decl_type_init(U->type, T->text);
 type_->token = T;
 free(U);
}
decl_type(type_) ::= ENUM(E) NAME(T). {
 type_ = psi_decl_type_init(E->type, T->text);
 type_->token = T;
 free(E);
}
decl_type(type_) ::= decl_type_token(T). {
 type_ = psi_decl_type_init(T->type, T->text);
 type_->token = T;
}
const_decl_type(type) ::= decl_type(type_). {
 type = type_;
}
const_decl_type(type) ::= CONST decl_type(type_). {
 type = type_;
}
impl(impl) ::= impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
 impl = psi_impl_init(func, stmts);
}
impl(impl) ::= STATIC impl_func(func) LBRACE impl_stmts(stmts) RBRACE. {
 func->static_memory = 1;
 impl = psi_impl_init(func, stmts);
}
impl_func(func) ::= FUNCTION reference(r) NSNAME(NAME) LPAREN RPAREN COLON impl_type(type). {
 func = psi_impl_func_init(NAME->text, NULL, type);
 func->token = NAME;
 func->return_reference = r;
}
impl_func(func) ::= FUNCTION reference(r) NSNAME(NAME) LPAREN impl_args(args) RPAREN COLON impl_type(type). {
 func = psi_impl_func_init(NAME->text, args, type);
 func->token = NAME;
 func->return_reference = r;
}
impl_func(func) ::= FUNCTION reference(func_r) NSNAME(NAME) LPAREN impl_args(args) COMMA impl_type(va_type) reference(va_r) ELLIPSIS DOLLAR_NAME(T) RPAREN COLON impl_type(func_type). {
 func = psi_impl_func_init(NAME->text, args, func_type);
 func->token = NAME;
 func->return_reference = func_r;
 func->vararg = psi_impl_arg_init(va_type, psi_impl_var_init(T->text, va_r), NULL);
 free(T);
}
impl_def_val(def) ::= impl_def_val_token(T). {
 def = psi_impl_def_val_init(T->type, T->text);
 def->token = T;
}
impl_var(var) ::= reference(r) DOLLAR_NAME(T). {
 var = psi_impl_var_init(T->text, r);
 var->token = T;
}
impl_type(type_) ::= impl_type_token(T). {
 type_ = psi_impl_type_init(T->type, T->text);
 free(T);
}
impl_arg(arg) ::= impl_type(type) impl_var(var). {
 arg = psi_impl_arg_init(type, var, NULL);
}
impl_arg(arg) ::= impl_type(type) impl_var(var) EQUALS impl_def_val(def). {
 arg = psi_impl_arg_init(type, var, def);
}
impl_args(args) ::= impl_arg(arg). {
 args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
   &arg);
}
impl_args(args) ::= impl_args(args_) COMMA impl_arg(arg). {
 args = psi_plist_add(args_, &arg);
}
impl_stmts(stmts) ::= impl_stmt(stmt). {
 stmts = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
   &stmt);
}
impl_stmts(stmts) ::= impl_stmts(stmts_) impl_stmt(stmt). {
 stmts = psi_plist_add(stmts_, &stmt);
}
impl_stmt(i) ::= return_stmt(r). {
 i = (struct psi_token**) r;
}
impl_stmt(i) ::= let_stmt(l). {
 i = (struct psi_token**) l;
}
impl_stmt(i) ::= set_stmt(s). {
 i = (struct psi_token**) s;
}
impl_stmt(i) ::= assert_stmt(s). {
 i = (struct psi_token **) s;
}
impl_stmt(i) ::= free_stmt(f). {
 i = (struct psi_token**) f;
}
number(exp) ::= number_token(tok). {
 exp = psi_number_init(tok->type, tok->text);
 exp->token = tok;
}
number(exp) ::= decl_var(var). {
 exp = psi_number_init(PSI_T_NAME, var);
 exp->token = psi_token_copy(var->token);
}
num_exp(exp) ::= number(num). {
 exp = psi_num_exp_init_num(num);
 exp->token = psi_token_copy(num->token);
}
num_exp(exp) ::= LPAREN(L) num_exp(exp_) RPAREN. {
 exp = psi_num_exp_init_unary(PSI_T_LPAREN, exp_);
 exp->token = L;
}
num_exp(exp) ::= num_exp(lhs_) binary_op_token(OP) num_exp(rhs_). {
 exp = psi_num_exp_init_binary(OP->type, lhs_, rhs_);
 exp->token = OP;
}
num_exp(exp) ::= unary_op_token(OP) num_exp(exp_). {
 exp = psi_num_exp_init_unary(OP->type, exp_);
 exp->token = OP;
}
let_exp(val) ::= NULL. {
 val = psi_let_exp_init(PSI_LET_NULL, NULL);
}
let_exp(val) ::= AMPERSAND NULL. {
 val = psi_let_exp_init(PSI_LET_NULL, NULL);
 val->is_reference = 1;
}
let_exp(val) ::= let_callback(cb). {
 val = psi_let_exp_init(PSI_LET_CALLBACK, cb);
}
let_exp(val) ::= let_calloc(ca). {
 val = psi_let_exp_init(PSI_LET_CALLOC, ca);
}
let_exp(val) ::= AMPERSAND let_calloc(ca). {
 val = psi_let_exp_init(PSI_LET_CALLOC, ca);
 val->is_reference = 1;
}
let_exp(val) ::= let_func(fn). {
 val = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, fn);
}
let_exp(val) ::= AMPERSAND let_func(fn). {
 val = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, fn);
 val->is_reference = 1;
}
let_exp(val) ::= num_exp(exp). {
 val = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, exp);
}
let_exp(val) ::= AMPERSAND num_exp(exp). {
 val = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, exp);
 val->is_reference = 1;
}
let_exp(exp) ::= decl_var(var_) EQUALS let_exp(val). {
 exp = val;
 exp->var = var_;
}
let_stmt(let) ::= LET(T) let_exp(val) EOS. {
 let = psi_let_stmt_init(val);
 let->token = T;
}
let_stmt(let) ::= TEMP(T) decl_var(var) EQUALS reference(r) decl_var(val_) EOS. {
 let = psi_let_stmt_init(psi_let_exp_init_ex(var, PSI_LET_TMP, val_));
 let->token = T;
 let->exp->is_reference = r ? 1 : 0;
}
let_callback(cb) ::= CALLBACK(T) callback_rval(F) LPAREN impl_var(var) LPAREN callback_arg_list(args_) RPAREN RPAREN. {
 cb = psi_let_callback_init(psi_let_func_init(F->type, F->text, var), args_);
 cb->token = T;
 free(F);
}
let_calloc(alloc) ::= CALLOC(T) LPAREN num_exp(nmemb) COMMA num_exp(size) RPAREN. {
 alloc = psi_let_calloc_init(nmemb, size);
 alloc->token = T;
}
let_func(func) ::= let_func_token(T) LPAREN impl_var(var) RPAREN. {
 func = psi_let_func_init(T->type, T->text, var);
 func->token = T;
}
let_func(func) ::= let_func_token(T) LPAREN impl_var(var) COMMA let_exps(vals) RPAREN. {
 func = psi_let_func_init(T->type, T->text, var);
 func->token = T;
 func->inner = vals;
}
let_exps(exps) ::= let_exp(exp). {
 exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
   &exp);
}
let_exps(exps) ::= let_exps(exps_) COMMA let_exp(exp). {
 exps = psi_plist_add(exps_, &exp);
}
callback_arg_list(args) ::= . {
 args = NULL;
}
callback_arg_list(args) ::= callback_args(args_). {
 args = args_;
}
callback_args(args) ::= set_exp(val). {
 args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &val);
}
callback_args(args) ::= callback_args(args_) COMMA set_exp(val). {
 args = psi_plist_add(args_, &val);
}
callback_rval(rval) ::= let_func_token(F). {
 rval = F;
}
callback_rval(rval) ::= VOID(V). {
 rval = V;
}
set_func(func) ::= set_func_token(T) LPAREN decl_var(var) RPAREN. {
 func = psi_set_func_init(T->type, T->text, var);
 func->token = T;
}
set_func(func) ::= set_func_token(T) LPAREN decl_var(var) COMMA set_exps(vals) RPAREN. {
 func = psi_set_func_init(T->type, T->text, var);
 func->token = T;
 func->inner = vals;
}
set_func(func) ::= set_func_token(T) LPAREN decl_var(var) COMMA ELLIPSIS RPAREN. {
 func = psi_set_func_init(T->type, T->text, var);
 func->token = T;
 func->recursive = 1;
}
set_exp(val) ::= set_func(fn). {
 val = psi_set_exp_init(PSI_SET_FUNC, fn);
}
set_exp(val) ::= num_exp(num). {
 val = psi_set_exp_init(PSI_SET_NUMEXP, num);
}
set_exps(exps) ::= set_exp(exp). {
 exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &exp);
}
set_exps(exps) ::= set_exps(exps_) COMMA set_exp(exp). {
 exps = psi_plist_add(exps_, &exp);
}
set_exp(exp) ::= impl_var(var_) EQUALS set_exp(val). {
 exp = val;
 exp->var = var_;
}
set_stmt(set) ::= SET(T) set_exp(exp) EOS. {
 set = psi_set_stmt_init(exp);
 set->token = T;
}
return_stmt(ret) ::= RETURN(T) set_func(func) EOS. {
 ret = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, func));
 ret->token = T;
}
free_stmt(free) ::= FREE(T) free_exps(calls) EOS. {
 free = psi_free_stmt_init(calls);
 free->token = T;
}
free_exps(calls) ::= free_exp(call). {
 calls = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
   &call);
}
free_exps(calls) ::= free_exps(calls_) COMMA free_exp(call). {
 calls = psi_plist_add(calls_, &call);
}
free_exp(call) ::= NAME(F) LPAREN decl_vars(vars) RPAREN. {
 call = psi_free_exp_init(F->text, vars);
 call->token = F;
}
assert_stmt(ass) ::= assert_stmt_token(T) num_exp(exp) EOS. {
 ass = psi_assert_stmt_init(T->type, exp);
 ass->token = T;
}
reference(r) ::= . {
 r = false;
}
reference(r) ::= AMPERSAND. {
 r = true;
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
