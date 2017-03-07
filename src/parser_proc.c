/*
** 2000-05-29
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** Driver template for the LEMON parser generator.
**
** The "lemon" program processes an LALR(1) input grammar file, then uses
** this template to construct a parser.  The "lemon" program inserts text
** at each "%%" line.  Also, any "P-a-r-s-e" identifer prefix (without the
** interstitial "-" characters) contained in this template is changed into
** the value of the %name directive from the grammar.  Otherwise, the content
** of this template is copied straight through into the generate parser
** source file.
**
** The following is the concatenation of all %include directives from the
** input grammar file:
*/
#include <stdio.h>
/************ Begin %include sections from the grammar ************************/
#line 1 "src/parser_proc.y"

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

#line 62 "src/parser_proc.c"
/**************** End of %include directives **********************************/
/* These constants specify the various numeric values for terminal symbols
** in a format understandable to "makeheaders".  This section is blank unless
** "lemon" is run with the "-m" command-line option.
***************** Begin makeheaders token definitions *************************/
/**************** End makeheaders token definitions ***************************/

/* The next sections is a series of control #defines.
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used to store the integer codes
**                       that represent terminal and non-terminal symbols.
**                       "unsigned char" is used if there are fewer than
**                       256 symbols.  Larger types otherwise.
**    YYNOCODE           is a number of type YYCODETYPE that is not used for
**                       any terminal or nonterminal symbol.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       (also known as: "terminal symbols") have fall-back
**                       values which should be used if the original symbol
**                       would not parse.  This permits keywords to sometimes
**                       be used as identifiers, for example.
**    YYACTIONTYPE       is the data type used for "action codes" - numbers
**                       that indicate what to do in response to the next
**                       token.
**    ParseTOKENTYPE     is the data type used for minor type for terminal
**                       symbols.  Background: A "minor type" is a semantic
**                       value associated with a terminal or non-terminal
**                       symbols.  For example, for an "ID" terminal symbol,
**                       the minor type might be the name of the identifier.
**                       Each non-terminal can have a different minor type.
**                       Terminal symbols all have the same minor type, though.
**                       This macros defines the minor type for terminal 
**                       symbols.
**    YYMINORTYPE        is the data type used for all minor types.
**                       This is typically a union of many types, one of
**                       which is ParseTOKENTYPE.  The entry in the union
**                       for terminal symbols is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    ParseARG_SDECL     A static variable declaration for the %extra_argument
**    ParseARG_PDECL     A parameter declaration for the %extra_argument
**    ParseARG_STORE     Code to store %extra_argument into yypParser
**    ParseARG_FETCH     Code to extract %extra_argument from yypParser
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YY_MAX_SHIFT       Maximum value for shift actions
**    YY_MIN_SHIFTREDUCE Minimum value for shift-reduce actions
**    YY_MAX_SHIFTREDUCE Maximum value for shift-reduce actions
**    YY_MIN_REDUCE      Maximum value for reduce actions
**    YY_ERROR_ACTION    The yy_action[] code for syntax error
**    YY_ACCEPT_ACTION   The yy_action[] code for accept
**    YY_NO_ACTION       The yy_action[] code for no-op
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/************* Begin control #defines *****************************************/
#define YYCODETYPE unsigned char
#define YYNOCODE 193
#define YYACTIONTYPE unsigned short int
#define YYWILDCARD 74
#define ParseTOKENTYPE struct psi_token *
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  struct psi_decl_union* yy15;
  struct psi_decl_abi* yy26;
  struct psi_impl_arg* yy34;
  struct psi_const* yy38;
  struct psi_let_calloc* yy45;
  struct psi_impl* yy49;
  struct psi_impl_func* yy56;
  struct psi_number* yy57;
  struct psi_let_func* yy67;
  bool yy89;
  struct psi_let_callback* yy120;
  struct psi_cpp_macro_decl* yy134;
  struct psi_impl_def_val* yy145;
  struct psi_free_exp* yy146;
  struct psi_decl_enum_item* yy169;
  struct psi_decl_type* yy172;
  struct psi_plist* yy179;
  struct psi_set_exp* yy180;
  struct psi_let_exp* yy200;
  struct psi_assert_stmt* yy201;
  struct psi_num_exp* yy207;
  struct psi_free_stmt* yy220;
  struct psi_token** yy238;
  struct psi_layout yy239;
  struct psi_plist * yy243;
  struct psi_impl_type* yy246;
  struct psi_decl_var* yy271;
  struct psi_cpp_exp* yy274;
  struct psi_decl* yy303;
  struct psi_let_stmt* yy319;
  struct psi_decl_arg* yy320;
  struct psi_decl_enum * yy323;
  struct psi_decl_struct* yy324;
  struct psi_return_stmt* yy342;
  struct psi_const_type* yy351;
  struct psi_set_stmt* yy358;
  struct psi_set_func* yy362;
  struct psi_layout* yy369;
  struct psi_impl_var* yy370;
  unsigned yy382;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL struct psi_parser *P;
