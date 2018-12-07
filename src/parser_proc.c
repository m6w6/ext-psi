/* A Bison parser, made by GNU Bison 3.2.  */

/* Skeleton implementation for Bison GLR parsers in C

   Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "glr.c"

/* Pure parsers.  */
#define YYPURE 1


/* "%code top" blocks.  */
#line 1 "src/parser_proc_grammar.y" /* glr.c:221  */

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#line 61 "src/parser_proc.c" /* glr.c:221  */


/* Substitute the variable and function names.  */
#define yyparse psi_parser_proc_parse
#define yylex   psi_parser_proc_lex
#define yyerror psi_parser_proc_error
#define yydebug psi_parser_proc_debug




# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
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


/* Unqualified %code blocks.  */
#line 9 "src/parser_proc_grammar.y" /* glr.c:261  */

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

#line 188 "src/parser_proc.c" /* glr.c:261  */

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
# define yytrue true
# define yyfalse false
#else
  /* When we move to stdbool, get rid of the various casts to yybool.  */
  typedef unsigned char yybool;
# define yytrue 1
# define yyfalse 0
#endif

#ifndef YYSETJMP
# include <setjmp.h>
# define YYJMP_BUF jmp_buf
# define YYSETJMP(Env) setjmp (Env)
/* Pacify Clang and ICC.  */
# define YYLONGJMP(Env, Val)                    \
 do {                                           \
   longjmp (Env, Val);                          \
   YYASSERT (0);                                \
 } while (yyfalse)
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

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  166
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   8213

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  140
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  142
/* YYNRULES -- Number of rules.  */
#define YYNRULES  637
/* YYNRULES -- Number of states.  */
#define YYNSTATES  950
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 16
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   394

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
static const unsigned short yyrline[] =
{
       0,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     413,   413,   413,   413,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   415,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     416,   416,   416,   416,   416,   416,   416,   416,   416,   416,
     420,   421,   424,   425,   428,   429,   430,   431,   437,   441,
     444,   447,   450,   456,   459,   462,   465,   468,   474,   480,
     483,   489,   512,   516,   520,   525,   529,   533,   537,   544,
     545,   549,   550,   554,   555,   556,   560,   561,   565,   566,
     570,   571,   572,   576,   577,   581,   586,   591,   596,   605,
     608,   611,   612,   618,   623,   631,   634,   638,   642,   649,
     653,   657,   661,   666,   677,   688,   693,   698,   702,   708,
     719,   722,   726,   734,   738,   744,   748,   755,   759,   763,
     770,   771,   772,   776,   790,   796,   799,   805,   808,   814,
     815,   823,   834,   843,   855,   856,   860,   870,   879,   891,
     892,   895,   901,   902,   906,   910,   914,   919,   924,   932,
     933,   934,   937,   943,   946,   949,   955,   956,   960,   963,
     966,   972,   975,   978,   986,   998,  1001,  1004,  1007,  1014,
    1017,  1027,  1030,  1033,  1036,  1037,  1038,  1042,  1045,  1048,
    1059,  1066,  1076,  1079,  1085,  1088,  1095,  1131,  1134,  1140,
    1143,  1149,  1155,  1156,  1157,  1158,  1159,  1160,  1164,  1168,
    1169,  1173,  1174,  1178,  1179,  1186,  1187,  1191,  1198,  1209,
    1216,  1224,  1248,  1277,  1284,  1295,  1341,  1382,  1397,  1400,
    1403,  1409,  1412,  1418,  1433,  1436,  1465,  1473,  1501,  1506,
    1514,  1524,  1534,  1537,  1541,  1547,  1561,  1578,  1581,  1587,
    1594,  1601,  1609,  1620,  1627,  1630,  1636,  1641,  1649,  1653,
    1657,  1661,  1665,  1669,  1676,  1680,  1684,  1688,  1692,  1696,
    1702,  1706,  1713,  1716,  1728,  1732,  1736,  1743,  1756,  1769,
    1782,  1785,  1792,  1793,  1797,  1800,  1803,  1806,  1812,  1816,
    1823,  1826,  1829,  1844,  1845,  1846,  1847,  1851,  1854,  1860,
    1861,  1867,  1870,  1876,  1877,  1881,  1882,  1892,  1895,  1902,
    1907,  1912,  1922,  1925,  1931,  1934,  1940,  1947,  1954,  1961,
    1962,  1966,  1967,  1968,  1969,  1970,  1974,  1975,  1976,  1977,
    1981,  1984,  1990,  1993,  1996,  1999,  2002,  2008,  2012,  2020,
    2021,  2025,  2032,  2035,  2038,  2041,  2045,  2048,  2054,  2058,
    2066,  2073,  2078,  2086,  2094,  2095,  2096,  2097,  2098,  2099,
    2100,  2101,  2102,  2103,  2107,  2110,  2116,  2119,  2125,  2126,
    2130,  2133,  2139,  2142,  2148,  2155,  2159,  2166,  2169,  2172,
    2178,  2185,  2188,  2191,  2198,  2203,  2211,  2212,  2213,  2214,
    2215,  2216,  2217,  2218,  2222,  2225,  2231,  2234,  2240,  2247,
    2248,  2252,  2259,  2262,  2268,  2276,  2279,  2285
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
  "ignored_decl", "ignored_decl_qualifiers", "ignored_decl_body",
  "ignored_decl_body_stmts", "ignored_decl_body_stmt", "decl", "decl_body",
  "decl_func_body", "decl_functor_body", "decl_anon_functor_body",
  "decl_functor", "decl_anon_functor", "decl_func", "decl_args",
  "decl_arg_list", "decl_anon_arg", "decl_arg", "decl_var", "decl_union",
  "decl_struct", "decl_struct_args", "struct_args_block", "struct_args",
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

#define YYPACT_NINF -731
#define YYTABLE_NINF -636

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short yypact[] =
{
     529,  -731,  -731,  -731,  -731,  -731,   128,  -731,  -731,  -731,
     582,  -731,  -731,  -731,   555,   722,  7975,  7975,  7975,   348,
      77,   -23,    80,  -731,   281,  -731,   132,   529,  -731,  -731,
    -731,  -731,  -731,  7120,   109,  -731,  -731,  -731,  -731,   409,
     161,  -731,  -731,  -731,  -731,   493,    26,  -731,  -731,    30,
      96,   126,  -731,  -731,  -731,  -731,   125,  -731,   142,  -731,
    -731,  -731,  7975,  7975,  7975,  -731,  -731,  -731,   145,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,   861,  -731,  -731,  -731,  -731,   151,   987,   987,    33,
    -731,   987,  6894,  7975,  7975,  1728,   154,  -731,  -731,  -731,
     165,  7975,   164,   164,  -731,  -731,  -731,  -731,  -731,  -731,
    1353,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,   114,  -731,  -731,   114,   181,  -731,  -731,  -731,  -731,
    -731,  -731,   201,   192,  -731,   214,  -731,   218,  -731,   234,
    -731,  1841,   722,   138,  -731,    26,  -731,  -731,    46,   224,
    -731,  -731,   232,  7975,    17,  -731,  -731,  -731,   261,  -731,
     101,  -731,  -731,  -731,   507,  -731,   233,   244,   248,  1954,
    1954,  7975,   230,  -731,  -731,  -731,  7459,    26,  -731,  1693,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  1806,  1919,
    2032,  2145,  -731,  2258,  2371,  -731,  -731,  -731,  2484,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  2597,  2710,  2823,  2936,  3049,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  3162,  -731,  3275,  3388,  3501,  3614,  3727,  3840,  -731,
    3953,  -731,  -731,  4066,  4179,  4292,  4405,  4518,  4631,  4744,
    4857,  4970,  5083,  5196,  5309,  5422,  5535,  5648,  5761,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  5874,   987,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,   987,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,   116,  6894,  -731,
    -731,  -731,  -731,  7572,  6894,   250,  8076,  -731,   111,  -731,
     169,  -731,  -731,  -731,  -731,   245,   247,   247,    91,    91,
    6103,   256,  -731,   230,   252,   266,  -731,   268,  -731,  -731,
    -731,  1467,  -731,   255,   224,  -731,  -731,  -731,  -731,  -731,
     301,  -731,  -731,  1239,  -731,   283,  -731,    52,  7120,  -731,
     279,   173,   284,  -731,  -731,   175,   277,   286,  -731,  7459,
    6555,  7459,  7975,  7459,  -731,  -731,   129,  -731,  -731,  -731,
    -731,  -731,  6781,  -731,   287,  -731,  7975,   299,  -731,   317,
    8076,   307,  -731,  -731,  -731,  -731,   755,   331,  -731,  7108,
    7975,  -731,  -731,  1580,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  6894,  6894,   323,  1420,  7459,  7459,  -731,  -731,
    -731,  -731,   153,  -731,  -731,  -731,  -731,  -731,  5990,  6781,
     325,  -731,   307,  -731,  8100,  -731,  -731,  6103,   179,   427,
    -731,  -731,  -731,  -731,  -731,  -731,  8052,   320,  7685,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    1113,  -731,    76,    56,  1954,   224,   308,   493,   224,   309,
    6781,  7975,   338,   346,   356,  8100,   351,   357,  -731,   360,
     369,   354,   363,   122,  -731,   370,   376,  -731,  -731,  -731,
     769,  7459,  -731,  7744,  -731,   255,   375,  -731,  -731,  -731,
     378,  -731,  8076,   379,   388,  7676,  -731,   398,  1728,   389,
    -731,  -731,  7007,   229,  7975,   164,   164,  -731,  -731,    36,
      38,    47,  7225,  -731,  -731,  6781,  6781,   394,  -731,  -731,
    -731,  -731,  -731,   391,   186,  -731,    80,  -731,  -731,  -731,
    -731,  -731,   255,   180,  -731,  -731,  -731,   255,  -731,   196,
    -731,   399,  -731,  -731,   403,  8100,  -731,  -731,  6216,  -731,
    6555,  -731,  7459,  -731,    80,  7459,  -731,  7975,  7857,  -731,
    -731,  -731,  -731,  -731,   405,   393,  -731,  -731,  -731,  -731,
    6894,  6894,   411,  -731,    71,   412,  -731,   389,   247,   247,
    6781,  -731,  7838,  -731,  -731,   641,   413,   641,   407,  7975,
    1954,  -731,  7233,   224,   392,   224,   224,   158,   350,   238,
     431,  8100,  -731,  -731,  -731,  -731,   434,  6668,  -731,   433,
    7459,   219,  -731,   436,   287,   440,   987,  7916,  8076,  8124,
     449,   441,   443,  7346,   446,   412,  7459,  7459,  -731,  6781,
    -731,   641,  -731,    80,  6103,   448,   452,  -731,  -731,   453,
    -731,  -731,   431,  -731,  -731,  -731,  7857,  -731,   455,  6781,
      80,  -731,  6329,   456,   460,  -731,   395,  -731,  -731,  -731,
     462,   458,   471,   389,   472,  -731,  -731,   474,  8148,  -731,
      48,  -731,   476,   484,   224,   488,    80,  7563,   489,   491,
    -731,   492,  -731,  -731,    61,  -731,   495,   494,  -731,  7346,
    -731,   506,  1954,   500,  -731,   445,   511,  6781,  6216,   512,
    -731,  6555,  -731,  -731,   515,   519,   523,   389,  -731,   516,
     520,  1954,   276,  6442,  7442,   346,  -731,  -731,  -731,   518,
    6668,  -731,  -731,   522,   521,  -731,   526,   524,   530,   534,
     535,   528,  -731,  -731,  6216,  -731,   542,  -731,   641,   537,
     224,    80,   538,  6555,  -731,   539,  -731,  1954,  -731,   541,
    -731,  -731,  -731,   543,  6442,   224,   548,  -731,   549,  -731
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short yydefact[] =
{
     280,   401,   398,   402,   396,   397,   399,   393,   394,   392,
     391,   383,   285,   284,     0,     0,     0,     0,   510,   382,
       0,   432,   635,   286,     0,   436,     0,   281,   282,   288,
     287,   289,   293,   527,     0,   379,   385,   384,   390,   405,
     417,   389,   290,   291,   292,     0,   422,   443,   445,   446,
       0,     0,   457,   295,   294,   296,     0,   297,     0,   400,
     395,   391,     0,     0,     0,   382,   437,   444,   427,   299,
     310,   307,   309,   311,   312,   323,   320,   321,   318,   324,
     319,     0,   322,   313,   314,   315,     0,   335,   335,     0,
     303,     0,     0,   510,   510,     0,     0,   365,   370,   466,
     369,     0,   518,   518,    33,    34,    35,    36,    37,   623,
     584,    24,    42,    41,    40,    38,    39,    32,    31,    25,
      29,    28,    26,    27,    43,   592,   591,   589,   587,   588,
     590,   586,   585,   593,    30,   621,   619,   618,   620,   617,
     616,   386,    44,    45,   387,   388,   507,   551,   552,   553,
     554,   555,     0,     0,   548,     0,   433,     0,   637,     0,
     636,   391,     0,     0,   434,   422,     1,   283,   533,   520,
     381,   467,     0,   528,   529,   531,   380,   407,   411,   409,
     413,   406,   403,   418,   405,   404,     0,     0,     0,   458,
     458,     0,     0,   386,   387,   388,     0,   422,    71,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,   161,   162,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     111,   109,   110,   108,   106,   107,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     163,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   159,   156,   157,   158,   160,     0,   335,   305,   300,
      46,    55,    56,    57,    58,    60,    61,    65,   109,   110,
     108,   106,   107,   127,   129,   130,   131,   132,   133,   134,
     163,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   337,   308,   336,
     301,   316,   317,   302,   304,   345,   346,     0,     0,    22,
      23,    20,    21,     0,     0,   348,   306,   347,   386,   509,
     387,   508,   366,   363,   371,     0,     0,     0,     0,     0,
       0,     0,   298,     0,     0,     0,   435,     0,   536,   535,
     534,   523,   469,   527,   520,   530,   532,   412,   408,   414,
     415,   410,   419,     0,   431,     0,   420,   392,   527,   463,
       0,     0,   460,   461,   464,     0,   486,   512,   484,     0,
     635,     0,     0,     0,   629,   630,     0,   560,   563,   562,
     564,   565,     0,   566,   428,   429,     0,     0,   424,     0,
     327,   328,   325,   338,   506,   505,     0,     0,   501,     0,
       0,   343,   340,   350,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    13,    12,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,   472,   471,
     473,   470,   497,   361,   362,   495,   494,   496,     0,     0,
       0,   357,   359,   498,   358,   488,   499,     0,     0,     0,
     364,   421,   497,   525,   526,   524,     0,     0,     0,   528,
     468,   416,   189,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   277,   278,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
     200,   201,   202,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,   218,   219,
     220,   221,   227,   225,   226,   224,   222,   223,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   279,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   275,   272,   273,   274,   276,   441,   442,
       0,   439,     0,   520,   458,   520,     0,     0,   520,     0,
       0,   513,     0,     0,     0,   612,     0,     0,   611,    45,
       0,     0,     0,     0,   632,     0,     0,   606,   537,   561,
       0,     0,   426,   329,   425,   527,     0,   502,   504,   339,
       0,   352,   353,     0,   351,     0,   341,     0,     0,   514,
     374,   367,   375,     0,   376,   518,   518,   373,   372,   623,
      24,     0,     0,   492,   356,     0,     0,     0,   538,   557,
     558,   559,   556,     0,     0,   542,   635,   547,   549,   550,
     522,   521,   527,     0,   438,   440,   423,   527,   465,     0,
     449,     0,   462,   447,     0,   487,   485,   483,     0,   567,
     635,   610,     0,   546,   635,     0,   631,     0,   607,   604,
     628,   430,   330,   333,     0,   331,   503,   500,   344,   349,
       0,     0,     0,   368,     0,   477,   474,   514,     0,     0,
       0,   490,     0,   491,   355,     0,     0,     0,   544,     0,
     458,   455,     0,   520,     0,   520,   520,   497,     0,    31,
      30,   573,   578,   574,   576,   577,    44,     0,   613,   624,
       0,     0,   633,   623,   609,     0,   335,     0,   354,   342,
       0,   515,     0,   514,     0,   477,   378,   377,   489,     0,
     539,     0,   543,   635,     0,     0,     0,   456,   453,     0,
     450,   448,     0,   575,   598,   584,   607,   599,     0,     0,
     635,   579,   635,     0,     0,   634,     0,   326,   332,   334,
       0,     0,     0,   514,   478,   481,   475,     0,   493,   540,
       0,   545,     0,     0,   520,     0,   635,     0,   594,     0,
     626,   625,   614,   568,     0,   519,     0,     0,   479,   514,
     476,     0,   458,     0,   454,     0,     0,     0,     0,     0,
     615,   635,   622,   605,     0,     0,     0,   514,   482,     0,
       0,   458,     0,   600,     0,   498,   596,   571,   569,   595,
       0,   583,   627,     0,     0,   480,     0,     0,     0,     0,
       0,   601,   602,   580,     0,   570,     0,   516,     0,     0,
     520,   635,     0,   635,   597,     0,   541,   458,   451,     0,
     581,   603,   517,     0,   600,   520,     0,   452,     0,   582
};

  /* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -731,  -351,   -73,   -11,   -47,  -731,  -731,  -731,   547,  -731,
    -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,  -731,
    -731,  -731,   -86,  -731,  -281,  -731,  -731,  -731,  -476,  -731,
    -731,   421,  -118,    41,  -104,  -179,   -19,    -5,  -731,  -731,
    -731,   554,  -731,  -731,   416,  -731,  -731,  -731,  -731,   -76,
    -261,  -731,  -731,  -181,  -731,  -731,   410,  -731,   -45,   573,
      39,    -3,    50,  -731,  -731,  -731,  -731,  -182,  -731,   -44,
       3,   -33,  -731,  -731,   213,  -349,  -731,  -210,  -731,     9,
    -731,   -41,  -369,  -731,   -66,  -731,   150,  -731,  -446,  -444,
     166,  -731,  -709,   -87,  -380,  -731,  -375,   -29,  -731,   459,
    -731,  -731,   586,  -731,  -158,  -683,  -730,  -731,  -731,   620,
    -731,   249,  -373,  -731,  -283,  -696,   220,  -145,  -731,  -731,
    -692,  -731,  -731,  -254,  -284,  -731,  -731,  -731,  -175,  -731,
    -408,  -410,  -413,  -731,  -731,  -731,  -731,  -731,  -731,   -83,
     -21,  -698
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short yydefgoto[] =
{
      -1,   706,   499,   169,   357,   638,    26,    27,    28,    29,
      30,    86,    87,    88,    89,   363,    90,    91,    92,   318,
     754,   755,   358,   359,   376,   683,   684,    31,   500,   501,
      32,    96,   689,   690,   691,    33,    34,    35,    36,    37,
      38,    39,    40,    41,   182,   408,   411,   185,    42,   188,
     502,    43,   197,   804,    44,    45,   639,   640,   641,    46,
      47,    48,    99,   419,    50,   420,    51,   421,   422,   423,
     424,   503,    53,    54,   489,   490,   693,   814,   854,   101,
     427,   428,   655,   505,   506,   676,   458,    56,   102,   103,
     146,   652,   765,   386,   402,   517,   172,   446,   174,   175,
     400,    57,    58,   714,   715,   656,   716,   153,   717,   718,
     719,   436,   437,   438,   906,   907,   908,   793,   794,   795,
     142,   889,   909,   838,   920,   921,   439,   666,   805,   440,
     922,   658,   143,   843,   871,   441,   442,   443,   663,   664,
     660,   160
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short yytable[] =
{
     171,   159,   360,    52,   173,   141,   144,   145,   425,    55,
     418,   418,    98,    68,   170,   444,   387,   659,   100,   374,
     659,   504,   657,   667,   520,   483,   377,    52,   518,   176,
      52,   707,   516,   778,   317,   450,    55,   486,   487,   695,
     797,   696,   792,   643,   364,   820,   796,   823,    52,    67,
      49,   193,   194,   195,   388,   451,    97,   389,   815,   361,
      49,  -446,  -466,   669,  -466,  -392,   168,  -391,    22,  -392,
     316,   -24,   743,   670,    49,   398,    11,    49,   109,   892,
     770,   375,   378,   380,   186,  -392,  -392,   459,   727,   397,
     384,   859,    98,   462,   401,    49,   811,   837,   100,   483,
     156,   841,   674,   155,   855,   796,   812,   409,   483,   726,
     410,   483,   881,     1,     2,     3,     4,     5,     6,     7,
       8,   447,   488,  -392,   158,  -391,     9,   485,   189,   702,
     703,    61,   166,   399,    65,   669,   382,    59,   504,    60,
     778,   405,   454,   455,   878,  -518,  -386,  -511,   456,   385,
    -518,   187,   362,   746,   642,  -446,   747,   868,   190,    98,
     457,   191,   404,   445,    52,   100,   668,   183,     4,     5,
     898,   135,   136,   137,   138,   139,   140,  -457,   192,   196,
     426,   319,   682,   886,  -360,   383,  -360,  -360,   915,  -497,
     910,  -497,  -497,    62,    63,    64,   796,  -457,   936,   385,
      67,   685,   686,    97,  -387,  -511,   645,   646,   648,   649,
     837,    49,   780,   781,   925,   391,   708,  -511,   796,   776,
     777,   429,   430,   431,   432,   433,   910,   434,   435,   783,
     784,   452,   796,     1,     2,     3,     4,     5,     6,     7,
       8,   390,   695,   374,   696,   392,     9,   695,   939,   696,
     377,    61,   845,   671,   393,   834,   835,   394,    11,   379,
     381,   396,   401,   728,   403,   730,   766,   407,   733,   413,
     836,   429,   430,   431,   432,   433,   415,   434,   435,   416,
     484,   735,   463,   485,   509,     1,     2,     3,     4,     5,
       6,     7,     8,   834,   835,   374,   507,   510,     9,   511,
     756,   374,   377,   161,   168,   375,   692,   521,   377,   448,
      11,   644,   453,    93,    94,    18,    65,   650,   647,   701,
     651,   671,   429,   430,   431,   432,   433,   659,   434,   435,
     672,   483,   798,   674,   483,   483,   772,   773,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   779,   861,   673,
     688,   147,   782,   678,   148,   687,   704,   375,   149,   721,
     150,   151,   461,   375,   162,    62,    63,    64,    65,   791,
     163,   152,   731,   734,   519,   737,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   171,   738,   739,   741,   173,
     374,   740,   742,   743,   744,   745,   653,   377,   661,   170,
     665,   818,   748,   828,   164,   830,   831,   749,   757,   374,
     374,   758,   759,   177,   178,   179,   377,   377,   180,   816,
     817,   662,   760,   762,   764,   774,   775,   807,   791,   659,
     147,   181,   785,   148,   870,   404,   786,   149,   806,   150,
     151,   709,   710,   711,   712,   810,   813,   824,   821,   680,
     858,   675,   375,   697,   698,   504,   829,   483,   483,   832,
     713,   894,   729,   839,   893,   418,   840,   842,   418,  -608,
     867,   375,   375,   846,   850,   852,   851,   856,   659,   808,
     809,   862,    98,   912,   884,   863,   864,   866,   100,   872,
     659,   873,   874,   876,   694,   875,   877,     1,     2,     3,
       4,     5,     6,     7,     8,   880,   879,   723,   882,   692,
       9,   177,   178,   179,   692,    61,   180,   883,   904,   791,
     659,   885,    11,   888,   890,   941,   891,   895,   896,   181,
     899,   659,   901,     1,     2,     3,     4,     5,     6,     7,
       8,   791,   902,   903,   913,   911,     9,   742,   914,   916,
     938,    10,   924,   917,   927,   791,   926,   929,    11,    12,
      13,   928,   933,   930,   801,   947,   931,   935,   932,   937,
      14,   940,   942,   944,   167,   767,   945,    62,    63,    64,
      65,   948,   949,   395,   763,    69,     1,     2,     3,     4,
       5,     6,     7,     8,   184,   725,   414,   165,   826,     9,
     412,   418,   491,   732,    61,   857,   677,   157,   768,   769,
     736,    11,    15,    16,    17,    18,    19,    20,    21,   822,
      22,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,   406,    82,    83,    84,    85,   751,   154,
     426,   934,   508,   833,   147,    23,   519,   148,   919,   654,
      24,   149,    25,   150,   151,   709,   710,   711,   712,   171,
     946,   865,   753,   173,   802,     0,    62,    63,    64,    65,
       0,     0,     0,   170,     0,     0,     0,     0,     0,     0,
       0,     0,   170,   384,     0,    98,     0,   374,   374,     0,
      98,   100,     0,   519,   377,   377,   100,   694,   519,     0,
     900,     0,   694,   418,     0,    66,     0,     0,     0,   799,
       0,     0,   445,     0,     0,   445,     0,     0,     0,   918,
     847,     0,   418,   800,     0,     0,     1,     2,     3,     4,
       5,     6,     7,     8,     0,     0,   662,     0,     0,     9,
       0,     0,     0,     0,    61,     0,     0,     0,     0,   375,
     375,    11,     0,     0,     0,   943,     0,     0,   418,     1,
       2,     3,     4,     5,     6,     7,     8,   844,   825,     0,
       0,   723,     9,     0,     0,     0,     0,    61,     0,     0,
     853,   454,   455,   697,   698,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   849,     0,     0,   457,
     750,     0,   860,   445,     0,     0,    93,    94,    18,    65,
       0,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,     0,
       0,     0,     0,     0,   705,     0,     0,     0,     0,    62,
      63,    64,     0,    95,     0,     0,   897,     0,     0,     0,
       0,     0,     0,     0,     0,   905,     0,     0,     0,     0,
       0,   198,     0,     0,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   905,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,     0,   275,     0,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     302,   303,   304,   305,   306,   307,   308,   309,     0,     0,
     310,     0,   311,   312,   313,   314,   315,   198,     0,     0,
     320,   200,   201,   202,   203,   204,   205,   206,   207,   321,
     322,   323,   324,   212,   325,   326,   215,   216,   217,   327,
     219,   220,   221,   222,   223,   224,   225,     0,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   328,   329,   330,   331,   332,   266,   267,
     268,   269,   270,   271,   272,   273,   274,     0,   275,     0,
     276,   277,   278,   279,   280,   333,   282,   334,   335,   336,
     337,   338,   339,   289,   340,   291,   292,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   309,     0,     0,   310,     0,   311,   312,
     313,   314,   315,   522,     0,     0,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   541,   542,   543,   544,   545,   546,
     547,   548,   549,     0,   550,   551,   552,   553,   554,   413,
     724,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   589,   590,   591,   592,   593,
     594,   595,   596,     0,   597,     0,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,   620,   621,
     622,   623,   624,   625,   626,   627,   628,   629,   630,   631,
       0,     0,   632,     0,   633,   634,   635,   636,   637,   522,
       0,     0,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,   540,
     541,   542,   543,   544,   545,   546,   547,   548,   549,     0,
     550,   551,   552,   553,   554,   413,     0,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,   591,   592,   593,   594,   595,   596,     0,
     597,     0,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   628,   629,   630,   631,  -584,     0,   632,     0,
     633,   634,   635,   636,   637,  -584,  -584,  -584,  -584,     0,
    -584,  -584,     0,     0,     0,  -584,     0,     0,     0,     0,
       0,     0,  -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,
    -584,  -584,  -584,  -584,     0,  -584,  -584,  -584,  -584,  -584,
    -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,
    -584,  -584,  -584,     0,     0,     0,     0,     0,  -584,  -584,
    -584,  -584,  -584,  -584,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     0,     0,     0,     9,     0,     0,
    -584,  -584,    61,  -584,  -584,  -584,  -584,  -584,  -584,    11,
    -584,     0,     0,  -584,  -584,  -584,  -584,  -584,  -584,  -584,
    -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,  -584,     0,
     104,     0,     0,     0,     0,     0,     0,     0,  -584,   105,
     106,   107,   108,     0,   109,   110,   512,     0,     0,   111,
     495,     0,   496,     0,   497,   367,   513,     0,     0,   498,
       0,     0,     0,     0,    93,    94,    18,    65,     0,     0,
       0,     0,     0,     0,   369,   370,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,   372,     0,
       0,     0,     0,   112,   113,   114,   115,   116,     0,     0,
       0,   688,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   514,   117,     0,   118,   119,   120,
     121,   122,   123,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   104,     0,     0,     0,     0,     0,     0,
       0,   515,   105,   106,   107,   108,     0,   109,   110,     0,
       0,     0,   111,     0,     0,   365,     0,   366,   367,     0,
       0,     0,   368,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   369,   370,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     371,   372,     0,     0,     0,     0,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,   373,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   117,     0,
     118,   119,   120,   121,   122,   123,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   -33,     0,     0,   681,
       0,     0,     0,     0,     0,   -33,   -33,   -33,   -33,     0,
     -33,   -33,     0,     0,     0,   -33,     0,     0,   -33,   -33,
     -33,   -33,     0,     0,     0,   -33,     0,     0,     0,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     7,     8,
     -33,   -33,     0,     0,     0,     9,     0,     0,     0,     0,
      61,     0,     0,   -33,   -33,     0,     0,    11,     0,   -33,
     -33,   -33,   -33,   -33,     0,     0,     0,     0,     0,     0,
       0,   -33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -33,     0,   -33,   -33,   -33,   -33,   -33,   -33,     0,
     -33,     0,     0,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -34,
       0,   -33,    93,    94,    18,    65,     0,     0,   -34,   -34,
     -34,   -34,     0,   -34,   -34,     0,     0,     0,   -34,     0,
       0,   -34,   -34,   -34,   -34,     0,     0,     0,   -34,     0,
       0,     0,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,   -34,   -34,     0,     0,     0,     9,     0,
       0,     0,     0,    61,     0,     0,   -34,   -34,     0,     0,
      11,     0,   -34,   -34,   -34,   -34,   -34,     0,     0,     0,
       0,     0,     0,     0,   -34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -34,     0,   -34,   -34,   -34,   -34,
     -34,   -34,     0,   -34,     0,     0,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -35,     0,   -34,    62,    63,    64,    65,     0,
       0,   -35,   -35,   -35,   -35,     0,   -35,   -35,     0,     0,
       0,   -35,     0,     0,   -35,   -35,   -35,   -35,     0,     0,
       0,   -35,     0,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,   -35,   -35,     0,     0,
       0,   417,     0,     0,     0,     0,    61,     0,     0,   -35,
     -35,     0,     0,    11,     0,   -35,   -35,   -35,   -35,   -35,
       0,     0,     0,     0,     0,     0,     0,   -35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -35,     0,   -35,
     -35,   -35,   -35,   -35,   -35,     0,   -35,     0,     0,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -36,     0,   -35,    62,    63,
      64,    65,     0,     0,   -36,   -36,   -36,   -36,     0,   -36,
     -36,     0,     0,     0,   -36,     0,     0,   -36,   -36,   -36,
     -36,     0,     0,     0,   -36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -36,
     -36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -36,   -36,     0,     0,     0,     0,   -36,   -36,
     -36,   -36,   -36,     0,     0,     0,     0,     0,     0,     0,
     -36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -36,     0,   -36,   -36,   -36,   -36,   -36,   -36,     0,   -36,
       0,     0,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -37,     0,
     -36,     0,     0,     0,     0,     0,     0,   -37,   -37,   -37,
     -37,     0,   -37,   -37,     0,     0,     0,   -37,     0,     0,
     -37,   -37,   -37,   -37,     0,     0,     0,   -37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -37,   -37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -37,   -37,     0,     0,     0,
       0,   -37,   -37,   -37,   -37,   -37,     0,     0,     0,     0,
       0,     0,     0,   -37,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -37,     0,   -37,   -37,   -37,   -37,   -37,
     -37,     0,   -37,     0,     0,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -60,     0,   -37,     0,     0,     0,     0,     0,     0,
     -60,   -60,   -60,   -60,     0,   -60,   -60,     0,     0,     0,
     -60,     0,     0,   -60,   -60,   -60,   -60,     0,     0,     0,
     -60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -60,   -60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -60,   -60,
       0,     0,     0,     0,   -60,   -60,   -60,   -60,   -60,     0,
       0,     0,     0,     0,     0,     0,   -60,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -60,     0,   -60,   -60,
     -60,   -60,   -60,   -60,     0,   -60,     0,     0,   -60,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,   -60,   -60,   -61,     0,  -623,     0,     0,     0,
       0,     0,     0,   -61,   -61,   -61,   -61,     0,   -61,   -61,
       0,     0,     0,   -61,     0,     0,   -61,   -61,   -61,   -61,
       0,     0,     0,   -61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -61,   -61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -61,   -61,     0,     0,     0,     0,   -61,   -61,   -61,
     -61,   -61,     0,     0,     0,     0,     0,     0,     0,   -61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -61,
       0,   -61,   -61,   -61,   -61,   -61,   -61,     0,   -61,     0,
       0,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,   -61,   -61,   -61,   -24,     0,  -584,
       0,     0,     0,     0,     0,     0,   -24,   -24,   -24,   -24,
       0,   -24,   -24,     0,     0,     0,   -24,     0,     0,   -24,
     -24,   -24,   -24,     0,     0,     0,   -24,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -24,   -24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -24,   -24,     0,     0,     0,     0,
     -24,   -24,   -24,   -24,   -24,     0,     0,     0,     0,     0,
       0,     0,   -24,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -24,     0,   -24,   -24,   -24,   -24,   -24,   -24,
       0,   -24,     0,     0,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -42,     0,   -24,     0,     0,     0,     0,     0,     0,   -42,
     -42,   -42,   -42,     0,   -42,   -42,     0,     0,     0,   -42,
       0,     0,   -42,   -42,   -42,   -42,     0,     0,     0,   -42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -42,   -42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -42,   -42,     0,
       0,     0,     0,   -42,   -42,   -42,   -42,   -42,     0,     0,
       0,     0,     0,     0,     0,   -42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -42,     0,   -42,   -42,   -42,
     -42,   -42,   -42,     0,   -42,     0,     0,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -41,     0,   -42,     0,     0,     0,     0,
       0,     0,   -41,   -41,   -41,   -41,     0,   -41,   -41,     0,
       0,     0,   -41,     0,     0,   -41,   -41,   -41,   -41,     0,
       0,     0,   -41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -41,   -41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -41,   -41,     0,     0,     0,     0,   -41,   -41,   -41,   -41,
     -41,     0,     0,     0,     0,     0,     0,     0,   -41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -41,     0,
     -41,   -41,   -41,   -41,   -41,   -41,     0,   -41,     0,     0,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -40,     0,   -41,     0,
       0,     0,     0,     0,     0,   -40,   -40,   -40,   -40,     0,
     -40,   -40,     0,     0,     0,   -40,     0,     0,   -40,   -40,
     -40,   -40,     0,     0,     0,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -40,   -40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -40,   -40,     0,     0,     0,     0,   -40,
     -40,   -40,   -40,   -40,     0,     0,     0,     0,     0,     0,
       0,   -40,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -40,     0,   -40,   -40,   -40,   -40,   -40,   -40,     0,
     -40,     0,     0,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -38,
       0,   -40,     0,     0,     0,     0,     0,     0,   -38,   -38,
     -38,   -38,     0,   -38,   -38,     0,     0,     0,   -38,     0,
       0,   -38,   -38,   -38,   -38,     0,     0,     0,   -38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -38,   -38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -38,   -38,     0,     0,
       0,     0,   -38,   -38,   -38,   -38,   -38,     0,     0,     0,
       0,     0,     0,     0,   -38,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -38,     0,   -38,   -38,   -38,   -38,
     -38,   -38,     0,   -38,     0,     0,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -39,     0,   -38,     0,     0,     0,     0,     0,
       0,   -39,   -39,   -39,   -39,     0,   -39,   -39,     0,     0,
       0,   -39,     0,     0,   -39,   -39,   -39,   -39,     0,     0,
       0,   -39,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -39,   -39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -39,
     -39,     0,     0,     0,     0,   -39,   -39,   -39,   -39,   -39,
       0,     0,     0,     0,     0,     0,     0,   -39,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -39,     0,   -39,
     -39,   -39,   -39,   -39,   -39,     0,   -39,     0,     0,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -32,     0,   -39,     0,     0,
       0,     0,     0,     0,   -32,   -32,   -32,   -32,     0,   -32,
     -32,     0,     0,     0,   -32,     0,     0,   -32,   -32,   -32,
     -32,     0,     0,     0,   -32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -32,
     -32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -32,   -32,     0,     0,     0,     0,   -32,   -32,
     -32,   -32,   -32,     0,     0,     0,     0,     0,     0,     0,
     -32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -32,     0,   -32,   -32,   -32,   -32,   -32,   -32,     0,   -32,
       0,     0,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -31,     0,
     -32,     0,     0,     0,     0,     0,     0,   -31,   -31,   -31,
     -31,     0,   -31,   -31,     0,     0,     0,   -31,     0,     0,
     -31,   -31,   -31,   -31,     0,     0,     0,   -31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -31,   -31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -31,   -31,     0,     0,     0,
       0,   -31,   -31,   -31,   -31,   -31,     0,     0,     0,     0,
       0,     0,     0,   -31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -31,     0,   -31,   -31,   -31,   -31,   -31,
     -31,     0,   -31,     0,     0,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -25,     0,   -31,     0,     0,     0,     0,     0,     0,
     -25,   -25,   -25,   -25,     0,   -25,   -25,     0,     0,     0,
     -25,     0,     0,   -25,   -25,   -25,   -25,     0,     0,     0,
     -25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -25,   -25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -25,   -25,
       0,     0,     0,     0,   -25,   -25,   -25,   -25,   -25,     0,
       0,     0,     0,     0,     0,     0,   -25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -25,     0,   -25,   -25,
     -25,   -25,   -25,   -25,     0,   -25,     0,     0,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -29,     0,   -25,     0,     0,     0,
       0,     0,     0,   -29,   -29,   -29,   -29,     0,   -29,   -29,
       0,     0,     0,   -29,     0,     0,   -29,   -29,   -29,   -29,
       0,     0,     0,   -29,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -29,   -29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -29,   -29,     0,     0,     0,     0,   -29,   -29,   -29,
     -29,   -29,     0,     0,     0,     0,     0,     0,     0,   -29,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -29,
       0,   -29,   -29,   -29,   -29,   -29,   -29,     0,   -29,     0,
       0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -28,     0,   -29,
       0,     0,     0,     0,     0,     0,   -28,   -28,   -28,   -28,
       0,   -28,   -28,     0,     0,     0,   -28,     0,     0,   -28,
     -28,   -28,   -28,     0,     0,     0,   -28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -28,   -28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -28,   -28,     0,     0,     0,     0,
     -28,   -28,   -28,   -28,   -28,     0,     0,     0,     0,     0,
       0,     0,   -28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -28,     0,   -28,   -28,   -28,   -28,   -28,   -28,
       0,   -28,     0,     0,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -26,     0,   -28,     0,     0,     0,     0,     0,     0,   -26,
     -26,   -26,   -26,     0,   -26,   -26,     0,     0,     0,   -26,
       0,     0,   -26,   -26,   -26,   -26,     0,     0,     0,   -26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -26,   -26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -26,   -26,     0,
       0,     0,     0,   -26,   -26,   -26,   -26,   -26,     0,     0,
       0,     0,     0,     0,     0,   -26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -26,     0,   -26,   -26,   -26,
     -26,   -26,   -26,     0,   -26,     0,     0,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -27,     0,   -26,     0,     0,     0,     0,
       0,     0,   -27,   -27,   -27,   -27,     0,   -27,   -27,     0,
       0,     0,   -27,     0,     0,   -27,   -27,   -27,   -27,     0,
       0,     0,   -27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -27,   -27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -27,   -27,     0,     0,     0,     0,   -27,   -27,   -27,   -27,
     -27,     0,     0,     0,     0,     0,     0,     0,   -27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -27,     0,
     -27,   -27,   -27,   -27,   -27,   -27,     0,   -27,     0,     0,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -43,     0,   -27,     0,
       0,     0,     0,     0,     0,   -43,   -43,   -43,   -43,     0,
     -43,   -43,     0,     0,     0,   -43,     0,     0,   -43,   -43,
     -43,   -43,     0,     0,     0,   -43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -43,   -43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -43,   -43,     0,     0,     0,     0,   -43,
     -43,   -43,   -43,   -43,     0,     0,     0,     0,     0,     0,
       0,   -43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -43,     0,   -43,   -43,   -43,   -43,   -43,   -43,     0,
     -43,     0,     0,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,   -43,  -138,
       0,   -43,     0,     0,     0,     0,     0,     0,  -138,  -138,
    -138,  -138,     0,  -138,  -138,     0,     0,     0,  -138,     0,
       0,  -138,  -138,  -138,  -138,     0,     0,     0,  -138,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -138,  -138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -138,  -138,     0,     0,
       0,     0,  -138,  -138,  -138,  -138,  -138,     0,     0,     0,
       0,     0,     0,     0,  -138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -138,     0,  -138,  -138,  -138,  -138,
    -138,  -138,     0,  -138,     0,     0,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -139,     0,  -592,     0,     0,     0,     0,     0,
       0,  -139,  -139,  -139,  -139,     0,  -139,  -139,     0,     0,
       0,  -139,     0,     0,  -139,  -139,  -139,  -139,     0,     0,
       0,  -139,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -139,  -139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -139,
    -139,     0,     0,     0,     0,  -139,  -139,  -139,  -139,  -139,
       0,     0,     0,     0,     0,     0,     0,  -139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -139,     0,  -139,
    -139,  -139,  -139,  -139,  -139,     0,  -139,     0,     0,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -140,     0,  -591,     0,     0,
       0,     0,     0,     0,  -140,  -140,  -140,  -140,     0,  -140,
    -140,     0,     0,     0,  -140,     0,     0,  -140,  -140,  -140,
    -140,     0,     0,     0,  -140,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -140,
    -140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -140,  -140,     0,     0,     0,     0,  -140,  -140,
    -140,  -140,  -140,     0,     0,     0,     0,     0,     0,     0,
    -140,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -140,     0,  -140,  -140,  -140,  -140,  -140,  -140,     0,  -140,
       0,     0,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -141,     0,
    -589,     0,     0,     0,     0,     0,     0,  -141,  -141,  -141,
    -141,     0,  -141,  -141,     0,     0,     0,  -141,     0,     0,
    -141,  -141,  -141,  -141,     0,     0,     0,  -141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -141,  -141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -141,  -141,     0,     0,     0,
       0,  -141,  -141,  -141,  -141,  -141,     0,     0,     0,     0,
       0,     0,     0,  -141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -141,     0,  -141,  -141,  -141,  -141,  -141,
    -141,     0,  -141,     0,     0,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -142,     0,  -587,     0,     0,     0,     0,     0,     0,
    -142,  -142,  -142,  -142,     0,  -142,  -142,     0,     0,     0,
    -142,     0,     0,  -142,  -142,  -142,  -142,     0,     0,     0,
    -142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -142,  -142,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -142,  -142,
       0,     0,     0,     0,  -142,  -142,  -142,  -142,  -142,     0,
       0,     0,     0,     0,     0,     0,  -142,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -142,     0,  -142,  -142,
    -142,  -142,  -142,  -142,     0,  -142,     0,     0,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -143,     0,  -588,     0,     0,     0,
       0,     0,     0,  -143,  -143,  -143,  -143,     0,  -143,  -143,
       0,     0,     0,  -143,     0,     0,  -143,  -143,  -143,  -143,
       0,     0,     0,  -143,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -143,  -143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -143,  -143,     0,     0,     0,     0,  -143,  -143,  -143,
    -143,  -143,     0,     0,     0,     0,     0,     0,     0,  -143,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -143,
       0,  -143,  -143,  -143,  -143,  -143,  -143,     0,  -143,     0,
       0,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -144,     0,  -590,
       0,     0,     0,     0,     0,     0,  -144,  -144,  -144,  -144,
       0,  -144,  -144,     0,     0,     0,  -144,     0,     0,  -144,
    -144,  -144,  -144,     0,     0,     0,  -144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -144,  -144,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -144,  -144,     0,     0,     0,     0,
    -144,  -144,  -144,  -144,  -144,     0,     0,     0,     0,     0,
       0,     0,  -144,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -144,     0,  -144,  -144,  -144,  -144,  -144,  -144,
       0,  -144,     0,     0,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -145,     0,  -586,     0,     0,     0,     0,     0,     0,  -145,
    -145,  -145,  -145,     0,  -145,  -145,     0,     0,     0,  -145,
       0,     0,  -145,  -145,  -145,  -145,     0,     0,     0,  -145,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -145,  -145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -145,  -145,     0,
       0,     0,     0,  -145,  -145,  -145,  -145,  -145,     0,     0,
       0,     0,     0,     0,     0,  -145,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -145,     0,  -145,  -145,  -145,
    -145,  -145,  -145,     0,  -145,     0,     0,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -146,     0,  -585,     0,     0,     0,     0,
       0,     0,  -146,  -146,  -146,  -146,     0,  -146,  -146,     0,
       0,     0,  -146,     0,     0,  -146,  -146,  -146,  -146,     0,
       0,     0,  -146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -146,  -146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -146,  -146,     0,     0,     0,     0,  -146,  -146,  -146,  -146,
    -146,     0,     0,     0,     0,     0,     0,     0,  -146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -146,     0,
    -146,  -146,  -146,  -146,  -146,  -146,     0,  -146,     0,     0,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,   -30,     0,  -593,     0,
       0,     0,     0,     0,     0,   -30,   -30,   -30,   -30,     0,
     -30,   -30,     0,     0,     0,   -30,     0,     0,   -30,   -30,
     -30,   -30,     0,     0,     0,   -30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -30,   -30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -30,   -30,     0,     0,     0,     0,   -30,
     -30,   -30,   -30,   -30,     0,     0,     0,     0,     0,     0,
       0,   -30,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -30,     0,   -30,   -30,   -30,   -30,   -30,   -30,     0,
     -30,     0,     0,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,  -148,
       0,   -30,     0,     0,     0,     0,     0,     0,  -148,  -148,
    -148,  -148,     0,  -148,  -148,     0,     0,     0,  -148,     0,
       0,  -148,  -148,  -148,  -148,     0,     0,     0,  -148,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -148,  -148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -148,  -148,     0,     0,
       0,     0,  -148,  -148,  -148,  -148,  -148,     0,     0,     0,
       0,     0,     0,     0,  -148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -148,     0,  -148,  -148,  -148,  -148,
    -148,  -148,     0,  -148,     0,     0,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -149,     0,  -621,     0,     0,     0,     0,     0,
       0,  -149,  -149,  -149,  -149,     0,  -149,  -149,     0,     0,
       0,  -149,     0,     0,  -149,  -149,  -149,  -149,     0,     0,
       0,  -149,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -149,  -149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -149,
    -149,     0,     0,     0,     0,  -149,  -149,  -149,  -149,  -149,
       0,     0,     0,     0,     0,     0,     0,  -149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -149,     0,  -149,
    -149,  -149,  -149,  -149,  -149,     0,  -149,     0,     0,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -150,     0,  -619,     0,     0,
       0,     0,     0,     0,  -150,  -150,  -150,  -150,     0,  -150,
    -150,     0,     0,     0,  -150,     0,     0,  -150,  -150,  -150,
    -150,     0,     0,     0,  -150,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -150,
    -150,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -150,  -150,     0,     0,     0,     0,  -150,  -150,
    -150,  -150,  -150,     0,     0,     0,     0,     0,     0,     0,
    -150,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -150,     0,  -150,  -150,  -150,  -150,  -150,  -150,     0,  -150,
       0,     0,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,
    -150,  -150,  -150,  -150,  -150,  -150,  -150,  -150,  -151,     0,
    -618,     0,     0,     0,     0,     0,     0,  -151,  -151,  -151,
    -151,     0,  -151,  -151,     0,     0,     0,  -151,     0,     0,
    -151,  -151,  -151,  -151,     0,     0,     0,  -151,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -151,  -151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -151,  -151,     0,     0,     0,
       0,  -151,  -151,  -151,  -151,  -151,     0,     0,     0,     0,
       0,     0,     0,  -151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -151,     0,  -151,  -151,  -151,  -151,  -151,
    -151,     0,  -151,     0,     0,  -151,  -151,  -151,  -151,  -151,
    -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,  -151,
    -151,  -152,     0,  -620,     0,     0,     0,     0,     0,     0,
    -152,  -152,  -152,  -152,     0,  -152,  -152,     0,     0,     0,
    -152,     0,     0,  -152,  -152,  -152,  -152,     0,     0,     0,
    -152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -152,  -152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -152,  -152,
       0,     0,     0,     0,  -152,  -152,  -152,  -152,  -152,     0,
       0,     0,     0,     0,     0,     0,  -152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -152,     0,  -152,  -152,
    -152,  -152,  -152,  -152,     0,  -152,     0,     0,  -152,  -152,
    -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,  -152,
    -152,  -152,  -152,  -152,  -153,     0,  -617,     0,     0,     0,
       0,     0,     0,  -153,  -153,  -153,  -153,     0,  -153,  -153,
       0,     0,     0,  -153,     0,     0,  -153,  -153,  -153,  -153,
       0,     0,     0,  -153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -153,  -153,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -153,  -153,     0,     0,     0,     0,  -153,  -153,  -153,
    -153,  -153,     0,     0,     0,     0,     0,     0,     0,  -153,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -153,
       0,  -153,  -153,  -153,  -153,  -153,  -153,     0,  -153,     0,
       0,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   104,     0,  -616,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
       0,   109,   110,     0,     0,     0,   111,     0,     0,   365,
     448,   366,   367,     0,     0,     0,   368,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   371,   372,     0,     0,     0,     0,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,   373,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,   118,   119,   120,   121,   122,   123,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
       0,     0,   449,   104,     1,     2,     3,     4,     5,     6,
       7,     8,   105,   106,   107,   108,     0,   699,   110,   512,
       0,     0,   700,   495,     0,   496,     0,   497,   367,    11,
       0,     0,   498,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   369,   370,   168,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     371,   372,     0,     0,     0,     0,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,    63,    64,    65,   117,     0,
     118,   119,   120,   121,   122,   123,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   104,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,     0,
     109,   110,   492,   493,   494,   111,   495,     0,   496,   448,
     497,   367,     0,     0,     0,   498,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     369,   370,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,   372,     0,     0,     0,     0,   112,
     113,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,     0,   118,   119,   120,   121,   122,   123,     0,
     124,     0,     0,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,     0,   109,   110,   787,     0,     0,   111,   495,
       0,   496,     0,   497,   367,     0,     0,     0,   498,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     158,     0,     0,   369,   370,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   371,   372,     0,     0,
       0,     0,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   788,   789,   119,   120,   121,
     122,   123,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   790,   135,   136,   137,   138,
     139,   140,   104,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,     0,   109,   110,   512,     0,
       0,   111,   495,     0,   496,     0,   497,   367,     0,     0,
       0,   498,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,   369,   370,   168,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   371,
     372,     0,     0,   869,     0,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,   118,
     119,   120,   121,   122,   123,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,     0,   109,
     110,   512,     0,     0,   111,   495,  -635,   496,     0,   497,
     367,     0,     0,     0,   498,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   158,     0,     0,   369,
     370,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   371,   372,     0,     0,     0,     0,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,   118,   119,   120,   121,   122,   123,     0,   124,
       0,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   512,     0,     0,   111,   495,     0,
     496,     0,   497,   367,     0,     0,     0,   498,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,   369,   370,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   371,   372,     0,     0,     0,
       0,   112,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,     0,   118,   119,   120,   121,   122,
     123,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   104,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,     0,   109,   110,   787,     0,     0,
     111,   495,     0,   496,     0,   497,   367,     0,     0,     0,
     498,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   369,   370,   168,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   371,   372,
       0,     0,     0,     0,   112,   113,   114,   115,   116,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   117,   788,   789,   119,
     120,   121,   122,   123,     0,   124,     0,     0,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   790,   135,   136,
     137,   138,   139,   140,   104,     0,     0,     0,     0,     0,
       0,     0,     0,   105,   106,   107,   108,     0,   109,   110,
     512,     0,     0,   111,   495,     0,   496,     0,   497,   367,
       0,     0,     0,   498,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   369,   370,
     168,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,   372,     0,     0,     0,     0,   112,   113,   114,
     115,   116,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   117,
       0,   118,   119,   120,   121,   122,   123,     0,   124,     0,
       0,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   104,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
       0,   109,   110,     0,     0,     0,   111,     0,     0,   365,
       0,   366,   367,     0,     0,     0,   368,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   369,   370,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   371,   372,     0,     0,     0,     0,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,   373,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,   118,   119,   120,   121,   122,   123,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     104,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,     0,   109,   110,     0,     0,     0,   111,
       0,     0,     0,     0,     0,     0,    11,     0,     0,  -527,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   113,   114,   115,   116,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,   117,     0,   118,   119,   120,
     121,   122,   123,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   104,     0,     0,     0,     0,     0,     0,
       0,     0,   105,   106,   107,   108,     0,   109,   110,     0,
       0,   679,   111,     0,     0,     0,     0,     0,     0,    11,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,     0,   168,
       0,     0,     0,   482,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,   114,   115,
     116,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    65,   117,     0,
     118,   119,   120,   121,   122,   123,     0,   124,     0,     0,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   104,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,     0,
     109,   110,     0,     0,     0,   111,     0,     0,   771,     0,
       0,     0,     0,     0,     0,   722,   827,   464,   465,   466,
     467,   468,   469,   470,   471,   472,   473,   474,   475,   476,
     477,   478,   479,   480,   481,     0,     0,     0,     0,     0,
     705,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,     0,   118,   119,   120,   121,   122,   123,     0,
     124,     0,     0,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   104,
       0,     0,     0,     0,     0,     0,     0,     0,   105,   106,
     107,   108,     0,   109,   110,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   764,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   168,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,   114,   115,   116,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,     0,   118,   119,   120,   121,
     122,   123,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   104,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   923,   109,   110,     0,     0,
       0,   111,     0,     0,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,     0,     0,     0,     0,     0,   705,   168,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   117,     0,   118,
     119,   120,   121,   122,   123,     0,   124,     0,     0,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   104,     0,     0,     0,     0,
       0,     0,     0,     0,   105,   106,   107,   108,     0,   109,
     110,     0,     0,     0,   111,     0,     0,   887,     0,     0,
       0,     0,     0,     0,   460,   464,   465,   466,   467,   468,
     469,   470,   471,   472,   473,   474,   475,   476,   477,   478,
     479,   480,   481,     0,     0,     0,     0,     0,   705,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     117,     0,   118,   119,   120,   121,   122,   123,     0,   124,
       0,     0,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,     0,     0,     0,   111,     0,     0,
       0,   761,     0,     0,     0,     0,     0,   722,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,     0,     0,     0,     0,
       0,   482,     0,     0,     0,     0,     0,   104,     0,     0,
       0,   112,   113,   114,   115,   116,   105,   106,   107,   108,
       0,   109,   110,     0,     0,     0,   111,     0,     0,     0,
       0,     0,     0,   117,     0,   118,   119,   120,   121,   122,
     123,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,     0,     0,     0,     0,     0,     0,     0,   752,     0,
     112,   113,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     0,   118,   119,   120,   121,   122,   123,
       0,   124,     0,     0,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     104,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   819,   803,   110,     0,     0,     0,   111,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,     0,     0,
       0,     0,     0,   705,     0,     0,   168,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   104,
       0,     0,     0,   112,   113,   114,   115,   116,   105,   106,
     107,   108,     0,   109,   110,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,   117,     0,   118,   119,   120,
     121,   122,   123,     0,   124,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,     0,     0,     0,     0,     0,   104,     0,
     848,     0,   112,   113,   114,   115,   116,   105,   106,   107,
     108,     0,   109,   110,     0,     0,     0,   111,     0,     0,
       0,     0,     0,     0,   117,     0,   118,   119,   120,   121,
     122,   123,     0,   124,     0,     0,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   117,     0,   118,   119,   120,   121,   122,
     123,     0,   124,     0,     0,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   720,     0,     0,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,     0,     0,     0,     0,     0,   705,   464,   465,
     466,   467,   468,   469,   470,   471,   472,   473,   474,   475,
     476,   477,   478,   479,   480,   481,     0,     0,     0,     0,
       0,   482,   464,   465,   466,   467,   468,   469,   470,   471,
     472,   473,   474,   475,   476,   477,   478,   479,   480,   481,
       0,     0,     0,     0,     0,   705,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,     0,     0,     0,     0,     0,   482,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,     0,     0,
       0,     0,     0,   705
};

static const short yycheck[] =
{
      33,    22,    88,     0,    33,    16,    17,    18,   190,     0,
     189,   190,    15,    10,    33,   196,   103,   430,    15,    92,
     433,   390,   430,   433,   404,   376,    92,    24,   403,    34,
      27,   507,   401,   716,    81,   316,    27,   386,   387,   485,
     738,   485,   738,   418,    91,   775,   738,   777,    45,    10,
       0,    62,    63,    64,   141,   316,    15,   144,   767,    26,
      10,    31,    32,   436,    34,    29,    49,    29,    91,    33,
      81,    33,    24,   442,    24,    29,    29,    27,    17,    18,
      33,    92,    93,    94,    45,    33,    34,   368,    32,   165,
     101,   821,    95,   374,    38,    45,    25,   789,    95,   450,
     123,   797,    26,    26,   813,   797,    35,     6,   459,    33,
       9,   462,    64,     4,     5,     6,     7,     8,     9,    10,
      11,   197,    31,    87,    44,    87,    17,    36,    32,   498,
     499,    22,     0,    87,    87,   508,    95,     9,   507,    11,
     823,   124,    26,    27,   853,    31,    35,    36,    32,    35,
      36,   125,   119,    31,   415,   125,    34,   840,    32,   162,
      44,    36,   173,   196,   161,   162,    37,     6,     7,     8,
     879,   110,   111,   112,   113,   114,   115,    32,    36,    34,
     191,    30,   463,   866,    31,    31,    33,    34,   897,    31,
     888,    33,    34,    84,    85,    86,   888,    32,   928,    35,
     161,   482,   483,   162,    35,    36,    33,    34,    33,    34,
     902,   161,    32,    33,   910,    23,    37,    36,   910,    33,
      34,    92,    93,    94,    95,    96,   924,    98,    99,    33,
      34,   317,   924,     4,     5,     6,     7,     8,     9,    10,
      11,    40,   688,   316,   688,    31,    17,   693,   931,   693,
     316,    22,    33,    34,    36,    17,    18,    23,    29,    93,
      94,   123,    38,   643,    32,   645,    37,     6,   648,    36,
      32,    92,    93,    94,    95,    96,    32,    98,    99,    31,
      35,   650,    32,    36,    32,     4,     5,     6,     7,     8,
       9,    10,    11,    17,    18,   368,    40,    31,    17,    31,
     675,   374,   368,    22,    49,   316,   485,     6,   374,    26,
      29,    32,   359,    84,    85,    86,    87,    40,    34,   498,
      34,    34,    92,    93,    94,    95,    96,   740,    98,    99,
      31,   682,   740,    26,   685,   686,   705,   706,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   722,   824,    32,
     121,     3,   727,    22,     6,    32,    31,   368,    10,    39,
      12,    13,   373,   374,    83,    84,    85,    86,    87,   738,
      89,    23,    64,    64,   403,    37,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   418,    40,    31,    31,   418,
     463,    40,    32,    24,    40,    32,   429,   463,   431,   418,
     433,   770,    32,   783,   123,   785,   786,    31,    33,   482,
     483,    33,    33,     4,     5,     6,   482,   483,     9,   768,
     769,   432,    34,    25,    35,    31,    35,    34,   797,   842,
       3,    22,    33,     6,   842,   446,    33,    10,    33,    12,
      13,    14,    15,    16,    17,    34,    34,    40,    35,   460,
     819,   456,   463,   486,   487,   824,    64,   808,   809,   109,
      33,   874,   644,    32,   874,   644,    32,    34,   647,    33,
     839,   482,   483,    33,    25,    32,    35,    31,   891,   760,
     761,    33,   485,   891,   864,    33,    33,    32,   485,    33,
     903,    31,    97,    35,   485,    33,    25,     4,     5,     6,
       7,     8,     9,    10,    11,    31,    34,   518,    32,   688,
      17,     4,     5,     6,   693,    22,     9,    33,   887,   888,
     933,    33,    29,    34,    33,   933,    34,    32,    34,    22,
      24,   944,    32,     4,     5,     6,     7,     8,     9,    10,
      11,   910,    97,    32,    25,    33,    17,    32,    25,    33,
     930,    22,    34,    33,    33,   924,    34,    33,    29,    30,
      31,    35,    34,    33,   745,   945,    32,    25,    33,    32,
      41,    33,    33,    32,    27,   693,    33,    84,    85,    86,
      87,    33,    33,   162,   688,    30,     4,     5,     6,     7,
       8,     9,    10,    11,    40,   640,   186,    24,   780,    17,
     184,   780,   389,   647,    22,   815,   456,    21,   695,   696,
     651,    29,    83,    84,    85,    86,    87,    88,    89,   777,
      91,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,   174,    79,    80,    81,    82,   671,    19,
     651,   924,   393,   788,     3,   116,   675,     6,   902,   429,
     121,    10,   123,    12,    13,    14,    15,    16,    17,   692,
     944,   836,   673,   692,   747,    -1,    84,    85,    86,    87,
      -1,    -1,    -1,   692,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   701,   694,    -1,   688,    -1,   760,   761,    -1,
     693,   688,    -1,   722,   760,   761,   693,   688,   727,    -1,
     882,    -1,   693,   882,    -1,   123,    -1,    -1,    -1,   742,
      -1,    -1,   745,    -1,    -1,   748,    -1,    -1,    -1,   901,
     806,    -1,   901,   744,    -1,    -1,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    -1,   747,    -1,    -1,    17,
      -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,   760,
     761,    29,    -1,    -1,    -1,   937,    -1,    -1,   937,     4,
       5,     6,     7,     8,     9,    10,    11,   800,   779,    -1,
      -1,   782,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,
     813,    26,    27,   816,   817,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   807,    -1,    -1,    44,
      31,    -1,   823,   836,    -1,    -1,    84,    85,    86,    87,
      -1,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    84,
      85,    86,    -1,   121,    -1,    -1,   879,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   888,    -1,    -1,    -1,    -1,
      -1,     0,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   924,    31,    32,    33,    34,    35,    36,    37,    38,
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
     121,   122,   123,   124,   125,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    -1,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    68,    69,    70,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    -1,    -1,    -1,    17,    -1,    -1,
      87,    88,    22,    90,    91,    92,    93,    94,    95,    29,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   125,    12,
      13,    14,    15,    -1,    17,    18,    19,    -1,    -1,    22,
      23,    -1,    25,    -1,    27,    28,    29,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,   121,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   124,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    -1,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,    -1,   119,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,     4,     5,     6,     7,     8,     9,    10,    11,
      47,    48,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    60,    61,    -1,    -1,    29,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,   118,    84,    85,    86,    87,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    10,    11,    47,    48,    -1,    -1,    -1,    17,    -1,
      -1,    -1,    -1,    22,    -1,    -1,    60,    61,    -1,    -1,
      29,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,   118,    84,    85,    86,    87,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
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
      86,    87,    -1,    -1,    12,    13,    14,    15,    -1,    17,
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
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
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
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
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
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
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
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
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
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
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
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
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
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
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
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
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
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
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
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
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
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
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
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
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
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
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
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
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
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
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
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
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
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
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
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
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
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
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
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
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
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
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
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
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
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
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
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
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
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
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
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
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
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
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
      -1,   118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
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
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
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
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
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
     118,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
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
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
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
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
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
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
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
      -1,    -1,   118,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,    29,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    19,    -1,    -1,    22,    23,
      -1,    25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    19,    -1,
      -1,    22,    23,    -1,    25,    -1,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    64,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    19,    -1,    -1,    22,    23,    24,    25,    -1,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    94,    95,    -1,    97,    -1,    -1,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      -1,    90,    91,    92,    93,    94,    95,    -1,    97,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      -1,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    87,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    33,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    49,
      -1,    -1,    -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    -1,
      90,    91,    92,    93,    94,    95,    -1,    97,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    33,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    -1,    90,    91,    92,    93,    94,    95,    -1,
      97,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    33,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    -1,    90,
      91,    92,    93,    94,    95,    -1,    97,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    90,    91,    92,    93,    94,    95,    -1,    97,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    35,    -1,    -1,    -1,    -1,    -1,    32,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    -1,    90,    91,    92,    93,    94,    95,
      -1,    97,    -1,    -1,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    35,    17,    18,    -1,    -1,    -1,    22,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,
      -1,    -1,    -1,    66,    67,    68,    69,    70,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,
      93,    94,    95,    -1,    97,    -1,    -1,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      64,    -1,    66,    67,    68,    69,    70,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,
      94,    95,    -1,    97,    -1,    -1,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    -1,    90,    91,    92,    93,    94,
      95,    -1,    97,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    39,    -1,    -1,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      22,    29,    30,    31,    41,    83,    84,    85,    86,    87,
      88,    89,    91,   116,   121,   123,   146,   147,   148,   149,
     150,   167,   170,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   188,   191,   194,   195,   199,   200,   201,   202,
     204,   206,   210,   212,   213,   219,   227,   241,   242,     9,
      11,    22,    84,    85,    86,    87,   123,   200,   210,    30,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    79,    80,    81,    82,   151,   152,   153,   154,
     156,   157,   158,    84,    85,   121,   171,   173,   201,   202,
     210,   219,   228,   229,     3,    12,    13,    14,    15,    17,
      18,    22,    66,    67,    68,    69,    70,    88,    90,    91,
      92,    93,    94,    95,    97,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   143,   260,   272,   143,   143,   230,     3,     6,    10,
      12,    13,    23,   247,   249,    26,   123,   242,    44,   280,
     281,    22,    83,    89,   123,   199,     0,   148,    49,   143,
     176,   211,   236,   237,   238,   239,   177,     4,     5,     6,
       9,    22,   184,     6,   181,   187,   200,   125,   189,    32,
      32,    36,    36,   143,   143,   143,    34,   192,     0,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    81,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     119,   121,   122,   123,   124,   125,   143,   144,   159,    30,
       3,    12,    13,    14,    15,    17,    18,    22,    66,    67,
      68,    69,    70,    88,    90,    91,    92,    93,    94,    95,
      97,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   144,   162,   163,
     162,    26,   119,   155,   144,    25,    27,    28,    32,    47,
      48,    60,    61,    78,   142,   143,   164,   224,   143,   230,
     143,   230,   173,    31,   143,    35,   233,   233,   233,   233,
      40,    23,    31,    36,    23,   171,   123,   189,    29,    87,
     240,    38,   234,    32,   143,   124,   239,     6,   185,     6,
       9,   186,   184,    36,   196,    32,    31,    17,   175,   203,
     205,   207,   208,   209,   210,   207,   143,   220,   221,    92,
      93,    94,    95,    96,    98,    99,   251,   252,   253,   266,
     269,   275,   276,   277,   193,   211,   237,   189,    26,   118,
     164,   190,   162,   144,    26,    27,    32,    44,   226,   164,
      32,   143,   164,    32,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    65,   141,    35,    36,   215,   215,    31,   214,
     215,   214,    19,    20,    21,    23,    25,    27,    32,   142,
     168,   169,   190,   211,   222,   223,   224,    40,   251,    32,
      31,    31,    19,    29,    87,   124,   222,   235,   236,   237,
     234,     6,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      31,    32,    33,    34,    35,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    81,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   119,   121,   122,   123,   124,   125,   145,   196,
     197,   198,   190,   236,    32,    33,    34,    34,    33,    34,
      40,    34,   231,   211,   256,   222,   245,   270,   271,   272,
     280,   211,   143,   278,   279,   211,   267,   271,    37,   252,
     222,    34,    31,    32,    26,   177,   225,   226,    22,    33,
     143,   119,   164,   165,   166,   164,   164,    32,   121,   172,
     173,   174,   175,   216,   219,   228,   229,   211,   211,    17,
      22,   175,   222,   222,    31,    65,   141,   168,    37,    14,
      15,    16,    17,    33,   243,   244,   246,   248,   249,   250,
      39,    39,    32,   143,    37,   198,    33,    32,   234,   207,
     234,    64,   209,   234,    64,   222,   221,    37,    40,    31,
      40,    31,    32,    24,    40,    32,    31,    34,    32,    31,
      31,   211,    64,   143,   160,   161,   236,    33,    33,    33,
      34,    35,    25,   174,    35,   232,    37,   172,   233,   233,
      33,    33,   222,   222,    31,    35,    33,    34,   245,   236,
      32,    33,   236,    33,    34,    33,    33,    19,    89,    90,
     109,   222,   255,   257,   258,   259,   260,   281,   270,   211,
     280,   193,   279,    17,   193,   268,    33,    34,   164,   164,
      34,    25,    35,    34,   217,   232,   215,   215,   222,    35,
     246,    35,   244,   246,    40,   143,   207,    33,   234,    64,
     234,   234,   109,   257,    17,    18,    32,   260,   263,    32,
      32,   255,    34,   273,   211,    33,    33,   162,    64,   143,
      25,    35,    32,   211,   218,   232,    31,   217,   222,   246,
     280,   168,    33,    33,    33,   268,    32,   222,   245,    64,
     270,   274,    33,    31,    97,    33,    35,    25,   232,    34,
      31,    64,    32,    33,   234,    33,   245,    34,    34,   261,
      33,    34,    18,   271,   272,    32,    34,   211,   232,    24,
     207,    32,    97,    32,   222,   211,   254,   255,   256,   262,
     281,    33,   270,    25,    25,   232,    33,    33,   207,   263,
     264,   265,   270,    33,    34,   255,    34,    33,    35,    33,
      33,    32,    33,    34,   254,    25,   246,    32,   234,   245,
      33,   270,    33,   207,    32,    33,   264,   234,    33,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short yyr1[] =
{
       0,   140,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     142,   142,   142,   142,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   144,   144,   144,   144,
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
     144,   144,   144,   144,   145,   145,   145,   145,   145,   145,
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
     145,   145,   145,   145,   145,   145,   145,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   148,   148,   148,   148,
     148,   148,   148,   148,   148,   148,   148,   148,   149,   150,
     150,   151,   151,   151,   151,   151,   151,   151,   151,   152,
     152,   153,   153,   154,   154,   154,   155,   155,   156,   156,
     157,   157,   157,   158,   158,   159,   159,   159,   159,   160,
     160,   160,   160,   161,   161,   162,   162,   163,   163,   164,
     164,   164,   164,   164,   164,   164,   164,   164,   164,   164,
     165,   165,   166,   166,   166,   167,   167,   168,   168,   168,
     169,   169,   169,   170,   170,   171,   171,   172,   172,   173,
     173,   173,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   175,   176,   176,   177,   177,   178,   178,   178,   179,
     179,   179,   179,   180,   180,   180,   181,   181,   182,   182,
     182,   183,   183,   183,   183,   184,   184,   184,   184,   184,
     184,   185,   185,   186,   186,   186,   186,   187,   187,   187,
     188,   188,   189,   189,   190,   190,   191,   192,   192,   193,
     193,   194,   195,   195,   195,   195,   195,   195,   196,   197,
     197,   198,   198,   199,   199,   200,   200,   201,   201,   202,
     202,   202,   202,   203,   203,   204,   205,   206,   207,   207,
     207,   208,   208,   209,   209,   209,   210,   210,   211,   211,
     212,   213,   214,   214,   215,   216,   216,   217,   217,   218,
     218,   218,   218,   219,   220,   220,   221,   221,   222,   222,
     222,   222,   222,   222,   223,   223,   223,   223,   223,   223,
     224,   224,   225,   225,   226,   226,   226,   227,   228,   229,
     230,   230,   231,   231,   232,   232,   232,   232,   233,   233,
     234,   234,   234,   235,   235,   235,   235,   236,   236,   237,
     237,   238,   238,   239,   239,   240,   240,   241,   241,   242,
     242,   242,   243,   243,   244,   244,   245,   246,   247,   248,
     248,   249,   249,   249,   249,   249,   250,   250,   250,   250,
     251,   251,   252,   252,   252,   252,   252,   253,   253,   254,
     254,   254,   255,   255,   255,   255,   255,   255,   256,   256,
     257,   258,   258,   259,   260,   260,   260,   260,   260,   260,
     260,   260,   260,   260,   261,   261,   262,   262,   263,   263,
     264,   264,   265,   265,   266,   267,   267,   268,   268,   268,
     269,   270,   270,   270,   271,   271,   272,   272,   272,   272,
     272,   272,   272,   272,   273,   273,   274,   274,   275,   276,
     276,   277,   278,   278,   279,   280,   280,   281
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     2,     2,     1,     2,     2,     2,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     6,     2,     2,     0,
       1,     1,     3,     1,     3,     0,     1,     1,     2,     3,
       2,     3,     5,     2,     4,     1,     1,     1,     1,     4,
       0,     1,     1,     1,     3,     6,     5,     1,     1,     1,
       1,     1,     1,     3,     4,     1,     2,     1,     2,     1,
       1,     2,     4,     4,     1,     1,     1,     3,     3,     1,
       2,     2,     1,     1,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     1,     2,     2,     0,     1,     1,     2,     1,
       2,     0,     1,     0,     1,     1,     2,     0,     1,     2,
       3,     4,     0,     4,     1,     2,     5,     0,     2,     1,
       3,     3,     1,     2,     2,     3,     1,     2,     3,     1,
       2,     1,     1,     1,     2,     1,     1,     5,     7,     5,
       7,    13,    16,     5,     7,     6,     5,     1,     0,     1,
       1,     1,     3,     1,     1,     3,     1,     2,     3,     2,
       4,     4,     1,     1,     3,     4,     5,     0,     2,     2,
       4,     1,     3,     5,     1,     3,     1,     3,     1,     4,
       3,     3,     2,     5,     1,     1,     1,     1,     1,     1,
       4,     2,     1,     2,     2,     1,     1,     2,     2,     2,
       0,     1,     0,     1,     0,     2,     7,     9,     0,     7,
       0,     3,     3,     0,     1,     1,     1,     0,     1,     1,
       2,     1,     2,     1,     2,     1,     1,     4,     5,     7,
       8,    13,     1,     3,     2,     4,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     3,     6,     1,
       2,     1,     1,     1,     1,     2,     1,     1,     3,     4,
       6,     8,    12,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     3,     1,     1,
       0,     1,     1,     3,     3,     6,     1,     0,     1,     1,
       3,     1,     1,     3,     5,     6,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     2,     1,     3,     3,     1,
       1,     3,     1,     3,     4,     0,     1,     1
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
       0,     0,     0,     0,     0,     1,     2,     2,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     2,     1,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       1,     0,     0,     0,     2,     1,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0
};

/* YYCONFLP[YYPACT[STATE-NUM]] -- Pointer into YYCONFL of start of
   list of conflicting reductions corresponding to action entry for
   state STATE-NUM in yytable.  0 means no conflicts.  The list in
   yyconfl is terminated by a rule number of 0.  */
static const unsigned short yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    15,     0,     0,     0,     0,     0,     0,     0,  3714,
       0,  3716,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3700,  3702,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3696,     0,     0,     0,
       0,     0,     0,     0,     0,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  3706,     0,  3708,  3710,     0,  3718,
       0,  3720,  3722,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  3698,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  3704,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,     0,     0,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3712,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3724,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   167,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       0,     0,     0,     0,     3,     0,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,    21,    23,    25,    27,     0,
      29,    31,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,    35,    37,    39,    41,    43,    45,    47,    49,
      51,    53,    55,    57,     0,    59,    61,    63,    65,    67,
      69,    71,    73,    75,    77,    79,    81,    83,    85,    87,
      89,    91,    93,     0,     0,     0,     0,     0,    95,    97,
      99,   101,   103,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     107,   109,     0,   111,   113,   115,   117,   119,   121,     0,
     123,     0,     0,   125,   127,   129,   131,   133,   135,   137,
     139,   141,   143,   145,   147,   149,   151,   153,   155,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   157,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   169,     0,     0,     0,
       0,     0,     0,     0,     0,   171,   173,   175,   177,     0,
     179,   181,     0,     0,     0,   183,     0,     0,   185,   187,
     189,   191,     0,     0,     0,   193,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     195,   197,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   199,   201,     0,     0,     0,     0,   203,
     205,   207,   209,   211,     0,     0,     0,     0,     0,     0,
       0,   213,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,   217,   219,   221,   223,   225,   227,     0,
     229,     0,     0,   231,   233,   235,   237,   239,   241,   243,
     245,   247,   249,   251,   253,   255,   257,   259,   261,   263,
       0,     0,     0,     0,     0,     0,     0,     0,   265,   267,
     269,   271,     0,   273,   275,     0,     0,     0,   277,     0,
       0,   279,   281,   283,   285,     0,     0,     0,   287,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   289,   291,     0,     0,     0,   159,     0,
       0,     0,     0,   161,     0,     0,   293,   295,     0,     0,
     163,     0,   297,   299,   301,   303,   305,     0,     0,     0,
       0,     0,     0,     0,   307,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   309,     0,   311,   313,   315,   317,
     319,   321,     0,   323,     0,     0,   325,   327,   329,   331,
     333,   335,   337,   339,   341,   343,   345,   347,   349,   351,
     353,   355,   357,     0,     0,     0,     0,     0,   165,     0,
       0,   359,   361,   363,   365,     0,   367,   369,     0,     0,
       0,   371,     0,     0,   373,   375,   377,   379,     0,     0,
       0,   381,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   383,   385,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   387,
     389,     0,     0,     0,     0,   391,   393,   395,   397,   399,
       0,     0,     0,     0,     0,     0,     0,   401,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   403,     0,   405,
     407,   409,   411,   413,   415,     0,   417,     0,     0,   419,
     421,   423,   425,   427,   429,   431,   433,   435,   437,   439,
     441,   443,   445,   447,   449,   451,     0,     0,     0,     0,
       0,     0,     0,     0,   453,   455,   457,   459,     0,   461,
     463,     0,     0,     0,   465,     0,     0,   467,   469,   471,
     473,     0,     0,     0,   475,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   477,
     479,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   481,   483,     0,     0,     0,     0,   485,   487,
     489,   491,   493,     0,     0,     0,     0,     0,     0,     0,
     495,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     497,     0,   499,   501,   503,   505,   507,   509,     0,   511,
       0,     0,   513,   515,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   535,   537,   539,   541,   543,   545,     0,
       0,     0,     0,     0,     0,     0,     0,   547,   549,   551,
     553,     0,   555,   557,     0,     0,     0,   559,     0,     0,
     561,   563,   565,   567,     0,     0,     0,   569,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   571,   573,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   575,   577,     0,     0,     0,
       0,   579,   581,   583,   585,   587,     0,     0,     0,     0,
       0,     0,     0,   589,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   591,     0,   593,   595,   597,   599,   601,
     603,     0,   605,     0,     0,   607,   609,   611,   613,   615,
     617,   619,   621,   623,   625,   627,   629,   631,   633,   635,
     637,   639,     0,     0,     0,     0,     0,     0,     0,     0,
     641,   643,   645,   647,     0,   649,   651,     0,     0,     0,
     653,     0,     0,   655,   657,   659,   661,     0,     0,     0,
     663,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   665,   667,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   669,   671,
       0,     0,     0,     0,   673,   675,   677,   679,   681,     0,
       0,     0,     0,     0,     0,     0,   683,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   685,     0,   687,   689,
     691,   693,   695,   697,     0,   699,     0,     0,   701,   703,
     705,   707,   709,   711,   713,   715,   717,   719,   721,   723,
     725,   727,   729,   731,   733,     0,     0,     0,     0,     0,
       0,     0,     0,   736,   739,   742,   745,     0,   748,   751,
       0,     0,     0,   754,     0,     0,   757,   760,   763,   766,
       0,     0,     0,   769,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   772,   775,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   778,   781,     0,     0,     0,     0,   784,   787,   790,
     793,   796,     0,     0,     0,     0,     0,     0,     0,   799,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   802,
       0,   805,   808,   811,   814,   817,   820,     0,   823,     0,
       0,   826,   829,   832,   835,   838,   841,   844,   847,   850,
     853,   856,   859,   862,   865,   868,   871,   876,     0,   874,
       0,     0,     0,     0,     0,     0,   878,   880,   882,   884,
       0,   886,   888,     0,     0,     0,   890,     0,     0,   892,
     894,   896,   898,     0,     0,     0,   900,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   902,   904,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   906,   908,     0,     0,     0,     0,
     910,   912,   914,   916,   918,     0,     0,     0,     0,     0,
       0,     0,   920,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   922,     0,   924,   926,   928,   930,   932,   934,
       0,   936,     0,     0,   938,   940,   942,   944,   946,   948,
     950,   952,   954,   956,   958,   960,   962,   964,   966,   968,
     970,     0,     0,     0,     0,     0,     0,     0,     0,   972,
     974,   976,   978,     0,   980,   982,     0,     0,     0,   984,
       0,     0,   986,   988,   990,   992,     0,     0,     0,   994,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   996,   998,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1000,  1002,     0,
       0,     0,     0,  1004,  1006,  1008,  1010,  1012,     0,     0,
       0,     0,     0,     0,     0,  1014,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1016,     0,  1018,  1020,  1022,
    1024,  1026,  1028,     0,  1030,     0,     0,  1032,  1034,  1036,
    1038,  1040,  1042,  1044,  1046,  1048,  1050,  1052,  1054,  1056,
    1058,  1060,  1062,  1064,     0,     0,     0,     0,     0,     0,
       0,     0,  1066,  1068,  1070,  1072,     0,  1074,  1076,     0,
       0,     0,  1078,     0,     0,  1080,  1082,  1084,  1086,     0,
       0,     0,  1088,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1090,  1092,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1094,  1096,     0,     0,     0,     0,  1098,  1100,  1102,  1104,
    1106,     0,     0,     0,     0,     0,     0,     0,  1108,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1110,     0,
    1112,  1114,  1116,  1118,  1120,  1122,     0,  1124,     0,     0,
    1126,  1128,  1130,  1132,  1134,  1136,  1138,  1140,  1142,  1144,
    1146,  1148,  1150,  1152,  1154,  1156,  1158,     0,     0,     0,
       0,     0,     0,     0,     0,  1160,  1162,  1164,  1166,     0,
    1168,  1170,     0,     0,     0,  1172,     0,     0,  1174,  1176,
    1178,  1180,     0,     0,     0,  1182,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1184,  1186,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1188,  1190,     0,     0,     0,     0,  1192,
    1194,  1196,  1198,  1200,     0,     0,     0,     0,     0,     0,
       0,  1202,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1204,     0,  1206,  1208,  1210,  1212,  1214,  1216,     0,
    1218,     0,     0,  1220,  1222,  1224,  1226,  1228,  1230,  1232,
    1234,  1236,  1238,  1240,  1242,  1244,  1246,  1248,  1250,  1252,
       0,     0,     0,     0,     0,     0,     0,     0,  1254,  1256,
    1258,  1260,     0,  1262,  1264,     0,     0,     0,  1266,     0,
       0,  1268,  1270,  1272,  1274,     0,     0,     0,  1276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1278,  1280,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1282,  1284,     0,     0,
       0,     0,  1286,  1288,  1290,  1292,  1294,     0,     0,     0,
       0,     0,     0,     0,  1296,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1298,     0,  1300,  1302,  1304,  1306,
    1308,  1310,     0,  1312,     0,     0,  1314,  1316,  1318,  1320,
    1322,  1324,  1326,  1328,  1330,  1332,  1334,  1336,  1338,  1340,
    1342,  1344,  1346,     0,     0,     0,     0,     0,     0,     0,
       0,  1348,  1350,  1352,  1354,     0,  1356,  1358,     0,     0,
       0,  1360,     0,     0,  1362,  1364,  1366,  1368,     0,     0,
       0,  1370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1372,  1374,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1376,
    1378,     0,     0,     0,     0,  1380,  1382,  1384,  1386,  1388,
       0,     0,     0,     0,     0,     0,     0,  1390,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1392,     0,  1394,
    1396,  1398,  1400,  1402,  1404,     0,  1406,     0,     0,  1408,
    1410,  1412,  1414,  1416,  1418,  1420,  1422,  1424,  1426,  1428,
    1430,  1432,  1434,  1436,  1438,  1440,     0,     0,     0,     0,
       0,     0,     0,     0,  1442,  1444,  1446,  1448,     0,  1450,
    1452,     0,     0,     0,  1454,     0,     0,  1456,  1458,  1460,
    1462,     0,     0,     0,  1464,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1466,
    1468,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1470,  1472,     0,     0,     0,     0,  1474,  1476,
    1478,  1480,  1482,     0,     0,     0,     0,     0,     0,     0,
    1484,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1486,     0,  1488,  1490,  1492,  1494,  1496,  1498,     0,  1500,
       0,     0,  1502,  1504,  1506,  1508,  1510,  1512,  1514,  1516,
    1518,  1520,  1522,  1524,  1526,  1528,  1530,  1532,  1534,     0,
       0,     0,     0,     0,     0,     0,     0,  1536,  1538,  1540,
    1542,     0,  1544,  1546,     0,     0,     0,  1548,     0,     0,
    1550,  1552,  1554,  1556,     0,     0,     0,  1558,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1560,  1562,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1564,  1566,     0,     0,     0,
       0,  1568,  1570,  1572,  1574,  1576,     0,     0,     0,     0,
       0,     0,     0,  1578,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1580,     0,  1582,  1584,  1586,  1588,  1590,
    1592,     0,  1594,     0,     0,  1596,  1598,  1600,  1602,  1604,
    1606,  1608,  1610,  1612,  1614,  1616,  1618,  1620,  1622,  1624,
    1626,  1628,     0,     0,     0,     0,     0,     0,     0,     0,
    1630,  1632,  1634,  1636,     0,  1638,  1640,     0,     0,     0,
    1642,     0,     0,  1644,  1646,  1648,  1650,     0,     0,     0,
    1652,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1654,  1656,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1658,  1660,
       0,     0,     0,     0,  1662,  1664,  1666,  1668,  1670,     0,
       0,     0,     0,     0,     0,     0,  1672,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1674,     0,  1676,  1678,
    1680,  1682,  1684,  1686,     0,  1688,     0,     0,  1690,  1692,
    1694,  1696,  1698,  1700,  1702,  1704,  1706,  1708,  1710,  1712,
    1714,  1716,  1718,  1720,  1722,     0,     0,     0,     0,     0,
       0,     0,     0,  1724,  1726,  1728,  1730,     0,  1732,  1734,
       0,     0,     0,  1736,     0,     0,  1738,  1740,  1742,  1744,
       0,     0,     0,  1746,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1748,  1750,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1752,  1754,     0,     0,     0,     0,  1756,  1758,  1760,
    1762,  1764,     0,     0,     0,     0,     0,     0,     0,  1766,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1768,
       0,  1770,  1772,  1774,  1776,  1778,  1780,     0,  1782,     0,
       0,  1784,  1786,  1788,  1790,  1792,  1794,  1796,  1798,  1800,
    1802,  1804,  1806,  1808,  1810,  1812,  1814,  1816,     0,     0,
       0,     0,     0,     0,     0,     0,  1818,  1820,  1822,  1824,
       0,  1826,  1828,     0,     0,     0,  1830,     0,     0,  1832,
    1834,  1836,  1838,     0,     0,     0,  1840,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1842,  1844,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1846,  1848,     0,     0,     0,     0,
    1850,  1852,  1854,  1856,  1858,     0,     0,     0,     0,     0,
       0,     0,  1860,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1862,     0,  1864,  1866,  1868,  1870,  1872,  1874,
       0,  1876,     0,     0,  1878,  1880,  1882,  1884,  1886,  1888,
    1890,  1892,  1894,  1896,  1898,  1900,  1902,  1904,  1906,  1908,
    1910,     0,     0,     0,     0,     0,     0,     0,     0,  1912,
    1914,  1916,  1918,     0,  1920,  1922,     0,     0,     0,  1924,
       0,     0,  1926,  1928,  1930,  1932,     0,     0,     0,  1934,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1936,  1938,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1940,  1942,     0,
       0,     0,     0,  1944,  1946,  1948,  1950,  1952,     0,     0,
       0,     0,     0,     0,     0,  1954,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1956,     0,  1958,  1960,  1962,
    1964,  1966,  1968,     0,  1970,     0,     0,  1972,  1974,  1976,
    1978,  1980,  1982,  1984,  1986,  1988,  1990,  1992,  1994,  1996,
    1998,  2000,  2002,  2004,     0,     0,     0,     0,     0,     0,
       0,     0,  2006,  2008,  2010,  2012,     0,  2014,  2016,     0,
       0,     0,  2018,     0,     0,  2020,  2022,  2024,  2026,     0,
       0,     0,  2028,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2030,  2032,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2034,  2036,     0,     0,     0,     0,  2038,  2040,  2042,  2044,
    2046,     0,     0,     0,     0,     0,     0,     0,  2048,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2050,     0,
    2052,  2054,  2056,  2058,  2060,  2062,     0,  2064,     0,     0,
    2066,  2068,  2070,  2072,  2074,  2076,  2078,  2080,  2082,  2084,
    2086,  2088,  2090,  2092,  2094,  2096,  2098,     0,     0,     0,
       0,     0,     0,     0,     0,  2100,  2102,  2104,  2106,     0,
    2108,  2110,     0,     0,     0,  2112,     0,     0,  2114,  2116,
    2118,  2120,     0,     0,     0,  2122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2124,  2126,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2128,  2130,     0,     0,     0,     0,  2132,
    2134,  2136,  2138,  2140,     0,     0,     0,     0,     0,     0,
       0,  2142,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2144,     0,  2146,  2148,  2150,  2152,  2154,  2156,     0,
    2158,     0,     0,  2160,  2162,  2164,  2166,  2168,  2170,  2172,
    2174,  2176,  2178,  2180,  2182,  2184,  2186,  2188,  2190,  2192,
       0,     0,     0,     0,     0,     0,     0,     0,  2194,  2196,
    2198,  2200,     0,  2202,  2204,     0,     0,     0,  2206,     0,
       0,  2208,  2210,  2212,  2214,     0,     0,     0,  2216,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2218,  2220,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2222,  2224,     0,     0,
       0,     0,  2226,  2228,  2230,  2232,  2234,     0,     0,     0,
       0,     0,     0,     0,  2236,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2238,     0,  2240,  2242,  2244,  2246,
    2248,  2250,     0,  2252,     0,     0,  2254,  2256,  2258,  2260,
    2262,  2264,  2266,  2268,  2270,  2272,  2274,  2276,  2278,  2280,
    2282,  2284,  2286,     0,     0,     0,     0,     0,     0,     0,
       0,  2288,  2290,  2292,  2294,     0,  2296,  2298,     0,     0,
       0,  2300,     0,     0,  2302,  2304,  2306,  2308,     0,     0,
       0,  2310,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2312,  2314,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2316,
    2318,     0,     0,     0,     0,  2320,  2322,  2324,  2326,  2328,
       0,     0,     0,     0,     0,     0,     0,  2330,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2332,     0,  2334,
    2336,  2338,  2340,  2342,  2344,     0,  2346,     0,     0,  2348,
    2350,  2352,  2354,  2356,  2358,  2360,  2362,  2364,  2366,  2368,
    2370,  2372,  2374,  2376,  2378,  2380,     0,     0,     0,     0,
       0,     0,     0,     0,  2382,  2384,  2386,  2388,     0,  2390,
    2392,     0,     0,     0,  2394,     0,     0,  2396,  2398,  2400,
    2402,     0,     0,     0,  2404,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2406,
    2408,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2410,  2412,     0,     0,     0,     0,  2414,  2416,
    2418,  2420,  2422,     0,     0,     0,     0,     0,     0,     0,
    2424,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2426,     0,  2428,  2430,  2432,  2434,  2436,  2438,     0,  2440,
       0,     0,  2442,  2444,  2446,  2448,  2450,  2452,  2454,  2456,
    2458,  2460,  2462,  2464,  2466,  2468,  2470,  2472,  2474,     0,
       0,     0,     0,     0,     0,     0,     0,  2476,  2478,  2480,
    2482,     0,  2484,  2486,     0,     0,     0,  2488,     0,     0,
    2490,  2492,  2494,  2496,     0,     0,     0,  2498,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2500,  2502,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2504,  2506,     0,     0,     0,
       0,  2508,  2510,  2512,  2514,  2516,     0,     0,     0,     0,
       0,     0,     0,  2518,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2520,     0,  2522,  2524,  2526,  2528,  2530,
    2532,     0,  2534,     0,     0,  2536,  2538,  2540,  2542,  2544,
    2546,  2548,  2550,  2552,  2554,  2556,  2558,  2560,  2562,  2564,
    2566,  2568,     0,     0,     0,     0,     0,     0,     0,     0,
    2570,  2572,  2574,  2576,     0,  2578,  2580,     0,     0,     0,
    2582,     0,     0,  2584,  2586,  2588,  2590,     0,     0,     0,
    2592,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2594,  2596,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2598,  2600,
       0,     0,     0,     0,  2602,  2604,  2606,  2608,  2610,     0,
       0,     0,     0,     0,     0,     0,  2612,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2614,     0,  2616,  2618,
    2620,  2622,  2624,  2626,     0,  2628,     0,     0,  2630,  2632,
    2634,  2636,  2638,  2640,  2642,  2644,  2646,  2648,  2650,  2652,
    2654,  2656,  2658,  2660,  2662,     0,     0,     0,     0,     0,
       0,     0,     0,  2664,  2666,  2668,  2670,     0,  2672,  2674,
       0,     0,     0,  2676,     0,     0,  2678,  2680,  2682,  2684,
       0,     0,     0,  2686,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2688,  2690,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2692,  2694,     0,     0,     0,     0,  2696,  2698,  2700,
    2702,  2704,     0,     0,     0,     0,     0,     0,     0,  2706,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2708,
       0,  2710,  2712,  2714,  2716,  2718,  2720,     0,  2722,     0,
       0,  2724,  2726,  2728,  2730,  2732,  2734,  2736,  2738,  2740,
    2742,  2744,  2746,  2748,  2750,  2752,  2754,  2756,     0,     0,
       0,     0,     0,     0,     0,     0,  2758,  2760,  2762,  2764,
       0,  2766,  2768,     0,     0,     0,  2770,     0,     0,  2772,
    2774,  2776,  2778,     0,     0,     0,  2780,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2782,  2784,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2786,  2788,     0,     0,     0,     0,
    2790,  2792,  2794,  2796,  2798,     0,     0,     0,     0,     0,
       0,     0,  2800,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2802,     0,  2804,  2806,  2808,  2810,  2812,  2814,
       0,  2816,     0,     0,  2818,  2820,  2822,  2824,  2826,  2828,
    2830,  2832,  2834,  2836,  2838,  2840,  2842,  2844,  2846,  2848,
    2850,     0,     0,     0,     0,     0,     0,     0,     0,  2852,
    2854,  2856,  2858,     0,  2860,  2862,     0,     0,     0,  2864,
       0,     0,  2866,  2868,  2870,  2872,     0,     0,     0,  2874,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2876,  2878,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2880,  2882,     0,
       0,     0,     0,  2884,  2886,  2888,  2890,  2892,     0,     0,
       0,     0,     0,     0,     0,  2894,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2896,     0,  2898,  2900,  2902,
    2904,  2906,  2908,     0,  2910,     0,     0,  2912,  2914,  2916,
    2918,  2920,  2922,  2924,  2926,  2928,  2930,  2932,  2934,  2936,
    2938,  2940,  2942,  2944,     0,     0,     0,     0,     0,     0,
       0,     0,  2946,  2948,  2950,  2952,     0,  2954,  2956,     0,
       0,     0,  2958,     0,     0,  2960,  2962,  2964,  2966,     0,
       0,     0,  2968,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2970,  2972,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2974,  2976,     0,     0,     0,     0,  2978,  2980,  2982,  2984,
    2986,     0,     0,     0,     0,     0,     0,     0,  2988,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2990,     0,
    2992,  2994,  2996,  2998,  3000,  3002,     0,  3004,     0,     0,
    3006,  3008,  3010,  3012,  3014,  3016,  3018,  3020,  3022,  3024,
    3026,  3028,  3030,  3032,  3034,  3036,  3038,     0,     0,     0,
       0,     0,     0,     0,     0,  3040,  3042,  3044,  3046,     0,
    3048,  3050,     0,     0,     0,  3052,     0,     0,  3054,  3056,
    3058,  3060,     0,     0,     0,  3062,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3064,  3066,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3068,  3070,     0,     0,     0,     0,  3072,
    3074,  3076,  3078,  3080,     0,     0,     0,     0,     0,     0,
       0,  3082,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3084,     0,  3086,  3088,  3090,  3092,  3094,  3096,     0,
    3098,     0,     0,  3100,  3102,  3104,  3106,  3108,  3110,  3112,
    3114,  3116,  3118,  3120,  3122,  3124,  3126,  3128,  3130,  3132,
       0,     0,     0,     0,     0,     0,     0,     0,  3134,  3136,
    3138,  3140,     0,  3142,  3144,     0,     0,     0,  3146,     0,
       0,  3148,  3150,  3152,  3154,     0,     0,     0,  3156,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3158,  3160,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3162,  3164,     0,     0,
       0,     0,  3166,  3168,  3170,  3172,  3174,     0,     0,     0,
       0,     0,     0,     0,  3176,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  3178,     0,  3180,  3182,  3184,  3186,
    3188,  3190,     0,  3192,     0,     0,  3194,  3196,  3198,  3200,
    3202,  3204,  3206,  3208,  3210,  3212,  3214,  3216,  3218,  3220,
    3222,  3224,  3226,     0,     0,     0,     0,     0,     0,     0,
       0,  3228,  3230,  3232,  3234,     0,  3236,  3238,     0,     0,
       0,  3240,     0,     0,  3242,  3244,  3246,  3248,     0,     0,
       0,  3250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3252,  3254,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3256,
    3258,     0,     0,     0,     0,  3260,  3262,  3264,  3266,  3268,
       0,     0,     0,     0,     0,     0,     0,  3270,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  3272,     0,  3274,
    3276,  3278,  3280,  3282,  3284,     0,  3286,     0,     0,  3288,
    3290,  3292,  3294,  3296,  3298,  3300,  3302,  3304,  3306,  3308,
    3310,  3312,  3314,  3316,  3318,  3320,     0,     0,     0,     0,
       0,     0,     0,     0,  3322,  3324,  3326,  3328,     0,  3330,
    3332,     0,     0,     0,  3334,     0,     0,  3336,  3338,  3340,
    3342,     0,     0,     0,  3344,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3346,
    3348,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3350,  3352,     0,     0,     0,     0,  3354,  3356,
    3358,  3360,  3362,     0,     0,     0,     0,     0,     0,     0,
    3364,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3366,     0,  3368,  3370,  3372,  3374,  3376,  3378,     0,  3380,
       0,     0,  3382,  3384,  3386,  3388,  3390,  3392,  3394,  3396,
    3398,  3400,  3402,  3404,  3406,  3408,  3410,  3412,  3414,     0,
       0,     0,     0,     0,     0,     0,     0,  3416,  3418,  3420,
    3422,     0,  3424,  3426,     0,     0,     0,  3428,     0,     0,
    3430,  3432,  3434,  3436,     0,     0,     0,  3438,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3440,  3442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3444,  3446,     0,     0,     0,
       0,  3448,  3450,  3452,  3454,  3456,     0,     0,     0,     0,
       0,     0,     0,  3458,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3460,     0,  3462,  3464,  3466,  3468,  3470,
    3472,     0,  3474,     0,     0,  3476,  3478,  3480,  3482,  3484,
    3486,  3488,  3490,  3492,  3494,  3496,  3498,  3500,  3502,  3504,
    3506,  3508,     0,     0,     0,     0,     0,     0,     0,     0,
    3510,  3512,  3514,  3516,     0,  3518,  3520,     0,     0,     0,
    3522,     0,     0,  3524,  3526,  3528,  3530,     0,     0,     0,
    3532,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3534,  3536,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  3538,  3540,
       0,     0,     0,     0,  3542,  3544,  3546,  3548,  3550,     0,
       0,     0,     0,     0,     0,     0,  3552,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3554,     0,  3556,  3558,
    3560,  3562,  3564,  3566,     0,  3568,     0,     0,  3570,  3572,
    3574,  3576,  3578,  3580,  3582,  3584,  3586,  3588,  3590,  3592,
    3594,  3596,  3598,  3600,  3602,     0,     0,     0,     0,     0,
       0,     0,     0,  3604,  3606,  3608,  3610,     0,  3612,  3614,
       0,     0,     0,  3616,     0,     0,  3618,  3620,  3622,  3624,
       0,     0,     0,  3626,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  3628,  3630,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3632,  3634,     0,     0,     0,     0,  3636,  3638,  3640,
    3642,  3644,     0,     0,     0,     0,     0,     0,     0,  3646,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3648,
       0,  3650,  3652,  3654,  3656,  3658,  3660,     0,  3662,     0,
       0,  3664,  3666,  3668,  3670,  3672,  3674,  3676,  3678,  3680,
    3682,  3684,  3686,  3688,  3690,  3692,  3694,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3726,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3728
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,   391,     0,   391,     0,   391,     0,   391,     0,   382,
       0,   382,     0,   405,     0,   466,     0,   466,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   622,
       0,   622,     0,   622,     0,   622,     0,   622,     0,   391,
       0,   391,     0,   391,     0,   391,     0,   405,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    46,     0,    46,     0,    46,     0,    46,
       0,    46,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    57,     0,    57,     0,    57,
       0,    57,     0,    57,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,    58,
       0,    58,     0,    58,     0,    58,     0,    58,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   623,     0,   623,     0,   623,     0,   623,
       0,   623,     0,   584,   622,     0,   584,   622,     0,   584,
     622,     0,   584,   622,     0,   584,   622,     0,   584,   622,
       0,   584,   622,     0,   584,   622,     0,   584,   622,     0,
     584,   622,     0,   584,   622,     0,   584,   622,     0,   584,
     622,     0,   584,   622,     0,   584,   622,     0,   584,   622,
       0,   584,   622,     0,   584,   622,     0,   584,   622,     0,
     584,   622,     0,   584,   622,     0,   584,   622,     0,   584,
     622,     0,   584,   622,     0,   584,   622,     0,   584,   622,
       0,   584,   622,     0,   584,   622,     0,   584,   622,     0,
     584,   622,     0,   584,   622,     0,   584,   622,     0,   584,
     622,     0,   584,   622,     0,   584,   622,     0,   584,   622,
       0,   584,   622,     0,   584,   622,     0,   584,   622,     0,
     584,   622,     0,   584,   622,     0,   584,   622,     0,   584,
     622,     0,   584,   622,     0,   584,   622,     0,   584,   622,
       0,   584,   622,     0,   622,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
      65,     0,    65,     0,    65,     0,    65,     0,    65,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   109,     0,   109,     0,   109,     0,
     109,     0,   109,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   110,     0,
     110,     0,   110,     0,   110,     0,   110,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   108,     0,   108,     0,   108,     0,   108,     0,
     108,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   131,     0,   131,     0,
     131,     0,   131,     0,   131,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     132,     0,   132,     0,   132,     0,   132,     0,   132,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   133,     0,   133,     0,   133,     0,
     133,     0,   133,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   134,     0,
     134,     0,   134,     0,   134,     0,   134,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   163,     0,   163,     0,   163,     0,   163,     0,
     163,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   592,     0,   592,     0,
     592,     0,   592,     0,   592,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     591,     0,   591,     0,   591,     0,   591,     0,   591,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   589,     0,   589,     0,   589,     0,
     589,     0,   589,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   587,     0,
     587,     0,   587,     0,   587,     0,   587,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   588,     0,   588,     0,   588,     0,   588,     0,
     588,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   590,     0,   590,     0,
     590,     0,   590,     0,   590,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     586,     0,   586,     0,   586,     0,   586,     0,   586,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   593,     0,
     593,     0,   593,     0,   593,     0,   593,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   147,     0,   147,     0,   147,     0,   147,     0,
     147,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   621,     0,   621,     0,
     621,     0,   621,     0,   621,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     619,     0,   619,     0,   619,     0,   619,     0,   619,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   618,     0,   618,     0,   618,     0,
     618,     0,   618,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   620,     0,
     620,     0,   620,     0,   620,     0,   620,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   617,     0,   617,     0,   617,     0,   617,     0,
     617,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   616,     0,   616,     0,
     616,     0,   616,     0,   616,     0,   511,     0,   511,     0,
     459,     0,   459,     0,   460,     0,   497,     0,   497,     0,
     497,     0,    45,     0,   623,     0,   391,     0,   572,     0,
     572,     0,   572,     0,   623,     0,   342,     0,   493,     0
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (P);
  YYUSE (tokens);
  YYUSE (index);
  if (!yyvaluep)
    return;
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, P, tokens, index);
  YYFPRINTF (yyo, ")");
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

  return (size_t) (yystpcpy (yyres, yystr) - yyres);
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
typedef short yyItemNum;

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
yyuserAction (yyRuleNum yyn, int yyrhslen, yyGLRStackItem* yyvsp,
              yyGLRStack* yystackp,
              YYSTYPE* yyvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  yybool yynormal YY_ATTRIBUTE_UNUSED = (yybool) (yystackp->yysplitPoint == YY_NULLPTR);
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
# define YYFILL(N) yyfill (yyvsp, &yylow, (N), yynormal)
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
  case 287:
#line 431 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		psi_cpp_exp_exec((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 4499 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 288:
#line 437 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	char *libname = strdup((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text->val);
	P->file.libnames = psi_plist_add(P->file.libnames, &libname);
}
#line 4508 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 289:
#line 441 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_const(P, (*(struct psi_const **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4516 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 290:
#line 444 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_decl(P, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4524 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 291:
#line 447 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_decl_extvars(P, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4532 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 292:
#line 450 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if (P->flags & PSI_DEBUG) {
		P->error(PSI_DATA(P), (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token, PSI_NOTICE, "Ignored decl: %s", (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name->val);
	}
	psi_decl_free(&(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4543 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 293:
#line 456 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_typedef(P, (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4551 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 294:
#line 459 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_struct(P, (*(struct psi_decl_struct **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4559 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 295:
#line 462 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_union(P, (*(struct psi_decl_union **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4567 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 296:
#line 465 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4575 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 297:
#line 468 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_impl(P, (*(struct psi_impl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4583 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 298:
#line 474 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4591 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 299:
#line 480 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4599 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 300:
#line 483 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = (*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4607 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 301:
#line 489 "src/parser_proc_grammar.y" /* glr.c:821  */
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
				psi_token_free(&old);
			}
		}
		psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));

		(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, msg);
	} else {
		(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, NULL);
	}
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4635 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 302:
#line 512 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4644 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 303:
#line 516 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4653 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 304:
#line 520 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4663 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 305:
#line 525 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_cpp_macro_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4672 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 306:
#line 529 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4681 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 307:
#line 533 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4690 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 308:
#line 537 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4699 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 325:
#line 581 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4709 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 326:
#line 586 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 4719 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 327:
#line 591 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_num_exp_tokens((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4729 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 328:
#line 596 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_token_free);
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_plist_add(list, &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4740 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 329:
#line 605 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL);
}
#line 4748 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 330:
#line 608 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL); /* FIXME */
}
#line 4756 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 332:
#line 612 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4764 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 333:
#line 618 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4774 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 334:
#line 623 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4784 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 335:
#line 631 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4792 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 337:
#line 638 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4801 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 338:
#line 642 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4810 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 339:
#line 649 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4819 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 340:
#line 653 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4828 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 341:
#line 657 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4837 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 342:
#line 661 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4846 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 343:
#line 666 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINED, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 4862 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 344:
#line 677 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		uint8_t exists;

		(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
		exists = psi_cpp_defined(P->preproc, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINED, &exists, 0));
		(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
		(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 4878 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 345:
#line 688 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4888 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 346:
#line 693 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4898 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 347:
#line 698 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4907 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 348:
#line 702 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4918 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 349:
#line 708 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->data.call->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4931 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 350:
#line 719 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4939 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 352:
#line 726 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	/* TODO: clang include test macros */
	uint8_t no = 1;
	struct psi_num_exp *exp = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &no, 0));
	exp->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	exp->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free), &exp);
}
#line 4952 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 353:
#line 734 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free),
		&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4961 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 354:
