#ifndef _PSI_DATA_H
#define _PSI_DATA_H

#include "types.h"
#include "error.h"

#define PSI_DATA(D) ((struct psi_data *) (D))

#define PSI_DATA_MEMBERS \
	constants *consts; \
	decl_typedefs *defs; \
	decl_structs *structs; \
	decl_unions *unions; \
	decl_enums *enums; \
	decls *decls; \
	impls *impls; \
	union { \
		decl_file file; \
		decl_libs libs; \
	} psi; \
	psi_error_cb error; \
	unsigned errors; \
	unsigned flags

struct psi_data {
	PSI_DATA_MEMBERS;
};

struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src);
void psi_data_dtor(struct psi_data *data);

#endif
