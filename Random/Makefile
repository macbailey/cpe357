SHELL = /bin/sh
CC       = gcc
CCFLAGS  = -Wall -g -ansi -pedantic
MAIN = quiz
OBJECTS  = $(MAIN).o

all:$(MAIN)

clean:
	rm -f $(OBJECTS) *~

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJECTS)

$(OBJECTS): $(MAIN).c
	$(CC) -c $(CCFLAGS) $(MAIN).c
