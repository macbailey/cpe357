#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h> 

int main() 
{ 
  int pid;

  pid = fork(); 

  if (pid == 0) {  
    printf("This is the child, pid  %d\n", getpid()); 
  } else {  
    printf("This is the parent, pid %d\n", getpid()); 
    wait(NULL);
  } 
  return 0; 
}
