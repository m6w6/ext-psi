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

struct psi_impl *psi_impl_init(struct psi_impl_func *func,
		struct psi_plist *stmts)
{
	struct psi_impl *impl = pecalloc(1, sizeof(*impl), 1);
	size_t i = 0;
	struct psi_token **abstract_stmt;

	impl->stmts.ret = psi_plist_init((psi_plist_dtor) psi_return_stmt_free);
	impl->stmts.let = psi_plist_init((psi_plist_dtor) psi_let_stmt_free);
	impl->stmts.set = psi_plist_init((psi_plist_dtor) psi_set_stmt_free);
	impl->stmts.fre = psi_plist_init((psi_plist_dtor) psi_free_stmt_free);
	impl->stmts.ass = psi_plist_init((psi_plist_dtor) psi_assert_stmt_free);

	while (psi_plist_get(stmts, i++, &abstract_stmt)) {
		switch ((*abstract_stmt)->type) {
		case PSI_T_RETURN:
			impl->stmts.ret = psi_plist_add(impl->stmts.ret, &abstract_stmt);
			break;
		case PSI_T_LET:
		case PSI_T_TEMP:
			impl->stmts.let = psi_plist_add(impl->stmts.let, &abstract_stmt);
			break;
		case PSI_T_SET:
			impl->stmts.set = psi_plist_add(impl->stmts.set, &abstract_stmt);
			break;
		case PSI_T_FREE:
			impl->stmts.fre = psi_plist_add(impl->stmts.fre, &abstract_stmt);
			break;
		case PSI_T_PRE_ASSERT:
		case PSI_T_POST_ASSERT:
			impl->stmts.ass = psi_plist_add(impl->stmts.ass, &abstract_stmt);
			break;
		default:
			assert(0);
		}
	}
	free(stmts);

	impl->func = func;

	return impl;
}

void psi_impl_free(struct psi_impl **impl_ptr)
{
	if (*impl_ptr) {
		struct psi_impl *impl = *impl_ptr;

		*impl_ptr = NULL;
		psi_impl_func_free(&impl->func);
		psi_plist_free(impl->stmts.ret);
		psi_plist_free(impl->stmts.let);
		psi_plist_free(impl->stmts.set);
		psi_plist_free(impl->stmts.fre);
		psi_plist_free(impl->stmts.ass);
		free(impl);
	}
}

void psi_impl_dump(struct psi_dump *dump, struct psi_impl *impl)
{
	size_t i;
	struct psi_return_stmt *ret;
	struct psi_let_stmt *let;
	struct psi_set_stmt *set;
	struct psi_free_stmt *fre;
	struct psi_assert_stmt *ass;

	psi_impl_func_dump(dump, impl->func);
	PSI_DUMP(dump, " {\n");
	for (i = 0; psi_plist_get(impl->stmts.let, i, &let); ++i) {
		psi_let_stmt_dump(dump, let);
	}
	for (i = 0; psi_plist_get(impl->stmts.ass, i, &ass); ++i) {
		psi_assert_stmt_dump(dump, ass);
	}
	for (i = 0; psi_plist_get(impl->stmts.ret, i, &ret); ++i) {
		psi_return_stmt_dump(dump, ret);
	}
	for (i = 0; psi_plist_get(impl->stmts.set, i, &set); ++i) {
		psi_set_stmt_dump(dump, set);
	}
	for (i = 0; psi_plist_get(impl->stmts.fre, i, &fre); ++i) {
		psi_free_stmt_dump(dump, fre);
	}
	PSI_DUMP(dump, "}\n");
}

bool psi_impl_validate(struct psi_data *data, struct psi_impl *impl,
		struct psi_validate_scope *scope)
{
	scope->impl = impl;

	if (!psi_impl_func_validate(data, impl->func, scope)) {
		return false;
	}
	if (!psi_return_stmt_validate(data, scope)) {
		return false;
	}
	if (!psi_let_stmts_validate(data, scope)) {
		return false;
	}
	if (!psi_set_stmts_validate(data, scope)) {
		return false;
	}
	if (!psi_assert_stmts_validate(data, scope)) {
		return false;
	}
	if (!psi_free_stmts_validate(data, scope)) {
		return false;
	}
	return true;
}

size_t psi_impl_num_min_args(struct psi_impl *impl)
{
	size_t i;
	struct psi_impl_arg *arg;

	for (i = 0; psi_plist_get(impl->func->args, i, &arg); ++i) {
		if (arg->def) {
			break;
		}
	}
	return i;
}

void psi_impl_stmt_free(struct psi_token ***abstract_stmt)
{
	switch ((**abstract_stmt)->type) {
	case PSI_T_LET:
		psi_let_stmt_free((void *) abstract_stmt);
		break;
	case PSI_T_SET:
		psi_set_stmt_free((void *) abstract_stmt);
		break;
	case PSI_T_RETURN:
		psi_return_stmt_free((void *) abstract_stmt);
		break;
	case PSI_T_FREE:
		psi_free_stmt_free((void *) abstract_stmt);
		break;
	case PSI_T_PRE_ASSERT:
	case PSI_T_POST_ASSERT:
		psi_assert_stmt_free((void *) abstract_stmt);
		break;
	default:
		assert(0);
	}
}

struct psi_decl_arg *psi_impl_get_decl_arg(struct psi_impl *impl,
		struct psi_decl_var *var)
{
	struct psi_return_stmt *ret;

	if (psi_plist_get(impl->stmts.ret, 0, &ret)) {
		if (ret->exp->args) {
			size_t i = 0;
			struct psi_decl_var *arg;

			while (psi_plist_get(ret->exp->args, i++, &arg)) {
				if (zend_string_equals(var->name, arg->name)) {
					return var->arg = arg->arg;
				}
			}
		}
	}

	return psi_decl_get_arg(impl->decl, var);
}

struct psi_let_stmt *psi_impl_get_let(struct psi_impl *impl,
		struct psi_decl_var* var)
{
	size_t i = 0;
	struct psi_let_stmt *let;

	while (psi_plist_get(impl->stmts.let, i++, &let)) {
		if (let->exp->var->arg == var->arg) {
			return let;
		}
	}
	return NULL;
}

struct psi_impl_arg *psi_impl_get_arg(struct psi_impl *impl,
		struct psi_impl_var* var)
{
	size_t i = 0;
	struct psi_impl_arg *iarg;

	while (psi_plist_get(impl->func->args, i++, &iarg)) {
		if (zend_string_equals(var->name, iarg->var->name)) {
			return var->arg = iarg;
		}
	}
	return NULL;
}

struct psi_decl_arg *psi_impl_get_temp_let_arg(struct psi_impl *impl,
		struct psi_decl_var* var)
{
	size_t j = 0;
	struct psi_let_stmt *let = NULL;

	while (psi_plist_get(impl->stmts.let, j++, &let)) {
		if (let->exp->kind != PSI_LET_TMP) {
			continue;
		}
		if (!zend_string_equals(let->exp->var->name, var->name)) {
			continue;
		}
		return var->arg = let->exp->var->arg;
	}
	return NULL;
}
