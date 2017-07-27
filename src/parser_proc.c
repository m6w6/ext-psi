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

#line 165 "src/parser_proc.c" /* glr.c:264  */

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
#define YYFINAL  169
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3407

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  132
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  123
/* YYNRULES -- Number of rules.  */
#define YYNRULES  485
/* YYNRULES -- Number of states.  */
#define YYNSTATES  718
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 13
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   386

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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     374,   374,   374,   374,   375,   375,   375,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   375,   375,   375,
     375,   375,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   376,   376,
     376,   376,   376,   376,   380,   381,   384,   385,   388,   389,
     390,   391,   397,   405,   408,   411,   412,   415,   418,   421,
     424,   430,   436,   439,   445,   468,   472,   476,   481,   485,
     489,   493,   500,   501,   505,   506,   510,   511,   512,   516,
     517,   521,   522,   526,   527,   528,   532,   533,   537,   538,
     539,   540,   541,   542,   546,   551,   559,   562,   565,   566,
     572,   577,   585,   588,   592,   596,   603,   607,   611,   615,
     620,   630,   640,   645,   650,   656,   665,   668,   672,   676,
     682,   689,   695,   696,   697,   698,   702,   705,   736,   743,
     744,   745,   746,   750,   753,   762,   768,   769,   777,   788,
     797,   806,   814,   817,   821,   825,   829,   834,   839,   847,
     848,   849,   852,   858,   861,   864,   870,   871,   872,   873,
     874,   875,   876,   877,   881,   882,   886,   889,   892,   898,
     901,   904,   912,   924,   927,   930,   937,   940,   950,   953,
     956,   959,   960,   964,   967,   970,   981,   984,   990,   991,
     995,   996,  1000,  1004,  1010,  1011,  1017,  1020,  1026,  1027,
    1034,  1035,  1039,  1046,  1057,  1064,  1075,  1082,  1093,  1104,
    1118,  1119,  1131,  1134,  1137,  1140,  1147,  1150,  1156,  1165,
    1177,  1185,  1188,  1198,  1211,  1216,  1224,  1234,  1244,  1247,
    1251,  1257,  1271,  1288,  1291,  1297,  1304,  1314,  1321,  1324,
    1330,  1335,  1343,  1347,  1351,  1355,  1359,  1363,  1370,  1374,
    1378,  1382,  1389,  1402,  1415,  1428,  1431,  1438,  1441,  1444,
    1447,  1453,  1457,  1464,  1467,  1470,  1476,  1479,  1485,  1486,
    1492,  1495,  1501,  1502,  1512,  1515,  1522,  1527,  1532,  1542,
    1545,  1551,  1554,  1560,  1567,  1574,  1575,  1576,  1577,  1578,
    1579,  1580,  1581,  1582,  1586,  1589,  1595,  1598,  1601,  1604,
    1607,  1613,  1617,  1625,  1626,  1630,  1637,  1640,  1643,  1647,
    1650,  1653,  1659,  1663,  1671,  1678,  1686,  1694,  1695,  1696,
    1697,  1698,  1699,  1700,  1701,  1702,  1703,  1707,  1710,  1716,
    1719,  1725,  1726,  1730,  1733,  1739,  1742,  1748,  1755,  1762,
    1765,  1768,  1775,  1780,  1788,  1789,  1790,  1791,  1792,  1793,
    1794,  1795,  1799,  1802,  1808,  1811,  1817,  1824,  1825,  1829,
    1836,  1839,  1845,  1853,  1856,  1862
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
  "\"?\"", "PRAGMA", "PRAGMA_ONCE", "LINE", "ERROR", "WARNING", "IF",
  "IFDEF", "IFNDEF", "ELSE", "ELIF", "ENDIF", "DEFINE", "DEFINED", "UNDEF",
  "IMPORT", "INCLUDE", "INCLUDE_NEXT", "TYPEDEF", "STRUCT", "UNION",
  "ENUM", "CONST", "LIB", "STATIC", "CALLBACK", "FUNCTION", "LET", "SET",
  "TEMP", "FREE", "RETURN", "PRE_ASSERT", "POST_ASSERT", "BOOLVAL",
  "INTVAL", "STRVAL", "PATHVAL", "STRLEN", "FLOATVAL", "ARRVAL", "OBJVAL",
  "COUNT", "CALLOC", "TO_BOOL", "TO_INT", "TO_STRING", "TO_FLOAT",
  "TO_ARRAY", "TO_OBJECT", "COMMENT", "WHITESPACE", "NO_WHITESPACE",
  "CPP_HEADER", "CPP_ATTRIBUTE", "CPP_EXTENSION", "CPP_PASTE",
  "CPP_RESTRICT", "CPP_ASM", "BINARY", "UNARY", "$accept",
  "binary_op_token", "unary_op_token", "name_token", "any_noeol_token",
  "file", "blocks", "block", "lib", "cpp", "cpp_exp", "cpp_ignored_token",
  "cpp_message_token", "cpp_include_token", "cpp_header_token",
  "cpp_no_arg_token", "cpp_name_arg_token", "cpp_exp_arg_token",
  "cpp_special_name_token", "cpp_macro_decl", "cpp_macro_sig",
  "cpp_macro_sig_args", "cpp_macro_decl_tokens",
  "cpp_macro_decl_token_list", "cpp_macro_exp", "cpp_macro_call_args",
  "cpp_macro_call_arg_list", "constant", "constant_type",
  "constant_type_token", "impl_def_val", "impl_def_val_token",
  "decl_typedef", "typedef", "const_decl_type", "decl_type",
  "decl_type_complex", "decl_type_simple", "decl_real_type",
  "decl_stdint_type", "int_signed", "int_width", "decl_int_type",
  "int_signed_types", "signed_short_types", "signed_long_types",
  "int_width_types", "decl_stmt", "decl_asm", "ignored_quoted_strings",
  "decl_ext_var_stmt", "decl_ext_var", "decl_ext_var_list", "decl_vars",
  "decl", "decl_body", "decl_func_body", "decl_functor_body",
  "decl_functor", "decl_func", "decl_args", "decl_anon_arg", "decl_arg",
  "decl_var", "decl_union", "decl_struct", "decl_struct_args",
  "struct_args_block", "struct_args", "struct_arg_var_list",
  "decl_vars_with_layout", "decl_enum", "decl_enum_items",
  "decl_enum_item", "num_exp", "number", "enum_name", "union_name",
  "struct_name", "optional_name", "decl_layout", "align_and_size",
  "array_size", "indirection", "pointers", "asterisks", "asterisk", "impl",
  "impl_func", "impl_args", "impl_arg", "impl_var", "impl_type",
  "impl_type_token", "impl_stmts", "impl_stmt", "let_stmt", "let_exp",
  "let_exp_byref", "let_exp_assign", "let_calloc", "let_callback",
  "let_func", "let_func_token", "let_func_exps", "let_exps",
  "callback_rval", "callback_arg_list", "callback_args", "return_stmt",
  "set_stmt", "set_exp", "set_func", "set_func_token", "set_func_exps",
  "set_exps", "assert_stmt", "assert_stmt_token", "free_stmt", "free_exps",
  "free_exp", "reference", "byref", YY_NULLPTR
};
#endif

