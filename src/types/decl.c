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

#include <dlfcn.h>
#include "data.h"

#define PSI_FUNC_REDIRS
#include "php_psi_posix.h"

struct psi_decl *psi_decl_init(struct psi_decl_arg *func, struct psi_plist *args)
{
	struct psi_decl *d = calloc(1, sizeof(*d));

	d->func = func;
	d->args = args;

	return d;
}

void psi_decl_free(struct psi_decl **d_ptr)
{
	if (*d_ptr) {
		struct psi_decl *d = *d_ptr;

		*d_ptr = NULL;

		psi_decl_abi_free(&d->abi);
		psi_decl_arg_free(&d->func);
		if (d->args) {
			psi_plist_free(d->args);
		}
		free(d);
	}
}

void psi_decl_dump(int fd, struct psi_decl *decl)
{
	psi_decl_abi_dump(fd, decl->abi);
	dprintf(fd, " ");
	psi_decl_arg_dump(fd, decl->func, 0);
	dprintf(fd, "(");
	if (decl->args) {
		size_t i;
		struct psi_decl_arg *arg;

		for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
			if (i) {
				dprintf(fd, ", ");
			}
			psi_decl_arg_dump(fd, arg, 0);
		}
		if (decl->varargs) {
			dprintf(fd, ", ...");
		}
	}
	dprintf(fd, ");");
}

static inline bool psi_decl_validate_func(struct psi_data *data,
		struct psi_decl *decl, struct psi_decl_arg *func, void *dl)
{
	struct psi_func_redir *redir;

	if (!strcmp(func->var->name, "dlsym")) {
		data->error(data, func->token, PSI_WARNING,
				"Cannot dlsym dlsym (sic!)");
		return false;
	}

	for (redir = &psi_func_redirs[0]; redir->name; ++redir) {
		if (!strcmp(func->var->name, redir->name)) {
			decl->sym = redir->func;
		}
	}
	if (!decl->sym) {
#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
#ifndef RTLD_DEFAULT
# define RTLD_DEFAULT ((void *) 0)
#endif
		decl->sym = dlsym(dl ?: RTLD_DEFAULT, func->var->name);
		if (!decl->sym) {
			data->error(data, func->token, PSI_WARNING,
					"Failed to locate symbol '%s': %s", func->var->name,
					dlerror() ?: "not found");
			return false;
		}
	}
	return true;
}

bool psi_decl_validate(struct psi_data *data, struct psi_decl *decl, void *dl,
		struct psi_validate_stack *type_stack)
{
	if (!psi_decl_validate_nodl(data, decl, type_stack)) {
		return false;
	}
	if (!psi_decl_validate_func(data, decl, decl->func, dl)) {
		return false;
	}

	return true;
}

bool psi_decl_validate_nodl(struct psi_data *data, struct psi_decl *decl,
		struct psi_validate_stack *type_stack)
{
	if (!decl->abi) {
		decl->abi = psi_decl_abi_init("default");
	} else if (!psi_decl_abi_validate(data, decl->abi)) {
		data->error(data, decl->abi->token, PSI_WARNING,
				"Invalid calling convention: '%s'", decl->abi->token->text);
		return false;
	}
	if (!psi_decl_arg_validate(data, decl->func, type_stack)) {
		return false;
	}
	if (decl->args) {
		size_t i = 0;
		struct psi_decl_arg *arg;

		while (psi_plist_get(decl->args, i++, &arg)) {
			if (!psi_decl_arg_validate(data, arg, type_stack)) {
				return false;
			}
		}
	}

	return true;
}
