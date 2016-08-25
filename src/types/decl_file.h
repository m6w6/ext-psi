#ifndef _PSI_TYPES_DECL_FILE_H
#define _PSI_TYPES_DECL_FILE_H

typedef struct decl_file {
	char *ln;
	char *fn;
} decl_file;

static inline void free_decl_file(decl_file *file) {
	if (file->ln) {
		free(file->ln);
	}
	if (file->fn) {
		free(file->fn);
	}
	memset(file, 0, sizeof(*file));
}

#endif
