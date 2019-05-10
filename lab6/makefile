PDF := raport
TARGETS := zad
OBJECTS :=
ADDITIONAL := zad.dat zad.jpg $(PDF).pdf
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

zad :

zad.dat : zad.sh zad
	./$< > $@

zad.jpg : zad.dat
	gnuplot -e 'load "$(patsubst %.jpg,%.txt,$@)"'
