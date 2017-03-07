/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton implementation for Bison GLR parsers in C

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

/* C GLR parser skeleton written by Paul Hilfinger.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1


/* "%code top" blocks.  */
#line 1 "src/parser_proc_grammar.y" /* glr.c:222  */

#include "php_psi_stdinc.h"

#line 54 "src/parser_proc.c" /* glr.c:222  */


/* Substitute the variable and function names.  */
#define yyparse psi_parser_proc_parse
#define yylex   psi_parser_proc_lex
#define yyerror psi_parser_proc_error
#define yydebug psi_parser_proc_debug


/* First part of user declarations.  */

#line 66 "src/parser_proc.c" /* glr.c:240  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser_proc.h"

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Default (constant) value used for initialization for null
   right-hand sides.  Unlike the standard yacc.c template, here we set
   the default value of $$ to a zeroed-out value.  Since the default
   value is undefined, this behavior is technically correct.  */
static YYSTYPE yyval_default;

/* Copy the second part of user declarations.  */

#line 94 "src/parser_proc.c" /* glr.c:263  */
/* Unqualified %code blocks.  */
#line 5 "src/parser_proc_grammar.y" /* glr.c:264  */

#include <assert.h>
#include <stdarg.h>

#include "plist.h"
#include "parser.h"
#define YYDEBUG 1

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
static inline void psi_parser_proc_add_from_typedef(struct psi_parser *P, struct psi_decl_arg *def)
{
	if (def->type->real.def) {
		switch (def->type->type) {
		case PSI_T_STRUCT:
			psi_parser_proc_add_struct(P, def->type->real.strct);
			break;
		case PSI_T_UNION:
			psi_parser_proc_add_union(P, def->type->real.unn);
			break;
		case PSI_T_ENUM:
			psi_parser_proc_add_enum(P, def->type->real.enm);
			break;
		default:
			break;
		}
	}
}
static inline void psi_parser_proc_add_typedef(struct psi_parser *P, struct psi_decl_arg *def)
{
	assert(def);
	if (!P->types) {
		P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	P->types = psi_plist_add(P->types, &def);
	
	psi_parser_proc_add_from_typedef(P, def);
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
	if (!P->decls) {
		P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
	}
	P->decls = psi_plist_add(P->decls, &decl);
}
static inline void psi_parser_proc_add_impl(struct psi_parser *P, struct psi_impl *impl) {
	assert(impl);
	if (!P->impls) {
		P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	P->impls = psi_plist_add(P->impls, &impl);
}

/* end code */

#line 185 "src/parser_proc.c" /* glr.c:264  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YYFREE
# define YYFREE free
#endif
#ifndef YYMALLOC
# define YYMALLOC malloc
#endif
#ifndef YYREALLOC
# define YYREALLOC realloc
#endif

#define YYSIZEMAX ((size_t) -1)

#ifdef __cplusplus
   typedef bool yybool;
#else
   typedef unsigned char yybool;
#endif
#define yytrue 1
#define yyfalse 0

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify clang.  */
# define YYLONGJMP(Env, Val) (longjmp (Env, Val), YYASSERT (0))
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#ifndef YYASSERT
# define YYASSERT(Condition) ((void) ((Condition) || (abort (), 0)))
#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  129
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2029

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  123
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  110
/* YYNRULES -- Number of rules.  */
#define YYNRULES  429
/* YYNRULES -- Number of states.  */
#define YYNSTATES  629
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 13
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   377

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     387,   387,   387,   387,   388,   388,   388,   388,   388,   388,
     388,   388,   388,   388,   388,   388,   388,   388,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   389,   389,   389,   389,   389,   389,   389,   389,
     389,   389,   393,   394,   397,   398,   401,   402,   403,   404,
     410,   418,   421,   424,   427,   430,   433,   436,   442,   448,
     454,   477,   481,   485,   490,   495,   499,   506,   507,   511,
     512,   513,   517,   518,   522,   523,   527,   528,   529,   533,
     534,   538,   543,   548,   556,   559,   563,   568,   576,   579,
     583,   587,   594,   598,   602,   606,   616,   626,   631,   636,
     642,   651,   654,   658,   662,   668,   675,   681,   682,   683,
     684,   688,   691,   698,   699,   700,   701,   702,   706,   712,
     713,   721,   731,   739,   750,   753,   757,   761,   765,   770,
     775,   783,   784,   785,   788,   794,   797,   800,   806,   807,
     808,   809,   810,   811,   812,   813,   817,   818,   822,   825,
     828,   834,   837,   840,   848,   860,   863,   866,   873,   876,
     886,   889,   892,   895,   896,   900,   903,   906,   917,   923,
     930,   938,   945,   956,   957,   961,   967,   977,   987,  1000,
    1001,  1013,  1016,  1019,  1022,  1028,  1031,  1041,  1054,  1059,
    1067,  1077,  1087,  1090,  1094,  1100,  1103,  1109,  1117,  1124,
    1127,  1133,  1138,  1146,  1150,  1154,  1158,  1162,  1169,  1173,
    1177,  1181,  1188,  1201,  1214,  1227,  1230,  1237,  1240,  1246,
    1250,  1257,  1260,  1266,  1269,  1275,  1278,  1290,  1293,  1300,
    1305,  1310,  1320,  1323,  1329,  1332,  1338,  1345,  1352,  1353,
    1354,  1355,  1356,  1357,  1358,  1359,  1360,  1364,  1367,  1373,
    1376,  1379,  1382,  1385,  1391,  1395,  1403,  1404,  1408,  1415,
    1418,  1421,  1424,  1427,  1433,  1437,  1445,  1452,  1460,  1468,
    1469,  1470,  1471,  1472,  1473,  1474,  1475,  1476,  1477,  1481,
    1484,  1490,  1493,  1499,  1500,  1504,  1507,  1513,  1516,  1522,
    1529,  1536,  1539,  1542,  1549,  1554,  1562,  1563,  1564,  1565,
    1566,  1567,  1568,  1569,  1573,  1576,  1582,  1585,  1591,  1598,
    1599,  1603,  1610,  1613,  1619,  1627,  1630,  1636,  1639,  1645
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "BOOL", "CHAR", "SHORT",
  "INT", "SIGNED", "UNSIGNED", "LONG", "FLOAT", "DOUBLE", "STRING",
  "MIXED", "ARRAY", "OBJECT", "CALLABLE", "VOID", "ZVAL", "INT8", "UINT8",
  "INT16", "UINT16", "INT32", "UINT32", "INT64", "UINT64", "NULL", "TRUE",
  "FALSE", "NAME", "NSNAME", "DOLLAR_NAME", "NUMBER", "QUOTED_STRING",
  "QUOTED_CHAR", "\"end of line\"", "\";\"", "\"(\"", "\")\"", "\",\"",
  "\":\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\"=\"", "\"#\"", "\"|\"",
  "\"^\"", "\"&\"", "\"<<\"", "\">>\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"",
  "\"%\"", "\"<\"", "\">\"", "\">=\"", "\"<=\"", "\"||\"", "\"&&\"",
  "\"==\"", "\"!=\"", "\"~\"", "\"!\"", "\".\"", "\"\\\\\"", "\"...\"",
  "ERROR", "WARNING", "IF", "IFDEF", "IFNDEF", "ELSE", "ELIF", "ENDIF",
  "DEFINE", "DEFINED", "UNDEF", "IMPORT", "INCLUDE", "INCLUDE_NEXT",
  "TYPEDEF", "STRUCT", "UNION", "ENUM", "CONST", "LIB", "STATIC",
  "CALLBACK", "FUNCTION", "LET", "SET", "TEMP", "FREE", "RETURN",
  "PRE_ASSERT", "POST_ASSERT", "BOOLVAL", "INTVAL", "STRVAL", "PATHVAL",
  "STRLEN", "FLOATVAL", "ARRVAL", "OBJVAL", "COUNT", "CALLOC", "TO_BOOL",
  "TO_INT", "TO_STRING", "TO_FLOAT", "TO_ARRAY", "TO_OBJECT", "COMMENT",
  "WHITESPACE", "NO_WHITESPACE", "CPP_HEADER", "BINARY", "UNARY",
  "$accept", "binary_op_token", "unary_op_token", "name_token",
  "any_noeol_token", "file", "blocks", "block", "lib", "cpp", "cpp_exp",
  "cpp_message_token", "cpp_include_token", "cpp_header_token",
  "cpp_no_arg_token", "cpp_name_arg_token", "cpp_exp_arg_token",
  "cpp_macro_decl", "cpp_macro_sig", "cpp_macro_sig_args",
  "cpp_macro_decl_tokens", "cpp_macro_decl_token_list", "cpp_macro_exp",
  "cpp_macro_call_args", "cpp_macro_call_arg_list", "constant",
  "constant_type", "constant_type_token", "impl_def_val",
  "impl_def_val_token", "decl_typedef", "typedef", "const_decl_type",
  "decl_type", "decl_type_complex", "decl_type_simple", "decl_real_type",
  "decl_stdint_type", "int_signed", "int_width", "decl_int_type",
  "int_signed_types", "signed_short_types", "signed_long_types",
  "int_width_types", "decl_stmt", "decl", "decl_fn", "decl_functor",
  "decl_func", "decl_args", "decl_arg", "decl_var", "decl_union",
  "decl_struct", "decl_struct_args", "struct_args_block", "struct_args",
  "struct_arg", "decl_enum", "decl_enum_items", "decl_enum_item",
  "num_exp", "number", "enum_name", "union_name", "struct_name",
  "optional_name", "decl_layout", "align_and_size", "array_size",
  "indirection", "pointers", "impl", "impl_func", "impl_args", "impl_arg",
  "impl_var", "impl_type", "impl_type_token", "impl_stmts", "impl_stmt",
  "let_stmt", "let_exp", "let_exp_byref", "let_exp_assign", "let_calloc",
  "let_callback", "let_func", "let_func_token", "let_func_exps",
  "let_exps", "callback_rval", "callback_arg_list", "callback_args",
  "return_stmt", "set_stmt", "set_exp", "set_func", "set_func_token",
  "set_func_exps", "set_exps", "assert_stmt", "assert_stmt_token",
  "free_stmt", "free_exps", "free_exp", "decl_vars", "reference", "byref", YY_NULLPTR
};
#endif

#define YYPACT_NINF -490
#define YYTABLE_NINF -428

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     925,  -490,  -490,  -490,  -490,  -490,    54,  -490,  -490,  1321,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  1695,  -490,
    -490,  1423,  1722,  1473,  1473,  1473,  1568,     0,   -50,    -3,
    -490,    45,   925,  -490,  -490,  -490,  -490,  -490,   347,  -490,
    -490,  -490,  -490,  -490,    82,    97,  -490,  -490,    19,    28,
    -490,  -490,  -490,  -490,  -490,  -490,    40,  -490,    42,  -490,
    -490,  -490,  -490,  -490,  -490,    55,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  1332,  -490,
    1473,  1473,  1473,  1795,    31,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,   885,  -490,  -490,  -490,  -490,    87,   697,
     -12,  -490,  1155,  1251,  1473,  1473,    88,  -490,    89,  1473,
      99,    99,    75,    75,   108,  -490,  -490,   122,   126,  -490,
      55,   128,  -490,  -490,   114,   118,  -490,   134,  -490,  -490,
    -490,   123,  -490,   130,  1378,  -490,   171,  -490,    35,  -490,
    -490,    82,  -490,  -490,  1749,  1473,   384,  1473,   124,    55,
    -490,  -490,  -490,  -490,  -490,  1749,   697,   579,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,   697,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  1251,  -490,  -490,  -490,  -490,  1441,
    1251,   140,  1964,    38,  -490,    38,  -490,  -490,  -490,   139,
     146,   146,    -2,    -2,  1368,   136,  -490,   384,   151,   157,
    -490,    55,   123,  -490,  -490,  -490,  -490,  -490,  -490,    55,
    1822,   347,    50,  -490,   145,    14,  -490,   347,   812,   347,
    1473,    59,  -490,  -490,   120,  -490,  -490,  -490,  -490,  -490,
     337,  -490,   153,  1473,    67,  -490,   156,  -490,  -490,  1866,
    1473,  -490,  -490,  1251,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  1251,   158,  1722,   347,   347,  -490,  -490,  -490,
    -490,    55,  -490,     3,   234,    36,   150,  1473,  -490,  1378,
      55,  1378,   123,  1595,   337,  1473,  -490,   154,   162,  -490,
     166,  -490,  -490,  -490,  1025,  -490,  -490,  -490,  -490,  -490,
    -490,   337,  -490,  1964,  -490,   176,   192,  -490,   193,   198,
     187,   196,    18,  -490,  -490,   200,  -490,  -490,  1839,  -490,
     199,   123,  1622,  1473,  -490,   209,  1964,   210,   211,  -490,
     206,   212,   979,  -490,  -490,  -490,  1473,  -490,  -490,  -490,
    -490,  -490,   213,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -490,  -490,  -490,  -490,   216,    74,  -490,    -3,  -490,  -490,
     219,  1378,  -490,    55,   221,  -490,  1964,  -490,  1098,  -490,
     222,  1849,   223,  1893,  -490,   337,   812,  -490,   347,  -490,
      -3,   347,  -490,  1473,  -490,  -490,  -490,  -490,   224,  -490,
     226,   227,  -490,  -490,  1251,   228,   225,   215,  -490,  -490,
     232,  -490,   505,   231,   505,   233,  -490,   123,   235,  -490,
     104,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,   236,
     240,  1964,  -490,  -490,  -490,  -490,   242,  1206,   337,  -490,
    -490,  -490,   244,   347,  -490,    79,  -490,   123,   697,  1473,
    1964,   252,   248,  -490,  -490,  -490,   505,  -490,    -3,     3,
    -490,  -490,  -490,  -490,  -490,   249,   337,    -3,  -490,  -490,
     131,   251,   255,  -490,   347,  -490,  -490,  -490,   254,   264,
    -490,    -6,  -490,    -3,  1946,   260,   262,  -490,   263,  -490,
    -490,  -490,  -490,   265,   256,   266,   337,  1098,   268,  -490,
     812,   269,   270,   459,  1920,   154,  -490,  -490,  -490,   271,
    1206,  -490,  -490,   273,   272,   276,   278,  -490,  -490,  1098,
    -490,  -490,   505,   277,   812,  -490,  -490,  -490,  -490
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short int yydefact[] =
{
     152,   261,   258,   262,   256,   257,   259,   245,   246,     0,
     248,   249,   250,   251,   252,   253,   254,   255,   244,   157,
     156,     0,     0,     0,     0,   325,     0,     0,     0,   427,
     158,     0,   153,   154,   160,   159,   161,   163,   333,   235,
     237,   236,   242,   243,   265,   275,   241,   162,     0,     0,
     284,   283,   289,   165,   164,   166,     0,   167,     0,   260,
     247,    37,    33,    31,    24,   333,   335,    35,    36,    32,
      30,    28,    27,    25,    26,    34,    29,   290,     0,   244,
       0,     0,     0,     0,     0,   177,   178,   189,   186,   187,
     184,   190,   185,     0,   188,   179,   180,   181,     0,   198,
       0,   172,     0,     0,   325,   325,     0,   230,   229,     0,
     329,   329,   238,   239,   240,   322,   217,   262,   245,   220,
       0,     0,   216,   234,     0,     0,   429,     0,   428,     1,
     155,   331,   295,     0,   334,   266,   270,   268,   272,   263,
     276,   265,   264,   278,   291,     0,     0,     0,   334,   333,
     336,   297,   238,   239,   240,   291,   198,   198,   175,   169,
      71,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   200,   170,   199,   182,   183,   171,
     174,   173,   207,   208,     0,    22,    23,    20,    21,     0,
       0,   209,   176,   238,   324,   239,   323,   228,   231,     0,
       0,     0,     0,     0,     0,     0,   168,     0,     0,     0,
     299,   333,   331,   271,   267,   273,   274,   269,   277,   292,
       0,     0,     0,   293,   311,     0,   309,     0,   427,     0,
       0,     0,   419,   420,     0,   357,   360,   359,   361,   362,
       0,   363,     0,     0,     0,   193,     0,   192,   201,     0,
       0,   205,   203,   211,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    13,    12,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,   302,   301,   303,
     300,   333,   296,   221,     0,     0,     0,     0,   298,     0,
       0,     0,   331,     0,     0,     0,   308,     0,     0,   413,
      31,   319,   318,   320,     0,   411,   409,   408,   410,   407,
     406,     0,   321,   402,   313,     0,     0,   401,     0,     0,
       0,     0,     0,   422,   412,     0,   337,   358,     0,   288,
       0,   331,     0,   194,   202,     0,   213,     0,   212,   204,
       0,   327,     0,   305,   233,   232,     0,   223,   225,   226,
     224,   227,     0,   222,   338,   350,   351,   352,   353,   349,
     354,   355,   356,   348,     0,     0,   342,   427,   347,   332,
       0,     0,   279,     0,     0,   294,   312,   310,     0,   364,
      24,     0,     0,     0,   317,     0,   427,   400,     0,   346,
     427,     0,   421,     0,   399,   418,   287,   281,     0,   196,
       0,   195,   206,   210,     0,     0,     0,     0,   304,   306,
       0,   215,     0,     0,     0,   344,   285,   331,    31,   369,
      30,   387,   386,   384,   382,   383,   385,   381,   380,    34,
      29,   373,   374,   370,   371,   372,     0,     0,     0,   315,
     316,   403,   414,     0,   425,     0,   423,   331,   198,     0,
     214,     0,     0,   307,   286,   339,     0,   343,   427,   221,
     280,   393,   379,   388,   394,     0,     0,   427,   375,   314,
     427,     0,     0,   424,     0,   282,   191,   197,     0,     0,
     340,     0,   345,   427,     0,   389,     0,   416,   415,   404,
     365,   426,   330,     0,     0,     0,     0,     0,     0,   405,
     427,     0,     0,   395,     0,   321,   391,   368,   366,   390,
       0,   378,   417,     0,     0,     0,   396,   397,   376,     0,
     367,   328,     0,     0,   427,   392,   341,   377,   398
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -490,  -281,   -97,    -8,    43,  -490,  -490,   288,  -490,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,  -490,
    -149,  -490,  -272,  -490,  -490,  -490,  -490,  -490,  -249,  -490,
    -490,   299,  -134,   -21,  -490,  -490,  -490,  -490,   279,  -490,
    -490,   182,  -490,  -490,  -490,  -490,    27,   308,  -490,  -490,
     172,   -20,   -38,  -490,  -490,    33,  -171,  -490,  -103,    29,
    -490,   -54,  -302,  -490,  -490,  -490,  -490,    37,  -490,    34,
    -293,   -56,    -5,  -490,   315,  -490,  -170,  -447,  -489,  -490,
      39,  -306,  -490,  -271,  -454,    20,  -490,  -490,  -490,  -169,
    -490,  -490,  -490,  -490,  -490,  -490,  -490,  -472,    21,  -490,
    -490,  -490,  -490,  -490,  -490,  -490,  -140,  -490,   -26,  -465
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,   485,   411,   131,   274,    31,    32,    33,    34,    35,
      98,    99,   100,   279,   101,   102,   103,   158,   500,   501,
     275,   276,   292,   437,   438,    36,   121,   122,   452,   453,
      37,   441,    38,    39,    40,    41,    42,    43,    44,    45,
      46,   139,   314,   317,   142,    47,   107,    49,    50,    51,
     322,    52,   412,    53,    54,   378,   379,   442,   443,   109,
     325,   326,   413,   414,    56,   110,   111,   115,   507,   300,
     310,   133,   391,    57,    58,   465,   466,   415,   467,   468,
     334,   335,   336,   606,   607,   608,   533,   534,   535,   536,
     598,   609,   565,   615,   616,   337,   338,   416,   417,   418,
     571,   588,   339,   340,   341,   422,   423,   545,   419,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
     132,    77,   108,   127,    78,   123,   290,   345,   347,   147,
     321,   372,   349,   537,   541,   112,   113,   114,   352,   388,
     515,   321,   277,   555,   532,   558,   489,    48,   427,    55,
     447,   448,   449,   134,   124,   377,   450,   451,   428,   455,
     374,   315,   456,    29,   316,   129,   457,   126,   458,   459,
     460,   461,   462,   463,   395,   492,   143,   396,   493,    48,
     148,    55,   123,    59,   594,    60,   144,   580,   372,   155,
     151,   372,   152,   153,   154,   464,   399,   424,   427,  -326,
    -326,   436,   145,   568,   146,   157,   135,   136,   137,   392,
     393,   138,   476,   343,   281,   291,   293,   295,   587,   472,
     439,   298,   483,   140,     4,     5,   431,   432,   278,   484,
      66,   515,  -329,   513,   514,   304,   299,  -329,   573,   574,
     585,   561,   562,   159,   323,   297,   312,  -289,   612,   375,
     376,   617,   610,   626,    61,   323,   595,   324,   497,   342,
     299,   294,   296,    62,   148,   301,   302,   303,   399,   400,
    -326,   306,   628,  -218,   610,   372,   620,  -219,   372,   305,
     307,    64,   401,   426,   402,   308,   403,   309,   311,   404,
     405,   406,   407,   408,   409,   410,   531,   313,   353,   150,
     373,   126,   383,   540,   285,   286,    66,   290,   374,   385,
     386,   394,   429,   290,   433,   469,   440,   287,   288,   479,
     478,   586,    67,    68,  -412,   521,   522,   523,   524,   525,
     526,   527,   528,   563,   327,   328,   329,   330,   331,   332,
     333,    69,   486,    70,   560,    71,    72,    73,    74,   487,
     489,   488,   550,   490,   491,   531,   569,   494,   496,   505,
      75,    76,   405,   406,   407,   408,   409,   410,   502,   503,
     511,   504,   553,   506,   575,   387,   290,   512,   516,   321,
     517,   -24,   538,   547,   584,   548,   552,   549,   551,   372,
     482,   554,   556,  -379,  -388,   290,   291,   454,   566,   559,
     567,   351,   291,   132,   570,   578,   579,   583,   602,   397,
     589,   420,   590,   592,   604,   531,   382,   593,   321,   123,
     597,   599,   613,   600,   603,   601,   148,   611,   531,   614,
     582,   619,   621,   622,   389,   623,   627,   531,   624,   348,
     130,   106,   421,   318,   141,   446,    84,   344,   327,   328,
     329,   330,   331,   332,   333,   430,   380,   444,   445,   509,
      61,   477,   435,   125,   557,   291,   384,   398,   625,    62,
      61,   564,   425,   546,   108,    63,     0,     0,     0,    62,
       0,     0,     0,     0,   291,    63,     0,    64,   401,     0,
     402,     0,   403,   475,     0,   404,   148,    64,     0,   470,
       0,   151,     0,   312,     0,   471,     0,   324,     0,     0,
     285,   286,    66,     0,     0,     0,     0,     0,     0,   576,
       0,     0,    66,   287,   288,     0,     0,   290,    67,    68,
       0,     0,   475,     0,     0,     0,     0,     0,    67,    68,
       0,     0,   108,     0,     0,   499,     0,    69,     0,    70,
       0,    71,    72,    73,    74,     0,     0,    69,   510,    70,
       0,    71,    72,    73,    74,     0,    75,    76,     0,     0,
     542,     0,     0,   544,     0,     0,    75,    76,     0,     0,
     123,     0,    61,   382,   543,     0,     0,     0,   389,     0,
       0,    62,     0,     0,     0,     0,   399,   400,   327,   328,
     329,   330,   331,   332,   333,   421,     0,     0,     0,    64,
     401,  -427,   402,     0,   403,     0,   291,   404,     0,     0,
       0,     0,     0,     0,     0,   572,     0,     0,   455,   126,
       0,   456,   285,   286,    66,   457,     0,   458,   459,   460,
     461,   462,   463,     0,     0,   287,   288,     0,     0,     0,
      67,    68,   581,     0,     0,     0,   591,     0,     0,     0,
       0,   577,     0,     0,     0,     0,     0,     0,     0,    69,
       0,    70,     0,    71,    72,    73,    74,     0,     0,   605,
       0,     0,     0,     0,     0,     0,     0,     0,    75,    76,
     405,   406,   407,   408,   409,   410,     0,     0,     0,   160,
       0,   605,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,     0,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   239,     0,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   160,   346,   273,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,     0,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
     239,     0,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,    61,     0,   273,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,   399,
     400,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,   401,     0,   402,     0,   403,     0,     0,
     404,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   126,     0,     0,   285,   286,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   287,   288,
       0,     0,     0,    67,    68,     0,     0,     0,    61,     0,
       0,     0,     0,     0,     0,     0,     0,    62,     0,     0,
       0,     0,    69,    63,    70,     0,    71,    72,    73,    74,
       0,     0,   156,     0,     0,    64,     0,     0,     0,     0,
       0,    75,    76,   405,   406,   407,   408,   409,   410,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     9,     0,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,    18,    67,    68,     0,     0,
       0,    19,    20,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,    69,     0,    70,     0,    71,
      72,    73,    74,     1,     2,     3,     4,     5,     6,     7,
       8,     0,     0,     0,    75,    76,     9,     0,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,    18,
      22,    23,    24,    25,    26,    27,    28,     0,    29,     0,
       0,     0,   508,     0,     0,     0,     0,     0,    61,     1,
       2,     3,     4,     5,     6,     7,     8,    62,     0,     0,
       0,     0,    30,    63,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,   480,   401,     0,   402,     0,
     403,     0,     0,   404,     0,   104,   105,    25,    83,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   285,   286,
      66,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   287,   288,     0,     0,     0,    67,    68,     0,     0,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
      62,    80,    81,    82,   481,    69,   518,    70,     0,    71,
      72,    73,    74,     0,     0,   519,     0,     0,    64,   401,
       0,   402,     0,   403,    75,    76,   404,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,     0,
       0,   285,   286,    66,     0,     0,     0,     0,    61,     0,
       0,     0,     0,     0,   287,   288,     0,    62,     0,    67,
      68,     0,     0,    63,     0,     0,     0,     0,     0,     0,
       0,     0,   280,     0,     0,    64,     0,     0,    69,     0,
     520,     0,    71,    72,    73,    74,     0,     0,     0,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,    61,
       0,     0,     0,     0,     0,     0,     0,     0,    62,     0,
       0,     0,     0,     0,   518,     0,    67,    68,     0,     0,
       0,     0,     0,   519,     0,     0,    64,   401,     0,   402,
       0,   403,     0,     0,   404,    69,     0,    70,     0,    71,
      72,    73,    74,     0,    61,     0,     0,     0,     0,   285,
     286,    66,     0,    62,    75,    76,     0,     0,     0,    63,
       0,     0,   287,   288,     0,     0,     0,    67,    68,     0,
       0,    64,     0,     0,   282,     0,   283,     0,     0,   284,
       0,     0,     0,     0,     0,     0,    69,     0,   520,     0,
      71,    72,    73,    74,   285,   286,     0,   521,   522,   523,
     524,   525,   526,   527,   528,   529,   530,   287,   288,     0,
       0,     0,    67,    68,    61,     0,     0,     0,     0,     0,
       0,   289,     0,    62,     0,    61,     0,     0,     0,    63,
       0,    69,     0,    70,    62,    71,    72,    73,    74,     0,
      63,    64,     0,     0,     0,     0,     0,     0,     0,    65,
      75,    76,    64,     0,     0,     0,     0,     0,     0,     0,
     149,    61,     0,     0,     0,     0,    66,     0,     0,     0,
      62,    61,     0,     0,     0,     0,    63,   150,     0,     0,
      62,     0,    67,    68,     0,     0,    63,     0,    64,     0,
       0,     0,     0,    67,    68,     0,   381,     0,    64,     0,
       0,    69,     0,    70,     0,    71,    72,    73,    74,     0,
       0,     0,    69,   150,    70,     0,    71,    72,    73,    74,
      75,    76,     0,   150,     0,     0,     0,     0,     0,    67,
      68,    75,    76,     0,    61,     0,     0,     0,     0,    67,
      68,     0,     0,    62,     0,     0,     0,     0,    69,    63,
      70,     0,    71,    72,    73,    74,     0,     0,    69,     0,
      70,    64,    71,    72,    73,    74,    61,    75,    76,   350,
       0,     0,     0,     0,     0,    62,     0,    75,    76,     0,
       0,    63,     0,     0,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    64,    94,    95,    96,    97,     0,     0,
       0,     0,    67,    68,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    69,     0,    70,     0,    71,    72,    73,    74,     0,
       0,     0,     0,     0,    67,    68,     0,     0,     0,     0,
      75,    76,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    69,     0,    70,     0,    71,    72,    73,
      74,   116,     1,     2,   117,     4,     5,     6,   118,     8,
     119,     0,    75,    76,     0,   120,     0,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,    79,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,     0,
       0,     0,   473,     0,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,    79,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,     0,     0,     0,   473,
       0,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,    79,     0,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,   474,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    80,    81,    82,   320,     0,     0,     0,     0,     0,
       0,     0,   498,     0,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,    80,    81,
      82,   320,     9,     0,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,    79,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,     0,     0,     0,     9,
       0,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,    18,     1,     2,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,   319,     0,    10,    11,
      12,    13,    14,    15,    16,    17,     0,     0,     0,    79,
       0,    80,    81,    82,    83,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,   104,   105,
      25,    83,   120,     0,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,    79,     1,     2,     3,     4,
       5,     6,     7,     8,     0,    80,    81,    82,   320,   390,
       0,    10,    11,    12,    13,    14,    15,    16,    17,     0,
       0,     0,    79,     1,     2,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     0,     0,    10,    11,
      12,    13,    14,    15,    16,    17,   495,     0,     0,    79,
       0,    80,    81,    82,     0,     0,     0,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     367,   368,   369,   370,   371,   434,     0,     0,    80,    81,
      82,     0,     0,     0,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   539,     0,     0,    80,    81,    82,     0,     0,
       0,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   367,   368,   369,   370,   371,   618,
       0,     0,     0,     0,     0,     0,     0,     0,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,   369,   370,   371,   596,     0,     0,     0,
       0,     0,     0,     0,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   369,
     370,   371,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   369,   370,   371
};

static const short int yycheck[] =
{
      38,     9,    22,    29,     9,    26,   103,   156,   157,    65,
     144,   292,   284,   478,   486,    23,    24,    25,   290,   312,
     467,   155,    34,   512,   478,   514,    32,     0,   334,     0,
      27,    28,    29,    38,    34,    37,    33,    34,   340,     3,
      42,     6,     6,    93,     9,     0,    10,    50,    12,    13,
      14,    15,    16,    17,    40,    37,    37,    43,    40,    32,
      65,    32,    83,     9,    70,    11,    38,   556,   349,    38,
      78,   352,    80,    81,    82,    39,    17,    18,   384,    41,
      42,   353,    42,   537,    42,    93,     4,     5,     6,    39,
      40,     9,   394,   149,   102,   103,   104,   105,   570,   392,
     372,   109,   404,     6,     7,     8,    39,    40,   120,   411,
      55,   558,    37,    39,    40,   120,    41,    42,    39,    40,
     567,    17,    18,    36,   144,    37,   134,    38,   600,   300,
     301,   603,   597,   622,     3,   155,   583,   145,   431,   147,
      41,   104,   105,    12,   149,   111,   112,   113,    17,    18,
      42,    37,   624,    31,   619,   436,   610,    31,   439,    31,
      42,    30,    31,    43,    33,    31,    35,    44,    38,    38,
     111,   112,   113,   114,   115,   116,   478,     6,    38,    55,
      41,    50,    46,   485,    53,    54,    55,   284,    42,    38,
      33,    46,    39,   290,    38,    45,    38,    66,    67,    37,
      46,    70,    71,    72,    38,   101,   102,   103,   104,   105,
     106,   107,   108,   109,    94,    95,    96,    97,    98,    99,
     100,    90,    46,    92,   517,    94,    95,    96,    97,    37,
      32,    38,   504,    46,    38,   537,   538,    37,    39,    33,
     109,   110,   111,   112,   113,   114,   115,   116,    39,    39,
      37,    40,    37,    41,   547,   311,   353,    41,    39,   393,
      39,    39,    39,    39,   566,    39,    41,    40,    40,   550,
     404,    39,    41,    38,    38,   372,   284,    43,    38,    46,
      38,   289,   290,   321,    40,    33,    38,    38,    32,   327,
      39,   329,    37,    39,   596,   597,   304,    33,   432,   320,
      40,    39,    33,    40,    38,    40,   311,    39,   610,    39,
     559,    40,    39,    41,   319,    39,    39,   619,    40,   276,
      32,    22,   330,   141,    45,   381,    18,   155,    94,    95,
      96,    97,    98,    99,   100,   343,   303,   375,   376,   442,
       3,   395,   350,    28,   514,   353,   307,   327,   619,    12,
       3,   520,   331,   493,   374,    18,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,   372,    18,    -1,    30,    31,    -1,
      33,    -1,    35,   393,    -1,    38,   381,    30,    -1,   387,
      -1,   389,    -1,   391,    -1,   390,    -1,   395,    -1,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,   548,
      -1,    -1,    55,    66,    67,    -1,    -1,   504,    71,    72,
      -1,    -1,   432,    -1,    -1,    -1,    -1,    -1,    71,    72,
      -1,    -1,   442,    -1,    -1,   433,    -1,    90,    -1,    92,
      -1,    94,    95,    96,    97,    -1,    -1,    90,   446,    92,
      -1,    94,    95,    96,    97,    -1,   109,   110,    -1,    -1,
     488,    -1,    -1,   491,    -1,    -1,   109,   110,    -1,    -1,
     481,    -1,     3,   471,   490,    -1,    -1,    -1,   473,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    94,    95,
      96,    97,    98,    99,   100,   493,    -1,    -1,    -1,    30,
      31,    32,    33,    -1,    35,    -1,   504,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   543,    -1,    -1,     3,    50,
      -1,     6,    53,    54,    55,    10,    -1,    12,    13,    14,
      15,    16,    17,    -1,    -1,    66,    67,    -1,    -1,    -1,
      71,    72,   558,    -1,    -1,    -1,   574,    -1,    -1,    -1,
      -1,   549,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,
      -1,    92,    -1,    94,    95,    96,    97,    -1,    -1,   597,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,   110,
     111,   112,   113,   114,   115,   116,    -1,    -1,    -1,     0,
      -1,   619,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    -1,    83,    -1,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,     0,   119,   120,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      83,    -1,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,     3,    -1,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      -1,    -1,    -1,    71,    72,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    90,    18,    92,    -1,    94,    95,    96,    97,
      -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    71,    72,    -1,    -1,
      -1,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    90,    -1,    92,    -1,    94,
      95,    96,    97,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,   109,   110,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    -1,    -1,
      -1,    -1,   117,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    -1,    33,    -1,
      35,    -1,    -1,    38,    -1,    86,    87,    88,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,    -1,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    86,    87,    88,    89,    90,    18,    92,    -1,    94,
      95,    96,    97,    -1,    -1,    27,    -1,    -1,    30,    31,
      -1,    33,    -1,    35,   109,   110,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,     3,    -1,
      -1,    -1,    -1,    -1,    66,    67,    -1,    12,    -1,    71,
      72,    -1,    -1,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    90,    -1,
      92,    -1,    94,    95,    96,    97,    -1,    -1,    -1,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    -1,    18,    -1,    71,    72,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    -1,    30,    31,    -1,    33,
      -1,    35,    -1,    -1,    38,    90,    -1,    92,    -1,    94,
      95,    96,    97,    -1,     3,    -1,    -1,    -1,    -1,    53,
      54,    55,    -1,    12,   109,   110,    -1,    -1,    -1,    18,
      -1,    -1,    66,    67,    -1,    -1,    -1,    71,    72,    -1,
      -1,    30,    -1,    -1,    33,    -1,    35,    -1,    -1,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    90,    -1,    92,    -1,
      94,    95,    96,    97,    53,    54,    -1,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    66,    67,    -1,
      -1,    -1,    71,    72,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    80,    -1,    12,    -1,     3,    -1,    -1,    -1,    18,
      -1,    90,    -1,    92,    12,    94,    95,    96,    97,    -1,
      18,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
     109,   110,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,     3,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      12,     3,    -1,    -1,    -1,    -1,    18,    55,    -1,    -1,
      12,    -1,    71,    72,    -1,    -1,    18,    -1,    30,    -1,
      -1,    -1,    -1,    71,    72,    -1,    38,    -1,    30,    -1,
      -1,    90,    -1,    92,    -1,    94,    95,    96,    97,    -1,
      -1,    -1,    90,    55,    92,    -1,    94,    95,    96,    97,
     109,   110,    -1,    55,    -1,    -1,    -1,    -1,    -1,    71,
      72,   109,   110,    -1,     3,    -1,    -1,    -1,    -1,    71,
      72,    -1,    -1,    12,    -1,    -1,    -1,    -1,    90,    18,
      92,    -1,    94,    95,    96,    97,    -1,    -1,    90,    -1,
      92,    30,    94,    95,    96,    97,     3,   109,   110,    38,
      -1,    -1,    -1,    -1,    -1,    12,    -1,   109,   110,    -1,
      -1,    18,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    30,    81,    82,    83,    84,    -1,    -1,
      -1,    -1,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    -1,    92,    -1,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,    -1,    71,    72,    -1,    -1,    -1,    -1,
     109,   110,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    90,    -1,    92,    -1,    94,    95,    96,
      97,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,   109,   110,    -1,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    -1,
      -1,    -1,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,    -1,    86,    87,    88,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    86,    87,
      88,    89,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      -1,    86,    87,    88,    89,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    86,    87,
      88,    89,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    86,    87,    88,    89,    17,
      -1,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    30,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    26,    37,    -1,    -1,    30,
      -1,    86,    87,    88,    -1,    -1,    -1,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    39,    -1,    -1,    86,    87,
      88,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    39,    -1,    -1,    86,    87,    88,    -1,    -1,
      -1,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      19,    20,    21,    22,    23,    24,    25,    26,    30,    36,
      37,    47,    85,    86,    87,    88,    89,    90,    91,    93,
     117,   128,   129,   130,   131,   132,   148,   153,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   168,   169,   170,
     171,   172,   174,   176,   177,   182,   187,   196,   197,     9,
      11,     3,    12,    18,    30,    38,    55,    71,    72,    90,
      92,    94,    95,    96,    97,   109,   110,   126,   195,    30,
      86,    87,    88,    89,   170,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    81,    82,    83,    84,   133,   134,
     135,   137,   138,   139,    86,    87,   154,   169,   174,   182,
     188,   189,   126,   126,   126,   190,     3,     6,    10,    12,
      17,   149,   150,   156,    34,   197,    50,   231,   232,     0,
     130,   126,   175,   194,   195,     4,     5,     6,     9,   164,
       6,   161,   167,    37,    38,    42,    42,   194,   195,    38,
      55,   126,   126,   126,   126,    38,    27,   126,   140,    36,
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    83,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   120,   127,   143,   144,    34,   120,   136,
      27,   126,    33,    35,    38,    53,    54,    66,    67,    80,
     125,   126,   145,   126,   190,   126,   190,    37,   126,    41,
     192,   192,   192,   192,   195,    31,    37,    42,    31,    44,
     193,    38,   126,     6,   165,     6,     9,   166,   164,    17,
      89,   155,   173,   174,   126,   183,   184,    94,    95,    96,
      97,    98,    99,   100,   203,   204,   205,   218,   219,   225,
     226,   227,   126,   194,   173,   143,   119,   143,   127,   145,
      38,   126,   145,    38,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,   124,    41,    42,   179,   179,    37,   178,   179,
     178,    38,   126,    46,   203,    38,    33,   194,   193,   195,
      17,   195,    39,    40,    46,    40,    43,   175,   208,    17,
      18,    31,    33,    35,    38,   111,   112,   113,   114,   115,
     116,   125,   175,   185,   186,   200,   220,   221,   222,   231,
     175,   126,   228,   229,    18,   221,    43,   204,   185,    39,
     126,    39,    40,    38,    39,   126,   145,   146,   147,   145,
      38,   154,   180,   181,   175,   175,   194,    27,    28,    29,
      33,    34,   151,   152,    43,     3,     6,    10,    12,    13,
      14,    15,    16,    17,    39,   198,   199,   201,   202,    45,
     126,   195,   193,    17,    70,   174,   185,   184,    46,    37,
      30,    89,   155,   185,   185,   124,    46,    37,    38,    32,
      46,    38,    37,    40,    37,    37,    39,   193,    70,   126,
     141,   142,    39,    39,    40,    33,    41,   191,    43,   181,
     126,    37,    41,    39,    40,   200,    39,    39,    18,    27,
      92,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   185,   207,   209,   210,   211,   212,   232,    39,    39,
     185,   220,   175,   231,   175,   230,   229,    39,    39,    40,
     145,    40,    41,    37,    39,   201,    41,   199,   201,    46,
     193,    17,    18,   109,   212,   215,    38,    38,   207,   185,
      40,   223,   175,    39,    40,   193,   143,   126,    33,    38,
     201,   231,   151,    38,   185,   200,    70,   220,   224,    39,
      37,   175,    39,    33,    70,   200,    40,    40,   213,    39,
      40,    40,    32,    38,   185,   175,   206,   207,   208,   214,
     232,    39,   220,    33,    39,   216,   217,   220,    39,    40,
     207,    39,    41,    39,    40,   206,   201,    39,   220
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   125,   125,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   131,   132,
     133,   133,   133,   133,   133,   133,   133,   134,   134,   135,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   140,   140,   140,   141,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   146,   146,   147,   147,   148,   149,   150,   150,   150,
     150,   151,   151,   152,   152,   152,   152,   152,   153,   154,
     154,   154,   154,   154,   155,   155,   156,   156,   157,   157,
     157,   158,   158,   158,   158,   159,   159,   159,   160,   160,
     160,   160,   160,   160,   160,   160,   161,   161,   162,   162,
     162,   163,   163,   163,   163,   164,   164,   164,   164,   164,
     165,   165,   166,   166,   166,   167,   167,   167,   168,   169,
     169,   169,   169,   170,   170,   171,   171,   171,   171,   172,
     172,   173,   173,   173,   173,   174,   174,   174,   175,   175,
     176,   177,   178,   178,   179,   180,   180,   181,   182,   183,
     183,   184,   184,   185,   185,   185,   185,   185,   186,   186,
     186,   186,   187,   188,   189,   190,   190,   191,   191,   192,
     192,   193,   193,   194,   194,   195,   195,   196,   196,   197,
     197,   197,   198,   198,   199,   199,   200,   201,   202,   202,
     202,   202,   202,   202,   202,   202,   202,   203,   203,   204,
     204,   204,   204,   204,   205,   205,   206,   206,   206,   207,
     207,   207,   207,   207,   208,   208,   209,   210,   211,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   212,   213,
     213,   214,   214,   215,   215,   216,   216,   217,   217,   218,
     219,   220,   220,   220,   221,   221,   222,   222,   222,   222,
     222,   222,   222,   222,   223,   223,   224,   224,   225,   226,
     226,   227,   228,   228,   229,   230,   230,   231,   231,   232
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     2,     1,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     6,     2,     2,     0,     1,     1,     3,     0,     1,
       1,     2,     3,     2,     3,     2,     4,     1,     1,     1,
       4,     0,     1,     1,     3,     6,     1,     1,     1,     1,
       1,     0,     1,     1,     1,     1,     1,     1,     3,     1,
       1,     2,     4,     4,     2,     1,     1,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     0,     1,     2,     1,     2,
       0,     1,     0,     1,     1,     0,     1,     2,     2,     5,
       7,     6,     8,     1,     1,     6,     7,     6,     5,     1,
       2,     0,     1,     1,     3,     2,     4,     3,     3,     2,
       4,     4,     1,     1,     3,     1,     2,     3,     4,     1,
       3,     1,     3,     1,     4,     3,     3,     2,     1,     1,
       1,     1,     2,     2,     2,     0,     1,     0,     7,     0,
       7,     0,     3,     0,     1,     1,     2,     4,     5,     7,
       8,    13,     1,     3,     2,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     3,     6,     1,     2,     1,     1,
       1,     1,     1,     1,     3,     4,     6,     8,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     3,     1,     1,     0,     1,     1,     3,     3,
       3,     1,     1,     3,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     3,     3,     1,
       1,     3,     1,     3,     4,     1,     3,     0,     1,     1
};


/* YYDPREC[RULE-NUM] -- Dynamic precedence of rule #RULE-NUM (0 if none).  */
static const unsigned char yydprec[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYMERGER[RULE-NUM] -- Index of merging function for rule #RULE-NUM.  */
static const unsigned char yymerger[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYIMMEDIATE[RULE-NUM] -- True iff rule #RULE-NUM is not to be deferred, as
   in the case of predicates.  */
static const yybool yyimmediate[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned char yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   244,     0,   244,     0
};

/* Error token number */
#define YYTERROR 1




#undef yynerrs
#define yynerrs (yystackp->yyerrcnt)
#undef yychar
#define yychar (yystackp->yyrawchar)
#undef yylval
#define yylval (yystackp->yyval)
#undef yylloc
#define yylloc (yystackp->yyloc)
#define psi_parser_proc_nerrs yynerrs
#define psi_parser_proc_char yychar
#define psi_parser_proc_lval yylval
#define psi_parser_proc_lloc yylloc

static const int YYEOF = 0;
static const int YYEMPTY = -2;

typedef enum { yyok, yyaccept, yyabort, yyerr } YYRESULTTAG;

#define YYCHK(YYE)                              \
  do {                                          \
    YYRESULTTAG yychk_flag = YYE;               \
    if (yychk_flag != yyok)                     \
      return yychk_flag;                        \
  } while (0)

#if YYDEBUG

# ifndef YYFPRINTF
#  define YYFPRINTF fprintf
# endif

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YYDPRINTF(Args)                        \
  do {                                          \
    if (yydebug)                                \
      YYFPRINTF Args;                           \
  } while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (P);
  YYUSE (tokens);
  YYUSE (index);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, P, tokens, index);
  YYFPRINTF (yyoutput, ")");
}

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                  \
  do {                                                                  \
    if (yydebug)                                                        \
      {                                                                 \
        YYFPRINTF (stderr, "%s ", Title);                               \
        yy_symbol_print (stderr, Type, Value, P, tokens, index);        \
        YYFPRINTF (stderr, "\n");                                       \
      }                                                                 \
  } while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;

struct yyGLRStack;
static void yypstack (struct yyGLRStack* yystackp, size_t yyk)
  YY_ATTRIBUTE_UNUSED;
static void yypdumpstack (struct yyGLRStack* yystackp)
  YY_ATTRIBUTE_UNUSED;

#else /* !YYDEBUG */

# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)

#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYMAXDEPTH * sizeof (GLRStackItem)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Minimum number of free items on the stack allowed after an
   allocation.  This is to allow allocation and initialization
   to be completed by functions that call yyexpandGLRStack before the
   stack is expanded, thus insuring that all necessary pointers get
   properly redirected to new data.  */
#define YYHEADROOM 2

#ifndef YYSTACKEXPANDABLE
#  define YYSTACKEXPANDABLE 1
#endif

#if YYSTACKEXPANDABLE
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyexpandGLRStack (Yystack);                       \
  } while (0)
