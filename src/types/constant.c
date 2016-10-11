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
# else
# include "php_config.h"
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "constant.h"

constant *init_constant(const_type *type, const char *name, impl_def_val *val) {
	constant *c = calloc(1, sizeof(*c));
	c->type = type;
	c->name = strdup(name);
	c->val = val;
	return c;
}

void free_constant(constant *constant) {
	free_const_type(constant->type);
	free(constant->name);
	free_impl_def_val(constant->val);
	free(constant);
}

void dump_constant(int fd, constant *cnst) {
	dprintf(fd, "const ");
	dump_const_type(fd, cnst->type);
	dprintf(fd, " %s = ", cnst->name);
	dump_impl_def_val(fd, cnst->val);
	dprintf(fd, ";");
}

int validate_constant(struct psi_data *data, constant *c) {
	/* FIXME */
	return 1;
}
