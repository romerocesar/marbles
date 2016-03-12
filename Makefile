# $Id: Makefile 85 2006-11-30 04:33:13Z julio $

CC=gcc
EXTRA=-O3 -fomit-frame-pointer -march=pentium4
#EXTRA=-g -pg

LOADLIBES=-lglut -lGL -lGLU -lX11 -lm -lSDL -lpthread

CFLAGS=-Wall -pipe ${EXTRA}


objects = model.o view.o input.o material.o marble.o texto.o main.o 

marbles: $(objects)
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@


.PHONY: clean
clean:
	rm -f marbles *.o

# para poder usar flymake-mode
check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
