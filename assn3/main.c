#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 25


/*int cmpfunction(const void * a, const void * b)
{
	struct node *node1 = (struct node *)a;
	struct node *node2 = (struct node *)b;
	if((node1 -> count) == (node2 -> count))
	{	
		return (node1 -> name > node2 -> name) - (node1 -> name < node2 -> name); 
	}
	return (node1 -> count > node2 -> count) - (node1 -> count < node2 -> count); 
}
*/

int main(int argc, char* argv[])
{	
	int count = 0; 
	struct node *freq_Counter = malloc(sizeof(struct node)*MAX_COUNT);
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);
	freq_Counter = readAndFreq(infile);
	sortIt(freq_Counter);
 	/*qsort(freq_Counter, MAX_COUNT, sizeof(struct node), cmpfunction);*/

	while(count < MAX_COUNT)
	{
		if(freq_Counter[count].count != 0)
		{
			printf("(%c) ", freq_Counter[count].name);
			printf("%d\n", freq_Counter[count].count);
		}
		count++; 
	}


	return 0;
}
