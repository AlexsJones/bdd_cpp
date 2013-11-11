/*
 * =====================================================================================
 *
 *       Filename:  template_factory.c
 *
 *    Description:  produces cpp files
 *
 *        Version:  1.0
 *        Created:  11/11/13 18:28:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  jonesax@hush.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "template_factory.h"
#include <string.h>
#define METHOD "void %s%s()\n{\n};"

void format_string_with_underscore(char **s)
{
	char *_s = *s;
	while(*_s != '\0')
	{
		if(*_s == ' ')
		{
			*_s = '_';
		}
		++_s;
	}
}
void template_from_commands(command_obj *o)
{	
	char buffer[sizeof(char)*1024];

	format_string_with_underscore(&o->gc);
	sprintf(buffer,METHOD,"Given",o->gc);
	printf("%s\n",buffer);

	bzero(buffer,sizeof(char)*1024);
	format_string_with_underscore(&o->wc);
	sprintf(buffer,METHOD,"When",o->wc);
	printf("%s\n",buffer);

	while(o->ac->head)
	{
		bzero(buffer,sizeof(char)*1024);
		char *d = o->ac->head->_data;
		format_string_with_underscore(&d);
		sprintf(buffer,METHOD,"And",d);
		printf("%s\n",buffer);
		o->ac->head = o->ac->head->next_node;
	}
	bzero(buffer,sizeof(char)*1024);
	format_string_with_underscore(&o->tc);
	sprintf(buffer,METHOD,"When",o->tc);
	printf("%s\n",buffer);

}
