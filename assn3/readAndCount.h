#ifndef RACH 
#define RACH 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node{
	char *name; 
	int count; 
	struct node *next; 
}; 

extern struct node *readAndFreq(FILE *infile); 

#endif