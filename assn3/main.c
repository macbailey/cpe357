#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
 node_ptr sortIt( node *unSorted);
 node_ptr linkIt( node *sorted);

int main(int argc, char* argv[])
{	
	int count = 0; 
	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);
	freq_Counter = readAndFreq(infile);
	sortIt(freq_Counter);
	freq_Counter = linkIt(freq_Counter);
	while(count < MAX_COUNT)
	{
		if(freq_Counter[count].count != 0)
		{
			printf("(%c) ", freq_Counter[count].name);
			printf("%d \n", freq_Counter[count].count);
			printf("%p \n", (void *)&freq_Counter[++count]);
			printf("%p \n", (void *)&freq_Counter[count].next);
		}
		count++; 
	}
	return 0;
}
