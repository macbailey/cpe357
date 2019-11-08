#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>
#define ITIMER_REAL      0
#define ITIMER_VIRTUAL   1
#define ITIMER_PROF      2
int main(int argc, char *argv[])
{
  char input = '\0'; 

  if(argv[1] != NULL)
    input = *argv[1]; 
  if(isalpha(input))
  {
    if(isdigit(input))
    {
      printf("It has both\n");
    } else{
      printf("it is not a digit\n");
    }
    
  } else {
    printf("It is a digit\n");
  }
  return 0; 
}
