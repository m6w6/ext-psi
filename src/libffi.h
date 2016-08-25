#ifndef _PSI_LIBFFI_H
#define _PSI_LIBFFI_H

#include "context.h"

#ifdef HAVE_LIBFFI
struct psi_context_ops *psi_libffi_ops(void);
#endif

#endif
