CC       = gcc
CCFLAGS  = -pedantic -Wall -g 
LDFLAGS  = -lm

all:

	$(CC) $(CCFLAGS) -o forkit $(LDFLAGS) forkit.c
	$(CC) $(CCFLAGS) -o tryit $(LDFLAGS)	tryit.c
clean:
	rm -f forkit tryit *.o
