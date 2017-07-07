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
#include "token.h"
#include "data.h"

#define PSI_STD_TYPES
#include "php_psi_posix.h"

struct psi_decl_type *psi_decl_type_init(token_t type, const char *name)
{
	struct psi_decl_type *t = calloc(1, sizeof(*t));
	t->type = type;
	t->name = strdup(name);
	return t;
}

void psi_decl_type_free(struct psi_decl_type **type_ptr)
{
	if (*type_ptr) {
		struct psi_decl_type *type = *type_ptr;

		*type_ptr = NULL;
		if (type->token) {
			free(type->token);
		}
		if (type->type == PSI_T_FUNCTION) {
			psi_decl_free(&type->real.func);
		}
		free(type->name);
		free(type);
	}
}

struct psi_decl_type *psi_decl_type_copy(struct psi_decl_type *src)
{
	struct psi_decl_type *dst = calloc(1, sizeof(*dst));

	dst->type = src->type;
	if (src->name) {
		dst->name = strdup(src->name);
	}
	if (src->token) {
		dst->token = psi_token_copy(src->token);
	}
	return dst;
}

struct psi_plist *psi_decl_type_get_args(struct psi_decl_type *dtyp,
		struct psi_decl_type **real_typ_ptr)
{
	struct psi_decl_type *var_typ;

	var_typ = psi_decl_type_get_real(dtyp);
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

size_t psi_decl_type_get_size(struct psi_decl_type *dtyp,
		struct psi_decl_type **real_typ_ptr)
{
	struct psi_decl_type *var_typ;

	var_typ = psi_decl_type_get_real(dtyp);
	if (real_typ_ptr) {
		*real_typ_ptr = var_typ;
	}

