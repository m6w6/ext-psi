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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include "data.h"
#include "debug.h"

typedef bool (*psi_validate_list_entry)(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr);

struct psi_validate_list {
	struct psi_plist *src;
	struct psi_plist **dst;
	struct psi_plist *cur;
	struct psi_plist *chk;
};

static inline void psi_validate_list(struct psi_validate_scope *scope,
		struct psi_data *dst, struct psi_validate_list *list,
		psi_validate_list_entry validate)
{
	if (!list->cur) {
		list->cur = list->src;
	}

	if (psi_plist_count(list->cur)) {
		size_t i = 0;
		void *ptr = NULL;

		list->chk = psi_plist_init(NULL);

		while (psi_plist_get(list->cur, i++, &ptr)) {
			*dst->last_error = 0;

			PSI_DEBUG_PRINT(dst, "PSI: validate %s ", "»");
			if (validate(scope, dst, ptr)) {
				PSI_DEBUG_PRINT(dst, " %s\n", "✔");
				*list->dst = psi_plist_add(*list->dst, &ptr);
			} else {
				PSI_DEBUG_PRINT(dst, " %s (%s)\n", "✘", dst->last_error);
				list->chk = psi_plist_add(list->chk, &ptr);
			}
		}

		if (list->cur != list->src) {
			psi_plist_free(list->cur);
		}
		list->cur = list->chk;
	}
}

static bool psi_validate_type(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl_arg *def = ptr;

	PSI_DEBUG_PRINT(dst, "typedef %s", def->var->name->val);
	return psi_decl_arg_validate_typedef(dst, def, scope);
}

static bool psi_validate_struct(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl_struct *str = ptr;

	PSI_DEBUG_PRINT(dst, "struct %s", str->name->val);
	if (psi_decl_struct_validate(dst, str, scope)) {
		PSI_DEBUG_PRINT(dst, "::(%zu, %zu)", str->align, str->size);
		return true;
	}
	return false;
}

static bool psi_validate_union(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl_union *unn = ptr;

	PSI_DEBUG_PRINT(dst, "union %s", unn->name->val);
	if (psi_decl_union_validate(dst, unn, scope)) {
		PSI_DEBUG_PRINT(dst, "::(%zu, %zu)", unn->align, unn->size);
		return true;
	}
	return false;
}

static bool psi_validate_enum(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl_enum *enm = ptr;

	PSI_DEBUG_PRINT(dst, "enum %s", enm->name->val);
	return psi_decl_enum_validate(dst, enm);
}

static bool psi_validate_extvar(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl_extvar *evar = ptr;

	PSI_DEBUG_PRINT(dst, "extvar %s", evar->arg->var->name->val);
	if (psi_decl_extvar_validate(dst, evar, scope)) {
		dst->decls = psi_plist_add(dst->decls, &evar->getter);
		dst->decls = psi_plist_add(dst->decls, &evar->setter);
		return true;
	}
	return false;
}

static bool psi_validate_decl(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_decl *decl = ptr;

	PSI_DEBUG_PRINT(dst, "decl %s", decl->func->var->name->val);
	return psi_decl_validate(dst, decl, scope);
}

static bool psi_validate_const(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_const *cnst = ptr;

	PSI_DEBUG_PRINT(dst, "constant %s", cnst->name->val);
	return psi_const_validate(dst, cnst, scope);
}

static bool psi_validate_impl(struct psi_validate_scope *scope,
		struct psi_data *dst, void *ptr)
{
	struct psi_impl *impl = ptr;

	PSI_DEBUG_PRINT(dst, "impl %s", impl->func->name->val);
	return psi_impl_validate(dst, impl, scope);
}

bool psi_validate(struct psi_validate_scope *scope,
		struct psi_data *dst, struct psi_data *src)
{
	struct psi_validate_list types = {src->types, &dst->types, NULL, NULL};
	struct psi_validate_list structs = {src->structs, &dst->structs, NULL, NULL};
	struct psi_validate_list unions = {src->unions, &dst->unions, NULL, NULL};
	struct psi_validate_list enums = {src->enums, &dst->enums, NULL, NULL};
	struct psi_validate_list vars = {src->vars, &dst->vars, NULL, NULL};
	struct psi_validate_list decls = {src->decls, &dst->decls, NULL, NULL};
	struct psi_validate_list consts = {src->consts, &dst->consts, NULL, NULL};
	struct psi_validate_list impls = {src->impls, &dst->impls, NULL, NULL};
	unsigned flags = dst->flags;
	size_t check_count = ~0;

	/* fail early if libraries are not found */
	if (!psi_decl_file_validate(dst, src)) {
		return false;
	}

	/* silence loop */
	dst->flags |= PSI_SILENT;

	while (true) {
		size_t count_all = psi_plist_count(types.cur ?: types.src)
				+ psi_plist_count(structs.cur ?: structs.src)
				+ psi_plist_count(unions.cur ?: unions.src)
				+ psi_plist_count(enums.cur ?: enums.src)
				+ psi_plist_count(vars.cur ?: vars.src)
				+ psi_plist_count(decls.cur ?: decls.src);

		if (check_count != count_all) {
			check_count = count_all;

			PSI_DEBUG_PRINT(dst,
					"PSI: validate data(%p) %zu type checks remaining\n",
					src, check_count);

			psi_validate_list(scope, dst, &types, psi_validate_type);
			psi_validate_list(scope, dst, &structs, psi_validate_struct);
			psi_validate_list(scope, dst, &unions, psi_validate_union);
			psi_validate_list(scope, dst, &enums, psi_validate_enum);
			psi_validate_list(scope, dst, &vars, psi_validate_extvar);
			psi_validate_list(scope, dst, &decls, psi_validate_decl);
			continue;
		}

		/* nothing changed; bail out */
		if (count_all) {
			src->errors += count_all;

			if ((dst->flags & PSI_SILENT) && !(flags & PSI_SILENT)) {
				/* one last error-spitting round, if not explicitly suppressed */
				dst->flags ^= PSI_SILENT;
				check_count = ~0;

				PSI_DEBUG_PRINT(dst, "PSI: validation bail out with %zu"
						" type checks remaining, errors follow\n", count_all);
				continue;
			}
		}

		break;
	}

	/* reset original flags */
	dst->flags = flags;

	psi_validate_list(scope, dst, &consts, psi_validate_const);
	psi_validate_list(scope, dst, &impls, psi_validate_impl);

	if (types.cur != types.src) {
		psi_plist_free(types.cur);
	}
	if (structs.cur != structs.src) {
		psi_plist_free(structs.cur);
	}
	if (unions.cur != unions.src) {
		psi_plist_free(unions.cur);
	}
	if (enums.cur != enums.src) {
		psi_plist_free(enums.cur);
	}
	if (vars.cur != vars.src) {
		psi_plist_free(vars.cur);
	}
	if (decls.cur != decls.src) {
		psi_plist_free(decls.cur);
	}
	if (consts.cur != consts.src) {
		psi_plist_free(consts.cur);
	}
	if (impls.cur != impls.src) {
		psi_plist_free(impls.cur);
	}

	return true;
}
