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

#include <dlfcn.h>
#include <fnmatch.h>

#include <Zend/zend_smart_str.h>

#include "data.h"

#define PSI_FUNC_REDIRS
#include "php_psi_predef.h"

struct psi_decl *psi_decl_init(struct psi_decl_arg *func, struct psi_plist *args)
{
	struct psi_decl *d = pecalloc(1, sizeof(*d), 1);

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
		if (d->redir) {
			zend_string_release(d->redir);
		}
		free(d);
	}
}

void psi_decl_dump(struct psi_dump *dump, struct psi_decl *decl)
{
	if (decl->abi) {
		psi_decl_abi_dump(dump, decl->abi);
	}
	PSI_DUMP(dump, " ");
	/* FIXME: functions returning arrays */
	psi_decl_arg_dump(dump, decl->func, 0);
	PSI_DUMP(dump, "(");
	if (decl->args) {
		size_t i;
		struct psi_decl_arg *arg;

		for (i = 0; psi_plist_get(decl->args, i, &arg); ++i) {
			if (i) {
				PSI_DUMP(dump, ", ");
			}
			psi_decl_arg_dump(dump, arg, 0);
		}
		if (decl->varargs) {
			PSI_DUMP(dump, ", ...");
		}
	}
	if (decl->func->var->array_size) {
		PSI_DUMP(dump, ")[%u]", decl->func->var->array_size);
	}
	if (decl->redir) {
		PSI_DUMP(dump, ") __asm__ (\"%s\");", decl->redir->val);
	} else {
		PSI_DUMP(dump, ");");
	}
}

static inline bool psi_decl_validate_func(struct psi_data *data,
		struct psi_decl *decl, struct psi_decl_arg *func)
{
	struct psi_func_redir *redir;

	if (!func->var->name) {
		data->error(data, func->token, PSI_WARNING, "Cannot load anonymous decl");
		return false;
	}

	for (redir = &psi_func_redirs[0]; redir->name; ++redir) {
		if (!strcmp(func->var->name->val, redir->name)) {
			decl->sym = redir->func;
			break;
		}
	}
	if (!decl->sym) {
		decl->sym = psi_dlsym(data->file.dlopened, func->var->name->val,
			decl->redir ? decl->redir->val : NULL);
	}
	if (!decl->sym) {
		data->error(data, func->token, PSI_WARNING,
				"Failed to locate symbol '%s(%s)': %s",
				func->var->name->val,
				decl->redir ? decl->redir->val : "",
				dlerror() ?: "not found");
		return false;
	}
	return true;
}

bool psi_decl_validate(struct psi_data *data, struct psi_decl *decl,
		struct psi_validate_scope *scope)
{
	if (!psi_decl_validate_nodl(data, decl, scope)) {
		return false;
	}
	if (!psi_decl_validate_func(data, decl, decl->func)) {
		return false;
	}

	return true;
}

bool psi_decl_validate_nodl(struct psi_data *data, struct psi_decl *decl,
		struct psi_validate_scope *scope)
{
	if (!decl->abi) {
		decl->abi = psi_decl_abi_init(NULL);
	} else if (!psi_decl_abi_validate(data, decl->abi)) {
		data->error(data, decl->abi->token, PSI_WARNING,
				"Invalid calling convention: '%s'",
				decl->abi->token->text->val);
		return false;
	}
	if (!psi_decl_arg_validate(data, decl->func, scope)) {
		return false;
	}
	if (decl->args) {
		size_t i = 0;
		struct psi_decl_arg *arg;

		while (psi_plist_get(decl->args, i++, &arg)) {
			if (!arg->var->name) {
				smart_str name = {0};

				smart_str_appendl_ex(&name, ZEND_STRL("arg"), 1);
				smart_str_append_unsigned_ex(&name, i, 1);

				arg->var->name = smart_str_extract(&name);
				arg->var->fqn = zend_string_copy(arg->var->name);
			}
			if (!psi_decl_arg_validate(data, arg, scope)) {
				return false;
			}
		}
	}

	return true;
}

bool psi_decl_is_blacklisted(const char *name)
{
	char *blacklisted;
	size_t i = 0;

	while (psi_plist_get(PSI_G(blacklist).decls, i++, &blacklisted)) {
		if (!fnmatch(blacklisted, name, 0)) {
			return true;
		}
	}
	return false;
}

struct psi_decl_arg *psi_decl_get_arg(struct psi_decl *decl, struct psi_decl_var *var) {
	if (var->arg) {
		size_t i = 0;
		struct psi_decl_arg *arg = decl->func;

		do {
			if (var->arg == arg) {
				return arg;
			}
		} while (psi_plist_get(decl->args, i++, &arg));
	}

	return psi_decl_arg_get_by_var(var, decl->args, decl->func);
}
