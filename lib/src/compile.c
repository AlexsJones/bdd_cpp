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
static char *executable_name(char *filename)
{
	char *n = malloc(sizeof(char)*512);
	char *name = strdup(filename);
	bzero(n,sizeof(char)*512);
	strncpy(n,"test_",strlen("test_"));
	strtok(name,".");
	strncat(n,name,strlen(name));
	free(name);
	return n;
}
static char *build_string(char *fpath,char *obj_references, char *framework_references, char *test_exe)
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
	strncat(b,test_exe,strlen(test_exe));
	return b;
}
int compile_test(char *fpath)
{
	//get the framework path
	char *framework_path = jnx_hash_get(configuration,"FRAMEWORK");
	assert(framework_path);
	//get test_exe name
	char *test_exe_name = executable_name(fpath);
	printf("NAME:  %s\n",test_exe_name);

	if(file_exists(test_exe_name))
	{
		printf("Removing defunct binary file\n");
		remove(test_exe_name);
	}
	//get the reference path
	char *ref_path = get_ref_path(strdup(fpath));
	if(!file_exists(ref_path))
	{
		//create new .pickled file
		FILE *fp;
		if((fp = fopen(ref_path,"w")) == NULL)
		{
			return 1;
		}
		fclose(fp);
	}
	//read from pickled file	
	char *ref_buffer;
	size_t o = jnx_file_read(ref_path,&ref_buffer);
	if(ref_buffer[strlen(ref_buffer) -1] == '\n') 
	{
		ref_buffer[strlen(ref_buffer) -1] = '\0';
	}
	//create build string
	char *out = build_string(fpath,ref_buffer,framework_path,test_exe_name);
	printf("-->%s<--\n",out);

	//int ret = system(out);
	free(out);
	free(ref_buffer);
	free(ref_path);
	free(test_exe_name);
	return 0;
}
