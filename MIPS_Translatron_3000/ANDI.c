/*
* Author: Emily Allgeyer
*/


#include "Instruction.h"

void andi_immd_assm(void) {
    // Check that the opcode is ANDI
    if (strcmp(OP_CODE, "ANDI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Check parameter types
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    // Check parameter values
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /*
        I-type format:
        [ opcode (6) | rs (5) | rt (5) | immediate (16) ]
        Bit positions:
        - opcode: 31-26 (6 bits)
        - rs:     25-21 (source)
        - rt:     20-16 (destination)
        - imm:    15-0  (immediate value)
    */

    setBits_str(31, "001100");                  // opcode for ANDI
    setBits_num(25, PARAM2.value, 5);           // rs (source)
    setBits_num(20, PARAM1.value, 5);           // rt (destination)
    setBits_num(15, PARAM3.value, 16);          // immediate value

    state = COMPLETE_ENCODE;
}

void andi_immd_bin(void) {
    // Check if the opcode matches ANDI
    if (checkBits(31, "001100") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /*
        Decode I-type format:
        [ opcode (6) | rs (5) | rt (5) | immediate (16) ]
    */
    uint32_t rs = getBits(25, 5);
    uint32_t rt = getBits(20, 5);
    uint32_t imm = getBits(15, 16);

    // Set decoded values into instruction fields
    setOp("ANDI");
    setParam(1, REGISTER, rt);         // destination
    setParam(2, REGISTER, rs);         // source
    setParam(3, IMMEDIATE, imm);       // immediate

    state = COMPLETE_DECODE;
}


