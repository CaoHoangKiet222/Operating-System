CC=gcc
CFLAGS=-c

all: main.o ex1.o
	$(CC) main.o ex1.o -o main && ./main && rm -rf *o

main.o: main.c
	$(CC) $(CFLAGS) main.c

ex1.o: ex1.h
	$(CC) $(CFLAGS) ex1.c

clean: 
	rm -rf *o main
