#include <stdio.h>

int main()
{
	int c; 
	int count = 0; 
	int spaces; 
	while ((c = getchar()) != EOF)
	{
		switch(c)
		{
			case '\t' : 
				spaces = 8 - count % 8;
				int i; 
				for(i = 0; i < spaces; i++)
				{
					putchar(' ');
					count++; 
				}
				break;
			case '\b' :
				if(count > 0)
				{
					count = count - 1;
				}
				putchar(c);  
				break; 
			case '\n' :
			case '\r' :
				count = 0; 
				putchar(c); 
				break; 
			default:
				putchar(c);
				count++; 
				break;
		}
	}
	return(0);
}
