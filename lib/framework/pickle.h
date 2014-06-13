/*
 * =====================================================================================
 *
 *       Filename:  pickle.h
 *
 *    Description:  Pickle framework
 *
 *        Version:  1.0
 *        Created:  11/22/13 08:18:59
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __PICKLE_MACRO__
#define __PICKLE_MACRO__
typedef enum { PASS, FAIL, NOT_IMPLMENTED }state;
int pickle_process(state _s);
int pickle_evaluate();
#endif
