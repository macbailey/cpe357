#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
struct node* sortIt(struct node *unSorted);
struct node* linkIt(struct node *sorted);

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
char printNode(struct node currentNode)
{
	if(currentNode.next)
	{
		struct node* nextNode = currentNode.next;
		return (nextNode -> name);
	}
	return 'a'; 
	
}
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
	linkIt(freq_Counter);
	while(count < MAX_COUNT)
	{
		if(freq_Counter[count].count != 0)
		{
			printf("(%c) ", freq_Counter[count].name);
			printf("%d ", freq_Counter[count].count);
			printf("%c \n", printNode(freq_Counter[count]));

		}
		count++; 
	}


	return 0;
}
