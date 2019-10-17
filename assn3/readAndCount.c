#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_COUNT 256

struct node{
	char *name; 
	int count; 
	struct node *next; 
}; 

int main(int argc, char* argv[])
{
	char c;
	int count = 0; 
	struct node *freq_Counter = malloc(sizeof(struct node)*MAX_COUNT);
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);

	while(count < MAX_COUNT)
	{
		freq_Counter[count].name = (char *)count; 
		freq_Counter[count].count = 0; 
		count++; 
	}
	count = 0; 
	while((c = fgetc(infile)) != EOF)
	{
/*		if(c == NULL)
			perror(c); */
		freq_Counter[(int)c].count++;  

	}
	while(count < MAX_COUNT)
	{
		if(count == 10)
		{
			printf("%d (nl) ", freq_Counter[count].name); 
			printf("%d\n", freq_Counter[count].count);
		}
		if(freq_Counter[count].count != 0 && count != 10)
		{
			printf("%d (%c) ",freq_Counter[count].name, freq_Counter[count].name);
			printf("%d\n", freq_Counter[count].count);
		}
		count++; 
	}
	return 0; 
}
