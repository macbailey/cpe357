#ifndef MYTAR_H_
#define MYTAR_H_

#define FILE_NAME_LENGTH 100
#define LINK_NAME_LENGTH 100
#define PREFIX_LENGTH 155

stuct header {
  char name[FILE_NAME_LENGTH];
  char mode[8]; 
  char uid[8]; 
  char gid[8];
  char size[12];
  char mtime[12];
  char chksum[8];
  char typeflag[1];
  char linkname[LINK_NAME_LENGTH];
  char magic[6]; 
  char version[2];
  char uname[32];
  char gname[32];
  char devmajor[8]; 
  char devminor[8]; 
  char prefix[PREFIX_LENGTH];
}
