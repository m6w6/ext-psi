
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

$(PHP_PSI_SRCDIR)/src/parser_proc.h: $(PHP_PSI_SRCDIR)/src/parser_proc.c

$(PHP_PSI_SRCDIR)/src/parser_proc.c: $(PHP_PSI_SRCDIR)/src/parser_proc_grammar.y
	# trickery needed for relative #line directives
	cd $(PHP_PSI_SRCDIR) && bison -Wall -v -d -o $(patsubst $(PHP_PSI_SRCDIR)/%,%,$@) $(patsubst $(PHP_PSI_SRCDIR)/%,%,$<)

$(PHP_PSI_SRCDIR)/src/parser_scan.re: $(PHP_PSI_SRCDIR)/src/parser_proc.h
	touch $@
$(PHP_PSI_SRCDIR)/src/parser_scan.c: $(PHP_PSI_SRCDIR)/src/parser_scan.re
	# trickery needed for relative #line directives
	cd $(PHP_PSI_SRCDIR) && $(RE2C) -o $(patsubst $(PHP_PSI_SRCDIR)/%,%,$@) $(patsubst $(PHP_PSI_SRCDIR)/%,%,$<)

$(PHP_PSI_SRCDIR)/src/calc/%.h: $(PHP_PSI_SRCDIR)/scripts/gen_calc_%.php $(PHP_PSI_SRCDIR)/scripts/_include.php
	$(PHP_EXECUTABLE) $< >$@

$(PHP_PSI_SRCDIR)/src/calc.h: | $(PHP_PSI_SRCDIR)/src/calc/basic.h $(PHP_PSI_SRCDIR)/src/calc/bin.h $(PHP_PSI_SRCDIR)/src/calc/bool.h $(PHP_PSI_SRCDIR)/src/calc/unary.h $(PHP_PSI_SRCDIR)/src/calc/cast.h $(PHP_PSI_SRCDIR)/src/calc/cmp.h $(PHP_PSI_SRCDIR)/src/calc/oper.h

.PHONY: psi-generated
psi-generated: $(PHP_PSI_GENERATED)


PHP_PSI_DEPEND = $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(PHP_PSI_SOURCES:.c=.dep))

$(PHP_PSI_BUILDDIR)/%.dep: $(PHP_PSI_SRCDIR)/%.c | $(PHP_PSI_GENERATED)
	@echo Generating $@ ...
	@$(CC) -MM -MG -MF $@ -MT $(patsubst $(PHP_PSI_SRCDIR)/%,$(PHP_PSI_BUILDDIR)/%,$(@:.dep=.lo)) \
		$(CPPFLAGS) $(DEFS) $(INCLUDES) $< \
			|| touch $@

php_psi_stdinc.h:
php_psi_posix.h:

ifneq ($(findstring clean,$(MAKECMDGOALS)),clean)
ifneq ($(PSI_DEPS),)
-include $(PHP_PSI_DEPEND)
endif
endif

.PHONY: psi-build-headers
psi-build-headers: $(PHP_PSI_HEADERS)

.PHONY: psi-clean-headers
psi-clean-headers:
	-rm -f $(PHP_PSI_HEADERS)

.PHONY: psi-clean
psi-clean: psi-clean-headers

.PHONY: psi-clean-objects
psi-clean-objects:
	-rm -f $(PHP_PSI_BUILDDIR)/src/*o
	-rm -f $(PHP_PSI_BUILDDIR)/src/types/*o

psi-clean: psi-clean-objects

.PHONY: psi-clean-generated
psi-clean-generated:
	-rm -f $(PHP_PSI_GENERATED)

.PHONY: psi-clean-depend
psi-clean-depend:
	-rm -f $(PHP_PSI_DEPEND)

psi-clean: psi-clean-depend

.PHONY: psi-watch
psi-watch:
	-while inotifywait -q -e modify -r $(PHP_PSI_SRCDIR); do $(MAKE); done

.PHONY: psi-paranoid-backups
psi-paranoid-backups:
	@-if test -z "$(REPO)"; then \
		echo; \
		echo "Usage: make psi-paranoid-backups REPO=<repo to push to>"; \
		echo; \
	else \
		echo "Watching $(PHP_PSI_SRCDIR) for changes to flush and push to $(REPO) ..."; \
		while inotifywait -q -e modify -r $(PHP_PSI_SRCDIR); do \
			git ci -am flush; \
			git push $(REPO); \
		done; \
	fi

install-headers: psi-build-headers
clean: psi-clean-headers
ifneq ($(PSI_DEPS),)
clean: psi-clean-depend
endif

