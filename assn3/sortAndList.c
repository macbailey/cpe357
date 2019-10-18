#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256


struct node* sortIt( struct node* unSorted)
{
	qsort(unSorted, MAX_COUNT, sizeof(struct node), cmpfunction);
	return unSorted;
}

int cmpfunction(const void * a, const void * b)
{
	struct node *node1 = (struct node *)a;
	struct node *node2 = (struct node *)b;
	if((node1 -> count) == (node2 -> count))
	{	
		return (node1 -> name > node2 -> name) - (node1 -> name < node2 -> name); 
	}
	return (node1 -> count > node2 -> count) - (node1 -> count < node2 -> count); 
}


