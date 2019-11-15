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

#define PERMS 0644
#define PATH_MAX 4096
#define BUFFER 5000

static int insert_special_int(char *where, size_t size, int32_t val);

uint32_t chksum(struct header *h)
{
   
  unsigned char *c; 
  int i;
  uint32_t s = 0; 
  c = (unsigned char *)h; 
  for(i = 0; i < 512; i++)
    s += (i < 148 || i > 155) ? c[i] : ' ';
    /*s += c[i]; */
  return s; 
}

void write_Header(struct header *hdr, int fd)
{ 
  write(fd, hdr->name, 100);
  write(fd, hdr->mode, 8);
  write(fd, hdr->uid, 8);
  write(fd, hdr->gid, 8);
  write(fd, hdr->size, 12);
  write(fd, hdr->mtime, 12);
  write(fd, hdr->chksum, 8);
  if(hdr->typeflag == '0')
  {
    write(fd, "0", 1);
  } 
  if(hdr->typeflag == '5')
  {
    write(fd, "5", 1); 
  }
  if(hdr->typeflag == '2')
  {
    write(fd, "2", 1); 
  }
  write(fd, hdr->linkname, 100);
  write(fd, hdr->magic, 6);
  write(fd, hdr->version, 2);
  write(fd, hdr->uname, 32);
  write(fd, hdr->gname, 32); 
  write(fd, hdr->devmajor, 8); 
  write(fd, hdr->devminor, 8); 
  write(fd, hdr->prefix, 155);
  write(fd, hdr->more, 12);

}

struct header *create_Header(char* name, struct header *hdr)
{
  char blank[8];
  char more_blank[12];
  char most_blank[155];
  struct stat sb; 
  char* post; 
  int mode; 
  extern int errno; 
  
  char prefix[255] = {'\0'};

  memset(blank, 0, 8);
  memset(more_blank, 0, 12);
  memset(most_blank, 0, 155);

  if(lstat(name, &sb) < 0)
    printf("--lstat in create_Header-- %s: %s\n", name, strerror(errno));

  memset(hdr, 0, 512);
  if(strlen(name) <= 100)
  {
    strncpy(hdr->name, name, 100);
    strncpy(hdr->prefix, most_blank, 155);
  } else {
    strcpy(prefix, name); 
    post = prefix + strlen(prefix);

    while((post - prefix) > 155)
    {
      *(post = rindex(prefix, '/')) = '\0';
    }
    if((post = rindex(prefix, '/')))
      *post = '\0';
    strncpy(hdr->prefix, prefix, 155); 
    strncpy(hdr->name, name + (post - prefix + 1), 100);

  }

  mode = (int)sb.st_mode & 00777;
  sprintf(hdr->mode, "%7.7o", mode);

  insert_special_int(hdr->uid, 8, (int32_t)sb.st_uid); 

  sprintf(hdr->gid, "%7.7o", (int)sb.st_gid);

  sprintf(hdr->size, "%11.11o", (int)sb.st_size);

  sprintf(hdr->mtime, "%o", (int)sb.st_mtime);

  strncpy(hdr->chksum, "        ", 8);

  if(S_ISDIR(sb.st_mode))
  {
    hdr->typeflag = '5';
  }
  else if(S_ISREG(sb.st_mode))
    hdr->typeflag = '0';

  else if(S_ISLNK(sb.st_mode))
  {
    hdr->typeflag = '2';
    readlink(hdr->name, hdr->linkname, 100);
  } else {
    printf("typeflag setting issue\n");
  }
  strncpy(hdr->magic, "ustar", 6);
  strncpy(hdr->version, "00", 2);
  strncpy(hdr->uname, getpwuid(sb.st_uid)->pw_name, 32);
  strncpy(hdr->gname, getgrgid(sb.st_gid)->gr_name, 32);

  
  strncpy(hdr->devmajor, blank, 8); 
  strncpy(hdr->devminor,blank, 8);

  strncpy(hdr->more, more_blank, 12);

  
  sprintf(hdr->chksum,"%7.7o", chksum(hdr)); 
  
  return hdr; 
}

