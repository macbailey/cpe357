#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

#define ITIMER_REAL      0
#define ITIMER_VIRTUAL   1
#define ITIMER_PROF      2

/*int main(int argc, char *argv[])
{
  char input = '\0'; 

  if(argv[1] != NULL)
    input = *argv[1]; 
  if(isalpha(input))
  {
    if(isdigit(input))
    {
      printf("It has both\n");
    } else{
      printf("it is not a digit\n");
    }
    
  } else {
    printf("It is a digit\n");
  }
  return 0; 
}*/

void handler (int number)
{
 static int count = 1;
 if(count++%2)
 {
  printf("tick\n");
 } else {
  printf("tock\n");
 }
}

int main ()
{
  struct sigaction sa;
  struct itimerval timer;
  signal(SIGALRM, handler);

  /*Install timer_handler as the signal handler for SIGVTALRM.*/
  memset (&sa, 0, sizeof(sa));
  sa.sa_handler = handler;
  sigaction (SIGVTALRM, &sa, NULL);

  /* Configure the timer to expire after 250 msec...*/
  timer.it_value.tv_sec = 0;
  timer.it_value.tv_usec = 500000;

  /* ... and every 250 msec after that. */
  timer.it_interval.tv_sec = 0;
  timer.it_interval.tv_usec = 500000;

  /* Start a virtual timer. It counts down whenever this process is
  executing. */
  setitimer (ITIMER_VIRTUAL, &timer, NULL);

  /* Do busy work. */
  while (1);
}
