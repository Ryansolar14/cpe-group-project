#include "Instruction.h"

/*
* Modified by: Alex White
* Date: 04/07/2025
*/

void mfhi_reg_assm(void) {
	// Checking that the op code matches
	// strcmp returns 0 if they match, if not equal to zero the opcode does not match and error state is set
	if (strcmp(OP_CODE, "MFHI") != 0) {

		state = WRONG_COMMAND;
		return;
	}

	/*
		Checking the type of parameters
	*/

	// The only parameter should be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG; //If the parameter type is not a register, set state to MISSING_REG
		return;
	}


	/*
		Checking the value of parameter
	*/
	// Rd should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG; // If the register value is out of bounds, set state to INVALID_REG
		return;
	}

	/*
	Putting the binary together
	*/
	// Set the opcode
	setBits_str(31, "000000");
	// set rd
	setBits_num(15, PARAM1.value, 5);

	// Set the funct 
	setBits_str(5, "010000"); //MFHI funct is 16 not 18
	// set 25-16 as 0s 
	setBits_str(21, "000000");
	setBits_str(25, "000000");
	// set 10-6 as 0s 
	setBits_str(10, "00000");

	// tell the system the encoding is done
	state = COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "000000") != 0 || checkBits(5, "010000") != 0 /*16 not 18*/|| checkBits(25, "0000000000") != 0 || checkBits(10, "00000") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	// If the op code bits match, then the rest can be read as correctly

	/*
		Finding values in the binary
	*/

	// getBits(start_bit, width)
	uint32_t Rd = getBits(15, 5);
	/*
		Setting Instuciton values
	*/
	setOp("MFHI");
	//setParam(param_num, param_type, param_value)
	setParam(1, REGISTER, Rd); //destination


	// tell the system the decoding is done
	state = COMPLETE_DECODE;
}


