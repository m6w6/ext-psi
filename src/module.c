/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "php_psi_stdinc.h"

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "zend_constants.h"
#include "zend_operators.h"

#include "php_psi.h"
#include "token.h"
#include "parser.h"
#include "cpp.h"

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

//#define ZEND_INI_MH(name) int name(zend_ini_entry *entry, zend_string *new_value, void *mh_arg1, void *mh_arg2, void *mh_arg3, int stage)

static void OnUpdateBlacklist(const char *str, void (*cb)(const char*, size_t))
{
	const char *end;

	do {
		size_t len;

		end = strchr(str, ',');
		if (end) {
			len = end - str;
		} else {
			len = strlen(str);
		}
		if (len) {
			cb(str, len);
		}

		str = end + 1;
	} while (end);
}

static void psi_blacklist_add_decl(const char *pattern, size_t len);
static ZEND_INI_MH(OnUpdateBlacklistedDecls)
{
	OnUpdateBlacklist(new_value->val, psi_blacklist_add_decl);
	return SUCCESS;
}

static void psi_blacklist_add_var(const char *pattern, size_t len);
static ZEND_INI_MH(OnUpdateBlacklistedVars)
{
	OnUpdateBlacklist(new_value->val, psi_blacklist_add_var);
	return SUCCESS;
}

static void OnDisplayBlacklist(struct psi_plist *bl)
{
	size_t i = 0;
	char *item;

	while (psi_plist_get(bl, i++, &item)) {
		if (i > 1) {
			PUTS(",");
		}
		PUTS(item);
	}
}
static ZEND_INI_DISP(OnDisplayBlacklistedDecls)
{
	OnDisplayBlacklist(PSI_G(blacklist).decls);
}
static ZEND_INI_DISP(OnDisplayBlacklistedVars)
{
	OnDisplayBlacklist(PSI_G(blacklist).vars);
}

PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("psi.engine", PSI_ENGINE, PHP_INI_SYSTEM, OnUpdateString, engine, zend_psi_globals, psi_globals)
	STD_PHP_INI_ENTRY("psi.directory", "psi.d", PHP_INI_SYSTEM, OnUpdateString, directory, zend_psi_globals, psi_globals)
	PHP_INI_ENTRY_EX("psi.blacklist.decls", "", PHP_INI_SYSTEM, OnUpdateBlacklistedDecls, OnDisplayBlacklistedDecls)
	PHP_INI_ENTRY_EX("psi.blacklist.vars", "", PHP_INI_SYSTEM, OnUpdateBlacklistedVars, OnDisplayBlacklistedVars)
PHP_INI_END();

static zend_object_handlers psi_object_handlers;
static zend_class_entry *psi_class_entry;

zend_class_entry *psi_object_get_class_entry()
{
	return psi_class_entry;
}

static void psi_object_free(zend_object *o)
{
	psi_object *obj = PSI_OBJ(NULL, o);

	if (obj->data) {
		if (obj->dtor) {
			obj->dtor(obj->data);
		}
		obj->data = NULL;
	}
	zend_object_std_dtor(o);
}

zend_object *psi_object_init_ex(zend_class_entry *ce, void *data, void (*dtor)(void *))
{
	psi_object *o;

	if (!ce) {
		ce = psi_class_entry;
	}

	o = ecalloc(1, sizeof(*o) + zend_object_properties_size(ce));

	o->data = data;
	o->dtor = dtor;

	zend_object_std_init(&o->std, ce);
	object_properties_init(&o->std, ce);
	o->std.handlers = &psi_object_handlers;
	return &o->std;
}

zend_object *psi_object_init(zend_class_entry *ce)
{
	return psi_object_init_ex(ce, NULL, NULL);
}

ZEND_BEGIN_ARG_INFO_EX(ai_psi_dump, 0, 0, 0)
	ZEND_ARG_INFO(0, stream)
ZEND_END_ARG_INFO();
static PHP_FUNCTION(psi_dump)
{
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
	psi_context_dump(PSI_G(context), fd);
}

ZEND_BEGIN_ARG_INFO_EX(ai_psi_validate, 0, 0, 1)
	ZEND_ARG_INFO(0, file)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(1, errcnt)
