#ifndef RACH 
#define RACH 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*typedef to create Node class */
typedef struct Node{
	unsigned char name; 
	char *huff_code; 
	int count; 
	struct Node* next; 
	struct Node* right; 
	struct Node* left; 
}node;
/*type def an easier node pointer*/
typedef node* node_ptr; 


extern node_ptr readAndFreq(int fd, node_ptr freq_Counter); 

#endif
