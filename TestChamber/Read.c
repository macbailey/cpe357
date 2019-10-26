#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#define size 8192
void readIt(int fd)
{
  char buff[size];
  int num; 
  size_t byte_size = 2; 
  while((num = read(fd, buff, byte_size)))
  {
    write(fd, buff, num); 
  }
  close(fd); 
}