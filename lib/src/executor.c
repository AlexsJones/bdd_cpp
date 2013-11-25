/*
 * =====================================================================================
 *
 *       Filename:  executor.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/13 18:37:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <jnxc_headers/jnxterm.h>
#include <jnxc_headers/jnxhash.h>
#include "executor.h"
#include <stdio.h>
#define __USE_XOPEN_EXTENDED
#include <ftw.h>
extern jnx_hashmap *configuration;

void run(char *filepath)
{
	char buffer[512];
	sprintf(buffer,"%s/%s",jnx_hash_get(configuration,"BUILDPATH"),filepath);
	printf("%s\n",buffer);
	int ret = system(buffer);
	switch(ret)
	{
		case 0:
			jnx_term_printf_in_color(JNX_COL_GREEN,"PASS\n");
			jnx_term_default();	
			break;
		default:
			jnx_term_printf_in_color(JNX_COL_RED,"FAIL\n");
	}
}
int file_walk(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	switch(typeflag)
	{
		case FTW_F:
			printf("Running [%s]\n",fpath + ftwbuf->base);
			run((char*)fpath + ftwbuf->base);		
			break;
	}
	return 0;
}
void execute()
{
	nftw(jnx_hash_get(configuration,"BUILDPATH"),file_walk,atoi(jnx_hash_get(configuration,"FTWDEPTH")),FTW_DEPTH | FTW_SL);
}
