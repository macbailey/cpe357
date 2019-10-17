CC       = gcc
CCFLAGS  = -Wall -ansi -pedantic -g
LD = gcc
LDFLAGS = -static
PROG = main
OBJECTS  = main.o readAndCount.o
SRCS = main.c readAndCount.c 
HRDS = 
EXTRACLEAN = 
all:    $(PROG)

allclean: clean
	@rm− f $(EXTRACLEAN)
clean:
	rm −f $(OBJS) 


$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJECTS)

$(OBJECTS): $(PROG).c readAndCount.h
	$(CC) -c $(PROG).c
