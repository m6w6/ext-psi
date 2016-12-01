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

#ifndef PSI_CALC_H
#define PSI_CALC_H

#include "token.h"
#include "impl_val.h"

#define PRIfval "f"
#define PRIdval "lf"
#define PRIldval "Lf"

typedef token_t (*psi_calc)(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);

token_t psi_calc_add(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_sub(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_mul(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_div(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_mod(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);

token_t psi_calc_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_bin_not(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);

token_t psi_calc_bin_lshift(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_bin_rshift(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_bin_and(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_bin_xor(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);
token_t psi_calc_bin_or(token_t t1, impl_val *v1, token_t t2, impl_val *v2, impl_val *res);

void psi_calc_cast(token_t in_type, impl_val *in_val, token_t out_type, impl_val *out_val);

#endif
