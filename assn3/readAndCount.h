#ifndef RACH 
#define RACH 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
	char name; 
	int count; 
	struct Node* next; 
	struct Node* right; 
	struct Node* left; 
}node;

typedef node* node_ptr; 

extern node_ptr readAndFreq(FILE *infile); 

#endif
