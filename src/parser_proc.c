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
#define YYNOCODE 170
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE struct psi_token *
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  struct psi_plist* yy7;
  struct psi_decl* yy17;
  struct psi_impl_type* yy40;
  struct psi_decl_union* yy47;
  struct psi_impl_arg* yy56;
  struct psi_decl_arg* yy64;
  struct psi_number* yy66;
  struct psi_let_callback* yy76;
  struct psi_decl_enum * yy87;
  struct psi_free_stmt* yy102;
  struct psi_decl_enum_item* yy109;
  struct psi_set_exp* yy113;
  struct psi_free_exp* yy114;
  struct psi_impl_var* yy123;
  struct psi_num_exp* yy124;
  struct psi_decl_var* yy131;
  struct psi_let_func* yy133;
  struct psi_decl_struct* yy137;
  struct psi_let_stmt* yy138;
  struct psi_assert_stmt* yy146;
  struct psi_decl_abi* yy180;
  struct psi_const_type* yy181;
  struct psi_decl_type* yy182;
  struct psi_let_exp* yy196;
  struct psi_layout yy207;
  struct psi_layout* yy221;
  struct psi_impl_func* yy226;
  struct psi_let_calloc* yy227;
  bool yy247;
  struct psi_return_stmt* yy258;
  struct psi_token** yy282;
  unsigned yy296;
  struct psi_set_stmt* yy300;
  struct psi_impl* yy303;
  struct psi_plist * yy304;
  struct psi_impl_def_val* yy319;
  struct psi_set_func* yy324;
  struct psi_const* yy336;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL struct psi_parser *P;
