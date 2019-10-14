/*
* fw: frequent words
*/
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>                                                 

#include "longstring.h"
#include "tally.h"

#define DEFAULT WORDS 10

void usage(char *s) {
	fprintf(stderr,
		"usage: %s [-n num] [ file1 [ file2 [...] ] ]\n",s);
	exit(EXIT FAILURE);                                                 
}

int convert int(char *s) {
	/* convert a string to an integer, checking for conversion errors in
	* the process. LOngs are bigger than ints, so we have to check for
	* that overflow, too.
	*/
	long res;
	char *end;
	if (!s) {
		fprintf(stderr,"convert_int: NULL string argument\n");                                                       30 fprintf(stderr,"convert_int: NULL string argument\n");
		usage("fw");
	}
	res = strtol(s,&end,0);
	if (*end) {
		fprintf(stderr,"%s: not a well-formed number\n",s);
		usage("fw");
	}

	if (INT MIN > res || INT MAX < res ) {
		/* make sure the result is not too big or too small */                                
		errno = ERANGE;
		perror(s);
		usage("fw");
	}
	return (int)res;
}

int main(int argc, char *argv[]) {
	FILE *infile;
	char *inname="stdin";                                                
	int i;
	int num words = DEFAULT WORDS;
	int fileidx = 1; 
	char *s; 
	wordlist *list;

	/* process the command–line argument */
	if ( argc > 1 ) {
		if ( !strncmp(argv[1],"-n",2) ) {
			if ( argv[1][2] != ’\0’ ) {                                              
				/* it’s of the form –n30 */
				num words=convert int(argv[1]+2);
				fileidx = 2;
			} else if ( argc > 2) {
				/* it’s of the form –n 30 */ 
				num words=convert int(argv[2]); 
				fileidx = 3;
			} else {
				/* it’s neither. Somebody blew it */
				fprintf(stderr,                                                   
					"usage: %s [-n num] [ file1 [ file2 [...] ] ]\n",argv[0]);
				exit(−1);
			}
		}
	}

	/* make sure the number makes sense */
	if ( num words < 0 ) {
		fprintf(stderr,"%s:  It is not possible to count fewer than zero words\n",
			argv[0]);                                                                                                        
		exit(−2);
	}

	/* read the files (or stdin) and process the words */
	if ( fileidx < argc ) {      /* there are files on the command line */
		for (infile=NULL; fileidx < argc && !infile; fileidx++) {
			inname = argv[fileidx]; 
			infile = fopen(inname,"r"); 
			if ( !infile ) {
				perror(inname);                                                                                                   
			}
		}
	} else {
		infile = stdin;
		inname = "stdin";
	}

	while ( infile ) {
		while ( NULL != ( s = s readstring(infile) ) ) {
			/* Note: s  readstring() returns a pointer to a statically                                                          
			* allocated memory region.  This pointer can only be relied
			* upon until the next call to s  readstring().
			*   The point of this is to eliminate many unnecessary copies.
			*/
		tally string(s);
		}

		/* open the next file, if any */
		if ( fclose(infile) ) {
			perror(inname);                                                                                                   
		};

		/* open the next file, if any */
		for (infile=NULL; fileidx < argc && !infile; fileidx++) {
			inname = argv[fileidx]; 
			infile = fopen(inname,"r"); 
			if ( !infile ) {
				perror(inname);
			}
		}	                                                                                                                   
	}

	/* report the results */
	printf("The top %d words (out of %d) are:\n",num words, count table());
	list = tally topN(num words);
	for (i=0 ; list[i]; i++ ){
		printf("%9d %s\n",list[i]−>count, list[i]−>word);
	}

	return 0; 
}