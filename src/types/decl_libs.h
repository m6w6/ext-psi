#ifndef _PSI_TYPES_DECL_LIBS_H
#define _PSI_TYPES_DECL_LIBS_H

typedef struct decl_libs {
	void **dl;
	size_t count;
} decl_libs;

static inline void free_decl_libs(decl_libs *libs) {
	if (libs->dl) {
		size_t i;
		for (i = 0; i < libs->count; ++i) {
			if (libs->dl[i]) {
				dlclose(libs->dl[i]);
			}
		}
		free(libs->dl);
	}
	memset(libs, 0, sizeof(*libs));
}

static inline void add_decl_lib(decl_libs *libs, void *dlopened) {
	libs->dl = realloc(libs->dl, ++libs->count * sizeof(*libs->dl));
	libs->dl[libs->count-1] = dlopened;
}

#endif
