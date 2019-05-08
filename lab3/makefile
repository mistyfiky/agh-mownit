PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := pierwsze_1.jpg pierwsze_2.jpg pierwsze_3.jpg $(PDF).pdf
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
	$(RM) pierwsze_*.dat
	$(RM) $(PDF).log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf: $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

%.dat: pierwsze
	./$<

%.jpg: %.dat
	gnuplot -e 'load "$(patsubst %.jpg,%.txt,$@)"'