#define ParseARG_PDECL ,struct psi_parser *P
#define ParseARG_FETCH struct psi_parser *P = yypParser->P
#define ParseARG_STORE yypParser->P = P
#define YYFALLBACK 1
#define YYNSTATE             233
#define YYNRULE              191
#define YY_MAX_SHIFT         232
#define YY_MIN_SHIFTREDUCE   385
#define YY_MAX_SHIFTREDUCE   575
#define YY_MIN_REDUCE        576
#define YY_MAX_REDUCE        766
#define YY_ERROR_ACTION      767
#define YY_ACCEPT_ACTION     768
#define YY_NO_ACTION         769
/************* End control #defines *******************************************/

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N <= YY_MAX_SHIFT             Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   N between YY_MIN_SHIFTREDUCE       Shift to an arbitrary state then
**     and YY_MAX_SHIFTREDUCE           reduce by rule N-YY_MIN_SHIFTREDUCE.
**
**   N between YY_MIN_REDUCE            Reduce by rule N-YY_MIN_REDUCE
**     and YY_MAX_REDUCE
**
**   N == YY_ERROR_ACTION               A syntax error has occurred.
**
**   N == YY_ACCEPT_ACTION              The parser accepts its input.
**
**   N == YY_NO_ACTION                  No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as either:
**
**    (A)   N = yy_action[ yy_shift_ofst[S] + X ]
**    (B)   N = yy_default[S]
**
** The (A) formula is preferred.  The B formula is used instead if:
**    (1)  The yy_shift_ofst[S]+X value is out of range, or
**    (2)  yy_lookahead[yy_shift_ofst[S]+X] is not equal to X, or
**    (3)  yy_shift_ofst[S] equal YY_SHIFT_USE_DFLT.
** (Implementation note: YY_SHIFT_USE_DFLT is chosen so that
** YY_SHIFT_USE_DFLT+X will be out of range for all possible lookaheads X.
** Hence only tests (1) and (2) need to be evaluated.)
**
** The formulas above are for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
**
*********** Begin parsing tables **********************************************/
#define YY_ACTTAB_COUNT (1132)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   482,  497,  520,  497,  497,  497,  497,  497,  497,  497,
 /*    10 */   497,  497,  497,  104,  525,  519,  189,  136,  565,  519,
 /*    20 */   521,  114,   17,  529,  531,   28,   28,  568,   25,   25,
 /*    30 */   510,  127,   42,   52,   11,   10,   70,  104,   28,   28,
 /*    40 */   173,  173,  173,  173,  173,  173,  173,  173,  173,  173,
 /*    50 */   142,  568,   25,   25,   50,   94,   42,   52,   11,   10,
 /*    60 */    70,  568,  511,  501,  505,  505,  505,  505,  505,  438,
 /*    70 */   174,   59,   30,   30,   30,   30,   30,   30,   30,   30,
 /*    80 */    30,   30,   30,   30,   30,   29,   51,   30,   30,  171,
 /*    90 */     2,  101,  100,   99,  499,  436,  158,   37,  401,  401,
 /*   100 */   584,  585,  478,   92,   77,   75,   74,  482,  497,  226,
 /*   110 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*   120 */   120,  104,  526,  519,  144,  504,  166,  519,  441,  441,
 /*   130 */   441,  441,  559,   28,   28,  568,  166,  166,  166,  166,
 /*   140 */   166,  166,  166,  218,  493,   81,   28,   28,  173,  173,
 /*   150 */   173,  173,  173,  173,  173,  173,  173,  173,  392,  146,
 /*   160 */   485,   78,   94,  437,  440,  482,  497,  464,  497,  497,
 /*   170 */   497,  497,  497,  497,  497,  497,  497,  497,  174,   68,
 /*   180 */    68,   68,   68,   68,   68,   68,   68,   68,   68,   68,
 /*   190 */    68,   68,  482,   29,   68,   68,  232,  471,  204,  206,
 /*   200 */   205,  503,  498,   46,   37,  513,  178,  502,  515,  478,
 /*   210 */    92,   77,   75,   74,  183,  135,  517,  516,  462,  128,
 /*   220 */    44,  514,  518,  482,  497,  463,  497,  497,  497,  497,
 /*   230 */   497,  497,  497,  497,  497,  497,  467,  423,  457,  180,
 /*   240 */   129,  560,  421,  453,  422,  149,  420,  419,  498,   46,
 /*   250 */   569,  417,  493,   21,  470,  134,  101,  100,   99,  498,
 /*   260 */    46,   91,   36,  418,  176,  161,  142,  478,   92,   77,
 /*   270 */    75,   74,  118,  142,  437,  439,  149,  119,   94,  172,
 /*   280 */   121,  482,  497,  162,  497,  497,  497,  497,  497,  497,
 /*   290 */   497,  497,  497,  497,  478,   92,   77,  221,  493,  573,
 /*   300 */   574,  575,   60,  768,    3,    3,  132,  219,   56,  493,
 /*   310 */   126,  112,  152,  142,  101,  100,   99,  106,  215,  195,
 /*   320 */    37,  454,  506,   73,    1,  478,   92,   77,   75,   74,
 /*   330 */   170,  142,  124,   80,   79,  568,   87,  182,  186,  482,
 /*   340 */   497,  207,  497,  497,  497,  497,  497,  497,  497,  497,
 /*   350 */   497,  497,  447,  191,  142,  104,   88,  519,   18,  512,
 /*   360 */   190,  519,  515,  122,  172,  498,   35,   28,   28,  568,
 /*   370 */   517,  516,  204,  206,  205,  514,  518,  520,   37,  105,
 /*   380 */    28,   28,  133,  478,   92,   77,   75,   74,  431,  464,
 /*   390 */   445,  444,  185,  186,   76,  521,  108,  482,  497,  207,
 /*   400 */   497,  497,  497,  497,  497,  497,  497,  497,  497,  497,
 /*   410 */   203,  219,   98,   96,  103,  493,  172,  402,   90,  591,
 /*   420 */     4,  472,  509,  498,   46,  142,  466,   29,  569,  520,
 /*   430 */   204,  206,  205,  188,  186,  520,   37,  142,  142,  142,
 /*   440 */   569,  478,   92,   77,   75,   74,  159,  521,  109,  143,
 /*   450 */   432,  192,   94,  521,  110,  482,  497,  207,  497,  497,
 /*   460 */   497,  497,  497,  497,  497,  497,  497,  497,  203,  219,
 /*   470 */    98,   96,  194,  493,  153,   38,   90,  142,  520,  473,
 /*   480 */   490,  498,   46,  142,  562,   40,  175,  489,  204,  206,
 /*   490 */   205,  540,    8,  402,   37,  586,  521,  116,  139,  478,
 /*   500 */    92,   77,   75,   74,  521,  115,  483,  528,  530,  148,
 /*   510 */    85,  527,  542,  482,  497,   79,  497,  497,  497,  497,
 /*   520 */   497,  497,  497,  497,  497,  497,  142,  219,   98,   96,
 /*   530 */   156,  493,  550,   13,  142,  408,  547,  547,  547,  547,
 /*   540 */   547,  547,  547,  547,  547,  547,  204,  206,  205,  549,
 /*   550 */     7,  520,  548,  467,  520,  539,    6,  478,   92,   77,
 /*   560 */    75,   74,  157,  520,  179,   23,  165,  569,   93,  521,
 /*   570 */   111,   22,  521,  113,  470,  137,  561,  169,  167,  498,
 /*   580 */    46,  521,  123,  104,  545,  519,  552,  448,   24,  519,
 /*   590 */   412,   65,  565,   41,  520,   28,   28,  568,  465,  142,
 /*   600 */   172,  456,  142,  125,  204,  206,  205,  224,   28,   28,
 /*   610 */   166,  142,  521,  117,  455,  478,   92,   77,   75,   74,
 /*   620 */   166,  166,  166,  166,  166,  166,  166,  396,  225,  493,
 /*   630 */   616,  104,  449,  519,  616,   19,  512,  519,  214,  515,
 /*   640 */   565,   45,  142,   28,   28,  568,  201,  517,  516,  202,
 /*   650 */   488,  486,  514,  518,  481,   29,   28,   28,  166,  479,
 /*   660 */   175,  138,    2,   47,   95,   48,  430,   97,  166,  166,
 /*   670 */   166,  166,  166,  166,  166,  231,  231,  140,  521,  115,
 /*   680 */   755,  528,  530,  141,  429,  527,  541,  130,  208,  428,
 /*   690 */   230,  229,  389,  390,  228,  227,   49,  423,  217,  425,
 /*   700 */    69,   64,  421,   29,  422,  461,  420,  419,  142,  460,
 /*   710 */   433,  417,  398,   21,  147,   61,   71,  150,  164,  151,
 /*   720 */    62,   63,   32,  418,  176,   30,   30,   30,   30,   30,
 /*   730 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   740 */    30,   30,   30,  507,  507,  507,  507,   30,   30,   30,
 /*   750 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   760 */    30,   30,   30,   30,   30,  572,  155,  219,   15,   25,
 /*   770 */    25,  558,   34,   42,   52,   11,   10,   70,  557,  563,
 /*   780 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   790 */    30,   30,   30,   30,   30,   30,   30,   30,  536,  507,
 /*   800 */   507,  507,  507,  507,  500,  535,   82,  551,   12,   14,
 /*   810 */    43,  506,  537,  538,   30,   30,   30,   30,   30,   30,
 /*   820 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   830 */    30,   30,  168,    5,   53,   54,   27,    9,  452,   16,
 /*   840 */   177,  451,   20,  181,   83,   84,   55,   26,   68,   68,
 /*   850 */    68,   68,   68,   68,   68,   68,   68,   68,   68,   68,
 /*   860 */    68,   68,   68,   68,   68,   68,  184,  520,  569,  104,
 /*   870 */    86,  519,  187,   57,  644,  519,  443,  442,  565,  165,
 /*   880 */   522,   28,   28,  568,   72,  521,  113,  193,   89,  196,
 /*   890 */   477,  198,  197,  199,   28,   28,  166,  554,  131,  552,
 /*   900 */   200,  475,  496,  474,  495,  494,  166,  166,  166,  166,
 /*   910 */   166,  166,  166,  172,  405,  142,   30,   30,   30,   30,
 /*   920 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   930 */    30,   30,   30,   30,  507,  507,  507,  507,  446,  616,
 /*   940 */   427,   29,   68,   68,   68,   68,   68,   68,   68,   68,
 /*   950 */    68,   68,   68,   68,   68,   68,   68,   68,   68,   68,
 /*   960 */   761,  209,  211,  212,  210,  102,  459,   31,  216,  416,
 /*   970 */   222,  213,  410,  220,  457,   39,  410,   58,  223,  175,
 /*   980 */   409,  399,   66,   66,  107,   33,  391,  388,  387,  386,
 /*   990 */   507,  507,  507,  507,  507,   66,   66,  521,  115,  385,
 /*  1000 */   528,  530,  578,  578,  527,  534,  578,  578,  578,  578,
 /*  1010 */   578,  578,  578,  578,  578,  578,  578,  578,  578,  578,
 /*  1020 */   154,  578,  578,  578,  578,  578,  578,  142,  578,  578,
 /*  1030 */   578,  578,  578,  221,  578,  573,  574,  575,   60,  578,
 /*  1040 */   578,  578,   67,  578,  520,  578,  175,  145,  578,  578,
 /*  1050 */   578,  578,  578,  106,  215,  195,  165,  578,  578,   73,
 /*  1060 */     1,  520,  521,  113,  521,  115,  520,  528,  530,   80,
 /*  1070 */    79,  527,  163,  165,  160,  578,  552,  578,  165,  521,
 /*  1080 */   113,  578,  578,  520,  521,  113,  578,  578,  578,  578,
 /*  1090 */   172,  556,  142,  552,  142,  165,  555,  578,  552,  578,
 /*  1100 */   578,  521,  113,  578,  578,  578,  578,  172,  578,  142,
 /*  1110 */   578,  578,  172,  546,  142,  552,  578,  578,  578,  578,
 /*  1120 */   578,  578,  578,  578,  578,  578,  578,  578,  578,  172,
 /*  1130 */   578,  142,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,  130,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   14,   15,   16,  177,  178,   23,   20,
 /*    20 */   148,  149,   23,  151,  152,   26,   27,   28,   62,   63,
 /*    30 */   143,  144,   66,   67,   68,   69,   70,   14,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */   178,   28,   62,   63,  167,   57,   66,   67,   68,   69,
 /*    60 */    70,   28,  143,   97,   15,   16,   17,   18,   19,   75,
 /*    70 */    71,   72,   22,   23,   24,   25,   26,   27,   28,   29,
 /*    80 */    30,   31,   32,   33,   34,   86,  167,   37,   38,  191,
 /*    90 */    96,   93,   94,   95,  137,   97,   14,   99,   74,   74,
 /*   100 */    76,   76,  104,  105,  106,  107,  108,    2,    3,   85,
 /*   110 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   120 */   171,   14,   15,   16,  175,  167,   41,   20,    1,    2,
 /*   130 */     3,    4,   75,   26,   27,   28,   51,   52,   53,   54,
 /*   140 */    55,   56,   57,   14,  187,   88,   39,   40,   41,   42,
 /*   150 */    43,   44,   45,   46,   47,   48,   49,   50,  169,  170,
 /*   160 */     5,  172,   57,  116,  117,    2,    3,  130,    5,    6,
 /*   170 */     7,    8,    9,   10,   11,   12,   13,   14,   71,   22,
 /*   180 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   190 */    33,   34,    2,   86,   37,   38,  168,  132,   93,   94,
 /*   200 */    95,  167,  137,  138,   99,  147,  101,  167,  150,  104,
 /*   210 */   105,  106,  107,  108,  177,  178,  158,  159,  130,  131,
 /*   220 */    57,  163,  164,    2,    3,  130,    5,    6,    7,    8,
 /*   230 */     9,   10,   11,   12,   13,   14,   14,  113,   14,  128,
 /*   240 */   165,  166,  118,  132,  120,  142,  122,  123,  137,  138,
 /*   250 */    28,  127,  187,  129,  132,  133,   93,   94,   95,  137,
 /*   260 */   138,  106,   99,  139,  140,  130,  178,  104,  105,  106,
 /*   270 */   107,  108,  171,  178,  116,  117,  142,  171,   57,  176,
 /*   280 */   171,    2,    3,  130,    5,    6,    7,    8,    9,   10,
 /*   290 */    11,   12,   13,   14,  104,  105,  106,   73,  187,   75,
 /*   300 */    76,   77,   78,  179,  180,  181,  130,  183,   86,  187,
 /*   310 */   176,  171,  101,  178,   93,   94,   95,   93,   94,   95,
 /*   320 */    99,   14,  111,   99,  100,  104,  105,  106,  107,  108,
 /*   330 */   142,  178,  171,  109,  110,   28,   57,  177,  178,    2,
 /*   340 */     3,  113,    5,    6,    7,    8,    9,   10,   11,   12,
 /*   350 */    13,   14,  124,  125,  178,   14,  128,   16,  146,  147,
 /*   360 */   132,   20,  150,  171,  176,  137,  138,   26,   27,   28,
 /*   370 */   158,  159,   93,   94,   95,  163,  164,  130,   99,   88,
 /*   380 */    39,   40,  142,  104,  105,  106,  107,  108,   97,  130,
 /*   390 */   130,  130,  177,  178,   57,  148,  149,    2,    3,  113,
 /*   400 */     5,    6,    7,    8,    9,   10,   11,   12,   13,   14,
 /*   410 */   124,  183,  184,  185,   14,  187,  176,   74,  132,   76,
 /*   420 */   134,  135,  141,  137,  138,  178,   14,   86,   28,  130,
 /*   430 */    93,   94,   95,  177,  178,  130,   99,  178,  178,  178,
 /*   440 */    28,  104,  105,  106,  107,  108,  162,  148,  149,  114,
 /*   450 */   115,  141,   57,  148,  149,    2,    3,  113,    5,    6,
 /*   460 */     7,    8,    9,   10,   11,   12,   13,   14,  124,  183,
 /*   470 */   184,  185,  121,  187,   87,   88,  132,  178,  130,  135,
 /*   480 */   187,  137,  138,  178,   87,   88,  130,  187,   93,   94,
 /*   490 */    95,   87,   88,   74,   99,   76,  148,  149,  178,  104,
 /*   500 */   105,  106,  107,  108,  148,  149,  189,  151,  152,  170,
 /*   510 */    57,  155,  156,    2,    3,  110,    5,    6,    7,    8,
 /*   520 */     9,   10,   11,   12,   13,   14,  178,  183,  184,  185,
 /*   530 */   176,  187,   87,   88,  178,   14,   41,   42,   43,   44,
 /*   540 */    45,   46,   47,   48,   49,   50,   93,   94,   95,   87,
 /*   550 */    88,  130,   57,   14,  130,   87,   88,  104,  105,  106,
 /*   560 */   107,  108,  140,  130,   87,   88,  142,   28,   57,  148,
 /*   570 */   149,   86,  148,  149,  132,  133,  166,  153,  154,  137,
 /*   580 */   138,  148,  149,   14,  160,   16,  162,   87,   88,   20,
 /*   590 */    87,   88,   23,  176,  130,   26,   27,   28,  126,  178,
 /*   600 */   176,  126,  178,  178,   93,   94,   95,   86,   39,   40,
 /*   610 */    41,  178,  148,  149,  126,  104,  105,  106,  107,  108,
 /*   620 */    51,   52,   53,   54,   55,   56,   57,   87,   88,  187,
 /*   630 */    92,   14,  126,   16,   96,  146,  147,   20,   92,  150,
 /*   640 */    23,  119,  178,   26,   27,   28,   92,  158,  159,  136,
 /*   650 */     2,  190,  163,  164,    2,   86,   39,   40,   41,  188,
 /*   660 */   130,  178,   96,  116,  119,  116,  182,  119,   51,   52,
 /*   670 */    53,   54,   55,   56,   57,   64,   65,   14,  148,  149,
 /*   680 */   111,  151,  152,   14,  182,  155,  156,  157,   14,  182,
 /*   690 */    79,   80,   81,   82,   83,   84,  119,  113,  102,   14,
 /*   700 */    89,   90,  118,   86,  120,  186,  122,  123,  178,  186,
 /*   710 */   115,  127,   14,  129,  173,   92,   98,   87,  101,  111,
 /*   720 */    92,   92,   86,  139,  140,   21,   22,   23,   24,   25,
 /*   730 */    26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
 /*   740 */    36,   37,   38,    1,    2,    3,    4,   21,   22,   23,
 /*   750 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   760 */    34,   35,   36,   37,   38,  181,   20,  183,   96,   62,
 /*   770 */    63,   75,   86,   66,   67,   68,   69,   70,   75,   75,
 /*   780 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   790 */    31,   32,   33,   34,   35,   36,   37,   38,   75,   57,
 /*   800 */    58,   59,   60,   61,   97,   75,   98,   87,   98,   88,
 /*   810 */    86,  111,   87,   87,   21,   22,   23,   24,   25,   26,
 /*   820 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   830 */    37,   38,   87,   86,   86,   86,   86,   98,   75,   96,
 /*   840 */    87,   75,   86,   14,   87,   87,   86,   88,   21,   22,
 /*   850 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   860 */    33,   34,   35,   36,   37,   38,   14,  130,   28,   14,
 /*   870 */    87,   16,   14,   86,   86,   20,   75,   75,   23,  142,
 /*   880 */    87,   26,   27,   28,   98,  148,  149,   20,   14,   16,
 /*   890 */    87,   16,   88,   86,   39,   40,   41,  160,  161,  162,
 /*   900 */    92,   75,   14,   75,   14,   14,   51,   52,   53,   54,
 /*   910 */    55,   56,   57,  176,   87,  178,   21,   22,   23,   24,
 /*   920 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   930 */    35,   36,   37,   38,    1,    2,    3,    4,   14,   96,
 /*   940 */    87,   86,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   950 */    29,   30,   31,   32,   33,   34,   35,   36,   37,   38,
 /*   960 */     0,   16,   16,   86,   88,   14,  103,   98,   16,   75,
 /*   970 */    14,   92,   16,   19,   14,   86,   20,   96,   14,  130,
 /*   980 */    87,   14,   26,   27,   86,   14,   14,   14,   14,   19,
 /*   990 */    57,   58,   59,   60,   61,   39,   40,  148,  149,   76,
 /*  1000 */   151,  152,  192,  192,  155,  156,  192,  192,  192,  192,
 /*  1010 */   192,  192,  192,  192,  192,  192,  192,  192,  192,  192,
 /*  1020 */    87,  192,  192,  192,  192,  192,  192,  178,  192,  192,
 /*  1030 */   192,  192,  192,   73,  192,   75,   76,   77,   78,  192,
 /*  1040 */   192,  192,   86,  192,  130,  192,  130,   91,  192,  192,
 /*  1050 */   192,  192,  192,   93,   94,   95,  142,  192,  192,   99,
 /*  1060 */   100,  130,  148,  149,  148,  149,  130,  151,  152,  109,
 /*  1070 */   110,  155,  156,  142,  160,  192,  162,  192,  142,  148,
 /*  1080 */   149,  192,  192,  130,  148,  149,  192,  192,  192,  192,
 /*  1090 */   176,  160,  178,  162,  178,  142,  160,  192,  162,  192,
 /*  1100 */   192,  148,  149,  192,  192,  192,  192,  176,  192,  178,
 /*  1110 */   192,  192,  176,  160,  178,  162,  192,  192,  192,  192,
 /*  1120 */   192,  192,  192,  192,  192,  192,  192,  192,  192,  176,
 /*  1130 */   192,  178,
};
#define YY_SHIFT_USE_DFLT (1132)
#define YY_SHIFT_COUNT    (232)
#define YY_SHIFT_MIN      (-34)
#define YY_SHIFT_MAX      (974)
static const short yy_shift_ofst[] = {
 /*     0 */   224,  163,  221,  960,   -2,  569,   -1,  617,   -1,   -1,
 /*    10 */    -1,  855,  855,  855,  855,  -10,  -10,  107,  -34,  707,
 /*    20 */   279,  337,  279,  105,  395,  341,  341,  341,  341,  341,
 /*    30 */   341,  341,  933,   24,   23,   23,  453,  511,  742,  956,
 /*    40 */    23,   23,   23,   23,  307,   -6,   23,   23,   23,   -6,
 /*    50 */    -5,   -5,   82,   -5,   -5,   33,   33,   33,  129,  495,
 /*    60 */   611,  742,  742,  742,  956,  956,  956,  956,  956,  956,
 /*    70 */    85,   49,   49,  127,  190,  190,  307,  155,   25,   -5,
 /*    80 */   405,   82,   -5,  485,  485,   33,  485,   33,  485,  546,
 /*    90 */   554,  648,  652,   33,   33,  566,  546,  566,  546,  663,
 /*   100 */   669,  674,  546,  596,  596,  129,  685,  698,  704,  726,
 /*   110 */   759,  793,  827,  895,  895,  895,  895,  895,  921,  921,
 /*   120 */   921,  921,  921,   50,  157,  222,  211,  387,  397,   57,
 /*   130 */   404,  445,  462,  468,  477,  400,  412,  500,  539,  412,
 /*   140 */   538,  538,  400,  291,  503,  521,  343,  540,  419,  618,
 /*   150 */   623,  630,  608,  628,  629,  636,  746,  672,  686,  696,
 /*   160 */   703,  723,  708,  730,  720,  710,  724,  721,  725,  745,
 /*   170 */   747,  748,  700,  749,  750,  739,  743,  763,  753,  766,
 /*   180 */   756,  757,  829,  760,  758,  852,  840,  783,  858,  787,
 /*   190 */   788,  801,  802,  786,  867,  874,  803,  873,  804,  875,
 /*   200 */   807,  808,  826,  828,  888,  890,  891,  924,  843,  853,
 /*   210 */   945,  876,  946,  877,  879,  951,  863,  952,  869,  881,
 /*   220 */   894,  954,  889,  893,  964,  967,  898,  971,  972,  973,
 /*   230 */   974,  970,  923,
};
#define YY_REDUCE_USE_DFLT (-162)
#define YY_REDUCE_COUNT (107)
#define YY_REDUCE_MIN   (-161)
#define YY_REDUCE_MAX   (953)
static const short yy_reduce_ofst[] = {
 /*     0 */   124,  228,  286,  584,  344,  424,  530,  737,  356,  849,
 /*    10 */   916,  914,  931,  936,  953,  212,  489, -128,   58,   58,
 /*    20 */   122,  111,  442,   65,   65,  247,  299,  305,  348,  421,
 /*    30 */   433,  464, -113,  -11,   88,   37,  -43,  -43,  -81,  -51,
 /*    40 */    95,  135,  153,  176, -161,   47,  259,  260,  261,  158,
 /*    50 */   103,  134,   75,  188,  240,  160,  215,  256,  335, -102,
 /*    60 */    28,  -42,   34,   40,  101,  106,  109,  140,  161,  192,
 /*    70 */   284,  281,  310,  351,  293,  300,  320,  317,  339,  354,
 /*    80 */   422,  410,  417,  472,  475,  425,  488,  320,  506,  522,
 /*    90 */   513,  461,  471,  483,  320,  547,  545,  549,  548,  484,
 /*   100 */   502,  507,  577,  519,  523,  595,  507,  541,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   767,  767,  767,  767,  767,  734,  767,  755,  767,  767,
 /*    10 */   767,  755,  755,  755,  755,  767,  767,  767,  767,  767,
 /*    20 */   659,  767,  659,  767,  767,  767,  767,  767,  767,  767,
 /*    30 */   767,  767,  767,  767,  767,  757,  767,  767,  767,  604,
 /*    40 */   767,  767,  767,  767,  757,  767,  767,  767,  767,  767,
 /*    50 */   755,  755,  767,  755,  755,  757,  757,  757,  767,  767,
 /*    60 */   767,  767,  767,  767,  767,  767,  767,  767,  767,  767,
 /*    70 */   767,  767,  767,  767,  683,  682,  767,  675,  767,  755,
 /*    80 */   767,  767,  755,  767,  767,  767,  767,  660,  767,  617,
 /*    90 */   667,  678,  671,  767,  767,  767,  617,  767,  617,  615,
 /*   100 */   615,  615,  617,  649,  649,  767,  615,  588,  767,  767,
 /*   110 */   767,  767,  767,  744,  724,  723,  715,  625,  595,  606,
 /*   120 */   605,  597,  594,  714,  598,  767,  767,  767,  767,  767,
 /*   130 */   767,  767,  767,  767,  767,  758,  758,  767,  767,  767,
 /*   140 */   686,  685,  767,  767,  767,  767,  767,  767,  767,  699,
 /*   150 */   767,  767,  767,  767,  767,  767,  767,  767,  767,  767,
 /*   160 */   767,  767,  767,  767,  767,  767,  767,  735,  767,  767,
 /*   170 */   767,  767,  767,  767,  767,  711,  767,  767,  767,  767,
 /*   180 */   767,  767,  767,  767,  767,  767,  758,  767,  767,  767,
 /*   190 */   641,  767,  767,  767,  767,  767,  767,  767,  767,  767,
 /*   200 */   767,  767,  767,  767,  767,  767,  767,  767,  687,  767,
 /*   210 */   767,  767,  767,  767,  767,  767,  767,  767,  626,  767,
 /*   220 */   767,  767,  602,  767,  767,  767,  767,  767,  767,  767,
 /*   230 */   767,  767,  767,
};
/********** End of lemon-generated parsing tables *****************************/

/* The next table maps tokens (terminal symbols) into fallback tokens.  
** If a construct like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
**
** This feature can be used, for example, to cause some keywords in a language
** to revert to identifiers if they keyword does not apply in the context where
** it appears.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*       BOOL => nothing */
    0,  /*        INT => nothing */
    0,  /*      FLOAT => nothing */
   14,  /*     STRING => NAME */
    0,  /*     DOUBLE => nothing */
    0,  /*       INT8 => nothing */
    0,  /*      UINT8 => nothing */
    0,  /*      INT16 => nothing */
    0,  /*     UINT16 => nothing */
    0,  /*      INT32 => nothing */
    0,  /*     UINT32 => nothing */
    0,  /*      INT64 => nothing */
    0,  /*     UINT64 => nothing */
    0,  /*       NAME => nothing */
    0,  /*       NULL => nothing */
    0,  /*     NUMBER => nothing */
    0,  /*       TRUE => nothing */
    0,  /*      FALSE => nothing */
    0,  /* QUOTED_STRING => nothing */
    0,  /*     NSNAME => nothing */
    0,  /*       PIPE => nothing */
    0,  /*      CARET => nothing */
    0,  /*  AMPERSAND => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*   ASTERISK => nothing */
    0,  /*      SLASH => nothing */
    0,  /*     MODULO => nothing */
    0,  /*     RCHEVR => nothing */
    0,  /*     LCHEVR => nothing */
    0,  /*     CMP_GE => nothing */
    0,  /*     CMP_LE => nothing */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*     CMP_EQ => nothing */
    0,  /*     CMP_NE => nothing */
    0,  /*      TILDE => nothing */
    0,  /*        NOT => nothing */
   14,  /*       ZVAL => NAME */
    0,  /*     OBJVAL => nothing */
    0,  /*     ARRVAL => nothing */
    0,  /*    PATHVAL => nothing */
    0,  /*     STRLEN => nothing */
    0,  /*     STRVAL => nothing */
    0,  /*   FLOATVAL => nothing */
    0,  /*     INTVAL => nothing */
    0,  /*    BOOLVAL => nothing */
   14,  /*      COUNT => NAME */
    0,  /*  TO_OBJECT => nothing */
    0,  /*   TO_ARRAY => nothing */
    0,  /*  TO_STRING => nothing */
    0,  /*     TO_INT => nothing */
    0,  /*   TO_FLOAT => nothing */
    0,  /*    TO_BOOL => nothing */
    0,  /*       VOID => nothing */
    0,  /*      MIXED => nothing */
    0,  /*      ARRAY => nothing */
    0,  /*     OBJECT => nothing */
    0,  /*   CALLABLE => nothing */
    0,  /* PRE_ASSERT => nothing */
    0,  /* POST_ASSERT => nothing */
   14,  /*      ERROR => NAME */
   14,  /*    WARNING => NAME */
   14,  /*       TEMP => NAME */
   14,  /*       FREE => NAME */
   14,  /*        SET => NAME */
   14,  /*        LET => NAME */
   14,  /*     RETURN => NAME */
   14,  /*     CALLOC => NAME */
   14,  /*   CALLBACK => NAME */
   14,  /*        LIB => NAME */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