#else
# define YY_RESERVE_GLRSTACK(Yystack)                   \
  do {                                                  \
    if (Yystack->yyspaceLeft < YYHEADROOM)              \
      yyMemoryExhausted (Yystack);                      \
  } while (0)
#endif


#if YYERROR_VERBOSE

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static size_t
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      size_t yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return strlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

#endif /* !YYERROR_VERBOSE */

/** State numbers, as in LALR(1) machine */
typedef int yyStateNum;

/** Rule numbers, as in LALR(1) machine */
typedef int yyRuleNum;

/** Grammar symbol */
typedef int yySymbol;

/** Item references, as in LALR(1) machine */
typedef short int yyItemNum;

typedef struct yyGLRState yyGLRState;
typedef struct yyGLRStateSet yyGLRStateSet;
typedef struct yySemanticOption yySemanticOption;
typedef union yyGLRStackItem yyGLRStackItem;
typedef struct yyGLRStack yyGLRStack;

struct yyGLRState {
  /** Type tag: always true.  */
  yybool yyisState;
  /** Type tag for yysemantics.  If true, yysval applies, otherwise
   *  yyfirstVal applies.  */
  yybool yyresolved;
  /** Number of corresponding LALR(1) machine state.  */
  yyStateNum yylrState;
  /** Preceding state in this stack */
  yyGLRState* yypred;
  /** Source position of the last token produced by my symbol */
  size_t yyposn;
  union {
    /** First in a chain of alternative reductions producing the
     *  non-terminal corresponding to this state, threaded through
     *  yynext.  */
    yySemanticOption* yyfirstVal;
    /** Semantic value for this state.  */
    YYSTYPE yysval;
  } yysemantics;
};

