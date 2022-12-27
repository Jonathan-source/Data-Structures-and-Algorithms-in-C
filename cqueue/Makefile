CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o cqueue.o
	$(CC) $(CC_FLAGS) main.o cqueue.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

cqueue.o: cqueue.c
	$(CC) $(CC_FLAGS) -c cqueue.c

clean:
	rm *.o main
