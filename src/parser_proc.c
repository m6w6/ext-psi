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
#line 1 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"

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

#line 62 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
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
#define YYNOCODE 159
#define YYACTIONTYPE unsigned short int
#define ParseTOKENTYPE struct psi_token *
typedef union {
  int yyinit;
  ParseTOKENTYPE yy0;
  struct psi_let_calloc* yy9;
  struct psi_decl_var* yy11;
  struct psi_let_exp* yy20;
  struct psi_set_func* yy26;
  struct psi_let_func* yy27;
  struct psi_impl_var* yy37;
  struct psi_plist * yy43;
  struct psi_decl_enum * yy63;
  struct psi_token** yy78;
  struct psi_return_stmt* yy90;
  struct psi_layout yy91;
  struct psi_impl_def_val* yy93;
  struct psi_free_exp* yy94;
  struct psi_impl* yy97;
  struct psi_set_stmt* yy98;
  struct psi_decl* yy103;
  bool yy121;
  struct psi_decl_type* yy132;
  struct psi_impl_type* yy138;
  struct psi_layout* yy141;
  struct psi_set_exp* yy147;
  struct psi_const* yy154;
  struct psi_plist* yy163;
  struct psi_impl_func* yy168;
  struct psi_const_type* yy171;
  struct psi_decl_arg* yy184;
  struct psi_number* yy188;
  struct psi_free_stmt* yy192;
  unsigned yy202;
  struct psi_impl_arg* yy210;
  struct psi_decl_enum_item* yy217;
  struct psi_decl_abi* yy218;
  struct psi_let_callback* yy220;
  struct psi_num_exp* yy259;
  struct psi_decl_union* yy271;
  struct psi_decl_struct* yy275;
  struct psi_let_stmt* yy311;
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
#define YY_ACTTAB_COUNT (960)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   394,  409,   93,  409,  409,  409,  409,  409,  409,  409,
 /*    10 */   409,  409,  409,   93,  436,  430,  478,  164,  116,  430,
 /*    20 */   350,  423,   15,  475,  431,   27,   27,  478,    2,  133,
 /*    30 */    27,   27,  148,  148,  148,  148,  148,  148,  148,  148,
 /*    40 */   148,  148,  432,  100,   48,  440,  442,   83,   29,   29,
 /*    50 */    29,   29,   29,   29,   29,   29,   29,   29,  149,   56,
 /*    60 */   478,  422,  107,  122,   28,  155,   90,   89,   88,  365,
 /*    70 */   348,  397,   35,  470,  410,   43,   70,  390,   81,   67,
 /*    80 */    65,   64,  394,  409,   47,  409,  409,  409,  409,  409,
 /*    90 */   409,  409,  409,  409,  409,   39,   49,   11,   10,   60,
 /*   100 */    93,  437,  430,  349,  352,  411,  430,  417,  417,  417,
 /*   110 */   417,  417,   27,   27,  478,  405,  146,   27,   27,  148,
 /*   120 */   148,  148,  148,  148,  148,  148,  148,  148,  148,   83,
 /*   130 */   374,  108,  394,  409,  376,  409,  409,  409,  409,  409,
 /*   140 */   409,  409,  409,  409,  409,  149,  405,   80,  179,  181,
 /*   150 */   180,   28,  193,  182,   35,  425,  153,  376,  427,  390,
 /*   160 */    81,   67,   65,   64,  359,  166,  428,  494,   77,  122,
 /*   170 */   426,  429,  165,  122,  494,  382,  114,  410,   33,   41,
 /*   180 */   410,   43,  394,  409,  431,  409,  409,  409,  409,  409,
 /*   190 */   409,  409,  409,  409,  409,  158,  115,  416,   90,   89,
 /*   200 */    88,  415,  432,   96,   34,  414,  182,  375,  134,  390,
 /*   210 */    81,   67,   65,   64,  194,   87,   85,  178,  405,  136,
 /*   220 */   421,  405,  167,  122,  169,   79,  137,    4,  384,   83,
 /*   230 */   410,   43,  394,  409,  112,  409,  409,  409,  409,  409,
 /*   240 */   409,  409,  409,  409,  409,  357,  122,  394,   90,   89,
 /*   250 */    88,  382,  117,  182,   35,  119,  410,   43,  122,  390,
 /*   260 */    81,   67,   65,   64,  178,  122,  379,  194,   87,   85,
 /*   270 */    94,  405,   79,  122,  395,  385,  343,  410,   43,   76,
 /*   280 */   479,  366,  394,  409,  122,  409,  409,  409,  409,  409,
 /*   290 */   409,  409,  409,  409,  409,  478,  402,  405,  179,  181,
 /*   300 */   180,  383,  349,  351,   35,  124,  410,   43,  401,  390,
 /*   310 */    81,   67,   65,   64,  194,   87,   85,   53,  405,  131,
 /*   320 */   419,  419,  419,  419,  390,   81,   67,  431,   68,   66,
 /*   330 */   147,  132,  394,  409,  431,  409,  409,  409,  409,  409,
 /*   340 */   409,  409,  409,  409,  409,  432,   97,  405,  179,  181,
 /*   350 */   180,   38,  432,  102,   35,  124,  431,  127,  431,  390,
 /*   360 */    81,   67,   65,   64,   36,  128,  122,  418,  419,  419,
 /*   370 */   419,  419,  419,  122,  432,   98,  432,  104,   20,   83,
 /*   380 */   106,  472,  394,  409,  431,  409,  409,  409,  409,  409,
 /*   390 */   409,  409,  409,  409,  409,  122,  377,  122,  179,  181,
 /*   400 */   180,  368,  432,  103,   35,  353,  353,  353,  353,  390,
 /*   410 */    81,   67,   65,   64,   29,   29,   29,   29,   29,   29,
 /*   420 */    29,   29,   29,  122,  109,  471,  356,  145,  113,   74,
 /*   430 */   157,  161,  394,  409,  105,  409,  409,  409,  409,  409,
 /*   440 */   409,  409,  409,  409,  409,  160,  161,  367,  179,  181,
 /*   450 */   180,  361,  147,  147,  189,  163,  161,   42,  176,  390,
 /*   460 */    81,   67,   65,   64,   92,  122,  177,  458,  458,  458,
 /*   470 */   458,  458,  458,  458,  458,  458,  458,  335,  479,   82,
 /*   480 */   123,  344,  333,  459,  334,  400,  332,  331,   37,  473,
 /*   490 */   398,  329,  393,   19,    8,  451,  391,  118,  179,  181,
 /*   500 */   180,  378,    2,  330,  151,   13,  461,    7,  460,  390,
 /*   510 */    81,   67,   65,   64,   93,  479,  430,    6,  450,   84,
 /*   520 */   430,   86,  120,  475,   44,  342,   27,   27,  478,   23,
 /*   530 */   154,   27,   27,  141,  643,    3,    3,   45,  194,   24,
 /*   540 */   360,  379,  121,  141,  141,  141,  141,  141,  141,  141,
 /*   550 */   341,  183,   46,  340,  192,  479,  345,  337,   93,  373,
 /*   560 */   430,  372,   61,   57,  430,   28,  126,  475,  125,   58,
 /*   570 */    27,   27,  478,   59,  130,   27,   27,  141,  419,  419,
 /*   580 */   419,  419,   31,   16,   32,  469,  631,  141,  141,  141,
 /*   590 */   141,  141,  141,  141,   29,   29,   29,   29,   29,   29,
 /*   600 */    29,   29,   29,   29,   93,  637,  430,   71,  468,   28,
 /*   610 */   430,  447,  446,  475,  462,   12,   27,   27,  478,  369,
 /*   620 */   139,   27,   27,  141,   40,  448,  419,  419,  419,  419,
 /*   630 */   419,   14,    5,  141,  141,  141,  141,  141,  141,  141,
 /*   640 */   449,  143,  418,   50,  129,   51,   26,  364,  369,    9,
 /*   650 */    17,  363,  152,   72,   18,   28,   29,   29,   29,   29,
 /*   660 */    29,   29,   29,   29,   29,   29,  196,  483,  484,  156,
 /*   670 */    93,   52,  430,   95,  190,  170,  430,   73,  159,   63,
 /*   680 */     1,  479,   27,   27,  478,  162,   75,   27,   27,   69,
 /*   690 */    68,   54,  522,  355,  354,  196,  483,  484,   62,  168,
 /*   700 */    78,   25,   95,  190,  170,  389,  335,  171,   63,    1,
 /*   710 */   172,  333,  173,  334,  141,  332,  331,  174,   69,   68,
 /*   720 */   329,   28,   19,  175,  141,  141,  141,  141,  141,  141,
 /*   730 */   141,  387,  330,  151,  150,   29,   29,   29,   29,   29,
 /*   740 */    29,   29,   29,   29,   29,  431,  386,  494,  408,  407,
 /*   750 */   185,  406,  432,  101,  358,  439,  441,  140,  184,  438,
 /*   760 */   452,  110,  339,  432,   99,  482,  186,  194,  144,  142,
 /*   770 */   187,  431,  188,  122,  456,   91,  463,  371,  191,   30,
 /*   780 */    55,  433,  147,  140,  122,  328,  195,  487,  487,  432,
 /*   790 */    99,  487,  487,  150,  487,   39,   49,   11,   10,   60,
 /*   800 */   465,  111,  463,  150,  487,  487,  487,  487,  147,  487,
 /*   810 */   122,  432,  101,  413,  439,  441,  487,  487,  438,  453,
 /*   820 */   487,  432,  101,  487,  439,  441,  150,  487,  438,  445,
 /*   830 */   487,  487,  122,  487,  487,  487,  487,  487,  431,  487,
 /*   840 */   487,  431,  122,  487,  432,  101,  487,  439,  441,  487,
 /*   850 */   140,  438,  138,  140,  487,  487,  432,   99,  487,  432,
 /*   860 */    99,  487,  487,  487,  487,  122,  487,  135,  487,  463,
 /*   870 */   467,  431,  463,  487,  431,  147,  487,  122,  147,  487,
 /*   880 */   122,  487,  487,  140,  487,  487,  140,  487,  487,  432,
 /*   890 */    99,  487,  432,   99,  487,  487,  487,  487,  487,  487,
 /*   900 */   466,  487,  463,  457,  487,  463,  487,  487,  147,  487,
 /*   910 */   122,  147,  487,  122,  487,   21,  424,  487,  487,  427,
 /*   920 */   487,  487,   22,  424,  487,  487,  427,  428,  487,  487,
 /*   930 */   487,  426,  429,  487,  428,  487,  487,  487,  426,  429,
 /*   940 */   487,   39,   49,   11,   10,   60,  487,  487,  487,  487,
 /*   950 */   487,  487,  487,  487,  487,  487,  487,  487,  487,  412,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     2,    3,   14,    5,    6,    7,    8,    9,   10,   11,
 /*    10 */    12,   13,   14,   14,   15,   16,   28,  143,  144,   20,
 /*    20 */    63,  118,   23,   23,  105,   26,   27,   28,   71,   14,
 /*    30 */    31,   32,   33,   34,   35,   36,   37,   38,   39,   40,
 /*    40 */    41,   42,  123,  124,  141,  126,  127,   49,   21,   22,
 /*    50 */    23,   24,   25,   26,   27,   28,   29,   30,   59,   60,
 /*    60 */    28,  118,  119,  144,   65,  103,   68,   69,   70,  107,
 /*    70 */    72,    5,   74,   63,  112,  113,   66,   79,   80,   81,
 /*    80 */    82,   83,    2,    3,  141,    5,    6,    7,    8,    9,
 /*    90 */    10,   11,   12,   13,   14,   54,   55,   56,   57,   58,
 /*   100 */    14,   15,   16,   91,   92,  112,   20,   15,   16,   17,
 /*   110 */    18,   19,   26,   27,   28,  153,  157,   31,   32,   33,
 /*   120 */    34,   35,   36,   37,   38,   39,   40,   41,   42,   49,
 /*   130 */   105,  106,    2,    3,  105,    5,    6,    7,    8,    9,
 /*   140 */    10,   11,   12,   13,   14,   59,  153,   81,   68,   69,
 /*   150 */    70,   65,   14,   88,   74,  122,   76,  105,  125,   79,
 /*   160 */    80,   81,   82,   83,   99,  100,  133,   64,  103,  144,
 /*   170 */   137,  138,  107,  144,   71,  107,  108,  112,  113,   49,
 /*   180 */   112,  113,    2,    3,  105,    5,    6,    7,    8,    9,
 /*   190 */    10,   11,   12,   13,   14,  143,  144,  141,   68,   69,
 /*   200 */    70,  141,  123,  124,   74,  141,   88,  105,  136,   79,
 /*   210 */    80,   81,   82,   83,  149,  150,  151,   99,  153,  105,
 /*   220 */   116,  153,  116,  144,   96,  107,  105,  109,  110,   49,
 /*   230 */   112,  113,    2,    3,  105,    5,    6,    7,    8,    9,
 /*   240 */    10,   11,   12,   13,   14,  105,  144,    2,   68,   69,
 /*   250 */    70,  107,  108,   88,   74,  144,  112,  113,  144,   79,
 /*   260 */    80,   81,   82,   83,   99,  144,   14,  149,  150,  151,
 /*   270 */    66,  153,  107,  144,  155,  110,   72,  112,  113,   49,
 /*   280 */    28,   14,    2,    3,  144,    5,    6,    7,    8,    9,
 /*   290 */    10,   11,   12,   13,   14,   28,  153,  153,   68,   69,
 /*   300 */    70,  107,   91,   92,   74,  117,  112,  113,  153,   79,
 /*   310 */    80,   81,   82,   83,  149,  150,  151,   65,  153,  142,
 /*   320 */     1,    2,    3,    4,   79,   80,   81,  105,   85,   49,
 /*   330 */   142,  115,    2,    3,  105,    5,    6,    7,    8,    9,
 /*   340 */    10,   11,   12,   13,   14,  123,  124,  153,   68,   69,
 /*   350 */    70,  142,  123,  124,   74,  117,  105,   76,  105,   79,
 /*   360 */    80,   81,   82,   83,   66,   67,  144,   86,   49,   50,
 /*   370 */    51,   52,   53,  144,  123,  124,  123,  124,   65,   49,
 /*   380 */   142,  140,    2,    3,  105,    5,    6,    7,    8,    9,
 /*   390 */    10,   11,   12,   13,   14,  144,  101,  144,   68,   69,
 /*   400 */    70,  101,  123,  124,   74,    1,    2,    3,    4,   79,
 /*   410 */    80,   81,   82,   83,   22,   23,   24,   25,   26,   27,
 /*   420 */    28,   29,   30,  144,  139,  140,  105,  117,  117,   49,
 /*   430 */   143,  144,    2,    3,  144,    5,    6,    7,    8,    9,
 /*   440 */    10,   11,   12,   13,   14,  143,  144,  101,   68,   69,
 /*   450 */    70,  101,  142,  142,   64,  143,  144,   94,   64,   79,
 /*   460 */    80,   81,   82,   83,   14,  144,  111,   33,   34,   35,
 /*   470 */    36,   37,   38,   39,   40,   41,   42,   88,   28,   49,
 /*   480 */    89,   90,   93,   49,   95,    2,   97,   98,   66,   67,
 /*   490 */   156,  102,    2,  104,   66,   67,  154,  144,   68,   69,
 /*   500 */    70,   14,   71,  114,  115,   66,   67,   66,   67,   79,
 /*   510 */    80,   81,   82,   83,   14,   28,   16,   66,   67,   94,
 /*   520 */    20,   94,   14,   23,   91,  148,   26,   27,   28,   66,
 /*   530 */    67,   31,   32,   33,  145,  146,  147,   91,  149,   66,
 /*   540 */    67,   14,   14,   43,   44,   45,   46,   47,   48,   49,
 /*   550 */   148,   14,   94,  148,   77,   28,   90,   14,   14,  152,
 /*   560 */    16,  152,   73,   64,   20,   65,   86,   23,   67,   64,
 /*   570 */    26,   27,   28,   64,   20,   31,   32,   33,    1,    2,
 /*   580 */     3,    4,   65,   71,   65,   63,   86,   43,   44,   45,
 /*   590 */    46,   47,   48,   49,   21,   22,   23,   24,   25,   26,
 /*   600 */    27,   28,   29,   30,   14,    0,   16,   73,   63,   65,
 /*   610 */    20,   63,   63,   23,   67,   73,   26,   27,   28,   14,
 /*   620 */    76,   31,   32,   33,   65,   67,   49,   50,   51,   52,
 /*   630 */    53,   66,   65,   43,   44,   45,   46,   47,   48,   49,
 /*   640 */    67,   67,   86,   65,   67,   65,   65,   63,   14,   73,
 /*   650 */    71,   63,   67,   67,   65,   65,   21,   22,   23,   24,
 /*   660 */    25,   26,   27,   28,   29,   30,   61,   62,   63,   14,
 /*   670 */    14,   65,   16,   68,   69,   70,   20,   67,   14,   74,
 /*   680 */    75,   28,   26,   27,   28,   14,   67,   31,   32,   84,
 /*   690 */    85,   65,   65,   63,   63,   61,   62,   63,   73,   20,
 /*   700 */    14,   66,   68,   69,   70,   67,   88,   16,   74,   75,
 /*   710 */    66,   93,   16,   95,   33,   97,   98,   65,   84,   85,
 /*   720 */   102,   65,  104,   64,   43,   44,   45,   46,   47,   48,
 /*   730 */    49,   63,  114,  115,  105,   21,   22,   23,   24,   25,
 /*   740 */    26,   27,   28,   29,   30,  105,   63,   71,   14,   14,
 /*   750 */    66,   14,  123,  124,   14,  126,  127,  117,   16,  130,
 /*   760 */   131,  132,   67,  123,  124,  147,   16,  149,  128,  129,
 /*   770 */    65,  105,   64,  144,  134,   14,  136,   78,   16,   73,
 /*   780 */    71,   67,  142,  117,  144,   63,   19,  158,  158,  123,
 /*   790 */   124,  158,  158,  105,  158,   54,   55,   56,   57,   58,
 /*   800 */   134,  135,  136,  105,  158,  158,  158,  158,  142,  158,
 /*   810 */   144,  123,  124,   72,  126,  127,  158,  158,  130,  131,
 /*   820 */   158,  123,  124,  158,  126,  127,  105,  158,  130,  131,
 /*   830 */   158,  158,  144,  158,  158,  158,  158,  158,  105,  158,
 /*   840 */   158,  105,  144,  158,  123,  124,  158,  126,  127,  158,
 /*   850 */   117,  130,  131,  117,  158,  158,  123,  124,  158,  123,
 /*   860 */   124,  158,  158,  158,  158,  144,  158,  134,  158,  136,
 /*   870 */   134,  105,  136,  158,  105,  142,  158,  144,  142,  158,
 /*   880 */   144,  158,  158,  117,  158,  158,  117,  158,  158,  123,
 /*   890 */   124,  158,  123,  124,  158,  158,  158,  158,  158,  158,
 /*   900 */   134,  158,  136,  134,  158,  136,  158,  158,  142,  158,
 /*   910 */   144,  142,  158,  144,  158,  121,  122,  158,  158,  125,
 /*   920 */   158,  158,  121,  122,  158,  158,  125,  133,  158,  158,
 /*   930 */   158,  137,  138,  158,  133,  158,  158,  158,  137,  138,
 /*   940 */   158,   54,   55,   56,   57,   58,  158,  158,  158,  158,
 /*   950 */   158,  158,  158,  158,  158,  158,  158,  158,  158,   72,
};
#define YY_SHIFT_USE_DFLT (960)
#define YY_SHIFT_COUNT    (196)
#define YY_SHIFT_MIN      (-43)
#define YY_SHIFT_MAX      (887)
static const short yy_shift_ofst[] = {
 /*     0 */   634,  130,  180,  605,   -2,  500,   -1,  544,   -1,   -1,
 /*    10 */    -1,  590,  590,  590,  590,   86,   41,   41,  230,  280,
 /*    20 */   230,  741,  887,   80,  330,  656,  656,  656,  656,  656,
 /*    30 */   656,  577,  -12,  -12,  380,  430,  319,  -12,  -12,  -12,
 /*    40 */   -12,  267,  -43,  -12,  -12,  -12,  -43,    0,    0,   15,
 /*    50 */     0,    0,   32,   32,   32,  138,  434,  319,  319,  319,
 /*    60 */   681,   92,   92,  404,  245,  245,  267,   66,    0,  243,
 /*    70 */    15,    0,  313,  313,   32,  313,   32,  313,  390,  394,
 /*    80 */   483,  490,   32,   32,  431,  390,  431,  390,  508,  528,
 /*    90 */   537,  390,  477,  477,  138,  543,  573,  635,  714,   27,
 /*   100 */    27,   27,   27,   27,  392,  252,  281,  298,  422,   10,
 /*   110 */   428,  439,  441,  451,  463,  450,  487,  473,  527,  487,
 /*   120 */   103,  103,  450,  204,  489,  499,  501,  480,  505,  509,
 /*   130 */   517,  554,  512,  519,  522,  545,  548,  534,  549,  547,
 /*   140 */   542,  559,  565,  558,  574,  567,  578,  556,  580,  581,
 /*   150 */   576,  579,  584,  585,  588,  589,  586,  655,  606,  610,
 /*   160 */   664,  653,  619,  671,  626,  627,  630,  631,  625,  679,
 /*   170 */   686,  638,  691,  644,  696,  652,  659,  668,  683,  734,
 /*   180 */   735,  737,  740,  676,  695,  742,  684,  750,  705,  708,
 /*   190 */   761,  699,  762,  706,  709,  722,  767,
};
#define YY_REDUCE_USE_DFLT (-127)
#define YY_REDUCE_COUNT (95)
#define YY_REDUCE_MIN   (-126)
#define YY_REDUCE_MAX   (801)
static const short yy_reduce_ofst[] = {
 /*     0 */   389,   65,  118,  618,  165,  640,  629,  666,  688,  698,
 /*    10 */   721,  733,  736,  766,  769,  -81,  794,  801,   68,  -38,
 /*    20 */   144,   33,   33,  194,  194,   79,  222,  229,  251,  253,
 /*    30 */   279,  -57,   25,   52,   -7,   -7,  -97,  102,  114,  121,
 /*    40 */   129, -126,   12,   29,  140,  321,  211,  188,  238,  285,
 /*    50 */   310,  311,  287,  302,  312,  391,  -41,   56,   60,   64,
 /*    60 */    72,  104,  106,  128,  143,  155,  111,  119,  177,  216,
 /*    70 */   241,  209,  295,  300,  290,  346,  111,  350,  363,  355,
 /*    80 */   334,  342,  353,  111,  433,  425,  446,  427,  377,  402,
 /*    90 */   405,  458,  407,  409,  466,  405,
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
  "ASTERISK",      "SLASH",         "MODULO",        "TILDE",       
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
 /* 106 */ "num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO num_exp",
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
    case 31: /* TILDE */
    case 32: /* NOT */
    case 33: /* ZVAL */
    case 34: /* OBJVAL */
    case 35: /* ARRVAL */
    case 36: /* PATHVAL */
    case 37: /* STRLEN */
    case 38: /* STRVAL */
    case 39: /* FLOATVAL */
    case 40: /* INTVAL */
    case 41: /* BOOLVAL */
    case 42: /* COUNT */
    case 43: /* TO_OBJECT */
    case 44: /* TO_ARRAY */
    case 45: /* TO_STRING */
    case 46: /* TO_INT */
    case 47: /* TO_FLOAT */
    case 48: /* TO_BOOL */
    case 49: /* VOID */
    case 50: /* MIXED */
    case 51: /* ARRAY */
    case 52: /* OBJECT */
    case 53: /* CALLABLE */
    case 54: /* TEMP */
    case 55: /* FREE */
    case 56: /* SET */
    case 57: /* LET */
    case 58: /* RETURN */
    case 59: /* CALLOC */
    case 60: /* CALLBACK */
    case 61: /* LIB */
    case 62: /* EOF */
    case 63: /* EOS */
    case 64: /* COLON */
    case 65: /* LPAREN */
    case 66: /* COMMA */
    case 67: /* RPAREN */
    case 68: /* ENUM */
    case 69: /* STRUCT */
    case 70: /* UNION */
    case 71: /* LBRACE */
    case 72: /* RBRACE */
    case 73: /* EQUALS */
    case 74: /* CONST */
    case 75: /* TYPEDEF */
    case 76: /* ELLIPSIS */
    case 77: /* LBRACKET */
    case 78: /* RBRACKET */
    case 79: /* CHAR */
    case 80: /* SHORT */
    case 81: /* LONG */
    case 82: /* UNSIGNED */
    case 83: /* SIGNED */
    case 84: /* STATIC */
    case 85: /* FUNCTION */
    case 86: /* DOLLAR_NAME */
{
#line 37 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
free((yypminor->yy0));
#line 1092 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
      /* Default NON-TERMINAL Destructor */
    case 87: /* error */
    case 94: /* align_and_size */
    case 142: /* reference */
    case 143: /* indirection */
    case 144: /* pointers */
    case 145: /* file */
    case 146: /* blocks */
    case 147: /* block */
    case 148: /* optional_name */
    case 149: /* enum_name */
    case 150: /* struct_name */
    case 151: /* union_name */
    case 152: /* decl_var_array_size */
    case 153: /* decl_scalar_type */
    case 154: /* decl_scalar_type_short */
    case 155: /* decl_scalar_type_long */
    case 156: /* decl_scalar_type_long_long */
    case 157: /* callback_rval */
{
#line 38 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
(void)P;
#line 1117 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 88: /* decl_enum */
{
#line 60 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_enum_free(&(yypminor->yy63));
#line 1124 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 89: /* decl_enum_items */
    case 91: /* decl_struct_args_block */
    case 92: /* decl_struct_args */
    case 101: /* decl_typedef_body_fn_args */
    case 106: /* decl_vars */
    case 108: /* decl_args */
    case 109: /* struct_args */
    case 119: /* impl_args */
    case 121: /* impl_stmts */
    case 132: /* let_exps */
    case 135: /* set_exps */
    case 139: /* free_exps */
{
#line 62 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_plist_free((yypminor->yy163));
#line 1142 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 90: /* decl_enum_item */
{
#line 64 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_enum_item_free(&(yypminor->yy217));
#line 1149 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 93: /* decl_struct */
{
#line 70 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_struct_free(&(yypminor->yy275));
#line 1156 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 95: /* decl_union */
{
#line 73 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_union_free(&(yypminor->yy271));
#line 1163 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 96: /* const_type */
{
#line 75 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_const_type_free(&(yypminor->yy171));
#line 1170 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 97: /* constant */
{
#line 77 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_const_free(&(yypminor->yy154));
#line 1177 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 98: /* decl_typedef */
    case 99: /* decl_typedef_body_ex */
    case 100: /* decl_typedef_body */
    case 103: /* decl_func */
    case 107: /* decl_arg */
    case 110: /* struct_arg */
{
#line 79 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_arg_free(&(yypminor->yy184));
#line 1189 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 102: /* decl */
{
#line 87 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_free(&(yypminor->yy103));
#line 1196 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 104: /* decl_abi */
{
#line 91 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_abi_free(&(yypminor->yy218));
#line 1203 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 105: /* decl_var */
{
#line 93 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_var_free(&(yypminor->yy11));
#line 1210 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 111: /* decl_layout */
{
#line 105 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_layout_free(&(yypminor->yy141));
#line 1217 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 112: /* decl_type */
    case 113: /* const_decl_type */
{
#line 107 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_decl_type_free(&(yypminor->yy132));
#line 1225 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 114: /* impl */
{
#line 111 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_free(&(yypminor->yy97));
#line 1232 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 115: /* impl_func */
{
#line 113 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_func_free(&(yypminor->yy168));
#line 1239 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 116: /* impl_def_val */
{
#line 115 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_def_val_free(&(yypminor->yy93));
#line 1246 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 117: /* impl_var */
{
#line 117 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_var_free(&(yypminor->yy37));
#line 1253 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 118: /* impl_arg */
    case 120: /* impl_vararg */
{
#line 119 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_arg_free(&(yypminor->yy210));
#line 1261 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 122: /* impl_stmt */
{
#line 127 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_stmt_free(&(yypminor->yy78));
#line 1268 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 123: /* number */
{
#line 129 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_number_free(&(yypminor->yy188));
#line 1275 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 124: /* num_exp */
{
#line 131 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_num_exp_free(&(yypminor->yy259));
#line 1282 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 125: /* let_stmt */
{
#line 133 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_let_stmt_free(&(yypminor->yy311));
#line 1289 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 126: /* let_calloc */
{
#line 135 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_let_calloc_free(&(yypminor->yy9));
#line 1296 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 127: /* let_func */
{
#line 137 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_let_func_free(&(yypminor->yy27));
#line 1303 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 128: /* callback_arg_list */
    case 129: /* callback_args */
{
#line 139 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_plist_free((yypminor->yy43));
#line 1311 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 130: /* let_callback */
{
#line 143 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_let_callback_free(&(yypminor->yy220));
#line 1318 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 131: /* let_exp */
{
#line 145 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_let_exp_free(&(yypminor->yy20));
#line 1325 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 133: /* set_stmt */
{
#line 149 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_set_stmt_free(&(yypminor->yy98));
#line 1332 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 134: /* set_exp */
{
#line 151 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_set_exp_free(&(yypminor->yy147));
#line 1339 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 136: /* set_func */
{
#line 155 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_set_func_free(&(yypminor->yy26));
#line 1346 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 137: /* return_stmt */
{
#line 157 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_return_stmt_free(&(yypminor->yy90));
#line 1353 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 138: /* free_stmt */
{
#line 159 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_free_stmt_free(&(yypminor->yy192));
#line 1360 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 140: /* free_exp */
{
#line 163 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_free_exp_free(&(yypminor->yy94));
#line 1367 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
      break;
    case 141: /* impl_type */
{
#line 165 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
psi_impl_type_free(&(yypminor->yy138));
#line 1374 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
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
  { 147, 3 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 147, 1 },
  { 148, 0 },
  { 148, 1 },
  { 94, 0 },
  { 94, 7 },
  { 149, 2 },
  { 150, 2 },
  { 151, 2 },
  { 88, 4 },
  { 89, 1 },
  { 89, 3 },
  { 90, 3 },
  { 90, 1 },
  { 91, 3 },
  { 92, 1 },
  { 92, 1 },
  { 93, 4 },
  { 95, 4 },
  { 96, 1 },
  { 97, 6 },
  { 98, 3 },
  { 99, 4 },
  { 99, 4 },
  { 99, 2 },
  { 100, 1 },
  { 101, 3 },
  { 100, 2 },
  { 100, 1 },
  { 102, 6 },
  { 102, 8 },
  { 103, 1 },
  { 103, 2 },
  { 100, 7 },
  { 100, 8 },
  { 104, 1 },
  { 152, 0 },
  { 152, 3 },
  { 105, 2 },
  { 105, 3 },
  { 106, 1 },
  { 106, 3 },
  { 107, 2 },
  { 100, 7 },
  { 107, 3 },
  { 107, 4 },
  { 108, 0 },
  { 108, 1 },
  { 108, 1 },
  { 108, 3 },
  { 109, 1 },
  { 109, 2 },
  { 110, 2 },
  { 110, 3 },
  { 111, 0 },
  { 111, 7 },
  { 153, 1 },
  { 153, 2 },
  { 154, 0 },
  { 154, 1 },
  { 153, 1 },
  { 153, 2 },
  { 155, 0 },
  { 155, 1 },
  { 155, 2 },
  { 156, 0 },
  { 156, 1 },
  { 112, 2 },
  { 112, 2 },
  { 112, 1 },
  { 112, 1 },
  { 112, 1 },
  { 112, 2 },
  { 112, 2 },
  { 112, 2 },
  { 112, 1 },
  { 113, 1 },
  { 113, 2 },
  { 114, 4 },
  { 114, 5 },
  { 115, 7 },
  { 115, 8 },
  { 115, 13 },
  { 116, 1 },
  { 117, 2 },
  { 141, 1 },
  { 118, 2 },
  { 118, 4 },
  { 119, 1 },
  { 119, 3 },
  { 121, 1 },
  { 121, 2 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 122, 1 },
  { 123, 1 },
  { 123, 1 },
  { 124, 1 },
  { 124, 3 },
  { 124, 3 },
  { 124, 2 },
  { 131, 1 },
  { 131, 2 },
  { 131, 1 },
  { 131, 1 },
  { 131, 2 },
  { 131, 1 },
  { 131, 2 },
  { 131, 1 },
  { 131, 2 },
  { 131, 3 },
  { 125, 3 },
  { 125, 6 },
  { 130, 8 },
  { 126, 6 },
  { 127, 4 },
  { 127, 6 },
  { 132, 1 },
  { 132, 3 },
  { 128, 0 },
  { 128, 1 },
  { 129, 1 },
  { 129, 3 },
  { 157, 1 },
  { 157, 1 },
  { 136, 4 },
  { 136, 6 },
  { 136, 6 },
  { 134, 1 },
  { 134, 1 },
  { 135, 1 },
  { 135, 3 },
  { 134, 3 },
  { 133, 3 },
  { 137, 3 },
  { 138, 3 },
  { 139, 1 },
  { 139, 3 },
  { 140, 4 },
  { 142, 0 },
  { 142, 1 },
  { 143, 0 },
  { 143, 1 },
  { 144, 1 },
  { 144, 2 },
  { 145, 1 },
  { 146, 1 },
  { 146, 2 },
  { 147, 1 },
  { 147, 1 },
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
#line 174 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (P->file.ln) {
  P->error(PSI_DATA(P), yymsp[-2].minor.yy0, PSI_WARNING, "Extra 'lib %s' statement has no effect", yymsp[-1].minor.yy0->text);
 } else {
  P->file.ln = strndup(yymsp[-1].minor.yy0->text + 1, yymsp[-1].minor.yy0->size - 2);
 }
 free(yymsp[-1].minor.yy0);
 free(yymsp[-2].minor.yy0);
}
#line 1857 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
        break;
      case 1: /* block ::= decl */
#line 183 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->decls) {
  P->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
 }
 P->decls = psi_plist_add(P->decls, &yymsp[0].minor.yy103);
}
#line 1868 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 2: /* block ::= impl */
#line 189 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->impls) {
  P->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
 }
 P->impls = psi_plist_add(P->impls, &yymsp[0].minor.yy97);
}
#line 1878 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 3: /* block ::= decl_typedef */
#line 195 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->types) {
  P->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
 }
 P->types = psi_plist_add(P->types, &yymsp[0].minor.yy184);
 switch (yymsp[0].minor.yy184->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[0].minor.yy184->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy184->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[0].minor.yy184->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy184->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[0].minor.yy184->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy184->type->real.enm);
  }
  break;
 }
}
#line 1914 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 4: /* block ::= constant */
#line 227 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->consts) {
  P->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
 }
 P->consts = psi_plist_add(P->consts, &yymsp[0].minor.yy154);
}
#line 1924 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 5: /* block ::= decl_struct */
#line 233 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->structs) {
  P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
 }
 P->structs = psi_plist_add(P->structs, &yymsp[0].minor.yy275);
}
#line 1934 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 6: /* block ::= decl_union */
#line 239 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->unions) {
  P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
 }
 P->unions = psi_plist_add(P->unions, &yymsp[0].minor.yy271);
}
#line 1944 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 7: /* block ::= decl_enum */
#line 245 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (!P->enums) {
  P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
 }
 P->enums = psi_plist_add(P->enums, &yymsp[0].minor.yy63);
}
#line 1954 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 8: /* optional_name ::= */
      case 42: /* decl_var_array_size ::= */ yytestcase(yyruleno==42);
      case 64: /* decl_scalar_type_short ::= */ yytestcase(yyruleno==64);
      case 68: /* decl_scalar_type_long ::= */ yytestcase(yyruleno==68);
      case 71: /* decl_scalar_type_long_long ::= */ yytestcase(yyruleno==71);
#line 251 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy0 = NULL;
}
#line 1965 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 9: /* optional_name ::= NAME */
      case 62: /* decl_scalar_type ::= CHAR */ yytestcase(yyruleno==62);
      case 65: /* decl_scalar_type_short ::= INT */ yytestcase(yyruleno==65);
      case 66: /* decl_scalar_type ::= INT */ yytestcase(yyruleno==66);
      case 69: /* decl_scalar_type_long ::= DOUBLE */ yytestcase(yyruleno==69);
      case 72: /* decl_scalar_type_long_long ::= INT */ yytestcase(yyruleno==72);
      case 130: /* callback_rval ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT */ yytestcase(yyruleno==130);
      case 131: /* callback_rval ::= VOID */ yytestcase(yyruleno==131);
#line 254 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy0 = yymsp[0].minor.yy0;
}
#line 1979 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy0 = yylhsminor.yy0;
        break;
      case 10: /* align_and_size ::= */
#line 257 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy91.pos = 0;
 yymsp[1].minor.yy91.len = 0;
}
#line 1988 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 11: /* align_and_size ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,64,&yymsp[-6].minor);
#line 261 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-6].minor.yy91.pos = atol(yymsp[-3].minor.yy0->text);
 yymsp[-6].minor.yy91.len = atol(yymsp[-1].minor.yy0->text);
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 1999 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,64,&yymsp[-5].minor);
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
}
        break;
      case 12: /* enum_name ::= ENUM optional_name */
      case 13: /* struct_name ::= STRUCT optional_name */ yytestcase(yyruleno==13);
      case 14: /* union_name ::= UNION optional_name */ yytestcase(yyruleno==14);
#line 267 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
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
#line 2020 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 15: /* decl_enum ::= enum_name LBRACE decl_enum_items RBRACE */
#line 297 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy63 = psi_decl_enum_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy163);
 yylhsminor.yy63->token = yymsp[-3].minor.yy0;
}
#line 2029 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[0].minor);
  yymsp[-3].minor.yy63 = yylhsminor.yy63;
        break;
      case 16: /* decl_enum_items ::= decl_enum_item */
#line 301 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_enum_item_free),
   &yymsp[0].minor.yy217);
}
#line 2040 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 17: /* decl_enum_items ::= decl_enum_items COMMA decl_enum_item */
#line 305 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy217);
}
#line 2048 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 18: /* decl_enum_item ::= NAME EQUALS num_exp */
#line 308 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy217 = psi_decl_enum_item_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy259);
 yylhsminor.yy217->token = yymsp[-2].minor.yy0;
}
#line 2058 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-1].minor);
  yymsp[-2].minor.yy217 = yylhsminor.yy217;
        break;
      case 19: /* decl_enum_item ::= NAME */
#line 312 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy217 = psi_decl_enum_item_init(yymsp[0].minor.yy0->text, NULL);
 yylhsminor.yy217->token = yymsp[0].minor.yy0;
}
#line 2068 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy217 = yylhsminor.yy217;
        break;
      case 20: /* decl_struct_args_block ::= LBRACE struct_args RBRACE */
{  yy_destructor(yypParser,71,&yymsp[-2].minor);
#line 316 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-2].minor.yy163 = yymsp[-1].minor.yy163;
}
#line 2077 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,72,&yymsp[0].minor);
}
        break;
      case 21: /* decl_struct_args ::= decl_struct_args_block */
#line 319 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = yymsp[0].minor.yy163;
}
#line 2086 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 22: /* decl_struct_args ::= EOS */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 322 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[0].minor.yy163 = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
}
#line 2095 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 23: /* decl_struct ::= STRUCT NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,69,&yymsp[-3].minor);
#line 325 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-3].minor.yy275 = psi_decl_struct_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy163);
 yymsp[-3].minor.yy275->align = yymsp[-1].minor.yy91.pos;
 yymsp[-3].minor.yy275->size = yymsp[-1].minor.yy91.len;
 yymsp[-3].minor.yy275->token = yymsp[-2].minor.yy0;
}
#line 2107 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 24: /* decl_union ::= UNION NAME align_and_size decl_struct_args */
{  yy_destructor(yypParser,70,&yymsp[-3].minor);
#line 331 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-3].minor.yy271 = psi_decl_union_init(yymsp[-2].minor.yy0->text, yymsp[0].minor.yy163);
 yymsp[-3].minor.yy271->align = yymsp[-1].minor.yy91.pos;
 yymsp[-3].minor.yy271->size = yymsp[-1].minor.yy91.len;
 yymsp[-3].minor.yy271->token = yymsp[-2].minor.yy0;
}
#line 2119 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 25: /* const_type ::= BOOL|INT|FLOAT|STRING */
#line 337 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy171 = psi_const_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2128 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy171 = yylhsminor.yy171;
        break;
      case 26: /* constant ::= CONST const_type NSNAME EQUALS impl_def_val EOS */
{  yy_destructor(yypParser,74,&yymsp[-5].minor);
#line 341 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-5].minor.yy154 = psi_const_init(yymsp[-4].minor.yy171, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy93);
 yymsp[-5].minor.yy154->token = yymsp[-3].minor.yy0;
}
#line 2138 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-2].minor);
  yy_destructor(yypParser,63,&yymsp[0].minor);
}
        break;
      case 27: /* decl_typedef ::= TYPEDEF decl_typedef_body EOS */
#line 345 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = yymsp[-1].minor.yy184;
 yylhsminor.yy184->token = yymsp[-2].minor.yy0;
}
#line 2149 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 28: /* decl_typedef_body_ex ::= struct_name align_and_size decl_struct_args_block decl_var */
#line 349 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(psi_decl_type_init(PSI_T_STRUCT, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy11);
 yylhsminor.yy184->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy184->type->real.strct = psi_decl_struct_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy163);
 yylhsminor.yy184->type->real.strct->token = yymsp[-3].minor.yy0;
 yylhsminor.yy184->type->real.strct->align = yymsp[-2].minor.yy91.pos;
 yylhsminor.yy184->type->real.strct->size = yymsp[-2].minor.yy91.len;
}
#line 2163 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-3].minor.yy184 = yylhsminor.yy184;
        break;
      case 29: /* decl_typedef_body_ex ::= union_name align_and_size decl_struct_args_block decl_var */
