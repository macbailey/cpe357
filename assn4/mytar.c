#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "mytar.h"
#define PATH_MAX 4096

void create_Archive(char* out_file, int num_Files, char** filenames,
 int v_Flag);
void extractFile(char* tar_file, int num_Files, char** filenames,
 int v_Flag, int s_Flag);
void createTable(char* out_file, int num_Files, char** filenames, 
  int v_Flag, int s_Flag);

void usage(int code, char* call)
{
  if(code == 1)
    fprintf(stderr, 
      "usage: %s [ctxSp[f tarfile]] [file1 [ file2 [...] ] ]\n", call);
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
  /*char cwd[PATH_MAX] = {'\0'}; */
  if(argc < 2)
  {
    usage(1, argv[0]);
    return 1; 
  }
  for(i = 0; i < strlen(argv[1]); i++)
  {
    if(argv[1][i] == 'c')
    {
      if(ctx_FLAG != 0)
      {
        usage(1, argv[0]);
        printf("c\n");
        return 1; 
      }
      ctx_FLAG = 1; 
    }
    else if(argv[1][i] == 't')
    {
      if(ctx_FLAG != 0)
      {
        usage(1, argv[0]);
        printf("t\n");
        return 1; 
      }
      ctx_FLAG = 2; 
    }
    else if(argv[1][i] == 'x')
    {
      if(ctx_FLAG != 0)
      {
        usage(1, argv[0]);
        printf("x\n");
        return 1; 
      }
      ctx_FLAG = 3; 
    }
    else if(argv[1][i] == 'f')
    {
      f_FLAG = 1; 
    }
    else if(argv[1][i] == 't')
    {
      s_FLAG = 1; 
    }
    else if(argv[1][i] == 'v')
    {
      v_FLAG = 1; 
    }
    else 
    {
      printf("%s: unregonized option '%c'\n", argv[0], argv[1][i]);
    }

  }
  if(ctx_FLAG == 0)
  {
    fprintf(stderr, "%s: you must choose one of the 'ctx' options.\n", argv[0]);
    usage(1, argv[0]);
    return 1; 
  }
  if(f_FLAG != 1)
  {
    fprintf(stderr, "%s: you must implement the 'f' file option.\n", argv[0]);
    usage(1, argv[0]);
    return 1; 
  }
  if(ctx_FLAG == 1)
    create_Archive(argv[2], argc - 3, argv + 3, v_FLAG);
  if(ctx_FLAG == 3)
  {
    extractFile(argv[2], argc - 3, argv + 3, v_FLAG, s_FLAG);
    s_FLAG = s_FLAG + s_FLAG;
    /*Create List From Tar*/
  }
  if(ctx_FLAG == 2)
  {
    createTable(argv[2], argc - 3, argv + 3, v_FLAG, s_FLAG);
  }

  return 0; 
}