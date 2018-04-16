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
#include "data.h"

#include "php_globals.h"

#include <dlfcn.h>
#include <ctype.h>

struct psi_data *psi_data_ctor_with_dtors(struct psi_data *data,
		psi_error_cb error, unsigned flags)
{
	if (!data) {
		data = calloc(1, sizeof(*data));
	}

	data->error = error;
	data->flags = flags;

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
	if (!data->libs) {
		data->libs = psi_plist_init((psi_plist_dtor) psi_libs_free);
	}
	return data;
}

struct psi_data *psi_data_ctor(struct psi_data *data, psi_error_cb error,
		unsigned flags)
{
	if (!data) {
		data = calloc(1, sizeof(*data));
	}

	data->error = error;
	data->flags = flags;

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
	if (!data->libs) {
		data->libs = psi_plist_init(NULL);
	}
	return data;
}

struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src)
{
	if (!dest) {
		dest = malloc(sizeof(*dest));
	}
	*dest = *src;
	memset(src, 0, sizeof(*src));
	return dest;
}

void psi_data_dtor(struct psi_data *data)
{
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
	if (data->libs) {
		psi_plist_free(data->libs);
	}

	psi_decl_file_dtor(&data->file);
}

void psi_data_dump(int fd, struct psi_data *D)
{
	if (D->file.fn) {
		dprintf(fd, "// filename=%s (%u errors)\n", D->file.fn, D->errors);
		if (D->file.ln) {
			dprintf(fd, "lib \"%s\";\n", D->file.ln);
		}
	} else {
		dprintf(fd, "// builtin predef\n");
	}
	if (psi_plist_count(D->types)) {
		size_t i = 0;
		struct psi_decl_arg *def;

		while (psi_plist_get(D->types, i++, &def)) {
			dprintf(fd, "typedef ");
			psi_decl_arg_dump(fd, def, 0);
			dprintf(fd, ";\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->unions)) {
		size_t i = 0;
		struct psi_decl_union *unn;

		while (psi_plist_get(D->unions, i++, &unn)) {
			if (!psi_decl_type_is_anon(unn->name, "union")) {
				psi_decl_union_dump(fd, unn);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->structs)) {
		size_t i = 0;
		struct psi_decl_struct *strct;

		while (psi_plist_get(D->structs, i++, &strct)) {
			if (!psi_decl_type_is_anon(strct->name, "struct")) {
				psi_decl_struct_dump(fd, strct);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->enums)) {
		size_t i = 0;
		struct psi_decl_enum *enm;

		while (psi_plist_get(D->enums, i++, &enm)) {
			if (!psi_decl_type_is_anon(enm->name, "enum")) {
				psi_decl_enum_dump(fd, enm, 0);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->consts)) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(D->consts, i++, &c)) {
			psi_const_dump(fd, c);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->decls)) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(D->decls, i++, &decl)) {
			psi_decl_dump(fd, decl);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->vars)) {
		size_t i = 0;
		struct psi_decl_extvar *evar;

		while (psi_plist_get(D->vars, i++, &evar)) {
			psi_decl_extvar_dump(fd, evar);
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->impls)) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(D->impls, i++, &impl)) {
			psi_impl_dump(fd, impl);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
}