#line 357 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(psi_decl_type_init(PSI_T_UNION, yymsp[-3].minor.yy0->text), yymsp[0].minor.yy11);
 yylhsminor.yy184->type->token = psi_token_copy(yymsp[-3].minor.yy0);
 yylhsminor.yy184->type->real.unn = psi_decl_union_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy163);
 yylhsminor.yy184->type->real.unn->token = yymsp[-3].minor.yy0;
 yylhsminor.yy184->type->real.unn->align = yymsp[-2].minor.yy91.pos;
 yylhsminor.yy184->type->real.unn->size = yymsp[-2].minor.yy91.len;
}
#line 2176 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-3].minor.yy184 = yylhsminor.yy184;
        break;
      case 30: /* decl_typedef_body_ex ::= decl_enum NAME */
#line 365 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(psi_decl_type_init(PSI_T_ENUM, yymsp[-1].minor.yy63->name), psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0));
 yylhsminor.yy184->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy184->type->token = psi_token_copy(yymsp[-1].minor.yy63->token);
 yylhsminor.yy184->type->real.enm = yymsp[-1].minor.yy63;
}
#line 2187 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy184 = yylhsminor.yy184;
        break;
      case 31: /* decl_typedef_body ::= decl_typedef_body_ex */
      case 34: /* decl_typedef_body ::= decl_arg */ yytestcase(yyruleno==34);
      case 37: /* decl_func ::= decl_arg */ yytestcase(yyruleno==37);