#define ParseARG_PDECL ,struct psi_parser *P
#define ParseARG_FETCH struct psi_parser *P = yypParser->P
#define ParseARG_STORE yypParser->P = P
#define YYFALLBACK 1
#define YYNSTATE             199
#define YYNRULE              159
#define YY_MAX_SHIFT         198
#define YY_MIN_SHIFTREDUCE   332
#define YY_MAX_SHIFTREDUCE   490
#define YY_MIN_REDUCE        491
#define YY_MAX_REDUCE        649
#define YY_ERROR_ACTION      650
#define YY_ACCEPT_ACTION     651
#define YY_NO_ACTION         652
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
#define YY_ACTTAB_COUNT (1029)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   398,  413,  481,  413,  413,  413,  413,  413,  413,  413,
 /*    10 */   413,  413,  413,   94,  441,  435,  378,  110,  398,  435,
 /*    20 */   380,  415,   17,  386,  116,   28,   28,  484,  414,   44,
 /*    30 */    25,   25,   40,   50,   11,   10,   61,  427,   28,   28,
 /*    40 */   150,  150,  150,  150,  150,  150,  150,  150,  150,  150,
 /*    50 */   417,  357,  357,  357,  357,   84,  124,  339,   94,  160,
 /*    60 */   117,   49,  337,  409,  338,  370,  336,  335,  151,   57,
 /*    70 */   409,  333,  484,   21,   29,  379,   91,   90,   89,  484,
 /*    80 */   352,  138,   36,  334,  153,  426,  109,  394,   82,   68,
 /*    90 */    66,   65,  398,  413,  126,  413,  413,  413,  413,  413,
 /*   100 */   413,  413,  413,  413,  413,  394,   82,   68,  152,   48,
 /*   110 */    94,  442,  435,  135,  383,  124,  435,  488,  195,  196,
 /*   120 */   149,  124,   28,   28,  484,  484,  437,  103,  485,  444,
 /*   130 */   446,  148,  139,  443,  458,   28,   28,  150,  150,  150,
 /*   140 */   150,  150,  150,  150,  150,  150,  150,   84,  124,  401,
 /*   150 */   398,  413,  420,  413,  413,  413,  413,  413,  413,  413,
 /*   160 */   413,  413,  413,  114,  380,  151,  166,  118,  181,  183,
 /*   170 */   182,   29,  124,  419,   36,   54,  155,  353,  356,  394,
 /*   180 */    82,   68,   66,   65,   30,   30,   30,   30,   30,   30,
 /*   190 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   200 */    30,   30,  354,  124,  124,   42,  353,  355,  398,  413,
 /*   210 */     2,  413,  413,  413,  413,  413,  413,  413,  413,  413,
 /*   220 */   413,  361,  360,  111,  476,   95,   91,   90,   89,  159,
 /*   230 */   163,  347,   35,  162,  163,   81,  479,  394,   82,   68,
 /*   240 */    66,   65,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   250 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   260 */   418,  124,  124,   84,  136,  126,  398,  413,  147,  413,
 /*   270 */   413,  413,  413,  413,  413,  413,  413,  413,  413,  165,
 /*   280 */   163,  373,  125,  348,   91,   90,   89,  115,   37,  130,
 /*   290 */    36,  108,   38,  478,  149,  394,   82,   68,   66,   65,
 /*   300 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   310 */    30,   30,   30,  149,  425,   30,   30,  423,  423,  423,
 /*   320 */   423,   77,  169,  475,  398,  413,   71,  413,  413,  413,
 /*   330 */   413,  413,  413,  413,  413,  413,  413,  171,  198,  489,
 /*   340 */   490,  406,  181,  183,  182,   96,  192,  172,   36,  129,
 /*   350 */   405,   64,    1,  394,   82,   68,   66,   65,  121,  422,
 /*   360 */   399,   70,   69,  133,   25,   25,   40,   50,   11,   10,
 /*   370 */    61,    8,  456,  423,  423,  423,  423,  423,   69,   67,
 /*   380 */    13,  466,  398,  413,  416,  413,  413,  413,  413,  413,
 /*   390 */   413,  413,  413,  413,  413,    7,  465,  134,  477,  184,
 /*   400 */   181,  183,  182,    6,  455,   93,   36,   23,  156,   39,
 /*   410 */   180,  394,   82,   68,   66,   65,  143,   22,   80,  485,
 /*   420 */     4,  388,  381,  414,   44,  382,  143,  143,  143,  143,
 /*   430 */   143,  143,  143,   24,  364,  372,  436,   84,  191,  485,
 /*   440 */   398,  413,  107,  413,  413,  413,  413,  413,  413,  413,
 /*   450 */   413,  413,  413,   43,  437,   97,  436,  371,  181,  183,
 /*   460 */   182,  196,   88,   86,   36,  409,  365,  178,  142,  394,
 /*   470 */    82,   68,   66,   65,  437,  101,  124,  383,  404,  146,
 /*   480 */   144,  421,  421,  421,  421,  421,  461,  179,  468,  397,
 /*   490 */   500,  485,  402,  395,  149,   75,  124,  500,  398,  413,
 /*   500 */   184,  413,  413,  413,  413,  413,  413,  413,  413,  413,
 /*   510 */   413,  363,  168,  120,    2,   78,  181,  183,  182,  167,
 /*   520 */    45,   85,   46,  122,  414,   34,   87,  394,   82,   68,
 /*   530 */    66,   65,   25,   25,   40,   50,   11,   10,   61,  123,
 /*   540 */   346,  463,  463,  463,  463,  463,  463,  463,  463,  463,
 /*   550 */   463,  339,  185,   83,  345,  344,  337,  464,  338,   47,
 /*   560 */   336,  335,  196,   88,   86,  333,  409,   21,  194,  377,
 /*   570 */   376,  349,  341,   62,  181,  183,  182,  334,  153,  436,
 /*   580 */    58,  127,  128,   32,   59,  394,   82,   68,   66,   65,
 /*   590 */    94,   60,  435,  132,   15,   33,  435,  437,   98,  481,
 /*   600 */   387,  184,   28,   28,  484,  414,   44,  474,  473,  651,
 /*   610 */     3,    3,  180,  196,  452,   28,   28,  143,  451,  124,
 /*   620 */    80,  467,   72,  389,   41,  414,   44,  143,  143,  143,
 /*   630 */   143,  143,  143,  143,  423,  423,  423,  423,   12,   14,
 /*   640 */    16,  453,  145,   94,    5,  435,   51,  409,   94,  435,
 /*   650 */   435,   29,  481,  422,  435,   28,   28,  484,   52,   27,
 /*   660 */    28,   28,  484,  196,   88,   86,  368,  409,   28,   28,
 /*   670 */   143,    9,  639,   28,   28,  154,  367,  152,   73,   20,
 /*   680 */   143,  143,  143,  143,  143,  143,  143,  158,   53,   74,
 /*   690 */   423,  423,  423,  423,  423,  437,  103,  161,  444,  446,
 /*   700 */   485,   76,  443,  450,   29,  164,   55,  528,  359,   29,
 /*   710 */   131,  358,  170,   63,   79,  141,  393,  124,  173,  386,
 /*   720 */   119,  174,  175,  176,  414,   44,   30,   30,   30,   30,
 /*   730 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   740 */    30,   30,   30,   30,  177,  412,  411,  391,   30,   30,
 /*   750 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   760 */    30,   30,   30,   30,   30,   30,  409,  390,  157,  410,
 /*   770 */   362,  500,  369,  343,  186,  188,  189,  414,   44,  187,
 /*   780 */    92,  190,  454,   30,   30,   30,   30,   30,   30,   30,
 /*   790 */    30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
 /*   800 */    30,  645,  375,   26,   94,  193,  435,   31,  436,   56,
 /*   810 */   435,  332,  493,  481,  436,  373,   28,   28,  484,  409,
 /*   820 */   493,  197,  493,  493,  493,  493,  437,   99,  493,   28,
 /*   830 */    28,  143,  437,  102,  493,  445,  447,  493,  493,  438,
 /*   840 */   493,  143,  143,  143,  143,  143,  143,  143,  124,   18,
 /*   850 */   428,  493,  436,  431,  124,  493,  493,  493,  493,  436,
 /*   860 */   493,  433,  432,  493,  142,   29,  430,  434,  493,  493,
 /*   870 */   437,  101,  198,  489,  490,  436,  493,  437,  104,   96,
 /*   880 */   192,  172,  470,  113,  468,   64,    1,  142,  493,  493,
 /*   890 */   149,  493,  124,  437,  101,   70,   69,  493,  152,  124,
 /*   900 */   493,  493,  493,  493,  493,  137,  493,  468,  152,  493,
 /*   910 */   493,  493,  493,  149,  493,  124,  437,  103,  493,  444,
 /*   920 */   446,  493,  436,  443,  457,  112,  437,  103,  493,  444,
 /*   930 */   446,  436,  493,  443,  140,  436,  493,  493,  124,  493,
 /*   940 */   437,  100,  493,  142,  493,  493,  436,  493,  124,  437,
 /*   950 */   101,  493,  493,  437,  106,  436,  493,  493,  142,  493,
 /*   960 */   493,  472,  124,  468,  437,  101,  493,  142,  493,  149,
 /*   970 */   493,  124,  493,  437,  101,  124,  471,  493,  468,   19,
 /*   980 */   428,  493,  493,  431,  149,  462,  124,  468,  436,  493,
 /*   990 */   493,  433,  432,  149,  493,  124,  430,  434,  429,  493,
 /*  1000 */   493,  431,  493,  493,  493,  493,  437,  105,  493,  433,
 /*  1010 */   432,  493,  493,  493,  430,  434,  493,  493,  493,  493,
 /*  1020 */   493,  493,  493,  493,  493,  493,  493,  493,  124,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,   23,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   14,   15,   16,  115,  116,    2,   20,
 /*    20 */   115,  122,   23,  117,  118,   26,   27,   28,  122,  123,
 /*    30 */    62,   63,   64,   65,   66,   67,   68,  128,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */    82,    1,    2,    3,    4,   57,  155,   98,   14,  154,
 /*    60 */   155,  152,  103,  164,  105,   14,  107,  108,   69,   70,
 /*    70 */   164,  112,   28,  114,   75,  115,   78,   79,   80,   28,
 /*    80 */    82,  115,   84,  124,  125,  128,  129,   89,   90,   91,
 /*    90 */    92,   93,    2,    3,  127,    5,    6,    7,    8,    9,
 /*   100 */    10,   11,   12,   13,   14,   89,   90,   91,  115,  152,
 /*   110 */    14,   15,   16,   14,   14,  155,   20,  158,   14,  160,
 /*   120 */   153,  155,   26,   27,   28,   28,  133,  134,   28,  136,
 /*   130 */   137,  168,  115,  140,  141,   39,   40,   41,   42,   43,
 /*   140 */    44,   45,   46,   47,   48,   49,   50,   57,  155,    5,
 /*   150 */     2,    3,  152,    5,    6,    7,    8,    9,   10,   11,
 /*   160 */    12,   13,   14,  115,  115,   69,  154,  155,   78,   79,
 /*   170 */    80,   75,  155,  152,   84,   75,   86,  101,  102,   89,
 /*   180 */    90,   91,   92,   93,   21,   22,   23,   24,   25,   26,
 /*   190 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   200 */    37,   38,   73,  155,  155,   57,  101,  102,    2,    3,
 /*   210 */    81,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   220 */    14,  115,  115,  150,  151,   76,   78,   79,   80,  154,
 /*   230 */   155,   82,   84,  154,  155,   91,   73,   89,   90,   91,
 /*   240 */    92,   93,   21,   22,   23,   24,   25,   26,   27,   28,
 /*   250 */    29,   30,   31,   32,   33,   34,   35,   36,   37,   38,
 /*   260 */   152,  155,  155,   57,  147,  127,    2,    3,  127,    5,
 /*   270 */     6,    7,    8,    9,   10,   11,   12,   13,   14,  154,
 /*   280 */   155,   14,   99,  100,   78,   79,   80,  127,   76,   77,
 /*   290 */    84,  153,   76,   77,  153,   89,   90,   91,   92,   93,
 /*   300 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   310 */    32,   33,   34,  153,  126,   37,   38,    1,    2,    3,
 /*   320 */     4,   57,  126,   73,    2,    3,   76,    5,    6,    7,
 /*   330 */     8,    9,   10,   11,   12,   13,   14,  106,   71,   72,
 /*   340 */    73,  164,   78,   79,   80,   78,   79,   80,   84,   86,
 /*   350 */   164,   84,   85,   89,   90,   91,   92,   93,  155,   96,
 /*   360 */   166,   94,   95,  153,   62,   63,   64,   65,   66,   67,
 /*   370 */    68,   76,   77,   57,   58,   59,   60,   61,   95,   57,
 /*   380 */    76,   77,    2,    3,   82,    5,    6,    7,    8,    9,
 /*   390 */    10,   11,   12,   13,   14,   76,   77,  125,  151,   98,
 /*   400 */    78,   79,   80,   76,   77,   14,   84,   76,   77,  153,
 /*   410 */   109,   89,   90,   91,   92,   93,   41,   75,  117,   28,
 /*   420 */   119,  120,  111,  122,  123,   14,   51,   52,   53,   54,
 /*   430 */    55,   56,   57,   76,   77,  111,  115,   57,   74,   28,
 /*   440 */     2,    3,  155,    5,    6,    7,    8,    9,   10,   11,
 /*   450 */    12,   13,   14,  104,  133,  134,  115,  111,   78,   79,
 /*   460 */    80,  160,  161,  162,   84,  164,  111,   74,  127,   89,
 /*   470 */    90,   91,   92,   93,  133,  134,  155,   14,    2,  138,
 /*   480 */   139,   15,   16,   17,   18,   19,  145,  121,  147,    2,
 /*   490 */    74,   28,  167,  165,  153,   57,  155,   81,    2,    3,
 /*   500 */    98,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   510 */    14,  109,  110,  155,   81,  113,   78,   79,   80,  117,
 /*   520 */   101,  104,  101,   14,  122,  123,  104,   89,   90,   91,
 /*   530 */    92,   93,   62,   63,   64,   65,   66,   67,   68,   14,
 /*   540 */   159,   41,   42,   43,   44,   45,   46,   47,   48,   49,
 /*   550 */    50,   98,   14,   57,  159,  159,  103,   57,  105,  104,
 /*   560 */   107,  108,  160,  161,  162,  112,  164,  114,   87,  163,
 /*   570 */   163,  100,   14,   83,   78,   79,   80,  124,  125,  115,
 /*   580 */    74,   77,   96,   75,   74,   89,   90,   91,   92,   93,
 /*   590 */    14,   74,   16,   20,   81,   75,   20,  133,  134,   23,
 /*   600 */   117,   98,   26,   27,   28,  122,  123,   73,   73,  156,
 /*   610 */   157,  158,  109,  160,   73,   39,   40,   41,   73,  155,
 /*   620 */   117,   77,   83,  120,   75,  122,  123,   51,   52,   53,
 /*   630 */    54,   55,   56,   57,    1,    2,    3,    4,   83,   76,
 /*   640 */    81,   77,   77,   14,   75,   16,   75,  164,   14,   20,
 /*   650 */    16,   75,   23,   96,   20,   26,   27,   28,   75,   75,
 /*   660 */    26,   27,   28,  160,  161,  162,   73,  164,   39,   40,
 /*   670 */    41,   83,   96,   39,   40,   77,   73,  115,   77,   75,
 /*   680 */    51,   52,   53,   54,   55,   56,   57,   14,   75,   77,
 /*   690 */    57,   58,   59,   60,   61,  133,  134,   14,  136,  137,
 /*   700 */    28,   77,  140,  141,   75,   14,   75,   75,   73,   75,
 /*   710 */    77,   73,   20,   83,   14,   86,   77,  155,   16,  117,
 /*   720 */   118,   76,   16,   75,  122,  123,   21,   22,   23,   24,
 /*   730 */    25,   26,   27,   28,   29,   30,   31,   32,   33,   34,
 /*   740 */    35,   36,   37,   38,   74,   14,   14,   73,   21,   22,
 /*   750 */    23,   24,   25,   26,   27,   28,   29,   30,   31,   32,
 /*   760 */    33,   34,   35,   36,   37,   38,  164,   73,  113,   14,
 /*   770 */    14,   81,  117,   77,   16,   16,   75,  122,  123,   76,
 /*   780 */    14,   74,   77,   21,   22,   23,   24,   25,   26,   27,
 /*   790 */    28,   29,   30,   31,   32,   33,   34,   35,   36,   37,
 /*   800 */    38,    0,   88,   76,   14,   16,   16,   83,  115,   81,
 /*   810 */    20,   73,  169,   23,  115,   14,   26,   27,   28,  164,
 /*   820 */   169,   19,  169,  169,  169,  169,  133,  134,  169,   39,
 /*   830 */    40,   41,  133,  134,  169,  136,  137,  169,  169,   77,
 /*   840 */   169,   51,   52,   53,   54,   55,   56,   57,  155,  131,
 /*   850 */   132,  169,  115,  135,  155,  169,  169,  169,  169,  115,
 /*   860 */   169,  143,  144,  169,  127,   75,  148,  149,  169,  169,
 /*   870 */   133,  134,   71,   72,   73,  115,  169,  133,  134,   78,
 /*   880 */    79,   80,  145,  146,  147,   84,   85,  127,  169,  169,
 /*   890 */   153,  169,  155,  133,  134,   94,   95,  169,  115,  155,
 /*   900 */   169,  169,  169,  169,  169,  145,  169,  147,  115,  169,
 /*   910 */   169,  169,  169,  153,  169,  155,  133,  134,  169,  136,
 /*   920 */   137,  169,  115,  140,  141,  142,  133,  134,  169,  136,
 /*   930 */   137,  115,  169,  140,  141,  115,  169,  169,  155,  169,
 /*   940 */   133,  134,  169,  127,  169,  169,  115,  169,  155,  133,
 /*   950 */   134,  169,  169,  133,  134,  115,  169,  169,  127,  169,
 /*   960 */   169,  145,  155,  147,  133,  134,  169,  127,  169,  153,
 /*   970 */   169,  155,  169,  133,  134,  155,  145,  169,  147,  131,
 /*   980 */   132,  169,  169,  135,  153,  145,  155,  147,  115,  169,
 /*   990 */   169,  143,  144,  153,  169,  155,  148,  149,  132,  169,
 /*  1000 */   169,  135,  169,  169,  169,  169,  133,  134,  169,  143,
 /*  1010 */   144,  169,  169,  169,  148,  149,  169,  169,  169,  169,
 /*  1020 */   169,  169,  169,  169,  169,  169,  169,  169,  155,
};
#define YY_SHIFT_USE_DFLT (1029)
#define YY_SHIFT_COUNT    (198)
#define YY_SHIFT_MIN      (-32)
#define YY_SHIFT_MAX      (802)
static const short yy_shift_ofst[] = {
 /*     0 */   267,  148,  206,  801,   -2,  576,   -1,  629,   -1,   -1,
 /*    10 */    -1,  790,  790,  790,  790,  470,  470,   96,  -32,  302,
 /*    20 */   264,  322,  264,   90,  380,  634,  634,  634,  634,  634,
 /*    30 */   634,  634,  633,   44,   44,  438,  496,  316,   44,   44,
 /*    40 */    44,   44,   51,  129,   44,   44,   44,  129,  -21,  -21,
 /*    50 */    99,  -21,  -21,   97,   97,   97,  104,  500,  316,  316,
 /*    60 */   316,  375,  466,  466,   50,   16,   16,   51,  144,  -21,
 /*    70 */   283,   99,  -21,  342,  342,   97,  342,   97,  342,  364,
 /*    80 */   393,  476,  487,   97,   97,  433,  364,  433,  364,  509,
 /*    90 */   525,  538,  364,  481,  481,  104,  558,  163,  705,  727,
 /*   100 */   762,  221,  221,  221,  221,  221,  278,  100,  263,  212,
 /*   110 */   216,  250,  295,  304,  319,  327,  331,  391,  411,  357,
 /*   120 */   463,  411,  416,  416,  391,  149,  490,  506,  504,  486,
 /*   130 */   510,  517,  508,  573,  513,  520,  534,  535,  541,  539,
 /*   140 */   545,  544,  555,  549,  563,  564,  565,  569,  571,  557,
 /*   150 */   583,  584,  588,  559,  593,  598,  603,  604,  601,  673,
 /*   160 */   613,  612,  683,  672,  624,  691,  631,  632,  635,  638,
 /*   170 */   630,  692,  700,  639,  702,  645,  706,  648,  670,  674,
 /*   180 */   694,  731,  732,  755,  756,  690,  696,  758,  703,  759,
 /*   190 */   701,  707,  766,  714,  789,  724,  728,  738,  802,
};
#define YY_REDUCE_USE_DFLT (-102)
#define YY_REDUCE_COUNT (96)
#define YY_REDUCE_MIN   (-101)
#define YY_REDUCE_MAX   (873)
static const short yy_reduce_ofst[] = {
 /*     0 */   453,  402,  301,  -41,  503,  341,  783,  737,   -7,  562,
 /*    10 */   793,  760,  816,  831,  840,  718,  848,  699,  866,  866,
 /*    20 */   -94,  655,  602,  483,  483,  321,  464,  693,  744,  807,
 /*    30 */   820,  873,  -43,  -99,  -95, -101, -101,  -91,  -40,  -34,
 /*    40 */    17,   48,   12,   76,   49,  106,  107,  105,  -33,  138,
 /*    50 */    73,  141,  160,   75,   79,  125,  183,  -37,    0,   21,
 /*    60 */   108,  117,  188,  196,  231,  177,  186,  203,  194,  210,
 /*    70 */   272,  247,  256,  311,  324,  287,  346,  203,  355,  349,
 /*    80 */   366,  325,  328,  358,  203,  419,  417,  421,  422,  381,
 /*    90 */   395,  396,  455,  406,  407,  471,  396,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   650,  650,  650,  650,  650,  618,  650,  639,  650,  650,
 /*    10 */   650,  639,  639,  639,  639,  650,  650,  650,  650,  650,
 /*    20 */   543,  650,  543,  650,  650,  650,  650,  650,  650,  650,
 /*    30 */   650,  650,  650,  650,  641,  650,  650,  650,  650,  650,
 /*    40 */   650,  650,  641,  650,  650,  650,  650,  650,  639,  639,
 /*    50 */   650,  639,  639,  641,  641,  641,  650,  650,  650,  650,
 /*    60 */   650,  650,  650,  650,  650,  567,  566,  650,  559,  639,
 /*    70 */   650,  650,  639,  650,  650,  650,  650,  544,  650,  501,
 /*    80 */   551,  562,  555,  650,  650,  650,  501,  650,  501,  499,
 /*    90 */   499,  499,  501,  533,  533,  650,  499,  650,  650,  650,
 /*   100 */   650,  628,  608,  607,  599,  509,  598,  650,  650,  650,
 /*   110 */   650,  650,  650,  650,  650,  650,  650,  642,  642,  650,
 /*   120 */   650,  650,  570,  569,  650,  650,  583,  650,  650,  650,
 /*   130 */   650,  650,  650,  650,  650,  650,  650,  650,  650,  650,
 /*   140 */   650,  650,  650,  650,  619,  650,  650,  650,  650,  650,
 /*   150 */   650,  650,  595,  650,  650,  650,  650,  650,  650,  650,
 /*   160 */   650,  650,  650,  642,  650,  650,  650,  525,  650,  650,
 /*   170 */   650,  650,  650,  650,  650,  650,  650,  650,  650,  650,
 /*   180 */   650,  650,  650,  650,  650,  571,  650,  650,  650,  650,
 /*   190 */   650,  650,  650,  650,  650,  510,  650,  650,  650,
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
  "TEMP",          "FREE",          "SET",           "LET",         
  "RETURN",        "CALLOC",        "CALLBACK",      "LIB",         
  "EOF",           "EOS",           "COLON",         "LPAREN",      
  "COMMA",         "RPAREN",        "ENUM",          "STRUCT",      
  "UNION",         "LBRACE",        "RBRACE",        "EQUALS",      
  "CONST",         "TYPEDEF",       "ELLIPSIS",      "LBRACKET",    
  "RBRACKET",      "CHAR",          "SHORT",         "LONG",        
  "UNSIGNED",      "SIGNED",        "STATIC",        "FUNCTION",    
  "DOLLAR_NAME",   "error",         "decl_enum",     "decl_enum_items",
  "decl_enum_item",  "decl_struct_args_block",  "decl_struct_args",  "decl_struct", 
  "align_and_size",  "decl_union",    "const_type",    "constant",    
  "decl_typedef",  "decl_typedef_body_ex",  "decl_typedef_body",  "decl_typedef_body_fn_args",
  "decl",          "decl_func",     "decl_abi",      "decl_var",    
  "decl_vars",     "decl_arg",      "decl_args",     "struct_args", 
  "struct_arg",    "decl_layout",   "decl_type",     "const_decl_type",
  "impl",          "impl_func",     "impl_def_val",  "impl_var",    
  "impl_arg",      "impl_args",     "impl_vararg",   "impl_stmts",  
  "impl_stmt",     "number",        "num_exp",       "let_stmt",    
  "let_calloc",    "let_func",      "callback_arg_list",  "callback_args",
  "let_callback",  "let_exp",       "let_exps",      "assert_stmt", 
  "set_stmt",      "set_exp",       "set_exps",      "set_func",    
  "return_stmt",   "free_stmt",     "free_exps",     "free_exp",    
  "impl_type",     "reference",     "indirection",   "pointers",    
  "file",          "blocks",        "block",         "optional_name",
  "enum_name",     "struct_name",   "union_name",    "decl_var_array_size",
  "decl_scalar_type",  "decl_scalar_type_short",  "decl_scalar_type_long",  "decl_scalar_type_long_long",
  "callback_rval",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "block ::= LIB QUOTED_STRING EOS",
 /*   1 */ "block ::= decl",
 /*   2 */ "block ::= impl",
 /*   3 */ "block ::= decl_typedef",
 /*   4 */ "block ::= constant",
 /*   5 */ "block ::= decl_struct",
 /*   6 */ "block ::= decl_union",
 /*   7 */ "block ::= decl_enum",
 /*   8 */ "optional_name ::=",
 /*   9 */ "optional_name ::= NAME",
 /*  10 */ "align_and_size ::=",
 /*  11 */ "align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN",
 /*  12 */ "enum_name ::= ENUM optional_name",
 /*  13 */ "struct_name ::= STRUCT optional_name",
 /*  14 */ "union_name ::= UNION optional_name",
 /*  15 */ "decl_enum ::= enum_name LBRACE decl_enum_items RBRACE",
 /*  16 */ "decl_enum_items ::= decl_enum_item",
 /*  17 */ "decl_enum_items ::= decl_enum_items COMMA decl_enum_item",
 /*  18 */ "decl_enum_item ::= NAME EQUALS num_exp",
 /*  19 */ "decl_enum_item ::= NAME",
 /*  20 */ "decl_struct_args_block ::= LBRACE struct_args RBRACE",
 /*  21 */ "decl_struct_args ::= decl_struct_args_block",
 /*  22 */ "decl_struct_args ::= EOS",
 /*  23 */ "decl_struct ::= STRUCT NAME align_and_size decl_struct_args",
 /*  24 */ "decl_union ::= UNION NAME align_and_size decl_struct_args",
 /*  25 */ "const_type ::= BOOL|INT|FLOAT|STRING",
 /*  26 */ "constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS",
 /*  27 */ "decl_typedef ::= TYPEDEF decl_typedef_body EOS",
 /*  28 */ "decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var",
 /*  29 */ "decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var",
 /*  30 */ "decl_typedef_body_ex ::= decl_enum NAME",
 /*  31 */ "decl_typedef_body ::= decl_typedef_body_ex",
 /*  32 */ "decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN",
 /*  33 */ "decl_typedef_body ::= decl_func decl_typedef_body_fn_args",
 /*  34 */ "decl_typedef_body ::= decl_arg",
 /*  35 */ "decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS",
 /*  36 */ "decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS",
 /*  37 */ "decl_func ::= decl_arg",
 /*  38 */ "decl_func ::= VOID NAME",
 /*  39 */ "decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  40 */ "decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  41 */ "decl_abi ::= NAME",
 /*  42 */ "decl_var_array_size ::=",
 /*  43 */ "decl_var_array_size ::= LBRACKET NUMBER RBRACKET",
 /*  44 */ "decl_var ::= NAME decl_var_array_size",
 /*  45 */ "decl_var ::= pointers NAME decl_var_array_size",
 /*  46 */ "decl_vars ::= decl_var",
 /*  47 */ "decl_vars ::= decl_vars COMMA decl_var",
 /*  48 */ "decl_arg ::= const_decl_type decl_var",
 /*  49 */ "decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args",
 /*  50 */ "decl_arg ::= VOID pointers NAME",
 /*  51 */ "decl_arg ::= CONST VOID pointers NAME",
 /*  52 */ "decl_args ::=",
 /*  53 */ "decl_args ::= VOID",
 /*  54 */ "decl_args ::= decl_arg",
 /*  55 */ "decl_args ::= decl_args COMMA decl_arg",
 /*  56 */ "struct_args ::= struct_arg",
 /*  57 */ "struct_args ::= struct_args struct_arg",
 /*  58 */ "struct_arg ::= decl_typedef_body_ex EOS",
 /*  59 */ "struct_arg ::= decl_arg decl_layout EOS",
 /*  60 */ "decl_layout ::=",
 /*  61 */ "decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN",
 /*  62 */ "decl_scalar_type ::= CHAR",
 /*  63 */ "decl_scalar_type ::= SHORT decl_scalar_type_short",
 /*  64 */ "decl_scalar_type_short ::=",
 /*  65 */ "decl_scalar_type_short ::= INT",
 /*  66 */ "decl_scalar_type ::= INT",
 /*  67 */ "decl_scalar_type ::= LONG decl_scalar_type_long",
 /*  68 */ "decl_scalar_type_long ::=",
 /*  69 */ "decl_scalar_type_long ::= DOUBLE",
 /*  70 */ "decl_scalar_type_long ::= LONG decl_scalar_type_long_long",
 /*  71 */ "decl_scalar_type_long_long ::=",
 /*  72 */ "decl_scalar_type_long_long ::= INT",
 /*  73 */ "decl_type ::= UNSIGNED decl_scalar_type",
 /*  74 */ "decl_type ::= SIGNED decl_scalar_type",
 /*  75 */ "decl_type ::= UNSIGNED",
 /*  76 */ "decl_type ::= SIGNED",
 /*  77 */ "decl_type ::= decl_scalar_type",
 /*  78 */ "decl_type ::= STRUCT NAME",
 /*  79 */ "decl_type ::= UNION NAME",
 /*  80 */ "decl_type ::= ENUM NAME",
 /*  81 */ "decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME",
 /*  82 */ "const_decl_type ::= decl_type",
 /*  83 */ "const_decl_type ::= CONST decl_type",
 /*  84 */ "impl ::= impl_func LBRACE impl_stmts RBRACE",
 /*  85 */ "impl ::= STATIC impl_func LBRACE impl_stmts RBRACE",
 /*  86 */ "impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type",
 /*  87 */ "impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type",
 /*  88 */ "impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type",
 /*  89 */ "impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING",
 /*  90 */ "impl_var ::= reference DOLLAR_NAME",
 /*  91 */ "impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE",
 /*  92 */ "impl_arg ::= impl_type impl_var",
 /*  93 */ "impl_arg ::= impl_type impl_var EQUALS impl_def_val",
 /*  94 */ "impl_args ::= impl_arg",
 /*  95 */ "impl_args ::= impl_args COMMA impl_arg",
 /*  96 */ "impl_stmts ::= impl_stmt",
 /*  97 */ "impl_stmts ::= impl_stmts impl_stmt",
 /*  98 */ "impl_stmt ::= return_stmt",
 /*  99 */ "impl_stmt ::= let_stmt",
 /* 100 */ "impl_stmt ::= set_stmt",
 /* 101 */ "impl_stmt ::= assert_stmt",
 /* 102 */ "impl_stmt ::= free_stmt",
 /* 103 */ "number ::= NUMBER|NSNAME",
 /* 104 */ "number ::= decl_var",
 /* 105 */ "num_exp ::= number",
 /* 106 */ "num_exp ::= LPAREN num_exp RPAREN",
 /* 107 */ "num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp",
 /* 108 */ "num_exp ::= TILDE|NOT|PLUS|MINUS num_exp",
 /* 109 */ "let_exp ::= NULL",
 /* 110 */ "let_exp ::= AMPERSAND NULL",
 /* 111 */ "let_exp ::= let_callback",
 /* 112 */ "let_exp ::= let_calloc",
 /* 113 */ "let_exp ::= AMPERSAND let_calloc",
 /* 114 */ "let_exp ::= let_func",
 /* 115 */ "let_exp ::= AMPERSAND let_func",
 /* 116 */ "let_exp ::= num_exp",
 /* 117 */ "let_exp ::= AMPERSAND num_exp",
 /* 118 */ "let_exp ::= decl_var EQUALS let_exp",
 /* 119 */ "let_stmt ::= LET let_exp EOS",
 /* 120 */ "let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS",
 /* 121 */ "let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN",
 /* 122 */ "let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN",
 /* 123 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN",
 /* 124 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN",
 /* 125 */ "let_exps ::= let_exp",
 /* 126 */ "let_exps ::= let_exps COMMA let_exp",
 /* 127 */ "callback_arg_list ::=",
 /* 128 */ "callback_arg_list ::= callback_args",
 /* 129 */ "callback_args ::= set_exp",
 /* 130 */ "callback_args ::= callback_args COMMA set_exp",
 /* 131 */ "callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT",
 /* 132 */ "callback_rval ::= VOID",
 /* 133 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN",
 /* 134 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN",
 /* 135 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN",
 /* 136 */ "set_exp ::= set_func",
 /* 137 */ "set_exp ::= num_exp",
 /* 138 */ "set_exps ::= set_exp",
 /* 139 */ "set_exps ::= set_exps COMMA set_exp",
 /* 140 */ "set_exp ::= impl_var EQUALS set_exp",
 /* 141 */ "set_stmt ::= SET set_exp EOS",
 /* 142 */ "return_stmt ::= RETURN set_func EOS",
 /* 143 */ "free_stmt ::= FREE free_exps EOS",
 /* 144 */ "free_exps ::= free_exp",
 /* 145 */ "free_exps ::= free_exps COMMA free_exp",
 /* 146 */ "free_exp ::= NAME LPAREN decl_vars RPAREN",
 /* 147 */ "assert_stmt ::= PRE_ASSERT|POST_ASSERT num_exp EOS",
 /* 148 */ "reference ::=",
 /* 149 */ "reference ::= AMPERSAND",
 /* 150 */ "indirection ::=",
 /* 151 */ "indirection ::= pointers",
 /* 152 */ "pointers ::= ASTERISK",
 /* 153 */ "pointers ::= pointers ASTERISK",
 /* 154 */ "file ::= blocks",
 /* 155 */ "blocks ::= block",
 /* 156 */ "blocks ::= blocks block",
 /* 157 */ "block ::= EOF",
 /* 158 */ "block ::= EOS",
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
    case 64: /* TEMP */
    case 65: /* FREE */
    case 66: /* SET */
    case 67: /* LET */
    case 68: /* RETURN */
    case 69: /* CALLOC */
    case 70: /* CALLBACK */
    case 71: /* LIB */
    case 72: /* EOF */
    case 73: /* EOS */
    case 74: /* COLON */
    case 75: /* LPAREN */
    case 76: /* COMMA */
    case 77: /* RPAREN */
    case 78: /* ENUM */
    case 79: /* STRUCT */
    case 80: /* UNION */
    case 81: /* LBRACE */
    case 82: /* RBRACE */
    case 83: /* EQUALS */
    case 84: /* CONST */
    case 85: /* TYPEDEF */
    case 86: /* ELLIPSIS */
    case 87: /* LBRACKET */
    case 88: /* RBRACKET */
    case 89: /* CHAR */
    case 90: /* SHORT */
    case 91: /* LONG */
    case 92: /* UNSIGNED */
    case 93: /* SIGNED */
    case 94: /* STATIC */
    case 95: /* FUNCTION */
    case 96: /* DOLLAR_NAME */
{
#line 37 "src/parser_proc.y"
free((yypminor->yy0));
#line 1132 "src/parser_proc.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 97: /* error */
    case 104: /* align_and_size */
    case 153: /* reference */
    case 154: /* indirection */
    case 155: /* pointers */
    case 156: /* file */
    case 157: /* blocks */
    case 158: /* block */
    case 159: /* optional_name */
    case 160: /* enum_name */
    case 161: /* struct_name */
    case 162: /* union_name */
    case 163: /* decl_var_array_size */
    case 164: /* decl_scalar_type */
    case 165: /* decl_scalar_type_short */
    case 166: /* decl_scalar_type_long */
    case 167: /* decl_scalar_type_long_long */
    case 168: /* callback_rval */
{
#line 38 "src/parser_proc.y"
(void)P;
#line 1157 "src/parser_proc.c"
}
      break;
    case 98: /* decl_enum */
{
#line 64 "src/parser_proc.y"
psi_decl_enum_free(&(yypminor->yy87));
#line 1164 "src/parser_proc.c"
}
      break;
    case 99: /* decl_enum_items */
    case 101: /* decl_struct_args_block */
    case 102: /* decl_struct_args */
    case 111: /* decl_typedef_body_fn_args */
    case 116: /* decl_vars */
    case 118: /* decl_args */
    case 119: /* struct_args */
    case 129: /* impl_args */
    case 131: /* impl_stmts */
    case 142: /* let_exps */
    case 146: /* set_exps */
    case 150: /* free_exps */
{
#line 66 "src/parser_proc.y"
psi_plist_free((yypminor->yy7));
#line 1182 "src/parser_proc.c"
}
      break;
    case 100: /* decl_enum_item */
{
#line 68 "src/parser_proc.y"
psi_decl_enum_item_free(&(yypminor->yy109));
#line 1189 "src/parser_proc.c"
}
      break;
    case 103: /* decl_struct */
{
#line 74 "src/parser_proc.y"
psi_decl_struct_free(&(yypminor->yy137));
#line 1196 "src/parser_proc.c"
}
      break;
    case 105: /* decl_union */
{
#line 77 "src/parser_proc.y"
psi_decl_union_free(&(yypminor->yy47));
#line 1203 "src/parser_proc.c"
}
      break;
    case 106: /* const_type */
{
#line 79 "src/parser_proc.y"
psi_const_type_free(&(yypminor->yy181));
#line 1210 "src/parser_proc.c"
}
      break;
    case 107: /* constant */
{
#line 81 "src/parser_proc.y"
psi_const_free(&(yypminor->yy336));
#line 1217 "src/parser_proc.c"
}
      break;
    case 108: /* decl_typedef */
    case 109: /* decl_typedef_body_ex */
    case 110: /* decl_typedef_body */
    case 113: /* decl_func */
    case 117: /* decl_arg */
    case 120: /* struct_arg */
{
#line 83 "src/parser_proc.y"
psi_decl_arg_free(&(yypminor->yy64));
#line 1229 "src/parser_proc.c"
}
      break;
    case 112: /* decl */
{
#line 91 "src/parser_proc.y"
psi_decl_free(&(yypminor->yy17));
#line 1236 "src/parser_proc.c"
}
      break;
    case 114: /* decl_abi */
{
#line 95 "src/parser_proc.y"
psi_decl_abi_free(&(yypminor->yy180));
#line 1243 "src/parser_proc.c"
}
      break;
    case 115: /* decl_var */
{
#line 97 "src/parser_proc.y"
psi_decl_var_free(&(yypminor->yy131));
#line 1250 "src/parser_proc.c"
}
      break;
    case 121: /* decl_layout */
{
#line 109 "src/parser_proc.y"
psi_layout_free(&(yypminor->yy221));
#line 1257 "src/parser_proc.c"
}
      break;
    case 122: /* decl_type */
    case 123: /* const_decl_type */
{
#line 111 "src/parser_proc.y"
psi_decl_type_free(&(yypminor->yy182));
#line 1265 "src/parser_proc.c"
}
      break;
    case 124: /* impl */
{
#line 115 "src/parser_proc.y"
psi_impl_free(&(yypminor->yy303));
#line 1272 "src/parser_proc.c"
}
      break;
    case 125: /* impl_func */
{
#line 117 "src/parser_proc.y"
psi_impl_func_free(&(yypminor->yy226));
#line 1279 "src/parser_proc.c"
}
      break;
    case 126: /* impl_def_val */
{
#line 119 "src/parser_proc.y"
psi_impl_def_val_free(&(yypminor->yy319));
#line 1286 "src/parser_proc.c"
}
      break;
    case 127: /* impl_var */
{
#line 121 "src/parser_proc.y"
psi_impl_var_free(&(yypminor->yy123));
#line 1293 "src/parser_proc.c"
}
      break;
    case 128: /* impl_arg */
    case 130: /* impl_vararg */
{
#line 123 "src/parser_proc.y"
psi_impl_arg_free(&(yypminor->yy56));
#line 1301 "src/parser_proc.c"
}
      break;
    case 132: /* impl_stmt */
{
#line 131 "src/parser_proc.y"
psi_impl_stmt_free(&(yypminor->yy282));
#line 1308 "src/parser_proc.c"
}
      break;
    case 133: /* number */
{
#line 133 "src/parser_proc.y"
psi_number_free(&(yypminor->yy66));
#line 1315 "src/parser_proc.c"
}
      break;
    case 134: /* num_exp */
{
#line 135 "src/parser_proc.y"
psi_num_exp_free(&(yypminor->yy124));
#line 1322 "src/parser_proc.c"
}
      break;
    case 135: /* let_stmt */
{
#line 137 "src/parser_proc.y"
psi_let_stmt_free(&(yypminor->yy138));
#line 1329 "src/parser_proc.c"
}
      break;
    case 136: /* let_calloc */
{
#line 139 "src/parser_proc.y"
psi_let_calloc_free(&(yypminor->yy227));
#line 1336 "src/parser_proc.c"
}
      break;
    case 137: /* let_func */
{
#line 141 "src/parser_proc.y"
psi_let_func_free(&(yypminor->yy133));
#line 1343 "src/parser_proc.c"
}
      break;
    case 138: /* callback_arg_list */
    case 139: /* callback_args */
{
#line 143 "src/parser_proc.y"
psi_plist_free((yypminor->yy304));
#line 1351 "src/parser_proc.c"
}
      break;
    case 140: /* let_callback */
{
#line 147 "src/parser_proc.y"
psi_let_callback_free(&(yypminor->yy76));
#line 1358 "src/parser_proc.c"
}
      break;
    case 141: /* let_exp */
{
#line 149 "src/parser_proc.y"
psi_let_exp_free(&(yypminor->yy196));
#line 1365 "src/parser_proc.c"
}
      break;
    case 143: /* assert_stmt */
{
#line 153 "src/parser_proc.y"
psi_assert_stmt_free(&(yypminor->yy146));
#line 1372 "src/parser_proc.c"
}
      break;
    case 144: /* set_stmt */
{
#line 155 "src/parser_proc.y"
psi_set_stmt_free(&(yypminor->yy300));
#line 1379 "src/parser_proc.c"
}
      break;
    case 145: /* set_exp */
{
#line 157 "src/parser_proc.y"
psi_set_exp_free(&(yypminor->yy113));
#line 1386 "src/parser_proc.c"
}
      break;
    case 147: /* set_func */
{
#line 161 "src/parser_proc.y"
psi_set_func_free(&(yypminor->yy324));
#line 1393 "src/parser_proc.c"
}
      break;
    case 148: /* return_stmt */
{
#line 163 "src/parser_proc.y"
psi_return_stmt_free(&(yypminor->yy258));
#line 1400 "src/parser_proc.c"
}
      break;
    case 149: /* free_stmt */
{
#line 165 "src/parser_proc.y"
psi_free_stmt_free(&(yypminor->yy102));
#line 1407 "src/parser_proc.c"
}
      break;
    case 151: /* free_exp */
{
#line 169 "src/parser_proc.y"
psi_free_exp_free(&(yypminor->yy114));
#line 1414 "src/parser_proc.c"
}
      break;
    case 152: /* impl_type */
{
#line 171 "src/parser_proc.y"
psi_impl_type_free(&(yypminor->yy40));
#line 1421 "src/parser_proc.c"
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
  { 158, 3 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 159, 0 },
  { 159, 1 },
  { 104, 0 },
  { 104, 7 },
  { 160, 2 },
  { 161, 2 },
  { 162, 2 },
  { 98, 4 },
  { 99, 1 },
  { 99, 3 },
  { 100, 3 },
  { 100, 1 },
  { 101, 3 },
  { 102, 1 },
  { 102, 1 },
  { 103, 4 },
  { 105, 4 },
  { 106, 1 },
  { 107, 6 },
  { 108, 3 },
  { 109, 4 },
  { 109, 4 },
  { 109, 2 },
  { 110, 1 },
  { 111, 3 },
  { 110, 2 },
  { 110, 1 },
  { 112, 6 },
  { 112, 8 },
  { 113, 1 },
  { 113, 2 },
  { 110, 7 },
  { 110, 8 },
  { 114, 1 },
  { 163, 0 },
  { 163, 3 },
  { 115, 2 },
  { 115, 3 },
  { 116, 1 },
  { 116, 3 },
  { 117, 2 },
  { 110, 7 },
  { 117, 3 },
  { 117, 4 },
  { 118, 0 },
  { 118, 1 },
  { 118, 1 },
  { 118, 3 },
  { 119, 1 },
  { 119, 2 },
  { 120, 2 },
  { 120, 3 },
  { 121, 0 },
  { 121, 7 },
  { 164, 1 },
  { 164, 2 },
  { 165, 0 },
  { 165, 1 },
  { 164, 1 },
  { 164, 2 },
  { 166, 0 },
  { 166, 1 },
  { 166, 2 },
  { 167, 0 },
  { 167, 1 },
  { 122, 2 },
  { 122, 2 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 122, 2 },
  { 122, 2 },
  { 122, 2 },
  { 122, 1 },
  { 123, 1 },
  { 123, 2 },
  { 124, 4 },
  { 124, 5 },
  { 125, 7 },
  { 125, 8 },
  { 125, 13 },
  { 126, 1 },
  { 127, 2 },
  { 152, 1 },
  { 128, 2 },
  { 128, 4 },
  { 129, 1 },
  { 129, 3 },
  { 131, 1 },
  { 131, 2 },
  { 132, 1 },
  { 132, 1 },
  { 132, 1 },
  { 132, 1 },
  { 132, 1 },
  { 133, 1 },
  { 133, 1 },
  { 134, 1 },
  { 134, 3 },
  { 134, 3 },
  { 134, 2 },
  { 141, 1 },
  { 141, 2 },
  { 141, 1 },
  { 141, 1 },
  { 141, 2 },
  { 141, 1 },
  { 141, 2 },
  { 141, 1 },
  { 141, 2 },
  { 141, 3 },
  { 135, 3 },
  { 135, 6 },
  { 140, 8 },
  { 136, 6 },
  { 137, 4 },
  { 137, 6 },
  { 142, 1 },
  { 142, 3 },
  { 138, 0 },
  { 138, 1 },
  { 139, 1 },
  { 139, 3 },
  { 168, 1 },
  { 168, 1 },
  { 147, 4 },
  { 147, 6 },
  { 147, 6 },
  { 145, 1 },
  { 145, 1 },
  { 146, 1 },
  { 146, 3 },
  { 145, 3 },
  { 144, 3 },
  { 148, 3 },
  { 149, 3 },
  { 150, 1 },
  { 150, 3 },
  { 151, 4 },
  { 143, 3 },
  { 153, 0 },
  { 153, 1 },
  { 154, 0 },
  { 154, 1 },
  { 155, 1 },
  { 155, 2 },
  { 156, 1 },
  { 157, 1 },
  { 157, 2 },
  { 158, 1 },
  { 158, 1 },
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
      case 0: /* block ::= LIB QUOTED_STRING EOS */
#line 180 "src/parser_proc.y"
{
 if (P->file.ln) {
  P->error(PSI_DATA(P), yymsp[-2].minor.yy0, PSI_WARNING, "Extra 'lib %s' statement has no effect", yymsp[-1].minor.yy0->text);
 } else {
  P->file.ln = strndup(yymsp[-1].minor.yy0->text + 1, yymsp[-1].minor.yy0->size - 2);
 }
 free(yymsp[-1].minor.yy0);
 free(yymsp[-2].minor.yy0);
}
#line 1906 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
        break;
      case 1: /* block ::= decl */
#line 189 "src/parser_proc.y"
{
 if (!P->decls) {
  P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
 }
 P->decls = psi_plist_add(P->decls, &yymsp[0].minor.yy17);
}
#line 1917 "src/parser_proc.c"
        break;
      case 2: /* block ::= impl */
#line 195 "src/parser_proc.y"
{
 if (!P->impls) {
  P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
 }
 P->impls = psi_plist_add(P->impls, &yymsp[0].minor.yy303);
}
#line 1927 "src/parser_proc.c"
        break;
      case 3: /* block ::= decl_typedef */
#line 201 "src/parser_proc.y"
{
 if (!P->types) {
  P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
 }
 P->types = psi_plist_add(P->types, &yymsp[0].minor.yy64);
 switch (yymsp[0].minor.yy64->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[0].minor.yy64->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy64->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[0].minor.yy64->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy64->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[0].minor.yy64->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy64->type->real.enm);
  }
  break;
 }
}
#line 1963 "src/parser_proc.c"
        break;
      case 4: /* block ::= constant */
#line 233 "src/parser_proc.y"
{
 if (!P->consts) {
  P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
 }
 P->consts = psi_plist_add(P->consts, &yymsp[0].minor.yy336);
}
#line 1973 "src/parser_proc.c"
        break;
      case 5: /* block ::= decl_struct */
#line 239 "src/parser_proc.y"
{
 if (!P->structs) {
  P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
 }
 P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy137);
}
#line 1983 "src/parser_proc.c"
        break;
      case 6: /* block ::= decl_union */
