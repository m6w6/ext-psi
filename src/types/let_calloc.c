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

struct psi_let_calloc *psi_let_calloc_init(struct psi_num_exp *nmemb,
		struct psi_num_exp *size)
{
	struct psi_let_calloc *alloc = calloc(1, sizeof(*alloc));

	alloc->nmemb = nmemb;
	alloc->size = size;

	return alloc;
}

void psi_let_calloc_free(struct psi_let_calloc **alloc_ptr)
{
	if (*alloc_ptr) {
		struct psi_let_calloc *alloc = *alloc_ptr;

		*alloc_ptr = NULL;
		psi_num_exp_free(&alloc->nmemb);
		psi_num_exp_free(&alloc->size);
		if (alloc->token) {
			free(alloc->token);
		}
		free(alloc);
	}
}

void psi_let_calloc_dump(int fd, struct psi_let_calloc *alloc)
{
	dprintf(fd, "calloc(");
	psi_num_exp_dump(fd, alloc->nmemb);
	dprintf(fd, ", ");
	psi_num_exp_dump(fd, alloc->size);
	dprintf(fd, ")");
}
