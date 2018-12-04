/*******************************************************************************
 Copyright (c) 2018, Michael Wallner <mike@php.net>.
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

#ifndef PSI_DLSYM_H
#define PSI_DLSYM_H

#include <stddef.h>
#include <dlfcn.h>

#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
#ifndef RTLD_DEFAULT
# define RTLD_DEFAULT ((void *) 0)
#endif

#include "plist.h"

static inline void *psi_dlsym(struct psi_plist *dllist, const char *name, const char *redir)
{
	void *dl, *sym = NULL;
	const char *test = redir ?: name;

again:
	if (dllist) {
		size_t i = 0;

		while (!sym && psi_plist_get(dllist, i++, &dl)) {
			sym = dlsym(dl, test);
		}
	}
	if (!sym) {
		sym = dlsym(RTLD_DEFAULT, test);
	}
	if (!sym && test == redir) {
		test = name;
		goto again;
	}

	return sym;
}

static inline size_t psi_dlname(char (*buf)[], size_t *len, const char *libname)
{
	if (strchr(libname, '/')) {
		return snprintf(*buf, *len, "%s", libname);
	} else {
		return snprintf(*buf, *len, "lib%s.%s", libname, PHP_PSI_SHLIB_SUFFIX);
	}
}

static inline void *psi_dlopen(const char *libname)
{
	return dlopen(libname, RTLD_LAZY | RTLD_LOCAL);
}

static inline void psi_dlclose(void *dl)
{
	dlclose(dl);
}

static inline char *psi_dlerror()
{
	return dlerror();
}

#endif /* PSI_DLSYM_H */
