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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif
#include "php_psi.h"
#include "data.h"

#include "php_globals.h"
#include "zend_types.h"

#include <dlfcn.h>
#include <ctype.h>

#if PSI_THREADED_PARSER
# include <pthread.h>

static pthread_mutex_t psi_string_mutex = PTHREAD_MUTEX_INITIALIZER;

zend_string *psi_string_init_interned(const char *buf, size_t len, int p)
{
	zend_string *str;

	pthread_mutex_lock(&psi_string_mutex);
	str = zend_string_init_interned(buf, len, p);
	pthread_mutex_unlock(&psi_string_mutex);

	return str;
}

zend_string *psi_new_interned_string(zend_string *str)
{
	zend_string *new_str;

	pthread_mutex_lock(&psi_string_mutex);
	new_str = zend_new_interned_string(str);
	pthread_mutex_unlock(&psi_string_mutex);

	return new_str;
}

#endif

static void psi_data_ctor_internal(struct psi_data *data,
		psi_error_cb error, unsigned flags)
{
	data->error = error;
	data->flags = flags;

	if (data->flags & PSI_DEBUG) {
		int fd = psi_fdopen(getenv("PSI_DEBUG"));

		if (fd > 0) {
			data->debug_fd = fd;
		} else {
			data->debug_fd = STDERR_FILENO;
		}
	}
}

struct psi_data *psi_data_ctor_with_dtors(struct psi_data *data,
		psi_error_cb error, unsigned flags)
{
	if (!data) {
		data = pecalloc(1, sizeof(*data), 1);
	}

	psi_data_ctor_internal(data, error, flags);

	if (!data->file.libnames) {
		data->file.libnames = psi_plist_init((psi_plist_dtor) psi_names_free);
	}
	if (!data->file.dlopened) {
		data->file.dlopened = psi_plist_init((psi_plist_dtor) psi_libs_free);
	}

	if (!data->consts) {
		data->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
	}
	if (!data->types) {
		data->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	if (!data->structs) {
		data->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
	}
	if (!data->unions) {
		data->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
	}
	if (!data->enums) {
		data->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
	}
	if (!data->decls) {
		data->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
	}
	if (!data->vars) {
		data->vars = psi_plist_init((psi_plist_dtor) psi_decl_extvar_free);
	}
	if (!data->impls) {
		data->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	return data;
}

struct psi_data *psi_data_ctor(struct psi_data *data, psi_error_cb error,
		unsigned flags)
{
	if (!data) {
		data = pecalloc(1, sizeof(*data), 1);
	}

	psi_data_ctor_internal(data, error, flags);

	if (!data->file.libnames) {
		data->file.libnames = psi_plist_init(NULL);
	}
	if (!data->file.dlopened) {
		data->file.dlopened = psi_plist_init(NULL);
	}

	if (!data->consts) {
		data->consts = psi_plist_init(NULL);
	}
	if (!data->types) {
		data->types = psi_plist_init(NULL);
	}
	if (!data->structs) {
		data->structs = psi_plist_init(NULL);
	}
	if (!data->unions) {
		data->unions = psi_plist_init(NULL);
	}
	if (!data->enums) {
		data->enums = psi_plist_init(NULL);
	}
	if (!data->decls) {
		data->decls = psi_plist_init(NULL);
	}
	if (!data->vars) {
		data->vars = psi_plist_init(NULL);
	}
	if (!data->impls) {
		data->impls = psi_plist_init(NULL);
	}
	return data;
}

struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src)
{
	if (!dest) {
		dest = pemalloc(sizeof(*dest), 1);
	}
	*dest = *src;
	memset(src, 0, sizeof(*src));
	return dest;
}

void psi_data_dtor(struct psi_data *data)
{
	if (data->debug_fd) {
		close(data->debug_fd);
	}
	if (data->consts) {
		psi_plist_free(data->consts);
	}
	if (data->types) {
		psi_plist_free(data->types);
	}
	if (data->structs) {
		psi_plist_free(data->structs);
	}
	if (data->unions) {
		psi_plist_free(data->unions);
	}
	if (data->enums) {
		psi_plist_free(data->enums);
	}
	if (data->decls) {
		psi_plist_free(data->decls);
	}
	if (data->vars) {
		psi_plist_free(data->vars);
	}
	if (data->impls) {
		psi_plist_free(data->impls);
	}

	psi_decl_file_dtor(&data->file);
}

void psi_data_dump(struct psi_dump *dump, struct psi_data *D)
{
	size_t i = 0;
	zend_string *libname;

	if (D->file.filename) {
		PSI_DUMP(dump, "// filename=%s (%u errors)\n", D->file.filename->val, D->errors);
	}
	while (psi_plist_get(D->file.libnames, i++, &libname)) {
		PSI_DUMP(dump, "#pragma lib \"%s\"\n", libname->val);
	}
	if (psi_plist_count(D->types)) {
		size_t i = 0;
		struct psi_decl_arg *def;

		while (psi_plist_get(D->types, i++, &def)) {
			PSI_DUMP(dump, "typedef ");
			psi_decl_arg_dump(dump, def, 0);
			PSI_DUMP(dump, ";\n");
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->unions)) {
		size_t i = 0;
		struct psi_decl_union *unn;

		while (psi_plist_get(D->unions, i++, &unn)) {
			if (!psi_decl_type_is_anon(unn->name, "union")) {
				psi_decl_union_dump(dump, unn);
				PSI_DUMP(dump, "\n");
			}
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->structs)) {
		size_t i = 0;
		struct psi_decl_struct *strct;

		while (psi_plist_get(D->structs, i++, &strct)) {
			if (!psi_decl_type_is_anon(strct->name, "struct")) {
				psi_decl_struct_dump(dump, strct);
				PSI_DUMP(dump, "\n");
			}
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->enums)) {
		size_t i = 0;
		struct psi_decl_enum *enm;

		while (psi_plist_get(D->enums, i++, &enm)) {
			if (true || !psi_decl_type_is_anon(enm->name, "enum")) {
				psi_decl_enum_dump(dump, enm, 0);
				PSI_DUMP(dump, "\n");
			}
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->consts)) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(D->consts, i++, &c)) {
			psi_const_dump(dump, c);
			PSI_DUMP(dump, "\n");
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->decls)) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(D->decls, i++, &decl)) {
			if (decl->extvar) {
				PSI_DUMP(dump, "/* extvar accessor \n");
			}
			psi_decl_dump(dump, decl);
			if (decl->extvar) {
				PSI_DUMP(dump, " */");
			}
			PSI_DUMP(dump, "\n");
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->vars)) {
		size_t i = 0;
		struct psi_decl_extvar *evar;

		while (psi_plist_get(D->vars, i++, &evar)) {
			psi_decl_extvar_dump(dump, evar);
		}
		PSI_DUMP(dump, "\n");
	}
	if (psi_plist_count(D->impls)) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(D->impls, i++, &impl)) {
			psi_impl_dump(dump, impl);
			PSI_DUMP(dump, "\n");
		}
		PSI_DUMP(dump, "\n");
	}
}
