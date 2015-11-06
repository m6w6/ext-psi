
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
#include "parser.h"

void psi_error(int type, const char *msg, ...);

size_t psi_t_alignment(token_t t);
size_t psi_t_size(token_t t);
size_t psi_t_align(token_t t, size_t s);

int psi_internal_type(impl_type *type);
zend_internal_arg_info *psi_internal_arginfo(impl *impl);
size_t psi_num_min_args(impl *impl);

void psi_to_int(zval *return_value, token_t t, impl_val *ret_val, decl_var *var);
void psi_to_double(zval *return_value, token_t t, impl_val *ret_val, decl_var *var);
void psi_to_string(zval *return_value, token_t t, impl_val *ret_val, decl_var *var);

ZEND_RESULT_CODE psi_parse_args(zend_execute_data *execute_data, impl *impl);
void *psi_do_let(decl_arg *darg);
void psi_do_set(zval *return_value, set_func *func, decl_vars *vars);
void psi_do_return(impl *impl, impl_val *ret_val, zval *return_value);
void psi_do_free(free_stmt *fre);
void psi_do_clean(impl *impl);

ZEND_BEGIN_MODULE_GLOBALS(psi)
	char *engine;
	char *directory;
	PSI_Context context;
ZEND_END_MODULE_GLOBALS(psi);

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