#define YYPACT_NINF -565
#define YYTABLE_NINF -484

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     954,  -565,  -565,  -565,  -565,  -565,   113,  -565,  -565,  2258,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  2910,  -565,
    -565,   192,  2937,  2766,  2766,  2766,   541,    35,    10,    50,
    -565,   313,    95,   954,  -565,  -565,  -565,  -565,  -565,  2307,
    -565,  -565,  -565,  -565,  -565,    41,    36,  -565,  -565,  -565,
      75,    -4,  -565,  -565,    79,    77,   106,  -565,  -565,  -565,
    -565,    91,  -565,   116,  -565,  -565,  -565,  -565,  -565,   664,
    -565,   105,    71,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  2425,   -22,  -565,  -565,  -565,  -565,  2766,  2766,
    2766,  3091,  -565,   107,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,   913,  -565,  -565,  -565,
    -565,   149,   794,   794,     3,  -565,   913,  2140,  2258,  2766,
    2766,   150,  1904,  -565,  -565,   153,  2766,   154,   154,    33,
      33,   162,  -565,  -565,   175,   184,  -565,   105,   187,  -565,
    -565,   182,   197,  -565,   198,  -565,  2987,  3014,    -4,  -565,
    -565,   196,  -565,   204,  2766,  -565,   239,  -565,    73,  -565,
    -565,    41,  -565,  -565,   208,   210,  3041,  3041,  2766,   -41,
    2766,  -565,  -565,   105,  -565,  -565,  -565,  -565,  -565,  -565,
    2307,  -565,  -565,  -565,  -565,  -565,  -565,   126,   794,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,   794,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  2140,  -565,  -565,  -565,  -565,  2474,
    2140,   215,  3264,   211,    13,  -565,    13,  -565,  -565,  -565,
    -565,   214,   216,   216,    30,    30,  2592,   213,  -565,   -41,
     218,   220,   224,     8,  -565,   105,   196,  -565,  -565,  -565,
    -565,  -565,  -565,   228,  -565,     1,  3118,  2307,    45,  -565,
    -565,   129,   217,    46,  -565,  2307,  1786,  2307,  2766,    81,
    -565,  -565,   109,  -565,  -565,  -565,  -565,  -565,  2022,  -565,
     237,  2766,   241,  -565,  2766,   244,  -565,  -565,  3136,  2766,
    -565,  -565,  2140,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  2140,  2140,  -565,   245,  3014,  2307,  2307,  -565,  -565,
    -565,  -565,   105,  -565,  1196,   123,   371,  -565,  -565,   240,
    -565,  2766,  -565,  -565,    42,  2425,   105,   204,   196,  1048,
     196,  2883,  2022,  2766,  -565,   238,   249,  -565,  -565,  -565,
    1078,  2022,  -565,  3288,  -565,   242,   250,  -565,   255,   262,
     251,   257,    56,  -565,  -565,   259,   255,  -565,  -565,  3108,
    -565,   260,  2307,  2643,  -565,   263,  3264,   265,   266,  3215,
    -565,   274,   267,  1945,  -565,  -565,  2766,  -565,  -565,  -565,
    -565,   272,  -565,  3288,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -565,  -565,  -565,   269,   141,  -565,    50,  -565,  -565,
     276,  -565,  -565,  2592,  -565,     1,   286,  -565,  -565,   289,
    3288,  -565,  1314,  -565,   290,   485,   292,  3163,  -565,  2022,
    2022,  1786,  -565,  2307,  -565,    50,  2307,  -565,  2766,  -565,
    -565,  -565,  -565,  -565,  -565,   301,   273,  -565,  -565,  2140,
    2140,   302,     7,   305,  -565,   267,   307,  -565,   464,   300,
     464,   306,  -565,   196,   196,  -565,   233,   125,   315,  3288,
    -565,  -565,  -565,  -565,   316,  1432,  2022,  -565,  3240,  -565,
    -565,   311,  2307,   143,  -565,   794,  2717,  3264,  3312,   322,
     319,   323,  2307,   320,   305,  -565,  -565,   464,  -565,    50,
    1196,  -565,  -565,   315,  -565,  -565,  -565,  -565,   324,  2022,
      50,  -565,  -565,  2022,  1550,   325,   328,  -565,  -565,  -565,
    -565,   330,   326,   337,   267,   331,  -565,   335,  -565,    -2,
    -565,    50,   594,   333,  3336,   336,  -565,   339,  -565,  -565,
    -565,   338,   342,  -565,  2307,  -565,   357,   352,  2022,  1314,
     353,  -565,  1786,   360,   361,   267,   356,  1668,  3190,   238,
    -565,  -565,  -565,   359,  1432,  -565,  -565,   369,   358,  -565,
     355,   362,   372,  -565,  -565,  1314,  -565,   367,  -565,   464,
     374,  1786,  -565,   376,  -565,  -565,  -565,  -565
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short int yydefact[] =
{
     164,   289,   286,   290,   284,   285,   287,   273,   274,     0,
     276,   277,   278,   279,   280,   281,   282,   283,   272,   169,
     168,     0,     0,     0,     0,   375,     0,     0,     0,   483,
     170,     0,     0,   165,   166,   172,   171,   173,   176,   386,
     263,   265,   264,   270,   271,   293,   303,   269,   174,   175,
       0,   308,   318,   320,   321,     0,     0,   330,   178,   177,
     179,     0,   180,     0,   288,   275,    33,    34,   471,   437,
      24,   386,   392,    39,    38,    37,    35,    36,    32,    31,
      25,    29,    28,    26,    27,   445,   444,   442,   440,   441,
     443,   439,   438,   446,    30,   469,   467,   466,   468,   465,
     464,   331,     0,   388,   390,    40,    41,   272,     0,     0,
       0,     0,   319,   314,   182,   193,   190,   192,   194,   195,
     206,   203,   204,   201,   207,   202,     0,   205,   196,   197,
     198,     0,   222,   222,     0,   186,     0,     0,     0,   375,
     375,     0,   386,   257,   340,   256,     0,   381,   381,   266,
     267,   268,   372,   242,   290,   273,   245,     0,     0,   241,
     262,     0,     0,   485,     0,   484,   272,     0,   308,     1,
     167,   383,   341,     0,   387,   294,   298,   296,   300,   291,
     304,   293,   292,   312,     0,     0,   332,   332,     0,     0,
       0,   387,   393,   386,   343,   389,   391,   266,   267,   268,
       0,   313,   209,   210,   211,   213,   212,   208,   222,   188,
     183,    75,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   115,
     113,   114,   112,   110,   111,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   162,
     160,   161,   163,   224,   191,   223,   184,   199,   200,   185,
     208,   187,   232,   233,     0,    22,    23,    20,    21,     0,
       0,   234,   189,   331,   266,   374,   267,   373,   253,   261,
     258,     0,     0,     0,     0,     0,     0,     0,   181,     0,
       0,     0,     0,     0,   345,   386,   383,   299,   295,   301,
     302,   297,   305,     0,   306,   333,     0,   386,     0,   334,
     336,     0,   360,     0,   358,     0,   483,     0,     0,     0,
     477,   478,     0,   414,   417,   416,   418,   419,     0,   420,
       0,     0,   315,   316,     0,     0,   215,   225,     0,     0,
     230,   227,   236,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    13,    12,    14,    15,    16,    17,    18,
      19,     0,     0,   254,     0,     0,     0,     0,   348,   347,
     349,   346,   386,   342,   246,     0,     0,   255,   307,     0,
     384,     0,   344,   310,     0,   339,     0,   337,   383,     0,
     383,     0,     0,     0,   357,     0,     0,   369,   368,   370,
       0,     0,   371,   460,   362,     0,     0,   459,    41,     0,
       0,     0,     0,   480,   470,     0,     0,   394,   415,     0,
     329,     0,     0,   216,   226,     0,   238,     0,   237,     0,
     228,     0,   377,     0,   260,   259,     0,   249,   250,   251,
     252,     0,   248,   247,   395,   407,   408,   409,   410,   406,
     411,   412,   413,   405,     0,     0,   399,   483,   404,   385,
       0,   311,   309,   338,   324,     0,     0,   335,   322,     0,
     361,   359,     0,   421,    24,     0,     0,     0,   366,     0,
       0,   483,   458,     0,   403,   483,     0,   479,     0,   457,
     476,   328,   317,   217,   220,     0,   218,   231,   235,     0,
       0,     0,     0,   353,   350,   377,     0,   240,     0,     0,
       0,   401,   326,   383,   383,   426,     0,    31,    30,   431,
     432,   427,   429,   430,    40,     0,     0,   364,     0,   365,
     461,   472,     0,     0,   481,   222,     0,   239,   229,     0,
     378,     0,     0,     0,   353,   327,   396,     0,   400,   483,
     246,   325,   323,     0,   428,   451,   437,   452,     0,     0,
     483,   433,   363,     0,   483,     0,     0,   482,   214,   219,
     221,     0,     0,     0,   377,   354,   351,     0,   397,     0,
     402,   483,     0,   447,   367,     0,   474,   473,   462,   422,
     382,     0,     0,   355,     0,   352,     0,     0,     0,     0,
       0,   463,   483,     0,     0,   377,     0,   453,     0,   371,
     449,   425,   423,   448,     0,   436,   475,     0,     0,   356,
       0,     0,   454,   455,   434,     0,   424,     0,   379,     0,
       0,   483,   450,     0,   398,   435,   456,   380
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -565,  -317,  -130,     0,    82,  -565,  -565,   383,  -565,  -565,
    -565,  -565,  -565,  -565,  -565,  -565,  -565,  -565,   282,  -565,
    -565,  -565,  -128,  -565,  -328,  -565,  -565,  -565,  -565,  -565,
    -210,  -565,  -565,  -154,   -11,   -23,  -565,  -565,  -565,   279,
     377,  -565,  -565,   243,  -565,  -565,  -565,  -565,   258,  -565,
    -565,  -565,  -565,  -141,   396,    -1,   -16,    18,  -565,  -565,
     246,  -312,   -14,   -39,  -565,  -565,    65,  -285,  -565,  -196,
    -565,    38,  -565,   -38,  -389,  -565,  -565,  -565,  -565,    63,
    -564,   -20,  -350,   -61,    -7,  -565,   329,  -565,   408,  -565,
    -153,  -506,  -561,  -565,    69,  -368,  -565,  -266,  -532,    48,
    -156,  -565,  -565,  -500,  -565,  -565,  -565,  -565,  -565,  -565,
    -565,  -533,    47,  -384,  -565,  -565,  -565,  -565,  -565,  -565,
    -124,   -28,  -538
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,   560,   481,   171,   333,    32,    33,    34,    35,    36,
     131,   132,   133,   134,   339,   135,   136,   137,   208,   209,
     575,   576,   334,   335,   352,   507,   508,    37,   158,   159,
     521,   522,    38,   141,    39,    40,    41,    42,    43,    44,
      45,    46,    47,   179,   378,   381,   182,    48,   185,   464,
      49,    50,   201,   412,    51,    52,    53,   144,    55,    56,
     388,   389,    57,   482,    58,    59,   449,   450,   513,   623,
     655,   146,   393,   394,   483,   484,    61,   147,   148,   152,
     583,   362,   374,   173,   414,   103,   104,    62,    63,   535,
     536,   485,   537,   538,   402,   403,   404,   690,   691,   692,
     601,   602,   603,   105,   680,   693,   638,   701,   702,   405,
     406,   486,   487,   106,   645,   667,   407,   408,   409,   492,
     493,   489,   165
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
     172,   164,   102,   160,   113,   336,   143,   350,   145,   101,
     190,   142,   488,   371,   605,   496,   418,   112,    54,   499,
     600,   624,   421,   149,   150,   151,   462,   626,   610,   629,
     564,   591,   174,    72,   498,   442,    54,   337,    60,    71,
     620,   459,   180,     4,     5,   175,   176,   177,   621,    54,
     178,    54,   604,   460,  -376,  -376,    72,   395,   396,   397,
     398,   399,   400,   401,   191,   523,   658,   448,   676,   161,
    -381,    60,   445,   641,   361,  -381,   541,   446,   447,   379,
     416,   542,   380,   550,   468,   469,   473,   498,   160,   474,
     673,   557,   558,   567,   506,   169,   568,   637,    68,   494,
     163,   442,   194,   172,   442,   604,   195,    29,   197,   198,
     199,   666,   183,   509,   510,   186,  -321,  -340,   544,  -340,
     548,   699,    64,   591,    65,   184,   207,   338,   363,   364,
     365,   102,   411,   188,   663,   174,   340,   351,   353,   354,
     356,   694,   635,   636,   187,  -330,   360,   200,   714,   696,
     366,   143,   497,   145,   703,   677,   142,   547,   189,   547,
      72,   413,   706,   599,   192,   112,   524,   694,   470,   471,
     608,   609,   390,   390,   376,   387,   387,   488,   716,   604,
     589,   590,   647,   502,    54,   210,   191,   358,   392,   442,
     410,  -330,   442,   442,   604,   361,    95,    96,    97,    98,
      99,   100,   355,   357,  -376,   604,  -243,   395,   396,   397,
     398,   399,   400,   401,   350,  -244,   599,   642,   367,   368,
     350,   395,   396,   397,   398,   399,   400,   401,   114,   370,
      85,    86,    87,    88,    89,    90,    91,    92,    93,   369,
     373,   523,   375,   631,   632,   377,   383,   384,   443,   415,
     662,   617,   618,   422,   664,   444,   456,   457,   445,   454,
     488,   458,   463,   472,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   500,   127,   128,   129,
     130,   502,   503,   511,   552,   539,   553,   562,   561,   688,
     599,   512,   350,   563,   564,   566,   569,   565,   488,   571,
     442,   442,   577,   488,   578,   599,   579,   581,   582,   587,
     588,   350,   350,   616,   461,   592,   599,     1,     2,     3,
       4,     5,     6,     7,     8,   593,   467,   488,   594,   -24,
       9,   606,    10,    11,    12,    13,    14,    15,    16,    17,
     615,   627,   619,   166,   351,   622,   625,   633,   172,   420,
     351,   644,   630,   639,   640,   651,   475,   656,   490,   585,
     652,   653,   661,   160,   668,   669,   453,   671,   191,   670,
     672,   674,   675,   679,   525,   681,   683,   526,   465,   682,
     174,   527,   684,   528,   529,   530,   531,   532,   533,   686,
     687,   516,   695,   697,   698,   700,   709,   708,   491,   705,
     713,   710,   167,   108,   109,   110,   111,   514,   515,   707,
     534,   501,   711,   715,   376,   717,   170,   417,   341,   505,
     660,   359,   351,   181,   382,   613,   372,   168,   657,   143,
     451,   145,   196,   391,   142,   551,   162,   628,   455,   712,
     634,   351,   351,   476,   614,   191,   495,     0,     0,   350,
     350,     0,     0,     0,     0,   390,     0,   390,   387,   543,
     387,   540,     0,   572,     0,   194,     0,   525,     0,   556,
     526,     0,     0,   392,   527,     0,   528,   529,   530,   531,
     532,   533,     0,     0,     0,     0,     0,   648,     0,     1,
       2,     3,     4,     5,     6,     7,     8,   143,     0,   145,
       0,     0,   142,   574,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,   107,   586,     0,     0,     0,
       0,     0,     0,     0,   611,     0,     0,   413,     0,     0,
       0,     0,   160,     0,     0,     0,     0,   612,   465,     0,
       0,     0,     0,   453,   153,     1,     2,   154,     4,     5,
       6,   155,     8,   156,     0,     0,     0,     0,   157,     0,
      10,    11,    12,    13,    14,    15,    16,    17,   491,     0,
       0,   107,     0,   646,     0,   108,   109,   110,     0,   351,
     351,     0,     0,   654,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   659,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   650,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   678,   685,     0,     0,     0,     0,
     689,     0,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
       0,     0,     0,     0,  -437,   559,   689,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
       0,  -437,     0,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,  -437,
    -437,  -437,  -437,  -437,  -437,  -437,     0,  -437,  -437,     0,
    -437,  -437,  -437,  -437,   211,     0,     0,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
       0,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
       0,   294,     0,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,    66,     0,   328,     0,
     329,   330,   331,   332,     0,    67,     0,     0,     0,     0,
      68,    69,     0,     0,     0,     0,     0,     0,     0,     0,
     202,   203,   204,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       0,     9,     0,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,    18,    73,    74,    75,    76,    77,
      19,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,    78,     0,    79,
      80,    81,    82,    83,    84,     0,     0,     0,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,     0,     0,     0,   205,
       0,   206,     0,    22,    23,    24,    25,    26,    27,    28,
       0,    29,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     0,     0,     0,     0,   545,     0,    10,    11,    12,
      13,    14,    15,    16,    17,    30,     0,     0,   107,     0,
      31,    66,     1,     2,     3,     4,     5,     6,     7,     8,
      67,     0,     0,     0,     0,    68,    69,    10,    11,    12,
      13,    14,    15,    16,    17,     0,     0,     0,   554,   477,
       0,   478,     0,   479,     0,     0,   480,     0,   546,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   345,   346,    72,     0,     0,     0,     0,   108,   109,
     110,   386,     0,     0,   347,   348,     0,     0,     0,     0,
      73,    74,    75,    76,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
     110,   555,    78,     0,    79,    80,    81,    82,    83,    84,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    66,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,    68,    69,     0,     0,     0,     0,     0,
       0,     0,     0,   517,   518,   519,    70,   477,     0,   478,
     520,   479,     0,     0,   480,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   345,
     346,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   347,   348,     0,     0,     0,     0,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,     0,    79,    80,    81,    82,    83,    84,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    66,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,    68,    69,     0,     0,     0,     0,     0,     0,     0,
       0,   595,     0,     0,    70,   477,     0,   478,     0,   479,
       0,     0,   480,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   163,     0,     0,   345,   346,    72,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     347,   348,     0,     0,     0,     0,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,   596,
     597,    80,    81,    82,    83,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,   598,    95,
      96,    97,    98,    99,   100,    66,     0,     0,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,   595,
       0,     0,    70,   477,     0,   478,     0,   479,     0,     0,
     480,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   345,   346,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   347,   348,
       0,     0,     0,     0,    73,    74,    75,    76,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,   596,   597,    80,
      81,    82,    83,    84,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,   598,    95,    96,    97,
      98,    99,   100,    66,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,    68,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,   477,     0,   478,     0,   479,     0,     0,   480,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     163,     0,     0,   345,   346,    72,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   347,   348,     0,     0,
     665,     0,    73,    74,    75,    76,    77,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78,     0,    79,    80,    81,    82,
      83,    84,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    66,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,   477,
    -483,   478,     0,   479,     0,     0,   480,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   163,     0,
       0,   345,   346,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   347,   348,     0,     0,     0,     0,
      73,    74,    75,    76,    77,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,    79,    80,    81,    82,    83,    84,
       0,     0,     0,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    66,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,    68,    69,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    70,   477,     0,   478,
       0,   479,     0,     0,   480,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,   345,
     346,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   347,   348,     0,     0,     0,     0,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,     0,    79,    80,    81,    82,    83,    84,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,    66,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,    68,    69,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,     0,    72,
       0,     0,     9,     0,    10,    11,    12,    13,    14,    15,
      16,    17,     0,     0,     0,   107,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,     0,     0,   584,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
      79,    80,    81,    82,    83,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    66,     0,     0,     0,     0,
       0,     0,     0,     0,    67,   139,   140,    25,   111,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,   477,     0,   478,     0,   479,     0,     0,
     480,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   345,   346,    72,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   347,   348,
       0,     0,     0,     0,    73,    74,    75,    76,    77,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,    79,    80,
      81,    82,    83,    84,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,    66,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,     0,     0,     0,    68,    69,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      70,     0,     0,   342,     0,   343,     0,     0,   344,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   345,   346,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   347,   348,     0,     0,
       0,     0,    73,    74,    75,    76,    77,     0,     0,     0,
       0,     0,     0,     0,   349,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    78,     0,    79,    80,    81,    82,
      83,    84,     0,     0,     0,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    66,     0,     0,     0,     0,     0,     0,     0,     0,
      67,     0,     0,     0,     0,    68,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      66,     0,     0,    72,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,    68,    69,     0,     0,     0,     0,
      73,    74,    75,    76,    77,     0,     0,    70,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    78,     0,    79,    80,    81,    82,    83,    84,
       0,     0,    72,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,    73,
      74,    75,    76,    77,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     0,    79,    80,    81,    82,    83,    84,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    66,     0,
       0,     0,     0,     0,     0,     0,     0,    67,     0,     0,
       0,     0,    68,    69,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    70,     0,     0,     0,     0,
       0,     0,     0,   193,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    66,     0,     0,
       0,     0,     0,     0,     0,     0,    67,     0,     0,     0,
       0,    68,    69,     0,     0,     0,     0,    73,    74,    75,
      76,    77,     0,     0,    70,     0,     0,     0,     0,     0,
       0,     0,   419,     0,     0,     0,     0,     0,     0,    78,
       0,    79,    80,    81,    82,    83,    84,     0,     0,     0,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,    73,    74,    75,    76,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    78,     0,
      79,    80,    81,    82,    83,    84,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,    66,     0,     0,     0,     0,
       0,     0,     0,     0,    67,     0,     0,     0,     0,    68,
      69,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,     0,     0,     0,     0,     0,     0,     0,
     452,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,     0,     0,     0,
       0,     0,     0,     0,     0,    67,     0,     0,     0,     0,
      68,    69,     0,     0,    73,    74,    75,    76,    77,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,    79,    80,
      81,    82,    83,    84,     0,     0,     0,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   573,     0,    73,    74,    75,    76,    77,
      66,     0,     0,     0,     0,     0,     0,     0,     0,    67,
       0,     0,     0,     0,    68,    69,     0,    78,     0,    79,
      80,    81,    82,    83,    84,     0,     0,    70,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,     0,     0,     0,     0,     0,    66,
       0,     0,     0,     0,     0,     0,     0,     0,    67,     0,
       0,     0,     0,    68,    69,     0,     0,   649,     0,    73,
      74,    75,    76,    77,     0,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,     0,    79,    80,    81,    82,    83,    84,     0,
       0,     0,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,    73,    74,
      75,    76,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      78,     0,    79,    80,    81,    82,    83,    84,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,     1,     2,     3,
       4,     5,     6,     7,     8,     0,     0,     0,     0,     0,
     545,     0,    10,    11,    12,    13,    14,    15,    16,    17,
       0,     0,     0,   107,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     0,     0,     0,     9,     0,    10,
      11,    12,    13,    14,    15,    16,    17,     0,     0,     0,
     107,     1,     2,     3,     4,     5,     6,     7,     8,     0,
       0,     0,     0,   549,   138,     0,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,     0,   107,     0,     0,
       0,     0,     0,   108,   109,   110,   386,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     0,
     108,   109,   110,   111,     9,     0,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     0,     0,   107,     1,     2,
       3,     4,     5,     6,     7,     8,     0,   139,   140,    25,
     111,     9,     0,    10,    11,    12,    13,    14,    15,    16,
      17,     0,     0,     0,   107,     1,     2,     3,     4,     5,
       6,     7,     8,     0,     0,     0,     0,     0,   385,     0,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,   107,     0,     0,     0,     0,     0,   108,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     0,   139,   140,    25,   111,   157,     0,
      10,    11,    12,    13,    14,    15,    16,    17,     0,     0,
       0,   107,     1,     2,     3,     4,     5,     6,     7,     8,
       0,   108,   109,   110,   386,   466,     0,    10,    11,    12,
      13,    14,    15,    16,    17,   570,     0,     0,   107,     0,
       0,     0,     0,     0,     0,     0,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,     0,   504,     0,     0,     0,   559,
       0,   108,   109,   110,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,   607,     0,     0,     0,     0,   441,   108,   109,
     110,   423,   424,   425,   426,   427,   428,   429,   430,   431,
     432,   433,   434,   435,   436,   437,   438,   439,   440,   704,
       0,     0,     0,     0,   559,     0,     0,     0,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   580,     0,     0,     0,
       0,   559,     0,   423,   424,   425,   426,   427,   428,   429,
     430,   431,   432,   433,   434,   435,   436,   437,   438,   439,
     440,   643,     0,     0,     0,     0,   441,     0,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,     0,     0,     0,     0,
       0,   559,   423,   424,   425,   426,   427,   428,   429,   430,
     431,   432,   433,   434,   435,   436,   437,   438,   439,   440,
       0,     0,     0,     0,     0,   441,   423,   424,   425,   426,
     427,   428,   429,   430,   431,   432,   433,   434,   435,   436,
     437,   438,   439,   440,     0,     0,     0,     0,     0,   559,
     423,   424,   425,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   435,   436,   437,   438,   439,   440,     0,     0,
       0,     0,     0,   441,   423,   424,   425,   426,   427,   428,
     429,   430,   431,   432,   433,   434,   435,   436,   437,   438,
     439,   440,     0,     0,     0,     0,     0,   559
};

