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
#define YYNOCODE 167
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE struct psi_token *
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  struct psi_const_type* yy7;
  struct psi_let_calloc* yy17;
  struct psi_decl_union* yy19;
  struct psi_impl_def_val* yy21;
  struct psi_token** yy38;
  struct psi_num_exp* yy39;
  struct psi_impl* yy49;
  struct psi_set_exp* yy67;
  struct psi_decl_enum_item* yy69;
  struct psi_decl* yy71;
  struct psi_let_func* yy72;
  struct psi_free_stmt* yy76;
  struct psi_set_func* yy78;
  struct psi_layout* yy81;
  struct psi_const* yy106;
  struct psi_impl_func* yy120;
  struct psi_return_stmt* yy130;
  struct psi_let_stmt* yy139;
  struct psi_impl_type* yy142;
  struct psi_let_exp* yy144;
  struct psi_decl_type* yy152;
  struct psi_number* yy160;
  struct psi_let_callback* yy164;
  struct psi_impl_var* yy185;
  unsigned yy190;
  struct psi_free_exp* yy197;
  struct psi_decl_var* yy207;
  struct psi_set_stmt* yy226;
  struct psi_impl_arg* yy238;
  struct psi_decl_abi* yy242;
  struct psi_decl_arg* yy260;
  struct psi_decl_struct* yy271;
  bool yy273;
  struct psi_decl_enum * yy279;
  struct psi_plist * yy287;
  struct psi_plist* yy303;
  struct psi_layout yy323;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define ParseARG_SDECL struct psi_parser *P;