#line 245 "src/parser_proc.y"
{
 if (!P->unions) {
  P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
 }
 P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy47);
}
#line 1993 "src/parser_proc.c"
        break;
      case 7: /* block ::= decl_enum */
#line 251 "src/parser_proc.y"
{
 if (!P->enums) {
  P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
 }
 P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy87);
}
#line 2003 "src/parser_proc.c"
        break;
      case 8: /* optional_name ::= */
      case 42: /* decl_var_array_size ::= */ yytestcase(yyruleno==42);
      case 64: /* decl_scalar_type_short ::= */ yytestcase(yyruleno==64);
      case 68: /* decl_scalar_type_long ::= */ yytestcase(yyruleno==68);
      case 71: /* decl_scalar_type_long_long ::= */ yytestcase(yyruleno==71);
#line 257 "src/parser_proc.y"
{
 yymsp[1].minor.yy0 = NULL;
}
#line 2014 "src/parser_proc.c"
        break;
      case 9: /* optional_name ::= NAME */
      case 62: /* decl_scalar_type ::= CHAR */ yytestcase(yyruleno==62);
      case 65: /* decl_scalar_type_short ::= INT */ yytestcase(yyruleno==65);
      case 66: /* decl_scalar_type ::= INT */ yytestcase(yyruleno==66);
      case 69: /* decl_scalar_type_long ::= DOUBLE */ yytestcase(yyruleno==69);
      case 72: /* decl_scalar_type_long_long ::= INT */ yytestcase(yyruleno==72);
      case 131: /* callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT */ yytestcase(yyruleno==131);
      case 132: /* callback_rval ::= VOID */ yytestcase(yyruleno==132);
