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
#include <time.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "mytar.h"

#define PERMS 0644
#define PATH_MAX 4096
#define BUFFER 5000
#define FILE_FLAG 0
#define DIR_FLAG 5
#define LINK_FLAG 2

static int insert_special_int(char *where, size_t size, int32_t val);
static int FLAG_V = 0; 

/*Checksum goes through the header and counts all the characters except for
the memory location for the checksum itself. This area stores spaces for the 
count and then replaces that value with the name*/
uint32_t chksum(struct header *h)
{
   
  unsigned char *c; 
  int i;
  uint32_t s = 0; 
  c = (unsigned char *)h; 
  for(i = 0; i < 512; i++)
    s += (i < 148 || i > 155) ? c[i] : ' ';
  return s; 
}

/*Write Header goes through the structure of the header and writes the 
each elements to the file desciptor decribed by fd*/
void write_Header(struct header *hdr, int fd)
{ 
  if(FLAG_V)
  {
    printf("%s\n", hdr->name);
  }
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

/*Create header populates all the elements listed in the header structure*/
struct header *create_Header(char* name, struct header *hdr)
{
  char blank[8];
  char more_blank[12];
  char most_blank[155];
  struct stat sb; 
  char* postfix; 
  int mode; 
  extern int errno; 
  
  char prefix[255] = {'\0'};

  memset(blank, 0, 8);
  memset(more_blank, 0, 12);
  memset(most_blank, 0, 155);

  if(lstat(name, &sb) < 0)
  {
    printf("--lstat in create_Header-- %s: %s\n", name, strerror(errno));
  }
  memset(hdr, 0, 512);
  
  /*checks if the file name is less than 100, if it is it will 
  write the file name to the prefix. If the name is larger than 
  155 it will continue to write to the name element */
  if(strlen(name) <= 100)
  {
    strncpy(hdr->name, name, 100);
    strncpy(hdr->prefix, most_blank, 155);
  } else {
    strcpy(prefix, name); 

    postfix = prefix + strlen(prefix);

    while((postfix - prefix) > 155)
    {
      *(postfix = rindex(prefix, '/')) = '\0';
    }
    if((postfix = rindex(prefix, '/')))
    {
      *postfix = '\0';
    }

    strncpy(hdr->prefix, prefix, 155); 
    strncpy(hdr->name, name + (postfix - prefix + 1), 100);

  }

  /*sb.st_mode is & with 00777 to clear ensure only correct mode
  is being collected*/
  mode = (int)sb.st_mode & (S_IRWXU|S_IRWXG|S_IRWXO);
  sprintf(hdr->mode, "%7.7o", mode);

  /*Insert Special is a provided function to deal with uid's larger
  than 7 octal digits*/
  insert_special_int(hdr->uid, 8, (int32_t)sb.st_uid);

  sprintf(hdr->gid, "%7.7o", (int)sb.st_gid);

  /*If the file is not a regualr file than it will be coded to have 
  a size of zero*/
  if(S_ISDIR(sb.st_mode))
  {
    sprintf(hdr->size,"%11.11o", 0);
  }
  else
  {
    sprintf(hdr->size, "%11.11o", (int)sb.st_size);
  }

  sprintf(hdr->mtime, "%o", (int)sb.st_mtime);

  /*Depending on the mode the typeflag will change, */
  if(S_ISDIR(sb.st_mode)){
    hdr->typeflag = '5';
  }
  else if(S_ISREG(sb.st_mode)){
    hdr->typeflag = '0';
  }
  else if(S_ISLNK(sb.st_mode))
  {
    hdr->typeflag = '2';
    readlink(name, hdr->linkname, 100);
  } else {
    printf("typeflag setting issue\n");
  }

  strncpy(hdr->magic, "ustar", 6);
  strncpy(hdr->version, "00", 2);

  /*Get group and  user name*/
  strncpy(hdr->uname, getpwuid(sb.st_uid)->pw_name, 32);
  strncpy(hdr->gname, getgrgid(sb.st_gid)->gr_name, 32);

  /*Chose to have devmajor and devminor all zeros */
  strncpy(hdr->devmajor, blank, 8); 
  strncpy(hdr->devminor,blank, 8);

  /*Additional 12 bits for end of header*/
  strncpy(hdr->more, more_blank, 12);

  /*Final checksum amount*/
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

/*Handles all of the files and writes them to fd*/
void file_Wrapper(int fd, char* filename, struct header *hdr)
{
  FILE  *readFile; 
  long fsize;
  int i; 
  int num_Blocks = 0;
  char *string[600] = {'\0'};
  create_Header(filename, hdr);
  write_Header(hdr, fd);

  if((readFile = fopen(filename, "rb")) == NULL)
  {
    printf("open in file_wrapper %s\n", strerror(errno)); 
  }
  
  fsize = strtol(hdr->size, NULL, 8); 
  num_Blocks = fsize/512;
  if(fsize%512)
    num_Blocks++; 

  for(i = 0; i < (num_Blocks); i++)
  {
    memset(string,0,512);
    fread(string, 1, 512, readFile);
    if(ferror(readFile))
      printf("Oh No! fread error\n");
    if((write(fd, string, 512)) == -1)
      printf("%s\n", strerror(errno));
  }
  fclose(readFile);
}

/*Handles all of the directories and sends them filewrapper if they are a file*/
void directory_Wrapper(int fd, char* dir_name, struct header *hdr)
{
  DIR *dir; 
  struct dirent *ent;
  struct stat buf;  
  char fullpath[255] = {'\0'};
  strcpy(fullpath,dir_name);
  strcat(fullpath, "/");

  if((dir=opendir(dir_name))==NULL)
        perror("dir\n");
  create_Header(fullpath, hdr);
  write_Header(hdr, fd);

  while ((ent = readdir(dir)))
  {
    if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, "..")){
      fullpath[0] = '\0'; 
      strcat(fullpath,dir_name);
      strcat(fullpath, "/");
      strcat(fullpath, ent->d_name);
      if (lstat(fullpath,&buf)<0){
        perror(fullpath);
        continue;
      }
      if (strlen(fullpath) > (255)){
        printf("%s: Name too long. Skipping.\n",fullpath);
        continue;
      }
      if (buf.st_mode & S_IFDIR)
      {
        directory_Wrapper(fd, fullpath, hdr);
      } else {
        file_Wrapper(fd, fullpath, hdr);
      }
    }
  }
}

/*Recieves files from mytar and checks for mode 
and prints out railing NULL blocks*/
void create_Archive(char* out_file, int num_Files, 
  char** filenames, int v_Flag)
{
  int i; 
  int fd; 
  struct stat sb;
  struct stat fb;   
  char blank[512]; 
  struct header hdr; 
  if ((fd = open(out_file, O_WRONLY|O_CREAT|O_TRUNC,PERMS)) < 0)
  {
    perror(out_file);
    exit(1);
  }

  lstat(out_file, &fb);

  if(v_Flag)
    FLAG_V = 1; 
  for(i = 0; i < num_Files; i++)
  {
    if(lstat(filenames[i], &sb) < 0)
    {  
      perror(filenames[i]); 
      continue;
    }
    if (strlen(filenames[i]) > (255)){
      printf("%s: Name too long. Skipping.\n", filenames[i]);
      continue;
    }
    if(sb.st_mode & S_IFDIR)
    {
      directory_Wrapper(fd, filenames[i], &hdr); 
    } else {
      file_Wrapper(fd, filenames[i], &hdr); 
    }
  }
  memset(blank, 0, 512); 
  write(fd, blank, 512);
  write(fd, blank, 512);
}