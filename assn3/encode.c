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

void writeBody(int fd, char*code)
{
  uint8_t character = 00000000;
  uint8_t j; 
  int i; 
  for(i = 0; i < 8; i++)
  {
/*    printf("code: %i\n", code[i]);
*/    if(code[i] !=  0)
    {
      character |= 0x01;
    }
    character <<= 1;
  }
  printf("character ");
  for(j = 0x80; j != 0; j >>= 1)
  {
    printf("%c",(character&j)?'1':'0');
    if (j==0x10)
      printf(" ");
  }
  printf("\n");

  write(fd, &character, 2);
}


char* encode(int fd, node_ptr freq_counter, char* code)
{
  int bit_Count = 0;
  int temp; 
  while((read_in = read(fd, &buffer, BUF_SIZE)) > 0)
  {
    for(i = 0; i < MAX_COUNT; i++)
    {
      if(buffer[0] == freq_counter[i].name)
      {
        huff_length = (int)strlen(freq_counter[i].huff_code);

        for(j = 0; j < huff_length; j++)
        {
          if(freq_counter[i].huff_code[j] == '1')
          {
            temp = 1; 
          } else 
            temp = 0; 
          code[bit_Count] = temp;
          temp = 0;
          bit_Count++; 
          if(bit_Count >= 8)
          {
            writeBody(fd, code);
            bit_Count = 0; 
          }
        }
      }
    }
  }
  return code;
}

