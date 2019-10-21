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