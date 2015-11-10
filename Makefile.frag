# provide headers in builddir, so they do not end up in /usr/include/ext/psi/src

PHP_PSI_HEADERS := $(addprefix $(PHP_PSI_BUILDDIR)/,$(PHP_PSI_HEADERS))
PHP_PSI_SOURCES := $(addprefix $(PHP_PSI_SRCDIR)/,$(PHP_PSI_SOURCES))

$(PHP_PSI_BUILDDIR)/%.h: $(PHP_PSI_SRCDIR)/src/%.h
	@cat >$@ <$<

all: psi-build-headers
clean: psi-clean-headers

.PHONY: psi-build-headers
psi-build-headers: $(PHP_PSI_HEADERS)

.PHONY: psi-clean-headers
psi-clean-headers:
	-rm -f $(PHP_PSI_HEADERS)

lempar.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lempar.c?name=3617143ddb9b176c3605defe6a9c798793280120"

lemon.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lemon.c?name=039f813b520b9395740c52f9cbf36c90b5d8df03"

./lemon: lemon.c | lempar.c
	$(CC) -o $@ $<

$(PHP_PSI_SRCDIR)/src/context.c: $(PHP_PSI_SRCDIR)/config.m4
	touch $@
$(PHP_PSI_SRCDIR)/src/%.c: $(PHP_PSI_BUILDDIR)/parser.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser_proc.y: $(PHP_PSI_BUILDDIR)/parser.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser_proc.c: $(PHP_PSI_SRCDIR)/src/parser_proc.y $(LEMON)
	$(LEMON) -c $<

$(PHP_PSI_SRCDIR)/src/parser.re: $(PHP_PSI_BUILDDIR)/parser.h $(PHP_PSI_BUILDDIR)/parser_proc.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser.c: $(PHP_PSI_SRCDIR)/src/parser.re
	$(RE2C) -o $@ $<
