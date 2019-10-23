#include <stdlib.h>
#include <stdio.h>
#include "readAndCount.h"
#define MAX_COUNT 256

/*Used to compare by count with a name tie breaker*/
int cmpfunction(const void * a, const void * b)
{
	 node_ptr node1 = ( node_ptr )a;
	 node_ptr node2 = ( node_ptr )b;
	if((node1 -> count) == (node2 -> count))
	{	
		return (node1 -> name > node2 -> name) - 
		(node1 -> name < node2 -> name); 
	}
	return (node1 -> count > node2 -> count) - 
	(node1 -> count < node2 -> count); 
}

/*Used to sort by count*/
node_ptr sortIt(node_ptr unSorted)
{
	qsort(unSorted, MAX_COUNT, sizeof( node), cmpfunction);
	return unSorted;
}
 
/*Used compare by name */
int name_cmpfunction(const void * a, const void * b)
{
	 node_ptr node1 = ( node_ptr )a;
	 node_ptr node2 = ( node_ptr )b;
	return (node1 -> name > node2 -> name) - 
	(node1 -> name < node2 -> name); 
}

/*used to sort by name */
node_ptr sortItName(node_ptr unSorted)
{
	qsort(unSorted, MAX_COUNT, sizeof( node), name_cmpfunction);
	return unSorted;
}
void linkIt(node_ptr* head, node_ptr sorted)
{	
	int i = MAX_COUNT; 	
	while(i > 0)
	{
		if(sorted[i].count != 0 && sorted[i].name != 0)
		{ 
			node_ptr current = malloc(sizeof(node));
			current->name = sorted[i].name;
		    current->count = sorted[i].count;
		    current->next = *head; 
		    current->right = NULL;
		    current->left = NULL; 
		    *head = current; 
		}
		i--;
	}
}

/*Inserts the new supernode properly into the linked list*/
void insertSorted(node_ptr* head, node_ptr insert_node)
{
	node_ptr current;
	if(*head == NULL || (*head)->count >= insert_node->count)
	{
		insert_node->next = *head;
		*head = insert_node; 
		return;
	}
	current = *head; 
	while(current->next != NULL && 
		current->next->count < insert_node->count)
	{
		current = current->next; 
	}
	insert_node->next = current->next;
	current->next = insert_node; 
}
	