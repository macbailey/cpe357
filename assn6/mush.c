#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<sys/wait.h>
#include <fcntl.h>
#include<unistd.h>


#include "parseline.h"

#define READ_END 0 
#define WRITE_END 1 

/*void forkLoop(int stuff)
{
  int one[2]; 
  int two[2]; 

  pid_t child1, child2, child3; 

  if(pipe(two)){
    perror("First pipe"); 
    exit(-1);
  }

   if(pipe(two)){
    perror("Second pipe");
    exit(-1); 
  }

  if(!(child1 = fork()))
  {
    if(-1 == dup2(one[WRITE_END], STDOUT_FILENO)) {
      perror("dup2");
      exit(-1);
    }
  }
}*/

/*takes in the number of stages and the list of stages*/
void displayStages(int c, struct stage *stage_list)
{
  int i,j;

  /*goes through each stage present and prints contents*/
  for (i=0;i<c;i++)
  {
    printf("\n--------\nStage %d: \"%s\"\n--------\n",i,stage_list[i].cmd);
    printf("%10s: %s\n", "input",stage_list[i].input);
    printf("%10s: %s\n", "output", stage_list[i].output);
    printf("%10s: %d\n", "argc", stage_list[i].argc);
    printf("%10s: ", "argv"); 
    for (j=0; j<stage_list[i].argc; j++)
    {
      /*if more than one argv, we need a comma*/
      if (j)
        putchar(',');
      printf("\"%s\"",stage_list[i].argv[j]);
    }
    printf("\n");
  }
}

/*usage helper function*/
void usage(char *out, int usage_num)
{
  if (usage_num == 1)
  {
    fprintf(stderr, "%s: bad input redirection\n",out);
    exit(1);
  }
  if (usage_num == 2)
  {
    fprintf(stderr, "%s: bad output redirection\n",out);
    exit(2);
  }
  if (usage_num == 3)
  {
    fprintf(stderr, "%s: ambiguous output\n", out);
    exit(3);
  }
}

/*does the bulk of parsing, takes in input line and list of stages*/
int parseline(char *line, struct stage *stage_list)
{
  int c = 0;
  char *cmdline;
  char *arg;
  char *stgptr;
  char *args;

  /*seperates the input line into string for each stage*/
  cmdline = strtok_r(line,"|",&stgptr);

  while (cmdline)
  {
    if (c == 10)
    {
      fprintf(stderr,"pipeline too deep\n");
      return -1;
    }
    strcpy(stage_list[c].cmd, cmdline);

    /*if more than one stage*/
    if (c)
    {
      if (strcmp(stage_list[c-1].output,"original stdout"))
      {
        usage(cmdline,3);
        return -1;
      }
      sprintf(stage_list[c].input, "pipe from stage %d",c-1);
      sprintf(stage_list[c-1].output, "pipe to stage %d",c);
      strcpy(stage_list[c].output, "original stdout");
    } else {
      strcpy(stage_list[c].input, "original stdin");
      strcpy(stage_list[c].output, "original stdout");
    }

    /*getting each string/char in given stage*/
    arg = strtok_r(cmdline, " ",&args);
    if (!arg)
    {
      fprintf(stderr,"invalid null command\n");
      return -1;
    }
    stage_list[c].argc=0;
    /*while we have an argument*/
    while(arg)
    {
      /*checking validity of input symbol use*/
      if(strcmp(arg,"<")==0)
      {
        /*use index and rindex to see if only one occurance
        *    of "<" symbol, if pointers dont match then error*/
        if (!(arg = strtok_r(NULL," ",&args)) || !strcmp(arg,">") ||
          index(stage_list[c].cmd,'<') != rindex(stage_list[c].cmd,'<'))
        {
          usage(stage_list[c].argv[0],1); 
          return -1;
        } 
        if (c)
        {
          usage(stage_list[c].argv[0],3);
          return -1;
        }
        strcpy(stage_list[c].input,arg);
      }
      /*checking validity of output symbol use*/
      else if (strcmp(arg,">")==0)
      {
        if (!(arg = strtok_r(NULL," ",&args)) || !strcmp(arg,"<") ||
                index(stage_list[c].cmd,'>') != rindex(stage_list[c].cmd,'>'))
        {
          usage(stage_list[c].argv[0],2);
          return -1;
        }
        strcpy(stage_list[c].output,arg);       
      } else {
        strcpy(stage_list[c].argv[stage_list[c].argc++],arg);
      }
        arg = strtok_r(NULL," ",&args); 
    }
    cmdline = strtok_r(NULL,"|",&stgptr);
    c++;  
  }
  /*returns number of stages*/
  return c;
}

int main(int argc, char* argv[])
{
  struct stage stage_list[10];
  char line[520];
  int i,num_stages;
  int input_fd = 0; 
  int output_fd = 0; 
  int count = 0; 

  printf("¯|_(ツ)_|¯ ");
  fgets(line,520,stdin);

  for (i=0;i<520;i++)
  {
    if (line[i] == '\n')
      line[i]='\0';
    if(line[i] != '\0')
      count++; 
  }

  /*checking if command over 512 bytes, if so error*/
  if (count>512)
  {
   fprintf(stderr, "command too long");
   exit(1);
  }

  /*gets all the info from teh given input line*/
  num_stages = parseline(line,stage_list);

  if (num_stages<0)
  {
    exit(1);
  }
  if(strcmp(stage_list[0].input, "original stdin"))
  {
    input_fd = open(stage_list[0].input, O_RDONLY);
    printf("input: %i\n", input_fd);
  }
  if(strcmp(stage_list[num_stages - 1].output, "original stdout"))
  {
    output_fd = open(stage_list[num_stages - 1].output, 
      O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    printf("output: %i\n", output_fd);
  }

  /*display info in specified format*/
  displayStages(num_stages,stage_list);
  return 0;   
}