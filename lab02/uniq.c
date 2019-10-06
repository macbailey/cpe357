#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	FILE *fp; 
	char *read_long_line(FILE *); 

	fp = fopen(*++argv, "w+");
	if (fp == NULL)
	{
		printf("can't open %s\n", *argv);
		return 1; 
	} 
	else 
	{
		if(read_long_line(fp))
			printf("got it\n");
	}

	return 0; 
}
char *read_long_line(FILE *fp)
{
	int c;

	size_t count = 1; 
	while ((c = getchar()) != EOF || (c = getchar()) != '\n')
	{
		++count; 
	}

	char *new;
	//new = safe_malloc(count + 1);
	new = malloc(count);
	// printf("%s\n", new);
	return new;
}


// void *safe_malloc(size_t size)
// {
// 	void *new; 
// 	if ((new = malloc(size)) == NULL)
// 	{
// 		perror("safe_malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	return new; 
// }