#define ParseARG_PDECL ,struct psi_parser *P
#define ParseARG_FETCH struct psi_parser *P = yypParser->P
#define ParseARG_STORE yypParser->P = P
#define YYFALLBACK 1
#define YYNSTATE             197
#define YYNRULE              157
#define YY_MAX_SHIFT         196
#define YY_MIN_SHIFTREDUCE   328
#define YY_MAX_SHIFTREDUCE   484
#define YY_MIN_REDUCE        485
#define YY_MAX_REDUCE        641
#define YY_ERROR_ACTION      642
#define YY_ACCEPT_ACTION     643
#define YY_NO_ACTION         644
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
#define YY_ACTTAB_COUNT (1024)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   394,  409,   93,  409,  409,  409,  409,  409,  409,  409,
 /*    10 */   409,  409,  409,   93,  436,  430,  478,   21,  424,  430,
 /*    20 */   425,  427,   15,  427,  411,   27,   27,  478,  475,  428,
 /*    30 */   494,  428,  150,  426,  429,  426,  429,  494,   27,   27,
 /*    40 */   148,  148,  148,  148,  148,  148,  148,  148,  148,  148,
 /*    50 */   432,  101,  124,  439,  441,   83,  423,  438,  452,  110,
 /*    60 */   417,  417,  417,  417,  417,  405,  149,   56,  366,  422,
 /*    70 */   107,  122,   28,  376,   90,   89,   88,  147,  348,   48,
 /*    80 */    35,  133,  478,  164,  116,  390,   81,   67,   65,   64,
 /*    90 */   394,  409,   47,  409,  409,  409,  409,  409,  409,  409,
 /*   100 */   409,  409,  409,   39,   49,   11,   10,   60,   93,  437,
 /*   110 */   430,  158,  115,  141,  430,  353,  353,  353,  353,  478,
 /*   120 */    27,   27,  478,  141,  141,  141,  141,  141,  141,  141,
 /*   130 */   375,  193,  136,   27,   27,  148,  148,  148,  148,  148,
 /*   140 */   148,  148,  148,  148,  148,   83,  349,  352,  394,  409,
 /*   150 */   146,  409,  409,  409,  409,  409,  409,  409,  409,  409,
 /*   160 */   409,  149,  349,  351,  179,  181,  180,   28,  134,  122,
 /*   170 */    35,  122,  153,  109,  471,  390,   81,   67,   65,   64,
 /*   180 */    29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*   190 */    29,   29,   29,   29,   29,   29,   29,   29,  394,  419,
 /*   200 */   419,  419,  419,   41,  124,  145,  394,  409,  416,  409,
 /*   210 */   409,  409,  409,  409,  409,  409,  409,  409,  409,  415,
 /*   220 */   382,  114,   90,   89,   88,  410,   43,  414,   34,  106,
 /*   230 */   147,  123,  344,  390,   81,   67,   65,   64,   29,   29,
 /*   240 */    29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*   250 */    29,  374,  108,   29,   29,  419,  419,  419,  419,  419,
 /*   260 */   421,   83,  113,  397,  394,  409,  405,  409,  409,  409,
 /*   270 */   409,  409,  409,  409,  409,  409,  409,  167,  137,  112,
 /*   280 */    90,   89,   88,  390,   81,   67,   35,  147,   36,  128,
 /*   290 */   122,  390,   81,   67,   65,   64,  458,  458,  458,  458,
 /*   300 */   458,  458,  458,  458,  458,  458,  155,  379,  157,  161,
 /*   310 */   365,  169,  459,  160,  161,  410,   43,  122,  122,   76,
 /*   320 */   119,  479,  394,  409,  431,  409,  409,  409,  409,  409,
 /*   330 */   409,  409,  409,  409,  409,  376,  431,  357,  179,  181,
 /*   340 */   180,  402,  432,  100,   35,  440,  442,   80,  140,  390,
 /*   350 */    81,   67,   65,   64,  432,   99,  405,  163,  161,  144,
 /*   360 */   142,  127,  350,  122,  356,  456,   53,  463,   37,  473,
 /*   370 */     2,  418,  395,  147,  122,  122,  122,   66,    8,  451,
 /*   380 */   394,  409,  431,  409,  409,  409,  409,  409,  409,  409,
 /*   390 */   409,  409,  409,   94,  431,  401,  179,  181,  180,  343,
 /*   400 */   432,   96,   35,  122,   13,  461,  140,  390,   81,   67,
 /*   410 */    65,   64,  432,   99,   39,   49,   11,   10,   60,  470,
 /*   420 */    92,  122,   70,  465,  111,  463,  131,    7,  460,    6,
 /*   430 */   450,  147,  413,  122,  479,   83,   23,  154,  394,  409,
 /*   440 */   431,  409,  409,  409,  409,  409,  409,  409,  409,  409,
 /*   450 */   409,   68,  150,  472,  179,  181,  180,  132,  432,   97,
 /*   460 */    35,  378,   24,  360,   38,  390,   81,   67,   65,   64,
 /*   470 */   432,  101,   20,  439,  441,  479,  383,  438,  453,  122,
 /*   480 */   369,  410,   43,  382,  117,  377,  368,  105,  410,   43,
 /*   490 */   367,  122,  361,   74,  189,  379,  394,  409,   42,  409,
 /*   500 */   409,  409,  409,  409,  409,  409,  409,  409,  409,  479,
 /*   510 */   176,  177,  179,  181,  180,  398,   22,  424,  393,  400,
 /*   520 */   427,  431,  405,  390,   81,   67,   65,   64,  428,  405,
 /*   530 */    44,  391,  426,  429,  118,  196,  483,  484,    2,  432,
 /*   540 */   102,   84,   95,  190,  170,   45,   86,  335,   63,    1,
 /*   550 */   120,   82,  333,  342,  334,  121,  332,  331,   69,   68,
 /*   560 */   122,  329,  183,   19,   46,  341,  340,  192,  345,  337,
 /*   570 */   179,  181,  180,  330,  151,   39,   49,   11,   10,   60,
 /*   580 */   373,  390,   81,   67,   65,   64,   93,  372,  430,   61,
 /*   590 */    57,  126,  430,  412,  125,  475,  182,   58,   27,   27,
 /*   600 */   478,   59,  130,   31,  643,    3,    3,  178,  194,  469,
 /*   610 */    16,   27,   27,  141,  468,   79,  431,    4,  384,   32,
 /*   620 */   410,   43,  447,  141,  141,  141,  141,  141,  141,  141,
 /*   630 */   419,  419,  419,  419,  432,   98,  446,   71,   93,  462,
 /*   640 */   430,   12,   40,  448,  430,   28,  143,  475,   14,  182,
 /*   650 */    27,   27,  478,    5,   50,  122,  418,  194,   87,   85,
 /*   660 */   178,  405,   51,   27,   27,  141,  631,   26,   79,    9,
 /*   670 */    17,  385,  364,  410,   43,  141,  141,  141,  141,  141,
 /*   680 */   141,  141,  152,  363,   18,   72,  419,  419,  419,  419,
 /*   690 */   419,  156,   52,   73,  159,  479,   75,   28,  431,  162,
 /*   700 */    54,  522,  355,  354,  129,   78,   62,  168,  139,  389,
 /*   710 */   194,   87,   85,  171,  405,  172,  432,  104,  173,   29,
 /*   720 */    29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*   730 */    29,   29,   29,   29,   29,   29,   29,  122,  174,  408,
 /*   740 */   175,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*   750 */    29,   29,   29,   29,   29,   29,   29,   29,   29,  387,
 /*   760 */   386,  407,  406,  358,  371,  494,  184,  339,  185,  187,
 /*   770 */   186,  188,   91,  449,   29,   29,   29,   29,   29,   29,
 /*   780 */    29,   29,   29,   29,   29,   29,   29,   29,   29,   29,
 /*   790 */    29,   29,  191,   93,   25,  430,  637,   30,   55,  430,
 /*   800 */   328,  195,  475,  431,  487,   27,   27,  478,  487,  487,
 /*   810 */   369,  487,  487,  487,  487,  487,  487,  487,   27,   27,
 /*   820 */   141,  432,  103,  487,  487,  487,  487,  487,  433,  182,
 /*   830 */   141,  141,  141,  141,  141,  141,  141,  487,  487,  487,
 /*   840 */   359,  166,  122,  487,   77,   93,  487,  430,  165,  487,
 /*   850 */   487,  430,   28,  410,   33,  487,  487,   27,   27,  478,
 /*   860 */   487,  487,  487,  487,  487,  196,  483,  484,  487,  487,
 /*   870 */    27,   27,   95,  190,  170,  487,  487,  487,   63,    1,
 /*   880 */   487,  487,  487,  487,  487,  487,  487,  487,   69,   68,
 /*   890 */   194,   87,   85,  335,  405,  487,  150,  487,  333,  487,
 /*   900 */   334,  487,  332,  331,   28,  150,  487,  329,  487,   19,
 /*   910 */   487,  487,  487,  487,  432,  101,  487,  439,  441,  330,
 /*   920 */   151,  438,  445,  432,  101,  487,  439,  441,  487,  487,
 /*   930 */   438,  138,  487,  487,  487,  122,  487,  487,  487,  487,
 /*   940 */   487,  487,  487,  431,  122,  487,  431,  487,  487,  487,
 /*   950 */   487,  487,  482,  487,  194,  140,  487,  487,  140,  487,
 /*   960 */   487,  432,   99,  487,  432,   99,  487,  487,  487,  487,
 /*   970 */   487,  487,  135,  487,  463,  467,  487,  463,  487,  431,
 /*   980 */   147,  487,  122,  147,  431,  122,  487,  487,  487,  487,
 /*   990 */   487,  140,  487,  487,  487,  487,  140,  432,   99,  487,
 /*  1000 */   487,  487,  432,   99,  487,  487,  487,  487,  466,  487,
 /*  1010 */   463,  487,  487,  457,  487,  463,  147,  487,  122,  487,
 /*  1020 */   487,  147,  487,  122,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,   14,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   14,   15,   16,   28,  129,  130,   20,
 /*    20 */   130,  133,   23,  133,  120,   26,   27,   28,   23,  141,
 /*    30 */    72,  141,  113,  145,  146,  145,  146,   79,   39,   40,
 /*    40 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   50,
 /*    50 */   131,  132,  125,  134,  135,   57,  126,  138,  139,  140,
 /*    60 */    15,   16,   17,   18,   19,  161,   67,   68,   14,  126,
 /*    70 */   127,  152,   73,  113,   76,   77,   78,  150,   80,  149,
 /*    80 */    82,   14,   28,  151,  152,   87,   88,   89,   90,   91,
 /*    90 */     2,    3,  149,    5,    6,    7,    8,    9,   10,   11,
 /*   100 */    12,   13,   14,   62,   63,   64,   65,   66,   14,   15,
 /*   110 */    16,  151,  152,   41,   20,    1,    2,    3,    4,   28,
 /*   120 */    26,   27,   28,   51,   52,   53,   54,   55,   56,   57,
 /*   130 */   113,   14,  113,   39,   40,   41,   42,   43,   44,   45,
 /*   140 */    46,   47,   48,   49,   50,   57,   99,  100,    2,    3,
 /*   150 */   165,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   160 */    14,   67,   99,  100,   76,   77,   78,   73,  144,  152,
 /*   170 */    82,  152,   84,  147,  148,   87,   88,   89,   90,   91,
 /*   180 */    21,   22,   23,   24,   25,   26,   27,   28,   29,   30,
 /*   190 */    31,   32,   33,   34,   35,   36,   37,   38,    2,    1,
 /*   200 */     2,    3,    4,   57,  125,  125,    2,    3,  149,    5,
 /*   210 */     6,    7,    8,    9,   10,   11,   12,   13,   14,  149,
 /*   220 */   115,  116,   76,   77,   78,  120,  121,  149,   82,  150,
 /*   230 */   150,   97,   98,   87,   88,   89,   90,   91,   22,   23,
 /*   240 */    24,   25,   26,   27,   28,   29,   30,   31,   32,   33,
 /*   250 */    34,  113,  114,   37,   38,   57,   58,   59,   60,   61,
 /*   260 */   124,   57,  125,    5,    2,    3,  161,    5,    6,    7,
 /*   270 */     8,    9,   10,   11,   12,   13,   14,  124,  113,  113,
 /*   280 */    76,   77,   78,   87,   88,   89,   82,  150,   74,   75,
 /*   290 */   152,   87,   88,   89,   90,   91,   41,   42,   43,   44,
 /*   300 */    45,   46,   47,   48,   49,   50,  111,   14,  151,  152,
 /*   310 */   115,  104,   57,  151,  152,  120,  121,  152,  152,   57,
 /*   320 */   152,   28,    2,    3,  113,    5,    6,    7,    8,    9,
 /*   330 */    10,   11,   12,   13,   14,  113,  113,  113,   76,   77,
 /*   340 */    78,  161,  131,  132,   82,  134,  135,   89,  125,   87,
 /*   350 */    88,   89,   90,   91,  131,  132,  161,  151,  152,  136,
 /*   360 */   137,   84,   71,  152,  113,  142,   73,  144,   74,   75,
 /*   370 */    79,   94,  163,  150,  152,  152,  152,   57,   74,   75,
 /*   380 */     2,    3,  113,    5,    6,    7,    8,    9,   10,   11,
 /*   390 */    12,   13,   14,   74,  113,  161,   76,   77,   78,   80,
 /*   400 */   131,  132,   82,  152,   74,   75,  125,   87,   88,   89,
 /*   410 */    90,   91,  131,  132,   62,   63,   64,   65,   66,   71,
 /*   420 */    14,  152,   74,  142,  143,  144,  150,   74,   75,   74,
 /*   430 */    75,  150,   80,  152,   28,   57,   74,   75,    2,    3,
 /*   440 */   113,    5,    6,    7,    8,    9,   10,   11,   12,   13,
 /*   450 */    14,   93,  113,  148,   76,   77,   78,  123,  131,  132,
 /*   460 */    82,   14,   74,   75,  150,   87,   88,   89,   90,   91,
 /*   470 */   131,  132,   73,  134,  135,   28,  115,  138,  139,  152,
 /*   480 */    14,  120,  121,  115,  116,  109,  109,  152,  120,  121,
 /*   490 */   109,  152,  109,   57,   72,   14,    2,    3,  102,    5,
 /*   500 */     6,    7,    8,    9,   10,   11,   12,   13,   14,   28,
 /*   510 */    72,  119,   76,   77,   78,  164,  129,  130,    2,    2,
 /*   520 */   133,  113,  161,   87,   88,   89,   90,   91,  141,  161,
 /*   530 */    99,  162,  145,  146,  152,   69,   70,   71,   79,  131,
 /*   540 */   132,  102,   76,   77,   78,   99,  102,   96,   82,   83,
 /*   550 */    14,   57,  101,  156,  103,   14,  105,  106,   92,   93,
 /*   560 */   152,  110,   14,  112,  102,  156,  156,   85,   98,   14,
 /*   570 */    76,   77,   78,  122,  123,   62,   63,   64,   65,   66,
 /*   580 */   160,   87,   88,   89,   90,   91,   14,  160,   16,   81,
 /*   590 */    72,   94,   20,   80,   75,   23,   96,   72,   26,   27,
 /*   600 */    28,   72,   20,   73,  153,  154,  155,  107,  157,   71,
 /*   610 */    79,   39,   40,   41,   71,  115,  113,  117,  118,   73,
 /*   620 */   120,  121,   71,   51,   52,   53,   54,   55,   56,   57,
 /*   630 */     1,    2,    3,    4,  131,  132,   71,   81,   14,   75,
 /*   640 */    16,   81,   73,   75,   20,   73,   75,   23,   74,   96,
 /*   650 */    26,   27,   28,   73,   73,  152,   94,  157,  158,  159,
 /*   660 */   107,  161,   73,   39,   40,   41,   94,   73,  115,   81,
 /*   670 */    79,  118,   71,  120,  121,   51,   52,   53,   54,   55,
 /*   680 */    56,   57,   75,   71,   73,   75,   57,   58,   59,   60,
 /*   690 */    61,   14,   73,   75,   14,   28,   75,   73,  113,   14,
 /*   700 */    73,   73,   71,   71,   75,   14,   81,   20,   84,   75,
 /*   710 */   157,  158,  159,   16,  161,   74,  131,  132,   16,   21,
 /*   720 */    22,   23,   24,   25,   26,   27,   28,   29,   30,   31,
 /*   730 */    32,   33,   34,   35,   36,   37,   38,  152,   73,   14,
 /*   740 */    72,   21,   22,   23,   24,   25,   26,   27,   28,   29,
 /*   750 */    30,   31,   32,   33,   34,   35,   36,   37,   38,   71,
 /*   760 */    71,   14,   14,   14,   86,   79,   16,   75,   74,   73,
 /*   770 */    16,   72,   14,   75,   21,   22,   23,   24,   25,   26,
 /*   780 */    27,   28,   29,   30,   31,   32,   33,   34,   35,   36,
 /*   790 */    37,   38,   16,   14,   74,   16,    0,   81,   79,   20,
 /*   800 */    71,   19,   23,  113,  166,   26,   27,   28,  166,  166,
 /*   810 */    14,  166,  166,  166,  166,  166,  166,  166,   39,   40,
 /*   820 */    41,  131,  132,  166,  166,  166,  166,  166,   75,   96,
 /*   830 */    51,   52,   53,   54,   55,   56,   57,  166,  166,  166,
 /*   840 */   107,  108,  152,  166,  111,   14,  166,   16,  115,  166,
 /*   850 */   166,   20,   73,  120,  121,  166,  166,   26,   27,   28,
 /*   860 */   166,  166,  166,  166,  166,   69,   70,   71,  166,  166,
 /*   870 */    39,   40,   76,   77,   78,  166,  166,  166,   82,   83,
 /*   880 */   166,  166,  166,  166,  166,  166,  166,  166,   92,   93,
 /*   890 */   157,  158,  159,   96,  161,  166,  113,  166,  101,  166,
 /*   900 */   103,  166,  105,  106,   73,  113,  166,  110,  166,  112,
 /*   910 */   166,  166,  166,  166,  131,  132,  166,  134,  135,  122,
 /*   920 */   123,  138,  139,  131,  132,  166,  134,  135,  166,  166,
 /*   930 */   138,  139,  166,  166,  166,  152,  166,  166,  166,  166,
 /*   940 */   166,  166,  166,  113,  152,  166,  113,  166,  166,  166,
 /*   950 */   166,  166,  155,  166,  157,  125,  166,  166,  125,  166,
 /*   960 */   166,  131,  132,  166,  131,  132,  166,  166,  166,  166,
 /*   970 */   166,  166,  142,  166,  144,  142,  166,  144,  166,  113,
 /*   980 */   150,  166,  152,  150,  113,  152,  166,  166,  166,  166,
 /*   990 */   166,  125,  166,  166,  166,  166,  125,  131,  132,  166,
 /*  1000 */   166,  166,  131,  132,  166,  166,  166,  166,  142,  166,
 /*  1010 */   144,  166,  166,  142,  166,  144,  150,  166,  152,  166,
 /*  1020 */   166,  150,  166,  152,
};
#define YY_SHIFT_USE_DFLT (1024)
#define YY_SHIFT_COUNT    (196)
#define YY_SHIFT_MIN      (-42)
#define YY_SHIFT_MAX      (831)
static const short yy_shift_ofst[] = {
 /*     0 */   466,  146,  204,  796,   -2,  572,   -1,  624,   -1,   -1,
 /*    10 */    -1,  779,  779,  779,  779,   94,   41,   41,  262,  320,
 /*    20 */   262,  352,  513,   88,  378,  831,  831,  831,  831,  831,
 /*    30 */   831,  629,  -12,  -12,  436,  494,  198,  -12,  -12,  -12,
 /*    40 */   -12,   54,  291,  -12,  -12,  -12,  291,    5,    5,   67,
 /*    50 */     5,    5,   91,   91,   91,  117,  255,  198,  198,  198,
 /*    60 */    72,   45,   45,  114,  196,  196,   54,  258,    5,  358,
 /*    70 */    67,    5,  399,  399,   91,  399,   91,  399,  422,  438,
 /*    80 */   517,  516,   91,   91,  459,  422,  459,  422,  536,  541,
 /*    90 */   548,  422,  482,  482,  117,  555,  698,  720,  753,  159,
 /*   100 */   159,  159,  159,  159,  216,  293,  277,  214,  294,  348,
 /*   110 */   304,  330,  353,  355,  362,  406,  447,  388,  481,  447,
 /*   120 */   -42,  -42,  406,  319,  508,  518,  519,  497,  525,  529,
 /*   130 */   530,  582,  531,  546,  538,  543,  551,  556,  565,  564,
 /*   140 */   560,  569,  574,  568,  571,  580,  581,  562,  589,  594,
 /*   150 */   588,  591,  601,  607,  612,  611,  610,  677,  619,  618,
 /*   160 */   680,  667,  621,  685,  627,  628,  631,  632,  625,  687,
 /*   170 */   691,  634,  697,  641,  702,  665,  668,  688,  689,  725,
 /*   180 */   747,  748,  749,  686,  692,  750,  694,  754,  696,  699,
 /*   190 */   758,  678,  776,  716,  719,  729,  782,
};
#define YY_REDUCE_USE_DFLT (-113)
#define YY_REDUCE_COUNT (95)
#define YY_REDUCE_MIN   (-112)
#define YY_REDUCE_MAX   (871)
static const short yy_reduce_ofst[] = {
 /*     0 */   451,  733,  500,  797,  553,  223,  -81,  281,  339,  783,
 /*    10 */   792,  830,  833,  866,  871,  211, -112,  387,  105,  195,
 /*    20 */   368, -110, -110,  361,  361,  269,  327,  408,  503,  585,
 /*    30 */   690,  -57,  138,  -40,  -96,  -96,  -70,   17,   19,  165,
 /*    40 */   166,  -68,   47,  222,  224,  251,   63,  -73,   79,   26,
 /*    50 */    80,  137,  157,  162,  206,  134,  -15,   59,   70,   78,
 /*    60 */    24,  136,  153,  207,  180,  234,  168,  209,  276,  334,
 /*    70 */   305,  314,  376,  377,  335,  381,  168,  383,  396,  392,
 /*    80 */   351,  369,  382,  168,  431,  439,  446,  444,  397,  409,
 /*    90 */   410,  462,  420,  427,  470,  410,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   642,  642,  642,  642,  642,  611,  642,  631,  642,  642,
 /*    10 */   642,  631,  631,  631,  631,  642,  642,  642,  537,  642,
 /*    20 */   537,  642,  642,  642,  642,  642,  642,  642,  642,  642,
 /*    30 */   642,  642,  642,  633,  642,  642,  642,  642,  642,  642,
 /*    40 */   642,  633,  642,  642,  642,  642,  642,  631,  631,  642,
 /*    50 */   631,  631,  633,  633,  633,  642,  642,  642,  642,  642,
 /*    60 */   642,  642,  642,  642,  561,  560,  642,  553,  631,  642,
 /*    70 */   642,  631,  642,  642,  642,  642,  538,  642,  495,  545,
 /*    80 */   556,  549,  642,  642,  642,  495,  642,  495,  493,  493,
 /*    90 */   493,  495,  527,  527,  642,  493,  642,  642,  642,  621,
 /*   100 */   601,  600,  592,  503,  591,  642,  642,  642,  642,  642,
 /*   110 */   642,  642,  642,  642,  642,  634,  634,  642,  642,  642,
 /*   120 */   564,  563,  642,  642,  577,  642,  642,  642,  642,  642,
 /*   130 */   642,  642,  642,  642,  642,  642,  642,  642,  642,  642,
 /*   140 */   642,  642,  612,  642,  642,  642,  642,  642,  642,  642,
 /*   150 */   588,  642,  642,  642,  642,  642,  642,  642,  642,  642,
 /*   160 */   642,  634,  642,  642,  642,  519,  642,  642,  642,  642,
 /*   170 */   642,  642,  642,  642,  642,  642,  642,  642,  642,  642,
 /*   180 */   642,  642,  642,  565,  642,  642,  642,  642,  642,  642,
 /*   190 */   642,  642,  642,  504,  642,  642,  642,
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
  "OBJECT",        "CALLABLE",      "TEMP",          "FREE",        
  "SET",           "LET",           "RETURN",        "CALLOC",      
  "CALLBACK",      "LIB",           "EOF",           "EOS",         
  "COLON",         "LPAREN",        "COMMA",         "RPAREN",      
  "ENUM",          "STRUCT",        "UNION",         "LBRACE",      
  "RBRACE",        "EQUALS",        "CONST",         "TYPEDEF",     
  "ELLIPSIS",      "LBRACKET",      "RBRACKET",      "CHAR",        
  "SHORT",         "LONG",          "UNSIGNED",      "SIGNED",      
  "STATIC",        "FUNCTION",      "DOLLAR_NAME",   "error",       
  "decl_enum",     "decl_enum_items",  "decl_enum_item",  "decl_struct_args_block",
  "decl_struct_args",  "decl_struct",   "align_and_size",  "decl_union",  
  "const_type",    "constant",      "decl_typedef",  "decl_typedef_body_ex",
  "decl_typedef_body",  "decl_typedef_body_fn_args",  "decl",          "decl_func",   
  "decl_abi",      "decl_var",      "decl_vars",     "decl_arg",    
  "decl_args",     "struct_args",   "struct_arg",    "decl_layout", 
  "decl_type",     "const_decl_type",  "impl",          "impl_func",   
  "impl_def_val",  "impl_var",      "impl_arg",      "impl_args",   
  "impl_vararg",   "impl_stmts",    "impl_stmt",     "number",      
  "num_exp",       "let_stmt",      "let_calloc",    "let_func",    
  "callback_arg_list",  "callback_args",  "let_callback",  "let_exp",     
  "let_exps",      "set_stmt",      "set_exp",       "set_exps",    
  "set_func",      "return_stmt",   "free_stmt",     "free_exps",   
  "free_exp",      "impl_type",     "reference",     "indirection", 
  "pointers",      "file",          "blocks",        "block",       
  "optional_name",  "enum_name",     "struct_name",   "union_name",  
  "decl_var_array_size",  "decl_scalar_type",  "decl_scalar_type_short",  "decl_scalar_type_long",
  "decl_scalar_type_long_long",  "callback_rval",
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
 /* 101 */ "impl_stmt ::= free_stmt",
 /* 102 */ "number ::= NUMBER|NSNAME",
 /* 103 */ "number ::= decl_var",
 /* 104 */ "num_exp ::= number",
 /* 105 */ "num_exp ::= LPAREN num_exp RPAREN",
 /* 106 */ "num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp",
 /* 107 */ "num_exp ::= TILDE|NOT|PLUS|MINUS num_exp",
 /* 108 */ "let_exp ::= NULL",
 /* 109 */ "let_exp ::= AMPERSAND NULL",
 /* 110 */ "let_exp ::= let_callback",
 /* 111 */ "let_exp ::= let_calloc",
 /* 112 */ "let_exp ::= AMPERSAND let_calloc",
 /* 113 */ "let_exp ::= let_func",
 /* 114 */ "let_exp ::= AMPERSAND let_func",
 /* 115 */ "let_exp ::= num_exp",
 /* 116 */ "let_exp ::= AMPERSAND num_exp",
 /* 117 */ "let_exp ::= decl_var EQUALS let_exp",
 /* 118 */ "let_stmt ::= LET let_exp EOS",
 /* 119 */ "let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS",
 /* 120 */ "let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN",
 /* 121 */ "let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN",
 /* 122 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN",
 /* 123 */ "let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN",
 /* 124 */ "let_exps ::= let_exp",
 /* 125 */ "let_exps ::= let_exps COMMA let_exp",
 /* 126 */ "callback_arg_list ::=",
 /* 127 */ "callback_arg_list ::= callback_args",
 /* 128 */ "callback_args ::= set_exp",
 /* 129 */ "callback_args ::= callback_args COMMA set_exp",
 /* 130 */ "callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT",
 /* 131 */ "callback_rval ::= VOID",
 /* 132 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN",
 /* 133 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN",
 /* 134 */ "set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN",
 /* 135 */ "set_exp ::= set_func",
 /* 136 */ "set_exp ::= num_exp",
 /* 137 */ "set_exps ::= set_exp",
 /* 138 */ "set_exps ::= set_exps COMMA set_exp",
 /* 139 */ "set_exp ::= impl_var EQUALS set_exp",
 /* 140 */ "set_stmt ::= SET set_exp EOS",
 /* 141 */ "return_stmt ::= RETURN set_func EOS",
 /* 142 */ "free_stmt ::= FREE free_exps EOS",
 /* 143 */ "free_exps ::= free_exp",
 /* 144 */ "free_exps ::= free_exps COMMA free_exp",
 /* 145 */ "free_exp ::= NAME LPAREN decl_vars RPAREN",
 /* 146 */ "reference ::=",
 /* 147 */ "reference ::= AMPERSAND",
 /* 148 */ "indirection ::=",
 /* 149 */ "indirection ::= pointers",
 /* 150 */ "pointers ::= ASTERISK",
 /* 151 */ "pointers ::= pointers ASTERISK",
 /* 152 */ "file ::= blocks",
 /* 153 */ "blocks ::= block",
 /* 154 */ "blocks ::= blocks block",
 /* 155 */ "block ::= EOF",
 /* 156 */ "block ::= EOS",
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
    case 62: /* TEMP */
    case 63: /* FREE */
    case 64: /* SET */
    case 65: /* LET */
    case 66: /* RETURN */
    case 67: /* CALLOC */
    case 68: /* CALLBACK */
    case 69: /* LIB */
    case 70: /* EOF */
    case 71: /* EOS */
    case 72: /* COLON */
    case 73: /* LPAREN */
    case 74: /* COMMA */
    case 75: /* RPAREN */
    case 76: /* ENUM */
    case 77: /* STRUCT */
    case 78: /* UNION */
    case 79: /* LBRACE */
    case 80: /* RBRACE */
    case 81: /* EQUALS */
    case 82: /* CONST */
    case 83: /* TYPEDEF */
    case 84: /* ELLIPSIS */
    case 85: /* LBRACKET */
    case 86: /* RBRACKET */
    case 87: /* CHAR */
    case 88: /* SHORT */
    case 89: /* LONG */
    case 90: /* UNSIGNED */
    case 91: /* SIGNED */
    case 92: /* STATIC */
    case 93: /* FUNCTION */
    case 94: /* DOLLAR_NAME */
{
#line 37 "src/parser_proc.y"
free((yypminor->yy0));
#line 1124 "src/parser_proc.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 95: /* error */
    case 102: /* align_and_size */
    case 150: /* reference */
    case 151: /* indirection */
    case 152: /* pointers */
    case 153: /* file */
    case 154: /* blocks */
    case 155: /* block */
    case 156: /* optional_name */
    case 157: /* enum_name */
    case 158: /* struct_name */
    case 159: /* union_name */
    case 160: /* decl_var_array_size */
    case 161: /* decl_scalar_type */
    case 162: /* decl_scalar_type_short */
    case 163: /* decl_scalar_type_long */
    case 164: /* decl_scalar_type_long_long */
    case 165: /* callback_rval */
{
#line 38 "src/parser_proc.y"
(void)P;
#line 1149 "src/parser_proc.c"
}
      break;
    case 96: /* decl_enum */
{
#line 63 "src/parser_proc.y"
psi_decl_enum_free(&(yypminor->yy279));
#line 1156 "src/parser_proc.c"
}
      break;
    case 97: /* decl_enum_items */
    case 99: /* decl_struct_args_block */
    case 100: /* decl_struct_args */
    case 109: /* decl_typedef_body_fn_args */
    case 114: /* decl_vars */
    case 116: /* decl_args */
    case 117: /* struct_args */
    case 127: /* impl_args */
    case 129: /* impl_stmts */
    case 140: /* let_exps */
    case 143: /* set_exps */
    case 147: /* free_exps */
{
#line 65 "src/parser_proc.y"
psi_plist_free((yypminor->yy303));
#line 1174 "src/parser_proc.c"
}
      break;
    case 98: /* decl_enum_item */
{
#line 67 "src/parser_proc.y"
psi_decl_enum_item_free(&(yypminor->yy69));
#line 1181 "src/parser_proc.c"
}
      break;
    case 101: /* decl_struct */
{
#line 73 "src/parser_proc.y"
psi_decl_struct_free(&(yypminor->yy271));
#line 1188 "src/parser_proc.c"
}
      break;
    case 103: /* decl_union */
{
#line 76 "src/parser_proc.y"
psi_decl_union_free(&(yypminor->yy19));
#line 1195 "src/parser_proc.c"
}
      break;
    case 104: /* const_type */
{
#line 78 "src/parser_proc.y"
psi_const_type_free(&(yypminor->yy7));
#line 1202 "src/parser_proc.c"
}
      break;
    case 105: /* constant */
{
#line 80 "src/parser_proc.y"
psi_const_free(&(yypminor->yy106));
#line 1209 "src/parser_proc.c"
}
      break;
    case 106: /* decl_typedef */
    case 107: /* decl_typedef_body_ex */
    case 108: /* decl_typedef_body */
    case 111: /* decl_func */
    case 115: /* decl_arg */
    case 118: /* struct_arg */
{
#line 82 "src/parser_proc.y"
psi_decl_arg_free(&(yypminor->yy260));
#line 1221 "src/parser_proc.c"
}
      break;
    case 110: /* decl */
{
#line 90 "src/parser_proc.y"
psi_decl_free(&(yypminor->yy71));
#line 1228 "src/parser_proc.c"
}
      break;
    case 112: /* decl_abi */
{
#line 94 "src/parser_proc.y"
psi_decl_abi_free(&(yypminor->yy242));
#line 1235 "src/parser_proc.c"
}
      break;
    case 113: /* decl_var */
{
#line 96 "src/parser_proc.y"
psi_decl_var_free(&(yypminor->yy207));
#line 1242 "src/parser_proc.c"
}
      break;
    case 119: /* decl_layout */
{
#line 108 "src/parser_proc.y"
psi_layout_free(&(yypminor->yy81));
#line 1249 "src/parser_proc.c"
}
      break;
    case 120: /* decl_type */
    case 121: /* const_decl_type */
{
#line 110 "src/parser_proc.y"
psi_decl_type_free(&(yypminor->yy152));
#line 1257 "src/parser_proc.c"
}
      break;
    case 122: /* impl */
{
#line 114 "src/parser_proc.y"
psi_impl_free(&(yypminor->yy49));
#line 1264 "src/parser_proc.c"
}
      break;
    case 123: /* impl_func */
{
#line 116 "src/parser_proc.y"
psi_impl_func_free(&(yypminor->yy120));
#line 1271 "src/parser_proc.c"
}
      break;
    case 124: /* impl_def_val */
{
#line 118 "src/parser_proc.y"
psi_impl_def_val_free(&(yypminor->yy21));
#line 1278 "src/parser_proc.c"
}
      break;
    case 125: /* impl_var */
{
#line 120 "src/parser_proc.y"
psi_impl_var_free(&(yypminor->yy185));
#line 1285 "src/parser_proc.c"
}
      break;
    case 126: /* impl_arg */
    case 128: /* impl_vararg */
{
#line 122 "src/parser_proc.y"
psi_impl_arg_free(&(yypminor->yy238));
#line 1293 "src/parser_proc.c"
}
      break;
    case 130: /* impl_stmt */
{
#line 130 "src/parser_proc.y"
psi_impl_stmt_free(&(yypminor->yy38));
#line 1300 "src/parser_proc.c"
}
      break;
    case 131: /* number */
{
#line 132 "src/parser_proc.y"
psi_number_free(&(yypminor->yy160));
#line 1307 "src/parser_proc.c"
}
      break;
    case 132: /* num_exp */
{
#line 134 "src/parser_proc.y"
psi_num_exp_free(&(yypminor->yy39));
#line 1314 "src/parser_proc.c"
}
      break;
    case 133: /* let_stmt */
{
#line 136 "src/parser_proc.y"
psi_let_stmt_free(&(yypminor->yy139));
#line 1321 "src/parser_proc.c"
}
      break;
    case 134: /* let_calloc */
{
#line 138 "src/parser_proc.y"
psi_let_calloc_free(&(yypminor->yy17));
#line 1328 "src/parser_proc.c"
}
      break;
    case 135: /* let_func */
{
#line 140 "src/parser_proc.y"
psi_let_func_free(&(yypminor->yy72));
#line 1335 "src/parser_proc.c"
}
      break;
    case 136: /* callback_arg_list */
    case 137: /* callback_args */
{
#line 142 "src/parser_proc.y"
psi_plist_free((yypminor->yy287));
#line 1343 "src/parser_proc.c"
}
      break;
    case 138: /* let_callback */
{
#line 146 "src/parser_proc.y"
psi_let_callback_free(&(yypminor->yy164));
#line 1350 "src/parser_proc.c"
}
      break;
    case 139: /* let_exp */
{
#line 148 "src/parser_proc.y"
psi_let_exp_free(&(yypminor->yy144));
#line 1357 "src/parser_proc.c"
}
      break;
    case 141: /* set_stmt */
{
#line 152 "src/parser_proc.y"
psi_set_stmt_free(&(yypminor->yy226));
#line 1364 "src/parser_proc.c"
}
      break;
    case 142: /* set_exp */
{
#line 154 "src/parser_proc.y"
psi_set_exp_free(&(yypminor->yy67));
#line 1371 "src/parser_proc.c"
}
      break;
    case 144: /* set_func */
{
#line 158 "src/parser_proc.y"
psi_set_func_free(&(yypminor->yy78));
#line 1378 "src/parser_proc.c"
}
      break;
    case 145: /* return_stmt */
{
#line 160 "src/parser_proc.y"
psi_return_stmt_free(&(yypminor->yy130));
#line 1385 "src/parser_proc.c"
}
      break;
    case 146: /* free_stmt */
{
#line 162 "src/parser_proc.y"
psi_free_stmt_free(&(yypminor->yy76));
#line 1392 "src/parser_proc.c"
}
      break;
    case 148: /* free_exp */
{
#line 166 "src/parser_proc.y"
psi_free_exp_free(&(yypminor->yy197));
#line 1399 "src/parser_proc.c"
}
      break;
    case 149: /* impl_type */
{
#line 168 "src/parser_proc.y"
psi_impl_type_free(&(yypminor->yy142));
#line 1406 "src/parser_proc.c"
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
  { 155, 3 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 155, 1 },
  { 156, 0 },
  { 156, 1 },
  { 102, 0 },
  { 102, 7 },
  { 157, 2 },
  { 158, 2 },
  { 159, 2 },
  { 96, 4 },
  { 97, 1 },
  { 97, 3 },
  { 98, 3 },
  { 98, 1 },
  { 99, 3 },
  { 100, 1 },
  { 100, 1 },
  { 101, 4 },
  { 103, 4 },
  { 104, 1 },
  { 105, 6 },
  { 106, 3 },
  { 107, 4 },
  { 107, 4 },
  { 107, 2 },
  { 108, 1 },
  { 109, 3 },
  { 108, 2 },
  { 108, 1 },
  { 110, 6 },
  { 110, 8 },
  { 111, 1 },
  { 111, 2 },
  { 108, 7 },
  { 108, 8 },
  { 112, 1 },
  { 160, 0 },
  { 160, 3 },
  { 113, 2 },
  { 113, 3 },
  { 114, 1 },
  { 114, 3 },
  { 115, 2 },
  { 108, 7 },
  { 115, 3 },
  { 115, 4 },
  { 116, 0 },
  { 116, 1 },
  { 116, 1 },
  { 116, 3 },
  { 117, 1 },
  { 117, 2 },
  { 118, 2 },
  { 118, 3 },
  { 119, 0 },
  { 119, 7 },
  { 161, 1 },
  { 161, 2 },
  { 162, 0 },
  { 162, 1 },
  { 161, 1 },
  { 161, 2 },
  { 163, 0 },
  { 163, 1 },
  { 163, 2 },
  { 164, 0 },
  { 164, 1 },
  { 120, 2 },
  { 120, 2 },
  { 120, 1 },
  { 120, 1 },
  { 120, 1 },
  { 120, 2 },
  { 120, 2 },
  { 120, 2 },
  { 120, 1 },
  { 121, 1 },
  { 121, 2 },
  { 122, 4 },
  { 122, 5 },
  { 123, 7 },
  { 123, 8 },
  { 123, 13 },
  { 124, 1 },
  { 125, 2 },
  { 149, 1 },
  { 126, 2 },
  { 126, 4 },
  { 127, 1 },
  { 127, 3 },
  { 129, 1 },
  { 129, 2 },
  { 130, 1 },
  { 130, 1 },
  { 130, 1 },
  { 130, 1 },
  { 131, 1 },
  { 131, 1 },
  { 132, 1 },
  { 132, 3 },
  { 132, 3 },
  { 132, 2 },
  { 139, 1 },
  { 139, 2 },
  { 139, 1 },
  { 139, 1 },
  { 139, 2 },
  { 139, 1 },
  { 139, 2 },
  { 139, 1 },
  { 139, 2 },
  { 139, 3 },
  { 133, 3 },
  { 133, 6 },
  { 138, 8 },
  { 134, 6 },
  { 135, 4 },
  { 135, 6 },
  { 140, 1 },
  { 140, 3 },
  { 136, 0 },
  { 136, 1 },
  { 137, 1 },
  { 137, 3 },
  { 165, 1 },
  { 165, 1 },
  { 144, 4 },
  { 144, 6 },
  { 144, 6 },
  { 142, 1 },
  { 142, 1 },
  { 143, 1 },
  { 143, 3 },
  { 142, 3 },
  { 141, 3 },
  { 145, 3 },
  { 146, 3 },
  { 147, 1 },
  { 147, 3 },
  { 148, 4 },
  { 150, 0 },
  { 150, 1 },
  { 151, 0 },
  { 151, 1 },
  { 152, 1 },
  { 152, 2 },
  { 153, 1 },
  { 154, 1 },
  { 154, 2 },
  { 155, 1 },
  { 155, 1 },
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
#line 177 "src/parser_proc.y"
{
 if (P->file.ln) {
  P->error(PSI_DATA(P), yymsp[-2].minor.yy0, PSI_WARNING, "Extra 'lib %s' statement has no effect", yymsp[-1].minor.yy0->text);
 } else {
  P->file.ln = strndup(yymsp[-1].minor.yy0->text + 1, yymsp[-1].minor.yy0->size - 2);
 }
 free(yymsp[-1].minor.yy0);
 free(yymsp[-2].minor.yy0);
}
#line 1889 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
        break;
      case 1: /* block ::= decl */
#line 186 "src/parser_proc.y"
{
 if (!P->decls) {
  P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
 }
 P->decls = psi_plist_add(P->decls, &yymsp[0].minor.yy71);
}
#line 1900 "src/parser_proc.c"
        break;
      case 2: /* block ::= impl */
#line 192 "src/parser_proc.y"
{
 if (!P->impls) {
  P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
 }
 P->impls = psi_plist_add(P->impls, &yymsp[0].minor.yy49);
}
#line 1910 "src/parser_proc.c"
        break;
      case 3: /* block ::= decl_typedef */
#line 198 "src/parser_proc.y"
{
 if (!P->types) {
  P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
 }
 P->types = psi_plist_add(P->types, &yymsp[0].minor.yy260);
 switch (yymsp[0].minor.yy260->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[0].minor.yy260->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy260->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[0].minor.yy260->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy260->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[0].minor.yy260->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy260->type->real.enm);
  }
  break;
 }
}
#line 1946 "src/parser_proc.c"
        break;
      case 4: /* block ::= constant */
#line 230 "src/parser_proc.y"
{
 if (!P->consts) {
  P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
 }
 P->consts = psi_plist_add(P->consts, &yymsp[0].minor.yy106);
}
#line 1956 "src/parser_proc.c"
        break;
      case 5: /* block ::= decl_struct */
#line 236 "src/parser_proc.y"
{
 if (!P->structs) {
  P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
 }
 P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy271);
}
#line 1966 "src/parser_proc.c"
        break;
      case 6: /* block ::= decl_union */
