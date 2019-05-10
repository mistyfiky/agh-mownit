PDF := raport
TARGETS := root_finding root_finding_multiple root_finding_modified zad3
OBJECTS := demo_fn.o
ADDITIONAL := zad1.jpg root_finding_multiple.out zad2.jpg zad3.out $(PDF).pdf
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

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

root_finding root_finding_multiple root_finding_modified : demo_fn.o

root_finding_multiple.out : root_finding_multiple
	echo '' > $@
	./$< bisection >> $@
	./$< brent >> $@
	./$< falsepos >> $@

zad1.jpg zad2.jpg :
	gnuplot -e 'load "$(patsubst %.jpg,%.txt,$@)"'

zad3 :

zad3.out : zad3
	echo '' > $@
	./$< newton >> $@
	./$< secant >> $@
	./$< steffenson >> $@
