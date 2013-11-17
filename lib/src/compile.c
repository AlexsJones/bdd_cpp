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
#include <jnxc_headers/jnxterm.h>
static char *get_ref_path(char *fpath)
{

	char *buffer = malloc(sizeof(char) *1024);
	char *pch = strtok(fpath,".");	
	strcpy(buffer,pch);
	strcat(buffer,".");
	strcat(buffer,REF_FILE_EXT);
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
	strcat(b," ");
	strcat(b,"test_");
	strtok(fpath,".");
	strcat(b,fpath);
	return b;
}
int compile_test(char *fpath)
{
	char *ref_path = get_ref_path(strdup(fpath));
	if(!file_exists(ref_path))
	{
		printf("missing .pickled file for %s\n",ref_path);
		jnx_term_printf_in_color(JNX_COL_RED,"Ignoring test for %s\n",fpath);
		jnx_term_default();
	}
	else{
		char *out = build_string(fpath,ref_path);
		printf("%s\n",out);
		free(out);
	}
	free(ref_path);
	return 0;
}