#line 738 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4969 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 355:
#line 744 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4978 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 356:
#line 748 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init(NULL, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4987 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 357:
#line 755 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4996 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 358:
#line 759 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init(PSI_T_NUMBER, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5005 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 359:
#line 763 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5014 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 363:
#line 776 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5022 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 364:
#line 790 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5030 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 365:
#line 796 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5038 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 366:
#line 799 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5046 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 367:
#line 805 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5054 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 368:
#line 808 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5062 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 370:
#line 815 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5075 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 371:
#line 823 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5091 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 372:
#line 834 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 5105 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 373:
#line 843 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 5119 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 375:
#line 856 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5128 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 376:
#line 860 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5143 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 377:
#line 870 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 5157 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 378:
#line 879 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 5171 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 380:
#line 892 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5179 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 381:
#line 895 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5187 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 384:
#line 906 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5196 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 386:
#line 914 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5206 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 387:
#line 919 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5216 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 388:
#line 924 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5226 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 391:
#line 934 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5234 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 392:
#line 937 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5242 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 393:
#line 943 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5250 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 394:
#line 946 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5258 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 395:
#line 949 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5266 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 398:
#line 960 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5274 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 399:
#line 963 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5282 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 400:
#line 966 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5290 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 401:
#line 972 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5298 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 402:
#line 975 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5306 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 403:
#line 978 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5319 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 404:
#line 986 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
}
#line 5333 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 405:
#line 998 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5341 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 406:
#line 1001 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5349 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 407:
#line 1004 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5357 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 408:
#line 1007 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5369 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 409:
#line 1014 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5377 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 410:
#line 1017 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5389 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 411:
#line 1027 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5397 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 413:
#line 1033 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5405 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 417:
#line 1042 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5413 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 418:
#line 1045 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5421 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 419:
#line 1048 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5434 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 420:
#line 1059 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = zend_string_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5446 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 421:
#line 1066 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = zend_string_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5458 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 422:
#line 1076 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5466 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 423:
#line 1079 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5474 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 424:
#line 1085 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5482 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 425:
#line 1088 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat("", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5491 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 426:
#line 1095 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_decl_extvar_free);

	if ((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))) {
		size_t i = 0;
		struct psi_decl_var *var;

		while (psi_plist_get((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), i++, &var)) {
			if (psi_decl_extvar_is_blacklisted(var->name->val)) {
				psi_decl_var_free(&var);
			} else {
				struct psi_decl_extvar *evar = psi_decl_extvar_init(
					psi_decl_arg_init(psi_decl_type_copy((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type), var));
				list = psi_plist_add(list, &evar);
			}
		}
		free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	}

	if (psi_decl_extvar_is_blacklisted((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->var->name->val)) {
		psi_decl_arg_free(&(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	} else {
		struct psi_decl_extvar *evar = psi_decl_extvar_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));

		if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
			evar->redir = zend_string_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
			psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		}
		list = psi_plist_add(list, &evar);
	}

	(*(struct psi_plist **)(&(*yyvalp))) = list;
}
#line 5529 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 427:
#line 1131 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5537 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 428:
#line 1134 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5545 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 429:
#line 1140 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5553 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 430:
#line 1143 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5561 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 431:
#line 1149 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5569 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 444:
#line 1179 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_decl **)(&(*yyvalp)))->abi = psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 5578 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 447:
#line 1191 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5590 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 448:
#line 1198 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5603 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 449:
#line 1209 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5615 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 450:
#line 1216 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5628 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 451:
#line 1224 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5657 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 452:
#line 1248 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-12)].yystate.yysemantics.yysval));
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval))->type = PSI_T_NAME;

	struct psi_token *type_token = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval))), 1, "rval");
	struct psi_decl_arg *rval_func = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-15)].yystate.yysemantics.yysval)), psi_decl_var_init(type_token->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-14)].yystate.yysemantics.yysval)), 0));
	struct psi_decl *rval_decl = psi_decl_init(rval_func, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));

	rval_func->var->token = psi_token_copy(type_token);
	rval_func->token = psi_token_copy(type_token);
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		rval_func->var->pointer_level += 1;
		rval_func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}

	struct psi_decl_type *type = psi_decl_type_init(PSI_T_FUNCTION, type_token->text);
	struct psi_decl_arg *func = psi_decl_arg_init(type, psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval))->text, 1, 0));

	type->real.func = rval_decl;
	func->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval)));
	func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval)));
	type->token = type_token;

	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init(func, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
}
#line 5688 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 453:
#line 1277 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5700 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 454:
#line 1284 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5713 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 455:
#line 1295 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5725 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 456:
#line 1341 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5736 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 458:
#line 1397 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5744 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 459:
#line 1400 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5752 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 460:
#line 1403 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5760 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 461:
#line 1409 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5768 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 462:
#line 1412 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5776 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 463:
#line 1418 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	char digest[17];
	struct psi_token *name;

	psi_token_hash((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token, digest);
	name = psi_token_append("@", psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token), 2, "funct", digest);

	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, name->text),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = name;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5796 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 464:
