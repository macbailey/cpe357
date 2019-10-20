#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

node_ptr readAndFreq(FILE *infile)
{
	char c, newCount;
	int count = 0;
	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);

	while(count < MAX_COUNT)
	{
		newCount = (char)count;

		freq_Counter[count].name = newCount; 
		freq_Counter[count].count = 0; 
		freq_Counter[count].right = NULL;
		freq_Counter[count].left = NULL; 
		count++; 
	}

	count = 0; 

	while((c = fgetc(infile)) != EOF)
	{
		freq_Counter[(int)c].count++;  
	}
	return freq_Counter; 
}
