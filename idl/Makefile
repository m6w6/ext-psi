CFLAGS += -g -D$(shell uname | tr a-z A-Z)
SOURCES := parser.c lexer.c validator.c compiler.c main.c
HEADERS := $(addsuffix .[ch], $(basename $(SOURCES)))

GENERATED_FILES := $(addsuffix .h, $(basename $(SOURCES)))

.PHONY: all
all: headers main

.PHONY: headers
headers: makeheaders $(SOURCES)
	./makeheaders $(HEADERS) types.h

GENERATED_FILES += lempar.c
lempar.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lempar.c?name=3617143ddb9b176c3605defe6a9c798793280120"

GENERATED_FILES += lemon.c
lemon.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lemon.c?name=039f813b520b9395740c52f9cbf36c90b5d8df03"

GENERATED_FILES += lemon
lemon: lemon.c | lempar.c

GENERATED_FILES += makeheaders.c
makeheaders.c:
	curl -sSo makeheaders.c "https://www.fossil-scm.org/xfer/raw/src/makeheaders.c?name=c42268ec69aae42b8dd10471fd73377d789873ca"
#http://www.hwaci.com/sw/mkhdr/makeheaders.c

GENERATED_FILES += makeheaders
makeheaders: makeheaders.c

GENERATED_FILES += main
main: $(SOURCES)

GENERATED_FILES += parser.c
parser.c: parser.y lemon
	./lemon -c -m $<

GENERATED_FILES += lexer.c
lexer.c: lexer.re
	re2c -o $@ $<

%.h: headers

%.c: %.h
	touch $@

.PHONY: clean
clean:
	-echo rm -f $(GENERATED_FILES)
