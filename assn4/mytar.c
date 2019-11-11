#include <stdio.h>
#include <stdlib.h>

#include "mytar.h"

void create_Archive(char* archive_name, char* filenames);

void usage(int code)
{
  if(code == 1)
    printf("Invalid Input\n");
  if(code == 2)
    printf("No output file\n");
}

int main(int argc, char* argv[])
{
  if(argc < 2)
  {
    usage(1);
    return 1; 
  }
  printf("%c\n", argv[1][0]);
  printf("%c\n", argv[1][1]);
  printf("%c\n", argv[1][2]);
  if(argv[1][0] != 'c' && argv[1][0] != 't'  && argv[1][0] != 'x')
  {
    usage(1);
    printf("1\n");
    return 1; 
  }
  if(argv[1][1]) 
  {
    if(argv[1][1] == 'v')
      printf("It is verbose\n");
    else if(argv[1][1] == 'f')
      printf("Here is the file\n");
    else
    {
      if(!argv[1][2])
      {
        usage(2);
        return 1; 
      }
    }
  }
  if(argv[1][2])
  {
    if(argv[1][2] != 'f')
    {
        usage(2);
        return 1; 
    }
  }
  if(argv[1][0] == 'c')
  {
    create_Archive(argv[2], argv[3]);
  }
  return 0; 
}