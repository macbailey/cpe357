#include <stdio.h> 

int main()
{
	int c; 
	int count = 0; 
	while ((c = getchar()) != EOF)
	{
		if( c == '\t')
		{
			int spaces; 
			spaces = 8 - count % 8;
			int i; 
			for(i = 1; i < spaces; i = i + 1)
			{
				putchar('*');

			}	
			c = '*'; 	
		}
		if( c == '\b')
			putchar('!'); 
		if( c == '\r')
			count = 0; 
		if(c == '\n')
			count = 0; 	
		count++; 
		putchar(c);
	} 
	return(0); 
}