#line 260 "src/parser_proc.y"
{
 yylhsminor.yy0 = yymsp[0].minor.yy0;
}
#line 2028 "src/parser_proc.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* align_and_size ::= */
#line 263 "src/parser_proc.y"
{
 yymsp[1].minor.yy207.pos = 0;
 yymsp[1].minor.yy207.len = 0;
}
#line 2037 "src/parser_proc.c"
        break;
      case 11: /* align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,74,&yymsp[-6].minor);
#line 267 "src/parser_proc.y"
{
 yymsp[-6].minor.yy207.pos = atol(yymsp[-3].minor.yy0->text);
 yymsp[-6].minor.yy207.len = atol(yymsp[-1].minor.yy0->text);
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2048 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-5].minor);
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
}
        break;
      case 12: /* enum_name ::= ENUM optional_name */
      case 13: /* struct_name ::= STRUCT optional_name */ yytestcase(yyruleno==13);
      case 14: /* union_name ::= UNION optional_name */ yytestcase(yyruleno==14);
#line 273 "src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = yymsp[0].minor.yy0;
  free(yymsp[-1].minor.yy0);
 } else {
  char digest[17];
  psi_token_hash(yymsp[-1].minor.yy0, digest);
  yylhsminor.yy0 = psi_token_translit(psi_token_append(yymsp[-1].minor.yy0, 1, digest), " ", "@");
 }
}
#line 2069 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* decl_enum ::= enum_name LBRACE decl_enum_items RBRACE */
#line 303 "src/parser_proc.y"
{
 yylhsminor.yy87 = psi_decl_enum_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy7);
 yylhsminor.yy87->token = yymsp[-3].minor.yy0;
}
#line 2078 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,82,&yymsp[0].minor);
  yymsp[-3].minor.yy87 = yylhsminor.yy87;
        break;
      case 16: /* decl_enum_items ::= decl_enum_item */
