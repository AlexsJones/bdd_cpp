/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Entrypoint for pickle framework
 *
 *        Version:  1.0
 *        Created:  11/19/13 07:42:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <jnxc_headers/jnxterm.h>
#include "pickle.h"
void pickle_not_implemented()
{
	jnx_term_printf_in_color(JNX_COL_YELLOW,"NOT IMPLEMENTED\n");
	jnx_term_default();
}
