#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TABLE_SIZE = 3000; /* initial table size */

size_t size = TABLE_SIZE;


typedef struct Node { 
	int key;        /*  */
	char value;     /* holds the word */ 
	int count = 0; 
}
int num_items = 0; 
int main(int argc, char *argv[])
{
	File *fp = fopen(argv[1], "r+"); 

	char *table;

	hashtable_init(table);

	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}

}

/* Initialize hashtable to NULL */
void hashtable_init(char *ht)
{
	ht = (char *)malloc(sizeof(char)*TABLE_SIZE);
	int i = 0; 
	while(i < TABLE_SIZE)
   {
      table[i] = NULL;
      i++;
   }
}


/* inserts an element in hashtable */
void insert(int key, char value)
{
	struct Node *entry = (struct Node*)
			malloc(sizeof(struct Node));
	/*key will be the string name horner hashed*/
	entry->key = horner_hash(value);
	entry->value = value;

	table[entry->key] = entry;

	if(get_load_factor > 0.5)
	{
		rehash();
	}

	if( table[entry->key]== value)
	{
		entry->count++;
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

