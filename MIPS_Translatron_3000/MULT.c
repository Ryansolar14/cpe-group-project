/*
* Created by GitHub Copilot and Ryan Busch
* Date: 04/04/2025
*/

#include "Instruction.h"

// Encodes MULT to binary
void mult_reg_assm(void) {
    // Checking that the op code matches
    // strcmp returns 0 if they match, if not equal to zero the opcode does not match and error state is set
    if (strcmp(OP_CODE, "MULT") != 0) {
        state = WRONG_COMMAND; // If the op code doesn't match, return wrong command
        return;
    }

    /*
        Checking the type of parameters
    */

    // Param 1 should be a register
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG
        return;
    }

    // Param 2 should be a register
    if (PARAM2.type != REGISTER) {
        state = MISSING_REG; // Set state to MISSING_REG
        return;
    }

    /*
        Checking the value of parameters
    */

    // Rs should be 31 or less
    if (PARAM1.value > 31) {
        state = INVALID_REG; // If the register value is out of bounds, set state to INVALID_REG
        return;
    }

    // Rt should be 31 or less
    if (PARAM2.value > 31) {
        state = INVALID_REG; // If the register value is out of bounds, set state to INVALID_REG
        return;
    }

    /*
        Encoding instruction in binary
    */

    setBits_num(31, 0, 6); // Set the opcode (0 for R-type instructions)
    setBits_str(5, "011000"); // Set the funct (24 for MULT)
    setBits_num(25, PARAM1.value, 5); // Set Rs
    setBits_num(20, PARAM2.value, 5); // Set Rt

    // No Rd for MULT, so no need to set it

    state = COMPLETE_ENCODE; // Set state to reflect that the instruction has been encoded
}

// Decodes binary to MULT
void mult_reg_bin(void) {
    // Checking that the opcode matches
    // checkBits returns 0 if the bit string matches, if not equal to zero the opcode does not match and error state is set
    if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0) {
        state = WRONG_COMMAND; // If the opcode doesn't match, return wrong command
        return;
    }

    /*
        Finding values in the binary
    */

    // getBits(start_bit, width)
    uint32_t Rs = getBits(25, 5); // Fetch the Rs bits
    uint32_t Rt = getBits(20, 5); // Fetch the Rt bits

    /*
        Setting Instruction values
    */

    setOp("MULT"); // Set the operation to MULT

    // Set the parameters for the instruction
    setParam(1, REGISTER, Rs); // Set param 1 to first source register operand
    setParam(2, REGISTER, Rt); // Set param 2 to second source register operand

    state = COMPLETE_DECODE; // Set state to reflect that the instruction has been decoded
}