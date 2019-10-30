#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "readAndCount.h"
#define MAX_COUNT 256
#define BUF_SIZE 1
#define BIG_BUFF 4192

node_ptr sortIt(node_ptr unSorted);
void linkIt(node_ptr* head, node_ptr sorted);
void addtree(node_ptr* head);
node_ptr get_Code(node_ptr root, char* code, int pos, node_ptr freq_Counter);
char* header(int fd, node_ptr freq_counter);
void encode(int in_fd, int out_fd, node_ptr freq_counter, char* code);

/*
Main file is the start of all commands and tasks, which in order are:
1. Read in file and check for empty files
2. Count frequencies of characters and create nodes for each 
3. Sort the files in order of frequency using q sort
4. Create a linked list of the nodes
5. Create a Huffman tree from linked list 
6. Create Huffman codes for each character 
7. Return Huffman codes of each character  
*/

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

int main(int argc, char* argv[])
{		
	node_ptr head = NULL; 

	int input_fd, output_fd;    /* Input and output file descriptors */


	char* code = malloc(sizeof(char)*MAX_COUNT);

  char* body_buffer = malloc(sizeof(char)*BIG_BUFF);

	node_ptr freq_Counter = malloc(sizeof(node)*MAX_COUNT);



	if(argc != 3){
      printf ("Usage: cp file1 file2");
      return 1;
  }

  /* Create input file descriptor */
  input_fd = open (argv [1], O_RDONLY);
  if (input_fd == -1) {
          perror ("open");
          return 2;
  }
  /* Create output file descriptor */
  if(argv[2] != NULL)
  {
    output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if(output_fd == -1)
    {
      perror("open");
      return 3;
    }
  }
  freq_Counter = readAndFreq(input_fd, freq_Counter);

  close(input_fd);

	freq_Counter = sortIt(freq_Counter); 

	linkIt(&head, freq_Counter);

	while(getLength(head) > 1)
	{
		addtree(&head); 
	}

	freq_Counter = get_Code(head, code, 0, freq_Counter); 

	header(output_fd,  freq_Counter);

  input_fd = open (argv [1], O_RDONLY);

  body_buffer[0] = '\0';

  encode(input_fd, output_fd, freq_Counter, body_buffer);

  return 0; 
}
