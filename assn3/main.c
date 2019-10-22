#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
#define COUNT 10

node_ptr sortItName(node_ptr unSorted);
node_ptr sortIt(node_ptr unSorted);
void linkIt(node_ptr* head, node_ptr sorted);
int getLength(node_ptr array);
void push(node_ptr* head, int count, char name);
void printTree(node_ptr head);
void insertSorted(node_ptr* head, node_ptr insert_node);



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
void deleteNode(node_ptr* head)
{
	node_ptr temp = *head;
	*head = temp->next; 
	return; 
}
void linkIt(node_ptr* head, node_ptr sorted)
{	
	int i = MAX_COUNT; 	
	while(i > 0)
	{
		if(sorted[i].count != 0)
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
	printTree(*head);
}

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


void printTree(node_ptr head)
{
	node_ptr current = head; 
	while(current != NULL)
	{
		if(current->name != '\0')
		{
			printf("%c ", current-> name); 
		}
		printf("%d \n", current-> count);
		current = current->next; 
	}
	printf("End Of Tree\n\n");
}


void addtree(node_ptr* head)
{

	node_ptr super_node = malloc(sizeof(node)); 
	
	int left_count = (*head)->count;

	int right_count = (*head)->next->count;

	super_node->left = malloc(sizeof(node));

	super_node->count = (left_count + right_count);
	printf("count: %d \n", super_node->count);
	super_node->left = *head;

	super_node->right = (*head)->next; 

	deleteNode(head); 
	deleteNode(head);

	insertSorted(head, super_node); 
}
int findLocation(char name, node_ptr freq_Counter)
{
	int i; 
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_Counter[i].name == name)
		{
			return i; 
		}
	}
	return 0; 
}
node_ptr encode(node_ptr root, char* code, int pos, node_ptr freq_Counter)
{
	int dest = 0; 
	int dest_len = strlen(code);
	char* new_code = malloc(sizeof(char)*MAX_COUNT); 
	if(root->left)
	{
		code[dest_len] = '0';
		code[dest_len + 1] = '\0';
		encode(root->left, code, pos+1, freq_Counter);
	}
	if(root->right)
	{
		code[dest_len] = '1';
		code[dest_len + 1] = '\0';
		encode(root->right, code, pos+1, freq_Counter);	
	}
 	if(!(root->left || root->right))
	{
		dest = findLocation(root->name, freq_Counter); 
		strcpy(new_code, code); 
		freq_Counter[dest].huff_code = new_code;
	}	
	sortItName(freq_Counter);
	return freq_Counter;
}


int main(int argc, char* argv[])
{	
	int i = 0; 
	node_ptr head = NULL; 
	char* code = malloc(sizeof(char)*MAX_COUNT);

	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);

	FILE *infile = fopen(argv[1], "r");
	if(!infile)
		perror(argv[1]);

	freq_Counter = readAndFreq(infile, freq_Counter);
	
	freq_Counter = sortIt(freq_Counter);

	linkIt(&head, freq_Counter);

	while(getLength(head) > 1)
	{
		addtree(&head); 
	}

	freq_Counter = encode(head, code, 0, freq_Counter); 
	while(i < MAX_COUNT)
	{
		if(freq_Counter[i].huff_code != NULL)
		{
			printf("0x%x: %s \n",
			freq_Counter[i].name, 
			freq_Counter[i].huff_code);
		}
		
		i++;
	}
	return 0;
}


