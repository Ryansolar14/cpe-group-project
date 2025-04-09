/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

/*
* Modified by: Alex White
* Date: 04/07/2025
*/

#include "Instruction.h"

// Checking that the op code matches
// strcmp returns 0 if they match, if not equal to zero the opcode does not match and error state is set
void lui_immd_assm(void) {
	if (strcmp(OP_CODE, "LUI") != 0) {
		state = WRONG_COMMAND; // If the op code doesn't match, return wrong command
		return;
	}
	
	/*
        Checking the type of parameters
    */
	//the first parameter has to be a register
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}
	//the second parameter has to be immediate
	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_PARAM;
		return;
	}

	//there are only two parameters in a LUI instruction

	/*
		Checking the value of parameters
	*/
	// Rt should be 31 or less
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	// The immediate value should be within the valid range
	if (PARAM2.value > 0xFFFF) {
		state = INVALID_IMMED;
		return;
	}
	

	setBits_str(31, "001111"); //set opcode
	setBits_num(20, PARAM1.value, 5); //set rt
	/*    rs is not used so keep it 00000     */
	setBits_num(15, PARAM2.value, 16); //set immediate

	state = COMPLETE_ENCODE;
}


void lui_immd_bin(void) {
	// Check if the op code bits match
	// check_bits(start_bit, bit_string) returns 0 if the bit_string matches
	//  any x will be skipped
	// If the manual shows (0), then the value of that bit doesnt matter
	if (checkBits(31, "001111") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	/*
        Finding values in the binary
    */

	//uint32_t Rs = getBits(25, 5); **rs is not used in this instruction
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	setOp("LUI");
	setParam(1, REGISTER, Rt); 
	//setParam(2, REGISTER, Rs); **rs is not used in this instruction
	setParam(2, IMMEDIATE, imm16); 

	state = COMPLETE_DECODE;
}