ZEND_END_ARG_INFO();
static PHP_FUNCTION(psi_validate)
{
	zend_string *file;
	struct psi_parser_input *I;
	struct psi_parser P;
	struct psi_data D = {0};
	struct psi_validate_scope S = {0};
	zend_long flags = 0;
	zval *errcnt = NULL;

#if PHP_DEBUG
	if (psi_check_env("PSI_DEBUG")) {
		flags |= PSI_DEBUG;
	}
#endif

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS(), "P|lz", &file, &flags, &errcnt)) {
		return;
	}

	if (!psi_parser_init(&P, psi_error_wrapper, flags)) {
		RETURN_FALSE;
	}
	if (!(I = psi_parser_open_file(&P, file->val, true))) {
		psi_parser_dtor(&P);
		RETURN_FALSE;
	}

	psi_parser_parse(&P, I);
	psi_data_ctor(&D, P.error, P.flags);
	psi_validate_scope_ctor(&S);
	S.cpp = P.preproc;

	RETVAL_BOOL(psi_validate(&S, &D, PSI_DATA(&P)));

	if (errcnt) {
		ZVAL_DEREF(errcnt);
		convert_to_long(errcnt);
		ZVAL_LONG(errcnt, P.errors);
	}

	psi_validate_scope_dtor(&S);
	psi_data_dtor(&D);
	psi_parser_dtor(&P);
	psi_parser_input_free(&I);
}

ZEND_BEGIN_ARG_INFO_EX(ai_psi_validate_string, 0, 0, 1)
	ZEND_ARG_INFO(0, string)
	ZEND_ARG_INFO(0, flags)
	ZEND_ARG_INFO(1, errcnt)
ZEND_END_ARG_INFO();
static PHP_FUNCTION(psi_validate_string)
{
	zend_string *string;
	struct psi_parser_input *I;
	struct psi_parser P;
	struct psi_data D = {0};
	struct psi_validate_scope S = {0};
	zend_long flags = 0;
	zval *errcnt = NULL;

#if PHP_DEBUG
	if (psi_check_env("PSI_DEBUG")) {
		flags |= PSI_DEBUG;
	}
#endif

	if (SUCCESS != zend_parse_parameters(ZEND_NUM_ARGS(), "S|lz", &string, &flags, &errcnt)) {
		return;
	}

	if (!psi_parser_init(&P, psi_error_wrapper, flags)) {
		RETURN_FALSE;
	}
	if (!(I = psi_parser_open_string(&P, string->val, string->len))) {
		psi_parser_dtor(&P);
		RETURN_FALSE;
	}

	psi_parser_parse(&P, I);
	psi_data_ctor(&D, P.error, P.flags);
	psi_validate_scope_ctor(&S);
	S.cpp = P.preproc;

	RETVAL_BOOL(psi_validate(&S, &D, PSI_DATA(&P)));

	if (errcnt) {
		ZVAL_DEREF(errcnt);
		convert_to_long(errcnt);
		ZVAL_LONG(errcnt, P.errors);
	}

	psi_validate_scope_dtor(&S);
	psi_data_dtor(&D);
	psi_parser_dtor(&P);
	psi_parser_input_free(&I);
}

