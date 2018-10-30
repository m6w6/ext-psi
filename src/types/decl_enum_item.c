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

struct psi_decl_enum_item *psi_decl_enum_item_init(zend_string *name,
		struct psi_num_exp *num)
{
	struct psi_decl_enum_item *i = calloc(1, sizeof(*i));
	i->name = zend_string_copy(name);
	i->num = num;
	return i;
}

void psi_decl_enum_item_free(struct psi_decl_enum_item **i_ptr)
{
	if (*i_ptr) {
		struct psi_decl_enum_item *i = *i_ptr;

		*i_ptr = NULL;
		psi_token_free(&i->token);
		if (i->num) {
			if (i->num == &i->inc) {
				switch (i->inc.op) {
				case PSI_T_NUMBER:
					psi_number_free(&i->inc.data.n);
					break;
				case PSI_T_PLUS:
					psi_num_exp_free(&i->inc.data.b.lhs);
					psi_num_exp_free(&i->inc.data.b.rhs);
					break;
				default:
					assert(0);
				}
			} else {
				psi_num_exp_free(&i->num);
			}
		}
		zend_string_release(i->name);
		free(i);
	}
}

void psi_decl_enum_item_dump(int fd, struct psi_decl_enum_item *item)
{
	dprintf(fd, "%s", item->name->val);
	if (item->num && item->num != &item->inc) {
		dprintf(fd, " = ");
		psi_num_exp_dump(fd, item->num);
	}
}

bool psi_decl_enum_item_validate(struct psi_data *data,
		struct psi_decl_enum *enm, struct psi_decl_enum_item *item, size_t seq)
{
	struct psi_validate_scope scope = {0};

	if (!item->num) {
		if (seq) {
			int64_t one = 1;

			item->inc.op = PSI_T_PLUS;
			item->inc.data.b.lhs = psi_num_exp_init_unary(PSI_T_LPAREN,
					psi_num_exp_copy(item->prev->num));
			item->inc.data.b.rhs = psi_num_exp_init_num(
							psi_number_init(PSI_T_INT64, &one, 0));
			item->num = &item->inc;
		} else {
			int64_t nil = 0;

			item->inc.op = PSI_T_NUMBER;
			item->inc.data.n = psi_number_init(PSI_T_INT64, &nil, 0);
			item->num = &item->inc;
		}
	}

	scope.current_enum = enm;
	if (!psi_num_exp_validate(data, item->num, &scope)) {
		return false;
	}

	item->val = psi_num_exp_get_long(item->num, NULL, NULL);

	return true;
}
