#ifndef _PSI_TOKEN_H
#define _PSI_TOKEN_H

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>

#include "parser_proc.h"

#define PSI_T_POINTER PSI_T_ASTERISK
#define PSI_T_LONG_DOUBLE (PSI_T_DOUBLE << 16)

typedef int token_t;

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
	case PSI_T_FLOAT:
		return ALIGNOF_FLOAT;
	case PSI_T_DOUBLE:
		return ALIGNOF_DOUBLE;
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return ALIGNOF_VOID_P;
	case PSI_T_ENUM:
		return ALIGNOF_INT;
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
	case PSI_T_FLOAT:
		return SIZEOF_FLOAT;
	case PSI_T_DOUBLE:
		return SIZEOF_DOUBLE;
	case PSI_T_POINTER:
	case PSI_T_FUNCTION:
		return SIZEOF_VOID_P;
	case PSI_T_ENUM:
		return SIZEOF_INT;
	default:
		assert(0);
	}
	return 0;
}

struct psi_token {
	token_t type;
	unsigned size, line, col;
	char *text, *file;
	char buf[1];
};

struct psi_parser;

struct psi_token *psi_token_alloc(struct psi_parser *P);
size_t psi_token_alloc_size(size_t token_len, size_t fname_len);
struct psi_token *psi_token_copy(struct psi_token *src);
struct psi_token *psi_token_cat(unsigned argc, ...);
struct psi_token *psi_token_append(struct psi_token *T, unsigned argc, ...);
struct psi_token *psi_token_translit(struct psi_token *T, char *from, char *to);
uint64_t psi_token_hash(struct psi_token *t, char *digest_buf);

#endif
