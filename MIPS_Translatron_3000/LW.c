/*
* Modified by: Ryan Busch with assistance from GitHub Copilot
* Date: 04/01/2025
*/

#include "Instruction.h"

void lw_immd_assm(void) {
	//Check that op code matches
	// strcmp(string1, string2) return 0 if they match
	if (strcmp(OP_CODE, "LW") != 0) {
		state = WRONG_COMMAND;// If the op code doesn't match, return wrong command
		return;
	}

	/*
		Checking the type of parameters
	*/

	//First parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//In LW, the second parameter is an immediate value
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
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
	if ( PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}

	//Check if intermediate value is valid
	if ( PARAM2.value > 0x7FFF) {
		state = INVALID_IMMED;
		return;
	}
	
	//Encode instruction 
	setBits_str(31, "100011"); //Set Opcode

	setBits_num(20, PARAM1.value, 5); //Set Rt
	setBits_num(25, PARAM3.value, 5); //Set Rs
	setBits_num(15, PARAM2.value, 16); //Set immediate value (imm16)

	state = COMPLETE_ENCODE; //Set state to reflect that the instruction has been encoded
}


void lw_immd_bin(void) {

	//Check that opcode matches
	if (checkBits(31, "100011") != 0) {
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
	uint32_t imm16 = getBits(15, 16);

	/*
		Setting Instruction values
	*/

	setOp("LW"); // Set the opcode to LW

	//Set the parameters for the instruction
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rt);
	setParam(3, REGISTER, Rs);
	setParam(2, IMMEDIATE, imm16);
	
	state = COMPLETE_DECODE; //Set state to reflect that the instruction has been decoded

}
