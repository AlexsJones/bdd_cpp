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

#define TEMPLATEPATH "template/template.c"

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
size_t write_file(char *str)
{
	FILE* fp;
	if ((fp = fopen(TEMPLATEPATH, "a")) == NULL) {
		perror("file: ");
		return -1;
	}
	size_t size = fwrite(str, 1,strlen(str), fp);
	fclose(fp);
	return size;
}
void purge_existing()
{
	FILE *fp;
	if((fp = fopen(TEMPLATEPATH,"r")) != NULL)
	{
		fclose(fp);
		remove(TEMPLATEPATH);
	}
}
void scribe_new(jnx_list *h)
{
	purge_existing();

	jnx_node *r = h->head;
	jnx_list *methodsl = jnx_list_init();
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
	printf("%s %s\n",filename,desc);
	
	char *_header = scribe_write_header(filename,desc);
	//write header
	write_file(_header);
	printf("Wrote header...\n");
	free(filename);
	free(desc);
	jnx_list_delete(&h);

	while(methodsl->head)
	{
		feature_component *f = methodsl->head->_data;
		
		char buffer[512];
		sprintf(buffer,METHOD,f->str);
		write_file(remove_empty_spaces(buffer));	
		free(f->str);
		printf("Wrote function...\n");	
		free(f);
		methodsl->head = methodsl->head->next_node;
	}
	jnx_list_delete(&methodsl);
	printf("Scribe done!\n");
	printf("Output available at %s\n",TEMPLATEPATH);
}
