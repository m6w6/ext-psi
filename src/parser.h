#ifndef _PSI_PARSER_H
#define _PSI_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <Zend/zend_types.h>

#include "parser_proc.h"

#define BSIZE 256

typedef int token_t;

typedef struct PSI_Token {
	token_t type;
	unsigned line;
	size_t size;
	char text[1];
} PSI_Token;

typedef struct decl_type {
	char *name;
	token_t type;
	struct decl_type *real;
} decl_type;

static inline decl_type *init_decl_type(token_t type, char *name) {
	decl_type *t = malloc(sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline void free_decl_type(decl_type *type) {
	free(type->name);
	free(type);
}

typedef struct decl_typedef {
	char *alias;
	decl_type *type;
} decl_typedef;

static inline decl_typedef *init_decl_typedef(char *name, decl_type *type) {
	decl_typedef *t = malloc(sizeof(*t));
	t->alias = strdup(name);
	t->type = type;
	return t;
}

static inline void free_decl_typedef(decl_typedef *t) {
	free(t->alias);
	free_decl_type(t->type);
	free(t);
}

typedef struct decl_typedefs {
	size_t count;
	decl_typedef **list;
} decl_typedefs;

static decl_typedefs *add_decl_typedef(decl_typedefs *defs, decl_typedef *def) {
	if (!defs) {
		defs = calloc(1, sizeof(*defs));
	}
	defs->list = realloc(defs->list, ++defs->count * sizeof(*defs->list));
	defs->list[defs->count-1] = def;
	return defs;
}

static void free_decl_typedefs(decl_typedefs *defs) {
	size_t i;

	for (i = 0; i < defs->count; ++i) {
		free_decl_typedef(defs->list[i]);
	}
	free(defs->list);
	free(defs);
}

typedef struct decl_var {
	char *name;
	unsigned pointer_level;
} decl_var;

static inline decl_var *init_decl_var(char *name, unsigned pl) {
	decl_var *v = malloc(sizeof(*v));
	v->name = (char *) strdup((const char *) name);
	v->pointer_level = pl;
	return v;
}

static inline void free_decl_var(decl_var *var) {
	free(var->name);
	free(var);
}

typedef struct decl_arg {
	decl_type *type;
	decl_var *var;
} decl_arg;

static inline decl_arg *init_decl_arg(decl_type *type, decl_var *var) {
	decl_arg *arg = malloc(sizeof(*arg));
	arg->type = type;
	arg->var = var;
	return arg;
}

static inline void free_decl_arg(decl_arg *arg) {
	free_decl_type(arg->type);
	free_decl_var(arg->var);
	free(arg);
}

typedef struct decl_vars {
	decl_var **vars;
	size_t count;
} decl_vars;

static inline decl_vars *init_decl_vars(decl_var *var) {
	decl_vars *vars = malloc(sizeof(*vars));
	vars->count = 1;
	vars->vars = malloc(sizeof(*vars->vars));
	vars->vars[0] = var;
	return vars;
}

static inline decl_vars *add_decl_var(decl_vars *vars, decl_var *var) {
	vars->vars = realloc(vars->vars, ++vars->count * sizeof(*vars->vars));
	vars->vars[vars->count-1] = var;
	return vars;
}

static inline void free_decl_vars(decl_vars *vars) {
	size_t i;

	for (i = 0; i < vars->count; ++i) {
		free_decl_var(vars->vars[i]);
	}
	free(vars->vars);
	free(vars);
}

typedef struct decl_args {
	decl_arg **args;
	size_t count;
} decl_args;

static inline decl_args *init_decl_args(decl_arg *arg) {
	decl_args *args = malloc(sizeof(*args));
	args->count = 1;
	args->args = malloc(sizeof(*args->args));
	args->args[0] = arg;
	return args;
}

static inline decl_args *add_decl_arg(decl_args *args, decl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count-1] = arg;
	return args;
}

static inline void free_decl_args(decl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		free_decl_arg(args->args[i]);
	}
	free(args->args);
	free(args);
}

typedef struct decl_abi {
	char *convention;
} decl_abi;

static inline decl_abi *init_decl_abi(char *convention) {
	decl_abi *abi = malloc(sizeof(*abi));
	abi->convention = strdup(convention);
	return abi;
}

static inline void free_decl_abi(decl_abi *abi) {
	free(abi->convention);
	free(abi);
}

