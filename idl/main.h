/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
typedef struct PSI_Validator PSI_Validator;
typedef struct decl_typedefs decl_typedefs;
typedef struct decl_typedef decl_typedef;
typedef struct decl_type decl_type;
typedef int token_t;
struct decl_type {
	char *name;
	token_t type;
	struct decl_type *real;
};
struct decl_typedef {
	char *alias;
	decl_type *type;
};
struct decl_typedefs {
	size_t count;
	decl_typedef **list;
};
typedef struct decls decls;
typedef struct decl decl;
typedef struct decl_abi decl_abi;
struct decl_abi {
	char *convention;
};
typedef struct decl_arg decl_arg;
typedef struct decl_var decl_var;
struct decl_var {
	char *name;
	unsigned pointer_level;
};
struct decl_arg {
	decl_type *type;
	decl_var *var;
};
typedef struct decl_args decl_args;
struct decl_args {
	decl_arg **args;
	size_t count;
};
struct decl {
	decl_abi *abi;
	decl_arg *func;
	decl_args *args;
	void *dlptr;
};
struct decls {
	size_t count;
	decl **list;
};
typedef struct impls impls;
typedef struct impl impl;
typedef struct impl_func impl_func;
typedef struct impl_args impl_args;
typedef struct impl_arg impl_arg;
typedef struct impl_type impl_type;
struct impl_type {
	char *name;
	token_t type;
};
typedef struct impl_var impl_var;
struct impl_var {
	char *name;
	unsigned reference:1;
};
typedef struct impl_def_val impl_def_val;
struct impl_def_val {
	token_t type;
	union {
		int64_t digits;
		double decimals;
	} v;
	unsigned is_null:1;
};
struct impl_arg {
	impl_type *type;
	impl_var *var;
	impl_def_val *def;
};
struct impl_args {
	impl_arg **args;
	size_t count;
};
struct impl_func {
	char *name;
	impl_args *args;
	impl_type *return_type;
};
typedef struct impl_stmts impl_stmts;
typedef struct impl_stmt impl_stmt;
typedef struct let_stmt let_stmt;
typedef struct let_value let_value;
typedef struct let_func let_func;
struct let_func {
	token_t type;
	char *name;
};
struct let_value {
	let_func *func;
	impl_var *var;
	unsigned null_pointer_ref:1;
};
struct let_stmt {
	decl_var *var;
	let_value *val;
};
typedef struct set_stmt set_stmt;
typedef struct set_value set_value;
typedef struct set_func set_func;
struct set_func {
	token_t type;
	char *name;
};
typedef struct decl_vars decl_vars;
struct decl_vars {
	decl_var **vars;
	size_t count;
};
struct set_value {
	set_func *func;
	decl_vars *vars;
};
struct set_stmt {
	impl_var *var;
	set_value *val;
};
typedef struct ret_stmt ret_stmt;
struct ret_stmt {
	set_func *func;
	decl_var *decl;
};
struct impl_stmt {
	token_t type;
	union {
		let_stmt *let;
		set_stmt *set;
		ret_stmt *ret;
		void *ptr;
	} s;
};
struct impl_stmts {
	impl_stmt **stmts;
	size_t count;
};
struct impl {
	impl_func *func;
	impl_stmts *stmts;
};
struct impls {
	size_t count;
	impl **list;
};
struct PSI_Validator {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
	void *dlopened;
};
void PSI_ValidatorDtor(PSI_Validator *V);
int PSI_ValidatorValidate(PSI_Validator *V);
typedef struct PSI_Lexer PSI_Lexer;
#define BSIZE 256
struct PSI_Lexer {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
	FILE *fp;
	size_t line;
	char *cur, *tok, *lim, *eof, *ctx, *mrk, buf[BSIZE];
};
void PSI_LexerDtor(PSI_Lexer *L);
PSI_Validator *PSI_ValidatorInit(PSI_Validator *V,PSI_Lexer *L);
void PSI_ParserFree(void *p,void(*freeProc)(void *));
PSI_Lexer *PSI_LexerInit(PSI_Lexer *L,const char *filename);
void *PSI_ParserAlloc(void *(*mallocProc)(size_t));
int main(int argc,char *argv[]);
typedef struct PSI_Token PSI_Token;
struct PSI_Token {
	token_t type;
	unsigned line;
	size_t size;
	char text[1];
};
#define PSI_ParserTOKENTYPE PSI_Token *
#define PSI_ParserARG_PDECL ,PSI_Lexer *L
void PSI_Parser(void *yyp,int yymajor,PSI_ParserTOKENTYPE yyminor PSI_ParserARG_PDECL);
PSI_Token *PSI_TokenAlloc(PSI_Lexer *L,token_t t);
token_t PSI_LexerScan(PSI_Lexer *L);
#if !defined(NDEBUG)
void PSI_ParserTrace(FILE *TraceFILE,char *zTracePrompt);
#endif