struct yyGLRStateSet {
  yyGLRState** yystates;
  /** During nondeterministic operation, yylookaheadNeeds tracks which
   *  stacks have actually needed the current lookahead.  During deterministic
   *  operation, yylookaheadNeeds[0] is not maintained since it would merely
   *  duplicate yychar != YYEMPTY.  */
  yybool* yylookaheadNeeds;
  size_t yysize, yycapacity;
};

struct yySemanticOption {
  /** Type tag: always false.  */
  yybool yyisState;
  /** Rule number for this reduction */
  yyRuleNum yyrule;
  /** The last RHS state in the list of states to be reduced.  */
  yyGLRState* yystate;
  /** The lookahead for this reduction.  */
  int yyrawchar;
  YYSTYPE yyval;
  /** Next sibling in chain of options.  To facilitate merging,
   *  options are chained in decreasing order by address.  */
  yySemanticOption* yynext;
};

/** Type of the items in the GLR stack.  The yyisState field
 *  indicates which item of the union is valid.  */
union yyGLRStackItem {
  yyGLRState yystate;
  yySemanticOption yyoption;
};

struct yyGLRStack {
  int yyerrState;


  int yyerrcnt;
  int yyrawchar;
  YYSTYPE yyval;

  YYJMP_BUF yyexception_buffer;
  yyGLRStackItem* yyitems;
  yyGLRStackItem* yynextFree;
  size_t yyspaceLeft;
  yyGLRState* yysplitPoint;
  yyGLRState* yylastDeleted;
  yyGLRStateSet yytops;
};

