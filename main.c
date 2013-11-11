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
#include "template_factory.h"
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
					
				jnx_node *h = o->ac->head;
				jnx_node *l = o->ac->head;

				while(h)
				{
					printf("AND -> %s\n",h->_data);
					h = h->next_node;
				}	
				h = l;		
				printf("THEN -> %s\n",o->tc);	
				printf("---------------------------\n");
		
				template_from_commands(o);	
			
				command_obj_delete(o);
				break;
		}
	}


	return 0;
}
