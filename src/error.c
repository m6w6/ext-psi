/*******************************************************************************
 Copyright (c) 2016, Michael Wallner <mike@php.net>.
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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif
#include "data.h"

/* zend_error_cb */
#include "Zend/zend.h"
/* is executing/compiling query API */
#include "Zend/zend_compile.h"
#include "Zend/zend_execute.h"

/* PG(), strlcpy, vslprintf */
#include "php.h"

void psi_error_wrapper(struct psi_data *context, struct psi_token *t, int type, const char *msg, ...)
{
	va_list argv;
	const char *fn = NULL;
	unsigned ln = 0;

	if (context) {
		if (context->flags & PSI_SILENT) {
			/* context->last_error may be an argument to print */
			char error[sizeof(context->last_error)];

			va_start(argv, msg);
			vslprintf(error, sizeof(error), msg, argv);
			va_end(argv);

			memcpy(context->last_error, error,
					sizeof(context->last_error));
			return;
		}
	}

	if (t) {
		fn = t->file->val;
		ln = t->line;
	} else if (zend_is_executing()) {
		fn = zend_get_executed_filename();
		ln = zend_get_executed_lineno();
	} else if (zend_is_compiling()) {
		fn = zend_get_compiled_filename()->val;
		ln = zend_get_compiled_lineno();
	} else {
		fn = "PSI module startup";
	}

	va_start(argv, msg);
	psi_verror(type, fn, ln, msg, argv);
	va_end(argv);

	va_start(argv, msg);
	PSI_DEBUG_LOCK(context,
			PSI_DEBUG_PRINTV(context, msg, argv);
			PSI_DEBUG_PRINT(context, "\n");
	);
	va_end(argv);

	if (context) {
		strlcpy(context->last_error, PG(last_error_message)->val,
				sizeof(context->last_error));
	}
}

void psi_error(int type, const char *fn, unsigned ln, const char *msg, ...)
{
	va_list argv;

	va_start(argv, msg);
	psi_verror(type, fn, ln, msg, argv);
	va_end(argv);
}

void psi_verror(int type, const char *fn, unsigned ln, const char *msg, va_list argv)
{
	zend_string *message = zend_vstrpprintf(0, msg, argv);
	zend_error_cb(type, fn, ln, message);
	zend_string_release(message);
}