#line 242 "src/parser_proc.y"
{
 if (!P->unions) {
  P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
 }
 P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy19);
}
#line 1976 "src/parser_proc.c"
        break;
      case 7: /* block ::= decl_enum */
#line 248 "src/parser_proc.y"
{
 if (!P->enums) {
  P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
 }
 P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy279);
}
#line 1986 "src/parser_proc.c"
        break;
      case 8: /* optional_name ::= */
      case 42: /* decl_var_array_size ::= */ yytestcase(yyruleno==42);
      case 64: /* decl_scalar_type_short ::= */ yytestcase(yyruleno==64);
      case 68: /* decl_scalar_type_long ::= */ yytestcase(yyruleno==68);
      case 71: /* decl_scalar_type_long_long ::= */ yytestcase(yyruleno==71);
#line 254 "src/parser_proc.y"
{
 yymsp[1].minor.yy0 = NULL;
}
#line 1997 "src/parser_proc.c"
        break;
      case 9: /* optional_name ::= NAME */
      case 62: /* decl_scalar_type ::= CHAR */ yytestcase(yyruleno==62);
      case 65: /* decl_scalar_type_short ::= INT */ yytestcase(yyruleno==65);
      case 66: /* decl_scalar_type ::= INT */ yytestcase(yyruleno==66);
      case 69: /* decl_scalar_type_long ::= DOUBLE */ yytestcase(yyruleno==69);
      case 72: /* decl_scalar_type_long_long ::= INT */ yytestcase(yyruleno==72);
      case 130: /* callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT */ yytestcase(yyruleno==130);
      case 131: /* callback_rval ::= VOID */ yytestcase(yyruleno==131);
