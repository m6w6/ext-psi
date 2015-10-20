
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "php_psi.h"

#include "libjit.h"

ZEND_DECLARE_MODULE_GLOBALS(psi);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("psi.directory", "psis", PHP_INI_ALL, OnUpdateString, directory, zend_psi_globals, psi_globals)
PHP_INI_END();

void psi_error(int type, const char *msg, ...)
{
	char buf[0x1000];
	va_list argv;

	va_start(argv, msg);
	vslprintf(buf, 0x1000, msg, argv);
	va_end(argv);

	php_error(type, buf);
}

PHP_MINIT_FUNCTION(psi)
{
	REGISTER_INI_ENTRIES();

	PSI_ContextInit(&PSI_G(context), PSI_Libjit(), psi_error);
	PSI_ContextBuild(&PSI_G(context), PSI_G(directory));

	return SUCCESS;
}
PHP_MSHUTDOWN_FUNCTION(psi)
{
	PSI_ContextDtor(&PSI_G(context));

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
