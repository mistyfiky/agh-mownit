PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := zad3.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

% :: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean :
	$(RM) zad3.dat
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

zad3.dat : zad2
	./zad3.sh > zad3.dat

zad3.jpg : zad3.dat
	gnuplot -e 'load "zad3.txt"'
