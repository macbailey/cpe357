#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "readAndCount.h"
#define MAX_COUNT 256

uint32_t number_Of_Chars = 0; 
uint8_t character;
uint32_t count_of_character = 0; 
int i;
char* shutUp; 

char* header(int fd, node_ptr freq_counter)
{
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_counter[i].huff_code != NULL)
			number_Of_Chars++;
	}

	write(fd, &number_Of_Chars, 4); 
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_counter[i].huff_code != NULL)
		{
			character = freq_counter[i].name; 
			count_of_character = freq_counter[i].count; 
			write(fd, &character, 1);
			write(fd, &count_of_character, 4);
		}
		
	}

	return shutUp; 
}