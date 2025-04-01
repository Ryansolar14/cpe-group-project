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

//Decodes sw to binary
void sw_immd_assm(void) {
	//Check that op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "SW") != 0) {
		state = WRONG_COMMAND; //If the op code doesn't match, return wrong command
		return;
	}

	//First parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//In SW, the second parameter is an immediate value
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	//Third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	/*
		Checking the value of parameters
	*/

	//Check if registers 1 and 3 are valid (31 or less)
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if (PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	//Check if intermediate value is valid
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}

	//Encode instruction
	setBits_str(31, "101011"); //Set Opcode

	setBits_num(20, PARAM1.value, 5); //Set Rt
	setBits_num(25, PARAM3.value, 5); //Set Rs
	setBits_num(15, PARAM2.value, 16); //Set immediate value

	state = COMPLETE_ENCODE; //Set state to reflect that the instruction has been encoded
}

//Decodes binary to sw
void sw_immd_bin(void) {

	//Check that opcode matches
	if (checkBits(31, "101011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	//Read other inputs if opcode bits match

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t offset = getBits(15, 16);

	setOp("SW"); //Set the opcode to SW

	//Set the parameters for the instruction
	// setParam(param_num, type, value)
	setParam(1, REGISTER, Rt); 
	setParam(3, REGISTER, Rs); 
	setParam(2, IMMEDIATE, offset); 

	state = COMPLETE_DECODE; //Set state to reflect that the instruction has been decoded
}