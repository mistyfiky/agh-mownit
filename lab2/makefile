PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := rys.jpg dane1.jpg dane2.jpg testowy.jpg $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS := -lgsl -lgslcblas -lm

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

% :: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean :
	$(RM) gsl_interp_*.txt wartosci.txt
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)

rys.jpg : interpolacja
	./$<
	gnuplot -e 'load "$<.txt"'

%.jpg : %.txt
	gnuplot -e 'load "$<"'
