#ifndef PARSE_H_
#define PARSE_H_

struct stage
{
  char *stage_cont;
  char input[512];
  char output[512];
  int argc;
  int num_args; 
  char *argv[10];
  char *cmd; 
};
#endif