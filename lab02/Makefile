SHELL = /bin/sh
CC       = gcc
CCFLAGS  = -ansi -pedantic -Wall
MAIN = FileOpener
OBJECTS  = $(MAIN).o

all:$(MAIN)

clean:
	rm -f $(OBJECTS) *~

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJECTS)

$(OBJECTS): $(MAIN).c
	$(CC) -c $(CCFLAGS) $(MAIN).c
