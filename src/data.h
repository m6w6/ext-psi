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

#include <stdarg.h>
#include <dlfcn.h>

#define PSI_DEBUG 0x1
#define PSI_SILENT 0x2

#ifndef RTLD_NEXT
# define RTLD_NEXT ((void *) -1l)
#endif
#ifndef RTLD_DEFAULT
# define RTLD_DEFAULT ((void *) 0)
#endif

static inline void *psi_dlsym(struct psi_plist *dllist, const char *name, const char *redir)
{
	void *dl, *sym = NULL;
	const char *test = redir ?: name;

again:
	if (dllist) {
		size_t i = 0;

		while (!sym && psi_plist_get(dllist, i++, &dl)) {
			sym = dlsym(dl, test);
		}
	}
	if (!sym) {
		sym = dlsym(RTLD_DEFAULT, test);
	}
	if (!sym && test == redir) {
		test = name;
		goto again;
	}

	return sym;
}

#define PSI_DEBUG_PRINT(ctx, ...) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		dprintf(PSI_DATA(ctx)->debug_fd, __VA_ARGS__); \
	} \
} while(0)
#define PSI_DEBUG_PRINTV(ctx, msg, argv) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		vdprintf(PSI_DATA(ctx)->debug_fd, msg, argv); \
	} \
} while(0)
#define PSI_DEBUG_DUMP(ctx, dump_func, ...) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		struct psi_dump dump_ = {{ .fd = PSI_DATA(ctx)->debug_fd}, \
				.fun = (psi_dump_cb) dprintf}; \
		dump_func(&dump_, __VA_ARGS__); \
	} \
} while (0)

union psi_dump_arg {
	void *hn;
	int fd;
};
typedef void (*psi_dump_cb)(union psi_dump_arg, const char *msg, ...);
struct psi_dump {
	union psi_dump_arg ctx;
	psi_dump_cb fun;
};
#define PSI_DUMP(dump, ...) do { \
	struct psi_dump _dump_tmp, *_dump_ptr = dump; \
	if (!_dump_ptr) { \
		_dump_ptr = &_dump_tmp; \
		_dump_tmp.ctx.fd = STDOUT_FILENO; \
		_dump_tmp.fun = (psi_dump_cb) dprintf; \
	} \
	_dump_ptr->fun(_dump_ptr->ctx, __VA_ARGS__); \
} while(0)

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