#line 307 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
   &yymsp[0].minor.yy109);
}
#line 2089 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 17: /* decl_enum_items ::= decl_enum_items COMMA decl_enum_item */
#line 311 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy109);
}
#line 2097 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 18: /* decl_enum_item ::= NAME EQUALS num_exp */
#line 314 "src/parser_proc.y"
{
 yylhsminor.yy109 = psi_decl_enum_item_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy124);
 yylhsminor.yy109->token = yymsp[-2].minor.yy0;
}
#line 2107 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-1].minor);
  yymsp[-2].minor.yy109 = yylhsminor.yy109;
        break;
      case 19: /* decl_enum_item ::= NAME */
#line 318 "src/parser_proc.y"
{
 yylhsminor.yy109 = psi_decl_enum_item_init(yymsp[0].minor.yy0->text, NULL);
 yylhsminor.yy109->token = yymsp[0].minor.yy0;
}
#line 2117 "src/parser_proc.c"
  yymsp[0].minor.yy109 = yylhsminor.yy109;
        break;
      case 20: /* decl_struct_args_block ::= LBRACE struct_args RBRACE */
{  yy_destructor(yypParser,81,&yymsp[-2].minor);
#line 322 "src/parser_proc.y"
{
 yymsp[-2].minor.yy7 = yymsp[-1].minor.yy7;
}
#line 2126 "src/parser_proc.c"
  yy_destructor(yypParser,82,&yymsp[0].minor);
}
        break;
      case 21: /* decl_struct_args ::= decl_struct_args_block */
#line 325 "src/parser_proc.y"
{
 yylhsminor.yy7 = yymsp[0].minor.yy7;
}
#line 2135 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 22: /* decl_struct_args ::= EOS */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 328 "src/parser_proc.y"
{
 yymsp[0].minor.yy7 = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}
#line 2144 "src/parser_proc.c"
}
        break;
      case 23: /* decl_struct ::= STRUCT NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,79,&yymsp[-3].minor);
#line 331 "src/parser_proc.y"
{
 yymsp[-3].minor.yy137 = psi_decl_struct_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy7);
 yymsp[-3].minor.yy137->align = yymsp[-1].minor.yy207.pos;
 yymsp[-3].minor.yy137->size = yymsp[-1].minor.yy207.len;
 yymsp[-3].minor.yy137->token = yymsp[-2].minor.yy0;
}
#line 2156 "src/parser_proc.c"
}
        break;
      case 24: /* decl_union ::= UNION NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,80,&yymsp[-3].minor);
#line 337 "src/parser_proc.y"
{
 yymsp[-3].minor.yy47 = psi_decl_union_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy7);
 yymsp[-3].minor.yy47->align = yymsp[-1].minor.yy207.pos;
 yymsp[-3].minor.yy47->size = yymsp[-1].minor.yy207.len;
 yymsp[-3].minor.yy47->token = yymsp[-2].minor.yy0;
}
#line 2168 "src/parser_proc.c"
}
        break;
      case 25: /* const_type ::= BOOL|INT|FLOAT|STRING */
#line 343 "src/parser_proc.y"
{
 yylhsminor.yy181 = psi_const_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2177 "src/parser_proc.c"
  yymsp[0].minor.yy181 = yylhsminor.yy181;
        break;
      case 26: /* constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS */
{  yy_destructor(yypParser,84,&yymsp[-5].minor);
#line 347 "src/parser_proc.y"
{
 yymsp[-5].minor.yy336 = psi_const_init(yymsp[-4].minor.yy181, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy319);
 yymsp[-5].minor.yy336->token = yymsp[-3].minor.yy0;
}
#line 2187 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-2].minor);
  yy_destructor(yypParser,73,&yymsp[0].minor);
}
        break;
      case 27: /* decl_typedef ::= TYPEDEF decl_typedef_body EOS */
#line 351 "src/parser_proc.y"
{
 yylhsminor.yy64 = yymsp[-1].minor.yy64;
 yylhsminor.yy64->token = yymsp[-2].minor.yy0;
}
#line 2198 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy64 = yylhsminor.yy64;
        break;
      case 28: /* decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var */
#line 355 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy131);
 yylhsminor.yy64->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy64->type->real.strct = psi_decl_struct_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy7);
 yylhsminor.yy64->type->real.strct->token = yymsp[-3].minor.yy0;
 yylhsminor.yy64->type->real.strct->align = yymsp[-2].minor.yy207.pos;
 yylhsminor.yy64->type->real.strct->size = yymsp[-2].minor.yy207.len;
}
#line 2212 "src/parser_proc.c"
  yymsp[-3].minor.yy64 = yylhsminor.yy64;
        break;
      case 29: /* decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var */
#line 363 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy131);
 yylhsminor.yy64->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy64->type->real.unn = psi_decl_union_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy7);
 yylhsminor.yy64->type->real.unn->token = yymsp[-3].minor.yy0;
 yylhsminor.yy64->type->real.unn->align = yymsp[-2].minor.yy207.pos;
 yylhsminor.yy64->type->real.unn->size = yymsp[-2].minor.yy207.len;
}
#line 2225 "src/parser_proc.c"
  yymsp[-3].minor.yy64 = yylhsminor.yy64;
        break;
      case 30: /* decl_typedef_body_ex ::= decl_enum NAME */
#line 371 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, yymsp[-1].minor.yy87->name), psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0));
 yylhsminor.yy64->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy64->type->token = psi_token_copy(yymsp[-1].minor.yy87->token);
 yylhsminor.yy64->type->real.enm = yymsp[-1].minor.yy87;
}
#line 2236 "src/parser_proc.c"
  yymsp[-1].minor.yy64 = yylhsminor.yy64;
        break;
      case 31: /* decl_typedef_body ::= decl_typedef_body_ex */
      case 34: /* decl_typedef_body ::= decl_arg */ yytestcase(yyruleno==34);
      case 37: /* decl_func ::= decl_arg */ yytestcase(yyruleno==37);
