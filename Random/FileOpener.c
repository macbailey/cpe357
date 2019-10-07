#include <stdio.h>
#include <stdlib.h>

char *len, **new, **old; 
int main(int argc, char *argv[]) 
{
	char *read_long_line(FILE *);
   FILE *fp;
	fp = fopen("in_test.txt", "r+");
   if (fp != NULL)
   {
   	read_long_line(fp); 
   	/*if (old == NULL)
   	{
   		old = &len;
   		printf("Here is the old one: %s\n", *old);
   	} else {
   		new =  &len;
   	}*/   
	free(len);
	   fclose(fp);
		return 0;
   }
   return 1; 
}

char *read_long_line(FILE *file)
{
	long nl = 1; 
	int c;
	while ((c = fgetc(file)) != EOF)
	{
		while ((c = fgetc(file)) != '\n')
		{
			nl++;
		}
/*		fseek(file, 0, SEEK_SET);
*/		len = (char *)malloc(sizeof(char)*nl);
	   printf("%s\n", fgets(len, nl, file));
	}
	return 0;
}
