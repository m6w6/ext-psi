/*******************************************************************************
 Copyright (c) 2017, Michael Wallner <mike@php.net>.
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

#include "php_psi.h"

#include <fnmatch.h>
#include <Zend/zend_smart_str.h>

#include "data.h"

struct psi_decl_extvar *psi_decl_extvar_init(struct psi_decl_arg *arg)
{
	struct psi_decl_extvar *evar = pecalloc(1, sizeof(*evar), 1);

	evar->arg = arg;
	return evar;
}

void psi_decl_extvar_free(struct psi_decl_extvar **evar_ptr)
{
	if (*evar_ptr) {
		struct psi_decl_extvar *evar = *evar_ptr;

		*evar_ptr = NULL;
		psi_token_free(&evar->token);
		psi_decl_arg_free(&evar->arg);
		psi_decl_free(&evar->getter);
		psi_decl_free(&evar->setter);
		free(evar);
	}
}

bool psi_decl_extvar_validate(struct psi_data *data,
		struct psi_decl_extvar *evar, struct psi_validate_scope *scope)
{
	if (!psi_decl_arg_validate(data, evar->arg, scope)) {
		return false;
	}

	evar->size = psi_decl_arg_get_size(evar->arg);
	if (!evar->size) {
		data->error(data, evar->arg->var->token, PSI_WARNING,
				"Failed to calculate size of symbol '%s'", evar->arg->var->name->val);
		return false;
	}

	if (!evar->sym) {
		evar->sym = psi_dlsym(data->file.dlopened, evar->arg->var->name->val,
			evar->redir ? evar->redir->val : NULL);
	}
	if (!evar->sym) {
		data->error(data, evar->arg->var->token, PSI_WARNING,
				"Failed to locate symbol '%s': %s", evar->arg->var->name->val,
				dlerror() ?: "not found");
		return false;
	}

	evar->getter = psi_decl_extvar_getter(evar);
	if (!psi_decl_validate_nodl(data, evar->getter, scope)) {
		return false;
	}
	evar->setter = psi_decl_extvar_setter(evar);
	if (!psi_decl_validate_nodl(data, evar->setter, scope)) {
		return false;
	}

	return true;
}

void psi_decl_extvar_dump(struct psi_dump *dump, struct psi_decl_extvar *evar)
{
	PSI_DUMP(dump, "extern ");
	psi_decl_arg_dump(dump, evar->arg, 0);
	PSI_DUMP(dump, ";\n");
}

struct psi_decl *psi_decl_extvar_setter(struct psi_decl_extvar *evar)
{
	zend_string *type_str = zend_string_init_interned(ZEND_STRS("void"), 1);
	struct psi_decl_type *func_type = psi_decl_type_init(PSI_T_VOID, type_str);
	struct psi_decl_var *func_var = psi_decl_var_copy(evar->arg->var);
	struct psi_decl_arg *func = psi_decl_arg_init(func_type, func_var);
	struct psi_decl_type *arg_type = psi_decl_type_copy(evar->arg->type);
	struct psi_decl_var *arg_var = psi_decl_var_copy(evar->arg->var);
	struct psi_decl_arg *arg = psi_decl_arg_init(arg_type, arg_var);
	struct psi_plist *args = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	struct psi_decl *decl = psi_decl_init(func, psi_plist_add(args, &arg));
	smart_str name = {0};

	zend_string_release(type_str);

	func_var->pointer_level = 0;
	func_var->array_size = 0;

	smart_str_append_ex(&name, func_var->name, 1);
	smart_str_appendl_ex(&name, ZEND_STRL("_set"), 1);
	zend_string_release(func_var->name);
	func_var->name = zend_new_interned_string(smart_str_extract(&name));

	decl->extvar = 1;

	return decl;
}

void psi_decl_extvar_set(struct psi_decl_extvar *evar, void *ptr)
{
	memcpy(evar->sym, ptr, evar->size);
}

struct psi_decl *psi_decl_extvar_getter(struct psi_decl_extvar *evar)
{
	struct psi_decl_type *func_type = psi_decl_type_copy(evar->arg->type);
	struct psi_decl_var *func_var = psi_decl_var_copy(evar->arg->var);
	struct psi_decl_arg *func = psi_decl_arg_init(func_type, func_var);
	struct psi_decl *decl = psi_decl_init(func, NULL);
	smart_str name = {0};

	smart_str_append_ex(&name, func_var->name, 1);
	smart_str_appendl_ex(&name, ZEND_STRL("_get"), 1);
	zend_string_release(func_var->name);
	func_var->name = zend_new_interned_string(smart_str_extract(&name));

	decl->extvar = 1;

	return decl;
}

void psi_decl_extvar_get(struct psi_decl_extvar *evar, void *ptr)
{
	memcpy(ptr, evar->sym, evar->size);
}


bool psi_decl_extvar_is_blacklisted(const char *name)
{
	char *blacklisted;
	size_t i = 0;

	while (psi_plist_get(PSI_G(blacklist).vars, i++, &blacklisted)) {
		if (!fnmatch(blacklisted, name, 0)) {
			return true;
		}
	}
	return false;
}
