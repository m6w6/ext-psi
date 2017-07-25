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

#include "php_globals.h"

#include <dlfcn.h>
#include <ctype.h>

struct psi_data *psi_data_ctor_with_dtors(struct psi_data *data,
		psi_error_cb error, unsigned flags)
{
	if (!data) {
		data = calloc(1, sizeof(*data));
	}

	data->error = error;
	data->flags = flags;

	if (!data->consts) {
		data->consts = psi_plist_init((psi_plist_dtor) psi_const_free);
	}
	if (!data->types) {
		data->types = psi_plist_init((psi_plist_dtor) psi_decl_arg_free);
	}
	if (!data->structs) {
		data->structs = psi_plist_init((psi_plist_dtor) psi_decl_struct_free);
	}
	if (!data->unions) {
		data->unions = psi_plist_init((psi_plist_dtor) psi_decl_union_free);
	}
	if (!data->enums) {
		data->enums = psi_plist_init((psi_plist_dtor) psi_decl_enum_free);
	}
	if (!data->decls) {
		data->decls = psi_plist_init((psi_plist_dtor) psi_decl_free);
	}
	if (!data->impls) {
		data->impls = psi_plist_init((psi_plist_dtor) psi_impl_free);
	}
	if (!data->libs) {
		data->libs = psi_plist_init((psi_plist_dtor) psi_libs_free);
	}
	return data;
}

struct psi_data *psi_data_ctor(struct psi_data *data, psi_error_cb error,
		unsigned flags)
{
	if (!data) {
		data = calloc(1, sizeof(*data));
	}

	data->error = error;
	data->flags = flags;

	if (!data->consts) {
		data->consts = psi_plist_init(NULL);
	}
	if (!data->types) {
		data->types = psi_plist_init(NULL);
	}
	if (!data->structs) {
		data->structs = psi_plist_init(NULL);
	}
	if (!data->unions) {
		data->unions = psi_plist_init(NULL);
	}
	if (!data->enums) {
		data->enums = psi_plist_init(NULL);
	}
	if (!data->decls) {
		data->decls = psi_plist_init(NULL);
	}
	if (!data->impls) {
		data->impls = psi_plist_init(NULL);
	}
	if (!data->libs) {
		data->libs = psi_plist_init(NULL);
	}
	return data;
}

struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src)
{
	if (!dest) {
		dest = malloc(sizeof(*dest));
	}
	*dest = *src;
	memset(src, 0, sizeof(*src));
	return dest;
}

void psi_data_dtor(struct psi_data *data)
{
	if (data->consts) {
		psi_plist_free(data->consts);
	}
	if (data->types) {
		psi_plist_free(data->types);
	}
	if (data->structs) {
		psi_plist_free(data->structs);
	}
	if (data->unions) {
		psi_plist_free(data->unions);
	}
	if (data->enums) {
		psi_plist_free(data->enums);
	}
	if (data->decls) {
		psi_plist_free(data->decls);
	}
	if (data->impls) {
		psi_plist_free(data->impls);
	}
	if (data->libs) {
		psi_plist_free(data->libs);
	}

	psi_decl_file_dtor(&data->file);
}