**
** After the "shift" half of a SHIFTREDUCE action, the stateno field
** actually contains the reduce action for the second half of the
** SHIFTREDUCE.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number, or reduce action in SHIFTREDUCE */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  yyStackEntry *yytos;          /* Pointer to top element of the stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyhwm;                    /* High-water mark of the stack */
#endif
#ifndef YYNOERRORRECOVERY
  int yyerrcnt;                 /* Shifts left before out of the error */
#endif
  ParseARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
  yyStackEntry yystk0;          /* First stack entry */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void ParseTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "BOOL",          "INT",           "FLOAT",       
  "STRING",        "DOUBLE",        "INT8",          "UINT8",       
  "INT16",         "UINT16",        "INT32",         "UINT32",      
  "INT64",         "UINT64",        "NAME",          "NULL",        
  "NUMBER",        "TRUE",          "FALSE",         "QUOTED_STRING",
  "NSNAME",        "PIPE",          "CARET",         "AMPERSAND",   
  "LSHIFT",        "RSHIFT",        "PLUS",          "MINUS",       
  "ASTERISK",      "SLASH",         "MODULO",        "RCHEVR",      
  "LCHEVR",        "CMP_GE",        "CMP_LE",        "OR",          
  "AND",           "CMP_EQ",        "CMP_NE",        "TILDE",       
  "NOT",           "ZVAL",          "OBJVAL",        "ARRVAL",      
  "PATHVAL",       "STRLEN",        "STRVAL",        "FLOATVAL",    
  "INTVAL",        "BOOLVAL",       "COUNT",         "TO_OBJECT",   
  "TO_ARRAY",      "TO_STRING",     "TO_INT",        "TO_FLOAT",    
  "TO_BOOL",       "VOID",          "MIXED",         "ARRAY",       
  "OBJECT",        "CALLABLE",      "PRE_ASSERT",    "POST_ASSERT", 
  "ERROR",         "WARNING",       "TEMP",          "FREE",        
  "SET",           "LET",           "RETURN",        "CALLOC",      
  "CALLBACK",      "LIB",           "ANY",           "EOS",         
  "EOL",           "COMMENT",       "HASH",          "IFDEF",       
  "IFNDEF",        "ENDIF",         "ELSE",          "UNDEF",       
  "DEFINE",        "NO_WHITESPACE",  "LPAREN",        "RPAREN",      
  "COMMA",         "IF",            "ELIF",          "DEFINED",     
  "COLON",         "ENUM",          "STRUCT",        "UNION",       
  "LBRACE",        "RBRACE",        "EQUALS",        "CONST",       
  "TYPEDEF",       "ELLIPSIS",      "LBRACKET",      "RBRACKET",    
  "CHAR",          "SHORT",         "LONG",          "UNSIGNED",    
  "SIGNED",        "STATIC",        "FUNCTION",      "DOLLAR_NAME", 
  "error",         "decl_enum",     "decl_enum_items",  "decl_enum_item",
  "decl_struct_args_block",  "decl_struct_args",  "decl_struct",   "align_and_size",
  "decl_union",    "const_type",    "constant",      "decl_typedef",
  "decl_typedef_body_ex",  "decl_typedef_body",  "decl_typedef_body_fn_args",  "decl",        
  "decl_func",     "decl_abi",      "decl_var",      "decl_vars",   
  "decl_arg",      "decl_args",     "struct_args",   "struct_arg",  
  "decl_layout",   "decl_type",     "const_decl_type",  "impl",        
  "impl_func",     "impl_def_val",  "impl_var",      "impl_arg",    
  "impl_args",     "impl_vararg",   "impl_stmts",    "impl_stmt",   
  "number",        "num_exp",       "let_stmt",      "let_calloc",  
  "let_func",      "callback_arg_list",  "callback_args",  "let_callback",
  "let_exp",       "let_exps",      "assert_stmt",   "set_stmt",    
  "set_exp",       "set_exps",      "set_func",      "return_stmt", 
  "free_stmt",     "free_exps",     "free_exp",      "impl_type",   
  "cpp_exp",       "cpp_macro_decl",  "cpp_macro_decl_tokens",  "cpp_macro_exp",
  "cpp_macro_sig",  "cpp_macro_sig_args",  "cpp_macro_call",  "cpp_macro_call_args",
  "reference",     "indirection",   "pointers",      "file",        
  "blocks",        "block",         "optional_name",  "enum_name",   
  "struct_name",   "union_name",    "decl_var_array_size",  "decl_scalar_type",
  "decl_scalar_type_short",  "decl_scalar_type_long",  "decl_scalar_type_long_long",  "callback_rval",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "block ::= HASH cpp_exp EOL",
 /*   1 */ "cpp_exp ::= ERROR|WARNING QUOTED_STRING",
 /*   2 */ "cpp_exp ::= IFDEF NAME",
 /*   3 */ "cpp_exp ::= IFNDEF NAME",
 /*   4 */ "cpp_exp ::= ENDIF",
 /*   5 */ "cpp_exp ::= ELSE",
 /*   6 */ "cpp_exp ::= UNDEF NAME",
 /*   7 */ "cpp_exp ::= DEFINE NAME cpp_macro_decl",
 /*   8 */ "cpp_macro_decl ::=",
 /*   9 */ "cpp_macro_decl ::= cpp_macro_sig",
 /*  10 */ "cpp_macro_decl ::= cpp_macro_sig cpp_macro_decl_tokens",
 /*  11 */ "cpp_macro_sig ::= NO_WHITESPACE LPAREN cpp_macro_sig_args RPAREN",
 /*  12 */ "cpp_macro_sig_args ::=",
 /*  13 */ "cpp_macro_sig_args ::= NAME",
 /*  14 */ "cpp_macro_sig_args ::= cpp_macro_sig_args COMMA NAME",
 /*  15 */ "cpp_macro_decl ::= cpp_macro_decl_tokens",
 /*  16 */ "cpp_macro_decl_tokens ::= ANY",
 /*  17 */ "cpp_macro_decl_tokens ::= cpp_macro_decl_tokens ANY",
 /*  18 */ "cpp_exp ::= IF cpp_macro_exp",
 /*  19 */ "cpp_exp ::= ELIF cpp_macro_exp",
 /*  20 */ "cpp_macro_exp ::= LPAREN cpp_macro_exp RPAREN",
 /*  21 */ "cpp_macro_exp ::= TILDE|NOT|PLUS|MINUS cpp_macro_exp",
 /*  22 */ "cpp_macro_exp ::= cpp_macro_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE cpp_macro_exp",
 /*  23 */ "cpp_macro_exp ::= DEFINED NAME",
 /*  24 */ "cpp_macro_exp ::= DEFINED LPAREN NAME RPAREN",
 /*  25 */ "cpp_macro_exp ::= NUMBER|NSNAME",
 /*  26 */ "cpp_macro_exp ::= NAME",
 /*  27 */ "cpp_macro_exp ::= NAME LPAREN cpp_macro_call_args RPAREN",
 /*  28 */ "cpp_macro_call_args ::=",
 /*  29 */ "cpp_macro_call_args ::= cpp_macro_exp",
 /*  30 */ "cpp_macro_call_args ::= cpp_macro_call_args COMMA cpp_macro_exp",
 /*  31 */ "block ::= LIB QUOTED_STRING EOS",
 /*  32 */ "block ::= decl",
 /*  33 */ "block ::= impl",
 /*  34 */ "block ::= decl_typedef",
 /*  35 */ "block ::= constant",
 /*  36 */ "block ::= decl_struct",
 /*  37 */ "block ::= decl_union",
 /*  38 */ "block ::= decl_enum",
 /*  39 */ "optional_name ::=",
 /*  40 */ "optional_name ::= NAME",
 /*  41 */ "align_and_size ::=",
 /*  42 */ "align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN",
 /*  43 */ "enum_name ::= ENUM optional_name",
 /*  44 */ "struct_name ::= STRUCT optional_name",
 /*  45 */ "union_name ::= UNION optional_name",
 /*  46 */ "decl_enum ::= enum_name LBRACE decl_enum_items RBRACE",
 /*  47 */ "decl_enum_items ::= decl_enum_item",
 /*  48 */ "decl_enum_items ::= decl_enum_items COMMA decl_enum_item",
 /*  49 */ "decl_enum_item ::= NAME EQUALS num_exp",
 /*  50 */ "decl_enum_item ::= NAME",
 /*  51 */ "decl_struct_args_block ::= LBRACE struct_args RBRACE",
 /*  52 */ "decl_struct_args ::= decl_struct_args_block",
 /*  53 */ "decl_struct_args ::= EOS",
 /*  54 */ "decl_struct ::= STRUCT NAME align_and_size decl_struct_args",
 /*  55 */ "decl_union ::= UNION NAME align_and_size decl_struct_args",
 /*  56 */ "const_type ::= BOOL|INT|FLOAT|STRING",
 /*  57 */ "constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS",
 /*  58 */ "decl_typedef ::= TYPEDEF decl_typedef_body EOS",
 /*  59 */ "decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var",
 /*  60 */ "decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var",
 /*  61 */ "decl_typedef_body_ex ::= decl_enum NAME",
 /*  62 */ "decl_typedef_body ::= decl_typedef_body_ex",
 /*  63 */ "decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN",
 /*  64 */ "decl_typedef_body ::= decl_func decl_typedef_body_fn_args",
 /*  65 */ "decl_typedef_body ::= decl_arg",
 /*  66 */ "decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS",
 /*  67 */ "decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS",
 /*  68 */ "decl_func ::= decl_arg",
 /*  69 */ "decl_func ::= VOID NAME",
 /*  70 */ "decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  71 */ "decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  72 */ "decl_abi ::= NAME",
 /*  73 */ "decl_var_array_size ::=",
 /*  74 */ "decl_var_array_size ::= LBRACKET NUMBER RBRACKET",
 /*  75 */ "decl_var ::= NAME decl_var_array_size",
 /*  76 */ "decl_var ::= pointers NAME decl_var_array_size",
 /*  77 */ "decl_vars ::= decl_var",
 /*  78 */ "decl_vars ::= decl_vars COMMA decl_var",
 /*  79 */ "decl_arg ::= const_decl_type decl_var",
 /*  80 */ "decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  81 */ "decl_arg ::= VOID pointers NAME",
 /*  82 */ "decl_arg ::= CONST VOID pointers NAME",
 /*  83 */ "decl_args ::=",
 /*  84 */ "decl_args ::= VOID",
 /*  85 */ "decl_args ::= decl_arg",
 /*  86 */ "decl_args ::= decl_args COMMA decl_arg",
 /*  87 */ "struct_args ::= struct_arg",
 /*  88 */ "struct_args ::= struct_args struct_arg",
 /*  89 */ "struct_arg ::= decl_typedef_body_ex EOS",
 /*  90 */ "struct_arg ::= decl_arg decl_layout EOS",
 /*  91 */ "decl_layout ::=",
 /*  92 */ "decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN",
 /*  93 */ "decl_scalar_type ::= CHAR",
 /*  94 */ "decl_scalar_type ::= SHORT decl_scalar_type_short",
 /*  95 */ "decl_scalar_type_short ::=",
 /*  96 */ "decl_scalar_type_short ::= INT",
 /*  97 */ "decl_scalar_type ::= INT",
 /*  98 */ "decl_scalar_type ::= LONG decl_scalar_type_long",
 /*  99 */ "decl_scalar_type_long ::=",
 /* 100 */ "decl_scalar_type_long ::= DOUBLE",
 /* 101 */ "decl_scalar_type_long ::= LONG decl_scalar_type_long_long",
 /* 102 */ "decl_scalar_type_long_long ::=",
 /* 103 */ "decl_scalar_type_long_long ::= INT",
 /* 104 */ "decl_type ::= UNSIGNED decl_scalar_type",
 /* 105 */ "decl_type ::= SIGNED decl_scalar_type",
 /* 106 */ "decl_type ::= UNSIGNED",
 /* 107 */ "decl_type ::= SIGNED",
 /* 108 */ "decl_type ::= decl_scalar_type",
 /* 109 */ "decl_type ::= STRUCT NAME",
 /* 110 */ "decl_type ::= UNION NAME",
 /* 111 */ "decl_type ::= ENUM NAME",
 /* 112 */ "decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME",
 /* 113 */ "const_decl_type ::= decl_type",
 /* 114 */ "const_decl_type ::= CONST decl_type",
 /* 115 */ "impl ::= impl_func LBRACE impl_stmts RBRACE",
 /* 116 */ "impl ::= STATIC impl_func LBRACE impl_stmts RBRACE",
 /* 117 */ "impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type",
 /* 118 */ "impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type",
 /* 119 */ "impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type",
 /* 120 */ "impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING",
 /* 121 */ "impl_var ::= reference DOLLAR_NAME",
 /* 122 */ "impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE",
 /* 123 */ "impl_arg ::= impl_type impl_var",
 /* 124 */ "impl_arg ::= impl_type impl_var EQUALS impl_def_val",
 /* 125 */ "impl_args ::= impl_arg",
 /* 126 */ "impl_args ::= impl_args COMMA impl_arg",
 /* 127 */ "impl_stmts ::= impl_stmt",
 /* 128 */ "impl_stmts ::= impl_stmts impl_stmt",
 /* 129 */ "impl_stmt ::= return_stmt",
 /* 130 */ "impl_stmt ::= let_stmt",
 /* 131 */ "impl_stmt ::= set_stmt",
 /* 132 */ "impl_stmt ::= assert_stmt",
 /* 133 */ "impl_stmt ::= free_stmt",
 /* 134 */ "number ::= NUMBER|NSNAME",
 /* 135 */ "number ::= decl_var",
 /* 136 */ "num_exp ::= number",
 /* 137 */ "num_exp ::= LPAREN num_exp RPAREN",
 /* 138 */ "num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp",
 /* 139 */ "num_exp ::= TILDE|NOT|PLUS|MINUS num_exp",
 /* 140 */ "let_exp ::= NULL",
 /* 141 */ "let_exp ::= AMPERSAND NULL",
 /* 142 */ "let_exp ::= let_callback",
 /* 143 */ "let_exp ::= let_calloc",
 /* 144 */ "let_exp ::= AMPERSAND let_calloc",
 /* 145 */ "let_exp ::= let_func",
 /* 146 */ "let_exp ::= AMPERSAND let_func",
 /* 147 */ "let_exp ::= num_exp",
 /* 148 */ "let_exp ::= AMPERSAND num_exp",
 /* 149 */ "let_exp ::= decl_var EQUALS let_exp",
 /* 150 */ "let_stmt ::= LET let_exp EOS",
 /* 151 */ "let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS",
 /* 152 */ "let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN",
 /* 153 */ "let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN",
 /* 154 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN",
 /* 155 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN",
 /* 156 */ "let_exps ::= let_exp",
 /* 157 */ "let_exps ::= let_exps COMMA let_exp",
 /* 158 */ "callback_arg_list ::=",
 /* 159 */ "callback_arg_list ::= callback_args",
 /* 160 */ "callback_args ::= set_exp",
 /* 161 */ "callback_args ::= callback_args COMMA set_exp",
 /* 162 */ "callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT",
 /* 163 */ "callback_rval ::= VOID",
 /* 164 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN",
 /* 165 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN",
 /* 166 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN",
 /* 167 */ "set_exp ::= set_func",
 /* 168 */ "set_exp ::= num_exp",
 /* 169 */ "set_exps ::= set_exp",
 /* 170 */ "set_exps ::= set_exps COMMA set_exp",
 /* 171 */ "set_exp ::= impl_var EQUALS set_exp",
 /* 172 */ "set_stmt ::= SET set_exp EOS",
 /* 173 */ "return_stmt ::= RETURN set_func EOS",
 /* 174 */ "free_stmt ::= FREE free_exps EOS",
 /* 175 */ "free_exps ::= free_exp",
 /* 176 */ "free_exps ::= free_exps COMMA free_exp",
 /* 177 */ "free_exp ::= NAME LPAREN decl_vars RPAREN",
 /* 178 */ "assert_stmt ::= PRE_ASSERT|POST_ASSERT num_exp EOS",
 /* 179 */ "reference ::=",
 /* 180 */ "reference ::= AMPERSAND",
 /* 181 */ "indirection ::=",
 /* 182 */ "indirection ::= pointers",
 /* 183 */ "pointers ::= ASTERISK",
 /* 184 */ "pointers ::= pointers ASTERISK",
 /* 185 */ "file ::= blocks",
 /* 186 */ "blocks ::= block",
 /* 187 */ "blocks ::= blocks block",
 /* 188 */ "block ::= EOS",
 /* 189 */ "block ::= EOL",
 /* 190 */ "block ::= COMMENT",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.  Return the number
