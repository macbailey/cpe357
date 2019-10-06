#include <stdio.h>

main() {

	int c; 
	/* char ch; */ 
   FILE *fp;
	fp = fopen("in_test.txt", "r");
   if (fp != NULL)
   {
	   while ((c = fgetc((FILE*)fp)) != '\n')
	   {
	   	fputc(c, (FILE*)fp);
	   	
	   }
	   fclose(fp);
	   return 0; 
   }
  return 1; 
   
}


/* int main()
{
   char ch;
   FILE *fp;
   if (fp = fopen("test.c", "r"))
   {
     ch = getc(fp);
     while (ch != EOF)
     {
        putc(ch, stdout);
        ch = getc(fp);
     }
     fclose(fp);
     return 0;
   }
*/
