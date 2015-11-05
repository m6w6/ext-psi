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

/* in php_psi.h */
size_t psi_t_alignment(token_t);
size_t psi_t_size(token_t);

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
	struct decl_struct *strct;
} decl_type;

static inline decl_type *init_decl_type(token_t type, char *name) {
	decl_type *t = calloc(1, sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline decl_type *real_decl_type(decl_type *type) {
	while (type->real) {
		type = type->real;
	}
	return type;
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
	decl_typedef *t = calloc(1, sizeof(*t));
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

static inline decl_typedefs *add_decl_typedef(decl_typedefs *defs, decl_typedef *def) {
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
	unsigned array_size;
	struct decl_arg *arg;
} decl_var;

static inline decl_var *init_decl_var(char *name, unsigned pl, unsigned as) {
	decl_var *v = calloc(1, sizeof(*v));
	v->name = (char *) strdup((const char *) name);
	v->pointer_level = pl;
	v->array_size = as;
	return v;
}

static inline void free_decl_var(decl_var *var) {
	free(var->name);
	free(var);
}

typedef struct decl_arg {
	decl_type *type;
	decl_var *var;
	struct let_stmt *let;
} decl_arg;

static inline decl_arg *init_decl_arg(decl_type *type, decl_var *var) {
	decl_arg *arg = calloc(1, sizeof(*arg));
	arg->type = type;
	arg->var = var;
	arg->let = NULL;
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
	decl_vars *vars = calloc(1, sizeof(*vars));
	vars->count = 1;
	vars->vars = calloc(1, sizeof(*vars->vars));
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
	decl_args *args = calloc(1, sizeof(*args));
	args->count = 1;
	args->args = calloc(1, sizeof(*args->args));
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
	decl_abi *abi = calloc(1, sizeof(*abi));
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
	decl *d = calloc(1, sizeof(*d));
	d->abi = abi;
	d->func = func;
	d->args = args;
	return d;
}

static inline void free_decl(decl *d) {
	free_decl_abi(d->abi);
	free_decl_arg(d->func);
	if (d->args) {
		free_decl_args(d->args);
	}
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

typedef struct decl_struct_layout {
	size_t pos;
	size_t len;
} decl_struct_layout;

typedef struct decl_struct {
	char *name;
	decl_args *args;
	decl_struct_layout *layout;
} decl_struct;

static inline decl_struct *init_decl_struct(char *name, decl_args *args) {
	decl_struct *s = calloc(1, sizeof(*s));
	s->name = strdup(name);
	s->args = args;
	return s;
}

static inline void free_decl_struct(decl_struct *s) {
	if (s->args) {
		free_decl_args(s->args);
	}
	if (s->layout) {
		free(s->layout);
	}
	free(s->name);
	free(s);
}

static inline size_t decl_struct_size(decl_struct *s) {
	size_t c = s->args->count - 1;
	decl_type *type = real_decl_type(s->args->args[c]->type);
	return s->layout[c].pos + psi_t_alignment(type->type);
}

typedef struct decl_structs {
	size_t count;
	decl_struct **list;
} decl_structs;

static inline decl_structs *add_decl_struct(decl_structs *ss, decl_struct *s) {
	if (!ss) {
		ss = calloc(1, sizeof(*ss));
	}
	ss->list = realloc(ss->list, ++ss->count * sizeof(*ss->list));
	ss->list[ss->count-1] = s;
	return ss;
}

static inline void free_decl_structs(decl_structs *ss) {
	size_t i;

	for (i = 0; i < ss->count; ++i) {
		free_decl_struct(ss->list[i]);
	}
	free(ss->list);
	free(ss);
}

typedef union impl_val {
	char cval;
	int8_t i8;
	short sval;
	int16_t i16;
	int ival;
	int32_t i32;
	long lval;
	int64_t i64;
	float fval;
	double dval;
	union {
		zend_bool bval;
		zend_long lval;
		zend_string *str;
	} zend;
	void *ptr;
	uint8_t _dbg[sizeof(void *)];
} impl_val;

static inline impl_val *deref_impl_val(impl_val *ret_val, decl_var *var) {
	unsigned i;

	if (var->arg->var != var) for (i = 0; i < var->pointer_level; ++i) {
		ret_val = *(void **) ret_val;
	}
	return ret_val;
}

typedef struct impl_type {
	char *name;
	token_t type;
} impl_type;

static inline impl_type *init_impl_type(token_t type, char *name) {
	impl_type *t = calloc(1, sizeof(*t));

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
	impl_var *var = calloc(1, sizeof(*var));
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
	impl_def_val *def = calloc(1, sizeof(*def));
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
	impl_val val;
	zval *_zv;
} impl_arg;

static inline impl_arg *init_impl_arg(impl_type *type, impl_var *var, impl_def_val *def) {
	impl_arg *arg = calloc(1, sizeof(*arg));
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
	impl_args *args = calloc(1, sizeof(*args));
	args->args = calloc(1, sizeof(*args->args));
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
	unsigned return_reference:1;
} impl_func;

static inline impl_func *init_impl_func(char *name, impl_args *args, impl_type *type, int ret_reference) {
	impl_func *func = calloc(1, sizeof(*func));
	func->name = strdup(name);
	func->args = args ? args : init_impl_args(NULL);
	func->return_type = type;
	func->return_reference = ret_reference;
	return func;
}

static inline void free_impl_func(impl_func *f) {
	free_impl_type(f->return_type);
	free_impl_args(f->args);
	free(f->name);
	free(f);
}

typedef struct let_calloc {
	size_t n;
	decl_type *type;
} let_calloc;

static inline let_calloc *init_let_calloc(long n, decl_type *type) {
	let_calloc *alloc = calloc(1, sizeof(*alloc));
	alloc->n = n;
	alloc->type = type;
	return alloc;
}

static inline void free_let_calloc(let_calloc *alloc) {
	free_decl_type(alloc->type);
	free(alloc);
}

typedef struct let_func {
	token_t type;
	char *name;
	let_calloc *alloc;
} let_func;

static inline let_func *init_let_func(token_t type, char *name, let_calloc *alloc) {
	let_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	func->alloc = alloc;
	return func;
}

static inline void free_let_func(let_func *func) {
	if (func->alloc) {
		free_let_calloc(func->alloc);
	}
	free(func->name);
	free(func);
}

typedef struct let_value {
	let_func *func;
	impl_var *var;
	unsigned is_reference:1;
} let_value;

static inline let_value *init_let_value(let_func *func, impl_var *var, int is_reference) {
	let_value *val = calloc(1, sizeof(*val));
	val->is_reference = is_reference;
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
	impl_arg *arg;
	impl_val out;
	void *ptr;
	void *mem;
} let_stmt;

static inline let_stmt *init_let_stmt(decl_var *var, let_value *val) {
	let_stmt *let = calloc(1, sizeof(*let));
	let->var = var;
	let->val = val;
	return let;
}

static inline void free_let_stmt(let_stmt *stmt) {
	free_decl_var(stmt->var);
	if (stmt->val) {
		free_let_value(stmt->val);
	}
	free(stmt);
}

typedef struct set_func {
	token_t type;
	char *name;
} set_func;

static inline set_func *init_set_func(token_t type, char *name) {
	set_func *func = calloc(1, sizeof(*func));
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
	set_value *val = calloc(1, sizeof(*val));
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
	impl_arg *arg;
} set_stmt;

static inline set_stmt *init_set_stmt(impl_var *var, set_value *val) {
	set_stmt *set = calloc(1, sizeof(*set));
	set->var = var;
	set->val = val;
	return set;
}

static inline void free_set_stmt(set_stmt *set) {
	free_impl_var(set->var);
	free_set_value(set->val);
	free(set);
}

typedef struct return_stmt {
	set_func *func;
	decl_var *decl;
} return_stmt;

static inline return_stmt *init_return_stmt(set_func *func, decl_var *decl) {
	return_stmt *ret = calloc(1, sizeof(*ret));
	ret->func = func;
	ret->decl = decl;
	return ret;
}

static inline void free_return_stmt(return_stmt *ret) {
	free_set_func(ret->func);
	free_decl_var(ret->decl);
	free(ret);
}

typedef struct free_stmt {
	decl_vars *vars;
} free_stmt;

static inline free_stmt *init_free_stmt(decl_vars *vars) {
	free_stmt *free_ = calloc(1, sizeof(*free_));
	free_->vars = vars;
	return free_;
}

static inline void free_free_stmt(free_stmt *free_) {
	free_decl_vars(free_->vars);
	free(free_);
}

typedef struct impl_stmt {
	token_t type;
	union {
		let_stmt *let;
		set_stmt *set;
		return_stmt *ret;
		free_stmt *fre;
		void *ptr;
	} s;
} impl_stmt;

static inline impl_stmt *init_impl_stmt(token_t type, void *ptr) {
	impl_stmt *stmt = calloc(1, sizeof(*stmt));
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
	case PSI_T_RETURN:
		free_return_stmt(stmt->s.ret);
		break;
	case PSI_T_FREE:
		free_free_stmt(stmt->s.fre);
		break;
	}
	free(stmt);
}

typedef struct impl_stmts {
	struct {
		return_stmt **list;
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
	struct {
		free_stmt **list;
		size_t count;
	} fre;
} impl_stmts;

static inline void *add_impl_stmt_ex(void *list, size_t count, void *stmt) {
	list = realloc(list, count * sizeof(list));
	((void **)list)[count-1] = stmt;
	return list;
}

static inline impl_stmts *add_impl_stmt(impl_stmts *stmts, impl_stmt *stmt) {
	switch (stmt->type) {
	case PSI_T_RETURN:
		stmts->ret.list = add_impl_stmt_ex(stmts->ret.list, ++stmts->ret.count, stmt->s.ret);
		break;
	case PSI_T_LET:
		stmts->let.list = add_impl_stmt_ex(stmts->let.list, ++stmts->let.count, stmt->s.let);
		break;
	case PSI_T_SET:
		stmts->set.list = add_impl_stmt_ex(stmts->set.list, ++stmts->set.count, stmt->s.set);
		break;
	case PSI_T_FREE:
		stmts->fre.list = add_impl_stmt_ex(stmts->fre.list, ++stmts->fre.count, stmt->s.fre);
		break;
	}
	free(stmt);
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
		free_return_stmt(stmts->ret.list[i]);
	}
	free(stmts->ret.list);
	for (i = 0; i < stmts->set.count; ++i) {
		free_set_stmt(stmts->set.list[i]);
	}
	free(stmts->set.list);
	for (i = 0; i < stmts->fre.count; ++i) {
		free_free_stmt(stmts->fre.list[i]);
	}
	free(stmts->fre.list);
	free(stmts);
}

typedef struct impl {
	impl_func *func;
	impl_stmts *stmts;
	decl *decl;
} impl;

static inline impl *init_impl(impl_func *func, impl_stmts *stmts) {
	impl *i = calloc(1, sizeof(*i));
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

static inline impls *add_impl(impls *impls, impl *impl) {
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

typedef struct const_type {
	token_t type;
	char *name;
} const_type;

static inline const_type *init_const_type(token_t type, const char *name) {
	const_type *ct = calloc(1, sizeof(*ct));
	ct->type = type;
	ct->name = strdup(name);
	return ct;
}

static inline void free_const_type(const_type *type) {
	free(type->name);
	free(type);
}

typedef struct constant {
	const_type *type;
	char *name;
	impl_def_val *val;
} constant;

static inline constant *init_constant(const_type *type, char *name, impl_def_val *val) {
	constant *c = calloc(1, sizeof(*c));
	c->type = type;
	c->name = strdup(name);
	c->val = val;
	return c;
}

static inline void free_constant(constant *constant) {
	free_const_type(constant->type);
	free(constant->name);
	free_impl_def_val(constant->val);
	free(constant);
}

typedef struct constants {
	size_t count;
	constant **list;
} constants;

static inline constants *add_constant(constants *constants, constant *constant) {
	if (!constants) {
		constants = calloc(1, sizeof(*constants));
	}
	constants->list = realloc(constants->list, ++constants->count * sizeof(*constants->list));
	constants->list[constants->count-1] = constant;
	return constants;
}

static inline void free_constants(constants *c) {
	size_t i;

	for (i = 0; i < c->count; ++i) {
		free_constant(c->list[i]);
	}
	free(c->list);
	free(c);
}

#define PSI_ERROR 16
#define PSI_WARNING 32
typedef void (*psi_error_cb)(int type, const char *msg, ...);

#define PSI_DATA_MEMBERS \
	constants *consts; \
	decl_typedefs *defs; \
	decl_structs *structs; \
	decls *decls; \
	impls *impls; \
	char *lib; \
	char *fn; \
	psi_error_cb error
typedef struct PSI_Data {
	PSI_DATA_MEMBERS;
} PSI_Data;

static inline void PSI_DataExchange(PSI_Data *dest, PSI_Data *src) {
	memcpy(dest, src, sizeof(*dest));
	memset(src, 0, sizeof(*src));
}

static inline void PSI_DataDtor(PSI_Data *data) {
	if (data->consts) {
		free_constants(data->consts);
	}
	if (data->defs) {
		free_decl_typedefs(data->defs);
	}
	if (data->structs) {
		free_decl_structs(data->structs);
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
	PSI_DATA_MEMBERS;
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

	T = calloc(1, sizeof(*T) + token_len);
	T->type = P->num;
	T->line = P->line;
	T->size = token_len;
	T->text[token_len] = 0;
	memcpy(T->text, P->tok, token_len);

	return T;
}

#define PSI_PARSER_DEBUG 0x1

PSI_Parser *PSI_ParserInit(PSI_Parser *P, const char *filename, psi_error_cb error, unsigned flags);
void PSI_ParserSyntaxError(PSI_Parser *P, const char *fn, size_t ln, const char *msg, ...);
size_t PSI_ParserFill(PSI_Parser *P, size_t n);
token_t PSI_ParserScan(PSI_Parser *P);
void PSI_ParserParse(PSI_Parser *P, PSI_Token *T);
void PSI_ParserDtor(PSI_Parser *P);
void PSI_ParserFree(PSI_Parser **P);

#endif