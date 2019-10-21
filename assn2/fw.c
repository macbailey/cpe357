#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define HUNK 3000
#define table_size 3000 /* initial table size */
/*Global Variable to keep track of items in hash table */
int num_items = 0; 

/*Node struct to hold value and frequency of words in hash*/
typedef struct n1{        
	char* value;     /* char* character array to hold words */ 
	int count; 
} node;

/*Functon Prototypes*/
node *hashtable_init();
void insert(char *newValue, node *ht);
int horner_hash(char *value);
int get_table_size();
double get_load_factor();
char *readlongline(FILE *fp);
int get_num_items();
void rehash();


/* Initialize hashtable to NULL */
node *hashtable_init()
{
	node *ht = malloc(sizeof(*ht)*table_size);
	int i = 0; 
	while(i < table_size)
	{
		ht[i].value = 0; 
		ht[i].count =  0;
		i++;
	}
	return ht;
}

/* inserts an element in hashtable */
void insert(char *newValue, node *ht)
{
	/*key will be the address in the hash table*/
	int key; 
	/*Using horner hash for quadratic for collision resolution*/
	key = horner_hash(newValue);
	/*Allocate size of string to insert word*/
	ht[key].value = (char*)malloc(sizeof(char)*strlen(newValue));
	/*inserting word into newly created address*/
	ht[key].value = newValue;
	/*If load factor is above half rehash*/
	if(get_load_factor() > 0.5)
	{
		rehash();
	}
	/*If our word already exists in the array increment the count*/
	if(ht[key].value == newValue)
	{
		ht[key].count += 1; 
	}
	/*Increase number of items by one*/
	num_items++; 
	 
}

/* function returns corresponding index of given value */
int horner_hash(char *value)
{
	/*key will hold the int value*/
	/*n is the min value between the length
	of the string or 8*/
	/*result holds the product*/
	int key, n, result; 
	/*i is the index character of the string*/
	int i = 0; 
	if(strlen(value) > 8)
	{ 
		n = 8; 
	} else {
		n = strlen(value);
	}
	while (i < strlen(value));
	{	
		int v = value[i]; 
		int m = 31^(n-1-i);
/*		int key += ord(value[i])*31**(n-1-i);*/	
		result = v*m;
		key += result; 
		i++;
	}
	/*modulus the table size to ensure the address
	  will fit into the table*/
	key = key % get_table_size();
    
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
	/*we would have realloc'd the table 
	for twice its size and then 
	allocated the new space for NULL values*/

}
/*Reads line from file pointer and returns a value at
the first non alpa character*/
char *readlongline(FILE *fp)
{	
	char *line; 
	int i, size, c; 
	i = 0; 
	size = 0; 
	line = malloc(HUNK);
	if(!line){ 
		perror("malloc"); 
		exit(3);
	}

	while(EOF != (c = getchar()))
	{
		if(i >= size - 2)
		{
			size += HUNK;
			if(NULL == (line = realloc(line, size)))
			{
				perror("malloc"); 
				exit(3);
			}
		}
		line[i++] = c; 
		if (!(isalpha(c)))
		{
			/* trying to remove an extra character*/

			break; 
		}
	}
	if(line)
	{
		line[i] = '\0';
		if(NULL == (line = realloc(line, i++)))
		{
			perror("malloc"); 
			exit(12); 
		}

	}

	return line; 

}

/*main calls file, sends it read long line, and inserts values*/
int main(int argc, char *argv[])
{
	char *last, *next;

	node *ht = hashtable_init();

	FILE *fp = fopen(argv[1], "r+"); 
	
	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}

	last = readlongline(fp);

	if ( last )
		insert(last, ht);

	while ( (next = readlongline(fp)) ) {
		if ( !strcmp(last, next) ) {
			free(next);

		} else {
			insert(next, ht);
			free(last);
			last = next;
		}
	}

	
	return 0; 
}
