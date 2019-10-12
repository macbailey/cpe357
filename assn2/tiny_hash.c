#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HUNK 3000
#define table_size 3000 /* initial table size */


char *hashtable_init()
{
	char *ht = malloc(sizeof(char)*table_size);
	int i = 0; 
	while(i < table_size)
	{
		ht[i] = 0; 
	}

	return ht;
}

void insert(char *newValue, char *ht)
{
	int key = atoi(newValue); 
	
	ht[key] = malloc(sizeof(char)*strlen(newValue)); 
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

	char *ht = hashtable_init();

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
		/* they’re the same, drop it
		*/
		} else {
			/* they’re different, write it. */
			insert(next, ht);
			free(last);
			/* remember to clean up the old one. */
			last = next;
		}
	}

	printf("hello");

	
	return 0; 
}