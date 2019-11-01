#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>

int dirFinder(char* path, int level)
{ 
  DIR *prevDir; 
  struct dirent* currectDir; 

  
  /*open up previous directory*/
  prevDir = opendir("..");

  if(prevDir == NULL)
  {
    perror("mypwd");
    return 1; 
  }
  if(level >= MAX_PATH)
  {
    perror("path too long");
    return 2; 
  }
  while((currectDir = readdir(prevDir)) != NULL)
  {

    printf("currectDir:\n");
  }
}

int main(int argc, char* argv[])
{
  char* path;
  int level;
  int retVal = 0; 

  path = malloc(sizeof(path)*MAX_PATH)
  retVal = dirFinder(path, level)

  return retVal; 
}