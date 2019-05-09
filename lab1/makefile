PDF := raport
TARGETS := $(patsubst %.c,%,$(wildcard *.c))
ADDITIONAL := $(PDF).pdf
CC := gcc
CFLAGS := -Wall -Wextra
LDFLAGS :=

.PHONY : all clean distclean

all : $(TARGETS) $(ADDITIONAL) clean

% :: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean :
	$(RM) $(PDF).log texput.log *.aux

distclean : clean
	$(RM) $(TARGETS) $(ADDITIONAL)

$(PDF).aux :
	pdflatex -interaction=nonstopmode $(PDF)
	$(RM) $(PDF).pdf

$(PDF).pdf : $(PDF).aux
	pdflatex -interaction=nonstopmode $(PDF)