** of errors.  Return 0 on success.
*/
static int yyGrowStack(yyParser *p){
  int newSize;
  int idx;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  idx = p->yytos ? (int)(p->yytos - p->yystack) : 0;
  if( p->yystack==&p->yystk0 ){
    pNew = malloc(newSize*sizeof(pNew[0]));
    if( pNew ) pNew[0] = p->yystk0;
  }else{
    pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  }
  if( pNew ){
    p->yystack = pNew;
    p->yytos = &p->yystack[idx];
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows from %d to %d entries.\n",
              yyTracePrompt, p->yystksz, newSize);
    }
#endif
    p->yystksz = newSize;
  }
  return pNew==0; 
}
#endif

/* Datatype of the argument to the memory allocated passed as the
** second argument to ParseAlloc() below.  This can be changed by
** putting an appropriate #define in the %include section of the input
** grammar.
*/
#ifndef YYMALLOCARGTYPE
# define YYMALLOCARGTYPE size_t
#endif

/* Initialize a new parser that has already been allocated.
*/
void ParseInit(void *yypParser){
  yyParser *pParser = (yyParser*)yypParser;
#ifdef YYTRACKMAXSTACKDEPTH
  pParser->yyhwm = 0;
#endif
#if YYSTACKDEPTH<=0
  pParser->yytos = NULL;
  pParser->yystack = NULL;
  pParser->yystksz = 0;
  if( yyGrowStack(pParser) ){
    pParser->yystack = &pParser->yystk0;
    pParser->yystksz = 1;
  }
#endif
#ifndef YYNOERRORRECOVERY
  pParser->yyerrcnt = -1;
#endif
  pParser->yytos = pParser->yystack;
  pParser->yystack[0].stateno = 0;
  pParser->yystack[0].major = 0;
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to Parse and ParseFree.
*/
void *ParseAlloc(void *(*mallocProc)(YYMALLOCARGTYPE)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (YYMALLOCARGTYPE)sizeof(yyParser) );
  if( pParser ) ParseInit(pParser);
  return pParser;
}
#endif /* Parse_ENGINEALWAYSONSTACK */


/* The following function deletes the "minor type" or semantic value
** associated with a symbol.  The symbol can be either a terminal
** or nonterminal. "yymajor" is the symbol code, and "yypminor" is
** a pointer to the value to be deleted.  The code used to do the 
** deletions is derived from the %destructor and/or %token_destructor
** directives of the input grammar.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  ParseARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are *not* used
    ** inside the C code.
    */
/********* Begin destructor definitions ***************************************/
      /* TERMINAL Destructor */
    case 1: /* BOOL */
    case 2: /* INT */
    case 3: /* FLOAT */
    case 4: /* STRING */
    case 5: /* DOUBLE */
    case 6: /* INT8 */
    case 7: /* UINT8 */
    case 8: /* INT16 */
    case 9: /* UINT16 */
    case 10: /* INT32 */
    case 11: /* UINT32 */
    case 12: /* INT64 */
    case 13: /* UINT64 */
    case 14: /* NAME */
    case 15: /* NULL */
    case 16: /* NUMBER */
    case 17: /* TRUE */
    case 18: /* FALSE */
    case 19: /* QUOTED_STRING */
    case 20: /* NSNAME */
    case 21: /* PIPE */
    case 22: /* CARET */
    case 23: /* AMPERSAND */
    case 24: /* LSHIFT */
    case 25: /* RSHIFT */
    case 26: /* PLUS */
    case 27: /* MINUS */
    case 28: /* ASTERISK */
    case 29: /* SLASH */
    case 30: /* MODULO */
    case 31: /* RCHEVR */
    case 32: /* LCHEVR */
    case 33: /* CMP_GE */
    case 34: /* CMP_LE */
    case 35: /* OR */
    case 36: /* AND */
    case 37: /* CMP_EQ */
    case 38: /* CMP_NE */
    case 39: /* TILDE */
    case 40: /* NOT */
    case 41: /* ZVAL */
    case 42: /* OBJVAL */
    case 43: /* ARRVAL */
    case 44: /* PATHVAL */
    case 45: /* STRLEN */
    case 46: /* STRVAL */
    case 47: /* FLOATVAL */
    case 48: /* INTVAL */
    case 49: /* BOOLVAL */
    case 50: /* COUNT */
    case 51: /* TO_OBJECT */
    case 52: /* TO_ARRAY */
    case 53: /* TO_STRING */
    case 54: /* TO_INT */
    case 55: /* TO_FLOAT */
    case 56: /* TO_BOOL */
    case 57: /* VOID */
    case 58: /* MIXED */
    case 59: /* ARRAY */
    case 60: /* OBJECT */
    case 61: /* CALLABLE */
    case 62: /* PRE_ASSERT */
    case 63: /* POST_ASSERT */
    case 64: /* ERROR */
    case 65: /* WARNING */
    case 66: /* TEMP */
    case 67: /* FREE */
    case 68: /* SET */
    case 69: /* LET */
    case 70: /* RETURN */
    case 71: /* CALLOC */
    case 72: /* CALLBACK */
    case 73: /* LIB */
    case 74: /* ANY */
    case 75: /* EOS */
    case 76: /* EOL */
    case 77: /* COMMENT */
    case 78: /* HASH */
    case 79: /* IFDEF */
    case 80: /* IFNDEF */
    case 81: /* ENDIF */
    case 82: /* ELSE */
    case 83: /* UNDEF */
    case 84: /* DEFINE */
    case 85: /* NO_WHITESPACE */
    case 86: /* LPAREN */
    case 87: /* RPAREN */
    case 88: /* COMMA */
    case 89: /* IF */
    case 90: /* ELIF */
    case 91: /* DEFINED */
    case 92: /* COLON */
    case 93: /* ENUM */
    case 94: /* STRUCT */
    case 95: /* UNION */
    case 96: /* LBRACE */
    case 97: /* RBRACE */
    case 98: /* EQUALS */
    case 99: /* CONST */
    case 100: /* TYPEDEF */
    case 101: /* ELLIPSIS */
    case 102: /* LBRACKET */
    case 103: /* RBRACKET */
    case 104: /* CHAR */
    case 105: /* SHORT */
    case 106: /* LONG */
    case 107: /* UNSIGNED */
    case 108: /* SIGNED */
    case 109: /* STATIC */
    case 110: /* FUNCTION */
    case 111: /* DOLLAR_NAME */
{
#line 37 "src/parser_proc.y"
free((yypminor->yy0));
#line 1220 "src/parser_proc.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 112: /* error */
    case 119: /* align_and_size */
    case 176: /* reference */
    case 177: /* indirection */
    case 178: /* pointers */
    case 179: /* file */
    case 180: /* blocks */
    case 181: /* block */
    case 182: /* optional_name */
    case 183: /* enum_name */
    case 184: /* struct_name */
    case 185: /* union_name */
    case 186: /* decl_var_array_size */
    case 187: /* decl_scalar_type */
    case 188: /* decl_scalar_type_short */
    case 189: /* decl_scalar_type_long */
    case 190: /* decl_scalar_type_long_long */
    case 191: /* callback_rval */
{
#line 38 "src/parser_proc.y"
(void)P;
#line 1245 "src/parser_proc.c"
}
      break;
    case 113: /* decl_enum */
{
#line 66 "src/parser_proc.y"
psi_decl_enum_free(&(yypminor->yy323));
#line 1252 "src/parser_proc.c"
}
      break;
    case 114: /* decl_enum_items */
    case 116: /* decl_struct_args_block */
    case 117: /* decl_struct_args */
    case 126: /* decl_typedef_body_fn_args */
    case 131: /* decl_vars */
    case 133: /* decl_args */
    case 134: /* struct_args */
    case 144: /* impl_args */
    case 146: /* impl_stmts */
    case 157: /* let_exps */
    case 161: /* set_exps */
    case 165: /* free_exps */
    case 170: /* cpp_macro_decl_tokens */
    case 172: /* cpp_macro_sig */
    case 173: /* cpp_macro_sig_args */
    case 174: /* cpp_macro_call */
    case 175: /* cpp_macro_call_args */
{
#line 68 "src/parser_proc.y"
psi_plist_free((yypminor->yy179));
#line 1275 "src/parser_proc.c"
}
      break;
    case 115: /* decl_enum_item */
{
#line 70 "src/parser_proc.y"
psi_decl_enum_item_free(&(yypminor->yy169));
#line 1282 "src/parser_proc.c"
}
      break;
    case 118: /* decl_struct */
{
#line 76 "src/parser_proc.y"
psi_decl_struct_free(&(yypminor->yy324));
#line 1289 "src/parser_proc.c"
}
      break;
    case 120: /* decl_union */
{
#line 79 "src/parser_proc.y"
psi_decl_union_free(&(yypminor->yy15));
#line 1296 "src/parser_proc.c"
}
      break;
    case 121: /* const_type */
{
#line 81 "src/parser_proc.y"
psi_const_type_free(&(yypminor->yy351));
#line 1303 "src/parser_proc.c"
}
      break;
    case 122: /* constant */
{
#line 83 "src/parser_proc.y"
psi_const_free(&(yypminor->yy38));
#line 1310 "src/parser_proc.c"
}
      break;
    case 123: /* decl_typedef */
    case 124: /* decl_typedef_body_ex */
    case 125: /* decl_typedef_body */
    case 128: /* decl_func */
    case 132: /* decl_arg */
    case 135: /* struct_arg */
{
#line 85 "src/parser_proc.y"
psi_decl_arg_free(&(yypminor->yy320));
#line 1322 "src/parser_proc.c"
}
      break;
    case 127: /* decl */
{
#line 93 "src/parser_proc.y"
psi_decl_free(&(yypminor->yy303));
#line 1329 "src/parser_proc.c"
}
      break;
    case 129: /* decl_abi */
{
#line 97 "src/parser_proc.y"
psi_decl_abi_free(&(yypminor->yy26));
#line 1336 "src/parser_proc.c"
}
      break;
    case 130: /* decl_var */
{
#line 99 "src/parser_proc.y"
psi_decl_var_free(&(yypminor->yy271));
#line 1343 "src/parser_proc.c"
}
      break;
    case 136: /* decl_layout */
{
#line 111 "src/parser_proc.y"
psi_layout_free(&(yypminor->yy369));
#line 1350 "src/parser_proc.c"
}
      break;
    case 137: /* decl_type */
    case 138: /* const_decl_type */
{
#line 113 "src/parser_proc.y"
psi_decl_type_free(&(yypminor->yy172));
#line 1358 "src/parser_proc.c"
}
      break;
    case 139: /* impl */
{
#line 117 "src/parser_proc.y"
psi_impl_free(&(yypminor->yy49));
#line 1365 "src/parser_proc.c"
}
      break;
    case 140: /* impl_func */
{
#line 119 "src/parser_proc.y"
psi_impl_func_free(&(yypminor->yy56));
#line 1372 "src/parser_proc.c"
}
      break;
    case 141: /* impl_def_val */
{
#line 121 "src/parser_proc.y"
psi_impl_def_val_free(&(yypminor->yy145));
#line 1379 "src/parser_proc.c"
}
      break;
    case 142: /* impl_var */
{
#line 123 "src/parser_proc.y"
psi_impl_var_free(&(yypminor->yy370));
#line 1386 "src/parser_proc.c"
}
      break;
    case 143: /* impl_arg */
    case 145: /* impl_vararg */
{
#line 125 "src/parser_proc.y"
psi_impl_arg_free(&(yypminor->yy34));
#line 1394 "src/parser_proc.c"
}
      break;
    case 147: /* impl_stmt */
{
#line 133 "src/parser_proc.y"
psi_impl_stmt_free(&(yypminor->yy238));
#line 1401 "src/parser_proc.c"
}
      break;
    case 148: /* number */
{
#line 135 "src/parser_proc.y"
psi_number_free(&(yypminor->yy57));
#line 1408 "src/parser_proc.c"
}
      break;
    case 149: /* num_exp */
    case 171: /* cpp_macro_exp */
{
#line 137 "src/parser_proc.y"
psi_num_exp_free(&(yypminor->yy207));
#line 1416 "src/parser_proc.c"
}
      break;
    case 150: /* let_stmt */
{
#line 139 "src/parser_proc.y"
psi_let_stmt_free(&(yypminor->yy319));
#line 1423 "src/parser_proc.c"
}
      break;
    case 151: /* let_calloc */
{
#line 141 "src/parser_proc.y"
psi_let_calloc_free(&(yypminor->yy45));
#line 1430 "src/parser_proc.c"
}
      break;
    case 152: /* let_func */
{
#line 143 "src/parser_proc.y"
psi_let_func_free(&(yypminor->yy67));
#line 1437 "src/parser_proc.c"
}
      break;
    case 153: /* callback_arg_list */
    case 154: /* callback_args */
{
#line 145 "src/parser_proc.y"
psi_plist_free((yypminor->yy243));
#line 1445 "src/parser_proc.c"
}
      break;
    case 155: /* let_callback */
{
#line 149 "src/parser_proc.y"
psi_let_callback_free(&(yypminor->yy120));
#line 1452 "src/parser_proc.c"
}
      break;
    case 156: /* let_exp */
{
#line 151 "src/parser_proc.y"
psi_let_exp_free(&(yypminor->yy200));
#line 1459 "src/parser_proc.c"
}
      break;
    case 158: /* assert_stmt */
{
#line 155 "src/parser_proc.y"
psi_assert_stmt_free(&(yypminor->yy201));
#line 1466 "src/parser_proc.c"
}
      break;
    case 159: /* set_stmt */
{
#line 157 "src/parser_proc.y"
psi_set_stmt_free(&(yypminor->yy358));
#line 1473 "src/parser_proc.c"
}
      break;
    case 160: /* set_exp */
{
#line 159 "src/parser_proc.y"
psi_set_exp_free(&(yypminor->yy180));
#line 1480 "src/parser_proc.c"
}
      break;
    case 162: /* set_func */
{
#line 163 "src/parser_proc.y"
psi_set_func_free(&(yypminor->yy362));
#line 1487 "src/parser_proc.c"
}
      break;
    case 163: /* return_stmt */
{
#line 165 "src/parser_proc.y"
psi_return_stmt_free(&(yypminor->yy342));
#line 1494 "src/parser_proc.c"
}
      break;
    case 164: /* free_stmt */
{
#line 167 "src/parser_proc.y"
psi_free_stmt_free(&(yypminor->yy220));
#line 1501 "src/parser_proc.c"
}
      break;
    case 166: /* free_exp */
{
#line 171 "src/parser_proc.y"
psi_free_exp_free(&(yypminor->yy146));
#line 1508 "src/parser_proc.c"
}
      break;
    case 167: /* impl_type */
{
#line 173 "src/parser_proc.y"
psi_impl_type_free(&(yypminor->yy246));
#line 1515 "src/parser_proc.c"
}
      break;
    case 168: /* cpp_exp */
{
#line 175 "src/parser_proc.y"
psi_cpp_exp_free(&(yypminor->yy274));
#line 1522 "src/parser_proc.c"
}
      break;
    case 169: /* cpp_macro_decl */
{
#line 177 "src/parser_proc.y"
psi_cpp_macro_decl_free(&(yypminor->yy134));
#line 1529 "src/parser_proc.c"
}
      break;
/********* End destructor definitions *****************************************/
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
*/
static void yy_pop_parser_stack(yyParser *pParser){
  yyStackEntry *yytos;
  assert( pParser->yytos!=0 );
  assert( pParser->yytos > pParser->yystack );
  yytos = pParser->yytos--;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yy_destructor(pParser, yytos->major, &yytos->minor);
}

/*
** Clear all secondary memory allocations from the parser
*/
void ParseFinalize(void *p){
  yyParser *pParser = (yyParser*)p;
  while( pParser->yytos>pParser->yystack ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  if( pParser->yystack!=&pParser->yystk0 ) free(pParser->yystack);
#endif
}

#ifndef Parse_ENGINEALWAYSONSTACK
/* 
** Deallocate and destroy a parser.  Destructors are called for
** all stack elements before shutting the parser down.
**
** If the YYPARSEFREENEVERNULL macro exists (for example because it
** is defined in a %include section of the input grammar) then it is
** assumed that the input pointer is never NULL.
*/
void ParseFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
#ifndef YYPARSEFREENEVERNULL
  if( p==0 ) return;
#endif
  ParseFinalize(p);
  (*freeProc)(p);
}
#endif /* Parse_ENGINEALWAYSONSTACK */

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int ParseStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyhwm;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
*/
static unsigned int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yytos->stateno;
 
  if( stateno>=YY_MIN_REDUCE ) return stateno;
  assert( stateno <= YY_SHIFT_COUNT );
  do{
    i = yy_shift_ofst[stateno];
    assert( iLookAhead!=YYNOCODE );
    i += iLookAhead;
    if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        assert( yyFallback[iFallback]==0 ); /* Fallback loop must terminate */
        iLookAhead = iFallback;
        continue;
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD && iLookAhead>0
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead],
               yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
      return yy_default[stateno];
    }else{
      return yy_action[i];
    }
  }while(1);
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser){
   ParseARG_FETCH;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
/******** Begin %stack_overflow code ******************************************/
/******** End %stack_overflow code ********************************************/
   ParseARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Print tracing information for a SHIFT action
*/
#ifndef NDEBUG
static void yyTraceShift(yyParser *yypParser, int yyNewState){
  if( yyTraceFILE ){
    if( yyNewState<YYNSTATE ){
      fprintf(yyTraceFILE,"%sShift '%s', go to state %d\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major],
         yyNewState);
    }else{
      fprintf(yyTraceFILE,"%sShift '%s'\n",
         yyTracePrompt,yyTokenName[yypParser->yytos->major]);
    }
  }
}
#else
# define yyTraceShift(X,Y)
#endif

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  ParseTOKENTYPE yyMinor        /* The minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yytos++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
    yypParser->yyhwm++;
    assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack) );
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH] ){
    yypParser->yytos--;
    yyStackOverflow(yypParser);
    return;
  }
#else
  if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz] ){
    if( yyGrowStack(yypParser) ){
      yypParser->yytos--;
      yyStackOverflow(yypParser);
      return;
    }
  }
#endif
  if( yyNewState > YY_MAX_SHIFT ){
    yyNewState += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
  }
  yytos = yypParser->yytos;
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor.yy0 = yyMinor;
  yyTraceShift(yypParser, yyNewState);
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 181, 3 },
  { 168, 2 },
  { 168, 2 },
  { 168, 2 },
  { 168, 1 },
  { 168, 1 },
  { 168, 2 },
  { 168, 3 },
  { 169, 0 },
  { 169, 1 },
  { 169, 2 },
  { 172, 4 },
  { 173, 0 },
  { 173, 1 },
  { 173, 3 },
  { 169, 1 },
  { 170, 1 },
  { 170, 2 },
  { 168, 2 },
  { 168, 2 },
  { 171, 3 },
  { 171, 2 },
  { 171, 3 },
  { 171, 2 },
  { 171, 4 },
  { 171, 1 },
  { 171, 1 },
  { 171, 4 },
  { 175, 0 },
  { 175, 1 },
  { 175, 3 },
  { 181, 3 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 182, 0 },
  { 182, 1 },
  { 119, 0 },
  { 119, 7 },
  { 183, 2 },
  { 184, 2 },
  { 185, 2 },
  { 113, 4 },
  { 114, 1 },
  { 114, 3 },
  { 115, 3 },
  { 115, 1 },
  { 116, 3 },
  { 117, 1 },
  { 117, 1 },
  { 118, 4 },
  { 120, 4 },
  { 121, 1 },
  { 122, 6 },
  { 123, 3 },
  { 124, 4 },
  { 124, 4 },
  { 124, 2 },
  { 125, 1 },
  { 126, 3 },
  { 125, 2 },
  { 125, 1 },
  { 127, 6 },
  { 127, 8 },
  { 128, 1 },
  { 128, 2 },
  { 125, 7 },
  { 125, 8 },
  { 129, 1 },
  { 186, 0 },
  { 186, 3 },
  { 130, 2 },
  { 130, 3 },
  { 131, 1 },
  { 131, 3 },
  { 132, 2 },
  { 125, 7 },
  { 132, 3 },
  { 132, 4 },
  { 133, 0 },
  { 133, 1 },
  { 133, 1 },
  { 133, 3 },
  { 134, 1 },
  { 134, 2 },
  { 135, 2 },
  { 135, 3 },
  { 136, 0 },
  { 136, 7 },
  { 187, 1 },
  { 187, 2 },
  { 188, 0 },
  { 188, 1 },
  { 187, 1 },
  { 187, 2 },
  { 189, 0 },
  { 189, 1 },
  { 189, 2 },
  { 190, 0 },
  { 190, 1 },
  { 137, 2 },
  { 137, 2 },
  { 137, 1 },
  { 137, 1 },
  { 137, 1 },
  { 137, 2 },
  { 137, 2 },
  { 137, 2 },
  { 137, 1 },
  { 138, 1 },
  { 138, 2 },
  { 139, 4 },
  { 139, 5 },
  { 140, 7 },
  { 140, 8 },
  { 140, 13 },
  { 141, 1 },
  { 142, 2 },
  { 167, 1 },
  { 143, 2 },
  { 143, 4 },
  { 144, 1 },
  { 144, 3 },
  { 146, 1 },
  { 146, 2 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 148, 1 },
  { 148, 1 },
  { 149, 1 },
  { 149, 3 },
  { 149, 3 },
  { 149, 2 },
  { 156, 1 },
  { 156, 2 },
  { 156, 1 },
  { 156, 1 },
  { 156, 2 },
  { 156, 1 },
  { 156, 2 },
  { 156, 1 },
  { 156, 2 },
  { 156, 3 },
  { 150, 3 },
  { 150, 6 },
  { 155, 8 },
  { 151, 6 },
  { 152, 4 },
  { 152, 6 },
  { 157, 1 },
  { 157, 3 },
  { 153, 0 },
  { 153, 1 },
  { 154, 1 },
  { 154, 3 },
  { 191, 1 },
  { 191, 1 },
  { 162, 4 },
  { 162, 6 },
  { 162, 6 },
  { 160, 1 },
  { 160, 1 },
  { 161, 1 },
  { 161, 3 },
  { 160, 3 },
  { 159, 3 },
  { 163, 3 },
  { 164, 3 },
  { 165, 1 },
  { 165, 3 },
  { 166, 4 },
  { 158, 3 },
  { 176, 0 },
  { 176, 1 },
  { 177, 0 },
  { 177, 1 },
  { 178, 1 },
  { 178, 2 },
  { 179, 1 },
  { 180, 1 },
  { 180, 2 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  unsigned int yyruleno        /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  ParseARG_FETCH;
  yymsp = yypParser->yytos;
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    yysize = yyRuleInfo[yyruleno].nrhs;
    fprintf(yyTraceFILE, "%sReduce [%s], go to state %d.\n", yyTracePrompt,
      yyRuleName[yyruleno], yymsp[-yysize].stateno);
  }
#endif /* NDEBUG */

  /* Check that the stack is large enough to grow by a single entry
  ** if the RHS of the rule is empty.  This ensures that there is room
  ** enough on the stack to push the LHS value */
  if( yyRuleInfo[yyruleno].nrhs==0 ){
#ifdef YYTRACKMAXSTACKDEPTH
    if( (int)(yypParser->yytos - yypParser->yystack)>yypParser->yyhwm ){
      yypParser->yyhwm++;
      assert( yypParser->yyhwm == (int)(yypParser->yytos - yypParser->yystack));
    }
#endif
#if YYSTACKDEPTH>0 
    if( yypParser->yytos>=&yypParser->yystack[YYSTACKDEPTH-1] ){
      yyStackOverflow(yypParser);
      return;
    }
#else
    if( yypParser->yytos>=&yypParser->yystack[yypParser->yystksz-1] ){
      if( yyGrowStack(yypParser) ){
        yyStackOverflow(yypParser);
        return;
      }
      yymsp = yypParser->yytos;
    }
#endif
  }

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
/********** Begin reduce actions **********************************************/
        YYMINORTYPE yylhsminor;
      case 0: /* block ::= HASH cpp_exp EOL */
{  yy_destructor(yypParser,78,&yymsp[-2].minor);
#line 199 "src/parser_proc.y"
{
 P->cpp.exp = yymsp[-1].minor.yy274;
}
#line 2041 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[0].minor);
}
        break;
      case 1: /* cpp_exp ::= ERROR|WARNING QUOTED_STRING */
      case 2: /* cpp_exp ::= IFDEF NAME */ yytestcase(yyruleno==2);
      case 3: /* cpp_exp ::= IFNDEF NAME */ yytestcase(yyruleno==3);
      case 6: /* cpp_exp ::= UNDEF NAME */ yytestcase(yyruleno==6);
#line 202 "src/parser_proc.y"
{
 yylhsminor.yy274 = psi_cpp_exp_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy0);
 yylhsminor.yy274->token = yymsp[-1].minor.yy0;
}
#line 2054 "src/parser_proc.c"
  yymsp[-1].minor.yy274 = yylhsminor.yy274;
        break;
      case 4: /* cpp_exp ::= ENDIF */
      case 5: /* cpp_exp ::= ELSE */ yytestcase(yyruleno==5);
