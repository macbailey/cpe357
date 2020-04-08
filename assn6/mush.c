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
#include <stdio.h>
#include <errno.h>
#include <signal.h>

#define TRY_AGAIN -3
#define ARGLIM 12
#define PIPELIM 10
#define STAGELIM 10
#define MAXLEN 520

#include "parseline.h"

/*Function Prototypes*/
int parseline(char *line, struct stage *stage_list);
void forkit(struct stage *stage_list, int num_stages);

/*Signal handler for SIGINT and EOF*/
void handler(int signum)
{
  switch (signum)
  {
    /*clearing errno to ensure proper handling*/
    errno = '\0';
  case 2:
    printf("\n");
    errno = '\0';
    break;
  }
}

/*If given file in comand line, opens file*/
FILE *open_file(char *path, char *mode)
{
  FILE *fp;
  if (!(fp = fopen(path, mode)))
  {
    perror(path);
    exit(EXIT_FAILURE);
  }
  return fp;
}

int main(int argc, char *argv[])
{

  FILE *inputfd;
  struct sigaction sa;
  sa.sa_handler = handler;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);

  /*Sigaction for signal handling*/
  if (sigaction(SIGINT, &sa, NULL) < 0)
  {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  /*If a file is given in the command line*/
  if (argc == 2)
    inputfd = open_file(argv[1], "r");
  else if (argc > 2)
  {
    printf("Incorrect input: mush [File]\n");
    exit(1);
  }
  else
    inputfd = stdin;

  /*For loop to continue the shell operations*/
  for (;;)
  {
    struct stage stage_list[STAGELIM];
    char line[MAXLEN] = {'\0'};
    int i;
    int num_stages = 0;
    int count = 0;

    /*Initializing stage_list*/
    memset(stage_list, 0, sizeof(stage_list));

    /*Checking if shell should begin prompt or not*/
    if (isatty(fileno(inputfd)) && isatty(STDOUT_FILENO))
    {
      printf("8-p ");
    }

    /*setting errno to null to 
    ensure proper error handling*/
    errno = '\0';

    /*Checking if we have an interrupt
    or a EOF, if neither end program*/
    if (!fgets(line, MAXLEN, inputfd))
    {
      if (errno == EINTR)
      {
        errno = '\0';
        continue;
      }
      else if (feof(inputfd))
      {
        if (inputfd == stdin)
          printf("\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        if (inputfd == stdin)
          printf("\n");
        exit(1);
        return 0;
      }
    }

    /*Initializing line*/
    for (i = 0; i < MAXLEN; i++)
    {
      if (line[i] == '\n')
        line[i] = '\0';
      if (line[i] != '\0')
        count++;
    }

    /*checking if command over 512 bytes, if so error*/
    if (count > 512)
    {
      fprintf(stderr, "command too long");
      exit(1);
    }
    /*gets all the info from teh given input line*/
    num_stages = parseline(line, stage_list);

    if (num_stages == -1)
      exit(1);

    if (num_stages == TRY_AGAIN)
      continue;

    /*DO THAT WORK*/
    forkit(stage_list, num_stages);
  }
  return 0;
}

/*usage helper function*/
void usage(char *out, int usage_num)
{
  if (usage_num == 1)
  {
    fprintf(stderr, "%s: bad input redirection\n", out);
  }
  if (usage_num == 2)
  {
    fprintf(stderr, "%s: bad output redirection\n", out);
  }
  if (usage_num == 3)
  {
    fprintf(stderr, "%s: Ambiguous Output\n", out);
  }
  if (usage_num == 4)
  {
    fprintf(stderr, "%s: Ambiguous Input\n", out);
  }
}

/*does the bulk of parsing, 
takes in input line and list of stages*/
int parseline(char *line, struct stage *stage_list)
{
  int fd[2];
  int c = 0;
  char *cmdline;
  char *arg;
  char *stgptr;
  char *args;

  /*seperates the input line into string for each stage*/
  cmdline = strtok_r(line, "|", &stgptr);

  /*While there is still content*/
  while (cmdline)
  {
    if (c >= PIPELIM)
    {
      fprintf(stderr, "Pipeline too deep.\n");
      return TRY_AGAIN;
    }

    strcpy(stage_list[c].cmd, cmdline);

    /*if more than one stage*/
    if (c)
    {
      /*pipe the file desciptor*/
      pipe(fd);

      /*Checking for ambigous output*/
      if (stage_list[c - 1].output)
      {
        usage(stage_list[0].argv[0], 3);
        return TRY_AGAIN;
      }

      /*Connecting input/output pipes*/
      stage_list[c - 1].output = fd[1];
      stage_list[c].input = fd[0];
    }

    /*String to token arguments splits by spaces*/
    arg = strtok_r(cmdline, " ", &args);

    /*Check if not arguemnts*/
    if (!arg)
    {
      fprintf(stderr, "invalid null command\n");
      return TRY_AGAIN;
    }

    stage_list[c].argc = 0;

    /*while we have an argument*/
    while (arg)
    {
      /*checking validity of input symbol use*/
      if (strcmp(arg, "<") == 0)
      {
        /*use index and rindex to see if only one occurance
        *     of "<" symbol, if pointers dont match then error*/
        if (!(arg = strtok_r(NULL, " ", &args)) || !strcmp(arg, ">") ||
            index(stage_list[c].cmd, '<') != rindex(stage_list[c].cmd, '<'))
        {
          usage(stage_list[c].argv[0], 1);
          return TRY_AGAIN;
        }
        /*If there there is still arguments*/
        if (c)
        {
          usage(stage_list[c].argv[0], 4);
          return TRY_AGAIN;
        }

        if ((stage_list[c].input = open(arg, O_RDONLY)) < 0)
        {
          perror(arg);
          return TRY_AGAIN;
        }
      }

      /*checking validity of output symbol use*/
      else if (strcmp(arg, ">") == 0)
      {

        /*use index and rindex to see if only one occurance
        *     of ">" symbol, if pointers dont match then error*/
        if (!(arg = strtok_r(NULL, " ", &args)) || !strcmp(arg, "<") ||
            index(stage_list[c].cmd, '>') != rindex(stage_list[c].cmd, '>'))
        {
          usage(stage_list[c].argv[0], 2);
          return TRY_AGAIN;
        }

        /*strcpy(stage_list[c].output,arg);*/
        if ((stage_list[c].output = open(arg, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
        {
          perror(arg);
          return TRY_AGAIN;
        }
      }
      else
      {
        strcpy(stage_list[c].argv[stage_list[c].argc++], arg);

        /*Checking if there are too many arguments*/
        if (stage_list[c].argc == ARGLIM)
        {
          fprintf(stderr, "Too many arguements.\n");
          return TRY_AGAIN;
        }
      }
      arg = strtok_r(NULL, " ", &args);
    }

    cmdline = strtok_r(NULL, "|", &stgptr);
    /*increment count*/
    c++;

    /*If the command is change directory
    chdir instaed of execvp*/
    if (!strcmp(stage_list[0].argv[0], "cd"))
    {
      if (chdir(stage_list[0].argv[1]) < 0)
        printf("%s: %s \n", stage_list[0].argv[1], strerror(errno));
      return TRY_AGAIN;
    }
    /*if exit is given, exit the program*/
    if (!strcmp(stage_list[0].argv[0], "exit"))
      exit(1);
  }

  /*assigning STDIN & STDOUT*/
  if (!stage_list[0].input)
    stage_list[0].input = dup(0);
  if (!stage_list[c - 1].output)
    stage_list[c - 1].output = dup(1);

  /*returns number of stages*/
  return c;
}

void forkit(struct stage *stage_list, int num_stages)
{
  pid_t pid[PIPELIM];
  int i;
  int j;
  int status;

  for (i = 0; i < num_stages; i++)
  {
    /*If a child*/
    if (!(pid[i] = fork()))
    {

      char *arguments[PIPELIM] = {'\0'};

      /*Reading arguments from stages*/
      for (j = 0; j < stage_list[i].argc; j++)
        arguments[j] = stage_list[i].argv[j];

      /*Null terminator*/
      arguments[j + 1] = NULL;

      /*Error checing*/
      if (dup2(stage_list[i].input, STDIN_FILENO) == -1 ||
          dup2(stage_list[i].output, STDOUT_FILENO) == -1)
      {
        perror(stage_list[i].cmd);
        exit(1);
      }

      /*closing I/O*/
      for (j = 0; j < num_stages; j++)
      {
        close(stage_list[j].input);
        close(stage_list[j].output);
      }

      /*Exectuing commands with arguemnts*/
      execvp(arguments[0], arguments);
      /*If error print error value*/
      perror(arguments[0]);
      exit(1);
    }

    /*Close stages*/
    close(stage_list[i].input);
    close(stage_list[i].output);
  }

  /*Waiting for children*/
  for (i = 0; i < num_stages; i++)
  {
    while (waitpid(pid[i], &status, 0) < 0)
      ;
  }
  /*Flushing out stdout*/
  fflush(stdout);
}