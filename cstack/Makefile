CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o cstack.o
	$(CC) $(CC_FLAGS) main.o cstack.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

cstack.o: cstack.c
	$(CC) $(CC_FLAGS) -c cstack.c

clean:
	rm *.o main
