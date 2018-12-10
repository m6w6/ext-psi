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
#define YYFINAL  161
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   7875

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  138
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  142
/* YYNRULES -- Number of rules.  */
#define YYNRULES  629
/* YYNRULES -- Number of states.  */
#define YYNSTATES  938
/* YYMAXRHS -- Maximum number of symbols on right-hand side of rule.  */
#define YYMAXRHS 16
/* YYMAXLEFT -- Maximum number of symbols to the left of a handle
   accessed by $0, $-1, etc., in any rule.  */
#define YYMAXLEFT 0

/* YYTRANSLATE(X) -- Bison symbol number corresponding to X.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   392

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
     135,   136,   137
};

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short yyrline[] =
{
       0,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     410,   410,   410,   410,   410,   410,   410,   410,   410,   410,
     411,   411,   411,   411,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   412,   412,   412,   412,   412,   412,
     412,   412,   412,   412,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   413,   413,   413,   413,   413,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   414,   414,   414,   414,   414,   414,
     414,   414,   414,   414,   418,   419,   422,   423,   426,   427,
     428,   429,   435,   438,   441,   444,   450,   453,   456,   459,
     462,   468,   471,   477,   500,   504,   508,   513,   517,   521,
     528,   529,   533,   537,   538,   542,   543,   544,   548,   549,
     553,   554,   558,   559,   560,   564,   565,   569,   574,   579,
     584,   593,   596,   599,   600,   606,   611,   619,   622,   626,
     630,   637,   641,   645,   649,   654,   665,   676,   681,   686,
     690,   696,   707,   710,   714,   722,   726,   732,   736,   743,
     747,   751,   758,   759,   760,   764,   778,   784,   787,   793,
     796,   802,   803,   811,   822,   831,   843,   844,   848,   858,
     867,   879,   880,   883,   889,   890,   894,   898,   902,   907,
     912,   920,   921,   922,   925,   931,   934,   937,   943,   944,
     948,   951,   954,   960,   963,   966,   974,   986,   989,   992,
     995,  1002,  1005,  1015,  1018,  1021,  1024,  1025,  1026,  1030,
    1033,  1036,  1047,  1054,  1064,  1067,  1073,  1076,  1083,  1119,
    1122,  1128,  1131,  1137,  1143,  1144,  1145,  1146,  1147,  1148,
    1152,  1156,  1157,  1161,  1162,  1166,  1167,  1174,  1175,  1179,
    1186,  1197,  1204,  1212,  1236,  1265,  1272,  1283,  1329,  1370,
    1385,  1388,  1391,  1397,  1400,  1406,  1421,  1424,  1453,  1461,
    1489,  1494,  1502,  1512,  1522,  1525,  1529,  1535,  1549,  1566,
    1569,  1575,  1582,  1589,  1597,  1608,  1615,  1618,  1624,  1629,
    1637,  1641,  1645,  1649,  1653,  1657,  1664,  1668,  1672,  1676,
    1680,  1684,  1690,  1694,  1701,  1704,  1716,  1720,  1724,  1731,
    1744,  1757,  1770,  1773,  1780,  1781,  1785,  1788,  1791,  1794,
    1800,  1804,  1811,  1814,  1817,  1832,  1833,  1834,  1835,  1839,
    1842,  1848,  1849,  1855,  1858,  1864,  1865,  1869,  1870,  1880,
    1883,  1890,  1895,  1900,  1910,  1913,  1919,  1922,  1928,  1935,
    1942,  1949,  1950,  1954,  1955,  1956,  1957,  1958,  1962,  1963,
    1964,  1965,  1969,  1972,  1978,  1981,  1984,  1987,  1990,  1996,
    2000,  2008,  2009,  2013,  2020,  2023,  2026,  2029,  2033,  2036,
    2042,  2046,  2054,  2061,  2066,  2074,  2082,  2083,  2084,  2085,
    2086,  2087,  2088,  2089,  2090,  2091,  2095,  2098,  2104,  2107,
    2113,  2114,  2118,  2121,  2127,  2130,  2136,  2143,  2147,  2154,
    2157,  2160,  2166,  2173,  2176,  2179,  2186,  2191,  2199,  2200,
    2201,  2202,  2203,  2204,  2205,  2206,  2210,  2213,  2219,  2222,
    2228,  2235,  2236,  2240,  2247,  2250,  2256,  2264,  2267,  2273
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
  "\"\\\\\"", "\"...\"", "\"?\"", "PRAGMA", "LINE", "ERROR", "WARNING",
  "IF", "IFDEF", "IFNDEF", "ELSE", "ELIF", "ENDIF", "DEFINE", "DEFINED",
  "UNDEF", "IMPORT", "INCLUDE", "INCLUDE_NEXT", "TYPEDEF", "STRUCT",
  "UNION", "ENUM", "CONST", "STATIC", "CALLBACK", "FUNCTION", "LET", "SET",
  "TEMP", "FREE", "RETURN", "AS", "PRE_ASSERT", "POST_ASSERT", "BOOLVAL",
  "INTVAL", "STRVAL", "PATHVAL", "STRLEN", "FLOATVAL", "ARRVAL", "OBJVAL",
  "COUNT", "CALLOC", "TO_BOOL", "TO_INT", "TO_STRING", "TO_FLOAT",
  "TO_ARRAY", "TO_OBJECT", "COMMENT", "WHITESPACE", "NO_WHITESPACE",
  "CPP_HEADER", "CPP_ATTRIBUTE", "CPP_EXTENSION", "CPP_PASTE",
  "CPP_INLINE", "CPP_RESTRICT", "CPP_ASM", "BSLASH", "LONG_DOUBLE", "INT8",
  "UINT8", "INT16", "UINT16", "INT32", "UINT32", "INT64", "UINT64",
  "INT128", "UINT128", "BINARY", "UNARY", "$accept", "binary_op_token",
  "unary_op_token", "name_token", "any_noeol_token", "any_nobrace_token",
  "file", "blocks", "block", "cpp", "cpp_exp", "cpp_macro_decl_arg_token",
  "cpp_ignored_token", "cpp_message_token", "cpp_include_token",
  "cpp_header_token", "cpp_no_arg_token", "cpp_name_arg_token",
  "cpp_exp_arg_token", "cpp_macro_decl", "cpp_macro_sig",
  "cpp_macro_sig_args", "cpp_macro_decl_tokens",
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

#define YYPACT_NINF -710
#define YYTABLE_NINF -628

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const short yypact[] =
{
     529,  -710,  -710,  -710,  -710,  -710,    90,  -710,  -710,  -710,
     500,  -710,  -710,  -710,   742,  1480,  7560,  7560,  7560,   158,
     -25,    18,  -710,   247,  -710,    71,   529,  -710,  -710,  -710,
    -710,  6818,   570,  -710,  -710,  -710,  -710,   119,   192,  -710,
    -710,  -710,  -710,   758,   -41,  -710,  -710,    35,    55,   117,
    -710,  -710,  -710,  -710,    59,  -710,   104,  -710,  -710,  -710,
    7560,  7560,  7560,  -710,  -710,  -710,   102,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,   133,   851,   975,   975,    31,  -710,   975,
    6596,  7560,  7560,  1743,   138,  -710,  -710,  -710,   159,  7560,
     171,   171,  -710,  -710,  -710,  -710,  -710,  -710,  1335,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,   108,  -710,  -710,
     108,   180,  -710,  -710,  -710,  -710,  -710,  -710,   184,   204,
    -710,  -710,   193,  -710,   209,  -710,  1854,  1480,   113,  -710,
     -41,  -710,  -710,    34,   198,  -710,  -710,   214,  7560,     9,
    -710,  -710,  -710,   242,  -710,   136,  -710,  -710,  -710,   179,
    -710,   229,   218,   231,  1965,  1965,  7560,   129,  -710,  -710,
    -710,  7151,   -41,  -710,  -710,  1709,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  1820,  1931,  2042,  2153,  -710,  2264,
    2375,  -710,  -710,  -710,  2486,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  2597,  2708,  2819,
    2930,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  3041,  3152,  3263,
    3374,  3485,  3596,  -710,  3707,  -710,  -710,  3818,  3929,  4040,
    4151,  4262,  4373,  4484,  4595,  4706,  4817,  4928,  5039,  5150,
    5261,  5372,  5483,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    5594,   975,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
     975,  -710,  -710,  -710,  -710,  -710,  -710,  -710,    83,  6596,
    -710,  -710,  -710,  -710,  7213,  6596,   238,  7738,  -710,    77,
    -710,   121,  -710,  -710,  -710,  -710,   236,   237,   237,    43,
      43,  5819,   232,   129,   243,   248,  -710,   249,  -710,  -710,
    -710,  1447,  -710,   225,   198,  -710,  -710,  -710,  -710,  -710,
     275,  -710,  -710,  1223,  -710,   256,  -710,    96,  6818,  -710,
     251,   146,   255,  -710,  -710,   169,   245,   257,  -710,  7151,
    6263,  7151,  7560,  7151,  -710,  -710,   475,  -710,  -710,  -710,
    -710,  -710,  6485,  -710,   259,  -710,  7560,   263,  -710,   266,
    7738,   269,  -710,  -710,  -710,  -710,  6628,   277,  -710,  6921,
    7560,  -710,  -710,  1598,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  6596,  6596,   268,  1566,  7151,  7151,  -710,  -710,
    -710,  -710,   142,  -710,  -710,  -710,  -710,  -710,  5708,  6485,
     270,  -710,   269,  -710,  7762,  -710,  -710,  5819,   512,   623,
    -710,  -710,  -710,  -710,  -710,  -710,  7714,   264,  7275,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  1099,  -710,
      88,    94,  1965,   198,   240,   758,   198,   244,  6485,  7560,
     265,   267,   278,  7762,   280,   290,  -710,   274,   298,   283,
     292,   131,  -710,   293,   297,  -710,  -710,  -710,  6806,  7151,
    -710,  7333,  -710,   225,   302,  -710,  -710,  -710,   303,  -710,
    7738,   305,   312,  7665,  -710,   314,  1743,   313,  -710,  -710,
    6707,   721,  7560,   171,   171,  -710,  -710,    61,    64,    73,
    7134,  -710,  -710,  6485,  6485,   316,  -710,  -710,  -710,  -710,
    -710,   318,   181,  -710,    18,  -710,  -710,  -710,  -710,  -710,
     225,   206,  -710,  -710,  -710,   225,  -710,   207,  -710,   321,
    -710,  -710,   322,  7762,  -710,  -710,  5930,  -710,  6263,  -710,
    7151,  -710,    18,  7151,  -710,  7560,  7444,  -710,  -710,  -710,
    -710,  -710,   323,   315,  -710,  -710,  -710,  -710,  6596,  6596,
     333,  -710,    63,   335,  -710,   313,   237,   237,  6485,  -710,
    7690,  -710,  -710,   782,   337,   782,   330,  7560,  1965,  -710,
    6929,   198,   309,   198,   198,   156,   272,   213,   342,  7762,
    -710,  -710,  -710,  -710,   344,  6374,  -710,   347,  7151,   226,
    -710,   349,   259,   350,   975,  7502,  7738,  7786,   359,   352,
     353,  7040,   360,   335,  7151,  7151,  -710,  6485,  -710,   782,
    -710,    18,  5819,   361,   362,  -710,  -710,   363,  -710,  -710,
     342,  -710,  -710,  -710,  7444,  -710,   370,  6485,    18,  -710,
    6041,   372,   375,  -710,   317,  -710,  -710,  -710,   376,   358,
     385,   313,   377,  -710,  -710,   382,  7810,  -710,    44,  -710,
     383,   381,   198,   386,    18,  7640,   384,   387,  -710,   389,
    -710,  -710,   100,  -710,   392,   391,  -710,  7040,  -710,   397,
    1965,   394,  -710,   332,   398,  6485,  5930,   399,  -710,  6263,
    -710,  -710,   401,   406,   410,   313,  -710,   404,   405,  1965,
     260,  6152,  7427,   267,  -710,  -710,  -710,   407,  6374,  -710,
    -710,   408,   411,  -710,   412,   415,   416,   418,   420,   409,
    -710,  -710,  5930,  -710,   426,  -710,   782,   423,   198,    18,
     432,  6263,  -710,   433,  -710,  1965,  -710,   435,  -710,  -710,
    -710,   439,  6152,   198,   440,  -710,   441,  -710
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const unsigned short yydefact[] =
{
     274,   393,   390,   394,   388,   389,   391,   385,   386,   384,
     383,   375,   279,   278,     0,     0,     0,     0,   502,   374,
     424,   627,   280,     0,   428,     0,   275,   276,   281,   282,
     286,   519,     0,   371,   377,   376,   382,   397,   409,   381,
     283,   284,   285,     0,   414,   435,   437,   438,     0,     0,
     449,   288,   287,   289,     0,   290,     0,   392,   387,   383,
       0,     0,     0,   374,   429,   436,   419,   291,   301,   302,
     303,   304,   315,   312,   313,   310,   316,   311,   300,   314,
     305,   306,   307,     0,     0,   327,   327,     0,   295,     0,
       0,   502,   502,     0,     0,   357,   362,   458,   361,     0,
     510,   510,    32,    33,    34,    35,    36,   615,   576,    24,
      40,    39,    37,    38,    31,    25,    29,    28,    26,    27,
      41,   584,   583,   581,   579,   580,   582,   578,   577,   585,
      30,   613,   611,   610,   612,   609,   608,   378,    42,    43,
     379,   380,   499,   543,   544,   545,   546,   547,     0,     0,
     540,   425,     0,   629,     0,   628,   383,     0,     0,   426,
     414,     1,   277,   525,   512,   373,   459,     0,   520,   521,
     523,   372,   399,   403,   401,   405,   398,   395,   410,   397,
     396,     0,     0,     0,   450,   450,     0,     0,   378,   379,
     380,     0,   414,   292,    69,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
     157,   158,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   108,   107,   106,   104,
     105,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   159,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   155,   152,   153,   154,   156,
       0,   327,   297,    44,    53,    54,    55,    56,    58,    59,
      63,   107,   106,   104,   105,   125,   126,   127,   128,   129,
     130,   159,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   329,   299,
     328,   293,   308,   309,   294,   296,   337,   338,     0,     0,
      22,    23,    20,    21,     0,     0,   340,   298,   339,   378,
     501,   379,   500,   358,   355,   363,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   427,     0,   528,   527,
     526,   515,   461,   519,   512,   522,   524,   404,   400,   406,
     407,   402,   411,     0,   423,     0,   412,   384,   519,   455,
       0,     0,   452,   453,   456,     0,   478,   504,   476,     0,
     627,     0,     0,     0,   621,   622,     0,   552,   555,   554,
     556,   557,     0,   558,   420,   421,     0,     0,   416,     0,
     319,   320,   317,   330,   498,   497,     0,     0,   493,     0,
       0,   335,   332,   342,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    13,    12,    14,    15,    16,    17,
      18,    19,     0,     0,     0,     0,     0,     0,   464,   463,
     465,   462,   489,   353,   354,   487,   486,   488,     0,     0,
       0,   349,   351,   490,   350,   480,   491,     0,     0,     0,
     356,   413,   489,   517,   518,   516,     0,     0,     0,   520,
     460,   408,   185,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   271,   272,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   222,   221,   220,   218,   219,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     273,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   269,   266,   267,   268,   270,   433,   434,     0,   431,
       0,   512,   450,   512,     0,     0,   512,     0,     0,   505,
       0,     0,     0,   604,     0,     0,   603,    43,     0,     0,
       0,     0,   624,     0,     0,   598,   529,   553,     0,     0,
     418,   321,   417,   519,     0,   494,   496,   331,     0,   344,
     345,     0,   343,     0,   333,     0,     0,   506,   366,   359,
     367,     0,   368,   510,   510,   365,   364,   615,    24,     0,
       0,   484,   348,     0,     0,     0,   530,   549,   550,   551,
     548,     0,     0,   534,   627,   539,   541,   542,   514,   513,
     519,     0,   430,   432,   415,   519,   457,     0,   441,     0,
     454,   439,     0,   479,   477,   475,     0,   559,   627,   602,
       0,   538,   627,     0,   623,     0,   599,   596,   620,   422,
     322,   325,     0,   323,   495,   492,   336,   341,     0,     0,
       0,   360,     0,   469,   466,   506,     0,     0,     0,   482,
       0,   483,   347,     0,     0,     0,   536,     0,   450,   447,
       0,   512,     0,   512,   512,   489,     0,    31,    30,   565,
     570,   566,   568,   569,    42,     0,   605,   616,     0,     0,
     625,   615,   601,     0,   327,     0,   346,   334,     0,   507,
       0,   506,     0,   469,   370,   369,   481,     0,   531,     0,
     535,   627,     0,     0,     0,   448,   445,     0,   442,   440,
       0,   567,   590,   576,   599,   591,     0,     0,   627,   571,
     627,     0,     0,   626,     0,   318,   324,   326,     0,     0,
       0,   506,   470,   473,   467,     0,   485,   532,     0,   537,
       0,     0,   512,     0,   627,     0,   586,     0,   618,   617,
     606,   560,     0,   511,     0,     0,   471,   506,   468,     0,
     450,     0,   446,     0,     0,     0,     0,     0,   607,   627,
     614,   597,     0,     0,     0,   506,   474,     0,     0,   450,
       0,   592,     0,   490,   588,   563,   561,   587,     0,   575,
     619,     0,     0,   472,     0,     0,     0,     0,     0,   593,
     594,   572,     0,   562,     0,   508,     0,     0,   512,   627,
       0,   627,   589,     0,   533,   450,   443,     0,   573,   595,
     509,     0,   592,   512,     0,   444,     0,   574
};

  /* YYPGOTO[NTERM-NUM].  */
