%code top {
#include "php_psi_stdinc.h"
}

%code {
#include <assert.h>
#include <stdarg.h>

#include "plist.h"
#include "parser.h"

#define YYDEBUG 1
#define PSI_PARSER_PROC_DEBUG 1

static int psi_parser_proc_lex(YYSTYPE *u, struct psi_parser *P, struct psi_plist *tokens, size_t *index);
static void psi_parser_proc_error(struct psi_parser *P, struct psi_plist *tokens, size_t *index, const char *msg);

static inline void psi_parser_proc_add_struct(struct psi_parser *P, struct psi_decl_struct *strct)
{
	assert(strct);
	if (!P->structs) {
		P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
	}
	P->structs = psi_plist_add(P->structs, &strct);
}
static inline void psi_parser_proc_add_union(struct psi_parser *P, struct psi_decl_union *u)
{
	assert(u);
	if (!P->unions) {
		P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
	}
	P->unions = psi_plist_add(P->unions, &u);
}
static inline void psi_parser_proc_add_enum(struct psi_parser *P, struct psi_decl_enum *e)
{
	assert(e);
	if (!P->enums) {
		P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
	}
	P->enums = psi_plist_add(P->enums, &e);
}
static inline void psi_parser_proc_add_typedef(struct psi_parser *P, struct psi_decl_arg *def)
{
	assert(def);
	if (!P->types) {
		P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	P->types = psi_plist_add(P->types, &def);
}
static inline void psi_parser_proc_add_const(struct psi_parser *P, struct psi_const *cnst) {
	assert(cnst);
	if (!P->consts) {
		P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
	}
	P->consts = psi_plist_add(P->consts, &cnst);

}
static inline void psi_parser_proc_add_decl(struct psi_parser *P, struct psi_decl *decl) {
	assert(decl);

	if (psi_decl_is_blacklisted(decl->func->var->name->val)) {
		psi_decl_free(&decl);
		return;
	}

	if (!P->decls) {
		P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
	}
	P->decls = psi_plist_add(P->decls, &decl);
}
static inline void psi_parser_proc_add_decl_extvars(struct psi_parser *P, struct psi_plist *list) {
	assert(list);
	if (!P->vars) {
		P->vars = psi_plist_init((psi_plist_dtor) psi_decl_extvar_free);
	}
	P->vars = psi_plist_add_r(P->vars, psi_plist_count(list), psi_plist_eles(list));
	free(list);
}
static inline void psi_parser_proc_add_impl(struct psi_parser *P, struct psi_impl *impl) {
	assert(impl);
	if (!P->impls) {
		P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	P->impls = psi_plist_add(P->impls, &impl);
}

/* end code */
}

%code requires {
#include "plist.h"
#include "types/layout.h"

#define yytokentype psi_token_type

#define PSI_T_CAST			PSI_T_EQUALS
#define PSI_T_POINTER		PSI_T_ASTERISK

struct psi_parser;

}

%require "3.0"
%language "c"
%name-prefix "psi_parser_proc_"
%token-table
%verbose
%glr-parser

%param {struct psi_parser *P} {struct psi_plist *tokens} {size_t *index}

%define api.pure true
%define api.token.prefix {PSI_T_}
%define api.value.type union

%define parse.error verbose
%define parse.trace true

%initial-action {
}

%start file

%token <struct psi_token *> BOOL
%token <struct psi_token *> CHAR
%token <struct psi_token *> SHORT
%token <struct psi_token *> INT
%token <struct psi_token *> SIGNED
%token <struct psi_token *> UNSIGNED
%token <struct psi_token *> LONG
%token <struct psi_token *> FLOAT
%token <struct psi_token *> DOUBLE
%token <struct psi_token *> STRING
%token <struct psi_token *> MIXED
%token <struct psi_token *> ARRAY
%token <struct psi_token *> OBJECT
%token <struct psi_token *> CALLABLE
%token <struct psi_token *> VOID
%token <struct psi_token *> ZVAL
%token <struct psi_token *> NULL
%token <struct psi_token *> TRUE
%token <struct psi_token *> FALSE
%token <struct psi_token *> NAME
%token <struct psi_token *> NSNAME
%token <struct psi_token *> DOLLAR_NAME
%token <struct psi_token *> NUMBER
%token <struct psi_token *> QUOTED_STRING
%token <struct psi_token *> QUOTED_CHAR
%token <struct psi_token *> SIZEOF
%token <struct psi_token *> VOLATILE

%token <struct psi_token *> EOF 0		"end of file"
%token <struct psi_token *> EOL			"end of line"
%token <struct psi_token *> EOS			";"
%token <struct psi_token *> LPAREN		"("
%token <struct psi_token *> RPAREN		")"
%token <struct psi_token *> COMMA		","
%token <struct psi_token *> COLON		":"
%token <struct psi_token *> LBRACE		"{"
%token <struct psi_token *> RBRACE		"}"
%token <struct psi_token *> LBRACKET	"["
%token <struct psi_token *> RBRACKET	"]"
%token <struct psi_token *> EQUALS		"="
%token <struct psi_token *> HASH		"#"
%token <struct psi_token *> PIPE		"|"
%token <struct psi_token *> CARET		"^"
%token <struct psi_token *> AMPERSAND	"&"
%token <struct psi_token *> LSHIFT		"<<"
%token <struct psi_token *> RSHIFT		">>"
%token <struct psi_token *> PLUS		"+"
%token <struct psi_token *> MINUS		"-"
%token <struct psi_token *> ASTERISK	"*"
%token <struct psi_token *> SLASH		"/"
%token <struct psi_token *> MODULO		"%"
%token <struct psi_token *> LCHEVR		"<"
%token <struct psi_token *> RCHEVR		">"
%token <struct psi_token *> CMP_GE		">="
%token <struct psi_token *> CMP_LE		"<="
%token <struct psi_token *> OR			"||"
%token <struct psi_token *> AND			"&&"
%token <struct psi_token *> CMP_EQ		"=="
%token <struct psi_token *> CMP_NE		"!="
%token <struct psi_token *> TILDE		"~"
%token <struct psi_token *> NOT			"!"
%token <struct psi_token *> PERIOD		"."
%token <struct psi_token *> BACKSLASH	"\\"
%token <struct psi_token *> ELLIPSIS	"..."
%token <struct psi_token *> IIF			"?"

%token <struct psi_token *> PRAGMA
%token <struct psi_token *> PRAGMA_ONCE
%token <struct psi_token *> LINE
%token <struct psi_token *> ERROR
%token <struct psi_token *> WARNING
%token <struct psi_token *> IF
%token <struct psi_token *> IFDEF
%token <struct psi_token *> IFNDEF
%token <struct psi_token *> ELSE
%token <struct psi_token *> ELIF
%token <struct psi_token *> ENDIF
%token <struct psi_token *> DEFINE
%token <struct psi_token *> DEFINED
%token <struct psi_token *> UNDEF
%token <struct psi_token *> IMPORT
%token <struct psi_token *> INCLUDE
%token <struct psi_token *> INCLUDE_NEXT

%token <struct psi_token *> TYPEDEF
%token <struct psi_token *> STRUCT
%token <struct psi_token *> UNION
%token <struct psi_token *> ENUM
%token <struct psi_token *> CONST
%token <struct psi_token *> LIB
%token <struct psi_token *> STATIC
%token <struct psi_token *> CALLBACK
%token <struct psi_token *> FUNCTION
%token <struct psi_token *> LET
%token <struct psi_token *> SET
%token <struct psi_token *> TEMP
%token <struct psi_token *> FREE
%token <struct psi_token *> RETURN
%token <struct psi_token *> AS
%token <struct psi_token *> PRE_ASSERT
%token <struct psi_token *> POST_ASSERT
%token <struct psi_token *> BOOLVAL
%token <struct psi_token *> INTVAL
%token <struct psi_token *> STRVAL
%token <struct psi_token *> PATHVAL
%token <struct psi_token *> STRLEN
%token <struct psi_token *> FLOATVAL
%token <struct psi_token *> ARRVAL
%token <struct psi_token *> OBJVAL
%token <struct psi_token *> COUNT
%token <struct psi_token *> CALLOC
%token <struct psi_token *> TO_BOOL
%token <struct psi_token *> TO_INT
%token <struct psi_token *> TO_STRING
%token <struct psi_token *> TO_FLOAT
%token <struct psi_token *> TO_ARRAY
%token <struct psi_token *> TO_OBJECT

%token <struct psi_token *> COMMENT
%token <struct psi_token *> WHITESPACE
%token <struct psi_token *> NO_WHITESPACE
%token <struct psi_token *> CPP_HEADER
%token <struct psi_token *> CPP_ATTRIBUTE
%token <struct psi_token *> CPP_EXTENSION
%token <struct psi_token *> CPP_PASTE
%token <struct psi_token *> CPP_INLINE
%token <struct psi_token *> CPP_RESTRICT
%token <struct psi_token *> CPP_ASM

/* virtual tokens */
%token <struct psi_token *> BSLASH
%token <struct psi_token *> LONG_DOUBLE
%token <struct psi_token *> INT8
%token <struct psi_token *> UINT8
%token <struct psi_token *> INT16
%token <struct psi_token *> UINT16
%token <struct psi_token *> INT32
%token <struct psi_token *> UINT32
%token <struct psi_token *> INT64
%token <struct psi_token *> UINT64
%token <struct psi_token *> INT128
%token <struct psi_token *> UINT128


%precedence IIF COLON
%precedence OR
%precedence AND
%precedence PIPE
%precedence CARET
%precedence AMPERSAND
%precedence CMP_EQ CMP_NE
%precedence LCHEVR CMP_LE RCHEVR CMP_GE
%precedence LSHIFT RSHIFT
%precedence PLUS MINUS
%precedence ASTERISK SLASH MODULO
//%precedence NOT TILDE
%precedence BINARY
%precedence UNARY

%type		<struct psi_token *>				lib optional_name enum_name struct_name union_name
%destructor	{psi_token_free(&$$);}				lib optional_name enum_name struct_name union_name

%type		<struct psi_token *>				cpp_message_token cpp_include_token cpp_header_token cpp_no_arg_token cpp_name_arg_token cpp_exp_arg_token
%destructor	{}									cpp_message_token cpp_include_token cpp_header_token cpp_no_arg_token cpp_name_arg_token cpp_exp_arg_token

%type		<struct psi_token *>				name_token any_noeol_token binary_op_token unary_op_token
%destructor	{}									name_token any_noeol_token binary_op_token unary_op_token

%type		<struct psi_token *>				int_width int_width_types int_signed_types
%destructor	{psi_token_free(&$$);}				int_width int_width_types int_signed_types

%type		<struct psi_token *>				signed_long_types signed_short_types int_signed
%destructor	{}									signed_long_types signed_short_types int_signed

%type		<struct psi_cpp_exp *>				cpp cpp_exp
%destructor	{psi_cpp_exp_free(&$$);}			cpp cpp_exp
%type		<struct psi_cpp_macro_decl *> 		cpp_macro_decl
%destructor	{psi_cpp_macro_decl_free(&$$);}		cpp_macro_decl
%type		<struct psi_plist *>				cpp_macro_sig cpp_macro_sig_args cpp_macro_decl_tokens cpp_macro_decl_token_list cpp_macro_call_args cpp_macro_call_arg_list
%destructor {psi_plist_free($$);}				cpp_macro_sig cpp_macro_sig_args cpp_macro_decl_tokens cpp_macro_decl_token_list cpp_macro_call_args cpp_macro_call_arg_list
%type		<struct psi_num_exp *>				cpp_macro_exp
%destructor	{psi_num_exp_free(&$$);}			cpp_macro_exp

%type		<struct psi_token *>				impl_def_val_token
%destructor	{}									impl_def_val_token

%type		<struct psi_const *>				constant
%destructor	{psi_const_free(&$$);}				constant
%type		<struct psi_impl_def_val *>			impl_def_val
%destructor	{psi_impl_def_val_free(&$$);}		impl_def_val

%type		<struct psi_token *>				decl_real_type decl_int_type decl_type_simple
%destructor	{psi_token_free(&$$);}				decl_real_type decl_int_type decl_type_simple

%type		<struct psi_token *>				decl_asm quoted_strings
%destructor	{psi_token_free(&$$);}				decl_asm quoted_strings

%type		<struct psi_decl_type *>			decl_type qualified_decl_type decl_type_complex
%destructor	{psi_decl_type_free(&$$);}			decl_type qualified_decl_type decl_type_complex
%type		<struct psi_decl *>					decl_stmt decl decl_body decl_func_body decl_functor_body decl_anon_functor_body ignored_decl
%destructor	{psi_decl_free(&$$);}				decl_stmt decl decl_body decl_func_body decl_functor_body decl_anon_functor_body ignored_decl
%type		<struct psi_decl_arg *>				decl_typedef decl_func decl_functor decl_anon_functor decl_arg decl_anon_arg typedef typedef_decl typedef_anon typedef_anon_decl
%destructor	{psi_decl_arg_free(&$$);}			decl_typedef decl_func decl_functor decl_anon_functor decl_arg decl_anon_arg typedef typedef_decl typedef_anon typedef_anon_decl
%type		<struct psi_decl_var *>				decl_var
%destructor	{psi_decl_var_free(&$$);}			decl_var
%type		<struct psi_decl_struct *>			decl_struct
%destructor	{psi_decl_struct_free(&$$);}		decl_struct
%type		<struct psi_decl_union *>			decl_union
%destructor	{psi_decl_union_free(&$$);}			decl_union
%type		<struct psi_decl_enum *>			decl_enum
%destructor	{psi_decl_enum_free(&$$);}			decl_enum
%type		<struct psi_decl_enum_item *>		decl_enum_item
%destructor	{psi_decl_enum_item_free(&$$);}		decl_enum_item
%type		<struct psi_plist *>				decl_args decl_arg_list decl_struct_args struct_args_block struct_args struct_arg_var_list decl_enum_items decl_vars decl_vars_with_layout call_decl_vars decl_extvar_stmt decl_extvar_list
%destructor	{psi_plist_free($$);}				decl_args decl_arg_list decl_struct_args struct_args_block struct_args struct_arg_var_list decl_enum_items decl_vars decl_vars_with_layout call_decl_vars decl_extvar_stmt decl_extvar_list

%type		<struct psi_layout>					align_and_size
%destructor	{}									align_and_size
%type		<struct psi_layout *>				decl_layout
%destructor	{psi_layout_free(&$$);}				decl_layout

%type		<struct psi_number *>				sizeof sizeof_body sizeof_body_notypes
%destructor	{psi_number_free(&$$);}				sizeof sizeof_body sizeof_body_notypes

%type		<struct psi_impl *>					impl
%destructor	{psi_impl_free(&$$);}				impl
%type		<struct psi_impl_func *>			impl_func
%destructor	{psi_impl_func_free(&$$);}			impl_func
%type		<struct psi_impl_arg *>				impl_arg
%destructor	{psi_impl_arg_free(&$$);}			impl_arg
%type		<struct psi_impl_type *>			impl_type impl_type_restricted
%destructor	{psi_impl_type_free(&$$);}			impl_type impl_type_restricted
%type		<struct psi_impl_var *>				impl_var
%destructor	{psi_impl_var_free(&$$);}			impl_var

%type		<struct psi_let_stmt *>				let_stmt
%destructor	{psi_let_stmt_free(&$$);}			let_stmt
%type		<struct psi_let_exp *>				let_exp let_exp_byref let_exp_assign
%destructor	{psi_let_exp_free(&$$);}			let_exp let_exp_byref let_exp_assign
%type		<struct psi_let_calloc *>			let_calloc
%destructor	{psi_let_calloc_free(&$$);}			let_calloc
%type		<struct psi_let_callback *>			let_callback
%destructor	{psi_let_callback_free(&$$);}		let_callback
%type		<struct psi_let_func *>				let_func
%destructor	{psi_let_func_free(&$$);}			let_func
%type		<struct psi_set_stmt *>				set_stmt
%destructor	{psi_set_stmt_free(&$$);}			set_stmt
%type		<struct psi_set_exp *>				set_exp
%destructor	{psi_set_exp_free(&$$);}			set_exp
%type		<struct psi_set_func *>				set_func
%destructor	{psi_set_func_free(&$$);}			set_func
%type		<struct psi_assert_stmt *>			assert_stmt
%destructor	{psi_assert_stmt_free(&$$);}		assert_stmt
%type		<struct psi_return_stmt *>			return_stmt
%destructor	{psi_return_stmt_free(&$$);}		return_stmt
%type		<struct psi_return_exp *>			return_exp
%destructor	{psi_return_exp_free(&$$);}			return_exp
%type		<struct psi_free_stmt *>			free_stmt
%destructor	{psi_free_stmt_free(&$$);}			free_stmt
%type		<struct psi_free_exp *>				free_exp
%destructor	{psi_free_exp_free(&$$);}			free_exp

%type		<struct psi_token **>				impl_stmt
%destructor	{psi_impl_stmt_free(&$$);}			impl_stmt
%type		<struct psi_token *>				impl_type_token impl_type_restricted_token impl_type_extended_token callback_rval let_func_token set_func_token assert_stmt_token
%destructor	{psi_token_free(&$$);}				impl_type_token impl_type_restricted_token impl_type_extended_token callback_rval let_func_token set_func_token assert_stmt_token
%type		<struct psi_plist *>				impl_args impl_stmts let_exps let_func_exps callback_arg_list callback_args set_exps set_func_exps free_exps
%destructor	{psi_plist_free($$);}				impl_args impl_stmts let_exps let_func_exps callback_arg_list callback_args set_exps set_func_exps free_exps

%type		<struct psi_num_exp *>				num_exp
%destructor	{psi_num_exp_free(&$$);}			num_exp
%type		<struct psi_number *>				number
%destructor	{psi_number_free(&$$);}				number

%type		<size_t>							indirection pointers asterisks array_size
%destructor	{}									indirection pointers asterisks array_size
%type		<bool>								reference
%destructor	{}									reference

%%

/* rules */


binary_op_token: PIPE | CARET | AMPERSAND | LSHIFT | RSHIFT | PLUS | MINUS | ASTERISK | SLASH | MODULO | RCHEVR | LCHEVR | CMP_GE | CMP_LE | OR | AND | CMP_EQ | CMP_NE ;
unary_op_token: TILDE | NOT | PLUS | MINUS ;
name_token: NAME | FUNCTION | TEMP | FREE | SET | LET | CALLOC | CALLBACK | LIB | BOOL | STRING | MIXED | ARRAY | OBJECT | ERROR | WARNING | LINE | PRAGMA_ONCE | PRAGMA | AS | let_func_token | set_func_token;
any_noeol_token: BOOL | CHAR | SHORT | INT | SIGNED | UNSIGNED | LONG | FLOAT | DOUBLE | STRING | MIXED | ARRAY | OBJECT | CALLABLE | VOID | ZVAL | NULL | TRUE | FALSE | NAME | NSNAME | DOLLAR_NAME | NUMBER | QUOTED_STRING | QUOTED_CHAR | EOF | EOS | LPAREN | RPAREN | COMMA | COLON | LBRACE | RBRACE | LBRACKET | RBRACKET | EQUALS | HASH | PIPE | CARET | AMPERSAND | LSHIFT | RSHIFT | PLUS | MINUS | ASTERISK | SLASH | MODULO | LCHEVR | RCHEVR | CMP_GE | CMP_LE | OR | AND | CMP_EQ | CMP_NE | TILDE | NOT | PERIOD | BACKSLASH | ELLIPSIS | ERROR | WARNING | LINE | PRAGMA | PRAGMA_ONCE | IIF | IF | IFDEF | IFNDEF | ELSE | ELIF | ENDIF | DEFINE | DEFINED | UNDEF | INCLUDE | TYPEDEF | STRUCT | UNION | ENUM | CONST | LIB | STATIC | CALLBACK | FUNCTION | LET | SET | TEMP | FREE | RETURN | PRE_ASSERT | POST_ASSERT | BOOLVAL | INTVAL | STRVAL | PATHVAL | STRLEN | FLOATVAL | ARRVAL | OBJVAL | COUNT | CALLOC | TO_BOOL | TO_INT | TO_STRING | TO_FLOAT | TO_ARRAY | TO_OBJECT | COMMENT | CPP_HEADER | CPP_PASTE | CPP_INLINE | CPP_RESTRICT | CPP_EXTENSION | CPP_ASM | SIZEOF | VOLATILE | AS;
any_nobrace_token: BOOL | CHAR | SHORT | INT | SIGNED | UNSIGNED | LONG | FLOAT | DOUBLE | STRING | MIXED | ARRAY | OBJECT | CALLABLE | VOID | ZVAL | NULL | TRUE | FALSE | NAME | NSNAME | DOLLAR_NAME | NUMBER | QUOTED_STRING | QUOTED_CHAR | EOF | EOS | LPAREN | RPAREN | COMMA | COLON | LBRACKET | RBRACKET | EQUALS | HASH | PIPE | CARET | AMPERSAND | LSHIFT | RSHIFT | PLUS | MINUS | ASTERISK | SLASH | MODULO | LCHEVR | RCHEVR | CMP_GE | CMP_LE | OR | AND | CMP_EQ | CMP_NE | TILDE | NOT | PERIOD | BACKSLASH | ELLIPSIS | ERROR | WARNING | LINE | PRAGMA | PRAGMA_ONCE | IIF | IF | IFDEF | IFNDEF | ELSE | ELIF | ENDIF | DEFINE | DEFINED | UNDEF | INCLUDE | TYPEDEF | STRUCT | UNION | ENUM | CONST | LIB | STATIC | CALLBACK | FUNCTION | LET | SET | TEMP | FREE | RETURN | PRE_ASSERT | POST_ASSERT | BOOLVAL | INTVAL | STRVAL | PATHVAL | STRLEN | FLOATVAL | ARRVAL | OBJVAL | COUNT | CALLOC | TO_BOOL | TO_INT | TO_STRING | TO_FLOAT | TO_ARRAY | TO_OBJECT | COMMENT | CPP_HEADER | CPP_PASTE | CPP_INLINE | CPP_RESTRICT | CPP_EXTENSION | CPP_ASM | SIZEOF | VOLATILE | AS;


file:
	%empty
|	blocks
;
blocks:
	block
|	blocks block
;
block:
	EOS
|	EOL
|	COMMENT
|	cpp {
	if ($cpp) {
		psi_cpp_exp_exec($cpp, P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&$cpp);
	}
}
|	lib {
	char *libname = strdup($lib->text->val);
	P->file.libnames = psi_plist_add(P->file.libnames, &libname);
}
|	constant {
	psi_parser_proc_add_const(P, $constant);
}
|	decl_stmt {
	psi_parser_proc_add_decl(P, $decl_stmt);
}
|	decl_extvar_stmt[list] {
	psi_parser_proc_add_decl_extvars(P, $list);
}
|	ignored_decl {
	if (P->flags & PSI_DEBUG) {
		P->error(PSI_DATA(P), $ignored_decl->func->token, PSI_NOTICE, "Ignored decl: %s", $ignored_decl->func->var->name->val);
	}
	psi_decl_free(&$ignored_decl);
}
|	decl_typedef[def] {
	psi_parser_proc_add_typedef(P, $def);
}
|	decl_struct[struct] {
	psi_parser_proc_add_struct(P, $struct);
}
|	decl_union[union] {
	psi_parser_proc_add_union(P, $union);
}
|	decl_enum[enum] {
	psi_parser_proc_add_enum(P, $enum);
}
|	impl {
	psi_parser_proc_add_impl(P, $impl);
}
;

lib:
	LIB QUOTED_STRING EOS {
	$lib = $QUOTED_STRING;
}
;

cpp:
	HASH EOL {
	$cpp = NULL;
}
|	HASH cpp_exp[exp] EOL {
	$cpp = $exp;
}
;

cpp_exp[exp]:
	cpp_message_token cpp_macro_decl_tokens[tokens] {
	if ($tokens) {
		struct psi_token *msg = NULL;

		if (psi_plist_get($tokens, 0, &msg)) {
			size_t index = 1;
			struct psi_token *next;

			msg = psi_token_copy(msg);
			while (psi_plist_get($tokens, index++, &next)) {
				struct psi_token *old = msg;
				msg = psi_token_cat(" ", 2, msg, next);
				psi_token_free(&old);
			}
		}
		psi_plist_free($tokens);

		$exp = psi_cpp_exp_init($cpp_message_token->type, msg);
	} else {
		$exp = psi_cpp_exp_init($cpp_message_token->type, NULL);
	}
	$exp->token = psi_token_copy($cpp_message_token);
}
|	cpp_include_token[INCLUDE] cpp_header_token {
	$exp = psi_cpp_exp_init($INCLUDE->type, psi_token_copy($cpp_header_token));
	$exp->token = psi_token_copy($INCLUDE);
}
|	cpp_no_arg_token {
	$exp = psi_cpp_exp_init($cpp_no_arg_token->type, NULL);
	$exp->token = psi_token_copy($cpp_no_arg_token);
}
|	cpp_name_arg_token any_noeol_token[name_token] {
	$name_token->type = PSI_T_NAME;
	$exp = psi_cpp_exp_init($cpp_name_arg_token->type, psi_token_copy($name_token));
	$exp->token = psi_token_copy($cpp_name_arg_token);
}
|	DEFINE cpp_macro_decl {
	$exp = psi_cpp_exp_init($DEFINE->type, $cpp_macro_decl);
	$exp->token = psi_token_copy($DEFINE);
}
|	cpp_exp_arg_token cpp_macro_exp {
	$exp = psi_cpp_exp_init($cpp_exp_arg_token->type, $cpp_macro_exp);
	$exp->token = psi_token_copy($cpp_exp_arg_token);
}
| 	PRAGMA_ONCE {
	$exp = psi_cpp_exp_init($PRAGMA_ONCE->type, NULL);
	$exp->token = psi_token_copy($PRAGMA_ONCE);
}
|	cpp_ignored_token cpp_macro_decl_tokens[tokens] {
	psi_plist_free($tokens);
	$exp = NULL;
}
;

cpp_ignored_token:
	LINE
|	PRAGMA
;

cpp_message_token:
	ERROR
|	WARNING
;

cpp_include_token:
	IMPORT
|	INCLUDE
|	INCLUDE_NEXT
;

cpp_header_token:
	QUOTED_STRING
|	CPP_HEADER
;

cpp_no_arg_token:
	ELSE
|	ENDIF
;

cpp_name_arg_token:
	IFDEF
|	IFNDEF
|	UNDEF
;

cpp_exp_arg_token:
	IF
|	ELIF
;

cpp_macro_decl[macro]:
	any_noeol_token[name_token] cpp_macro_decl_tokens %dprec 1 {
	$name_token->type = PSI_T_NAME;
	$macro = psi_cpp_macro_decl_init(NULL, $cpp_macro_decl_tokens, NULL);
	$macro->token = psi_token_copy($name_token);
}
|	name_token NO_WHITESPACE LPAREN cpp_macro_sig RPAREN cpp_macro_decl_tokens %dprec 2 {
	$name_token->type = PSI_T_NAME;
	$macro = psi_cpp_macro_decl_init($cpp_macro_sig, $cpp_macro_decl_tokens, NULL);
	$macro->token = psi_token_copy($name_token);
}
|	name_token cpp_macro_exp[num_exp] %dprec 2 {
	$name_token->type = PSI_T_NAME;
	$macro = psi_cpp_macro_decl_init(NULL, psi_num_exp_tokens($num_exp, NULL), $num_exp);
	$macro->token = psi_token_copy($name_token);
}
|	name_token quoted_strings[strings] %dprec 2 {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_token_free);
	$name_token->type = PSI_T_NAME;
	$macro = psi_cpp_macro_decl_init(NULL, psi_plist_add(list, &$strings), NULL);
	$macro->token = psi_token_copy($name_token);
}
;

cpp_macro_sig[sig]:
	%empty {
	$sig = psi_plist_init(NULL);
}
|	ELLIPSIS {
	$sig = psi_plist_init(NULL); /* FIXME */
}
|	cpp_macro_sig_args
|	cpp_macro_sig_args[args] COMMA ELLIPSIS {
	$sig = $args;
}
;

cpp_macro_sig_args[args]:
	name_token {
	$name_token = psi_token_copy($name_token);
	$name_token->type = PSI_T_NAME;
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &$name_token);
}
|	cpp_macro_sig_args[args_] COMMA name_token {
	$name_token = psi_token_copy($name_token);
	$name_token->type = PSI_T_NAME;
	$args = psi_plist_add($args_, &$name_token);
}
;

