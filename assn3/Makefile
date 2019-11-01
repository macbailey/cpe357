CC       = gcc
CCFLAGS  = -std=c89 -pedantic -Wall -g 
LDFLAGS  = -lm
HEN_SOURCES = readAndCount.c sortAndList.c encode.c hencode.c buildAndCode.c
HDE_SOURCES = readAndCount.c sortAndList.c encode.c hdecode.c buildAndCode.c
INCLUDES = $(readAndCount.h)
OBJECTS  = $(SOURCES:=.o)

all:
	$(CC) $(CCFLAGS) -o hencode $(LDFLAGS) $(HEN_SOURCES)

	$(CC) $(CCFLAGS) -o hdecode $(LDFLAGS) $(HDE_SOURCES)

clean:
	rm -f hdecode hencode *.o
