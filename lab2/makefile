PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := rys.jpg dane1.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm

.PHONY: all clean distclean

all: $(TARGETS) $(ADDITIONAL) clean

$(TARGETS):
	$(CC) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CFLAGS) $(LDFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))
	$(RM) gsl_interp_*.txt wartosci.txt
	$(RM) $(PDF).log *.aux

distclean: clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux:
	pdflatex $(PDF) -interaction=nonstopmode > /dev/null 2>&1

$(PDF).pdf: $(PDF).aux
	pdflatex $(PDF) -interaction=nonstopmode

rys.jpg: interpolacja
	./$<
	gnuplot -e 'load "$<.txt"'

dane1.jpg:
	gnuplot -e 'load "dane1.txt"'
