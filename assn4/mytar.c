#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "mytar.h"
#define PATH_MAX 4096

/*Function Prototypes*/
void create_Archive(char* out_file, int num_Files, char** filenames,
 int v_Flag);
void extract_Archive(char* tar_file, int num_Files, char** filenames,
 int v_Flag, int s_Flag);
void createTable(char* out_file, int num_Files, char** filenames, 
  int v_Flag, int s_Flag);

/*Usage to catch errors and print to stdout*/
void usage(int code, char* call)
{
  if(code == 1)
    fprintf(stderr, 
      "usage: %s [ctxSp[f tarfile]] [file1 [ file2 [...] ] ]\n", call);
}

int main(int argc, char* argv[])
{
  int i;
  int ctx_FLAG = 0; 
  int f_FLAG = 0; 
  int v_FLAG = 0; 
  int s_FLAG = 0; 
  /*If less than two arguments*/
  if(argc < 2)
  {
    fprintf(stderr, "%s: you must choose one of the 'ctx' options.\n", argv[0]);
    usage(1, argv[0]);
    return 1; 
  }
  /*Go through all the characters in argument one*/
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
      if(argv[2] == NULL)
      {
        printf("%s: option 'f' requires an archive name\n", argv[0]);
        usage(1, argv[0]); 
        return 1; 
      }
    }
    else if(argv[1][i] == 'S')
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
  /*If there is no c, t, or x flags in the arguments*/
  if(ctx_FLAG == 0)
  {
    fprintf(stderr, "%s: you must choose one of the 'ctx' options.\n", argv[0]);
    usage(1, argv[0]);
    return 1; 
  }
  /*If there is no f flag*/
  if(f_FLAG != 1)
  {
    fprintf(stderr, "%s: you must implement the 'f' file option.\n", argv[0]);
    usage(1, argv[0]);
    return 1; 
  }
  /*If ctx_FLAG is one then we are creating a directory*/
  if(ctx_FLAG == 1)
    create_Archive(argv[2], argc - 3, argv + 3, v_FLAG);
  /*If ctx_FLAG is three then we are extracting a directory*/
  if(ctx_FLAG == 3)
  {
    extract_Archive(argv[2], argc - 3, argv + 3, v_FLAG, s_FLAG);
  }
  /*If ctx_FLAG is two then we are creating archive listing*/
  if(ctx_FLAG == 2)
  {
    createTable(argv[2], argc - 3, argv + 3, v_FLAG, s_FLAG);
  }

  return 0; 
}