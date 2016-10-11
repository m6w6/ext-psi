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
#else
# include "php_config.h"
#endif

#include <stdlib.h>
#include <stdio.h>

#include "data.h"

decl_typedefs *add_decl_typedef(decl_typedefs *defs, decl_arg *def) {
	if (!defs) {
		defs = calloc(1, sizeof(*defs));
	}
	defs->list = realloc(defs->list, ++defs->count * sizeof(*defs->list));
	defs->list[defs->count - 1] = def;
	return defs;
}

void free_decl_typedefs(decl_typedefs *defs) {
	size_t i;
	for (i = 0; i < defs->count; ++i) {
		free_decl_arg(defs->list[i]);
	}
	free(defs->list);
	free(defs);
}

static inline void dump_typedef(int fd, decl_arg *tdef) {
	dprintf(fd, "typedef ");
	dump_decl_arg(fd, tdef, 0);
	dprintf(fd, ";");
}

void dump_decl_typedefs(int fd, decl_typedefs *defs) {
	size_t i;

	for (i = 0; i < defs->count; ++i) {
		decl_arg *tdef = defs->list[i];

		dump_typedef(fd, tdef);
		dprintf(fd, "\n");
	}
}

int validate_decl_typedef(struct psi_data *data, decl_arg *def) {
	if (!validate_decl_type(data, def->type, def)) {
		const char *pre;

		switch (def->type->type) {
		case PSI_T_STRUCT:	pre = "struct ";	break;
		case PSI_T_UNION:	pre = "union ";		break;
		case PSI_T_ENUM:	pre = "enum ";		break;
		default:			pre = "";			break;
		}
		data->error(data, def->token, PSI_WARNING,
			"Type '%s' cannot be aliased to %s'%s'",
			def->var->name, pre, def->type->name);
		return 0;
	}
	if (def->type->type == PSI_T_VOID) {
		if (def->var->pointer_level) {
			def->type->type = PSI_T_POINTER;
		} else {
			data->error(data, def->token, PSI_WARNING,
				"Type '%s' cannot be aliased to 'void'",
				def->type->name);
			return 0;
		}
	}
	return 1;
}
