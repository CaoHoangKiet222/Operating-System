vpath %.h factorial readline
vpath %.c factorial readline

CC=gcc
CFLAGS=-c

all: main.o readline.o factorial.o
	$(CC) main.o readline.o factorial.o -o myfactorial && ./myfactorial && rm -rf *o myfactorial

main.o: main.c readline.h factorial.h
	$(CC) $(CFLAGS) main.c

readline.o: readline.c readline.h
	$(CC) $(CFLAGS) readline/readline.c

factorial.o: factorial.c factorial.h
	$(CC) $(CFLAGS) factorial/factorial.c

clean: 
	rm -rf *o myfactorial
