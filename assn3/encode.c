#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

uint32_t nummber_Of_Chars = 0; 
uint8_t c1 = 0; 
int i = 0;
char* shutUp; 

char* encode(node_ptr freq_counter)
{
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_counter[i].huff_code != NULL)
		{
			nummber_Of_Chars++;

		}
	}
	printf("encode, number of chars: %i\n",nummber_Of_Chars);
	return shutUp; 

}