#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parseline.h"
int num_stages = 0; 
int in_Flag = 0; 
int our_Flag = 0; 
void usage(char* c, int num)
{
  if(num == 1)
  {
    printf("%s: bad input redirection\n", c);
    exit(1);
  }
  if(num == 2)
  {
    printf("%s: bad output redirection\n", c);
    exit(2);
  }
  if(num == 3)
  {
    printf("%s: too many commands\n", c);
    exit(3); 
  }
  if(num == 4)
  {
    printf("invalid null command \n");
    exit(4);
  }
  if(num == 5)
  {
    printf("ambigous input \n");
    exit(5);
  }
}
int isString(char* s)
{
  printf("isString: %s ", s);
  if ((strcmp(s,"|")==0)){
    printf("returning one\n");
    return 1;}
  if ((strcmp(s,"<") == 0) || (strcmp(s,">") == 0) || (strcmp(s,"|") == 0)) 
  {
    printf("returning zero\n");
    return 0; 
  }
  printf("returning one\n");
  return 1; 
}

int removeSpaces(char* input, char** output)
{
  int j = 0; 
  char *token; 
  const char space[2] = " "; 
  
  
  token = strtok(input, space); 

  while(token != NULL)
  {
    output[j] = token;
    if(strcmp(output[j], "\n") != 0)
      j++;
    token = strtok(NULL, space);
  }

  return j; 
}

void inputBuilder(struct stage *parser)
{
  int j; 
  char input[512] = {'\0'}; 

  for(j = 0; j < parser->num_args; j++)
  {
    strcat(input, parser->argv[j]);
    strcat(input," ");
  }
  printf("INPUT: %s\n", input);
  parser->stage_cont = input;
  input[0] = '\0';
}
void findCmd(struct stage *parser)
{
  if(isString(parser->argv[0]))
  {
    parser->cmd = parser->argv[0];
  }
}
void grammarCheck(struct stage *parser)
{
  int i; 
  for(i = 0; i <  parser->num_args; i++)
  {
    if(!strcmp(parser->argv[i], "<"))
    {
    }
  }
}

int main(int argc, char *argv[])
{
  int size, i; 
  int num_Pipes = 0; 
  int k = 0; 
  char input[512] = {'\0'};
  char *comms_args[100]; 
  struct stage parser[10];
  printf("line: ");
  fgets(input, 512, stdin); 

  size = removeSpaces(input, comms_args);
  
  for(i = 0; i < size; i++)
  {
    printf("%i: %s\n", i, comms_args[i]);
  }
  printf("%i\n",size);
  for(i = 0; i < size; i++)
  {
    if(strcmp(comms_args[i], "|") == 0)
    {
      
      parser[num_Pipes].num_args = (k); 
      num_Pipes++;
      k = 0;
      continue; 
    }
    parser[num_Pipes].num_args = k+1;
    parser[num_Pipes].argv[k] = comms_args[i];
    printf("num_Pipes: %i k: %i - %s\n", num_Pipes, k, parser[num_Pipes].argv[k]);
    k++; 
  }
  num_stages = num_Pipes; 
  for(i = 0; i < num_stages+1; i++)
  {
    printf("%i\n",i);
    printf("%i\n",parser[i].num_args);
    parser->stage_num = i; 
    findCmd(&parser[i]);
    printf("cmd: %s\n", parser->cmd);
    inputBuilder(&parser[i]);
    grammarCheck(&parser[i]);

  }
/*  grammarCheck(sep_commands, num_Pipes);
*/
  return 0; 
}