cpp_macro_decl_tokens[tokens]:
	%empty {
	$tokens = NULL;
}
| cpp_macro_decl_token_list
;

cpp_macro_decl_token_list[tokens]:
	any_noeol_token[token] {
	$token = psi_token_copy($token);
	$tokens = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &$token);
}
|	cpp_macro_decl_token_list[tokens_] any_noeol_token[token] {
	$token = psi_token_copy($token);
	$tokens = psi_plist_add($tokens_, &$token);
}
;

cpp_macro_exp[exp]:
	LPAREN cpp_macro_exp[exp_] RPAREN {
	$exp = psi_num_exp_init_unary($LPAREN->type, $exp_);
	$exp->token = psi_token_copy($LPAREN);
}
|	unary_op_token cpp_macro_exp[exp_] %prec UNARY {
	$exp = psi_num_exp_init_unary($unary_op_token->type, $exp_);
	$exp->token = psi_token_copy($unary_op_token);
}
|	cpp_macro_exp[lhs] binary_op_token cpp_macro_exp[rhs] %prec BINARY {
	$exp = psi_num_exp_init_binary($binary_op_token->type, $lhs, $rhs);
	$exp->token = psi_token_copy($binary_op_token);
}
|	cpp_macro_exp[cond] IIF cpp_macro_exp[truthy] COLON cpp_macro_exp[falsy] {
	$exp = psi_num_exp_init_ternary($IIF->type, $cond, $truthy, $falsy);
	$exp->token = psi_token_copy($IIF);
}

