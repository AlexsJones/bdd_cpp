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
#include "scribe.h"
int main(int argc, char **argv)
{
	int i,c;
	while((i = getopt(argc,argv,"f:")) != -1)
	{
		switch(i)
		{
			case 'f':
				printf("Input file %s\n",optarg);
				jnx_list *h;
			   	if((h= parse_file_to_data(optarg)) == NULL)
				{
					return 1;
				}
				scribe_new(h);
				break;
		}
	}

	return 0;
}

