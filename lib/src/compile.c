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
char *ref_exists(char *fpath)
{

	char *buffer = malloc(sizeof(char) *1024);
	char *pch = strtok(fpath,".");	

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
	return NULL;
}
int compile_test(char *fpath)
{
	printf("compile_test\n");
	char *ref_path;
	if((ref_path = ref_exists(fpath)) == NULL)
	{
		return 1;
	}
	printf("Found references\n");

	char *refstr;
	size_t s = jnx_file_read(ref_path,&refstr);
	free(ref_path);
	printf("%s\n",refstr);
	//look step_definitions for pickle.cmp for .c implementation file path references
	
	//compile recursively with pickle.cmp
	

	return 0;
}
