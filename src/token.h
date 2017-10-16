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

#ifndef PSI_TOKEN_H
#define PSI_TOKEN_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <sys/param.h>

static inline size_t psi_align(size_t s, size_t a) {
	return ((s - 1) | (a - 1)) + 1;
}

static inline size_t psi_offset_padding(size_t diff, size_t alignment) {
	if (diff && diff <= psi_align(diff, alignment)) {
		diff = 0;
	}

	return diff;
}

#include "parser_proc.h"
#undef YYDEBUG

#if SIZEOF_CHAR == SIZEOF_INT8_T
# define ALIGNOF_INT8_T ALIGNOF_CHAR
# define ALIGNOF_UINT8_T ALIGNOF_CHAR
#else
# error SIZEOF_CHAR != 8
#endif
#if SIZEOF_SHORT == SIZEOF_INT16_T
# define ALIGNOF_INT16_T ALIGNOF_SHORT
# define ALIGNOF_UINT16_T ALIGNOF_SHORT
#else
# error SIZEOF_SHORT != 16
#endif
#if SIZEOF_INT == SIZEOF_INT32_T
# define ALIGNOF_INT32_T ALIGNOF_INT
# define ALIGNOF_UINT32_T ALIGNOF_INT
#elif SIZEOF_LONG == SIZEOF_INT32_T
# define ALIGNOF_INT32_T ALIGNOF_LONG
# define ALIGNOF_UINT32_T ALIGNOF_LONG
#else
# error SIZEOF_INT != 32 and SIZEOF_LONG != 32
#endif
#if SIZEOF_LONG == SIZEOF_INT64_T
# define ALIGNOF_INT64_T ALIGNOF_LONG
# define ALIGNOF_UINT64_T ALIGNOF_LONG
# elif HAVE_LONG_LONG_INT && SIZEOF_LONG_LONG_INT == SIZEOF_INT64_T
# define ALIGNOF_INT64_T ALIGNOF_LONG_LONG
# define ALIGNOF_UINT64_T ALIGNOF_LONG_LONG
#else
# error SIZEOF_LONG != 64 and SIZEOF_LONG_LONG != 64
#endif

#if HAVE_INT128
# define SIZEOF_INT128_T SIZEOF___INT128
# define SIZEOF_UINT128_T SIZEOF_UNSIGNED___INT128
# define ALIGNOF_INT128_T ALIGNOF___INT128
# define ALIGNOF_UINT128_T ALIGNOF___INT128
# define INT128_MAX ((__int128) (UINT128_MAX >> 1))
# define INT128_MIN (-INT128_MAX-1)
# define UINT128_MAX ((unsigned __int128) ~ 0)
typedef __int128 int128_t;
typedef unsigned __int128 uint128_t;
#endif

typedef enum psi_token_type token_t;

static inline size_t psi_t_alignment(token_t t)
{
#define PSI_ALIGNOF(T) case PSI_T_## T: return ALIGNOF_## T ##_T;
	switch (t) {
	PSI_ALIGNOF(INT8);
	PSI_ALIGNOF(UINT8);
	PSI_ALIGNOF(INT16);
	PSI_ALIGNOF(UINT16);
	PSI_ALIGNOF(INT32);
	PSI_ALIGNOF(UINT32);
	PSI_ALIGNOF(INT64);
	PSI_ALIGNOF(UINT64);
#if HAVE_INT128
	PSI_ALIGNOF(INT128);
	PSI_ALIGNOF(UINT128);
#endif
	case PSI_T_FLOAT:
		return ALIGNOF_FLOAT;
	case PSI_T_DOUBLE:
		return ALIGNOF_DOUBLE;
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return ALIGNOF_VOID_P;
	case PSI_T_ENUM:
		return ALIGNOF_INT;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		return ALIGNOF_LONG_DOUBLE;
#endif
	default:
		assert(0);
	}
	return 0;
}

static inline size_t psi_t_size(token_t t)
{
#define PSI_SIZEOF(T) case PSI_T_## T : return SIZEOF_## T ##_T;
	switch (t) {
	PSI_SIZEOF(INT8);
	PSI_SIZEOF(UINT8);
	PSI_SIZEOF(INT16);
	PSI_SIZEOF(UINT16);
	PSI_SIZEOF(INT32);
	PSI_SIZEOF(UINT32);
	PSI_SIZEOF(INT64);
	PSI_SIZEOF(UINT64);
#if HAVE_INT128
	PSI_SIZEOF(INT128);
	PSI_SIZEOF(UINT128);
#endif
	case PSI_T_FLOAT:
		return SIZEOF_FLOAT;
	case PSI_T_DOUBLE:
		return SIZEOF_DOUBLE;
	case PSI_T_VOID:
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return SIZEOF_VOID_P;
	case PSI_T_ENUM:
		return SIZEOF_INT;
#ifdef HAVE_LONG_DOUBLE
	case PSI_T_LONG_DOUBLE:
		return SIZEOF_LONG_DOUBLE;
#endif
	default:
		assert(!t);
	}
	return 0;
}

static inline const char *psi_t_indent(unsigned level) {
	static const char indent[] =
			"\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
	return &indent[32 - MIN(32, level)];
}

static inline const char *psi_t_indirection(unsigned pointer_level) {
	static const char indir[] = "********************************";
	return &indir[32 - MIN(32, pointer_level)];
}

struct psi_token {
	token_t type;
	unsigned size, line, col, flags;
	char *text, *file;
	char buf[1];
};

struct psi_parser;

struct psi_token *psi_token_init(token_t token_typ, const char *token_txt,
		size_t token_len, unsigned col, unsigned line, const char *file);
size_t psi_token_alloc_size(size_t token_len, size_t fname_len);
struct psi_token *psi_token_copy(struct psi_token *src);
void psi_token_copy_ctor(struct psi_token **src);
struct psi_token *psi_token_cat(const char *sep, unsigned argc, ...);
struct psi_token *psi_token_prepend(const char *sep, struct psi_token *T, unsigned argc, ...);
struct psi_token *psi_token_append(const char *sep, struct psi_token *T, unsigned argc, ...);
struct psi_token *psi_token_translit(struct psi_token *T, char *from, char *to);
uint64_t psi_token_hash(struct psi_token *t, char *digest_buf);
void psi_token_dump(int fd, struct psi_token *t);
void psi_token_free(struct psi_token **token);

#endif
