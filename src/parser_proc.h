/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_PSI_PARSER_PROC_SRC_PARSER_PROC_H_INCLUDED
# define YY_PSI_PARSER_PROC_SRC_PARSER_PROC_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int psi_parser_proc_debug;
#endif
/* "%code requires" blocks.  */
#line 82 "src/parser_proc_grammar.y" /* glr.c:197  */

#include "plist.h"
#include "types/layout.h"

struct psi_parser;


#line 52 "src/parser_proc.h" /* glr.c:197  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PSI_T_EOF = 0,
    PSI_T_BOOL = 258,
    PSI_T_CHAR = 259,
    PSI_T_SHORT = 260,
    PSI_T_INT = 261,
    PSI_T_SIGNED = 262,
    PSI_T_UNSIGNED = 263,
    PSI_T_LONG = 264,
    PSI_T_FLOAT = 265,
    PSI_T_DOUBLE = 266,
    PSI_T_STRING = 267,
    PSI_T_MIXED = 268,
    PSI_T_ARRAY = 269,
    PSI_T_OBJECT = 270,
    PSI_T_CALLABLE = 271,
    PSI_T_VOID = 272,
    PSI_T_ZVAL = 273,
    PSI_T_NULL = 274,
    PSI_T_TRUE = 275,
    PSI_T_FALSE = 276,
    PSI_T_NAME = 277,
    PSI_T_NSNAME = 278,
    PSI_T_DOLLAR_NAME = 279,
    PSI_T_NUMBER = 280,
    PSI_T_QUOTED_STRING = 281,
    PSI_T_QUOTED_CHAR = 282,
    PSI_T_SIZEOF = 283,
    PSI_T_VOLATILE = 284,
    PSI_T_EOL = 285,
    PSI_T_EOS = 286,
    PSI_T_LPAREN = 287,
    PSI_T_RPAREN = 288,
    PSI_T_COMMA = 289,
    PSI_T_COLON = 290,
    PSI_T_LBRACE = 291,
    PSI_T_RBRACE = 292,
    PSI_T_LBRACKET = 293,
    PSI_T_RBRACKET = 294,
    PSI_T_EQUALS = 295,
    PSI_T_HASH = 296,
    PSI_T_PIPE = 297,
    PSI_T_CARET = 298,
    PSI_T_AMPERSAND = 299,
    PSI_T_LSHIFT = 300,
    PSI_T_RSHIFT = 301,
    PSI_T_PLUS = 302,
    PSI_T_MINUS = 303,
    PSI_T_ASTERISK = 304,
    PSI_T_SLASH = 305,
    PSI_T_MODULO = 306,
    PSI_T_LCHEVR = 307,
    PSI_T_RCHEVR = 308,
    PSI_T_CMP_GE = 309,
    PSI_T_CMP_LE = 310,
    PSI_T_OR = 311,
    PSI_T_AND = 312,
    PSI_T_CMP_EQ = 313,
    PSI_T_CMP_NE = 314,
    PSI_T_TILDE = 315,
    PSI_T_NOT = 316,
    PSI_T_PERIOD = 317,
    PSI_T_BACKSLASH = 318,
    PSI_T_ELLIPSIS = 319,
    PSI_T_IIF = 320,
    PSI_T_PRAGMA = 321,
    PSI_T_PRAGMA_ONCE = 322,
    PSI_T_LINE = 323,
    PSI_T_ERROR = 324,
    PSI_T_WARNING = 325,
    PSI_T_IF = 326,
    PSI_T_IFDEF = 327,
    PSI_T_IFNDEF = 328,
    PSI_T_ELSE = 329,
    PSI_T_ELIF = 330,
    PSI_T_ENDIF = 331,
    PSI_T_DEFINE = 332,
    PSI_T_DEFINED = 333,
    PSI_T_UNDEF = 334,
    PSI_T_IMPORT = 335,
    PSI_T_INCLUDE = 336,
    PSI_T_INCLUDE_NEXT = 337,
    PSI_T_TYPEDEF = 338,
    PSI_T_STRUCT = 339,
    PSI_T_UNION = 340,
    PSI_T_ENUM = 341,
    PSI_T_CONST = 342,
    PSI_T_LIB = 343,
    PSI_T_STATIC = 344,
    PSI_T_CALLBACK = 345,
    PSI_T_FUNCTION = 346,
    PSI_T_LET = 347,
    PSI_T_SET = 348,
    PSI_T_TEMP = 349,
    PSI_T_FREE = 350,
    PSI_T_RETURN = 351,
    PSI_T_PRE_ASSERT = 352,
    PSI_T_POST_ASSERT = 353,
    PSI_T_BOOLVAL = 354,
    PSI_T_INTVAL = 355,
    PSI_T_STRVAL = 356,
    PSI_T_PATHVAL = 357,
    PSI_T_STRLEN = 358,
    PSI_T_FLOATVAL = 359,
    PSI_T_ARRVAL = 360,
    PSI_T_OBJVAL = 361,
    PSI_T_COUNT = 362,
    PSI_T_CALLOC = 363,
    PSI_T_TO_BOOL = 364,
    PSI_T_TO_INT = 365,
    PSI_T_TO_STRING = 366,
    PSI_T_TO_FLOAT = 367,
    PSI_T_TO_ARRAY = 368,
    PSI_T_TO_OBJECT = 369,
    PSI_T_COMMENT = 370,
    PSI_T_WHITESPACE = 371,
    PSI_T_NO_WHITESPACE = 372,
    PSI_T_CPP_HEADER = 373,
    PSI_T_CPP_ATTRIBUTE = 374,
    PSI_T_CPP_EXTENSION = 375,
    PSI_T_CPP_PASTE = 376,
    PSI_T_CPP_INLINE = 377,
    PSI_T_CPP_RESTRICT = 378,
    PSI_T_CPP_ASM = 379,
    PSI_T_BINARY = 380,
    PSI_T_UNARY = 381
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{

  /* reference  */
  bool PSI_T_reference;
  /* array_size  */
  size_t PSI_T_array_size;
  /* indirection  */
  size_t PSI_T_indirection;
  /* pointers  */
  size_t PSI_T_pointers;
  /* asterisks  */
  size_t PSI_T_asterisks;
  /* assert_stmt  */
  struct psi_assert_stmt * PSI_T_assert_stmt;
  /* constant  */
  struct psi_const * PSI_T_constant;
  /* constant_type  */
  struct psi_const_type * PSI_T_constant_type;
  /* cpp  */
  struct psi_cpp_exp * PSI_T_cpp;
  /* cpp_exp  */
  struct psi_cpp_exp * PSI_T_cpp_exp;
  /* cpp_macro_decl  */
  struct psi_cpp_macro_decl * PSI_T_cpp_macro_decl;
  /* decl_stmt  */
  struct psi_decl * PSI_T_decl_stmt;
  /* decl  */
  struct psi_decl * PSI_T_decl;
  /* decl_body  */
  struct psi_decl * PSI_T_decl_body;
  /* decl_func_body  */
  struct psi_decl * PSI_T_decl_func_body;
  /* decl_functor_body  */
  struct psi_decl * PSI_T_decl_functor_body;
  /* decl_typedef  */
  struct psi_decl_arg * PSI_T_decl_typedef;
  /* typedef  */
  struct psi_decl_arg * PSI_T_typedef;
  /* typedef_anon  */
  struct psi_decl_arg * PSI_T_typedef_anon;
  /* typedef_decl  */
  struct psi_decl_arg * PSI_T_typedef_decl;
  /* typedef_anon_decl  */
  struct psi_decl_arg * PSI_T_typedef_anon_decl;
  /* decl_functor  */
  struct psi_decl_arg * PSI_T_decl_functor;
  /* decl_func  */
  struct psi_decl_arg * PSI_T_decl_func;
  /* decl_anon_arg  */
  struct psi_decl_arg * PSI_T_decl_anon_arg;
  /* decl_arg  */
  struct psi_decl_arg * PSI_T_decl_arg;
  /* decl_enum  */
  struct psi_decl_enum * PSI_T_decl_enum;
  /* decl_enum_item  */
  struct psi_decl_enum_item * PSI_T_decl_enum_item;
  /* decl_struct  */
  struct psi_decl_struct * PSI_T_decl_struct;
  /* qualified_decl_type  */
  struct psi_decl_type * PSI_T_qualified_decl_type;
  /* decl_type  */
  struct psi_decl_type * PSI_T_decl_type;
  /* decl_type_complex  */
  struct psi_decl_type * PSI_T_decl_type_complex;
  /* decl_union  */
  struct psi_decl_union * PSI_T_decl_union;
  /* decl_var  */
  struct psi_decl_var * PSI_T_decl_var;
  /* free_exp  */
  struct psi_free_exp * PSI_T_free_exp;
  /* free_stmt  */
  struct psi_free_stmt * PSI_T_free_stmt;
  /* impl  */
  struct psi_impl * PSI_T_impl;
  /* impl_arg  */
  struct psi_impl_arg * PSI_T_impl_arg;
  /* impl_def_val  */
  struct psi_impl_def_val * PSI_T_impl_def_val;
  /* impl_func  */
  struct psi_impl_func * PSI_T_impl_func;
  /* impl_type  */
  struct psi_impl_type * PSI_T_impl_type;
  /* impl_var  */
  struct psi_impl_var * PSI_T_impl_var;
  /* align_and_size  */
  struct psi_layout PSI_T_align_and_size;
  /* decl_layout  */
  struct psi_layout * PSI_T_decl_layout;
  /* let_callback  */
  struct psi_let_callback * PSI_T_let_callback;
  /* let_calloc  */
  struct psi_let_calloc * PSI_T_let_calloc;
  /* let_exp  */
  struct psi_let_exp * PSI_T_let_exp;
  /* let_exp_byref  */
  struct psi_let_exp * PSI_T_let_exp_byref;
  /* let_exp_assign  */
  struct psi_let_exp * PSI_T_let_exp_assign;
  /* let_func  */
  struct psi_let_func * PSI_T_let_func;
  /* let_stmt  */
  struct psi_let_stmt * PSI_T_let_stmt;
  /* cpp_macro_exp  */
  struct psi_num_exp * PSI_T_cpp_macro_exp;
  /* num_exp  */
  struct psi_num_exp * PSI_T_num_exp;
  /* number  */
  struct psi_number * PSI_T_number;
  /* sizeof  */
  struct psi_number * PSI_T_sizeof;
  /* sizeof_body  */
  struct psi_number * PSI_T_sizeof_body;
  /* sizeof_body_notypes  */
  struct psi_number * PSI_T_sizeof_body_notypes;
  /* cpp_macro_sig  */
  struct psi_plist * PSI_T_cpp_macro_sig;
  /* cpp_macro_sig_args  */
  struct psi_plist * PSI_T_cpp_macro_sig_args;
  /* cpp_macro_decl_tokens  */
  struct psi_plist * PSI_T_cpp_macro_decl_tokens;
  /* cpp_macro_decl_token_list  */
  struct psi_plist * PSI_T_cpp_macro_decl_token_list;
  /* cpp_macro_call_args  */
  struct psi_plist * PSI_T_cpp_macro_call_args;
  /* cpp_macro_call_arg_list  */
  struct psi_plist * PSI_T_cpp_macro_call_arg_list;
  /* decl_vars  */
  struct psi_plist * PSI_T_decl_vars;
  /* decl_args  */
  struct psi_plist * PSI_T_decl_args;
  /* decl_struct_args  */
  struct psi_plist * PSI_T_decl_struct_args;
  /* struct_args_block  */
  struct psi_plist * PSI_T_struct_args_block;
  /* struct_args  */
  struct psi_plist * PSI_T_struct_args;
  /* struct_arg_var_list  */
  struct psi_plist * PSI_T_struct_arg_var_list;
  /* decl_vars_with_layout  */
  struct psi_plist * PSI_T_decl_vars_with_layout;
  /* decl_enum_items  */
  struct psi_plist * PSI_T_decl_enum_items;
  /* impl_args  */
  struct psi_plist * PSI_T_impl_args;
  /* impl_stmts  */
  struct psi_plist * PSI_T_impl_stmts;
  /* let_func_exps  */
  struct psi_plist * PSI_T_let_func_exps;
  /* let_exps  */
  struct psi_plist * PSI_T_let_exps;
  /* callback_arg_list  */
  struct psi_plist * PSI_T_callback_arg_list;
  /* callback_args  */
  struct psi_plist * PSI_T_callback_args;
  /* set_func_exps  */
  struct psi_plist * PSI_T_set_func_exps;
  /* set_exps  */
  struct psi_plist * PSI_T_set_exps;
  /* free_exps  */
  struct psi_plist * PSI_T_free_exps;
  /* return_stmt  */
  struct psi_return_stmt * PSI_T_return_stmt;
  /* set_exp  */
  struct psi_set_exp * PSI_T_set_exp;
  /* set_func  */
  struct psi_set_func * PSI_T_set_func;
  /* set_stmt  */
  struct psi_set_stmt * PSI_T_set_stmt;
  /* "end of file"  */
  struct psi_token * PSI_T_EOF;
  /* BOOL  */
  struct psi_token * PSI_T_BOOL;
  /* CHAR  */
  struct psi_token * PSI_T_CHAR;
  /* SHORT  */
  struct psi_token * PSI_T_SHORT;
  /* INT  */
  struct psi_token * PSI_T_INT;
  /* SIGNED  */
  struct psi_token * PSI_T_SIGNED;
  /* UNSIGNED  */
  struct psi_token * PSI_T_UNSIGNED;
  /* LONG  */
  struct psi_token * PSI_T_LONG;
  /* FLOAT  */
  struct psi_token * PSI_T_FLOAT;
  /* DOUBLE  */
  struct psi_token * PSI_T_DOUBLE;
  /* STRING  */
  struct psi_token * PSI_T_STRING;
  /* MIXED  */
  struct psi_token * PSI_T_MIXED;
  /* ARRAY  */
  struct psi_token * PSI_T_ARRAY;
  /* OBJECT  */
  struct psi_token * PSI_T_OBJECT;
  /* CALLABLE  */
  struct psi_token * PSI_T_CALLABLE;
  /* VOID  */
  struct psi_token * PSI_T_VOID;
  /* ZVAL  */
  struct psi_token * PSI_T_ZVAL;
  /* NULL  */
  struct psi_token * PSI_T_NULL;
  /* TRUE  */
  struct psi_token * PSI_T_TRUE;
  /* FALSE  */
  struct psi_token * PSI_T_FALSE;
  /* NAME  */
  struct psi_token * PSI_T_NAME;
  /* NSNAME  */
  struct psi_token * PSI_T_NSNAME;
  /* DOLLAR_NAME  */
  struct psi_token * PSI_T_DOLLAR_NAME;
  /* NUMBER  */
  struct psi_token * PSI_T_NUMBER;
  /* QUOTED_STRING  */
  struct psi_token * PSI_T_QUOTED_STRING;
  /* QUOTED_CHAR  */
  struct psi_token * PSI_T_QUOTED_CHAR;
  /* SIZEOF  */
  struct psi_token * PSI_T_SIZEOF;
  /* VOLATILE  */
  struct psi_token * PSI_T_VOLATILE;
  /* "end of line"  */
  struct psi_token * PSI_T_EOL;
  /* ";"  */
  struct psi_token * PSI_T_EOS;
  /* "("  */
  struct psi_token * PSI_T_LPAREN;
  /* ")"  */
  struct psi_token * PSI_T_RPAREN;
  /* ","  */
  struct psi_token * PSI_T_COMMA;
  /* ":"  */
  struct psi_token * PSI_T_COLON;
  /* "{"  */
  struct psi_token * PSI_T_LBRACE;
  /* "}"  */
  struct psi_token * PSI_T_RBRACE;
  /* "["  */
  struct psi_token * PSI_T_LBRACKET;
  /* "]"  */
  struct psi_token * PSI_T_RBRACKET;
  /* "="  */
  struct psi_token * PSI_T_EQUALS;
  /* "#"  */
  struct psi_token * PSI_T_HASH;
  /* "|"  */
  struct psi_token * PSI_T_PIPE;
  /* "^"  */
  struct psi_token * PSI_T_CARET;
  /* "&"  */
  struct psi_token * PSI_T_AMPERSAND;
  /* "<<"  */
  struct psi_token * PSI_T_LSHIFT;
  /* ">>"  */
  struct psi_token * PSI_T_RSHIFT;
  /* "+"  */
  struct psi_token * PSI_T_PLUS;
  /* "-"  */
  struct psi_token * PSI_T_MINUS;
  /* "*"  */
  struct psi_token * PSI_T_ASTERISK;
  /* "/"  */
  struct psi_token * PSI_T_SLASH;
  /* "%"  */
  struct psi_token * PSI_T_MODULO;
  /* "<"  */
  struct psi_token * PSI_T_LCHEVR;
  /* ">"  */
  struct psi_token * PSI_T_RCHEVR;
  /* ">="  */
  struct psi_token * PSI_T_CMP_GE;
  /* "<="  */
  struct psi_token * PSI_T_CMP_LE;
  /* "||"  */
  struct psi_token * PSI_T_OR;
  /* "&&"  */
  struct psi_token * PSI_T_AND;
  /* "=="  */
  struct psi_token * PSI_T_CMP_EQ;
  /* "!="  */
  struct psi_token * PSI_T_CMP_NE;
  /* "~"  */
  struct psi_token * PSI_T_TILDE;
  /* "!"  */
  struct psi_token * PSI_T_NOT;
  /* "."  */
  struct psi_token * PSI_T_PERIOD;
  /* "\\"  */
  struct psi_token * PSI_T_BACKSLASH;
  /* "..."  */
  struct psi_token * PSI_T_ELLIPSIS;
  /* "?"  */
  struct psi_token * PSI_T_IIF;
  /* PRAGMA  */
  struct psi_token * PSI_T_PRAGMA;
  /* PRAGMA_ONCE  */
  struct psi_token * PSI_T_PRAGMA_ONCE;
  /* LINE  */
  struct psi_token * PSI_T_LINE;
  /* ERROR  */
  struct psi_token * PSI_T_ERROR;
  /* WARNING  */
  struct psi_token * PSI_T_WARNING;
  /* IF  */
  struct psi_token * PSI_T_IF;
  /* IFDEF  */
  struct psi_token * PSI_T_IFDEF;
  /* IFNDEF  */
  struct psi_token * PSI_T_IFNDEF;
  /* ELSE  */
  struct psi_token * PSI_T_ELSE;
  /* ELIF  */
  struct psi_token * PSI_T_ELIF;
  /* ENDIF  */
  struct psi_token * PSI_T_ENDIF;
  /* DEFINE  */
  struct psi_token * PSI_T_DEFINE;
  /* DEFINED  */
  struct psi_token * PSI_T_DEFINED;
  /* UNDEF  */
  struct psi_token * PSI_T_UNDEF;
  /* IMPORT  */
  struct psi_token * PSI_T_IMPORT;
  /* INCLUDE  */
  struct psi_token * PSI_T_INCLUDE;
  /* INCLUDE_NEXT  */
  struct psi_token * PSI_T_INCLUDE_NEXT;
  /* TYPEDEF  */
  struct psi_token * PSI_T_TYPEDEF;
  /* STRUCT  */
  struct psi_token * PSI_T_STRUCT;
  /* UNION  */
  struct psi_token * PSI_T_UNION;
  /* ENUM  */
  struct psi_token * PSI_T_ENUM;
  /* CONST  */
  struct psi_token * PSI_T_CONST;
  /* LIB  */
  struct psi_token * PSI_T_LIB;
  /* STATIC  */
  struct psi_token * PSI_T_STATIC;
  /* CALLBACK  */
  struct psi_token * PSI_T_CALLBACK;
  /* FUNCTION  */
  struct psi_token * PSI_T_FUNCTION;
  /* LET  */
  struct psi_token * PSI_T_LET;
  /* SET  */
  struct psi_token * PSI_T_SET;
  /* TEMP  */
  struct psi_token * PSI_T_TEMP;
  /* FREE  */
  struct psi_token * PSI_T_FREE;
  /* RETURN  */
  struct psi_token * PSI_T_RETURN;
  /* PRE_ASSERT  */
  struct psi_token * PSI_T_PRE_ASSERT;
  /* POST_ASSERT  */
  struct psi_token * PSI_T_POST_ASSERT;
  /* BOOLVAL  */
  struct psi_token * PSI_T_BOOLVAL;
  /* INTVAL  */
  struct psi_token * PSI_T_INTVAL;
  /* STRVAL  */
  struct psi_token * PSI_T_STRVAL;
  /* PATHVAL  */
  struct psi_token * PSI_T_PATHVAL;
  /* STRLEN  */
  struct psi_token * PSI_T_STRLEN;
  /* FLOATVAL  */
  struct psi_token * PSI_T_FLOATVAL;
  /* ARRVAL  */
  struct psi_token * PSI_T_ARRVAL;
  /* OBJVAL  */
  struct psi_token * PSI_T_OBJVAL;
  /* COUNT  */
  struct psi_token * PSI_T_COUNT;
  /* CALLOC  */
  struct psi_token * PSI_T_CALLOC;
  /* TO_BOOL  */
  struct psi_token * PSI_T_TO_BOOL;
  /* TO_INT  */
  struct psi_token * PSI_T_TO_INT;
  /* TO_STRING  */
  struct psi_token * PSI_T_TO_STRING;
  /* TO_FLOAT  */
  struct psi_token * PSI_T_TO_FLOAT;
  /* TO_ARRAY  */
  struct psi_token * PSI_T_TO_ARRAY;
  /* TO_OBJECT  */
  struct psi_token * PSI_T_TO_OBJECT;
  /* COMMENT  */
  struct psi_token * PSI_T_COMMENT;
  /* WHITESPACE  */
  struct psi_token * PSI_T_WHITESPACE;
  /* NO_WHITESPACE  */
  struct psi_token * PSI_T_NO_WHITESPACE;
  /* CPP_HEADER  */
  struct psi_token * PSI_T_CPP_HEADER;
  /* CPP_ATTRIBUTE  */
  struct psi_token * PSI_T_CPP_ATTRIBUTE;
  /* CPP_EXTENSION  */
  struct psi_token * PSI_T_CPP_EXTENSION;
  /* CPP_PASTE  */
  struct psi_token * PSI_T_CPP_PASTE;
  /* CPP_INLINE  */
  struct psi_token * PSI_T_CPP_INLINE;
  /* CPP_RESTRICT  */
  struct psi_token * PSI_T_CPP_RESTRICT;
  /* CPP_ASM  */
  struct psi_token * PSI_T_CPP_ASM;
  /* binary_op_token  */
  struct psi_token * PSI_T_binary_op_token;
  /* unary_op_token  */
  struct psi_token * PSI_T_unary_op_token;
  /* name_token  */
  struct psi_token * PSI_T_name_token;
  /* any_noeol_token  */
  struct psi_token * PSI_T_any_noeol_token;
  /* lib  */
  struct psi_token * PSI_T_lib;
  /* cpp_message_token  */
  struct psi_token * PSI_T_cpp_message_token;
  /* cpp_include_token  */
  struct psi_token * PSI_T_cpp_include_token;
  /* cpp_header_token  */
  struct psi_token * PSI_T_cpp_header_token;
  /* cpp_no_arg_token  */
  struct psi_token * PSI_T_cpp_no_arg_token;
  /* cpp_name_arg_token  */
  struct psi_token * PSI_T_cpp_name_arg_token;
  /* cpp_exp_arg_token  */
  struct psi_token * PSI_T_cpp_exp_arg_token;
  /* cpp_special_name_token  */
  struct psi_token * PSI_T_cpp_special_name_token;
  /* constant_type_token  */
  struct psi_token * PSI_T_constant_type_token;
  /* impl_def_val_token  */
  struct psi_token * PSI_T_impl_def_val_token;
  /* decl_type_simple  */
  struct psi_token * PSI_T_decl_type_simple;
  /* decl_real_type  */
  struct psi_token * PSI_T_decl_real_type;
  /* int_signed  */
  struct psi_token * PSI_T_int_signed;
  /* int_width  */
  struct psi_token * PSI_T_int_width;
  /* decl_int_type  */
  struct psi_token * PSI_T_decl_int_type;
  /* int_signed_types  */
  struct psi_token * PSI_T_int_signed_types;
  /* signed_short_types  */
  struct psi_token * PSI_T_signed_short_types;
  /* signed_long_types  */
  struct psi_token * PSI_T_signed_long_types;
  /* int_width_types  */
  struct psi_token * PSI_T_int_width_types;
  /* enum_name  */
  struct psi_token * PSI_T_enum_name;
  /* union_name  */
  struct psi_token * PSI_T_union_name;
  /* struct_name  */
  struct psi_token * PSI_T_struct_name;
  /* optional_name  */
  struct psi_token * PSI_T_optional_name;
  /* impl_type_token  */
  struct psi_token * PSI_T_impl_type_token;
  /* let_func_token  */
  struct psi_token * PSI_T_let_func_token;
  /* callback_rval  */
  struct psi_token * PSI_T_callback_rval;
  /* set_func_token  */
  struct psi_token * PSI_T_set_func_token;
  /* assert_stmt_token  */
  struct psi_token * PSI_T_assert_stmt_token;
  /* impl_stmt  */
  struct psi_token ** PSI_T_impl_stmt;
#line 671 "src/parser_proc.h" /* glr.c:197  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int psi_parser_proc_parse (struct psi_parser *P, struct psi_plist *tokens, size_t *index);

#endif /* !YY_PSI_PARSER_PROC_SRC_PARSER_PROC_H_INCLUDED  */