void psi_data_dump(int fd, struct psi_data *D)
{
	if (D->file.fn) {
		dprintf(fd, "// filename=%s (%u errors)\n", D->file.fn, D->errors);
		if (D->file.ln) {
			dprintf(fd, "lib \"%s\";\n", D->file.ln);
		}
	} else {
		dprintf(fd, "// builtin predef\n");
	}
	if (psi_plist_count(D->types)) {
		size_t i = 0;
		struct psi_decl_arg *def;

		while (psi_plist_get(D->types, i++, &def)) {
			dprintf(fd, "typedef ");
			psi_decl_arg_dump(fd, def, 0);
			dprintf(fd, ";\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->unions)) {
		size_t i = 0;
		struct psi_decl_union *unn;

		while (psi_plist_get(D->unions, i++, &unn)) {
			if (!psi_decl_type_is_anon(unn->name, "union")) {
				psi_decl_union_dump(fd, unn);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->structs)) {
		size_t i = 0;
		struct psi_decl_struct *strct;

		while (psi_plist_get(D->structs, i++, &strct)) {
			if (!psi_decl_type_is_anon(strct->name, "struct")) {
				psi_decl_struct_dump(fd, strct);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->enums)) {
		size_t i = 0;
		struct psi_decl_enum *enm;

		while (psi_plist_get(D->enums, i++, &enm)) {
			if (!psi_decl_type_is_anon(enm->name, "enum")) {
				psi_decl_enum_dump(fd, enm, 0);
				dprintf(fd, "\n");
			}
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->consts)) {
		size_t i = 0;
		struct psi_const *c;

		while (psi_plist_get(D->consts, i++, &c)) {
			psi_const_dump(fd, c);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->decls)) {
		size_t i = 0;
		struct psi_decl *decl;

		while (psi_plist_get(D->decls, i++, &decl)) {
			psi_decl_dump(fd, decl);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
	if (psi_plist_count(D->impls)) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(D->impls, i++, &impl)) {
			psi_impl_dump(fd, impl);
			dprintf(fd, "\n");
		}
		dprintf(fd, "\n");
	}
}

bool psi_data_validate(struct psi_data *dst, struct psi_data *src)
{
	void *dlopened = NULL;
	size_t check_count = ~0;
	struct psi_plist *check_types = src->types;
	struct psi_plist *check_structs = src->structs;
	struct psi_plist *check_unions = src->unions;
	struct psi_plist *check_enums = src->enums;
	struct psi_plist *check_decls = src->decls;
	unsigned flags = dst->flags;
	unsigned errors = src->errors;
	struct psi_validate_stack type_stack;

	/* fail early if library is not found */
	if (!psi_decl_file_validate(dst, src, &dlopened)) {
		return false;
	}

	psi_validate_stack_ctor(&type_stack);

	dst->flags |= PSI_SILENT;

	while (check_count) {
		struct psi_plist *recheck_types;
		struct psi_plist *recheck_structs;
		struct psi_plist *recheck_unions;
		struct psi_plist *recheck_enums;
		struct psi_plist *recheck_decls;
		size_t count_types = psi_plist_count(check_types);
		size_t count_structs = psi_plist_count(check_structs);
		size_t count_unions = psi_plist_count(check_unions);
		size_t count_enums = psi_plist_count(check_enums);
		size_t count_decls = psi_plist_count(check_decls);
		size_t count_all = count_types + count_structs + count_unions
				+ count_enums + count_decls;

		if (check_count == count_all) {
			/* nothing changed; bail out */
			if (count_all && (dst->flags & PSI_SILENT) && !(flags & PSI_SILENT)) {
				/* one last error-spitting round, if not explicitly suppressed */
				dst->flags ^= PSI_SILENT;
				check_count = ~0;

				PSI_DEBUG_PRINT(dst, "PSI: validation bail out with %zu"
						" type checks remaining, errors follow\n", count_all);
				continue;
			}
			check_count = 0;
		} else {
			recheck_types = count_types ? psi_plist_init(NULL) : NULL;
			recheck_structs = count_structs ? psi_plist_init(NULL) : NULL;
			recheck_unions = count_unions ? psi_plist_init(NULL) : NULL;
			recheck_enums = count_enums ? psi_plist_init(NULL) : NULL;
			recheck_decls = count_decls ? psi_plist_init(NULL) : NULL;

			check_count = count_all;
			src->errors = errors + check_count;

			PSI_DEBUG_PRINT(dst, "PSI: validate data(%p) %zu type checks remaining\n",
					src, check_count);

			if (count_types) {
				size_t i = 0;
				struct psi_decl_arg *def;

				while (psi_plist_get(check_types, i++, &def)) {
					*dst->last_error = 0;
					dst->types = psi_plist_add(dst->types, &def);
					PSI_DEBUG_PRINT(dst, "PSI: validate typedef %s ", def->var->name);
					if (psi_decl_arg_validate_typedef(PSI_DATA(dst), def, &type_stack)) {
						PSI_DEBUG_PRINT(dst, "%s\n", "✔");
					} else {
						PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
						recheck_types = psi_plist_add(recheck_types, &def);
						psi_plist_pop(dst->types, NULL);
					}
				}
			}
			if (count_structs) {
				size_t i = 0;
				struct psi_decl_struct *str;

				while (psi_plist_get(check_structs, i++, &str)) {
					*dst->last_error = 0;
					dst->structs = psi_plist_add(dst->structs, &str);
					PSI_DEBUG_PRINT(dst, "PSI: validate struct %s ", str->name);
					if (psi_decl_struct_validate(PSI_DATA(dst), str, &type_stack)) {
						PSI_DEBUG_PRINT(dst, "%s ::(%zu, %zu)\n", "✔", str->align, str->size);
					} else {
						PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
						recheck_structs = psi_plist_add(recheck_structs, &str);
						psi_plist_pop(dst->structs, NULL);
					}
				}
			}
			if (count_unions) {
				size_t i = 0;
				struct psi_decl_union *unn;

				while (psi_plist_get(check_unions, i++, &unn)) {
					*dst->last_error = 0;
					dst->unions = psi_plist_add(dst->unions, &unn);
					PSI_DEBUG_PRINT(dst, "PSI: validate union %s ", unn->name);
					if (psi_decl_union_validate(PSI_DATA(dst), unn, &type_stack)) {
						PSI_DEBUG_PRINT(dst, "%s ::(%zu, %zu)\n", "✔", unn->align, unn->size);
					} else {
						PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
						recheck_unions = psi_plist_add(recheck_unions, &unn);
						psi_plist_pop(dst->unions, NULL);
					}
				}
			}
			if (count_enums) {
				size_t i = 0;
				struct psi_decl_enum *enm;

				while (psi_plist_get(check_enums, i++, &enm)) {
					*dst->last_error = 0;
					PSI_DEBUG_PRINT(dst, "PSI: validate enum %s ", enm->name);
					if (psi_decl_enum_validate(PSI_DATA(dst), enm)) {
						PSI_DEBUG_PRINT(dst, "%s\n", "✔");
						dst->enums = psi_plist_add(dst->enums, &enm);
					} else {
						PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
						recheck_enums = psi_plist_add(recheck_enums, &enm);
					}
				}
			}
			if (count_decls) {
				size_t i = 0;
				struct psi_decl *decl;

				while (psi_plist_get(check_decls, i++, &decl)) {
					*dst->last_error = 0;
					PSI_DEBUG_PRINT(dst, "PSI: validate decl %s ", decl->func->var->name);
					if (psi_decl_validate(PSI_DATA(dst), decl, dlopened, &type_stack)) {
						PSI_DEBUG_PRINT(dst, "%s\n", "✔");
						dst->decls = psi_plist_add(dst->decls, &decl);
					} else {
						PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
						recheck_decls = psi_plist_add(recheck_decls, &decl);
					}
				}
			}
		}

		if (check_types && check_types != src->types) {
			psi_plist_free(check_types);
		}
		check_types = recheck_types;
		if (check_structs && check_structs != src->structs) {
			psi_plist_free(check_structs);
		}
		check_structs = recheck_structs;
		if (check_unions && check_unions != src->unions) {
			psi_plist_free(check_unions);
		}
		check_unions = recheck_unions;
		if (check_enums && check_enums != src->enums) {
			psi_plist_free(check_enums);
		}
		check_enums = recheck_enums;
		if (check_decls && check_decls != src->decls) {
			psi_plist_free(check_decls);
		}
		check_decls = recheck_decls;
	}

	/* reset original flags */
	dst->flags = flags;

	if (dst->structs) {
		size_t i = 0;
		struct psi_decl_struct *str;

		while (psi_plist_get(dst->structs, i++, &str)) {
			size_t nlen = strlen(str->name);
			size_t slen = sizeof("psi\\SIZEOF_STRUCT_");
			size_t alen = sizeof("psi\\ALIGNOF_STRUCT_");
			char *nptr = str->name, *sname, *aname;
			struct psi_const *cnst;
			struct psi_const_type *ctyp;
			struct psi_impl_def_val *cval;

			sname = malloc(slen + nlen + 1);
			strcpy(sname, "psi\\SIZEOF_STRUCT_");
			aname = malloc(alen + nlen + 1);
			strcpy(aname, "psi\\ALIGNOF_STRUCT_");

			nptr = str->name;
			while (*nptr) {
				size_t off = nptr - str->name;
				sname[slen - 1 + off] = aname[alen - 1 + off] = toupper(*nptr++);
			}
			sname[slen - 1 + nlen] = aname[alen - 1 + nlen] = 0;

			ctyp = psi_const_type_init(PSI_T_INT, "int");
			cval = psi_impl_def_val_init(PSI_T_INT, NULL);
			cval->ival.zend.lval = str->size;
			cnst = psi_const_init(ctyp, sname, cval);
			src->consts = psi_plist_add(src->consts, &cnst);
			free(sname);

			ctyp = psi_const_type_init(PSI_T_INT, "int");
			cval = psi_impl_def_val_init(PSI_T_INT, NULL);
			cval->ival.zend.lval = str->align;
			cnst = psi_const_init(ctyp, aname, cval);
			src->consts = psi_plist_add(src->consts, &cnst);
			free(aname);
		}
	}

	if (src->consts) {
		size_t i = 0;
		struct psi_const *cnst;

		while (psi_plist_get(src->consts, i++, &cnst)) {
			*dst->last_error = 0;
			PSI_DEBUG_PRINT(dst, "PSI: validate const %s ", cnst->name);
			if (psi_const_validate(PSI_DATA(dst), cnst)) {
				PSI_DEBUG_PRINT(dst, "%s\n", "✔");
				dst->consts = psi_plist_add(dst->consts, &cnst);
			} else {
				PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
				++src->errors;
			}
		}
	}

	if (src->impls) {
		size_t i = 0;
		struct psi_impl *impl;

		while (psi_plist_get(src->impls, i++, &impl)) {
			*dst->last_error = 0;
			PSI_DEBUG_PRINT(dst, "PSI: validate impl %s ", impl->func->name);
			if (psi_impl_validate(PSI_DATA(dst), impl)) {
				PSI_DEBUG_PRINT(dst, "%s\n", "✔");
				dst->impls = psi_plist_add(dst->impls, &impl);
			} else {
				PSI_DEBUG_PRINT(dst, "%s (%s)\n", "✘", dst->last_error);
				++src->errors;
			}
		}
	}

	psi_validate_stack_dtor(&type_stack);

	return true;
}

