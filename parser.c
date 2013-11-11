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
typedef enum context { GIVEN, WHEN, AND, THEN } context;
char *i[4] = { "Given","When","And","Then" };
command_obj *parse_file_to_data(char *fp)
{
	context current_context = -1;
	state current_state = SEEKING;	
	///
	command_obj *cobj = malloc(sizeof(command_obj));
	cobj->ac = jnx_list_init();
	cobj->ac_c = 0;
	///
	char *b;
	size_t rb = jnx_file_read(fp,&b);	
	if(rb == 0)
	{
		printf("Unable to read file\n");
		return NULL;
	}
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
						current_context = l;
						break;
					}
					else{
						//			printf("No match between %s %s\n",word,i[l]);
					}
				}		
				break;
			case FOUND:
				printf("\n");	
				char *sp = b;	
				int _l = 0;
				while(*sp != '\n') ++_l,++sp;
				char *a = malloc(sizeof(char) *_l);
				memcpy(a,b,sizeof(char) * _l);	
				b = b + _l +1;
				switch(current_context)
				{
					case GIVEN:
						cobj->gc = a;
						break;
					case WHEN:
						cobj->wc = a;
						break;
					case AND:
						cobj->ac_c++;
						jnx_list_add(cobj->ac,a);
						break;
					case THEN:
						cobj->tc = a;
						break;
				}
				current_state = SEEKING;
				break;
		}
	}
	return cobj;
}
void command_obj_delete(command_obj *o)
{
	free(o->gc);
	free(o->wc);
	int c;
	jnx_node *h = o->ac->head;
	while(h)
	{
		free(h->_data);
		h = h->next_node;
	}
	jnx_list_delete(&o->ac);
	free(o->tc);
	free(o);
}
