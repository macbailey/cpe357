#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "mytar.h"

void extract_Archive(char* tar_file, int num_Files, 
  char** filenames, int v_Flag, int s_Flag)
{
  int fd; 
  struct header hdr; 
  char buf_Header[512] = {'\0'};
  char end_of_header[1024] = {'\0'};
  fd = open(tar_file, O_WRONLY);

  read(fd, stdout, 100);
  fflush(stdout);
  read(fd, &hdr.mode, 8);
  read(fd, &hdr.uid, 8);
  read(fd, &hdr.gid, 8);
  read(fd, &hdr.size, 12);
  read(fd, &hdr.mtime, 12);
  read(fd, &hdr.chksum, 8);
  read(fd, &hdr.typeflag, 1);
  read(fd, &hdr.linkname, 100);
  read(fd, &hdr.magic, 6);
  read(fd, &hdr.version, 2);
  read(fd, &hdr.uname, 32);
  read(fd, &hdr.gname, 32); 
  read(fd, &hdr.devmajor, 8); 
  read(fd, &hdr.devminor, 8); 
  read(fd, &hdr.prefix, 155);
  read(fd, &hdr.more, 12);

}