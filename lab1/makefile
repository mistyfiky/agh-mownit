TARGETS := $(patsubst %.c,%,$(wildcard *.c))
CC := gcc
CFLAGS := -Wall -Wextra
REPORT := sprawozdanie.pdf

.PHONY: all clean distclean clean_report

all: $(TARGETS) $(REPORT) clean clean_report

$(TARGETS):
	$(CC) $(CFLAGS) -c $@.c -o $@.o
	$(CC) $(CFLAGS) $@.o -o $@

clean:
	$(RM) $(patsubst %,%.o,$(TARGETS))

distclean: clean distclean_report
	$(RM) $(TARGETS)

$(REPORT):
	pdflatex $(patsubst %.pdf,%,$@)

clean_report:
	$(RM) $(patsubst %,%.aux,$(TARGETS)) $(patsubst %.pdf,%.aux,$(REPORT)) $(patsubst %.pdf,%.log,$(REPORT))

distclean_report: clean_report
	$(RM) $(REPORT)
