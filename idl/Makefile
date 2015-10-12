CFLAGS += -g -D$(shell uname | tr a-z A-Z)
.PHONY: all
all: main

makeheaders.c:
	curl -sSO http://www.hwaci.com/sw/mkhdr/makeheaders.c

GENERATED_FILES += makeheaders
makeheaders: makeheaders.c

GENERATED_FILES += main
main: main.c parser.c lexer.c validator.c

GENERATED_FILES += parser.h
parser.h: parser.c makeheaders
	./makeheaders $<:$@
	touch $@

GENERATED_FILES += parser.c
parser.c: parser.y types.h
	lemon -c -m $<

GENERATED_FILES += lexer.c
lexer.c: lexer.re parser.h
	re2c -o $@ $<

.PHONY: clean
clean:
	-rm -f $(GENERATED_FILES)
