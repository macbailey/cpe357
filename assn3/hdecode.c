#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include "readAndCount.h"
#define MAX_COUNT 256
#define BUF_SIZE 1
#define BIG_BUFF 4192

node_ptr sortIt(node_ptr unSorted);
void linkIt(node_ptr* head, node_ptr sorted);
void addtree(node_ptr* head);
node_ptr get_Code(node_ptr root, char* code, int pos, node_ptr freq_Counter);
void findLetters(node_ptr freq_Counter, node_ptr root, int in_fd, int out_fd);

int getLength(node_ptr head)
{
  int count = 0;
  node_ptr current = head; 
  while(current != NULL)
  {
    count++;
    current = current->next; 
  }
  return count; 
}
/*
Main file is the start of all commands and tasks, which in order are:
1. Read in header to recieve number of characters and frequency 
2. Sort the files in order of frequency using q sort
3. Create a linked list of the nodes
4. Create a Huffman tree from linked list 
5. Create Huffman codes for each character 
6. Return Huffman codes of each character 
7. Use body of encoded message to decrypt body  
*/

node_ptr readHeader(int fd, node_ptr freq_Counter)
{
  uint32_t numOfChars; 
  uint8_t letter; 
  uint32_t  count_of_letter; 
  unsigned char newCount;
  unsigned int count = 0;
  int i; 

  read(fd, &numOfChars, 4);

  if(numOfChars == 0)
  {
    printf("decode file is empty\n");
    return NULL; 
  }


  /*Initialize nodes*/
  for(count = 0; count < MAX_COUNT; count ++)
  {
    newCount = (char)count;

    freq_Counter[count].name = newCount; 
    freq_Counter[count].count = 0; 
    freq_Counter[count].next = NULL;
    freq_Counter[count].right = NULL;
    freq_Counter[count].left = NULL; 
  }


  for(i = 0; i < numOfChars; i++)
  {
    read(fd, &letter, 1); 
    read(fd, &count_of_letter, 4);
    newCount = (char)letter;
    freq_Counter[letter].count = count_of_letter; 
  }

  return freq_Counter;

}

int main(int argc, char* argv[])
{
  node_ptr head = NULL; 

  int input_fd, output_fd;    

  char* code = malloc(sizeof(char)*MAX_COUNT);

  node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);

    if(argc != 3){
      printf ("Usage: cp file1 file2");
      return 1;
  }

  input_fd = open (argv [1], O_RDONLY);
  if (input_fd == -1) {
          perror ("open");
          return 2;
  }
  if(argv[2] != NULL)
  {
    output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1)
    {
      perror("open");
      return 3;
    }
  }

  if(readHeader(input_fd, freq_Counter) == NULL)
    return 1; 

  freq_Counter = sortIt(freq_Counter); 

  linkIt(&head, freq_Counter);

  while(getLength(head) > 1)
  {
    addtree(&head); 
  }

  freq_Counter = get_Code(head, code, 0, freq_Counter); 

  findLetters(freq_Counter, head, input_fd, output_fd);

  return 0; 
}