typedef struct decl {
	decl_abi *abi;
	decl_arg *func;
	decl_args *args;
	void *dlptr;
} decl;

static inline decl* init_decl(decl_abi *abi, decl_arg *func, decl_args *args) {
	decl *d = malloc(sizeof(*d));
	d->abi = abi;
	d->func = func;
	d->args = args;
	return d;
}

static inline void free_decl(decl *d) {
	free_decl_abi(d->abi);
	free_decl_arg(d->func);
	free_decl_args(d->args);
	free(d);
}

typedef struct decls {
	size_t count;
	decl **list;
} decls;

static inline decls *add_decl(decls *decls, decl *decl) {
	if (!decls) {
		decls = calloc(1, sizeof(*decls));
	}
	decls->list = realloc(decls->list, ++decls->count * sizeof(*decls->list));
	decls->list[decls->count-1] = decl;
	return decls;
}

static inline void free_decls(decls *decls) {
	size_t i;

	for (i = 0; i < decls->count; ++i) {
		free_decl(decls->list[i]);
	}
	free(decls->list);
	free(decls);
}

typedef struct impl_type {
	char *name;
	token_t type;
} impl_type;

static inline impl_type *init_impl_type(token_t type, char *name) {
	impl_type *t = malloc(sizeof(*t));

	t->type = type;
	t->name = (char *) strdup((const char *) name);
	return t;
}

static inline void free_impl_type(impl_type *type) {
	free(type->name);
	free(type);
}

typedef struct impl_var {
	char *name;
	unsigned reference:1;
} impl_var;

static inline impl_var *init_impl_var(char *name, int is_reference) {
	impl_var *var = malloc(sizeof(*var));
	var->name = (char *) strdup((const char *) name);
	var->reference = is_reference;
	return var;
}

static inline void free_impl_var(impl_var *var) {
	free(var->name);
	free(var);
}

typedef struct impl_def_val {
	token_t type;
	char *text;
} impl_def_val;

static inline impl_def_val *init_impl_def_val(PSI_Token *T) {
	impl_def_val *def = malloc(sizeof(*def));
	def->type = T->type;
	def->text = strdup(T->text);
	return def;
}

static inline void free_impl_def_val(impl_def_val *def) {
	free(def->text);
	free(def);
}

typedef struct impl_arg {
	impl_type *type;
	impl_var *var;
	impl_def_val *def;
	union {
		unsigned char bval;
		zend_long lval;
		double dval;
		struct {
			char *val;
			size_t len;
		} str;
	} val;
} impl_arg;

static inline impl_arg *init_impl_arg(impl_type *type, impl_var *var, impl_def_val *def) {
	impl_arg *arg = malloc(sizeof(*arg));
	arg->type = type;
	arg->var = var;
	arg->def = def;
	return arg;
}

static inline void free_impl_arg(impl_arg *arg) {
	free_impl_type(arg->type);
	free_impl_var(arg->var);
	if (arg->def) {
		free_impl_def_val(arg->def);
	}
	free(arg);
}

typedef struct impl_args {
	impl_arg **args;
	size_t count;
} impl_args;

static inline impl_args *init_impl_args(impl_arg *arg) {
	impl_args *args = malloc(sizeof(*args));
	args->args = malloc(sizeof(*args->args));
	if (arg) {
		args->count = 1;
		args->args[0] = arg;
	} else {
		args->count = 0;
		args->args = NULL;
	}
	return args;
}

static inline impl_args *add_impl_arg(impl_args *args, impl_arg *arg) {
	args->args = realloc(args->args, ++args->count * sizeof(*args->args));
	args->args[args->count-1] = arg;
	return args;
}

static inline void free_impl_args(impl_args *args) {
	size_t i;

	for (i = 0; i < args->count; ++i) {
		free_impl_arg(args->args[i]);
	}
	free(args->args);
	free(args);
}

typedef struct impl_func {
	char *name;
	impl_args *args;
	impl_type *return_type;
} impl_func;

static inline impl_func *init_impl_func(char *name, impl_args *args, impl_type *type) {
	impl_func *func = malloc(sizeof(*func));
	func->name = strdup(name);
	func->args = args ? args : init_impl_args(NULL);
	func->return_type = type;
	return func;
}

static inline void free_impl_func(impl_func *f) {
	free_impl_type(f->return_type);
	free_impl_args(f->args);
	free(f->name);
	free(f);
}