#line 1433 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5804 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 465:
#line 1436 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)),
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)))
	);
}
#line 5815 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 466:
#line 1465 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5828 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 467:
#line 1473 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5836 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 468:
#line 1501 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)) + !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5846 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 469:
#line 1506 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5856 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 470:
#line 1514 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_union **)(&(*yyvalp))) = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_union **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_union **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_union **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5868 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 471:
#line 1524 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_struct **)(&(*yyvalp))) = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_struct **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5880 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 472:
#line 1534 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5888 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 474:
#line 1541 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5896 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 475:
#line 1547 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5915 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 476:
#line 1561 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5934 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 477:
#line 1578 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5942 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 478:
#line 1581 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5950 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 479:
#line 1587 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 5962 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 480:
#line 1594 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 5974 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 481:
#line 1601 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 5987 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 482:
#line 1609 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 6000 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 483:
#line 1620 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_enum **)(&(*yyvalp))) = psi_decl_enum_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
}
#line 6009 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 484:
#line 1627 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6017 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 485:
#line 1630 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6025 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 486:
#line 1636 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, NULL);
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6035 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 487:
#line 1641 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6045 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 488:
#line 1649 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 6054 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 489:
#line 1653 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_cast((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->token);
}
#line 6063 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 490:
#line 1657 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary(PSI_T_LPAREN, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6072 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 491:
#line 1661 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6081 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 492:
#line 1665 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6090 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 493:
#line 1669 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6099 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 494:
#line 1676 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6108 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 495:
#line 1680 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6117 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 496:
#line 1684 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6126 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 497:
#line 1688 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6135 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 498:
#line 1692 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_NAME, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 6144 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 499:
#line 1696 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6152 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 500:
#line 1702 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6161 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 501:
#line 1706 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6170 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 502:
#line 1713 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6178 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 503:
#line 1716 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		int8_t sizeof_void_p = sizeof(void *);
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
		psi_decl_type_free(&(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_SIZEOF, (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 0);
	}
}
#line 6192 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 504:
#line 1728 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	int8_t sizeof_void_p = sizeof(void *);
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
}
#line 6201 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 505:
#line 1732 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	int8_t sizeof_a = sizeof('a');
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_a, 0);
}
#line 6210 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 506:
#line 1736 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	uint64_t len = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text->len + 1;
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_UINT64, &len, 0);
}
#line 6219 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 507:
#line 1743 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6234 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 508:
#line 1756 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6249 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 509:
#line 1769 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6264 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 510:
#line 1782 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 6272 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 511:
#line 1785 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&(*yyvalp)))->type = PSI_T_NAME;
}
#line 6281 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 514:
#line 1797 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = NULL;
}
#line 6289 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 515:
#line 1800 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(0, 0, psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text->val), NULL));
}
#line 6297 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 516:
#line 1803 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val), NULL);
}
#line 6305 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 517:
#line 1806 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val), psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval))->text->val), NULL));
}
#line 6313 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 518:
#line 1812 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = 0;
	(*(struct psi_layout*)(&(*yyvalp))).len = 0;
}
#line 6322 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 519:
#line 1816 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val);
	(*(struct psi_layout*)(&(*yyvalp))).len = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val);
}
#line 6331 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 520:
#line 1823 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6339 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 521:
#line 1826 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6347 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 522:
#line 1829 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	struct psi_validate_scope scope = {0};
	psi_validate_scope_ctor(&scope);
	scope.cpp = P->preproc;
	if (psi_num_exp_validate(PSI_DATA(P), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &scope)) {
		(*(size_t*)(&(*yyvalp))) = psi_num_exp_get_long((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), NULL, P->preproc);
	} else {
		(*(size_t*)(&(*yyvalp))) = 0;
	}
	psi_num_exp_free(&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	psi_validate_scope_dtor(&scope);
}
#line 6364 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 527:
#line 1851 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6372 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 528:
#line 1854 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6380 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 530:
#line 1861 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6388 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 531:
#line 1867 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 1;
}
#line 6396 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 532:
#line 1870 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)) + 1;
}
#line 6404 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 537:
#line 1892 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6412 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 538:
#line 1895 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6421 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 539:
#line 1902 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, NULL, (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
}
#line 6431 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 540:
#line 1907 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval));
}
#line 6441 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 541:
#line 1912 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval));
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6453 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 542:
#line 1922 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6461 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 543:
#line 1925 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6469 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 544:
#line 1931 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
}
#line 6477 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 545:
#line 1934 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6485 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 546:
#line 1940 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_var **)(&(*yyvalp))) = psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6494 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 547:
#line 1947 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6503 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 548:
#line 1954 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6512 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 560:
#line 1981 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6520 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 561:
#line 1984 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6528 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 562:
#line 1990 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_return_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6536 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 563:
#line 1993 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_let_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6544 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 564:
#line 1996 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_set_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6552 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 565:
#line 1999 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_assert_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6560 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 566:
#line 2002 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_free_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6568 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 567:
#line 2008 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init((*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6577 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 568:
#line 2012 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init(psi_let_exp_init_ex((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), PSI_LET_TMP, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->exp->is_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6587 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 570:
#line 2021 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = true;
}
#line 6596 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 571:
#line 2025 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = false;
}
#line 6605 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 572:
#line 2032 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 6613 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 573:
#line 2035 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6621 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 574:
#line 2038 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6629 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 575:
#line 2041 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6638 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 576:
#line 2045 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLBACK, (*(struct psi_let_callback **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6646 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 577:
#line 2048 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, (*(struct psi_let_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6654 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 578:
#line 2054 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6663 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 579:
#line 2058 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = 1;
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 6673 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 580:
#line 2066 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_calloc **)(&(*yyvalp))) = psi_let_calloc_init((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 6682 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 581:
#line 2073 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)));
}
#line 6692 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 582:
#line 2078 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval)));
}
#line 6702 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 583:
#line 2086 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_func **)(&(*yyvalp))) = psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6712 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 594:
#line 2107 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6720 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 595:
#line 2110 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6728 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 596:
#line 2116 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6736 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 597:
#line 2119 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6744 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 600:
#line 2130 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6752 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 601:
#line 2133 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6760 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 602:
#line 2139 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6768 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 603:
#line 2142 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6776 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 604:
#line 2148 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_stmt **)(&(*yyvalp))) = psi_return_stmt_init((*(struct psi_return_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_return_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6785 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 605:
#line 2155 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->token);
}
#line 6794 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 606:
#line 2159 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init(NULL, NULL, psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 6803 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 607:
#line 2166 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6811 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 608:
#line 2169 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6819 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 609:
#line 2172 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6827 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 610:
#line 2178 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_stmt **)(&(*yyvalp))) = psi_set_stmt_init((*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_set_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6836 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 611:
#line 2185 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6844 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 612:
#line 2188 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6852 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 613:
#line 2191 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = (*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_set_exp **)(&(*yyvalp)))->var = (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6861 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 614:
#line 2198 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6871 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 615:
#line 2203 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->recursive = 1;
}
#line 6881 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 624:
#line 2222 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6889 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 625:
#line 2225 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6897 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 626:
#line 2231 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6905 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 627:
#line 2234 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6913 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 628:
#line 2240 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_assert_stmt **)(&(*yyvalp))) = psi_assert_stmt_init((enum psi_assert_kind) (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_assert_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6922 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 631:
#line 2252 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_free_stmt **)(&(*yyvalp))) = psi_free_stmt_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6931 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 632:
#line 2259 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6939 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 633:
#line 2262 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6947 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 634:
#line 2268 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_free_exp **)(&(*yyvalp))) = psi_free_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6957 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 635:
#line 2276 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(bool*)(&(*yyvalp))) = false;
}
#line 6965 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 636:
#line 2279 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(bool*)(&(*yyvalp))) = true;
}
#line 6973 "src/parser_proc.c" /* glr.c:821  */
    break;


