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
#include <assert.h>

#include "data.h"

struct psi_decl_arg *psi_decl_arg_init(struct psi_decl_type *type,
		struct psi_decl_var *var)
{
	struct psi_decl_arg *arg = pecalloc(1, sizeof(*arg), 1);
	arg->token = var->token;
	arg->type = type;
	arg->var = var;
	var->arg = arg;
	return arg;
}

void psi_decl_arg_free(struct psi_decl_arg **arg_ptr)
{
	if (*arg_ptr) {
		struct psi_decl_arg *arg = *arg_ptr;

		*arg_ptr = NULL;
		if (arg->token && arg->token != arg->var->token) {
			psi_token_free(&arg->token);
		}
		psi_decl_type_free(&arg->type);
		psi_decl_var_free(&arg->var);
		if (arg->layout) {
			psi_layout_free(&arg->layout);
		}
		free(arg);
	}
}

void psi_decl_arg_dump(int fd, struct psi_decl_arg *arg, unsigned level)
{
	if (arg->type->type == PSI_T_FUNCTION) {
		psi_decl_type_dump(fd, arg->type->real.func->func->type, level);
		if (arg->type->real.func->func->type->type == PSI_T_FUNCTION) {
			dprintf(fd, "(");
		}
		dprintf(fd, " %s(*%s)",
				psi_t_indirection(arg->var->pointer_level - !! arg->var->array_size),
				arg->var->name->val);
		dprintf(fd, "(");
		if (arg->type->real.func->args) {
			size_t j = 0;
			struct psi_decl_arg *farg;

			++level;
			while (psi_plist_get(arg->type->real.func->args, j++, &farg)) {
				if (j > 1) {
					dprintf(fd, ", ");
				}
				psi_decl_arg_dump(fd, farg, level);
			}
			--level;
			if (arg->type->real.func->varargs) {
				dprintf(fd, ", ...");
			}
		}
		dprintf(fd, ")");
		if (arg->type->real.func->func->type->type == PSI_T_FUNCTION) {
			struct psi_decl *decl = arg->type->real.func->func->type->real.func;

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
			dprintf(fd, "))");
		}
	} else {
		psi_decl_type_dump(fd, arg->type, level);
		dprintf(fd, " ");
		psi_decl_var_dump(fd, arg->var);
	}
}

bool psi_decl_arg_validate(struct psi_data *data, struct psi_decl_arg *arg,
		struct psi_validate_scope *scope)
{
	if (!psi_decl_type_validate(data, arg->type, NULL, scope)) {
		 if (!arg->var->pointer_level) {
			data->error(data, arg->type->token, PSI_WARNING,
					"Cannot use '%s' as type for '%s'%s%s",
					arg->type->name->val,
					arg->var->name->val,
					*data->last_error ? ": " : "", data->last_error);
			return false;
		 }
	}
	return true;
}

bool psi_decl_arg_validate_typedef(struct psi_data *data,
		struct psi_decl_arg *def, struct psi_validate_scope *scope)
{
	if (psi_validate_scope_has_type(scope, def->var->name)) {
		return true;
	}
	psi_validate_scope_add_type(scope, def->var->name, def);

	if (def->type->type == PSI_T_VOID) {
		if (def->var->pointer_level) {
			def->type->type = PSI_T_POINTER;
		} else {
			data->error(data, def->token, PSI_WARNING,
					"Type '%s' cannot be aliased to 'void'",
					def->type->name->val);
			return false;
		}
	} else if (!psi_decl_type_validate(data, def->type, def, scope)) {
		const char *pre;

		switch (def->type->type) {
		case PSI_T_STRUCT:
			pre = "struct ";
			break;
		case PSI_T_UNION:
			pre = "union ";
			break;
		case PSI_T_ENUM:
			pre = "enum ";
			break;
		default:
			pre = "";
			break;
		}
		data->error(data, def->token, PSI_WARNING,
				"Type '%s' cannot be aliased to '%s%s'%s%s",
				def->var->name->val, pre,
				def->type->name->val,
				*data->last_error ? ": " : "", data->last_error);
		return false;
	}

	return true;
}

bool psi_decl_arg_is_pointer(struct psi_decl_arg *darg)
{
	if (darg->var->pointer_level) {
		if (darg->var->array_size) {
			return darg->var->pointer_level > 1;
		}
		return true;
	} else if (psi_decl_type_is_weak(darg->type) && darg->type->real.def) {
		return psi_decl_arg_is_pointer(darg->type->real.def);
	}
	return false;
}

size_t psi_decl_arg_align(struct psi_decl_arg *darg, size_t *pos, size_t *len)
{
	size_t align = psi_decl_arg_get_align(darg);

	if (align) {
		*len = psi_decl_arg_get_size(darg);
		*pos = psi_align(align, *pos);
	}

	return align;
}

size_t psi_decl_arg_get_align(struct psi_decl_arg *darg)
{
	size_t align;

	if (psi_decl_arg_is_pointer(darg)) {
		align = psi_t_alignment(PSI_T_POINTER);
	} else {
		align = psi_decl_type_get_align(darg->type);
	}

	return align;
}

size_t psi_decl_arg_get_size(struct psi_decl_arg *darg)
{
	size_t size;
	struct psi_decl_type *real = psi_decl_type_get_real(darg->type);

	if (darg->var->array_size && darg->var->pointer_level > 1) {
		size = psi_t_size(PSI_T_POINTER) * darg->var->array_size;
	} else if (psi_decl_arg_is_pointer(darg)) {
		size = psi_t_size(PSI_T_POINTER);
	} else {
		switch (real->type) {
		case PSI_T_UNION:
			size = real->real.unn->size;
			break;
		case PSI_T_STRUCT:
			size = real->real.strct->size;
			break;
		case PSI_T_ENUM:
		default:
			size = psi_t_size(real->type);
			break;
		}

		if (darg->var->array_size) {
			size *= darg->var->array_size;
		}
	}

	return size;
}

struct psi_decl_arg *psi_decl_arg_get_by_name(struct psi_plist *args,
		zend_string *name)
{
	size_t i = 0;
	struct psi_decl_arg *arg;

	if (args)
		while (psi_plist_get(args, i++, &arg)) {
			if (zend_string_equals(name, arg->var->name)) {
				return arg;
			}
		}

	return NULL;
}

struct psi_decl_arg *psi_decl_arg_get_by_var(struct psi_decl_var *var,
		struct psi_plist *args, struct psi_decl_arg *func)
{
	struct psi_decl_arg *arg = psi_decl_arg_get_by_name(args, var->name);

	if (arg) {
		assert(!var->arg || var->arg == arg);

		return var->arg = arg;
	}

	if (func && zend_string_equals(var->name, func->var->name)) {
		return var->arg = func;
	}

	return NULL;
}
