#define BLKSIZE 512 
#define ARG_LIM 11
struct stage {
  int input;
  int output;
  int argc;
  char argv[BLKSIZE][ARG_LIM];
  char cmd[BLKSIZE]; 
};
