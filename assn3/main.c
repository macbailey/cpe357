#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256

node_ptr sortIt(node_ptr unSorted);
void linkIt(node_ptr* head, node_ptr sorted);
void addtree(node_ptr* head);
node_ptr get_Code(node_ptr root, char* code, int pos, node_ptr freq_Counter);
char* encode(node_ptr freq_counter);

/*
Main file is the start of all commands and tasks, which in order are:
1. Read in file and check for empty files
2. Count frequencies of characters and create nodes for each 
3. Sort the files in order of frequency using q sort
4. Create a linked list of the nodes
5. Create a Huffman tree from linked list 
6. Create Huffman codes for each character 
7. Return Huffman codes of each character  
*/

int getLength(node_ptr head)
{
	int count = 0;
	node_ptr current = head; 
	while(current != NULL)
	{
		count++;
		current = current->next; 
	}
	return count; 
}

int main(int argc, char* argv[])
{		
	node_ptr head = NULL; 

	char* code = malloc(sizeof(char)*MAX_COUNT);

	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);

	FILE *infile = fopen(argv[1], "r");

	fseek(infile, 0, SEEK_END);

	if (ftell(infile) == 0)
	{
	  return 0; 
	}
	fseek(infile, 0, SEEK_SET);


	freq_Counter = readAndFreq(infile, freq_Counter);
	
	freq_Counter = sortIt(freq_Counter);

	linkIt(&head, freq_Counter);

	while(getLength(head) > 1)
	{
		addtree(&head); 
	}

	freq_Counter = get_Code(head, code, 0, freq_Counter); 
/*	while(i < MAX_COUNT)
	{
		if(freq_Counter[i].huff_code != NULL)
		{
			printf("0x%02x: %s\n",
			freq_Counter[i].name, 
			freq_Counter[i].huff_code);
		}
		i++;
	}*/
	encode(freq_Counter);
	return 0;
}