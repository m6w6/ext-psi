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

#ifndef PHP_PSI_H
#define PHP_PSI_H

#include "php.h"

extern zend_module_entry psi_module_entry;
#define phpext_psi_ptr &psi_module_entry

#define PHP_PSI_VERSION "0.1.0"

#ifdef PHP_WIN32
#	define PHP_PSI_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_PSI_API __attribute__ ((visibility("default")))
#else
#	define PHP_PSI_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

static inline int psi_check_env(const char *var) {
	char *set = getenv(var);
	return (set && *set && (*set != '0' || set[1]));
}

#include "php_network.h"

static inline int psi_fdopen(const char *desc)
{
	int fd = -1;

	if (desc) {
		char *addr = strstr(desc, "://");

		if (addr) {
			addr += 3;
		}
		if (addr && *addr) {
			struct sockaddr_storage sa = {0};
			socklen_t ss = 0;
			int rc = php_network_parse_network_address_with_port(addr,
					strlen(addr), (struct sockaddr *) &sa, &ss);

			if (SUCCESS == rc) {
				int styp = strncmp(desc, "udp:", 4)
						? SOCK_STREAM
						: SOCK_DGRAM;
				int sfam = sa.ss_family == AF_INET6
						? ((struct sockaddr_in6 *) &sa)->sin6_family
						: ((struct sockaddr_in *) &sa)->sin_family;

				fd = socket(sfam, styp, 0);

				if (fd > 0 && 0 != connect(fd, (struct sockaddr *) &sa, ss)) {
					perror(desc);
					close(fd);
					fd = -1;
				}
			}
		} else if (!strcmp(desc, "stdout")) {
			fd = STDOUT_FILENO;
		} else if (!strcmp(desc, "stderr")) {
			fd = STDERR_FILENO;
		} else if (!(fd = atoi(desc)) || -1 == fcntl(fd, F_GETFD)) {
			fd = open(desc, O_WRONLY|O_APPEND|O_CREAT|O_CLOEXEC, 0664);
		}
	}
	return fd;
}

typedef struct psi_object {
	void *data;
	void (*dtor)(void *data);
	size_t size;
	zend_object std;
} psi_object;

static inline psi_object *PSI_OBJ(zval *zv, zend_object *zo) {
	if (zv) {
		zo = Z_OBJ_P(zv);
	}
	if (!zo) {
		return NULL;
	}
	return (void *) (((char *) zo) - zo->handlers->offset);
}

PHP_PSI_API zend_object *psi_object_init(zend_class_entry *ce);
PHP_PSI_API zend_object *psi_object_init_ex(zend_class_entry *ce, void *data, void (*dtor)(void *));
PHP_PSI_API zend_class_entry *psi_object_get_class_entry();

ZEND_BEGIN_MODULE_GLOBALS(psi)
	char *engine;
	char *directory;
	char *search_path;
	struct psi_context_ops *ops;
	struct psi_context *context;
	struct {
		struct psi_plist *decls;
		struct psi_plist *vars;
	} blacklist;
ZEND_END_MODULE_GLOBALS(psi);

ZEND_EXTERN_MODULE_GLOBALS(psi);

#define PSI_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(psi, v)

#if defined(ZTS) && defined(COMPILE_DL_PSI)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_PSI_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
