%include {
#include "php_psi_stdinc.h"

#include <assert.h>
#include <stdarg.h>

#include "plist.h"
#include "parser.h"

/* rename lemon symbols, works better than DEF(%name) */
#define ParseAlloc psi_parser_proc_init_ex
#define Parse psi_parser_proc_parse
#define ParseTrace psi_parser_proc_trace
#define ParseFree psi_parser_proc_free_ex

/* fwd decls */
void *ParseAlloc(void *(*mallocProc)(size_t));
void ParseFree(void *p, void (*freeProc)(void*));

/* wrappers */
void *psi_parser_proc_init(void)
{
	return ParseAlloc(malloc);
}

void psi_parser_proc_free(void **parser_proc)
{
	if (*parser_proc) {
		ParseFree(*parser_proc, free);
		*parser_proc = NULL;
	}
}

}
