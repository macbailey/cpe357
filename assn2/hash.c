#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TABLE_SIZE = 3000; /* initial table size */

size_t size = TABLE_SIZE;


typedef struct{         /*  */
	char* value;     /* holds the word */ 
	int count; 
} Node;

int num_items = 0; 


/* Initialize hashtable to NULL */
Node* hashtable_init(char *ht)
{
	NODE* ht = malloc(sizeof(*ht)*TABLE_SIZE);
	int i = 0; 
	while(i < TABLE_SIZE)
	{
		ht[i].value = NULL; 
		ht[i].count =  0;
		i++;
	}
}


/* inserts an element in hashtable */
void insert(char value, char *ht)
{
	int key; 
	/*key will be the string name horner hashed*/
	key = horner_hash(value);
	
	ht[key].value = malloc(sizeof(char)*value);
	ht[key].value = value;

	if(get_load_factor > 0.5)
	{
		rehash();
	}

	if( ht[key]== value)
	{
		kt[key].count += 1; 
	}

	num_items++; 
	 
}

/* function returns corresponding index of given value */
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
        return key;
}

/* load factor calculation */
double get_load_factor(Node)
{
   return (double) get_num_items(table/table_size);
}

/* size of hashtable */
int get_table_size()
{
   return table_size;
}

/* number of words in hashtable */
int get_num_items(table[entry->key])
{
   int cnt = num_items;
   return cnt;
}

void rehash()
{

}
/* print all hashtable */

int main(int argc, char *argv[])
{
	File *fp = fopen(argv[1], "r+"); 

	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}

	char *ht;

	hashtable_init(ht);



}