#line 371 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = yymsp[0].minor.yy184;
}
#line 2197 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy184 = yylhsminor.yy184;
        break;
      case 32: /* decl_typedef_body_fn_args ::= LPAREN decl_args RPAREN */
{  yy_destructor(yypParser,65,&yymsp[-2].minor);
#line 374 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-2].minor.yy163 = yymsp[-1].minor.yy163;
}
#line 2206 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,67,&yymsp[0].minor);
}
        break;
      case 33: /* decl_typedef_body ::= decl_func decl_typedef_body_fn_args */
#line 377 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(psi_decl_type_init(PSI_T_FUNCTION, yymsp[-1].minor.yy184->var->name), psi_decl_var_copy(yymsp[-1].minor.yy184->var));
 yylhsminor.yy184->type->token = psi_token_copy(yymsp[-1].minor.yy184->token);
 yylhsminor.yy184->type->real.func = psi_decl_init(psi_decl_abi_init("default"), yymsp[-1].minor.yy184, yymsp[0].minor.yy163);
}
#line 2217 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy184 = yylhsminor.yy184;
        break;
      case 35: /* decl ::= decl_abi decl_func LPAREN decl_args RPAREN EOS */
#line 385 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy103 = psi_decl_init(yymsp[-5].minor.yy218, yymsp[-4].minor.yy184, yymsp[-2].minor.yy163);
}
#line 2225 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-3].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-5].minor.yy103 = yylhsminor.yy103;
        break;
      case 36: /* decl ::= decl_abi decl_func LPAREN decl_args COMMA ELLIPSIS RPAREN EOS */
