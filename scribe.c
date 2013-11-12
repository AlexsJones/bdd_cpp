/*
 * =====================================================================================
 *
 *       Filename:  scribe.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/12/13 17:58:36
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
#include "scribe.h"
#include <jnxc_headers/jnxfile.h>
#define HEADER "/*\
 * =====================================================================================\n\
 *\n\
 *       Filename:          \n\
 *\n\
 *    Description:  \n\
 *\n\
 *        Version:  1.0\n\
 *        Created:  \n\
 *       Revision:  none\n\
 *       Compiler:  gcc\n\
 *\n\
 *         Author:  ANON, \n\
 *   Organization:  \n\
 *\n\
 * =====================================================================================\n\
 */\n"

void scribe_new(jnx_hashmap *h)
{
	printf("Scribing new file\n");

	jnx_file_write("Testout.cpp",HEADER,strlen(HEADER));
	
}
