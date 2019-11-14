#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

static int count = 0; 
static int end = 0; 
static int turn = 1; 

/*Handler for swtiching half seconds*/
void handler (int number)
{
  
  if(turn)
  {
    printf("Tick...");
    fflush(stdout);
    turn = 0; 
  } else {
    printf("Tock\n");
    fflush(stdout); 
    turn = 1; 
    count--;
  }
  if(count < 1)
    end =1; 
   
}

int main (int argc, char* argv[])
{
  int i; 
  struct sigaction sa;
  struct itimerval timer;
  signal(SIGALRM, handler); 
  int alpha = 0; 

  /*If there is more than two args*/
  if(argc != 2)
  {
    printf("usage: timeit <seconds>\n");
    return 1; 
  }

  /*Check if there are characters in input*/
  for(i = 0; i < strlen(argv[1]); i++)
  {
    if(isalpha(argv[1][i]))
      alpha = 1; 
  }
  /*If there is report it */
  if(alpha)
  {
    printf("%s: malformed time.\n", argv[1]);
    return 1; 
   }else {
    count = atoi(argv[1]); 
    if(count < 0)
      end = 1; 
  }

  memset (&sa, 0, sizeof(sa));
  sa.sa_handler = handler;
  sigaction (SIGVTALRM, &sa, NULL);

  /*Setting values for half second interval*/
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 500000;
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 500000;


  /*Set timer*/
  setitimer (ITIMER_VIRTUAL, &timer, NULL);

  for(;;)
  {
    if(end)
    {
      printf("Time's up!\n");
      break;
    }
  }
  return 0; 
}