#line 388 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy103 = psi_decl_init(yymsp[-7].minor.yy218, yymsp[-6].minor.yy184, yymsp[-4].minor.yy163);
 yylhsminor.yy103->varargs = 1;
}
#line 2237 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-5].minor);
  yy_destructor(yypParser,66,&yymsp[-3].minor);
  yy_destructor(yypParser,76,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-7].minor.yy103 = yylhsminor.yy103;
        break;
      case 38: /* decl_func ::= VOID NAME */
#line 395 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[-1].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, 0, 0)
 );
 yylhsminor.yy184->type->token = yymsp[-1].minor.yy0;
 yylhsminor.yy184->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy184->token = yymsp[0].minor.yy0;
}
#line 2256 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy184 = yylhsminor.yy184;
        break;
      case 39: /* decl_typedef_body ::= VOID indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 404 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy202, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy184->var->pointer_level = yymsp[-3].minor.yy202;
 yylhsminor.yy184->type->token = psi_token_copy(func_->token);
 yylhsminor.yy184->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy163);
}
#line 2277 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
  yymsp[-6].minor.yy184 = yylhsminor.yy184;
        break;
      case 40: /* decl_typedef_body ::= CONST VOID pointers LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
{  yy_destructor(yypParser,74,&yymsp[-7].minor);
#line 420 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text),
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy202, 0)
 );
 func_->type->token = yymsp[-6].minor.yy0;
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yymsp[-7].minor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yymsp[-7].minor.yy184->var->pointer_level = yymsp[-3].minor.yy202;
 yymsp[-7].minor.yy184->type->token = psi_token_copy(func_->token);
 yymsp[-7].minor.yy184->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy163);
}
#line 2301 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
}
        break;
      case 41: /* decl_abi ::= NAME */
