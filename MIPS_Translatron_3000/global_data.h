#pragma once

#ifndef _GLOBAL_DATA_H_
#define _GLOBAL_DATA_H_

#include <stdint.h>

/*----------------------------\
		   Defines
\----------------------------*/
#define OP_SIZE 10
#define OP_CODE assm_instruct.op
//#define S_FLAG assm_instruct.s_flag
#define COND_SIZE 2
#define COND assm_instruct.cond
#define PARAM1 assm_instruct.param1
#define PARAM2 assm_instruct.param2
#define PARAM3 assm_instruct.param3
#define PARAM4 assm_instruct.param4
//#define SHIFT assm_instruct.shift
#define BIN32 instruct

/*----------------------------\
		   Enums
\----------------------------*/

// code constants to indicate statuses
enum code {
	NO_ERROR,
	WRONG_COMMAND,
	UNRECOGNIZED_COMMAND,
	UNRECOGNIZED_COND,
	COMPLETE_ENCODE,
	COMPLETE_DECODE,
	MISSING_REG,
	INVALID_REG,
	MISSING_PARAM,
	INVALID_PARAM,
	UNEXPECTED_PARAM,
	INVALID_IMMED,
	MISSING_SPACE,
	MISSING_COMMA,
	INVALID_SHIFT,
	MISSING_SHIFT,
	UNDEF_ERROR
};

// type of possible parameters
typedef enum Param_Type {
	EMPTY,
	REGISTER,
	IMMEDIATE
} Param_Type;

//typedef enum Shift_Type {
//	LSL,
//	LSR,
//	ASR,
//	ROR,
//	RRX,
//	NONE
//} Shift_Type;

/*----------------------------\
		   Data Types
\----------------------------*/
// struct for a multi-type parameter
struct Param {
	Param_Type type : 8;
	uint32_t value;
};

// struct for the text instruction
typedef struct {
	char op[OP_SIZE + 1];
	//int s_flag;
	char cond[COND_SIZE + 1];
	struct Param param1;
	struct Param param2;
	struct Param param3;
	struct Param param4;
	//Shift_Type shift;
} Assm_Instruct;


/*----------------------------\
		 Global Variables
\----------------------------*/

extern Assm_Instruct assm_instruct;
extern uint32_t instruct;
extern uint16_t state;

#endif