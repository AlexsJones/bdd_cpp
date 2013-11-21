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
static char *refs(char *test_exe)
{
	char *r = malloc(sizeof(char)*256);
	bzero(r,sizeof(char)*256);
	strncpy(r,test_exe,strlen(test_exe));
	strncat(r,".",1);
	strncat(r,REF_FILE_EXT,strlen(REF_FILE_EXT));

	char *buffer = malloc(sizeof(char)*1024);
	bzero(buffer,sizeof(char)*1024);
	if(!file_exists(r))
	{
		strncpy(buffer," ",1);
	}else{
		char *microbuff;
		size_t read_bytes = jnx_file_read(r,&microbuff);
		strncpy(buffer,microbuff,strlen(microbuff));
				free(microbuff);
				if(buffer[strlen(buffer) -1] == '\n')
				{
					buffer[strlen(buffer) -1] = '\0';
				}
	}
	free(r);
	return buffer;
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
		printf("Removing defunct binary file for [%s]\n",test_exe_name);
		remove(test_exe_name);
	}
	//get the reference path
	char *r = refs(test_exe_name);	
	printf("references ->%s<-\n",r);
	free(r);

	char *build_str = build_string(fpath,r,framework_path,test_exe_name);
	jnx_term_printf_in_color(JNX_COL_MAGENTA,"%s\n",build_str);
	jnx_term_default();
	free(test_exe_name);
	return 0;
}
