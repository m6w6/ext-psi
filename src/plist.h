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

#ifndef PSI_PLIST_H
#define PSI_PLIST_H

struct psi_plist;

typedef void (*psi_plist_dtor)(void *);

struct psi_plist *psi_plist_init(void (*dtor)(void *));
struct psi_plist *psi_plist_init_ex(size_t size, void (*dtor)(void *));
void psi_plist_free(struct psi_plist *list);

size_t psi_plist_count(struct psi_plist *list);

struct psi_plist *psi_plist_add(struct psi_plist *list, void *ptr);
bool psi_plist_get(struct psi_plist *list, size_t index, void *ptr);
bool psi_plist_del(struct psi_plist *list, size_t index, void *ptr);
bool psi_plist_shift(struct psi_plist *list, void *ptr);
bool psi_plist_pop(struct psi_plist *list, void *ptr);

#include "Zend/zend.h"
#include "Zend/zend_sort.h"

void psi_plist_sort(struct psi_plist *list, compare_func_t cmp, swap_func_t swp);

#endif
