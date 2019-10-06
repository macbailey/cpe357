#include <stdio.h>

int main(int argc, char *argv[]) 
{
	int c; 
   FILE *fp;
	fp = fopen("in_test.txt", "r+");
   if (fp != NULL)
   {
	   while ((c = fgetc((FILE*)fp)) != '\n')
	   {
	   	fputc(c, stdout);
	   }
	   printf("\n");
	   fclose(fp);
	   return 0; 
   }
	return 1; 
}