|	DEFINED name_token {
	{
		uint8_t exists;

		$name_token->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, $name_token);
		$exp = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINED, &exists, 0));
		$exp->token = psi_token_copy($DEFINED);
		$exp->data.n->token = psi_token_copy($name_token);
	}
}
|	DEFINED LPAREN name_token RPAREN {
	{
		uint8_t exists;

		$name_token->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, $name_token);
		$exp = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINED, &exists, 0));
		$exp->token = psi_token_copy($DEFINED);
		$exp->data.n->token = psi_token_copy($name_token);
	}
}
|	NUMBER {
	$exp = psi_num_exp_init_num(psi_number_init($NUMBER->type, $NUMBER->text, $NUMBER->flags));
	$exp->token = psi_token_copy($NUMBER);
	$exp->data.n->token = psi_token_copy($NUMBER);
}
|	QUOTED_CHAR {
	$exp = psi_num_exp_init_num(psi_number_init($QUOTED_CHAR->type, $QUOTED_CHAR->text, 0));
	$exp->token = psi_token_copy($QUOTED_CHAR);
	$exp->data.n->token = psi_token_copy($QUOTED_CHAR);
}
|	sizeof {
	$exp = psi_num_exp_init_num($sizeof);
	$exp->token = psi_token_copy($sizeof->token);
}
|	name_token {
	$name_token->type = PSI_T_NAME;
	$exp = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, $name_token->text, 0));
	$exp->token = psi_token_copy($name_token);
	$exp->data.n->token = psi_token_copy($name_token);
}
|	name_token LPAREN cpp_macro_call_args RPAREN {
	$name_token->type = PSI_T_NAME;
	$exp = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init($name_token->text, $cpp_macro_call_args), 0));
	$exp->token = psi_token_copy($name_token);
	$exp->data.n->token = psi_token_copy($name_token);
	$exp->data.n->data.call->token = psi_token_copy($name_token);
}
;

