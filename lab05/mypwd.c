#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_PATH 2048

int dirFinder(char **path, int level)
{
  DIR *prevDir;
  struct dirent *currectDir;
  struct stat here;
  struct stat there;
  struct stat checkHere;
  struct stat checkThere;

  /*open up previous directory*/
  prevDir = opendir("..");
  /*Check if prev is not NULL */
  if (prevDir == NULL)
  {
    perror("cannot get current directory");
    return 1;
  }
  /*If the path is beyond 2048*/
  if (level >= MAX_PATH)
  {
    perror("path too long");
    return 2;
  }

  /*To check if current and parent are same*/
  stat(".", &checkHere);
  stat("..", &checkThere);
  if (checkThere.st_ino == checkHere.st_ino &&
      checkThere.st_dev == checkHere.st_dev)
  {
    closedir(prevDir);
    return level;
  }

  /*set a structure for the local directory*/
  stat(".", &here);
  chdir("..");
  /*Reads through whole directory*/
  while ((currectDir = readdir(prevDir)) != NULL)
  {
    /*setting directory name*/
    stat(currectDir->d_name, &there);
    /*If the directory here matches there*/
    if (there.st_dev == here.st_dev && there.st_ino == here.st_ino)
    {
      path[level] = currectDir->d_name;
      /*Recursive call*/
      dirFinder(path, ++level);
      break;
    }
  }
  return 0;
}

int main(int argc, char *argv[])
{
  char **path = malloc(sizeof(path) * MAX_PATH);
  char *out_path = malloc(sizeof(out_path) * MAX_PATH);
  int level = 0;
  int i;

  out_path = '\0';

  dirFinder(path, level);

  /*Find length of path*/
  for (i = 0; i < MAX_PATH; i++)
  {
    if (path[i] != NULL)
    {
      level++;
    }
  }

  /*print out path*/
  printf("/");
  for (i = level - 1; i > -1; i--)
  {
    printf("/%s", path[i]);
  }
  printf("\n");
  return 0;
}
