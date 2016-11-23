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

#ifndef PSI_PARSER_H
#define PSI_PARSER_H

#include <stdarg.h>

#define BSIZE 256

#include "token.h"
#include "types.h"
#include "data.h"

struct psi_parser {
	PSI_DATA_MEMBERS;
	token_t num;
	unsigned line, col;
	char *cur, *tok, *lim, *eof, *ctx, *mrk;

	/* internals */
	void *proc;

	struct {
		HashTable defs;
		unsigned level;
		unsigned skip;
	} cpp;

	struct {
		enum psi_parser_input_type {
			PSI_PARSE_FILE = 1,
			PSI_PARSE_STRING
		} type;

		union {
			struct {
				FILE *handle;
				char *buffer;
#if HAVE_MMAP
				size_t length;
#endif
			} file;
			struct {
				char *buffer;
				size_t length;
			} string;
		} data;
	} input;
};

struct psi_parser *psi_parser_init(struct psi_parser *P, psi_error_cb error, unsigned flags);
bool psi_parser_open_file(struct psi_parser *P, const char *filename);
bool psi_parser_open_string(struct psi_parser *P, const char *string, size_t length);
token_t psi_parser_scan(struct psi_parser *P);
void psi_parser_parse(struct psi_parser *P, struct psi_token *src);
void psi_parser_dtor(struct psi_parser *P);
void psi_parser_free(struct psi_parser **P);

#endif
