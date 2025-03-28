#ifndef _ARM_INTERP_H_
#define _ARM_INTERP_H_

#pragma warning(disable : 4996)

#include "global_data.h"
#include "MIPS_Instruction.h"


// buffer size constant
#define BUFF_SIZE 100

/*
	Purpose: dummy function to test code
	Params: none
	Return: none
*/
void test(void);

/*
	Purpose: dummy function to test code
	Params: none
	Return: none
*/
void test(void);

/*
	Purpose: initializes anything that needs to be initialized
	Params: none
	Return: none
*/
void initAll(void);


/*
	Purpose: menu for assembly to machine conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void assembly2machine(char* buff);


/*
	Purpose: menu for machine to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void machine2assembly(char* buff);


/*
	Purpose: menu for binary to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void binary2assembly(char* buff);


/*
	Purpose: menu for hex to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void hex2assembly(char* buff);

#endif