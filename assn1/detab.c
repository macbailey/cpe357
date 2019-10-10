#include <stdio.h>

int main()
{
	int c;		 //Switch statement int  
	int count = 0;	 //Count for what position the cursor is in 
	int spaces;	 //Holds the position to the next tab bar
	//While not at the end of the file 
	while ((c = getchar()) != EOF)
	{	
		printf("Here is c: %c\n", c);
		//Switches through 4 cases
		switch(c)
		{
			//Case: Tab
			case '\t' : 
				//Calculates how many spaces to next tab bar
				spaces = 8 - count % 8;
				int i; 
				//Fill position to next tab bar with spaces 
				for(i = 0; i < spaces; i++)
				{
					putchar(' ');
					count++; 
				}
				break;
			//Case: Backspace
			case '\b' :
				if(count > 0)
				{
					count = count - 1; //Go one position back
				}
				putchar(c);  
				break; 
			//Case: Newline & Carriage Return
			case '\n' :
			case '\r' :
				count = 0; 
				putchar(c); 
				break; 
			//Default: print character and increment the position by one 
			default:
				putchar(c);
				count++; 
				break;
		}
	}
	return(0);
}