cpp_macro_call_args[args]:
	%empty {
	$args = NULL;
}
|	cpp_macro_call_arg_list
;

cpp_macro_call_arg_list[args]:
	CPP_HEADER {
	/* TODO: clang include test macros */
	uint8_t no = 1;
	struct psi_num_exp *exp = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &no, 0));
	exp->token = psi_token_copy($CPP_HEADER);
	exp->data.n->token = psi_token_copy($CPP_HEADER);
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free), &exp);
}
|	cpp_macro_exp {
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free),
		&$cpp_macro_exp);
}
|	cpp_macro_call_arg_list[args_] COMMA cpp_macro_exp {
	$args = psi_plist_add($args_, &$cpp_macro_exp);
}
;

constant[const]:
	CONST impl_type_restricted[type] NSNAME EQUALS impl_def_val EOS {
	$const = psi_const_init($type, $NSNAME->text, $impl_def_val);
	$const->token = psi_token_copy($NSNAME);
}
|	CONST NSNAME EQUALS impl_def_val EOS {
	$const = psi_const_init(NULL, $NSNAME->text, $impl_def_val);
	$const->token = psi_token_copy($NSNAME);
}
;

impl_def_val[val]:
	impl_def_val_token[token] %dprec 2 {
	$val = psi_impl_def_val_init($token->type, $token->text);
	$val->token = psi_token_copy($token);
}
|	num_exp[num] %dprec 1 {
	$val = psi_impl_def_val_init(PSI_T_NUMBER, $num);
	$val->token = psi_token_copy($num->token);
}
|	quoted_strings[token] {
	$val = psi_impl_def_val_init($token->type, $token->text);
	$val->token = $token;
}
;

impl_def_val_token:
	NULL
|	TRUE
|	FALSE
;

decl_typedef[def]:
	TYPEDEF typedef[def_] EOS {
	$def = $def_;
}
/*
|	TYPEDEF VOID name_token EOS {
	$def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_VOID, $VOID->text),
		psi_decl_var_init($name_token->text, 0, 0)
	);
	$def->token = psi_token_copy($VOID);
	$def->type->token = psi_token_copy($VOID);
	$def->var->token = psi_token_copy($name_token);
}
*/
|	CPP_EXTENSION TYPEDEF typedef[def_] EOS {
	$def = $def_;
}
;

typedef[def]:
	typedef_decl {
	$def = $typedef_decl;
}
|	CPP_EXTENSION typedef_decl {
	$def = $typedef_decl;
}
;

typedef_anon[def]:
	typedef_anon_decl {
	$def = $typedef_anon_decl;
}
|	CPP_EXTENSION typedef_anon_decl {
	$def = $typedef_anon_decl;
}
;

typedef_decl[def]:
	decl_arg
|	decl_func_body[decl] {
	$def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, $decl->func->var->name),
		psi_decl_var_copy($decl->func->var)
	);
	$def->type->token = psi_token_copy($decl->func->token);
	$def->type->real.func = $decl;
}
|	decl_enum[enum] name_token {
	$name_token->type = PSI_T_NAME;
	$def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_ENUM, $enum->name),
		psi_decl_var_init($name_token->text, 0, 0)
	);
	$def->var->token = psi_token_copy($name_token);
	$def->type->token = psi_token_copy($enum->token);
	$def->type->real.enm = $enum;
	psi_parser_proc_add_enum(P, $enum);
}
|	struct_name[struct] align_and_size[as] struct_args_block[args] decl_var[var] {
	$def = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, $struct->text), $var);
	$def->type->token = $struct;
	$def->type->real.strct = psi_decl_struct_init($struct->text, $args);
	$def->type->real.strct->token = psi_token_copy($struct);
	$def->type->real.strct->align = $as.pos;
	$def->type->real.strct->size = $as.len;
	psi_parser_proc_add_struct(P, $def->type->real.strct);
}
|	union_name[union] align_and_size[as] struct_args_block[args] decl_var[var] {
	$def = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, $union->text), $var);
	$def->type->token = $union;
	$def->type->real.unn = psi_decl_union_init($union->text, $args);
	$def->type->real.unn->token = psi_token_copy($union);
	$def->type->real.unn->align = $as.pos;
	$def->type->real.unn->size = $as.len;
	psi_parser_proc_add_union(P, $def->type->real.unn);
}
;

typedef_anon_decl[def]:
	typedef_decl %dprec 2
|	qualified_decl_type[type] %dprec 1 {
	$def = psi_decl_arg_init($type, psi_decl_var_init(NULL, 0, 0));
	$def->var->token = psi_token_copy($type->token);
}
|	decl_enum[enum] {
	$def = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_ENUM, $enum->name),
		psi_decl_var_init(NULL, 0, 0)
	);
	$def->var->token = psi_token_copy($enum->token);
	$def->type->token = psi_token_copy($enum->token);
	$def->type->real.enm = $enum;
	psi_parser_proc_add_enum(P, $enum);
}
|	struct_name[struct] align_and_size[as] struct_args_block[args] {
	$def = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, $struct->text), psi_decl_var_init(NULL, 0, 0));
	$def->type->token = $struct;
	$def->type->real.strct = psi_decl_struct_init($struct->text, $args);
	$def->type->real.strct->token = psi_token_copy($struct);
	$def->type->real.strct->align = $as.pos;
	$def->type->real.strct->size = $as.len;
	psi_parser_proc_add_struct(P, $def->type->real.strct);
}
|	union_name[union] align_and_size[as] struct_args_block[args] {
	$def = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, $union->text), psi_decl_var_init(NULL, 0, 0));
	$def->type->token = $union;
	$def->type->real.unn = psi_decl_union_init($union->text, $args);
	$def->type->real.unn->token = psi_token_copy($union);
	$def->type->real.unn->align = $as.pos;
	$def->type->real.unn->size = $as.len;
	psi_parser_proc_add_union(P, $def->type->real.unn);
}
;

qualified_decl_type[type]:
	decl_type
