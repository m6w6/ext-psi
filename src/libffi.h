#ifndef _PSI_LIBFFI_H
#define _PSI_LIBFFI_H

#include "context.h"

#ifdef HAVE_LIBFFI
PSI_ContextOps *PSI_Libffi(void);
#endif

#endif
