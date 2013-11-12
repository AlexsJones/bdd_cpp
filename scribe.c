/*
 * =====================================================================================
 *
 *       Filename:  scribe.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/13 17:58:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "scribe.h"
#include <jnxc_headers/jnxfile.h>
#define HEADER "/*\
 * =====================================================================================\n\
 *\n\
 *        %s       \n\
 *\n\
 *   	 %s  \n\
 *\n\
 *        Version:  1.0\n\
 *        Created:  %s\n\
 *       Revision:  none\n\
 *       Compiler:  gcc\n\
 *\n\
 *         Author:  ANON, \n\
 *   Organization:  \n\
 *\n\
 * =====================================================================================\n\
 */\n"
char *scribe_write_header(char *filename,char *desc)
{
	char *s = malloc(sizeof(char) * (strlen(HEADER) + strlen(filename)));
	time_t t;
	time(&t);
	char *createtime = ctime(&t);
	sprintf(s,HEADER,filename,desc,createtime);
	return s;
}
void scribe_new(jnx_hashmap *h)
{
	printf("Scribing new file\n");

	char *s = scribe_write_header(jnx_hash_get(h,"Feature"),jnx_hash_get(h,"Scenario"));
	printf("%s\n",s);
}
