
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <jit/jit.h>
#include <dirent.h>
#include <fnmatch.h>

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_scandir.h"

#include "php_psi.h"

#include "parser.h"
#include "validator.h"
#include "compiler.h"

ZEND_DECLARE_MODULE_GLOBALS(psi);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("psi.directory", "psis", PHP_INI_ALL, OnUpdateString, directory, zend_psi_globals, psi_globals)
PHP_INI_END();

static void psi_error(int type, const char *msg, ...)
{
	char buf[0x1000];
	va_list argv;

	va_start(argv, msg);
	vslprintf(buf, 0x1000, msg, argv);
	va_end(argv);

	php_error(type, buf);
}

static int psi_select_dirent(const struct dirent *entry)
{
#ifndef FNM_CASEFOLD
#define FNM_CASEFOLD 0
#endif
	return 0 == fnmatch("*.psi", entry->d_name, FNM_CASEFOLD);
}

PHP_MINIT_FUNCTION(psi)
{
	jit_context_t ctx;
	int i, n;
	struct dirent **entries = NULL;

	REGISTER_INI_ENTRIES();

	jit_init();

	if (!(ctx = jit_context_create())) {
		zend_error(E_WARNING, "Could not initialize libjit!");
		return FAILURE;
	}

	PSI_G(context) = ctx;

	n = php_scandir(PSI_G(directory), &entries, psi_select_dirent, alphasort);
	if (n < 0) {
		php_error(E_WARNING, "Failed to scan PSI directory '%s'", PSI_G(directory));
	} else for (i = 0; i < n; ++i) {
		char psi[MAXPATHLEN];
		PSI_Parser P;
		PSI_Validator V;

		if (MAXPATHLEN <= slprintf(psi, MAXPATHLEN, "%s/%s", PSI_G(directory), entries[i]->d_name)) {
			php_error(E_WARNING, "Path to PSI file too long: %s/%s",
				PSI_G(directory), entries[i]->d_name);
		}
		if (!PSI_ParserInit(&P, psi, psi_error, 0)) {
			php_error(E_WARNING, "Failed to init PSI parser (%s): %s",
				psi, strerror(errno));
			continue;
		}

		while (-1 != PSI_ParserScan(&P)) {
			PSI_ParserParse(&P, PSI_TokenAlloc(&P));
		};
		PSI_ParserParse(&P, NULL);

		if (!PSI_ValidatorInit(&V, &P)) {
			php_error(E_WARNING, "Failed to init PSI validator");
			break;
		}
		PSI_ParserDtor(&P);

		if (PSI_ValidatorValidate(&V)) {
			PSI_Compiler C;

			jit_context_build_start(ctx);
			if (PSI_CompilerInit(&C, &V, ctx)) {
				zend_function_entry *closures = PSI_CompilerCompile(&C);

				if (closures && SUCCESS != zend_register_functions(NULL, closures, NULL, MODULE_PERSISTENT)) {
					psi_error(E_WARNING, "Failed to register functions!");
				}
				//PSI_CompilerDtor(&C);
			}
			jit_context_build_end(ctx);
		}
		PSI_ValidatorDtor(&V);
	}
	if (entries) {
		for (i = 0; i < n; ++i) {
			free(entries[i]);
		}
		free(entries);
	}
	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(psi)
{
	jit_context_t ctx = PSI_G(context);
	jit_context_destroy(ctx);

	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(psi)
{
#if defined(COMPILE_DL_PSI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(psi)
{
	return SUCCESS;
}
/* }}} */

PHP_MINFO_FUNCTION(psi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psi support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
const zend_function_entry psi_functions[] = {
	PHP_FE_END
};

zend_module_entry psi_module_entry = {
	STANDARD_MODULE_HEADER,
	"psi",
	psi_functions,
	PHP_MINIT(psi),
	PHP_MSHUTDOWN(psi),
	PHP_RINIT(psi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(psi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(psi),
	PHP_PSI_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PSI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(psi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