#line 6977 "src/parser_proc.c" /* glr.c:821  */
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
#line 294 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7028 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 142: /* unary_op_token  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7034 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 143: /* name_token  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7040 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 144: /* any_noeol_token  */
#line 294 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7046 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 149: /* lib  */
#line 288 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7052 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 150: /* cpp  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 7058 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 151: /* cpp_exp  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 7064 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 153: /* cpp_message_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7070 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 154: /* cpp_include_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7076 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 155: /* cpp_header_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7082 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 156: /* cpp_no_arg_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7088 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 157: /* cpp_name_arg_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7094 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 158: /* cpp_exp_arg_token  */
#line 291 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7100 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 159: /* cpp_macro_decl  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_macro_decl_free(&(*(struct psi_cpp_macro_decl **)(&(*yyvaluep))));}
#line 7106 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 160: /* cpp_macro_sig  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7112 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 161: /* cpp_macro_sig_args  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7118 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 162: /* cpp_macro_decl_tokens  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7124 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 163: /* cpp_macro_decl_token_list  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7130 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 164: /* cpp_macro_exp  */
#line 309 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 7136 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 165: /* cpp_macro_call_args  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7142 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 166: /* cpp_macro_call_arg_list  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7148 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 167: /* constant  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_const_free(&(*(struct psi_const **)(&(*yyvaluep))));}
#line 7154 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 168: /* impl_def_val  */
#line 317 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_def_val_free(&(*(struct psi_impl_def_val **)(&(*yyvaluep))));}
#line 7160 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 169: /* impl_def_val_token  */
#line 312 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7166 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 170: /* decl_typedef  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7172 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 171: /* typedef  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7178 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 172: /* typedef_anon  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7184 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 173: /* typedef_decl  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7190 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 174: /* typedef_anon_decl  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7196 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 175: /* qualified_decl_type  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7202 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 177: /* decl_type  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7208 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 178: /* decl_type_complex  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7214 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 179: /* decl_type_simple  */
#line 320 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7220 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 180: /* decl_real_type  */
#line 320 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7226 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 181: /* int_signed  */
#line 300 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7232 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 182: /* int_width  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7238 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 183: /* decl_int_type  */
#line 320 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7244 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 184: /* int_signed_types  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7250 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 185: /* signed_short_types  */
#line 300 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7256 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 186: /* signed_long_types  */
#line 300 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7262 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 187: /* int_width_types  */
#line 297 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7268 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 188: /* decl_stmt  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7274 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 189: /* decl_asm  */
#line 323 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7280 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 190: /* quoted_strings  */
#line 323 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7286 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 191: /* decl_extvar_stmt  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7292 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 192: /* decl_extvar_list  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7298 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 193: /* decl_vars  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7304 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 194: /* ignored_decl  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7310 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 199: /* decl  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7316 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 200: /* decl_body  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7322 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 201: /* decl_func_body  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7328 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 202: /* decl_functor_body  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7334 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 203: /* decl_anon_functor_body  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7340 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 204: /* decl_functor  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7346 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 205: /* decl_anon_functor  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7352 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 206: /* decl_func  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7358 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 207: /* decl_args  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7364 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 208: /* decl_arg_list  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7370 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 209: /* decl_anon_arg  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7376 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 210: /* decl_arg  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7382 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 211: /* decl_var  */
#line 332 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_var_free(&(*(struct psi_decl_var **)(&(*yyvaluep))));}
#line 7388 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 212: /* decl_union  */
#line 336 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_union_free(&(*(struct psi_decl_union **)(&(*yyvaluep))));}
#line 7394 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 213: /* decl_struct  */
#line 334 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_struct_free(&(*(struct psi_decl_struct **)(&(*yyvaluep))));}
#line 7400 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 214: /* decl_struct_args  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7406 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 215: /* struct_args_block  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7412 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 216: /* struct_args  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7418 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 217: /* struct_arg_var_list  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7424 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 218: /* decl_vars_with_layout  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7430 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 219: /* decl_enum  */
#line 338 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_enum_free(&(*(struct psi_decl_enum **)(&(*yyvaluep))));}
#line 7436 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 220: /* decl_enum_items  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7442 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 221: /* decl_enum_item  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_enum_item_free(&(*(struct psi_decl_enum_item **)(&(*yyvaluep))));}
#line 7448 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 222: /* num_exp  */
#line 398 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 7454 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 223: /* number  */
#line 400 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7460 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 224: /* sizeof  */
#line 350 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7466 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 225: /* sizeof_body  */
#line 350 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7472 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 226: /* sizeof_body_notypes  */
#line 350 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7478 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 227: /* enum_name  */
#line 288 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7484 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 228: /* union_name  */
#line 288 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7490 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 229: /* struct_name  */
#line 288 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7496 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 230: /* optional_name  */
#line 288 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7502 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 232: /* decl_layout  */
#line 347 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_layout_free(&(*(struct psi_layout **)(&(*yyvaluep))));}
#line 7508 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 233: /* align_and_size  */
#line 345 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7514 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 234: /* array_size  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7520 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 236: /* indirection  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7526 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 237: /* pointers  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7532 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 238: /* asterisks  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7538 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 241: /* impl  */
#line 353 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_free(&(*(struct psi_impl **)(&(*yyvaluep))));}
#line 7544 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 242: /* impl_func  */
#line 355 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_func_free(&(*(struct psi_impl_func **)(&(*yyvaluep))));}
#line 7550 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 243: /* impl_args  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7556 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 244: /* impl_arg  */
#line 357 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_arg_free(&(*(struct psi_impl_arg **)(&(*yyvaluep))));}
#line 7562 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 245: /* impl_var  */
#line 361 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_var_free(&(*(struct psi_impl_var **)(&(*yyvaluep))));}
#line 7568 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 246: /* impl_type  */
#line 359 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7574 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 247: /* impl_type_restricted  */
#line 359 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7580 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 248: /* impl_type_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7586 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 249: /* impl_type_restricted_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7592 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 250: /* impl_type_extended_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7598 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 251: /* impl_stmts  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7604 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 252: /* impl_stmt  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_stmt_free(&(*(struct psi_token ***)(&(*yyvaluep))));}
#line 7610 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 253: /* let_stmt  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_stmt_free(&(*(struct psi_let_stmt **)(&(*yyvaluep))));}
#line 7616 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 254: /* let_exp  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7622 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 255: /* let_exp_byref  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7628 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 256: /* let_exp_assign  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7634 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 257: /* let_calloc  */
#line 368 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_calloc_free(&(*(struct psi_let_calloc **)(&(*yyvaluep))));}
#line 7640 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 258: /* let_callback  */
#line 370 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_callback_free(&(*(struct psi_let_callback **)(&(*yyvaluep))));}
#line 7646 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 259: /* let_func  */
#line 372 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_func_free(&(*(struct psi_let_func **)(&(*yyvaluep))));}
#line 7652 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 260: /* let_func_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7658 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 261: /* let_func_exps  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7664 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 262: /* let_exps  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7670 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 263: /* callback_rval  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7676 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 264: /* callback_arg_list  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7682 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 265: /* callback_args  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7688 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 266: /* return_stmt  */
#line 382 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_return_stmt_free(&(*(struct psi_return_stmt **)(&(*yyvaluep))));}
#line 7694 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 267: /* return_exp  */
#line 384 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_return_exp_free(&(*(struct psi_return_exp **)(&(*yyvaluep))));}
#line 7700 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 268: /* call_decl_vars  */
#line 342 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7706 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 269: /* set_stmt  */
#line 374 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_stmt_free(&(*(struct psi_set_stmt **)(&(*yyvaluep))));}
#line 7712 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 270: /* set_exp  */
#line 376 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_exp_free(&(*(struct psi_set_exp **)(&(*yyvaluep))));}
#line 7718 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 271: /* set_func  */
#line 378 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_func_free(&(*(struct psi_set_func **)(&(*yyvaluep))));}
#line 7724 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 272: /* set_func_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7730 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 273: /* set_func_exps  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7736 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 274: /* set_exps  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7742 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 275: /* assert_stmt  */
#line 380 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_assert_stmt_free(&(*(struct psi_assert_stmt **)(&(*yyvaluep))));}
#line 7748 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 276: /* assert_stmt_token  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7754 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 277: /* free_stmt  */
#line 386 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_free_stmt_free(&(*(struct psi_free_stmt **)(&(*yyvaluep))));}
#line 7760 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 278: /* free_exps  */
#line 395 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7766 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 279: /* free_exp  */
#line 388 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_free_exp_free(&(*(struct psi_free_exp **)(&(*yyvaluep))));}
#line 7772 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 280: /* reference  */
#line 405 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7778 "src/parser_proc.c" /* glr.c:851  */
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
  (!!((Yystate) == (-731)))

