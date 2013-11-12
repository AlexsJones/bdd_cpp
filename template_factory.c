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
#include <jnxc_headers/jnxfile.h>
#define TEMPLATE "template/template.cpp"
#define METHOD "void %s%s()\n{\n\n};\n"
void write_to_template_setup()
{
	int exists = 0;
	FILE *fp = fopen(TEMPLATE,"r");
	if(fp != NULL) exists = 1;fclose(fp);
	if(exists)
	{
		remove(TEMPLATE);
	}
}
void write_to_template(char *s)
{
	FILE* fp;
	if ((fp = fopen(TEMPLATE, "a")) == NULL) {
		perror("file: ");
		exit(1);
	}
	size_t size = fwrite(s, 1,strlen(s), fp);
	fclose(fp);
}
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
	write_to_template_setup();


	char buffer[sizeof(char)*1024];

	format_string_with_underscore(&o->gc);
	sprintf(buffer,METHOD,"Given",o->gc);
	printf("%s\n",buffer);
	write_to_template(buffer);
	bzero(buffer,sizeof(char)*1024);
	format_string_with_underscore(&o->wc);
	sprintf(buffer,METHOD,"When",o->wc);
	printf("%s\n",buffer);
	write_to_template(buffer);
	while(o->ac->head)
	{
		bzero(buffer,sizeof(char)*1024);
		char *d = o->ac->head->_data;
		format_string_with_underscore(&d);
		sprintf(buffer,METHOD,"And",d);
		printf("%s\n",buffer);
		write_to_template(buffer);
		o->ac->head = o->ac->head->next_node;
	}
	bzero(buffer,sizeof(char)*1024);
	format_string_with_underscore(&o->tc);
	sprintf(buffer,METHOD,"Then",o->tc);
	printf("%s\n",buffer);
	write_to_template(buffer);

}
