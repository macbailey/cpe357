#ifndef RACH 
#define RACH 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
	char name; 
	char *huff_code; 
	unsigned int count; 
	struct Node* next; 
	struct Node* right; 
	struct Node* left; 
}node;

typedef node* node_ptr; 

typedef struct H_Nodes{
	char name; 
	char* code; 
}h_node; 

typedef h_node* h_node_ptr; 
extern node_ptr readAndFreq(FILE *infile, node_ptr freq_Counter); 

#endif