#line 436 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy218 = psi_decl_abi_init(yymsp[0].minor.yy0->text);
 yylhsminor.yy218->token = yymsp[0].minor.yy0;
}
#line 2312 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy218 = yylhsminor.yy218;
        break;
      case 43: /* decl_var_array_size ::= LBRACKET NUMBER RBRACKET */
{  yy_destructor(yypParser,77,&yymsp[-2].minor);
#line 443 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-2].minor.yy0 = yymsp[-1].minor.yy0;
}
#line 2321 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,78,&yymsp[0].minor);
}
        break;
      case 44: /* decl_var ::= NAME decl_var_array_size */
#line 446 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy11 = psi_decl_var_init(yymsp[-1].minor.yy0->text, 0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy11->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2334 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy11 = yylhsminor.yy11;
        break;
      case 45: /* decl_var ::= pointers NAME decl_var_array_size */
#line 453 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy11 = psi_decl_var_init(yymsp[-1].minor.yy0->text, yymsp[-2].minor.yy202+!!yymsp[0].minor.yy0, yymsp[0].minor.yy0?atol(yymsp[0].minor.yy0->text):0);
 yylhsminor.yy11->token = yymsp[-1].minor.yy0;
 if (yymsp[0].minor.yy0) {
  free(yymsp[0].minor.yy0);
 }
}
#line 2346 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-2].minor.yy11 = yylhsminor.yy11;
        break;
      case 46: /* decl_vars ::= decl_var */
#line 460 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_var_free),
   &yymsp[0].minor.yy11);
}
#line 2355 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 47: /* decl_vars ::= decl_vars COMMA decl_var */
#line 464 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy11);
}
#line 2363 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 48: /* decl_arg ::= const_decl_type decl_var */
#line 467 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(yymsp[-1].minor.yy132, yymsp[0].minor.yy11);
}
#line 2372 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy184 = yylhsminor.yy184;
        break;
      case 49: /* decl_typedef_body ::= const_decl_type indirection LPAREN indirection NAME RPAREN decl_typedef_body_fn_args */
