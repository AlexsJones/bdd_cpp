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
#include "compile.h"
#include <jnxc_headers/jnxfile.h>
static char *ref_exists(char *fpath)
{

	char *buffer = malloc(sizeof(char) *1024);
	char *pch = strtok(fpath,".");	

	//RESET AFTER TOK ! ! ! TODO
	strcpy(buffer,pch);
	strcat(buffer,".");
	strcat(buffer,REF_FILE_EXT);
	printf("%s\n",buffer);
	struct stat t;
	int status = stat(buffer,&t);
	if(status != -1)
	{
		return buffer;
	}
	free(buffer);
	free(fpath);
	return NULL;
}
static char *build_string(char *fpath,char *obj_references)
{
	char *b = malloc(sizeof(char) * 2048);
	strcpy(b,COMPILER);
	strcat(b," ");
	strcat(b,fpath);
	strcat(b," ");
	strcat(b,obj_references);
	strcat(b," ");
	strcat(b,"-o");
	//filename
	strcat(b," ");
	strcat(b,"test_");
	strcat(b,fpath);
	return b;
}
int compile_test(char *fpath)
{
	char *ref_path;
	if((ref_path = ref_exists(strdup(fpath))) == NULL)
	{
		return 1;
	}
	char *refstr;
	size_t s = jnx_file_read(ref_path,&refstr);
	free(ref_path);
	char *out = build_string(fpath,refstr);
	free(refstr);

	printf("build string : %s\n",out);
	//compile recursively with pickle.cmp
	free(out);	
	return 0;
}