typedef struct let_func {
	token_t type;
	char *name;
} let_func;

static inline let_func *init_let_func(token_t type, char *name) {
	let_func *func = malloc(sizeof(*func));
	func->type = type;
	func->name = (char *) strdup((const char *) name);
	return func;
}

static inline void free_let_func(let_func *func) {
	free(func->name);
	free(func);
}

typedef struct let_value {
	let_func *func;
	impl_var *var;
	unsigned null_pointer_ref:1;
} let_value;

static inline let_value *init_let_value(let_func *func, impl_var *var, int null_pointer_ref) {
	let_value *val = malloc(sizeof(*val));
	val->null_pointer_ref = null_pointer_ref;
	val->func = func;
	val->var = var;
	return val;
}

static inline void free_let_value(let_value *val) {
	if (val->func) {
		free_let_func(val->func);
	}
	if (val->var) {
		free_impl_var(val->var);
	}
	free(val);
}

typedef struct let_stmt {
	decl_var *var;
	let_value *val;
} let_stmt;

static inline let_stmt *init_let_stmt(decl_var *var, let_value *val) {
	let_stmt *let = malloc(sizeof(*let));
	let->var = var;
	let->val = val;
	return let;
}

static inline void free_let_stmt(let_stmt *stmt) {
	free_decl_var(stmt->var);
	free_let_value(stmt->val);
	free(stmt);
}

typedef struct set_func {
	token_t type;
	char *name;
} set_func;

static inline set_func *init_set_func(token_t type, char *name) {
	set_func *func = malloc(sizeof(*func));
	func->type = type;
	func->name = (char *) strdup((const char *) name);
	return func;
}

static inline void free_set_func(set_func *func) {
	free(func->name);
	free(func);
}

typedef struct set_value {
	set_func *func;
	decl_vars *vars;
} set_value;

static inline set_value *init_set_value(set_func *func, decl_vars *vars) {
	set_value *val = malloc(sizeof(*val));
	val->func = func;
	val->vars = vars;
	return val;
}

static inline void free_set_value(set_value *val) {
	free_set_func(val->func);
	free_decl_vars(val->vars);
	free(val);
}

typedef struct set_stmt {
	impl_var *var;
	set_value *val;
} set_stmt;

static inline set_stmt *init_set_stmt(impl_var *var, set_value *val) {
	set_stmt *set = malloc(sizeof(*set));
	set->var = var;
	set->val = val;
	return set;
}

static inline void free_set_stmt(set_stmt *set) {
	free_impl_var(set->var);
	free_set_value(set->val);
	free(set);
}

typedef struct ret_stmt {
	set_func *func;
	decl_var *decl;
} ret_stmt;

static inline ret_stmt *init_ret_stmt(set_func *func, decl_var *decl) {
	ret_stmt *ret = malloc(sizeof(*ret));
	ret->func = func;
	ret->decl = decl;
	return ret;
}

static inline void free_ret_stmt(ret_stmt *ret) {
	free_set_func(ret->func);
	free_decl_var(ret->decl);
	free(ret);
}

typedef struct impl_stmt {
	token_t type;
	union {
		let_stmt *let;
		set_stmt *set;
		ret_stmt *ret;
		void *ptr;
	} s;
} impl_stmt;

static inline impl_stmt *init_impl_stmt(token_t type, void *ptr) {
	impl_stmt *stmt = malloc(sizeof(*stmt));
	stmt->type = type;
	stmt->s.ptr = ptr;
	return stmt;
}

static inline void free_impl_stmt(impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_LET:
		free_let_stmt(stmt->s.let);
		break;
	case PSI_T_SET:
		free_set_stmt(stmt->s.set);
		break;
	case PSI_T_RET:
		free_ret_stmt(stmt->s.ret);
		break;
	}
	free(stmt);
}

typedef struct impl_stmts {
	struct {
		ret_stmt **list;
		size_t count;
	} ret;
	struct {
		let_stmt **list;
		size_t count;
	} let;
	struct {
		set_stmt **list;
		size_t count;
	} set;
} impl_stmts;

static inline void *add_impl_stmt_ex(void *list, size_t count, void *stmt) {
	list = realloc(list, count * sizeof(list));
	((void **)list)[count-1] = stmt;
	return list;
}

