PHP_INCLUDES := -I/Users/Mike/Sources/php-src.git/{.,main,includes,Zend,TSRM,ext}
JIT_INCLUDES := -I/usr/local/include
UNAME := $(shell uname | tr a-z A-Z)
INCLUDES += $(PHP_INCLUDES) $(JIT_INCLUDES)
CFLAGS += -g -D$(UNAME) $(INCLUDES)
LDFLAGS += -ljit -ljitdynamic /usr/local/php7/lib/libphp7.dylib -Xlinker -rpath -Xlinker /usr/local/php7/lib
SOURCES := parser_proc.c parser.c validator.c compiler.c main.c

GENERATED_FILES := $(addsuffix .h, $(basename $(SOURCES)))

.PHONY: all
all: main

##
# The lemon parser generator
##
GENERATED_FILES += lempar.c
lempar.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lempar.c?name=3617143ddb9b176c3605defe6a9c798793280120"

GENERATED_FILES += lemon.c
lemon.c:
	curl -sSo $@ "http://www.sqlite.org/src/raw/tool/lemon.c?name=039f813b520b9395740c52f9cbf36c90b5d8df03"

GENERATED_FILES += lemon
lemon: lemon.c | lempar.c

##
# Main test program
##
$(SOURCES): Makefile

GENERATED_FILES += main
main: $(SOURCES)

##
# Parser proc
##
GENERATED_FILES += parser_proc.c
parser_proc.c: parser_proc.y lemon
	./lemon -c $<

##
# Parser with lexer
##
GENERATED_FILES += parser.c
parser.c: parser.re
	re2c -o $@ $<

.PHONY: clean
clean:
	-echo rm -f $(GENERATED_FILES)
