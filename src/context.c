#include <sys/param.h>
#include <dirent.h>
#include <fnmatch.h>
#include <errno.h>

#include "php.h"
#include "php_scandir.h"
#include "context.h"
#include "parser.h"
#include "validator.h"

PSI_Context *PSI_ContextInit(PSI_Context *C, PSI_ContextOps *ops, PSI_ContextErrorFunc error)
{
	if (!C) {
		C = malloc(sizeof(*C));
	}
	memset(C, 0, sizeof(*C));

	C->error = error;
	C->ops = ops;
	ops->init(C);

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
		C->error(PSI_WARNING, "Failed to scan PSI directory '%s'", path);
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

			if (V.consts) {
				zend_constant zc;

				zc.flags = CONST_PERSISTENT|CONST_CS;
				zc.module_number = EG(current_module)->module_number;

				for (i = 0; i < V.consts->count; ++i) {
					constant *c = V.consts->list[i];

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
	size_t count = C->count++;
	zend_function_entry *zfe;

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
			free(C->closures[i]->arg_info);
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

