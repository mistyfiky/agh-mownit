PDF := raport
TARGETS := root_finding root_finding_brent root_finding_falsepos root_finding_modified
OBJECTS := $(patsubst %,%.o,$(TARGETS)) demo_fn.o
ADDITIONAL := zad1.jpg root_finding.out root_finding_brent.out root_finding_falsepos.out zad2.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lm -lgsl -lgslcblas

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

clean :
	$(RM) $(OBJECTS)
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS)
	$(RM) $(ADDITIONAL)

root_finding : demo_fn.o root_finding.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $^

root_finding_% : demo_fn.o root_finding_%.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

%.jpg : %.txt
	gnuplot -e 'load "$<"'

%.out : %
	./$< > $@
