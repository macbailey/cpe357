#include <stdio.h>
#include <string.h>

size_t strsp(const char *s, const char *accept)
{
	int i, j = 0; 
	size_t count = 0; 

	while(i < strlen(accept))
	{
		while(j < strlen(s))
		{
			if(s[j] == accept[i])
			{
				count++;
			}
			j++;		
		}
		j = 0;

		i++;
	}

	if(count == 0)
	{
		return -1;
	}else{
		return count;
	}
}

int main () {
   int len;
   const char str1[] = "ABCDEFG019874";
   const char str2[] = "ABCD";

   len = strsp(str1, str2);

   printf("Length of initial segment matching %d\n", len );
   
   return(0);
}


