#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  int fd; 

  fd = open(argv[1], O_RDONLY | O_CREAT | O_TRUNC);

}