#line 470 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 struct psi_decl_arg *func_ = psi_decl_arg_init(
  yymsp[-6].minor.yy132,
  psi_decl_var_init(yymsp[-2].minor.yy0->text, yymsp[-5].minor.yy202, 0)
 );
 func_->var->token = yymsp[-2].minor.yy0;
 func_->token = yymsp[-2].minor.yy0;
 yylhsminor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(PSI_T_FUNCTION, func_->var->name),
  psi_decl_var_copy(func_->var)
 );
 yylhsminor.yy184->var->pointer_level = yymsp[-3].minor.yy202;
 yylhsminor.yy184->type->token = psi_token_copy(func_->token);
 yylhsminor.yy184->type->real.func = psi_decl_init(psi_decl_abi_init("default"), func_, yymsp[0].minor.yy163);
}
#line 2392 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
  yymsp[-6].minor.yy184 = yylhsminor.yy184;
        break;
      case 50: /* decl_arg ::= VOID pointers NAME */
#line 485 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy202, 0)
 );
 yylhsminor.yy184->type->token = yymsp[-2].minor.yy0;
 yylhsminor.yy184->var->token = yymsp[0].minor.yy0;
 yylhsminor.yy184->token = yymsp[0].minor.yy0;
}
#line 2408 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 51: /* decl_arg ::= CONST VOID pointers NAME */
{  yy_destructor(yypParser,74,&yymsp[-3].minor);
#line 494 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-3].minor.yy184 = psi_decl_arg_init(
  psi_decl_type_init(yymsp[-2].minor.yy0->type, yymsp[-2].minor.yy0->text),
  psi_decl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy202, 0)
 );
 yymsp[-3].minor.yy184->type->token = yymsp[-2].minor.yy0;
 yymsp[-3].minor.yy184->var->token = yymsp[0].minor.yy0;
 yymsp[-3].minor.yy184->token = yymsp[0].minor.yy0;
}
#line 2423 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 52: /* decl_args ::= */
#line 503 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy163 = NULL;
}
#line 2431 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 53: /* decl_args ::= VOID */
{  yy_destructor(yypParser,49,&yymsp[0].minor);
#line 506 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[0].minor.yy163 = NULL;
}
#line 2439 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 54: /* decl_args ::= decl_arg */
      case 56: /* struct_args ::= struct_arg */ yytestcase(yyruleno==56);
#line 509 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_decl_arg_free),
   &yymsp[0].minor.yy184);
}
#line 2449 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 55: /* decl_args ::= decl_args COMMA decl_arg */
#line 513 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy184);
}
#line 2457 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 57: /* struct_args ::= struct_args struct_arg */
#line 520 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-1].minor.yy163, &yymsp[0].minor.yy184);
}
#line 2466 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy163 = yylhsminor.yy163;
        break;
      case 58: /* struct_arg ::= decl_typedef_body_ex EOS */
#line 523 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy184 = yymsp[-1].minor.yy184;
 switch (yymsp[-1].minor.yy184->type->type) {
 case PSI_T_STRUCT:
  if (yymsp[-1].minor.yy184->type->real.strct) {
   if (!P->structs) {
    P->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
   }
   P->structs = psi_plist_add(P->structs, &yymsp[-1].minor.yy184->type->real.strct);
  }
  break;
 case PSI_T_UNION:
  if (yymsp[-1].minor.yy184->type->real.unn) {
   if (!P->unions) {
    P->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
   }
   P->unions = psi_plist_add(P->unions, &yymsp[-1].minor.yy184->type->real.unn);
  }
  break;
 case PSI_T_ENUM:
  if (yymsp[-1].minor.yy184->type->real.enm) {
   if (!P->enums) {
    P->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
   }
   P->enums = psi_plist_add(P->enums, &yymsp[-1].minor.yy184->type->real.enm);
  }
  break;
 }
}
#line 2500 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-1].minor.yy184 = yylhsminor.yy184;
        break;
      case 59: /* struct_arg ::= decl_arg decl_layout EOS */
#line 552 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-2].minor.yy184->layout = yymsp[-1].minor.yy141;
 yylhsminor.yy184 = yymsp[-2].minor.yy184;
}
#line 2510 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy184 = yylhsminor.yy184;
        break;
      case 60: /* decl_layout ::= */
#line 556 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy141 = NULL;
}
#line 2519 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 61: /* decl_layout ::= COLON COLON LPAREN NUMBER COMMA NUMBER RPAREN */
{  yy_destructor(yypParser,64,&yymsp[-6].minor);
#line 559 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-6].minor.yy141 = psi_layout_init(atol(yymsp[-3].minor.yy0->text), atol(yymsp[-1].minor.yy0->text));
 free(yymsp[-3].minor.yy0);
 free(yymsp[-1].minor.yy0);
}
#line 2529 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,64,&yymsp[-5].minor);
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
}
        break;
      case 63: /* decl_scalar_type ::= SHORT decl_scalar_type_short */
      case 67: /* decl_scalar_type ::= LONG decl_scalar_type_long */ yytestcase(yyruleno==67);
      case 70: /* decl_scalar_type_long ::= LONG decl_scalar_type_long_long */ yytestcase(yyruleno==70);
#line 567 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 if (yymsp[0].minor.yy0) {
  yylhsminor.yy0 = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
  free(yymsp[-1].minor.yy0);
  free(yymsp[0].minor.yy0);
 } else {
  yylhsminor.yy0 = yymsp[-1].minor.yy0;
 }
}
#line 2549 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy0 = yylhsminor.yy0;
        break;
      case 73: /* decl_type ::= UNSIGNED decl_scalar_type */
      case 74: /* decl_type ::= SIGNED decl_scalar_type */ yytestcase(yyruleno==74);
#line 615 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 struct psi_token *T = psi_token_cat(2, yymsp[-1].minor.yy0, yymsp[0].minor.yy0);
 yylhsminor.yy132 = psi_decl_type_init(T->type, T->text);
 yylhsminor.yy132->token = T;
 free(yymsp[-1].minor.yy0);
 free(yymsp[0].minor.yy0);
}
#line 2562 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy132 = yylhsminor.yy132;
        break;
      case 75: /* decl_type ::= UNSIGNED */
      case 76: /* decl_type ::= SIGNED */ yytestcase(yyruleno==76);
#line 629 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy132 = psi_decl_type_init(PSI_T_NAME, yymsp[0].minor.yy0->text);
 yylhsminor.yy132->token = yymsp[0].minor.yy0;
}
#line 2572 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy132 = yylhsminor.yy132;
        break;
      case 77: /* decl_type ::= decl_scalar_type */
      case 81: /* decl_type ::= FLOAT|DOUBLE|INT8|UINT8|INT16|UINT16|INT32|UINT32|INT64|UINT64|NAME */ yytestcase(yyruleno==81);
#line 637 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy132 = psi_decl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy132->token = yymsp[0].minor.yy0;
}
#line 2582 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy132 = yylhsminor.yy132;
        break;
      case 78: /* decl_type ::= STRUCT NAME */
      case 79: /* decl_type ::= UNION NAME */ yytestcase(yyruleno==79);
      case 80: /* decl_type ::= ENUM NAME */ yytestcase(yyruleno==80);
#line 641 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy132 = psi_decl_type_init(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy132->token = yymsp[0].minor.yy0;
 free(yymsp[-1].minor.yy0);
}
#line 2594 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy132 = yylhsminor.yy132;
        break;
      case 82: /* const_decl_type ::= decl_type */
#line 660 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy132 = yymsp[0].minor.yy132;
}
#line 2602 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy132 = yylhsminor.yy132;
        break;
      case 83: /* const_decl_type ::= CONST decl_type */
{  yy_destructor(yypParser,74,&yymsp[-1].minor);
#line 663 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-1].minor.yy132 = yymsp[0].minor.yy132;
}
#line 2611 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 84: /* impl ::= impl_func LBRACE impl_stmts RBRACE */
#line 666 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy97 = psi_impl_init(yymsp[-3].minor.yy168, yymsp[-1].minor.yy163);
}
#line 2619 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[0].minor);
  yymsp[-3].minor.yy97 = yylhsminor.yy97;
        break;
      case 85: /* impl ::= STATIC impl_func LBRACE impl_stmts RBRACE */
{  yy_destructor(yypParser,84,&yymsp[-4].minor);
#line 669 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-3].minor.yy168->static_memory = 1;
 yymsp[-4].minor.yy97 = psi_impl_init(yymsp[-3].minor.yy168, yymsp[-1].minor.yy163);
}
#line 2631 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,71,&yymsp[-2].minor);
  yy_destructor(yypParser,72,&yymsp[0].minor);
}
        break;
      case 86: /* impl_func ::= FUNCTION reference NSNAME LPAREN RPAREN COLON impl_type */
{  yy_destructor(yypParser,85,&yymsp[-6].minor);
#line 673 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-6].minor.yy168 = psi_impl_func_init(yymsp[-4].minor.yy0->text, NULL, yymsp[0].minor.yy138);
 yymsp[-6].minor.yy168->token = yymsp[-4].minor.yy0;
 yymsp[-6].minor.yy168->return_reference = yymsp[-5].minor.yy121;
}
#line 2644 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-3].minor);
  yy_destructor(yypParser,67,&yymsp[-2].minor);
  yy_destructor(yypParser,64,&yymsp[-1].minor);
}
        break;
      case 87: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args RPAREN COLON impl_type */
{  yy_destructor(yypParser,85,&yymsp[-7].minor);
#line 678 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-7].minor.yy168 = psi_impl_func_init(yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy163, yymsp[0].minor.yy138);
 yymsp[-7].minor.yy168->token = yymsp[-5].minor.yy0;
 yymsp[-7].minor.yy168->return_reference = yymsp[-6].minor.yy121;
}
#line 2658 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,67,&yymsp[-2].minor);
  yy_destructor(yypParser,64,&yymsp[-1].minor);
}
        break;
      case 88: /* impl_func ::= FUNCTION reference NSNAME LPAREN impl_args COMMA impl_type reference ELLIPSIS DOLLAR_NAME RPAREN COLON impl_type */
{  yy_destructor(yypParser,85,&yymsp[-12].minor);
#line 683 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-12].minor.yy168 = psi_impl_func_init(yymsp[-10].minor.yy0->text, yymsp[-8].minor.yy163, yymsp[0].minor.yy138);
 yymsp[-12].minor.yy168->token = yymsp[-10].minor.yy0;
 yymsp[-12].minor.yy168->return_reference = yymsp[-11].minor.yy121;
 yymsp[-12].minor.yy168->vararg = psi_impl_arg_init(yymsp[-6].minor.yy138, psi_impl_var_init(yymsp[-3].minor.yy0->text, yymsp[-5].minor.yy121), NULL);
 free(yymsp[-3].minor.yy0);
}
#line 2674 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-9].minor);
  yy_destructor(yypParser,66,&yymsp[-7].minor);
  yy_destructor(yypParser,76,&yymsp[-4].minor);
  yy_destructor(yypParser,67,&yymsp[-2].minor);
  yy_destructor(yypParser,64,&yymsp[-1].minor);
}
        break;
      case 89: /* impl_def_val ::= NULL|NUMBER|TRUE|FALSE|QUOTED_STRING */
