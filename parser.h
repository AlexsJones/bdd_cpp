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
#include <jnxc_headers/jnxhash.h>
#include <jnxc_headers/jnxlist.h>
jnx_hashmap* parse_file_to_data(char *fp);
#endif
