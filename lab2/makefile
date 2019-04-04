TARGETS := $(patsubst %.c,%,$(wildcard *.c))
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm
REPORT := raport.pdf

.PHONY: all clean distclean clean_interpolacja clean_report

all: $(TARGETS) rys.jpg $(REPORT) clean clean_interpolacja clean_report

$(TARGETS):
	$(CC) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CFLAGS) $(LDFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))

distclean: clean distclean_interpolacja distclean_report
	$(RM) $(TARGETS)

$(REPORT):
	pdflatex $(patsubst %.pdf,%,$@)

clean_report:
	$(RM) $(patsubst %,%.aux,$(TARGETS)) $(patsubst %.pdf,%.aux,$(REPORT)) $(patsubst %.pdf,%.log,$(REPORT))

distclean_report: clean_report
	$(RM) $(REPORT)

inter.txt: interpolacja
	./$<

rys.jpg: inter.txt
	gnuplot -e 'set output "$@"' -e 'set terminal jpeg' -e 'plot "$<" with lines'

clean_interpolacja:
	$(RM) inter.txt wartosci.txt

distclean_interpolacja: clean_interpolacja
	$(RM) rys.jpg
