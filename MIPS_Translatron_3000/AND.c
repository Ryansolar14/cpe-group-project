/*
* Author: Emily Allgeyer
*/
#include "Instruction.h"

void and_reg_assm(void) {
    // Checking that the op code matches
    if (strcmp(OP_CODE, "AND") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Checking the type of parameters
    */
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /*
        Checking the value of parameters
    */
    if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }

    /*
        Putting the binary together
        Format: [ opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) ]
        Bit positions:
        - opcode: 31-26
        - rs:     25-21
        - rt:     20-16
        - rd:     15-11
        - shamt:  10-6
        - funct:   5-0
    */

    // Set the opcode (0 for AND)
    setBits_num(31, 0, 6);

    // Set source register Rs
    setBits_num(25, PARAM2.value, 5);

    // Set source register Rt
    setBits_num(20, PARAM3.value, 5);

    // Set destination register Rd
    setBits_num(15, PARAM1.value, 5);

    // Set shamt (shift amount), 0 for AND
    setBits_num(10, 0, 5);

    // Set funct code for AND (100100)
    setBits_str(5, "100100");

    // Tell the system the encoding is done
    state = COMPLETE_ENCODE;
}

void and_reg_bin(void) {
    // Check if the op code and function bits match the AND instruction
    if (checkBits(31, "000000") != 0 || checkBits(5, "100100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Extract values from the binary
        Same bit positions as in encoding
    */
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);
    uint32_t Rd = getBits(15, 5);

    /*
        Set instruction values
    */
    setOp("AND");
    setParam(1, REGISTER, Rd); // destination
    setParam(2, REGISTER, Rs); // source 1
    setParam(3, REGISTER, Rt); // source 2

    // Tell the system the decoding is done
    state = COMPLETE_DECODE;
}
