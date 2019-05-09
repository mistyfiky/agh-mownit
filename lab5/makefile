PDF := raport
TARGETS := root_finding
ADDITIONAL := zad1.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

clean :
	$(RM) demo_fn.o root_finding.o
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

root_finding : demo_fn.o root_finding.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $^

zad1.jpg : zad1.txt
	gnuplot -e 'load "$<"'