#line 690 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy93 = psi_impl_def_val_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy93->token = yymsp[0].minor.yy0;
}
#line 2688 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy93 = yylhsminor.yy93;
        break;
      case 90: /* impl_var ::= reference DOLLAR_NAME */
#line 694 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy37 = psi_impl_var_init(yymsp[0].minor.yy0->text, yymsp[-1].minor.yy121);
 yylhsminor.yy37->token = yymsp[0].minor.yy0;
}
#line 2697 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy37 = yylhsminor.yy37;
        break;
      case 91: /* impl_type ::= VOID|MIXED|BOOL|INT|FLOAT|STRING|ARRAY|OBJECT|CALLABLE */
#line 698 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy138 = psi_impl_type_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 free(yymsp[0].minor.yy0);
}
#line 2706 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy138 = yylhsminor.yy138;
        break;
      case 92: /* impl_arg ::= impl_type impl_var */
#line 702 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy210 = psi_impl_arg_init(yymsp[-1].minor.yy138, yymsp[0].minor.yy37, NULL);
}
#line 2714 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy210 = yylhsminor.yy210;
        break;
      case 93: /* impl_arg ::= impl_type impl_var EQUALS impl_def_val */
#line 705 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy210 = psi_impl_arg_init(yymsp[-3].minor.yy138, yymsp[-2].minor.yy37, yymsp[0].minor.yy93);
}
#line 2722 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-1].minor);
  yymsp[-3].minor.yy210 = yylhsminor.yy210;
        break;
      case 94: /* impl_args ::= impl_arg */
#line 708 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_arg_free),
   &yymsp[0].minor.yy210);
}
#line 2732 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 95: /* impl_args ::= impl_args COMMA impl_arg */
#line 712 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy210);
}
#line 2740 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 96: /* impl_stmts ::= impl_stmt */
#line 715 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_impl_stmt_free),
   &yymsp[0].minor.yy78);
}
#line 2750 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 97: /* impl_stmts ::= impl_stmts impl_stmt */
#line 719 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-1].minor.yy163, &yymsp[0].minor.yy78);
}
#line 2758 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy163 = yylhsminor.yy163;
        break;
      case 98: /* impl_stmt ::= return_stmt */
#line 722 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy78 = (struct psi_token**) yymsp[0].minor.yy90;
}
#line 2766 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy78 = yylhsminor.yy78;
        break;
      case 99: /* impl_stmt ::= let_stmt */
#line 725 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy78 = (struct psi_token**) yymsp[0].minor.yy311;
}
#line 2774 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy78 = yylhsminor.yy78;
        break;
      case 100: /* impl_stmt ::= set_stmt */
#line 728 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy78 = (struct psi_token**) yymsp[0].minor.yy98;
}
#line 2782 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy78 = yylhsminor.yy78;
        break;
      case 101: /* impl_stmt ::= free_stmt */
#line 731 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy78 = (struct psi_token**) yymsp[0].minor.yy192;
}
#line 2790 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy78 = yylhsminor.yy78;
        break;
      case 102: /* number ::= NUMBER|NSNAME */
#line 734 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy188 = psi_number_init(yymsp[0].minor.yy0->type, yymsp[0].minor.yy0->text);
 yylhsminor.yy188->token = yymsp[0].minor.yy0;
}
#line 2799 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy188 = yylhsminor.yy188;
        break;
      case 103: /* number ::= decl_var */
#line 738 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy188 = psi_number_init(PSI_T_NAME, yymsp[0].minor.yy11);
 yylhsminor.yy188->token = psi_token_copy(yymsp[0].minor.yy11->token);
}
#line 2808 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy188 = yylhsminor.yy188;
        break;
      case 104: /* num_exp ::= number */
#line 742 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy259 = psi_num_exp_init_num(yymsp[0].minor.yy188);
 yylhsminor.yy259->token = psi_token_copy(yymsp[0].minor.yy188->token);
}
#line 2817 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy259 = yylhsminor.yy259;
        break;
      case 105: /* num_exp ::= LPAREN num_exp RPAREN */
#line 746 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy259 = psi_num_exp_init_unary(PSI_T_LPAREN, yymsp[-1].minor.yy259);
 yylhsminor.yy259->token = yymsp[-2].minor.yy0;
}
#line 2826 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-2].minor.yy259 = yylhsminor.yy259;
        break;
      case 106: /* num_exp ::= num_exp PIPE|CARET|AMPERSAND|LSHIFT|RSHIFT|PLUS|MINUS|ASTERISK|SLASH|MODULO num_exp */
#line 750 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy259 = psi_num_exp_init_binary(yymsp[-1].minor.yy0->type, yymsp[-2].minor.yy259, yymsp[0].minor.yy259);
 yylhsminor.yy259->token = yymsp[-1].minor.yy0;
}
#line 2836 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-2].minor.yy259 = yylhsminor.yy259;
        break;
      case 107: /* num_exp ::= TILDE|NOT|PLUS|MINUS num_exp */
#line 754 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy259 = psi_num_exp_init_unary(yymsp[-1].minor.yy0->type, yymsp[0].minor.yy259);
 yylhsminor.yy259->token = yymsp[-1].minor.yy0;
}
#line 2845 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[-1].minor.yy259 = yylhsminor.yy259;
        break;
      case 108: /* let_exp ::= NULL */
{  yy_destructor(yypParser,15,&yymsp[0].minor);
#line 758 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[0].minor.yy20 = psi_let_exp_init(PSI_LET_NULL, NULL);
}
#line 2854 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 109: /* let_exp ::= AMPERSAND NULL */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 761 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-1].minor.yy20 = psi_let_exp_init(PSI_LET_NULL, NULL);
 yymsp[-1].minor.yy20->is_reference = 1;
}
#line 2864 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,15,&yymsp[0].minor);
}
        break;
      case 110: /* let_exp ::= let_callback */
#line 765 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy20 = psi_let_exp_init(PSI_LET_CALLBACK, yymsp[0].minor.yy220);
}
#line 2873 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy20 = yylhsminor.yy20;
        break;
      case 111: /* let_exp ::= let_calloc */
#line 768 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy20 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy9);
}
#line 2881 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy20 = yylhsminor.yy20;
        break;
      case 112: /* let_exp ::= AMPERSAND let_calloc */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 771 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-1].minor.yy20 = psi_let_exp_init(PSI_LET_CALLOC, yymsp[0].minor.yy9);
 yymsp[-1].minor.yy20->is_reference = 1;
}
#line 2891 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 113: /* let_exp ::= let_func */
#line 775 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy20 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy27);
}
#line 2899 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy20 = yylhsminor.yy20;
        break;
      case 114: /* let_exp ::= AMPERSAND let_func */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 778 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-1].minor.yy20 = psi_let_exp_init_ex(NULL, PSI_LET_FUNC, yymsp[0].minor.yy27);
 yymsp[-1].minor.yy20->is_reference = 1;
}
#line 2909 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 115: /* let_exp ::= num_exp */
#line 782 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy20 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy259);
}
#line 2917 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy20 = yylhsminor.yy20;
        break;
      case 116: /* let_exp ::= AMPERSAND num_exp */
{  yy_destructor(yypParser,23,&yymsp[-1].minor);
#line 785 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[-1].minor.yy20 = psi_let_exp_init_ex(NULL, PSI_LET_NUMEXP, yymsp[0].minor.yy259);
 yymsp[-1].minor.yy20->is_reference = 1;
}
#line 2927 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 117: /* let_exp ::= decl_var EQUALS let_exp */
#line 789 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy20 = yymsp[0].minor.yy20;
 yylhsminor.yy20->var = yymsp[-2].minor.yy11;
}
#line 2936 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-1].minor);
  yymsp[-2].minor.yy20 = yylhsminor.yy20;
        break;
      case 118: /* let_stmt ::= LET let_exp EOS */
#line 793 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy311 = psi_let_stmt_init(yymsp[-1].minor.yy20);
 yylhsminor.yy311->token = yymsp[-2].minor.yy0;
}
#line 2946 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy311 = yylhsminor.yy311;
        break;
      case 119: /* let_stmt ::= TEMP decl_var EQUALS reference decl_var EOS */
#line 797 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy311 = psi_let_stmt_init(psi_let_exp_init_ex(yymsp[-4].minor.yy11, PSI_LET_TMP, yymsp[-1].minor.yy11));
 yylhsminor.yy311->token = yymsp[-5].minor.yy0;
 yylhsminor.yy311->exp->is_reference = yymsp[-2].minor.yy121 ? 1 : 0;
}
#line 2957 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-3].minor);
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-5].minor.yy311 = yylhsminor.yy311;
        break;
      case 120: /* let_callback ::= CALLBACK callback_rval LPAREN impl_var LPAREN callback_arg_list RPAREN RPAREN */
