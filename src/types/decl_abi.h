#ifndef _PSI_TYPES_DECL_ABI_H
#define _PSI_TYPES_DECL_ABI_H

typedef struct decl_abi {
	struct psi_token *token;
	char *convention;
} decl_abi;

static inline decl_abi *init_decl_abi(const char *convention) {
	decl_abi *abi = calloc(1, sizeof(*abi));
	abi->convention = strdup(convention);
	return abi;
}

static inline void free_decl_abi(decl_abi *abi) {
	if (abi->token) {
		free(abi->token);
	}
	free(abi->convention);
	free(abi);
}

#endif