static const short int yycheck[] =
{
      39,    29,     9,    26,    18,   133,    22,   137,    22,     9,
      71,    22,   396,   167,   552,   399,   344,    18,     0,   408,
     552,   585,   350,    23,    24,    25,   376,   588,   561,   590,
      32,   537,    39,    55,   402,   352,    18,    34,     0,    38,
      33,    33,     6,     7,     8,     4,     5,     6,    41,    31,
       9,    33,   552,    45,    41,    42,    55,    98,    99,   100,
     101,   102,   103,   104,    71,   454,   627,    37,    70,    34,
      37,    33,    42,   605,    41,    42,    34,   362,   363,     6,
     208,    39,     9,   472,    39,    40,    40,   455,   111,    43,
     654,   480,   481,    37,   422,     0,    40,   597,    17,    18,
      50,   418,   102,   142,   421,   605,   128,    97,   108,   109,
     110,   644,    37,   441,   442,    38,    37,    38,   468,    40,
     470,   685,     9,   629,    11,   129,   126,   124,   148,   149,
     150,   138,   193,    42,   640,   142,   136,   137,   138,   139,
     140,   679,    17,    18,    38,    38,   146,    40,   709,   682,
     157,   167,    43,   167,   687,   661,   167,   469,    42,   471,
      55,   200,   694,   552,    93,   166,    43,   705,    39,    40,
     559,   560,   186,   187,   174,   186,   187,   561,   711,   679,
      39,    40,    39,    40,   166,    36,   193,    37,   188,   506,
     190,    38,   509,   510,   694,    41,   115,   116,   117,   118,
     119,   120,   139,   140,    42,   705,    31,    98,    99,   100,
     101,   102,   103,   104,   344,    31,   605,   606,    31,    37,
     350,    98,    99,   100,   101,   102,   103,   104,    36,    31,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    42,
      44,   630,    38,   593,   594,     6,    38,    37,    37,   123,
     639,   579,   580,    38,   643,    41,    38,    37,    42,    46,
     644,    37,    34,    46,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    39,    85,    86,    87,
      88,    40,    38,    38,    46,    45,    37,    37,    46,   678,
     679,   445,   422,    38,    32,    38,    37,    46,   682,    39,
     617,   618,    39,   687,    39,   694,    40,    33,    41,    37,
      41,   441,   442,    40,   375,    39,   705,     4,     5,     6,
       7,     8,     9,    10,    11,    39,   387,   711,    39,    39,
      17,    39,    19,    20,    21,    22,    23,    24,    25,    26,
      39,    41,    40,    30,   344,    40,    39,   114,   387,   349,
     350,    40,    46,    38,    38,    33,   395,    37,   397,   513,
      41,    38,    38,   386,    39,    37,   366,    41,   375,    39,
      33,    40,    37,    40,     3,    39,    38,     6,   385,    40,
     387,    10,    40,    12,    13,    14,    15,    16,    17,    32,
      38,   452,    39,    33,    33,    39,    41,    39,   398,    40,
      33,    39,    89,    90,    91,    92,    93,   446,   447,    40,
      39,   411,    40,    39,   414,    39,    33,   335,   136,   419,
     630,   142,   422,    46,   181,   566,   168,    31,   624,   445,
     365,   445,   103,   187,   445,   473,    28,   590,   369,   705,
     596,   441,   442,   395,   568,   452,   399,    -1,    -1,   579,
     580,    -1,    -1,    -1,    -1,   469,    -1,   471,   469,   466,
     471,   461,    -1,   502,    -1,   465,    -1,     3,    -1,   480,
       6,    -1,    -1,   473,    10,    -1,    12,    13,    14,    15,
      16,    17,    -1,    -1,    -1,    -1,    -1,   615,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,   513,    -1,   513,
      -1,    -1,   513,   503,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,   516,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   563,    -1,    -1,   566,    -1,    -1,
      -1,    -1,   555,    -1,    -1,    -1,    -1,   565,   545,    -1,
      -1,    -1,    -1,   543,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    -1,    -1,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,   568,    -1,
      -1,    30,    -1,   612,    -1,    90,    91,    92,    -1,   579,
     580,    -1,    -1,   622,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   629,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   616,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    90,    91,    92,    40,   674,    -1,    -1,    -1,    -1,
     679,    -1,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,     0,    71,   705,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,    -1,   123,   124,    -1,
     126,   127,   128,   129,     0,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      -1,    87,    -1,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,     3,    -1,   124,    -1,
     126,   127,   128,   129,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    72,    73,    74,    75,    76,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    94,    -1,    96,
      97,    98,    99,   100,   101,    -1,    -1,    -1,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,   126,
      -1,   128,    -1,    89,    90,    91,    92,    93,    94,    95,
      -1,    97,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,   121,    -1,    -1,    30,    -1,
     126,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    -1,    30,    31,
      -1,    33,    -1,    35,    -1,    -1,    38,    -1,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    90,    91,
      92,    93,    94,    -1,    96,    97,    98,    99,   100,   101,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    -1,    33,
      34,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    96,    97,    98,    99,   100,   101,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    27,    -1,    -1,    30,    31,    -1,    33,    -1,    35,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    95,
      96,    97,    98,    99,   100,   101,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    30,    31,    -1,    33,    -1,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    95,    96,    97,
      98,    99,   100,   101,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    31,    -1,    33,    -1,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    96,    97,    98,    99,
     100,   101,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    33,    -1,    35,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    96,    97,    98,    99,   100,   101,
      -1,    -1,    -1,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    33,
      -1,    35,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    96,    97,    98,    99,   100,   101,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    -1,    55,
      -1,    -1,    17,    -1,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    72,    73,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      96,    97,    98,    99,   100,   101,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    90,    91,    92,    93,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    35,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    96,    97,
      98,    99,   100,   101,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    -1,    33,    -1,    35,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    -1,    96,    97,    98,    99,
     100,   101,    -1,    -1,    -1,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    96,    97,    98,    99,   100,   101,
      -1,    -1,    55,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,    72,
      73,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    96,    97,    98,    99,   100,   101,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    -1,    72,    73,    74,
      75,    76,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    96,    97,    98,    99,   100,   101,    -1,    -1,    -1,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,    72,    73,    74,    75,
      76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      96,    97,    98,    99,   100,   101,    -1,    -1,    -1,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    72,    73,    74,    75,    76,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,    96,    97,
      98,    99,   100,   101,    -1,    -1,    -1,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,    70,    -1,    72,    73,    74,    75,    76,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    94,    -1,    96,
      97,    98,    99,   100,   101,    -1,    -1,    30,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    -1,    -1,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    96,    97,    98,    99,   100,   101,    -1,
      -1,    -1,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,    72,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    96,    97,    98,    99,   100,   101,    -1,    -1,
      -1,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,
      17,    -1,    19,    20,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    30,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      30,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    70,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    90,    91,    92,    93,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      90,    91,    92,    93,    17,    -1,    19,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    -1,    30,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    90,    91,    92,
      93,    17,    -1,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    30,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,    -1,    -1,    -1,    -1,    -1,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,    90,    91,    92,    93,    17,    -1,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      -1,    30,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    90,    91,    92,    93,    17,    -1,    19,    20,    21,
      22,    23,    24,    25,    26,    37,    -1,    -1,    30,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    39,    -1,    -1,    -1,    71,
      -1,    90,    91,    92,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    39,    -1,    -1,    -1,    -1,    71,    90,    91,
      92,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    39,
      -1,    -1,    -1,    -1,    71,    -1,    -1,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    41,    -1,    -1,    -1,
      -1,    71,    -1,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    41,    -1,    -1,    -1,    -1,    71,    -1,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    71,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    -1,    71,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,    71,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    71,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    71
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      19,    20,    21,    22,    23,    24,    25,    26,    30,    36,
      37,    47,    89,    90,    91,    92,    93,    94,    95,    97,
     121,   126,   137,   138,   139,   140,   141,   159,   164,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   179,   182,
     183,   186,   187,   188,   189,   190,   191,   194,   196,   197,
     203,   208,   219,   220,     9,    11,     3,    12,    17,    18,
      30,    38,    55,    72,    73,    74,    75,    76,    94,    96,
      97,    98,    99,   100,   101,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   135,   216,   217,   218,   235,   245,    30,    90,    91,
      92,    93,   187,   194,    36,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    85,    86,    87,
      88,   142,   143,   144,   145,   147,   148,   149,    17,    90,
      91,   165,   166,   188,   189,   194,   203,   209,   210,   135,
     135,   135,   211,     3,     6,    10,    12,    17,   160,   161,
     167,    34,   220,    50,   253,   254,    30,    89,   186,     0,
     139,   135,   195,   215,   216,     4,     5,     6,     9,   175,
       6,   172,   178,    37,   129,   180,    38,    38,    42,    42,
     215,   216,    93,    38,   135,   128,   218,   135,   135,   135,
      40,   184,    27,    28,    29,   126,   128,   135,   150,   151,
      36,     0,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    87,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   124,   126,
     127,   128,   129,   136,   154,   155,   154,    34,   124,   146,
     135,   150,    33,    35,    38,    53,    54,    66,    67,    84,
     134,   135,   156,   135,   135,   211,   135,   211,    37,   171,
     135,    41,   213,   213,   213,   213,   216,    31,    37,    42,
      31,   165,   180,    44,   214,    38,   135,     6,   176,     6,
       9,   177,   175,    38,    37,    17,    93,   166,   192,   193,
     194,   192,   135,   204,   205,    98,    99,   100,   101,   102,
     103,   104,   226,   227,   228,   241,   242,   248,   249,   250,
     135,   215,   185,   195,   216,   123,   154,   136,   156,    38,
     135,   156,    38,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    71,   133,    37,    41,    42,   199,   199,    37,   198,
     199,   198,    38,   135,    46,   226,    38,    37,    37,    33,
      45,   215,   214,    34,   181,   216,    17,   215,    39,    40,
      39,    40,    46,    40,    43,   195,   231,    31,    33,    35,
      38,   134,   195,   206,   207,   223,   243,   244,   245,   253,
     195,   135,   251,   252,    18,   244,   245,    43,   227,   206,
      39,   135,    40,    38,    39,   135,   156,   157,   158,   156,
     156,    38,   165,   200,   195,   195,   215,    27,    28,    29,
      34,   162,   163,   206,    43,     3,     6,    10,    12,    13,
      14,    15,    16,    17,    39,   221,   222,   224,   225,    45,
     135,    34,    39,   216,   214,    17,    70,   193,   214,    70,
     206,   205,    46,    37,    30,    93,   166,   206,   206,    71,
     133,    46,    37,    38,    32,    46,    38,    37,    40,    37,
      37,    39,   195,    70,   135,   152,   153,    39,    39,    40,
      41,    33,    41,   212,    43,   165,   135,    37,    41,    39,
      40,   223,    39,    39,    39,    27,    95,    96,   114,   206,
     230,   232,   233,   234,   235,   254,    39,    39,   206,   206,
     243,   195,   253,   185,   252,    39,    40,   156,   156,    40,
      33,    41,    40,   201,   212,    39,   224,    41,   222,   224,
      46,   214,   214,   114,   232,    17,    18,   235,   238,    38,
      38,   230,   206,    41,    40,   246,   195,    39,   154,    70,
     135,    33,    41,    38,   195,   202,    37,   201,   224,   253,
     162,    38,   206,   223,   206,    70,   243,   247,    39,    37,
      39,    41,    33,   212,    40,    37,    70,   223,    40,    40,
     236,    39,    40,    38,    40,   195,    32,    38,   206,   195,
     229,   230,   231,   237,   254,    39,   243,    33,    33,   212,
      39,   239,   240,   243,    39,    40,   230,    40,    39,    41,
      39,    40,   229,    33,   224,    39,   243,    39
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     134,   134,   134,   134,   135,   135,   135,   135,   135,   135,
     135,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   143,   143,   144,   144,   145,   145,   145,   146,
     146,   147,   147,   148,   148,   148,   149,   149,   150,   150,
     150,   150,   150,   150,   151,   151,   152,   152,   152,   152,
     153,   153,   154,   154,   155,   155,   156,   156,   156,   156,
     156,   156,   156,   156,   156,   156,   157,   157,   158,   158,
     159,   160,   161,   161,   161,   161,   162,   162,   162,   163,
     163,   163,   163,   164,   164,   164,   165,   165,   165,   165,
     165,   165,   166,   166,   167,   167,   168,   168,   168,   169,
     169,   169,   169,   170,   170,   170,   171,   171,   171,   171,
     171,   171,   171,   171,   172,   172,   173,   173,   173,   174,
     174,   174,   174,   175,   175,   175,   175,   175,   176,   176,
     177,   177,   177,   178,   178,   178,   179,   179,   180,   180,
     181,   181,   182,   183,   184,   184,   185,   185,   186,   186,
     187,   187,   188,   188,   189,   189,   190,   190,   190,   190,
     191,   191,   192,   192,   192,   192,   193,   193,   193,   193,
     194,   194,   194,   194,   195,   195,   196,   197,   198,   198,
     199,   200,   200,   201,   201,   202,   202,   203,   204,   204,
     205,   205,   206,   206,   206,   206,   206,   206,   207,   207,
     207,   207,   208,   209,   210,   211,   211,   212,   212,   212,
     212,   213,   213,   214,   214,   214,   215,   215,   216,   216,
     217,   217,   218,   218,   219,   219,   220,   220,   220,   221,
     221,   222,   222,   223,   224,   225,   225,   225,   225,   225,
     225,   225,   225,   225,   226,   226,   227,   227,   227,   227,
     227,   228,   228,   229,   229,   229,   230,   230,   230,   230,
     230,   230,   231,   231,   232,   233,   234,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   236,   236,   237,
     237,   238,   238,   239,   239,   240,   240,   241,   242,   243,
     243,   243,   244,   244,   245,   245,   245,   245,   245,   245,
     245,   245,   246,   246,   247,   247,   248,   249,   249,   250,
     251,   251,   252,   253,   253,   254
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     3,     2,     2,     1,     2,     2,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     2,     0,     1,     1,     3,
       1,     3,     0,     1,     1,     2,     3,     2,     3,     5,
       2,     4,     1,     1,     1,     4,     0,     1,     1,     3,
       6,     1,     1,     1,     1,     1,     0,     1,     1,     1,
       1,     1,     1,     3,     4,     4,     1,     1,     2,     4,
       4,     2,     2,     1,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     2,     0,     1,     2,     1,     2,     0,     1,
       0,     1,     1,     0,     1,     2,     3,     4,     0,     4,
       1,     2,     2,     3,     0,     2,     1,     3,     1,     2,
       1,     1,     5,     7,     5,     7,     6,     7,     6,     5,
       1,     2,     0,     1,     1,     3,     1,     2,     3,     2,
       1,     2,     4,     3,     3,     2,     4,     4,     1,     1,
       3,     4,     5,     0,     2,     2,     4,     4,     1,     3,
       1,     3,     1,     4,     3,     3,     2,     5,     1,     1,
       1,     1,     2,     2,     2,     0,     1,     0,     2,     7,
       9,     0,     7,     0,     2,     3,     0,     1,     1,     2,
       1,     2,     1,     2,     4,     5,     7,     8,    13,     1,
       3,     2,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       1,     3,     6,     1,     2,     1,     1,     1,     2,     1,
       1,     1,     3,     4,     6,     8,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     2,     1,
       3,     1,     1,     0,     1,     1,     3,     3,     3,     1,
       1,     3,     5,     6,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     1,     3,     3,     1,     1,     3,
       1,     3,     4,     0,     1,     1
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned short int yyconflp[] =
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
       0,     0,     0,     0,     0,     0,     5,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   259,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     7,     0,     0,     9,    11,    13,
      15,    17,    19,    21,    23,    25,    27,    29,    31,    33,
      35,    37,    39,    41,    43,    45,    47,    49,    51,    53,
      55,    57,    59,    61,    63,    65,    67,    69,    71,    73,
      75,    77,    79,    81,    83,    85,    87,    89,    91,    93,
      95,    97,    99,   101,   103,   105,   107,   109,   111,   113,
     115,   117,   119,   121,   123,   125,   127,   129,   131,   133,
     135,   137,   139,   141,   143,   145,   147,   149,   151,   153,
     155,   157,   159,   161,   163,   165,   167,   169,   171,   173,
       0,   175,     0,   177,   179,   181,   183,   185,   187,   189,
     191,   193,   195,   197,   199,   201,   203,   205,   207,   209,
     211,   213,   215,   217,   219,   221,   223,   225,   227,   229,
     231,   233,   235,   237,   239,   241,     0,   243,   245,     0,
     247,   249,   251,   253,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   255,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   261,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   263
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   272,     0,   272,     0,   340,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   470,     0,   470,     0,   470,
       0,   470,     0,   470,     0,   272,     0,   272,     0,   272,
       0,   229,     0,   367,     0
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
        case 171:
#line 391 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		psi_cpp_exp_exec((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 2509 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 172:
#line 397 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if (P->file.ln) {
		P->error(PSI_DATA(P), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), PSI_WARNING,
				"Extra 'lib \"%s\"' statement has no effect", (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	} else {
		P->file.ln = strndup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->size);
	}
}
#line 2522 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 173:
#line 405 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_const(P, (*(struct psi_const **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2530 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 174:
#line 408 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_decl(P, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2538 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 176:
#line 412 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_typedef(P, (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2546 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 177:
#line 415 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_struct(P, (*(struct psi_decl_struct **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2554 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 178:
#line 418 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_union(P, (*(struct psi_decl_union **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2562 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 179:
#line 421 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2570 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 180:
#line 424 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_impl(P, (*(struct psi_impl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2578 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 181:
#line 430 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2586 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 182:
#line 436 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 2594 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 183:
#line 439 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = (*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2602 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 184:
#line 445 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 2630 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 185:
#line 468 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2639 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 186:
#line 472 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2648 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 187:
#line 476 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2658 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 188:
#line 481 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_cpp_macro_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2667 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 189:
#line 485 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2676 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 190:
#line 489 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2685 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 191:
#line 493 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 2694 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 214:
#line 546 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 2704 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 215:
#line 551 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2714 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 216:
#line 559 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL);
}
#line 2722 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 217:
#line 562 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL); /* FIXME */
}
#line 2730 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 219:
#line 566 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 2738 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 220:
#line 572 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2748 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 221:
#line 577 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2758 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 222:
#line 585 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2766 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 224:
#line 592 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2775 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 225:
#line 596 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2784 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 226:
#line 603 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 2793 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 227:
#line 607 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2802 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 228:
#line 611 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 2811 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 229:
#line 615 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 2820 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 230:
#line 620 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 2835 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 231:
#line 630 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 2850 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 232:
#line 640 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2860 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 233:
#line 645 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2870 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 234:
#line 650 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2881 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 235:
#line 656 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 2892 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 236:
#line 665 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 2900 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 238:
#line 672 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free), 
		&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2909 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 239:
#line 676 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2917 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 240:
#line 682 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init((*(struct psi_const_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 2926 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 241:
#line 689 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_const_type **)(&(*yyvalp))) = psi_const_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
}
#line 2934 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 246:
#line 702 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = NULL;
}
#line 2942 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 247:
#line 705 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if (psi_num_exp_validate(PSI_DATA(P), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL, NULL, NULL, NULL, NULL)) {
		impl_val res = {0};
		token_t type = psi_num_exp_exec((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), &res, NULL, &P->preproc->defs);
		
		if (type == PSI_T_FLOAT || type == PSI_T_DOUBLE) {
			(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init(type, NULL);
		} else {
			(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init(PSI_T_INT, NULL);
		}
		
		switch (type) {
		case PSI_T_UINT8:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.u8;	break;
		case PSI_T_UINT16:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.u16;	break;
		case PSI_T_UINT32:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.u32;	break;
		case PSI_T_UINT64:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.u64;	break; /* FIXME */
		case PSI_T_INT8:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.i8;	break;
		case PSI_T_INT16:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.i16;	break;
		case PSI_T_INT32:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.i32;	break;
		case PSI_T_INT64:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.zend.lval = res.i64;	break;
		case PSI_T_FLOAT:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.dval = res.fval;		break;
		case PSI_T_DOUBLE:	(*(struct psi_impl_def_val **)(&(*yyvalp)))->ival.dval = res.dval;		break;
		default:
			assert(0);
		
		}
	} else {
		(*(struct psi_impl_def_val **)(&(*yyvalp))) = NULL;
	}
	psi_num_exp_free(&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2978 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 248:
#line 736 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 2987 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 253:
#line 750 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 2995 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 254:
#line 753 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_VOID, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3009 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 255:
#line 762 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 3017 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 257:
#line 769 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3030 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 258:
#line 777 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_ENUM, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->name),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.enm = (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3046 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 259:
#line 788 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 3060 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 260:
#line 797 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 3074 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 261:
#line 806 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3084 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 262:
#line 814 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3092 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 264:
#line 821 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3101 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 266:
#line 829 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3111 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 267:
#line 834 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3121 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 268:
#line 839 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3131 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 271:
#line 849 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3139 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 272:
#line 852 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3147 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 273:
#line 858 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3155 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 274:
#line 861 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3163 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 275:
#line 864 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3171 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 286:
#line 886 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3179 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 287:
#line 889 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3187 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 288:
#line 892 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3195 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 289:
#line 898 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3203 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 290:
#line 901 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3211 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 291:
#line 904 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3224 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 292:
#line 912 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
}
#line 3238 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 293:
#line 924 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3246 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 294:
#line 927 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3254 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 295:
#line 930 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3266 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 296:
#line 937 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3274 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 297:
#line 940 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3286 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 298:
#line 950 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3294 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 300:
#line 956 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3302 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 303:
#line 964 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3310 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 304:
#line 967 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3318 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 305:
#line 970 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3331 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 306:
#line 981 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 3339 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 307:
#line 984 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 3347 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 313:
#line 1004 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_decl_arg_free(&(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3355 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 315:
#line 1011 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3363 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 316:
#line 1017 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3371 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 317:
#line 1020 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3379 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 319:
#line 1027 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_decl **)(&(*yyvalp)))->abi = psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 3388 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 322:
#line 1039 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 3400 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 323:
#line 1046 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 3413 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 324:
#line 1057 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 3425 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 325:
#line 1064 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 3438 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 326:
#line 1075 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3450 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 327:
#line 1082 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3466 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 328:
#line 1093 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3482 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 329:
#line 1104 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3498 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 331:
#line 1119 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3512 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 332:
#line 1131 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3520 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 333:
#line 1134 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3528 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 334:
#line 1137 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3536 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 335:
#line 1140 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3544 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 336:
#line 1147 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3552 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 337:
#line 1150 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0)
	);
}
#line 3563 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 338:
#line 1156 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3577 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 339:
#line 1165 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text),
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3591 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 340:
#line 1177 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3604 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 341:
#line 1185 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3612 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 342:
#line 1188 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 3627 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 343:
#line 1198 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 3642 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 344:
#line 1211 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)) + !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3652 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 345:
#line 1216 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3662 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 346:
#line 1224 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_union **)(&(*yyvalp))) = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_union **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_union **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_union **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3674 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 347:
#line 1234 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_struct **)(&(*yyvalp))) = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_struct **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3686 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 348:
#line 1244 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3694 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 350:
#line 1251 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 3702 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 351:
#line 1257 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	if ((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		size_t i = 0;
		struct psi_decl_arg *arg;
		
		while (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), i++, &arg)) {
			arg->type = psi_decl_type_copy((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type);
			(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&(*yyvalp))), &arg);
		}
		free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3721 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 352:
