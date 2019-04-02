TARGET=zad1 zad2 zad3 sprawozdanie.pdf
CC=gcc
CFLAGS=-Wall

all: $(TARGET) clean

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%: %.o
	$(CC) -o $@ $^ $(CFLAGS)

%.pdf: %.tex
	pdflatex $^

.PHONY: clean distclean

clean:
	-rm -f *.o
	-rm -f *.{aux,log}

distclean: clean
	-rm -f $(TARGET)