#line 257 "src/parser_proc.y"
{
 yylhsminor.yy0 = yymsp[0].minor.yy0;
}
#line 2011 "src/parser_proc.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* align_and_size ::= */
#line 260 "src/parser_proc.y"
{
 yymsp[1].minor.yy323.pos = 0;
 yymsp[1].minor.yy323.len = 0;
}
#line 2020 "src/parser_proc.c"
        break;
      case 11: /* align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,72,&yymsp[-6].minor);
#line 264 "src/parser_proc.y"
{
 yymsp[-6].minor.yy323.pos = atol(yymsp[-3].minor.yy0->text);
 yymsp[-6].minor.yy323.len = atol(yymsp[-1].minor.yy0->text);
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2031 "src/parser_proc.c"
  yy_destructor(yypParser,72,&yymsp[-5].minor);
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
}
        break;
      case 12: /* enum_name ::= ENUM optional_name */
      case 13: /* struct_name ::= STRUCT optional_name */ yytestcase(yyruleno==13);
      case 14: /* union_name ::= UNION optional_name */ yytestcase(yyruleno==14);
#line 270 "src/parser_proc.y"
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
#line 2052 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* decl_enum ::= enum_name LBRACE decl_enum_items RBRACE */
#line 300 "src/parser_proc.y"
{
 yylhsminor.yy279 = psi_decl_enum_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy303);
 yylhsminor.yy279->token = yymsp[-3].minor.yy0;
}
#line 2061 "src/parser_proc.c"
  yy_destructor(yypParser,79,&yymsp[-2].minor);
  yy_destructor(yypParser,80,&yymsp[0].minor);
  yymsp[-3].minor.yy279 = yylhsminor.yy279;
        break;
      case 16: /* decl_enum_items ::= decl_enum_item */
