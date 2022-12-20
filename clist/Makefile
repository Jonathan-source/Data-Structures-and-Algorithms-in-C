CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o clist.o
	$(CC) $(CC_FLAGS) main.o clist.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

clist.o: clist.c
	$(CC) $(CC_FLAGS) -c clist.c

clean:
	rm *.o main
