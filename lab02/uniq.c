#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{


	/*Max pointer will be 512, because that's my birthday*/
	long maxBuffer = 512;

	/*current postion will keep track of how far we have gone 
	in memory and how long the previous line is*/
	long currentPosition = 0; 

	/*Initializing a pointer with a memory address so we can use 
	the current postition to return to the beginning of the line 
	being read in*/
	char *currentLine = (char *)malloc(sizeof(char)*maxBuffer);
	char **holder = &currentLine;

	/*allocating a single memory slot of size char 
	since we only have to hold one memory*/
	char *lastLine = (char *)calloc(1, sizeof(char)); 

	/*having a char c to hold each character in the file*/
	char c; 

	/*a while loop that will stop when we have reached the end of the file*/
    while ((c = getchar()) != EOF)
    {	
    	/*When the line is past 512 we need to reallocate more memory*/
		if(currentPosition == maxBuffer)
		{
			/*we will multiply the maxbuffer by 
			two because that is what Jasper 
			said to do in 202, that rhymed*/
			maxBuffer += maxBuffer;

			/*When we go to reallocate memory we also 
			need to reset our spot in memory to start 
			back at where we started so we take away 
			our current position so far*/
			currentLine = realloc(*holder - currentPosition,
			maxBuffer*sizeof(char));
			/*now that we have reset our original 
			memory we will be able
			to ensure we don't right over over previous entries,
			so we will add our current postion to the current line*/
			currentLine += currentPosition; 
		}

		/*If we hit a new line we need to check for likeness and print*/
	 	if(c == '\n')
		{	
			/*Setting current line back to zero to ensure if 
			another line starts before this one ends
			there is no memory bleed over*/
			*currentLine = '\0';

			/*set the current line back to where it 
			started by removing the counts it has 
			gone from the beginning*/
			currentLine -= currentPosition; 
			currentPosition += 1; 
			/*for the first line ensure that the last line 
			is allocated with memory and copy in the 
			current line, since it can't be a duplicate*/
			if(lastLine == NULL)
			{
				lastLine = realloc(lastLine, currentPosition);
				strcpy(lastLine, currentLine);
			}

			/*If the current line and the last line are not 
			the same then output the line*/
			if(strcmp(currentLine, lastLine) != 0)
			{
				printf("%s\n",currentLine); 
			}
			
			/*regardless if they match we want to make the current 
			line the last line and allocate one more for the 
			end of line terminator*/
			lastLine = realloc(lastLine, currentPosition);
			currentPosition = 0; 
			strcpy(lastLine, currentLine);
			

		} else {

			/*increase the current position becuase it 
			needs to keep track of this line*/
			currentPosition++; 
			/*if all else fails make the 
			currentLine pointer set to c*/
			*currentLine= c;
			/*increase the currentLine so we 
			go to the next spot in c*/				
			currentLine++;

		}

	}
	free(lastLine); 
	free(currentLine); 
	return 0; 
}
