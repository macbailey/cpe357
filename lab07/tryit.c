#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
  int pid, child;
  char* command;
  char* path;

  if(argc < 2){
    printf("usage: tryit command\n");
    exit(1);
  }
  pid = fork();
  command = argv[1];
  path = argv[1];
  if(pid == 0)
  {
    if(execl(path, command, NULL) == -1)
    {
      printf("%s: No such file or directory\n",command);
      exit(1);
    }
  } else {
    waitpid(pid, &child, 0);
    if(child != 0)
    {
      printf("Process %i exited with an error value.\n", pid);
      exit(1);
    } else {
      printf("Process %i succeeded.\n", pid);
    }
  }
  return 0; 
} 