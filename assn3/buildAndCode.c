#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include "readAndCount.h"
#define MAX_COUNT 256
#define BUF_SIZE 1

void insertSorted(node_ptr* head, node_ptr insert_node);
node_ptr sortItName(node_ptr unSorted);
node_ptr sortIt(node_ptr unSorted);

/*deletes node from linked list by severing next ties*/
void deleteNode(node_ptr* head)
{
	node_ptr temp = *head;
	*head = temp->next; 
	return; 
}

/*Used for troubleshooting linked list*/
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

/*Used to determine location of character in array*/
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

/*Reads code as left = 0 and right = 1 once a leaf is found 
the code is finished and it attached to the corresponding node*/
node_ptr get_Code(node_ptr root, char* code, int pos, node_ptr freq_Counter)
{
		int dest = 0; 
		int dest_len = strlen(code);
		char* new_code = malloc(sizeof(char)); 
		if(root->right)
		{
			code[dest_len] = '1';
			code[dest_len + 1] = '\0';
			get_Code(root->right, code, pos+1, freq_Counter);	
		}
		if(root->left)
		{
			code[dest_len] = '0';
			code[dest_len + 1] = '\0';
			get_Code(root->left, code, pos+1, freq_Counter);
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

/*Compiles a tree from the linked list*/
void addtree(node_ptr* head)
{

	node_ptr super_node = malloc(sizeof(node)); 

	int left_count = (*head)->count;

	int right_count = (*head)->next->count;

	super_node->left = malloc(sizeof(node));

	super_node->count = (left_count + right_count);
	super_node->left = *head;

	super_node->right = (*head)->next; 

	deleteNode(head); 
	deleteNode(head);

	insertSorted(head, super_node); 
}

void findLetters(node_ptr freq_Counter, node_ptr root, int in_fd, int out_fd)
{
	uint8_t buffer[BUF_SIZE]; 
	uint8_t j;
	ssize_t read_in; 
	int i; 
	char val; 
	node_ptr master_node = root; 
	while((read_in = read(in_fd, &buffer, BUF_SIZE)) > 0)
	{
		for(j = 0x80; j != 0; j >>= 1)
  	{
			if (j==0x10)
      	val = ' ';
  		val = (buffer[0]&j)?'1':'0';
	  	printf("\n");
	  	printf("val: %c\n", val);
	  	if(!(root->left || root->right))
			{
				printf("leaf \n");
				i = write(out_fd, &root->name, sizeof(root->name));
				if(i == -1)
				{
					perror("write");
				}
				root = master_node;
			}
			if(val == '0')
			{	
				printf("left \n");
				root = root->left; 
				/*findLetters(freq_Counter, root->left, in_fd, out_fd);*/
			}
			if(val == '1')
			{
				printf("right \n");
				root = root->right; 
				/*findLetters(freq_Counter, root->right, in_fd, out_fd);*/
			}
		}
	}
}
