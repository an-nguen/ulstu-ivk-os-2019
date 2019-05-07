CC=gcc
CFLAGS=-std=c11

all:
	$(CC) $(CFLAGS) ./thr.c -o ./thr.out -pthread

clean:
	find . -name \*.o -type f -delete

delete:
	find . -name \*.out -type f -delete