	switch (var_typ->type) {
	case PSI_T_STRUCT:
		return var_typ->real.strct ? var_typ->real.strct->size : 0;
	case PSI_T_UNION:
		return var_typ->real.unn ? var_typ->real.unn->size : 0;
	default:
		return psi_t_size(var_typ->type);
	}
}

bool psi_decl_type_get_alias(struct psi_decl_type *type, struct psi_plist *defs)
{
	size_t i = 0;
	struct psi_std_type *stdtyp;
	struct psi_decl_arg *def;

	if (type->real.def) {
		return true;
	}
	if (defs) {
		while (psi_plist_get(defs, i++, &def)) {
			if (def->type->type != type->type
					&& !strcmp(def->var->name, type->name)) {
				type->real.def = def;
				return true;
			}
		}
	}
	for (stdtyp = &psi_std_types[0]; stdtyp->type_tag; ++stdtyp) {
		if (!strcmp(type->name, stdtyp->alias ?: stdtyp->type_name)) {
			type->type = stdtyp->type_tag;
			return true;
		}
	}

	return false;
}

bool psi_decl_type_get_struct(struct psi_decl_type *type, struct psi_plist *structs)
{
	size_t i = 0;
	struct psi_decl_struct *s;

	if (type->real.strct) {
		return true;
	}
	if (structs) {
		while (psi_plist_get(structs, i++, &s)) {
			if (!strcmp(s->name, type->name)) {
				type->real.strct = s;
				return true;
			}
		}
	}
	return false;
}

bool psi_decl_type_get_union(struct psi_decl_type *type, struct psi_plist *unions)
{
	size_t i = 0;
	struct psi_decl_union *u;

	if (type->real.unn) {
		return true;
	}
	if (unions) {
		while (psi_plist_get(unions, i++, &u)) {
			if (!strcmp(u->name, type->name)) {
				type->real.unn = u;
				return true;
			}
		}
	}
	return false;
}

bool psi_decl_type_get_enum(struct psi_decl_type *type, struct psi_plist *enums)
{
	size_t i = 0;
	struct psi_decl_enum *e;

	if (type->real.enm) {
		return true;
	}
	if (enums) {
		while (psi_plist_get(enums, i++, &e)) {
			if (!strcmp(e->name, type->name)) {
				type->real.enm = e;
				return true;
			}
		}
	}
	return false;
}

bool psi_decl_type_get_decl(struct psi_decl_type *type, struct psi_plist *decls)
{
	size_t i = 0;
	struct psi_decl *decl;

	if (type->real.func) {
		return true;
	}
	if (decls) {
		while (psi_plist_get(decls, i++, &decl)) {
			if (!strcmp(decl->func->var->name, type->name)) {
				type->real.func = decl;
				return true;
			}
		}
	}
	return false;
}

bool psi_decl_type_validate(struct psi_data *data, struct psi_decl_type *type,
		bool is_pointer, struct psi_validate_stack *type_stack)
{
	if (psi_decl_type_is_weak(type)) {
		if (!psi_decl_type_get_alias(type, data->types)) {
			if (!psi_validate_stack_has_type(type_stack, type->name)) {
				return false;
			}
			type->real.def = psi_validate_stack_get_type(type_stack, type->name);
		}
		if (type->real.def) {
			return psi_decl_type_validate(data, type->real.def->type,
					is_pointer, type_stack);
		}
		return true;
	}

	switch (type->type) {
	case PSI_T_STRUCT:
		if (!psi_decl_type_get_struct(type, data->structs)) {
			if (psi_validate_stack_has_struct(type_stack, type->name)) {
				type->real.strct = psi_validate_stack_get_struct(type_stack, type->name);
			} else if (is_pointer) {
				return true;
			} else {
				data->error(data, type->token, PSI_WARNING,
						"Unknown struct '%s'", type->name);
				return false;
			}
		}
		if (!psi_decl_struct_validate(data, type->real.strct, type_stack)) {
			return false;
		}
		break;
	case PSI_T_UNION:
		if (!psi_decl_type_get_union(type, data->unions)) {
			if (psi_validate_stack_has_union(type_stack, type->name)) {
				type->real.unn = psi_validate_stack_get_union(type_stack, type->name);
			} else if (is_pointer) {
				return true;
			} else {
				data->error(data, type->token, PSI_WARNING,
						"Unknown union '%s'", type->name);
				return false;
			}
		}
		if (!psi_decl_union_validate(data, type->real.unn, type_stack)) {
			return false;
		}
		break;
	case PSI_T_ENUM:
		if (!psi_decl_type_get_enum(type, data->enums)) {
			data->error(data, type->token, PSI_WARNING,
					"Unknown enum '%s'", type->name);
			return false;
		}
		break;
	case PSI_T_FUNCTION:
		if (!psi_decl_type_get_decl(type, data->decls)) {
			data->error(data, type->token, PSI_WARNING,
					"Unknown decl '%s'", type->name);
			return false;
		}
		if (!psi_decl_validate_nodl(data, type->real.func, type_stack)) {
			return false;
		}
		break;
	default:
		break;
	}

	return true;
}

void psi_decl_type_dump_args_with_layout(int fd, struct psi_plist *args,
		unsigned level)
{
	size_t i = 0;

	dprintf(fd, " {\n");
	if (args) {
		struct psi_decl_arg *sarg;

		++level;
		while (psi_plist_get(args, i++, &sarg)) {
			dprintf(fd, "%s", psi_t_indent(level));
			psi_decl_arg_dump(fd, sarg, level);
			if (sarg->layout->bfw) {
				dprintf(fd, ":%zu", sarg->layout->bfw->len);
			}
			dprintf(fd, "::(%zu, %zu);\n", sarg->layout->pos,
					sarg->layout->len);
		}
		--level;
	}
	dprintf(fd, "%s", psi_t_indent(level));
	dprintf(fd, "}");
}

void psi_decl_type_dump(int fd, struct psi_decl_type *t, unsigned level)
{
	switch (t->type) {
	case PSI_T_POINTER:
		dprintf(fd, "%s *", t->name);
		return;

	case PSI_T_ENUM:
		dprintf(fd, "enum ");
		if (psi_decl_type_is_anon(t->name, "enum")) {
			size_t i = 0, c = psi_plist_count(t->real.enm->items);
			struct psi_decl_enum_item *item;

			dprintf(fd, "{\n");
			++level;
			while (psi_plist_get(t->real.enm->items, i++, &item)) {
				dprintf(fd, "%s", psi_t_indent(level));
				psi_decl_enum_item_dump(fd, item);
				if (i < c) {
					dprintf(fd, "%s\n", i < c ? "," : "");
				}
			}
			--level;
			dprintf(fd, "%s\n} ", psi_t_indent(level));
			return;
		}
		break;

	case PSI_T_STRUCT:
		dprintf(fd, "struct ");
		if (psi_decl_type_is_anon(t->name, "struct")) {
			psi_decl_type_dump_args_with_layout(fd, t->real.strct->args, level);
			return;
		}
		break;

	case PSI_T_UNION:
		dprintf(fd, "union ");
		if (psi_decl_type_is_anon(t->name, "union")) {
			psi_decl_type_dump_args_with_layout(fd, t->real.unn->args, level);
			return;
		}
		break;
	}
	dprintf(fd, "%s", t->name);
}

int psi_decl_type_is_weak(struct psi_decl_type *type)
{
	switch (type->type) {
	case PSI_T_CHAR:
	case PSI_T_SHORT:
	case PSI_T_INT:
	case PSI_T_LONG:
	case PSI_T_UNSIGNED:
	case PSI_T_SIGNED:
	case PSI_T_NAME:
		return type->type;
	default:
		return 0;
	}
}

struct psi_decl_type *psi_decl_type_get_real(struct psi_decl_type *type)
{
	while (psi_decl_type_is_weak(type) && type->real.def) {
		type = type->real.def->type;
	}
	return type;
}

size_t psi_decl_type_get_align(struct psi_decl_type *t)
{
	struct psi_decl_type *real = psi_decl_type_get_real(t);
	size_t align;

	switch (real->type) {
	case PSI_T_STRUCT:
		align = psi_decl_struct_get_align(real->real.strct);
		break;
	case PSI_T_UNION:
		align = psi_decl_union_get_align(real->real.unn);
		break;
	case PSI_T_ENUM:
	default:
		align = psi_t_alignment(real->type);
	}

	return align;
}

size_t psi_decl_type_get_args_align(struct psi_plist *args)
{
	size_t i = 0, maxalign = 0;
	struct psi_decl_arg *darg;

	while (psi_plist_get(args, i++, &darg)) {
		size_t align = psi_decl_arg_get_align(darg);

		if (align > maxalign) {
			maxalign = align;
		}
	}

	return maxalign;
}