#line 304 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
   &yymsp[0].minor.yy69);
}
#line 2072 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 17: /* decl_enum_items ::= decl_enum_items COMMA decl_enum_item */
#line 308 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy69);
}
#line 2080 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 18: /* decl_enum_item ::= NAME EQUALS num_exp */
#line 311 "src/parser_proc.y"
{
 yylhsminor.yy69 = psi_decl_enum_item_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy39);
 yylhsminor.yy69->token = yymsp[-2].minor.yy0;
}
#line 2090 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yymsp[-2].minor.yy69 = yylhsminor.yy69;
        break;
      case 19: /* decl_enum_item ::= NAME */
#line 315 "src/parser_proc.y"
{
 yylhsminor.yy69 = psi_decl_enum_item_init(yymsp[0].minor.yy0->text, NULL);
 yylhsminor.yy69->token = yymsp[0].minor.yy0;
}
#line 2100 "src/parser_proc.c"
  yymsp[0].minor.yy69 = yylhsminor.yy69;
        break;
      case 20: /* decl_struct_args_block ::= LBRACE struct_args RBRACE */
{  yy_destructor(yypParser,79,&yymsp[-2].minor);
#line 319 "src/parser_proc.y"
{
 yymsp[-2].minor.yy303 = yymsp[-1].minor.yy303;
}
#line 2109 "src/parser_proc.c"
  yy_destructor(yypParser,80,&yymsp[0].minor);
}
        break;
      case 21: /* decl_struct_args ::= decl_struct_args_block */
#line 322 "src/parser_proc.y"
{
 yylhsminor.yy303 = yymsp[0].minor.yy303;
}
#line 2118 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 22: /* decl_struct_args ::= EOS */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 325 "src/parser_proc.y"
{
 yymsp[0].minor.yy303 = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}
#line 2127 "src/parser_proc.c"
}
        break;
      case 23: /* decl_struct ::= STRUCT NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,77,&yymsp[-3].minor);
#line 328 "src/parser_proc.y"
{
 yymsp[-3].minor.yy271 = psi_decl_struct_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy303);
 yymsp[-3].minor.yy271->align = yymsp[-1].minor.yy323.pos;
 yymsp[-3].minor.yy271->size = yymsp[-1].minor.yy323.len;
 yymsp[-3].minor.yy271->token = yymsp[-2].minor.yy0;
}
#line 2139 "src/parser_proc.c"
}
        break;
      case 24: /* decl_union ::= UNION NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,78,&yymsp[-3].minor);
#line 334 "src/parser_proc.y"
{
 yymsp[-3].minor.yy19 = psi_decl_union_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy303);
 yymsp[-3].minor.yy19->align = yymsp[-1].minor.yy323.pos;
 yymsp[-3].minor.yy19->size = yymsp[-1].minor.yy323.len;
 yymsp[-3].minor.yy19->token = yymsp[-2].minor.yy0;
}
#line 2151 "src/parser_proc.c"
}
        break;
      case 25: /* const_type ::= BOOL|INT|FLOAT|STRING */
#line 340 "src/parser_proc.y"
{
 yylhsminor.yy7 = psi_const_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2160 "src/parser_proc.c"
  yymsp[0].minor.yy7 = yylhsminor.yy7;
        break;
      case 26: /* constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS */
{  yy_destructor(yypParser,82,&yymsp[-5].minor);
#line 344 "src/parser_proc.y"
{
 yymsp[-5].minor.yy106 = psi_const_init(yymsp[-4].minor.yy7, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy21);
 yymsp[-5].minor.yy106->token = yymsp[-3].minor.yy0;
}
#line 2170 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-2].minor);
  yy_destructor(yypParser,71,&yymsp[0].minor);
}
        break;
      case 27: /* decl_typedef ::= TYPEDEF decl_typedef_body EOS */
#line 348 "src/parser_proc.y"
{
 yylhsminor.yy260 = yymsp[-1].minor.yy260;
 yylhsminor.yy260->token = yymsp[-2].minor.yy0;
}
#line 2181 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 28: /* decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var */
#line 352 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy207);
 yylhsminor.yy260->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy260->type->real.strct = psi_decl_struct_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy303);
 yylhsminor.yy260->type->real.strct->token = yymsp[-3].minor.yy0;
 yylhsminor.yy260->type->real.strct->align = yymsp[-2].minor.yy323.pos;
 yylhsminor.yy260->type->real.strct->size = yymsp[-2].minor.yy323.len;
}
#line 2195 "src/parser_proc.c"
  yymsp[-3].minor.yy260 = yylhsminor.yy260;
        break;
      case 29: /* decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var */
#line 360 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy207);
 yylhsminor.yy260->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy260->type->real.unn = psi_decl_union_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy303);
 yylhsminor.yy260->type->real.unn->token = yymsp[-3].minor.yy0;
 yylhsminor.yy260->type->real.unn->align = yymsp[-2].minor.yy323.pos;
 yylhsminor.yy260->type->real.unn->size = yymsp[-2].minor.yy323.len;
}
#line 2208 "src/parser_proc.c"
  yymsp[-3].minor.yy260 = yylhsminor.yy260;
        break;
      case 30: /* decl_typedef_body_ex ::= decl_enum NAME */
#line 368 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, yymsp[-1].minor.yy279->name), psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0));
 yylhsminor.yy260->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy260->type->token = psi_token_copy(yymsp[-1].minor.yy279->token);
 yylhsminor.yy260->type->real.enm = yymsp[-1].minor.yy279;
}
#line 2219 "src/parser_proc.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 31: /* decl_typedef_body ::= decl_typedef_body_ex */
      case 34: /* decl_typedef_body ::= decl_arg */ yytestcase(yyruleno==34);
      case 37: /* decl_func ::= decl_arg */ yytestcase(yyruleno==37);
#line 374 "src/parser_proc.y"
{
 yylhsminor.yy260 = yymsp[0].minor.yy260;
}
#line 2229 "src/parser_proc.c"
  yymsp[0].minor.yy260 = yylhsminor.yy260;
        break;
      case 32: /* decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN */
{  yy_destructor(yypParser,73,&yymsp[-2].minor);
#line 377 "src/parser_proc.y"
{
 yymsp[-2].minor.yy303 = yymsp[-1].minor.yy303;
}
#line 2238 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
}
        break;
      case 33: /* decl_typedef_body ::= decl_func decl_typedef_body_fn_args */
#line 380 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, yymsp[-1].minor.yy260->var->name), psi_decl_var_copy(yymsp[-1].minor.yy260->var));
 yylhsminor.yy260->type->token = psi_token_copy(yymsp[-1].minor.yy260->token);
 yylhsminor.yy260->type->real.func = psi_decl_init(psi_decl_abi_init("default"), yymsp[-1].minor.yy260, yymsp[0].minor.yy303);
}
#line 2249 "src/parser_proc.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 35: /* decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS */
#line 388 "src/parser_proc.y"
{
 yylhsminor.yy71 = psi_decl_init(yymsp[-5].minor.yy242, yymsp[-4].minor.yy260, yymsp[-2].minor.yy303);
}
#line 2257 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-3].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-5].minor.yy71 = yylhsminor.yy71;
        break;
      case 36: /* decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS */
