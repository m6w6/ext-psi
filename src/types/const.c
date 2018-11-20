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

struct psi_const *psi_const_init(struct psi_impl_type *type, zend_string *name,
		struct psi_impl_def_val *val)
{
	struct psi_const *c = pecalloc(1, sizeof(*c), 1);

	if (name->val[0] == '\\') {
		c->name = zend_string_init(&name->val[1], name->len-1, 1);
	} else {
		c->name = zend_string_copy(name);
	}
	c->type = type;
	c->val = val;
	return c;
}

void psi_const_free(struct psi_const **constant_ptr)
{
	if (*constant_ptr) {
		struct psi_const *constant = *constant_ptr;

		*constant_ptr = NULL;
		psi_token_free(&constant->token);
		psi_impl_type_free(&constant->type);
		zend_string_release(constant->name);
		psi_impl_def_val_free(&constant->val);
		free(constant);
	}
}

void psi_const_dump(struct psi_dump *dump, struct psi_const *cnst)
{
	PSI_DUMP(dump, "const ");
	if (cnst->type) {
		psi_impl_type_dump(dump, cnst->type);
	}
	PSI_DUMP(dump, " %s = ", cnst->name->val);
	psi_impl_def_val_dump(dump, cnst->val);
	PSI_DUMP(dump, ";");
}

bool psi_const_validate(struct psi_data *data, struct psi_const *c,
		struct psi_validate_scope *scope)
{
	if (!psi_impl_def_val_validate(data, c->val, c->type, scope)) {
		return false;
	}
	return true;
}
