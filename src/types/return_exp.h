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

#ifndef PSI_TYPES_RETURN_EXP_H
#define PSI_TYPES_RETURN_EXP_H

struct psi_return_exp {
	struct psi_token *token;
	struct psi_decl_var *func;
	struct psi_plist *args;
	struct psi_set_exp *set;
};

struct psi_return_exp *psi_return_exp_init(struct psi_decl_var *func,
		struct psi_plist *args, struct psi_set_exp *set);
void psi_return_exp_free(struct psi_return_exp **exp_ptr);
void psi_return_exp_dump(int fd, struct psi_return_exp *exp);
void psi_return_exp_exec(struct psi_return_exp *exp, zval *return_value,
		struct psi_call_frame *frame);
bool psi_return_exp_validate(struct psi_data *data, struct psi_return_exp *exp,
		struct psi_impl *impl);
const char *psi_return_exp_get_decl_name(struct psi_return_exp *exp);

#endif /* RETURN_EXP_H */
