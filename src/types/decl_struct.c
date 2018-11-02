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

#include <assert.h>

struct psi_decl_struct* psi_decl_struct_init(zend_string *name,
		struct psi_plist *args)
{
	struct psi_decl_struct *s = pecalloc(1, sizeof(*s), 1);
	s->name = zend_string_copy(name);
	s->args = args;
	return s;
}

void psi_decl_struct_free(struct psi_decl_struct **s_ptr)
{
	if (*s_ptr) {
		struct psi_decl_struct *s = *s_ptr;

		*s_ptr = NULL;
		psi_token_free(&s->token);
		if (s->args) {
			psi_plist_free(s->args);
		}
		if (s->engine.type && s->engine.dtor) {
			s->engine.dtor(s->engine.type);
		}
		zend_string_release(s->name);
		free(s);
	}
}

void psi_decl_struct_dump(int fd, struct psi_decl_struct *strct)
{
	dprintf(fd, "struct %s::(%zu, %zu)", strct->name->val, strct->align,
			strct->size);
	if (psi_plist_count(strct->args)) {
		psi_decl_type_dump_args_with_layout(fd, strct->args, 0);
	} else {
		dprintf(fd, ";");
	}
}

struct psi_decl_arg *psi_decl_struct_get_arg(struct psi_decl_struct *s,
		struct psi_decl_var *var)
{
	if (s->args) {
		return psi_decl_arg_get_by_var(var, s->args, NULL);
	}

	return NULL;
}

bool psi_decl_struct_validate(struct psi_data *data, struct psi_decl_struct *s,
		struct psi_validate_scope *scope)
{
	size_t i, pos = 0, len = 0;
	struct psi_decl_arg *darg, *prev_arg;

	if (!s) {
		return false;
	}
	if (psi_validate_scope_has_struct(scope, s->name)) {
		return true;
	}

	if (!s->size && !psi_plist_count(s->args)) {
		/* TODO: return true and check those structs are only used by address */
		/* suppress needless warning
		data->error(data, s->token, PSI_WARNING, "Empty struct %s",
				s->name);
				*/
		return false;
	}

	psi_validate_scope_add_struct(scope, s->name, s);

	for (i = 0; psi_plist_get(s->args, i, &darg); ++i) {
		size_t align;

		darg->var->arg = darg;

		if (!psi_decl_arg_validate(data, darg, scope)) {
			psi_validate_scope_del_struct(scope, s->name);
			return false;
		}

		if (darg->layout && darg->layout->len) {
			pos = darg->layout->pos;
			align = psi_decl_arg_align(darg, &pos, &len);

			if (!align) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed zero alignment of %s.%s of type '%s'",
						len, s->name->val, darg->var->name->val,
						darg->type->name->val);
				psi_validate_scope_del_struct(scope, s->name);
				return false;
			}

			if (darg->layout->len != len) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed size %zu of %s.%s does not match"
						" pre-defined size %zu of type '%s'",
						len, s->name->val, darg->var->name->val,
						darg->layout->len, darg->type->name->val);
			}
			if (darg->layout->pos != pos) {
				data->error(data, darg->token, PSI_WARNING,
						"Computed offset %zu of %s.%s does not match"
						" pre-defined offset %zu",
						pos, s->name->val, darg->var->name->val,
						darg->layout->pos);
			}
		} else {
			if (i) {
				if (prev_arg->layout && prev_arg->layout->bfw && darg->layout && darg->layout->bfw) {
					struct psi_decl_type *real = NULL;
					size_t max_bfw = 8 * psi_decl_type_get_size(prev_arg->type, &real);

					switch (real->type) {
					case PSI_T_INT8:
					case PSI_T_UINT8:
					case PSI_T_INT16:
					case PSI_T_UINT16:
					case PSI_T_INT32:
					case PSI_T_UINT32:
					case PSI_T_INT64:
					case PSI_T_UINT64:
						break;
					default:
						data->error(data, darg->token, PSI_WARNING,
								"Unsupported type for bit field: %s",
								real->name->val);
						psi_validate_scope_del_struct(scope, s->name);
						return false;
					}
					darg->layout->bfw->pos = prev_arg->layout->bfw->pos + prev_arg->layout->bfw->len;
					if (max_bfw >= darg->layout->bfw->pos + darg->layout->bfw->len) {
						pos = prev_arg->layout->pos;
					} else {
						darg->layout->bfw->pos = 0;
						pos = prev_arg->layout->pos + prev_arg->layout->len;
					}
				} else {
					pos = prev_arg->layout->pos + prev_arg->layout->len;
				}
			} else {
				pos = 0;
			}

			align = psi_decl_arg_align(darg, &pos, &len);

			if (darg->layout) {
				if (darg->layout->pos != pos && !darg->layout->bfw) {
					data->error(data, darg->token, PSI_WARNING,
							"Computed offset %zu of %s.%s does not match"
							" pre-defined offset %zu",
							pos, s->name->val, darg->var->name->val,
							darg->layout->pos);
				}
				darg->layout->pos = pos;
				darg->layout->len = len;
			} else {
				darg->layout = psi_layout_init(pos, len, NULL);
			}
		}

		if (align > s->align) {
			s->align = align;
		}
		prev_arg = darg;
	}

	if (psi_plist_count(s->args)) {
		size_t size;

		psi_plist_sort(s->args, psi_layout_sort_cmp, NULL);
		psi_plist_get(s->args, psi_plist_count(s->args) - 1, &darg);

		size = darg->layout->pos + darg->layout->len;
		if (s->size < size) {
			s->size = psi_align(size, s->align);
		}
	}

	assert(s->size);

	return true;
}

size_t psi_decl_struct_get_align(struct psi_decl_struct *s)
{
	if (!s) {
		return 0;
	}
	if (!s->align) {
		s->align = psi_decl_type_get_args_align(s->args);
	}
	return s->align;
}
