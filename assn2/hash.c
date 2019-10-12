#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HUNK 3000
#define table_size 3000 /* initial table size */

int num_items = 0; 


typedef struct n1{        
	char* value;     /* char* character array to hold words */ 
	int count; 
} node;

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
	node* ht = malloc(sizeof(*ht)*table_size);
	int i = 0; 
	while(i < table_size)
	{
		ht[i].value = NULL; 
		ht[i].count =  0;
		i++;
	}
	return ht;
}

/* inserts an element in hashtable */
void insert(char *newValue, node *ht)
{
	int key; 
	/*key will be the address in the hash table*/
	key = horner_hash(newValue);
	
	ht[key].value = (char*)malloc(sizeof(char)*strlen(newValue));
	ht[key].value = newValue;

	if(get_load_factor() > 0.5)
	{
		rehash();
	}

	if(ht[key].value == newValue)
	{
		ht[key].count += 1; 
	}

	num_items++; 
	 
}

/* function returns corresponding index of given value */
int horner_hash(char *value)
{
	int key; 
	int n; 
	int i = 0; 
	if(len(value) > 8)
	{
		n = 8; 
	} else {
		n = len(value);
	}
	while (i < len(value));
	{	
		int v = value[i]; 
		int m = 31^(n-1-i);
/*		int key += ord(value[i])*31**(n-1-i);*/	

		int key = v*m; 
		i++;
	}
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

}
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

	while(EOF != (c = getc(fp)))
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
		if (c == '\n')
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

int main(int argc, char *argv[])
{
	int num_items = 0; 
	char *last, *next;

	node *ht = hashtable_init();

	FILE *fp = fopen(argv[1], "r+"); 
	
	if (fp == NULL)
	{
		printf("There doesn't seem to be anything here"); 
	}

	last = readlongline(fp);

	if ( last )
		insert(last, *ht);

	while ( (next = readlongline(fp)) ) {
		if ( !strcmp(last, next) ) {
			free(next);
		/* they’re the same, drop it
		*/
		} else {
			/* they’re different, write it. */
			insert(next, *ht);
			free(last);
			/* remember to clean up the old one. */
			last = next;
		}
	}

	
	return 0; 
}
