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

#include <stdlib.h>
#include <stdio.h>

#include "token.h"
#include "php_psi_stdtypes.h"

#include "data.h"

decl_type *init_decl_type(token_t type, const char *name) {
	decl_type *t = calloc(1, sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

void free_decl_type(decl_type *type) {
	if (type->token) {
		free(type->token);
	}
	if (type->type == PSI_T_FUNCTION) {
		free_decl(type->real.func);
	}
	free(type->name);
	free(type);
}

decl_args *extract_decl_type_args(decl_type *dtyp, decl_type **real_typ_ptr) {
	decl_type *var_typ;
	var_typ = real_decl_type(dtyp);
	if (real_typ_ptr) {
		*real_typ_ptr = var_typ;
	}
	switch (var_typ->type) {
	case PSI_T_STRUCT:
		return var_typ->real.strct->args;
	case PSI_T_UNION:
		return var_typ->real.unn->args;
	default:
		return NULL;
	}
}


int locate_decl_type_alias(decl_typedefs *defs, decl_type *type) {
	size_t i;
	struct psi_std_type *stdtyp;

	if (type->real.def) {
		return 1;
	}
	if (defs) for (i = 0; i < defs->count; ++i) {
		decl_arg *def = defs->list[i];

		if (def->type->type != type->type && !strcmp(def->var->name, type->name)) {
			type->real.def = def;
			return 1;
		}
	}
	for (stdtyp = &psi_std_types[0]; stdtyp->type_tag; ++stdtyp) {
		if (!strcmp(type->name, stdtyp->alias ?: stdtyp->type_name)) {
			type->type = stdtyp->type_tag;
			return 1;
		}
	}

	return 0;
}

int locate_decl_type_struct(decl_structs *structs, decl_type *type) {
	size_t i;

	if (type->real.strct) {
		return 1;
	}
	if (structs) for (i = 0; i < structs->count; ++i) {
		if (!strcmp(structs->list[i]->name, type->name)) {
			type->real.strct = structs->list[i];
			return 1;
		}
	}
	return 0;
}

int locate_decl_type_union(decl_unions *unions, decl_type *type) {
	size_t i;

	if (type->real.unn) {
		return 1;
	}
	if (unions) for (i = 0; i < unions->count; ++i) {
		if (!strcmp(unions->list[i]->name, type->name)) {
			type->real.unn = unions->list[i];
			return 1;
		}
	}
	return 0;
}

int locate_decl_type_enum(decl_enums *enums, decl_type *type) {
	size_t i;

	if (type->real.enm) {
		return 1;
	}
	if (enums) for (i = 0; i < enums->count; ++i) {
		if (!strcmp(enums->list[i]->name, type->name)) {
			type->real.enm = enums->list[i];
			return 1;
		}
	}
	return 0;
}

int locate_decl_type_decl(decls *decls, decl_type *type) {
	size_t i;

	if (type->real.func) {
		return 1;
	}
	if (decls) for (i = 0; i < decls->count; ++i) {
		if (!strcmp(decls->list[i]->func->var->name, type->name)) {
			type->real.func = decls->list[i];
			return 1;
		}
	}

	return 0;
}

int validate_decl_type(struct psi_data *data, decl_type *type, decl_arg *def) {
	if (weak_decl_type(type)) {
		if (!locate_decl_type_alias(data->defs, type)) {
			return 0;
		}
		if (type->real.def) {
			return validate_decl_type(data, type->real.def->type, type->real.def);
		}
		return 1;
	}

	switch (type->type) {
	case PSI_T_STRUCT:
		if (!locate_decl_type_struct(data->structs, type)) {
			return 0;
		}
		break;
	case PSI_T_UNION:
		if (!locate_decl_type_union(data->unions, type)) {
			return 0;
		}
		break;
	case PSI_T_ENUM:
		if (!locate_decl_type_enum(data->enums, type)) {
			return 0;
		}
		break;
	case PSI_T_FUNCTION:
		if (!locate_decl_type_decl(data->decls, type)) {
			return 0;
		}
		if (!validate_decl_nodl(data, type->real.func)) {
			return 0;
		}
		break;
	}
	return 1;
}

void dump_decl_type(int fd, decl_type *t, unsigned level) {
	switch (t->type) {
	case PSI_T_POINTER:
		dprintf(fd, "%s *", t->name);
		return;

	case PSI_T_ENUM:
		dprintf(fd, "enum ");
		if (is_anon_type(t->name, "enum")) {
			dump_decl_enum_items(fd, t->real.enm->items, level);
			return;
		}
		break;

	case PSI_T_STRUCT:
		dprintf(fd, "struct ");
		if (is_anon_type(t->name, "struct")) {
			dump_decl_args_with_layout(fd, t->real.strct->args, level);
			return;
		}
		break;

	case PSI_T_UNION:
		dprintf(fd, "union ");
		if (is_anon_type(t->name, "union")) {
			dump_decl_args_with_layout(fd, t->real.unn->args, level);
			return;
		}
		break;
	}
	dprintf(fd, "%s", t->name);
}

int weak_decl_type(decl_type *type) {
	switch (type->type) {
	case PSI_T_CHAR:
	case PSI_T_SHORT:
	case PSI_T_INT:
	case PSI_T_LONG:
	case PSI_T_NAME:
		return type->type;
	default:
		return 0;
	}
}

decl_type *real_decl_type(decl_type *type) {
	while (weak_decl_type(type)) {
		type = type->real.def->type;
	}
	return type;
}

size_t alignof_decl_type(decl_type *t) {
	decl_type *real = real_decl_type(t);
	size_t align;

	switch (real->type) {
	case PSI_T_STRUCT:
		align = alignof_decl_struct(real->real.strct);
		break;
	case PSI_T_UNION:
		align = alignof_decl_union(real->real.unn);
		break;
	case PSI_T_ENUM:
	default:
		align = psi_t_alignment(real->type);
	}

	return align;
}