#if YYSTACKEXPANDABLE
static void yyexpandGLRStack (yyGLRStack* yystackp);
#endif

static _Noreturn void
yyFail (yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index, const char* yymsg)
{
  if (yymsg != YY_NULLPTR)
    yyerror (P, tokens, index, yymsg);
  YYLONGJMP (yystackp->yyexception_buffer, 1);
}

static _Noreturn void
yyMemoryExhausted (yyGLRStack* yystackp)
{
  YYLONGJMP (yystackp->yyexception_buffer, 2);
}

#if YYDEBUG || YYERROR_VERBOSE
/** A printable representation of TOKEN.  */
static inline const char*
yytokenName (yySymbol yytoken)
{
  if (yytoken == YYEMPTY)
    return "";

  return yytname[yytoken];
}
#endif

/** Fill in YYVSP[YYLOW1 .. YYLOW0-1] from the chain of states starting
 *  at YYVSP[YYLOW0].yystate.yypred.  Leaves YYVSP[YYLOW1].yystate.yypred
 *  containing the pointer to the next state in the chain.  */
static void yyfillin (yyGLRStackItem *, int, int) YY_ATTRIBUTE_UNUSED;
static void
yyfillin (yyGLRStackItem *yyvsp, int yylow0, int yylow1)
{
  int i;
  yyGLRState *s = yyvsp[yylow0].yystate.yypred;
  for (i = yylow0-1; i >= yylow1; i -= 1)
    {
#if YYDEBUG
      yyvsp[i].yystate.yylrState = s->yylrState;
#endif
      yyvsp[i].yystate.yyresolved = s->yyresolved;
      if (s->yyresolved)
        yyvsp[i].yystate.yysemantics.yysval = s->yysemantics.yysval;
      else
        /* The effect of using yysval or yyloc (in an immediate rule) is
         * undefined.  */
        yyvsp[i].yystate.yysemantics.yyfirstVal = YY_NULLPTR;
      s = yyvsp[i].yystate.yypred = s->yypred;
    }
}

/* Do nothing if YYNORMAL or if *YYLOW <= YYLOW1.  Otherwise, fill in
 * YYVSP[YYLOW1 .. *YYLOW-1] as in yyfillin and set *YYLOW = YYLOW1.
 * For convenience, always return YYLOW1.  */
static inline int yyfill (yyGLRStackItem *, int *, int, yybool)
     YY_ATTRIBUTE_UNUSED;
static inline int
yyfill (yyGLRStackItem *yyvsp, int *yylow, int yylow1, yybool yynormal)
{
  if (!yynormal && yylow1 < *yylow)
    {
      yyfillin (yyvsp, *yylow, yylow1);
      *yylow = yylow1;
    }
  return yylow1;
}

/** Perform user action for rule number YYN, with RHS length YYRHSLEN,
 *  and top stack item YYVSP.  YYLVALP points to place to put semantic
 *  value ($$), and yylocp points to place for location information
 *  (@$).  Returns yyok for normal return, yyaccept for YYACCEPT,
 *  yyerr for YYERROR, yyabort for YYABORT.  */
static YYRESULTTAG
yyuserAction (yyRuleNum yyn, size_t yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yystackp->yysplitPoint == YY_NULLPTR);
  int yylow;
  YYUSE (yyvalp);
  YYUSE (P);
  YYUSE (tokens);
  YYUSE (index);
  YYUSE (yyrhslen);
# undef yyerrok
# define yyerrok (yystackp->yyerrState = 0)
# undef YYACCEPT
# define YYACCEPT return yyaccept
# undef YYABORT
# define YYABORT return yyabort
# undef YYERROR
# define YYERROR return yyerrok, yyerr
# undef YYRECOVERING
# define YYRECOVERING() (yystackp->yyerrState != 0)
# undef yyclearin
# define yyclearin (yychar = YYEMPTY)
# undef YYFILL
# define YYFILL(N) yyfill (yyvsp, &yylow, N, yynormal)
# undef YYBACKUP
# define YYBACKUP(Token, Value)                                              \
  return yyerror (P, tokens, index, YY_("syntax error: cannot back up")),     \
         yyerrok, yyerr

  yylow = 1;
  if (yyrhslen == 0)
    *yyvalp = yyval_default;
  else
    *yyvalp = yyvsp[YYFILL (1-yyrhslen)].yystate.yysemantics.yysval;
  switch (yyn)
    {
        case 159:
#line 404 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		psi_cpp_exp_exec((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 2014 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 160:
#line 410 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if (P->file.ln) {
		P->error(PSI_DATA(P), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), PSI_WARNING,
				"Extra 'lib %s' statement has no effect", (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	} else {
		P->file.ln = strndup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text + 1, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->size - 2);
	}
}
#line 2027 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 161:
#line 418 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_const(P, (*(struct psi_const **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2035 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 162:
#line 421 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_decl(P, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2043 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 163:
#line 424 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_typedef(P, (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2051 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 164:
#line 427 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_struct(P, (*(struct psi_decl_struct **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2059 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 165:
#line 430 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_union(P, (*(struct psi_decl_union **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2067 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 166:
#line 433 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2075 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 167:
#line 436 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_impl(P, (*(struct psi_impl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2083 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 168:
#line 442 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2091 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 169:
#line 448 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = (*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2099 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 170:
#line 454 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		struct psi_token *msg = NULL;
		
		if (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0, &msg)) {
			size_t index = 1;
			struct psi_token *next;

			msg = psi_token_copy(msg);			
			while (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), index++, &next)) {
				struct psi_token *old = msg;
				msg = psi_token_cat(" ", 2, msg, next);
				free(old);
			}
		}
		psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		
		(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, msg);
	} else {
		(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, NULL);
	}
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2127 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 171:
#line 477 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2136 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 172:
#line 481 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2145 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 173:
#line 485 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2155 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 174:
#line 490 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2165 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 175:
#line 495 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_cpp_macro_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2174 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 176:
#line 499 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2183 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 191:
#line 538 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 2193 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 192:
#line 543 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2203 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 193:
#line 548 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2213 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 194:
#line 556 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL);
}
#line 2221 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 196:
#line 563 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2231 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 197:
#line 568 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2241 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 198:
#line 576 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2249 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 200:
#line 583 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2258 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 201:
#line 587 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2267 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 202:
#line 594 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 2276 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 203:
#line 598 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2285 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 204:
#line 602 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2294 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 205:
#line 606 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 2309 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 206:
#line 616 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2324 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 207:
#line 626 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2334 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 208:
#line 631 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2344 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 209:
#line 636 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2355 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 210:
#line 642 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)))));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 2366 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 211:
#line 651 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2374 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 213:
#line 658 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((void (*)(void *)) psi_num_exp_free), 
		&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2383 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 214:
#line 662 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2391 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 215:
#line 668 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init((*(struct psi_const_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 2400 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 216:
#line 675 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_const_type **)(&(*yyvalp))) = psi_const_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
}
#line 2408 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 221:
#line 688 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = NULL;
}
#line 2416 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 222:
#line 691 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2425 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 228:
#line 706 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2433 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 230:
#line 713 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 2446 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 231:
#line 721 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_ENUM, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->name),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.enm = (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2461 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 232:
#line 731 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
}
#line 2474 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 233:
#line 739 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
}
#line 2487 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 234:
#line 750 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 2495 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 236:
#line 757 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 2504 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 238:
#line 765 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2514 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 239:
#line 770 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2524 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 240:
#line 775 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2534 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 243:
#line 785 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2542 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 244:
#line 788 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2550 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 245:
#line 794 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2558 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 246:
#line 797 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2566 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 247:
#line 800 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2574 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 258:
#line 822 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2582 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 259:
#line 825 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2590 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 260:
#line 828 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2598 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 261:
#line 834 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2606 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 262:
#line 837 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2614 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 263:
#line 840 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2627 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 264:
#line 848 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
}
#line 2641 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 265:
#line 860 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 2649 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 266:
#line 863 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2657 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 267:
#line 866 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2669 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 268:
#line 873 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2677 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 269:
#line 876 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2689 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 270:
#line 886 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 2697 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 272:
#line 892 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 2705 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 275:
#line 900 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 2713 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 276:
#line 903 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2721 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 277:
#line 906 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2734 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 278:
#line 917 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2742 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 279:
#line 923 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(psi_decl_abi_init("default"), (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 2754 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 280:
#line 930 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(psi_decl_abi_init("default"), (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 2767 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 281:
#line 938 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 2779 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 282:
#line 945 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 2792 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 285:
#line 961 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2803 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 286:
#line 967 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2818 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 287:
#line 977 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2833 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 288:
#line 987 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2848 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 290:
#line 1001 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2862 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 291:
#line 1013 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2870 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 292:
#line 1016 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2878 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 293:
#line 1019 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2886 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 294:
#line 1022 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2894 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 295:
#line 1028 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2902 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 296:
#line 1031 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2917 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 297:
#line 1041 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2932 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 298:
#line 1054 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)) + !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2942 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 299:
#line 1059 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2952 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 300:
#line 1067 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_union **)(&(*yyvalp))) = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_union **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_union **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_union **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 2964 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 301:
#line 1077 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_struct **)(&(*yyvalp))) = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_struct **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 2976 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 302:
#line 1087 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2984 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 304:
#line 1094 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2992 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 305:
#line 1100 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3000 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 306:
#line 1103 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3008 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 307:
#line 1109 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	psi_parser_proc_add_from_typedef(P, (*(struct psi_decl_arg **)(&(*yyvalp))));
}
#line 3018 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 308:
#line 1117 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_enum **)(&(*yyvalp))) = psi_decl_enum_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 3027 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 309:
#line 1124 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3035 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 310:
#line 1127 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3043 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 311:
#line 1133 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, NULL);
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3053 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 312:
#line 1138 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3063 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 313:
#line 1146 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 3072 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 314:
#line 1150 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_cast((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->token);
}
#line 3081 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 315:
#line 1154 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary(PSI_T_LPAREN, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3090 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 316:
#line 1158 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3099 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 317:
#line 1162 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3108 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 318:
#line 1169 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3117 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 319:
#line 1173 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3126 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 320:
#line 1177 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3135 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 321:
#line 1181 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_NAME, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 3144 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 322:
#line 1188 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3159 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 323:
#line 1201 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3174 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 324:
#line 1214 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3189 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 325:
#line 1227 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3197 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 326:
#line 1230 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&(*yyvalp)))->type = PSI_T_NAME;
}
#line 3206 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 327:
#line 1237 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = NULL;
}
#line 3214 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 328:
#line 1240 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text));
}
#line 3222 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 329:
#line 1246 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = 0;
	(*(struct psi_layout*)(&(*yyvalp))).len = 0;
}
#line 3231 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 330:
#line 1250 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text);
	(*(struct psi_layout*)(&(*yyvalp))).len = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 3240 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 331:
