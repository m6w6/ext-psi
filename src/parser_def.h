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

#ifndef PSI_PARSER_INC
#define PSI_PARSER_INC

#define CONCAT2(x,y) x##y
#define CONCAT1(x,y) CONCAT2(x,y)
#define COUNTED(x) CONCAT1(parse_ ##x## _, __LINE__)

#define TOKEN_PREFIX PSI_T
#define TOKEN_STRUCT struct psi_token *

#ifdef GENERATE
# define DEF(dn, dv) dn dv
# define PASS(nt, rule) nt ::= rule.
# define PARSE(nt, rule) nt ::= rule.
# define PARSE_NAMED(nt, nt_name, rule) NAMED(nt, nt_name) ::= rule.
# define PARSE_TYPED(nt, nt_name, rule) TYPED(nt, nt_name) ::= rule.
# define TOKEN(t) t
# define NAMED(t, name) t(name)
# define TYPED(t, name) t(name)
# define TOKEN_TYPE(token, type_) %type token {type_}
# define TOKEN_DTOR(token, dtor) %destructor token {dtor}
# define T(token) token
# define TOKEN_CLASS(type, tokens) DEF(%token_class, type##_token tokens .)
#else
# ifndef TEST
#  include "parser.h"
#  include "plist.h"
# endif
# define DEF(dn, dv)
# define PASS(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P) { \
		(void) #rule; \
	}
# define PARSE(nt, rule) \
	static void COUNTED(nt) (struct psi_parser *P rule)
# define PARSE_NAMED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P NAMED(nt, nt_name) rule)
# define PARSE_TYPED(nt, nt_name, rule) \
	static void COUNTED(nt) (struct psi_parser *P TYPED(nt, nt_name) rule)
# define TOKEN(t)
# define NAMED(t, name) , struct psi_token *name
# define TYPED(t, name) , TOKEN_TYPE_NAME(t) name
# define TOKEN_TYPE_NAME(token) token##_parse_t
# define TOKEN_TYPE(token, type) typedef type TOKEN_TYPE_NAME(token);
# define TOKEN_DTOR(token, dtor)
# define T(token) CONCAT1(TOKEN_PREFIX, _ ##token ),
# define TOKEN_CLASS(type, tokens) static token_t type##_token[] = { tokens 0 };
#endif


#endif
