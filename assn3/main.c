#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

int main(int argc, char* argv[])
{
	struct node *freq_Counter = malloc(sizeof(struct node)*MAX_COUNT);
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);
	freq_Counter = readAndFreq(infile);
 	qsort((void*) freq_Counter, 256, sizeof(struct node), cmpfunction)
 	cmpfunction(struct node1, struct node2)
 	{
 		return (node1.count > node2.count) - (node1.count < node2.count); 
 	}
	return 0;
}