#line 214 "src/parser_proc.y"
{
 yylhsminor.yy274 = psi_cpp_exp_init(yymsp[0].minor.yy0->type, NULL);
 yylhsminor.yy274->token = yymsp[0].minor.yy0;
}
#line 2064 "src/parser_proc.c"
  yymsp[0].minor.yy274 = yylhsminor.yy274;
        break;
      case 7: /* cpp_exp ::= DEFINE NAME cpp_macro_decl */
#line 226 "src/parser_proc.y"
{
 yylhsminor.yy274 = psi_cpp_exp_init(yymsp[-2].minor.yy0->type, yymsp[0].minor.yy134);
 yylhsminor.yy274->token = yymsp[-2].minor.yy0;
 yymsp[0].minor.yy134->token = yymsp[-1].minor.yy0;
}
#line 2074 "src/parser_proc.c"
  yymsp[-2].minor.yy274 = yylhsminor.yy274;
        break;
      case 8: /* cpp_macro_decl ::= */
#line 231 "src/parser_proc.y"
{
 yymsp[1].minor.yy134 = psi_cpp_macro_decl_init(NULL, NULL, NULL);
}
#line 2082 "src/parser_proc.c"
        break;
      case 9: /* cpp_macro_decl ::= cpp_macro_sig */
#line 234 "src/parser_proc.y"
{
 yylhsminor.yy134 = psi_cpp_macro_decl_init(yymsp[0].minor.yy179, NULL, NULL);
}
#line 2089 "src/parser_proc.c"
  yymsp[0].minor.yy134 = yylhsminor.yy134;
        break;
      case 10: /* cpp_macro_decl ::= cpp_macro_sig cpp_macro_decl_tokens */
#line 237 "src/parser_proc.y"
{
 yylhsminor.yy134 = psi_cpp_macro_decl_init(yymsp[-1].minor.yy179, yymsp[0].minor.yy179, NULL);
}
#line 2097 "src/parser_proc.c"
  yymsp[-1].minor.yy134 = yylhsminor.yy134;
        break;
      case 11: /* cpp_macro_sig ::= NO_WHITESPACE LPAREN cpp_macro_sig_args RPAREN */
{  yy_destructor(yypParser,85,&yymsp[-3].minor);
#line 240 "src/parser_proc.y"
{
 yymsp[-3].minor.yy179 = yymsp[-1].minor.yy179;
}
#line 2106 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
}
        break;
      case 12: /* cpp_macro_sig_args ::= */
      case 28: /* cpp_macro_call_args ::= */ yytestcase(yyruleno==28);
      case 83: /* decl_args ::= */ yytestcase(yyruleno==83);
#line 243 "src/parser_proc.y"
{
 yymsp[1].minor.yy179 = NULL;
}
#line 2118 "src/parser_proc.c"
        break;
      case 13: /* cpp_macro_sig_args ::= NAME */
      case 16: /* cpp_macro_decl_tokens ::= ANY */ yytestcase(yyruleno==16);
#line 246 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((void (*)(void *)) psi_token_free), &yymsp[0].minor.yy0);
}
#line 2126 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 14: /* cpp_macro_sig_args ::= cpp_macro_sig_args COMMA NAME */
#line 249 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy0);
}
#line 2134 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 15: /* cpp_macro_decl ::= cpp_macro_decl_tokens */
#line 252 "src/parser_proc.y"
{
 yylhsminor.yy134 = psi_cpp_macro_decl_init(NULL, yymsp[0].minor.yy179, NULL);
}
#line 2143 "src/parser_proc.c"
  yymsp[0].minor.yy134 = yylhsminor.yy134;
        break;
      case 17: /* cpp_macro_decl_tokens ::= cpp_macro_decl_tokens ANY */
#line 258 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-1].minor.yy179, &yymsp[0].minor.yy0);
}
#line 2151 "src/parser_proc.c"
  yymsp[-1].minor.yy179 = yylhsminor.yy179;
        break;
      case 18: /* cpp_exp ::= IF cpp_macro_exp */
      case 19: /* cpp_exp ::= ELIF cpp_macro_exp */ yytestcase(yyruleno==19);
#line 261 "src/parser_proc.y"
{
 yylhsminor.yy274 = psi_cpp_exp_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy207);
 yylhsminor.yy274->token = yymsp[-1].minor.yy0;
}
#line 2161 "src/parser_proc.c"
  yymsp[-1].minor.yy274 = yylhsminor.yy274;
        break;
      case 20: /* cpp_macro_exp ::= LPAREN cpp_macro_exp RPAREN */
#line 269 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_unary(yymsp[-2].minor.yy0->type, yymsp[-1].minor.yy207);
 yylhsminor.yy207->token = yymsp[-2].minor.yy0;
}
#line 2170 "src/parser_proc.c"
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-2].minor.yy207 = yylhsminor.yy207;
        break;
      case 21: /* cpp_macro_exp ::= TILDE|NOT|PLUS|MINUS cpp_macro_exp */
      case 139: /* num_exp ::= TILDE|NOT|PLUS|MINUS num_exp */ yytestcase(yyruleno==139);
#line 273 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_unary(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy207);
 yylhsminor.yy207->token = yymsp[-1].minor.yy0;
}
#line 2181 "src/parser_proc.c"
  yymsp[-1].minor.yy207 = yylhsminor.yy207;
        break;
      case 22: /* cpp_macro_exp ::= cpp_macro_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE cpp_macro_exp */
      case 138: /* num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp */ yytestcase(yyruleno==138);
#line 277 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_binary(yymsp[-1].minor.yy0->type, yymsp[-2].minor.yy207, yymsp[0].minor.yy207);
 yylhsminor.yy207->token = yymsp[-1].minor.yy0;
}
#line 2191 "src/parser_proc.c"
  yymsp[-2].minor.yy207 = yylhsminor.yy207;
        break;
      case 23: /* cpp_macro_exp ::= DEFINED NAME */
{  yy_destructor(yypParser,91,&yymsp[-1].minor);
#line 281 "src/parser_proc.y"
{
 {
  uint8_t exists = zend_hash_str_exists(&P->cpp.defs, yymsp[0].minor.yy0->text, yymsp[0].minor.yy0->size);
  yymsp[-1].minor.yy207 = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists));
  yymsp[-1].minor.yy207->token = yymsp[0].minor.yy0;
 }
}
#line 2204 "src/parser_proc.c"
}
        break;
      case 24: /* cpp_macro_exp ::= DEFINED LPAREN NAME RPAREN */
{  yy_destructor(yypParser,91,&yymsp[-3].minor);
#line 288 "src/parser_proc.y"
{
 {
  uint8_t exists = zend_hash_str_exists(&P->cpp.defs, yymsp[-1].minor.yy0->text, yymsp[-1].minor.yy0->size);
  yymsp[-3].minor.yy207 = psi_num_exp_init_num(psi_number_init(PSI_T_UINT8, &exists));
  yymsp[-3].minor.yy207->token = yymsp[-1].minor.yy0;
 }
}
#line 2217 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
}
        break;
      case 25: /* cpp_macro_exp ::= NUMBER|NSNAME */
#line 295 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_num(psi_number_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text));
 yylhsminor.yy207->token = yymsp[0].minor.yy0;
 yylhsminor.yy207->data.n->token = psi_token_copy(yymsp[0].minor.yy0);
}
#line 2229 "src/parser_proc.c"
  yymsp[0].minor.yy207 = yylhsminor.yy207;
        break;
      case 26: /* cpp_macro_exp ::= NAME */
#line 300 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_num(psi_number_init(PSI_T_DEFINE, yymsp[0].minor.yy0->text));
 yylhsminor.yy207->token = yymsp[0].minor.yy0;
 yylhsminor.yy207->data.n->token = psi_token_copy(yymsp[0].minor.yy0);
}
#line 2239 "src/parser_proc.c"
  yymsp[0].minor.yy207 = yylhsminor.yy207;
        break;
      case 27: /* cpp_macro_exp ::= NAME LPAREN cpp_macro_call_args RPAREN */