#line 802 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy220 = psi_let_callback_init(psi_let_func_init(yymsp[-6].minor.yy0->type, yymsp[-6].minor.yy0->text, yymsp[-4].minor.yy37), yymsp[-2].minor.yy43);
 yylhsminor.yy220->token = yymsp[-7].minor.yy0;
 free(yymsp[-6].minor.yy0);
}
#line 2969 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-5].minor);
  yy_destructor(yypParser,65,&yymsp[-3].minor);
  yy_destructor(yypParser,67,&yymsp[-1].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-7].minor.yy220 = yylhsminor.yy220;
        break;
      case 121: /* let_calloc ::= CALLOC LPAREN num_exp COMMA num_exp RPAREN */
#line 807 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy9 = psi_let_calloc_init(yymsp[-3].minor.yy259, yymsp[-1].minor.yy259);
 yylhsminor.yy9->token = yymsp[-5].minor.yy0;
}
#line 2982 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-5].minor.yy9 = yylhsminor.yy9;
        break;
      case 122: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var RPAREN */
#line 811 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy27 = psi_let_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy37);
 yylhsminor.yy27->token = yymsp[-3].minor.yy0;
}
#line 2994 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-3].minor.yy27 = yylhsminor.yy27;
        break;
      case 123: /* let_func ::= ZVAL|OBJVAL|ARRVAL|PATHVAL|STRLEN|STRVAL|FLOATVAL|INTVAL|BOOLVAL|COUNT LPAREN impl_var COMMA let_exps RPAREN */
#line 815 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy27 = psi_let_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy37);
 yylhsminor.yy27->token = yymsp[-5].minor.yy0;
 yylhsminor.yy27->inner = yymsp[-1].minor.yy163;
}
#line 3006 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-5].minor.yy27 = yylhsminor.yy27;
        break;
      case 124: /* let_exps ::= let_exp */
#line 820 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_let_exp_free),
   &yymsp[0].minor.yy20);
}
#line 3018 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 125: /* let_exps ::= let_exps COMMA let_exp */
#line 824 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy20);
}
#line 3026 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 126: /* callback_arg_list ::= */
#line 827 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy43 = NULL;
}
#line 3035 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 127: /* callback_arg_list ::= callback_args */
#line 830 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy43 = yymsp[0].minor.yy43;
}
#line 3042 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy43 = yylhsminor.yy43;
        break;
      case 128: /* callback_args ::= set_exp */
#line 833 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy43 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy147);
}
#line 3051 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy43 = yylhsminor.yy43;
        break;
      case 129: /* callback_args ::= callback_args COMMA set_exp */
#line 837 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy43 = psi_plist_add(yymsp[-2].minor.yy43, &yymsp[0].minor.yy147);
}
#line 3059 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy43 = yylhsminor.yy43;
        break;
      case 132: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var RPAREN */
#line 846 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy26 = psi_set_func_init(yymsp[-3].minor.yy0->type, yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy11);
 yylhsminor.yy26->token = yymsp[-3].minor.yy0;
}
#line 3069 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-3].minor.yy26 = yylhsminor.yy26;
        break;
      case 133: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA set_exps RPAREN */
#line 850 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy26 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy11);
 yylhsminor.yy26->token = yymsp[-5].minor.yy0;
 yylhsminor.yy26->inner = yymsp[-1].minor.yy163;
}
#line 3081 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-5].minor.yy26 = yylhsminor.yy26;
        break;
      case 134: /* set_func ::= TO_OBJECT|TO_ARRAY|TO_STRING|TO_INT|TO_FLOAT|TO_BOOL|ZVAL|VOID LPAREN decl_var COMMA ELLIPSIS RPAREN */
#line 855 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy26 = psi_set_func_init(yymsp[-5].minor.yy0->type, yymsp[-5].minor.yy0->text, yymsp[-3].minor.yy11);
 yylhsminor.yy26->token = yymsp[-5].minor.yy0;
 yylhsminor.yy26->recursive = 1;
}
#line 3094 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-4].minor);
  yy_destructor(yypParser,66,&yymsp[-2].minor);
  yy_destructor(yypParser,76,&yymsp[-1].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-5].minor.yy26 = yylhsminor.yy26;
        break;
      case 135: /* set_exp ::= set_func */
#line 860 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy147 = psi_set_exp_init(PSI_SET_FUNC, yymsp[0].minor.yy26);
}
#line 3106 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy147 = yylhsminor.yy147;
        break;
      case 136: /* set_exp ::= num_exp */
#line 863 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy147 = psi_set_exp_init(PSI_SET_NUMEXP, yymsp[0].minor.yy259);
}
#line 3114 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy147 = yylhsminor.yy147;
        break;
      case 137: /* set_exps ::= set_exp */
#line 866 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_set_exp_free),
   &yymsp[0].minor.yy147);
}
#line 3123 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 138: /* set_exps ::= set_exps COMMA set_exp */
#line 870 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy147);
}
#line 3131 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 139: /* set_exp ::= impl_var EQUALS set_exp */
#line 873 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy147 = yymsp[0].minor.yy147;
 yylhsminor.yy147->var = yymsp[-2].minor.yy37;
}
#line 3141 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,73,&yymsp[-1].minor);
  yymsp[-2].minor.yy147 = yylhsminor.yy147;
        break;
      case 140: /* set_stmt ::= SET set_exp EOS */
#line 877 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy98 = psi_set_stmt_init(yymsp[-1].minor.yy147);
 yylhsminor.yy98->token = yymsp[-2].minor.yy0;
}
#line 3151 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy98 = yylhsminor.yy98;
        break;
      case 141: /* return_stmt ::= RETURN set_func EOS */
#line 881 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy90 = psi_return_stmt_init(psi_set_exp_init(PSI_SET_FUNC, yymsp[-1].minor.yy26));
 yylhsminor.yy90->token = yymsp[-2].minor.yy0;
}
#line 3161 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy90 = yylhsminor.yy90;
        break;
      case 142: /* free_stmt ::= FREE free_exps EOS */
#line 885 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy192 = psi_free_stmt_init(yymsp[-1].minor.yy163);
 yylhsminor.yy192->token = yymsp[-2].minor.yy0;
}
#line 3171 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,63,&yymsp[0].minor);
  yymsp[-2].minor.yy192 = yylhsminor.yy192;
        break;
      case 143: /* free_exps ::= free_exp */
#line 889 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(psi_plist_init((psi_plist_dtor) psi_free_exp_free),
   &yymsp[0].minor.yy94);
}
#line 3181 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy163 = yylhsminor.yy163;
        break;
      case 144: /* free_exps ::= free_exps COMMA free_exp */
#line 893 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy163 = psi_plist_add(yymsp[-2].minor.yy163, &yymsp[0].minor.yy94);
}
#line 3189 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,66,&yymsp[-1].minor);
  yymsp[-2].minor.yy163 = yylhsminor.yy163;
        break;
      case 145: /* free_exp ::= NAME LPAREN decl_vars RPAREN */
#line 896 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy94 = psi_free_exp_init(yymsp[-3].minor.yy0->text, yymsp[-1].minor.yy163);
 yylhsminor.yy94->token = yymsp[-3].minor.yy0;
}
#line 3199 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,65,&yymsp[-2].minor);
  yy_destructor(yypParser,67,&yymsp[0].minor);
  yymsp[-3].minor.yy94 = yylhsminor.yy94;
        break;
      case 146: /* reference ::= */
#line 900 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy121 = false;
}
#line 3209 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 147: /* reference ::= AMPERSAND */
{  yy_destructor(yypParser,23,&yymsp[0].minor);
#line 903 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[0].minor.yy121 = true;
}
#line 3217 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 148: /* indirection ::= */
#line 906 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[1].minor.yy202 = 0;
}
#line 3225 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
        break;
      case 149: /* indirection ::= pointers */
#line 909 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy202 = yymsp[0].minor.yy202;
}
#line 3232 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yymsp[0].minor.yy202 = yylhsminor.yy202;
        break;
      case 150: /* pointers ::= ASTERISK */
{  yy_destructor(yypParser,28,&yymsp[0].minor);
#line 912 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yymsp[0].minor.yy202 = 1;
}
#line 3241 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 151: /* pointers ::= pointers ASTERISK */
#line 915 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
 yylhsminor.yy202 = yymsp[-1].minor.yy202+1;
}
#line 3249 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,28,&yymsp[0].minor);
  yymsp[-1].minor.yy202 = yylhsminor.yy202;
        break;
      case 152: /* file ::= blocks */
{  yy_destructor(yypParser,146,&yymsp[0].minor);
#line 169 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
}
#line 3258 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 153: /* blocks ::= block */
{  yy_destructor(yypParser,147,&yymsp[0].minor);
#line 170 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
}
#line 3266 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 154: /* blocks ::= blocks block */
{  yy_destructor(yypParser,146,&yymsp[-1].minor);
#line 171 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
}
#line 3274 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
  yy_destructor(yypParser,147,&yymsp[0].minor);
}
        break;
      case 155: /* block ::= EOF */
{  yy_destructor(yypParser,62,&yymsp[0].minor);
#line 172 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
}
#line 3283 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
}
        break;
      case 156: /* block ::= EOS */
{  yy_destructor(yypParser,63,&yymsp[0].minor);
#line 173 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
{
}
#line 3291 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
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
#line 40 "/home/mike/src/php-master/ext/psi/src/parser_proc.y"
 ++P->errors; if (TOKEN && TOKEN->type != PSI_T_EOF) { psi_error(PSI_WARNING, TOKEN->file, TOKEN->line, "PSI syntax error: Unexpected token '%s' at pos %u", TOKEN->text, TOKEN->col); } else { psi_error(PSI_WARNING, P->file.fn, P->line, "PSI syntax error: Unexpected end of input"); } 
#line 3353 "/home/mike/src/php-master/ext/psi/src/parser_proc.c"
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
