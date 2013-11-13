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
 *        Created:  %s\
 *       Compiler:  gcc\n\
 *\n\
 *         Author:  ANON, \n\
 *\n\
 * =====================================================================================\n\
 */\n"
#define METHOD "int %s(scenario *s)\n{\n\n};\n"
char *scribe_write_header(char *filename,char *desc)
{
	char *s = malloc(sizeof(char) * (strlen(HEADER) + strlen(filename)));
	time_t t;
	time(&t);
	char *createtime = ctime(&t);
	sprintf(s,HEADER,filename,desc,createtime);
	return s;
}
char *remove_empty_spaces(char *s)
{
	int c = 0;
	while(s[c] != '\0')
	{
		if(s[c] == ' ')
		{
			s[c] = '_';
		}	
		++c;
	}
	return s;
}
char *scribe_write_method(char *name)
{
	char buffer[512];
	sprintf(buffer,METHOD,name);
	return strdup(buffer);
}
void scribe_new(jnx_hashmap *h)
{	
	printf("Scribing new file\n");
	char *_header = scribe_write_header(jnx_hash_get(h,"Feature"),jnx_hash_get(h,"Scenario"));
		
	char *_gm = scribe_write_method(jnx_hash_get(h,"Given"));
	char *_wm = scribe_write_method(jnx_hash_get(h,"When"));
	char *_tm = scribe_write_method(jnx_hash_get(h,"Then"));

	printf("%s%s%s%s\n",_header,_gm,_wm,_tm);
}
