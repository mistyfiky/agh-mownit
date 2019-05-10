PDF := raport
TARGETS := root_finding
OBJECTS := $(patsubst %,%.o,$(TARGETS)) demo_fn.o
ADDITIONAL := zad1.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lm -lgsl -lgslcblas

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

clean :
	$(RM) $(OBJECTS)
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS) $(ADDITIONAL)

root_finding : demo_fn.o root_finding.o
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

zad1.jpg : zad1.txt
	gnuplot -e 'load "$<"'
