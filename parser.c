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
#include <jnxc_headers/jnxhash.h>
#include "parser.h"
char *i[6] = { "Feature","Scenario","Given","When","And","Then" };
jnx_hashmap *gherkinmap = NULL;
void write_data(int context,char *str)
{
	if(gherkinmap == NULL)
	{
		gherkinmap = jnx_hash_init(1024);
	}
	char *stored = jnx_hash_get(gherkinmap,i[context]);
	if(!stored)
	{
		printf("Storing for first time in hashmap [%s][%s]\n",i[context],str);
		jnx_hash_put(gherkinmap,i[context],str);
	}
	else
	{
		int l = strlen(stored) + strlen(str);
		char *stored_string = malloc(sizeof(char)*l);
		strcpy(stored_string,stored);
		strcat(stored_string,str);
		free(str);
		free(stored);
		printf("Writing to hashmap [%s][%s]\n",i[context],stored_string);
		jnx_hash_put(gherkinmap,i[context],stored_string);
	}
}
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
			write_data(current_context,cl);
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
