#include "Instruction.h"

void lw_immd_assm(void) {
	if (strcmp(OP_CODE, "LW") != 0) {

		state = WRONG_COMMAND;
		return;
	}
	
	
	if (PARAM1.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	if (PARAM2.type != IMMEDIATE) {
		state = INVALID_IMMED;
		return;
	}

	//reg
	if (PARAM3.type != REGISTER) {
		state = MISSING_REG;
		return;
	}

	//check if register 1 and 3
	if (PARAM1.value > 31) {
		state = INVALID_REG;
		return;
	}
	if ( PARAM3.value > 31) {
		state = INVALID_REG;
		return;
	}
	//register 2 
	if ( PARAM2.value > 0x7FFF) {
		state = INVALID_IMMED;
		return;
	}
	
	//encode instruction 
	setBits_str(31, "100011");
	setBits_num(20, PARAM1.value, 5);
	setBits_num(25, PARAM3.value, 5);
	setBits_num(15, PARAM2.value, 16);


	state = COMPLETE_ENCODE;
}


void lw_immd_bin(void) {

	//check op code 
	if (checkBits(31, "100011") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t imm16 = getBits(15, 16);

	setOp("LW");
	setParam(1, REGISTER, Rt);
	setParam(3, REGISTER, Rs);
	setParam(2, IMMEDIATE, imm16);
	state = COMPLETE_DECODE;

}
