SHELL   = /bin/sh
CC      = gcc
CFLAGS  = -std=c99 -pedantic -Wall -Wextra
MAIN 	= detab
OBJECTS = $(MAIN).o

all:$(MAIN)

clean:
	rm -f $(OBJECTS) *~

$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJECTS)

$(OBJECTS): $(MAIN).c
	$(CC) -c $(CCFLAGS) $(MAIN).c
