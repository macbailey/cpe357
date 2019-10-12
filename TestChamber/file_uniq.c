#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HUNK 3000

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

int main(int argc, char *argv[]){
	/* read lines from stdin until there are no more lines. For each line,
	* compare it to the previous line. If they are the different, print
	* the previous line. If the same, discard the previous line.
	*/
	char *last, *next;
	last = readlongline(stdin);
	if ( last )
		fputs(last, stdout);
	while ( (next = readlongline(stdin)) ) {
		if ( !strcmp(last, next) ) {
			free(next);
		/* they’re the same, drop it
		*/
		} else {
			/* they’re different, write it. */
			fputs(next, stdout);
			free(last);
			/* remember to clean up the old one. */
			last = next;
		}
	}

	return 0;
}