#line 377 "src/parser_proc.y"
{
 yylhsminor.yy64 = yymsp[0].minor.yy64;
}
#line 2246 "src/parser_proc.c"
  yymsp[0].minor.yy64 = yylhsminor.yy64;
        break;
      case 32: /* decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN */
{  yy_destructor(yypParser,75,&yymsp[-2].minor);
#line 380 "src/parser_proc.y"
{
 yymsp[-2].minor.yy7 = yymsp[-1].minor.yy7;
}
#line 2255 "src/parser_proc.c"
  yy_destructor(yypParser,77,&yymsp[0].minor);
}
        break;
      case 33: /* decl_typedef_body ::= decl_func decl_typedef_body_fn_args */
#line 383 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, yymsp[-1].minor.yy64->var->name), psi_decl_var_copy(yymsp[-1].minor.yy64->var));
 yylhsminor.yy64->type->token = psi_token_copy(yymsp[-1].minor.yy64->token);
 yylhsminor.yy64->type->real.func = psi_decl_init(psi_decl_abi_init("default"), yymsp[-1].minor.yy64, yymsp[0].minor.yy7);
}
#line 2266 "src/parser_proc.c"
  yymsp[-1].minor.yy64 = yylhsminor.yy64;
        break;
      case 35: /* decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS */
#line 391 "src/parser_proc.y"
{
 yylhsminor.yy17 = psi_decl_init(yymsp[-5].minor.yy180, yymsp[-4].minor.yy64, yymsp[-2].minor.yy7);
}
#line 2274 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-3].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-5].minor.yy17 = yylhsminor.yy17;
        break;
      case 36: /* decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS */
#line 394 "src/parser_proc.y"
{
 yylhsminor.yy17 = psi_decl_init(yymsp[-7].minor.yy180, yymsp[-6].minor.yy64, yymsp[-4].minor.yy7);
 yylhsminor.yy17->varargs = 1;
}
#line 2286 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-5].minor);
  yy_destructor(yypParser,76,&yymsp[-3].minor);
  yy_destructor(yypParser,86,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-7].minor.yy17 = yylhsminor.yy17;
        break;
      case 38: /* decl_func ::= VOID NAME */
#line 401 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[-1].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0)
 );
 yylhsminor.yy64->type->token = yymsp[-1].minor.yy0;
 yylhsminor.yy64->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy64->token = yymsp[0].minor.yy0;
}
#line 2305 "src/parser_proc.c"
  yymsp[-1].minor.yy64 = yylhsminor.yy64;
        break;
      case 39: /* decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 410 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy296, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy64->var->pointer_level = yymsp[-3].minor.yy296;
 yylhsminor.yy64->type->token = psi_token_copy(func_->token);
 yylhsminor.yy64->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy7);
}
#line 2326 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
  yymsp[-6].minor.yy64 = yylhsminor.yy64;
        break;
      case 40: /* decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
{  yy_destructor(yypParser,84,&yymsp[-7].minor);
#line 426 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy296, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yymsp[-7].minor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yymsp[-7].minor.yy64->var->pointer_level = yymsp[-3].minor.yy296;
 yymsp[-7].minor.yy64->type->token = psi_token_copy(func_->token);
 yymsp[-7].minor.yy64->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy7);
}
#line 2350 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
}
        break;
      case 41: /* decl_abi ::= NAME */
#line 442 "src/parser_proc.y"
{
 yylhsminor.yy180 = psi_decl_abi_init(yymsp[0].minor.yy0->text);
 yylhsminor.yy180->token = yymsp[0].minor.yy0;
}
#line 2361 "src/parser_proc.c"
  yymsp[0].minor.yy180 = yylhsminor.yy180;
        break;
      case 43: /* decl_var_array_size ::= LBRACKET NUMBER RBRACKET */
{  yy_destructor(yypParser,87,&yymsp[-2].minor);
#line 449 "src/parser_proc.y"
{
 yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
}
#line 2370 "src/parser_proc.c"
  yy_destructor(yypParser,88,&yymsp[0].minor);
}
        break;
      case 44: /* decl_var ::= NAME decl_var_array_size */
#line 452 "src/parser_proc.y"
{
 yylhsminor.yy131 = psi_decl_var_init(yymsp[-1].minor.yy0->text, 0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy131->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2383 "src/parser_proc.c"
  yymsp[-1].minor.yy131 = yylhsminor.yy131;
        break;
      case 45: /* decl_var ::= pointers NAME decl_var_array_size */
#line 459 "src/parser_proc.y"
{
 yylhsminor.yy131 = psi_decl_var_init(yymsp[-1].minor.yy0->text, yymsp[-2].minor.yy296+!!yymsp[0].minor.yy0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy131->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2395 "src/parser_proc.c"
  yymsp[-2].minor.yy131 = yylhsminor.yy131;
        break;
      case 46: /* decl_vars ::= decl_var */
#line 466 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
   &yymsp[0].minor.yy131);
}
#line 2404 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 47: /* decl_vars ::= decl_vars COMMA decl_var */
#line 470 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy131);
}
#line 2412 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 48: /* decl_arg ::= const_decl_type decl_var */
#line 473 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(yymsp[-1].minor.yy182, yymsp[0].minor.yy131);
}
#line 2421 "src/parser_proc.c"
  yymsp[-1].minor.yy64 = yylhsminor.yy64;
        break;
      case 49: /* decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 476 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  yymsp[-6].minor.yy182,
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy296, 0)
 );
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy64->var->pointer_level = yymsp[-3].minor.yy296;
 yylhsminor.yy64->type->token = psi_token_copy(func_->token);
 yylhsminor.yy64->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy7);
}
#line 2441 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
  yymsp[-6].minor.yy64 = yylhsminor.yy64;
        break;
      case 50: /* decl_arg ::= VOID pointers NAME */
#line 491 "src/parser_proc.y"
{
 yylhsminor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy296, 0)
 );
 yylhsminor.yy64->type->token = yymsp[-2].minor.yy0;
 yylhsminor.yy64->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy64->token = yymsp[0].minor.yy0;
}
#line 2457 "src/parser_proc.c"
  yymsp[-2].minor.yy64 = yylhsminor.yy64;
        break;
      case 51: /* decl_arg ::= CONST VOID pointers NAME */
{  yy_destructor(yypParser,84,&yymsp[-3].minor);
#line 500 "src/parser_proc.y"
{
 yymsp[-3].minor.yy64 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy296, 0)
 );
 yymsp[-3].minor.yy64->type->token = yymsp[-2].minor.yy0;
 yymsp[-3].minor.yy64->var->token = yymsp[0].minor.yy0;
 yymsp[-3].minor.yy64->token = yymsp[0].minor.yy0;
}
#line 2472 "src/parser_proc.c"
}
        break;
      case 52: /* decl_args ::= */
#line 509 "src/parser_proc.y"
{
 yymsp[1].minor.yy7 = NULL;
}
#line 2480 "src/parser_proc.c"
        break;
      case 53: /* decl_args ::= VOID */
{  yy_destructor(yypParser,57,&yymsp[0].minor);
#line 512 "src/parser_proc.y"
{
 yymsp[0].minor.yy7 = NULL;
}
#line 2488 "src/parser_proc.c"
}
        break;
      case 54: /* decl_args ::= decl_arg */
      case 56: /* struct_args ::= struct_arg */ yytestcase(yyruleno==56);
#line 515 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &yymsp[0].minor.yy64);
}
#line 2498 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 55: /* decl_args ::= decl_args COMMA decl_arg */
#line 519 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy64);
}
#line 2506 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 57: /* struct_args ::= struct_args struct_arg */
#line 526 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-1].minor.yy7, &yymsp[0].minor.yy64);
}
#line 2515 "src/parser_proc.c"
  yymsp[-1].minor.yy7 = yylhsminor.yy7;
        break;
      case 58: /* struct_arg ::= decl_typedef_body_ex EOS */
#line 529 "src/parser_proc.y"
{
 yylhsminor.yy64 = yymsp[-1].minor.yy64;
 switch (yymsp[-1].minor.yy64->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[-1].minor.yy64->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[-1].minor.yy64->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[-1].minor.yy64->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[-1].minor.yy64->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[-1].minor.yy64->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[-1].minor.yy64->type->real.enm);
  }
  break;
 }
}
#line 2549 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-1].minor.yy64 = yylhsminor.yy64;
        break;
      case 59: /* struct_arg ::= decl_arg decl_layout EOS */
#line 558 "src/parser_proc.y"
{
 yymsp[-2].minor.yy64->layout = yymsp[-1].minor.yy221;
 yylhsminor.yy64 = yymsp[-2].minor.yy64;
}
#line 2559 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy64 = yylhsminor.yy64;
        break;
      case 60: /* decl_layout ::= */
#line 562 "src/parser_proc.y"
{
 yymsp[1].minor.yy221 = NULL;
}
#line 2568 "src/parser_proc.c"
        break;
      case 61: /* decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,74,&yymsp[-6].minor);
#line 565 "src/parser_proc.y"
{
 yymsp[-6].minor.yy221 = psi_layout_init(atol(yymsp[-3].minor.yy0->text), atol(yymsp[-1].minor.yy0->text));
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2578 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-5].minor);
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
}
        break;
      case 63: /* decl_scalar_type ::= SHORT decl_scalar_type_short */
      case 67: /* decl_scalar_type ::= LONG decl_scalar_type_long */ yytestcase(yyruleno==67);
      case 70: /* decl_scalar_type_long ::= LONG decl_scalar_type_long_long */ yytestcase(yyruleno==70);
#line 573 "src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
  free(yymsp[-1].minor.yy0);
  free(yymsp[0].minor.yy0);
 } else {
  yylhsminor.yy0 = yymsp[-1].minor.yy0;
 }
}
#line 2598 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* decl_type ::= UNSIGNED decl_scalar_type */
      case 74: /* decl_type ::= SIGNED decl_scalar_type */ yytestcase(yyruleno==74);
#line 621 "src/parser_proc.y"
{
 struct psi_token *T = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
 yylhsminor.yy182 = psi_decl_type_init(T->type, T->text);
 yylhsminor.yy182->token = T;
 free(yymsp[-1].minor.yy0);
 free(yymsp[0].minor.yy0);
}
#line 2611 "src/parser_proc.c"
  yymsp[-1].minor.yy182 = yylhsminor.yy182;
        break;
      case 75: /* decl_type ::= UNSIGNED */
      case 76: /* decl_type ::= SIGNED */ yytestcase(yyruleno==76);
#line 635 "src/parser_proc.y"
{
 yylhsminor.yy182 = psi_decl_type_init(PSI_T_NAME, yymsp[0].minor.yy0->text);
 yylhsminor.yy182->token = yymsp[0].minor.yy0;
}
#line 2621 "src/parser_proc.c"
  yymsp[0].minor.yy182 = yylhsminor.yy182;
        break;
      case 77: /* decl_type ::= decl_scalar_type */
      case 81: /* decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME */ yytestcase(yyruleno==81);
#line 643 "src/parser_proc.y"
{
 yylhsminor.yy182 = psi_decl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy182->token = yymsp[0].minor.yy0;
}
#line 2631 "src/parser_proc.c"
  yymsp[0].minor.yy182 = yylhsminor.yy182;
        break;
      case 78: /* decl_type ::= STRUCT NAME */
      case 79: /* decl_type ::= UNION NAME */ yytestcase(yyruleno==79);
      case 80: /* decl_type ::= ENUM NAME */ yytestcase(yyruleno==80);
#line 647 "src/parser_proc.y"
{
 yylhsminor.yy182 = psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy182->token = yymsp[0].minor.yy0;
 free(yymsp[-1].minor.yy0);
}
#line 2643 "src/parser_proc.c"
  yymsp[-1].minor.yy182 = yylhsminor.yy182;
        break;
      case 82: /* const_decl_type ::= decl_type */