#line 1271 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	if ((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		size_t i = 0;
		struct psi_decl_arg *arg;
		
		while (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), i++, &arg)) {
			arg->type = psi_decl_type_copy((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type);
			(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&(*yyvalp))), &arg);
		}
		free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 3740 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 353:
#line 1288 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 3748 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 354:
#line 1291 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 3756 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 355:
#line 1297 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 3768 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 356:
#line 1304 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 3780 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 357:
#line 1314 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_enum **)(&(*yyvalp))) = psi_decl_enum_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 3789 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 358:
#line 1321 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3797 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 359:
#line 1324 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3805 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 360:
#line 1330 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, NULL);
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3815 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 361:
#line 1335 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3825 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 362:
#line 1343 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 3834 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 363:
#line 1347 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_cast((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->token);
}
#line 3843 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 364:
#line 1351 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary(PSI_T_LPAREN, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 3852 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 365:
#line 1355 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3861 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 366:
#line 1359 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 3870 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 367:
#line 1363 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 3879 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 368:
#line 1370 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3888 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 369:
#line 1374 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3897 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 370:
#line 1378 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 3906 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 371:
#line 1382 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_NAME, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 3915 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 372:
#line 1389 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3930 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 373:
#line 1402 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3945 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 374:
#line 1415 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 3960 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 375:
#line 1428 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 3968 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 376:
#line 1431 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&(*yyvalp)))->type = PSI_T_NAME;
}
#line 3977 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 377:
#line 1438 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = NULL;
}
#line 3985 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 378:
#line 1441 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(0, 0, psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text), NULL));
}
#line 3993 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 379:
#line 1444 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text), NULL);
}
#line 4001 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 380:
#line 1447 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text), psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval))->text), NULL));
}
#line 4009 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 381:
#line 1453 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = 0;
	(*(struct psi_layout*)(&(*yyvalp))).len = 0;
}
#line 4018 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 382:
#line 1457 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text);
	(*(struct psi_layout*)(&(*yyvalp))).len = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 4027 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 383:
