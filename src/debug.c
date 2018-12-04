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

#ifdef HAVE_CONFIG_H
# include "config.h"
#else
# include "php_config.h"
#endif

#include "php.h"
#include "debug.h"

#if PSI_THREADED_PARSER

# include <pthread.h>

static pthread_mutex_t debug_mutex;
static pthread_mutexattr_t debug_attr;

void psi_debug_lock(struct psi_data *data)
{
	pthread_mutex_lock(&debug_mutex);
}

void psi_debug_unlock(struct psi_data *data)
{
	pthread_mutex_unlock(&debug_mutex);
}

#endif

PHP_MINIT_FUNCTION(psi_debug);
PHP_MINIT_FUNCTION(psi_debug)
{
#if PSI_THREADED_PARSER
	pthread_mutexattr_init(&debug_attr);
	pthread_mutexattr_settype(&debug_attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&debug_mutex, &debug_attr);
#endif

	return 0;
}

PHP_MSHUTDOWN_FUNCTION(psi_debug);
PHP_MSHUTDOWN_FUNCTION(psi_debug)
{
#if PSI_THREADED_PARSER
	pthread_mutex_destroy(&debug_mutex);
	pthread_mutexattr_destroy(&debug_attr);
#endif

	return 0;
}
