/*
 * =====================================================================================
 *
 *       Filename:  parser.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/08/13 08:02:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __PARSER_H__
#define __PARSER_H__
#include <jnxc_headers/jnxlist.h>
typedef struct command_obj{
	char *gc;
	char *wc;
	jnx_list *ac;
	int ac_c;
	char *tc;
}command_obj;
command_obj *parse_file_to_data(char *fp);
#endif