#line 1257 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 3248 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 332:
#line 1260 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 3256 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 333:
#line 1266 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 3264 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 334:
#line 1269 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3272 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 335:
#line 1275 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 1;
}
#line 3280 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 336:
#line 1278 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)) + 1;
}
#line 3288 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 337:
#line 1290 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3296 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 338:
#line 1293 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 3305 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 339:
#line 1300 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, NULL, (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
}
#line 3315 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 340:
#line 1305 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval));
}
#line 3325 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 341:
#line 1310 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval));
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 3337 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 342:
#line 1320 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3345 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 343:
#line 1323 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3353 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 344:
#line 1329 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
}
#line 3361 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 345:
#line 1332 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3369 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 346:
#line 1338 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_var **)(&(*yyvalp))) = psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3378 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 347:
#line 1345 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3387 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 357:
#line 1364 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3395 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 358:
#line 1367 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3403 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 359:
#line 1373 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_return_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3411 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 360:
#line 1376 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_let_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3419 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 361:
#line 1379 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_set_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3427 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 362:
#line 1382 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_assert_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3435 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 363:
#line 1385 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_free_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3443 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 364:
#line 1391 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init((*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3452 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 365:
#line 1395 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init(psi_let_exp_init_ex((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), PSI_LET_TMP, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->exp->is_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 3462 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 367:
#line 1404 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = true;
}
#line 3471 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 368:
#line 1408 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = false;
}
#line 3480 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 369:
#line 1415 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 3488 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 370:
#line 1418 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3496 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 371:
#line 1421 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLBACK, (*(struct psi_let_callback **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3504 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 372:
#line 1424 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, (*(struct psi_let_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3512 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 373:
#line 1427 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3520 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 374:
#line 1433 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 3529 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 375:
#line 1437 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = 1;
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 3539 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 376:
#line 1445 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_calloc **)(&(*yyvalp))) = psi_let_calloc_init((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 3548 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 377:
#line 1452 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)));
}
#line 3558 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 378:
#line 1460 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_func **)(&(*yyvalp))) = psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 3568 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 389:
#line 1481 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3576 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 390:
#line 1484 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3584 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 391:
#line 1490 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3592 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 392:
#line 1493 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3600 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 395:
#line 1504 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3608 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 396:
#line 1507 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3616 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 397:
#line 1513 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3624 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 398:
#line 1516 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3632 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 399:
#line 1522 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_return_stmt **)(&(*yyvalp))) = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_return_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3641 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 400:
#line 1529 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_stmt **)(&(*yyvalp))) = psi_set_stmt_init((*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_set_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3650 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 401:
#line 1536 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3658 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 402:
#line 1539 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3666 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 403:
#line 1542 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = (*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_set_exp **)(&(*yyvalp)))->var = (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 3675 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 404:
#line 1549 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 3685 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 405:
#line 1554 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->recursive = 1;
}
#line 3695 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 414:
#line 1573 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3703 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 415:
#line 1576 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3711 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 416:
#line 1582 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3719 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 417:
#line 1585 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3727 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 418:
#line 1591 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_assert_stmt **)(&(*yyvalp))) = psi_assert_stmt_init((enum psi_assert_kind) (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_assert_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3736 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 421:
#line 1603 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_free_stmt **)(&(*yyvalp))) = psi_free_stmt_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3745 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 422:
#line 1610 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3753 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 423:
#line 1613 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3761 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 424:
#line 1619 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_free_exp **)(&(*yyvalp))) = psi_free_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 3771 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 425:
#line 1627 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3779 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 426:
#line 1630 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3787 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 427:
#line 1636 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = false;
}
#line 3795 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 428:
#line 1639 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = true;
}
#line 3803 "src/parser_proc.c" /* glr.c:816  */
    break;


#line 3807 "src/parser_proc.c" /* glr.c:816  */
      default: break;
    }

  return yyok;
# undef yyerrok
# undef YYABORT
# undef YYACCEPT
# undef YYERROR
# undef YYBACKUP
# undef yyclearin
# undef YYRECOVERING
}


static void
yyuserMerge (int yyn, YYSTYPE* yy0, YYSTYPE* yy1)
{
  YYUSE (yy0);
  YYUSE (yy1);

  switch (yyn)
    {

      default: break;
    }
}

                              /* Bison grammar-table manipulation.  */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  YYUSE (yyvaluep);
  YYUSE (P);
  YYUSE (tokens);
  YYUSE (index);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 124: /* binary_op_token  */
#line 269 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3858 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 125: /* unary_op_token  */
#line 269 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3864 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 126: /* name_token  */
#line 269 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3870 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 127: /* any_noeol_token  */
#line 269 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3876 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 131: /* lib  */
#line 263 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 3882 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 132: /* cpp  */
#line 278 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 3888 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 133: /* cpp_exp  */
#line 278 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 3894 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 134: /* cpp_message_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3900 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 135: /* cpp_include_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3906 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 136: /* cpp_header_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3912 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 137: /* cpp_no_arg_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3918 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 138: /* cpp_name_arg_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3924 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 139: /* cpp_exp_arg_token  */
#line 266 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3930 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 140: /* cpp_macro_decl  */
#line 280 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_macro_decl_free(&(*(struct psi_cpp_macro_decl **)(&(*yyvaluep))));}
#line 3936 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 141: /* cpp_macro_sig  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3942 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 142: /* cpp_macro_sig_args  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3948 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 143: /* cpp_macro_decl_tokens  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3954 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 144: /* cpp_macro_decl_token_list  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3960 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 145: /* cpp_macro_exp  */
#line 284 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 3966 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 146: /* cpp_macro_call_args  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3972 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 147: /* cpp_macro_call_arg_list  */
#line 282 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 3978 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 148: /* constant  */
#line 290 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_const_free(&(*(struct psi_const **)(&(*yyvaluep))));}
#line 3984 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 149: /* constant_type  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_const_type_free(&(*(struct psi_const_type **)(&(*yyvaluep))));}
#line 3990 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 150: /* constant_type_token  */
#line 287 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 3996 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 151: /* impl_def_val  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_def_val_free(&(*(struct psi_impl_def_val **)(&(*yyvaluep))));}
#line 4002 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 152: /* impl_def_val_token  */
#line 287 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4008 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 153: /* decl_typedef  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4014 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 154: /* typedef  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4020 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 155: /* const_decl_type  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4026 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 156: /* decl_type  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4032 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 157: /* decl_type_complex  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4038 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 158: /* decl_type_simple  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4044 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 159: /* decl_real_type  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4050 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 160: /* decl_stdint_type  */
#line 300 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4056 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 161: /* int_signed  */
#line 275 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4062 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 162: /* int_width  */
#line 272 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4068 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 163: /* decl_int_type  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4074 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 164: /* int_signed_types  */
#line 272 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4080 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 165: /* signed_short_types  */
#line 275 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4086 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 166: /* signed_long_types  */
#line 275 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4092 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 167: /* int_width_types  */
#line 272 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4098 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 168: /* decl_stmt  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4104 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 169: /* decl  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4110 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 170: /* decl_fn  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4116 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 171: /* decl_functor  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4122 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 172: /* decl_func  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4128 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 173: /* decl_args  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4134 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 174: /* decl_arg  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4140 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 175: /* decl_var  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_var_free(&(*(struct psi_decl_var **)(&(*yyvaluep))));}
#line 4146 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 176: /* decl_union  */
#line 313 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_union_free(&(*(struct psi_decl_union **)(&(*yyvaluep))));}
#line 4152 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 177: /* decl_struct  */
#line 311 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_struct_free(&(*(struct psi_decl_struct **)(&(*yyvaluep))));}
#line 4158 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 178: /* decl_struct_args  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4164 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 179: /* struct_args_block  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4170 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 180: /* struct_args  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4176 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 181: /* struct_arg  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4182 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 182: /* decl_enum  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_free(&(*(struct psi_decl_enum **)(&(*yyvaluep))));}
#line 4188 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 183: /* decl_enum_items  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4194 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 184: /* decl_enum_item  */
#line 317 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_item_free(&(*(struct psi_decl_enum_item **)(&(*yyvaluep))));}
#line 4200 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 185: /* num_exp  */
#line 370 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 4206 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 186: /* number  */
#line 372 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 4212 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 187: /* enum_name  */
#line 263 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4218 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 188: /* union_name  */
#line 263 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4224 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 189: /* struct_name  */
#line 263 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4230 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 190: /* optional_name  */
#line 263 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4236 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 191: /* decl_layout  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_layout_free(&(*(struct psi_layout **)(&(*yyvaluep))));}
#line 4242 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 192: /* align_and_size  */
#line 322 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4248 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 193: /* array_size  */
#line 375 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4254 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 194: /* indirection  */
#line 375 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4260 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 195: /* pointers  */
#line 375 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4266 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 196: /* impl  */
#line 327 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_free(&(*(struct psi_impl **)(&(*yyvaluep))));}
#line 4272 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 197: /* impl_func  */
#line 329 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_func_free(&(*(struct psi_impl_func **)(&(*yyvaluep))));}
#line 4278 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 198: /* impl_args  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4284 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 199: /* impl_arg  */
#line 331 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_arg_free(&(*(struct psi_impl_arg **)(&(*yyvaluep))));}
#line 4290 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 200: /* impl_var  */
#line 335 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_var_free(&(*(struct psi_impl_var **)(&(*yyvaluep))));}
#line 4296 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 201: /* impl_type  */
#line 333 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 4302 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 202: /* impl_type_token  */
#line 365 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4308 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 203: /* impl_stmts  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4314 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 204: /* impl_stmt  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_stmt_free(&(*(struct psi_token ***)(&(*yyvaluep))));}
#line 4320 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 205: /* let_stmt  */
#line 338 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_stmt_free(&(*(struct psi_let_stmt **)(&(*yyvaluep))));}
#line 4326 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 206: /* let_exp  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 4332 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 207: /* let_exp_byref  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 4338 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 208: /* let_exp_assign  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 4344 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 209: /* let_calloc  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_calloc_free(&(*(struct psi_let_calloc **)(&(*yyvaluep))));}
#line 4350 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 210: /* let_callback  */
#line 344 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_callback_free(&(*(struct psi_let_callback **)(&(*yyvaluep))));}
#line 4356 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 211: /* let_func  */
#line 346 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_func_free(&(*(struct psi_let_func **)(&(*yyvaluep))));}
#line 4362 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 212: /* let_func_token  */
#line 365 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4368 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 213: /* let_func_exps  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4374 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 214: /* let_exps  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4380 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 215: /* callback_rval  */
#line 365 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4386 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 216: /* callback_arg_list  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4392 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 217: /* callback_args  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4398 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 218: /* return_stmt  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_return_stmt_free(&(*(struct psi_return_stmt **)(&(*yyvaluep))));}
#line 4404 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 219: /* set_stmt  */
#line 348 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_stmt_free(&(*(struct psi_set_stmt **)(&(*yyvaluep))));}
#line 4410 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 220: /* set_exp  */
#line 350 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_exp_free(&(*(struct psi_set_exp **)(&(*yyvaluep))));}
#line 4416 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 221: /* set_func  */
#line 352 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_func_free(&(*(struct psi_set_func **)(&(*yyvaluep))));}
#line 4422 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 222: /* set_func_token  */
#line 365 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4428 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 223: /* set_func_exps  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4434 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 224: /* set_exps  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4440 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 225: /* assert_stmt  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_assert_stmt_free(&(*(struct psi_assert_stmt **)(&(*yyvaluep))));}
#line 4446 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 226: /* assert_stmt_token  */
#line 365 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4452 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 227: /* free_stmt  */
#line 358 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_stmt_free(&(*(struct psi_free_stmt **)(&(*yyvaluep))));}
#line 4458 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 228: /* free_exps  */
#line 367 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4464 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 229: /* free_exp  */
#line 360 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_exp_free(&(*(struct psi_free_exp **)(&(*yyvaluep))));}
#line 4470 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 230: /* decl_vars  */
#line 319 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4476 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 231: /* reference  */
#line 377 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4482 "src/parser_proc.c" /* glr.c:846  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}

/** Number of symbols composing the right hand side of rule #RULE.  */
static inline int
yyrhsLength (yyRuleNum yyrule)
{
  return yyr2[yyrule];
}

static void
yydestroyGLRState (char const *yymsg, yyGLRState *yys, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  if (yys->yyresolved)
    yydestruct (yymsg, yystos[yys->yylrState],
                &yys->yysemantics.yysval, P, tokens, index);
  else
    {
#if YYDEBUG
      if (yydebug)
        {
          if (yys->yysemantics.yyfirstVal)
            YYFPRINTF (stderr, "%s unresolved", yymsg);
          else
            YYFPRINTF (stderr, "%s incomplete", yymsg);
          YY_SYMBOL_PRINT ("", yystos[yys->yylrState], YY_NULLPTR, &yys->yyloc);
        }
#endif

      if (yys->yysemantics.yyfirstVal)
        {
          yySemanticOption *yyoption = yys->yysemantics.yyfirstVal;
          yyGLRState *yyrh;
          int yyn;
          for (yyrh = yyoption->yystate, yyn = yyrhsLength (yyoption->yyrule);
               yyn > 0;
               yyrh = yyrh->yypred, yyn -= 1)
            yydestroyGLRState (yymsg, yyrh, P, tokens, index);
        }
    }
}

/** Left-hand-side symbol for rule #YYRULE.  */
static inline yySymbol
yylhsNonterm (yyRuleNum yyrule)
{
  return yyr1[yyrule];
}

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-490)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return yypact_value_is_default (yypact[yystate]);
}

/** The default reduction for YYSTATE, assuming it has one.  */
static inline yyRuleNum
yydefaultAction (yyStateNum yystate)
{
  return yydefact[yystate];
}

#define yytable_value_is_error(Yytable_value) \
  0

/** Set *YYACTION to the action to take in YYSTATE on seeing YYTOKEN.
 *  Result R means
 *    R < 0:  Reduce on rule -R.
 *    R = 0:  Error.
 *    R > 0:  Shift to state R.
 *  Set *YYCONFLICTS to a pointer into yyconfl to a 0-terminated list
 *  of conflicting reductions.
 */
static inline void
yygetLRActions (yyStateNum yystate, int yytoken,
                int* yyaction, const short int** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yypact_value_is_default (yypact[yystate])
      || yyindex < 0 || YYLAST < yyindex || yycheck[yyindex] != yytoken)
    {
      *yyaction = -yydefact[yystate];
      *yyconflicts = yyconfl;
    }
  else if (! yytable_value_is_error (yytable[yyindex]))
    {
      *yyaction = yytable[yyindex];
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
  else
    {
      *yyaction = 0;
      *yyconflicts = yyconfl + yyconflp[yyindex];
    }
}

/** Compute post-reduction state.
 * \param yystate   the current state
 * \param yysym     the nonterminal to push on the stack
 */
static inline yyStateNum
yyLRgotoState (yyStateNum yystate, yySymbol yysym)
{
  int yyr = yypgoto[yysym - YYNTOKENS] + yystate;
  if (0 <= yyr && yyr <= YYLAST && yycheck[yyr] == yystate)
    return yytable[yyr];
  else
    return yydefgoto[yysym - YYNTOKENS];
}

static inline yybool
yyisShiftAction (int yyaction)
{
  return 0 < yyaction;
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return yyaction == 0;
}

                                /* GLRStates */

/** Return a fresh GLRStackItem in YYSTACKP.  The item is an LR state
 *  if YYISSTATE, and otherwise a semantic option.  Callers should call
 *  YY_RESERVE_GLRSTACK afterwards to make sure there is sufficient
 *  headroom.  */

static inline yyGLRStackItem*
yynewGLRStackItem (yyGLRStack* yystackp, yybool yyisState)
{
  yyGLRStackItem* yynewItem = yystackp->yynextFree;
  yystackp->yyspaceLeft -= 1;
  yystackp->yynextFree += 1;
  yynewItem->yystate.yyisState = yyisState;
  return yynewItem;
}

/** Add a new semantic action that will execute the action for rule
 *  YYRULE on the semantic values in YYRHS to the list of
 *  alternative actions for YYSTATE.  Assumes that YYRHS comes from
 *  stack #YYK of *YYSTACKP. */
