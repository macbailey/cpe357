#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>



#include "parseline.h"

int parseline(char *line,struct stage *stage_list);
void displayStages(int c, struct stage *stage_list);
void forkit(struct stage *stage_list, int num_stages);

int main(){

    struct stage stage_list[10];
    char line[520];
    int i,num_stages,count;

    printf("8-p ");
    fgets(line,520,stdin);
    for (i=0;i<520;i++){
      if (line[i] == '\n')
        line[i]='\0';
      if(line[i] != '\0')
        count++; 
    }

    /*checking if command over 512 bytes, if so error*/
    if (count>512){
	   fprintf(stderr, "command too long");
	   exit(1);
    }
    /*gets all the info from teh given input line*/
    num_stages = parseline(line,stage_list);
    if(num_stages < 0){
        exit(1);
    }
    forkit(stage_list,num_stages);

    /*display info in specified format*/
    /*displayStages(num_stages,stage_list);*/
    return 0;
}


/*takes in the number of stages and the list of stages*/
void displayStages(int c, struct stage *stage_list){
  int i,j;
  /*goes through each stage present and prints contents*/
  for (i=0;i<c;i++)
  {
    printf("\n--------\nStage %d: \"%s\"\n--------\n",i,stage_list[i].cmd);
   /* printf("%10s: %s\n", "input",stage_list[i].input);
    printf("%10s: %s\n", "output", stage_list[i].output);
   */ printf("%10s: %d\n", "argc", stage_list[i].argc);
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

  if (usage_num == 1){
    fprintf(stderr, "%s: bad input redirection\n",out);
    exit(1);
  }
  if (usage_num == 2){
    fprintf(stderr, "%s: bad output redirection\n",out);
    exit(2);
  }
  if (usage_num == 3){
    fprintf(stderr, "%s: Ambiguous Output\n",out);
    exit(3);
  }
  if (usage_num == 4){
    fprintf(stderr, "%s: Ambiguous Input\n",out);
    exit(4);
  }

}

/*does the bulk of parsing, takes in input line and list of stages*/
int parseline(char *line,struct stage *stage_list)
{
    
  int fd[2];
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
      fprintf(stderr,"Pipeline too deep.\n");
      return -1;
    }
    strcpy(stage_list[c].cmd,cmdline);
	
    /*if more than one stage*/
    if (c)
    {
      pipe(fd);

      if (stage_list[c-1].output)
      {
        usage(stage_list[0].argv[0],3);
        return -1;
      }

      stage_list[c-1].input = fd[1];
      stage_list[c].output = fd[0];
    }

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
        * 		of "<" symbol, if pointers dont match then error*/
        if (!(arg = strtok_r(NULL," ",&args)) || !strcmp(arg,">") ||
        index(stage_list[c].cmd,'<') != rindex(stage_list[c].cmd,'<'))
        {
      		usage(stage_list[c].argv[0],1);	
          return -1;
        }	
		    if(c)
        {   
			   usage(stage_list[c].argv[0],4);
			   return -1;
        }
        if ((stage_list[c].input = open(arg,O_RDONLY))<0)
        {
          perror(arg);
          return -1;
        }
	    }
	    /*checking validity of output symbol use*/
	    else if (strcmp(arg,">")==0)
		  {
		    if (!(arg = strtok_r(NULL," ",&args)) || !strcmp(arg,"<") ||
                index(stage_list[c].cmd,'>') != rindex(stage_list[c].cmd,'>')){
          usage(stage_list[c].argv[0],2);
          return -1;
        }
        /*strcpy(stage_list[c].output,arg);*/
        if ((stage_list[c].output = open(arg, O_WRONLY |
        O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0){
          perror(arg);
          return -1;
        }		    
	    } else {
        strcpy(stage_list[c].argv[stage_list[c].argc++],arg);
        if (stage_list[c].argc==11){
          fprintf(stderr,"Too many arguements.\n");
          exit(1);
        }
      }
      arg = strtok_r(NULL," ",&args);	
    }
	
    cmdline = strtok_r(NULL,"|",&stgptr);
    c++;	
  }
  if (!stage_list[0].input)
   stage_list[0].input = dup(0);
  if (!stage_list[c-1].output)
  	stage_list[c-1].output = dup(1);
  /*returns number of stages*/
  return c;
}

void forkit(struct stage *stage_list, int num_stages)
{
  pid_t pid[10];
  int i;
  int j;
  int status;

  for (i=0; i<num_stages; i++)
  {
    if (!(pid[i] = fork())) 
    {
      char *arguments[10];
      for (j=0; j < stage_list[i].argc; j++)
        arguments[j] = stage_list[i].argv[j];

      arguments[j+1] = NULL;

      printf("input: %d, output: %d \n", stage_list[i].input, stage_list[i].output);
      printf("STDIN_FILENO: %d, STDOUT_FILENO %d \n", STDIN_FILENO, STDOUT_FILENO);

      if (dup2(stage_list[i].input, STDIN_FILENO) == -1 || dup2(stage_list[i].output, STDOUT_FILENO) == -1)
      {
        perror(stage_list[i].cmd);
        exit(1);
      }

      for (j=0;j<num_stages;j++)
      {
        close(stage_list[j].input);
        close(stage_list[j].output);
      }

      execvp(arguments[0],arguments);
      fprintf(stderr,"%s: command not found\n",arguments[0]);
      exit(1);
    }
    close(stage_list[i].input);
    close(stage_list[i].output);
  }
  for (i=0;i<num_stages;i++)
  {
    while (waitpid(pid[i],&status, 0) < 0);
  }
  fflush(stdout);
}








