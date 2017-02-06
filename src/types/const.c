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

struct psi_const *psi_const_init(struct psi_const_type *type, const char *name,
		struct psi_impl_def_val *val)
{
	struct psi_const *c = calloc(1, sizeof(*c));
	c->type = type;
	c->name = strdup(name[0] == '\\' ? &name[1] : name);
	c->val = val;
	return c;
}

void psi_const_free(struct psi_const **constant_ptr)
{
	if (*constant_ptr) {
		struct psi_const *constant = *constant_ptr;

		*constant_ptr = NULL;
		if (constant->token) {
			free(constant->token);
		}
		psi_const_type_free(&constant->type);
		free(constant->name);
		psi_impl_def_val_free(&constant->val);
		free(constant);
	}
}

void psi_const_dump(int fd, struct psi_const *cnst)
{
	dprintf(fd, "const ");
	psi_const_type_dump(fd, cnst->type);
	dprintf(fd, " %s = ", cnst->name);
	psi_impl_def_val_dump(fd, cnst->val);
	dprintf(fd, ";");
}

bool psi_const_validate(struct psi_data *data, struct psi_const *c)
{
	if (!psi_impl_def_val_validate(data, c->val, c->type->type, c->type->name)) {
		return false;
	}
	return true;
}
