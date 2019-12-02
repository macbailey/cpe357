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
void extract_Archive(char *tf,int num,char **fs, int v, int s);
int checkEOF(struct header *hdr);
int checkHeader(struct header *hdr, int s);
char *filename(struct header *hdr, char *b, size_t size);
int fileSearch(char **fs, int num, const char *name);
uint32_t chksum(struct header *h);
void createDirectory(char *name);


/*Helper function to read the Tar file, reads set amount each time*/
int readTar(int fd, void *b, size_t blksize)
{
  int readfd;
  if ((readfd = read(fd, b, blksize)) < 0)
  {
    perror("readTar");
    exit(1);
  }
  return readfd;
}

/*Main extraction file to retrieve info from the Tar file*/
void extract_Archive(char *tf, int num, char **filenames, int vf, int sf)
{
  struct header hdr;
  long fsize = 0; 
  int i, num_Blocks, input, output, permission;
  char buff[512] = {'\0'};
  char name[255] = {'\0'};

  /*If trouble opening send error*/
  if ((input = open(tf, O_RDONLY, 0)) < 0)
  {
    perror(tf);
    exit(1);
  }

  /*Loop that reads through each block in the header,
  checks validity of header each run through*/
  while (readTar(input, &hdr, 512) && !checkEOF(&hdr))
  {
    /*gives us size of file, and block number info*/
    fsize = strtol(hdr.size, NULL, 8);    
    num_Blocks = fsize/512;
    if(fsize%512)
      num_Blocks++; 
    filename(&hdr, name, sizeof(name));

    /*if valid number of files and file is there*/  
    if (!num || fileSearch(filenames, num, name))
    {
      /*if verbose option selected*/
      if(vf)
        printf("%s\n",name);
      /*checks what type of file we are dealing with*/
      switch (hdr.typeflag)
      {
        /*Is it a directory?*/
        case '5':
          mkdir(name, S_IRWXU | S_IRWXG | S_IRWXO);
          break;
        /*Maybe a symlink?*/
        case '2':
          if (symlink(hdr.linkname, name))
          {
            perror(name);
          }
          break;
        /*Must be a file!*/
        default:
          createDirectory(name);
          permission = S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

        /*permissions*/
        if (strtol(hdr.mode, NULL, 8) & (S_IXUSR|S_IXGRP|S_IXOTH))
        {
          permission |= (S_IXUSR | S_IXGRP | S_IXOTH);
        }

        /*open file to put in data*/
        if ((output = open(name,O_WRONLY|O_CREAT,permission)) < 0)
        {
          perror(name);
          exit(1);
        }   

        /*going through content blocks*/
        for (i = 0; i < num_Blocks; i++)
        {
          if (read(input, buff, 512) < 0)
          {
                perror("read");
                exit(1);
          }
          if (fsize < 512)
          {
            if ((write(output, buff, fsize)) != fsize)
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
          /*reducing number of blocks to look at*/
          fsize -=512;
        }
        close(output);
        break;
      }
    } else {
    /*get correct block to point too*/
    lseek(input, 512 * (fsize/512 + ((fsize%512) ? 1:0)), SEEK_CUR);
    } 
  }
  close(input);
}

/*checks EOF*/
int checkEOF(struct header *hdr)
{
  return (!hdr->name[0] && !hdr->prefix[0]);
}

/*checks if the header is valid*/
int checkHeader(struct header *hdr, int sf)
{
  /*is the checksum good?*/
  if (strtol(hdr->chksum, NULL, 8) != chksum(hdr))
  {
    fprintf(stderr, "Malformed header found via checksum.\n");
  }

  /*does header have correct version?*/
  if (sf && (strncmp(hdr->version, "00", strlen("00")) 
        ||strncmp(hdr->magic, "ustar", strlen("ustar"))))
  {
    fprintf(stderr, "Versions do not match.\n");
    exit(1);
  }

  /*is it USTAR?*/
  else if (!sf && strncmp(hdr->magic, "ustar", strlen("ustar")))
  {
    fprintf(stderr, "Not correct USTAR format.\n");
    exit(1);
  }
  return 1;
}

/*make proper filename*/
char *filename(struct header *hdr, char *b, size_t size)
{
  memset(b, 0, size);
  if (strlen(hdr->prefix))
  {
    strncat(b, hdr->prefix, 154);
    strcat(b, "/");
  }
  strncat(b, hdr->name, 100);
  return b;
}

/*Looks for file specified*/
int fileSearch(char **filenames, int num, const char *name)
{
  int i;
  char n[255] = {'\0'};
  char f[255] = {'\0'};
  char *c;
  for (i = 0; i < num; i++)
  { 
    strcpy(f, filenames[i]);
    strcpy(n, name);
    if (f[strlen(f)-1] == '/')
      f[strlen(f)-1] = '\0';
    do 
    {
      if (!strcmp(f, n))
        return 1;
      if ((c = rindex(n, '/')))
      *c = '\0';
    } 
    while (c);
  }
  return 0;
}

/*creates directory*/
void createDirectory(char *name)
{
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
  } 
  while((c = strtok(NULL, "/")));
    rmdir(d);
}


/*helper function for createTable, gets the perimission for the List/Table*/
char *getPermissions(int correct, char typeflag, char *s)
{
  char everyperm[] = "-rwxrwxrwx";
  int i;

  for (i=10; i>0; i--)
      s[10-i] = (correct & (1<<(i-1))) ? '1' : '0';
      s[10] = '\0';

  /*does spot have a perm?, if not put dash*/
  for (i = 0;i <10; i++)
      s[i] = (s[i] == '0') ? '-' : everyperm[i];

  /*Is a directory?*/
  if (typeflag == '5')
      s[0] = 'd';

  /*Is a link?*/
  else if (typeflag == '2')
      s[0] = 'l';

  return s;
}

/*Does this when t option is specified*/
void createTable(char* out_file, int num_Files,
   char** filenames, int v_Flag, int s_Flag)
{
  char perm[11] = {'\0'};
  char modTime[17] = {'\0'};
  char fn[255] = {'\0'};
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
  while (read(fd,&hdr,512)>=0 && !checkEOF(&hdr) && checkHeader(&hdr,s_Flag))
  {
    /*getting modified time,size,and proper filename*/
    time = (time_t)strtol(hdr.mtime,NULL,8);
    size = strtol(hdr.size, NULL,8);
    filename(&hdr,fn,sizeof(fn));

    if (!num_Files || fileSearch(filenames,num_Files,fn))
    {
      /*if vflag given*/
      if (v_Flag)
      {
        /*getting local time and putting info into time string*/
        localtime_r(&time, &stm);
        sprintf(modTime,"%.4d-%.2d-%.2d %.2d:%.2d",
          stm.tm_year + 1900, stm.tm_mon + 1, stm.tm_mday,
          stm.tm_hour, stm.tm_min);

        /*Calling helper func getPermissions and printing contents*/
        printf("%.10s %8s/%8s %8ld %.16s %s\n",
          getPermissions(strtol(hdr.mode,NULL,8),
          hdr.typeflag, perm), hdr.uname, hdr.gname,
          size, modTime, fn);
      } else {
        printf("%s\n",fn);
      }
    }
    /*look at correct block*/
    lseek(fd, 512 * (size/512 + ((size%512) ? 1:0)),SEEK_CUR);  
  }    
  close(fd);
}