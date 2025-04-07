/*
* Author: Emily Allgeyer
*/


#include "Instruction.h"

void div_reg_assm(void) {
    // Ensure opcode matches DIV
    if (strcmp(OP_CODE, "DIV") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Validate parameter types
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    // Validate register numbers
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    /*
        R-type format for DIV:
        [ opcode (6) | rs (5) | rt (5) | rd (5) | shamt (5) | funct (6) ]
        Use 0 for rd and shamt.
        rs = PARAM2
        rt = PARAM1
    */
    setBits_str(31, "000000");              // opcode
    setBits_num(25, PARAM2.value, 5);       // rs
    setBits_num(20, PARAM1.value, 5);       // rt
    setBits_num(15, 0, 10);                 // rd + shamt = 0
    setBits_str(5, "011010");               // funct for DIV

    state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
    // Check opcode and funct bits
    if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Extract fields
    uint32_t rs = getBits(25, 5);
    uint32_t rt = getBits(20, 5);

    // Assign decoded fields
    setOp("DIV");
    setParam(1, REGISTER, rt); // operand 1
    setParam(2, REGISTER, rs); // operand 2

    state = COMPLETE_DECODE;
}
