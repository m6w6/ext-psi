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
#include "data.h"
#include "dl.h"

void psi_decl_file_dtor(struct psi_decl_file *file)
{
	if (file->libnames) {
		psi_plist_free(file->libnames);
	}
	if (file->dlopened) {
		psi_plist_free(file->dlopened);
	}
	if (file->filename) {
		zend_string_release(file->filename);
	}
	memset(file, 0, sizeof(*file));
}

static inline bool validate_lib(struct psi_data *dst, const zend_string *libname, void **dlopened)
{
	char lib[PATH_MAX];
	size_t len = PATH_MAX;

	if (!libname) {
		/* FIXME: assume stdlib */
		return true;
	}

	if (PATH_MAX == psi_dlname(&lib, &len, libname->val)) {
		dst->error(dst, NULL, PSI_WARNING, "Library name too long: '%s'",
				libname->val);
		return false;
	}

	if (!(*dlopened = psi_dlopen(lib))) {
		dst->error(dst, NULL, PSI_WARNING, "Could not open library '%s': %s",
				libname->val, psi_dlerror());
		return false;
	}

	return true;
}

bool psi_decl_file_validate(struct psi_data *dst, struct psi_data *src)
{
	size_t i = 0;
	zend_string *libname;
	void *dlopened;

	while (psi_plist_get(src->file.libnames, i++, &libname)) {
		if (!validate_lib(dst, libname, &dlopened)) {
			return false;
		}

		dst->file.libnames = psi_plist_add(dst->file.libnames, &libname);
		dst->file.dlopened = psi_plist_add(dst->file.dlopened, &dlopened);
	}

	if (src->file.filename) {
		dst->file.filename = zend_string_copy(src->file.filename);
	}
	return true;
}

void psi_libs_free(void **dlopened) {
	if (*dlopened) {
		psi_dlclose(*dlopened);
		*dlopened = NULL;
	}
}

void psi_names_free(zend_string **name) {
	if (*name) {
		zend_string_release(*name);
		*name = NULL;
	}
}
