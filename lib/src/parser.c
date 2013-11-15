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
jnx_list *components = NULL;

int check_exist(char *key)
{
	jnx_node *h = components->head;
	while(components->head)
	{
		feature_component *f = components->head->_data;
		if(strcmp(f->name,key) == 0)
		{
			components->head = h;
			return 1;
		}
		components->head = components->head->next_node;
	}
	components->head = h;
	return 0;
}
void append_to_existing(char *key, char *value)
{
	jnx_node *h = components->head;
	while(components->head)
	{
		feature_component *f = components->head->_data;
		if(strcmp(f->name,key) == 0)
		{
			// do our appending magic
			char *s = malloc((strlen(value) + strlen(f->str)));	
			strcpy(s,f->str);
			strcat(s," ");
			strcat(s,value);
			free(f->str);
			f->str = s;		
		
			components->head = h;
			return;
		}
		components->head = components->head->next_node;
	}
	components->head = h;

}
void write_data(int global_context,char *str)
{
	if(components == NULL)
	{
		components = jnx_list_init();
	}
	char *key = i[global_context], *value = str;
	if(check_exist(key))
	{
		append_to_existing(key,value);
	}else{
		feature_component *f = malloc(sizeof(feature_component));
		f->name = key;
		f->str = value;
		f->context = global_context;
		jnx_list_add(components,f);
	}
}
int get_context(char *str)
{
	int d;
	for(d=0;d<6; ++d)
	{
		if(strstr(str,i[d]))
		{
			return d;
		}
	}
	return -1;
}
void scan_lines(jnx_list *l)
{
	jnx_node *h = l->head;
	int global_context = 0;
	while(l->head)
	{
		char *cl = l->head->_data;

		int context = get_context(cl);	
		if(context != -1)
		{
			if(context != global_context)
			{
				global_context = context;
			}
		}
		write_data(global_context,cl);
		l->head = l->head->next_node;
	}
}
jnx_list* parse_file_to_data(char *fp)
{
	printf("starting parse_file_to_data: %s\n",fp);
	if(components != NULL)
	{
		jnx_list_delete(&components);
	}
	char *b = NULL;
	size_t rb = jnx_file_read(fp,&b);	
	if(!b)
	{
		printf("Unable to read file\n");
		return NULL;
	}
	printf("1\n");
	char *s = strdup(b);
	printf("2\n");
	free(b);
	printf("3\n");
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
	jnx_list_delete(&lines);
	printf("4\n");
	return components;
}