#line 391 "src/parser_proc.y"
{
 yylhsminor.yy71 = psi_decl_init(yymsp[-7].minor.yy242, yymsp[-6].minor.yy260, yymsp[-4].minor.yy303);
 yylhsminor.yy71->varargs = 1;
}
#line 2269 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-5].minor);
  yy_destructor(yypParser,74,&yymsp[-3].minor);
  yy_destructor(yypParser,84,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-7].minor.yy71 = yylhsminor.yy71;
        break;
      case 38: /* decl_func ::= VOID NAME */
#line 398 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[-1].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0)
 );
 yylhsminor.yy260->type->token = yymsp[-1].minor.yy0;
 yylhsminor.yy260->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy260->token = yymsp[0].minor.yy0;
}
#line 2288 "src/parser_proc.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 39: /* decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 407 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy190, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy260->var->pointer_level = yymsp[-3].minor.yy190;
 yylhsminor.yy260->type->token = psi_token_copy(func_->token);
 yylhsminor.yy260->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy303);
}
#line 2309 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
  yymsp[-6].minor.yy260 = yylhsminor.yy260;
        break;
      case 40: /* decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
{  yy_destructor(yypParser,82,&yymsp[-7].minor);
#line 423 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy190, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yymsp[-7].minor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yymsp[-7].minor.yy260->var->pointer_level = yymsp[-3].minor.yy190;
 yymsp[-7].minor.yy260->type->token = psi_token_copy(func_->token);
 yymsp[-7].minor.yy260->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy303);
}
#line 2333 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
}
        break;
      case 41: /* decl_abi ::= NAME */
#line 439 "src/parser_proc.y"
{
 yylhsminor.yy242 = psi_decl_abi_init(yymsp[0].minor.yy0->text);
 yylhsminor.yy242->token = yymsp[0].minor.yy0;
}
#line 2344 "src/parser_proc.c"
  yymsp[0].minor.yy242 = yylhsminor.yy242;
        break;
      case 43: /* decl_var_array_size ::= LBRACKET NUMBER RBRACKET */
{  yy_destructor(yypParser,85,&yymsp[-2].minor);
#line 446 "src/parser_proc.y"
{
 yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
}
#line 2353 "src/parser_proc.c"
  yy_destructor(yypParser,86,&yymsp[0].minor);
}
        break;
      case 44: /* decl_var ::= NAME decl_var_array_size */
#line 449 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_decl_var_init(yymsp[-1].minor.yy0->text, 0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy207->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2366 "src/parser_proc.c"
  yymsp[-1].minor.yy207 = yylhsminor.yy207;
        break;
      case 45: /* decl_var ::= pointers NAME decl_var_array_size */
#line 456 "src/parser_proc.y"
{
 yylhsminor.yy207 = psi_decl_var_init(yymsp[-1].minor.yy0->text, yymsp[-2].minor.yy190+!!yymsp[0].minor.yy0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy207->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2378 "src/parser_proc.c"
  yymsp[-2].minor.yy207 = yylhsminor.yy207;
        break;
      case 46: /* decl_vars ::= decl_var */
#line 463 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
   &yymsp[0].minor.yy207);
}
#line 2387 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 47: /* decl_vars ::= decl_vars COMMA decl_var */
#line 467 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy207);
}
#line 2395 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 48: /* decl_arg ::= const_decl_type decl_var */
#line 470 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(yymsp[-1].minor.yy152, yymsp[0].minor.yy207);
}
#line 2404 "src/parser_proc.c"
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 49: /* decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 473 "src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  yymsp[-6].minor.yy152,
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy190, 0)
 );
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy260->var->pointer_level = yymsp[-3].minor.yy190;
 yylhsminor.yy260->type->token = psi_token_copy(func_->token);
 yylhsminor.yy260->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy303);
}
#line 2424 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
  yymsp[-6].minor.yy260 = yylhsminor.yy260;
        break;
      case 50: /* decl_arg ::= VOID pointers NAME */
#line 488 "src/parser_proc.y"
{
 yylhsminor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy190, 0)
 );
 yylhsminor.yy260->type->token = yymsp[-2].minor.yy0;
 yylhsminor.yy260->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy260->token = yymsp[0].minor.yy0;
}
#line 2440 "src/parser_proc.c"
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 51: /* decl_arg ::= CONST VOID pointers NAME */
{  yy_destructor(yypParser,82,&yymsp[-3].minor);
#line 497 "src/parser_proc.y"
{
 yymsp[-3].minor.yy260 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy190, 0)
 );
 yymsp[-3].minor.yy260->type->token = yymsp[-2].minor.yy0;
 yymsp[-3].minor.yy260->var->token = yymsp[0].minor.yy0;
 yymsp[-3].minor.yy260->token = yymsp[0].minor.yy0;
}
#line 2455 "src/parser_proc.c"
}
        break;
      case 52: /* decl_args ::= */
#line 506 "src/parser_proc.y"
{
 yymsp[1].minor.yy303 = NULL;
}
#line 2463 "src/parser_proc.c"
        break;
      case 53: /* decl_args ::= VOID */
{  yy_destructor(yypParser,57,&yymsp[0].minor);
#line 509 "src/parser_proc.y"
{
 yymsp[0].minor.yy303 = NULL;
}
#line 2471 "src/parser_proc.c"
}
        break;
      case 54: /* decl_args ::= decl_arg */
      case 56: /* struct_args ::= struct_arg */ yytestcase(yyruleno==56);
#line 512 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &yymsp[0].minor.yy260);
}
#line 2481 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 55: /* decl_args ::= decl_args COMMA decl_arg */
#line 516 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy260);
}
#line 2489 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 57: /* struct_args ::= struct_args struct_arg */
#line 523 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-1].minor.yy303, &yymsp[0].minor.yy260);
}
#line 2498 "src/parser_proc.c"
  yymsp[-1].minor.yy303 = yylhsminor.yy303;
        break;
      case 58: /* struct_arg ::= decl_typedef_body_ex EOS */
#line 526 "src/parser_proc.y"
{
 yylhsminor.yy260 = yymsp[-1].minor.yy260;
 switch (yymsp[-1].minor.yy260->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[-1].minor.yy260->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[-1].minor.yy260->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[-1].minor.yy260->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[-1].minor.yy260->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[-1].minor.yy260->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[-1].minor.yy260->type->real.enm);
  }
  break;
 }
}
#line 2532 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-1].minor.yy260 = yylhsminor.yy260;
        break;
      case 59: /* struct_arg ::= decl_arg decl_layout EOS */
#line 555 "src/parser_proc.y"
{
 yymsp[-2].minor.yy260->layout = yymsp[-1].minor.yy81;
 yylhsminor.yy260 = yymsp[-2].minor.yy260;
}
#line 2542 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy260 = yylhsminor.yy260;
        break;
      case 60: /* decl_layout ::= */
#line 559 "src/parser_proc.y"
{
 yymsp[1].minor.yy81 = NULL;
}
#line 2551 "src/parser_proc.c"
        break;
      case 61: /* decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,72,&yymsp[-6].minor);
#line 562 "src/parser_proc.y"
{
 yymsp[-6].minor.yy81 = psi_layout_init(atol(yymsp[-3].minor.yy0->text), atol(yymsp[-1].minor.yy0->text));
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2561 "src/parser_proc.c"
  yy_destructor(yypParser,72,&yymsp[-5].minor);
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
}
        break;
      case 63: /* decl_scalar_type ::= SHORT decl_scalar_type_short */
      case 67: /* decl_scalar_type ::= LONG decl_scalar_type_long */ yytestcase(yyruleno==67);
      case 70: /* decl_scalar_type_long ::= LONG decl_scalar_type_long_long */ yytestcase(yyruleno==70);
#line 570 "src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
  free(yymsp[-1].minor.yy0);
  free(yymsp[0].minor.yy0);
 } else {
  yylhsminor.yy0 = yymsp[-1].minor.yy0;
 }
}
#line 2581 "src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* decl_type ::= UNSIGNED decl_scalar_type */
      case 74: /* decl_type ::= SIGNED decl_scalar_type */ yytestcase(yyruleno==74);
#line 618 "src/parser_proc.y"
{
 struct psi_token *T = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
 yylhsminor.yy152 = psi_decl_type_init(T->type, T->text);
 yylhsminor.yy152->token = T;
 free(yymsp[-1].minor.yy0);
 free(yymsp[0].minor.yy0);
}
#line 2594 "src/parser_proc.c"
  yymsp[-1].minor.yy152 = yylhsminor.yy152;
        break;
      case 75: /* decl_type ::= UNSIGNED */
      case 76: /* decl_type ::= SIGNED */ yytestcase(yyruleno==76);
#line 632 "src/parser_proc.y"
{
 yylhsminor.yy152 = psi_decl_type_init(PSI_T_NAME, yymsp[0].minor.yy0->text);
 yylhsminor.yy152->token = yymsp[0].minor.yy0;
}
#line 2604 "src/parser_proc.c"
  yymsp[0].minor.yy152 = yylhsminor.yy152;
        break;
      case 77: /* decl_type ::= decl_scalar_type */
      case 81: /* decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME */ yytestcase(yyruleno==81);
#line 640 "src/parser_proc.y"
{
 yylhsminor.yy152 = psi_decl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy152->token = yymsp[0].minor.yy0;
}
#line 2614 "src/parser_proc.c"
  yymsp[0].minor.yy152 = yylhsminor.yy152;
        break;
      case 78: /* decl_type ::= STRUCT NAME */
      case 79: /* decl_type ::= UNION NAME */ yytestcase(yyruleno==79);
      case 80: /* decl_type ::= ENUM NAME */ yytestcase(yyruleno==80);
#line 644 "src/parser_proc.y"
{
 yylhsminor.yy152 = psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy152->token = yymsp[0].minor.yy0;
 free(yymsp[-1].minor.yy0);
}
#line 2626 "src/parser_proc.c"
  yymsp[-1].minor.yy152 = yylhsminor.yy152;
        break;
      case 82: /* const_decl_type ::= decl_type */
#line 663 "src/parser_proc.y"
{
 yylhsminor.yy152 = yymsp[0].minor.yy152;
}
#line 2634 "src/parser_proc.c"
  yymsp[0].minor.yy152 = yylhsminor.yy152;
        break;
      case 83: /* const_decl_type ::= CONST decl_type */
{  yy_destructor(yypParser,82,&yymsp[-1].minor);
#line 666 "src/parser_proc.y"
{
 yymsp[-1].minor.yy152 = yymsp[0].minor.yy152;
}
#line 2643 "src/parser_proc.c"
}
        break;
      case 84: /* impl ::= impl_func LBRACE impl_stmts RBRACE */
