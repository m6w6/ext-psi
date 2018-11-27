/*******************************************************************************
 Copyright (c) 2018, Michael Wallner <mike@php.net>.
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

     * Redistributions of source code must retain the above copyright notice,
       this list of conditions and the following disclaimer.
     * Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#ifndef PSI_LIBFFI_COMPAT_H
#define PSI_LIBFFI_COMPAT_H

#include "php_psi_stdinc.h"

#undef PACKAGE
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#include <ffi.h>

#ifndef PSI_HAVE_FFI_CLOSURE_ALLOC
# if HAVE_UNISTD_H
#  include <unistd.h>
# endif
# if HAVE_SYS_MMAN_H
#  include <sys/mman.h>
#  ifndef MAP_ANONYMOUS
#   define MAP_ANONYMOUS MAP_ANON
#  endif
# endif
#endif

static inline void *psi_ffi_closure_alloc(size_t s, void **code)
{
#ifdef PSI_HAVE_FFI_CLOSURE_ALLOC
	return ffi_closure_alloc(s, code);
#elif HAVE_MMAP
	*code = mmap(NULL, s, PROT_EXEC|PROT_WRITE|PROT_READ,
			MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if (MAP_FAILED == *code) {
		return NULL;
	}
	return *code;
#else
# error "Neither ffi_closure_alloc() nor mmap() available"
#endif
}

static inline ffi_status psi_ffi_prep_closure(ffi_closure **closure, void **code, ffi_cif *sig, void (*handler)(ffi_cif*,void*,void**,void*), void *data) {
	*closure = psi_ffi_closure_alloc(sizeof(ffi_closure), code);
	assert(*closure != NULL);

#if PSI_HAVE_FFI_PREP_CLOSURE_LOC
	return ffi_prep_closure_loc(*closure, sig, handler, data, *code);

#elif PSI_HAVE_FFI_PREP_CLOSURE
	return ffi_prep_closure(*code, sig, handler, data);
#else
# error "Neither ffi_prep_closure() nor ffi_prep_closure_loc() is available"
	abort(); /* fix IDE warning */
#endif
}

static inline void psi_ffi_closure_free(void *c)
{
#ifdef PSI_HAVE_FFI_CLOSURE_ALLOC
	ffi_closure_free(c);
#elif HAVE_MMAP
	munmap(c, sizeof(ffi_closure));
#endif
}

static inline void psi_ffi_prep_va(ffi_cif *base, ffi_cif *signature, size_t argc, size_t va_count,
		ffi_type **param_types) {
	ffi_status rc;

#ifdef PSI_HAVE_FFI_PREP_CIF_VAR
	rc = ffi_prep_cif_var(signature, base->abi, argc, argc + va_count,
			base->rtype, param_types);
#else
	/* FIXME: test in config.m4; assume we can just call anyway */
	rc = ffi_prep_cif(signature, base->abi, argc + va_count, base->rtype, param_types);
#endif

	assert(FFI_OK == rc);
}


#endif /* LIBFFI_COMPAT_H */
