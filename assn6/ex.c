#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<unistd.h>

#define READ_END 0 
#define WRITE_END 1 

int main (int argc, char* argv[])
{
  int one[2]; 
  int two[2]; 

  pid_t child1, child2, child3; 

  if(pipe(one)){
    perror("First pipe"); 
    exit(-1);
  }

   if(pipe(two)){
    perror("Second pipe");
    exit(-1); 
  }

  if(!(child1 = fork()))
  {
    printf("one[WRITE_END]: %d, one[READ_END]: %d \n", one[WRITE_END], one[READ_END]);
    printf("STDIN_FILENO: %d, STDOUT_FILENO %d \n", STDIN_FILENO, STDOUT_FILENO);
    if(-1 == dup2(one[WRITE_END], STDOUT_FILENO)) {
      perror("dup2 child1");
      exit(-1);
    }

    close(one[READ_END]); 
    close(one[WRITE_END]); 
    close(two[READ_END]);
    close(two[WRITE_END]);

    execl("/bin/ls", "ls", NULL);
    perror("bin/ls");
    exit(-1); 
  }

  if(!(child2 = fork())) { 
    if(-1 == dup2(one[READ_END], STDIN_FILENO)){
      perror("dup2 child2 one"); 
      exit(-1); 
    }
    if(-1 == dup2(two[WRITE_END], STDOUT_FILENO)){
      perror("dup2 child2 two");
      exit(-1);
    }
    close(one[READ_END]); 
    close(one[WRITE_END]);
    close(two[READ_END]); 
    close(two[WRITE_END]);

    execl("/bin/sort","sort", "-r", NULL);
    perror("/bin/sort");
    exit(-1);
  }

  if(!(child3 = fork())) { 
    if(-1 == dup2(two[READ_END], STDIN_FILENO)){
      perror("dup2"); 
      exit(-1); 
    }

    close(one[READ_END]); 
    close(one[WRITE_END]);
    close(two[READ_END]); 
    close(two[WRITE_END]);

    execl("/bin/more", "more", NULL); 
    perror("/bin/more"); 
    exit(-1);
  }

  close(one[READ_END]); 
  close(one[WRITE_END]);
  close(two[READ_END]); 
  close(two[WRITE_END]);

  if(-1 == wait(NULL)){
    perror("wait");
  }
  if(-1 == wait(NULL)){
    perror("wait");
  }
  if(-1 == wait(NULL)){
    perror("wait");
  }
  exit(0);

}