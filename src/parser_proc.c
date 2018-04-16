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
static inline void psi_parser_proc_deanon_typedef(struct psi_decl_arg *def)
{
	switch (def->type->type) {
	case PSI_T_STRUCT:
		if (!psi_decl_type_is_anon(def->type->name, "struct")) {
			return;
		}
		break;
	case PSI_T_UNION:
		if (!psi_decl_type_is_anon(def->type->name, "union")) {
			return;
		}
		break;
	case PSI_T_ENUM:
		if (!psi_decl_type_is_anon(def->type->name, "enum")) {
			return;
		}
		break;
	default:
		return;
	}
	free(def->type->name);
	def->type->name = strdup(def->var->name);
}
static inline void psi_parser_proc_add_typedef(struct psi_parser *P, struct psi_decl_arg *def)
{
	assert(def);
	if (!P->types) {
		P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	//psi_parser_proc_deanon_typedef(def);
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
	
	if (psi_decl_is_blacklisted(decl->func->var->name)) {
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

#line 206 "src/parser_proc.c" /* glr.c:264  */

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
#define YYFINAL  160
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7599

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  140
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  141
/* YYNRULES -- Number of rules.  */
#define YYNRULES  626
/* YYNRULES -- Number of states.  */
#define YYNSTATES  925
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 13
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   394

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
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     434,   434,   434,   434,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   436,
     436,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   441,   442,   445,
     446,   449,   450,   451,   452,   458,   466,   469,   472,   475,
     481,   484,   487,   490,   493,   499,   505,   508,   514,   537,
     541,   545,   550,   554,   558,   562,   569,   570,   574,   575,
     579,   580,   581,   585,   586,   590,   591,   595,   596,   597,
     601,   602,   606,   611,   616,   621,   630,   633,   636,   637,
     643,   648,   656,   659,   663,   667,   674,   678,   682,   686,
     691,   702,   713,   718,   723,   727,   733,   743,   746,   750,
     754,   760,   767,   771,   775,   782,   783,   784,   788,   802,
     808,   811,   817,   820,   826,   827,   835,   846,   855,   867,
     868,   872,   882,   891,   903,   904,   907,   913,   914,   918,
     922,   926,   931,   936,   944,   945,   946,   949,   955,   958,
     961,   967,   968,   972,   975,   978,   984,   987,   990,   998,
    1010,  1013,  1016,  1019,  1026,  1029,  1039,  1042,  1045,  1048,
    1049,  1050,  1054,  1057,  1060,  1071,  1078,  1088,  1091,  1097,
    1100,  1107,  1137,  1140,  1146,  1149,  1155,  1158,  1161,  1164,
    1170,  1174,  1175,  1179,  1180,  1184,  1185,  1192,  1193,  1197,
    1204,  1215,  1222,  1230,  1258,  1265,  1276,  1322,  1363,  1378,
    1381,  1384,  1390,  1393,  1399,  1414,  1417,  1446,  1454,  1482,
    1487,  1495,  1505,  1515,  1518,  1522,  1528,  1542,  1559,  1562,
    1568,  1575,  1585,  1592,  1595,  1601,  1606,  1614,  1618,  1622,
    1626,  1630,  1634,  1641,  1645,  1649,  1653,  1657,  1661,  1667,
    1671,  1678,  1681,  1693,  1697,  1701,  1708,  1721,  1734,  1747,
    1750,  1757,  1758,  1762,  1765,  1768,  1771,  1777,  1781,  1788,
    1791,  1794,  1809,  1810,  1811,  1812,  1816,  1819,  1825,  1826,
    1832,  1835,  1841,  1842,  1846,  1847,  1857,  1860,  1867,  1872,
    1877,  1887,  1890,  1896,  1899,  1905,  1912,  1919,  1926,  1927,
    1931,  1932,  1933,  1934,  1938,  1939,  1940,  1941,  1942,  1946,
    1949,  1955,  1958,  1961,  1964,  1967,  1973,  1977,  1985,  1986,
    1990,  1997,  2000,  2003,  2006,  2010,  2013,  2019,  2023,  2031,
    2038,  2043,  2051,  2059,  2060,  2061,  2062,  2063,  2064,  2065,
    2066,  2067,  2068,  2072,  2075,  2081,  2084,  2090,  2091,  2095,
    2098,  2104,  2107,  2113,  2120,  2124,  2131,  2134,  2137,  2143,
    2150,  2153,  2156,  2163,  2168,  2176,  2177,  2178,  2179,  2180,
    2181,  2182,  2183,  2187,  2190,  2196,  2199,  2205,  2212,  2213,
    2217,  2224,  2227,  2233,  2241,  2244,  2250
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "BOOL", "CHAR", "SHORT",
  "INT", "SIGNED", "UNSIGNED", "LONG", "FLOAT", "DOUBLE", "STRING",
  "MIXED", "ARRAY", "OBJECT", "CALLABLE", "VOID", "ZVAL", "NULL", "TRUE",
  "FALSE", "NAME", "NSNAME", "DOLLAR_NAME", "NUMBER", "QUOTED_STRING",
  "QUOTED_CHAR", "SIZEOF", "VOLATILE", "\"end of line\"", "\";\"", "\"(\"",
  "\")\"", "\",\"", "\":\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"", "\"=\"",
  "\"#\"", "\"|\"", "\"^\"", "\"&\"", "\"<<\"", "\">>\"", "\"+\"", "\"-\"",
  "\"*\"", "\"/\"", "\"%\"", "\"<\"", "\">\"", "\">=\"", "\"<=\"",
  "\"||\"", "\"&&\"", "\"==\"", "\"!=\"", "\"~\"", "\"!\"", "\".\"",
  "\"\\\\\"", "\"...\"", "\"?\"", "PRAGMA", "PRAGMA_ONCE", "LINE", "ERROR",
  "WARNING", "IF", "IFDEF", "IFNDEF", "ELSE", "ELIF", "ENDIF", "DEFINE",
  "DEFINED", "UNDEF", "IMPORT", "INCLUDE", "INCLUDE_NEXT", "TYPEDEF",
  "STRUCT", "UNION", "ENUM", "CONST", "LIB", "STATIC", "CALLBACK",
  "FUNCTION", "LET", "SET", "TEMP", "FREE", "RETURN", "AS", "PRE_ASSERT",
  "POST_ASSERT", "BOOLVAL", "INTVAL", "STRVAL", "PATHVAL", "STRLEN",
  "FLOATVAL", "ARRVAL", "OBJVAL", "COUNT", "CALLOC", "TO_BOOL", "TO_INT",
  "TO_STRING", "TO_FLOAT", "TO_ARRAY", "TO_OBJECT", "COMMENT",
  "WHITESPACE", "NO_WHITESPACE", "CPP_HEADER", "CPP_ATTRIBUTE",
  "CPP_EXTENSION", "CPP_PASTE", "CPP_INLINE", "CPP_RESTRICT", "CPP_ASM",
  "BSLASH", "LONG_DOUBLE", "INT8", "UINT8", "INT16", "UINT16", "INT32",
  "UINT32", "INT64", "UINT64", "INT128", "UINT128", "BINARY", "UNARY",
  "$accept", "binary_op_token", "unary_op_token", "name_token",
  "any_noeol_token", "any_nobrace_token", "file", "blocks", "block", "lib",
  "cpp", "cpp_exp", "cpp_ignored_token", "cpp_message_token",
  "cpp_include_token", "cpp_header_token", "cpp_no_arg_token",
  "cpp_name_arg_token", "cpp_exp_arg_token", "cpp_macro_decl",
  "cpp_macro_sig", "cpp_macro_sig_args", "cpp_macro_decl_tokens",
  "cpp_macro_decl_token_list", "cpp_macro_exp", "cpp_macro_call_args",
  "cpp_macro_call_arg_list", "constant", "impl_def_val",
  "impl_def_val_token", "decl_typedef", "typedef", "typedef_anon",
  "typedef_decl", "typedef_anon_decl", "qualified_decl_type",
  "decl_type_qualifier_token", "decl_type", "decl_type_complex",
  "decl_type_simple", "decl_real_type", "int_signed", "int_width",
  "decl_int_type", "int_signed_types", "signed_short_types",
  "signed_long_types", "int_width_types", "decl_stmt", "decl_asm",
  "quoted_strings", "decl_extvar_stmt", "decl_extvar_list", "decl_vars",
  "ignored_decl", "ignored_decl_body", "ignored_decl_body_stmts",
  "ignored_decl_body_stmt", "decl", "decl_body", "decl_func_body",
  "decl_functor_body", "decl_anon_functor_body", "decl_functor",
  "decl_anon_functor", "decl_func", "decl_args", "decl_arg_list",
  "decl_anon_arg", "decl_arg", "decl_var", "decl_union", "decl_struct",
  "decl_struct_args", "struct_args_block", "struct_args",
  "struct_arg_var_list", "decl_vars_with_layout", "decl_enum",
  "decl_enum_items", "decl_enum_item", "num_exp", "number", "sizeof",
  "sizeof_body", "sizeof_body_notypes", "enum_name", "union_name",
  "struct_name", "optional_name", "optional_comma", "decl_layout",
  "align_and_size", "array_size", "array_qualifier_token", "indirection",
  "pointers", "asterisks", "asterisk", "pointer_qualifier_token", "impl",
  "impl_func", "impl_args", "impl_arg", "impl_var", "impl_type",
  "impl_type_restricted", "impl_type_token", "impl_type_restricted_token",
  "impl_type_extended_token", "impl_stmts", "impl_stmt", "let_stmt",
  "let_exp", "let_exp_byref", "let_exp_assign", "let_calloc",
  "let_callback", "let_func", "let_func_token", "let_func_exps",
  "let_exps", "callback_rval", "callback_arg_list", "callback_args",
  "return_stmt", "return_exp", "call_decl_vars", "set_stmt", "set_exp",
  "set_func", "set_func_token", "set_func_exps", "set_exps", "assert_stmt",
  "assert_stmt_token", "free_stmt", "free_exps", "free_exp", "reference",
  "byref", YY_NULLPTR
};
#endif

#define YYPACT_NINF -714
#define YYTABLE_NINF -625

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short int yypact[] =
{
     521,  -714,  -714,  -714,  -714,  -714,    97,  -714,  -714,  -714,
     708,  -714,  -714,  -714,   730,  1396,  7333,  7333,  7333,   101,
      34,   243,    28,  -714,  5528,  1654,    89,   521,  -714,  -714,
    -714,  -714,  -714,  6704,   562,  -714,  -714,  -714,  -714,   126,
     177,  -714,  -714,  -714,  -714,   -45,  -714,  -714,   143,    78,
     102,  -714,  -714,  -714,  -714,    59,  -714,   104,  -714,  -714,
    -714,  7333,  7333,  7333,  -714,  1654,  -714,    95,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
     871,  -714,  -714,  -714,  -714,   123,   997,   997,    23,  -714,
     997,  6478,  7333,  7333,  1767,   113,  -714,  -714,  -714,   124,
    7333,   125,   125,  -714,  -714,  -714,  5461,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,   115,  -714,  -714,
     115,   122,  -714,  -714,  -714,  -714,  -714,   139,  -714,   145,
    1654,   134,   169,  -714,   190,  -714,  1880,  1396,   -45,   134,
    -714,  -714,    38,   188,  -714,  -714,   197,  7333,     2,  -714,
    -714,  -714,   216,  -714,   114,  -714,  -714,  -714,   132,  -714,
     202,   206,  1993,  1993,  7333,   248,  -714,  -714,  -714,   134,
    6817,   209,  -714,  1506,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  1619,  -714,  -714,  -714,  -714,  1732,  1845,  -714,
    -714,  -714,  1958,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  2071,  2184,  2297,  2410,  2523,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  2636,  -714,  2749,  2862,  2975,
    3088,  3201,  3314,  -714,  3427,  -714,  -714,  3540,  3653,  3766,
    3879,  3992,  4105,  4218,  4331,  4444,  4557,  4670,  4783,  4896,
    5009,  5122,  5235,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    5348,   997,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
     997,  -714,  -714,  -714,  -714,  -714,  -714,  -714,    70,  6478,
    -714,  -714,  -714,  -714,  6930,  6478,   212,  7462,  -714,   144,
    -714,   153,  -714,  -714,  -714,  -714,   210,   220,   220,    47,
      47,   217,  -714,   134,  1249,  -714,   248,   214,   228,   231,
    -714,  -714,  -714,  -714,  1363,  -714,   219,   188,  -714,  -714,
    -714,  -714,  -714,   260,  -714,  -714,   244,  -714,    82,  6704,
    -714,   237,   166,   239,  -714,  -714,   176,   234,   252,  -714,
    6817,  6139,  6817,  7333,  6817,  -714,  -714,   224,  -714,  -714,
    -714,  -714,  -714,  6365,  -714,  -714,   254,  -714,  7333,  -714,
    -714,   259,  7462,   245,  -714,  -714,  -714,  -714,  6624,   270,
    -714,  6692,  7333,  -714,  -714,  6478,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  6478,  6478,   262,  1484,  6817,  6817,
    -714,  -714,  -714,  -714,  5687,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,  -714,  -714,  1123,  -714,   328,   478,  -714,  -714,
    -714,  -714,  -714,  -714,  -714,  5574,  -714,  -714,  6365,  -714,
    7438,  -714,  -714,   256,  7333,  -714,  -714,  -714,    33,   264,
    1993,   188,   233,  1654,   188,   235,  6365,  7333,   261,   263,
     271,  7486,   265,   275,  -714,   289,   300,   286,   303,   118,
    -714,   306,   301,  -714,  -714,  -714,   799,  6817,  6989,  -714,
     219,   315,  -714,  -714,  -714,   316,  7462,   317,   305,  7207,
    -714,   326,  1767,   319,  -714,  -714,  6591,   742,  7333,   125,
     125,  -714,  -714,   163,  -714,  -714,   321,  -714,   245,  7486,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,   320,   178,
    -714,    28,  -714,  -714,  -714,    25,    32,    35,  6798,  -714,
    -714,  6365,  6365,  -714,   184,  -714,   219,   187,  -714,   323,
    -714,  -714,   324,  7486,  -714,  -714,  5800,  -714,  6139,  -714,
    6817,  -714,    28,  6817,  -714,  7333,  7102,  -714,  -714,  -714,
    -714,  -714,   329,   330,  -714,  -714,  -714,  -714,  6478,  6478,
     333,  -714,    63,   334,  -714,   319,   220,   220,  -714,   584,
     335,   584,   332,  6365,  -714,  7414,  -714,  1993,  -714,  7215,
     188,   299,   188,   188,   170,   267,   207,   337,  7486,  -714,
    -714,  -714,  -714,   341,  6252,  -714,   340,  6817,   198,  -714,
     344,   254,   346,   997,  7274,  7462,  7510,   356,   347,   353,
    6817,   355,   334,  6817,  6817,  -714,   584,  -714,    28,  5687,
    -714,  6365,   354,  -714,  -714,   359,  -714,  -714,   337,  -714,
    -714,  -714,  7102,  -714,   363,  6365,    28,  -714,  5913,   365,
     357,  -714,   304,  -714,  -714,  -714,   371,   370,   381,   319,
     375,  -714,   379,  -714,    39,  -714,  7534,   378,   188,   380,
      28,  7083,   382,   385,  -714,   394,  -714,  -714,    53,  -714,
     383,   395,  -714,  6817,  -714,   390,   387,  -714,   338,   398,
    6365,  5800,   403,  -714,  6139,  -714,  -714,   405,   413,   415,
     319,   408,  1993,   175,  6026,  6921,   263,  -714,  -714,  -714,
     409,  6252,  -714,  -714,   410,   412,  -714,   407,   417,   420,
     422,   419,  -714,  -714,  5800,  -714,   434,  -714,   584,   188,
      28,   433,  6139,  -714,   437,  -714,  -714,   441,  -714,  -714,
    -714,  6026,   443,   445,  -714
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short int yydefact[] =
{
     277,   396,   393,   397,   391,   392,   394,   388,   389,   387,
     386,   378,   282,   281,     0,     0,     0,     0,   499,   377,
       0,     0,   624,   283,     0,     0,     0,   278,   279,   285,
     284,   286,   290,   516,     0,   374,   380,   379,   385,   400,
     412,   384,   287,   288,   289,   417,   435,   437,   438,     0,
       0,   448,   292,   291,   293,     0,   294,     0,   395,   390,
     386,     0,     0,     0,   377,     0,   436,   422,   296,   307,
     304,   306,   308,   309,   320,   317,   318,   315,   321,   316,
       0,   319,   310,   311,   312,     0,   332,   332,     0,   300,
       0,     0,   499,   499,     0,     0,   360,   365,   457,   364,
       0,   507,   507,    33,    34,   612,   573,    24,    39,    38,
      37,    35,    36,    32,    31,    25,    29,    28,    26,    27,
      40,   581,   580,   578,   576,   577,   579,   575,   574,   582,
      30,   610,   608,   607,   609,   606,   605,   381,    41,    42,
     382,   383,   496,   540,   541,   542,   543,     0,   537,     0,
       0,     0,     0,   626,     0,   625,   386,     0,   417,     0,
       1,   280,   522,   509,   376,   458,     0,   517,   518,   520,
     375,   402,   406,   404,   408,   401,   398,   413,   400,   399,
       0,     0,   449,   449,     0,     0,   381,   382,   383,     0,
       0,     0,    68,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   158,   159,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   108,   106,   107,   105,   103,   104,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   160,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   156,   153,   154,   155,   157,
       0,   332,   302,   297,    43,    52,    57,    58,    62,   106,
     107,   105,   103,   104,   124,   126,   127,   128,   129,   130,
     131,   160,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   334,   305,
     333,   298,   313,   314,   299,   301,   342,   343,     0,     0,
      22,    23,    20,    21,     0,     0,   345,   303,   344,   381,
     498,   382,   497,   361,   358,   366,     0,     0,     0,     0,
       0,     0,   295,     0,     0,   426,     0,     0,     0,     0,
     428,   525,   524,   523,   512,   460,   516,   509,   519,   521,
     407,   403,   409,   410,   405,   414,     0,   415,   387,   516,
     454,     0,     0,   451,   452,   455,     0,   475,   501,   473,
       0,   624,     0,     0,     0,   618,   619,     0,   549,   552,
     551,   553,   554,     0,   555,   429,   423,   424,     0,   421,
     419,     0,   324,   325,   322,   335,   495,   494,     0,     0,
     490,     0,     0,   340,   337,   347,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    13,    12,    14,    15,
      16,    17,    18,    19,     0,     0,     0,     0,     0,     0,
     463,   462,   464,   461,     0,   427,   186,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   274,   275,   187,   188,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,   200,   201,   202,
     203,   204,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   224,   222,   223,   221,
     219,   220,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   276,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   272,   269,   270,
     271,   273,   433,   434,     0,   431,     0,     0,   359,   416,
     486,   484,   483,   485,   514,     0,   515,   513,     0,   487,
       0,   477,   488,     0,     0,   517,   459,   411,     0,   456,
     449,   509,     0,     0,   509,     0,     0,   502,     0,     0,
       0,   601,     0,     0,   600,    42,     0,     0,     0,     0,
     621,     0,     0,   595,   526,   550,     0,     0,   326,   420,
     516,     0,   491,   493,   336,     0,   349,     0,   348,     0,
     338,     0,     0,   503,   369,   362,   370,     0,   371,   507,
     507,   368,   367,   486,   356,   357,     0,   352,   354,   353,
     430,   432,   527,   545,   546,   547,   548,   544,     0,     0,
     531,   624,   536,   538,   539,   612,    24,     0,     0,   481,
     511,     0,     0,   510,     0,   418,   516,     0,   441,     0,
     453,   439,     0,   476,   474,   472,     0,   556,   624,   599,
       0,   535,   624,     0,   620,     0,   596,   593,   617,   425,
     327,   330,     0,   328,   492,   489,   341,   346,     0,     0,
       0,   363,     0,   468,   465,   503,     0,     0,   351,     0,
       0,     0,   533,     0,   479,     0,   480,   449,   446,     0,
     509,     0,   509,   509,   486,     0,    31,    30,   562,   567,
     563,   565,   566,    41,     0,   602,   613,     0,     0,   622,
     612,   598,     0,   332,     0,   350,   339,     0,   504,     0,
       0,     0,   468,   373,   372,   528,     0,   532,   624,     0,
     478,     0,     0,   447,   444,     0,   442,   440,     0,   564,
     587,   573,   596,   588,     0,     0,   624,   568,   624,     0,
       0,   623,     0,   323,   329,   331,     0,     0,     0,   503,
     469,   466,     0,   529,     0,   534,   482,     0,   509,     0,
     624,     0,   583,     0,   615,   614,   603,   557,     0,   508,
       0,     0,   470,     0,   467,     0,     0,   445,     0,     0,
       0,     0,     0,   604,   624,   611,   594,     0,     0,     0,
     503,     0,   449,     0,   589,     0,   487,   585,   560,   558,
     584,     0,   572,   616,     0,     0,   471,     0,     0,     0,
       0,   590,   591,   569,     0,   559,     0,   505,     0,   509,
     624,     0,   624,   586,     0,   530,   443,     0,   570,   592,
     506,   589,     0,     0,   571
};

  /* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -714,  -333,   -75,    -6,   -50,  -714,  -714,  -714,   452,  -714,
    -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,  -714,
    -714,  -714,   -84,  -714,  -284,  -714,  -714,  -714,  -329,  -714,
    -714,   325,  -194,    30,  -187,  -176,   -19,   -14,  -714,  -714,
    -714,   449,  -714,  -714,   322,  -714,  -714,  -714,  -714,   339,
    -263,  -714,  -714,  -173,  -714,  -120,  -714,  -106,   475,    80,
      -2,    52,  -714,  -714,  -714,  -714,  -179,  -714,  -131,   -10,
     -31,  -714,  -714,   127,  -349,  -714,  -299,  -714,     9,  -714,
    -133,  -351,  -714,   -72,  -714,    57,  -714,  -454,  -444,   150,
    -714,  -711,   -87,  -376,  -714,  -371,   -25,  -714,   342,  -714,
    -714,   485,  -714,  -253,  -669,  -713,  -714,  -714,   493,  -714,
     128,  -392,  -714,  -391,  -684,    96,  -258,  -714,  -714,  -685,
    -714,  -714,  -365,  -400,  -714,  -714,  -714,  -300,  -714,  -403,
    -402,  -397,  -714,  -714,  -714,  -714,  -714,  -714,  -212,   -21,
    -689
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short int yydefgoto[] =
{
      -1,   712,   618,   163,   348,   602,    26,    27,    28,    29,
      30,    85,    86,    87,    88,   354,    89,    90,    91,   312,
     742,   743,   349,   350,   367,   667,   668,    31,   686,   687,
      32,    95,   673,   674,   675,    33,    34,    35,    36,    37,
      38,    39,    40,    41,   176,   401,   404,   179,    42,   181,
     688,    43,   191,   791,    44,   603,   604,   605,    45,    46,
      47,    98,   410,    49,   411,    50,   412,   413,   414,    51,
     619,    52,    53,   481,   482,   677,   801,   840,   100,   418,
     419,   641,   621,   622,   661,   450,    55,   101,   102,   142,
     638,   753,   377,   395,   623,   166,   438,   168,   169,   393,
      56,    57,   699,   700,   642,   701,   147,   702,   703,   704,
     427,   428,   429,   887,   888,   889,   780,   781,   782,   138,
     872,   890,   824,   900,   901,   430,   652,   792,   431,   902,
     644,   139,   829,   855,   432,   433,   434,   649,   650,   646,
     155
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short int yytable[] =
{
      67,   154,   165,   351,   416,    99,   409,   409,   167,    54,
     137,   140,   141,    97,   164,   378,   365,   436,   643,   368,
     170,   626,   653,   679,   645,   624,   442,   645,   478,   479,
     311,   385,   762,   680,   475,   655,    54,   784,   629,   390,
     355,   783,   779,   620,   802,    96,   805,   443,   808,   352,
     379,   162,    48,   380,  -387,   186,   187,   188,  -387,   659,
     149,  -386,    48,   731,    11,   -24,   715,   391,   763,   435,
     105,   875,   153,    48,   310,   451,    48,    48,   480,    48,
     180,   454,   656,   477,    99,   366,   369,   371,   798,   160,
      66,   823,    97,   843,   375,   184,   446,   447,   799,   783,
     827,   151,   448,   865,   143,   159,    58,   144,    59,   475,
     182,   145,  -387,   146,   449,  -387,  -387,    48,   475,  -386,
     402,   475,    64,   403,   373,   392,   398,  -448,   862,   190,
     171,   172,   173,   689,   183,   174,   171,   172,   173,   762,
     185,   174,   353,   628,   374,   189,  -507,    99,   175,   734,
     376,  -507,   735,   313,   175,    97,  -448,   852,  -500,   437,
     376,   397,   381,   131,   132,   133,   134,   135,   136,   896,
     384,   666,   415,   415,  -438,  -457,   382,  -457,   417,  -381,
    -500,   869,   891,   177,     4,     5,   783,    96,  -382,  -500,
     669,   670,   820,   821,  -355,   915,  -355,  -355,   823,   631,
     632,  -486,    48,  -486,  -486,   386,   783,   905,    48,   634,
     635,   760,   761,   387,   655,   891,   767,   768,   679,   783,
     770,   771,   400,   679,   820,   821,   394,   444,   680,   396,
     383,   831,   657,   680,   406,   365,    66,   407,   368,   822,
     439,   917,   370,   372,   455,   476,   607,     1,     2,     3,
       4,     5,     6,     7,     8,   718,   477,   484,   721,   608,
       9,   654,   609,   485,   708,    60,   627,   709,   162,   630,
     440,   659,    11,   633,   636,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   365,   723,   637,   368,   657,   744,
     365,   658,   663,   368,   671,   713,   716,   719,   725,   722,
     445,   676,   727,   726,   366,   728,   729,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   420,   421,   422,   423,
     424,   730,   425,   426,   731,   785,   732,    61,    62,    63,
      64,   645,   737,   475,    22,   733,   475,   475,   736,   748,
     420,   421,   422,   423,   424,   769,   425,   426,   745,   746,
     747,   750,   758,   366,   752,   759,   772,   773,   453,   366,
     765,   766,   793,   815,   794,   692,   150,   797,   800,   825,
     806,   625,   809,   826,   828,   778,   818,  -597,   165,   832,
     365,   836,   837,   368,   167,   838,   841,   847,   857,   639,
     164,   647,   848,   651,   814,   850,   816,   817,   856,   365,
     365,   858,   368,   368,   859,   860,   861,   803,   804,   863,
     864,   866,   810,   868,   881,   878,   871,   648,   873,   882,
     420,   421,   422,   423,   424,   854,   425,   426,   874,   879,
     884,   645,   397,   778,   660,   883,   892,   730,   894,   707,
     895,   897,   908,   904,   906,   907,   665,   681,   682,   366,
     909,   717,   910,   912,   409,   911,   876,   409,   689,   914,
     846,   877,   475,   475,   795,   796,   918,    99,   366,   366,
     920,   893,   867,   921,   851,    97,   923,   645,   924,   161,
     845,   143,   388,   755,   144,   751,   678,   645,   145,   178,
     146,   693,   694,   695,   696,   697,   676,   389,   691,   158,
     405,   676,   720,   842,   724,   662,   152,   483,   807,   919,
     399,   698,   148,   913,   606,   645,   640,   819,   899,   885,
     778,   922,   849,   789,   645,     1,     2,     3,     4,     5,
       6,     7,     8,   916,     0,     0,     0,     0,     9,     0,
     778,     0,     0,    10,     0,     0,     0,     0,     0,     0,
      11,    12,    13,   778,     0,     0,     0,     0,     0,     0,
     788,     0,    14,     0,     0,     0,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,     0,     0,     0,     9,
       0,     0,     0,     0,    60,     0,     0,   143,   812,     0,
     144,   409,   756,   757,   145,     0,   146,   693,   694,   695,
     696,   697,     0,     0,    15,    16,    17,    18,    19,    20,
      21,     0,    22,     0,     0,     0,     0,     0,   714,     0,
     415,     0,     0,   415,     0,     0,   739,     0,     0,     0,
       0,   417,     0,     0,     0,   625,     0,    23,     0,     0,
       0,     0,    24,     0,    25,   165,    61,    62,    63,     0,
       0,   167,   741,     0,     0,     0,     0,   164,     0,     0,
       0,     0,    99,     0,     0,     0,     0,    99,     0,     0,
      97,     0,   375,   365,   365,    97,   368,   368,     0,     0,
       0,   678,     0,     0,     0,     0,   678,     0,   164,     0,
       0,   625,     0,     0,     0,     0,     0,     0,     0,   786,
       0,     0,   437,   898,     0,   437,   409,     0,     0,   833,
       0,   787,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     0,     0,     0,     0,     9,     0,     0,     0,   648,
      60,     0,     0,     0,     0,     0,     0,    11,     0,     0,
       0,     0,   366,   366,     0,     0,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,   830,   415,     0,     9,
      68,     0,     0,   714,    60,     0,     0,     0,     0,   839,
       0,    11,   681,   682,     0,     0,     0,     0,     0,   754,
       0,     0,     0,     0,     0,     0,     0,   844,   835,     0,
       0,   437,    61,    62,    63,    64,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,     0,    81,
      82,    83,    84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    92,    93,    18,    64,
     738,    65,   880,     0,     0,     0,     0,     0,     0,     0,
     886,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,     0,
       0,     0,     0,   672,   711,     0,     0,     0,     0,     0,
       0,   192,   415,   886,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,     0,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,     0,   269,     0,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   295,
     296,   297,   298,   299,   300,   301,   302,   303,     0,     0,
     304,     0,   305,   306,   307,   308,   309,   192,     0,     0,
     314,   194,   195,   196,   197,   198,   199,   200,   201,   315,
     203,   204,   205,   206,   316,   317,   209,   210,   211,   318,
     213,   214,   215,   216,   217,   218,   219,     0,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   319,   320,   321,   322,   323,   260,   261,
     262,   263,   264,   265,   266,   267,   268,     0,   269,     0,
     270,   271,   272,   273,   274,   324,   276,   325,   326,   327,
     328,   329,   330,   283,   331,   285,   286,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   303,     0,     0,   304,     0,   305,   306,
     307,   308,   309,   486,     0,     0,   487,   488,   489,   490,
     491,   492,   493,   494,   495,   496,   497,   498,   499,   500,
     501,   502,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,     0,   514,   515,   516,   517,   518,   384,
     690,   519,   520,   521,   522,   523,   524,   525,   526,   527,
     528,   529,   530,   531,   532,   533,   534,   535,   536,   537,
     538,   539,   540,   541,   542,   543,   544,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,     0,   561,     0,   562,   563,   564,   565,
     566,   567,   568,   569,   570,   571,   572,   573,   574,   575,
     576,   577,   578,   579,   580,   581,   582,   583,   584,   585,
     586,   587,   588,   589,   590,   591,   592,   593,   594,   595,
       0,     0,   596,     0,   597,   598,   599,   600,   601,   486,
       0,     0,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,     0,
     514,   515,   516,   517,   518,   384,     0,   519,   520,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   540,   541,
     542,   543,   544,   545,   546,   547,   548,   549,   550,   551,
     552,   553,   554,   555,   556,   557,   558,   559,   560,     0,
     561,     0,   562,   563,   564,   565,   566,   567,   568,   569,
     570,   571,   572,   573,   574,   575,   576,   577,   578,   579,
     580,   581,   582,   583,   584,   585,   586,   587,   588,   589,
     590,   591,   592,   593,   594,   595,   103,     0,   596,     0,
     597,   598,   599,   600,   601,   104,     0,     0,     0,     0,
     105,   106,   610,     0,     0,   107,   611,     0,   612,     0,
     613,   358,   614,     0,     0,   615,     0,     0,     0,     0,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     0,
     360,   361,   162,     9,     0,     0,     0,     0,    60,     0,
       0,     0,     0,   362,   363,    11,     0,     0,     0,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     616,   113,     0,   114,   115,   116,   117,   118,   119,     0,
     120,     0,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,     0,
      92,    93,    18,    64,     0,     0,     0,   617,     1,     2,
       3,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       0,     9,     0,     0,     0,     0,    60,     0,     0,   -33,
       0,     0,     0,    11,     0,     0,     0,    94,   -33,     0,
       0,     0,     0,   -33,   -33,     0,     0,     0,   -33,     0,
       0,   -33,   -33,   -33,   -33,     0,     0,     0,   -33,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -33,   -33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -33,   -33,    92,    93,
      18,    64,   -33,   -33,   -33,   -33,   -33,     0,     0,     0,
       0,     0,     0,     0,   -33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -33,     0,   -33,   -33,   -33,   -33,
     -33,   -33,     0,   -33,     0,   672,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -34,     0,   -33,     0,     0,     0,     0,     0,
       0,   -34,     0,     0,     0,     0,   -34,   -34,     0,     0,
       0,   -34,     0,     0,   -34,   -34,   -34,   -34,     0,     0,
       0,   -34,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,   -34,   -34,     0,     0,
       0,     9,     0,     0,     0,     0,    60,     0,     0,   -34,
     -34,     0,     0,    11,     0,   -34,   -34,   -34,   -34,   -34,
       0,     0,     0,     0,     0,     0,     0,   -34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -34,     0,   -34,
     -34,   -34,   -34,   -34,   -34,     0,   -34,     0,     0,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -57,     0,   -34,    61,    62,
      63,    64,     0,     0,   -57,     0,     0,     0,     0,   -57,
     -57,     0,     0,     0,   -57,     0,     0,   -57,   -57,   -57,
     -57,     0,     0,     0,   -57,     0,     0,     0,     0,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,   -57,
     -57,     0,     0,     0,     9,     0,     0,     0,     0,    60,
       0,     0,   -57,   -57,     0,     0,    11,     0,   -57,   -57,
     -57,   -57,   -57,     0,     0,     0,     0,     0,     0,     0,
     -57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -57,     0,   -57,   -57,   -57,   -57,   -57,   -57,     0,   -57,
       0,     0,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,
     -57,   -57,   -57,   -57,   -57,   -57,   -57,   -57,   -58,     0,
    -612,    92,    93,    18,    64,     0,     0,   -58,     0,     0,
       0,     0,   -58,   -58,     0,     0,     0,   -58,     0,     0,
     -58,   -58,   -58,   -58,     0,     0,     0,   -58,     0,     0,
       0,     0,     0,     0,     1,     2,     3,     4,     5,     6,
       7,     8,   -58,   -58,     0,     0,     0,     9,     0,     0,
       0,     0,    60,     0,     0,   -58,   -58,     0,     0,    11,
       0,   -58,   -58,   -58,   -58,   -58,     0,     0,     0,     0,
       0,     0,     0,   -58,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -58,     0,   -58,   -58,   -58,   -58,   -58,
     -58,     0,   -58,     0,     0,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -24,     0,  -573,    61,    62,    63,    64,     0,     0,
     -24,     0,     0,     0,     0,   -24,   -24,     0,     0,     0,
     -24,     0,     0,   -24,   -24,   -24,   -24,     0,     0,     0,
     -24,     0,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     7,     8,   -24,   -24,     0,     0,     0,
     408,     0,     0,     0,     0,    60,     0,     0,   -24,   -24,
       0,     0,    11,     0,   -24,   -24,   -24,   -24,   -24,     0,
       0,     0,     0,     0,     0,     0,   -24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -24,     0,   -24,   -24,
     -24,   -24,   -24,   -24,     0,   -24,     0,     0,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -39,     0,   -24,    61,    62,    63,
      64,     0,     0,   -39,     0,     0,     0,     0,   -39,   -39,
       0,     0,     0,   -39,     0,     0,   -39,   -39,   -39,   -39,
       0,     0,     0,   -39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -39,   -39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -39,   -39,     0,     0,     0,     0,   -39,   -39,   -39,
     -39,   -39,     0,     0,     0,     0,     0,     0,     0,   -39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -39,
       0,   -39,   -39,   -39,   -39,   -39,   -39,     0,   -39,     0,
       0,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -38,     0,   -39,
       0,     0,     0,     0,     0,     0,   -38,     0,     0,     0,
       0,   -38,   -38,     0,     0,     0,   -38,     0,     0,   -38,
     -38,   -38,   -38,     0,     0,     0,   -38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -38,   -38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -38,   -38,     0,     0,     0,     0,
     -38,   -38,   -38,   -38,   -38,     0,     0,     0,     0,     0,
       0,     0,   -38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -38,     0,   -38,   -38,   -38,   -38,   -38,   -38,
       0,   -38,     0,     0,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
     -37,     0,   -38,     0,     0,     0,     0,     0,     0,   -37,
       0,     0,     0,     0,   -37,   -37,     0,     0,     0,   -37,
       0,     0,   -37,   -37,   -37,   -37,     0,     0,     0,   -37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -37,   -37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -37,   -37,     0,
       0,     0,     0,   -37,   -37,   -37,   -37,   -37,     0,     0,
       0,     0,     0,     0,     0,   -37,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -37,     0,   -37,   -37,   -37,
     -37,   -37,   -37,     0,   -37,     0,     0,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -35,     0,   -37,     0,     0,     0,     0,
       0,     0,   -35,     0,     0,     0,     0,   -35,   -35,     0,
       0,     0,   -35,     0,     0,   -35,   -35,   -35,   -35,     0,
       0,     0,   -35,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -35,   -35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -35,   -35,     0,     0,     0,     0,   -35,   -35,   -35,   -35,
     -35,     0,     0,     0,     0,     0,     0,     0,   -35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -35,     0,
     -35,   -35,   -35,   -35,   -35,   -35,     0,   -35,     0,     0,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -36,     0,   -35,     0,
       0,     0,     0,     0,     0,   -36,     0,     0,     0,     0,
     -36,   -36,     0,     0,     0,   -36,     0,     0,   -36,   -36,
     -36,   -36,     0,     0,     0,   -36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -36,   -36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -36,   -36,     0,     0,     0,     0,   -36,
     -36,   -36,   -36,   -36,     0,     0,     0,     0,     0,     0,
       0,   -36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -36,     0,   -36,   -36,   -36,   -36,   -36,   -36,     0,
     -36,     0,     0,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -32,
       0,   -36,     0,     0,     0,     0,     0,     0,   -32,     0,
       0,     0,     0,   -32,   -32,     0,     0,     0,   -32,     0,
       0,   -32,   -32,   -32,   -32,     0,     0,     0,   -32,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -32,   -32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -32,   -32,     0,     0,
       0,     0,   -32,   -32,   -32,   -32,   -32,     0,     0,     0,
       0,     0,     0,     0,   -32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -32,     0,   -32,   -32,   -32,   -32,
     -32,   -32,     0,   -32,     0,     0,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -31,     0,   -32,     0,     0,     0,     0,     0,
       0,   -31,     0,     0,     0,     0,   -31,   -31,     0,     0,
       0,   -31,     0,     0,   -31,   -31,   -31,   -31,     0,     0,
       0,   -31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -31,   -31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -31,
     -31,     0,     0,     0,     0,   -31,   -31,   -31,   -31,   -31,
       0,     0,     0,     0,     0,     0,     0,   -31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -31,     0,   -31,
     -31,   -31,   -31,   -31,   -31,     0,   -31,     0,     0,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -25,     0,   -31,     0,     0,
       0,     0,     0,     0,   -25,     0,     0,     0,     0,   -25,
     -25,     0,     0,     0,   -25,     0,     0,   -25,   -25,   -25,
     -25,     0,     0,     0,   -25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -25,
     -25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,   -25,     0,     0,     0,     0,   -25,   -25,
     -25,   -25,   -25,     0,     0,     0,     0,     0,     0,     0,
     -25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -25,     0,   -25,   -25,   -25,   -25,   -25,   -25,     0,   -25,
       0,     0,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -29,     0,
     -25,     0,     0,     0,     0,     0,     0,   -29,     0,     0,
       0,     0,   -29,   -29,     0,     0,     0,   -29,     0,     0,
     -29,   -29,   -29,   -29,     0,     0,     0,   -29,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -29,   -29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -29,   -29,     0,     0,     0,
       0,   -29,   -29,   -29,   -29,   -29,     0,     0,     0,     0,
       0,     0,     0,   -29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -29,     0,   -29,   -29,   -29,   -29,   -29,
     -29,     0,   -29,     0,     0,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -28,     0,   -29,     0,     0,     0,     0,     0,     0,
     -28,     0,     0,     0,     0,   -28,   -28,     0,     0,     0,
     -28,     0,     0,   -28,   -28,   -28,   -28,     0,     0,     0,
     -28,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -28,   -28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -28,   -28,
       0,     0,     0,     0,   -28,   -28,   -28,   -28,   -28,     0,
       0,     0,     0,     0,     0,     0,   -28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -28,     0,   -28,   -28,
     -28,   -28,   -28,   -28,     0,   -28,     0,     0,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -26,     0,   -28,     0,     0,     0,
       0,     0,     0,   -26,     0,     0,     0,     0,   -26,   -26,
       0,     0,     0,   -26,     0,     0,   -26,   -26,   -26,   -26,
       0,     0,     0,   -26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -26,   -26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -26,   -26,     0,     0,     0,     0,   -26,   -26,   -26,
     -26,   -26,     0,     0,     0,     0,     0,     0,     0,   -26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -26,
       0,   -26,   -26,   -26,   -26,   -26,   -26,     0,   -26,     0,
       0,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -27,     0,   -26,
       0,     0,     0,     0,     0,     0,   -27,     0,     0,     0,
       0,   -27,   -27,     0,     0,     0,   -27,     0,     0,   -27,
     -27,   -27,   -27,     0,     0,     0,   -27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -27,   -27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -27,   -27,     0,     0,     0,     0,
     -27,   -27,   -27,   -27,   -27,     0,     0,     0,     0,     0,
       0,     0,   -27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -27,     0,   -27,   -27,   -27,   -27,   -27,   -27,
       0,   -27,     0,     0,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -40,     0,   -27,     0,     0,     0,     0,     0,     0,   -40,
       0,     0,     0,     0,   -40,   -40,     0,     0,     0,   -40,
       0,     0,   -40,   -40,   -40,   -40,     0,     0,     0,   -40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -40,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -40,   -40,     0,
       0,     0,     0,   -40,   -40,   -40,   -40,   -40,     0,     0,
       0,     0,     0,     0,     0,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -40,     0,   -40,   -40,   -40,
     -40,   -40,   -40,     0,   -40,     0,     0,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,  -135,     0,   -40,     0,     0,     0,     0,
       0,     0,  -135,     0,     0,     0,     0,  -135,  -135,     0,
       0,     0,  -135,     0,     0,  -135,  -135,  -135,  -135,     0,
       0,     0,  -135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -135,  -135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -135,  -135,     0,     0,     0,     0,  -135,  -135,  -135,  -135,
    -135,     0,     0,     0,     0,     0,     0,     0,  -135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -135,     0,
    -135,  -135,  -135,  -135,  -135,  -135,     0,  -135,     0,     0,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -136,     0,  -581,     0,
       0,     0,     0,     0,     0,  -136,     0,     0,     0,     0,
    -136,  -136,     0,     0,     0,  -136,     0,     0,  -136,  -136,
    -136,  -136,     0,     0,     0,  -136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -136,  -136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -136,  -136,     0,     0,     0,     0,  -136,
    -136,  -136,  -136,  -136,     0,     0,     0,     0,     0,     0,
       0,  -136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -136,     0,  -136,  -136,  -136,  -136,  -136,  -136,     0,
    -136,     0,     0,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -137,
       0,  -580,     0,     0,     0,     0,     0,     0,  -137,     0,
       0,     0,     0,  -137,  -137,     0,     0,     0,  -137,     0,
       0,  -137,  -137,  -137,  -137,     0,     0,     0,  -137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -137,  -137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -137,  -137,     0,     0,
       0,     0,  -137,  -137,  -137,  -137,  -137,     0,     0,     0,
       0,     0,     0,     0,  -137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -137,     0,  -137,  -137,  -137,  -137,
    -137,  -137,     0,  -137,     0,     0,  -137,  -137,  -137,  -137,
    -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,  -138,     0,  -578,     0,     0,     0,     0,     0,
       0,  -138,     0,     0,     0,     0,  -138,  -138,     0,     0,
       0,  -138,     0,     0,  -138,  -138,  -138,  -138,     0,     0,
       0,  -138,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -138,  -138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -138,
    -138,     0,     0,     0,     0,  -138,  -138,  -138,  -138,  -138,
       0,     0,     0,     0,     0,     0,     0,  -138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -138,     0,  -138,
    -138,  -138,  -138,  -138,  -138,     0,  -138,     0,     0,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -139,     0,  -576,     0,     0,
       0,     0,     0,     0,  -139,     0,     0,     0,     0,  -139,
    -139,     0,     0,     0,  -139,     0,     0,  -139,  -139,  -139,
    -139,     0,     0,     0,  -139,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -139,
    -139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -139,  -139,     0,     0,     0,     0,  -139,  -139,
    -139,  -139,  -139,     0,     0,     0,     0,     0,     0,     0,
    -139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -139,     0,  -139,  -139,  -139,  -139,  -139,  -139,     0,  -139,
       0,     0,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -140,     0,
    -577,     0,     0,     0,     0,     0,     0,  -140,     0,     0,
       0,     0,  -140,  -140,     0,     0,     0,  -140,     0,     0,
    -140,  -140,  -140,  -140,     0,     0,     0,  -140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -140,  -140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -140,  -140,     0,     0,     0,
       0,  -140,  -140,  -140,  -140,  -140,     0,     0,     0,     0,
       0,     0,     0,  -140,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -140,     0,  -140,  -140,  -140,  -140,  -140,
    -140,     0,  -140,     0,     0,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -141,     0,  -579,     0,     0,     0,     0,     0,     0,
    -141,     0,     0,     0,     0,  -141,  -141,     0,     0,     0,
    -141,     0,     0,  -141,  -141,  -141,  -141,     0,     0,     0,
    -141,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -141,  -141,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -141,  -141,
       0,     0,     0,     0,  -141,  -141,  -141,  -141,  -141,     0,
       0,     0,     0,     0,     0,     0,  -141,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -141,     0,  -141,  -141,
    -141,  -141,  -141,  -141,     0,  -141,     0,     0,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -142,     0,  -575,     0,     0,     0,
       0,     0,     0,  -142,     0,     0,     0,     0,  -142,  -142,
       0,     0,     0,  -142,     0,     0,  -142,  -142,  -142,  -142,
       0,     0,     0,  -142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -142,  -142,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -142,  -142,     0,     0,     0,     0,  -142,  -142,  -142,
    -142,  -142,     0,     0,     0,     0,     0,     0,     0,  -142,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -142,
       0,  -142,  -142,  -142,  -142,  -142,  -142,     0,  -142,     0,
       0,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -143,     0,  -574,
       0,     0,     0,     0,     0,     0,  -143,     0,     0,     0,
       0,  -143,  -143,     0,     0,     0,  -143,     0,     0,  -143,
    -143,  -143,  -143,     0,     0,     0,  -143,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -143,  -143,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -143,  -143,     0,     0,     0,     0,
    -143,  -143,  -143,  -143,  -143,     0,     0,     0,     0,     0,
       0,     0,  -143,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -143,     0,  -143,  -143,  -143,  -143,  -143,  -143,
       0,  -143,     0,     0,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
     -30,     0,  -582,     0,     0,     0,     0,     0,     0,   -30,
       0,     0,     0,     0,   -30,   -30,     0,     0,     0,   -30,
       0,     0,   -30,   -30,   -30,   -30,     0,     0,     0,   -30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -30,   -30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -30,   -30,     0,
       0,     0,     0,   -30,   -30,   -30,   -30,   -30,     0,     0,
       0,     0,     0,     0,     0,   -30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -30,     0,   -30,   -30,   -30,
     -30,   -30,   -30,     0,   -30,     0,     0,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,  -145,     0,   -30,     0,     0,     0,     0,
       0,     0,  -145,     0,     0,     0,     0,  -145,  -145,     0,
       0,     0,  -145,     0,     0,  -145,  -145,  -145,  -145,     0,
       0,     0,  -145,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -145,  -145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -145,  -145,     0,     0,     0,     0,  -145,  -145,  -145,  -145,
    -145,     0,     0,     0,     0,     0,     0,     0,  -145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -145,     0,
    -145,  -145,  -145,  -145,  -145,  -145,     0,  -145,     0,     0,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -146,     0,  -610,     0,
       0,     0,     0,     0,     0,  -146,     0,     0,     0,     0,
    -146,  -146,     0,     0,     0,  -146,     0,     0,  -146,  -146,
    -146,  -146,     0,     0,     0,  -146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -146,  -146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -146,  -146,     0,     0,     0,     0,  -146,
    -146,  -146,  -146,  -146,     0,     0,     0,     0,     0,     0,
       0,  -146,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -146,     0,  -146,  -146,  -146,  -146,  -146,  -146,     0,
    -146,     0,     0,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -147,
       0,  -608,     0,     0,     0,     0,     0,     0,  -147,     0,
       0,     0,     0,  -147,  -147,     0,     0,     0,  -147,     0,
       0,  -147,  -147,  -147,  -147,     0,     0,     0,  -147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -147,  -147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -147,  -147,     0,     0,
       0,     0,  -147,  -147,  -147,  -147,  -147,     0,     0,     0,
       0,     0,     0,     0,  -147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -147,     0,  -147,  -147,  -147,  -147,
    -147,  -147,     0,  -147,     0,     0,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -148,     0,  -607,     0,     0,     0,     0,     0,
       0,  -148,     0,     0,     0,     0,  -148,  -148,     0,     0,
       0,  -148,     0,     0,  -148,  -148,  -148,  -148,     0,     0,
       0,  -148,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -148,  -148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -148,
    -148,     0,     0,     0,     0,  -148,  -148,  -148,  -148,  -148,
       0,     0,     0,     0,     0,     0,     0,  -148,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -148,     0,  -148,
    -148,  -148,  -148,  -148,  -148,     0,  -148,     0,     0,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -149,     0,  -609,     0,     0,
       0,     0,     0,     0,  -149,     0,     0,     0,     0,  -149,
    -149,     0,     0,     0,  -149,     0,     0,  -149,  -149,  -149,
    -149,     0,     0,     0,  -149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -149,
    -149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -149,  -149,     0,     0,     0,     0,  -149,  -149,
    -149,  -149,  -149,     0,     0,     0,     0,     0,     0,     0,
    -149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -149,     0,  -149,  -149,  -149,  -149,  -149,  -149,     0,  -149,
       0,     0,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -150,     0,
    -606,     0,     0,     0,     0,     0,     0,  -150,     0,     0,
       0,     0,  -150,  -150,     0,     0,     0,  -150,     0,     0,
    -150,  -150,  -150,  -150,     0,     0,     0,  -150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -150,  -150,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -150,  -150,     0,     0,     0,
       0,  -150,  -150,  -150,  -150,  -150,     0,     0,     0,     0,
       0,     0,     0,  -150,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -150,     0,  -150,  -150,  -150,  -150,  -150,
    -150,     0,  -150,     0,     0,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,   103,     0,  -605,     0,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,     0,     0,     0,
     107,     0,     0,   356,   440,   357,   358,     0,     0,     0,
     359,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   361,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   362,   363,
       0,     0,     0,     0,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,   364,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,     0,   114,   115,
     116,   117,   118,   119,     0,   120,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,  -573,     0,   441,     0,     0,     0,
       0,     0,     0,  -573,     0,     0,     0,     0,  -573,  -573,
       0,     0,     0,  -573,     0,     0,     0,     0,     0,     0,
    -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,
    -573,  -573,     0,  -573,  -573,  -573,  -573,  -573,  -573,  -573,
    -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,
    -573,     0,     0,     0,     0,     0,  -573,  -573,  -573,  -573,
    -573,  -573,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     0,     0,     0,     0,     9,     0,     0,  -573,  -573,
     156,  -573,  -573,  -573,  -573,  -573,  -573,    11,  -573,     0,
       0,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,  -573,
    -573,  -573,  -573,  -573,  -573,  -573,  -573,   103,     1,     2,
       3,     4,     5,     6,     7,     8,   104,     0,     0,     0,
       0,   705,   106,   610,     0,     0,   706,   611,     0,   612,
       0,   613,   358,    11,     0,     0,   615,     0,     0,     0,
       0,   157,    61,    62,    63,    64,     0,     0,     0,     0,
       0,   360,   361,   162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   362,   363,     0,     0,     0,     0,
     108,   109,   110,   111,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    61,    62,
      63,    64,   113,     0,   114,   115,   116,   117,   118,   119,
       0,   120,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     103,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,     0,   105,   106,   683,   684,   685,   107,
     611,     0,   612,   440,   613,   358,     0,     0,     0,   615,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   360,   361,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   362,   363,     0,
       0,     0,     0,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,     0,   114,   115,   116,
     117,   118,   119,     0,   120,     0,     0,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   103,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,   774,
       0,     0,   107,   611,     0,   612,     0,   613,   358,     0,
       0,     0,   615,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   360,   361,   162,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     362,   363,     0,     0,     0,     0,   108,   109,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   775,
     776,   115,   116,   117,   118,   119,     0,   120,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   777,
     131,   132,   133,   134,   135,   136,   103,     0,     0,     0,
       0,     0,     0,     0,     0,   104,     0,     0,     0,     0,
     105,   106,   610,     0,     0,   107,   611,     0,   612,     0,
     613,   358,     0,     0,     0,   615,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     360,   361,   162,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   362,   363,     0,     0,   853,     0,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,     0,   114,   115,   116,   117,   118,   119,     0,
     120,     0,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   103,
       0,     0,     0,     0,     0,     0,     0,     0,   104,     0,
       0,     0,     0,   105,   106,   610,     0,     0,   107,   611,
    -624,   612,     0,   613,   358,     0,     0,     0,   615,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     153,     0,     0,   360,   361,   162,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   362,   363,     0,     0,
       0,     0,   108,   109,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,     0,   114,   115,   116,   117,
     118,   119,     0,   120,     0,     0,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   103,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     0,     0,     0,   105,   106,   610,     0,
       0,   107,   611,     0,   612,     0,   613,   358,     0,     0,
       0,   615,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,     0,     0,   360,   361,   162,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   362,
     363,     0,     0,     0,     0,   108,   109,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,     0,   114,
     115,   116,   117,   118,   119,     0,   120,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   103,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,     0,     0,     0,   105,
     106,   774,     0,     0,   107,   611,     0,   612,     0,   613,
     358,     0,     0,     0,   615,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   360,
     361,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   362,   363,     0,     0,     0,     0,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   775,   776,   115,   116,   117,   118,   119,     0,   120,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   777,   131,   132,   133,   134,   135,   136,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,   610,     0,     0,   107,   611,     0,
     612,     0,   613,   358,     0,     0,     0,   615,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   360,   361,   162,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   362,   363,     0,     0,     0,
       0,   108,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,     0,   114,   115,   116,   117,   118,
     119,     0,   120,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   103,     0,     0,     0,     0,     0,     0,     0,     0,
     104,     0,     0,     0,     0,   105,   106,     0,     0,     0,
     107,     0,     0,   356,     0,   357,   358,     0,     0,     0,
     359,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   361,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   362,   363,
       0,     0,     0,     0,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,   364,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,     0,   114,   115,
     116,   117,   118,   119,     0,   120,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   103,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,   105,   106,
       0,     0,     0,   107,     0,     0,     0,     0,     0,     0,
      11,     0,     0,  -516,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     0,     0,     0,     0,
     162,     9,     0,     0,     0,     0,    60,     0,     0,     0,
     446,   447,     0,     0,     0,     0,     0,   108,   109,   110,
     111,   112,     0,     0,     0,     0,     0,     0,   449,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,   113,
       0,   114,   115,   116,   117,   118,   119,     0,   120,     0,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   103,    61,    62,
      63,     0,     0,     0,     0,     0,   104,     0,     0,     0,
       0,   105,   106,     0,     0,   664,   107,     0,     0,     0,
       0,     0,     0,    11,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,     0,   162,     0,     0,     0,   474,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,   113,     0,   114,   115,   116,   117,   118,   119,
       0,   120,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     103,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       0,   764,     0,     0,   105,   106,     0,     0,     0,   107,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,     0,     0,
       0,     0,     0,   711,     0,     0,   162,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,     0,   114,   115,   116,
     117,   118,   119,     0,   120,     0,     0,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   103,     0,     0,     0,     0,     0,     0,
       0,     0,   104,     0,     0,     0,     0,   105,   106,     0,
       0,     0,   107,     0,   903,     0,     0,     0,     0,     0,
       0,     0,   452,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,     0,     0,     0,     0,     0,   711,     0,     0,     0,
       0,     0,   103,     0,     0,     0,   108,   109,   110,   111,
     112,   104,     0,     0,     0,     0,   105,   106,     0,     0,
       0,   107,     0,     0,     0,     0,     0,     0,   113,     0,
     114,   115,   116,   117,   118,   119,     0,   120,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,     0,     0,     0,     0,
       0,     0,     0,   740,     0,   108,   109,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,     0,   114,
     115,   116,   117,   118,   119,     0,   120,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   103,     0,     0,     0,     0,
       0,     0,     0,     0,   104,     0,     0,   870,     0,   790,
     106,     0,     0,     0,   107,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,     0,     0,     0,     0,     0,   711,     0,
       0,   162,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,     0,   114,   115,   116,   117,   118,   119,     0,   120,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   104,     0,     0,
       0,     0,   105,   106,     0,     0,     0,   107,     0,     0,
       0,     0,   749,     0,     0,     0,     0,     0,   813,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,     0,     0,     0,
       0,     0,   474,     0,     0,     0,     0,   103,     0,     0,
       0,   108,   109,   110,   111,   112,   104,     0,     0,     0,
       0,   105,   106,     0,     0,     0,   107,     0,     0,     0,
       0,     0,     0,   113,     0,   114,   115,   116,   117,   118,
     119,     0,   120,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,     0,     0,     0,     0,   103,     0,   834,     0,
     108,   109,   110,   111,   112,   104,     0,     0,     0,     0,
     105,   106,     0,     0,     0,   107,     0,     0,     0,     0,
       0,     0,   113,     0,   114,   115,   116,   117,   118,   119,
       0,   120,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,     0,   114,   115,   116,   117,   118,   119,     0,
     120,     0,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   811,
       0,     0,     0,     0,     0,     0,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,     0,     0,     0,   710,     0,   711,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,     0,     0,
       0,     0,     0,   711,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,     0,     0,     0,     0,     0,   474,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,     0,     0,     0,     0,
       0,   711,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
       0,     0,     0,     0,     0,   474,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,     0,     0,     0,     0,     0,   711
};

static const short int yycheck[] =
{
      10,    22,    33,    87,   183,    15,   182,   183,    33,     0,
      16,    17,    18,    15,    33,   102,    91,   190,   421,    91,
      34,   397,   424,   477,   421,   396,   310,   424,   377,   378,
      80,   151,   701,   477,   367,   427,    27,   726,   409,   159,
      90,   726,   726,   394,   755,    15,   759,   310,   761,    26,
     137,    49,     0,   140,    29,    61,    62,    63,    33,    26,
      26,    29,    10,    24,    29,    33,    33,    29,    33,   189,
      17,    18,    44,    21,    80,   359,    24,    25,    31,    27,
     125,   365,   433,    36,    94,    91,    92,    93,    25,     0,
      10,   776,    94,   806,   100,    36,    26,    27,    35,   784,
     784,    21,    32,    64,     3,    25,     9,     6,    11,   442,
      32,    10,    87,    12,    44,    33,    34,    65,   451,    87,
       6,   454,    87,     9,    94,    87,   124,    32,   839,    34,
       4,     5,     6,   484,    32,     9,     4,     5,     6,   808,
      36,     9,   119,   406,    31,    65,    31,   157,    22,    31,
      35,    36,    34,    30,    22,   157,    32,   826,    36,   190,
      35,   167,    23,   110,   111,   112,   113,   114,   115,   880,
      36,   455,   182,   183,    31,    32,    31,    34,   184,    35,
      36,   850,   871,     6,     7,     8,   871,   157,    35,    36,
     474,   475,    17,    18,    31,   908,    33,    34,   883,    33,
      34,    31,   150,    33,    34,    36,   891,   891,   156,    33,
      34,    33,    34,    23,   606,   904,    32,    33,   672,   904,
      33,    34,     6,   677,    17,    18,    38,   311,   672,    32,
     150,    33,    34,   677,    32,   310,   156,    31,   310,    32,
      31,   910,    92,    93,    32,    35,    32,     4,     5,     6,
       7,     8,     9,    10,    11,   631,    36,    40,   634,    31,
      17,    37,    31,   383,   615,    22,     6,   618,    49,    32,
      26,    26,    29,    34,    40,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   359,   636,    34,   359,    34,   660,
     365,    32,    22,   365,    32,    39,    32,    64,    37,    64,
     350,   477,    31,    40,   310,    40,    31,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    92,    93,    94,    95,
      96,    32,    98,    99,    24,   728,    40,    84,    85,    86,
      87,   728,    31,   666,    91,    32,   669,   670,    32,    34,
      92,    93,    94,    95,    96,   716,    98,    99,    33,    33,
      33,    25,    31,   359,    35,    35,    33,    33,   364,   365,
     711,   712,    33,    64,    34,    37,   123,    34,    34,    32,
      35,   396,    40,    32,    34,   726,   109,    33,   409,    33,
     455,    25,    35,   455,   409,    32,    31,    33,    31,   420,
     409,   422,    33,   424,   770,    32,   772,   773,    33,   474,
     475,    97,   474,   475,    33,    35,    25,   756,   757,    34,
      31,    33,   763,    33,    24,    32,    34,   423,    33,    32,
      92,    93,    94,    95,    96,   828,    98,    99,    34,    34,
      32,   828,   438,   784,   448,    97,    33,    32,    25,   615,
      25,    33,    35,    34,    34,    33,   452,   478,   479,   455,
      33,   630,    32,    34,   630,    33,   858,   633,   809,    25,
     811,   858,   795,   796,   748,   749,    33,   477,   474,   475,
      33,   874,   848,    32,   825,   477,    33,   874,    33,    27,
     809,     3,   157,   677,     6,   672,   477,   884,    10,    40,
      12,    13,    14,    15,    16,    17,   672,   158,   604,    24,
     178,   677,   633,   802,   637,   448,    21,   380,   761,   912,
     168,    33,    19,   904,   386,   912,   420,   775,   883,   870,
     871,   921,   822,   735,   921,     4,     5,     6,     7,     8,
       9,    10,    11,   909,    -1,    -1,    -1,    -1,    17,    -1,
     891,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,   904,    -1,    -1,    -1,    -1,    -1,    -1,
     733,    -1,    41,    -1,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,    -1,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,     3,   767,    -1,
       6,   767,   679,   680,    10,    -1,    12,    13,    14,    15,
      16,    17,    -1,    -1,    83,    84,    85,    86,    87,    88,
      89,    -1,    91,    -1,    -1,    -1,    -1,    -1,   624,    -1,
     630,    -1,    -1,   633,    -1,    -1,   657,    -1,    -1,    -1,
      -1,   637,    -1,    -1,    -1,   660,    -1,   116,    -1,    -1,
      -1,    -1,   121,    -1,   123,   676,    84,    85,    86,    -1,
      -1,   676,   658,    -1,    -1,    -1,    -1,   676,    -1,    -1,
      -1,    -1,   672,    -1,    -1,    -1,    -1,   677,    -1,    -1,
     672,    -1,   678,   748,   749,   677,   748,   749,    -1,    -1,
      -1,   672,    -1,    -1,    -1,    -1,   677,    -1,   707,    -1,
      -1,   716,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   730,
      -1,    -1,   733,   882,    -1,   736,   882,    -1,    -1,   793,
      -1,   732,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    -1,   735,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
      -1,    -1,   748,   749,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,   787,   767,    -1,    17,
      30,    -1,    -1,   769,    22,    -1,    -1,    -1,    -1,   800,
      -1,    29,   803,   804,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   808,   794,    -1,
      -1,   822,    84,    85,    86,    87,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    79,
      80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,
      31,   123,   863,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     871,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,   121,    65,    -1,    -1,    -1,    -1,    -1,
      -1,     0,   882,   904,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    -1,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,    -1,    -1,
     119,    -1,   121,   122,   123,   124,   125,     0,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    -1,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    -1,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,    -1,    -1,   119,    -1,   121,   122,
     123,   124,   125,     0,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    -1,    81,    -1,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
      -1,    -1,   119,    -1,   121,   122,   123,   124,   125,     0,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      81,    -1,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,     3,    -1,   119,    -1,
     121,   122,   123,   124,   125,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    25,    -1,
      27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,    -1,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      47,    48,    49,    17,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    60,    61,    29,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      87,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    -1,
      84,    85,    86,    87,    -1,    -1,    -1,   124,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,     3,
      -1,    -1,    -1,    29,    -1,    -1,    -1,   121,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    84,    85,
      86,    87,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,   121,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,     8,     9,    10,    11,    47,    48,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    60,
      61,    -1,    -1,    29,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,   118,    84,    85,
      86,    87,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    47,
      48,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    22,
      -1,    -1,    60,    61,    -1,    -1,    29,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
     118,    84,    85,    86,    87,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    47,    48,    -1,    -1,    -1,    17,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    60,    61,    -1,    -1,    29,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,   118,    84,    85,    86,    87,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    10,    11,    47,    48,    -1,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    60,    61,
      -1,    -1,    29,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,   118,    84,    85,    86,
      87,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    -1,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    -1,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    -1,   118,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,   118,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,   118,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,   118,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    -1,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    68,
      69,    70,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,    87,    88,
      22,    90,    91,    92,    93,    94,    95,    29,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    17,    18,    19,    -1,    -1,    22,    23,    -1,    25,
      -1,    27,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85,
      86,    87,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    64,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    -1,    -1,    17,    18,    19,    -1,    -1,    22,    23,
      24,    25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,    -1,    17,    18,    19,    -1,
      -1,    22,    23,    -1,    25,    -1,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,
      18,    19,    -1,    -1,    22,    23,    -1,    25,    -1,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    32,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    -1,    -1,    -1,
      49,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      26,    27,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    84,    85,
      86,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    33,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    49,    -1,    -1,    -1,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    33,    -1,    -1,    17,    18,    -1,    -1,    -1,    22,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,     3,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    12,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    -1,    -1,    34,    -1,    17,
      18,    -1,    -1,    -1,    22,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    33,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    12,    -1,    -1,    -1,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,    -1,     3,    -1,    64,    -1,
      66,    67,    68,    69,    70,    12,    -1,    -1,    -1,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    35,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    39,    -1,    65,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned short int yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      22,    29,    30,    31,    41,    83,    84,    85,    86,    87,
      88,    89,    91,   116,   121,   123,   146,   147,   148,   149,
     150,   167,   170,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   188,   191,   194,   198,   199,   200,   201,   203,
     205,   209,   211,   212,   218,   226,   240,   241,     9,    11,
      22,    84,    85,    86,    87,   123,   199,   209,    30,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    79,    80,    81,    82,   151,   152,   153,   154,   156,
     157,   158,    84,    85,   121,   171,   173,   200,   201,   209,
     218,   227,   228,     3,    12,    17,    18,    22,    66,    67,
      68,    69,    70,    88,    90,    91,    92,    93,    94,    95,
      97,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   143,   259,   271,
     143,   143,   229,     3,     6,    10,    12,   246,   248,    26,
     123,   199,   241,    44,   279,   280,    22,    83,   198,   199,
       0,   148,    49,   143,   176,   210,   235,   236,   237,   238,
     177,     4,     5,     6,     9,    22,   184,     6,   181,   187,
     125,   189,    32,    32,    36,    36,   143,   143,   143,   199,
      34,   192,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    81,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   119,   121,   122,   123,   124,   125,
     143,   144,   159,    30,     3,    12,    17,    18,    22,    66,
      67,    68,    69,    70,    88,    90,    91,    92,    93,    94,
      95,    97,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   144,   162,
     163,   162,    26,   119,   155,   144,    25,    27,    28,    32,
      47,    48,    60,    61,    78,   142,   143,   164,   223,   143,
     229,   143,   229,   173,    31,   143,    35,   232,   232,   232,
     232,    23,    31,   199,    36,   195,    36,    23,   171,   189,
     195,    29,    87,   239,    38,   233,    32,   143,   124,   238,
       6,   185,     6,     9,   186,   184,    32,    31,    17,   175,
     202,   204,   206,   207,   208,   209,   206,   143,   219,   220,
      92,    93,    94,    95,    96,    98,    99,   250,   251,   252,
     265,   268,   274,   275,   276,   195,   193,   210,   236,    31,
      26,   118,   164,   190,   162,   144,    26,    27,    32,    44,
     225,   164,    32,   143,   164,    32,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    65,   141,    35,    36,   214,   214,
      31,   213,   214,   213,    40,   195,     0,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    31,    32,    33,    34,    35,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    81,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   119,   121,   122,   123,
     124,   125,   145,   195,   196,   197,   250,    32,    31,    31,
      19,    23,    25,    27,    29,    32,    87,   124,   142,   210,
     221,   222,   223,   234,   235,   236,   233,     6,   190,   235,
      32,    33,    34,    34,    33,    34,    40,    34,   230,   210,
     255,   221,   244,   269,   270,   271,   279,   210,   143,   277,
     278,   210,   266,   270,    37,   251,   221,    34,    32,    26,
     177,   224,   225,    22,    33,   143,   164,   165,   166,   164,
     164,    32,   121,   172,   173,   174,   175,   215,   218,   227,
     228,   210,   210,    19,    20,    21,   168,   169,   190,   221,
      37,   197,    37,    13,    14,    15,    16,    17,    33,   242,
     243,   245,   247,   248,   249,    17,    22,   175,   221,   221,
      39,    65,   141,    39,   143,    33,    32,   206,   233,    64,
     208,   233,    64,   221,   220,    37,    40,    31,    40,    31,
      32,    24,    40,    32,    31,    34,    32,    31,    31,   210,
      64,   143,   160,   161,   235,    33,    33,    33,    34,    35,
      25,   174,    35,   231,    37,   172,   232,   232,    31,    35,
      33,    34,   244,    33,    33,   221,   221,    32,    33,   235,
      33,    34,    33,    33,    19,    89,    90,   109,   221,   254,
     256,   257,   258,   259,   280,   269,   210,   279,   193,   278,
      17,   193,   267,    33,    34,   164,   164,    34,    25,    35,
      34,   216,   231,   214,   214,   245,    35,   243,   245,    40,
     221,    35,   206,    33,   233,    64,   233,   233,   109,   256,
      17,    18,    32,   259,   262,    32,    32,   254,    34,   272,
     210,    33,    33,   162,    64,   143,    25,    35,    32,   210,
     217,    31,   216,   245,   279,   168,   221,    33,    33,   267,
      32,   221,   244,    64,   269,   273,    33,    31,    97,    33,
      35,    25,   231,    34,    31,    64,    33,   233,    33,   244,
      34,    34,   260,    33,    34,    18,   270,   271,    32,    34,
     210,    24,    32,    97,    32,   221,   210,   253,   254,   255,
     261,   280,    33,   269,    25,    25,   231,    33,   206,   262,
     263,   264,   269,    33,    34,   254,    34,    33,    35,    33,
      32,    33,    34,   253,    25,   245,   233,   244,    33,   269,
      33,    32,   263,    33,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short int yyr1[] =
{
       0,   140,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     142,   142,   142,   142,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     145,   145,   145,   145,   145,   145,   145,   146,   146,   147,
     147,   148,   148,   148,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   149,   150,   150,   151,   151,
     151,   151,   151,   151,   151,   151,   152,   152,   153,   153,
     154,   154,   154,   155,   155,   156,   156,   157,   157,   157,
     158,   158,   159,   159,   159,   159,   160,   160,   160,   160,
     161,   161,   162,   162,   163,   163,   164,   164,   164,   164,
     164,   164,   164,   164,   164,   164,   164,   165,   165,   166,
     166,   167,   168,   168,   168,   169,   169,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   173,   174,
     174,   174,   174,   174,   175,   175,   175,   176,   176,   177,
     177,   178,   178,   178,   179,   179,   179,   179,   180,   180,
     180,   181,   181,   182,   182,   182,   183,   183,   183,   183,
     184,   184,   184,   184,   184,   184,   185,   185,   186,   186,
     186,   186,   187,   187,   187,   188,   188,   189,   189,   190,
     190,   191,   192,   192,   193,   193,   194,   194,   194,   194,
     195,   196,   196,   197,   197,   198,   198,   199,   199,   200,
     200,   201,   201,   201,   202,   202,   203,   204,   205,   206,
     206,   206,   207,   207,   208,   208,   208,   209,   209,   210,
     210,   211,   212,   213,   213,   214,   215,   215,   216,   216,
     217,   217,   218,   219,   219,   220,   220,   221,   221,   221,
     221,   221,   221,   222,   222,   222,   222,   222,   222,   223,
     223,   224,   224,   225,   225,   225,   226,   227,   228,   229,
     229,   230,   230,   231,   231,   231,   231,   232,   232,   233,
     233,   233,   234,   234,   234,   234,   235,   235,   236,   236,
     237,   237,   238,   238,   239,   239,   240,   240,   241,   241,
     241,   242,   242,   243,   243,   244,   245,   246,   247,   247,
     248,   248,   248,   248,   249,   249,   249,   249,   249,   250,
     250,   251,   251,   251,   251,   251,   252,   252,   253,   253,
     253,   254,   254,   254,   254,   254,   254,   255,   255,   256,
     257,   257,   258,   259,   259,   259,   259,   259,   259,   259,
     259,   259,   259,   260,   260,   261,   261,   262,   262,   263,
     263,   264,   264,   265,   266,   266,   267,   267,   267,   268,
     269,   269,   269,   270,   270,   271,   271,   271,   271,   271,
     271,   271,   271,   272,   272,   273,   273,   274,   275,   275,
     276,   277,   277,   278,   279,   279,   280
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
       1,     1,     1,     1,     1,     1,     1,     0,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,     3,     2,     2,
       1,     2,     2,     2,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     6,     2,     2,     0,     1,     1,     3,
       1,     3,     0,     1,     1,     2,     3,     2,     3,     5,
       2,     4,     1,     1,     1,     1,     4,     0,     1,     1,
       3,     6,     1,     1,     1,     1,     1,     1,     3,     4,
       1,     2,     1,     2,     1,     1,     2,     4,     4,     1,
       1,     1,     3,     3,     1,     2,     2,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     2,     2,
       0,     1,     1,     2,     1,     2,     0,     1,     0,     1,
       1,     2,     0,     1,     2,     3,     4,     0,     4,     1,
       2,     4,     0,     2,     1,     3,     3,     4,     3,     4,
       3,     1,     2,     1,     1,     1,     2,     1,     1,     5,
       7,     5,     7,    13,     5,     7,     6,     5,     1,     0,
       1,     1,     1,     3,     1,     1,     2,     1,     2,     3,
       2,     4,     4,     1,     1,     3,     4,     5,     0,     2,
       2,     4,     5,     1,     3,     1,     3,     1,     4,     3,
       3,     2,     5,     1,     1,     1,     1,     1,     1,     4,
       2,     1,     2,     2,     1,     1,     2,     2,     2,     0,
       1,     0,     1,     0,     2,     7,     9,     0,     7,     0,
       3,     3,     0,     1,     1,     1,     0,     1,     1,     2,
       1,     2,     1,     2,     1,     1,     4,     5,     7,     8,
      13,     1,     3,     2,     4,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     3,     6,     1,     2,
       1,     1,     1,     1,     2,     1,     1,     3,     4,     6,
       8,    12,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     1,     3,     1,     1,     0,
       1,     1,     3,     3,     6,     1,     0,     1,     1,     3,
       1,     1,     3,     5,     6,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     1,     3,     3,     1,     1,
       3,     1,     3,     4,     0,     1,     1
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
       0,     0,     1,     2,     2,     2,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     1,     0,     0,     0,     2,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,  3215,     0,
       0,     0,     0,     0,     0,  3217,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     9,     0,     0,
       0,    11,     0,     0,     0,  3201,  3203,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    13,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    15,     0,     0,     0,     0,  3197,
       0,     0,     0,     0,     0,     0,     0,     0,  3199,     0,
       0,     0,     0,     0,  3209,     0,  3211,  3213,     0,     0,
       0,  3219,     0,  3221,  3223,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3205,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  3225,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       3,     0,     0,     0,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   159,
       0,     0,     0,     0,     0,     0,     0,     0,   161,     0,
       0,     0,     0,   163,   165,     0,     0,     0,   167,     0,
       0,   169,   171,   173,   175,     0,     0,     0,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   179,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   183,   185,     0,     0,
       0,     0,   187,   189,   191,   193,   195,     0,     0,     0,
       0,     0,     0,     0,   197,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   199,     0,   201,   203,   205,   207,
     209,   211,     0,   213,     0,     0,   215,   217,   219,   221,
     223,   225,   227,   229,   231,   233,   235,   237,   239,   241,
     243,   245,   247,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,     0,     0,     0,   251,   253,     0,     0,
       0,   255,     0,     0,   257,   259,   261,   263,     0,     0,
       0,   265,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   267,   269,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   271,
     273,     0,     0,     0,     0,   275,   277,   279,   281,   283,
       0,     0,     0,     0,     0,     0,     0,   285,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   287,     0,   289,
     291,   293,   295,   297,   299,     0,   301,     0,     0,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   321,   323,
     325,   327,   329,   331,   333,   335,     0,     0,     0,     0,
       0,     0,     0,     0,   337,     0,     0,     0,     0,   339,
     341,     0,     0,     0,   343,     0,     0,   345,   347,   349,
     351,     0,     0,     0,   353,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   355,
     357,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   359,   361,     0,     0,     0,     0,   363,   365,
     367,   369,   371,     0,     0,     0,     0,     0,     0,     0,
     373,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     375,     0,   377,   379,   381,   383,   385,   387,     0,   389,
       0,     0,   391,   393,   395,   397,   399,   401,   403,   405,
     407,   409,   411,   413,   415,   417,   419,   421,   423,     0,
       0,     0,     0,     0,     0,     0,     0,   426,     0,     0,
       0,     0,   429,   432,     0,     0,     0,   435,     0,     0,
     438,   441,   444,   447,     0,     0,     0,   450,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   453,   456,     0,     0,     0,   149,     0,     0,
       0,     0,   151,     0,     0,   459,   462,     0,     0,   153,
       0,   465,   468,   471,   474,   477,     0,     0,     0,     0,
       0,     0,     0,   480,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   483,     0,   486,   489,   492,   495,   498,
     501,     0,   504,     0,     0,   507,   510,   513,   516,   519,
     522,   525,   528,   531,   534,   537,   540,   543,   546,   549,
     552,   557,     0,   555,     0,     0,     0,   155,     0,     0,
     559,     0,     0,     0,     0,   561,   563,     0,     0,     0,
     565,     0,     0,   567,   569,   571,   573,     0,     0,     0,
     575,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   577,   579,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   581,   583,
       0,     0,     0,     0,   585,   587,   589,   591,   593,     0,
       0,     0,     0,     0,     0,     0,   595,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   597,     0,   599,   601,
     603,   605,   607,   609,     0,   611,     0,     0,   613,   615,
     617,   619,   621,   623,   625,   627,   629,   631,   633,   635,
     637,   639,   641,   643,   645,     0,     0,     0,     0,     0,
       0,     0,     0,   647,     0,     0,     0,     0,   649,   651,
       0,     0,     0,   653,     0,     0,   655,   657,   659,   661,
       0,     0,     0,   663,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   665,   667,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   669,   671,     0,     0,     0,     0,   673,   675,   677,
     679,   681,     0,     0,     0,     0,     0,     0,     0,   683,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   685,
       0,   687,   689,   691,   693,   695,   697,     0,   699,     0,
       0,   701,   703,   705,   707,   709,   711,   713,   715,   717,
     719,   721,   723,   725,   727,   729,   731,   733,     0,     0,
       0,     0,     0,     0,     0,     0,   735,     0,     0,     0,
       0,   737,   739,     0,     0,     0,   741,     0,     0,   743,
     745,   747,   749,     0,     0,     0,   751,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   753,   755,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   757,   759,     0,     0,     0,     0,
     761,   763,   765,   767,   769,     0,     0,     0,     0,     0,
       0,     0,   771,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   773,     0,   775,   777,   779,   781,   783,   785,
       0,   787,     0,     0,   789,   791,   793,   795,   797,   799,
     801,   803,   805,   807,   809,   811,   813,   815,   817,   819,
     821,     0,     0,     0,     0,     0,     0,     0,     0,   823,
       0,     0,     0,     0,   825,   827,     0,     0,     0,   829,
       0,     0,   831,   833,   835,   837,     0,     0,     0,   839,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   841,   843,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   845,   847,     0,
       0,     0,     0,   849,   851,   853,   855,   857,     0,     0,
       0,     0,     0,     0,     0,   859,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   861,     0,   863,   865,   867,
     869,   871,   873,     0,   875,     0,     0,   877,   879,   881,
     883,   885,   887,   889,   891,   893,   895,   897,   899,   901,
     903,   905,   907,   909,     0,     0,     0,     0,     0,     0,
       0,     0,   911,     0,     0,     0,     0,   913,   915,     0,
       0,     0,   917,     0,     0,   919,   921,   923,   925,     0,
       0,     0,   927,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   929,   931,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     933,   935,     0,     0,     0,     0,   937,   939,   941,   943,
     945,     0,     0,     0,     0,     0,     0,     0,   947,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   949,     0,
     951,   953,   955,   957,   959,   961,     0,   963,     0,     0,
     965,   967,   969,   971,   973,   975,   977,   979,   981,   983,
     985,   987,   989,   991,   993,   995,   997,     0,     0,     0,
       0,     0,     0,     0,     0,   999,     0,     0,     0,     0,
    1001,  1003,     0,     0,     0,  1005,     0,     0,  1007,  1009,
    1011,  1013,     0,     0,     0,  1015,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1017,  1019,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1021,  1023,     0,     0,     0,     0,  1025,
    1027,  1029,  1031,  1033,     0,     0,     0,     0,     0,     0,
       0,  1035,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1037,     0,  1039,  1041,  1043,  1045,  1047,  1049,     0,
    1051,     0,     0,  1053,  1055,  1057,  1059,  1061,  1063,  1065,
    1067,  1069,  1071,  1073,  1075,  1077,  1079,  1081,  1083,  1085,
       0,     0,     0,     0,     0,     0,     0,     0,  1087,     0,
       0,     0,     0,  1089,  1091,     0,     0,     0,  1093,     0,
       0,  1095,  1097,  1099,  1101,     0,     0,     0,  1103,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1105,  1107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1109,  1111,     0,     0,
       0,     0,  1113,  1115,  1117,  1119,  1121,     0,     0,     0,
       0,     0,     0,     0,  1123,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1125,     0,  1127,  1129,  1131,  1133,
    1135,  1137,     0,  1139,     0,     0,  1141,  1143,  1145,  1147,
    1149,  1151,  1153,  1155,  1157,  1159,  1161,  1163,  1165,  1167,
    1169,  1171,  1173,     0,     0,     0,     0,     0,     0,     0,
       0,  1175,     0,     0,     0,     0,  1177,  1179,     0,     0,
       0,  1181,     0,     0,  1183,  1185,  1187,  1189,     0,     0,
       0,  1191,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1193,  1195,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1197,
    1199,     0,     0,     0,     0,  1201,  1203,  1205,  1207,  1209,
       0,     0,     0,     0,     0,     0,     0,  1211,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1213,     0,  1215,
    1217,  1219,  1221,  1223,  1225,     0,  1227,     0,     0,  1229,
    1231,  1233,  1235,  1237,  1239,  1241,  1243,  1245,  1247,  1249,
    1251,  1253,  1255,  1257,  1259,  1261,     0,     0,     0,     0,
       0,     0,     0,     0,  1263,     0,     0,     0,     0,  1265,
    1267,     0,     0,     0,  1269,     0,     0,  1271,  1273,  1275,
    1277,     0,     0,     0,  1279,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1281,
    1283,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1285,  1287,     0,     0,     0,     0,  1289,  1291,
    1293,  1295,  1297,     0,     0,     0,     0,     0,     0,     0,
    1299,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1301,     0,  1303,  1305,  1307,  1309,  1311,  1313,     0,  1315,
       0,     0,  1317,  1319,  1321,  1323,  1325,  1327,  1329,  1331,
    1333,  1335,  1337,  1339,  1341,  1343,  1345,  1347,  1349,     0,
       0,     0,     0,     0,     0,     0,     0,  1351,     0,     0,
       0,     0,  1353,  1355,     0,     0,     0,  1357,     0,     0,
    1359,  1361,  1363,  1365,     0,     0,     0,  1367,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1369,  1371,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1373,  1375,     0,     0,     0,
       0,  1377,  1379,  1381,  1383,  1385,     0,     0,     0,     0,
       0,     0,     0,  1387,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1389,     0,  1391,  1393,  1395,  1397,  1399,
    1401,     0,  1403,     0,     0,  1405,  1407,  1409,  1411,  1413,
    1415,  1417,  1419,  1421,  1423,  1425,  1427,  1429,  1431,  1433,
    1435,  1437,     0,     0,     0,     0,     0,     0,     0,     0,
    1439,     0,     0,     0,     0,  1441,  1443,     0,     0,     0,
    1445,     0,     0,  1447,  1449,  1451,  1453,     0,     0,     0,
    1455,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1457,  1459,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1461,  1463,
       0,     0,     0,     0,  1465,  1467,  1469,  1471,  1473,     0,
       0,     0,     0,     0,     0,     0,  1475,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1477,     0,  1479,  1481,
    1483,  1485,  1487,  1489,     0,  1491,     0,     0,  1493,  1495,
    1497,  1499,  1501,  1503,  1505,  1507,  1509,  1511,  1513,  1515,
    1517,  1519,  1521,  1523,  1525,     0,     0,     0,     0,     0,
       0,     0,     0,  1527,     0,     0,     0,     0,  1529,  1531,
       0,     0,     0,  1533,     0,     0,  1535,  1537,  1539,  1541,
       0,     0,     0,  1543,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1545,  1547,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1549,  1551,     0,     0,     0,     0,  1553,  1555,  1557,
    1559,  1561,     0,     0,     0,     0,     0,     0,     0,  1563,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1565,
       0,  1567,  1569,  1571,  1573,  1575,  1577,     0,  1579,     0,
       0,  1581,  1583,  1585,  1587,  1589,  1591,  1593,  1595,  1597,
    1599,  1601,  1603,  1605,  1607,  1609,  1611,  1613,     0,     0,
       0,     0,     0,     0,     0,     0,  1615,     0,     0,     0,
       0,  1617,  1619,     0,     0,     0,  1621,     0,     0,  1623,
    1625,  1627,  1629,     0,     0,     0,  1631,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1633,  1635,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1637,  1639,     0,     0,     0,     0,
    1641,  1643,  1645,  1647,  1649,     0,     0,     0,     0,     0,
       0,     0,  1651,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1653,     0,  1655,  1657,  1659,  1661,  1663,  1665,
       0,  1667,     0,     0,  1669,  1671,  1673,  1675,  1677,  1679,
    1681,  1683,  1685,  1687,  1689,  1691,  1693,  1695,  1697,  1699,
    1701,     0,     0,     0,     0,     0,     0,     0,     0,  1703,
       0,     0,     0,     0,  1705,  1707,     0,     0,     0,  1709,
       0,     0,  1711,  1713,  1715,  1717,     0,     0,     0,  1719,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1721,  1723,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1725,  1727,     0,
       0,     0,     0,  1729,  1731,  1733,  1735,  1737,     0,     0,
       0,     0,     0,     0,     0,  1739,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1741,     0,  1743,  1745,  1747,
    1749,  1751,  1753,     0,  1755,     0,     0,  1757,  1759,  1761,
    1763,  1765,  1767,  1769,  1771,  1773,  1775,  1777,  1779,  1781,
    1783,  1785,  1787,  1789,     0,     0,     0,     0,     0,     0,
       0,     0,  1791,     0,     0,     0,     0,  1793,  1795,     0,
       0,     0,  1797,     0,     0,  1799,  1801,  1803,  1805,     0,
       0,     0,  1807,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1809,  1811,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1813,  1815,     0,     0,     0,     0,  1817,  1819,  1821,  1823,
    1825,     0,     0,     0,     0,     0,     0,     0,  1827,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1829,     0,
    1831,  1833,  1835,  1837,  1839,  1841,     0,  1843,     0,     0,
    1845,  1847,  1849,  1851,  1853,  1855,  1857,  1859,  1861,  1863,
    1865,  1867,  1869,  1871,  1873,  1875,  1877,     0,     0,     0,
       0,     0,     0,     0,     0,  1879,     0,     0,     0,     0,
    1881,  1883,     0,     0,     0,  1885,     0,     0,  1887,  1889,
    1891,  1893,     0,     0,     0,  1895,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1897,  1899,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1901,  1903,     0,     0,     0,     0,  1905,
    1907,  1909,  1911,  1913,     0,     0,     0,     0,     0,     0,
       0,  1915,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1917,     0,  1919,  1921,  1923,  1925,  1927,  1929,     0,
    1931,     0,     0,  1933,  1935,  1937,  1939,  1941,  1943,  1945,
    1947,  1949,  1951,  1953,  1955,  1957,  1959,  1961,  1963,  1965,
       0,     0,     0,     0,     0,     0,     0,     0,  1967,     0,
       0,     0,     0,  1969,  1971,     0,     0,     0,  1973,     0,
       0,  1975,  1977,  1979,  1981,     0,     0,     0,  1983,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1985,  1987,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1989,  1991,     0,     0,
       0,     0,  1993,  1995,  1997,  1999,  2001,     0,     0,     0,
       0,     0,     0,     0,  2003,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2005,     0,  2007,  2009,  2011,  2013,
    2015,  2017,     0,  2019,     0,     0,  2021,  2023,  2025,  2027,
    2029,  2031,  2033,  2035,  2037,  2039,  2041,  2043,  2045,  2047,
    2049,  2051,  2053,     0,     0,     0,     0,     0,     0,     0,
       0,  2055,     0,     0,     0,     0,  2057,  2059,     0,     0,
       0,  2061,     0,     0,  2063,  2065,  2067,  2069,     0,     0,
       0,  2071,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2073,  2075,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2077,
    2079,     0,     0,     0,     0,  2081,  2083,  2085,  2087,  2089,
       0,     0,     0,     0,     0,     0,     0,  2091,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2093,     0,  2095,
    2097,  2099,  2101,  2103,  2105,     0,  2107,     0,     0,  2109,
    2111,  2113,  2115,  2117,  2119,  2121,  2123,  2125,  2127,  2129,
    2131,  2133,  2135,  2137,  2139,  2141,     0,     0,     0,     0,
       0,     0,     0,     0,  2143,     0,     0,     0,     0,  2145,
    2147,     0,     0,     0,  2149,     0,     0,  2151,  2153,  2155,
    2157,     0,     0,     0,  2159,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2161,
    2163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2165,  2167,     0,     0,     0,     0,  2169,  2171,
    2173,  2175,  2177,     0,     0,     0,     0,     0,     0,     0,
    2179,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2181,     0,  2183,  2185,  2187,  2189,  2191,  2193,     0,  2195,
       0,     0,  2197,  2199,  2201,  2203,  2205,  2207,  2209,  2211,
    2213,  2215,  2217,  2219,  2221,  2223,  2225,  2227,  2229,     0,
       0,     0,     0,     0,     0,     0,     0,  2231,     0,     0,
       0,     0,  2233,  2235,     0,     0,     0,  2237,     0,     0,
    2239,  2241,  2243,  2245,     0,     0,     0,  2247,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2249,  2251,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2253,  2255,     0,     0,     0,
       0,  2257,  2259,  2261,  2263,  2265,     0,     0,     0,     0,
       0,     0,     0,  2267,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2269,     0,  2271,  2273,  2275,  2277,  2279,
    2281,     0,  2283,     0,     0,  2285,  2287,  2289,  2291,  2293,
    2295,  2297,  2299,  2301,  2303,  2305,  2307,  2309,  2311,  2313,
    2315,  2317,     0,     0,     0,     0,     0,     0,     0,     0,
    2319,     0,     0,     0,     0,  2321,  2323,     0,     0,     0,
    2325,     0,     0,  2327,  2329,  2331,  2333,     0,     0,     0,
    2335,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2337,  2339,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2341,  2343,
       0,     0,     0,     0,  2345,  2347,  2349,  2351,  2353,     0,
       0,     0,     0,     0,     0,     0,  2355,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2357,     0,  2359,  2361,
    2363,  2365,  2367,  2369,     0,  2371,     0,     0,  2373,  2375,
    2377,  2379,  2381,  2383,  2385,  2387,  2389,  2391,  2393,  2395,
    2397,  2399,  2401,  2403,  2405,     0,     0,     0,     0,     0,
       0,     0,     0,  2407,     0,     0,     0,     0,  2409,  2411,
       0,     0,     0,  2413,     0,     0,  2415,  2417,  2419,  2421,
       0,     0,     0,  2423,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2425,  2427,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2429,  2431,     0,     0,     0,     0,  2433,  2435,  2437,
    2439,  2441,     0,     0,     0,     0,     0,     0,     0,  2443,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2445,
       0,  2447,  2449,  2451,  2453,  2455,  2457,     0,  2459,     0,
       0,  2461,  2463,  2465,  2467,  2469,  2471,  2473,  2475,  2477,
    2479,  2481,  2483,  2485,  2487,  2489,  2491,  2493,     0,     0,
       0,     0,     0,     0,     0,     0,  2495,     0,     0,     0,
       0,  2497,  2499,     0,     0,     0,  2501,     0,     0,  2503,
    2505,  2507,  2509,     0,     0,     0,  2511,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2513,  2515,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2517,  2519,     0,     0,     0,     0,
    2521,  2523,  2525,  2527,  2529,     0,     0,     0,     0,     0,
       0,     0,  2531,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2533,     0,  2535,  2537,  2539,  2541,  2543,  2545,
       0,  2547,     0,     0,  2549,  2551,  2553,  2555,  2557,  2559,
    2561,  2563,  2565,  2567,  2569,  2571,  2573,  2575,  2577,  2579,
    2581,     0,     0,     0,     0,     0,     0,     0,     0,  2583,
       0,     0,     0,     0,  2585,  2587,     0,     0,     0,  2589,
       0,     0,  2591,  2593,  2595,  2597,     0,     0,     0,  2599,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2601,  2603,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2605,  2607,     0,
       0,     0,     0,  2609,  2611,  2613,  2615,  2617,     0,     0,
       0,     0,     0,     0,     0,  2619,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2621,     0,  2623,  2625,  2627,
    2629,  2631,  2633,     0,  2635,     0,     0,  2637,  2639,  2641,
    2643,  2645,  2647,  2649,  2651,  2653,  2655,  2657,  2659,  2661,
    2663,  2665,  2667,  2669,     0,     0,     0,     0,     0,     0,
       0,     0,  2671,     0,     0,     0,     0,  2673,  2675,     0,
       0,     0,  2677,     0,     0,  2679,  2681,  2683,  2685,     0,
       0,     0,  2687,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2689,  2691,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2693,  2695,     0,     0,     0,     0,  2697,  2699,  2701,  2703,
    2705,     0,     0,     0,     0,     0,     0,     0,  2707,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2709,     0,
    2711,  2713,  2715,  2717,  2719,  2721,     0,  2723,     0,     0,
    2725,  2727,  2729,  2731,  2733,  2735,  2737,  2739,  2741,  2743,
    2745,  2747,  2749,  2751,  2753,  2755,  2757,     0,     0,     0,
       0,     0,     0,     0,     0,  2759,     0,     0,     0,     0,
    2761,  2763,     0,     0,     0,  2765,     0,     0,  2767,  2769,
    2771,  2773,     0,     0,     0,  2775,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2777,  2779,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2781,  2783,     0,     0,     0,     0,  2785,
    2787,  2789,  2791,  2793,     0,     0,     0,     0,     0,     0,
       0,  2795,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2797,     0,  2799,  2801,  2803,  2805,  2807,  2809,     0,
    2811,     0,     0,  2813,  2815,  2817,  2819,  2821,  2823,  2825,
    2827,  2829,  2831,  2833,  2835,  2837,  2839,  2841,  2843,  2845,
       0,     0,     0,     0,     0,     0,     0,     0,  2847,     0,
       0,     0,     0,  2849,  2851,     0,     0,     0,  2853,     0,
       0,  2855,  2857,  2859,  2861,     0,     0,     0,  2863,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2865,  2867,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2869,  2871,     0,     0,
       0,     0,  2873,  2875,  2877,  2879,  2881,     0,     0,     0,
       0,     0,     0,     0,  2883,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2885,     0,  2887,  2889,  2891,  2893,
    2895,  2897,     0,  2899,     0,     0,  2901,  2903,  2905,  2907,
    2909,  2911,  2913,  2915,  2917,  2919,  2921,  2923,  2925,  2927,
    2929,  2931,  2933,     0,     0,     0,     0,     0,     0,     0,
       0,  2935,     0,     0,     0,     0,  2937,  2939,     0,     0,
       0,  2941,     0,     0,  2943,  2945,  2947,  2949,     0,     0,
       0,  2951,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2953,  2955,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2957,
    2959,     0,     0,     0,     0,  2961,  2963,  2965,  2967,  2969,
       0,     0,     0,     0,     0,     0,     0,  2971,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2973,     0,  2975,
    2977,  2979,  2981,  2983,  2985,     0,  2987,     0,     0,  2989,
    2991,  2993,  2995,  2997,  2999,  3001,  3003,  3005,  3007,  3009,
    3011,  3013,  3015,  3017,  3019,  3021,     0,     0,     0,     0,
       0,     0,     0,     0,  3023,     0,     0,     0,     0,  3025,
    3027,     0,     0,     0,  3029,     0,     0,  3031,  3033,  3035,
    3037,     0,     0,     0,  3039,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3041,
    3043,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3045,  3047,     0,     0,     0,     0,  3049,  3051,
    3053,  3055,  3057,     0,     0,     0,     0,     0,     0,     0,
    3059,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3061,     0,  3063,  3065,  3067,  3069,  3071,  3073,     0,  3075,
       0,     0,  3077,  3079,  3081,  3083,  3085,  3087,  3089,  3091,
    3093,  3095,  3097,  3099,  3101,  3103,  3105,  3107,  3109,     0,
       0,     0,     0,     0,     0,     0,     0,  3111,     0,     0,
       0,     0,  3113,  3115,     0,     0,     0,  3117,     0,     0,
    3119,  3121,  3123,  3125,     0,     0,     0,  3127,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3129,  3131,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3133,  3135,     0,     0,     0,
       0,  3137,  3139,  3141,  3143,  3145,     0,     0,     0,     0,
       0,     0,     0,  3147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3149,     0,  3151,  3153,  3155,  3157,  3159,
    3161,     0,  3163,     0,     0,  3165,  3167,  3169,  3171,  3173,
    3175,  3177,  3179,  3181,  3183,  3185,  3187,  3189,  3191,  3193,
    3195,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,    21,    23,
       0,     0,     0,    25,     0,     0,     0,     0,     0,     0,
      27,    29,    31,    33,    35,    37,    39,    41,    43,    45,
      47,    49,     0,    51,    53,    55,    57,    59,    61,    63,
      65,    67,    69,    71,    73,    75,    77,    79,    81,    83,
      85,     0,     0,     0,     0,     0,    87,    89,    91,    93,
      95,    97,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    99,   101,
       0,   103,   105,   107,   109,   111,   113,     0,   115,     0,
       0,   117,   119,   121,   123,   125,   127,   129,   131,   133,
     135,   137,   139,   141,   143,   145,   147,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3227,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3229
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short int yyconfl[] =
{
       0,   386,     0,   386,     0,   386,     0,   386,     0,   377,
       0,   377,     0,   400,     0,   457,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   611,
       0,   611,     0,   611,     0,   611,     0,   611,     0,   386,
       0,   386,     0,   386,     0,   386,     0,   400,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    43,     0,    43,
       0,    43,     0,    43,     0,    43,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,    52,     0,    52,     0,    52,
       0,    52,     0,    52,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   612,     0,   612,     0,   612,     0,   612,
       0,   612,     0,   573,   611,     0,   573,   611,     0,   573,
     611,     0,   573,   611,     0,   573,   611,     0,   573,   611,
       0,   573,   611,     0,   573,   611,     0,   573,   611,     0,
     573,   611,     0,   573,   611,     0,   573,   611,     0,   573,
     611,     0,   573,   611,     0,   573,   611,     0,   573,   611,
       0,   573,   611,     0,   573,   611,     0,   573,   611,     0,
     573,   611,     0,   573,   611,     0,   573,   611,     0,   573,
     611,     0,   573,   611,     0,   573,   611,     0,   573,   611,
       0,   573,   611,     0,   573,   611,     0,   573,   611,     0,
     573,   611,     0,   573,   611,     0,   573,   611,     0,   573,
     611,     0,   573,   611,     0,   573,   611,     0,   573,   611,
       0,   573,   611,     0,   573,   611,     0,   573,   611,     0,
     573,   611,     0,   573,   611,     0,   573,   611,     0,   573,
     611,     0,   573,   611,     0,   611,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,    62,     0,    62,     0,    62,
       0,    62,     0,    62,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   106,     0,   106,     0,   106,     0,   106,
       0,   106,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   107,     0,   107,     0,   107,     0,   107,     0,   107,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   105,
       0,   105,     0,   105,     0,   105,     0,   105,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   103,     0,   103,
       0,   103,     0,   103,     0,   103,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   104,     0,   104,     0,   104,
       0,   104,     0,   104,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   124,     0,   124,     0,   124,     0,   124,
       0,   124,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   126,     0,   126,     0,   126,     0,   126,     0,   126,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   127,
       0,   127,     0,   127,     0,   127,     0,   127,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   128,     0,   128,
       0,   128,     0,   128,     0,   128,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   129,     0,   129,     0,   129,
       0,   129,     0,   129,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   130,     0,   130,     0,   130,     0,   130,
       0,   130,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   131,     0,   131,     0,   131,     0,   131,     0,   131,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   160,
       0,   160,     0,   160,     0,   160,     0,   160,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   581,     0,   581,
       0,   581,     0,   581,     0,   581,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   580,     0,   580,     0,   580,
       0,   580,     0,   580,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   578,     0,   578,     0,   578,     0,   578,
       0,   578,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   576,     0,   576,     0,   576,     0,   576,     0,   576,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   577,
       0,   577,     0,   577,     0,   577,     0,   577,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   579,     0,   579,
       0,   579,     0,   579,     0,   579,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   575,     0,   575,     0,   575,
       0,   575,     0,   575,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   574,     0,   574,     0,   574,     0,   574,
       0,   574,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   582,     0,   582,     0,   582,     0,   582,     0,   582,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   144,
       0,   144,     0,   144,     0,   144,     0,   144,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   610,     0,   610,
       0,   610,     0,   610,     0,   610,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   608,     0,   608,     0,   608,
       0,   608,     0,   608,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   607,     0,   607,     0,   607,     0,   607,
       0,   607,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   609,     0,   609,     0,   609,     0,   609,     0,   609,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   606,
       0,   606,     0,   606,     0,   606,     0,   606,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   605,     0,   605,
       0,   605,     0,   605,     0,   605,     0,   500,     0,   500,
       0,   450,     0,   450,     0,   451,     0,    42,     0,   486,
       0,   486,     0,   486,     0,   612,     0,   386,     0,   561,
       0,   561,     0,   561,     0,   612,     0,   339,     0,   482,
       0
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
        case 284:
#line 452 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		psi_cpp_exp_exec((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 4263 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 285:
#line 458 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if (P->file.ln) {
		P->error(PSI_DATA(P), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), PSI_WARNING,
				"Extra 'lib \"%s\"' statement has no effect", (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	} else {
		P->file.ln = strndup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->size);
	}
}
#line 4276 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 286:
#line 466 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_const(P, (*(struct psi_const **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4284 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 287:
#line 469 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_decl(P, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4292 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 288:
#line 472 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_decl_extvars(P, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4300 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 289:
#line 475 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if (P->flags & PSI_DEBUG) {
		P->error(PSI_DATA(P), (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token, PSI_NOTICE, "Ignored decl: %s", (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name);
	}
	psi_decl_free(&(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4311 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 290:
#line 481 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_typedef(P, (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4319 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 291:
#line 484 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_struct(P, (*(struct psi_decl_struct **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4327 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 292:
#line 487 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_union(P, (*(struct psi_decl_union **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4335 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 293:
#line 490 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4343 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 294:
#line 493 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_parser_proc_add_impl(P, (*(struct psi_impl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4351 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 295:
#line 499 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4359 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 296:
#line 505 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4367 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 297:
#line 508 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = (*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4375 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 298:
#line 514 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 4403 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 299:
#line 537 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4412 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 300:
#line 541 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4421 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 301:
#line 545 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4431 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 302:
#line 550 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_cpp_macro_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4440 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 303:
#line 554 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4449 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 304:
#line 558 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4458 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 305:
#line 562 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4467 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 322:
#line 606 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4477 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 323:
#line 611 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 4487 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 324:
#line 616 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_num_exp_tokens((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4497 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 325:
#line 621 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_token_free);
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_plist_add(list, &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4508 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 326:
#line 630 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL);
}
#line 4516 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 327:
#line 633 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL); /* FIXME */
}
#line 4524 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 329:
#line 637 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4532 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 330:
#line 643 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4542 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 331:
#line 648 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4552 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 332:
#line 656 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4560 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 334:
#line 663 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4569 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 335:
#line 667 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4578 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 336:
#line 674 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4587 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 337:
#line 678 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4596 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 338:
#line 682 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4605 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 339:
#line 686 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4614 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 340:
#line 691 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 4630 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 341:
#line 702 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 4646 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 342:
#line 713 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4656 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 343:
#line 718 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4666 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 344:
#line 723 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4675 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 345:
#line 727 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4686 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 346:
#line 733 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4698 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 347:
#line 743 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4706 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 349:
#line 750 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free), 
		&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4715 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 350:
#line 754 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4723 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 351:
#line 760 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4732 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 352:
#line 767 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4741 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 353:
#line 771 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init(PSI_T_NUMBER, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4750 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 354:
#line 775 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4759 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 358:
#line 788 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4767 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 359:
#line 802 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4775 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 360:
#line 808 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4783 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 361:
#line 811 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4791 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 362:
#line 817 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4799 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 363:
#line 820 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4807 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 365:
#line 827 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4820 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 366:
#line 835 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 4836 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 367:
#line 846 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 4850 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 368:
#line 855 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 4864 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 370:
#line 868 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4873 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 371:
#line 872 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_ENUM, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->name),
		psi_decl_var_init(NULL, 0, 0)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.enm = (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4888 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 372:
#line 882 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 4902 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 373:
#line 891 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 4916 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 375:
#line 904 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4924 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 376:
#line 907 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4932 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 379:
#line 918 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4941 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 381:
#line 926 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4951 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 382:
#line 931 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4961 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 383:
#line 936 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4971 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 386:
#line 946 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4979 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 387:
#line 949 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4987 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 388:
#line 955 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4995 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 389:
#line 958 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5003 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 390:
#line 961 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5011 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 393:
#line 972 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5019 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 394:
#line 975 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5027 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 395:
#line 978 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5035 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 396:
#line 984 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5043 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 397:
#line 987 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5051 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 398:
#line 990 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5064 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 399:
#line 998 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
}
#line 5078 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 400:
#line 1010 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5086 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 401:
#line 1013 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5094 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 402:
#line 1016 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5102 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 403:
#line 1019 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5114 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 404:
#line 1026 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5122 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 405:
#line 1029 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5134 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 406:
#line 1039 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5142 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 408:
#line 1045 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5150 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 412:
#line 1054 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5158 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 413:
#line 1057 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5166 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 414:
#line 1060 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5179 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 415:
#line 1071 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = strdup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5191 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 416:
#line 1078 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = strdup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5203 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 417:
#line 1088 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5211 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 418:
#line 1091 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5219 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 419:
#line 1097 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5227 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 420:
#line 1100 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat("", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	free((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5236 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 421:
#line 1107 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_decl_extvar_free);
	
	if ((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		size_t i = 0;
		struct psi_decl_var *var;
		
		while (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), i++, &var)) {
			if (psi_decl_extvar_is_blacklisted(var->name)) {
				psi_decl_var_free(&var);
			} else {
				list = psi_plist_add(list, psi_decl_extvar_init(
					psi_decl_arg_init(psi_decl_type_copy((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type), var)));
				}
		}
		free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
	
	if (psi_decl_extvar_is_blacklisted((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->var->name)) {
		psi_decl_arg_free(&(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	} else {
		struct psi_decl_extvar *evar = psi_decl_extvar_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
		list = psi_plist_add(list, &evar);
	}
	
	(*(struct psi_plist **)(&(*yyvalp))) = list;
}
#line 5268 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 422:
#line 1137 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5276 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 423:
#line 1140 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5284 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 424:
#line 1146 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5292 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 425:
#line 1149 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5300 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 426:
#line 1155 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5308 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 427:
#line 1158 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5316 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 428:
#line 1161 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5324 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 429:
#line 1164 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5332 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 436:
#line 1185 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_decl **)(&(*yyvalp)))->abi = psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 5341 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 439:
#line 1197 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5353 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 440:
#line 1204 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5366 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 441:
#line 1215 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5378 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 442:
#line 1222 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5391 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 443:
#line 1230 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	
	struct psi_token *type_token = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval))), 1, "rval");
	struct psi_decl_arg *rval_func = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval)), psi_decl_var_init(type_token->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval)), 0));
	struct psi_decl *rval_decl = psi_decl_init(rval_func, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	
	rval_func->var->token = psi_token_copy(type_token);
	rval_func->token = psi_token_copy(type_token);
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		rval_func->var->pointer_level += 1;
		rval_func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
	
	struct psi_decl_type *type = psi_decl_type_init(PSI_T_FUNCTION, type_token->text);
	struct psi_decl_arg *func = psi_decl_arg_init(type, psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval))->text, 1, 0));
	
	type->real.func = rval_decl;
	func->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)));
	func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)));
	
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(func, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	
}
#line 5421 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 444:
#line 1258 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5433 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 445:
#line 1265 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5446 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 446:
#line 1276 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5458 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 447:
#line 1322 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5469 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 449:
#line 1378 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5477 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 450:
#line 1381 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5485 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 451:
#line 1384 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5493 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 452:
#line 1390 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5501 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 453:
#line 1393 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5509 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 454:
#line 1399 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	char digest[17];
	struct psi_token *name;

	psi_token_hash((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func	->token, digest);
	name = psi_token_append("@", psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token), 2, "funct", digest);
	
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, name->text),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = name;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5529 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 455:
#line 1414 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5537 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 456:
#line 1417 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0)
	);
}
#line 5548 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 457:
#line 1446 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5561 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 458:
#line 1454 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5569 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 459:
#line 1482 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)) + !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5579 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 460:
#line 1487 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5589 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 461:
#line 1495 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_union **)(&(*yyvalp))) = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_union **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_union **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_union **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5601 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 462:
#line 1505 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_struct **)(&(*yyvalp))) = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_struct **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5613 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 463:
#line 1515 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5621 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 465:
#line 1522 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5629 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 466:
#line 1528 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 5648 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 467:
#line 1542 "src/parser_proc_grammar.y" /* glr.c:816  */
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
#line 5667 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 468:
#line 1559 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5675 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 469:
#line 1562 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5683 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 470:
#line 1568 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 5695 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 471:
#line 1575 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 5707 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 472:
#line 1585 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_decl_enum **)(&(*yyvalp))) = psi_decl_enum_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
}
#line 5716 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 473:
#line 1592 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5724 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 474:
#line 1595 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5732 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 475:
#line 1601 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, NULL);
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5742 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 476:
#line 1606 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5752 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 477:
#line 1614 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5761 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 478:
#line 1618 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_cast((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->token);
}
#line 5770 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 479:
#line 1622 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary(PSI_T_LPAREN, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5779 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 480:
#line 1626 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5788 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 481:
#line 1630 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5797 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 482:
#line 1634 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 5806 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 483:
#line 1641 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5815 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 484:
#line 1645 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5824 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 485:
#line 1649 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5833 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 486:
#line 1653 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5842 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 487:
#line 1657 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_NAME, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5851 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 488:
#line 1661 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5859 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 489:
#line 1667 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 5868 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 490:
#line 1671 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5877 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 491:
#line 1678 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5885 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 492:
#line 1681 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		int8_t sizeof_void_p = sizeof(void *);
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
		psi_decl_type_free(&(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_SIZEOF, (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 0);
	}
}
#line 5899 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 493:
#line 1693 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	int8_t sizeof_void_p = sizeof(void *);
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
}
#line 5908 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 494:
#line 1697 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	int8_t sizeof_a = sizeof('a');
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_a, 0);
}
#line 5917 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 495:
#line 1701 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	uint64_t len = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->size + 1;
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_UINT64, &len, 0);
}
#line 5926 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 496:
#line 1708 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 5941 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 497:
#line 1721 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 5956 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 498:
#line 1734 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 5971 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 499:
#line 1747 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5979 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 500:
#line 1750 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&(*yyvalp)))->type = PSI_T_NAME;
}
#line 5988 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 503:
#line 1762 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = NULL;
}
#line 5996 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 504:
#line 1765 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(0, 0, psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text), NULL));
}
#line 6004 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 505:
#line 1768 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text), NULL);
}
#line 6012 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 506:
#line 1771 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text), psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval))->text), NULL));
}
#line 6020 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 507:
#line 1777 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = 0;
	(*(struct psi_layout*)(&(*yyvalp))).len = 0;
}
#line 6029 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 508:
#line 1781 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text);
	(*(struct psi_layout*)(&(*yyvalp))).len = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 6038 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 509:
