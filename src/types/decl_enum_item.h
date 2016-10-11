#ifndef _PSI_TYPES_DECL_ENUM_ITEM_H
#define _PSI_TYPES_DECL_ENUM_ITEM_H

#include "token.h"
#include "num_exp.h"

typedef struct decl_enum_item {
	struct psi_token *token;
	char *name;
	num_exp *num;
	num_exp inc;
	struct decl_enum_item *prev;
} decl_enum_item;

decl_enum_item *init_decl_enum_item(const char *name, num_exp *num);
void free_decl_enum_item(decl_enum_item *i);

#endif
