/*
 * =====================================================================================
 *
 *       Filename:  filesys.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/13/13 18:12:11
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
#include <sys/types.h>
#include <sys/stat.h>
#include "filesys.h"
#define __USE_XOPEN_EXTENDED
#include <ftw.h>
#include <jnxc_headers/jnxhash.h>
#include "compile.h"
extern jnx_hashmap *configuration;
static int dir_exists(char *dir)
{
	struct stat t;
	int status = stat(dir,&t);
	if(status == -1) return 0;

	if(S_ISDIR(t.st_mode))
	{
		return 1;
	}else{
		return 0;
	}
}
int feature_walk(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{

	jnx_list *feature_contents = NULL;
	switch(typeflag)
	{
		case FTW_F:
			feature_contents= parse_file_to_data((char*)fpath + ftwbuf->base);
			if(feature_contents){
				scribe_new(feature_contents,(char*)fpath + ftwbuf->base);
			}
			break;
	}
	return 0;
}
void filesys_steps_from_features()
{
	char *featurepath = jnx_hash_get(configuration,"FEATUREPATH");

	if(!dir_exists(featurepath))
	{
		printf("Could not find a /features folder. Sure it exists?\n");
		return;
	}
	if(dir_exists(jnx_hash_get(configuration,"STEPPATH")))
	{

		printf("step_definitions already exist - Overwrite?[Y/N]\n");
		char c = getchar();
		if(c == 'Y' || c == 'y'){
			nftw(featurepath,feature_walk,atoi(jnx_hash_get(configuration,"FTWDEPTH")),FTW_DEPTH | FTW_SL);
		}
		else{
			printf("Ignoring\n");
		}

	}else{
		int d = mkdir(jnx_hash_get(configuration,"STEPPATH"),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		if(d == 0) { printf("Created new step_definitions directory\n");
			nftw(featurepath,feature_walk,atoi(jnx_hash_get(configuration,"FTWDEPTH")),FTW_DEPTH | FTW_SL);
		}
	}
}
int step_walk(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	switch(typeflag)
	{
		case FTW_F:
			if(!strstr(fpath + ftwbuf->base,REF_FILE_EXT))
			{
				if(compile_test((char*)fpath + ftwbuf->base) != 0)
				{
					printf("Could not find appropriate .pickled file for [%s] object file references\n",fpath+ftwbuf->base);
				}
				else
				{
					//run test?
				}
			}
			break;
	}
	return 0;
}
void filesys_test_from_steps()
{
	char *step_path = jnx_hash_get(configuration,"STEPPATH");
	if(!dir_exists(step_path))
	{
		printf("Could not find /step_definitions folder. Sure it exists?\n");
	}
	//parse
	nftw(step_path,step_walk,atoi(jnx_hash_get(configuration,"FTWDEPTH")),FTW_DEPTH | FTW_SL);

	//compile

	//execute

	//return
}
