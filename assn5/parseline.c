#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void removeSpaces(char* input, char** output)
{
  const char space[2] = " "; 
  char *token; 
  
  token = strtok(input, space); 
  while(token != NULL)
  {
    if(strcmp(token, " ") == 0)
      continue; 
    token = *output; 
    ++*output;
    token = strtok(NULL, space); 
  }
}

/*  for(i = 0; i < strlen(input); i++)
  {
    if(*input == ' ')
    {
      ++input;
      if(output[0] != NULL)
      {
        *++output; 
      }
    }
    else{
      strcat(*output, input);
    }
  }
}*/

int main(int argc, char *argv[])
{
  int i; 
  char input[512] = {'\0'};
  char *comms_args[100]; 
  printf("Tell me something: \n");
  fgets(input, 512, stdin); 
  removeSpaces(input, comms_args);
  for(i = 0; i < 99; i++)
  {
    printf("output %i: %s \n", i, comms_args[i]);
  }
}