#line 666 "src/parser_proc.y"
{
 yylhsminor.yy182 = yymsp[0].minor.yy182;
}
#line 2651 "src/parser_proc.c"
  yymsp[0].minor.yy182 = yylhsminor.yy182;
        break;
      case 83: /* const_decl_type ::= CONST decl_type */
{  yy_destructor(yypParser,84,&yymsp[-1].minor);
#line 669 "src/parser_proc.y"
{
 yymsp[-1].minor.yy182 = yymsp[0].minor.yy182;
}
#line 2660 "src/parser_proc.c"
}
        break;
      case 84: /* impl ::= impl_func LBRACE impl_stmts RBRACE */
#line 672 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_impl_init(yymsp[-3].minor.yy226, yymsp[-1].minor.yy7);
}
#line 2668 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,82,&yymsp[0].minor);
  yymsp[-3].minor.yy303 = yylhsminor.yy303;
        break;
      case 85: /* impl ::= STATIC impl_func LBRACE impl_stmts RBRACE */
{  yy_destructor(yypParser,94,&yymsp[-4].minor);
#line 675 "src/parser_proc.y"
{
 yymsp[-3].minor.yy226->static_memory = 1;
 yymsp[-4].minor.yy303 = psi_impl_init(yymsp[-3].minor.yy226, yymsp[-1].minor.yy7);
}
#line 2680 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,82,&yymsp[0].minor);
}
        break;
      case 86: /* impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type */
{  yy_destructor(yypParser,95,&yymsp[-6].minor);
#line 679 "src/parser_proc.y"
{
 yymsp[-6].minor.yy226 = psi_impl_func_init(yymsp[-4].minor.yy0->text, NULL, yymsp[0].minor.yy40);
 yymsp[-6].minor.yy226->token = yymsp[-4].minor.yy0;
 yymsp[-6].minor.yy226->return_reference = yymsp[-5].minor.yy247;
}
#line 2693 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-3].minor);
  yy_destructor(yypParser,77,&yymsp[-2].minor);
  yy_destructor(yypParser,74,&yymsp[-1].minor);
}
        break;
      case 87: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type */
{  yy_destructor(yypParser,95,&yymsp[-7].minor);
#line 684 "src/parser_proc.y"
{
 yymsp[-7].minor.yy226 = psi_impl_func_init(yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy7, yymsp[0].minor.yy40);
 yymsp[-7].minor.yy226->token = yymsp[-5].minor.yy0;
 yymsp[-7].minor.yy226->return_reference = yymsp[-6].minor.yy247;
}
#line 2707 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,77,&yymsp[-2].minor);
  yy_destructor(yypParser,74,&yymsp[-1].minor);
}
        break;
      case 88: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type */
{  yy_destructor(yypParser,95,&yymsp[-12].minor);
#line 689 "src/parser_proc.y"
{
 yymsp[-12].minor.yy226 = psi_impl_func_init(yymsp[-10].minor.yy0->text, yymsp[-8].minor.yy7, yymsp[0].minor.yy40);
 yymsp[-12].minor.yy226->token = yymsp[-10].minor.yy0;
 yymsp[-12].minor.yy226->return_reference = yymsp[-11].minor.yy247;
 yymsp[-12].minor.yy226->vararg = psi_impl_arg_init(yymsp[-6].minor.yy40, psi_impl_var_init(yymsp[-3].minor.yy0->text, yymsp[-5].minor.yy247), NULL);
 free(yymsp[-3].minor.yy0);
}
#line 2723 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-9].minor);
  yy_destructor(yypParser,76,&yymsp[-7].minor);
  yy_destructor(yypParser,86,&yymsp[-4].minor);
  yy_destructor(yypParser,77,&yymsp[-2].minor);
  yy_destructor(yypParser,74,&yymsp[-1].minor);
}
        break;
      case 89: /* impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING */
#line 696 "src/parser_proc.y"
{
 yylhsminor.yy319 = psi_impl_def_val_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy319->token = yymsp[0].minor.yy0;
}
#line 2737 "src/parser_proc.c"
  yymsp[0].minor.yy319 = yylhsminor.yy319;
        break;
      case 90: /* impl_var ::= reference DOLLAR_NAME */
#line 700 "src/parser_proc.y"
{
 yylhsminor.yy123 = psi_impl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy247);
 yylhsminor.yy123->token = yymsp[0].minor.yy0;
}
#line 2746 "src/parser_proc.c"
  yymsp[-1].minor.yy123 = yylhsminor.yy123;
        break;
      case 91: /* impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE */
#line 704 "src/parser_proc.y"
{
 yylhsminor.yy40 = psi_impl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2755 "src/parser_proc.c"
  yymsp[0].minor.yy40 = yylhsminor.yy40;
        break;
      case 92: /* impl_arg ::= impl_type impl_var */
#line 708 "src/parser_proc.y"
{
 yylhsminor.yy56 = psi_impl_arg_init(yymsp[-1].minor.yy40, yymsp[0].minor.yy123, NULL);
}
#line 2763 "src/parser_proc.c"
  yymsp[-1].minor.yy56 = yylhsminor.yy56;
        break;
      case 93: /* impl_arg ::= impl_type impl_var EQUALS impl_def_val */
#line 711 "src/parser_proc.y"
{
 yylhsminor.yy56 = psi_impl_arg_init(yymsp[-3].minor.yy40, yymsp[-2].minor.yy123, yymsp[0].minor.yy319);
}
#line 2771 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-1].minor);
  yymsp[-3].minor.yy56 = yylhsminor.yy56;
        break;
      case 94: /* impl_args ::= impl_arg */
#line 714 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
   &yymsp[0].minor.yy56);
}
#line 2781 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 95: /* impl_args ::= impl_args COMMA impl_arg */
#line 718 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy56);
}
#line 2789 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 96: /* impl_stmts ::= impl_stmt */
#line 721 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
   &yymsp[0].minor.yy282);
}
#line 2799 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 97: /* impl_stmts ::= impl_stmts impl_stmt */
#line 725 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-1].minor.yy7, &yymsp[0].minor.yy282);
}
#line 2807 "src/parser_proc.c"
  yymsp[-1].minor.yy7 = yylhsminor.yy7;
        break;
      case 98: /* impl_stmt ::= return_stmt */
#line 728 "src/parser_proc.y"
{
 yylhsminor.yy282 = (struct psi_token**) yymsp[0].minor.yy258;
}
#line 2815 "src/parser_proc.c"
  yymsp[0].minor.yy282 = yylhsminor.yy282;
        break;
      case 99: /* impl_stmt ::= let_stmt */
#line 731 "src/parser_proc.y"
{
 yylhsminor.yy282 = (struct psi_token**) yymsp[0].minor.yy138;
}
#line 2823 "src/parser_proc.c"
  yymsp[0].minor.yy282 = yylhsminor.yy282;
        break;
      case 100: /* impl_stmt ::= set_stmt */
#line 734 "src/parser_proc.y"
{
 yylhsminor.yy282 = (struct psi_token**) yymsp[0].minor.yy300;
}
#line 2831 "src/parser_proc.c"
  yymsp[0].minor.yy282 = yylhsminor.yy282;
        break;
      case 101: /* impl_stmt ::= assert_stmt */
#line 737 "src/parser_proc.y"
{
 yylhsminor.yy282 = (struct psi_token **) yymsp[0].minor.yy146;
}
#line 2839 "src/parser_proc.c"
  yymsp[0].minor.yy282 = yylhsminor.yy282;
        break;
      case 102: /* impl_stmt ::= free_stmt */
#line 740 "src/parser_proc.y"
{
 yylhsminor.yy282 = (struct psi_token**) yymsp[0].minor.yy102;
}
#line 2847 "src/parser_proc.c"
  yymsp[0].minor.yy282 = yylhsminor.yy282;
        break;
      case 103: /* number ::= NUMBER|NSNAME */
#line 743 "src/parser_proc.y"
{
 yylhsminor.yy66 = psi_number_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy66->token = yymsp[0].minor.yy0;
}
#line 2856 "src/parser_proc.c"
  yymsp[0].minor.yy66 = yylhsminor.yy66;
        break;
      case 104: /* number ::= decl_var */
#line 747 "src/parser_proc.y"
{
 yylhsminor.yy66 = psi_number_init(PSI_T_NAME, yymsp[0].minor.yy131);
 yylhsminor.yy66->token = psi_token_copy(yymsp[0].minor.yy131->token);
}
#line 2865 "src/parser_proc.c"
  yymsp[0].minor.yy66 = yylhsminor.yy66;
        break;
      case 105: /* num_exp ::= number */
#line 751 "src/parser_proc.y"
{
 yylhsminor.yy124 = psi_num_exp_init_num(yymsp[0].minor.yy66);
 yylhsminor.yy124->token = psi_token_copy(yymsp[0].minor.yy66->token);
}
#line 2874 "src/parser_proc.c"
  yymsp[0].minor.yy124 = yylhsminor.yy124;
        break;
      case 106: /* num_exp ::= LPAREN num_exp RPAREN */
#line 755 "src/parser_proc.y"
{
 yylhsminor.yy124 = psi_num_exp_init_unary(PSI_T_LPAREN, yymsp[-1].minor.yy124);
 yylhsminor.yy124->token = yymsp[-2].minor.yy0;
}
#line 2883 "src/parser_proc.c"
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-2].minor.yy124 = yylhsminor.yy124;
        break;
      case 107: /* num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp */
#line 759 "src/parser_proc.y"
{
 yylhsminor.yy124 = psi_num_exp_init_binary(yymsp[-1].minor.yy0->type, yymsp[-2].minor.yy124, yymsp[0].minor.yy124);
 yylhsminor.yy124->token = yymsp[-1].minor.yy0;
}
#line 2893 "src/parser_proc.c"
  yymsp[-2].minor.yy124 = yylhsminor.yy124;
        break;
      case 108: /* num_exp ::= TILDE|NOT|PLUS|MINUS num_exp */
#line 763 "src/parser_proc.y"
{
 yylhsminor.yy124 = psi_num_exp_init_unary(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy124);
 yylhsminor.yy124->token = yymsp[-1].minor.yy0;
}
#line 2902 "src/parser_proc.c"
  yymsp[-1].minor.yy124 = yylhsminor.yy124;
        break;
      case 109: /* let_exp ::= NULL */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 767 "src/parser_proc.y"
{
 yymsp[0].minor.yy196 = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 2911 "src/parser_proc.c"
}
        break;
      case 110: /* let_exp ::= AMPERSAND NULL */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 770 "src/parser_proc.y"
{
 yymsp[-1].minor.yy196 = psi_let_exp_init(PSI_LET_NULL, NULL);
 yymsp[-1].minor.yy196->is_reference = 1;
}
#line 2921 "src/parser_proc.c"
  yy_destructor(yypParser,15,&yymsp[0].minor);
}
        break;
      case 111: /* let_exp ::= let_callback */
#line 774 "src/parser_proc.y"
{
 yylhsminor.yy196 = psi_let_exp_init(PSI_LET_CALLBACK, yymsp[0].minor.yy76);
}
#line 2930 "src/parser_proc.c"
  yymsp[0].minor.yy196 = yylhsminor.yy196;
        break;
      case 112: /* let_exp ::= let_calloc */
#line 777 "src/parser_proc.y"
{
 yylhsminor.yy196 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy227);
}
#line 2938 "src/parser_proc.c"
  yymsp[0].minor.yy196 = yylhsminor.yy196;
        break;
      case 113: /* let_exp ::= AMPERSAND let_calloc */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 780 "src/parser_proc.y"
{
 yymsp[-1].minor.yy196 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy227);
 yymsp[-1].minor.yy196->is_reference = 1;
}
#line 2948 "src/parser_proc.c"
}
        break;
      case 114: /* let_exp ::= let_func */
#line 784 "src/parser_proc.y"
{
 yylhsminor.yy196 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy133);
}
#line 2956 "src/parser_proc.c"
  yymsp[0].minor.yy196 = yylhsminor.yy196;
        break;
      case 115: /* let_exp ::= AMPERSAND let_func */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 787 "src/parser_proc.y"
{
 yymsp[-1].minor.yy196 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy133);
 yymsp[-1].minor.yy196->is_reference = 1;
}
#line 2966 "src/parser_proc.c"
}
        break;
      case 116: /* let_exp ::= num_exp */
