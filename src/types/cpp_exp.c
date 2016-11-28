/*******************************************************************************
 Copyright (c) 2017, Michael Wallner <mike@php.net>.
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

#include <assert.h>

#include "data.h"

struct psi_cpp_exp *psi_cpp_exp_init(token_t type, void *data)
{
	struct psi_cpp_exp *exp = calloc(1, sizeof(*exp));

	switch ((exp->type = type)) {
	case PSI_T_WARNING:
	case PSI_T_ERROR:
	case PSI_T_IFDEF:
	case PSI_T_IFNDEF:
		exp->data.tok = data;
		break;
	case PSI_T_DEFINE:
		exp->data.decl = data;
		break;
	case PSI_T_IF:
	case PSI_T_ELIF:
		exp->data.num = data;
		break;
	case PSI_T_ENDIF:
	case PSI_T_ELSE:
		break;
	default:
		assert(0);
		break;
	}
	return exp;
}

void psi_cpp_exp_free(struct psi_cpp_exp **exp_ptr)
{
	if (*exp_ptr) {
		struct psi_cpp_exp *exp = *exp_ptr;

		*exp_ptr = NULL;
		switch (exp->type) {
		case PSI_T_WARNING:
		case PSI_T_ERROR:
		case PSI_T_IFDEF:
		case PSI_T_IFNDEF:
			free(exp->data.tok);
			exp->data.tok = NULL;
			break;
		case PSI_T_DEFINE:
			psi_cpp_macro_decl_free(&exp->data.decl);
			break;
		case PSI_T_IF:
		case PSI_T_ELIF:
			psi_num_exp_free(&exp->data.num);
			break;
		case PSI_T_ENDIF:
		case PSI_T_ELSE:
			break;
		default:
			assert(0);
			break;
		}
		if (exp->token) {
			free(exp->token);
		}
		free(exp);
	}
}

void psi_cpp_exp_dump(int fd, struct psi_cpp_exp *exp)
{
	dprintf(fd, "#%s ", exp->token->text);
	switch (exp->type) {
	case PSI_T_WARNING:
	case PSI_T_ERROR:
	case PSI_T_IFDEF:
	case PSI_T_IFNDEF:
		dprintf(fd, "%s", exp->data.tok->text);
		break;
	case PSI_T_DEFINE:
		psi_cpp_macro_decl_dump(fd, exp->data.decl);
		break;
	case PSI_T_IF:
	case PSI_T_ELIF:
		psi_num_exp_dump(fd, exp->data.num);
		break;
	case PSI_T_ENDIF:
	case PSI_T_ELSE:
		break;
	default:
		assert(0);
		break;
	}
	dprintf(fd, "\n");
}
