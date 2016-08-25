#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_constants.h"
#include "zend_operators.h"

#include "php_psi.h"
#include "token.h"
#include "parser.h"

#if HAVE_LIBJIT
# include "libjit.h"
# ifndef HAVE_LIBFFI
#  define PSI_ENGINE "jit"
# endif
#endif
#if HAVE_LIBFFI
# include "libffi.h"
# define PSI_ENGINE "ffi"
#endif

ZEND_DECLARE_MODULE_GLOBALS(psi);

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("psi.engine", PSI_ENGINE, PHP_INI_SYSTEM, OnUpdateString, engine, zend_psi_globals, psi_globals)
	STD_PHP_INI_ENTRY("psi.directory", "psi.d", PHP_INI_SYSTEM, OnUpdateString, directory, zend_psi_globals, psi_globals)
PHP_INI_END();

static zend_object_handlers psi_object_handlers;
static zend_class_entry *psi_class_entry;

zend_class_entry *psi_object_get_class_entry()
{
	return psi_class_entry;
}

void psi_error_wrapper(void *context, struct psi_token *t, int type, const char *msg, ...)
{
	va_list argv;
	const char *fn = NULL;
	unsigned ln = 0;

	if (context) {
		if (PSI_DATA(context)->flags & PSI_PARSER_SILENT) {
			return;
		}
	}

	if (t) {
		fn = t->file;
		ln = t->line;
	} else if (zend_is_executing()) {
		fn = zend_get_executed_filename();
		ln = zend_get_executed_lineno();
	} else if (zend_is_compiling()) {
		fn = zend_get_compiled_filename()->val;
		ln = zend_get_compiled_lineno();
	}

	va_start(argv, msg);
	psi_verror(type, fn, ln, msg, argv);
	va_end(argv);
}

void psi_error(int type, const char *fn, unsigned ln, const char *msg, ...)
{
	va_list argv;

	va_start(argv, msg);
	psi_verror(type, fn, ln, msg, argv);
	va_end(argv);
}

void psi_verror(int type, const char *fn, unsigned ln, const char *msg, va_list argv)
{
	zend_error_cb(type, fn, ln, msg, argv);
}

static void psi_object_free(zend_object *o)
{
	psi_object *obj = PSI_OBJ(NULL, o);

	if (obj->data) {
		/* FIXME: how about registering a destructor?
		// free(obj->data); */
		obj->data = NULL;
	}
	zend_object_std_dtor(o);
}

static zend_object *psi_object_init(zend_class_entry *ce)
{
	psi_object *o = ecalloc(1, sizeof(*o) + zend_object_properties_size(ce));

	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &psi_object_handlers;
	return &o->std;
}

ZEND_BEGIN_ARG_INFO_EX(ai_psi_dump, 0, 0, 0)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO();
static PHP_FUNCTION(psi_dump) {
	php_stream *s;
	zval *r = NULL;
	int fd = STDOUT_FILENO;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS(), "|r!", &r)) {
		return;
	}
	if (r) {
		php_stream_from_zval(s, r);

		if (SUCCESS != php_stream_cast(s, PHP_STREAM_AS_FD | PHP_STREAM_CAST_INTERNAL, (void **)&fd, 1)) {
			RETURN_FALSE;
		}
	}
	psi_context_dump(&PSI_G(context), fd);
}

ZEND_BEGIN_ARG_INFO_EX(ai_psi_validate, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO();
static PHP_FUNCTION(psi_validate) {
	zend_string *file;
	struct psi_parser P;

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS(), "P", &file)) {
		return;
	}

	if (!psi_parser_init(&P, file->val, psi_error_wrapper, 0)) {
		RETURN_FALSE;
	}

	while (0 < psi_parser_scan(&P)) {
		psi_parser_parse(&P, psi_token_alloc(&P));
		if (P.num == PSI_T_EOF) {
			break;
		}
	}
	psi_parser_parse(&P, NULL);

	if (0 == psi_context_validate_data(NULL, PSI_DATA(&P)) && !P.errors) {
		RETVAL_TRUE;
	} else {
		RETVAL_FALSE;
	}
	psi_parser_dtor(&P);
}

static PHP_MINIT_FUNCTION(psi)
{
	struct psi_context_ops *ops = NULL;
	zend_class_entry ce = {0};
	unsigned flags = psi_check_env("PSI_DEBUG") ? PSI_PARSER_DEBUG : (
			psi_check_env("PSI_SILENT") ? PSI_PARSER_SILENT : 0);

	REGISTER_INI_ENTRIES();

	INIT_NS_CLASS_ENTRY(ce, "psi", "object", NULL);
	psi_class_entry = zend_register_internal_class_ex(&ce, NULL);
	psi_class_entry->create_object = psi_object_init;

	memcpy(&psi_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	psi_object_handlers.offset = XtOffsetOf(psi_object, std);
	psi_object_handlers.free_obj = psi_object_free;
	psi_object_handlers.clone_obj = NULL;

#ifdef HAVE_LIBJIT
	if (!strcasecmp(PSI_G(engine), "jit")) {
		ops = psi_libjit_ops();
	} else
#endif
#ifdef HAVE_LIBFFI
		ops = psi_libffi_ops();
#endif

	if (!ops) {
		php_error(E_WARNING, "No PSI engine found");
		return FAILURE;
	}

	psi_context_init(&PSI_G(context), ops, psi_error_wrapper, flags);
	psi_context_build(&PSI_G(context), PSI_G(directory));

	if (psi_check_env("PSI_DUMP")) {
		psi_context_dump(&PSI_G(context), STDOUT_FILENO);
	}

	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(psi)
{
	psi_context_dtor(&PSI_G(context));

	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}

#if defined(COMPILE_DL_PSI) && defined(ZTS)
static PHP_RINIT_FUNCTION(psi)
{
	ZEND_TSRMLS_CACHE_UPDATE();
	return SUCCESS;
}
#endif

static PHP_MINFO_FUNCTION(psi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "psi support", "enabled");
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

static const zend_function_entry psi_functions[] = {
	PHP_FE(psi_dump, ai_psi_dump)
	PHP_FE(psi_validate, ai_psi_validate)
	PHP_FE_END
};

zend_module_entry psi_module_entry = {
	STANDARD_MODULE_HEADER,
	"psi",
	psi_functions,
	PHP_MINIT(psi),
	PHP_MSHUTDOWN(psi),
#if defined(COMPILE_DL_PSI) && defined(ZTS)
	PHP_RINIT(psi),		/* Replace with NULL if there's nothing to do at request start */
#else
	NULL,
#endif
	NULL,
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