/** True iff LR state YYSTATE has only a default reduction (regardless
 *  of token).  */
static inline yybool
yyisDefaultedState (yyStateNum yystate)
{
  return (yybool) yypact_value_is_default (yypact[yystate]);
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
                int* yyaction, const short** yyconflicts)
{
  int yyindex = yypact[yystate] + yytoken;
  if (yyisDefaultedState (yystate)
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
  return (yybool) (0 < yyaction);
}

static inline yybool
yyisErrorAction (int yyaction)
{
  return (yybool) (yyaction == 0);
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
  size_t yysize = (size_t) (yystackp->yynextFree - yystackp->yyitems);
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
                          (unsigned long) yyi, (unsigned long) yyj));
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
yy_reduce_print (yybool yynormal, yyGLRStackItem* yyvsp, size_t yyk,
                 yyRuleNum yyrule, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
  int yynrhs = yyrhsLength (yyrule);
  int yyi;
  YYFPRINTF (stderr, "Reducing stack %lu by rule %d (line %lu):\n",
             (unsigned long) yyk, yyrule - 1,
             (unsigned long) yyrline[yyrule]);
  if (! yynormal)
    yyfillin (yyvsp, 1, -yynrhs);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyvsp[yyi - yynrhs + 1].yystate.yylrState],
                       &yyvsp[yyi - yynrhs + 1].yystate.yysemantics.yysval                       , P, tokens, index);
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
      yystackp->yyspaceLeft += (size_t) yynrhs;
      yystackp->yytops.yystates[0] = & yystackp->yynextFree[-1].yystate;
      YY_REDUCE_PRINT ((yytrue, yyrhs, yyk, yyrule, P, tokens, index));
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
      YY_REDUCE_PRINT ((yyfalse, yyrhsVals + YYMAXRHS + YYMAXLEFT - 1, yyk, yyrule, P, tokens, index));
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
                     (unsigned long) yyk, yyrule - 1));
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
                  (unsigned long) yyk, yyrule - 1, yynewLRState));
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
                                (unsigned long) yyk,
                                (unsigned long) yyi));
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
      yyGLRState** yynewStates = YY_NULLPTR;
      yybool* yynewLookaheadNeeds;

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
               yyx->yyrule - 1, (unsigned long) (yys->yyposn + 1),
               (unsigned long) yyx->yystate->yyposn);
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
                       (unsigned long) (yystates[yyi-1]->yyposn + 1),
                       (unsigned long) yystates[yyi]->yyposn);
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

  yystackp->yyspaceLeft += (size_t) (yystackp->yynextFree - yystackp->yyitems);
  yystackp->yynextFree = ((yyGLRStackItem*) yystackp->yysplitPoint) + 1;
  yystackp->yyspaceLeft -= (size_t) (yystackp->yynextFree - yystackp->yyitems);
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
                  (unsigned long) yyk, yystate));

      YYASSERT (yystate != YYFINAL);

      if (yyisDefaultedState (yystate))
        {
          YYRESULTTAG yyflag;
          yyRuleNum yyrule = yydefaultAction (yystate);
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, "Stack %lu dies.\n",
                          (unsigned long) yyk));
              yymarkStackDeleted (yystackp, yyk);
              return yyok;
            }
          yyflag = yyglrReduce (yystackp, yyk, yyrule, yyimmediate[yyrule], P, tokens, index);
          if (yyflag == yyerr)
            {
              YYDPRINTF ((stderr,
                          "Stack %lu dies "
                          "(predicate failure or explicit user error).\n",
                          (unsigned long) yyk));
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
          const short* yyconflicts;

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
                          (unsigned long) yynewStack,
                          (unsigned long) yyk));
              yyflag = yyglrReduce (yystackp, yynewStack,
                                    *yyconflicts,
                                    yyimmediate[*yyconflicts], P, tokens, index);
              if (yyflag == yyok)
                YYCHK (yyprocessOneStack (yystackp, yynewStack,
                                          yyposn, P, tokens, index));
              else if (yyflag == yyerr)
                {
                  YYDPRINTF ((stderr, "Stack %lu dies.\n",
                              (unsigned long) yynewStack));
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
                          (unsigned long) yyk));
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
                              (unsigned long) yyk));
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
                  if (yysz < yysize)
                    yysize_overflow = yytrue;
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
    default: /* Avoid compiler warnings. */
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
    if (yysz < yysize)
      yysize_overflow = yytrue;
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
#line 123 "src/parser_proc_grammar.y" /* glr.c:2265  */
{
}