#line 1464 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 4035 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 384:
#line 1467 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 4043 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 385:
#line 1470 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 4051 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 386:
#line 1476 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 4059 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 387:
#line 1479 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4067 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 389:
#line 1486 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4075 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 390:
#line 1492 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 1;
}
#line 4083 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 391:
#line 1495 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)) + 1;
}
#line 4091 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 394:
#line 1512 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4099 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 395:
#line 1515 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 4108 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 396:
#line 1522 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, NULL, (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
}
#line 4118 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 397:
#line 1527 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval));
}
#line 4128 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 398:
#line 1532 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval));
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4140 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 399:
#line 1542 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4148 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 400:
#line 1545 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4156 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 401:
#line 1551 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
}
#line 4164 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 402:
#line 1554 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4172 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 403:
#line 1560 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_var **)(&(*yyvalp))) = psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4181 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 404:
#line 1567 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4190 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 414:
#line 1586 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4198 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 415:
#line 1589 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4206 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 416:
#line 1595 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_return_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4214 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 417:
#line 1598 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_let_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4222 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 418:
#line 1601 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_set_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4230 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 419:
#line 1604 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_assert_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4238 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 420:
#line 1607 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_free_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4246 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 421:
#line 1613 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init((*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4255 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 422:
#line 1617 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init(psi_let_exp_init_ex((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), PSI_LET_TMP, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->exp->is_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4265 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 424:
#line 1626 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = true;
}
#line 4274 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 425:
#line 1630 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = false;
}
#line 4283 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 426:
#line 1637 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 4291 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 427:
#line 1640 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4299 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 428:
#line 1643 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 4308 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 429:
#line 1647 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLBACK, (*(struct psi_let_callback **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4316 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 430:
#line 1650 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, (*(struct psi_let_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4324 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 431:
#line 1653 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4332 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 432:
#line 1659 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4341 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 433:
#line 1663 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = 1;
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 4351 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 434:
#line 1671 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_calloc **)(&(*yyvalp))) = psi_let_calloc_init((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 4360 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 435:
#line 1678 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)));
}
#line 4370 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 436:
#line 1686 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_func **)(&(*yyvalp))) = psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4380 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 447:
#line 1707 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4388 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 448:
#line 1710 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4396 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 449:
#line 1716 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4404 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 450:
#line 1719 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4412 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 453:
#line 1730 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4420 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 454:
#line 1733 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4428 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 455:
#line 1739 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4436 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 456:
#line 1742 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4444 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 457:
#line 1748 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_return_stmt **)(&(*yyvalp))) = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_return_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4453 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 458:
#line 1755 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_stmt **)(&(*yyvalp))) = psi_set_stmt_init((*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_set_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4462 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 459:
#line 1762 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4470 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 460:
#line 1765 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4478 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 461:
#line 1768 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = (*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_set_exp **)(&(*yyvalp)))->var = (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4487 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 462:
#line 1775 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4497 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 463:
#line 1780 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->recursive = 1;
}
#line 4507 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 472:
#line 1799 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4515 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 473:
#line 1802 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4523 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 474:
#line 1808 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4531 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 475:
#line 1811 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4539 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 476:
#line 1817 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_assert_stmt **)(&(*yyvalp))) = psi_assert_stmt_init((enum psi_assert_kind) (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_assert_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4548 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 479:
#line 1829 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_free_stmt **)(&(*yyvalp))) = psi_free_stmt_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4557 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 480:
#line 1836 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4565 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 481:
#line 1839 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4573 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 482:
#line 1845 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_free_exp **)(&(*yyvalp))) = psi_free_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4583 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 483:
#line 1853 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = false;
}
#line 4591 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 484:
#line 1856 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = true;
}
#line 4599 "src/parser_proc.c" /* glr.c:816  */
    break;


