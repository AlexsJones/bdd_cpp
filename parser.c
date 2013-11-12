/*
 * =====================================================================================
 *
 *       Filename:  parser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/13 08:04:37
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
#include <string.h>
#include <strings.h>
#include <jnxc_headers/jnxfile.h>
#include "parser.h"
char *i[6] = { "Feature","Scenario","Given","When","And","Then" };
void scan_lines(jnx_list *l)
{
	jnx_node *h = l->head;
	int current_context = -1;
	while(l->head)
	{
		char *cl = l->head->_data;
		int c;
		for(c=0;c<6;++c)
			if(strstr(cl,i[c]))
		   	{
			   	current_context=c;
		   	}
		
			printf("Processing line with context %d->%s\n",current_context,cl);
		l->head = l->head->next_node;
	}
}
void parse_file_to_data(char *fp)
{
	char *b;
	size_t rb = jnx_file_read(fp,&b);	
	if(rb == 0)
	{
		printf("Unable to read file\n");
		return;
	}
	char *s = strdup(b);
	jnx_list *lines = jnx_list_init();
	while(*s != '\0')
	{
		char line[256];
		bzero(line,256);
		int linelen = 0;
		while(*s != '\n')
		{
			line[linelen] = *s;
			++s,++linelen;
		}
		if(strcmp(line,"") != 0)
		{
			jnx_list_add(lines,strdup(line));
		}
		++s;	
	}	
	scan_lines(lines);

}