#line 305 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_num(psi_number_init(PSI_T_FUNCTION,
   psi_cpp_macro_call_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy179)));
 yylhsminor.yy207->token = yymsp[-3].minor.yy0;
}
#line 2249 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-3].minor.yy207 = yylhsminor.yy207;
        break;
      case 29: /* cpp_macro_call_args ::= cpp_macro_exp */
#line 313 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((void (*)(void *)) psi_num_exp_free), &yymsp[0].minor.yy207);
}
#line 2259 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 30: /* cpp_macro_call_args ::= cpp_macro_call_args COMMA cpp_macro_exp */
#line 316 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy207);
}
#line 2267 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 31: /* block ::= LIB QUOTED_STRING EOS */
#line 319 "src/parser_proc.y"
{
 if (P->file.ln) {
  P->error(PSI_DATA(P), yymsp[-2].minor.yy0, PSI_WARNING, "Extra 'lib %s' statement has no effect", yymsp[-1].minor.yy0->text);
 } else {
  P->file.ln = strndup(yymsp[-1].minor.yy0->text + 1, yymsp[-1].minor.yy0->size - 2);
 }
 free(yymsp[-1].minor.yy0);
 free(yymsp[-2].minor.yy0);
}
#line 2282 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
        break;
      case 32: /* block ::= decl */
#line 328 "src/parser_proc.y"
{
 if (!P->decls) {
  P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
 }
 P->decls = psi_plist_add(P->decls, &yymsp[0].minor.yy303);
}
#line 2293 "src/parser_proc.c"
        break;
      case 33: /* block ::= impl */
#line 334 "src/parser_proc.y"
{
 if (!P->impls) {
  P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
 }
 P->impls = psi_plist_add(P->impls, &yymsp[0].minor.yy49);
}
#line 2303 "src/parser_proc.c"
        break;
      case 34: /* block ::= decl_typedef */
#line 340 "src/parser_proc.y"
{
 if (!P->types) {
  P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
 }
 P->types = psi_plist_add(P->types, &yymsp[0].minor.yy320);
 switch (yymsp[0].minor.yy320->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[0].minor.yy320->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy320->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[0].minor.yy320->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy320->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[0].minor.yy320->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy320->type->real.enm);
  }
  break;
 }
}
#line 2339 "src/parser_proc.c"
        break;
      case 35: /* block ::= constant */
#line 372 "src/parser_proc.y"
{
 if (!P->consts) {
  P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
 }
 P->consts = psi_plist_add(P->consts, &yymsp[0].minor.yy38);
}
#line 2349 "src/parser_proc.c"
        break;
      case 36: /* block ::= decl_struct */
#line 378 "src/parser_proc.y"
{
 if (!P->structs) {
  P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
 }
 P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy324);
}
#line 2359 "src/parser_proc.c"
        break;
      case 37: /* block ::= decl_union */
#line 384 "src/parser_proc.y"
{
 if (!P->unions) {
  P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
 }
 P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy15);
}
#line 2369 "src/parser_proc.c"
        break;
      case 38: /* block ::= decl_enum */
#line 390 "src/parser_proc.y"
{
 if (!P->enums) {
  P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
 }
 P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy323);
}
#line 2379 "src/parser_proc.c"
        break;
      case 39: /* optional_name ::= */
      case 73: /* decl_var_array_size ::= */ yytestcase(yyruleno==73);
      case 95: /* decl_scalar_type_short ::= */ yytestcase(yyruleno==95);
      case 99: /* decl_scalar_type_long ::= */ yytestcase(yyruleno==99);
      case 102: /* decl_scalar_type_long_long ::= */ yytestcase(yyruleno==102);
#line 396 "src/parser_proc.y"
{
 yymsp[1].minor.yy0 = NULL;
}
#line 2390 "src/parser_proc.c"
        break;
      case 40: /* optional_name ::= NAME */
      case 93: /* decl_scalar_type ::= CHAR */ yytestcase(yyruleno==93);
      case 96: /* decl_scalar_type_short ::= INT */ yytestcase(yyruleno==96);
      case 97: /* decl_scalar_type ::= INT */ yytestcase(yyruleno==97);
      case 100: /* decl_scalar_type_long ::= DOUBLE */ yytestcase(yyruleno==100);
      case 103: /* decl_scalar_type_long_long ::= INT */ yytestcase(yyruleno==103);
      case 162: /* callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT */ yytestcase(yyruleno==162);
      case 163: /* callback_rval ::= VOID */ yytestcase(yyruleno==163);
#line 399 "src/parser_proc.y"
{
 yylhsminor.yy0 = yymsp[0].minor.yy0;
}
#line 2404 "src/parser_proc.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 41: /* align_and_size ::= */
#line 402 "src/parser_proc.y"
{
 yymsp[1].minor.yy239.pos = 0;
 yymsp[1].minor.yy239.len = 0;
}
#line 2413 "src/parser_proc.c"
        break;
      case 42: /* align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,92,&yymsp[-6].minor);
#line 406 "src/parser_proc.y"
{
 yymsp[-6].minor.yy239.pos = atol(yymsp[-3].minor.yy0->text);
 yymsp[-6].minor.yy239.len = atol(yymsp[-1].minor.yy0->text);
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2424 "src/parser_proc.c"
  yy_destructor(yypParser,92,&yymsp[-5].minor);
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
}
        break;
      case 43: /* enum_name ::= ENUM optional_name */
      case 44: /* struct_name ::= STRUCT optional_name */ yytestcase(yyruleno==44);
      case 45: /* union_name ::= UNION optional_name */ yytestcase(yyruleno==45);
#line 412 "src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = yymsp[0].minor.yy0;
  free(yymsp[-1].minor.yy0);
 } else {
  char digest[17];
  psi_token_hash(yymsp[-1].minor.yy0, digest);
  yylhsminor.yy0 = psi_token_append("@", yymsp[-1].minor.yy0, 1, digest);
 }
}
#line 2445 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 46: /* decl_enum ::= enum_name LBRACE decl_enum_items RBRACE */
#line 442 "src/parser_proc.y"
{
 yylhsminor.yy323 = psi_decl_enum_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy179);
 yylhsminor.yy323->token = yymsp[-3].minor.yy0;
}
#line 2454 "src/parser_proc.c"
  yy_destructor(yypParser,96,&yymsp[-2].minor);
  yy_destructor(yypParser,97,&yymsp[0].minor);
  yymsp[-3].minor.yy323 = yylhsminor.yy323;
        break;
      case 47: /* decl_enum_items ::= decl_enum_item */
#line 446 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
   &yymsp[0].minor.yy169);
}
#line 2465 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 48: /* decl_enum_items ::= decl_enum_items COMMA decl_enum_item */
#line 450 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy169);
}
#line 2473 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 49: /* decl_enum_item ::= NAME EQUALS num_exp */
#line 453 "src/parser_proc.y"
{
 yylhsminor.yy169 = psi_decl_enum_item_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy207);
 yylhsminor.yy169->token = yymsp[-2].minor.yy0;
}
#line 2483 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-1].minor);
  yymsp[-2].minor.yy169 = yylhsminor.yy169;
        break;
      case 50: /* decl_enum_item ::= NAME */
#line 457 "src/parser_proc.y"
{
 yylhsminor.yy169 = psi_decl_enum_item_init(yymsp[0].minor.yy0->text, NULL);
 yylhsminor.yy169->token = yymsp[0].minor.yy0;
}
#line 2493 "src/parser_proc.c"
  yymsp[0].minor.yy169 = yylhsminor.yy169;
        break;
      case 51: /* decl_struct_args_block ::= LBRACE struct_args RBRACE */
{  yy_destructor(yypParser,96,&yymsp[-2].minor);
#line 461 "src/parser_proc.y"
{
 yymsp[-2].minor.yy179 = yymsp[-1].minor.yy179;
}
#line 2502 "src/parser_proc.c"
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 52: /* decl_struct_args ::= decl_struct_args_block */
#line 464 "src/parser_proc.y"
{
 yylhsminor.yy179 = yymsp[0].minor.yy179;
}
#line 2511 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 53: /* decl_struct_args ::= EOS */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 467 "src/parser_proc.y"
{
 yymsp[0].minor.yy179 = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}
#line 2520 "src/parser_proc.c"
}
        break;
      case 54: /* decl_struct ::= STRUCT NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,94,&yymsp[-3].minor);
#line 470 "src/parser_proc.y"
{
 yymsp[-3].minor.yy324 = psi_decl_struct_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy179);
 yymsp[-3].minor.yy324->align = yymsp[-1].minor.yy239.pos;
 yymsp[-3].minor.yy324->size = yymsp[-1].minor.yy239.len;
 yymsp[-3].minor.yy324->token = yymsp[-2].minor.yy0;
}
#line 2532 "src/parser_proc.c"
}
        break;
      case 55: /* decl_union ::= UNION NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,95,&yymsp[-3].minor);
#line 476 "src/parser_proc.y"
{
 yymsp[-3].minor.yy15 = psi_decl_union_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy179);
 yymsp[-3].minor.yy15->align = yymsp[-1].minor.yy239.pos;
 yymsp[-3].minor.yy15->size = yymsp[-1].minor.yy239.len;
 yymsp[-3].minor.yy15->token = yymsp[-2].minor.yy0;
}
#line 2544 "src/parser_proc.c"
}
        break;
      case 56: /* const_type ::= BOOL|INT|FLOAT|STRING */
#line 482 "src/parser_proc.y"
{
 yylhsminor.yy351 = psi_const_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2553 "src/parser_proc.c"
  yymsp[0].minor.yy351 = yylhsminor.yy351;
        break;
      case 57: /* constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS */
{  yy_destructor(yypParser,99,&yymsp[-5].minor);
#line 486 "src/parser_proc.y"
{
 yymsp[-5].minor.yy38 = psi_const_init(yymsp[-4].minor.yy351, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy145);
 yymsp[-5].minor.yy38->token = yymsp[-3].minor.yy0;
}
#line 2563 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
}
        break;
      case 58: /* decl_typedef ::= TYPEDEF decl_typedef_body EOS */
#line 490 "src/parser_proc.y"
{
 yylhsminor.yy320 = yymsp[-1].minor.yy320;
 yylhsminor.yy320->token = yymsp[-2].minor.yy0;
}
#line 2574 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy320 = yylhsminor.yy320;
        break;
      case 59: /* decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var */
#line 494 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy271);
 yylhsminor.yy320->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy320->type->real.strct = psi_decl_struct_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy179);
 yylhsminor.yy320->type->real.strct->token = yymsp[-3].minor.yy0;
 yylhsminor.yy320->type->real.strct->align = yymsp[-2].minor.yy239.pos;
 yylhsminor.yy320->type->real.strct->size = yymsp[-2].minor.yy239.len;
}
#line 2588 "src/parser_proc.c"
  yymsp[-3].minor.yy320 = yylhsminor.yy320;
        break;
      case 60: /* decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var */
#line 502 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy271);
 yylhsminor.yy320->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy320->type->real.unn = psi_decl_union_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy179);
 yylhsminor.yy320->type->real.unn->token = yymsp[-3].minor.yy0;
 yylhsminor.yy320->type->real.unn->align = yymsp[-2].minor.yy239.pos;
 yylhsminor.yy320->type->real.unn->size = yymsp[-2].minor.yy239.len;
}
#line 2601 "src/parser_proc.c"
  yymsp[-3].minor.yy320 = yylhsminor.yy320;
        break;
      case 61: /* decl_typedef_body_ex ::= decl_enum NAME */
#line 510 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, yymsp[-1].minor.yy323->name), psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0));
 yylhsminor.yy320->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy320->type->token = psi_token_copy(yymsp[-1].minor.yy323->token);
 yylhsminor.yy320->type->real.enm = yymsp[-1].minor.yy323;
}
#line 2612 "src/parser_proc.c"
  yymsp[-1].minor.yy320 = yylhsminor.yy320;
        break;
      case 62: /* decl_typedef_body ::= decl_typedef_body_ex */
      case 65: /* decl_typedef_body ::= decl_arg */ yytestcase(yyruleno==65);
      case 68: /* decl_func ::= decl_arg */ yytestcase(yyruleno==68);
#line 516 "src/parser_proc.y"
{
 yylhsminor.yy320 = yymsp[0].minor.yy320;
}
#line 2622 "src/parser_proc.c"
  yymsp[0].minor.yy320 = yylhsminor.yy320;
        break;
      case 63: /* decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN */
{  yy_destructor(yypParser,86,&yymsp[-2].minor);
#line 519 "src/parser_proc.y"
{
 yymsp[-2].minor.yy179 = yymsp[-1].minor.yy179;
}
#line 2631 "src/parser_proc.c"
  yy_destructor(yypParser,87,&yymsp[0].minor);
}
        break;
      case 64: /* decl_typedef_body ::= decl_func decl_typedef_body_fn_args */
#line 522 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, yymsp[-1].minor.yy320->var->name), psi_decl_var_copy(yymsp[-1].minor.yy320->var));
 yylhsminor.yy320->type->token = psi_token_copy(yymsp[-1].minor.yy320->token);
 yylhsminor.yy320->type->real.func = psi_decl_init(psi_decl_abi_init("default"), yymsp[-1].minor.yy320, yymsp[0].minor.yy179);
}
#line 2642 "src/parser_proc.c"
  yymsp[-1].minor.yy320 = yylhsminor.yy320;
        break;
      case 66: /* decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS */
#line 530 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_decl_init(yymsp[-5].minor.yy26, yymsp[-4].minor.yy320, yymsp[-2].minor.yy179);
}
#line 2650 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-3].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy303 = yylhsminor.yy303;
        break;
      case 67: /* decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS */
#line 533 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_decl_init(yymsp[-7].minor.yy26, yymsp[-6].minor.yy320, yymsp[-4].minor.yy179);
 yylhsminor.yy303->varargs = 1;
}
#line 2662 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-5].minor);
  yy_destructor(yypParser,88,&yymsp[-3].minor);
  yy_destructor(yypParser,101,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-7].minor.yy303 = yylhsminor.yy303;
        break;
      case 69: /* decl_func ::= VOID NAME */
#line 540 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[-1].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0)
 );
 yylhsminor.yy320->type->token = yymsp[-1].minor.yy0;
 yylhsminor.yy320->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy320->token = yymsp[0].minor.yy0;
}
#line 2681 "src/parser_proc.c"
  yymsp[-1].minor.yy320 = yylhsminor.yy320;
        break;
      case 70: /* decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 549 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy382, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy320->var->pointer_level = yymsp[-3].minor.yy382;
 yylhsminor.yy320->type->token = psi_token_copy(func_->token);
 yylhsminor.yy320->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy179);
}
#line 2702 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yymsp[-6].minor.yy320 = yylhsminor.yy320;
        break;
      case 71: /* decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
{  yy_destructor(yypParser,99,&yymsp[-7].minor);
#line 565 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy382, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yymsp[-7].minor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yymsp[-7].minor.yy320->var->pointer_level = yymsp[-3].minor.yy382;
 yymsp[-7].minor.yy320->type->token = psi_token_copy(func_->token);
 yymsp[-7].minor.yy320->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy179);
}
#line 2726 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
}
        break;
      case 72: /* decl_abi ::= NAME */
#line 581 "src/parser_proc.y"
{
 yylhsminor.yy26 = psi_decl_abi_init(yymsp[0].minor.yy0->text);
 yylhsminor.yy26->token = yymsp[0].minor.yy0;
}
#line 2737 "src/parser_proc.c"
  yymsp[0].minor.yy26 = yylhsminor.yy26;
        break;
      case 74: /* decl_var_array_size ::= LBRACKET NUMBER RBRACKET */
{  yy_destructor(yypParser,102,&yymsp[-2].minor);
#line 588 "src/parser_proc.y"
{
 yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
}
#line 2746 "src/parser_proc.c"
  yy_destructor(yypParser,103,&yymsp[0].minor);
}
        break;
      case 75: /* decl_var ::= NAME decl_var_array_size */
#line 591 "src/parser_proc.y"
{
 yylhsminor.yy271 = psi_decl_var_init(yymsp[-1].minor.yy0->text, 0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy271->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2759 "src/parser_proc.c"
  yymsp[-1].minor.yy271 = yylhsminor.yy271;
        break;
      case 76: /* decl_var ::= pointers NAME decl_var_array_size */
#line 598 "src/parser_proc.y"
{
 yylhsminor.yy271 = psi_decl_var_init(yymsp[-1].minor.yy0->text, yymsp[-2].minor.yy382+!!yymsp[0].minor.yy0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy271->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2771 "src/parser_proc.c"
  yymsp[-2].minor.yy271 = yylhsminor.yy271;
        break;
      case 77: /* decl_vars ::= decl_var */
#line 605 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
   &yymsp[0].minor.yy271);
}
#line 2780 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 78: /* decl_vars ::= decl_vars COMMA decl_var */
#line 609 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy271);
}
#line 2788 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 79: /* decl_arg ::= const_decl_type decl_var */
#line 612 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(yymsp[-1].minor.yy172, yymsp[0].minor.yy271);
}
#line 2797 "src/parser_proc.c"
  yymsp[-1].minor.yy320 = yylhsminor.yy320;
        break;
      case 80: /* decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 615 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  yymsp[-6].minor.yy172,
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy382, 0)
 );
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy320->var->pointer_level = yymsp[-3].minor.yy382;
 yylhsminor.yy320->type->token = psi_token_copy(func_->token);
 yylhsminor.yy320->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy179);
}
#line 2817 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yymsp[-6].minor.yy320 = yylhsminor.yy320;
        break;
      case 81: /* decl_arg ::= VOID pointers NAME */
