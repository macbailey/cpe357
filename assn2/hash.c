#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE = 3000;

typedef struct Node { 
	int key; 
	char value; 
	int count = 0; 
}
int num_items = 0; 
int main(int argc, char *argv[])
{
	File *fp = fopen(argv[1], "r+"); 

	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}
}

void insert(int key, char value)
{
	struct Node *entry = (struct Node*)
						malloc(sizeof(struct Node));
	/*key will be the string name horner hashed*/
	entry->key = horner_hash(value);
	entry->value = value;

	entry = table[entry->key];

	if(load_factor > 0.5)
	{
		rehash();
	}

	if(table[entry->key] == value)
	{
		entry->count++;
	}

	num_items++; 
	 
}

int horner_hash(char value)
{
	int i = 0; 
	if(len(value) > 8)
	{
		n = 8; 
	} else {
		n = len(value)
	}
	while (i < len(value))
	{
		int key += ord(value[i])*31**(n-1-i);
	}
	key = key % table_size();
}

int 