#line 1788 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6046 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 510:
#line 1791 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6054 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 511:
#line 1794 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	struct psi_validate_scope scope = {0};
	psi_validate_scope_ctor(&scope);
	scope.defs = &P->preproc->defs;
	if (psi_num_exp_validate(PSI_DATA(P), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &scope)) {
		(*(size_t*)(&(*yyvalp))) = psi_num_exp_get_long((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), NULL, &P->preproc->defs);
	} else {
		(*(size_t*)(&(*yyvalp))) = 0;
	}
	psi_num_exp_free(&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	psi_validate_scope_dtor(&scope);
}
#line 6071 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 516:
#line 1816 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6079 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 517:
#line 1819 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6087 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 519:
#line 1826 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6095 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 520:
#line 1832 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = 1;
}
#line 6103 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 521:
#line 1835 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)) + 1;
}
#line 6111 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 526:
#line 1857 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6119 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 527:
#line 1860 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6128 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 528:
#line 1867 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, NULL, (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
}
#line 6138 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 529:
#line 1872 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval));
}
#line 6148 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 530:
#line 1877 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval));
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6160 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 531:
#line 1887 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6168 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 532:
#line 1890 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6176 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 533:
#line 1896 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
}
#line 6184 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 534:
#line 1899 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6192 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 535:
#line 1905 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_var **)(&(*yyvalp))) = psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6201 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 536:
#line 1912 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6210 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 537:
#line 1919 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6219 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 549:
#line 1946 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6227 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 550:
#line 1949 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6235 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 551:
#line 1955 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_return_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6243 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 552:
#line 1958 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_let_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6251 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 553:
#line 1961 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_set_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6259 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 554:
#line 1964 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_assert_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6267 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 555:
#line 1967 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_free_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6275 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 556:
#line 1973 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init((*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6284 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 557:
#line 1977 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init(psi_let_exp_init_ex((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), PSI_LET_TMP, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->exp->is_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6294 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 559:
#line 1986 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = true;
}
#line 6303 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 560:
#line 1990 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = false;
}
#line 6312 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 561:
#line 1997 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 6320 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 562:
#line 2000 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6328 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 563:
#line 2003 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6336 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 564:
#line 2006 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6345 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 565:
#line 2010 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLBACK, (*(struct psi_let_callback **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6353 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 566:
#line 2013 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, (*(struct psi_let_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6361 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 567:
#line 2019 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6370 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 568:
#line 2023 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = 1;
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 6380 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 569:
#line 2031 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_calloc **)(&(*yyvalp))) = psi_let_calloc_init((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 6389 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 570:
#line 2038 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)));
}
#line 6399 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 571:
#line 2043 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval)));
}
#line 6409 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 572:
#line 2051 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_let_func **)(&(*yyvalp))) = psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6419 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 583:
#line 2072 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6427 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 584:
#line 2075 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6435 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 585:
#line 2081 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6443 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 586:
#line 2084 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6451 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 589:
#line 2095 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6459 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 590:
#line 2098 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6467 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 591:
#line 2104 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6475 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 592:
#line 2107 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6483 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 593:
#line 2113 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_return_stmt **)(&(*yyvalp))) = psi_return_stmt_init((*(struct psi_return_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_return_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6492 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 594:
#line 2120 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->token);
}
#line 6501 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 595:
#line 2124 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init(NULL, NULL, psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 6510 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 596:
#line 2131 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6518 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 597:
#line 2134 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6526 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 598:
#line 2137 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6534 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 599:
#line 2143 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_stmt **)(&(*yyvalp))) = psi_set_stmt_init((*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_set_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6543 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 600:
#line 2150 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6551 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 601:
#line 2153 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6559 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 602:
#line 2156 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = (*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_set_exp **)(&(*yyvalp)))->var = (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6568 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 603:
#line 2163 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6578 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 604:
#line 2168 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->recursive = 1;
}
#line 6588 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 613:
#line 2187 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6596 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 614:
#line 2190 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6604 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 615:
#line 2196 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6612 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 616:
#line 2199 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6620 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 617:
#line 2205 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_assert_stmt **)(&(*yyvalp))) = psi_assert_stmt_init((enum psi_assert_kind) (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_assert_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6629 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 620:
#line 2217 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_free_stmt **)(&(*yyvalp))) = psi_free_stmt_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6638 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 621:
#line 2224 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6646 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 622:
#line 2227 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6654 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 623:
#line 2233 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_free_exp **)(&(*yyvalp))) = psi_free_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6664 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 624:
#line 2241 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = false;
}
#line 6672 "src/parser_proc.c" /* glr.c:816  */
    break;

  case 625:
#line 2244 "src/parser_proc_grammar.y" /* glr.c:816  */
    {
	(*(bool*)(&(*yyvalp))) = true;
}
#line 6680 "src/parser_proc.c" /* glr.c:816  */
    break;


#line 6684 "src/parser_proc.c" /* glr.c:816  */
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
          case 141: /* binary_op_token  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6735 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 142: /* unary_op_token  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6741 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 143: /* name_token  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6747 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 144: /* any_noeol_token  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6753 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 149: /* lib  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6759 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 150: /* cpp  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 6765 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 151: /* cpp_exp  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 6771 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 153: /* cpp_message_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6777 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 154: /* cpp_include_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6783 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 155: /* cpp_header_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6789 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 156: /* cpp_no_arg_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6795 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 157: /* cpp_name_arg_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6801 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 158: /* cpp_exp_arg_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6807 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 159: /* cpp_macro_decl  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_cpp_macro_decl_free(&(*(struct psi_cpp_macro_decl **)(&(*yyvaluep))));}
#line 6813 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 160: /* cpp_macro_sig  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6819 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 161: /* cpp_macro_sig_args  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6825 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 162: /* cpp_macro_decl_tokens  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6831 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 163: /* cpp_macro_decl_token_list  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6837 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 164: /* cpp_macro_exp  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 6843 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 165: /* cpp_macro_call_args  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6849 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 166: /* cpp_macro_call_arg_list  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6855 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 167: /* constant  */
#line 336 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_const_free(&(*(struct psi_const **)(&(*yyvaluep))));}
#line 6861 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 168: /* impl_def_val  */
#line 338 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_def_val_free(&(*(struct psi_impl_def_val **)(&(*yyvaluep))));}
#line 6867 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 169: /* impl_def_val_token  */
#line 333 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6873 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 170: /* decl_typedef  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 6879 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 171: /* typedef  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 6885 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 172: /* typedef_anon  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 6891 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 173: /* typedef_decl  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 6897 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 174: /* typedef_anon_decl  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 6903 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 175: /* qualified_decl_type  */
#line 347 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 6909 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 177: /* decl_type  */
#line 347 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 6915 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 178: /* decl_type_complex  */
#line 347 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 6921 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 179: /* decl_type_simple  */
#line 341 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6927 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 180: /* decl_real_type  */
#line 341 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6933 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 181: /* int_signed  */
#line 321 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6939 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 182: /* int_width  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6945 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 183: /* decl_int_type  */
#line 341 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6951 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 184: /* int_signed_types  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6957 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 185: /* signed_short_types  */
#line 321 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6963 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 186: /* signed_long_types  */
#line 321 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 6969 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 187: /* int_width_types  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6975 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 188: /* decl_stmt  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 6981 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 189: /* decl_asm  */
#line 344 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6987 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 190: /* quoted_strings  */
#line 344 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 6993 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 191: /* decl_extvar_stmt  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6999 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 192: /* decl_extvar_list  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7005 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 193: /* decl_vars  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7011 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 194: /* ignored_decl  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7017 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 198: /* decl  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7023 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 199: /* decl_body  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7029 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 200: /* decl_func_body  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7035 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 201: /* decl_functor_body  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7041 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 202: /* decl_anon_functor_body  */
#line 349 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7047 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 203: /* decl_functor  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7053 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 204: /* decl_anon_functor  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7059 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 205: /* decl_func  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7065 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 206: /* decl_args  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7071 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 207: /* decl_arg_list  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7077 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 208: /* decl_anon_arg  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7083 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 209: /* decl_arg  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7089 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 210: /* decl_var  */
#line 353 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_var_free(&(*(struct psi_decl_var **)(&(*yyvaluep))));}
#line 7095 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 211: /* decl_union  */
#line 357 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_union_free(&(*(struct psi_decl_union **)(&(*yyvaluep))));}
#line 7101 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 212: /* decl_struct  */
#line 355 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_struct_free(&(*(struct psi_decl_struct **)(&(*yyvaluep))));}
#line 7107 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 213: /* decl_struct_args  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7113 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 214: /* struct_args_block  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7119 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 215: /* struct_args  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7125 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 216: /* struct_arg_var_list  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7131 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 217: /* decl_vars_with_layout  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7137 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 218: /* decl_enum  */
#line 359 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_free(&(*(struct psi_decl_enum **)(&(*yyvaluep))));}
#line 7143 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 219: /* decl_enum_items  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7149 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 220: /* decl_enum_item  */
#line 361 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_decl_enum_item_free(&(*(struct psi_decl_enum_item **)(&(*yyvaluep))));}
#line 7155 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 221: /* num_exp  */
#line 419 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 7161 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 222: /* number  */
#line 421 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7167 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 223: /* sizeof  */
#line 371 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7173 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 224: /* sizeof_body  */
#line 371 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7179 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 225: /* sizeof_body_notypes  */
#line 371 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7185 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 226: /* enum_name  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7191 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 227: /* union_name  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7197 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 228: /* struct_name  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7203 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 229: /* optional_name  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7209 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 231: /* decl_layout  */
#line 368 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_layout_free(&(*(struct psi_layout **)(&(*yyvaluep))));}
#line 7215 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 232: /* align_and_size  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7221 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 233: /* array_size  */
#line 424 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7227 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 235: /* indirection  */
#line 424 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7233 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 236: /* pointers  */
#line 424 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7239 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 237: /* asterisks  */
#line 424 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7245 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 240: /* impl  */
#line 374 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_free(&(*(struct psi_impl **)(&(*yyvaluep))));}
#line 7251 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 241: /* impl_func  */
#line 376 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_func_free(&(*(struct psi_impl_func **)(&(*yyvaluep))));}
#line 7257 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 242: /* impl_args  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7263 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 243: /* impl_arg  */
#line 378 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_arg_free(&(*(struct psi_impl_arg **)(&(*yyvaluep))));}
#line 7269 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 244: /* impl_var  */
#line 382 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_var_free(&(*(struct psi_impl_var **)(&(*yyvaluep))));}
#line 7275 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 245: /* impl_type  */
#line 380 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7281 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 246: /* impl_type_restricted  */
#line 380 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7287 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 247: /* impl_type_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7293 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 248: /* impl_type_restricted_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7299 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 249: /* impl_type_extended_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7305 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 250: /* impl_stmts  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7311 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 251: /* impl_stmt  */
#line 412 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_impl_stmt_free(&(*(struct psi_token ***)(&(*yyvaluep))));}
#line 7317 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 252: /* let_stmt  */
#line 385 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_stmt_free(&(*(struct psi_let_stmt **)(&(*yyvaluep))));}
#line 7323 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 253: /* let_exp  */
#line 387 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7329 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 254: /* let_exp_byref  */
#line 387 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7335 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 255: /* let_exp_assign  */
#line 387 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7341 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 256: /* let_calloc  */
#line 389 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_calloc_free(&(*(struct psi_let_calloc **)(&(*yyvaluep))));}
#line 7347 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 257: /* let_callback  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_callback_free(&(*(struct psi_let_callback **)(&(*yyvaluep))));}
#line 7353 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 258: /* let_func  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_let_func_free(&(*(struct psi_let_func **)(&(*yyvaluep))));}
#line 7359 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 259: /* let_func_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7365 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 260: /* let_func_exps  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7371 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 261: /* let_exps  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7377 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 262: /* callback_rval  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7383 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 263: /* callback_arg_list  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7389 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 264: /* callback_args  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7395 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 265: /* return_stmt  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_return_stmt_free(&(*(struct psi_return_stmt **)(&(*yyvaluep))));}
#line 7401 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 266: /* return_exp  */
#line 405 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_return_exp_free(&(*(struct psi_return_exp **)(&(*yyvaluep))));}
#line 7407 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 267: /* call_decl_vars  */
#line 363 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7413 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 268: /* set_stmt  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_stmt_free(&(*(struct psi_set_stmt **)(&(*yyvaluep))));}
#line 7419 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 269: /* set_exp  */
#line 397 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_exp_free(&(*(struct psi_set_exp **)(&(*yyvaluep))));}
#line 7425 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 270: /* set_func  */
#line 399 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_set_func_free(&(*(struct psi_set_func **)(&(*yyvaluep))));}
#line 7431 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 271: /* set_func_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7437 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 272: /* set_func_exps  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7443 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 273: /* set_exps  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7449 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 274: /* assert_stmt  */
#line 401 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_assert_stmt_free(&(*(struct psi_assert_stmt **)(&(*yyvaluep))));}
#line 7455 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 275: /* assert_stmt_token  */
#line 414 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7461 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 276: /* free_stmt  */
#line 407 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_stmt_free(&(*(struct psi_free_stmt **)(&(*yyvaluep))));}
#line 7467 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 277: /* free_exps  */
#line 416 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7473 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 278: /* free_exp  */
#line 409 "src/parser_proc_grammar.y" /* glr.c:846  */
      {psi_free_exp_free(&(*(struct psi_free_exp **)(&(*yyvaluep))));}
#line 7479 "src/parser_proc.c" /* glr.c:846  */
        break;

    case 279: /* reference  */
#line 426 "src/parser_proc_grammar.y" /* glr.c:846  */
      {}
#line 7485 "src/parser_proc.c" /* glr.c:846  */
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
  (!!((Yystate) == (-714)))

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
  #line 144 "src/parser_proc_grammar.y" /* glr.c:2270  */
{
}

#line 8838 "src/parser_proc.c" /* glr.c:2270  */

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

#line 2253 "src/parser_proc_grammar.y" /* glr.c:2584  */


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

