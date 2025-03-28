#ifndef _ARM_INSTUCTIONS_H_
#define _ARM_INSTUCTIONS_H_

#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "global_data.h"
#include "Instruction.h"

/*
	gets(char* buffer, int size)
	gets is depreciated and not considered safe, this define replaces
	it with a safer version the works virtually identically
*/
#define gets(x,y); if(fgets(x,y,stdin) != NULL){x[strlen(x)-1] = '\0';}

/*
	Purpose: sets the global instrucion variables to the defualt values
	Params: none
	Return: none
*/
void initInstructs(void);


/*
	Purpose: runs through each _assm function and tries to encode the parsed instruction
	Params: none
	Return: none
*/
void encode(void);

/*
	Purpose: runs through each _bin function and tries to decode the parsed bits
	Params: none
	Return: none
*/
void decode(void);

/*
	Purpose: serves as an indicator for the end of the instruction list
	Params: none
	Return: none
*/
void end_list(void);


/*----------------------------\
			Errors
\----------------------------*/
/*
	Purpose: prints formated error messaged
	Params: char* msg -- message to print
	Return: none
*/
void error(char* msg);


/*----------------------------\
		   Printing
\----------------------------*/
/*
	Purpose: prints a message based on the system status
	Params: none
	Return: none
*/
void printResult(void);

/*
	Purpose: prints the text instruction
	Params: none
	Return: none
*/
void printAssm(void);

/*
	Purpose: prints a parameter
	Params: Param* param - the parameter to print
	Return: none
*/
void printParam(struct Param* param);

//void printShift();

/*
	Purpose: prints thebinary instruction
	Params: none
	Return: none
*/
void printMachine(void);


/*----------------------------\
		   Parsing
\----------------------------*/
/*
	reads the assembly instruction into the instruction struct
*/
void parseAssem(char* line);


/*
	Purpose: reads a parameter from a given line
	Params: char* line - the line to read
			Param* param - the parameter to fill
	Return: char* - the ptr to after the param
*/
char* readParam(char* line, struct Param* param);


/*
	Purpose: converts a string into a decimal number
	Params: char *reg - the string to convert
	Return: char* - the ptr to after the number
*/
uint32_t reg2num(char *reg);


/*
	Purpose: converts a string into either a hex or decimal number
	Params: char* line - the string to convert
			uint32_t* value - the number to fill
	Return: char* - the ptr to after the number
*/
char* immd2num(char* line, uint32_t* value);


/*
	Purpose: parses the given hex line into into the binary instruction
	Params: char* line - the line to convert
	Return: none
*/
void parseHex(char* line);


/*
	Purpose: parses the given binary line into into the binary instruction
	Params: char* line - the line to convert
	Return: none
*/
void parseBin(char* line);




/*----------------------------\
		   Set Bits
\----------------------------*/
/*
	Purpose: sets bits in the binary instruction given a number and a number of bits
	Params: uint32_t start - the bit to start at
			uint32_t num - the number to use as a source of bits
			uint32_t size - the number of bits to set
	Return: none
*/
void setBits_num(uint32_t start, uint32_t num, uint32_t size);


/*
	Purpose: sets bits in the binary instruction given a string
	Params: uint32_t start - the bit to start at
			const char* str - the string to use as a source of bits, skips any x or X characters
	Return: none
*/
void setBits_str(uint32_t start, const char* str);


/*----------------------------\
		  Check Bits
\----------------------------*/
/*
	Purpose: checks if the given series of bits is in the binary instruction
	Params: uint32_t start - the bit to start at
			const char* str - the series of bits to look for, skips any x or X characters
	Return: int - 0 for present, 1 for not present
*/
int checkBits(uint32_t start, const char* str);


/*----------------------------\
		   Get Bits
\----------------------------*/
/*
	Purpose: gets a group of bits from the binary instruction
	Params: uint32_t start - the bit to strt grabbing from
			uint32_t the number of bits to grab
	Return: int - the number represented from the bits
*/
uint32_t getBits(uint32_t start, uint32_t size);

/*----------------------------\
		   Binary to Register
\----------------------------*/
/*
	Purpose: gets a group of bits from the binary instruction
	Params: uint32_t encode - register binary
			uint32_t the number of bits to grab
	Return: int - the number represented from the bits
*/
//uint32_t bin2reg(uint32_t encode);


/*----------------------------\
	 Set Instruction Parts
\----------------------------*/
/*
	Purpose: sets the specified parameter to the specified type and value
	Params: uint32_t param_num - which parameter to change
			Param_Type type - what type to set the parameter to
			uint32_t value - what value to set the parameter to
	Return: 0 for no error
*/
int setParam(uint32_t param_num, Param_Type type, uint32_t value);

/*
	Purpose: sets the opcode field in the instruction
	Params: char* opCode - string to set the op code to
	Return: none
*/
void setOp(char* opCode);



/*----------------------------\
			 Misc
\----------------------------*/
/*
	Purpose: fills a string with a binary version of a number, and insures a minimum length
	Params: char* str - the string to fill, uint32_t num - the number to convert, uint32_t size - the minimum size
	Return: char* - the same as the str pointer
*/
char* num2bin(char* str, uint32_t num, uint32_t size);

/*
	Purpose: converts a condition string to number
	Params: char* cond - the condition to convert
	Return: bit code for the condition
*/
//int cond2num(char* cond);

/*
	Purpose: converts a shift type to number
	Params: Shift_Type shift - the shift to convert
	Return: bit code for the shift
*/
//int shift2num(Shift_Type shift);

/*
	Purpose: converts a number to a shift type
	Params: int shift_code - the number to convert
	Return: Shift_Type for the code
*/
//Shift_Type num2shift(int shift_code);

/*
	Purpose: checks if the given prefix is at the beginning of the given string
	Params: char* line - the string to search in
			char* prefix - the string to search for
	Return: 0 if they don't match, 1 if they do
*/
int startswith(char* line, char* prefix);

#endif