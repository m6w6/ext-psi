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

#ifndef PSI_TYPES_SET_VALUE_H
#define PSI_TYPES_SET_VALUE_H

#include "set_func.h"
#include "decl_vars.h"
#include "decl_args.h"
#include "num_exp.h"
#include "impl_val.h"

typedef struct set_value {
	set_func *func;
	decl_vars *vars;
	num_exp *num;
	struct {
		struct set_value *set;
		impl_val *val;
	} outer;
	struct set_values *inner;
} set_value;

set_value *init_set_value(set_func *func, decl_vars *vars);
set_value *add_inner_set_value(set_value *val, set_value *inner);
void free_set_value(set_value *val);
void dump_set_value(int fd, set_value *set, unsigned level, int last);

#include <stdarg.h>

struct psi_data;

int validate_set_value(struct psi_data *data, set_value *set, ...);
int validate_set_value_ex(struct psi_data *data, set_value *set, decl_arg *ref, decl_args *ref_list);

#endif
