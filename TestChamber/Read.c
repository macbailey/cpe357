#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#define size 8192
void readIt(int fd)
{
  char buff[size];
  int num; 
  while((num = read(fd, buff, size_t size)))
  {
    write(STDOUT_FILE END, buff, num); 
  }
  close(fd); 
}