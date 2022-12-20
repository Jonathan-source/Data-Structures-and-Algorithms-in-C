CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o cvector.o
	$(CC) $(CC_FLAGS) main.o cvector.o -o main

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

cvector.o: cvector.c
	$(CC) $(CC_FLAGS) -c cvector.c

clean:
	rm *.o main
