CC = gcc
CC_FLAGS = -w -g -Wall -O0

main: main.o vec2.o
	$(CC) $(CC_FLAGS) main.o vec2.o -o main -lm

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

vec2.o: vec2.c
	$(CC) $(CC_FLAGS) -c vec2.c

clean:
	rm *.o main
