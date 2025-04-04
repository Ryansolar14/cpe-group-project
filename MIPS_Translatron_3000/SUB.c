/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

/*
* Modified by: Ryan Busch with assistance from GitHub Copilot
* Date: 04/03/2025
*/

#include "Instruction.h"

void sub_reg_assm(void) {
	// Checking that the op code matches
	//strcmp returns 0 if they match, if not equal to zero the opcode does not match and error state is set
	if (strcmp(OP_CODE, "SUB") != 0) {
	
		state = WRONG_COMMAND; //If the op code doesn't match, return wrong command
		return; 
	}

	/*
		Checking the type of parameters
	*/

	//The first parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG; //Set state to MISSING_REG
		return;
	}

	//The second parameter should be a register
	if (PARAM2.type != REGISTER) {
		state = MISSING_REG; //Set state to MISSING_REG
		return;
	}

	//The third parameter should be a register
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG; //Set state to MISSING_REG
		return;
	}

	/*
		Checking the value of parameters
	*/

	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG; //If the register is value is out of bounds, set state to INVALID_REG
		return;
	}

	// Rs should be 31 or less
	if (PARAM2.value > 31) {
		state = INVALID_REG; //If the register is value is out of bounds, set state to INVALID_REG
		return;
	}

	// Rt should be 31 or less
	if (PARAM3.value > 31) {
		state = INVALID_REG; //If the register is value is out of bounds, set state to INVALID_REG
		return;
	}

	/*
		Encoding instruction in binary
	*/

	
	setBits_num(31, 0, 6);//Set the opcode
	setBits_str(5, "100010"); //Set the funct field (sub funct code is 100010)

	setBits_num(15, PARAM1.value, 5); // set Rd
	setBits_num(25, PARAM2.value, 5); // set Rs
	setBits_num(20, PARAM3.value, 5); // set Rt

	state = COMPLETE_ENCODE; //Set state to reflect that the instruction has been encoded
}

void sub_reg_bin(void) {
	// Check if the opcode and funct bits are correct
	if (checkBits(31, "000000") != 0 || checkBits(5, "100010") != 0 ) {
		state = WRONG_COMMAND; //If the opcode and funct bits don't match, return wrong command
		return;
	}

	// Read other inputs if opcode bits match

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rd = getBits(15, 5); //Fetch the Rd bits
	uint32_t Rs = getBits(25, 5); //Fetch the Rs bits
	uint32_t Rt = getBits(20, 5); //Fetch the Rt bits	

	/*
		Setting Instruction values
	*/

	setOp("SUB"); //Set operation to SUB
	
	//Set the parameters for the instruction
	setParam(1, REGISTER, Rd); //Set param 1 to destination register
	setParam(2, REGISTER, Rs); //Set param 2 to first source register
	setParam(3, REGISTER, Rt); //Set param 3 to second source register
	
	state = COMPLETE_DECODE; //Set state to reflect that the instruction has been decoded
}


