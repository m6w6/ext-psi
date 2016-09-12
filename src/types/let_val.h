#ifndef _PSI_TYPES_LET_VAL_H
#define _PSI_TYPES_LET_VAL_H


enum let_val_kind {
	PSI_LET_NULL,
	PSI_LET_NUMEXP,
	PSI_LET_CALLOC,
	PSI_LET_CALLBACK,
	PSI_LET_FUNC,
	PSI_LET_TMP,
};
#define PSI_LET_REFERENCE 0x1;
typedef struct let_val {
	enum let_val_kind kind;
	decl_var *var;
	union {
		num_exp *num;
		let_calloc *alloc;
		let_callback *callback;
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
	case PSI_LET_CALLBACK:
		let->data.callback = data;
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
	case PSI_LET_CALLBACK:
		free_let_callback(let->data.callback);
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

#endif
