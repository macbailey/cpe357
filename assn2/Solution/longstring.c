/*
*  A  Utility  routine  that  reads  a  string  of  alphabetic  characters
*  and  returns  a  pointer  to  an  internam  buffer  containing  the  string.
*  All  leading  and  trailing  non–alphabetic  characters  are  ignored.
*
*  Revision  History:
*
*       $Log:  longstring.c,v  $
*       Revision  1.1   2004–02–18  12:21:16–08   pnico
*       Initial  revision                                                                                                                                                                                                       10
*
*
*/

#include  <string.h>
#include  <ctype.h>
#include  <stdlib.h>
#include  <stdio.h>

#define  CHUNK  80                                                                                                                                                                                                       20

char  *s  readstring(FILE  *infile){
	/*  s   readstring()  reads  a  string  of  arbitrary  length  from  the  given
	*  file  and  returns  a  pointer  to  a  lowercase  version  of  it  in  a  local
	*  buffer.    This  is  only  guaranteed  to  exist  until  the  next  call  to
	*  s   readstring()
	*
	*  The  technique  is  to  read  the  string  into  an  allocated  buffer,  increasing
	*  the  buffer  size  as  necessary.    As  the  buffer  size  grows  it  will
	*                                                                                                                                                                                                                                         30
	*  RETURNS:
	*     A  pointer  to  the  buffer,  or  NULL  if  there  is  no  string.
	*
		*/
	int  len;
	static  char  *buff=NULL;
	char  *ret; 
	int  size=0; 
	int  c;
	/*  Allocate  the  initial  buffer  to  hold  the  string  as  we  grow  */
	if  (  buff  ==  NULL  ) {
		size=CHUNK;
		if(NULL==(buff=(char*)malloc(size  *  sizeof(char))))  {
			perror("s_readstring");
			exit(−1);
		}
	}

	/*  skip  leading  non–alphabetic  characters  */                                                                                                                                                  50
	for  (  c  =  getc(infile)  ;  (c!=EOF)  &&  !  isalpha(c)  ;  c  =  getc(infile))
		/*  nothing  */;

	/*  now  read  the  string.    c  already  has  a  value  from  above  */
	for(  len=0  ;  isalpha(c)  &&  (c!=EOF)  ;  c=getc(infile)  )  {
		if(  len  >=  size−2  )  {              /*  buffer  is  too  small  */
			size  +=  CHUNK;
			if(NULL==(buff=(char*)realloc(buff,size  *  sizeof(char))))  {
				perror("s_readstring");
				exit(−1);                                                                                                                                                                                                                  60
			}
		}
		buff[len++]=tolower(c);
	}
	buff[len]=’\0’;              /*  final  nul  */

	if (len) {
		ret  =  buff;
	}  else  {
		ret  =  NULL;                                                                                                                                                                                                                 70
	}
	return ret; 
}
