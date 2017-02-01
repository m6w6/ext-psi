# provide headers in builddir, so they do not end up in /usr/include/ext/psi/src

PHP_PSI_HEADERS := $(addprefix $(PHP_PSI_BUILDDIR)/,$(PHP_PSI_HEADERS))
PHP_PSI_SOURCES := $(addprefix $(PHP_PSI_SRCDIR)/,$(PHP_PSI_SOURCES))

$(PHP_PSI_BUILDDIR)/types:
	mkdir -p $@
$(PHP_PSI_BUILDDIR)/types/%.h: $(PHP_PSI_SRCDIR)/src/types/%.h | $(PHP_PSI_BUILDDIR)/types
	@cat >$@ <$<
$(PHP_PSI_BUILDDIR)/%.h: $(PHP_PSI_SRCDIR)/src/%.h
	@cat >$@ <$<

install-headers: psi-build-headers
clean: psi-clean

.PHONY: psi-build-headers
psi-build-headers: $(PHP_PSI_HEADERS)

.PHONY: psi-clean-headers
psi-clean-headers:
	-rm -f $(PHP_PSI_HEADERS)

.PHONY: psi-clean-sources
psi-clean-sources:
	-rm -f $(PHP_PSI_BUILDDIR)/src/*o
	-rm -f $(PHP_PSI_BUILDDIR)/src/types/*o
	-rm -f $(PHP_PSI_SRCDIR)/src/parser.c $(PHP_PSI_SRCDIR)/src/parser_proc.c $(PHP_PSI_SRCDIR)/src/parser_proc.y

.PHONY: psi-clean-aux
psi-clean-aux:
	-rm -f lempar.c lemon.c lemon

.PHONY: psi-clean
psi-clean: psi-clean-headers psi-clean-sources psi-clean-aux


lempar.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lempar.c?name=db1bdb4821f2d8fbd76e577cf3ab18642c8d08d1"

lemon.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lemon.c?name=5ccba178a8e8a4b21e1c9232944d23973da38ad7"

./lemon: lemon.c | lempar.c
	$(CC) -o $@ $<

$(PHP_PSI_SRCDIR)/src/parser_proc.h: $(PHP_PSI_SRCDIR)/src/parser_proc.c

$(PHP_PSI_SRCDIR)/src/parser_proc.inc:
$(PHP_PSI_SRCDIR)/src/parser_proc.y: $(PHP_PSI_SRCDIR)/src/parser_def.h $(PHP_PSI_SRCDIR)/src/parser_proc.inc
	cat $(PHP_PSI_SRCDIR)/src/parser_proc.inc >$@
	$(CPP) -P -DGENERATE $< >>$@
$(PHP_PSI_SRCDIR)/src/parser_proc.c: $(PHP_PSI_SRCDIR)/src/parser_proc.y $(LEMON)
	$(LEMON) $<

$(PHP_PSI_SRCDIR)/src/parser.re: $(PHP_PSI_SRCDIR)/src/parser_proc.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser.c: $(PHP_PSI_SRCDIR)/src/parser.re
	$(RE2C) -o $@ $<

$(PHP_PSI_SRCDIR)/src/types/decl.c: $(PHP_PSI_SRCDIR)/php_psi_macros.h $(PHP_PSI_SRCDIR)/php_psi_redirs.h
$(PHP_PSI_SRCDIR)/src/context.c: $(PHP_PSI_SRCDIR)/php_psi_consts.h $(PHP_PSI_SRCDIR)/php_psi_decls.h $(PHP_PSI_SRCDIR)/php_psi_fn_decls.h $(PHP_PSI_SRCDIR)/php_psi_structs.h $(PHP_PSI_SRCDIR)/php_psi_types.h $(PHP_PSI_SRCDIR)/php_psi_unions.h $(PHP_PSI_SRCDIR)/php_psi_va_decls.h

# -- deps

PHP_PSI_DEPEND = $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(PHP_PSI_SOURCES:.c=.dep))

.PHONY: psi-clean-depend
psi-clean-depend:
	-rm -f $(PHP_PSI_DEPEND) $(PHP_PSI_BUILDDIR)/php_psi.dep

psi-clean: psi-clean-depend

$(PHP_PSI_BUILDDIR)/%.dep: $(PHP_PSI_SRCDIR)/%.c
	$(CC) -MM -MG -MF $@ -MT $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(@:.dep=.lo)) \
		$(CPPFLAGS) $(DEFS) $(INCLUDES) $< \
			|| touch $@

DEPS = 
ifneq  ($(DEPS),)
-include $(PHP_PSI_DEPEND)
-include $(PHP_PSI_BUILDDIR)/php_psi.dep
endif


# -- deps
