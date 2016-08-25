#ifndef _PSI_LIBJIT_H
#define _PSI_LIBJIT_H

#include "context.h"

#ifdef HAVE_LIBJIT
struct psi_context_ops *psi_libjit_ops(void);
#endif

#endif
