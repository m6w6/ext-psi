#ifndef _PSI_PARSER_H
#define _PSI_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include <Zend/zend_types.h>

#include "parser_proc.h"

#define BSIZE 256

#define PSI_T_POINTER PSI_T_ASTERISK
#define PSI_T_LONG_DOUBLE (PSI_T_DOUBLE << 16)

typedef int token_t;

/* in php_psi.h */
size_t psi_t_alignment(token_t);
size_t psi_t_size(token_t);

typedef struct PSI_Token {
	token_t type;
	unsigned size, *line;
	char *text, *file;
	char buf[1];
} PSI_Token;

typedef union impl_val {
	char cval;
	int8_t i8;
	uint8_t u8;
	short sval;
	int16_t i16;
	uint16_t u16;
	int ival;
	int32_t i32;
	uint32_t u32;
	long lval;
	int64_t i64;
	uint64_t u64;
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

typedef struct decl_type {
	PSI_Token *token;
	char *name;
	token_t type;
	struct decl_type *real;
	struct decl_struct *strct;
} decl_type;

static inline decl_type *init_decl_type(token_t type, const char *name) {
	decl_type *t = calloc(1, sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline decl_type *init_decl_type_ex(token_t type, int argc, ...) {
	va_list argv;
	char *ptr, *arg;
	unsigned i;
	size_t len, pos = 0, all = 0;
	decl_type *t = calloc(1, sizeof(*t));

	va_start(argv, argc);
	for (i = 0; i < argc; ++i) {
		arg = va_arg(argv, char *);
		len = va_arg(argv, size_t);

		if (len) {
			if (all) {
				pos = all;
				ptr = realloc(ptr, 1 + (all += len));
			} else {
				ptr = malloc(1 + (all = len));
			}
			memcpy(ptr + pos, arg, len);
		}
	}
	va_end(argv);

	if (!all) {
		ptr = calloc(1, 1);
	} else {
		ptr[all] = 0;
	}
	t->type = type;
	t->name = ptr;
	return t;
}

static inline decl_type *real_decl_type(decl_type *type) {
	while (type->real) {
		type = type->real;
	}
	return type;
}

static inline void free_decl_type(decl_type *type) {
	if (type->token) {
		free(type->token);
	}
	free(type->name);
	free(type);
}

typedef struct decl_typedef {
	PSI_Token *token;
	char *alias;
	decl_type *type;
} decl_typedef;

static inline decl_typedef *init_decl_typedef(const char *name, decl_type *type) {
	decl_typedef *t = calloc(1, sizeof(*t));
	t->alias = strdup(name);
	t->type = type;
	return t;
}

static inline void free_decl_typedef(decl_typedef *t) {
	if (t->token) {
		free(t->token);
	}
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
	PSI_Token *token;
	char *name;
	unsigned pointer_level;
	unsigned array_size;
	struct decl_arg *arg;
} decl_var;

static inline decl_var *init_decl_var(const char *name, unsigned pl, unsigned as) {
	decl_var *v = calloc(1, sizeof(*v));
	v->name = (char *) strdup((const char *) name);
	v->pointer_level = pl;
	v->array_size = as;
	return v;
}

static inline void free_decl_var(decl_var *var) {
	if (var->token) {
		free(var->token);
	}
	free(var->name);
	free(var);
}

typedef struct decl_struct_layout {
	size_t pos;
	size_t len;
} decl_struct_layout;

static inline decl_struct_layout *init_decl_struct_layout(size_t pos, size_t len) {
	decl_struct_layout *l = calloc(1, sizeof(*l));

	l->pos = pos;
	l->len = len;
	return l;
}

static inline void free_decl_struct_layout(decl_struct_layout *l) {
	free(l);
}

typedef struct decl_arg {
	PSI_Token *token;
	decl_type *type;
	decl_var *var;
	decl_struct_layout *layout;
	struct let_stmt *let;
	impl_val val;
	void *ptr;
	void *mem;
} decl_arg;

static inline decl_arg *init_decl_arg(decl_type *type, decl_var *var) {
	decl_arg *arg = calloc(1, sizeof(*arg));
	arg->token = var->token;
	arg->type = type;
	arg->var = var;
	var->arg = arg;
	arg->ptr = &arg->val;
	return arg;
}

static inline void free_decl_arg(decl_arg *arg) {
	free_decl_type(arg->type);
	free_decl_var(arg->var);
	if (arg->layout) {
		free_decl_struct_layout(arg->layout);
	}
	free(arg);
}

typedef struct decl_vars {
	decl_var **vars;
	size_t count;
} decl_vars;

static inline decl_vars *init_decl_vars(decl_var *var) {
	decl_vars *vars = calloc(1, sizeof(*vars));
	if (var) {
		vars->count = 1;
		vars->vars = calloc(1, sizeof(*vars->vars));
		vars->vars[0] = var;
	}
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
	unsigned varargs:1;
} decl_args;

static inline decl_args *init_decl_args(decl_arg *arg) {
	decl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
	}
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
	PSI_Token *token;
	char *convention;
} decl_abi;

static inline decl_abi *init_decl_abi(const char *convention) {
	decl_abi *abi = calloc(1, sizeof(*abi));
	abi->convention = strdup(convention);
	return abi;
}

static inline void free_decl_abi(decl_abi *abi) {
	if (abi->token) {
		free(abi->token);
	}
	free(abi->convention);
	free(abi);
}

typedef struct decl_callinfo {
	void *sym;
	void *info;
	size_t argc;
	void **args;
	void *rval;
} decl_callinfo;

typedef struct decl {
	decl_abi *abi;
	decl_arg *func;
	decl_args *args;
	struct impl *impl;
	decl_callinfo call;
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

typedef struct decl_struct {
	PSI_Token *token;
	char *name;
	decl_args *args;
	size_t size;
	struct {
		void *type;
		void (*dtor)(void *type);
	} engine;
} decl_struct;

static inline decl_struct *init_decl_struct(const char *name, decl_args *args) {
	decl_struct *s = calloc(1, sizeof(*s));
	s->name = strdup(name);
	s->args = args;
	return s;
}

static inline void free_decl_struct(decl_struct *s) {
	if (s->token) {
		free(s->token);
	}
	if (s->args) {
		free_decl_args(s->args);
	}
	free(s->name);
	free(s);
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

typedef struct impl_type {
	char *name;
	token_t type;
} impl_type;

static inline impl_type *init_impl_type(token_t type, const char *name) {
	impl_type *t = calloc(1, sizeof(*t));

	t->type = type;
	t->name = strdup(name);
	return t;
}

static inline void free_impl_type(impl_type *type) {
	free(type->name);
	free(type);
}

typedef struct impl_var {
	PSI_Token *token;
	char *name;
	unsigned reference:1;
} impl_var;

static inline impl_var *init_impl_var(const char *name, int is_reference) {
	impl_var *var = calloc(1, sizeof(*var));
	var->name = strdup(name);
	var->reference = is_reference;
	return var;
}

static inline void free_impl_var(impl_var *var) {
	if (var->token) {
		free(var->token);
	}
	free(var->name);
	free(var);
}

typedef struct impl_def_val {
	token_t type;
	char *text;
} impl_def_val;

static inline impl_def_val *init_impl_def_val(token_t t, const char *text) {
	impl_def_val *def = calloc(1, sizeof(*def));
	def->type = t;
	def->text = strdup(text);
	return def;
}

static inline void free_impl_def_val(impl_def_val *def) {
	free(def->text);
	free(def);
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

static inline constant *init_constant(const_type *type, const char *name, impl_def_val *val) {
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

typedef struct impl_vararg {
	impl_arg *name;
	struct impl_args *args;
	token_t *types;
	impl_val *values;
	void **free_list;
} impl_vararg;

typedef struct impl_args {
	impl_arg **args;
	size_t count;
	impl_vararg vararg;
} impl_args;

static inline impl_args *init_impl_args(impl_arg *arg) {
	impl_args *args = calloc(1, sizeof(*args));
	if (arg) {
		args->count = 1;
		args->args = calloc(1, sizeof(*args->args));
		args->args[0] = arg;
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
	if (args->vararg.name) {
		free_impl_arg(args->vararg.name);
	}
	free(args->args);
	free(args);
}

typedef struct impl_func {
	PSI_Token *token;
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
	if (f->token) {
		free(f->token);
	}
	free_impl_type(f->return_type);
	free_impl_args(f->args);
	free(f->name);
	free(f);
}

typedef struct num_exp {
	PSI_Token *token;
	token_t t;
	union {
		char *numb;
		constant *cnst;
		decl_var *dvar;
	} u;
	token_t operator;
	int (*calculator)(int t1, impl_val *v1, int t2, impl_val *v2, impl_val *res);
	struct num_exp *operand;
} num_exp;

static inline num_exp *init_num_exp(token_t t, void *num) {
	num_exp *exp = calloc(1, sizeof(*exp));
	switch (exp->t = t) {
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		exp->u.numb = strdup(num);
		break;
	case PSI_T_NAME:
		exp->u.dvar = num;
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return exp;
}

static inline void free_num_exp(num_exp *exp) {
	if (exp->token) {
		free(exp->token);
	}
	switch (exp->t) {
	case PSI_T_NUMBER:
		free(exp->u.numb);
		break;
	case PSI_T_NSNAME:
		break;
	case PSI_T_NAME:
		free_decl_var(exp->u.dvar);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	if (exp->operand) {
		free_num_exp(exp->operand);
	}
	free(exp);
}

typedef struct let_calloc {
	num_exp *nmemb;
	num_exp *size;
} let_calloc;

static inline let_calloc *init_let_calloc(num_exp *nmemb, num_exp *size) {
	let_calloc *alloc = calloc(1, sizeof(*alloc));
	alloc->nmemb = nmemb;
	alloc->size = size;
	return alloc;
}

static inline void free_let_calloc(let_calloc *alloc) {
	free_num_exp(alloc->nmemb);
	free_num_exp(alloc->size);
	free(alloc);
}

typedef struct let_func {
	token_t type;
	char *name;
	impl_var *var;
	impl_arg *arg;
} let_func;

static inline let_func *init_let_func(token_t type, const char *name, impl_var *var) {
	let_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	func->var = var;
	return func;
}

static inline void free_let_func(let_func *func) {
	free_impl_var(func->var);
	free(func->name);
	free(func);
}

#define PSI_LET_REFERENCE 0x1;
typedef struct let_val {
	enum let_val_kind {
		PSI_LET_NULL,
		PSI_LET_NUMEXP,
		PSI_LET_CALLOC,
		PSI_LET_FUNC,
		PSI_LET_TMP,
	} kind;
	union {
		num_exp *num;
		let_calloc *alloc;
		let_func *func;
		decl_var *var;
	} data;
	union {
		struct {
			unsigned is_reference:1;
		} one;
		unsigned all;
	} flags;
} let_val;

static inline let_val *init_let_val(enum let_val_kind kind, void *data) {
	let_val *let = calloc(1, sizeof(*let));
	switch (let->kind = kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_NUMEXP:
		let->data.num = data;
		break;
	case PSI_LET_CALLOC:
		let->data.alloc = data;
		break;
	case PSI_LET_FUNC:
		let->data.func = data;
		break;
	case PSI_LET_TMP:
		let->data.var = data;
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	return let;
}

static inline void free_let_val(let_val *let) {
	switch (let->kind) {
	case PSI_LET_NULL:
		break;
	case PSI_LET_NUMEXP:
		free_num_exp(let->data.num);
		break;
	case PSI_LET_CALLOC:
		free_let_calloc(let->data.alloc);
		break;
	case PSI_LET_FUNC:
		free_let_func(let->data.func);
		break;
	case PSI_LET_TMP:
		free_decl_var(let->data.var);
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	free(let);
}

typedef struct let_stmt {
	decl_var *var;
	let_val *val;

	void *ptr;
} let_stmt;

static inline let_stmt *init_let_stmt(decl_var *var, let_val *val) {
	let_stmt *let = calloc(1, sizeof(*let));
	let->var = var;
	let->val = val;
	return let;
}

static inline void free_let_stmt(let_stmt *stmt) {
	if (stmt->val) {
		if (stmt->val->kind == PSI_LET_TMP && stmt->var->arg) {
			free_decl_arg(stmt->var->arg);
		}
		free_let_val(stmt->val);
	}
	free_decl_var(stmt->var);
	free(stmt);
}

struct set_value;

typedef struct set_func {
	PSI_Token *token;
	token_t type;
	char *name;
	void (*handler)(zval *, struct set_value *set, impl_val *ret_val);
} set_func;

static inline set_func *init_set_func(token_t type, const char *name) {
	set_func *func = calloc(1, sizeof(*func));
	func->type = type;
	func->name = strdup(name);
	return func;
}

static inline void free_set_func(set_func *func) {
	if (func->token) {
		free(func->token);
	}
	free(func->name);
	free(func);
}

typedef struct set_value {
	set_func *func;
	decl_vars *vars;
	num_exp *num;
	struct {
		struct set_value *set;
		impl_val *val;
	} outer;
	struct set_value **inner;
	size_t count;
} set_value;

static inline set_value *init_set_value(set_func *func, decl_vars *vars) {
	set_value *val = calloc(1, sizeof(*val));
	val->func = func;
	val->vars = vars;
	return val;
}
static inline set_value *add_inner_set_value(set_value *val, set_value *inner) {
	val->inner = realloc(val->inner, ++val->count * sizeof(*val->inner));
	val->inner[val->count-1] = inner;
	inner->outer.set = val;
	return val;
}

static inline void free_set_value(set_value *val) {
	if (val->func) {
		free_set_func(val->func);
	}
	if (val->vars) {
		free_decl_vars(val->vars);
	}
	if (val->inner && (!val->outer.set || val->outer.set->inner != val->inner)) {
		size_t i;
		for (i = 0; i < val->count; ++i) {
			free_set_value(val->inner[i]);
		}
		free(val->inner);
	}
	if (val->num) {
		free_num_exp(val->num);
	}
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
	PSI_Token *token;
	set_value *set;
	decl_arg *decl;
} return_stmt;

static inline return_stmt *init_return_stmt(set_value *val) {
	return_stmt *ret = calloc(1, sizeof(*ret));
	ret->set = val;
	return ret;
}

static inline void free_return_stmt(return_stmt *ret) {
	if (ret->token) {
		free(ret->token);
	}
	free_set_value(ret->set);
	free(ret);
}

typedef struct free_call {
	PSI_Token *token;
	char *func;
	decl_vars *vars;
	decl *decl;
} free_call;

static inline free_call *init_free_call(const char *func, decl_vars *vars) {
	free_call *f = calloc(1, sizeof(*f));
	f->func = strdup(func);
	f->vars = vars;
	return f;
}

static inline void free_free_call(free_call *f) {
	if (f->token) {
		free(f->token);
	}
	free(f->func);
	free_decl_vars(f->vars);
	free(f);
}

typedef struct free_calls {
	free_call **list;
	size_t count;
} free_calls;

static inline free_calls *init_free_calls(free_call *f) {
	free_calls *fcs = calloc(1, sizeof(*fcs));
	if (f) {
		fcs->count = 1;
		fcs->list = calloc(1, sizeof(*fcs->list));
		fcs->list[0] = f;
	}
	return fcs;
}

static inline void free_free_calls(free_calls *fcs) {
	size_t i;

	for (i = 0; i < fcs->count; ++i) {
		free_free_call(fcs->list[i]);
	}
	free(fcs->list);
	free(fcs);
}

static inline free_calls *add_free_call(free_calls *fcs, free_call *f) {
	fcs->list = realloc(fcs->list, ++fcs->count * sizeof(*fcs->list));
	fcs->list[fcs->count-1] = f;
	return fcs;
}

typedef struct free_stmt {
	free_calls *calls;
} free_stmt;

static inline free_stmt *init_free_stmt(free_calls *calls) {
	free_stmt *f = calloc(1, sizeof(*f));
	f->calls = calls;
	return f;
}

static inline void free_free_stmt(free_stmt *f) {
	free_free_calls(f->calls);
	free(f);
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

typedef struct decl_file {
	char *ln;
	char *fn;
} decl_file;

static inline void free_decl_file(decl_file *file) {
	if (file->ln) {
		free(file->ln);
	}
	if (file->fn) {
		free(file->fn);
	}
	memset(file, 0, sizeof(*file));
}

typedef struct decl_libs {
	void **dl;
	size_t count;
} decl_libs;

static inline void free_decl_libs(decl_libs *libs) {
	if (libs->dl) {
		size_t i;
		for (i = 0; i < libs->count; ++i) {
			if (libs->dl[i]) {
				dlclose(libs->dl[i]);
			}
		}
		free(libs->dl);
	}
	memset(libs, 0, sizeof(*libs));
}

static inline void add_decl_lib(decl_libs *libs, void *dlopened) {
	libs->dl = realloc(libs->dl, ++libs->count * sizeof(*libs->dl));
	libs->dl[libs->count-1] = dlopened;
}

static inline impl_val *deref_impl_val(impl_val *ret_val, decl_var *var) {
	unsigned i;

	ZEND_ASSERT(var->arg->var != var);
#if 0
	fprintf(stderr, "deref: %s pl=%u:%u as=%u:%u %p\n",
			var->name, var->pointer_level, var->arg->var->pointer_level,
			var->array_size, var->arg->var->array_size, ret_val);
#endif
	for (i = 0; i < var->pointer_level; ++i) {
#if 0
		fprintf(stderr, "-- %p %p %p\n", ret_val, *(void**)ret_val, ret_val->ptr);
#endif
		ret_val = *(void **) ret_val;
	}
	return ret_val;
}

static inline impl_val *enref_impl_val(void *ptr, decl_var *var) {
	impl_val *val, *val_ptr;
	unsigned i;

	ZEND_ASSERT(var->arg->var == var);
#if 0
	fprintf(stderr, "enref: %s pl=%u:%u as=%u:%u\n",
			var->name, var->pointer_level, var->arg->var->pointer_level,
			var->array_size, var->arg->var->array_size);
#endif
	if (!var->pointer_level && real_decl_type(var->arg->type)->type != PSI_T_STRUCT) {
		return ptr;
	}

	val = val_ptr = calloc(var->pointer_level + 1, sizeof(void *));
	for (i = !var->arg->var->array_size; i < var->pointer_level; ++i) {
#if 0
		fprintf(stderr, "++\n");
#endif
		val_ptr->ptr = (void **) val_ptr + 1;
		val_ptr = val_ptr->ptr;
	}
	val_ptr->ptr = ptr;
	return val;
}

static inline impl_val *struct_member_ref(decl_arg *set_arg, impl_val *struct_ptr, impl_val **to_free) {
	void *ptr = (char *) struct_ptr + set_arg->layout->pos;
#if 0
	fprintf(stderr, "struct member %s: %p\n", set_arg->var->name, ptr);
#endif
	return ptr;
}


#define PSI_ERROR 16
#define PSI_WARNING 32
typedef void (*psi_error_cb)(PSI_Token *token, int type, const char *msg, ...);

#define PSI_DATA(D) ((PSI_Data *) (D))
#define PSI_DATA_MEMBERS \
	constants *consts; \
	decl_typedefs *defs; \
	decl_structs *structs; \
	decls *decls; \
	impls *impls; \
	union { \
		decl_file file; \
		decl_libs libs; \
	} psi; \
	psi_error_cb error
typedef struct PSI_Data {
	PSI_DATA_MEMBERS;
} PSI_Data;

static inline PSI_Data *PSI_DataExchange(PSI_Data *dest, PSI_Data *src) {
	if (!dest) {
		dest = malloc(sizeof(*dest));
	}
	memcpy(dest, src, sizeof(*dest));
	memset(src, 0, sizeof(*src));
	return dest;
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
	free_decl_file(&data->psi.file);
}

typedef struct PSI_Parser {
	PSI_DATA_MEMBERS;
	FILE *fp;
	token_t num;
	void *proc;
	unsigned flags, errors, line, col;
	char *cur, *tok, *lim, *eof, *ctx, *mrk, buf[BSIZE];
} PSI_Parser;

static inline size_t PSI_TokenAllocSize(size_t token_len, size_t fname_len) {
	return sizeof(PSI_Token) + token_len + fname_len + sizeof(unsigned) + 2;
}

static inline PSI_Token *PSI_TokenAlloc(PSI_Parser *P) {
	PSI_Token *T;
	size_t token_len, fname_len;
	token_t token_typ;

	if (P->cur < P->tok) {
		return NULL;
	}

	token_typ = P->num;
	token_len = P->cur - P->tok;
	fname_len = strlen(P->psi.file.fn);

	T = calloc(1, PSI_TokenAllocSize(token_len, fname_len));
	T->type = token_typ;
	T->size = token_len;
	T->text = &T->buf[0];
	T->file = &T->buf[token_len + 1];
	T->line = (void *) &T->buf[fname_len + token_len + 2];

	memcpy(T->text, P->tok, token_len);
	memcpy(T->file, P->psi.file.fn, fname_len);
	memcpy(T->line, &P->line, sizeof(unsigned));

	return T;
}

static inline PSI_Token *PSI_TokenCopy(PSI_Token *src) {
	size_t strct_len = PSI_TokenAllocSize(src->size, strlen(src->file));
	PSI_Token *ptr = malloc(strct_len);

	memcpy(ptr, src, strct_len);

	ptr->text = &ptr->buf[0];
	ptr->file = &ptr->buf[ptr->size + 1];

	return ptr;
}

static inline PSI_Token *PSI_TokenCat(unsigned argc, ...) {
	va_list argv;
	unsigned i;
	PSI_Token *T = NULL;

	va_start(argv, argc);
	for (i = 0; i < argc; ++i) {
		PSI_Token *arg = va_arg(argv, PSI_Token *);

		if (T) {
			size_t fname_len = strlen(T->file);

			T = realloc(T, PSI_TokenAllocSize(T->size + arg->size, fname_len));
			memmove(&T->buf[T->size + 1], T->file, fname_len + 1);
			memcpy(T->file - 1, arg->text, arg->size + 1);
			T->file = &T->buf[T->size + 1];
		} else {
			T = PSI_TokenCopy(arg);
			T->type = PSI_T_NAME;
		}
	}
	va_end(argv);

	return T;
}

static inline const char *PSI_TokenLocation(PSI_Token *t) {
	return t ? t->file : "<builtin>:0:0";
}

#define PSI_PARSER_DEBUG 0x1

PSI_Parser *PSI_ParserInit(PSI_Parser *P, const char *filename, psi_error_cb error, unsigned flags);
void PSI_ParserSyntaxError(PSI_Parser *P, const char *fn, size_t ln, const char *msg, ...);
size_t PSI_ParserFill(PSI_Parser *P, size_t n);
token_t PSI_ParserScan(PSI_Parser *P);
void PSI_ParserParse(PSI_Parser *P, PSI_Token *src);
void PSI_ParserDtor(PSI_Parser *P);
void PSI_ParserFree(PSI_Parser **P);

#endif
