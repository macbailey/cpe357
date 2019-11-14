#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mytar.h"

void create_Archive(char* out_file, int num_Files, char** filenames, int v_Flag);
void extract_Archive(char* tar_file, int num_Files, char** filenames, int v_Flag, int s_Flag);


void usage(int code)
{
  if(code == 1)
    printf("Invalid Input\n");
  if(code == 2)
    printf("No output file\n");
}

int main(int argc, char* argv[])
{
  int i;
  int ctx_FLAG = 0; 
  int f_FLAG = 0; 
  int v_FLAG = 0; 
  int s_FLAG = 0; 
  if(argc < 2)
  {
    usage(1);
    return 1; 
  }
  for(i = 0; i < strlen(argv[1]); i++)
  {
    if(argv[1][i] == 'c')
    {
      if(ctx_FLAG != 0)
      {
        usage(1);
        printf("c\n");
        return 1; 
      }
      ctx_FLAG = 1; 
    }
    if(argv[1][i] == 't')
    {
      if(ctx_FLAG != 0)
      {
        usage(1);
        printf("t\n");
        return 1; 
      }
      ctx_FLAG = 2; 
    }
    if(argv[1][i] == 'x')
    {
      if(ctx_FLAG != 0)
      {
        usage(1);
        printf("x\n");
        return 1; 
      }
      ctx_FLAG = 3; 
    }
    if(argv[1][i] == 'f')
    {
      f_FLAG = 1; 
    }
    if(argv[1][i] == 't')
    {
      s_FLAG = 1; 
    }
    if(argv[1][i] == 'v')
    {
      v_FLAG = 1; 
    }

  }
  if(ctx_FLAG == 0 || f_FLAG == 0)
  {
    usage(1);
    printf("OR\n");
    return 1; 
  }
  if(ctx_FLAG == 1)
    create_Archive(argv[2], argc - 3, argv + 3, v_FLAG);
  if(ctx_FLAG == 3)
  {
    printf("GOING EXTRACT !\n");
    extract_Archive(argv[2], argc - 3, argv + 3, v_FLAG, s_FLAG);
    s_FLAG = s_FLAG + s_FLAG;
    /*Create List From Tar*/
  }
  if(ctx_FLAG == 2)
  {
    /*Creat Extract Function*/
  }

  return 0; 
}