#line 4603 "src/parser_proc.c" /* glr.c:816  */
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
          case 133: /* binary_op_token  */
#line 258 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4654 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 134: /* unary_op_token  */
#line 258 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4660 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 135: /* name_token  */
#line 258 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4666 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 136: /* any_noeol_token  */
#line 258 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4672 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 140: /* lib  */
#line 252 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4678 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 141: /* cpp  */
#line 267 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 4684 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 142: /* cpp_exp  */
#line 267 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 4690 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 144: /* cpp_message_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4696 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 145: /* cpp_include_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4702 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 146: /* cpp_header_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4708 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 147: /* cpp_no_arg_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4714 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 148: /* cpp_name_arg_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4720 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 149: /* cpp_exp_arg_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4726 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 150: /* cpp_special_name_token  */
#line 255 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4732 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 151: /* cpp_macro_decl  */
#line 269 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_macro_decl_free(&(*(struct psi_cpp_macro_decl **)(&(*yyvaluep))));}
#line 4738 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 152: /* cpp_macro_sig  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4744 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 153: /* cpp_macro_sig_args  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4750 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 154: /* cpp_macro_decl_tokens  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4756 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 155: /* cpp_macro_decl_token_list  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4762 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 156: /* cpp_macro_exp  */
#line 273 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 4768 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 157: /* cpp_macro_call_args  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4774 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 158: /* cpp_macro_call_arg_list  */
#line 271 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4780 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 159: /* constant  */
#line 279 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_const_free(&(*(struct psi_const **)(&(*yyvaluep))));}
#line 4786 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 160: /* constant_type  */
#line 281 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_const_type_free(&(*(struct psi_const_type **)(&(*yyvaluep))));}
#line 4792 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 161: /* constant_type_token  */
#line 276 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4798 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 162: /* impl_def_val  */
#line 283 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_def_val_free(&(*(struct psi_impl_def_val **)(&(*yyvaluep))));}
#line 4804 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 163: /* impl_def_val_token  */
#line 276 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4810 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 164: /* decl_typedef  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4816 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 165: /* typedef  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4822 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 166: /* const_decl_type  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4828 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 167: /* decl_type  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4834 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 168: /* decl_type_complex  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 4840 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 169: /* decl_type_simple  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4846 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 170: /* decl_real_type  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4852 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 171: /* decl_stdint_type  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4858 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 172: /* int_signed  */
#line 264 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4864 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 173: /* int_width  */
#line 261 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4870 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 174: /* decl_int_type  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4876 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 175: /* int_signed_types  */
#line 261 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4882 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 176: /* signed_short_types  */
#line 264 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4888 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 177: /* signed_long_types  */
#line 264 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 4894 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 178: /* int_width_types  */
#line 261 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 4900 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 179: /* decl_stmt  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4906 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 185: /* decl_vars  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4912 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 186: /* decl  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4918 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 187: /* decl_body  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4924 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 188: /* decl_func_body  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4930 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 189: /* decl_functor_body  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 4936 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 190: /* decl_functor  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4942 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 191: /* decl_func  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4948 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 192: /* decl_args  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4954 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 193: /* decl_anon_arg  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4960 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 194: /* decl_arg  */
#line 296 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 4966 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 195: /* decl_var  */
#line 298 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_var_free(&(*(struct psi_decl_var **)(&(*yyvaluep))));}
#line 4972 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 196: /* decl_union  */
#line 302 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_union_free(&(*(struct psi_decl_union **)(&(*yyvaluep))));}
#line 4978 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 197: /* decl_struct  */
#line 300 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_struct_free(&(*(struct psi_decl_struct **)(&(*yyvaluep))));}
#line 4984 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 198: /* decl_struct_args  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4990 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 199: /* struct_args_block  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 4996 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 200: /* struct_args  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5002 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 201: /* struct_arg_var_list  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5008 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 202: /* decl_vars_with_layout  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5014 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 203: /* decl_enum  */
#line 304 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_free(&(*(struct psi_decl_enum **)(&(*yyvaluep))));}
#line 5020 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 204: /* decl_enum_items  */
#line 308 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5026 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 205: /* decl_enum_item  */
#line 306 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_item_free(&(*(struct psi_decl_enum_item **)(&(*yyvaluep))));}
#line 5032 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 206: /* num_exp  */
#line 359 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 5038 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 207: /* number  */
#line 361 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 5044 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 208: /* enum_name  */
#line 252 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5050 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 209: /* union_name  */
#line 252 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5056 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 210: /* struct_name  */
#line 252 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5062 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 211: /* optional_name  */
#line 252 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5068 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 212: /* decl_layout  */
#line 313 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_layout_free(&(*(struct psi_layout **)(&(*yyvaluep))));}
#line 5074 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 213: /* align_and_size  */
#line 311 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5080 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 214: /* array_size  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5086 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 215: /* indirection  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5092 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 216: /* pointers  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5098 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 217: /* asterisks  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5104 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 219: /* impl  */
#line 316 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_free(&(*(struct psi_impl **)(&(*yyvaluep))));}
#line 5110 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 220: /* impl_func  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_func_free(&(*(struct psi_impl_func **)(&(*yyvaluep))));}
#line 5116 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 221: /* impl_args  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5122 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 222: /* impl_arg  */
#line 320 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_arg_free(&(*(struct psi_impl_arg **)(&(*yyvaluep))));}
#line 5128 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 223: /* impl_var  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_var_free(&(*(struct psi_impl_var **)(&(*yyvaluep))));}
#line 5134 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 224: /* impl_type  */
#line 322 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 5140 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 225: /* impl_type_token  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5146 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 226: /* impl_stmts  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5152 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 227: /* impl_stmt  */
#line 352 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_stmt_free(&(*(struct psi_token ***)(&(*yyvaluep))));}
#line 5158 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 228: /* let_stmt  */
#line 327 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_stmt_free(&(*(struct psi_let_stmt **)(&(*yyvaluep))));}
#line 5164 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 229: /* let_exp  */
#line 329 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 5170 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 230: /* let_exp_byref  */
#line 329 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 5176 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 231: /* let_exp_assign  */
#line 329 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 5182 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 232: /* let_calloc  */
#line 331 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_calloc_free(&(*(struct psi_let_calloc **)(&(*yyvaluep))));}
#line 5188 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 233: /* let_callback  */
#line 333 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_callback_free(&(*(struct psi_let_callback **)(&(*yyvaluep))));}
#line 5194 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 234: /* let_func  */
#line 335 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_func_free(&(*(struct psi_let_func **)(&(*yyvaluep))));}
#line 5200 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 235: /* let_func_token  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5206 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 236: /* let_func_exps  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5212 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 237: /* let_exps  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5218 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 238: /* callback_rval  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5224 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 239: /* callback_arg_list  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5230 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 240: /* callback_args  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5236 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 241: /* return_stmt  */
#line 345 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_return_stmt_free(&(*(struct psi_return_stmt **)(&(*yyvaluep))));}
#line 5242 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 242: /* set_stmt  */
#line 337 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_stmt_free(&(*(struct psi_set_stmt **)(&(*yyvaluep))));}
#line 5248 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 243: /* set_exp  */
#line 339 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_exp_free(&(*(struct psi_set_exp **)(&(*yyvaluep))));}
#line 5254 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 244: /* set_func  */
#line 341 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_func_free(&(*(struct psi_set_func **)(&(*yyvaluep))));}
#line 5260 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 245: /* set_func_token  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5266 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 246: /* set_func_exps  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5272 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 247: /* set_exps  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5278 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 248: /* assert_stmt  */
#line 343 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_assert_stmt_free(&(*(struct psi_assert_stmt **)(&(*yyvaluep))));}
#line 5284 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 249: /* assert_stmt_token  */
#line 354 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 5290 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 250: /* free_stmt  */
#line 347 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_stmt_free(&(*(struct psi_free_stmt **)(&(*yyvaluep))));}
#line 5296 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 251: /* free_exps  */
#line 356 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 5302 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 252: /* free_exp  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_exp_free(&(*(struct psi_free_exp **)(&(*yyvaluep))));}
#line 5308 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 253: /* reference  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 5314 "src/parser_proc.c" /* glr.c:846  */
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
  (!!((Yystate) == (-565)))

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
  #line 98 "src/parser_proc_grammar.y" /* glr.c:2270  */
{
}

#line 6667 "src/parser_proc.c" /* glr.c:2270  */

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

#line 1865 "src/parser_proc_grammar.y" /* glr.c:2584  */


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

