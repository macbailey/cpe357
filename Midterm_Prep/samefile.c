#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

char* sprint_bits(char *buffer, unsigned int num){

 int i = 0;
 int j = 0;

  char* temp = (char *)malloc(sizeof(int));

 strcpy(buffer, "");

 for (i = 0; i < 8*(sizeof(int)); i++)
 {
   strcpy(temp, buffer);
   if (num & 1)
   {
     strcpy(buffer, "1");
     strcat(buffer, temp);
   } else {
     strcpy(buffer, "0");
     strcat(buffer, temp);
   }
   num = num >> 1;
 }

 /*strip zeroes*/
 while(buffer[j] == '0')
 {
  j++;
 }

 return (buffer + j);
}
 
int main(int argc, char* argv[])
{
  char* byte = malloc(sizeof(int));
  unsigned int var =  3735929054; 
  sprint_bits(byte, var);
  printf("%s \n", byte);
 return 0; 
}
