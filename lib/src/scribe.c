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
#include <string.h>
#include <time.h>
#include "parser.h"
#include "scribe.h"
#include <jnxc_headers/jnxfile.h>
#include <jnxc_headers/jnxhash.h>
extern jnx_hashmap *configuration;
#define HEADER "/*\n\
*=====================================================================================\n\
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
*/\n\
#include <stdio.h>\n\
#include <%s/pickle.h>\n\
"
#define METHOD "int?%s(void)\n{\nreturn pickle_not_implemented();\n};\n"
#define CALLER "n?+=?%s();\n"
char *scribe_write_header(char *filename,char *desc)
{
	char *fworkpath = jnx_hash_get(configuration,"FRAMEWORK");
	char *s = malloc(sizeof(char) * (strlen(HEADER) + strlen(filename) + strlen(fworkpath)));
	time_t t;
	time(&t);
	char *createtime = malloc(sizeof(char) * 46);
	ctime_r(&t,createtime);
	sprintf(s,HEADER,filename,desc,createtime,fworkpath);
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
		if(s[c] == '?')
		{
			s[c] = ' ';
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
size_t write_file(char *str,char *path)
{
	FILE* fp;
	if ((fp = fopen(path, "a")) == NULL) {
		perror("file: ");
		return -1;
	}
	size_t size = fwrite(str, 1,strlen(str), fp);
	fclose(fp);
	return size;
}
void purge_existing(char *path)
{
	FILE *fp;
	if((fp = fopen(path,"r")) != NULL)
	{
		fclose(fp);
		remove(path);
	}
}
char *create_feature_name(char *f)
{
	char *pch = strtok(f,".");
	char buffer [256];
	strcpy(buffer,"../");
	strcat(buffer,jnx_hash_get(configuration,"STEPPATH"));
	strcat(buffer,"/");
	strcat(buffer,pch);
	strcat(buffer,".c");
	return strdup(buffer);
}
void scribe_new(jnx_list *h,char *f)
{
	char *stepfilename = create_feature_name(f);
	purge_existing(stepfilename);
	jnx_node *r = h->head;
	jnx_list *methodsl = jnx_list_create();
	char *filename=NULL,*desc=NULL;
	while(h->head)
	{
		feature_component *f = h->head->_data;	

		switch(f->context)
		{
			//Feature
			case 0:
				filename = f->str;
				break;
				//Scenario:
			case 1:
				desc = f->str;
				break;
			default:
				jnx_list_add(methodsl,f);
		}
		h->head = h->head->next_node;
	}
	char *_header = scribe_write_header(filename,desc);
	//write header
	write_file(_header,stepfilename);
	free(filename);
	free(desc);
	jnx_list_destroy(&h);
	
	jnx_node *methodsh = methodsl->head;
	while(methodsl->head)
	{
		feature_component *f = methodsl->head->_data;
		
		char buffer[512];
		sprintf(buffer,METHOD,f->str,f->str);
		//write method
		write_file(remove_empty_spaces(buffer),stepfilename);	
		methodsl->head = methodsl->head->next_node;
	}
	//now lets go over the list again and pull out callers
	methodsl->head = methodsh;
	write_file("int main(int argc, char **argv){\n\nint n = 0;\n",stepfilename);
	while(methodsl->head)
	{
		feature_component *f = methodsl->head->_data;
		char buffer[512];
		sprintf(buffer,CALLER,f->str);
		//write method
		write_file(remove_empty_spaces(buffer),stepfilename);	
		free(f->str);
		free(f);
		methodsl->head = methodsl->head->next_node;
	}
	write_file("\n\nreturn n;\n };",stepfilename);
	jnx_list_destroy(&methodsl);
}
