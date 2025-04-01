/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

/*
* Modified by: Ryan Busch with assistance from GitHub Copilot
* Date: 04/01/2025
*/

#include "Instruction.h"

void sub_reg_assm(void) {
	// Checking that the op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "SUB") != 0) {
	
		state = WRONG_COMMAND; //If the op code doesn't match, return wrong command
		return; 
	}

	/*
		Checking the type of parameters
	*/

	//The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//The second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//The third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG;
		return;
	}

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	/*
		Encoding instruction in binary
	*/

	
	setBits_num(31, 0, 6);// Set the opcode
	setBits_str(5, "100010"); // Set the funct 

	setBits_num(15, PARAM1.value, 5); // set Rd
	setBits_num(25, PARAM2.value, 5); // set Rs
	setBits_num(20, PARAM3.value, 5); // set Rt

	state = COMPLETE_ENCODE; //Set state to reflect that the instruction has been encoded
}

void sub_reg_bin(void) {
	// Check if the opcode and funct bits are correct
	if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0 ) {
		state = WRONG_COMMAND;
		return;
	}

	// Read other inputs if opcode bits match

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rd = getBits(15, 5);
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);	

	/*
		Setting Instruction values
	*/

	setOp("SUB"); //setOpCode(0); //Set opcode to 0 for R-type instructions
	
	//Set the parameters for the instruction
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rd); //destination
	setParam(2, REGISTER, Rs); //first source register operand
	setParam(3, REGISTER, Rt); //second source register operand

	state = COMPLETE_DECODE; //Set state to reflect that the instruction has been decoded
}