static const short yypgoto[] =
{
    -710,  -333,   -75,   -14,   -62,  -710,  -710,  -710,   442,  -710,
    -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,  -710,
    -710,  -710,   -78,  -710,  -279,  -710,  -710,  -710,  -468,  -710,
    -710,   324,  -206,    29,  -197,  -178,   -19,    -6,  -710,  -710,
    -710,   445,  -710,  -710,   301,  -710,  -710,  -710,  -710,   -87,
    -250,  -710,  -710,  -177,  -710,  -710,   306,  -710,  -144,   463,
      41,    -4,    49,  -710,  -710,  -710,  -710,  -180,  -710,  -145,
      10,   -31,  -710,  -710,   111,  -340,  -710,  -311,  -710,    13,
    -710,  -146,  -351,  -710,   -73,  -710,    50,  -710,  -434,  -432,
     176,  -710,  -690,   -85,  -370,  -710,  -358,   -22,  -710,   326,
    -710,  -710,   477,  -710,  -266,  -676,  -709,  -710,  -710,   481,
    -710,   118,  -365,  -710,  -410,  -681,    95,  -263,  -710,  -710,
    -694,  -710,  -710,  -375,  -416,  -710,  -710,  -710,  -306,  -710,
    -401,  -400,  -402,  -710,  -710,  -710,  -710,  -710,  -710,  -214,
     -20,  -684
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const short yydefgoto[] =
{
      -1,   694,   489,   164,   348,   626,    25,    26,    27,    28,
      83,    84,    85,    86,    87,   354,    88,    89,    90,   312,
     742,   743,   349,   350,   367,   671,   672,    29,   490,   491,
      30,    94,   677,   678,   679,    31,    32,    33,    34,    35,
      36,    37,    38,    39,   177,   398,   401,   180,    40,   183,
     492,    41,   192,   792,    42,    43,   627,   628,   629,    44,
      45,    46,    97,   409,    48,   410,    49,   411,   412,   413,
     414,   493,    51,    52,   479,   480,   681,   802,   842,    99,
     417,   418,   643,   495,   496,   664,   448,    54,   100,   101,
     142,   640,   753,   377,   392,   507,   167,   436,   169,   170,
     390,    55,    56,   702,   703,   644,   704,   149,   705,   706,
     707,   426,   427,   428,   894,   895,   896,   781,   782,   783,
     138,   877,   897,   826,   908,   909,   429,   654,   793,   430,
     910,   646,   139,   831,   859,   431,   432,   433,   651,   652,
     648,   155
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const short yytable[] =
{
     166,   154,   137,   140,   141,   415,   408,   408,   351,   168,
      50,    96,   165,    53,   434,   365,   378,   368,   647,   645,
      66,   647,   311,   655,   510,    98,   171,   355,   766,   695,
     494,   440,   784,    50,   473,   508,    50,   476,   477,    53,
     506,   683,   785,   684,    95,   780,   188,   189,   190,    47,
     631,    65,   379,    50,   808,   380,   811,   352,   163,    47,
     441,   657,   153,   388,    21,   803,  -438,  -458,   731,  -458,
     310,   161,    47,   387,   478,    47,   366,   369,   371,   475,
     449,   658,   182,   825,   181,   375,   452,   184,   799,    96,
    -384,   784,    47,  -383,  -384,   186,   151,   -24,   800,    57,
     847,    58,    11,    98,   829,   437,   758,   473,   869,   444,
     445,   843,  -378,  -503,   662,   446,   473,   107,   880,   473,
     389,   714,   373,   172,   173,   174,   715,   447,   175,  -384,
    -384,   395,   391,   657,  -449,   766,   191,   690,   691,  -510,
     187,   176,   399,   376,  -510,   400,   494,  -384,   353,   185,
    -383,   866,   856,    96,   394,   630,  -379,  -503,  -438,    63,
     435,   143,   734,   193,   144,   735,    50,    98,   145,   374,
     146,   147,   416,  -352,   670,  -352,  -352,   886,   874,   633,
     634,   148,   784,   172,   173,   174,    95,  -489,   175,  -489,
    -489,  -449,   898,   673,   674,   903,   825,    65,   178,     4,
       5,   176,   636,   637,   784,    47,   376,   924,   131,   132,
     133,   134,   135,   136,   764,   765,  -503,   913,   784,   419,
     420,   421,   422,   423,   381,   424,   425,   382,   898,   383,
     822,   823,   384,   442,   386,   365,   391,   368,   768,   769,
     771,   772,   683,   927,   684,   824,   393,   683,   397,   684,
     405,     1,     2,     3,     4,     5,     6,     7,     8,   833,
     659,   716,   406,   718,     9,   403,   721,   370,   372,   156,
     453,   474,   497,   475,   163,   499,    11,   822,   823,   500,
     501,   511,   438,   632,   365,   638,   368,   723,   443,   635,
     365,   639,   368,   659,   660,   662,   366,   680,   661,   666,
     675,   692,   725,   709,   719,   744,   730,   726,   722,   727,
     689,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     728,   729,   731,   732,   733,   736,   647,   786,   737,   157,
      60,    61,    62,    63,   158,   745,   746,   473,   747,   750,
     473,   473,   760,   761,   849,   366,   748,   762,   752,   795,
     451,   366,   767,   763,   773,   774,   794,   770,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   798,   159,   801,
     812,   509,   809,   817,   827,   779,   828,   166,   365,   820,
     368,   830,  -600,   834,   838,   840,   168,   839,   641,   165,
     649,   844,   653,   864,   850,   851,   852,   365,   365,   368,
     368,   816,   854,   818,   819,   860,   861,   806,   650,   863,
     865,   867,   862,   868,   871,   870,   804,   805,   876,   873,
     878,   887,   394,   879,   883,   884,   889,   890,   647,   858,
     891,   901,   899,   730,   779,   902,   668,   904,   905,   366,
     663,   912,   914,   921,   915,   685,   686,   916,   917,   918,
     919,   923,   717,   920,   408,   925,   846,   408,   366,   366,
     882,   494,   881,   473,   473,   928,   930,   932,   162,   796,
     797,    96,   933,   936,   937,   755,   855,   647,   900,   751,
     402,   385,   872,   179,   713,    98,   160,   404,   682,   647,
     720,   481,   845,   724,   711,   396,   665,   152,   680,   810,
     150,   498,   922,   680,     1,     2,     3,     4,     5,     6,
       7,     8,   656,   821,   642,   907,   934,     9,   853,   647,
     929,   790,    59,     0,   892,   779,     0,     0,     0,    11,
     647,     0,     0,     1,     2,     3,     4,     5,     6,     7,
       8,     0,     0,     0,     0,     0,     9,   779,   926,   696,
       0,    10,     0,     0,     0,     0,   789,     0,    11,    12,
      13,   779,     0,   935,     0,   419,   420,   421,   422,   423,
      14,   424,   425,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     0,    60,    61,    62,    63,     9,   814,     0,
     408,     0,    59,     0,     0,     0,     0,     0,   756,   757,
       0,     0,   419,   420,   421,   422,   423,     0,   424,   425,
       0,    15,    16,    17,    18,    19,    20,     0,    21,     0,
       0,    64,     0,     0,     0,   416,   143,     0,   739,   144,
       0,     0,     0,   145,     0,   146,   147,   697,   698,   699,
     700,   509,     0,    22,     0,     0,     0,   741,    23,   166,
      24,     0,     0,    60,    61,    62,   701,     0,   168,     0,
       0,   165,     0,     0,     0,     0,     0,     0,   375,     0,
     165,     0,    96,   365,   365,   368,   368,    96,     0,     0,
       0,     0,     0,     0,     0,     0,    98,     0,   509,   682,
     888,    98,   408,   509,   682,     0,     0,     0,     0,   787,
       0,     0,   435,     0,     0,   435,     0,     0,     0,   906,
       0,   408,   788,     0,     0,     0,   835,     0,     0,     0,
       0,   650,     0,     0,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     0,   366,   366,     0,     0,     9,     0,
       0,     0,     0,    59,     0,   931,     0,   408,     0,     0,
      11,     0,     0,   813,     0,     0,   711,   832,   754,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     7,     8,
     841,     0,    67,   685,   686,     9,     0,     0,     0,     0,
      59,   837,     0,     0,     0,   143,     0,    11,   144,     0,
       0,   848,   145,   435,   146,   147,   697,   698,   699,   700,
       0,     0,     0,     0,    91,    92,    18,    63,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,     0,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   885,     0,     0,     0,
     676,    60,    61,    62,    63,   893,     0,     0,     0,     0,
       0,   194,     0,     0,   195,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
     221,   893,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
       0,   270,     0,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,     0,     0,   304,     0,
     305,   306,   307,   308,   309,   194,     0,     0,   313,   196,
     197,   198,   199,   200,   201,   202,   203,   314,   315,   316,
     317,   208,   318,   319,   211,   212,   213,   320,   215,   216,
     217,   218,   219,   220,   221,     0,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   321,   322,   323,   324,   261,   262,   263,   264,   265,
     266,   267,   268,   269,     0,   270,     0,   271,   272,   273,
     274,   275,   276,   325,   326,   327,   328,   329,   330,   283,
     331,   285,   286,   332,   333,   334,   335,   336,   337,   338,
     339,   340,   341,   342,   343,   344,   345,   346,   347,   303,
       0,     0,   304,     0,   305,   306,   307,   308,   309,   512,
       0,     0,   513,   514,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   527,   528,   529,   530,
     531,   532,   533,   534,   535,   536,   537,   538,   539,     0,
     540,   541,   542,   543,   544,   403,   712,   545,   546,   547,
     548,   549,   550,   551,   552,   553,   554,   555,   556,   557,
     558,   559,   560,   561,   562,   563,   564,   565,   566,   567,
     568,   569,   570,   571,   572,   573,   574,   575,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,     0,   586,
       0,   587,   588,   589,   590,   591,   592,   593,   594,   595,
     596,   597,   598,   599,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   613,   614,   615,
     616,   617,   618,   619,     0,     0,   620,     0,   621,   622,
     623,   624,   625,   512,     0,     0,   513,   514,   515,   516,
     517,   518,   519,   520,   521,   522,   523,   524,   525,   526,
     527,   528,   529,   530,   531,   532,   533,   534,   535,   536,
     537,   538,   539,     0,   540,   541,   542,   543,   544,   403,
       0,   545,   546,   547,   548,   549,   550,   551,   552,   553,
     554,   555,   556,   557,   558,   559,   560,   561,   562,   563,
     564,   565,   566,   567,   568,   569,   570,   571,   572,   573,
     574,   575,   576,   577,   578,   579,   580,   581,   582,   583,
     584,   585,     0,   586,     0,   587,   588,   589,   590,   591,
     592,   593,   594,   595,   596,   597,   598,   599,   600,   601,
     602,   603,   604,   605,   606,   607,   608,   609,   610,   611,
     612,   613,   614,   615,   616,   617,   618,   619,  -576,     0,
     620,     0,   621,   622,   623,   624,   625,  -576,  -576,  -576,
    -576,     0,  -576,  -576,     0,     0,     0,  -576,     0,     0,
       0,     0,     0,     0,  -576,  -576,  -576,  -576,  -576,  -576,
    -576,  -576,  -576,  -576,  -576,  -576,     0,  -576,  -576,  -576,
    -576,  -576,  -576,  -576,  -576,  -576,  -576,  -576,  -576,  -576,
    -576,  -576,  -576,  -576,  -576,     0,     0,     0,     0,     0,
    -576,  -576,  -576,  -576,  -576,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -576,     0,  -576,  -576,  -576,  -576,  -576,  -576,     0,
    -576,     0,     0,  -576,  -576,  -576,  -576,  -576,  -576,  -576,
    -576,  -576,  -576,  -576,  -576,  -576,  -576,  -576,  -576,     0,
     102,     0,     0,     0,     0,     0,     0,     0,  -576,   103,
     104,   105,   106,     0,   107,   108,   502,     0,     0,   109,
     485,     0,   486,     0,   487,   358,   503,     0,     0,   488,
       0,     0,     0,     0,     1,     2,     3,     4,     5,     6,
       7,     8,     0,     0,   360,   361,   163,     9,     0,     0,
       0,     0,    59,     0,     0,     0,     0,   362,   363,    11,
       0,     0,     0,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   504,     0,   114,   115,   116,   117,   118,
     119,     0,   120,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,     0,     0,    91,    92,    18,    63,     0,     0,   505,
       1,     2,     3,     4,     5,     6,     7,     8,     0,     0,
       0,     0,     0,     9,     0,     0,     0,     0,    59,     0,
       0,     0,     0,     0,     0,    11,     0,     0,     0,    93,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
     103,   104,   105,   106,     0,   107,   108,     0,     0,     0,
     109,     0,     0,   356,     0,   357,   358,     0,     0,     0,
     359,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   361,     0,     0,    91,
      92,    18,    63,     0,     0,     0,     0,     0,   362,   363,
       0,     0,     0,     0,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,   364,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   676,   114,   115,   116,   117,
     118,   119,     0,   120,     0,     0,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   -32,     0,     0,   669,     0,     0,     0,     0,
       0,   -32,   -32,   -32,   -32,     0,   -32,   -32,     0,     0,
       0,   -32,     0,     0,   -32,   -32,   -32,   -32,     0,     0,
       0,   -32,     0,     0,     0,     0,     0,     1,     2,     3,
       4,     5,     6,     7,     8,     0,   -32,   -32,     0,     0,
       9,     0,     0,     0,     0,    59,     0,     0,     0,   -32,
     -32,     0,    11,     0,     0,   -32,   -32,   -32,   -32,     0,
       0,     0,     0,     0,     0,     0,   -32,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -32,   -32,   -32,
     -32,   -32,   -32,     0,   -32,     0,     0,   -32,   -32,   -32,
     -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,   -32,
     -32,   -32,   -32,   -33,     0,   -32,    91,    92,    18,    63,
       0,     0,   -33,   -33,   -33,   -33,     0,   -33,   -33,     0,
       0,     0,   -33,     0,     0,   -33,   -33,   -33,   -33,     0,
       0,     0,   -33,     0,     0,     0,     0,     0,     1,     2,
       3,     4,     5,     6,     7,     8,     0,   -33,   -33,     0,
       0,     9,     0,     0,     0,     0,    59,     0,     0,     0,
     -33,   -33,     0,    11,     0,     0,   -33,   -33,   -33,   -33,
       0,     0,     0,     0,     0,     0,     0,   -33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -33,   -33,
     -33,   -33,   -33,   -33,     0,   -33,     0,     0,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -34,     0,   -33,    60,    61,    62,
      63,     0,     0,   -34,   -34,   -34,   -34,     0,   -34,   -34,
       0,     0,     0,   -34,     0,     0,   -34,   -34,   -34,   -34,
       0,     0,     0,   -34,     0,     0,     0,     0,     0,     1,
       2,     3,     4,     5,     6,     7,     8,     0,   -34,   -34,
       0,     0,   407,     0,     0,     0,     0,    59,     0,     0,
       0,   -34,   -34,     0,    11,     0,     0,   -34,   -34,   -34,
     -34,     0,     0,     0,     0,     0,     0,     0,   -34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -34,
     -34,   -34,   -34,   -34,   -34,     0,   -34,     0,     0,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -35,     0,   -34,    60,    61,
      62,    63,     0,     0,   -35,   -35,   -35,   -35,     0,   -35,
     -35,     0,     0,     0,   -35,     0,     0,   -35,   -35,   -35,
     -35,     0,     0,     0,   -35,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -35,
     -35,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -35,   -35,     0,     0,     0,     0,   -35,   -35,
     -35,   -35,     0,     0,     0,     0,     0,     0,     0,   -35,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -35,   -35,   -35,   -35,   -35,   -35,     0,   -35,     0,     0,
     -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,   -35,
     -35,   -35,   -35,   -35,   -35,   -35,   -36,     0,   -35,     0,
       0,     0,     0,     0,     0,   -36,   -36,   -36,   -36,     0,
     -36,   -36,     0,     0,     0,   -36,     0,     0,   -36,   -36,
     -36,   -36,     0,     0,     0,   -36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -36,   -36,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -36,   -36,     0,     0,     0,     0,   -36,
     -36,   -36,   -36,     0,     0,     0,     0,     0,     0,     0,
     -36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -36,   -36,   -36,   -36,   -36,   -36,     0,   -36,     0,
       0,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,   -36,
     -36,   -36,   -36,   -36,   -36,   -36,   -36,   -58,     0,   -36,
       0,     0,     0,     0,     0,     0,   -58,   -58,   -58,   -58,
       0,   -58,   -58,     0,     0,     0,   -58,     0,     0,   -58,
     -58,   -58,   -58,     0,     0,     0,   -58,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -58,   -58,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -58,   -58,     0,     0,     0,     0,
     -58,   -58,   -58,   -58,     0,     0,     0,     0,     0,     0,
       0,   -58,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -58,   -58,   -58,   -58,   -58,   -58,     0,   -58,
       0,     0,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,
     -58,   -58,   -58,   -58,   -58,   -58,   -58,   -58,   -59,     0,
    -615,     0,     0,     0,     0,     0,     0,   -59,   -59,   -59,
     -59,     0,   -59,   -59,     0,     0,     0,   -59,     0,     0,
     -59,   -59,   -59,   -59,     0,     0,     0,   -59,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -59,   -59,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -59,   -59,     0,     0,     0,
       0,   -59,   -59,   -59,   -59,     0,     0,     0,     0,     0,
       0,     0,   -59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -59,   -59,   -59,   -59,   -59,   -59,     0,
     -59,     0,     0,   -59,   -59,   -59,   -59,   -59,   -59,   -59,
     -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -59,   -24,
       0,  -576,     0,     0,     0,     0,     0,     0,   -24,   -24,
     -24,   -24,     0,   -24,   -24,     0,     0,     0,   -24,     0,
       0,   -24,   -24,   -24,   -24,     0,     0,     0,   -24,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -24,   -24,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -24,   -24,     0,     0,
       0,     0,   -24,   -24,   -24,   -24,     0,     0,     0,     0,
       0,     0,     0,   -24,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -24,   -24,   -24,   -24,   -24,   -24,
       0,   -24,     0,     0,   -24,   -24,   -24,   -24,   -24,   -24,
     -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,   -24,
     -40,     0,   -24,     0,     0,     0,     0,     0,     0,   -40,
     -40,   -40,   -40,     0,   -40,   -40,     0,     0,     0,   -40,
       0,     0,   -40,   -40,   -40,   -40,     0,     0,     0,   -40,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -40,   -40,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -40,   -40,     0,
       0,     0,     0,   -40,   -40,   -40,   -40,     0,     0,     0,
       0,     0,     0,     0,   -40,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -40,   -40,   -40,   -40,   -40,
     -40,     0,   -40,     0,     0,   -40,   -40,   -40,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -40,   -39,     0,   -40,     0,     0,     0,     0,     0,     0,
     -39,   -39,   -39,   -39,     0,   -39,   -39,     0,     0,     0,
     -39,     0,     0,   -39,   -39,   -39,   -39,     0,     0,     0,
     -39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -39,   -39,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -39,   -39,
       0,     0,     0,     0,   -39,   -39,   -39,   -39,     0,     0,
       0,     0,     0,     0,     0,   -39,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -39,   -39,   -39,   -39,
     -39,   -39,     0,   -39,     0,     0,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -37,     0,   -39,     0,     0,     0,     0,     0,
       0,   -37,   -37,   -37,   -37,     0,   -37,   -37,     0,     0,
       0,   -37,     0,     0,   -37,   -37,   -37,   -37,     0,     0,
       0,   -37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -37,   -37,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -37,
     -37,     0,     0,     0,     0,   -37,   -37,   -37,   -37,     0,
       0,     0,     0,     0,     0,     0,   -37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -37,   -37,   -37,
     -37,   -37,   -37,     0,   -37,     0,     0,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,   -37,
     -37,   -37,   -37,   -38,     0,   -37,     0,     0,     0,     0,
       0,     0,   -38,   -38,   -38,   -38,     0,   -38,   -38,     0,
       0,     0,   -38,     0,     0,   -38,   -38,   -38,   -38,     0,
       0,     0,   -38,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -38,   -38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -38,   -38,     0,     0,     0,     0,   -38,   -38,   -38,   -38,
       0,     0,     0,     0,     0,     0,     0,   -38,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -38,   -38,
     -38,   -38,   -38,   -38,     0,   -38,     0,     0,   -38,   -38,
     -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,   -38,
     -38,   -38,   -38,   -38,   -31,     0,   -38,     0,     0,     0,
       0,     0,     0,   -31,   -31,   -31,   -31,     0,   -31,   -31,
       0,     0,     0,   -31,     0,     0,   -31,   -31,   -31,   -31,
       0,     0,     0,   -31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   -31,   -31,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -31,   -31,     0,     0,     0,     0,   -31,   -31,   -31,
     -31,     0,     0,     0,     0,     0,     0,     0,   -31,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -31,
     -31,   -31,   -31,   -31,   -31,     0,   -31,     0,     0,   -31,
     -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,   -31,
     -31,   -31,   -31,   -31,   -31,   -25,     0,   -31,     0,     0,
       0,     0,     0,     0,   -25,   -25,   -25,   -25,     0,   -25,
     -25,     0,     0,     0,   -25,     0,     0,   -25,   -25,   -25,
     -25,     0,     0,     0,   -25,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   -25,
     -25,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -25,   -25,     0,     0,     0,     0,   -25,   -25,
     -25,   -25,     0,     0,     0,     0,     0,     0,     0,   -25,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -25,   -25,   -25,   -25,   -25,   -25,     0,   -25,     0,     0,
     -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,   -25,
     -25,   -25,   -25,   -25,   -25,   -25,   -29,     0,   -25,     0,
       0,     0,     0,     0,     0,   -29,   -29,   -29,   -29,     0,
     -29,   -29,     0,     0,     0,   -29,     0,     0,   -29,   -29,
     -29,   -29,     0,     0,     0,   -29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     -29,   -29,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -29,   -29,     0,     0,     0,     0,   -29,
     -29,   -29,   -29,     0,     0,     0,     0,     0,     0,     0,
     -29,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -29,   -29,   -29,   -29,   -29,   -29,     0,   -29,     0,
       0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -28,     0,   -29,
       0,     0,     0,     0,     0,     0,   -28,   -28,   -28,   -28,
       0,   -28,   -28,     0,     0,     0,   -28,     0,     0,   -28,
     -28,   -28,   -28,     0,     0,     0,   -28,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   -28,   -28,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -28,   -28,     0,     0,     0,     0,
     -28,   -28,   -28,   -28,     0,     0,     0,     0,     0,     0,
       0,   -28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -28,   -28,   -28,   -28,   -28,   -28,     0,   -28,
       0,     0,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,
     -28,   -28,   -28,   -28,   -28,   -28,   -28,   -28,   -26,     0,
     -28,     0,     0,     0,     0,     0,     0,   -26,   -26,   -26,
     -26,     0,   -26,   -26,     0,     0,     0,   -26,     0,     0,
     -26,   -26,   -26,   -26,     0,     0,     0,   -26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   -26,   -26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -26,   -26,     0,     0,     0,
       0,   -26,   -26,   -26,   -26,     0,     0,     0,     0,     0,
       0,     0,   -26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -26,   -26,   -26,   -26,   -26,   -26,     0,
     -26,     0,     0,   -26,   -26,   -26,   -26,   -26,   -26,   -26,
     -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -26,   -27,
       0,   -26,     0,     0,     0,     0,     0,     0,   -27,   -27,
     -27,   -27,     0,   -27,   -27,     0,     0,     0,   -27,     0,
       0,   -27,   -27,   -27,   -27,     0,     0,     0,   -27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -27,   -27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   -27,   -27,     0,     0,
       0,     0,   -27,   -27,   -27,   -27,     0,     0,     0,     0,
       0,     0,     0,   -27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -27,   -27,   -27,   -27,   -27,   -27,
       0,   -27,     0,     0,   -27,   -27,   -27,   -27,   -27,   -27,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,
     -41,     0,   -27,     0,     0,     0,     0,     0,     0,   -41,
     -41,   -41,   -41,     0,   -41,   -41,     0,     0,     0,   -41,
       0,     0,   -41,   -41,   -41,   -41,     0,     0,     0,   -41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -41,   -41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -41,   -41,     0,
       0,     0,     0,   -41,   -41,   -41,   -41,     0,     0,     0,
       0,     0,     0,     0,   -41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -41,   -41,   -41,   -41,   -41,
     -41,     0,   -41,     0,     0,   -41,   -41,   -41,   -41,   -41,
     -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,  -134,     0,   -41,     0,     0,     0,     0,     0,     0,
    -134,  -134,  -134,  -134,     0,  -134,  -134,     0,     0,     0,
    -134,     0,     0,  -134,  -134,  -134,  -134,     0,     0,     0,
    -134,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -134,  -134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -134,  -134,
       0,     0,     0,     0,  -134,  -134,  -134,  -134,     0,     0,
       0,     0,     0,     0,     0,  -134,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -134,  -134,  -134,  -134,
    -134,  -134,     0,  -134,     0,     0,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -135,     0,  -584,     0,     0,     0,     0,     0,
       0,  -135,  -135,  -135,  -135,     0,  -135,  -135,     0,     0,
       0,  -135,     0,     0,  -135,  -135,  -135,  -135,     0,     0,
       0,  -135,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -135,  -135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -135,
    -135,     0,     0,     0,     0,  -135,  -135,  -135,  -135,     0,
       0,     0,     0,     0,     0,     0,  -135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -135,  -135,  -135,
    -135,  -135,  -135,     0,  -135,     0,     0,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -136,     0,  -583,     0,     0,     0,     0,
       0,     0,  -136,  -136,  -136,  -136,     0,  -136,  -136,     0,
       0,     0,  -136,     0,     0,  -136,  -136,  -136,  -136,     0,
       0,     0,  -136,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -136,  -136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -136,  -136,     0,     0,     0,     0,  -136,  -136,  -136,  -136,
       0,     0,     0,     0,     0,     0,     0,  -136,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -136,  -136,
    -136,  -136,  -136,  -136,     0,  -136,     0,     0,  -136,  -136,
    -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,  -136,  -137,     0,  -581,     0,     0,     0,
       0,     0,     0,  -137,  -137,  -137,  -137,     0,  -137,  -137,
       0,     0,     0,  -137,     0,     0,  -137,  -137,  -137,  -137,
       0,     0,     0,  -137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -137,  -137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -137,  -137,     0,     0,     0,     0,  -137,  -137,  -137,
    -137,     0,     0,     0,     0,     0,     0,     0,  -137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -137,
    -137,  -137,  -137,  -137,  -137,     0,  -137,     0,     0,  -137,
    -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,  -137,
    -137,  -137,  -137,  -137,  -137,  -138,     0,  -579,     0,     0,
       0,     0,     0,     0,  -138,  -138,  -138,  -138,     0,  -138,
    -138,     0,     0,     0,  -138,     0,     0,  -138,  -138,  -138,
    -138,     0,     0,     0,  -138,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -138,
    -138,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -138,  -138,     0,     0,     0,     0,  -138,  -138,
    -138,  -138,     0,     0,     0,     0,     0,     0,     0,  -138,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -138,  -138,  -138,  -138,  -138,  -138,     0,  -138,     0,     0,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -139,     0,  -580,     0,
       0,     0,     0,     0,     0,  -139,  -139,  -139,  -139,     0,
    -139,  -139,     0,     0,     0,  -139,     0,     0,  -139,  -139,
    -139,  -139,     0,     0,     0,  -139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -139,  -139,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -139,  -139,     0,     0,     0,     0,  -139,
    -139,  -139,  -139,     0,     0,     0,     0,     0,     0,     0,
    -139,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -139,  -139,  -139,  -139,  -139,  -139,     0,  -139,     0,
       0,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,  -139,
    -139,  -139,  -139,  -139,  -139,  -139,  -139,  -140,     0,  -582,
       0,     0,     0,     0,     0,     0,  -140,  -140,  -140,  -140,
       0,  -140,  -140,     0,     0,     0,  -140,     0,     0,  -140,
    -140,  -140,  -140,     0,     0,     0,  -140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -140,  -140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -140,  -140,     0,     0,     0,     0,
    -140,  -140,  -140,  -140,     0,     0,     0,     0,     0,     0,
       0,  -140,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -140,  -140,  -140,  -140,  -140,  -140,     0,  -140,
       0,     0,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,  -140,  -140,  -140,  -141,     0,
    -578,     0,     0,     0,     0,     0,     0,  -141,  -141,  -141,
    -141,     0,  -141,  -141,     0,     0,     0,  -141,     0,     0,
    -141,  -141,  -141,  -141,     0,     0,     0,  -141,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -141,  -141,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -141,  -141,     0,     0,     0,
       0,  -141,  -141,  -141,  -141,     0,     0,     0,     0,     0,
       0,     0,  -141,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -141,  -141,  -141,  -141,  -141,  -141,     0,
    -141,     0,     0,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -142,
       0,  -577,     0,     0,     0,     0,     0,     0,  -142,  -142,
    -142,  -142,     0,  -142,  -142,     0,     0,     0,  -142,     0,
       0,  -142,  -142,  -142,  -142,     0,     0,     0,  -142,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -142,  -142,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -142,  -142,     0,     0,
       0,     0,  -142,  -142,  -142,  -142,     0,     0,     0,     0,
       0,     0,     0,  -142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -142,  -142,  -142,  -142,  -142,  -142,
       0,  -142,     0,     0,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
     -30,     0,  -585,     0,     0,     0,     0,     0,     0,   -30,
     -30,   -30,   -30,     0,   -30,   -30,     0,     0,     0,   -30,
       0,     0,   -30,   -30,   -30,   -30,     0,     0,     0,   -30,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   -30,   -30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -30,   -30,     0,
       0,     0,     0,   -30,   -30,   -30,   -30,     0,     0,     0,
       0,     0,     0,     0,   -30,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   -30,   -30,   -30,   -30,   -30,
     -30,     0,   -30,     0,     0,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,  -144,     0,   -30,     0,     0,     0,     0,     0,     0,
    -144,  -144,  -144,  -144,     0,  -144,  -144,     0,     0,     0,
    -144,     0,     0,  -144,  -144,  -144,  -144,     0,     0,     0,
    -144,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  -144,  -144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -144,  -144,
       0,     0,     0,     0,  -144,  -144,  -144,  -144,     0,     0,
       0,     0,     0,     0,     0,  -144,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -144,  -144,  -144,  -144,
    -144,  -144,     0,  -144,     0,     0,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -145,     0,  -613,     0,     0,     0,     0,     0,
       0,  -145,  -145,  -145,  -145,     0,  -145,  -145,     0,     0,
       0,  -145,     0,     0,  -145,  -145,  -145,  -145,     0,     0,
       0,  -145,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -145,  -145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -145,
    -145,     0,     0,     0,     0,  -145,  -145,  -145,  -145,     0,
       0,     0,     0,     0,     0,     0,  -145,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -145,  -145,  -145,
    -145,  -145,  -145,     0,  -145,     0,     0,  -145,  -145,  -145,
    -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,  -145,
    -145,  -145,  -145,  -146,     0,  -611,     0,     0,     0,     0,
       0,     0,  -146,  -146,  -146,  -146,     0,  -146,  -146,     0,
       0,     0,  -146,     0,     0,  -146,  -146,  -146,  -146,     0,
       0,     0,  -146,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -146,  -146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -146,  -146,     0,     0,     0,     0,  -146,  -146,  -146,  -146,
       0,     0,     0,     0,     0,     0,     0,  -146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -146,  -146,
    -146,  -146,  -146,  -146,     0,  -146,     0,     0,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -147,     0,  -610,     0,     0,     0,
       0,     0,     0,  -147,  -147,  -147,  -147,     0,  -147,  -147,
       0,     0,     0,  -147,     0,     0,  -147,  -147,  -147,  -147,
       0,     0,     0,  -147,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -147,  -147,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -147,  -147,     0,     0,     0,     0,  -147,  -147,  -147,
    -147,     0,     0,     0,     0,     0,     0,     0,  -147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -147,
    -147,  -147,  -147,  -147,  -147,     0,  -147,     0,     0,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -148,     0,  -612,     0,     0,
       0,     0,     0,     0,  -148,  -148,  -148,  -148,     0,  -148,
    -148,     0,     0,     0,  -148,     0,     0,  -148,  -148,  -148,
    -148,     0,     0,     0,  -148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -148,
    -148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  -148,  -148,     0,     0,     0,     0,  -148,  -148,
    -148,  -148,     0,     0,     0,     0,     0,     0,     0,  -148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -148,  -148,  -148,  -148,  -148,  -148,     0,  -148,     0,     0,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -149,     0,  -609,     0,
       0,     0,     0,     0,     0,  -149,  -149,  -149,  -149,     0,
    -149,  -149,     0,     0,     0,  -149,     0,     0,  -149,  -149,
    -149,  -149,     0,     0,     0,  -149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -149,  -149,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -149,  -149,     0,     0,     0,     0,  -149,
    -149,  -149,  -149,     0,     0,     0,     0,     0,     0,     0,
    -149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -149,  -149,  -149,  -149,  -149,  -149,     0,  -149,     0,
       0,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,   102,     0,  -608,
       0,     0,     0,     0,     0,     0,   103,   104,   105,   106,
       0,   107,   108,     0,     0,     0,   109,     0,     0,   356,
     438,   357,   358,     0,     0,     0,   359,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   360,   361,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   362,   363,     0,     0,     0,     0,
     110,   111,   112,   113,     0,     0,     0,     0,     0,     0,
       0,   364,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,     0,   120,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,     0,
     439,   102,     1,     2,     3,     4,     5,     6,     7,     8,
     103,   104,   105,   106,     0,   687,   108,   502,     0,     0,
     688,   485,     0,   486,     0,   487,   358,    11,     0,     0,
     488,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   360,   361,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   362,   363,
       0,     0,     0,     0,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,    61,    62,    63,     0,   114,   115,   116,   117,
     118,   119,     0,   120,     0,     0,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   102,     0,     0,     0,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,   482,   483,
     484,   109,   485,     0,   486,   438,   487,   358,     0,     0,
       0,   488,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   360,   361,   163,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   362,
     363,     0,     0,     0,     0,   110,   111,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,     0,   120,     0,     0,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   102,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   104,   105,   106,     0,   107,   108,   775,
       0,     0,   109,   485,     0,   486,     0,   487,   358,     0,
       0,     0,   488,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   153,     0,     0,   360,   361,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     362,   363,     0,     0,     0,     0,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   776,   777,   115,
     116,   117,   118,   119,     0,   120,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   778,   131,   132,
     133,   134,   135,   136,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,   106,     0,   107,   108,
     502,     0,     0,   109,   485,     0,   486,     0,   487,   358,
       0,     0,     0,   488,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,     0,     0,   360,   361,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   362,   363,     0,     0,   857,     0,   110,   111,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,     0,   120,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   102,     0,     0,     0,     0,
       0,     0,     0,     0,   103,   104,   105,   106,     0,   107,
     108,   502,     0,     0,   109,   485,  -627,   486,     0,   487,
     358,     0,     0,     0,   488,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,     0,     0,   360,
     361,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   362,   363,     0,     0,     0,     0,   110,   111,
     112,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,     0,   120,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   102,     0,     0,     0,
       0,     0,     0,     0,     0,   103,   104,   105,   106,     0,
     107,   108,   502,     0,     0,   109,   485,     0,   486,     0,
     487,   358,     0,     0,     0,   488,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,     0,     0,
     360,   361,   163,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   362,   363,     0,     0,     0,     0,   110,
     111,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,     0,   120,     0,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   102,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   104,   105,   106,
       0,   107,   108,   775,     0,     0,   109,   485,     0,   486,
       0,   487,   358,     0,     0,     0,   488,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   360,   361,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   362,   363,     0,     0,     0,     0,
     110,   111,   112,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   776,   777,   115,   116,   117,   118,   119,     0,   120,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   778,   131,   132,   133,   134,   135,   136,   102,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   104,   105,
     106,     0,   107,   108,   502,     0,     0,   109,   485,     0,
     486,     0,   487,   358,     0,     0,     0,   488,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   360,   361,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   362,   363,     0,     0,     0,
       0,   110,   111,   112,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,     0,
     120,     0,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   102,
       0,     0,     0,     0,     0,     0,     0,     0,   103,   104,
     105,   106,     0,   107,   108,     0,     0,     0,   109,     0,
       0,   356,     0,   357,   358,     0,     0,     0,   359,     0,
       0,     0,     1,     2,     3,     4,     5,     6,     7,     8,
       0,     0,     0,   360,   361,     9,     0,     0,     0,     0,
      59,     0,     0,     0,   444,   445,   362,   363,     0,     0,
       0,     0,   110,   111,   112,   113,     0,     0,     0,     0,
       0,     0,   447,   364,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
       0,   120,     0,     0,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
     102,    60,    61,    62,     0,     0,     0,     0,     0,   103,
     104,   105,   106,     0,   107,   108,     0,     0,     0,   109,
       0,     0,     0,     0,     0,     0,    11,     0,     0,  -519,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    63,     0,   114,   115,   116,   117,   118,
     119,     0,   120,     0,     0,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   102,     0,     0,     0,     0,     0,     0,     0,     0,
     103,   104,   105,   106,     0,   107,   108,   738,     0,     0,
     109,     0,     0,     0,     0,     0,     0,    11,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,     0,   163,     0,     0,
       0,   693,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    63,     0,   114,   115,   116,   117,
     118,   119,     0,   120,     0,     0,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   102,     0,     0,     0,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,     0,     0,
       0,   109,     0,     0,   667,     0,     0,     0,     0,     0,
       0,   710,   815,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,     0,     0,     0,     0,     0,   472,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,     0,   120,     0,     0,   121,   122,   123,
     124,   125,   126,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,   102,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   104,   105,   106,     0,   107,   108,     0,
       0,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   752,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   163,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,   115,
     116,   117,   118,   119,     0,   120,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   102,     0,     0,     0,     0,     0,
       0,     0,     0,   103,   104,   105,   106,   759,   107,   108,
       0,     0,     0,   109,     0,     0,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,     0,     0,     0,     0,     0,   693,
     163,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,   110,   111,   112,
     113,     0,     0,     0,     0,   103,   104,   105,   106,     0,
     107,   108,     0,     0,     0,   109,     0,     0,     0,   114,
     115,   116,   117,   118,   119,   450,   120,     0,     0,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   102,   110,
     111,   112,   113,     0,     0,     0,     0,   103,   104,   105,
     106,     0,   107,   108,     0,     0,     0,   109,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   710,   120,     0,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   102,     0,     0,     0,
       0,   110,   111,   112,   113,   103,   104,   105,   106,     0,
     107,   108,     0,     0,     0,   109,     0,     0,     0,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,     0,
     120,     0,     0,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,     0,
       0,     0,     0,     0,     0,     0,     0,   740,     0,   110,
     111,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,     0,   120,     0,
       0,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   102,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   104,   105,   106,
     911,   791,   108,     0,     0,     0,   109,     0,     0,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,     0,     0,     0,
       0,     0,   693,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,     0,     0,     0,     0,
     110,   111,   112,   113,   103,   104,   105,   106,     0,   107,
     108,     0,     0,     0,   109,     0,     0,     0,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,     0,   120,
       0,     0,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,     0,     0,
       0,     0,     0,   102,     0,     0,   836,     0,   110,   111,
     112,   113,   103,   104,   105,   106,     0,   107,   108,     0,
       0,     0,   109,     0,     0,     0,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,     0,   120,     0,     0,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,   115,
     116,   117,   118,   119,     0,   120,     0,     0,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   875,     0,     0,     0,     0,     0,
       0,     0,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
     749,     0,     0,     0,     0,   693,     0,   454,   455,   456,
     457,   458,   459,   460,   461,   462,   463,   464,   465,   466,
     467,   468,   469,   470,   471,   807,     0,     0,     0,     0,
     472,     0,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
       0,     0,     0,   708,     0,   693,   454,   455,   456,   457,
     458,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     468,   469,   470,   471,     0,     0,     0,     0,     0,   693,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,     0,     0,
       0,     0,     0,   472,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,     0,     0,     0,     0,     0,   693,   454,   455,
     456,   457,   458,   459,   460,   461,   462,   463,   464,   465,
     466,   467,   468,   469,   470,   471,     0,     0,     0,     0,
       0,   472,   454,   455,   456,   457,   458,   459,   460,   461,
     462,   463,   464,   465,   466,   467,   468,   469,   470,   471,
       0,     0,     0,     0,     0,   693
};

static const short yycheck[] =
{
      31,    21,    16,    17,    18,   185,   184,   185,    86,    31,
       0,    15,    31,     0,   191,    90,   101,    90,   420,   420,
      10,   423,    84,   423,   394,    15,    32,    89,   704,   497,
     381,   310,   726,    23,   367,   393,    26,   377,   378,    26,
     391,   475,   726,   475,    15,   726,    60,    61,    62,     0,
     408,    10,   137,    43,   763,   140,   765,    26,    49,    10,
     310,   426,    44,    29,    89,   755,    31,    32,    24,    34,
      84,     0,    23,   160,    31,    26,    90,    91,    92,    36,
     359,   432,   123,   777,    43,    99,   365,    32,    25,    93,
      29,   785,    43,    29,    33,    36,   121,    33,    35,     9,
     809,    11,    29,    93,   785,   192,    33,   440,    64,    26,
      27,   801,    35,    36,    26,    32,   449,    17,    18,   452,
      86,    33,    93,     4,     5,     6,    32,    44,     9,    33,
      34,   122,    38,   498,    32,   811,    34,   488,   489,    31,
      36,    22,     6,    35,    36,     9,   497,    86,   117,    32,
      86,   841,   828,   157,   168,   405,    35,    36,   123,    86,
     191,     3,    31,    30,     6,    34,   156,   157,    10,    31,
      12,    13,   186,    31,   453,    33,    34,   867,   854,    33,
      34,    23,   876,     4,     5,     6,   157,    31,     9,    33,
      34,    32,   876,   472,   473,   885,   890,   156,     6,     7,
       8,    22,    33,    34,   898,   156,    35,   916,   108,   109,
     110,   111,   112,   113,    33,    34,    36,   898,   912,    90,
      91,    92,    93,    94,    40,    96,    97,    23,   912,    36,
      17,    18,    23,   311,   121,   310,    38,   310,    32,    33,
      33,    34,   676,   919,   676,    32,    32,   681,     6,   681,
      32,     4,     5,     6,     7,     8,     9,    10,    11,    33,
      34,   631,    31,   633,    17,    36,   636,    91,    92,    22,
      32,    35,    40,    36,    49,    32,    29,    17,    18,    31,
      31,     6,    26,    32,   359,    40,   359,   638,   350,    34,
     365,    34,   365,    34,    31,    26,   310,   475,    32,    22,
      32,    31,    37,    39,    64,   663,    32,    40,    64,    31,
     488,    98,    99,   100,   101,   102,   103,   104,   105,   106,
      40,    31,    24,    40,    32,    32,   728,   728,    31,    82,
      83,    84,    85,    86,    87,    33,    33,   670,    33,    25,
     673,   674,   693,   694,   812,   359,    34,    31,    35,    34,
     364,   365,   710,    35,    33,    33,    33,   715,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    34,   121,    34,
      40,   393,    35,    64,    32,   726,    32,   408,   453,   107,
     453,    34,    33,    33,    25,    32,   408,    35,   419,   408,
     421,    31,   423,    35,    33,    33,    33,   472,   473,   472,
     473,   771,    32,   773,   774,    33,    31,   758,   422,    33,
      25,    34,    95,    31,    33,    32,   756,   757,    34,    33,
      33,    24,   436,    34,    32,    34,    32,    95,   830,   830,
      32,    25,    33,    32,   785,    25,   450,    33,    33,   453,
     446,    34,    34,    34,    33,   476,   477,    35,    33,    33,
      32,    25,   632,    33,   632,    32,   807,   635,   472,   473,
     862,   812,   862,   796,   797,    33,    33,    32,    26,   748,
     749,   475,    33,    33,    33,   681,   827,   879,   879,   676,
     179,   157,   852,    38,   628,   475,    23,   181,   475,   891,
     635,   380,   803,   639,   508,   169,   446,    20,   676,   765,
      19,   383,   912,   681,     4,     5,     6,     7,     8,     9,
      10,    11,    37,   776,   419,   890,   932,    17,   824,   921,
     921,   735,    22,    -1,   875,   876,    -1,    -1,    -1,    29,
     932,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    -1,    -1,    -1,    -1,    -1,    17,   898,   918,    37,
      -1,    22,    -1,    -1,    -1,    -1,   733,    -1,    29,    30,
      31,   912,    -1,   933,    -1,    90,    91,    92,    93,    94,
      41,    96,    97,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    83,    84,    85,    86,    17,   768,    -1,
     768,    -1,    22,    -1,    -1,    -1,    -1,    -1,   683,   684,
      -1,    -1,    90,    91,    92,    93,    94,    -1,    96,    97,
      -1,    82,    83,    84,    85,    86,    87,    -1,    89,    -1,
      -1,   121,    -1,    -1,    -1,   639,     3,    -1,   659,     6,
      -1,    -1,    -1,    10,    -1,    12,    13,    14,    15,    16,
      17,   663,    -1,   114,    -1,    -1,    -1,   661,   119,   680,
     121,    -1,    -1,    83,    84,    85,    33,    -1,   680,    -1,
      -1,   680,    -1,    -1,    -1,    -1,    -1,    -1,   682,    -1,
     689,    -1,   676,   748,   749,   748,   749,   681,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   676,    -1,   710,   676,
     870,   681,   870,   715,   681,    -1,    -1,    -1,    -1,   730,
      -1,    -1,   733,    -1,    -1,   736,    -1,    -1,    -1,   889,
      -1,   889,   732,    -1,    -1,    -1,   794,    -1,    -1,    -1,
      -1,   735,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    10,    11,    -1,   748,   749,    -1,    -1,    17,    -1,
      -1,    -1,    -1,    22,    -1,   925,    -1,   925,    -1,    -1,
      29,    -1,    -1,   767,    -1,    -1,   770,   788,    37,    -1,
      -1,    -1,     4,     5,     6,     7,     8,     9,    10,    11,
     801,    -1,    30,   804,   805,    17,    -1,    -1,    -1,    -1,
      22,   795,    -1,    -1,    -1,     3,    -1,    29,     6,    -1,
      -1,   811,    10,   824,    12,    13,    14,    15,    16,    17,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    -1,
      78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   867,    -1,    -1,    -1,
     119,    83,    84,    85,    86,   876,    -1,    -1,    -1,    -1,
      -1,     0,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   912,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      -1,    80,    -1,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,    -1,    -1,   117,    -1,
     119,   120,   121,   122,   123,     0,    -1,    -1,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    -1,    80,    -1,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
      -1,    -1,   117,    -1,   119,   120,   121,   122,   123,     0,
      -1,    -1,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    -1,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    -1,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    -1,    -1,   117,    -1,   119,   120,
     121,   122,   123,     0,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      -1,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    -1,    80,    -1,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,     3,    -1,
     117,    -1,   119,   120,   121,   122,   123,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    -1,
       3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   123,    12,
      13,    14,    15,    -1,    17,    18,    19,    -1,    -1,    22,
      23,    -1,    25,    -1,    27,    28,    29,    -1,    -1,    32,
      -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    -1,    -1,    47,    48,    49,    17,    -1,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    60,    61,    29,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,    -1,    -1,    83,    84,    85,    86,    -1,    -1,   122,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,    -1,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    -1,   119,
      -1,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    -1,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,    -1,   117,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    10,    11,    -1,    47,    48,    -1,    -1,
      17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,    60,
      61,    -1,    29,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,   116,    83,    84,    85,    86,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,     4,     5,
       6,     7,     8,     9,    10,    11,    -1,    47,    48,    -1,
      -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      60,    61,    -1,    29,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,   116,    83,    84,    85,
      86,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    10,    11,    -1,    47,    48,
      -1,    -1,    17,    -1,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    60,    61,    -1,    29,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     3,    -1,   116,    83,    84,
      85,    86,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     3,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     3,    -1,
     116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     3,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     3,    -1,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     3,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     3,    -1,
     116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     3,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     3,    -1,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     3,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     3,    -1,
     116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     3,
      -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,
      22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,   116,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     3,    -1,   116,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     3,    -1,   116,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,    26,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,   116,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
     116,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    -1,    17,    18,    19,    -1,    -1,
      22,    23,    -1,    25,    -1,    27,    28,    29,    -1,    -1,
      32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    61,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    84,    85,    86,    -1,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    26,    27,    28,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    19,
      -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    87,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,    18,
      19,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    64,    -1,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,     3,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,    17,
      18,    19,    -1,    -1,    22,    23,    24,    25,    -1,    27,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,     3,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    19,    -1,    -1,    22,    23,    -1,    25,    -1,
      27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      -1,    17,    18,    19,    -1,    -1,    22,    23,    -1,    25,
      -1,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    87,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,     3,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    19,    -1,    -1,    22,    23,    -1,
      25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,    13,
      14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,
      -1,    25,    -1,    27,    28,    -1,    -1,    -1,    32,    -1,
      -1,    -1,     4,     5,     6,     7,     8,     9,    10,    11,
      -1,    -1,    -1,    47,    48,    17,    -1,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    26,    27,    60,    61,    -1,    -1,
      -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,    93,
      -1,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
       3,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,    12,
      13,    14,    15,    -1,    17,    18,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    -1,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    13,    14,    15,    -1,    17,    18,    31,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    49,    -1,    -1,
      -1,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    86,    -1,    88,    89,    90,    91,
      92,    93,    -1,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,     3,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    12,    13,    14,    15,    -1,    17,    18,    -1,    -1,
      -1,    22,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,     3,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,     3,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    13,    14,    15,    33,    17,    18,
      -1,    -1,    -1,    22,    -1,    -1,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    66,    67,    68,
      69,    -1,    -1,    -1,    -1,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    32,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    12,    13,    14,
      15,    -1,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    32,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    12,    13,    14,    15,    -1,
      17,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,     3,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    13,    14,    15,
      33,    17,    18,    -1,    -1,    -1,    22,    -1,    -1,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    -1,    65,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    12,    13,    14,    15,    -1,    17,
      18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    88,    89,    90,    91,    92,    93,    -1,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,    -1,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    64,    -1,    66,    67,
      68,    69,    12,    13,    14,    15,    -1,    17,    18,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    89,    90,    91,    92,    93,    -1,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,
      90,    91,    92,    93,    -1,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      35,    -1,    -1,    -1,    -1,    65,    -1,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    35,    -1,    -1,    -1,    -1,
      65,    -1,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    39,    -1,    65,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    -1,    65,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const unsigned short yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    10,    11,    17,
      22,    29,    30,    31,    41,    82,    83,    84,    85,    86,
      87,    89,   114,   119,   121,   144,   145,   146,   147,   165,
     168,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     186,   189,   192,   193,   197,   198,   199,   200,   202,   204,
     208,   210,   211,   217,   225,   239,   240,     9,    11,    22,
      83,    84,    85,    86,   121,   198,   208,    30,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    78,
      79,    80,    81,   148,   149,   150,   151,   152,   154,   155,
     156,    83,    84,   119,   169,   171,   199,   200,   208,   217,
     226,   227,     3,    12,    13,    14,    15,    17,    18,    22,
      66,    67,    68,    69,    88,    89,    90,    91,    92,    93,
      95,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   141,   258,   270,
     141,   141,   228,     3,     6,    10,    12,    13,    23,   245,
     247,   121,   240,    44,   278,   279,    22,    82,    87,   121,
     197,     0,   146,    49,   141,   174,   209,   234,   235,   236,
     237,   175,     4,     5,     6,     9,    22,   182,     6,   179,
     185,   198,   123,   187,    32,    32,    36,    36,   141,   141,
     141,    34,   190,    30,     0,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      80,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   117,   119,   120,   121,   122,   123,
     141,   142,   157,     3,    12,    13,    14,    15,    17,    18,
      22,    66,    67,    68,    69,    88,    89,    90,    91,    92,
      93,    95,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   142,   160,
     161,   160,    26,   117,   153,   142,    25,    27,    28,    32,
      47,    48,    60,    61,    77,   140,   141,   162,   222,   141,
     228,   141,   228,   171,    31,   141,    35,   231,   231,   231,
     231,    40,    23,    36,    23,   169,   121,   187,    29,    86,
     238,    38,   232,    32,   141,   122,   237,     6,   183,     6,
       9,   184,   182,    36,   194,    32,    31,    17,   173,   201,
     203,   205,   206,   207,   208,   205,   141,   218,   219,    90,
      91,    92,    93,    94,    96,    97,   249,   250,   251,   264,
     267,   273,   274,   275,   191,   209,   235,   187,    26,   116,
     162,   188,   160,   142,    26,    27,    32,    44,   224,   162,
      32,   141,   162,    32,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    65,   139,    35,    36,   213,   213,    31,   212,
     213,   212,    19,    20,    21,    23,    25,    27,    32,   140,
     166,   167,   188,   209,   220,   221,   222,    40,   249,    32,
      31,    31,    19,    29,    86,   122,   220,   233,   234,   235,
     232,     6,     0,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      31,    32,    33,    34,    35,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    80,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     117,   119,   120,   121,   122,   123,   143,   194,   195,   196,
     188,   234,    32,    33,    34,    34,    33,    34,    40,    34,
     229,   209,   254,   220,   243,   268,   269,   270,   278,   209,
     141,   276,   277,   209,   265,   269,    37,   250,   220,    34,
      31,    32,    26,   175,   223,   224,    22,    33,   141,   117,
     162,   163,   164,   162,   162,    32,   119,   170,   171,   172,
     173,   214,   217,   226,   227,   209,   209,    17,    22,   173,
     220,   220,    31,    65,   139,   166,    37,    14,    15,    16,
      17,    33,   241,   242,   244,   246,   247,   248,    39,    39,
      32,   141,    37,   196,    33,    32,   232,   205,   232,    64,
     207,   232,    64,   220,   219,    37,    40,    31,    40,    31,
      32,    24,    40,    32,    31,    34,    32,    31,    31,   209,
      64,   141,   158,   159,   234,    33,    33,    33,    34,    35,
      25,   172,    35,   230,    37,   170,   231,   231,    33,    33,
     220,   220,    31,    35,    33,    34,   243,   234,    32,    33,
     234,    33,    34,    33,    33,    19,    87,    88,   107,   220,
     253,   255,   256,   257,   258,   279,   268,   209,   278,   191,
     277,    17,   191,   266,    33,    34,   162,   162,    34,    25,
      35,    34,   215,   230,   213,   213,   220,    35,   244,    35,
     242,   244,    40,   141,   205,    33,   232,    64,   232,   232,
     107,   255,    17,    18,    32,   258,   261,    32,    32,   253,
      34,   271,   209,    33,    33,   160,    64,   141,    25,    35,
      32,   209,   216,   230,    31,   215,   220,   244,   278,   166,
      33,    33,    33,   266,    32,   220,   243,    64,   268,   272,
      33,    31,    95,    33,    35,    25,   230,    34,    31,    64,
      32,    33,   232,    33,   243,    34,    34,   259,    33,    34,
      18,   269,   270,    32,    34,   209,   230,    24,   205,    32,
      95,    32,   220,   209,   252,   253,   254,   260,   279,    33,
     268,    25,    25,   230,    33,    33,   205,   261,   262,   263,
     268,    33,    34,   253,    34,    33,    35,    33,    33,    32,
      33,    34,   252,    25,   244,    32,   232,   243,    33,   268,
      33,   205,    32,    33,   262,   232,    33,    33
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned short yyr1[] =
{
       0,   138,   139,   139,   139,   139,   139,   139,   139,   139,
     139,   139,   139,   139,   139,   139,   139,   139,   139,   139,
     140,   140,   140,   140,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   141,   141,   141,   141,   141,   141,
     141,   141,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   142,   142,   142,   142,   142,   142,   142,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   144,   144,   145,   145,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   147,   147,   148,   148,   148,   148,   148,   148,   148,
     149,   149,   150,   151,   151,   152,   152,   152,   153,   153,
     154,   154,   155,   155,   155,   156,   156,   157,   157,   157,
     157,   158,   158,   158,   158,   159,   159,   160,   160,   161,
     161,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   163,   163,   164,   164,   164,   165,   165,   166,
     166,   166,   167,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   171,   171,   171,   171,   172,   172,   172,   172,
     172,   173,   173,   173,   174,   174,   175,   175,   176,   176,
     176,   177,   177,   177,   177,   178,   178,   178,   179,   179,
     180,   180,   180,   181,   181,   181,   181,   182,   182,   182,
     182,   182,   182,   183,   183,   184,   184,   184,   184,   185,
     185,   185,   186,   186,   187,   187,   188,   188,   189,   190,
     190,   191,   191,   192,   193,   193,   193,   193,   193,   193,
     194,   195,   195,   196,   196,   197,   197,   198,   198,   199,
     199,   200,   200,   200,   200,   201,   201,   202,   203,   204,
     205,   205,   205,   206,   206,   207,   207,   207,   208,   208,
     209,   209,   210,   211,   212,   212,   213,   214,   214,   215,
     215,   216,   216,   216,   216,   217,   218,   218,   219,   219,
     220,   220,   220,   220,   220,   220,   221,   221,   221,   221,
     221,   221,   222,   222,   223,   223,   224,   224,   224,   225,
     226,   227,   228,   228,   229,   229,   230,   230,   230,   230,
     231,   231,   232,   232,   232,   233,   233,   233,   233,   234,
     234,   235,   235,   236,   236,   237,   237,   238,   238,   239,
     239,   240,   240,   240,   241,   241,   242,   242,   243,   244,
     245,   246,   246,   247,   247,   247,   247,   247,   248,   248,
     248,   248,   249,   249,   250,   250,   250,   250,   250,   251,
     251,   252,   252,   252,   253,   253,   253,   253,   253,   253,
     254,   254,   255,   256,   256,   257,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   259,   259,   260,   260,
     261,   261,   262,   262,   263,   263,   264,   265,   265,   266,
     266,   266,   267,   268,   268,   268,   269,   269,   270,   270,
     270,   270,   270,   270,   270,   270,   271,   271,   272,   272,
     273,   274,   274,   275,   276,   276,   277,   278,   278,   279
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
       1,     1,     1,     1,     0,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     2,     2,     1,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     6,     2,
       2,     0,     1,     1,     3,     1,     3,     0,     1,     1,
       2,     3,     2,     3,     5,     2,     4,     1,     1,     1,
       1,     4,     0,     1,     1,     1,     3,     6,     5,     1,
       1,     1,     1,     1,     1,     3,     4,     1,     2,     1,
       2,     1,     1,     2,     4,     4,     1,     1,     1,     3,
       3,     1,     2,     2,     1,     1,     1,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     2,     1,     1,     2,     2,     0,     1,     1,
       2,     1,     2,     0,     1,     0,     1,     1,     2,     0,
       1,     2,     3,     4,     0,     4,     1,     2,     5,     0,
       2,     1,     3,     3,     1,     2,     2,     3,     1,     2,
       3,     1,     2,     1,     1,     1,     2,     1,     1,     5,
       7,     5,     7,    13,    16,     5,     7,     6,     5,     1,
       0,     1,     1,     1,     3,     1,     1,     3,     1,     2,
       3,     2,     4,     4,     1,     1,     3,     4,     5,     0,
       2,     2,     4,     1,     3,     5,     1,     3,     1,     3,
       1,     4,     3,     3,     2,     5,     1,     1,     1,     1,
       1,     1,     4,     2,     1,     2,     2,     1,     1,     2,
       2,     2,     0,     1,     0,     1,     0,     2,     7,     9,
       0,     7,     0,     3,     3,     0,     1,     1,     1,     0,
       1,     1,     2,     1,     2,     1,     2,     1,     1,     4,
       5,     7,     8,    13,     1,     3,     2,     4,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     1,     3,
       6,     1,     2,     1,     1,     1,     1,     2,     1,     1,
       3,     4,     6,     8,    12,     5,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     3,
       1,     1,     0,     1,     1,     3,     3,     6,     1,     0,
       1,     1,     3,     1,     1,     3,     5,     6,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     3,
       3,     1,     1,     3,     1,     3,     4,     0,     1,     1
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
       0,     0,     0,     0,     0,     0,     0,     1,     2,     2,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     2,
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     2,     1,     0,     0,     0,     2,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     1,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
static const unsigned short yyconflp[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  3380,     0,     0,  3382,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3362,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3366,
    3368,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3364,     0,    17,     0,
       0,     0,     0,     0,     9,     0,     0,     0,    11,     0,
       0,     0,     0,  3372,     0,  3374,  3376,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  3384,     0,  3386,
    3388,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   163,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  3378,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3390,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
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
       0,     0,     3,     0,     0,     0,     0,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    23,    25,
      27,     0,    29,    31,     0,     0,     0,    33,     0,     0,
       0,     0,     0,     0,    35,    37,    39,    41,    43,    45,
      47,    49,    51,    53,    55,    57,     0,    59,    61,    63,
      65,    67,    69,    71,    73,    75,    77,    79,    81,    83,
      85,    87,    89,    91,    93,     0,     0,     0,     0,     0,
      95,    97,    99,   101,   103,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,     0,   107,   109,   111,   113,   115,   117,     0,
     119,     0,     0,   121,   123,   125,   127,   129,   131,   133,
     135,   137,   139,   141,   143,   145,   147,   149,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   165,     0,     0,     0,     0,     0,     0,     0,
       0,   167,   169,   171,   173,     0,   175,   177,     0,     0,
       0,   179,     0,     0,   181,   183,   185,   187,     0,     0,
       0,   189,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   191,   193,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   195,
     197,     0,     0,     0,     0,   199,   201,   203,   205,     0,
       0,     0,     0,     0,     0,     0,   207,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   209,   211,   213,
     215,   217,   219,     0,   221,     0,     0,   223,   225,   227,
     229,   231,   233,   235,   237,   239,   241,   243,   245,   247,
     249,   251,   253,   255,     0,     0,     0,     0,     0,     0,
       0,     0,   257,   259,   261,   263,     0,   265,   267,     0,
       0,     0,   269,     0,     0,   271,   273,   275,   277,     0,
       0,     0,   279,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   281,   283,     0,
       0,   155,     0,     0,     0,     0,   157,     0,     0,     0,
     285,   287,     0,   159,     0,     0,   289,   291,   293,   295,
       0,     0,     0,     0,     0,     0,     0,   297,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   299,   301,
     303,   305,   307,   309,     0,   311,     0,     0,   313,   315,
     317,   319,   321,   323,   325,   327,   329,   331,   333,   335,
     337,   339,   341,   343,   345,     0,     0,     0,     0,     0,
     161,     0,     0,   347,   349,   351,   353,     0,   355,   357,
       0,     0,     0,   359,     0,     0,   361,   363,   365,   367,
       0,     0,     0,   369,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   371,   373,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   375,   377,     0,     0,     0,     0,   379,   381,   383,
     385,     0,     0,     0,     0,     0,     0,     0,   387,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   389,
     391,   393,   395,   397,   399,     0,   401,     0,     0,   403,
     405,   407,   409,   411,   413,   415,   417,   419,   421,   423,
     425,   427,   429,   431,   433,   435,     0,     0,     0,     0,
       0,     0,     0,     0,   437,   439,   441,   443,     0,   445,
     447,     0,     0,     0,   449,     0,     0,   451,   453,   455,
     457,     0,     0,     0,   459,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   461,
     463,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   465,   467,     0,     0,     0,     0,   469,   471,
     473,   475,     0,     0,     0,     0,     0,     0,     0,   477,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     479,   481,   483,   485,   487,   489,     0,   491,     0,     0,
     493,   495,   497,   499,   501,   503,   505,   507,   509,   511,
     513,   515,   517,   519,   521,   523,   525,     0,     0,     0,
       0,     0,     0,     0,     0,   527,   529,   531,   533,     0,
     535,   537,     0,     0,     0,   539,     0,     0,   541,   543,
     545,   547,     0,     0,     0,   549,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     551,   553,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   555,   557,     0,     0,     0,     0,   559,
     561,   563,   565,     0,     0,     0,     0,     0,     0,     0,
     567,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   569,   571,   573,   575,   577,   579,     0,   581,     0,
       0,   583,   585,   587,   589,   591,   593,   595,   597,   599,
     601,   603,   605,   607,   609,   611,   613,   615,     0,     0,
       0,     0,     0,     0,     0,     0,   617,   619,   621,   623,
       0,   625,   627,     0,     0,     0,   629,     0,     0,   631,
     633,   635,   637,     0,     0,     0,   639,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   641,   643,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   645,   647,     0,     0,     0,     0,
     649,   651,   653,   655,     0,     0,     0,     0,     0,     0,
       0,   657,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   659,   661,   663,   665,   667,   669,     0,   671,
       0,     0,   673,   675,   677,   679,   681,   683,   685,   687,
     689,   691,   693,   695,   697,   699,   701,   703,   705,     0,
       0,     0,     0,     0,     0,     0,     0,   708,   711,   714,
     717,     0,   720,   723,     0,     0,     0,   726,     0,     0,
     729,   732,   735,   738,     0,     0,     0,   741,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   744,   747,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   750,   753,     0,     0,     0,
       0,   756,   759,   762,   765,     0,     0,     0,     0,     0,
       0,     0,   768,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   771,   774,   777,   780,   783,   786,     0,
     789,     0,     0,   792,   795,   798,   801,   804,   807,   810,
     813,   816,   819,   822,   825,   828,   831,   834,   837,   842,
       0,   840,     0,     0,     0,     0,     0,     0,   844,   846,
     848,   850,     0,   852,   854,     0,     0,     0,   856,     0,
       0,   858,   860,   862,   864,     0,     0,     0,   866,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   868,   870,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   872,   874,     0,     0,
       0,     0,   876,   878,   880,   882,     0,     0,     0,     0,
       0,     0,     0,   884,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   886,   888,   890,   892,   894,   896,
       0,   898,     0,     0,   900,   902,   904,   906,   908,   910,
     912,   914,   916,   918,   920,   922,   924,   926,   928,   930,
     932,     0,     0,     0,     0,     0,     0,     0,     0,   934,
     936,   938,   940,     0,   942,   944,     0,     0,     0,   946,
       0,     0,   948,   950,   952,   954,     0,     0,     0,   956,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   958,   960,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   962,   964,     0,
       0,     0,     0,   966,   968,   970,   972,     0,     0,     0,
       0,     0,     0,     0,   974,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   976,   978,   980,   982,   984,
     986,     0,   988,     0,     0,   990,   992,   994,   996,   998,
    1000,  1002,  1004,  1006,  1008,  1010,  1012,  1014,  1016,  1018,
    1020,  1022,     0,     0,     0,     0,     0,     0,     0,     0,
    1024,  1026,  1028,  1030,     0,  1032,  1034,     0,     0,     0,
    1036,     0,     0,  1038,  1040,  1042,  1044,     0,     0,     0,
    1046,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1048,  1050,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1052,  1054,
       0,     0,     0,     0,  1056,  1058,  1060,  1062,     0,     0,
       0,     0,     0,     0,     0,  1064,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1066,  1068,  1070,  1072,
    1074,  1076,     0,  1078,     0,     0,  1080,  1082,  1084,  1086,
    1088,  1090,  1092,  1094,  1096,  1098,  1100,  1102,  1104,  1106,
    1108,  1110,  1112,     0,     0,     0,     0,     0,     0,     0,
       0,  1114,  1116,  1118,  1120,     0,  1122,  1124,     0,     0,
       0,  1126,     0,     0,  1128,  1130,  1132,  1134,     0,     0,
       0,  1136,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1138,  1140,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1142,
    1144,     0,     0,     0,     0,  1146,  1148,  1150,  1152,     0,
       0,     0,     0,     0,     0,     0,  1154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1156,  1158,  1160,
    1162,  1164,  1166,     0,  1168,     0,     0,  1170,  1172,  1174,
    1176,  1178,  1180,  1182,  1184,  1186,  1188,  1190,  1192,  1194,
    1196,  1198,  1200,  1202,     0,     0,     0,     0,     0,     0,
       0,     0,  1204,  1206,  1208,  1210,     0,  1212,  1214,     0,
       0,     0,  1216,     0,     0,  1218,  1220,  1222,  1224,     0,
       0,     0,  1226,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1228,  1230,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1232,  1234,     0,     0,     0,     0,  1236,  1238,  1240,  1242,
       0,     0,     0,     0,     0,     0,     0,  1244,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1246,  1248,
    1250,  1252,  1254,  1256,     0,  1258,     0,     0,  1260,  1262,
    1264,  1266,  1268,  1270,  1272,  1274,  1276,  1278,  1280,  1282,
    1284,  1286,  1288,  1290,  1292,     0,     0,     0,     0,     0,
       0,     0,     0,  1294,  1296,  1298,  1300,     0,  1302,  1304,
       0,     0,     0,  1306,     0,     0,  1308,  1310,  1312,  1314,
       0,     0,     0,  1316,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1318,  1320,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1322,  1324,     0,     0,     0,     0,  1326,  1328,  1330,
    1332,     0,     0,     0,     0,     0,     0,     0,  1334,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1336,
    1338,  1340,  1342,  1344,  1346,     0,  1348,     0,     0,  1350,
    1352,  1354,  1356,  1358,  1360,  1362,  1364,  1366,  1368,  1370,
    1372,  1374,  1376,  1378,  1380,  1382,     0,     0,     0,     0,
       0,     0,     0,     0,  1384,  1386,  1388,  1390,     0,  1392,
    1394,     0,     0,     0,  1396,     0,     0,  1398,  1400,  1402,
    1404,     0,     0,     0,  1406,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1408,
    1410,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1412,  1414,     0,     0,     0,     0,  1416,  1418,
    1420,  1422,     0,     0,     0,     0,     0,     0,     0,  1424,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1426,  1428,  1430,  1432,  1434,  1436,     0,  1438,     0,     0,
    1440,  1442,  1444,  1446,  1448,  1450,  1452,  1454,  1456,  1458,
    1460,  1462,  1464,  1466,  1468,  1470,  1472,     0,     0,     0,
       0,     0,     0,     0,     0,  1474,  1476,  1478,  1480,     0,
    1482,  1484,     0,     0,     0,  1486,     0,     0,  1488,  1490,
    1492,  1494,     0,     0,     0,  1496,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1498,  1500,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1502,  1504,     0,     0,     0,     0,  1506,
    1508,  1510,  1512,     0,     0,     0,     0,     0,     0,     0,
    1514,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1516,  1518,  1520,  1522,  1524,  1526,     0,  1528,     0,
       0,  1530,  1532,  1534,  1536,  1538,  1540,  1542,  1544,  1546,
    1548,  1550,  1552,  1554,  1556,  1558,  1560,  1562,     0,     0,
       0,     0,     0,     0,     0,     0,  1564,  1566,  1568,  1570,
       0,  1572,  1574,     0,     0,     0,  1576,     0,     0,  1578,
    1580,  1582,  1584,     0,     0,     0,  1586,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1588,  1590,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1592,  1594,     0,     0,     0,     0,
    1596,  1598,  1600,  1602,     0,     0,     0,     0,     0,     0,
       0,  1604,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1606,  1608,  1610,  1612,  1614,  1616,     0,  1618,
       0,     0,  1620,  1622,  1624,  1626,  1628,  1630,  1632,  1634,
    1636,  1638,  1640,  1642,  1644,  1646,  1648,  1650,  1652,     0,
       0,     0,     0,     0,     0,     0,     0,  1654,  1656,  1658,
    1660,     0,  1662,  1664,     0,     0,     0,  1666,     0,     0,
    1668,  1670,  1672,  1674,     0,     0,     0,  1676,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1678,  1680,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1682,  1684,     0,     0,     0,
       0,  1686,  1688,  1690,  1692,     0,     0,     0,     0,     0,
       0,     0,  1694,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1696,  1698,  1700,  1702,  1704,  1706,     0,
    1708,     0,     0,  1710,  1712,  1714,  1716,  1718,  1720,  1722,
    1724,  1726,  1728,  1730,  1732,  1734,  1736,  1738,  1740,  1742,
       0,     0,     0,     0,     0,     0,     0,     0,  1744,  1746,
    1748,  1750,     0,  1752,  1754,     0,     0,     0,  1756,     0,
       0,  1758,  1760,  1762,  1764,     0,     0,     0,  1766,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1768,  1770,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1772,  1774,     0,     0,
       0,     0,  1776,  1778,  1780,  1782,     0,     0,     0,     0,
       0,     0,     0,  1784,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1786,  1788,  1790,  1792,  1794,  1796,
       0,  1798,     0,     0,  1800,  1802,  1804,  1806,  1808,  1810,
    1812,  1814,  1816,  1818,  1820,  1822,  1824,  1826,  1828,  1830,
    1832,     0,     0,     0,     0,     0,     0,     0,     0,  1834,
    1836,  1838,  1840,     0,  1842,  1844,     0,     0,     0,  1846,
       0,     0,  1848,  1850,  1852,  1854,     0,     0,     0,  1856,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1858,  1860,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1862,  1864,     0,
       0,     0,     0,  1866,  1868,  1870,  1872,     0,     0,     0,
       0,     0,     0,     0,  1874,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1876,  1878,  1880,  1882,  1884,
    1886,     0,  1888,     0,     0,  1890,  1892,  1894,  1896,  1898,
    1900,  1902,  1904,  1906,  1908,  1910,  1912,  1914,  1916,  1918,
    1920,  1922,     0,     0,     0,     0,     0,     0,     0,     0,
    1924,  1926,  1928,  1930,     0,  1932,  1934,     0,     0,     0,
    1936,     0,     0,  1938,  1940,  1942,  1944,     0,     0,     0,
    1946,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1948,  1950,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1952,  1954,
       0,     0,     0,     0,  1956,  1958,  1960,  1962,     0,     0,
       0,     0,     0,     0,     0,  1964,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1966,  1968,  1970,  1972,
    1974,  1976,     0,  1978,     0,     0,  1980,  1982,  1984,  1986,
    1988,  1990,  1992,  1994,  1996,  1998,  2000,  2002,  2004,  2006,
    2008,  2010,  2012,     0,     0,     0,     0,     0,     0,     0,
       0,  2014,  2016,  2018,  2020,     0,  2022,  2024,     0,     0,
       0,  2026,     0,     0,  2028,  2030,  2032,  2034,     0,     0,
       0,  2036,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2038,  2040,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2042,
    2044,     0,     0,     0,     0,  2046,  2048,  2050,  2052,     0,
       0,     0,     0,     0,     0,     0,  2054,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2056,  2058,  2060,
    2062,  2064,  2066,     0,  2068,     0,     0,  2070,  2072,  2074,
    2076,  2078,  2080,  2082,  2084,  2086,  2088,  2090,  2092,  2094,
    2096,  2098,  2100,  2102,     0,     0,     0,     0,     0,     0,
       0,     0,  2104,  2106,  2108,  2110,     0,  2112,  2114,     0,
       0,     0,  2116,     0,     0,  2118,  2120,  2122,  2124,     0,
       0,     0,  2126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2128,  2130,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2132,  2134,     0,     0,     0,     0,  2136,  2138,  2140,  2142,
       0,     0,     0,     0,     0,     0,     0,  2144,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2146,  2148,
    2150,  2152,  2154,  2156,     0,  2158,     0,     0,  2160,  2162,
    2164,  2166,  2168,  2170,  2172,  2174,  2176,  2178,  2180,  2182,
    2184,  2186,  2188,  2190,  2192,     0,     0,     0,     0,     0,
       0,     0,     0,  2194,  2196,  2198,  2200,     0,  2202,  2204,
       0,     0,     0,  2206,     0,     0,  2208,  2210,  2212,  2214,
       0,     0,     0,  2216,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2218,  2220,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2222,  2224,     0,     0,     0,     0,  2226,  2228,  2230,
    2232,     0,     0,     0,     0,     0,     0,     0,  2234,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2236,
    2238,  2240,  2242,  2244,  2246,     0,  2248,     0,     0,  2250,
    2252,  2254,  2256,  2258,  2260,  2262,  2264,  2266,  2268,  2270,
    2272,  2274,  2276,  2278,  2280,  2282,     0,     0,     0,     0,
       0,     0,     0,     0,  2284,  2286,  2288,  2290,     0,  2292,
    2294,     0,     0,     0,  2296,     0,     0,  2298,  2300,  2302,
    2304,     0,     0,     0,  2306,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2308,
    2310,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2312,  2314,     0,     0,     0,     0,  2316,  2318,
    2320,  2322,     0,     0,     0,     0,     0,     0,     0,  2324,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2326,  2328,  2330,  2332,  2334,  2336,     0,  2338,     0,     0,
    2340,  2342,  2344,  2346,  2348,  2350,  2352,  2354,  2356,  2358,
    2360,  2362,  2364,  2366,  2368,  2370,  2372,     0,     0,     0,
       0,     0,     0,     0,     0,  2374,  2376,  2378,  2380,     0,
    2382,  2384,     0,     0,     0,  2386,     0,     0,  2388,  2390,
    2392,  2394,     0,     0,     0,  2396,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    2398,  2400,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2402,  2404,     0,     0,     0,     0,  2406,
    2408,  2410,  2412,     0,     0,     0,     0,     0,     0,     0,
    2414,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2416,  2418,  2420,  2422,  2424,  2426,     0,  2428,     0,
       0,  2430,  2432,  2434,  2436,  2438,  2440,  2442,  2444,  2446,
    2448,  2450,  2452,  2454,  2456,  2458,  2460,  2462,     0,     0,
       0,     0,     0,     0,     0,     0,  2464,  2466,  2468,  2470,
       0,  2472,  2474,     0,     0,     0,  2476,     0,     0,  2478,
    2480,  2482,  2484,     0,     0,     0,  2486,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  2488,  2490,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2492,  2494,     0,     0,     0,     0,
    2496,  2498,  2500,  2502,     0,     0,     0,     0,     0,     0,
       0,  2504,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2506,  2508,  2510,  2512,  2514,  2516,     0,  2518,
       0,     0,  2520,  2522,  2524,  2526,  2528,  2530,  2532,  2534,
    2536,  2538,  2540,  2542,  2544,  2546,  2548,  2550,  2552,     0,
       0,     0,     0,     0,     0,     0,     0,  2554,  2556,  2558,
    2560,     0,  2562,  2564,     0,     0,     0,  2566,     0,     0,
    2568,  2570,  2572,  2574,     0,     0,     0,  2576,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  2578,  2580,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2582,  2584,     0,     0,     0,
       0,  2586,  2588,  2590,  2592,     0,     0,     0,     0,     0,
       0,     0,  2594,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2596,  2598,  2600,  2602,  2604,  2606,     0,
    2608,     0,     0,  2610,  2612,  2614,  2616,  2618,  2620,  2622,
    2624,  2626,  2628,  2630,  2632,  2634,  2636,  2638,  2640,  2642,
       0,     0,     0,     0,     0,     0,     0,     0,  2644,  2646,
    2648,  2650,     0,  2652,  2654,     0,     0,     0,  2656,     0,
       0,  2658,  2660,  2662,  2664,     0,     0,     0,  2666,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  2668,  2670,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2672,  2674,     0,     0,
       0,     0,  2676,  2678,  2680,  2682,     0,     0,     0,     0,
       0,     0,     0,  2684,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2686,  2688,  2690,  2692,  2694,  2696,
       0,  2698,     0,     0,  2700,  2702,  2704,  2706,  2708,  2710,
    2712,  2714,  2716,  2718,  2720,  2722,  2724,  2726,  2728,  2730,
    2732,     0,     0,     0,     0,     0,     0,     0,     0,  2734,
    2736,  2738,  2740,     0,  2742,  2744,     0,     0,     0,  2746,
       0,     0,  2748,  2750,  2752,  2754,     0,     0,     0,  2756,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  2758,  2760,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2762,  2764,     0,
       0,     0,     0,  2766,  2768,  2770,  2772,     0,     0,     0,
       0,     0,     0,     0,  2774,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2776,  2778,  2780,  2782,  2784,
    2786,     0,  2788,     0,     0,  2790,  2792,  2794,  2796,  2798,
    2800,  2802,  2804,  2806,  2808,  2810,  2812,  2814,  2816,  2818,
    2820,  2822,     0,     0,     0,     0,     0,     0,     0,     0,
    2824,  2826,  2828,  2830,     0,  2832,  2834,     0,     0,     0,
    2836,     0,     0,  2838,  2840,  2842,  2844,     0,     0,     0,
    2846,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  2848,  2850,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  2852,  2854,
       0,     0,     0,     0,  2856,  2858,  2860,  2862,     0,     0,
       0,     0,     0,     0,     0,  2864,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2866,  2868,  2870,  2872,
    2874,  2876,     0,  2878,     0,     0,  2880,  2882,  2884,  2886,
    2888,  2890,  2892,  2894,  2896,  2898,  2900,  2902,  2904,  2906,
    2908,  2910,  2912,     0,     0,     0,     0,     0,     0,     0,
       0,  2914,  2916,  2918,  2920,     0,  2922,  2924,     0,     0,
       0,  2926,     0,     0,  2928,  2930,  2932,  2934,     0,     0,
       0,  2936,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  2938,  2940,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  2942,
    2944,     0,     0,     0,     0,  2946,  2948,  2950,  2952,     0,
       0,     0,     0,     0,     0,     0,  2954,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  2956,  2958,  2960,
    2962,  2964,  2966,     0,  2968,     0,     0,  2970,  2972,  2974,
    2976,  2978,  2980,  2982,  2984,  2986,  2988,  2990,  2992,  2994,
    2996,  2998,  3000,  3002,     0,     0,     0,     0,     0,     0,
       0,     0,  3004,  3006,  3008,  3010,     0,  3012,  3014,     0,
       0,     0,  3016,     0,     0,  3018,  3020,  3022,  3024,     0,
       0,     0,  3026,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  3028,  3030,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3032,  3034,     0,     0,     0,     0,  3036,  3038,  3040,  3042,
       0,     0,     0,     0,     0,     0,     0,  3044,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  3046,  3048,
    3050,  3052,  3054,  3056,     0,  3058,     0,     0,  3060,  3062,
    3064,  3066,  3068,  3070,  3072,  3074,  3076,  3078,  3080,  3082,
    3084,  3086,  3088,  3090,  3092,     0,     0,     0,     0,     0,
       0,     0,     0,  3094,  3096,  3098,  3100,     0,  3102,  3104,
       0,     0,     0,  3106,     0,     0,  3108,  3110,  3112,  3114,
       0,     0,     0,  3116,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  3118,  3120,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3122,  3124,     0,     0,     0,     0,  3126,  3128,  3130,
    3132,     0,     0,     0,     0,     0,     0,     0,  3134,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3136,
    3138,  3140,  3142,  3144,  3146,     0,  3148,     0,     0,  3150,
    3152,  3154,  3156,  3158,  3160,  3162,  3164,  3166,  3168,  3170,
    3172,  3174,  3176,  3178,  3180,  3182,     0,     0,     0,     0,
       0,     0,     0,     0,  3184,  3186,  3188,  3190,     0,  3192,
    3194,     0,     0,     0,  3196,     0,     0,  3198,  3200,  3202,
    3204,     0,     0,     0,  3206,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  3208,
    3210,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  3212,  3214,     0,     0,     0,     0,  3216,  3218,
    3220,  3222,     0,     0,     0,     0,     0,     0,     0,  3224,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3226,  3228,  3230,  3232,  3234,  3236,     0,  3238,     0,     0,
    3240,  3242,  3244,  3246,  3248,  3250,  3252,  3254,  3256,  3258,
    3260,  3262,  3264,  3266,  3268,  3270,  3272,     0,     0,     0,
       0,     0,     0,     0,     0,  3274,  3276,  3278,  3280,     0,
    3282,  3284,     0,     0,     0,  3286,     0,     0,  3288,  3290,
    3292,  3294,     0,     0,     0,  3296,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    3298,  3300,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  3302,  3304,     0,     0,     0,     0,  3306,
    3308,  3310,  3312,     0,     0,     0,     0,     0,     0,     0,
    3314,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3316,  3318,  3320,  3322,  3324,  3326,     0,  3328,     0,
       0,  3330,  3332,  3334,  3336,  3338,  3340,  3342,  3344,  3346,
    3348,  3350,  3352,  3354,  3356,  3358,  3360,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  3392,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  3394
};

/* YYCONFL[I] -- lists of conflicting rule numbers, each terminated by
   0, pointed into by YYCONFLP.  */
static const short yyconfl[] =
{
       0,   383,     0,   383,     0,   383,     0,   383,     0,   374,
       0,   374,     0,   397,     0,   458,     0,   458,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   614,     0,   614,     0,   614,
       0,   614,     0,   614,     0,   383,     0,   383,     0,   383,
       0,   383,     0,   397,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    44,     0,    44,     0,    44,
       0,    44,     0,    44,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    53,     0,    53,     0,    53,
       0,    53,     0,    53,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    54,     0,    54,     0,    54,
       0,    54,     0,    54,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    55,     0,    55,     0,    55,
       0,    55,     0,    55,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,    56,     0,    56,     0,    56,
       0,    56,     0,    56,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   615,     0,   615,     0,   615,
       0,   615,     0,   615,     0,   576,   614,     0,   576,   614,
       0,   576,   614,     0,   576,   614,     0,   576,   614,     0,
     576,   614,     0,   576,   614,     0,   576,   614,     0,   576,
     614,     0,   576,   614,     0,   576,   614,     0,   576,   614,
       0,   576,   614,     0,   576,   614,     0,   576,   614,     0,
     576,   614,     0,   576,   614,     0,   576,   614,     0,   576,
     614,     0,   576,   614,     0,   576,   614,     0,   576,   614,
       0,   576,   614,     0,   576,   614,     0,   576,   614,     0,
     576,   614,     0,   576,   614,     0,   576,   614,     0,   576,
     614,     0,   576,   614,     0,   576,   614,     0,   576,   614,
       0,   576,   614,     0,   576,   614,     0,   576,   614,     0,
     576,   614,     0,   576,   614,     0,   576,   614,     0,   576,
     614,     0,   576,   614,     0,   576,   614,     0,   576,   614,
       0,   576,   614,     0,   576,   614,     0,   576,   614,     0,
     614,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,    63,     0,    63,     0,    63,     0,    63,     0,
      63,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   107,     0,   107,     0,   107,     0,   107,     0,
     107,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   106,     0,   106,     0,   106,     0,   106,     0,
     106,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   104,     0,   104,     0,   104,     0,   104,     0,
     104,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   105,     0,   105,     0,   105,     0,   105,     0,
     105,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   125,     0,   125,     0,   125,     0,   125,     0,
     125,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   126,     0,   126,     0,   126,     0,   126,     0,
     126,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   127,     0,   127,     0,   127,     0,   127,     0,
     127,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   128,     0,   128,     0,   128,     0,   128,     0,
     128,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   129,     0,   129,     0,   129,     0,   129,     0,
     129,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   130,     0,   130,     0,   130,     0,   130,     0,
     130,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   159,     0,   159,     0,   159,     0,   159,     0,
     159,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   584,     0,   584,     0,   584,     0,   584,     0,
     584,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   583,     0,   583,     0,   583,     0,   583,     0,
     583,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   581,     0,   581,     0,   581,     0,   581,     0,
     581,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   579,     0,   579,     0,   579,     0,   579,     0,
     579,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   580,     0,   580,     0,   580,     0,   580,     0,
     580,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   582,     0,   582,     0,   582,     0,   582,     0,
     582,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   578,     0,   578,     0,   578,     0,   578,     0,
     578,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   577,     0,   577,     0,   577,     0,   577,     0,
     577,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   585,     0,   585,     0,   585,     0,   585,     0,
     585,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   143,     0,   143,     0,   143,     0,   143,     0,
     143,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   613,     0,   613,     0,   613,     0,   613,     0,
     613,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   611,     0,   611,     0,   611,     0,   611,     0,
     611,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   610,     0,   610,     0,   610,     0,   610,     0,
     610,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   612,     0,   612,     0,   612,     0,   612,     0,
     612,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   609,     0,   609,     0,   609,     0,   609,     0,
     609,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   608,     0,   608,     0,   608,     0,   608,     0,
     608,     0,   503,     0,   503,     0,   451,     0,   451,     0,
     452,     0,   489,     0,   489,     0,   489,     0,    43,     0,
     615,     0,   383,     0,   564,     0,   564,     0,   564,     0,
     615,     0,   334,     0,   485,     0
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
  case 281:
#line 429 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		psi_cpp_exp_exec((*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), P->preproc, PSI_DATA(P));
		psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	}
}
#line 4355 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 282:
#line 435 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_const(P, (*(struct psi_const **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4363 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 283:
#line 438 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_decl(P, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4371 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 284:
#line 441 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_decl_extvars(P, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4379 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 285:
#line 444 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if (P->flags & PSI_DEBUG) {
		P->error(PSI_DATA(P), (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token, PSI_NOTICE, "Ignored decl: %s", (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name->val);
	}
	psi_decl_free(&(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4390 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 286:
#line 450 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_typedef(P, (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4398 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 287:
#line 453 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_struct(P, (*(struct psi_decl_struct **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4406 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 288:
#line 456 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_union(P, (*(struct psi_decl_union **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4414 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 289:
#line 459 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_enum(P, (*(struct psi_decl_enum **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4422 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 290:
#line 462 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_parser_proc_add_impl(P, (*(struct psi_impl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4430 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 291:
#line 468 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4438 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 292:
#line 471 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = (*(struct psi_cpp_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4446 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 293:
#line 477 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 4474 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 294:
#line 500 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4483 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 295:
#line 504 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, NULL);
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4492 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 296:
#line 508 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4502 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 297:
#line 513 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_cpp_macro_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4511 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 298:
#line 517 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = psi_cpp_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4520 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 299:
#line 521 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	psi_plist_free((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_exp **)(&(*yyvalp))) = NULL;
}
#line 4529 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 317:
#line 569 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4539 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 318:
#line 574 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 4549 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 319:
#line 579 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_num_exp_tokens((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4559 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 320:
#line 584 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	struct psi_plist *list = psi_plist_init((psi_plist_dtor) psi_token_free);
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp))) = psi_cpp_macro_decl_init(NULL, psi_plist_add(list, &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_cpp_macro_decl **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4570 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 321:
#line 593 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL);
}
#line 4578 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 322:
#line 596 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_init(NULL); /* FIXME */
}
#line 4586 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 324:
#line 600 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 4594 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 325:
#line 606 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4604 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 326:
#line 611 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4614 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 327:
#line 619 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4622 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 329:
#line 626 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_token_free), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4631 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 330:
#line 630 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4640 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 331:
#line 637 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 4649 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 332:
#line 641 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4658 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 333:
#line 645 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 4667 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 334:
#line 649 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4676 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 335:
#line 654 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 4692 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 336:
#line 665 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 4708 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 337:
#line 676 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4718 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 338:
#line 681 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4728 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 339:
#line 686 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4737 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 340:
#line 690 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4748 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 341:
#line 696 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
		psi_cpp_macro_call_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 0));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->data.n->data.call->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4761 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 342:
#line 707 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 4769 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 344:
#line 714 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	/* TODO: clang include test macros */
	uint8_t no = 1;
	struct psi_num_exp *exp = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &no, 0));
	exp->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	exp->data.n->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free), &exp);
}
#line 4782 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 345:
#line 722 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_num_exp_free),
		&(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4791 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 346:
#line 726 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4799 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 347:
#line 732 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4808 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 348:
#line 736 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_const **)(&(*yyvalp))) = psi_const_init(NULL, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_const **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 4817 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 349:
#line 743 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 4826 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 350:
#line 747 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init(PSI_T_NUMBER, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4835 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 351:
#line 751 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_def_val **)(&(*yyvalp))) = psi_impl_def_val_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_def_val **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4844 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 355:
#line 764 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4852 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 356:
#line 778 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 4860 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 357:
#line 784 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4868 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 358:
#line 787 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4876 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 359:
#line 793 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4884 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 360:
#line 796 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4892 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 362:
#line 803 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 4905 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 363:
#line 811 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 4921 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 364:
#line 822 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 4935 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 365:
#line 831 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 4949 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 367:
#line 844 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 4958 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 368:
#line 848 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 4973 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 369:
#line 858 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_struct(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.strct);
}
#line 4987 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 370:
#line 867 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text), psi_decl_var_init(NULL, 0, 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	psi_parser_proc_add_union(P, (*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.unn);
}
#line 5001 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 372:
#line 880 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5009 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 373:
#line 883 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5017 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 376:
#line 894 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5026 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 378:
#line 902 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5036 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 379:
#line 907 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5046 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 380:
#line 912 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_type **)(&(*yyvalp))) = psi_decl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_decl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5056 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 383:
#line 922 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5064 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 384:
#line 925 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5072 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 385:
#line 931 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5080 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 386:
#line 934 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5088 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 387:
#line 937 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5096 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 390:
#line 948 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5104 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 391:
#line 951 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5112 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 392:
#line 954 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5120 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 393:
#line 960 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5128 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 394:
#line 963 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5136 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 395:
#line 966 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5149 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 396:
#line 974 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	}
}
#line 5163 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 397:
#line 986 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5171 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 398:
#line 989 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5179 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 399:
#line 992 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5187 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 400:
#line 995 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5199 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 401:
#line 1002 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5207 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 402:
#line 1005 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5219 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 403:
#line 1015 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5227 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 405:
#line 1021 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5235 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 409:
#line 1030 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5243 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 410:
#line 1033 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5251 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 411:
#line 1036 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat(" ", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5264 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 412:
#line 1047 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = zend_string_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5276 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 413:
#line 1054 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->redir = zend_string_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
		psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	}
}
#line 5288 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 414:
#line 1064 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 5296 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 415:
#line 1067 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5304 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 416:
#line 1073 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5312 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 417:
#line 1076 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = psi_token_cat("", 2, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	psi_token_free(&(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5321 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 418:
#line 1083 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5359 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 419:
#line 1119 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5367 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 420:
#line 1122 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5375 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 421:
#line 1128 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5383 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 422:
#line 1131 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5391 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 423:
#line 1137 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5399 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 436:
#line 1167 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_decl **)(&(*yyvalp)))->abi = psi_decl_abi_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text);
}
#line 5408 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 439:
#line 1179 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5420 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 440:
#line 1186 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5433 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 441:
#line 1197 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5445 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 442:
#line 1204 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5458 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 443:
#line 1212 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5487 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 444:
#line 1236 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5518 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 445:
#line 1265 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5530 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 446:
#line 1272 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl **)(&(*yyvalp))) = psi_decl_init((*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_decl **)(&(*yyvalp)))->varargs = 1;
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->pointer_level += 1;
		(*(struct psi_decl **)(&(*yyvalp)))->func->var->array_size = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	}
}
#line 5543 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 447:
#line 1283 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5555 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 448:
#line 1329 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(void) (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), 0));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_arg **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5566 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 450:
#line 1385 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5574 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 451:
#line 1388 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5582 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 452:
#line 1391 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5590 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 453:
#line 1397 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5598 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 454:
#line 1400 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5606 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 455:
#line 1406 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5626 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 456:
#line 1421 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = (*(struct psi_decl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5634 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 457:
#line 1424 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)),
		psi_decl_var_init(NULL, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)))
	);
}
#line 5645 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 458:
#line 1453 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init(
		psi_decl_type_init(PSI_T_FUNCTION, (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var->name),
		psi_decl_var_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->var)
	);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->token = psi_token_copy((*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->func->token);
	(*(struct psi_decl_arg **)(&(*yyvalp)))->type->real.func = (*(struct psi_decl **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5658 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 459:
#line 1461 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_arg **)(&(*yyvalp))) = psi_decl_arg_init((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5666 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 460:
#line 1489 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)) + !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5676 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 461:
#line 1494 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_var **)(&(*yyvalp))) = psi_decl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text, !! (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5686 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 462:
#line 1502 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_union **)(&(*yyvalp))) = psi_decl_union_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_union **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_union **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_union **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5698 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 463:
#line 1512 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_struct **)(&(*yyvalp))) = psi_decl_struct_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_struct **)(&(*yyvalp)))->align = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).pos;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->size = (*(struct psi_layout*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)).len;
	(*(struct psi_decl_struct **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5710 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 464:
#line 1522 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5718 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 466:
#line 1529 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 5726 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 467:
#line 1535 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5745 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 468:
#line 1549 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 5764 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 469:
#line 1566 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 5772 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 470:
#line 1569 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5780 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 471:
#line 1575 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 5792 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 472:
#line 1582 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 5804 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 473:
#line 1589 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free), &arg);
	}
}
#line 5817 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 474:
#line 1597 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	{
		struct psi_decl_var *var = psi_decl_var_init(NULL, 0, 0);
		struct psi_decl_arg *arg = psi_decl_arg_init(NULL, var);
		arg->layout = (*(struct psi_layout **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
		(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &arg);
	}
}
#line 5830 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 475:
#line 1608 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_decl_enum **)(&(*yyvalp))) = psi_decl_enum_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum **)(&(*yyvalp)))->token = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval));
}
#line 5839 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 476:
#line 1615 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5847 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 477:
#line 1618 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_decl_enum_item **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5855 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 478:
#line 1624 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, NULL);
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5865 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 479:
#line 1629 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_decl_enum_item **)(&(*yyvalp))) = psi_decl_enum_item_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->text, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_decl_enum_item **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5875 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 480:
#line 1637 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_num((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5884 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 481:
#line 1641 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_cast((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->token);
}
#line 5893 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 482:
#line 1645 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary(PSI_T_LPAREN, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 5902 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 483:
#line 1649 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_binary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5911 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 484:
#line 1653 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_unary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 5920 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 485:
#line 1657 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_num_exp **)(&(*yyvalp))) = psi_num_exp_init_ternary((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_num_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 5929 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 486:
#line 1664 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->flags);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5938 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 487:
#line 1668 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5947 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 488:
#line 1672 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5956 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 489:
#line 1676 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 5965 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 490:
#line 1680 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_NAME, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), 0);
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 5974 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 491:
#line 1684 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 5982 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 492:
#line 1690 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 5991 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 493:
#line 1694 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_number **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6000 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 494:
#line 1701 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_number **)(&(*yyvalp))) = (*(struct psi_number **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6008 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 495:
#line 1704 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		int8_t sizeof_void_p = sizeof(void *);
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
		psi_decl_type_free(&(*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	} else {
		(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_SIZEOF, (*(struct psi_decl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), 0);
	}
}
#line 6022 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 496:
#line 1716 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	int8_t sizeof_void_p = sizeof(void *);
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_void_p, 0);
}
#line 6031 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 497:
#line 1720 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	int8_t sizeof_a = sizeof('a');
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_INT8, &sizeof_a, 0);
}
#line 6040 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 498:
#line 1724 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	uint64_t len = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text->len + 1;
	(*(struct psi_number **)(&(*yyvalp))) = psi_number_init(PSI_T_UINT64, &len, 0);
}
#line 6049 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 499:
#line 1731 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6064 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 500:
#line 1744 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6079 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 501:
#line 1757 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	if ((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))) {
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	} else {
		char digest[17];

		psi_token_hash((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), digest);
		(*(struct psi_token **)(&(*yyvalp))) = psi_token_append("@", psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))), 1, digest);
	}
}
#line 6094 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 502:
#line 1770 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = NULL;
}
#line 6102 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 503:
#line 1773 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&(*yyvalp))) = (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_token **)(&(*yyvalp)))->type = PSI_T_NAME;
}
#line 6111 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 506:
#line 1785 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = NULL;
}
#line 6119 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 507:
#line 1788 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(0, 0, psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text->val), NULL));
}
#line 6127 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 508:
#line 1791 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val), NULL);
}
#line 6135 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 509:
#line 1794 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout **)(&(*yyvalp))) = psi_layout_init(atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val), atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val), psi_layout_init(0, atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval))->text->val), NULL));
}
#line 6143 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 510:
#line 1800 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = 0;
	(*(struct psi_layout*)(&(*yyvalp))).len = 0;
}
#line 6152 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 511:
#line 1804 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_layout*)(&(*yyvalp))).pos = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text->val);
	(*(struct psi_layout*)(&(*yyvalp))).len = atol((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))->text->val);
}
#line 6161 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 512:
#line 1811 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6169 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 513:
#line 1814 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6177 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 514:
#line 1817 "src/parser_proc_grammar.y" /* glr.c:821  */
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
#line 6194 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 519:
#line 1839 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 0;
}
#line 6202 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 520:
#line 1842 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6210 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 522:
#line 1849 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6218 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 523:
#line 1855 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = 1;
}
#line 6226 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 524:
#line 1858 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(size_t*)(&(*yyvalp))) = (*(size_t*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)) + 1;
}
#line 6234 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 529:
#line 1880 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
}
#line 6242 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 530:
#line 1883 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl **)(&(*yyvalp))) = psi_impl_init((*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6251 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 531:
#line 1890 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, NULL, (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval));
}
#line 6261 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 532:
#line 1895 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval));
}
#line 6271 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 533:
#line 1900 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_func **)(&(*yyvalp))) = psi_impl_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-8)].yystate.yysemantics.yysval)), (*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-10)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_func **)(&(*yyvalp)))->return_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval));
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)), psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))), NULL);
	(*(struct psi_impl_func **)(&(*yyvalp)))->vararg->var->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6283 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 534:
