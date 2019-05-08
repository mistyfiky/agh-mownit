PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS :=

.PHONY: all clean distclean

all: $(TARGETS) $(ADDITIONAL) clean

$(TARGETS):
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))
	$(RM) $(PDF).log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex -interaction=nonstopmode -draft $(PDF)

$(PDF).pdf: $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)
