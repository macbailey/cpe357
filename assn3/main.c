#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
node_ptr sortIt(node_ptr unSorted);
void linkIt(node_ptr sorted, int len);
int getLength(node_ptr array);
void push(node_ptr head, int count, char name);
void printTree(node_ptr head);

node_ptr head = NULL; 

int getLength(node_ptr array)
{
	int i = 0; 
	int len = 0; 
	while(i < MAX_COUNT)
	{
		if(array[i].count != 0)
		{
			len++;
		}
		i++;
	}
	return len; 

}
int main(int argc, char* argv[])
{	
	int len = 0; 
	int count = 0; 

	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);
	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);

	freq_Counter = readAndFreq(infile);
	freq_Counter = sortIt(freq_Counter);

	while(count < MAX_COUNT)
	{
		if(freq_Counter[count].count != 0)
		{
			printf("  %c: ",freq_Counter[count].name);
			printf("%d  ||", freq_Counter[count].count);
		}
		count++;
	}

	len = getLength(freq_Counter);
	linkIt(freq_Counter, len);

	return 0;
}

void linkIt(node_ptr sorted, int len)
{	
	int i = 0; 	
	while(i < MAX_COUNT)
	{
		if(sorted[i].count != 0)
		{
			if(head == NULL)
			{
				head = malloc(sizeof(node));
				head->name = sorted[i].name;
				head->count = sorted[i].count;
				head->right = NULL;
				head->left = NULL; 
				continue; 
			}
			push(head, sorted[i].count, sorted[i].name);
		}
		i++;
	}
	printTree(head); 
}

void push(node_ptr head, int count, char name)
{
    node_ptr current = head;

    while (current->right != NULL) {
        current = current->right;
    }

    current->right = malloc(sizeof(node));
    current->right->name = name;
    current->right->count = count;
    current->right->right = NULL;
    current->right->left = NULL; 
}

void printTree(node_ptr head)
{
	node_ptr current = head; 
	while(current != NULL)
	{
		printf("%c ",current->name);
		printf("%d \n", current-> count);
		current = current->right; 
	}
}

node_ptr addtree(node_ptr head)
{
	node_ptr node_1 = head; 
	node_ptr node_2 = head->right;
	node_ptr super_node = malloc(sizeof(node)); 
	super_node->count = (node_1->count + node_2->count);


}


