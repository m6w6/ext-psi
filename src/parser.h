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

struct psi_parser;

#include "parser_proc.h"
#undef YYDEBUG

#include "data.h"
#include "token.h"
#include "types.h"
#include "cpp.h"

struct psi_cpp;

struct psi_parser {
	PSI_DATA_MEMBERS;

	struct psi_cpp *preproc;
};

struct psi_parser_input {
	size_t length;
	char *file;
	unsigned lines;
	char buffer[1];
};

struct psi_parser_data {
	enum {
		PSI_PARSER_DATA_SELF,
		PSI_PARSER_DATA_CPP
	} type;
	union {
		struct psi_parser *parser;
		struct psi_cpp *cpp;
	} data;
};

struct psi_parser *psi_parser_init(struct psi_parser *P, psi_error_cb error, unsigned flags);
struct psi_parser_input *psi_parser_open_file(struct psi_parser *P, const char *filename, bool report_errors);
struct psi_parser_input *psi_parser_open_string(struct psi_parser *P, const char *string, size_t length);
struct psi_plist *psi_parser_scan(struct psi_parser *P, struct psi_parser_input *I);
struct psi_plist *psi_parser_preprocess(struct psi_parser *P, struct psi_plist **tokens);
bool psi_parser_process(struct psi_parser *P, struct psi_plist *tokens, size_t *processed);
bool psi_parser_parse(struct psi_parser *P, struct psi_parser_input *I);
void psi_parser_dtor(struct psi_parser *P);
void psi_parser_free(struct psi_parser **P);


#endif
