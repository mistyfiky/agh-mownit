PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS :=

.PHONY: all clean distclean

all: $(TARGETS) $(ADDITIONAL) clean

$(TARGETS):
	$(CC) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CFLAGS) $(LDFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))
	$(RM) $(PDF).log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex $(PDF) -interaction=nonstopmode > /dev/null 2>&1

$(PDF).pdf: $(PDF).aux
	pdflatex $(PDF) -interaction=nonstopmode
