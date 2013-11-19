/*
 * =====================================================================================
 *
 *       Filename:  compile.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/15/13 18:40:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filesys.h"
#include "compile.h"
#include <jnxc_headers/jnxfile.h>
#include <jnxc_headers/jnxterm.h>
extern jnx_hashmap *configuration;
static char *get_ref_path(char *fpath)
{
	char *buffer = malloc(sizeof(char) *1024);
	char *pch = strtok(fpath,".");	
	strncpy(buffer,pch,strlen(pch));
	strncat(buffer,".",1);
	strncat(buffer,REF_FILE_EXT,strlen(REF_FILE_EXT));
	return buffer;
}
int file_exists(char *f)
{
	struct stat t;
	if(stat(f,&t) != -1)
	{
		return 1;
	}else{
		return 0;
	}
}
static char *build_string(char *fpath,char *obj_references, char *framework_references)
{
	char *b = malloc(sizeof(char) * 2048);
	bzero(b,sizeof(char) * 2048);
	strncpy(b,COMPILER,strlen(COMPILER));
	strncat(b," ",1);
	strncat(b,fpath,strlen(fpath));
	strncat(b," ",1);
	strncat(b,obj_references,strlen(obj_references));
	strncat(b," ",1);
	strncat(b,framework_references,strlen(framework_references));	
	strncat(b,"/*.c",4);
	strncat(b," ",1);
	strncat(b,"-o",2);
	strncat(b," ",1);
	strncat(b,"test_",strlen("test_"));
	strtok(fpath,".");
	strncat(b,fpath,strlen(fpath));
	return b;
}
int compile_test(char *fpath)
{
	char *framework_path = jnx_hash_get(configuration,"FRAMEWORK");
	assert(framework_path);

	char *ref_path = get_ref_path(strdup(fpath));
	if(!file_exists(ref_path))
	{
		FILE *fp;
		if((fp = fopen(ref_path,"w")) == NULL)
		{
			return 1;
		}
	}

	char *ref_buffer;
	size_t o = jnx_file_read(ref_path,&ref_buffer);
	if(ref_buffer[strlen(ref_buffer) -1] == '\n') 
	{
		ref_buffer[strlen(ref_buffer) -1] = '\0';
	}
	char *out = build_string(fpath,ref_buffer,framework_path);
	printf("-->%s<--\n",out);

	//build
	//		int ret = system(out);

	free(out);
	free(ref_buffer);
	free(ref_path);
	return 0;
}
