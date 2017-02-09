# provide headers in builddir, so they do not end up in /usr/include/ext/psi/src

PHP_PSI_HEADERS := $(addprefix $(PHP_PSI_BUILDDIR)/,$(PHP_PSI_HEADERS))
PHP_PSI_SOURCES := $(addprefix $(PHP_PSI_SRCDIR)/,$(PHP_PSI_SOURCES))
PHP_PSI_GENERATED:=$(addprefix $(PHP_PSI_SRCDIR)/,$(PHP_PSI_GENERATED))

$(PHP_PSI_BUILDDIR)/types:
	mkdir -p $@
$(PHP_PSI_BUILDDIR)/types/%.h: $(PHP_PSI_SRCDIR)/src/types/%.h | $(PHP_PSI_BUILDDIR)/types
	@cat >$@ <$<
$(PHP_PSI_BUILDDIR)/%.h: $(PHP_PSI_SRCDIR)/src/%.h
	@cat >$@ <$<

$(PHP_PSI_BUILDDIR)/lempar.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lempar.c?name=db1bdb4821f2d8fbd76e577cf3ab18642c8d08d1"

$(PHP_PSI_BUILDDIR)/lemon.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lemon.c?name=5ccba178a8e8a4b21e1c9232944d23973da38ad7"

$(PHP_PSI_BUILDDIR)/lemon: $(PHP_PSI_BUILDDIR)/lemon.c | $(PHP_PSI_BUILDDIR)/lempar.c
	$(CC) -o $@ $<

$(PHP_PSI_SRCDIR)/src/parser_proc.h: $(PHP_PSI_SRCDIR)/src/parser_proc.c

$(PHP_PSI_SRCDIR)/src/parser_proc.inc:
$(PHP_PSI_SRCDIR)/src/parser_proc.y: $(PHP_PSI_SRCDIR)/src/parser_def.h $(PHP_PSI_SRCDIR)/src/parser_proc.inc
	cat $(PHP_PSI_SRCDIR)/src/parser_proc.inc >$@
	$(CPP) -P -DGENERATE $< >>$@
$(PHP_PSI_SRCDIR)/src/parser_proc.c: $(PHP_PSI_SRCDIR)/src/parser_proc.y $(LEMON)
	# trickery needed for relative #line directives
	cd $(PHP_PSI_SRCDIR) && $(LEMON_PATH)$(LEMON) $(patsubst $(PHP_PSI_SRCDIR)/%,%,$<)

$(PHP_PSI_SRCDIR)/src/parser.re: $(PHP_PSI_SRCDIR)/src/parser_proc.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser.c: $(PHP_PSI_SRCDIR)/src/parser.re
	$(RE2C) -o $@ $<

$(PHP_PSI_SRCDIR)/src/token.h: $(PHP_PSI_SRCDIR)/src/token_oper_cmp.h
$(PHP_PSI_SRCDIR)/src/token_oper_cmp.h: $(PHP_PSI_SRCDIR)/scripts/gen_oper.php
	$(PHP_EXECUTABLE) $< >$@

PHP_PSI_DEPEND = $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(PHP_PSI_SOURCES:.c=.dep))

$(PHP_PSI_BUILDDIR)/%.dep: $(PHP_PSI_SRCDIR)/%.c
	$(CC) -MM -MG -MF $@ -MT $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(@:.dep=.lo)) \
		$(CPPFLAGS) $(DEFS) $(INCLUDES) $< \
			|| touch $@

token_oper_cmp.h: $(PHP_PSI_SRCDIR)/src/token_oper_cmp.h
php_psi_stdinc.h:
php_psi_posix.h:

ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
ifneq ($(PSI_DEPS),)
-include $(PHP_PSI_DEPEND)
endif
endif

install-headers: psi-build-headers
.PHONY: psi-clean
clean: psi-clean

.PHONY: psi-build-headers
psi-build-headers: $(PHP_PSI_HEADERS)

.PHONY: psi-clean-headers
psi-clean-headers:
	-rm -f $(PHP_PSI_HEADERS)

psi-clean: psi-clean-headers

.PHONY: psi-clean-objects
psi-clean-objects:
	-rm -f $(PHP_PSI_BUILDDIR)/src/*o
	-rm -f $(PHP_PSI_BUILDDIR)/src/types/*o

psi-clean: psi-clean-objects

.PHONY: psi-clean-generated
psi-clean-generated:
	-rm -f $(PHP_PSI_GENERATED)

.PHONY: psi-clean-aux
psi-clean-aux:
	-rm -f $(PHP_PSI_BUILDDIR)/lempar.c $(PHP_PSI_BUILDDIR)/lemon.c $(PHP_PSI_BUILDDIR)/lemon

psi-clean: psi-clean-aux

.PHONY: psi-clean-depend
psi-clean-depend:
	-rm -f $(PHP_PSI_DEPEND)

psi-clean: psi-clean-depend

