vpath %.h HelloWorld
vpath %.c HelloWorld Main
CC=gcc

CFLAGS=-c -Wall

all: main.o hello.o
	$(CC) main.o hello.o -o hello && ./hello && rm -rf *o hello

main.o: main.c hello.h
	$(CC) $(CFLAGS) Main/main.c

hello.o: hello.c hello.h
	$(CC) $(CFLAGS) HelloWorld/hello.c
