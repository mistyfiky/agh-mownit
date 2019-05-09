PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm

.PHONY: all clean distclean

all: $(TARGETS) $(ADDITIONAL) clean

$(TARGETS):
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))
	$(RM) $(PDF).log texput.log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf: $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)
