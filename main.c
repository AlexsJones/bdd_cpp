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
#include <stdio.h>
#include "parser.h"
int main(int argc, char **argv)
{
	int i,c;
	while((i = getopt(argc,argv,"f:")) != -1)
	{
		switch(i)
		{
			case 'f':
				printf("Input file %s\n",optarg);
				command_obj *o = parse_file_to_data(optarg);	
			
				printf("---------------------------\n");
				printf("GIVEN -> %s\n",o->gc);
				printf("WHEN -> %s\n",o->wc);	
				for(c=0;c<o->ac_c;++c)
					printf("AND -> %s\n",jnx_list_remove(&o->ac));
				printf("THEN -> %s\n",o->tc);	
				printf("---------------------------\n");
			
			
				command_obj_delete(o);
				break;
		}
	}


	return 0;
}
