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

#include <dlfcn.h>

void psi_decl_file_dtor(struct psi_decl_file *file)
{
	if (file->ln) {
		free(file->ln);
	}
	if (file->fn) {
		free(file->fn);
	}
	memset(file, 0, sizeof(*file));
}

bool psi_decl_file_validate(struct psi_data *dst, struct psi_data *src, void **dlopened)
{
	char lib[MAXPATHLEN];
	const char *ptr = src->file.ln;
	size_t len;

	if (!ptr) {
		/* FIXME: assume stdlib */
		return true;
	} else if (!strchr(ptr, '/')) {
		len = snprintf(lib, MAXPATHLEN, "lib%s.%s", ptr, PHP_PSI_SHLIB_SUFFIX);
		if (MAXPATHLEN == len) {
			dst->error(dst, NULL, PSI_WARNING, "Library name too long: '%s'",
					ptr);
		}
		lib[len] = 0;
		ptr = lib;
	}
	if (!(*dlopened = dlopen(ptr, RTLD_LAZY | RTLD_LOCAL))) {
		dst->error(dst, NULL, PSI_WARNING, "Could not open library '%s': %s.",
				src->file.ln, dlerror());
		return false;
	}

	if (!dst->libs) {
		dst->libs = psi_plist_init((psi_plist_dtor) psi_libs_free);
	}
	dst->libs = psi_plist_add(dst->libs, dlopened);

	return true;
}

void psi_libs_free(void **dlopened) {
	if (*dlopened) {
		dlclose(*dlopened);
	}
}
