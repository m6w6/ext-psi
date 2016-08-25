#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include <string.h>

#include "data.h"

struct psi_data *psi_data_exchange(struct psi_data *dest, struct psi_data *src) {
	if (!dest) {
		dest = malloc(sizeof(*dest));
	}
	memcpy(dest, src, sizeof(*dest));
	memset(src, 0, sizeof(*src));
	return dest;
}

void psi_data_dtor(struct psi_data *data) {
	if (data->consts) {
		free_constants(data->consts);
	}
	if (data->defs) {
		free_decl_typedefs(data->defs);
	}
	if (data->structs) {
		free_decl_structs(data->structs);
	}
	if (data->unions) {
		free_decl_unions(data->unions);
	}
	if (data->enums) {
		free_decl_enums(data->enums);
	}
	if (data->decls) {
		free_decls(data->decls);
	}
	if (data->impls) {
		free_impls(data->impls);
	}
	free_decl_file(&data->psi.file);
}