static void
yyaddDeferredAction (yyGLRStack* yystackp, size_t yyk, yyGLRState* yystate,
                     yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yySemanticOption* yynewOption =
    &yynewGLRStackItem (yystackp, yyfalse)->yyoption;
  YYASSERT (!yynewOption->yyisState);
  yynewOption->yystate = yyrhs;
  yynewOption->yyrule = yyrule;
  if (yystackp->yytops.yylookaheadNeeds[yyk])
    {
      yynewOption->yyrawchar = yychar;
      yynewOption->yyval = yylval;
    }
  else
    yynewOption->yyrawchar = YYEMPTY;
  yynewOption->yynext = yystate->yysemantics.yyfirstVal;
  yystate->yysemantics.yyfirstVal = yynewOption;

  YY_RESERVE_GLRSTACK (yystackp);
}

                                /* GLRStacks */

/** Initialize YYSET to a singleton set containing an empty stack.  */
static yybool
yyinitStateSet (yyGLRStateSet* yyset)
{
  yyset->yysize = 1;
  yyset->yycapacity = 16;
  yyset->yystates = (yyGLRState**) YYMALLOC (16 * sizeof yyset->yystates[0]);
  if (! yyset->yystates)
    return yyfalse;
  yyset->yystates[0] = YY_NULLPTR;
  yyset->yylookaheadNeeds =
    (yybool*) YYMALLOC (16 * sizeof yyset->yylookaheadNeeds[0]);
  if (! yyset->yylookaheadNeeds)
    {
      YYFREE (yyset->yystates);
      return yyfalse;
    }
  return yytrue;
}

static void yyfreeStateSet (yyGLRStateSet* yyset)
{
  YYFREE (yyset->yystates);
  YYFREE (yyset->yylookaheadNeeds);
}

/** Initialize *YYSTACKP to a single empty stack, with total maximum
 *  capacity for all stacks of YYSIZE.  */
static yybool
yyinitGLRStack (yyGLRStack* yystackp, size_t yysize)
{
  yystackp->yyerrState = 0;
  yynerrs = 0;
  yystackp->yyspaceLeft = yysize;
  yystackp->yyitems =
    (yyGLRStackItem*) YYMALLOC (yysize * sizeof yystackp->yynextFree[0]);
  if (!yystackp->yyitems)
    return yyfalse;
  yystackp->yynextFree = yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;
  return yyinitStateSet (&yystackp->yytops);
}


#if YYSTACKEXPANDABLE
# define YYRELOC(YYFROMITEMS,YYTOITEMS,YYX,YYTYPE) \
  &((YYTOITEMS) - ((YYFROMITEMS) - (yyGLRStackItem*) (YYX)))->YYTYPE

/** If *YYSTACKP is expandable, extend it.  WARNING: Pointers into the
    stack from outside should be considered invalid after this call.
    We always expand when there are 1 or fewer items left AFTER an
    allocation, so that we can avoid having external pointers exist
    across an allocation.  */
static void
yyexpandGLRStack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yynewItems;
  yyGLRStackItem* yyp0, *yyp1;
  size_t yynewSize;
  size_t yyn;
  size_t yysize = yystackp->yynextFree - yystackp->yyitems;
  if (YYMAXDEPTH - YYHEADROOM < yysize)
    yyMemoryExhausted (yystackp);
  yynewSize = 2*yysize;
  if (YYMAXDEPTH < yynewSize)
    yynewSize = YYMAXDEPTH;
  yynewItems = (yyGLRStackItem*) YYMALLOC (yynewSize * sizeof yynewItems[0]);
  if (! yynewItems)
    yyMemoryExhausted (yystackp);
  for (yyp0 = yystackp->yyitems, yyp1 = yynewItems, yyn = yysize;
       0 < yyn;
       yyn -= 1, yyp0 += 1, yyp1 += 1)
    {
      *yyp1 = *yyp0;
      if (*(yybool *) yyp0)
        {
          yyGLRState* yys0 = &yyp0->yystate;
          yyGLRState* yys1 = &yyp1->yystate;
          if (yys0->yypred != YY_NULLPTR)
            yys1->yypred =
              YYRELOC (yyp0, yyp1, yys0->yypred, yystate);
          if (! yys0->yyresolved && yys0->yysemantics.yyfirstVal != YY_NULLPTR)
            yys1->yysemantics.yyfirstVal =
              YYRELOC (yyp0, yyp1, yys0->yysemantics.yyfirstVal, yyoption);
        }
      else
        {
          yySemanticOption* yyv0 = &yyp0->yyoption;
          yySemanticOption* yyv1 = &yyp1->yyoption;
          if (yyv0->yystate != YY_NULLPTR)
            yyv1->yystate = YYRELOC (yyp0, yyp1, yyv0->yystate, yystate);
          if (yyv0->yynext != YY_NULLPTR)
            yyv1->yynext = YYRELOC (yyp0, yyp1, yyv0->yynext, yyoption);
        }
    }
  if (yystackp->yysplitPoint != YY_NULLPTR)
    yystackp->yysplitPoint = YYRELOC (yystackp->yyitems, yynewItems,
                                      yystackp->yysplitPoint, yystate);

  for (yyn = 0; yyn < yystackp->yytops.yysize; yyn += 1)
    if (yystackp->yytops.yystates[yyn] != YY_NULLPTR)
      yystackp->yytops.yystates[yyn] =
        YYRELOC (yystackp->yyitems, yynewItems,
                 yystackp->yytops.yystates[yyn], yystate);
  YYFREE (yystackp->yyitems);
  yystackp->yyitems = yynewItems;
  yystackp->yynextFree = yynewItems + yysize;
  yystackp->yyspaceLeft = yynewSize - yysize;
}
#endif

static void
yyfreeGLRStack (yyGLRStack* yystackp)
{
  YYFREE (yystackp->yyitems);
  yyfreeStateSet (&yystackp->yytops);
}

/** Assuming that YYS is a GLRState somewhere on *YYSTACKP, update the
 *  splitpoint of *YYSTACKP, if needed, so that it is at least as deep as
 *  YYS.  */
static inline void
yyupdateSplit (yyGLRStack* yystackp, yyGLRState* yys)
{
  if (yystackp->yysplitPoint != YY_NULLPTR && yystackp->yysplitPoint > yys)
    yystackp->yysplitPoint = yys;
}

/** Invalidate stack #YYK in *YYSTACKP.  */
static inline void
yymarkStackDeleted (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    yystackp->yylastDeleted = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yystates[yyk] = YY_NULLPTR;
}

/** Undelete the last stack in *YYSTACKP that was marked as deleted.  Can
    only be done once after a deletion, and only when all other stacks have
    been deleted.  */
static void
yyundeleteLastStack (yyGLRStack* yystackp)
{
  if (yystackp->yylastDeleted == YY_NULLPTR || yystackp->yytops.yysize != 0)
    return;
  yystackp->yytops.yystates[0] = yystackp->yylastDeleted;
  yystackp->yytops.yysize = 1;
  YYDPRINTF ((stderr, "Restoring last deleted stack as stack #0.\n"));
  yystackp->yylastDeleted = YY_NULLPTR;
}

static inline void
yyremoveDeletes (yyGLRStack* yystackp)
{
  size_t yyi, yyj;
  yyi = yyj = 0;
  while (yyj < yystackp->yytops.yysize)
    {
      if (yystackp->yytops.yystates[yyi] == YY_NULLPTR)
        {
          if (yyi == yyj)
            {
              YYDPRINTF ((stderr, "Removing dead stacks.\n"));
            }
          yystackp->yytops.yysize -= 1;
        }
      else
        {
          yystackp->yytops.yystates[yyj] = yystackp->yytops.yystates[yyi];
          /* In the current implementation, it's unnecessary to copy
             yystackp->yytops.yylookaheadNeeds[yyi] since, after
             yyremoveDeletes returns, the parser immediately either enters
             deterministic operation or shifts a token.  However, it doesn't
             hurt, and the code might evolve to need it.  */
          yystackp->yytops.yylookaheadNeeds[yyj] =
            yystackp->yytops.yylookaheadNeeds[yyi];
          if (yyj != yyi)
            {
              YYDPRINTF ((stderr, "Rename stack %lu -> %lu.\n",
                          (unsigned long int) yyi, (unsigned long int) yyj));
            }
          yyj += 1;
        }
      yyi += 1;
    }
}

/** Shift to a new state on stack #YYK of *YYSTACKP, corresponding to LR
 * state YYLRSTATE, at input position YYPOSN, with (resolved) semantic
 * value *YYVALP and source location *YYLOCP.  */
static inline void
yyglrShift (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
            size_t yyposn,
            YYSTYPE* yyvalp)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yytrue;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yysval = *yyvalp;
  yystackp->yytops.yystates[yyk] = yynewState;

  YY_RESERVE_GLRSTACK (yystackp);
}

/** Shift stack #YYK of *YYSTACKP, to a new state corresponding to LR
 *  state YYLRSTATE, at input position YYPOSN, with the (unresolved)
 *  semantic value of YYRHS under the action for YYRULE.  */
static inline void
yyglrShiftDefer (yyGLRStack* yystackp, size_t yyk, yyStateNum yylrState,
                 size_t yyposn, yyGLRState* yyrhs, yyRuleNum yyrule)
{
  yyGLRState* yynewState = &yynewGLRStackItem (yystackp, yytrue)->yystate;
  YYASSERT (yynewState->yyisState);

  yynewState->yylrState = yylrState;
  yynewState->yyposn = yyposn;
  yynewState->yyresolved = yyfalse;
  yynewState->yypred = yystackp->yytops.yystates[yyk];
  yynewState->yysemantics.yyfirstVal = YY_NULLPTR;
  yystackp->yytops.yystates[yyk] = yynewState;

  /* Invokes YY_RESERVE_GLRSTACK.  */
  yyaddDeferredAction (yystackp, yyk, yynewState, yyrhs, yyrule);
}

#if !YYDEBUG
# define YY_REDUCE_PRINT(Args)
#else
# define YY_REDUCE_PRINT(Args)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print Args;               \
} while (0)

/*----------------------------------------------------------------------.
| Report that stack #YYK of *YYSTACKP is going to be reduced by YYRULE. |
`----------------------------------------------------------------------*/

static inline void
yy_reduce_print (int yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long int) yyk, yyrule - 1,
             (unsigned long int) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval
                                              , P, tokens, index);
      if (!yyvsp[yyi - yynrhs + 1].yystate.yyresolved)
        YYFPRINTF (stderr, " (unresolved)");
      YYFPRINTF (stderr, "\n");
    }
}
#endif

/** Pop the symbols consumed by reduction #YYRULE from the top of stack
 *  #YYK of *YYSTACKP, and perform the appropriate semantic action on their
 *  semantic values.  Assumes that all ambiguities in semantic values
 *  have been previously resolved.  Set *YYVALP to the resulting value,
 *  and *YYLOCP to the computed location (if any).  Return value is as
 *  for userAction.  */
static inline YYRESULTTAG
yydoAction (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
            YYSTYPE* yyvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  int yynrhs = yyrhsLength (yyrule);

  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      /* Standard special case: single stack.  */
      yyGLRStackItem* yyrhs = (yyGLRStackItem*) yystackp->yytops.yystates[yyk];
      YYASSERT (yyk == 0);
      yystackp->yynextFree -= yynrhs;
      yystackp->yyspaceLeft += yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((1, yyrhs, yyk, yyrule, P, tokens, index));
      return yyuserAction (yyrule, yynrhs, yyrhs, yystackp,
                           yyvalp, P, tokens, index);
    }
  else
    {
      int yyi;
      yyGLRState* yys;
      yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
      yys = yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred
        = yystackp->yytops.yystates[yyk];
      for (yyi = 0; yyi < yynrhs; yyi += 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yystackp->yytops.yystates[yyk] = yys;
      YY_REDUCE_PRINT ((0, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, P, tokens, index));
      return yyuserAction (yyrule, yynrhs, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, P, tokens, index);
    }
}

/** Pop items off stack #YYK of *YYSTACKP according to grammar rule YYRULE,
 *  and push back on the resulting nonterminal symbol.  Perform the
 *  semantic action associated with YYRULE and store its value with the
 *  newly pushed state, if YYFORCEEVAL or if *YYSTACKP is currently
 *  unambiguous.  Otherwise, store the deferred semantic action with
 *  the new state.  If the new state would have an identical input
 *  position, LR state, and predecessor to an existing state on the stack,
 *  it is identified with that existing state, eliminating stack #YYK from
 *  *YYSTACKP.  In this case, the semantic value is
 *  added to the options for the existing state's semantic value.
 */
static inline YYRESULTTAG
yyglrReduce (yyGLRStack* yystackp, size_t yyk, yyRuleNum yyrule,
             yybool yyforceEval, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  size_t yyposn = yystackp->yytops.yystates[yyk]->yyposn;

  if (yyforceEval || yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYSTYPE yysval;

      YYRESULTTAG yyflag = yydoAction (yystackp, yyk, yyrule, &yysval, P, tokens, index);
      if (yyflag == yyerr && yystackp->yysplitPoint != YY_NULLPTR)
        {
          YYDPRINTF ((stderr, "Parse on stack %lu rejected by rule #%d.\n",
                     (unsigned long int) yyk, yyrule - 1));
        }
      if (yyflag != yyok)
        return yyflag;
      YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyrule], &yysval, &yyloc);
      yyglrShift (yystackp, yyk,
                  yyLRgotoState (yystackp->yytops.yystates[yyk]->yylrState,
                                 yylhsNonterm (yyrule)),
                  yyposn, &yysval);
    }
  else
    {
      size_t yyi;
      int yyn;
      yyGLRState* yys, *yys0 = yystackp->yytops.yystates[yyk];
      yyStateNum yynewLRState;

      for (yys = yystackp->yytops.yystates[yyk], yyn = yyrhsLength (yyrule);
           0 < yyn; yyn -= 1)
        {
          yys = yys->yypred;
          YYASSERT (yys);
        }
      yyupdateSplit (yystackp, yys);
      yynewLRState = yyLRgotoState (yys->yylrState, yylhsNonterm (yyrule));
      YYDPRINTF ((stderr,
                  "Reduced stack %lu by rule #%d; action deferred.  "
                  "Now in state %d.\n",
                  (unsigned long int) yyk, yyrule - 1, yynewLRState));
      for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
        if (yyi != yyk && yystackp->yytops.yystates[yyi] != YY_NULLPTR)
          {
            yyGLRState *yysplit = yystackp->yysplitPoint;
            yyGLRState *yyp = yystackp->yytops.yystates[yyi];
            while (yyp != yys && yyp != yysplit && yyp->yyposn >= yyposn)
              {
                if (yyp->yylrState == yynewLRState && yyp->yypred == yys)
                  {
                    yyaddDeferredAction (yystackp, yyk, yyp, yys0, yyrule);
                    yymarkStackDeleted (yystackp, yyk);
                    YYDPRINTF ((stderr, "Merging stack %lu into stack %lu.\n",
                                (unsigned long int) yyk,
                                (unsigned long int) yyi));
                    return yyok;
                  }
                yyp = yyp->yypred;
              }
          }
      yystackp->yytops.yystates[yyk] = yys;
      yyglrShiftDefer (yystackp, yyk, yynewLRState, yyposn, yys0, yyrule);
    }
  return yyok;
}

