#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define table_size = 3000; /* initial table size */

int num_items = 0; 


/* Initialize hashtable to NULL */
Node* hashtable_init(char *ht)
{
	Node* ht = malloc(sizeof(*ht)*table_size);
	int i = 0; 
	while(i < table_size)
	{
		ht[i].value = NULL; 
		ht[i].count =  0;
		i++;
	}
}

typedef struct{        
	char* value;     /* holds the word */ 
	int count; 
} Node;



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
   return (double) (get_num_items()/get_table_size());
}

/* size of hashtable */
int get_table_size()
{
   return table_size;
}

/* number of words in hashtable */
int get_num_items()
{
   return num_items; 
}

void rehash()
{

}
/* print all hashtable */

int main(int argc, char *argv[])
{
	int num_items = 0; 
	char word; 
	File *fp = fopen(argv[1], "r+"); 

	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}

	char *ht;

	hashtable_init(ht);

	word = get_long_line(fp);

	if(word != NULL)
	{
		insert(word, ht);
	}


}

