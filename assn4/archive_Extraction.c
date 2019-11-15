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
#include <time.h>
#include <fcntl.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "mytar.h"

int readTar(int fd, void*b, size_t sz);
void extractFile(char *tf,int num,char **fs, int v, int s);
int checkEOF(struct header *hdr);
int checkHeader(struct header *hdr, int s);
char *filename(struct header *hdr, char *b, size_t size);
int isThere(char **fs, int num, const char *name);
uint32_t chksum(struct header *h);
void createParent(char *name);
/*
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
*/
int readTar(int fd, void *b, size_t sz){

    int readfd;
    if ((readfd = read(fd, b, sz)) < 0){
  perror("read");
  exit(1);
  }
    return readfd;
}

void extractFile(char *tf, int num, char **fs, int v, int s){


    struct header hdr;
    long size; 
    int i, block, input, output, permission;
    char buff[512];
    char name[255];

    /*If trouble opening send error*/
    if ((input = open(tf, O_RDONLY, 0)) < 0){
      perror(tf);
      exit(1);
    }


    while (readTar(input,&hdr,512) && !checkEOF(&hdr) && checkHeader(&hdr, s)){
  
  size = strtol(hdr.size,NULL,8);
  block = size/512 + ((size%512) ? 1:0);
  filename(&hdr, name, sizeof(name));
  
  if (!num || isThere(fs, num, name))
  {
      if(v)
    printf("%s\n",name);
      switch (hdr.typeflag)
      {
    case '5':
        mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
        break;
    case '2':
        if (symlink(hdr.linkname, name))
        {
            perror(name);
        }
        break;
    default:
        createParent(name);

        permission = S_IRUSR | S_IWUSR 
        |S_IRGRP | S_IWGRP
        |S_IROTH | S_IWOTH;

        if (strtol(hdr.mode, NULL, 8) & (S_IXUSR | S_IXGRP | S_IXOTH))
      permission |= S_IXUSR | S_IXGRP | S_IXOTH;

        if ((output = open(name, O_WRONLY | O_CREAT, permission)) < 0)
        {
      perror(name);
      exit(1);
        }
        for (i = 0; i < block; i++)
        {
      if (read(input, buff, 512) < 0)
      {
          perror("read");
          exit(1);
      }
      if (size < 512)
      {
          if ((write(output, buff, size)) != size)
          {
        perror("write");
        exit(1);
          }
          break;
      }
      if ((write(output, buff, 512)) != 512)
      {
          perror("write");
          exit(1);
      }
      size -=512;
         }
         close(output);
         break;
    }
      }
  else 
  {
      lseek(input, 512 * (size/512 + ((size%512) ? 1:0)), SEEK_CUR);
  }
     }
     close(input);
}


int checkEOF(struct header *hdr)
{
    return !hdr->name[0] && !hdr->prefix[0];
}

int checkHeader(struct header *hdr, int s)
{
/*  printf("%s\n", hdr->chksum);
  printf("%i\n", chksum(hdr));*/
  if (strtol(hdr->chksum, NULL, 8) != chksum(hdr)){
    fprintf(stderr, "Malformed header found. Bailing.\n");
    /*exit(1);*/
  }
  if (s && (strncmp(hdr->version, "00", strlen("00")) ||
  strcmp(hdr->magic, "ustar")))
  {
    fprintf(stderr, "Version mismatch. Bailing.\n");
    exit(1);
  }
  else if (!s && strncmp(hdr->magic, "ustar", strlen("ustar")))
  {
    fprintf(stderr, "Not a USTAR archive. Bailing\n");
    exit(1);
  }
  return 1;
}

char *filename(struct header *hdr, char *b, size_t size)
{
  memset(b, 0, size);
  if (strlen(hdr->prefix)){
    strncat(b, hdr->prefix, 154);
    strcat(b, "/");
  }
  strncat(b, hdr->name, 100);
  return b;
}

int isThere(char **fs, int num, const char *name)
{
  int i;
  char n[255];
  char f[255];
  char *c;
  for (i = 0; i < num; i++)
  { 
    strcpy(f, fs[i]);
    strcpy(n, name);
    if (f[strlen(f)-1] == '/')
      f[strlen(f)-1] = '\0';
    do 
    {
      if (!strcmp(f, n))
      return 1;
      if ((c = rindex(n, '/')))
      *c = '\0';
    } while (c);
  }
  return 0;
  }


void createParent(char *name){

    char p[255];
    char d[255];
    char *c;
    
    strcpy(p,name);
    memset(d, 0, 255);
    c = strtok(p, "/");
    do 
    {
      strcat(d, c);
      strcat(d, "/");
      mkdir(d, S_IRWXU | S_IRWXG | S_IRWXO);
    } while((c = strtok(NULL, "/")));
    rmdir(d);
}
char *getPermissions(int correct, char typeflag, char *s){

    char everyperm[] = "-rwxrwxrwx";
    int i;

    for (i=10;i>0;i--)
  s[10-i] = (correct & (1<<(i-1))) ? '1' : '0';
    s[10] = '\0';
    for (i = 0;i <10; i++)
  s[i] = (s[i] == '0') ? '-' : everyperm[i];
    if (typeflag == '5')
  s[0] = 'd';
    else if (typeflag == '2')
  s[0] = 'l';
    return s;

}

/*Does this when t option is specified*/
void createTable(char* out_file, int num_Files,
   char** filenames, int v_Flag, int s_Flag)
{
    char ps[11];
    char mt[17];
    char fn[255];
    struct header hdr;
    int fd;
    long size;
    time_t time = (time_t)strtol(hdr.mtime,NULL,8);
    struct tm stm;

    /*open archive*/
    if ((fd = open(out_file,O_RDONLY,0))<0)
  {
  perror(out_file);
  exit(1);
  }
    /*make sure we are looking at valid header*/
    while (read(fd,&hdr,512)>=0 && !checkEOF(&hdr) && checkHeader(&hdr,s_Flag)){
  time = (time_t)strtol(hdr.mtime,NULL,8);
  size = strtol(hdr.size, NULL,8);
  filename(&hdr,fn,sizeof(fn));
  
  if (!num_Files || isThere(filenames,num_Files,fn))
      {
    if (v_Flag){

      localtime_r(&time, &stm);
      sprintf(mt,"%.4d-%.2d-%.2d %.2d:%.2d",
        stm.tm_year + 1900,
        stm.tm_mon + 1,
        stm.tm_mday,
        stm.tm_hour,
        stm.tm_min);
      printf("%.10s %8s/%8s %8ld %.16s %s\n",
        getPermissions(strtol(hdr.mode,NULL,8),
           hdr.typeflag, ps),
        hdr.uname,
        hdr.gname,
        size,
        mt,
        fn);
      
    }
    else 
            printf("%s\n",fn);
  }
  lseek(fd, 512 * (size/512 + ((size%512) ? 1:0)),SEEK_CUR);
  /*exit(1);*/
    }
    
    close(fd);
}