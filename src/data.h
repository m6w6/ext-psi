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

#ifndef PSI_DATA_H
#define PSI_DATA_H

#include "types.h"
#include "error.h"
#include "plist.h"
#include "validate.h"
#include "dump.h"
#include "debug.h"

#include <stdarg.h>
#include <dlfcn.h>
#include <unistd.h>

#define PSI_DEBUG 0x1
#define PSI_SILENT 0x2

#if PSI_THREADED_PARSER
zend_string *psi_string_init_interned(const char *buf, size_t len, int p);
zend_string *psi_new_interned_string(zend_string *str);
#else
# define psi_string_init_interned zend_string_init_interned
# define psi_new_interned_string zend_new_interned_string
#endif


#define PSI_DATA(D) ((struct psi_data *) (D))

#define PSI_DATA_MEMBERS \
	struct psi_decl_file file; \
	struct psi_plist *consts; \
	struct psi_plist *types; \
	struct psi_plist *structs; \
	struct psi_plist *unions; \
	struct psi_plist *enums; \
	struct psi_plist *decls; \
	struct psi_plist *vars; \
	struct psi_plist *impls; \
	psi_error_cb error; \
	char last_error[0x1000]; \
	unsigned errors; \
	unsigned flags; \
	int debug_fd

struct psi_data {
	PSI_DATA_MEMBERS;
};

struct psi_data *psi_data_ctor(struct psi_data *data, psi_error_cb error, unsigned flags);
struct psi_data *psi_data_ctor_with_dtors(struct psi_data *data, psi_error_cb error, unsigned flags);
struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src);
void psi_data_dtor(struct psi_data *data);
void psi_data_dump(struct psi_dump *dump, struct psi_data *data);

#endif
