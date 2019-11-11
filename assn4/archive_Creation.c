#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#define PERMS 0644

#include "mytar.h"
#define PATH_MAX 4096
void write_Header(struct header *hdr, char* filename)
{
  int fd; 
  fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC,PERMS);
  write(fd, hdr->name, 100);
  write(fd, hdr->mode, 8);
  write(fd, hdr->uid, 8);
  write(fd, hdr->gid, 8);
  write(fd, hdr->size, 12);
  write(fd, hdr->mtime, 12);
  write(fd, hdr->chksum, 8);
  write(fd, hdr->typeflag, 1);
  write(fd, hdr->linkname, 100);
  write(fd, hdr->magic, 6);
  write(fd, hdr->version, 2);
  write(fd, hdr->uname, 32);
  write(fd, hdr->gname, 32); 
  write(fd, hdr->devmajor, 8); 
  write(fd, hdr->devminor, 8); 
  write(fd, hdr->prefix, 155); 
}
struct header *create_Header(char* path, char* name, struct header *hdr)
{
  struct stat sb; 
  char prefix[255]; 
  if(lstat(path, &sb) < 0)
  {
    perror(path);
    exit(1);
  }
  memset(hdr, 0, 512);
  if(strlen(name) <= 100)
  {
    strcpy(hdr->name, name); 
  } else {
    strcpy(prefix, name); 

  }
  sprintf(hdr->mode, "%.7o", (int)sb.st_mode);
  sprintf(hdr->uid, "%.7o", (int)sb.st_uid);
  sprintf(hdr->gid, "%.7o", (int)sb.st_gid);
  sprintf(hdr->size, "%.11o", (int)sb.st_size);
  sprintf(hdr->mtime, "%.11o", (int)sb.st_mtime);
  /*Make function for checksum*/
  if(S_ISDIR(sb.st_mode))
    hdr->typeflag = '5';
  if(S_ISREG(sb.st_mode))
    hdr->typeflag = '0';
  if(S_ISLNK(sb.st_mode))
  {
    hdr->typeflag = '2';
    readlink(path, hdr->linkname, 100);
  }
  strcpy(hdr->magic, "ustar");
  strcpy(hdr->version, "00");
  strcpy(hdr->uname, getpwuid(sb.st_uid)->pw_name);
  strcpy(hdr->gname, getgrgid(sb.st_gid)->gr_name);
  sprintf(hdr->devmajor,"%.7o", major(sb.st_dev));
  sprintf(hdr->devminor,"%.7o", minor(sb.st_dev));

  return hdr; 
}

void create_Archive(char* archive_name, char* filenames)
{
  DIR *dir; 
  struct dirent *ent;
  char cwd[PATH_MAX];
  struct stat buf;  
  struct header hdr; 
  char path[255];
  printf("%s\n", archive_name);
  if(getcwd(cwd, sizeof(cwd)) != NULL)
  if((dir=opendir(cwd))==NULL)
        perror("dir\n");

  while((ent = readdir(dir)) != NULL)
  {
    if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,".."))
      continue;

    strcat(path, cwd); 
    strcat(path, "/");
    strcat(path, ent->d_name);
    create_Header(path, ent->d_name, &hdr); 
    path[0] = '\0';
    write_Header(&hdr, archive_name);
    lstat(ent->d_name, &buf); 
    if(S_ISDIR(buf.st_mode))
    {
      chdir(ent->d_name);
      create_Archive(archive_name, filenames);
    }
  }
  chdir("..");
  closedir(dir);
}