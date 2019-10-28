#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
#define BUFFER_SIZE 8192

node_ptr readAndFreq(int fd, node_ptr freq_Counter)
{
	unsigned char newCount;
	unsigned int count = 0;
	ssize_t read_in; 
	char buffer[BUFFER_SIZE]; 

	printf("fd: %i\n", fd);
	/*Initialize nodes*/
	for(count = 0; count < MAX_COUNT; count ++)
	{
		newCount = (char)count;

		freq_Counter[count].name = newCount; 
		freq_Counter[count].count = 0; 
		freq_Counter[count].next = NULL;
		freq_Counter[count].right = NULL;
		freq_Counter[count].left = NULL; 
	}

	while((read_in = read(fd, &buffer, BUFFER_SIZE)))
	{
/*		read_in = read(fd, &buffer, BUFFER_SIZE); */
		printf("read_in: %d \n", read_in);
		freq_Counter[(int)buffer[0]].count++;
	}
	for(count = 0; count < MAX_COUNT; count++)
	{
		printf("char: %c freq: %d \n", freq_Counter[count].name, freq_Counter[count].count);
	}
	/*	while((c = fgetc(infile)) != EOF)
	{
		freq_Counter[c].count++;  
	}*/

	return freq_Counter; 
}