PHP_MINIT_FUNCTION(psi_cpp);
PHP_MINIT_FUNCTION(psi_builtin);
PHP_MINIT_FUNCTION(psi_context);
static PHP_MINIT_FUNCTION(psi)
{
	zend_class_entry ce = {0};

	REGISTER_INI_ENTRIES();

	zend_register_long_constant(ZEND_STRL("PSI_DEBUG"), PSI_DEBUG, CONST_CS|CONST_PERSISTENT, module_number);
	zend_register_long_constant(ZEND_STRL("PSI_SILENT"), PSI_SILENT, CONST_CS|CONST_PERSISTENT, module_number);

	INIT_NS_CLASS_ENTRY(ce, "psi", "object", NULL);
	psi_class_entry = zend_register_internal_class_ex(&ce, NULL);
	psi_class_entry->create_object = psi_object_init;

	memcpy(&psi_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
	psi_object_handlers.offset = XtOffsetOf(psi_object, std);
	psi_object_handlers.free_obj = psi_object_free;
	psi_object_handlers.clone_obj = NULL;

	if (SUCCESS != PHP_MINIT(psi_builtin)(type, module_number)) {
		return FAILURE;
	}
	if (SUCCESS != PHP_MINIT(psi_cpp)(type, module_number)) {
		return FAILURE;
	}
	if (SUCCESS != PHP_MINIT(psi_context)(type, module_number)) {
		return FAILURE;
	}

	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(psi_cpp);
PHP_MSHUTDOWN_FUNCTION(psi_builtin);
PHP_MSHUTDOWN_FUNCTION(psi_context);
static PHP_MSHUTDOWN_FUNCTION(psi)
{
	PHP_MSHUTDOWN(psi_context)(type, module_number);
	PHP_MSHUTDOWN(psi_cpp)(type, module_number);
	PHP_MSHUTDOWN(psi_builtin)(type, module_number);

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
	php_info_print_table_header(2, "PSI Support", "enabled");
	php_info_print_table_row(2, "Extension Version", PHP_PSI_VERSION);
	php_info_print_table_row(2, "Search Path", PSI_G(search_path));
	php_info_print_table_end();

	php_info_print_table_start();
	php_info_print_table_header(3, "Used Library", "Compiled", "Linked");
	php_info_print_table_row(3, "libffi",
#ifndef PHP_PSI_LIBFFI_VERSION
# define PHP_PSI_LIBFFI_VERSION "unknown"
#endif
#ifdef HAVE_LIBFFI
			PHP_PSI_LIBFFI_VERSION, "unknown"
#else
			"disabled", "disabled"
#endif
	);
	php_info_print_table_row(3, "libjit",
#ifdef HAVE_LIBJIT
			"unknown", "unknown"
#else
			"disabled", "disabled"
#endif
	);

	DISPLAY_INI_ENTRIES();
}

static void ptr_free(void *ptr)
{
	free(*(void **) ptr);
}

static void psi_blacklist_add_decl(const char *pattern, size_t len)
{
	char *tmp = strndup(pattern, len);
	struct psi_plist **decls = &PSI_G(blacklist).decls;

	*decls = psi_plist_add(*decls, &tmp);
}

static void psi_blacklist_add_var(const char *pattern, size_t len)
{
	char *tmp = strndup(pattern, len);
	struct psi_plist **vars = &PSI_G(blacklist).vars;

	*vars = psi_plist_add(*vars, &tmp);
}

static PHP_GINIT_FUNCTION(psi)
{
	char *tmp;
	struct psi_plist **bl_decls = &psi_globals->blacklist.decls;
	struct psi_plist **bl_vars = &psi_globals->blacklist.vars;

	*bl_decls = psi_plist_init(ptr_free);
	*bl_vars = psi_plist_init(ptr_free);

#define BL_ADD(D, d) \
	tmp = strdup(d); \
	*D = psi_plist_add(*D, &tmp)
#define BL_DECL_ADD(d) BL_ADD(bl_decls, d)
#define BL_VAR_ADD(d) BL_ADD(bl_vars, d)

	BL_DECL_ADD("dlsym");
	BL_DECL_ADD("alloca");
	BL_DECL_ADD("atexit");
	BL_DECL_ADD("at_quick_exit");

	/* missing */
	BL_DECL_ADD("_IO_cookie_init");
	BL_DECL_ADD("bindresvport6");

	/* va_list as arg */
	BL_DECL_ADD("*v*printf");
	BL_DECL_ADD("*v*scanf");
	BL_DECL_ADD("vsyslog");

	/* LFS/LFO for 32bit */
	BL_DECL_ADD("*stat*64");
	BL_DECL_ADD("*glob*64");
	/* Hurd only */
	BL_DECL_ADD("getumask");

	/* using hidden structs */
	BL_VAR_ADD("_IO_2_*");
}

static PHP_GSHUTDOWN_FUNCTION(psi)
{
	psi_plist_free(psi_globals->blacklist.decls);
}

static const zend_function_entry psi_functions[] = {
	PHP_FE(psi_dump, ai_psi_dump)
	PHP_FE(psi_validate, ai_psi_validate)
	PHP_FE(psi_validate_string, ai_psi_validate_string)
	PHP_FE_END
};

static const zend_module_dep psi_deps[] = {
	ZEND_MOD_REQUIRED("standard")
	{0}
};

zend_module_entry psi_module_entry = {
	STANDARD_MODULE_HEADER_EX,
	NULL,
	psi_deps,
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
	ZEND_MODULE_GLOBALS(psi),
	PHP_GINIT(psi),
	PHP_GSHUTDOWN(psi),
	NULL, /* post-deactivate */
	STANDARD_MODULE_PROPERTIES_EX
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
