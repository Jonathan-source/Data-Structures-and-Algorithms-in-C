CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o chashmap.o
	$(CC) $(CC_FLAGS) main.o chashmap.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

chashmap.o: chashmap.c
	$(CC) $(CC_FLAGS) -c chashmap.c

clean:
	rm *.o main
