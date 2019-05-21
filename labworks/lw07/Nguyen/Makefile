CC=gcc
CFLAGS=-std=c11

all:
	$(CC) $(CFLAGS) ./1.c -o ./1.out
	$(CC) $(CFLAGS) ./2.c -o ./2.out
	$(CC) $(CFLAGS) ./3.c -o ./3.out

clean:
	find . -name \*.o -type f -delete

delete:
	find . -name \*.out -type f -delete
