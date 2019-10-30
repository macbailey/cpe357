#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
int main (int argc, char *argv[])
{
  int array[] = {0,0,0,0,0,0,0,1}; 
  uint8_t buffer = 00000000; 
  uint8_t j; 
  int i; 
  for(i = 0; i < 8; i++)
  {
    buffer <<= 1;
    if(array[i] == 1)
    {
      buffer = buffer | 0x01; 
    }
    printf("%d\n", buffer);
  }
  for(j = 0x80; j != 0; j >>= 1)
  {
    printf("%c",(buffer&i)?'1':'0');
    if (i==0x10)
      printf(" ");
  }
  printf("\n");
  return 0; 
}