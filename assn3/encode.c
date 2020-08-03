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

uint32_t number_Of_Chars = 0; 
uint8_t character;
uint32_t count_of_character = 0; 
int i,j, huff_length;
char* shutUp; 
unsigned char newCount;
unsigned int count = 0;
ssize_t read_in; 
char buffer[BUF_SIZE]; 
size_t array_length = 0; 

/*Writes out the header*/
char* header(int fd, node_ptr freq_counter)
{
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_counter[i].huff_code != NULL)
			number_Of_Chars++;
	}

	write(fd, &number_Of_Chars, 4); 
	for(i = 0; i < MAX_COUNT; i++)
	{
		if(freq_counter[i].huff_code != NULL)
		{
			character = freq_counter[i].name; 
			count_of_character = freq_counter[i].count; 
			write(fd, &character, 1);
			write(fd, &count_of_character, 4);
		}
		
	}

	return shutUp; 
}

/*Writes out the body*/
void writeBody(int fd, char* code)
{
  uint8_t character = 000000000;
/*  uint8_t j; 
*/  int i; 
  int k; 
  for(i = 0; i < 8; i++)
  {
    character <<= 1;
    if(code[i] ==  1)
    {
      character |= 0x01;
    }
  }

  k = write(fd, &character, sizeof(character));
  if (k == -1 )
  {
    perror("write"); 
  }

}

/*Encodes each character using huffman codes*/
void encode(int in_fd, int out_fd,  node_ptr freq_counter)
{
  int bit_Count = 0;
  int i; 
  char* code_again = malloc(sizeof(char)*8);
  while((read_in = read(in_fd, &buffer, BUF_SIZE)) > 0)
  {
    for(i = 0; i < MAX_COUNT; i++)
    {
      if(buffer[0] == freq_counter[i].name)
      {
        huff_length = (int)strlen(freq_counter[i].huff_code);

        for(j = 0; j < huff_length; j++)
        {
          /*printf("huff code: %c\n", freq_counter[i].huff_code[j]);*/
          if(freq_counter[i].huff_code[j] == '1')
          {
            code_again[bit_Count] = 1; 
          }
          if(freq_counter[i].huff_code[j] == '0') 
          {
            code_again[bit_Count] = 0; 
          }
          bit_Count++; 
          /*printf("code: %d\n", temp);*/
          if(bit_Count >= 8)
          {
            writeBody(out_fd, code_again);
            bit_Count = 0; 
          }
        }
      }
    }
  }
  if(bit_Count != 0)
  {
    for(i = bit_Count; i < 8; i++)
    {
      code_again[i] = 0;    
    }
    writeBody(out_fd, code_again);
  }
}

