PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := pierwsze1.jpg pierwsze2.jpg pierwsze3.jpg dalsze.jpg $(PDF).pdf
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
	$(RM) *.dat
	$(RM) $(PDF).log texput.log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf: $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

pierwsze%.dat: pierwsze
	./$<

dalsze.dat: dalsze
	./$<

%.jpg: %.dat
	gnuplot -e 'load "$(patsubst %.jpg,%.txt,$@)"'