|	decl_type_qualifier_token decl_type[type_] {
	$type = $type_;
}
|	qualified_decl_type[type_] decl_type_qualifier_token {
	$type = $type_;
}
;

decl_type_qualifier_token:
	CONST
|	VOLATILE
;

decl_type[type]:
	decl_type_simple[token] {
	$type = psi_decl_type_init($token->type, $token->text);
	$type->token = $token;
}
|	decl_type_complex
;

decl_type_complex[type]:
	STRUCT[token] name_token {
	$name_token->type = PSI_T_NAME;
	$type = psi_decl_type_init($token->type, $name_token->text);
	$type->token = psi_token_copy($name_token);
}
|	UNION[token] name_token {
	$name_token->type = PSI_T_NAME;
	$type = psi_decl_type_init($token->type, $name_token->text);
	$type->token = psi_token_copy($name_token);
}
|	ENUM[token] name_token {
	$name_token->type = PSI_T_NAME;
	$type = psi_decl_type_init($token->type, $name_token->text);
	$type->token = psi_token_copy($name_token);
}
;

decl_type_simple[type]:
	decl_int_type
|	decl_real_type
|	NAME[type_] {
	$type = psi_token_copy($type_);
}
|	VOID[type_] {
	$type = psi_token_copy($type_);
}
;

decl_real_type[type]: /* allocated, so free, if set */
	FLOAT[type_] {
	$type = psi_token_copy($type_);
}
|	DOUBLE[type_] {
	$type = psi_token_copy($type_);
}
|	LONG DOUBLE {
	$type = psi_token_cat(" ", 2, $LONG, $DOUBLE);
}
;

int_signed[i]:
	SIGNED
|	UNSIGNED
;

int_width[i]: /* allocated, so free, if set */
	SHORT {
	$i = psi_token_copy($SHORT);
}
|	LONG {
	$i = psi_token_copy($LONG);
}
|	LONG[l1] LONG[l2] {
	$i = psi_token_cat(" ", 2, $l1, $l2);
}
;

decl_int_type[type]: /* allocated, so free, if set */
	CHAR {
	$type = psi_token_copy($CHAR);
}
|	INT {
	$type = psi_token_copy($INT);
}
|	int_signed int_signed_types {
	if ($2) {
		$type = psi_token_cat(" ", 2, $1, $2);
		psi_token_free(&$2);
	} else {
		$type = psi_token_copy($1);
	}
}
|	int_width int_width_types {
	if ($2) {
		$type = psi_token_cat(" ", 2, $1, $2);
		psi_token_free(&$1);
		psi_token_free(&$2);
	} else {
		$type = $1;
	}
}
;

int_signed_types[type]: /* allocated, so free, if set */
	%empty {
	$type = NULL;
}
|	NAME {
	$type = psi_token_copy($NAME);
}
|	CHAR {
	$type = psi_token_copy($CHAR);
}
|	SHORT signed_short_types {
	if ($2) {
		$type = psi_token_cat(" ", 2, $1, $2);
	} else {
		$type = psi_token_copy($1);
	}
}
|	INT {
	$type = psi_token_copy($INT);
}
|	LONG signed_long_types {
	if ($2) {
		$type = psi_token_cat(" ", 2, $1, $2);
	} else {
		$type = psi_token_copy($1);
	}
}
;

signed_short_types[type]:
	%empty {
	$type = NULL;
}
|	INT
;
signed_long_types[type]:
	%empty {
	$type = NULL;
}
|	INT
|	LONG
|	LONG INT
;

int_width_types[type]: /* allocated, so free, if set */
	%empty {
	$type = NULL;
}
|	INT {
	$type = psi_token_copy($INT);
}
|	int_signed int_signed_types {
	if ($2) {
		$type = psi_token_cat(" ", 2, $1, $2);
		psi_token_free(&$2);
	} else {
		$type = psi_token_copy($1);
	}
}
;

decl_stmt:
	decl decl_asm EOS {
	$decl_stmt = $decl;
	if ($decl_asm) {
		$decl->redir = zend_string_copy($decl_asm->text);
		psi_token_free(&$decl_asm);
	}
}
|	CPP_EXTENSION decl decl_asm EOS {
	$decl_stmt = $decl;
	if ($decl_asm) {
		$decl->redir = zend_string_copy($decl_asm->text);
		psi_token_free(&$decl_asm);
	}
}
;

decl_asm:
	%empty {
	$decl_asm = NULL;
}
|	CPP_ASM LPAREN quoted_strings RPAREN {
	$decl_asm = $quoted_strings;
}
;

quoted_strings[strings]:
	QUOTED_STRING {
	$strings = psi_token_copy($QUOTED_STRING);
}
|	quoted_strings[strings_] QUOTED_STRING {
	$strings = psi_token_cat("", 2, $strings_, $QUOTED_STRING);
	psi_token_free(&$strings_);
}
;

decl_extvar_stmt[list]:
	NAME decl_arg decl_extvar_list[vars] decl_asm EOS {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_decl_extvar_free);

	if ($vars) {
		size_t i = 0;
		struct psi_decl_var *var;

		while (psi_plist_get($vars, i++, &var)) {
			if (psi_decl_extvar_is_blacklisted(var->name->val)) {
				psi_decl_var_free(&var);
			} else {
				struct psi_decl_extvar *evar = psi_decl_extvar_init(
					psi_decl_arg_init(psi_decl_type_copy($decl_arg->type), var));
				list = psi_plist_add(list, &evar);
			}
		}
		free($vars);
	}

	if (psi_decl_extvar_is_blacklisted($decl_arg->var->name->val)) {
		psi_decl_arg_free(&$decl_arg);
	} else {
		struct psi_decl_extvar *evar = psi_decl_extvar_init($decl_arg);

		if ($decl_asm) {
			evar->redir = zend_string_copy($decl_asm->text);
			psi_token_free(&$decl_asm);
		}
		list = psi_plist_add(list, &evar);
	}

	$list = list;
}
;

decl_extvar_list[list]:
	%empty {
	$list = NULL;
}
|	COMMA decl_vars {
	$list = $decl_vars;
}
;

decl_vars[vars]:
	decl_var[var] {
	$vars = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &$var);
}
|	decl_vars[vars_] COMMA decl_var[var] {
	$vars = psi_plist_add($vars_, &$var);
}
;

ignored_decl:
	ignored_decl_qualifiers decl_body ignored_decl_body {
	$ignored_decl = $decl_body;
}
;

ignored_decl_qualifiers:
	STATIC
|	STATIC CPP_INLINE
|	CPP_EXTENSION CPP_INLINE
|	CPP_EXTENSION STATIC CPP_INLINE
|	CPP_INLINE
|	NAME CPP_INLINE
;

ignored_decl_body:
	LBRACE ignored_decl_body_stmts RBRACE
;

ignored_decl_body_stmts:
	ignored_decl_body_stmt
|	ignored_decl_body_stmts ignored_decl_body_stmt
;

ignored_decl_body_stmt:
	any_nobrace_token
|	ignored_decl_body
;

decl:
	decl_body
|	NAME[abi] decl_body {
	$decl = $decl_body;
	$decl->abi = psi_decl_abi_init($abi->text);
}
;

decl_body:
	decl_func_body
|	decl_functor_body
;

decl_func_body[decl]:
	decl_func[func] LPAREN decl_args[args] RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
|	decl_func[func] LPAREN decl_args[args] COMMA ELLIPSIS RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	$decl->varargs = 1;
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
;

decl_functor_body[decl]:
	decl_functor[func] LPAREN decl_args[args] RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
|	decl_functor[func] LPAREN decl_args[args] COMMA ELLIPSIS RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	$decl->varargs = 1;
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
|	qualified_decl_type[rval_type] indirection[i] LPAREN indirection[unused1] name_token[NAME] LPAREN decl_args[args] RPAREN RPAREN LPAREN decl_args[rval_args] RPAREN array_size[as] {
	(void) $unused1;
	$NAME->type = PSI_T_NAME;

	struct psi_token *type_token = psi_token_append("@", psi_token_copy($NAME), 1, "rval");
	struct psi_decl_arg *rval_func = psi_decl_arg_init($rval_type, psi_decl_var_init(type_token->text, $i, 0));
	struct psi_decl *rval_decl = psi_decl_init(rval_func, $rval_args);

	rval_func->var->token = psi_token_copy(type_token);
	rval_func->token = psi_token_copy(type_token);
	if ($as) {
		rval_func->var->pointer_level += 1;
		rval_func->var->array_size = $as;
	}

	struct psi_decl_type *type = psi_decl_type_init(PSI_T_FUNCTION, type_token->text);
	struct psi_decl_arg *func = psi_decl_arg_init(type, psi_decl_var_init($NAME->text, 1, 0));

	type->real.func = rval_decl;
	func->var->token = psi_token_copy($NAME);
	func->token = psi_token_copy($NAME);

	$decl = psi_decl_init(func, $args);
}
|	qualified_decl_type[rval_type] indirection[i] LPAREN indirection[unused1] LPAREN indirection[unused2] name_token[NAME] RPAREN LPAREN decl_args[args] RPAREN RPAREN LPAREN decl_args[rval_args] RPAREN array_size[as] {
	(void) $unused1;
	(void) $unused2;
	$NAME->type = PSI_T_NAME;

	struct psi_token *type_token = psi_token_append("@", psi_token_copy($NAME), 1, "rval");
	struct psi_decl_arg *rval_func = psi_decl_arg_init($rval_type, psi_decl_var_init(type_token->text, $i, 0));
	struct psi_decl *rval_decl = psi_decl_init(rval_func, $rval_args);

	rval_func->var->token = psi_token_copy(type_token);
	rval_func->token = psi_token_copy(type_token);
	if ($as) {
		rval_func->var->pointer_level += 1;
		rval_func->var->array_size = $as;
	}

	struct psi_decl_type *type = psi_decl_type_init(PSI_T_FUNCTION, type_token->text);
	struct psi_decl_arg *func = psi_decl_arg_init(type, psi_decl_var_init($NAME->text, 1, 0));

	type->real.func = rval_decl;
	func->var->token = psi_token_copy($NAME);
	func->token = psi_token_copy($NAME);
	type->token = type_token;

	$decl = psi_decl_init(func, $args);
}
;

