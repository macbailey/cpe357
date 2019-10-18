CC = gcc

CFLAGS = -Wall -ansi -g - pedantic 

MAIN = readAndCount main

all: $(MAIN) 

readAndCount: readAndCount.c readAndCount.h
	$(CC) $(CFLAGS) -o readAndCount readAndCount.c

main: main.c readAndCount.h
	$(CC) $(CFLAGS) -o main main.c

clean:
	rm *.o 