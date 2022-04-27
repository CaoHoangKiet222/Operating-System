CC=gcc
CFLAGS=-c

all: pi_multi-thread.o pi_serial.o
	$(CC) pi_multi-thread.o -o pi_multi-thread -lpthread -lm && ./pi_multi-thread 1000000
	$(CC) pi_serial.o -o pi_serial -lpthread -lm && ./pi_serial 1000000

pi_multi-thread.o: pi_multi-thread.c
	$(CC) $(CFLAGS) pi_multi-thread.c

pi_serial.o: pi_serial.c
	$(CC) $(CFLAGS) pi_serial.c

clean: 
	rm -f pi_serial pi_multi-thread *.o