#line 630 "src/parser_proc.y"
{
 yylhsminor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy382, 0)
 );
 yylhsminor.yy320->type->token = yymsp[-2].minor.yy0;
 yylhsminor.yy320->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy320->token = yymsp[0].minor.yy0;
}
#line 2833 "src/parser_proc.c"
  yymsp[-2].minor.yy320 = yylhsminor.yy320;
        break;
      case 82: /* decl_arg ::= CONST VOID pointers NAME */
{  yy_destructor(yypParser,99,&yymsp[-3].minor);
#line 639 "src/parser_proc.y"
{
 yymsp[-3].minor.yy320 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy382, 0)
 );
 yymsp[-3].minor.yy320->type->token = yymsp[-2].minor.yy0;
 yymsp[-3].minor.yy320->var->token = yymsp[0].minor.yy0;
 yymsp[-3].minor.yy320->token = yymsp[0].minor.yy0;
}
#line 2848 "src/parser_proc.c"
}
        break;
      case 84: /* decl_args ::= VOID */
{  yy_destructor(yypParser,57,&yymsp[0].minor);
#line 651 "src/parser_proc.y"
{
 yymsp[0].minor.yy179 = NULL;
}
#line 2857 "src/parser_proc.c"
}
        break;
      case 85: /* decl_args ::= decl_arg */
      case 87: /* struct_args ::= struct_arg */ yytestcase(yyruleno==87);
#line 654 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &yymsp[0].minor.yy320);
}
#line 2867 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 86: /* decl_args ::= decl_args COMMA decl_arg */
#line 658 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy320);
}
#line 2875 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 88: /* struct_args ::= struct_args struct_arg */
#line 665 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-1].minor.yy179, &yymsp[0].minor.yy320);
}
#line 2884 "src/parser_proc.c"
  yymsp[-1].minor.yy179 = yylhsminor.yy179;
        break;
      case 89: /* struct_arg ::= decl_typedef_body_ex EOS */
#line 668 "src/parser_proc.y"
{
 yylhsminor.yy320 = yymsp[-1].minor.yy320;
 switch (yymsp[-1].minor.yy320->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[-1].minor.yy320->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[-1].minor.yy320->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[-1].minor.yy320->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[-1].minor.yy320->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[-1].minor.yy320->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[-1].minor.yy320->type->real.enm);
  }
  break;
 }
}
#line 2918 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-1].minor.yy320 = yylhsminor.yy320;
        break;
      case 90: /* struct_arg ::= decl_arg decl_layout EOS */
#line 697 "src/parser_proc.y"
{
 yymsp[-2].minor.yy320->layout = yymsp[-1].minor.yy369;
 yylhsminor.yy320 = yymsp[-2].minor.yy320;
}
#line 2928 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy320 = yylhsminor.yy320;
        break;
      case 91: /* decl_layout ::= */
#line 701 "src/parser_proc.y"
{
 yymsp[1].minor.yy369 = NULL;
}
#line 2937 "src/parser_proc.c"
        break;
      case 92: /* decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,92,&yymsp[-6].minor);
#line 704 "src/parser_proc.y"
{
 yymsp[-6].minor.yy369 = psi_layout_init(atol(yymsp[-3].minor.yy0->text), atol(yymsp[-1].minor.yy0->text));
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2947 "src/parser_proc.c"
  yy_destructor(yypParser,92,&yymsp[-5].minor);
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
}
        break;
      case 94: /* decl_scalar_type ::= SHORT decl_scalar_type_short */
      case 98: /* decl_scalar_type ::= LONG decl_scalar_type_long */ yytestcase(yyruleno==98);
      case 101: /* decl_scalar_type_long ::= LONG decl_scalar_type_long_long */ yytestcase(yyruleno==101);
#line 712 "src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = psi_token_cat(" ", 2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
  free(yymsp[-1].minor.yy0);
  free(yymsp[0].minor.yy0);
 } else {
  yylhsminor.yy0 = yymsp[-1].minor.yy0;
 }
}
#line 2967 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 104: /* decl_type ::= UNSIGNED decl_scalar_type */
      case 105: /* decl_type ::= SIGNED decl_scalar_type */ yytestcase(yyruleno==105);
#line 760 "src/parser_proc.y"
{
 struct psi_token *T = psi_token_cat(" ", 2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
 yylhsminor.yy172 = psi_decl_type_init(T->type, T->text);
 yylhsminor.yy172->token = T;
 free(yymsp[-1].minor.yy0);
 free(yymsp[0].minor.yy0);
}
#line 2980 "src/parser_proc.c"
  yymsp[-1].minor.yy172 = yylhsminor.yy172;
        break;
      case 106: /* decl_type ::= UNSIGNED */
      case 107: /* decl_type ::= SIGNED */ yytestcase(yyruleno==107);
#line 774 "src/parser_proc.y"
{
 yylhsminor.yy172 = psi_decl_type_init(PSI_T_NAME, yymsp[0].minor.yy0->text);
 yylhsminor.yy172->token = yymsp[0].minor.yy0;
}
#line 2990 "src/parser_proc.c"
  yymsp[0].minor.yy172 = yylhsminor.yy172;
        break;
      case 108: /* decl_type ::= decl_scalar_type */
      case 112: /* decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME */ yytestcase(yyruleno==112);
#line 782 "src/parser_proc.y"
{
 yylhsminor.yy172 = psi_decl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy172->token = yymsp[0].minor.yy0;
}
#line 3000 "src/parser_proc.c"
  yymsp[0].minor.yy172 = yylhsminor.yy172;
        break;
      case 109: /* decl_type ::= STRUCT NAME */
      case 110: /* decl_type ::= UNION NAME */ yytestcase(yyruleno==110);
      case 111: /* decl_type ::= ENUM NAME */ yytestcase(yyruleno==111);
#line 786 "src/parser_proc.y"
{
 yylhsminor.yy172 = psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy172->token = yymsp[0].minor.yy0;
 free(yymsp[-1].minor.yy0);
}
#line 3012 "src/parser_proc.c"
  yymsp[-1].minor.yy172 = yylhsminor.yy172;
        break;
      case 113: /* const_decl_type ::= decl_type */
#line 805 "src/parser_proc.y"
{
 yylhsminor.yy172 = yymsp[0].minor.yy172;
}
#line 3020 "src/parser_proc.c"
  yymsp[0].minor.yy172 = yylhsminor.yy172;
        break;
      case 114: /* const_decl_type ::= CONST decl_type */
{  yy_destructor(yypParser,99,&yymsp[-1].minor);
#line 808 "src/parser_proc.y"
{
 yymsp[-1].minor.yy172 = yymsp[0].minor.yy172;
}
#line 3029 "src/parser_proc.c"
}
        break;
      case 115: /* impl ::= impl_func LBRACE impl_stmts RBRACE */
#line 811 "src/parser_proc.y"
{
 yylhsminor.yy49 = psi_impl_init(yymsp[-3].minor.yy56, yymsp[-1].minor.yy179);
}
#line 3037 "src/parser_proc.c"
  yy_destructor(yypParser,96,&yymsp[-2].minor);
  yy_destructor(yypParser,97,&yymsp[0].minor);
  yymsp[-3].minor.yy49 = yylhsminor.yy49;
        break;
      case 116: /* impl ::= STATIC impl_func LBRACE impl_stmts RBRACE */
{  yy_destructor(yypParser,109,&yymsp[-4].minor);
#line 814 "src/parser_proc.y"
{
 yymsp[-3].minor.yy56->static_memory = 1;
 yymsp[-4].minor.yy49 = psi_impl_init(yymsp[-3].minor.yy56, yymsp[-1].minor.yy179);
}
#line 3049 "src/parser_proc.c"
  yy_destructor(yypParser,96,&yymsp[-2].minor);
  yy_destructor(yypParser,97,&yymsp[0].minor);
}
        break;
      case 117: /* impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type */
{  yy_destructor(yypParser,110,&yymsp[-6].minor);
#line 818 "src/parser_proc.y"
{
 yymsp[-6].minor.yy56 = psi_impl_func_init(yymsp[-4].minor.yy0->text, NULL, yymsp[0].minor.yy246);
 yymsp[-6].minor.yy56->token = yymsp[-4].minor.yy0;
 yymsp[-6].minor.yy56->return_reference = yymsp[-5].minor.yy89;
}
#line 3062 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-3].minor);
  yy_destructor(yypParser,87,&yymsp[-2].minor);
  yy_destructor(yypParser,92,&yymsp[-1].minor);
}
        break;
      case 118: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type */
{  yy_destructor(yypParser,110,&yymsp[-7].minor);
#line 823 "src/parser_proc.y"
{
 yymsp[-7].minor.yy56 = psi_impl_func_init(yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy179, yymsp[0].minor.yy246);
 yymsp[-7].minor.yy56->token = yymsp[-5].minor.yy0;
 yymsp[-7].minor.yy56->return_reference = yymsp[-6].minor.yy89;
}
#line 3076 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,87,&yymsp[-2].minor);
  yy_destructor(yypParser,92,&yymsp[-1].minor);
}
        break;
      case 119: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type */
{  yy_destructor(yypParser,110,&yymsp[-12].minor);
#line 828 "src/parser_proc.y"
{
 yymsp[-12].minor.yy56 = psi_impl_func_init(yymsp[-10].minor.yy0->text, yymsp[-8].minor.yy179, yymsp[0].minor.yy246);
 yymsp[-12].minor.yy56->token = yymsp[-10].minor.yy0;
 yymsp[-12].minor.yy56->return_reference = yymsp[-11].minor.yy89;
 yymsp[-12].minor.yy56->vararg = psi_impl_arg_init(yymsp[-6].minor.yy246, psi_impl_var_init(yymsp[-3].minor.yy0->text, yymsp[-5].minor.yy89), NULL);
 free(yymsp[-3].minor.yy0);
}
#line 3092 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-9].minor);
  yy_destructor(yypParser,88,&yymsp[-7].minor);
  yy_destructor(yypParser,101,&yymsp[-4].minor);
  yy_destructor(yypParser,87,&yymsp[-2].minor);
  yy_destructor(yypParser,92,&yymsp[-1].minor);
}
        break;
      case 120: /* impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING */
#line 835 "src/parser_proc.y"
{
 yylhsminor.yy145 = psi_impl_def_val_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy145->token = yymsp[0].minor.yy0;
}
#line 3106 "src/parser_proc.c"
  yymsp[0].minor.yy145 = yylhsminor.yy145;
        break;
      case 121: /* impl_var ::= reference DOLLAR_NAME */
#line 839 "src/parser_proc.y"
{
 yylhsminor.yy370 = psi_impl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy89);
 yylhsminor.yy370->token = yymsp[0].minor.yy0;
}
#line 3115 "src/parser_proc.c"
  yymsp[-1].minor.yy370 = yylhsminor.yy370;
        break;
      case 122: /* impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE */
#line 843 "src/parser_proc.y"
{
 yylhsminor.yy246 = psi_impl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 3124 "src/parser_proc.c"
  yymsp[0].minor.yy246 = yylhsminor.yy246;
        break;
      case 123: /* impl_arg ::= impl_type impl_var */
#line 847 "src/parser_proc.y"
{
 yylhsminor.yy34 = psi_impl_arg_init(yymsp[-1].minor.yy246, yymsp[0].minor.yy370, NULL);
}
#line 3132 "src/parser_proc.c"
  yymsp[-1].minor.yy34 = yylhsminor.yy34;
        break;
      case 124: /* impl_arg ::= impl_type impl_var EQUALS impl_def_val */
#line 850 "src/parser_proc.y"
{
 yylhsminor.yy34 = psi_impl_arg_init(yymsp[-3].minor.yy246, yymsp[-2].minor.yy370, yymsp[0].minor.yy145);
}
#line 3140 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-1].minor);
  yymsp[-3].minor.yy34 = yylhsminor.yy34;
        break;
      case 125: /* impl_args ::= impl_arg */
#line 853 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
   &yymsp[0].minor.yy34);
}
#line 3150 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 126: /* impl_args ::= impl_args COMMA impl_arg */
#line 857 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy34);
}
#line 3158 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 127: /* impl_stmts ::= impl_stmt */
#line 860 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
   &yymsp[0].minor.yy238);
}
#line 3168 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 128: /* impl_stmts ::= impl_stmts impl_stmt */
#line 864 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-1].minor.yy179, &yymsp[0].minor.yy238);
}
#line 3176 "src/parser_proc.c"
  yymsp[-1].minor.yy179 = yylhsminor.yy179;
        break;
      case 129: /* impl_stmt ::= return_stmt */
#line 867 "src/parser_proc.y"
{
 yylhsminor.yy238 = (struct psi_token**) yymsp[0].minor.yy342;
}
#line 3184 "src/parser_proc.c"
  yymsp[0].minor.yy238 = yylhsminor.yy238;
        break;
      case 130: /* impl_stmt ::= let_stmt */
#line 870 "src/parser_proc.y"
{
 yylhsminor.yy238 = (struct psi_token**) yymsp[0].minor.yy319;
}
#line 3192 "src/parser_proc.c"
  yymsp[0].minor.yy238 = yylhsminor.yy238;
        break;
      case 131: /* impl_stmt ::= set_stmt */
#line 873 "src/parser_proc.y"
{
 yylhsminor.yy238 = (struct psi_token**) yymsp[0].minor.yy358;
}
#line 3200 "src/parser_proc.c"
  yymsp[0].minor.yy238 = yylhsminor.yy238;
        break;
      case 132: /* impl_stmt ::= assert_stmt */
#line 876 "src/parser_proc.y"
{
 yylhsminor.yy238 = (struct psi_token **) yymsp[0].minor.yy201;
}
#line 3208 "src/parser_proc.c"
  yymsp[0].minor.yy238 = yylhsminor.yy238;
        break;
      case 133: /* impl_stmt ::= free_stmt */
#line 879 "src/parser_proc.y"
{
 yylhsminor.yy238 = (struct psi_token**) yymsp[0].minor.yy220;
}
#line 3216 "src/parser_proc.c"
  yymsp[0].minor.yy238 = yylhsminor.yy238;
        break;
      case 134: /* number ::= NUMBER|NSNAME */
#line 882 "src/parser_proc.y"
{
 yylhsminor.yy57 = psi_number_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy57->token = yymsp[0].minor.yy0;
}
#line 3225 "src/parser_proc.c"
  yymsp[0].minor.yy57 = yylhsminor.yy57;
        break;
      case 135: /* number ::= decl_var */
#line 886 "src/parser_proc.y"
{
 yylhsminor.yy57 = psi_number_init(PSI_T_NAME, yymsp[0].minor.yy271);
 yylhsminor.yy57->token = psi_token_copy(yymsp[0].minor.yy271->token);
}
#line 3234 "src/parser_proc.c"
  yymsp[0].minor.yy57 = yylhsminor.yy57;
        break;
      case 136: /* num_exp ::= number */
#line 890 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_num(yymsp[0].minor.yy57);
 yylhsminor.yy207->token = psi_token_copy(yymsp[0].minor.yy57->token);
}
#line 3243 "src/parser_proc.c"
  yymsp[0].minor.yy207 = yylhsminor.yy207;
        break;
      case 137: /* num_exp ::= LPAREN num_exp RPAREN */
#line 894 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_num_exp_init_unary(PSI_T_LPAREN, yymsp[-1].minor.yy207);
 yylhsminor.yy207->token = yymsp[-2].minor.yy0;
}
#line 3252 "src/parser_proc.c"
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-2].minor.yy207 = yylhsminor.yy207;
        break;
      case 140: /* let_exp ::= NULL */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 906 "src/parser_proc.y"
{
 yymsp[0].minor.yy200 = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 3262 "src/parser_proc.c"
}
        break;
      case 141: /* let_exp ::= AMPERSAND NULL */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 909 "src/parser_proc.y"
{
 yymsp[-1].minor.yy200 = psi_let_exp_init(PSI_LET_NULL, NULL);
 yymsp[-1].minor.yy200->is_reference = 1;
}
#line 3272 "src/parser_proc.c"
  yy_destructor(yypParser,15,&yymsp[0].minor);
}
        break;
      case 142: /* let_exp ::= let_callback */
#line 913 "src/parser_proc.y"
{
 yylhsminor.yy200 = psi_let_exp_init(PSI_LET_CALLBACK, yymsp[0].minor.yy120);
}
#line 3281 "src/parser_proc.c"
  yymsp[0].minor.yy200 = yylhsminor.yy200;
        break;
      case 143: /* let_exp ::= let_calloc */
#line 916 "src/parser_proc.y"
{
 yylhsminor.yy200 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy45);
}
#line 3289 "src/parser_proc.c"
  yymsp[0].minor.yy200 = yylhsminor.yy200;
        break;
      case 144: /* let_exp ::= AMPERSAND let_calloc */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 919 "src/parser_proc.y"
{
 yymsp[-1].minor.yy200 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy45);
 yymsp[-1].minor.yy200->is_reference = 1;
}
#line 3299 "src/parser_proc.c"
}
        break;
      case 145: /* let_exp ::= let_func */
