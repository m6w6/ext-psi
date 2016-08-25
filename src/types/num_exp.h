#ifndef _PSI_TYPES_NUM_EXP
#define _PSI_TYPES_NUM_EXP

typedef struct num_exp {
	struct psi_token *token;
	token_t t;
	union {
		char *numb;
		constant *cnst;
		decl_var *dvar;
		struct decl_enum_item *enm;
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

static inline num_exp *copy_num_exp(num_exp *exp) {
	decl_var *dvar;
	num_exp *num = calloc(1, sizeof(*num));

	memcpy(num, exp, sizeof(*num));

	if (num->token) {
		num->token = psi_token_copy(num->token);
	}
	if (num->operand) {
		num->operand = copy_num_exp(num->operand);
	}
	switch (num->t) {
	case PSI_T_NUMBER:
	case PSI_T_NSNAME:
		num->u.numb = strdup(num->u.numb);
		break;
	case PSI_T_NAME:
		dvar = init_decl_var(num->u.dvar->name, num->u.dvar->pointer_level, num->u.dvar->array_size);
		dvar->arg = num->u.dvar->arg;
		if (num->u.dvar->token) {
			dvar->token = psi_token_copy(num->u.dvar->token);
		}
		num->u.dvar = dvar;
		break;
	}
	return num;
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
	case PSI_T_ENUM:
		break;
	EMPTY_SWITCH_DEFAULT_CASE();
	}
	if (exp->operand) {
		free_num_exp(exp->operand);
	}
	free(exp);
}

#endif
