#ifndef PHP_PSI_H
#define PHP_PSI_H

extern zend_module_entry psi_module_entry;
#define phpext_psi_ptr &psi_module_entry

#define PHP_PSI_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_PSI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PSI_API __attribute__ ((visibility("default")))
#else
#	define PHP_PSI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "context.h"

void psi_error_wrapper(void *context, PSI_Token *t, int type, const char *msg, ...);
void psi_error(int type, const char *fn, unsigned ln, const char *msg, ...);
void psi_verror(int type, const char *fn, unsigned ln, const char *msg, va_list argv);

static inline int psi_check_env(const char *var) {
	char *set = getenv(var);
	return (set && *set && '0' != *set);
}

typedef struct psi_object {
	void *data;
	size_t size;
	zend_object std;
} psi_object;

static inline psi_object *PSI_OBJ(zval *zv, zend_object *zo) {
	if (zv) {
		zo = Z_OBJ_P(zv);
	}
	return (void *) (((char *) zo) - zo->handlers->offset);
}

PHP_PSI_API zend_class_entry *psi_object_get_class_entry();

ZEND_BEGIN_MODULE_GLOBALS(psi)
	char *engine;
	char *directory;
	PSI_Context context;
ZEND_END_MODULE_GLOBALS(psi);

ZEND_EXTERN_MODULE_GLOBALS(psi);

#define PSI_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(psi, v)

#if defined(ZTS) && defined(COMPILE_DL_PSI)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_PSI_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