static inline impl_stmts *add_impl_stmt(impl_stmts *stmts, impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_RET:
		stmts->ret.list = add_impl_stmt_ex(stmts->ret.list, ++stmts->ret.count, stmt->s.ret);
		break;
	case PSI_T_LET:
		stmts->let.list = add_impl_stmt_ex(stmts->let.list, ++stmts->let.count, stmt->s.let);
		break;
	case PSI_T_SET:
		stmts->set.list = add_impl_stmt_ex(stmts->set.list, ++stmts->set.count, stmt->s.set);
		break;
	}
	return stmts;
}

static inline impl_stmts *init_impl_stmts(impl_stmt *stmt) {
	impl_stmts *stmts = calloc(1, sizeof(*stmts));
	return add_impl_stmt(stmts, stmt);
}

static inline void free_impl_stmts(impl_stmts *stmts) {
	size_t i;

	for (i = 0; i < stmts->let.count; ++i) {
		free_let_stmt(stmts->let.list[i]);
	}
	free(stmts->let.list);
	for (i = 0; i < stmts->ret.count; ++i) {
		free_ret_stmt(stmts->ret.list[i]);
	}
	free(stmts->ret.list);
	for (i = 0; i < stmts->set.count; ++i) {
		free_set_stmt(stmts->set.list[i]);
	}
	free(stmts->set.list);
	free(stmts);
}

typedef struct impl {
	impl_func *func;
	impl_stmts *stmts;
	decl *decl;
} impl;

static inline impl *init_impl(impl_func *func, impl_stmts *stmts) {
	impl *i = malloc(sizeof(*i));
	i->func = func;
	i->stmts = stmts;
	return i;
}

static inline void free_impl(impl *impl) {
	free_impl_func(impl->func);
	free_impl_stmts(impl->stmts);
	free(impl);
}

typedef struct impls {
	size_t count;
	impl **list;
} impls;

static impls *add_impl(impls *impls, impl *impl) {
	if (!impls) {
		impls = calloc(1, sizeof(*impls));
	}
	impls->list = realloc(impls->list, ++impls->count * sizeof(*impls->list));
	impls->list[impls->count-1] = impl;
	return impls;
}

static void free_impls(impls *impls) {
	size_t i;

	for (i = 0; i < impls->count; ++i) {
		free_impl(impls->list[i]);
	}
	free(impls->list);
	free(impls);
}

typedef struct PSI_Data {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
} PSI_Data;

static inline void PSI_DataExchange(PSI_Data *dest, PSI_Data *src) {
	memcpy(dest, src, sizeof(*dest));
	memset(src, 0, sizeof(*src));
}

static inline void PSI_DataDtor(PSI_Data *data) {
	if (data->defs) {
		free_decl_typedefs(data->defs);
	}
	if (data->decls) {
		free_decls(data->decls);
	}
	if (data->impls) {
		free_impls(data->impls);
	}
	if (data->lib) {
		free(data->lib);
	}
	if (data->fn) {
		free(data->fn);
	}
}

typedef struct PSI_Parser {
	decl_typedefs *defs;
	decls *decls;
	impls *impls;
	char *lib;
	char *fn;
	FILE *fp;
	unsigned flags;
	unsigned errors;
	void *proc;
	size_t line;
	token_t num;
	char *cur, *tok, *lim, *eof, *ctx, *mrk, buf[BSIZE];
} PSI_Parser;

static inline PSI_Token *PSI_TokenAlloc(PSI_Parser *P) {
	PSI_Token *T;
	size_t token_len;

	if (P->cur <= P->tok) {
		return NULL;
	}

	token_len = P->cur - P->tok;

	T = malloc(sizeof(*T) + token_len);
	T->type = P->num;
	T->line = P->line;
	T->size = token_len;
	T->text[token_len] = 0;
	memcpy(T->text, P->tok, token_len);

	return T;
}

#define PSI_PARSER_DEBUG 0x1

PSI_Parser *PSI_ParserInit(PSI_Parser *P, const char *filename, unsigned flags);
void PSI_ParserSyntaxError(PSI_Parser *P, const char *fn, size_t ln, const char *msg, ...);
size_t PSI_ParserFill(PSI_Parser *P, size_t n);
token_t PSI_ParserScan(PSI_Parser *P);
void PSI_ParserParse(PSI_Parser *P, PSI_Token *T);
void PSI_ParserDtor(PSI_Parser *P);
void PSI_ParserFree(PSI_Parser **P);

#endif
