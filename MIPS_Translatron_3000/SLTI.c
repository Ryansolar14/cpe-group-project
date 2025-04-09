/*
* Author: Ol' Jim
* Date: 06/13/2012
* ByteForge Systems
* MIPS-Translatron 3000
*/

// give this to the intern

// Implemented by Nicholas Bennett

#include "Instruction.h"

void slti_immd_assm(void) {
	if (strcmp(OP_CODE, "SLTI") != 0) {
        // If the opcode doesn't match, this isn't the correct command
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register (Rt)
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The second parameter should be a register (Rs)
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // The third parameter should be an immediate value
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rt should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    // Rs should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    // The immediate value is limited to 16 bits (0xFFFF)
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /*
        Putting the binary together
    */

    // Set the opcode (001010 for SLTI)
    setBits_str(31, "001010");

    // Set the target register (Rt)
    setBits_num(20, PARAM1.value, 5);

    // Set the source register (Rs)
    setBits_num(25, PARAM2.value, 5);

    // Set the immediate value
    setBits_num(15, PARAM3.value, 16);

    // Indicate that encoding is complete
    state = COMPLETE_ENCODE;
}

void slti_immd_bin(void) {
	// Check if the opcode bits match (001010 for SLTI)
    if (checkBits(31, "001010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Extracting values from the binary
    */
    uint32_t Rs = getBits(25, 5);    // Source register
    uint32_t Rt = getBits(20, 5);    // Target register
    uint32_t imm16 = getBits(15, 16); // Immediate value

    /*
        Setting instruction values
    */
    setOp("SLTI");                  // Set the operation to SLTI
    setParam(1, REGISTER, Rt);      // Target register
    setParam(2, REGISTER, Rs);      // Source register
    setParam(3, IMMEDIATE, imm16);  // Immediate value

    // Indicate that decoding is complete
    state = COMPLETE_DECODE;
}


