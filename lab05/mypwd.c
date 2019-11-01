#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include<unistd.h>  
#define MAX_PATH 2048

int dirFinder(char** path, int level)
{ 
  DIR *prevDir; 
  struct dirent* currectDir; 
  struct stat here;
  struct stat there;



  
  /*open up previous directory*/
  prevDir = opendir("..");
  /*Check if prev*/
  if(prevDir == NULL)
  {
    perror("cannot get current directory");
    return 1; 
  }
  if(level >= MAX_PATH)
  {
    perror("path too long");
    return 2; 
  }
  stat(".", &here);
  chdir("..");
  /*Reads through whole directory*/
  while((currectDir = readdir(prevDir)) != NULL)
  {
    stat(currectDir->d_name, &there);

/*    printf("Here: %i  %i  \n", here.st_dev, here.st_ino);
    printf("There: %i  %i  \n", there.st_dev, there.st_ino);  */
    if(there.st_dev == here.st_dev && there.st_ino == here.st_ino)
    {
      printf("currectDir: %s\n", currectDir->d_name);
      path[level] = currectDir->d_name; 
      level++; 
      dirFinder(path, level);

    }     
    
  }
  return 0; 
}

int main(int argc, char* argv[])
{
  char** path;
  int level = 0;
  int retVal; 

  path = malloc(sizeof(path)*MAX_PATH);
  retVal = dirFinder(path, level);

  return retVal; 
}