#line 791 "src/parser_proc.y"
{
 yylhsminor.yy196 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy124);
}
#line 2974 "src/parser_proc.c"
  yymsp[0].minor.yy196 = yylhsminor.yy196;
        break;
      case 117: /* let_exp ::= AMPERSAND num_exp */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 794 "src/parser_proc.y"
{
 yymsp[-1].minor.yy196 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy124);
 yymsp[-1].minor.yy196->is_reference = 1;
}
#line 2984 "src/parser_proc.c"
}
        break;
      case 118: /* let_exp ::= decl_var EQUALS let_exp */
#line 798 "src/parser_proc.y"
{
 yylhsminor.yy196 = yymsp[0].minor.yy196;
 yylhsminor.yy196->var = yymsp[-2].minor.yy131;
}
#line 2993 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-1].minor);
  yymsp[-2].minor.yy196 = yylhsminor.yy196;
        break;
      case 119: /* let_stmt ::= LET let_exp EOS */
#line 802 "src/parser_proc.y"
{
 yylhsminor.yy138 = psi_let_stmt_init(yymsp[-1].minor.yy196);
 yylhsminor.yy138->token = yymsp[-2].minor.yy0;
}
#line 3003 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy138 = yylhsminor.yy138;
        break;
      case 120: /* let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS */
#line 806 "src/parser_proc.y"
{
 yylhsminor.yy138 = psi_let_stmt_init(psi_let_exp_init_ex(yymsp[-4].minor.yy131, PSI_LET_TMP, yymsp[-1].minor.yy131));
 yylhsminor.yy138->token = yymsp[-5].minor.yy0;
 yylhsminor.yy138->exp->is_reference = yymsp[-2].minor.yy247 ? 1 : 0;
}
#line 3014 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-3].minor);
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-5].minor.yy138 = yylhsminor.yy138;
        break;
      case 121: /* let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN */
#line 811 "src/parser_proc.y"
{
 yylhsminor.yy76 = psi_let_callback_init(psi_let_func_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text, yymsp[-4].minor.yy123), yymsp[-2].minor.yy304);
 yylhsminor.yy76->token = yymsp[-7].minor.yy0;
 free(yymsp[-6].minor.yy0);
}
#line 3026 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-5].minor);
  yy_destructor(yypParser,75,&yymsp[-3].minor);
  yy_destructor(yypParser,77,&yymsp[-1].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-7].minor.yy76 = yylhsminor.yy76;
        break;
      case 122: /* let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN */
#line 816 "src/parser_proc.y"
{
 yylhsminor.yy227 = psi_let_calloc_init(yymsp[-3].minor.yy124, yymsp[-1].minor.yy124);
 yylhsminor.yy227->token = yymsp[-5].minor.yy0;
}
#line 3039 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-5].minor.yy227 = yylhsminor.yy227;
        break;
      case 123: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN */
#line 820 "src/parser_proc.y"
{
 yylhsminor.yy133 = psi_let_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy123);
 yylhsminor.yy133->token = yymsp[-3].minor.yy0;
}
#line 3051 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-3].minor.yy133 = yylhsminor.yy133;
        break;
      case 124: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN */
#line 824 "src/parser_proc.y"
{
 yylhsminor.yy133 = psi_let_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy123);
 yylhsminor.yy133->token = yymsp[-5].minor.yy0;
 yylhsminor.yy133->inner = yymsp[-1].minor.yy7;
}
#line 3063 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-5].minor.yy133 = yylhsminor.yy133;
        break;
      case 125: /* let_exps ::= let_exp */
#line 829 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
   &yymsp[0].minor.yy196);
}
#line 3075 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 126: /* let_exps ::= let_exps COMMA let_exp */
#line 833 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy196);
}
#line 3083 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 127: /* callback_arg_list ::= */
#line 836 "src/parser_proc.y"
{
 yymsp[1].minor.yy304 = NULL;
}
#line 3092 "src/parser_proc.c"
        break;
      case 128: /* callback_arg_list ::= callback_args */
#line 839 "src/parser_proc.y"
{
 yylhsminor.yy304 = yymsp[0].minor.yy304;
}
#line 3099 "src/parser_proc.c"
  yymsp[0].minor.yy304 = yylhsminor.yy304;
        break;
      case 129: /* callback_args ::= set_exp */
#line 842 "src/parser_proc.y"
{
 yylhsminor.yy304 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy113);
}
#line 3108 "src/parser_proc.c"
  yymsp[0].minor.yy304 = yylhsminor.yy304;
        break;
      case 130: /* callback_args ::= callback_args COMMA set_exp */
#line 846 "src/parser_proc.y"
{
 yylhsminor.yy304 = psi_plist_add(yymsp[-2].minor.yy304, &yymsp[0].minor.yy113);
}
#line 3116 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy304 = yylhsminor.yy304;
        break;
      case 133: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN */
#line 855 "src/parser_proc.y"
{
 yylhsminor.yy324 = psi_set_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy131);
 yylhsminor.yy324->token = yymsp[-3].minor.yy0;
}
#line 3126 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-3].minor.yy324 = yylhsminor.yy324;
        break;
      case 134: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN */
#line 859 "src/parser_proc.y"
{
 yylhsminor.yy324 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy131);
 yylhsminor.yy324->token = yymsp[-5].minor.yy0;
 yylhsminor.yy324->inner = yymsp[-1].minor.yy7;
}
#line 3138 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-5].minor.yy324 = yylhsminor.yy324;
        break;
      case 135: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN */
#line 864 "src/parser_proc.y"
{
 yylhsminor.yy324 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy131);
 yylhsminor.yy324->token = yymsp[-5].minor.yy0;
 yylhsminor.yy324->recursive = 1;
}
#line 3151 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-4].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,86,&yymsp[-1].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-5].minor.yy324 = yylhsminor.yy324;
        break;
      case 136: /* set_exp ::= set_func */
#line 869 "src/parser_proc.y"
{
 yylhsminor.yy113 = psi_set_exp_init(PSI_SET_FUNC, yymsp[0].minor.yy324);
}
#line 3163 "src/parser_proc.c"
  yymsp[0].minor.yy113 = yylhsminor.yy113;
        break;
      case 137: /* set_exp ::= num_exp */
#line 872 "src/parser_proc.y"
{
 yylhsminor.yy113 = psi_set_exp_init(PSI_SET_NUMEXP, yymsp[0].minor.yy124);
}
#line 3171 "src/parser_proc.c"
  yymsp[0].minor.yy113 = yylhsminor.yy113;
        break;
      case 138: /* set_exps ::= set_exp */
#line 875 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy113);
}
#line 3180 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 139: /* set_exps ::= set_exps COMMA set_exp */
#line 879 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy113);
}
#line 3188 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 140: /* set_exp ::= impl_var EQUALS set_exp */
#line 882 "src/parser_proc.y"
{
 yylhsminor.yy113 = yymsp[0].minor.yy113;
 yylhsminor.yy113->var = yymsp[-2].minor.yy123;
}
#line 3198 "src/parser_proc.c"
  yy_destructor(yypParser,83,&yymsp[-1].minor);
  yymsp[-2].minor.yy113 = yylhsminor.yy113;
        break;
      case 141: /* set_stmt ::= SET set_exp EOS */
#line 886 "src/parser_proc.y"
{
 yylhsminor.yy300 = psi_set_stmt_init(yymsp[-1].minor.yy113);
 yylhsminor.yy300->token = yymsp[-2].minor.yy0;
}
#line 3208 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy300 = yylhsminor.yy300;
        break;
      case 142: /* return_stmt ::= RETURN set_func EOS */
#line 890 "src/parser_proc.y"
{
 yylhsminor.yy258 = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, yymsp[-1].minor.yy324));
 yylhsminor.yy258->token = yymsp[-2].minor.yy0;
}
#line 3218 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy258 = yylhsminor.yy258;
        break;
      case 143: /* free_stmt ::= FREE free_exps EOS */
#line 894 "src/parser_proc.y"
{
 yylhsminor.yy102 = psi_free_stmt_init(yymsp[-1].minor.yy7);
 yylhsminor.yy102->token = yymsp[-2].minor.yy0;
}
#line 3228 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy102 = yylhsminor.yy102;
        break;
      case 144: /* free_exps ::= free_exp */
#line 898 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
   &yymsp[0].minor.yy114);
}
#line 3238 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 145: /* free_exps ::= free_exps COMMA free_exp */
#line 902 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_plist_add(yymsp[-2].minor.yy7, &yymsp[0].minor.yy114);
}
#line 3246 "src/parser_proc.c"
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yymsp[-2].minor.yy7 = yylhsminor.yy7;
        break;
      case 146: /* free_exp ::= NAME LPAREN decl_vars RPAREN */
#line 905 "src/parser_proc.y"
{
 yylhsminor.yy114 = psi_free_exp_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy7);
 yylhsminor.yy114->token = yymsp[-3].minor.yy0;
}
#line 3256 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,77,&yymsp[0].minor);
  yymsp[-3].minor.yy114 = yylhsminor.yy114;
        break;
      case 147: /* assert_stmt ::= PRE_ASSERT|POST_ASSERT num_exp EOS */
#line 909 "src/parser_proc.y"
{
 yylhsminor.yy146 = psi_assert_stmt_init(yymsp[-2].minor.yy0->type, yymsp[-1].minor.yy124);
 yylhsminor.yy146->token = yymsp[-2].minor.yy0;
}
#line 3267 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[0].minor);
  yymsp[-2].minor.yy146 = yylhsminor.yy146;
        break;
      case 148: /* reference ::= */
#line 913 "src/parser_proc.y"
{
 yymsp[1].minor.yy247 = false;
}
#line 3276 "src/parser_proc.c"
        break;
      case 149: /* reference ::= AMPERSAND */
{  yy_destructor(yypParser,23,&yymsp[0].minor);
#line 916 "src/parser_proc.y"
{
 yymsp[0].minor.yy247 = true;
}
#line 3284 "src/parser_proc.c"
}
        break;
      case 150: /* indirection ::= */
#line 919 "src/parser_proc.y"
{
 yymsp[1].minor.yy296 = 0;
}
#line 3292 "src/parser_proc.c"
        break;
      case 151: /* indirection ::= pointers */
#line 922 "src/parser_proc.y"
{
 yylhsminor.yy296 = yymsp[0].minor.yy296;
}
#line 3299 "src/parser_proc.c"
  yymsp[0].minor.yy296 = yylhsminor.yy296;
        break;
      case 152: /* pointers ::= ASTERISK */
{  yy_destructor(yypParser,28,&yymsp[0].minor);
#line 925 "src/parser_proc.y"
{
 yymsp[0].minor.yy296 = 1;
}
#line 3308 "src/parser_proc.c"
}
        break;
      case 153: /* pointers ::= pointers ASTERISK */
#line 928 "src/parser_proc.y"
{
 yylhsminor.yy296 = yymsp[-1].minor.yy296+1;
}
#line 3316 "src/parser_proc.c"
  yy_destructor(yypParser,28,&yymsp[0].minor);
  yymsp[-1].minor.yy296 = yylhsminor.yy296;
        break;
      case 154: /* file ::= blocks */
{  yy_destructor(yypParser,157,&yymsp[0].minor);
#line 175 "src/parser_proc.y"
{
}
#line 3325 "src/parser_proc.c"
}
        break;
      case 155: /* blocks ::= block */
{  yy_destructor(yypParser,158,&yymsp[0].minor);
#line 176 "src/parser_proc.y"
{
}
#line 3333 "src/parser_proc.c"
}
        break;
      case 156: /* blocks ::= blocks block */
{  yy_destructor(yypParser,157,&yymsp[-1].minor);
#line 177 "src/parser_proc.y"
{
}
#line 3341 "src/parser_proc.c"
  yy_destructor(yypParser,158,&yymsp[0].minor);
}
        break;
      case 157: /* block ::= EOF */
{  yy_destructor(yypParser,72,&yymsp[0].minor);
#line 178 "src/parser_proc.y"
{
}
#line 3350 "src/parser_proc.c"
}
        break;
      case 158: /* block ::= EOS */
{  yy_destructor(yypParser,73,&yymsp[0].minor);
#line 179 "src/parser_proc.y"
{
}
#line 3358 "src/parser_proc.c"
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
 ++P->errors; if (TOKEN && TOKEN->type != PSI_T_EOF) { psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col); } else { psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input"); } 
#line 3420 "src/parser_proc.c"
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
