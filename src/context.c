#include <sys/param.h>
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_scandir.h"
#include "context.h"
#include "parser.h"
#include "validator.h"

#define psi_predef_count(of) ((sizeof(psi_predef ##of## s)/sizeof(psi_predef ##of))-1)
typedef struct psi_predef_type {
	token_t type_tag;
	const char *type_name;
	const char *alias;
} psi_predef_type;
static const psi_predef_type psi_predef_types[] = {
	PHP_PSI_TYPES{0}
};
#define psi_predef_type_count() psi_predef_count(_type)

typedef struct psi_predef_const {
	token_t type_tag;
	const char *type_name;
	const char *name;
	const char *val_text;
	token_t val_type_tag;
} psi_predef_const;
static const psi_predef_const psi_predef_consts[] = {
	PHP_PSI_CONSTS{0}
};
#define psi_predef_const_count() psi_predef_count(_const)

typedef struct psi_predef_struct_member {
	token_t type_tag;
	const char *type_name;
	const char *name;
	size_t off;
	size_t len;
	size_t pointer_level;
	size_t array_size;
} psi_predef_struct_member;
#define PSI_PREDEF_STRUCT_MEMBERS 32
typedef struct psi_predef_struct {
	const char *name;
	psi_predef_struct_member members[PSI_PREDEF_STRUCT_MEMBERS];
} psi_predef_struct;
static const psi_predef_struct psi_predef_structs[] = {
	PHP_PSI_STRUCTS{0}
};
#define psi_predef_struct_count() psi_predef_count(_struct)

PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error)
{
	size_t i, j;
	PSI_Data data;

	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	C->error = error;
	C->ops = ops;
	ops->init(C);

	memset(&data, 0, sizeof(data));
	for (i = 0; i < psi_predef_type_count(); ++i) {
		const psi_predef_type *pre = &psi_predef_types[i];
		decl_type *type = init_decl_type(pre->type_tag, pre->type_name);
		decl_typedef *def = init_decl_typedef(pre->alias, type);

		data.defs = add_decl_typedef(data.defs, def);
	}
	for (i = 0; i < psi_predef_const_count(); ++i) {
		const psi_predef_const *pre = &psi_predef_consts[i];
		impl_def_val *val = init_impl_def_val(pre->val_type_tag, pre->val_text);
		const_type *type = init_const_type(pre->type_tag, pre->type_name);
		constant *constant = init_constant(type, pre->name, val);

		data.consts = add_constant(data.consts, constant);
	}
	for (i = 0; i < psi_predef_struct_count(); ++i) {
		const psi_predef_struct *pre = &psi_predef_structs[i];
		decl_args *dargs = init_decl_args(NULL);

		for (j = 0; j < PSI_PREDEF_STRUCT_MEMBERS; ++j) {
			const psi_predef_struct_member *member = &pre->members[j];
			decl_type *type;
			decl_var *dvar;

			if (!member->name) {
				break;
			}

			type = init_decl_type(member->type_tag, member->type_name);
			dvar = init_decl_var(member->name, member->pointer_level, member->array_size);
			dargs = add_decl_arg(dargs, init_decl_arg(type, dvar));
		}

		data.structs = add_decl_struct(data.structs,
				init_decl_struct(pre->name, dargs));
	}
	return C;
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
#define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}


void PSI_ContextBuild(PSI_Context *C, const char *path)
{
	int i, n;
	struct dirent **entries = NULL;

	n = php_scandir(path, &entries, psi_select_dirent, alphasort);

	if (n < 0) {
		return;
	} else for (i = 0; i < n; ++i) {
		char psi[MAXPATHLEN];
		PSI_Parser P;
		PSI_Validator V;

		if (MAXPATHLEN <= slprintf(psi, MAXPATHLEN, "%s/%s", path, entries[i]->d_name)) {
			C->error(PSI_WARNING, "Path to PSI file too long: %s/%s",
				path, entries[i]->d_name);
		}
		if (!PSI_ParserInit(&P, psi, C->error, 0)) {
			C->error(PSI_WARNING, "Failed to init PSI parser (%s): %s",
				psi, strerror(errno));
			continue;
		}

		while (-1 != PSI_ParserScan(&P)) {
			PSI_ParserParse(&P, PSI_TokenAlloc(&P));
		};
		PSI_ParserParse(&P, NULL);

		if (!PSI_ValidatorInit(&V, &P)) {
			C->error(PSI_WARNING, "Failed to init PSI validator");
			break;
		}
		PSI_ParserDtor(&P);

		if (PSI_ValidatorValidate(&V)) {
			zend_function_entry *closures;

			closures = PSI_ContextCompile(C, (PSI_Data *) &V);
			if (closures && SUCCESS != zend_register_functions(NULL, closures, NULL, MODULE_PERSISTENT)) {
				C->error(PSI_WARNING, "Failed to register functions!");
			}
		}
		PSI_ValidatorDtor(&V);
	}
	if (entries) {
		for (i = 0; i < n; ++i) {
			free(entries[i]);
		}
		free(entries);
	}

}

zend_function_entry *PSI_ContextCompile(PSI_Context *C, PSI_Data *D)
{
	size_t i, count = C->count++;
	zend_function_entry *zfe;

	if (D->consts) {
		zend_constant zc;

		zc.flags = CONST_PERSISTENT|CONST_CS;
		zc.module_number = EG(current_module)->module_number;

		for (i = 0; i < D->consts->count; ++i) {
			constant *c = D->consts->list[i];

			zc.name = zend_string_init(c->name + (c->name[0] == '\\'), strlen(c->name) - (c->name[0] == '\\'), 1);
			ZVAL_NEW_STR(&zc.value, zend_string_init(c->val->text, strlen(c->val->text), 1));

			switch (c->type->type) {
			case PSI_T_BOOL:
				convert_to_boolean(&zc.value);
				break;
			case PSI_T_INT:
				convert_to_long(&zc.value);
				break;
			case PSI_T_FLOAT:
				convert_to_double(&zc.value);
				break;
			}
			zend_register_constant(&zc);
		}
	}

	C->data = realloc(C->data, C->count * sizeof(*C->data));
	PSI_DataExchange(&C->data[count], D);

	zfe = C->ops->compile(C, &C->data[count]);

	C->closures = realloc(C->closures, C->count * sizeof(*C->closures));
	C->closures[count] = zfe;

	return zfe;
}

void PSI_ContextDtor(PSI_Context *C)
{
	size_t i;

	C->ops->dtor(C);

	for (i = 0; i < C->count; ++i) {
		PSI_DataDtor(&C->data[i]);
		if (C->closures[i]){
			free(C->closures[i]);
		}
	}
	free(C->data);
	free(C->closures);

	memset(C, 0, sizeof(*C));
}

void PSI_ContextFree(PSI_Context **C)
{
	if (*C) {
		PSI_ContextDtor(*C);
		free(*C);
		*C = NULL;
	}
}