#line 1910 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6291 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 535:
#line 1913 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_impl_arg **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6299 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 536:
#line 1919 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)), NULL);
}
#line 6307 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 537:
#line 1922 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_arg **)(&(*yyvalp))) = psi_impl_arg_init((*(struct psi_impl_type **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_impl_def_val **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6315 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 538:
#line 1928 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_var **)(&(*yyvalp))) = psi_impl_var_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text, (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_impl_var **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6324 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 539:
#line 1935 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6333 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 540:
#line 1942 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_impl_type **)(&(*yyvalp))) = psi_impl_type_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->text);
	(*(struct psi_impl_type **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6342 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 552:
#line 1969 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6350 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 553:
#line 1972 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)), &(*(struct psi_token ***)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6358 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 554:
#line 1978 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_return_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6366 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 555:
#line 1981 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_let_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6374 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 556:
#line 1984 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_set_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6382 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 557:
#line 1987 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_assert_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6390 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 558:
#line 1990 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token ***)(&(*yyvalp))) = (struct psi_token **) (*(struct psi_free_stmt **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6398 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 559:
#line 1996 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init((*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6407 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 560:
#line 2000 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_stmt **)(&(*yyvalp))) = psi_let_stmt_init(psi_let_exp_init_ex((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)), PSI_LET_TMP, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval))));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_let_stmt **)(&(*yyvalp)))->exp->is_reference = (*(bool*)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6417 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 562:
#line 2009 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = true;
}
#line 6426 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 563:
#line 2013 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = false;
}
#line 6435 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 564:
#line 2020 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 6443 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 565:
#line 2023 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6451 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 566:
#line 2026 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6459 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 567:
#line 2029 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLOC, (*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->static_memory = 1;
}
#line 6468 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 568:
#line 2033 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init(PSI_LET_CALLBACK, (*(struct psi_let_callback **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6476 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 569:
#line 2036 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, (*(struct psi_let_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6484 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 570:
#line 2042 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6493 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 571:
#line 2046 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_exp **)(&(*yyvalp))) = (*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_let_exp **)(&(*yyvalp)))->is_reference = 1;
	(*(struct psi_let_exp **)(&(*yyvalp)))->var = (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval));
}
#line 6503 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 572:
#line 2054 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_calloc **)(&(*yyvalp))) = psi_let_calloc_init((*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_let_calloc **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
}
#line 6512 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 573:
#line 2061 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), NULL);
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-7)].yystate.yysemantics.yysval)));
}
#line 6522 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 574:
#line 2066 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_callback **)(&(*yyvalp))) = psi_let_callback_init(psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-9)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->func->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-6)].yystate.yysemantics.yysval)));
	(*(struct psi_let_callback **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-11)].yystate.yysemantics.yysval)));
}
#line 6532 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 575:
#line 2074 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_let_func **)(&(*yyvalp))) = psi_let_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_let_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6542 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 586:
#line 2095 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6550 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 587:
#line 2098 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6558 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 588:
#line 2104 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6566 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 589:
#line 2107 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_let_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6574 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 592:
#line 2118 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6582 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 593:
#line 2121 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6590 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 594:
#line 2127 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6598 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 595:
#line 2130 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6606 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 596:
#line 2136 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_stmt **)(&(*yyvalp))) = psi_return_stmt_init((*(struct psi_return_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_return_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6615 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 597:
#line 2143 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)), (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)), psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->token);
}
#line 6624 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 598:
#line 2147 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_return_exp **)(&(*yyvalp))) = psi_return_exp_init(NULL, NULL, psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))));
	(*(struct psi_return_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval))->token);
}
#line 6633 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 599:
#line 2154 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6641 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 600:
#line 2157 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6649 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 601:
#line 2160 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6657 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 602:
#line 2166 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_stmt **)(&(*yyvalp))) = psi_set_stmt_init((*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_set_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6666 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 603:
#line 2173 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_FUNC, (*(struct psi_set_func **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6674 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 604:
#line 2176 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = psi_set_exp_init(PSI_SET_NUMEXP, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6682 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 605:
#line 2179 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_exp **)(&(*yyvalp))) = (*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
	(*(struct psi_set_exp **)(&(*yyvalp)))->var = (*(struct psi_impl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval));
}
#line 6691 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 606:
#line 2186 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-4)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->inner = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval));
}
#line 6701 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 607:
#line 2191 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_set_func **)(&(*yyvalp))) = psi_set_func_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->type, (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval))->text, (*(struct psi_decl_var **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-5)].yystate.yysemantics.yysval)));
	(*(struct psi_set_func **)(&(*yyvalp)))->recursive = 1;
}
#line 6711 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 616:
#line 2210 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = NULL;
}
#line 6719 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 617:
#line 2213 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval));
}
#line 6727 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 618:
#line 2219 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6735 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 619:
#line 2222 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_set_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6743 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 620:
#line 2228 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_assert_stmt **)(&(*yyvalp))) = psi_assert_stmt_init((enum psi_assert_kind) (*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval))->type, (*(struct psi_num_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_assert_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6752 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 623:
#line 2240 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_free_stmt **)(&(*yyvalp))) = psi_free_stmt_init((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_stmt **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)));
}
#line 6761 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 624:
#line 2247 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6769 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 625:
#line 2250 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_plist **)(&(*yyvalp))) = psi_plist_add((*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-2)].yystate.yysemantics.yysval)), &(*(struct psi_free_exp **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (0)].yystate.yysemantics.yysval)));
}
#line 6777 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 626:
#line 2256 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->type = PSI_T_NAME;
	(*(struct psi_free_exp **)(&(*yyvalp))) = psi_free_exp_init((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval))->text, (*(struct psi_plist **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-1)].yystate.yysemantics.yysval)));
	(*(struct psi_free_exp **)(&(*yyvalp)))->token = psi_token_copy((*(struct psi_token **)(&((yyGLRStackItem const *)yyvsp)[YYFILL (-3)].yystate.yysemantics.yysval)));
}
#line 6787 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 627:
#line 2264 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(bool*)(&(*yyvalp))) = false;
}
#line 6795 "src/parser_proc.c" /* glr.c:821  */
    break;

  case 628:
#line 2267 "src/parser_proc_grammar.y" /* glr.c:821  */
    {
	(*(bool*)(&(*yyvalp))) = true;
}
#line 6803 "src/parser_proc.c" /* glr.c:821  */
    break;


#line 6807 "src/parser_proc.c" /* glr.c:821  */
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
          case 139: /* binary_op_token  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6858 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 140: /* unary_op_token  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6864 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 141: /* name_token  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6870 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 142: /* any_noeol_token  */
#line 292 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6876 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 147: /* cpp  */
#line 301 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 6882 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 148: /* cpp_exp  */
#line 301 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_exp_free(&(*(struct psi_cpp_exp **)(&(*yyvaluep))));}
#line 6888 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 149: /* cpp_macro_decl_arg_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6894 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 151: /* cpp_message_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6900 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 152: /* cpp_include_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6906 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 153: /* cpp_header_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6912 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 154: /* cpp_no_arg_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6918 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 155: /* cpp_name_arg_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6924 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 156: /* cpp_exp_arg_token  */
#line 289 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6930 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 157: /* cpp_macro_decl  */
#line 303 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_cpp_macro_decl_free(&(*(struct psi_cpp_macro_decl **)(&(*yyvaluep))));}
#line 6936 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 158: /* cpp_macro_sig  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6942 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 159: /* cpp_macro_sig_args  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6948 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 160: /* cpp_macro_decl_tokens  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6954 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 161: /* cpp_macro_decl_token_list  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6960 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 162: /* cpp_macro_exp  */
#line 307 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 6966 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 163: /* cpp_macro_call_args  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6972 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 164: /* cpp_macro_call_arg_list  */
#line 305 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 6978 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 165: /* constant  */
#line 313 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_const_free(&(*(struct psi_const **)(&(*yyvaluep))));}
#line 6984 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 166: /* impl_def_val  */
#line 315 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_def_val_free(&(*(struct psi_impl_def_val **)(&(*yyvaluep))));}
#line 6990 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 167: /* impl_def_val_token  */
#line 310 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 6996 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 168: /* decl_typedef  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7002 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 169: /* typedef  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7008 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 170: /* typedef_anon  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7014 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 171: /* typedef_decl  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7020 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 172: /* typedef_anon_decl  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7026 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 173: /* qualified_decl_type  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7032 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 175: /* decl_type  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7038 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 176: /* decl_type_complex  */
#line 324 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_type_free(&(*(struct psi_decl_type **)(&(*yyvaluep))));}
#line 7044 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 177: /* decl_type_simple  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7050 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 178: /* decl_real_type  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7056 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 179: /* int_signed  */
#line 298 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7062 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 180: /* int_width  */
#line 295 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7068 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 181: /* decl_int_type  */
#line 318 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7074 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 182: /* int_signed_types  */
#line 295 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7080 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 183: /* signed_short_types  */
#line 298 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7086 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 184: /* signed_long_types  */
#line 298 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7092 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 185: /* int_width_types  */
#line 295 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7098 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 186: /* decl_stmt  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7104 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 187: /* decl_asm  */
#line 321 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7110 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 188: /* quoted_strings  */
#line 321 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7116 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 189: /* decl_extvar_stmt  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7122 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 190: /* decl_extvar_list  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7128 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 191: /* decl_vars  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7134 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 192: /* ignored_decl  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7140 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 197: /* decl  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7146 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 198: /* decl_body  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7152 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 199: /* decl_func_body  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7158 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 200: /* decl_functor_body  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7164 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 201: /* decl_anon_functor_body  */
#line 326 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_free(&(*(struct psi_decl **)(&(*yyvaluep))));}
#line 7170 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 202: /* decl_functor  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7176 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 203: /* decl_anon_functor  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7182 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 204: /* decl_func  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7188 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 205: /* decl_args  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7194 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 206: /* decl_arg_list  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7200 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 207: /* decl_anon_arg  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7206 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 208: /* decl_arg  */
#line 328 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_arg_free(&(*(struct psi_decl_arg **)(&(*yyvaluep))));}
#line 7212 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 209: /* decl_var  */
#line 330 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_var_free(&(*(struct psi_decl_var **)(&(*yyvaluep))));}
#line 7218 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 210: /* decl_union  */
#line 334 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_union_free(&(*(struct psi_decl_union **)(&(*yyvaluep))));}
#line 7224 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 211: /* decl_struct  */
#line 332 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_struct_free(&(*(struct psi_decl_struct **)(&(*yyvaluep))));}
#line 7230 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 212: /* decl_struct_args  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7236 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 213: /* struct_args_block  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7242 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 214: /* struct_args  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7248 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 215: /* struct_arg_var_list  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7254 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 216: /* decl_vars_with_layout  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7260 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 217: /* decl_enum  */
#line 336 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_enum_free(&(*(struct psi_decl_enum **)(&(*yyvaluep))));}
#line 7266 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 218: /* decl_enum_items  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7272 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 219: /* decl_enum_item  */
#line 338 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_decl_enum_item_free(&(*(struct psi_decl_enum_item **)(&(*yyvaluep))));}
#line 7278 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 220: /* num_exp  */
#line 396 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_num_exp_free(&(*(struct psi_num_exp **)(&(*yyvaluep))));}
#line 7284 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 221: /* number  */
#line 398 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7290 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 222: /* sizeof  */
#line 348 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7296 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 223: /* sizeof_body  */
#line 348 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7302 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 224: /* sizeof_body_notypes  */
#line 348 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_number_free(&(*(struct psi_number **)(&(*yyvaluep))));}
#line 7308 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 225: /* enum_name  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7314 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 226: /* union_name  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7320 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 227: /* struct_name  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7326 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 228: /* optional_name  */
#line 286 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_token_free(&(*(struct psi_token **)(&(*yyvaluep))));}
#line 7332 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 230: /* decl_layout  */
#line 345 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_layout_free(&(*(struct psi_layout **)(&(*yyvaluep))));}
#line 7338 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 231: /* align_and_size  */
#line 343 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7344 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 232: /* array_size  */
#line 401 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7350 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 234: /* indirection  */
#line 401 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7356 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 235: /* pointers  */
#line 401 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7362 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 236: /* asterisks  */
#line 401 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7368 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 239: /* impl  */
#line 351 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_free(&(*(struct psi_impl **)(&(*yyvaluep))));}
#line 7374 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 240: /* impl_func  */
#line 353 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_func_free(&(*(struct psi_impl_func **)(&(*yyvaluep))));}
#line 7380 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 241: /* impl_args  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7386 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 242: /* impl_arg  */
#line 355 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_arg_free(&(*(struct psi_impl_arg **)(&(*yyvaluep))));}
#line 7392 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 243: /* impl_var  */
#line 359 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_var_free(&(*(struct psi_impl_var **)(&(*yyvaluep))));}
#line 7398 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 244: /* impl_type  */
#line 357 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7404 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 245: /* impl_type_restricted  */
#line 357 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_type_free(&(*(struct psi_impl_type **)(&(*yyvaluep))));}
#line 7410 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 246: /* impl_type_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7416 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 247: /* impl_type_restricted_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7422 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 248: /* impl_type_extended_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7428 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 249: /* impl_stmts  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7434 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 250: /* impl_stmt  */
#line 389 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_impl_stmt_free(&(*(struct psi_token ***)(&(*yyvaluep))));}
#line 7440 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 251: /* let_stmt  */
#line 362 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_stmt_free(&(*(struct psi_let_stmt **)(&(*yyvaluep))));}
#line 7446 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 252: /* let_exp  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7452 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 253: /* let_exp_byref  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7458 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 254: /* let_exp_assign  */
#line 364 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_exp_free(&(*(struct psi_let_exp **)(&(*yyvaluep))));}
#line 7464 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 255: /* let_calloc  */
#line 366 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_calloc_free(&(*(struct psi_let_calloc **)(&(*yyvaluep))));}
#line 7470 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 256: /* let_callback  */
#line 368 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_callback_free(&(*(struct psi_let_callback **)(&(*yyvaluep))));}
#line 7476 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 257: /* let_func  */
#line 370 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_let_func_free(&(*(struct psi_let_func **)(&(*yyvaluep))));}
#line 7482 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 258: /* let_func_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7488 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 259: /* let_func_exps  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7494 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 260: /* let_exps  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7500 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 261: /* callback_rval  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7506 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 262: /* callback_arg_list  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7512 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 263: /* callback_args  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7518 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 264: /* return_stmt  */
#line 380 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_return_stmt_free(&(*(struct psi_return_stmt **)(&(*yyvaluep))));}
#line 7524 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 265: /* return_exp  */
#line 382 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_return_exp_free(&(*(struct psi_return_exp **)(&(*yyvaluep))));}
#line 7530 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 266: /* call_decl_vars  */
#line 340 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7536 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 267: /* set_stmt  */
#line 372 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_stmt_free(&(*(struct psi_set_stmt **)(&(*yyvaluep))));}
#line 7542 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 268: /* set_exp  */
#line 374 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_exp_free(&(*(struct psi_set_exp **)(&(*yyvaluep))));}
#line 7548 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 269: /* set_func  */
#line 376 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_set_func_free(&(*(struct psi_set_func **)(&(*yyvaluep))));}
#line 7554 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 270: /* set_func_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7560 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 271: /* set_func_exps  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7566 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 272: /* set_exps  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7572 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 273: /* assert_stmt  */
#line 378 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_assert_stmt_free(&(*(struct psi_assert_stmt **)(&(*yyvaluep))));}
#line 7578 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 274: /* assert_stmt_token  */
#line 391 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7584 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 275: /* free_stmt  */
#line 384 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_free_stmt_free(&(*(struct psi_free_stmt **)(&(*yyvaluep))));}
#line 7590 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 276: /* free_exps  */
#line 393 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_plist_free((*(struct psi_plist **)(&(*yyvaluep))));}
#line 7596 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 277: /* free_exp  */
#line 386 "src/parser_proc_grammar.y" /* glr.c:851  */
      {psi_free_exp_free(&(*(struct psi_free_exp **)(&(*yyvaluep))));}
#line 7602 "src/parser_proc.c" /* glr.c:851  */
        break;

    case 278: /* reference  */
#line 403 "src/parser_proc_grammar.y" /* glr.c:851  */
      {}
#line 7608 "src/parser_proc.c" /* glr.c:851  */
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
  (!!((Yystate) == (-710)))

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

#line 8961 "src/parser_proc.c" /* glr.c:2265  */

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

#line 2276 "src/parser_proc_grammar.y" /* glr.c:2578  */


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

