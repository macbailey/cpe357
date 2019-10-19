#include <stdlib.h>
#include <stdio.h>
#include "readAndCount.h"
#define MAX_COUNT 256

int cmpfunction(const void * a, const void * b);

 node_ptr sortIt( node_ptr unSorted)
{
	qsort(unSorted, MAX_COUNT, sizeof( node), cmpfunction);
	return unSorted;
}

int cmpfunction(const void * a, const void * b)
{
	 node_ptr node1 = ( node_ptr )a;
	 node_ptr node2 = ( node_ptr )b;
	if((node1 -> count) == (node2 -> count))
	{	
		return (node1 -> name > node2 -> name) - (node1 -> name < node2 -> name); 
	}
	return (node1 -> count > node2 -> count) - (node1 -> count < node2 -> count); 
}

 node_ptr linkIt(node_ptr sorted)
{	
	node nextNode; 
	node currentNode;
	int i = 0; 
	printf("In Link It \n");
	while(i < MAX_COUNT)
	{	

		printf("%p ", (void *)&sorted[i].next);
		printf("%p ", (void *)&sorted[++i]);
		/*Have to create an array of node pointers so I can point at next*/
		currentNode = sorted[i];
		nextNode = sorted[++i];
		currentNode.next = &nextNode;
		printf("%p \n", (void *)&sorted[i].next);
		i++; 

	}
	return sorted; 
}
