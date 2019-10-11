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
} Node;

int num_items = 0; 


/* Initialize hashtable to NULL */
void hashtable_init(char *ht)
{
	ht = (char *)malloc(sizeof(char)*TABLE_SIZE);
	int i = 0; 
	while(i < TABLE_SIZE)
   {
      ht[i] = NULL;
      i++;
   }
}


/* inserts an element in hashtable */
void insert(char value, char *ht)
{
	struct Node *entry = (struct Node*)
			malloc(sizeof(struct Node));
	/*key will be the string name horner hashed*/
	entry->key = horner_hash(value);
	entry->value = value;

	ht[entry->key] = entry;

	if(get_load_factor > 0.5)
	{
		rehash();
	}

	if( ht[entry->key]== value)
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


char *read_long_line()
{

	/* initializing variables */
   	int counter = 0;
   	char c;
	char *str = NULL;
	

   /* confused on this one */
   size_t buf_len = BUFLEN;	
	
   /* allocating memory for reading */
   str = (char*) malloc(buf_len * sizeof(char));

   /*  printf("Reading the file test.txt\n"); */
   	while((c=getchar()) != EOF && c != '\n')
	{
   		str[counter++] = c;
       	if (counter == buf_len)
       	{
      		buf_len += buf_len;
        	str = (char*)realloc(str, buf_len);
            
		}	
         		
		if(c == '\n')
		{
           
            str[counter] = '\0';
			str[counter++] = c;
        }
				
    }
   	return str;   
}

int main(int argc, char *argv[])
{

   	/* buffers */
	int cmp = 0;
	char *y = NULL;


	char *x = read_long_line();
   	/* char *y = read_long_line(); */	
	
	/* char *y = (char*) malloc(strlen(x) * sizeof(char)); */

   	/* while there is input */
	while(x != NULL && x[0] !='\0')
	{
		y = read_long_line();
		cmp = strcmp(x, y);
		if (cmp != 0)
   		{	
			puts(x);
		
   		}
		/* x = (char*) realloc(y, strlen(y)); */
   		strcpy(x, y);
		
	}


   /*free last part of mem */
	free(x);
	free(y);  
	return 0;
}

