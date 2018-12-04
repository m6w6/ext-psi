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

#ifndef PSI_DUMP_H
#define PSI_DUMP_H

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

union psi_dump_arg {
	void *hn;
	int fd;
};

typedef int (*psi_dump_cb)(union psi_dump_arg, const char *msg, ...);

struct psi_dump {
	union psi_dump_arg ctx;
	psi_dump_cb fun;
};

const struct psi_dump psi_dump_stdout;
const struct psi_dump psi_dump_stderr;

#define PSI_DUMP(dump, ...) do { \
	const struct psi_dump *_dump_ptr = dump; \
	if (!_dump_ptr) { \
		_dump_ptr = &psi_dump_stdout; \
	} \
	_dump_ptr->fun(_dump_ptr->ctx, __VA_ARGS__); \
} while(0)


#endif /* PSI_DUMP_H */
