#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"

int main(int argc, char* argv[])
{
	struct node *freq_Counter;
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);
	freq_Counter = readAndFreq(infile);
	printf("%s\n", freq_Counter[63].name);
	return 0;
}