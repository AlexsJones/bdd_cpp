/*
 * =====================================================================================
 *
 *       Filename:  parser.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/13 08:04:37
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
#include <string.h>
#include <strings.h>
#include <jnxc_headers/jnxfile.h>
#include "parser.h"
typedef enum state{ SEEKING, TESTING, FOUND, DONE } state;
char *i[4] = { "Given","When","And","Then" };
command_obj *parse_file_to_data(char *fp)
{
	char *b;
	size_t rb = jnx_file_read(fp,&b);	
	if(rb == 0)
	{
		printf("Unable to read file\n");
		return NULL;
	}
	state current_state = SEEKING;	
	while(current_state != DONE)
	{
		switch(current_state)
		{
			case SEEKING:
				if(*b == '\0') current_state = DONE;	
				int c;
				for(c=0;c<4;++c)
				{
					if(*b == i[c][0])
					{
						current_state = TESTING; 
						printf("%c matches %c from list\n",*b,i[c][0]); 
						break;
					}
				}
				break;
			case TESTING:
				printf("Entering testing %c\n",*b);
				char word[sizeof(char) * 6];
				bzero(word,sizeof(char)* 6);
				int _c=0,_d;
				while(*b != ' ')
				{
					word[_c] = *b;					
					++b,++_c;
				}
				printf("Produced word %s\n",word);
				int l;
				for(l = 0; l < 4; ++l)
				{
					if(strcmp(word,i[l]) == 0)
					{
						current_state = FOUND;
						break;
					}
					else{
			//			printf("No match between %s %s\n",word,i[l]);
					}
				}		
				break;
			case FOUND:
				
				
				printf("->");
				while(*b != '\n')
				{
					printf("%c",*b);
					++b;
				}	
				printf("\n");
				++b;
				current_state = SEEKING;
				break;
		}


	}
}
