#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

node_ptr readAndFreq(FILE *infile, node_ptr freq_Counter)
{
	unsigned char newCount;
	int c = 0; 
	int count = 0;

	/*Initialize nodes*/
	while(count < MAX_COUNT)
	{
		newCount = (char)count;

		freq_Counter[count].name = newCount; 
		freq_Counter[count].count = 0; 
		freq_Counter[count].next = NULL;
		freq_Counter[count].right = NULL;
		freq_Counter[count].left = NULL; 
		count++; 
	}

	count = 0; 
	/*create the frequency*/
	while((c = fgetc(infile)) != EOF)
	{
		freq_Counter[c].count++;  
	}
	return freq_Counter; 
}