decl_anon_functor_body[decl]:
	decl_anon_functor[func] LPAREN decl_args[args] RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
|	decl_anon_functor[func] LPAREN decl_args[args] COMMA ELLIPSIS RPAREN array_size[as] {
	$decl = psi_decl_init($func, $args);
	$decl->varargs = 1;
	if ($as) {
		$decl->func->var->pointer_level += 1;
		$decl->func->var->array_size = $as;
	}
}
;

decl_functor[arg]:
	qualified_decl_type[type] indirection[i] LPAREN indirection[unused1] name_token[NAME] RPAREN {
	(void) $unused1;
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init($type, psi_decl_var_init($NAME->text, $i, 0));
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}

/*
|	CONST VOID pointers LPAREN indirection[unused1] name_token[NAME] RPAREN {
	(void) $unused1;
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}
|	VOID pointers LPAREN indirection[unused1] name_token[NAME] RPAREN {
	(void) $unused1;
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}
|	VOID LPAREN indirection[unused1] name_token[NAME] RPAREN {
	(void) $unused1;
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, 0, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}
*/
;

decl_anon_functor[arg]:
	qualified_decl_type[type] indirection[i] LPAREN indirection[unused1] RPAREN {
	(void) $unused1;
	$arg = psi_decl_arg_init($type, psi_decl_var_init(NULL, $i, 0));
	$arg->var->token = psi_token_copy($LPAREN);
	$arg->token = psi_token_copy($LPAREN);
}
/*
|	CONST VOID pointers LPAREN indirection[unused1] RPAREN {
	(void) $unused1;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init(NULL, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($VOID);
	$arg->token = psi_token_copy($VOID);
}
|	VOID pointers LPAREN indirection[unused1] RPAREN {
	(void) $unused1;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init(NULL, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($VOID);
	$arg->token = psi_token_copy($VOID);
}
|	VOID LPAREN indirection[unused1] RPAREN {
	(void) $unused1;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init(NULL, 0, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($VOID);
	$arg->token = psi_token_copy($VOID);
}
*/
;

decl_func[func]:
	decl_arg
	/*
|	VOID name_token[NAME] {
	$func = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, 0, 0)
	);
	$func->type->token = psi_token_copy($VOID);
	$func->var->token = psi_token_copy($NAME);
	$func->token = psi_token_copy($NAME);
}
*/
;

decl_args[args]:
	%empty {
	$args = NULL;
}
|	VOID %dprec 2 {
	$args = NULL;
}
|	decl_arg_list[args_] %dprec 1 {
	$args = $args_;
}
;

decl_arg_list[args]:
	decl_anon_arg[arg] {
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &$arg);
}
|	decl_arg_list[args_] COMMA decl_anon_arg[arg] {
	$args = psi_plist_add($args_, &$arg);
}
;

decl_anon_arg[arg]:
	decl_anon_functor_body[decl] {
	char digest[17];
	struct psi_token *name;

	psi_token_hash($decl->func->token, digest);
	name = psi_token_append("@", psi_token_copy($decl->func->token), 2, "funct", digest);

	$arg = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, name->text),
		psi_decl_var_copy($decl->func->var)
	);
	$arg->token = name;
	$arg->type->token = psi_token_copy($decl->func->token);
	$arg->type->real.func = $decl;
}
|	decl_arg %dprec 2 {
	$arg = $decl_arg;
}
|	qualified_decl_type[type] indirection array_size[as] %dprec 1 {
	$arg = psi_decl_arg_init(
		$type,
		psi_decl_var_init(NULL, $indirection, $as)
	);
}
/*
|	CONST VOID pointers {
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init(NULL, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($VOID);
	$arg->token = psi_token_copy($VOID);
}
|	VOID pointers {
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init(NULL, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($VOID);
	$arg->token = psi_token_copy($VOID);
}
*/
;

decl_arg[arg]:
	decl_functor_body[decl] {
	$arg = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, $decl->func->var->name),
		psi_decl_var_copy($decl->func->var)
	);
	$arg->type->token = psi_token_copy($decl->func->token);
	$arg->type->real.func = $decl;
}
|	qualified_decl_type[type] decl_var[var] {
	$arg = psi_decl_arg_init($type, $var);
}
/*
|	CONST VOID pointers name_token[NAME] {
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}
|	VOID pointers name_token[NAME] {
	$NAME->type = PSI_T_NAME;
	$arg = psi_decl_arg_init(
		psi_decl_type_init($VOID->type, $VOID->text),
		psi_decl_var_init($NAME->text, $pointers, 0)
	);
	$arg->type->token = psi_token_copy($VOID);
	$arg->var->token = psi_token_copy($NAME);
	$arg->token = psi_token_copy($NAME);
}
*/
;

decl_var[var]:
	pointers name_token array_size {
	$name_token->type = PSI_T_NAME;
	$var = psi_decl_var_init($name_token->text, $pointers + !! $array_size, $array_size);
	$var->token = psi_token_copy($name_token);
}
|	name_token array_size {
	$name_token->type = PSI_T_NAME;
	$var = psi_decl_var_init($name_token->text, !! $array_size, $array_size);
	$var->token = psi_token_copy($name_token);
}
;

decl_union[union]:
	UNION name_token align_and_size[as] decl_struct_args[args] {
	$name_token->type = PSI_T_NAME;
	$union = psi_decl_union_init($name_token->text, $args);
	$union->align = $as.pos;
	$union->size = $as.len;
	$union->token = psi_token_copy($name_token);
}
;

decl_struct[struct]:
	STRUCT name_token align_and_size[as] decl_struct_args[args] {
	$name_token->type = PSI_T_NAME;
	$struct = psi_decl_struct_init($name_token->text, $args);
	$struct->align = $as.pos;
	$struct->size = $as.len;
	$struct->token = psi_token_copy($name_token);
}
;

decl_struct_args[args]:
	EOS {
	$args = NULL;
}
|	struct_args_block
;

struct_args_block[args]:
	LBRACE struct_args RBRACE {
	$args = $struct_args;
}
;

struct_args[args]:
	typedef_anon[arg] decl_layout[layout] struct_arg_var_list[vars] EOS {
	$arg->layout = $layout;
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &$arg);
	if ($vars) {
		size_t i = 0;
		struct psi_decl_arg *arg;

		while (psi_plist_get($vars, i++, &arg)) {
			arg->type = psi_decl_type_copy($arg->type);
			$args = psi_plist_add($args, &arg);
		}
		free($vars);
	}
}
|	struct_args[args_] typedef_anon[arg] decl_layout[layout] struct_arg_var_list[vars] EOS {
	$arg->layout = $layout;
	$args = psi_plist_add($args_, &$arg);
	if ($vars) {
		size_t i = 0;
		struct psi_decl_arg *arg;

		while (psi_plist_get($vars, i++, &arg)) {
			arg->type = psi_decl_type_copy($arg->type);
			$args = psi_plist_add($args, &arg);
		}
		free($vars);
	}
}
;

struct_arg_var_list[vars]:
	%empty {
	$vars = NULL;
}
|	COMMA decl_vars_with_layout[vars_] {
	$vars = $vars_;
}
;

decl_vars_with_layout[vars]:
	decl_var[var] decl_layout[layout] {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, $var);
		arg->layout = $layout;
		$vars = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
|	decl_vars_with_layout[vars_] COMMA decl_var[var] decl_layout[layout] {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, $var);
		arg->layout = $layout;
		$vars = psi_plist_add($vars_, &arg);
	}
}
|	decl_layout[layout] {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = $layout;
		$vars = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
|	decl_vars_with_layout[vars_] COMMA decl_layout[layout] {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = $layout;
		$vars = psi_plist_add($vars_, &arg);
	}
}
;

decl_enum[enum]:
	enum_name LBRACE decl_enum_items[list] optional_comma RBRACE {
	$enum = psi_decl_enum_init($enum_name->text, $list);
	$enum->token = $enum_name;
}
;

decl_enum_items[list]:
	decl_enum_item[i] {
	$list = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &$i);
}
|	decl_enum_items[list_] COMMA decl_enum_item[i] {
	$list = psi_plist_add($list_, &$i);
}
;

decl_enum_item[i]:
	name_token {
	$name_token->type = PSI_T_NAME;
	$i = psi_decl_enum_item_init($name_token->text, NULL);
	$i->token = psi_token_copy($name_token);
}
|	name_token EQUALS num_exp {
	$name_token->type = PSI_T_NAME;
	$i = psi_decl_enum_item_init($name_token->text, $num_exp);
	$i->token = psi_token_copy($name_token);
}
;

