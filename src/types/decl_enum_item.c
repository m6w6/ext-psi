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

struct psi_decl_enum_item *psi_decl_enum_item_init(const char *name,
		struct psi_num_exp *num)
{
	struct psi_decl_enum_item *i = calloc(1, sizeof(*i));
	i->name = strdup(name);
	i->num = num;
	return i;
}

void psi_decl_enum_item_free(struct psi_decl_enum_item **i_ptr)
{
	if (*i_ptr) {
		struct psi_decl_enum_item *i = *i_ptr;

		*i_ptr = NULL;
		if (i->token) {
			free(i->token);
		}
		if (i->num && i->num != &i->inc) {
			psi_num_exp_free(&i->num);
		}
		free(i->name);
		free(i);
	}
}

void psi_decl_enum_item_dump(int fd, struct psi_decl_enum_item *item)
{
	dprintf(fd, "%s", item->name);
	if (item->num && item->num != &item->inc) {
		dprintf(fd, " = ");
		psi_num_exp_dump(fd, item->num);
	}
}

bool psi_decl_enum_item_validate(struct psi_data *data,
		struct psi_decl_enum *enm, struct psi_decl_enum_item *item, size_t seq)
{
	if (!item->num) {
		if (seq) {
			item->inc.type = PSI_T_INT64;
			item->inc.data.ival.i64 = 1;
			item->inc.op = PSI_T_PLUS;
			item->inc.operand = item->prev->num ? : &item->prev->inc;
			item->num = &item->inc;
		} else {
			item->inc.type = PSI_T_INT64;
			item->inc.data.ival.i64 = 0;
			item->num = &item->inc;
		}
	}

	if (!psi_num_exp_validate(data, item->num, NULL, NULL, NULL, NULL, enm)) {
		return false;
	}

	item->val = psi_long_num_exp(item->num, NULL);

	return true;
}