static size_t
yysplitStack (yyGLRStack* yystackp, size_t yyk)
{
  if (yystackp->yysplitPoint == YY_NULLPTR)
    {
      YYASSERT (yyk == 0);
      yystackp->yysplitPoint = yystackp->yytops.yystates[yyk];
    }
  if (yystackp->yytops.yysize >= yystackp->yytops.yycapacity)
    {
      yyGLRState** yynewStates;
      yybool* yynewLookaheadNeeds;

      yynewStates = YY_NULLPTR;

      if (yystackp->yytops.yycapacity
          > (YYSIZEMAX / (2 * sizeof yynewStates[0])))
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yycapacity *= 2;

      yynewStates =
        (yyGLRState**) YYREALLOC (yystackp->yytops.yystates,
                                  (yystackp->yytops.yycapacity
                                   * sizeof yynewStates[0]));
      if (yynewStates == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yystates = yynewStates;

      yynewLookaheadNeeds =
        (yybool*) YYREALLOC (yystackp->yytops.yylookaheadNeeds,
                             (yystackp->yytops.yycapacity
                              * sizeof yynewLookaheadNeeds[0]));
      if (yynewLookaheadNeeds == YY_NULLPTR)
        yyMemoryExhausted (yystackp);
      yystackp->yytops.yylookaheadNeeds = yynewLookaheadNeeds;
    }
  yystackp->yytops.yystates[yystackp->yytops.yysize]
    = yystackp->yytops.yystates[yyk];
  yystackp->yytops.yylookaheadNeeds[yystackp->yytops.yysize]
    = yystackp->yytops.yylookaheadNeeds[yyk];
  yystackp->yytops.yysize += 1;
  return yystackp->yytops.yysize-1;
}

/** True iff YYY0 and YYY1 represent identical options at the top level.
 *  That is, they represent the same rule applied to RHS symbols
 *  that produce the same terminal symbols.  */
static yybool
yyidenticalOptions (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  if (yyy0->yyrule == yyy1->yyrule)
    {
      yyGLRState *yys0, *yys1;
      int yyn;
      for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
           yyn = yyrhsLength (yyy0->yyrule);
           yyn > 0;
           yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
        if (yys0->yyposn != yys1->yyposn)
          return yyfalse;
      return yytrue;
    }
  else
    return yyfalse;
}

/** Assuming identicalOptions (YYY0,YYY1), destructively merge the
 *  alternative semantic values for the RHS-symbols of YYY1 and YYY0.  */
static void
yymergeOptionSets (yySemanticOption* yyy0, yySemanticOption* yyy1)
{
  yyGLRState *yys0, *yys1;
  int yyn;
  for (yys0 = yyy0->yystate, yys1 = yyy1->yystate,
       yyn = yyrhsLength (yyy0->yyrule);
       yyn > 0;
       yys0 = yys0->yypred, yys1 = yys1->yypred, yyn -= 1)
    {
      if (yys0 == yys1)
        break;
      else if (yys0->yyresolved)
        {
          yys1->yyresolved = yytrue;
          yys1->yysemantics.yysval = yys0->yysemantics.yysval;
        }
      else if (yys1->yyresolved)
        {
          yys0->yyresolved = yytrue;
          yys0->yysemantics.yysval = yys1->yysemantics.yysval;
        }
      else
        {
          yySemanticOption** yyz0p = &yys0->yysemantics.yyfirstVal;
          yySemanticOption* yyz1 = yys1->yysemantics.yyfirstVal;
          while (yytrue)
            {
              if (yyz1 == *yyz0p || yyz1 == YY_NULLPTR)
                break;
              else if (*yyz0p == YY_NULLPTR)
                {
                  *yyz0p = yyz1;
                  break;
                }
              else if (*yyz0p < yyz1)
                {
                  yySemanticOption* yyz = *yyz0p;
                  *yyz0p = yyz1;
                  yyz1 = yyz1->yynext;
                  (*yyz0p)->yynext = yyz;
                }
              yyz0p = &(*yyz0p)->yynext;
            }
          yys1->yysemantics.yyfirstVal = yys0->yysemantics.yyfirstVal;
        }
    }
}

/** Y0 and Y1 represent two possible actions to take in a given
 *  parsing state; return 0 if no combination is possible,
 *  1 if user-mergeable, 2 if Y0 is preferred, 3 if Y1 is preferred.  */
static int
yypreference (yySemanticOption* y0, yySemanticOption* y1)
{
  yyRuleNum r0 = y0->yyrule, r1 = y1->yyrule;
  int p0 = yydprec[r0], p1 = yydprec[r1];

  if (p0 == p1)
    {
      if (yymerger[r0] == 0 || yymerger[r0] != yymerger[r1])
        return 0;
      else
        return 1;
    }
  if (p0 == 0 || p1 == 0)
    return 0;
  if (p0 < p1)
    return 3;
  if (p1 < p0)
    return 2;
  return 0;
}

static YYRESULTTAG yyresolveValue (yyGLRState* yys,
                                   yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index);


/** Resolve the previous YYN states starting at and including state YYS
 *  on *YYSTACKP. If result != yyok, some states may have been left
 *  unresolved possibly with empty semantic option chains.  Regardless
 *  of whether result = yyok, each state has been left with consistent
 *  data so that yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveStates (yyGLRState* yys, int yyn,
                 yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  if (0 < yyn)
    {
      YYASSERT (yys->yypred);
      YYCHK (yyresolveStates (yys->yypred, yyn-1, yystackp, P, tokens, index));
      if (! yys->yyresolved)
        YYCHK (yyresolveValue (yys, yystackp, P, tokens, index));
    }
  return yyok;
}

/** Resolve the states for the RHS of YYOPT on *YYSTACKP, perform its
 *  user action, and return the semantic value and location in *YYVALP
 *  and *YYLOCP.  Regardless of whether result = yyok, all RHS states
 *  have been destroyed (assuming the user action destroys all RHS
 *  semantic values if invoked).  */
static YYRESULTTAG
yyresolveAction (yySemanticOption* yyopt, yyGLRStack* yystackp,
                 YYSTYPE* yyvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  yyGLRStackItem yyrhsVals[YYMAXRHS + YYMAXLEFT + 1];
  int yynrhs = yyrhsLength (yyopt->yyrule);
  YYRESULTTAG yyflag =
    yyresolveStates (yyopt->yystate, yynrhs, yystackp, P, tokens, index);
  if (yyflag != yyok)
    {
      yyGLRState *yys;
      for (yys = yyopt->yystate; yynrhs > 0; yys = yys->yypred, yynrhs -= 1)
        yydestroyGLRState ("Cleanup: popping", yys, P, tokens, index);
      return yyflag;
    }

  yyrhsVals[YYMAXRHS + YYMAXLEFT].yystate.yypred = yyopt->yystate;
  {
    int yychar_current = yychar;
    YYSTYPE yylval_current = yylval;
    yychar = yyopt->yyrawchar;
    yylval = yyopt->yyval;
    yyflag = yyuserAction (yyopt->yyrule, yynrhs,
                           yyrhsVals + YYMAXRHS + YYMAXLEFT - 1,
                           yystackp, yyvalp, P, tokens, index);
    yychar = yychar_current;
    yylval = yylval_current;
  }
  return yyflag;
}

#if YYDEBUG
static void
yyreportTree (yySemanticOption* yyx, int yyindent)
{
  int yynrhs = yyrhsLength (yyx->yyrule);
  int yyi;
  yyGLRState* yys;
  yyGLRState* yystates[1 + YYMAXRHS];
  yyGLRState yyleftmost_state;

  for (yyi = yynrhs, yys = yyx->yystate; 0 < yyi; yyi -= 1, yys = yys->yypred)
    yystates[yyi] = yys;
  if (yys == YY_NULLPTR)
    {
      yyleftmost_state.yyposn = 0;
      yystates[0] = &yyleftmost_state;
    }
  else
    yystates[0] = yys;

  if (yyx->yystate->yyposn < yys->yyposn + 1)
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, empty>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1);
  else
    YYFPRINTF (stderr, "%*s%s -> <Rule %d, tokens %lu .. %lu>\n",
               yyindent, "", yytokenName (yylhsNonterm (yyx->yyrule)),
               yyx->yyrule - 1, (unsigned long int) (yys->yyposn + 1),
               (unsigned long int) yyx->yystate->yyposn);
  for (yyi = 1; yyi <= yynrhs; yyi += 1)
    {
      if (yystates[yyi]->yyresolved)
        {
          if (yystates[yyi-1]->yyposn+1 > yystates[yyi]->yyposn)
            YYFPRINTF (stderr, "%*s%s <empty>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]));
          else
            YYFPRINTF (stderr, "%*s%s <tokens %lu .. %lu>\n", yyindent+2, "",
                       yytokenName (yystos[yystates[yyi]->yylrState]),
                       (unsigned long int) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long int) yystates[yyi]->yyposn);
        }
      else
        yyreportTree (yystates[yyi]->yysemantics.yyfirstVal, yyindent+2);
    }
}
#endif

static YYRESULTTAG
yyreportAmbiguity (yySemanticOption* yyx0,
                   yySemanticOption* yyx1, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  YYUSE (yyx0);
  YYUSE (yyx1);

#if YYDEBUG
  YYFPRINTF (stderr, "Ambiguity detected.\n");
  YYFPRINTF (stderr, "Option 1,\n");
  yyreportTree (yyx0, 2);
  YYFPRINTF (stderr, "\nOption 2,\n");
  yyreportTree (yyx1, 2);
  YYFPRINTF (stderr, "\n");
#endif

  yyerror (P, tokens, index, YY_("syntax is ambiguous"));
  return yyabort;
}

/** Resolve the ambiguity represented in state YYS in *YYSTACKP,
 *  perform the indicated actions, and set the semantic value of YYS.
 *  If result != yyok, the chain of semantic options in YYS has been
 *  cleared instead or it has been left unmodified except that
 *  redundant options may have been removed.  Regardless of whether
 *  result = yyok, YYS has been left with consistent data so that
 *  yydestroyGLRState can be invoked if necessary.  */
static YYRESULTTAG
yyresolveValue (yyGLRState* yys, yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  yySemanticOption* yyoptionList = yys->yysemantics.yyfirstVal;
  yySemanticOption* yybest = yyoptionList;
  yySemanticOption** yypp;
  yybool yymerge = yyfalse;
  YYSTYPE yysval;
  YYRESULTTAG yyflag;

  for (yypp = &yyoptionList->yynext; *yypp != YY_NULLPTR; )
    {
      yySemanticOption* yyp = *yypp;

      if (yyidenticalOptions (yybest, yyp))
        {
          yymergeOptionSets (yybest, yyp);
          *yypp = yyp->yynext;
        }
      else
        {
          switch (yypreference (yybest, yyp))
            {
            case 0:
              return yyreportAmbiguity (yybest, yyp, P, tokens, index);
              break;
            case 1:
              yymerge = yytrue;
              break;
            case 2:
              break;
            case 3:
              yybest = yyp;
              yymerge = yyfalse;
              break;
            default:
              /* This cannot happen so it is not worth a YYASSERT (yyfalse),
                 but some compilers complain if the default case is
                 omitted.  */
              break;
            }
          yypp = &yyp->yynext;
        }
    }

  if (yymerge)
    {
      yySemanticOption* yyp;
      int yyprec = yydprec[yybest->yyrule];
      yyflag = yyresolveAction (yybest, yystackp, &yysval, P, tokens, index);
      if (yyflag == yyok)
        for (yyp = yybest->yynext; yyp != YY_NULLPTR; yyp = yyp->yynext)
          {
            if (yyprec == yydprec[yyp->yyrule])
              {
                YYSTYPE yysval_other;
                yyflag = yyresolveAction (yyp, yystackp, &yysval_other, P, tokens, index);
                if (yyflag != yyok)
                  {
                    yydestruct ("Cleanup: discarding incompletely merged value for",
                                yystos[yys->yylrState],
                                &yysval, P, tokens, index);
                    break;
                  }
                yyuserMerge (yymerger[yyp->yyrule], &yysval, &yysval_other);
              }
          }
    }
  else
    yyflag = yyresolveAction (yybest, yystackp, &yysval, P, tokens, index);

  if (yyflag == yyok)
    {
      yys->yyresolved = yytrue;
      yys->yysemantics.yysval = yysval;
    }
  else
    yys->yysemantics.yyfirstVal = YY_NULLPTR;
  return yyflag;
}

static YYRESULTTAG
yyresolveStack (yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  if (yystackp->yysplitPoint != YY_NULLPTR)
    {
      yyGLRState* yys;
      int yyn;

      for (yyn = 0, yys = yystackp->yytops.yystates[0];
           yys != yystackp->yysplitPoint;
           yys = yys->yypred, yyn += 1)
        continue;
      YYCHK (yyresolveStates (yystackp->yytops.yystates[0], yyn, yystackp
                             , P, tokens, index));
    }
  return yyok;
}

static void
yycompressStack (yyGLRStack* yystackp)
{
  yyGLRState* yyp, *yyq, *yyr;

  if (yystackp->yytops.yysize != 1 || yystackp->yysplitPoint == YY_NULLPTR)
    return;

  for (yyp = yystackp->yytops.yystates[0], yyq = yyp->yypred, yyr = YY_NULLPTR;
       yyp != yystackp->yysplitPoint;
       yyr = yyp, yyp = yyq, yyq = yyp->yypred)
    yyp->yypred = yyr;

  yystackp->yyspaceLeft += yystackp->yynextFree - yystackp->yyitems;
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= yystackp->yynextFree - yystackp->yyitems;
  yystackp->yysplitPoint = YY_NULLPTR;
  yystackp->yylastDeleted = YY_NULLPTR;

  while (yyr != YY_NULLPTR)
    {
      yystackp->yynextFree->yystate = *yyr;
      yyr = yyr->yypred;
      yystackp->yynextFree->yystate.yypred = &yystackp->yynextFree[-1].yystate;
      yystackp->yytops.yystates[0] = &yystackp->yynextFree->yystate;
      yystackp->yynextFree += 1;
      yystackp->yyspaceLeft -= 1;
    }
}

static YYRESULTTAG
yyprocessOneStack (yyGLRStack* yystackp, size_t yyk,
                   size_t yyposn, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  while (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
    {
      yyStateNum yystate = yystackp->yytops.yystates[yyk]->yylrState;
      YYDPRINTF ((stderr, "Stack %lu Entering state %d\n",
                  (unsigned long int) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], P, tokens, index);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          if (yyflag != yyok)
            return yyflag;
        }
      else
        {
          yySymbol yytoken;
          int yyaction;
          const short int* yyconflicts;

          yystackp->yytops.yylookaheadNeeds[yyk] = yytrue;
          if (yychar == YYEMPTY)
            {
              YYDPRINTF ((stderr, "Reading a token: "));
              yychar = yylex (&yylval, P, tokens, index);
            }

          if (yychar <= YYEOF)
            {
              yychar = yytoken = YYEOF;
              YYDPRINTF ((stderr, "Now at end of input.\n"));
            }
          else
            {
              yytoken = YYTRANSLATE (yychar);
              YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
            }

          yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);

          while (*yyconflicts != 0)
            {
              YYRESULTTAG yyflag;
              size_t yynewStack = yysplitStack (yystackp, yyk);
              YYDPRINTF ((stderr, "Splitting off stack %lu from %lu.\n",
                          (unsigned long int) yynewStack,
                          (unsigned long int) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], P, tokens, index);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, P, tokens, index));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long int) yynewStack));
                  yymarkStackDeleted (yystackp, yynewStack);
                }
              else
                return yyflag;
              yyconflicts += 1;
            }

          if (yyisShiftAction (yyaction))
            break;
          else if (yyisErrorAction (yyaction))
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long int) yyk));
              yymarkStackDeleted (yystackp, yyk);
              break;
            }
          else
            {
              YYRESULTTAG yyflag = yyglrReduce (yystackp, yyk, -yyaction,
                                                yyimmediate[-yyaction], P, tokens, index);
              if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr,
                              "Stack %lu dies "
                              "(predicate failure or explicit user error).\n",
                              (unsigned long int) yyk));
                  yymarkStackDeleted (yystackp, yyk);
                  break;
                }
              else if (yyflag != yyok)
                return yyflag;
            }
        }
    }
  return yyok;
}

