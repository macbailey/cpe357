#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char c; 
	char *readlongline(char);
	char *currentLine = (char *)malloc(sizeof(char)*100);
	char *lastLine = (char *)calloc(1, sizeof(char)); 

	while((c = getchar()) != EOF)
	{
		readlongline(c);
	}
	
	return 0; 
}

char *readlongline(char *c)
{
	/*Max pointer will be 512, because that's my birthday*/
	long maxBuffer = 512;

	char buffer = (char *)malloc(sizeof(char)*maxBuffer); 

    while ((c != EOF || (c != '\n')
    {	
    	/*When the line is past 512 we need to reallocate more memory*/
		if(currentPosition == maxBuffer)
		{
			/*we will multiply the maxbuffer by two because that is what Jasper 
			said to do in 202, that rhymed*/
			maxBuffer += maxBuffer;

			/*When we go to reallocate memory we also need to reset our spot in memory to start 
			back at where we started so we take away our current position so far*/
			
			buffer = realloc(buffer - currentPosition, maxBuffer*sizeof(char)); 

			/*now that we have reset our original memory we will be able to ensure we don't
			right over over previous entries, so we will add our current postion
			to the current line*/
			buffer += currentPosition; 
		}

		/*If we hit a new line we need to check for likeness and print*/
	 	if(c == '\n')
		{	
			/*Setting current line back to zero to ensure if another line starts before this one ends
			there is no memory bleed over*/
			*buffer = '\0';

			/*set the current line back to where it started by removing the counts it has 
			gone from the beginning*/
			buffer -= currentPosition; 
			*currentline = buffer
			currentPosition = 0; 
	
			

		} else {

			/*increase the current position becuase it needs to keep track of this line*/
			currentPosition++; 
			/*if all else fails make the currentLine pointer set to c*/
			*buffer= c;
			/*increase the currentLine so we go to the next spot in c*/				
			buffer++;

		}

	}
}
