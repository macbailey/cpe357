#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char c; 
	char *readlongline(char);
	char *currentLine = (char *)malloc(sizeof(char)*100);
	char *lastLine = (char *)calloc(1, sizeof(char)); 

	while((c = getchar()) != EOF)
	{	

		currentLine = readlongline(c);
		/*if(strcmp(currentLine, lastLine) != 0)
			{
				printf("%s\n",currentLine); 
			}
		lastLine = realloc(lastLine, strlen(currentLine));
		strcpy(lastLine, currentLine);*/
	}
	free(currentLine);
	return 0; 
}

char *readlongline(char c)
{	
	/*Max pointer will be 512, because that's my birthday*/
	long maxBuffer = 512;
	long currentPosition = 0;
	char *buffer, *returner;
	buffer = (char *)malloc(sizeof(char)*maxBuffer); 
	while(c != EOF)
	{
		/*When the line is past 512 we need to reallocate more memory*/
		if(currentPosition == maxBuffer)
		{
			/*we will multiply the maxbuffer by two because that is what Jasper 
			said to do in 202, that rhymed*/
			maxBuffer += maxBuffer;

			/*When we go to reallocate memory we also need to reset our spot in memory to start 
			back at where we started so we take away our current position so far*/

			buffer = realloc(buffer, maxBuffer*sizeof(char)); 
		}
		if(c == '\n')
		{
			/*Setting current line back to zero to ensure if another line starts before this one ends
			there is no memory bleed over*/
			*buffer = '\0';
			currentPosition = 0; 
			return(buffer);
		}

		currentPosition++; 
		/*if all else fails make the 
		currentLine pointer set to c*/
		*buffer = c;	
	}
}



/*
	if(currentPosition == maxBuffer)
	{

		maxBuffer += maxBuffer;


		
		buffer = realloc(buffer, maxBuffer*sizeof(char)); 
	}

	if(c == '\n' || c == EOF)
	{

		*buffer = '\0';


		currentPosition = 0; 
		return(buffer);

	}


	currentPosition++; 

	*buffer= c;	*/