#line 923 "src/parser_proc.y"
{
 yylhsminor.yy200 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy67);
}
#line 3307 "src/parser_proc.c"
  yymsp[0].minor.yy200 = yylhsminor.yy200;
        break;
      case 146: /* let_exp ::= AMPERSAND let_func */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 926 "src/parser_proc.y"
{
 yymsp[-1].minor.yy200 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy67);
 yymsp[-1].minor.yy200->is_reference = 1;
}
#line 3317 "src/parser_proc.c"
}
        break;
      case 147: /* let_exp ::= num_exp */
#line 930 "src/parser_proc.y"
{
 yylhsminor.yy200 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy207);
}
#line 3325 "src/parser_proc.c"
  yymsp[0].minor.yy200 = yylhsminor.yy200;
        break;
      case 148: /* let_exp ::= AMPERSAND num_exp */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 933 "src/parser_proc.y"
{
 yymsp[-1].minor.yy200 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy207);
 yymsp[-1].minor.yy200->is_reference = 1;
}
#line 3335 "src/parser_proc.c"
}
        break;
      case 149: /* let_exp ::= decl_var EQUALS let_exp */
#line 937 "src/parser_proc.y"
{
 yylhsminor.yy200 = yymsp[0].minor.yy200;
 yylhsminor.yy200->var = yymsp[-2].minor.yy271;
}
#line 3344 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-1].minor);
  yymsp[-2].minor.yy200 = yylhsminor.yy200;
        break;
      case 150: /* let_stmt ::= LET let_exp EOS */
#line 941 "src/parser_proc.y"
{
 yylhsminor.yy319 = psi_let_stmt_init(yymsp[-1].minor.yy200);
 yylhsminor.yy319->token = yymsp[-2].minor.yy0;
}
#line 3354 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy319 = yylhsminor.yy319;
        break;
      case 151: /* let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS */
#line 945 "src/parser_proc.y"
{
 yylhsminor.yy319 = psi_let_stmt_init(psi_let_exp_init_ex(yymsp[-4].minor.yy271, PSI_LET_TMP, yymsp[-1].minor.yy271));
 yylhsminor.yy319->token = yymsp[-5].minor.yy0;
 yylhsminor.yy319->exp->is_reference = yymsp[-2].minor.yy89 ? 1 : 0;
}
#line 3365 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-3].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy319 = yylhsminor.yy319;
        break;
      case 152: /* let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN */
#line 950 "src/parser_proc.y"
{
 yylhsminor.yy120 = psi_let_callback_init(psi_let_func_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text, yymsp[-4].minor.yy370), yymsp[-2].minor.yy243);
 yylhsminor.yy120->token = yymsp[-7].minor.yy0;
 free(yymsp[-6].minor.yy0);
}
#line 3377 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-5].minor);
  yy_destructor(yypParser,86,&yymsp[-3].minor);
  yy_destructor(yypParser,87,&yymsp[-1].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-7].minor.yy120 = yylhsminor.yy120;
        break;
      case 153: /* let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN */
#line 955 "src/parser_proc.y"
{
 yylhsminor.yy45 = psi_let_calloc_init(yymsp[-3].minor.yy207, yymsp[-1].minor.yy207);
 yylhsminor.yy45->token = yymsp[-5].minor.yy0;
}
#line 3390 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-5].minor.yy45 = yylhsminor.yy45;
        break;
      case 154: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN */
#line 959 "src/parser_proc.y"
{
 yylhsminor.yy67 = psi_let_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy370);
 yylhsminor.yy67->token = yymsp[-3].minor.yy0;
}
#line 3402 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-3].minor.yy67 = yylhsminor.yy67;
        break;
      case 155: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN */
#line 963 "src/parser_proc.y"
{
 yylhsminor.yy67 = psi_let_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy370);
 yylhsminor.yy67->token = yymsp[-5].minor.yy0;
 yylhsminor.yy67->inner = yymsp[-1].minor.yy179;
}
#line 3414 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-5].minor.yy67 = yylhsminor.yy67;
        break;
      case 156: /* let_exps ::= let_exp */
#line 968 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
   &yymsp[0].minor.yy200);
}
#line 3426 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 157: /* let_exps ::= let_exps COMMA let_exp */
#line 972 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy200);
}
#line 3434 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 158: /* callback_arg_list ::= */
#line 975 "src/parser_proc.y"
{
 yymsp[1].minor.yy243 = NULL;
}
#line 3443 "src/parser_proc.c"
        break;
      case 159: /* callback_arg_list ::= callback_args */
#line 978 "src/parser_proc.y"
{
 yylhsminor.yy243 = yymsp[0].minor.yy243;
}
#line 3450 "src/parser_proc.c"
  yymsp[0].minor.yy243 = yylhsminor.yy243;
        break;
      case 160: /* callback_args ::= set_exp */
#line 981 "src/parser_proc.y"
{
 yylhsminor.yy243 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy180);
}
#line 3459 "src/parser_proc.c"
  yymsp[0].minor.yy243 = yylhsminor.yy243;
        break;
      case 161: /* callback_args ::= callback_args COMMA set_exp */
#line 985 "src/parser_proc.y"
{
 yylhsminor.yy243 = psi_plist_add(yymsp[-2].minor.yy243, &yymsp[0].minor.yy180);
}
#line 3467 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy243 = yylhsminor.yy243;
        break;
      case 164: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN */
#line 994 "src/parser_proc.y"
{
 yylhsminor.yy362 = psi_set_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy271);
 yylhsminor.yy362->token = yymsp[-3].minor.yy0;
}
#line 3477 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-3].minor.yy362 = yylhsminor.yy362;
        break;
      case 165: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN */
#line 998 "src/parser_proc.y"
{
 yylhsminor.yy362 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy271);
 yylhsminor.yy362->token = yymsp[-5].minor.yy0;
 yylhsminor.yy362->inner = yymsp[-1].minor.yy179;
}
#line 3489 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-5].minor.yy362 = yylhsminor.yy362;
        break;
      case 166: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN */
#line 1003 "src/parser_proc.y"
{
 yylhsminor.yy362 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy271);
 yylhsminor.yy362->token = yymsp[-5].minor.yy0;
 yylhsminor.yy362->recursive = 1;
}
#line 3502 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,88,&yymsp[-2].minor);
  yy_destructor(yypParser,101,&yymsp[-1].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-5].minor.yy362 = yylhsminor.yy362;
        break;
      case 167: /* set_exp ::= set_func */
#line 1008 "src/parser_proc.y"
{
 yylhsminor.yy180 = psi_set_exp_init(PSI_SET_FUNC, yymsp[0].minor.yy362);
}
#line 3514 "src/parser_proc.c"
  yymsp[0].minor.yy180 = yylhsminor.yy180;
        break;
      case 168: /* set_exp ::= num_exp */
#line 1011 "src/parser_proc.y"
{
 yylhsminor.yy180 = psi_set_exp_init(PSI_SET_NUMEXP, yymsp[0].minor.yy207);
}
#line 3522 "src/parser_proc.c"
  yymsp[0].minor.yy180 = yylhsminor.yy180;
        break;
      case 169: /* set_exps ::= set_exp */
#line 1014 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy180);
}
#line 3531 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 170: /* set_exps ::= set_exps COMMA set_exp */
#line 1018 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy180);
}
#line 3539 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 171: /* set_exp ::= impl_var EQUALS set_exp */
#line 1021 "src/parser_proc.y"
{
 yylhsminor.yy180 = yymsp[0].minor.yy180;
 yylhsminor.yy180->var = yymsp[-2].minor.yy370;
}
#line 3549 "src/parser_proc.c"
  yy_destructor(yypParser,98,&yymsp[-1].minor);
  yymsp[-2].minor.yy180 = yylhsminor.yy180;
        break;
      case 172: /* set_stmt ::= SET set_exp EOS */
#line 1025 "src/parser_proc.y"
{
 yylhsminor.yy358 = psi_set_stmt_init(yymsp[-1].minor.yy180);
 yylhsminor.yy358->token = yymsp[-2].minor.yy0;
}
#line 3559 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy358 = yylhsminor.yy358;
        break;
      case 173: /* return_stmt ::= RETURN set_func EOS */
#line 1029 "src/parser_proc.y"
{
 yylhsminor.yy342 = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, yymsp[-1].minor.yy362));
 yylhsminor.yy342->token = yymsp[-2].minor.yy0;
}
#line 3569 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy342 = yylhsminor.yy342;
        break;
      case 174: /* free_stmt ::= FREE free_exps EOS */
#line 1033 "src/parser_proc.y"
{
 yylhsminor.yy220 = psi_free_stmt_init(yymsp[-1].minor.yy179);
 yylhsminor.yy220->token = yymsp[-2].minor.yy0;
}
#line 3579 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy220 = yylhsminor.yy220;
        break;
      case 175: /* free_exps ::= free_exp */
#line 1037 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
   &yymsp[0].minor.yy146);
}
#line 3589 "src/parser_proc.c"
  yymsp[0].minor.yy179 = yylhsminor.yy179;
        break;
      case 176: /* free_exps ::= free_exps COMMA free_exp */
#line 1041 "src/parser_proc.y"
{
 yylhsminor.yy179 = psi_plist_add(yymsp[-2].minor.yy179, &yymsp[0].minor.yy146);
}
#line 3597 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[-1].minor);
  yymsp[-2].minor.yy179 = yylhsminor.yy179;
        break;
      case 177: /* free_exp ::= NAME LPAREN decl_vars RPAREN */
#line 1044 "src/parser_proc.y"
{
 yylhsminor.yy146 = psi_free_exp_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy179);
 yylhsminor.yy146->token = yymsp[-3].minor.yy0;
}
#line 3607 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,87,&yymsp[0].minor);
  yymsp[-3].minor.yy146 = yylhsminor.yy146;
        break;
      case 178: /* assert_stmt ::= PRE_ASSERT|POST_ASSERT num_exp EOS */
#line 1048 "src/parser_proc.y"
{
 yylhsminor.yy201 = psi_assert_stmt_init(yymsp[-2].minor.yy0->type, yymsp[-1].minor.yy207);
 yylhsminor.yy201->token = yymsp[-2].minor.yy0;
}
#line 3618 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy201 = yylhsminor.yy201;
        break;
      case 179: /* reference ::= */
#line 1052 "src/parser_proc.y"
{
 yymsp[1].minor.yy89 = false;
}
#line 3627 "src/parser_proc.c"
        break;
      case 180: /* reference ::= AMPERSAND */
{  yy_destructor(yypParser,23,&yymsp[0].minor);
#line 1055 "src/parser_proc.y"
{
 yymsp[0].minor.yy89 = true;
}
#line 3635 "src/parser_proc.c"
}
        break;
      case 181: /* indirection ::= */
#line 1058 "src/parser_proc.y"
{
 yymsp[1].minor.yy382 = 0;
}
#line 3643 "src/parser_proc.c"
        break;
      case 182: /* indirection ::= pointers */
#line 1061 "src/parser_proc.y"
{
 yylhsminor.yy382 = yymsp[0].minor.yy382;
}
#line 3650 "src/parser_proc.c"
  yymsp[0].minor.yy382 = yylhsminor.yy382;
        break;
      case 183: /* pointers ::= ASTERISK */
{  yy_destructor(yypParser,28,&yymsp[0].minor);
#line 1064 "src/parser_proc.y"
{
 yymsp[0].minor.yy382 = 1;
}
#line 3659 "src/parser_proc.c"
}
        break;
      case 184: /* pointers ::= pointers ASTERISK */
#line 1067 "src/parser_proc.y"
{
 yylhsminor.yy382 = yymsp[-1].minor.yy382+1;
}
#line 3667 "src/parser_proc.c"
  yy_destructor(yypParser,28,&yymsp[0].minor);
  yymsp[-1].minor.yy382 = yylhsminor.yy382;
        break;
      case 185: /* file ::= blocks */
{  yy_destructor(yypParser,180,&yymsp[0].minor);
#line 193 "src/parser_proc.y"
{
}
#line 3676 "src/parser_proc.c"
}
        break;
      case 186: /* blocks ::= block */
{  yy_destructor(yypParser,181,&yymsp[0].minor);
#line 194 "src/parser_proc.y"
{
}
#line 3684 "src/parser_proc.c"
}
        break;
      case 187: /* blocks ::= blocks block */
{  yy_destructor(yypParser,180,&yymsp[-1].minor);
#line 195 "src/parser_proc.y"
{
}
#line 3692 "src/parser_proc.c"
  yy_destructor(yypParser,181,&yymsp[0].minor);
}
        break;
      case 188: /* block ::= EOS */
{  yy_destructor(yypParser,75,&yymsp[0].minor);
#line 196 "src/parser_proc.y"
{
}
#line 3701 "src/parser_proc.c"
}
        break;
      case 189: /* block ::= EOL */
{  yy_destructor(yypParser,76,&yymsp[0].minor);
#line 197 "src/parser_proc.y"
{
}
#line 3709 "src/parser_proc.c"
}
        break;
      case 190: /* block ::= COMMENT */
{  yy_destructor(yypParser,77,&yymsp[0].minor);
#line 198 "src/parser_proc.y"
{
}
#line 3717 "src/parser_proc.c"
}
        break;
      default:
        break;
/********** End reduce actions ************************************************/
  };
  assert( yyruleno<sizeof(yyRuleInfo)/sizeof(yyRuleInfo[0]) );
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact <= YY_MAX_SHIFTREDUCE ){
    if( yyact>YY_MAX_SHIFT ){
      yyact += YY_MIN_REDUCE - YY_MIN_SHIFTREDUCE;
    }
    yymsp -= yysize-1;
    yypParser->yytos = yymsp;
    yymsp->stateno = (YYACTIONTYPE)yyact;
    yymsp->major = (YYCODETYPE)yygoto;
    yyTraceShift(yypParser, yyact);
  }else{
    assert( yyact == YY_ACCEPT_ACTION );
    yypParser->yytos -= yysize;
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yytos>yypParser->yystack ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
/************ Begin %parse_failure code ***************************************/
/************ End %parse_failure code *****************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  ParseTOKENTYPE yyminor         /* The minor type of the error token */
){
  ParseARG_FETCH;
#define TOKEN yyminor
/************ Begin %syntax_error code ****************************************/
#line 40 "src/parser_proc.y"
 ++P->errors; if (TOKEN) { psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col); } else { psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input"); } 
#line 3779 "src/parser_proc.c"
/************ End %syntax_error code ******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  ParseARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
#ifndef YYNOERRORRECOVERY
  yypParser->yyerrcnt = -1;
#endif
  assert( yypParser->yytos==yypParser->yystack );
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
/*********** Begin %parse_accept code *****************************************/
/*********** End %parse_accept code *******************************************/
  ParseARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "ParseAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void Parse(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  ParseTOKENTYPE yyminor       /* The value for the token */
  ParseARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  unsigned int yyact;   /* The parser action. */
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  int yyendofinput;     /* True if we are at the end of input */
#endif
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  yypParser = (yyParser*)yyp;
  assert( yypParser->yytos!=0 );
#if !defined(YYERRORSYMBOL) && !defined(YYNOERRORRECOVERY)
  yyendofinput = (yymajor==0);
#endif
  ParseARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput '%s'\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact <= YY_MAX_SHIFTREDUCE ){
      yy_shift(yypParser,yyact,yymajor,yyminor);
#ifndef YYNOERRORRECOVERY
      yypParser->yyerrcnt--;
#endif
      yymajor = YYNOCODE;
    }else if( yyact <= YY_MAX_REDUCE ){
      yy_reduce(yypParser,yyact-YY_MIN_REDUCE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
      yyminorunion.yy0 = yyminor;
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminor);
      }
      yymx = yypParser->yytos->major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor, &yyminorunion);
        yymajor = YYNOCODE;
      }else{
        while( yypParser->yytos >= yypParser->yystack
            && yymx != YYERRORSYMBOL
            && (yyact = yy_find_reduce_action(
                        yypParser->yytos->stateno,
                        YYERRORSYMBOL)) >= YY_MIN_REDUCE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yytos < yypParser->yystack || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
          yypParser->yyerrcnt = -1;
#endif
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          yy_shift(yypParser,yyact,YYERRORSYMBOL,yyminor);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor, yyminor);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor, yyminor);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
#ifndef YYNOERRORRECOVERY
        yypParser->yyerrcnt = -1;
#endif
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yytos>yypParser->yystack );
#ifndef NDEBUG
  if( yyTraceFILE ){
    yyStackEntry *i;
    char cDiv = '[';
    fprintf(yyTraceFILE,"%sReturn. Stack=",yyTracePrompt);
    for(i=&yypParser->yystack[1]; i<=yypParser->yytos; i++){
      fprintf(yyTraceFILE,"%c%s", cDiv, yyTokenName[i->major]);
      cDiv = ' ';
    }
    fprintf(yyTraceFILE,"]\n");
  }
#endif
  return;
}