static void
yyreportSyntaxError (yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  if (yystackp->yyerrState != 0)
    return;
#if ! YYERROR_VERBOSE
  yyerror (P, tokens, index, YY_("syntax error"));
#else
  {
  yySymbol yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);
  size_t yysize0 = yytnamerr (YY_NULLPTR, yytokenName (yytoken));
  size_t yysize = yysize0;
  yybool yysize_overflow = yyfalse;
  char* yymsg = YY_NULLPTR;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected").  */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[yystackp->yytops.yystates[0]->yylrState];
      yyarg[yycount++] = yytokenName (yytoken);
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for this
             state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;
          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytokenName (yyx);
                {
                  size_t yysz = yysize + yytnamerr (YY_NULLPTR, yytokenName (yyx));
                  yysize_overflow |= yysz < yysize;
                  yysize = yysz;
                }
              }
        }
    }

  switch (yycount)
    {
#define YYCASE_(N, S)                   \
      case N:                           \
        yyformat = S;                   \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  {
    size_t yysz = yysize + strlen (yyformat);
    yysize_overflow |= yysz < yysize;
    yysize = yysz;
  }

  if (!yysize_overflow)
    yymsg = (char *) YYMALLOC (yysize);

  if (yymsg)
    {
      char *yyp = yymsg;
      int yyi = 0;
      while ((*yyp = *yyformat))
        {
          if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
            {
              yyp += yytnamerr (yyp, yyarg[yyi++]);
              yyformat += 2;
            }
          else
            {
              yyp++;
              yyformat++;
            }
        }
      yyerror (P, tokens, index, yymsg);
      YYFREE (yymsg);
    }
  else
    {
      yyerror (P, tokens, index, YY_("syntax error"));
      yyMemoryExhausted (yystackp);
    }
  }
#endif /* YYERROR_VERBOSE */
  yynerrs += 1;
}

/* Recover from a syntax error on *YYSTACKP, assuming that *YYSTACKP->YYTOKENP,
   yylval, and yylloc are the syntactic category, semantic value, and location
   of the lookahead.  */
static void
yyrecoverSyntaxError (yyGLRStack* yystackp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  size_t yyk;
  int yyj;

  if (yystackp->yyerrState == 3)
    /* We just shifted the error token and (perhaps) took some
       reductions.  Skip tokens until we can proceed.  */
    while (yytrue)
      {
        yySymbol yytoken;
        if (yychar == YYEOF)
          yyFail (yystackp, P, tokens, index, YY_NULLPTR);
        if (yychar != YYEMPTY)
          {
            yytoken = YYTRANSLATE (yychar);
            yydestruct ("Error: discarding",
                        yytoken, &yylval, P, tokens, index);
          }
        YYDPRINTF ((stderr, "Reading a token: "));
        yychar = yylex (&yylval, P, tokens, index);
        if (yychar <= YYEOF)
          {
            yychar = yytoken = YYEOF;
            YYDPRINTF ((stderr, "Now at end of input.\n"));
          }
        else
          {
            yytoken = YYTRANSLATE (yychar);
            YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
          }
        yyj = yypact[yystackp->yytops.yystates[0]->yylrState];
        if (yypact_value_is_default (yyj))
          return;
        yyj += yytoken;
        if (yyj < 0 || YYLAST < yyj || yycheck[yyj] != yytoken)
          {
            if (yydefact[yystackp->yytops.yystates[0]->yylrState] != 0)
              return;
          }
        else if (! yytable_value_is_error (yytable[yyj]))
          return;
      }

  /* Reduce to one stack.  */
  for (yyk = 0; yyk < yystackp->yytops.yysize; yyk += 1)
    if (yystackp->yytops.yystates[yyk] != YY_NULLPTR)
      break;
  if (yyk >= yystackp->yytops.yysize)
    yyFail (yystackp, P, tokens, index, YY_NULLPTR);
  for (yyk += 1; yyk < yystackp->yytops.yysize; yyk += 1)
    yymarkStackDeleted (yystackp, yyk);
  yyremoveDeletes (yystackp);
  yycompressStack (yystackp);

  /* Now pop stack until we find a state that shifts the error token.  */
  yystackp->yyerrState = 3;
  while (yystackp->yytops.yystates[0] != YY_NULLPTR)
    {
      yyGLRState *yys = yystackp->yytops.yystates[0];
      yyj = yypact[yys->yylrState];
      if (! yypact_value_is_default (yyj))
        {
          yyj += YYTERROR;
          if (0 <= yyj && yyj <= YYLAST && yycheck[yyj] == YYTERROR
              && yyisShiftAction (yytable[yyj]))
            {
              /* Shift the error token.  */
              YY_SYMBOL_PRINT ("Shifting", yystos[yytable[yyj]],
                               &yylval, &yyerrloc);
              yyglrShift (yystackp, 0, yytable[yyj],
                          yys->yyposn, &yylval);
              yys = yystackp->yytops.yystates[0];
              break;
            }
        }
      if (yys->yypred != YY_NULLPTR)
        yydestroyGLRState ("Error: popping", yys, P, tokens, index);
      yystackp->yytops.yystates[0] = yys->yypred;
      yystackp->yynextFree -= 1;
      yystackp->yyspaceLeft += 1;
    }
  if (yystackp->yytops.yystates[0] == YY_NULLPTR)
    yyFail (yystackp, P, tokens, index, YY_NULLPTR);
}

#define YYCHK1(YYE)                                                          \
  do {                                                                       \
    switch (YYE) {                                                           \
    case yyok:                                                               \
      break;                                                                 \
    case yyabort:                                                            \
      goto yyabortlab;                                                       \
    case yyaccept:                                                           \
      goto yyacceptlab;                                                      \
    case yyerr:                                                              \
      goto yyuser_error;                                                     \
    default:                                                                 \
      goto yybuglab;                                                         \
    }                                                                        \
  } while (0)

/*----------.
| yyparse.  |
`----------*/

int
yyparse (struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  int yyresult;
  yyGLRStack yystack;
  yyGLRStack* const yystackp = &yystack;
  size_t yyposn;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY;
  yylval = yyval_default;

  /* User initialization code.  */
  #line 118 "src/parser_proc_grammar.y" /* glr.c:2270  */
{
}

#line 5835 "src/parser_proc.c" /* glr.c:2270  */

  if (! yyinitGLRStack (yystackp, YYINITDEPTH))
    goto yyexhaustedlab;
  switch (YYSETJMP (yystack.yyexception_buffer))
    {
    case 0: break;
    case 1: goto yyabortlab;
    case 2: goto yyexhaustedlab;
    default: goto yybuglab;
    }
  yyglrShift (&yystack, 0, 0, 0, &yylval);
  yyposn = 0;

  while (yytrue)
    {
      /* For efficiency, we have two loops, the first of which is
         specialized to deterministic operation (single stack, no
         potential ambiguity).  */
      /* Standard mode */
      while (yytrue)
        {
          yyRuleNum yyrule;
          int yyaction;
          const short int* yyconflicts;

          yyStateNum yystate = yystack.yytops.yystates[0]->yylrState;
          YYDPRINTF ((stderr, "Entering state %d\n", yystate));
          if (yystate == YYFINAL)
            goto yyacceptlab;
          if (yyisDefaultedState (yystate))
            {
              yyrule = yydefaultAction (yystate);
              if (yyrule == 0)
                {

                  yyreportSyntaxError (&yystack, P, tokens, index);
                  goto yyuser_error;
                }
              YYCHK1 (yyglrReduce (&yystack, 0, yyrule, yytrue, P, tokens, index));
            }
          else
            {
              yySymbol yytoken;
              if (yychar == YYEMPTY)
                {
                  YYDPRINTF ((stderr, "Reading a token: "));
                  yychar = yylex (&yylval, P, tokens, index);
                }

              if (yychar <= YYEOF)
                {
                  yychar = yytoken = YYEOF;
                  YYDPRINTF ((stderr, "Now at end of input.\n"));
                }
              else
                {
                  yytoken = YYTRANSLATE (yychar);
                  YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
                }

              yygetLRActions (yystate, yytoken, &yyaction, &yyconflicts);
              if (*yyconflicts != 0)
                break;
              if (yyisShiftAction (yyaction))
                {
                  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
                  yychar = YYEMPTY;
                  yyposn += 1;
                  yyglrShift (&yystack, 0, yyaction, yyposn, &yylval);
                  if (0 < yystack.yyerrState)
                    yystack.yyerrState -= 1;
                }
              else if (yyisErrorAction (yyaction))
                {

                  yyreportSyntaxError (&yystack, P, tokens, index);
                  goto yyuser_error;
                }
              else
                YYCHK1 (yyglrReduce (&yystack, 0, -yyaction, yytrue, P, tokens, index));
            }
        }

      while (yytrue)
        {
          yySymbol yytoken_to_shift;
          size_t yys;

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            yystackp->yytops.yylookaheadNeeds[yys] = yychar != YYEMPTY;

          /* yyprocessOneStack returns one of three things:

              - An error flag.  If the caller is yyprocessOneStack, it
                immediately returns as well.  When the caller is finally
                yyparse, it jumps to an error label via YYCHK1.

              - yyok, but yyprocessOneStack has invoked yymarkStackDeleted
                (&yystack, yys), which sets the top state of yys to NULL.  Thus,
                yyparse's following invocation of yyremoveDeletes will remove
                the stack.

              - yyok, when ready to shift a token.

             Except in the first case, yyparse will invoke yyremoveDeletes and
             then shift the next token onto all remaining stacks.  This
             synchronization of the shift (that is, after all preceding
             reductions on all stacks) helps prevent double destructor calls
             on yylval in the event of memory exhaustion.  */

          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            YYCHK1 (yyprocessOneStack (&yystack, yys, yyposn, P, tokens, index));
          yyremoveDeletes (&yystack);
          if (yystack.yytops.yysize == 0)
            {
              yyundeleteLastStack (&yystack);
              if (yystack.yytops.yysize == 0)
                yyFail (&yystack, P, tokens, index, YY_("syntax error"));
              YYCHK1 (yyresolveStack (&yystack, P, tokens, index));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));

              yyreportSyntaxError (&yystack, P, tokens, index);
              goto yyuser_error;
            }

          /* If any yyglrShift call fails, it will fail after shifting.  Thus,
             a copy of yylval will already be on stack 0 in the event of a
             failure in the following loop.  Thus, yychar is set to YYEMPTY
             before the loop to make sure the user destructor for yylval isn't
             called twice.  */
          yytoken_to_shift = YYTRANSLATE (yychar);
          yychar = YYEMPTY;
          yyposn += 1;
          for (yys = 0; yys < yystack.yytops.yysize; yys += 1)
            {
              int yyaction;
              const short int* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long int) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long int) yys,
                          yystack.yytops.yystates[yys]->yylrState));
            }

          if (yystack.yytops.yysize == 1)
            {
              YYCHK1 (yyresolveStack (&yystack, P, tokens, index));
              YYDPRINTF ((stderr, "Returning to deterministic operation.\n"));
              yycompressStack (&yystack);
              break;
            }
        }
      continue;
    yyuser_error:
      yyrecoverSyntaxError (&yystack, P, tokens, index);
      yyposn = yystack.yytops.yystates[0]->yyposn;
    }

 yyacceptlab:
  yyresult = 0;
  goto yyreturn;

 yybuglab:
  YYASSERT (yyfalse);
  goto yyabortlab;

 yyabortlab:
  yyresult = 1;
  goto yyreturn;

 yyexhaustedlab:
  yyerror (P, tokens, index, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;

 yyreturn:
  if (yychar != YYEMPTY)
    yydestruct ("Cleanup: discarding lookahead",
                YYTRANSLATE (yychar), &yylval, P, tokens, index);

  /* If the stack is well-formed, pop the stack until it is empty,
     destroying its entries as we go.  But free the stack regardless
     of whether it is well-formed.  */
  if (yystack.yyitems)
    {
      yyGLRState** yystates = yystack.yytops.yystates;
      if (yystates)
        {
          size_t yysize = yystack.yytops.yysize;
          size_t yyk;
          for (yyk = 0; yyk < yysize; yyk += 1)
            if (yystates[yyk])
              {
                while (yystates[yyk])
                  {
                    yyGLRState *yys = yystates[yyk];
                  if (yys->yypred != YY_NULLPTR)
                      yydestroyGLRState ("Cleanup: popping", yys, P, tokens, index);
                    yystates[yyk] = yys->yypred;
                    yystack.yynextFree -= 1;
                    yystack.yyspaceLeft += 1;
                  }
                break;
              }
        }
      yyfreeGLRStack (&yystack);
    }

  return yyresult;
}

/* DEBUGGING ONLY */
#if YYDEBUG
static void
yy_yypstack (yyGLRState* yys)
{
  if (yys->yypred)
    {
      yy_yypstack (yys->yypred);
      YYFPRINTF (stderr, " -> ");
    }
  YYFPRINTF (stderr, "%d@%lu", yys->yylrState,
             (unsigned long int) yys->yyposn);
}

static void
yypstates (yyGLRState* yyst)
{
  if (yyst == YY_NULLPTR)
    YYFPRINTF (stderr, "<null>");
  else
    yy_yypstack (yyst);
  YYFPRINTF (stderr, "\n");
}

static void
yypstack (yyGLRStack* yystackp, size_t yyk)
{
  yypstates (yystackp->yytops.yystates[yyk]);
}

#define YYINDEX(YYX)                                                         \
    ((YYX) == YY_NULLPTR ? -1 : (yyGLRStackItem*) (YYX) - yystackp->yyitems)


static void
yypdumpstack (yyGLRStack* yystackp)
{
  yyGLRStackItem* yyp;
  size_t yyi;
  for (yyp = yystackp->yyitems; yyp < yystackp->yynextFree; yyp += 1)
    {
      YYFPRINTF (stderr, "%3lu. ",
                 (unsigned long int) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long int) yyp->yystate.yyposn,
                     (long int) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long int) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long int) YYINDEX (yyp->yyoption.yystate),
                     (long int) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long int) yyi,
               (long int) YYINDEX (yystackp->yytops.yystates[yyi]));
  YYFPRINTF (stderr, "\n");
}
#endif

#undef yylval
#undef yychar
#undef yynerrs

/* Substitute the variable and function names.  */
#define yyparse psi_parser_proc_parse
#define yylex   psi_parser_proc_lex
#define yyerror psi_parser_proc_error
#define yylval  psi_parser_proc_lval
#define yychar  psi_parser_proc_char
#define yydebug psi_parser_proc_debug
#define yynerrs psi_parser_proc_nerrs

#line 1648 "src/parser_proc_grammar.y" /* glr.c:2584  */


/* epilogue */

static int psi_parser_proc_lex(YYSTYPE *lvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
	struct psi_token *token;

	if (psi_plist_get(tokens, (*index)++, &token)) {
		if (P->flags & PSI_DEBUG) {
			psi_token_dump(2, token);
		}

		*((struct psi_token **)lvalp) = token;
		return token->type;
	} else {
		(*index)--;
		PSI_DEBUG_PRINT(P, "EOF(%d)\n", PSI_T_EOF);
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
		P->error(PSI_DATA(P), T, PSI_WARNING, "PSI %s at col %u", msg, T->col);
	} else {
		P->error(PSI_DATA(P), NULL, PSI_WARNING, "PSI %s", msg);
	}
	P->errors++;
}