num_exp[exp]:
	number {
	$exp = psi_num_exp_init_num($number);
	$exp->token = psi_token_copy($number->token);
}
|	LPAREN qualified_decl_type[type] RPAREN num_exp[exp_] %prec UNARY {
	$exp = psi_num_exp_init_cast($type, $exp_);
	$exp->token = psi_token_copy($type->token);
}
|	LPAREN num_exp[exp_] RPAREN {
	$exp = psi_num_exp_init_unary(PSI_T_LPAREN, $exp_);
	$exp->token = psi_token_copy($LPAREN);
}
|	num_exp[lhs] binary_op_token[op] num_exp[rhs] %prec BINARY {
	$exp = psi_num_exp_init_binary($op->type, $lhs, $rhs);
	$exp->token = psi_token_copy($op);
}
|	unary_op_token[op] num_exp[exp_] %prec UNARY {
	$exp = psi_num_exp_init_unary($op->type, $exp_);
	$exp->token = psi_token_copy($op);
}
|	num_exp[cond] IIF num_exp[truthy] COLON num_exp[falsy] {
	$exp = psi_num_exp_init_ternary($IIF->type, $cond, $truthy, $falsy);
	$exp->token = psi_token_copy($IIF);
}
;

number[num]:
	NUMBER[token] {
	$num = psi_number_init($token->type, $token->text, $token->flags);
	$num->token = psi_token_copy($token);
}
|	NSNAME[token] {
	$num = psi_number_init($token->type, $token->text, 0);
	$num->token = psi_token_copy($token);
}
|	QUOTED_CHAR[token] {
	$num = psi_number_init($token->type, $token->text, 0);
	$num->token = psi_token_copy($token);
}
|	NULL[token] {
	$num = psi_number_init($token->type, $token->text, 0);
	$num->token = psi_token_copy($token);
}
|	decl_var {
	$num = psi_number_init(PSI_T_NAME, $decl_var, 0);
	$num->token = psi_token_copy($decl_var->token);
}
|	sizeof {
	$num = $sizeof;
}
;

sizeof:
	SIZEOF LPAREN sizeof_body[sizeof_] RPAREN {
	$sizeof = $sizeof_;
	$sizeof->token = psi_token_copy($SIZEOF);
}
|	SIZEOF sizeof_body_notypes[sizeof_] {
	$sizeof = $sizeof_;
	$sizeof->token = psi_token_copy($SIZEOF);
}
;

sizeof_body[sizeof]:
	sizeof_body_notypes[sizeof_] {
	$sizeof = $sizeof_;
}
|	decl_type indirection {
	if ($indirection) {
		int8_t sizeof_void_p = sizeof(void *);
		$sizeof = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
		psi_decl_type_free(&$decl_type);
	} else {
		$sizeof = psi_number_init(PSI_T_SIZEOF, $decl_type, 0);
	}
}
;

sizeof_body_notypes[sizeof]:
	AMPERSAND NAME {
	int8_t sizeof_void_p = sizeof(void *);
	$sizeof = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
}
|	QUOTED_CHAR {
	int8_t sizeof_a = sizeof('a');
	$sizeof = psi_number_init(PSI_T_INT8, &sizeof_a, 0);
}
|	QUOTED_STRING {
	uint64_t len = $QUOTED_STRING->text->len + 1;
	$sizeof = psi_number_init(PSI_T_UINT64, &len, 0);
}
;

enum_name[name]:
	ENUM optional_name[name_] {
	if ($name_) {
		$name = psi_token_copy($name_);
	} else {
		char digest[17];

		psi_token_hash($ENUM, digest);
		$name = psi_token_append("@", psi_token_copy($ENUM), 1, digest);
	}
}
;

union_name[name]:
	UNION optional_name[name_] {
	if ($name_) {
		$name = psi_token_copy($name_);
	} else {
		char digest[17];

		psi_token_hash($UNION, digest);
		$name = psi_token_append("@", psi_token_copy($UNION), 1, digest);
	}
}
;

struct_name[name]:
	STRUCT optional_name[name_] {
	if ($name_) {
		$name = psi_token_copy($name_);
	} else {
		char digest[17];

		psi_token_hash($STRUCT, digest);
		$name = psi_token_append("@", psi_token_copy($STRUCT), 1, digest);
	}
}
;

optional_name[name]:
	%empty {
	$name = NULL;
}
|	name_token {
	$name = $name_token;
	$name->type = PSI_T_NAME;
}
;

optional_comma:
	%empty
|	COMMA
;

decl_layout[l]:
	%empty {
	$l = NULL;
}
|	COLON NUMBER[width] {
	$l = psi_layout_init(0, 0, psi_layout_init(0, atol($width->text->val), NULL));
}
|	COLON COLON LPAREN NUMBER[align] COMMA NUMBER[size] RPAREN {
	$l = psi_layout_init(atol($align->text->val), atol($size->text->val), NULL);
}
|	COLON NUMBER[width] COLON COLON LPAREN NUMBER[align] COMMA NUMBER[size] RPAREN {
	$l = psi_layout_init(atol($align->text->val), atol($size->text->val), psi_layout_init(0, atol($width->text->val), NULL));
}
;

align_and_size[as]:
	%empty {
	$as.pos = 0;
	$as.len = 0;
}
|	COLON COLON LPAREN NUMBER[align] COMMA NUMBER[size] RPAREN {
	$as.pos = atol($align->text->val);
	$as.len = atol($size->text->val);
}
;

array_size[as]:
	%empty {
	$as = 0;
}
|	LBRACKET array_qualifier_token RBRACKET {
	$as = 0;
}
|	LBRACKET num_exp RBRACKET {
	struct psi_validate_scope scope = {0};
	psi_validate_scope_ctor(&scope);
	scope.cpp = P->preproc;
	if (psi_num_exp_validate(PSI_DATA(P), $num_exp, &scope)) {
		$as = psi_num_exp_get_long($num_exp, NULL, P->preproc);
	} else {
		$as = 0;
	}
	psi_num_exp_free(&$num_exp);
	psi_validate_scope_dtor(&scope);
}
;

array_qualifier_token:
	%empty
|	CPP_RESTRICT
|	VOLATILE
|	CONST
;

indirection[i]:
	%empty {
	$i = 0;
}
|	pointers[p] %prec UNARY {
	$i = $p;
}
;

pointers[p]:
	asterisks
|	asterisks[a] CPP_RESTRICT {
	$p = $a;
}
;

asterisks[a]:
	asterisk {
	$a = 1;
}
|	asterisks[a_] asterisk {
	$a = $a_ + 1;
}
;

asterisk:
	ASTERISK
|	ASTERISK pointer_qualifier_token
;

pointer_qualifier_token:
	CONST
|	VOLATILE
;

/*
 *
 * impl
 *
 */

impl:
	impl_func[func] LBRACE impl_stmts[stmts] RBRACE {
	$impl = psi_impl_init($func, $stmts);
}
|	STATIC impl_func[func] LBRACE impl_stmts[stmts] RBRACE {
	$impl = psi_impl_init($func, $stmts);
	$func->static_memory = 1;
}
;

impl_func[func]:
	FUNCTION reference[r] NSNAME LPAREN RPAREN COLON impl_type[type] {
	$func = psi_impl_func_init($NSNAME->text, NULL, $type);
	$func->token = psi_token_copy($NSNAME);
	$func->return_reference = $r;
}
|	FUNCTION reference[r] NSNAME LPAREN impl_args[args] RPAREN COLON impl_type[type] {
	$func = psi_impl_func_init($NSNAME->text, $args, $type);
	$func->token = psi_token_copy($NSNAME);
	$func->return_reference = $r;
}
|	FUNCTION reference[r] NSNAME LPAREN impl_args[args] COMMA impl_type[va_type] reference[va_r] ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type[type] {
	$func = psi_impl_func_init($NSNAME->text, $args, $type);
	$func->token = psi_token_copy($NSNAME);
	$func->return_reference = $r;
	$func->vararg = psi_impl_arg_init($va_type, psi_impl_var_init($DOLLAR_NAME->text, $va_r), NULL);
	$func->vararg->var->token = psi_token_copy($DOLLAR_NAME);
}
;

impl_args[args]:
	impl_arg[arg] {
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &$arg);
}
|	impl_args[args_] COMMA impl_arg[arg] {
	$args = psi_plist_add($args_, &$arg);
}
;

impl_arg[arg]:
	impl_type[type] impl_var[var] {
	$arg = psi_impl_arg_init($type, $var, NULL);
}
|	impl_type[type] impl_var[var] EQUALS impl_def_val[val] {
	$arg = psi_impl_arg_init($type, $var, $val);
}
;

impl_var[var]:
	reference DOLLAR_NAME {
	$var = psi_impl_var_init($DOLLAR_NAME->text, $reference);
	$var->token = psi_token_copy($DOLLAR_NAME);
}
;

impl_type[type]:
	impl_type_token[token] {
	$type = psi_impl_type_init($token->type, $token->text);
	$type->token = psi_token_copy($token);
}
;

impl_type_restricted[type]:
	impl_type_restricted_token[token] {
	$type = psi_impl_type_init($token->type, $token->text);
	$type->token = psi_token_copy($token);
}
;

impl_type_token:
	impl_type_restricted_token
|	impl_type_extended_token
;

impl_type_restricted_token:
	BOOL
|	INT
|	FLOAT
|	STRING
|	MIXED
;

impl_type_extended_token:
	VOID
|	ARRAY
|	OBJECT
|	CALLABLE
;

impl_stmts[stmts]:
	impl_stmt[stmt] {
	$stmts = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &$stmt);
}
|	impl_stmts[stmts_] impl_stmt[stmt] {
	$stmts = psi_plist_add($stmts_, &$stmt);
}
;

impl_stmt[stmt]:
	return_stmt[s] {
	$stmt = (struct psi_token **) $s;
}
|	let_stmt[s] {
	$stmt = (struct psi_token **) $s;
}
|	set_stmt[s] {
	$stmt = (struct psi_token **) $s;
}
|	assert_stmt[s] {
	$stmt = (struct psi_token **) $s;
}
|	free_stmt[s] {
	$stmt = (struct psi_token **) $s;
}
;

