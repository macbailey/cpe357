#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_COUNT 256
int main(int argc, char* argv[])
{
	char c;
	int count = 0; 
	int freq_Counter[MAX_COUNT]; 
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);

	while(count < MAX_COUNT)
	{
		freq_Counter[count] = 0; 
		count ++;
	}
	while((c = fgetc(infile)) != EOF)
	{
/*		if(c == NULL)
			perror(c); */
		freq_Counter[(int)c]++; 

	}
	return 0; 


}