#line 9131 "src/parser_proc.c" /* glr.c:2265  */

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
          const short* yyconflicts;

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
            yystackp->yytops.yylookaheadNeeds[yys] = (yybool) (yychar != YYEMPTY);

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
              const short* yyconflicts;
              yyStateNum yystate = yystack.yytops.yystates[yys]->yylrState;
              yygetLRActions (yystate, yytoken_to_shift, &yyaction,
                              &yyconflicts);
              /* Note that yyconflicts were handled by yyprocessOneStack.  */
              YYDPRINTF ((stderr, "On stack %lu, ", (unsigned long) yys));
              YY_SYMBOL_PRINT ("shifting", yytoken_to_shift, &yylval, &yylloc);
              yyglrShift (&yystack, yys, yyaction, yyposn,
                          &yylval);
              YYDPRINTF ((stderr, "Stack %lu now in state #%d\n",
                          (unsigned long) yys,
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
             (unsigned long) yys->yyposn);
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
                 (unsigned long) (yyp - yystackp->yyitems));
      if (*(yybool *) yyp)
        {
          YYASSERT (yyp->yystate.yyisState);
          YYASSERT (yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Res: %d, LR State: %d, posn: %lu, pred: %ld",
                     yyp->yystate.yyresolved, yyp->yystate.yylrState,
                     (unsigned long) yyp->yystate.yyposn,
                     (long) YYINDEX (yyp->yystate.yypred));
          if (! yyp->yystate.yyresolved)
            YYFPRINTF (stderr, ", firstVal: %ld",
                       (long) YYINDEX (yyp->yystate
                                             .yysemantics.yyfirstVal));
        }
      else
        {
          YYASSERT (!yyp->yystate.yyisState);
          YYASSERT (!yyp->yyoption.yyisState);
          YYFPRINTF (stderr, "Option. rule: %d, state: %ld, next: %ld",
                     yyp->yyoption.yyrule - 1,
                     (long) YYINDEX (yyp->yyoption.yystate),
                     (long) YYINDEX (yyp->yyoption.yynext));
        }
      YYFPRINTF (stderr, "\n");
    }
  YYFPRINTF (stderr, "Tops:");
  for (yyi = 0; yyi < yystackp->yytops.yysize; yyi += 1)
    YYFPRINTF (stderr, "%lu: %ld; ", (unsigned long) yyi,
               (long) YYINDEX (yystackp->yytops.yystates[yyi]));
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

#line 2288 "src/parser_proc_grammar.y" /* glr.c:2578  */


/* epilogue */

#define PSI_DEBUG_LEX 0
static int psi_parser_proc_lex(YYSTYPE *lvalp, struct psi_parser *P, struct psi_plist *tokens, size_t *index)
{
	struct psi_token *token;
#if PSI_DEBUG_LEX
	PSI_DEBUG_PRINT(P, "PSI: LEX index %4zu ", *index);
#endif
	if (psi_plist_get(tokens, (*index)++, &token) && token) {
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
			const char *pos;
			
			if (!psi_plist_get(tokens, i++, &T)) {
				break;
			}
			
			if (i < last + 1) {
				pos = "preceding";
			} else if (i > last + 1) {
				pos = "following";
			} else {
				pos = "offending";
			}
			
			P->error(PSI_DATA(P), T, PSI_WARNING, "PSI %s token '%s' at col %u", 
					pos, T ? T->text->val : "<deleted>", T ? T->col : 0);
		}
	} else {
		P->error(PSI_DATA(P), NULL, PSI_WARNING, "PSI %s", msg);
	}
	P->errors++;
}

