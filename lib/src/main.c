/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/13 07:56:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <getopt.h>
#include <jnxc_headers/jnxlist.h>
#include <jnxc_headers/jnxfile.h>
#include <jnxc_headers/jnxterm.h>
#include <unistd.h>
#include <stdio.h>
#include "filesys.h"
#define PAUSE sleep(1);
jnx_hashmap *configuration = NULL;
int main(int argc, char **argv)
{
	configuration = jnx_hash_init(1024);
	jnx_hash_put(configuration,"FEATUREPATH","features");
	jnx_hash_put(configuration,"FTWDEPTH","8");
	jnx_hash_put(configuration,"STEPPATH","step_definitions");
	int c;
	for(c=0;c<argc;++c)
	{
		if(strcmp(argv[c],"gen") == 0)
		{

				jnx_term_load_spinner(1);	
				filesys_steps_from_features();
				PAUSE
				jnx_term_load_spinner(0);
		}
		else{
			printf("====== Pickle =======\n");
			printf("opts: \n");
			printf("gen\n");

		}
	}
	jnx_hash_delete(configuration);
	return 0;
}

