#ifndef MYTAR_H_
#define MYTAR_H_

#define FILE_NAME_LENGTH 100
#define MODE_LENGTH 8
#define UID_LENGTH 8
#define GID_LENGTH 8
#define SIZE_LENGTH 12
#define MTIME_LENGTH 12
#define CHKSUM_LENGTH 8
#define LINK_NAME_LENGTH 100
#define MAGIC_LENGTH 6
#define VERSION_LENGTH 2
#define UNAME_LENGTH 32
#define GNAME_LENGTH 32
#define DEVMAJOR_LENGTH 8
#define DEVMINOR_LENGTH 8
#define PREFIX_LENGTH 155
#define MORE_LENGTH 12

/*Struct for header*/
struct header {
  char name[FILE_NAME_LENGTH];
  char mode[MODE_LENGTH]; 
  char uid[UID_LENGTH]; 
  char gid[GID_LENGTH];
  char size[SIZE_LENGTH];
  char mtime[MTIME_LENGTH];
  char chksum[CHKSUM_LENGTH];
  char typeflag;
  char linkname[LINK_NAME_LENGTH];
  char magic[MAGIC_LENGTH]; 
  char version[VERSION_LENGTH];
  char uname[UNAME_LENGTH];
  char gname[GNAME_LENGTH];
  char devmajor[DEVMAJOR_LENGTH]; 
  char devminor[DEVMINOR_LENGTH]; 
  char prefix[PREFIX_LENGTH];
  char more[MORE_LENGTH];
};
#endif
