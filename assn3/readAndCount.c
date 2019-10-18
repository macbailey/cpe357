#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

struct node* readAndFreq(FILE *infile)
{
	char c, newCount;
	int count = 0;
	struct node *freq_Counter = malloc(sizeof(struct node)*MAX_COUNT);

	while(count < MAX_COUNT)
	{
		newCount = (char) count;

		freq_Counter[count].name = newCount; 
		freq_Counter[count].count = 0; 
		count++; 
	}
	count = 0; 
	while((c = fgetc(infile)) != EOF)
	{
		freq_Counter[(int)c].count++;  

	}
	while(count < MAX_COUNT)
	{
		if(count == 10)
		{	
			printf("(nl) %d\n", freq_Counter[count].count);
		}
		if(freq_Counter[count].count != 0 && count != 10)
		{
			printf("(%c) ", freq_Counter[count].name);
			printf("%d\n", freq_Counter[count].count);
		}
		count++; 
	}
	return freq_Counter; 
}