static int insert_special_int(char *where, size_t size, int32_t val) {
  
  int err=0;

  if ( val < 0 || ( size < sizeof(val))  ) {
    
    err++;
  } else {
    /* game on....*/
    memset(where, 0, size);     /*   Clear out the buffer  */
    *(int32_t *)(where+size-sizeof(val)) = htonl(val); /* place the int */
    *where |= 0x80;             /* set that high-order bit */
  }

  return err;
}

void file_Wrapper(int fd, char* filename, struct header *hdr)
{
  FILE  *readFile; 
  long fsize;
  int i; 
  int num_Blocks = 0;
  char *string[512] = {'\0'};
  create_Header(filename, hdr);
  write_Header(hdr, fd);

  if((readFile = fopen(filename, "rb")) == NULL);
  {
    printf("open in file_wrapper %s\n", strerror(errno)); 
  }
  

  fsize = strtol(hdr->size, NULL, 8); 
  num_Blocks = fsize/512;
  if(fsize%512)
    num_Blocks++; 
  printf("num_Blocks: %i\n", num_Blocks+1);

  for(i = 0; i < (num_Blocks); i++)
  {

    memset(string,0,512);
    fread(string, 1, 512, readFile);
    if(ferror(readFile))
      printf("fread error\n");
    if((write(fd, string, 512)) == -1)
      printf("%s\n", strerror(errno));

  }
  
  fclose(readFile);
}

void directory_Wrapper(int fd, char* dir_name, struct header hdr)
{
  DIR *dir; 
  struct dirent *ent;
  struct stat buf;  
  char path[255] = {'\0'};
  printf("Incoming Directory Name: %s\n", dir_name);
  if((dir=opendir(dir_name))==NULL)
        perror("dir\n");
  create_Header(dir_name, &hdr);
  write_Header(&hdr, fd);
  chdir(dir_name);
  while((ent = readdir(dir)) != NULL)
  {
    if(!strcmp(ent->d_name,".") || !strcmp(ent->d_name,".."))
      continue;
    printf("directory_Wrapper: %s\n", ent->d_name);

    lstat(ent->d_name, &buf); 

    if(S_ISREG(buf.st_mode))
    {
      file_Wrapper(fd, ent->d_name, &hdr); 

    } else {
      printf("I am a directory\n");

      strcat(path, ent->d_name); 
      strcat(path, "/");

      printf("next directory: %s\n", path);
/*      create_Header(ent->d_name, &hdr);
      write_Header(&hdr, fd);*/ 

      directory_Wrapper(fd, path, hdr);
    }
    path[0] = '\0';

  }
  chdir("..");
  closedir(dir);
}



/*void file_Wrapper(int fd, char* filename, struct header hdr)
{
  int i; 
  FILE* readFile; 
  int buf = '\0';
  int count = 0; 
  char* zero = '\0';
  int remainder = 0; 

  create_Header(filename, &hdr);
  write_Header(&hdr, fd);

  if((readFile = fopen(filename, "rb")))
    printf("open in file_wrapper %s\n", strerror(errno)); 
  while((buf = fgetc(readFile)) != EOF)
  {
    count++; 
    write(fd, &buf, 1); 
  }

  remainder = count % 512;
   printf("count: %i remainder: %i \n", count, re);
  if(remainder != 0)
  {
    for(i = 0; i < remainder; i++)
    {
      write(fd, &zero, 1);
    }
  } 
  fclose(readFile);
}*/

void create_Archive(char* out_file, int num_Files, 
  char** filenames, int v_Flag)
{
  int i; 
  int fd; 
  struct stat sb;  
  char blank[512]; 
  /*Might want to create one header per file*/
  struct header hdr; 
  fd = open(out_file, O_WRONLY|O_CREAT|O_TRUNC,PERMS);
  for(i = 0; i < num_Files; i++)
  {
    if(lstat(filenames[i], &sb) < 0)
      perror(filenames[i]); 
    if(S_ISDIR(sb.st_mode))
    {
      directory_Wrapper(fd, filenames[i], hdr); 
    }
    if(S_ISREG(sb.st_mode))
    {
      printf("Is a regular file \n");
      file_Wrapper(fd, filenames[i], &hdr); 
    }
  }
  memset(blank, 0, 512); 
  write(fd, blank, 512);
  write(fd, blank, 512);
}