let_stmt[let]:
	LET let_exp_assign[exp] EOS {
	$let = psi_let_stmt_init($exp);
	$let->token = psi_token_copy($LET);
}
|	TEMP decl_var[var] EQUALS reference decl_var[val] EOS {
	$let = psi_let_stmt_init(psi_let_exp_init_ex($var, PSI_LET_TMP, $val));
	$let->token = psi_token_copy($TEMP);
	$let->exp->is_reference = $reference;
}
;

let_exp[exp]:
	let_exp_assign
|	byref let_exp_byref[exp_] {
	$exp = $exp_;
	$exp->is_reference = true;
}
|	let_exp_byref[exp_] {
	$exp = $exp_;
	$exp->is_reference = false;
}
;

let_exp_byref[exp]:
	NULL %dprec 2 {
	$exp = psi_let_exp_init(PSI_LET_NULL, NULL);
}
|	num_exp[num] %dprec 1 {
	$exp = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, $num);
}
|	let_calloc[calloc] {
	$exp = psi_let_exp_init(PSI_LET_CALLOC, $calloc);
}
|	STATIC let_calloc[calloc] {
	$exp = psi_let_exp_init(PSI_LET_CALLOC, $calloc);
	$calloc->static_memory = 1;
}
|	let_callback[callback] {
	$exp = psi_let_exp_init(PSI_LET_CALLBACK, $callback);
}
|	let_func[func] {
	$exp = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, $func);
}
;

let_exp_assign[exp]:
	decl_var[var] EQUALS let_exp_byref[exp_] {
	$exp = $exp_;
	$exp->var = $var;
}
|	decl_var[var] EQUALS byref let_exp_byref[exp_] {
	$exp = $exp_;
	$exp->is_reference = 1;
	$exp->var = $var;
}
;

let_calloc[calloc]:
	CALLOC LPAREN num_exp[nmemb] COMMA num_exp[size] RPAREN {
	$calloc = psi_let_calloc_init($nmemb, $size);
	$calloc->token = psi_token_copy($CALLOC);
}
;

let_callback[callback]:
	CALLBACK callback_rval[func] LPAREN impl_var[var] LPAREN callback_arg_list[args] RPAREN RPAREN {
	$callback = psi_let_callback_init(psi_let_func_init($func->type, $func->text, $var), $args, NULL);
	$callback->func->token = psi_token_copy($func);
	$callback->token = psi_token_copy($CALLBACK);
}
|	CALLBACK LPAREN call_decl_vars[cb_args] RPAREN AS callback_rval[func] LPAREN impl_var[var] LPAREN callback_arg_list[args] RPAREN RPAREN {
	$callback = psi_let_callback_init(psi_let_func_init($func->type, $func->text, $var), $args, $cb_args);
	$callback->func->token = psi_token_copy($func);
	$callback->token = psi_token_copy($CALLBACK);
}
;

let_func[func]:
	let_func_token[token] LPAREN impl_var[var] let_func_exps[exps] RPAREN {
	$func = psi_let_func_init($token->type, $token->text, $var);
	$func->token = psi_token_copy($token);
	$func->inner = $exps;
}
;

let_func_token:
	ZVAL
|	OBJVAL
|	ARRVAL
|	PATHVAL
|	STRLEN
|	STRVAL
|	FLOATVAL
|	INTVAL
|	BOOLVAL
|	COUNT
;

let_func_exps[exps]:
	%empty {
	$exps = NULL;
}
|	COMMA let_exps[exps_] {
	$exps = $exps_;
}
;

let_exps[exps]:
	let_exp[exp] {
	$exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &$exp);
}
|	let_exps[exps_] COMMA let_exp[exp] {
	$exps = psi_plist_add($exps_, &$exp);
}
;

callback_rval[rval]:
	VOID
|	let_func_token
;

callback_arg_list[list]:
	%empty {
	$list = NULL;
}
|	callback_args[args] {
	$list = $args;
}
;

callback_args[args]:
	set_exp[exp] {
	$args = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &$exp);
}
|	callback_args[args_] COMMA set_exp[exp] {
	$args = psi_plist_add($args_, &$exp);
}
;

return_stmt[return]:
	RETURN return_exp EOS {
	$return = psi_return_stmt_init($return_exp);
	$return->token = psi_token_copy($RETURN);
}
;

return_exp:
	decl_var[func] LPAREN call_decl_vars[args] RPAREN AS set_func {
	$return_exp = psi_return_exp_init($func, $args, psi_set_exp_init(PSI_SET_FUNC, $set_func));
	$return_exp->token = psi_token_copy($func->token);
}
|	set_func {
	$return_exp = psi_return_exp_init(NULL, NULL, psi_set_exp_init(PSI_SET_FUNC, $set_func));
	$return_exp->token = psi_token_copy($set_func->token);
}
;

call_decl_vars[args]:
	%empty {
	$args = NULL;
}
|	VOID {
	$args = NULL;
}
|	decl_vars[vars] {
	$args = $vars;
}
;

set_stmt[set]:
	SET set_exp[exp] EOS {
	$set = psi_set_stmt_init($exp);
	$set->token = psi_token_copy($SET);
}
;

set_exp[exp]:
	set_func[func] {
	$exp = psi_set_exp_init(PSI_SET_FUNC, $func);
}
|	num_exp[num] {
	$exp = psi_set_exp_init(PSI_SET_NUMEXP, $num);
}
|	impl_var[var] EQUALS set_exp[exp_] {
	$exp = $exp_;
	$exp->var = $var;
}
;

set_func[func]:
	set_func_token[token] LPAREN decl_var[var] set_func_exps[exps] RPAREN {
	$func = psi_set_func_init($token->type, $token->text, $var);
	$func->token = psi_token_copy($token);
	$func->inner = $exps;
}
|	set_func_token[token] LPAREN decl_var[var] COMMA ELLIPSIS RPAREN {
	$func = psi_set_func_init($token->type, $token->text, $var);
	$func->token = psi_token_copy($token);
	$func->recursive = 1;
}
;

set_func_token:
	TO_OBJECT
|	TO_ARRAY
|	TO_STRING
|	TO_INT
|	TO_FLOAT
|	TO_BOOL
|	ZVAL
|	VOID
;

set_func_exps[exps]:
	%empty {
	$exps = NULL;
}
|	COMMA set_exps[exps_] {
	$exps = $exps_;
}
;

set_exps[exps]:
	set_exp[exp] {
	$exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &$exp);
}
|	set_exps[exps_] COMMA set_exp[exp] {
	$exps = psi_plist_add($exps_, &$exp);
}
;

assert_stmt[assert]:
	assert_stmt_token[token] num_exp[exp] EOS {
	$assert = psi_assert_stmt_init((enum psi_assert_kind) $token->type, $exp);
	$assert->token = psi_token_copy($token);
}
;

assert_stmt_token:
	PRE_ASSERT
|	POST_ASSERT
;

free_stmt[free]:
	FREE free_exps[exps] EOS {
	$free = psi_free_stmt_init($exps);
	$free->token = psi_token_copy($FREE);
}
;

free_exps[exps]:
	free_exp[exp] {
	$exps = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &$exp);
}
|	free_exps[exps_] COMMA free_exp[exp] {
	$exps = psi_plist_add($exps_, &$exp);
}
;

free_exp[exp]:
	name_token[NAME] LPAREN decl_vars[vars] RPAREN {
	$NAME->type = PSI_T_NAME;
	$exp = psi_free_exp_init($NAME->text, $vars);
	$exp->token = psi_token_copy($NAME);
}
;

reference:
	%empty {
	$reference = false;
}
|	byref {
	$reference = true;
}
;

byref:
	AMPERSAND %prec UNARY
;

%%

/* epilogue */

#define PSI_DEBUG_LEX 0
static int psi_parser_proc_lex(YYSTYPE *lvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
	struct psi_token *token;
#if PSI_DEBUG_LEX
	PSI_DEBUG_PRINT(P, "PSI: LEX index %4zu ", *index);
#endif
	if (psi_plist_get(tokens, (*index)++, &token)) {
#if PSI_DEBUG_LEX	
		PSI_DEBUG_DUMP(P, psi_token_dump, token);
#endif
		*((struct psi_token **)lvalp) = token;
		return token->type;
	} else {
#if PSI_DEBUG_LEX
		PSI_DEBUG_PRINT(P, "EOF\n");
#endif
		(*index)--;
	}

	return PSI_T_EOF;
}

static void psi_parser_proc_error(struct psi_parser *P, struct psi_plist *tokens, size_t *index, const char *msg)
{
	struct psi_token *T = NULL;
	size_t last;

	if (*index == 0) {
		last = 0;
	} else {
		last = --(*index);
	}

	psi_plist_get(tokens, last, &T);
	if (T) {
		size_t i = (last >= 5) ? last - 5 : 0; 
		
		P->error(PSI_DATA(P), T, PSI_WARNING, "PSI %s at col %u", msg, T->col);
		while (i <= last || T->type != PSI_T_EOS) {
			if (!psi_plist_get(tokens, i++, &T)) {
				break;
			}
			P->error(PSI_DATA(P), T, PSI_WARNING, "PSI %s token '%s' at col %u", 
					i<last+1?"preceding":i>last+1?"following":"offending", T->text->val, T->col);
		}
	} else {
		P->error(PSI_DATA(P), NULL, PSI_WARNING, "PSI %s", msg);
	}
	P->errors++;
}

