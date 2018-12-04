/*******************************************************************************
 Copyright (c) 2018, Michael Wallner <mike@php.net>.
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

#ifndef PSI_DEBUG_H
#define PSI_DEBUG_H

#include <stdarg.h>
#include <stdio.h>

#include "data.h"

#if PSI_THREADED_PARSER
void psi_debug_lock(struct psi_data *data);
void psi_debug_unlock(struct psi_data *data);
#else
# define psi_debug_lock(ctx)
# define psi_debug_unlock(ctx)
#endif

#define PSI_DEBUG_PRINT(ctx, ...) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		psi_debug_lock(PSI_DATA(ctx)); \
		dprintf(PSI_DATA(ctx)->debug_fd, __VA_ARGS__); \
		psi_debug_unlock(PSI_DATA(ctx)); \
	} \
} while(0)

#define PSI_DEBUG_PRINTV(ctx, msg, argv) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		psi_debug_lock(PSI_DATA(ctx)); \
		vdprintf(PSI_DATA(ctx)->debug_fd, msg, argv); \
		psi_debug_unlock(PSI_DATA(ctx)); \
	} \
} while(0)

#define PSI_DEBUG_DUMP(ctx, dump_func, ...) do { \
	if ((ctx) && (PSI_DATA(ctx)->flags & PSI_DEBUG)) { \
		struct psi_dump dump_ = {{ .fd = PSI_DATA(ctx)->debug_fd}, \
				.fun = (psi_dump_cb) dprintf}; \
		psi_debug_lock(PSI_DATA(ctx)); \
		dump_func(&dump_, __VA_ARGS__); \
		psi_debug_unlock(PSI_DATA(ctx)); \
	} \
} while (0)

#endif /* PSI_DEBUG_H */
