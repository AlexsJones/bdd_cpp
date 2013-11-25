/*
*=====================================================================================
*
*        Feature: I want to test pickle to show that it uses Given,When,Then steps.       
*
*   	 Scenario: Testing pickle with a calculator example.  
*
*        Version:  1.0
*        Created:  Mon Nov 25 07:43:31 2013
*       Compiler:  gcc
*
*         Author:  ANON, 
*
* =====================================================================================
*/
#include <stdio.h>
#include </usr/share/pickle/framework/pickle.h>
#include "../project_code/calc.h"

int _inputA;
int _inputB;
int _expectedOutput;
int _actualOutput;
int Given_I_have_the_initial_setup_variables(void)
{
	_inputA = 3;
	_inputB = 5;
	_expectedOutput = 15;
	return pickle_process(PASS);
};
int When_I_multiply_them_together(void)
{
	_actualOutput = multiply(_inputA,_inputB);
	return pickle_process(PASS);
};
int Then_I_expect_to_see_the_output_variable(void)
{
	if(_actualOutput == _expectedOutput)
	{
		return pickle_process(PASS);
}
	else{
		return pickle_process(FAIL);
	}
};
int main(int argc, char **argv){

int n = 0;
n += Given_I_have_the_initial_setup_variables();
n += When_I_multiply_them_together();
n += Then_I_expect_to_see_the_output_variable();


return n;
 };