#line 669 "src/parser_proc.y"
{
 yylhsminor.yy49 = psi_impl_init(yymsp[-3].minor.yy120, yymsp[-1].minor.yy303);
}
#line 2651 "src/parser_proc.c"
  yy_destructor(yypParser,79,&yymsp[-2].minor);
  yy_destructor(yypParser,80,&yymsp[0].minor);
  yymsp[-3].minor.yy49 = yylhsminor.yy49;
        break;
      case 85: /* impl ::= STATIC impl_func LBRACE impl_stmts RBRACE */
{  yy_destructor(yypParser,92,&yymsp[-4].minor);
#line 672 "src/parser_proc.y"
{
 yymsp[-3].minor.yy120->static_memory = 1;
 yymsp[-4].minor.yy49 = psi_impl_init(yymsp[-3].minor.yy120, yymsp[-1].minor.yy303);
}
#line 2663 "src/parser_proc.c"
  yy_destructor(yypParser,79,&yymsp[-2].minor);
  yy_destructor(yypParser,80,&yymsp[0].minor);
}
        break;
      case 86: /* impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type */
{  yy_destructor(yypParser,93,&yymsp[-6].minor);
#line 676 "src/parser_proc.y"
{
 yymsp[-6].minor.yy120 = psi_impl_func_init(yymsp[-4].minor.yy0->text, NULL, yymsp[0].minor.yy142);
 yymsp[-6].minor.yy120->token = yymsp[-4].minor.yy0;
 yymsp[-6].minor.yy120->return_reference = yymsp[-5].minor.yy273;
}
#line 2676 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-3].minor);
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[-1].minor);
}
        break;
      case 87: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type */
{  yy_destructor(yypParser,93,&yymsp[-7].minor);
#line 681 "src/parser_proc.y"
{
 yymsp[-7].minor.yy120 = psi_impl_func_init(yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy303, yymsp[0].minor.yy142);
 yymsp[-7].minor.yy120->token = yymsp[-5].minor.yy0;
 yymsp[-7].minor.yy120->return_reference = yymsp[-6].minor.yy273;
}
#line 2690 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[-1].minor);
}
        break;
      case 88: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type */
{  yy_destructor(yypParser,93,&yymsp[-12].minor);
#line 686 "src/parser_proc.y"
{
 yymsp[-12].minor.yy120 = psi_impl_func_init(yymsp[-10].minor.yy0->text, yymsp[-8].minor.yy303, yymsp[0].minor.yy142);
 yymsp[-12].minor.yy120->token = yymsp[-10].minor.yy0;
 yymsp[-12].minor.yy120->return_reference = yymsp[-11].minor.yy273;
 yymsp[-12].minor.yy120->vararg = psi_impl_arg_init(yymsp[-6].minor.yy142, psi_impl_var_init(yymsp[-3].minor.yy0->text, yymsp[-5].minor.yy273), NULL);
 free(yymsp[-3].minor.yy0);
}
#line 2706 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-9].minor);
  yy_destructor(yypParser,74,&yymsp[-7].minor);
  yy_destructor(yypParser,84,&yymsp[-4].minor);
  yy_destructor(yypParser,75,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[-1].minor);
}
        break;
      case 89: /* impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING */
#line 693 "src/parser_proc.y"
{
 yylhsminor.yy21 = psi_impl_def_val_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy21->token = yymsp[0].minor.yy0;
}
#line 2720 "src/parser_proc.c"
  yymsp[0].minor.yy21 = yylhsminor.yy21;
        break;
      case 90: /* impl_var ::= reference DOLLAR_NAME */
#line 697 "src/parser_proc.y"
{
 yylhsminor.yy185 = psi_impl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy273);
 yylhsminor.yy185->token = yymsp[0].minor.yy0;
}
#line 2729 "src/parser_proc.c"
  yymsp[-1].minor.yy185 = yylhsminor.yy185;
        break;
      case 91: /* impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE */
#line 701 "src/parser_proc.y"
{
 yylhsminor.yy142 = psi_impl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2738 "src/parser_proc.c"
  yymsp[0].minor.yy142 = yylhsminor.yy142;
        break;
      case 92: /* impl_arg ::= impl_type impl_var */
#line 705 "src/parser_proc.y"
{
 yylhsminor.yy238 = psi_impl_arg_init(yymsp[-1].minor.yy142, yymsp[0].minor.yy185, NULL);
}
#line 2746 "src/parser_proc.c"
  yymsp[-1].minor.yy238 = yylhsminor.yy238;
        break;
      case 93: /* impl_arg ::= impl_type impl_var EQUALS impl_def_val */
#line 708 "src/parser_proc.y"
{
 yylhsminor.yy238 = psi_impl_arg_init(yymsp[-3].minor.yy142, yymsp[-2].minor.yy185, yymsp[0].minor.yy21);
}
#line 2754 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yymsp[-3].minor.yy238 = yylhsminor.yy238;
        break;
      case 94: /* impl_args ::= impl_arg */
#line 711 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
   &yymsp[0].minor.yy238);
}
#line 2764 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 95: /* impl_args ::= impl_args COMMA impl_arg */
#line 715 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy238);
}
#line 2772 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 96: /* impl_stmts ::= impl_stmt */
#line 718 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
   &yymsp[0].minor.yy38);
}
#line 2782 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 97: /* impl_stmts ::= impl_stmts impl_stmt */
#line 722 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-1].minor.yy303, &yymsp[0].minor.yy38);
}
#line 2790 "src/parser_proc.c"
  yymsp[-1].minor.yy303 = yylhsminor.yy303;
        break;
      case 98: /* impl_stmt ::= return_stmt */
#line 725 "src/parser_proc.y"
{
 yylhsminor.yy38 = (struct psi_token**) yymsp[0].minor.yy130;
}
#line 2798 "src/parser_proc.c"
  yymsp[0].minor.yy38 = yylhsminor.yy38;
        break;
      case 99: /* impl_stmt ::= let_stmt */
#line 728 "src/parser_proc.y"
{
 yylhsminor.yy38 = (struct psi_token**) yymsp[0].minor.yy139;
}
#line 2806 "src/parser_proc.c"
  yymsp[0].minor.yy38 = yylhsminor.yy38;
        break;
      case 100: /* impl_stmt ::= set_stmt */
#line 731 "src/parser_proc.y"
{
 yylhsminor.yy38 = (struct psi_token**) yymsp[0].minor.yy226;
}
#line 2814 "src/parser_proc.c"
  yymsp[0].minor.yy38 = yylhsminor.yy38;
        break;
      case 101: /* impl_stmt ::= free_stmt */
#line 734 "src/parser_proc.y"
{
 yylhsminor.yy38 = (struct psi_token**) yymsp[0].minor.yy76;
}
#line 2822 "src/parser_proc.c"
  yymsp[0].minor.yy38 = yylhsminor.yy38;
        break;
      case 102: /* number ::= NUMBER|NSNAME */
#line 737 "src/parser_proc.y"
{
 yylhsminor.yy160 = psi_number_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy160->token = yymsp[0].minor.yy0;
}
#line 2831 "src/parser_proc.c"
  yymsp[0].minor.yy160 = yylhsminor.yy160;
        break;
      case 103: /* number ::= decl_var */
#line 741 "src/parser_proc.y"
{
 yylhsminor.yy160 = psi_number_init(PSI_T_NAME, yymsp[0].minor.yy207);
 yylhsminor.yy160->token = psi_token_copy(yymsp[0].minor.yy207->token);
}
#line 2840 "src/parser_proc.c"
  yymsp[0].minor.yy160 = yylhsminor.yy160;
        break;
      case 104: /* num_exp ::= number */
#line 745 "src/parser_proc.y"
{
 yylhsminor.yy39 = psi_num_exp_init_num(yymsp[0].minor.yy160);
 yylhsminor.yy39->token = psi_token_copy(yymsp[0].minor.yy160->token);
}
#line 2849 "src/parser_proc.c"
  yymsp[0].minor.yy39 = yylhsminor.yy39;
        break;
      case 105: /* num_exp ::= LPAREN num_exp RPAREN */
#line 749 "src/parser_proc.y"
{
 yylhsminor.yy39 = psi_num_exp_init_unary(PSI_T_LPAREN, yymsp[-1].minor.yy39);
 yylhsminor.yy39->token = yymsp[-2].minor.yy0;
}
#line 2858 "src/parser_proc.c"
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-2].minor.yy39 = yylhsminor.yy39;
        break;
      case 106: /* num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO|RCHEVR|LCHEVR|CMP_GE|CMP_LE|OR|AND|CMP_EQ|CMP_NE num_exp */
#line 753 "src/parser_proc.y"
{
 yylhsminor.yy39 = psi_num_exp_init_binary(yymsp[-1].minor.yy0->type, yymsp[-2].minor.yy39, yymsp[0].minor.yy39);
 yylhsminor.yy39->token = yymsp[-1].minor.yy0;
}
#line 2868 "src/parser_proc.c"
  yymsp[-2].minor.yy39 = yylhsminor.yy39;
        break;
      case 107: /* num_exp ::= TILDE|NOT|PLUS|MINUS num_exp */
#line 757 "src/parser_proc.y"
{
 yylhsminor.yy39 = psi_num_exp_init_unary(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy39);
 yylhsminor.yy39->token = yymsp[-1].minor.yy0;
}
#line 2877 "src/parser_proc.c"
  yymsp[-1].minor.yy39 = yylhsminor.yy39;
        break;
      case 108: /* let_exp ::= NULL */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 761 "src/parser_proc.y"
{
 yymsp[0].minor.yy144 = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 2886 "src/parser_proc.c"
}
        break;
      case 109: /* let_exp ::= AMPERSAND NULL */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 764 "src/parser_proc.y"
{
 yymsp[-1].minor.yy144 = psi_let_exp_init(PSI_LET_NULL, NULL);
 yymsp[-1].minor.yy144->is_reference = 1;
}
#line 2896 "src/parser_proc.c"
  yy_destructor(yypParser,15,&yymsp[0].minor);
}
        break;
      case 110: /* let_exp ::= let_callback */
#line 768 "src/parser_proc.y"
{
 yylhsminor.yy144 = psi_let_exp_init(PSI_LET_CALLBACK, yymsp[0].minor.yy164);
}
#line 2905 "src/parser_proc.c"
  yymsp[0].minor.yy144 = yylhsminor.yy144;
        break;
      case 111: /* let_exp ::= let_calloc */
#line 771 "src/parser_proc.y"
{
 yylhsminor.yy144 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy17);
}
#line 2913 "src/parser_proc.c"
  yymsp[0].minor.yy144 = yylhsminor.yy144;
        break;
      case 112: /* let_exp ::= AMPERSAND let_calloc */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 774 "src/parser_proc.y"
{
 yymsp[-1].minor.yy144 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy17);
 yymsp[-1].minor.yy144->is_reference = 1;
}
#line 2923 "src/parser_proc.c"
}
        break;
      case 113: /* let_exp ::= let_func */
#line 778 "src/parser_proc.y"
{
 yylhsminor.yy144 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy72);
}
#line 2931 "src/parser_proc.c"
  yymsp[0].minor.yy144 = yylhsminor.yy144;
        break;
      case 114: /* let_exp ::= AMPERSAND let_func */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 781 "src/parser_proc.y"
{
 yymsp[-1].minor.yy144 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy72);
 yymsp[-1].minor.yy144->is_reference = 1;
}
#line 2941 "src/parser_proc.c"
}
        break;
      case 115: /* let_exp ::= num_exp */
#line 785 "src/parser_proc.y"
{
 yylhsminor.yy144 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy39);
}
#line 2949 "src/parser_proc.c"
  yymsp[0].minor.yy144 = yylhsminor.yy144;
        break;
      case 116: /* let_exp ::= AMPERSAND num_exp */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 788 "src/parser_proc.y"
{
 yymsp[-1].minor.yy144 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy39);
 yymsp[-1].minor.yy144->is_reference = 1;
}
#line 2959 "src/parser_proc.c"
}
        break;
      case 117: /* let_exp ::= decl_var EQUALS let_exp */
#line 792 "src/parser_proc.y"
{
 yylhsminor.yy144 = yymsp[0].minor.yy144;
 yylhsminor.yy144->var = yymsp[-2].minor.yy207;
}
#line 2968 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yymsp[-2].minor.yy144 = yylhsminor.yy144;
        break;
      case 118: /* let_stmt ::= LET let_exp EOS */
