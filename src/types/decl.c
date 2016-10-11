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

#include "php_psi_macros.h"
#include "php_psi_redirs.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <dlfcn.h>

#include "data.h"

decl *init_decl(decl_abi *abi, decl_arg *func, decl_args *args) {
	decl *d = calloc(1, sizeof(*d));
	d->abi = abi;
	d->func = func;
	d->args = args;
	return d;
}

void free_decl(decl *d) {
	free_decl_abi(d->abi);
	free_decl_arg(d->func);
	if (d->args) {
		free_decl_args(d->args);
	}
	free(d);
}

void dump_decl(int fd, decl *decl) {
	dump_decl_abi(fd, decl->abi);
	dprintf(fd, " ");
	dump_decl_arg(fd, decl->func, 0);
	dprintf(fd, "(");
	if (decl->args) {
		dump_decl_args(fd, decl->args, 0);
	}
	dprintf(fd, ");");
}

static inline int validate_decl_func(struct psi_data *data, void *dl, decl *decl, decl_arg *func)
{
	struct psi_func_redir *redir;

	if (!strcmp(func->var->name, "dlsym")) {
		data->error(data, func->token, PSI_WARNING, "Cannot dlsym dlsym (sic!)");
		return 0;
	}

	for (redir = &psi_func_redirs[0]; redir->name; ++redir) {
		if (!strcmp(func->var->name, redir->name)) {
			decl->call.sym = redir->func;
		}
	}
	if (!decl->call.sym) {
#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
		decl->call.sym = dlsym(dl ?: RTLD_NEXT, func->var->name);
		if (!decl->call.sym) {
			data->error(data, func->token, PSI_WARNING,
				"Failed to locate symbol '%s': %s",
				func->var->name, dlerror() ?: "not found");
		}
	}
	return 1;
}

int validate_decl(struct psi_data *data, void *dl, decl *decl) {
	if (!validate_decl_nodl(data, decl)) {
		return 0;
	}
	if (!validate_decl_func(data, dl, decl, decl->func)) {
		return 0;
	}
	return 1;
}

int validate_decl_nodl(struct psi_data *data, decl *decl) {
	if (!validate_decl_abi(data, decl->abi)) {
		data->error(data, decl->abi->token, PSI_WARNING,
				"Invalid calling convention: '%s'", decl->abi->token->text);
		return 0;
	}
	if (!validate_decl_arg(data, decl->func)) {
		return 0;
	}
	if (decl->args) {
		size_t i;

		for (i = 0; i < decl->args->count; ++i) {
			if (!validate_decl_arg(data, decl->args->args[i])) {
				return 0;
			}
		}
	}
	return 1;
}
