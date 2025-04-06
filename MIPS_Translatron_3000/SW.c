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

// Decodes SW to binary
void sw_immd_assm(void) {
    // Checking that the op code matches
    // strcmp returns 0 if they match, if not equal to zero the opcode does not match and error state is set
    if (strcmp(OP_CODE, "SW") != 0) {
        state = WRONG_COMMAND; // If the op code doesn't match, return wrong command
        return;
    }

    /*
        Checking the type of parameters
    */

    // The first parameter should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG
        return;
    }

    // In SW, the second parameter should be an immediate value
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_PARAM; // Set state to INVALID_PARAM
        return;
    }

    // The third parameter should be a register
    if (PARAM3.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rt should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG; // If the register value is out of bounds, set state to INVALID_REG
        return;
    }

    // Rs should be 31 or less
    if (PARAM3.value > 31) {
        state = INVALID_REG; // If the register value is out of bounds, set state to INVALID_REG
        return;
    }

    // The immediate value should be within the valid range
    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED; // If the immediate value is out of bounds, set state to INVALID_IMMED
        return;
    }

    /*
        Encoding instruction in binary
    */

    setBits_str(31, "101011"); // Set the opcode (SW opcode is 101011)

    setBits_num(20, PARAM1.value, 5); // Set Rt
    setBits_num(25, PARAM3.value, 5); // Set Rs
    setBits_num(15, PARAM2.value, 16); // Set immediate value (imm16)

    state = COMPLETE_ENCODE; // Set state to reflect that the instruction has been encoded
}

// Decodes binary to SW
void sw_immd_bin(void) {
    // Checking that the opcode matches
    // checkBits returns 0 if the bit string matches, if not equal to zero the opcode does not match and error state is set
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND; // If the opcode doesn't match, return wrong command
        return;
    }

    /*
        Finding values in the binary
    */

    // getBits(start_bit, width)
    uint32_t Rs = getBits(25, 5); // Fetch the Rs bits
    uint32_t Rt = getBits(20, 5); // Fetch the Rt bits
    uint32_t offset = getBits(15, 16); // Fetch the immediate value bits

    /*
        Setting Instruction values
    */

    setOp("SW"); // Set the operation to SW

    // Set the parameters for the instruction
    setParam(1, REGISTER, Rt); // Set param 1 to destination register
    setParam(3, REGISTER, Rs); // Set param 3 to base register
    setParam(2, IMMEDIATE, offset); // Set param 2 to immediate value

    state = COMPLETE_DECODE; // Set state to reflect that the instruction has been decoded
}