#line 796 "src/parser_proc.y"
{
 yylhsminor.yy139 = psi_let_stmt_init(yymsp[-1].minor.yy144);
 yylhsminor.yy139->token = yymsp[-2].minor.yy0;
}
#line 2978 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy139 = yylhsminor.yy139;
        break;
      case 119: /* let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS */
#line 800 "src/parser_proc.y"
{
 yylhsminor.yy139 = psi_let_stmt_init(psi_let_exp_init_ex(yymsp[-4].minor.yy207, PSI_LET_TMP, yymsp[-1].minor.yy207));
 yylhsminor.yy139->token = yymsp[-5].minor.yy0;
 yylhsminor.yy139->exp->is_reference = yymsp[-2].minor.yy273 ? 1 : 0;
}
#line 2989 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-3].minor);
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-5].minor.yy139 = yylhsminor.yy139;
        break;
      case 120: /* let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN */
#line 805 "src/parser_proc.y"
{
 yylhsminor.yy164 = psi_let_callback_init(psi_let_func_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text, yymsp[-4].minor.yy185), yymsp[-2].minor.yy287);
 yylhsminor.yy164->token = yymsp[-7].minor.yy0;
 free(yymsp[-6].minor.yy0);
}
#line 3001 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-5].minor);
  yy_destructor(yypParser,73,&yymsp[-3].minor);
  yy_destructor(yypParser,75,&yymsp[-1].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-7].minor.yy164 = yylhsminor.yy164;
        break;
      case 121: /* let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN */
#line 810 "src/parser_proc.y"
{
 yylhsminor.yy17 = psi_let_calloc_init(yymsp[-3].minor.yy39, yymsp[-1].minor.yy39);
 yylhsminor.yy17->token = yymsp[-5].minor.yy0;
}
#line 3014 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy17 = yylhsminor.yy17;
        break;
      case 122: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN */
#line 814 "src/parser_proc.y"
{
 yylhsminor.yy72 = psi_let_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy185);
 yylhsminor.yy72->token = yymsp[-3].minor.yy0;
}
#line 3026 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-3].minor.yy72 = yylhsminor.yy72;
        break;
      case 123: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN */
#line 818 "src/parser_proc.y"
{
 yylhsminor.yy72 = psi_let_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy185);
 yylhsminor.yy72->token = yymsp[-5].minor.yy0;
 yylhsminor.yy72->inner = yymsp[-1].minor.yy303;
}
#line 3038 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy72 = yylhsminor.yy72;
        break;
      case 124: /* let_exps ::= let_exp */
#line 823 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
   &yymsp[0].minor.yy144);
}
#line 3050 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 125: /* let_exps ::= let_exps COMMA let_exp */
#line 827 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy144);
}
#line 3058 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 126: /* callback_arg_list ::= */
#line 830 "src/parser_proc.y"
{
 yymsp[1].minor.yy287 = NULL;
}
#line 3067 "src/parser_proc.c"
        break;
      case 127: /* callback_arg_list ::= callback_args */
#line 833 "src/parser_proc.y"
{
 yylhsminor.yy287 = yymsp[0].minor.yy287;
}
#line 3074 "src/parser_proc.c"
  yymsp[0].minor.yy287 = yylhsminor.yy287;
        break;
      case 128: /* callback_args ::= set_exp */
#line 836 "src/parser_proc.y"
{
 yylhsminor.yy287 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy67);
}
#line 3083 "src/parser_proc.c"
  yymsp[0].minor.yy287 = yylhsminor.yy287;
        break;
      case 129: /* callback_args ::= callback_args COMMA set_exp */
#line 840 "src/parser_proc.y"
{
 yylhsminor.yy287 = psi_plist_add(yymsp[-2].minor.yy287, &yymsp[0].minor.yy67);
}
#line 3091 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy287 = yylhsminor.yy287;
        break;
      case 132: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN */
#line 849 "src/parser_proc.y"
{
 yylhsminor.yy78 = psi_set_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy207);
 yylhsminor.yy78->token = yymsp[-3].minor.yy0;
}
#line 3101 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-3].minor.yy78 = yylhsminor.yy78;
        break;
      case 133: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN */
#line 853 "src/parser_proc.y"
{
 yylhsminor.yy78 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy207);
 yylhsminor.yy78->token = yymsp[-5].minor.yy0;
 yylhsminor.yy78->inner = yymsp[-1].minor.yy303;
}
#line 3113 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy78 = yylhsminor.yy78;
        break;
      case 134: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN */
#line 858 "src/parser_proc.y"
{
 yylhsminor.yy78 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy207);
 yylhsminor.yy78->token = yymsp[-5].minor.yy0;
 yylhsminor.yy78->recursive = 1;
}
#line 3126 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-4].minor);
  yy_destructor(yypParser,74,&yymsp[-2].minor);
  yy_destructor(yypParser,84,&yymsp[-1].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-5].minor.yy78 = yylhsminor.yy78;
        break;
      case 135: /* set_exp ::= set_func */
#line 863 "src/parser_proc.y"
{
 yylhsminor.yy67 = psi_set_exp_init(PSI_SET_FUNC, yymsp[0].minor.yy78);
}
#line 3138 "src/parser_proc.c"
  yymsp[0].minor.yy67 = yylhsminor.yy67;
        break;
      case 136: /* set_exp ::= num_exp */
#line 866 "src/parser_proc.y"
{
 yylhsminor.yy67 = psi_set_exp_init(PSI_SET_NUMEXP, yymsp[0].minor.yy39);
}
#line 3146 "src/parser_proc.c"
  yymsp[0].minor.yy67 = yylhsminor.yy67;
        break;
      case 137: /* set_exps ::= set_exp */
#line 869 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy67);
}
#line 3155 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 138: /* set_exps ::= set_exps COMMA set_exp */
#line 873 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy67);
}
#line 3163 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 139: /* set_exp ::= impl_var EQUALS set_exp */
#line 876 "src/parser_proc.y"
{
 yylhsminor.yy67 = yymsp[0].minor.yy67;
 yylhsminor.yy67->var = yymsp[-2].minor.yy185;
}
#line 3173 "src/parser_proc.c"
  yy_destructor(yypParser,81,&yymsp[-1].minor);
  yymsp[-2].minor.yy67 = yylhsminor.yy67;
        break;
      case 140: /* set_stmt ::= SET set_exp EOS */
#line 880 "src/parser_proc.y"
{
 yylhsminor.yy226 = psi_set_stmt_init(yymsp[-1].minor.yy67);
 yylhsminor.yy226->token = yymsp[-2].minor.yy0;
}
#line 3183 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy226 = yylhsminor.yy226;
        break;
      case 141: /* return_stmt ::= RETURN set_func EOS */
#line 884 "src/parser_proc.y"
{
 yylhsminor.yy130 = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, yymsp[-1].minor.yy78));
 yylhsminor.yy130->token = yymsp[-2].minor.yy0;
}
#line 3193 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy130 = yylhsminor.yy130;
        break;
      case 142: /* free_stmt ::= FREE free_exps EOS */
#line 888 "src/parser_proc.y"
{
 yylhsminor.yy76 = psi_free_stmt_init(yymsp[-1].minor.yy303);
 yylhsminor.yy76->token = yymsp[-2].minor.yy0;
}
#line 3203 "src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[0].minor);
  yymsp[-2].minor.yy76 = yylhsminor.yy76;
        break;
      case 143: /* free_exps ::= free_exp */
#line 892 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
   &yymsp[0].minor.yy197);
}
#line 3213 "src/parser_proc.c"
  yymsp[0].minor.yy303 = yylhsminor.yy303;
        break;
      case 144: /* free_exps ::= free_exps COMMA free_exp */
#line 896 "src/parser_proc.y"
{
 yylhsminor.yy303 = psi_plist_add(yymsp[-2].minor.yy303, &yymsp[0].minor.yy197);
}
#line 3221 "src/parser_proc.c"
  yy_destructor(yypParser,74,&yymsp[-1].minor);
  yymsp[-2].minor.yy303 = yylhsminor.yy303;
        break;
      case 145: /* free_exp ::= NAME LPAREN decl_vars RPAREN */
#line 899 "src/parser_proc.y"
{
 yylhsminor.yy197 = psi_free_exp_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy303);
 yylhsminor.yy197->token = yymsp[-3].minor.yy0;
}
#line 3231 "src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-2].minor);
  yy_destructor(yypParser,75,&yymsp[0].minor);
  yymsp[-3].minor.yy197 = yylhsminor.yy197;
        break;
      case 146: /* reference ::= */
#line 903 "src/parser_proc.y"
{
 yymsp[1].minor.yy273 = false;
}
#line 3241 "src/parser_proc.c"
        break;
      case 147: /* reference ::= AMPERSAND */
{  yy_destructor(yypParser,23,&yymsp[0].minor);
#line 906 "src/parser_proc.y"
{
 yymsp[0].minor.yy273 = true;
}
#line 3249 "src/parser_proc.c"
}
        break;
      case 148: /* indirection ::= */
#line 909 "src/parser_proc.y"
{
 yymsp[1].minor.yy190 = 0;
}
#line 3257 "src/parser_proc.c"
        break;
      case 149: /* indirection ::= pointers */
#line 912 "src/parser_proc.y"
{
 yylhsminor.yy190 = yymsp[0].minor.yy190;
}
#line 3264 "src/parser_proc.c"
  yymsp[0].minor.yy190 = yylhsminor.yy190;
        break;
      case 150: /* pointers ::= ASTERISK */
{  yy_destructor(yypParser,28,&yymsp[0].minor);
#line 915 "src/parser_proc.y"
{
 yymsp[0].minor.yy190 = 1;
}
#line 3273 "src/parser_proc.c"
}
        break;
      case 151: /* pointers ::= pointers ASTERISK */
#line 918 "src/parser_proc.y"
{
 yylhsminor.yy190 = yymsp[-1].minor.yy190+1;
}
#line 3281 "src/parser_proc.c"
  yy_destructor(yypParser,28,&yymsp[0].minor);
  yymsp[-1].minor.yy190 = yylhsminor.yy190;
        break;
      case 152: /* file ::= blocks */
{  yy_destructor(yypParser,154,&yymsp[0].minor);
#line 172 "src/parser_proc.y"
{
}
#line 3290 "src/parser_proc.c"
}
        break;
      case 153: /* blocks ::= block */
{  yy_destructor(yypParser,155,&yymsp[0].minor);
#line 173 "src/parser_proc.y"
{
}
#line 3298 "src/parser_proc.c"
}
        break;
      case 154: /* blocks ::= blocks block */
{  yy_destructor(yypParser,154,&yymsp[-1].minor);
#line 174 "src/parser_proc.y"
{
}
#line 3306 "src/parser_proc.c"
  yy_destructor(yypParser,155,&yymsp[0].minor);
}
        break;
      case 155: /* block ::= EOF */
{  yy_destructor(yypParser,70,&yymsp[0].minor);
#line 175 "src/parser_proc.y"
{
}
#line 3315 "src/parser_proc.c"
}
        break;
      case 156: /* block ::= EOS */
{  yy_destructor(yypParser,71,&yymsp[0].minor);
#line 176 "src/parser_proc.y"
{
}
#line 3323 "src/parser_proc.c"
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
#line 3385 "src/parser_proc.c"
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
