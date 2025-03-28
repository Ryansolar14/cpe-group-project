#include "MIPS_Instruction.h"

Assm_Instruct assm_instruct;
uint32_t instruct;
uint16_t state;

/*----------------------------\
	   assembly_instructs
\----------------------------*/
// array containing all of the _assm functions
void (*assembly_instructs[])(void) = {
	// function names are placed below in a comma seperated list

	// immediate instructions
	addi_immd_assm,
	andi_immd_assm,
	ori_immd_assm,
	lui_immd_assm,
	lw_immd_assm,
	beq_immd_assm,
	bne_immd_assm,
	slti_immd_assm,
	sw_immd_assm,
	
	

	// register functions
	add_reg_assm,
	sub_reg_assm,
	mult_reg_assm,
	div_reg_assm,
	mfhi_reg_assm,
	mflo_reg_assm,
	and_reg_assm,
	or_reg_assm,
	slt_reg_assm,
	
	

	end_list
};


// array containing all of the _bin functions for 32 bit instructions
void (*binary_instructs[])(void) = {
	// function names are placed below in a comma seperated list

	// immediate instructions
	addi_immd_bin,
	andi_immd_bin,
	ori_immd_bin,
	lui_immd_bin,
	lw_immd_bin,
	beq_immd_bin,
	bne_immd_bin,
	slti_immd_bin,
	sw_immd_bin,


	// register functions
	add_reg_bin,
	sub_reg_bin,
	mult_reg_bin,
	div_reg_bin,
	mfhi_reg_bin,
	mflo_reg_bin,
	and_reg_bin,
	or_reg_bin,
	slt_reg_bin,

	end_list
};


/*
	Purpose: sets the global instrucion variables to the defualt values
	Params: none
	Return: none
*/
void initInstructs(void) {
	// clears any errors
	state = NO_ERROR;

	// sets the binary instruction to 0
	BIN32 = 0x00;

	// clears the op code
	memset(OP_CODE, '\0', OP_SIZE + 1);

	memset(COND, '\0', COND_SIZE + 1);

	//S_FLAG = 0;

	// clears all parameters
	PARAM1.type = EMPTY;
	PARAM2.type = EMPTY;
	PARAM3.type = EMPTY;
	PARAM4.type = EMPTY;

	//SHIFT = NONE;
}


/*
	Purpose: runs through each _assm function and tries to encode the parsed instruction
	Params: none
	Return: none
*/
void encode(void) {
	// clears any errors
	state = NO_ERROR;

	// loops through all of the instruction functions
	for (int i = 0; ((state == NO_ERROR) || (state == WRONG_COMMAND)); i++) {
		(*assembly_instructs[i])();
	}
}

/*
	Purpose: runs through each _bin function and tries to decode the parsed bits
	Params: none
	Return: none
*/
void decode(void) {
	// clears any errors
	state = NO_ERROR;

	// loops through each instruction function
	for (int i = 0; ((state == NO_ERROR) || (state == WRONG_COMMAND)); i++) {
		(*binary_instructs[i])();
	}
}

/*
	Purpose: serves as an indicator for the end of the instruction list
	Params: none
	Return: none
*/
void end_list(void) {
	state = UNRECOGNIZED_COMMAND;
}


/*----------------------------\
			Errors
\----------------------------*/
/*
	Purpose: prints formated error messaged
	Params: char* msg -- message to print
	Return: none
*/
void error(char* msg) {
	printf("ERROR: %s\n", msg);
}


/*----------------------------\
		   Printing
\----------------------------*/
/*
	Purpose: prints a message based on the system status
	Params: none
	Return: none
*/
void printResult(void) {
	// checks the current state and prints a corresponding message
	switch (state) {
	case NO_ERROR: {
		puts("System is Error Free");
		break;
	}
	case COMPLETE_ENCODE: {
		printMachine();
		break;
	}
	case COMPLETE_DECODE: {
		printAssm();
		break;
	}
	case UNRECOGNIZED_COMMAND: {
		error("The given instruction was not recognized");
		break;
	}
	case UNRECOGNIZED_COND: {
		error("The given conditional is not recognized");
		break;
	}
	case MISSING_REG: {
		error("Missing register parameter");
		break;
	}
	case INVALID_REG: {
		error("The given register is invalid for the specified command");
		break;
	}
	case MISSING_PARAM: {
		error("Expected a param, none was found");
		break;
	}
	case INVALID_PARAM: {
		error("The given parameter is invalid for the specified command");
		break;
	}
	case UNEXPECTED_PARAM: {
		error("Found a parameter when none was expected");
		break;
	}
	case INVALID_IMMED: {
		error("The given immediate value is invalid for the specified command");
		break;
	}
	case MISSING_SPACE: {
		error("Expected a space, none was found");
		break;
	}
	case MISSING_COMMA: {
		error("Expected a comma, none was found");
		break;
	}
	case INVALID_SHIFT: {
		error("The given shift is invalid");
		break;
	}
	case MISSING_SHIFT: {
		error("Expected a shift value but none was found");
		break;
	}
	case UNDEF_ERROR:
	default: {
		error("An unknown error code has occured");
		break;
	}
	}
}

/*
	Purpose: prints the text instruction
	Params: none
	Return: none
*/
void printAssm(void) {
	// prints the op code
	printf("%s", assm_instruct.op);
	printf(" ");

	// checks param 1 and prints if it isn't empty
	if (PARAM1.type != EMPTY) {
		printParam(&PARAM1);
	}

	// checks param 2 and prints if it isn't empty
	if (PARAM2.type != EMPTY) {
		if (PARAM2.type == IMMEDIATE && (strcmp(OP_CODE, "LW") == 0 || strcmp(OP_CODE, "SW") == 0)) {
			printf(", ");
			printParam(&PARAM2);
		}
		else {
			printf(", ");
			printParam(&PARAM2);
		}
	}

	// checks param 3 and prints if it isn't empty
	if (PARAM3.type != EMPTY) {
		if (PARAM3.type == REGISTER && (strcmp(OP_CODE, "LW") == 0 || strcmp(OP_CODE, "SW") == 0)) {
			printf("(");
			printParam(&PARAM3);
			printf(")");
		}
		else {
			printf(", ");
			printParam(&PARAM3);
		}
	}

	// checks param 4 and prints if it isn't empty
	if (PARAM4.type != EMPTY) {
		printf(", ");
		printParam(&PARAM4);
	}

	// prints the new line
	printf("\n");
}

/*
	Purpose: prints a parameter
	Params: Param* param - the parameter to print
	Return: none
*/
void printParam(struct Param* param) {
	// checks the type of parameter and prints accordingly
	switch (param->type) {
	case EMPTY: {
		printf("<>");
	}
	case REGISTER: {
		uint32_t temp = param->value;
		if (param->value == 0) {
			printf("$zero");
		}
		else if (param->value == 2 || param->value == 3) {
			temp -= 2;
			printf("$v%d", temp);
		}
		else if (param->value >= 4 && param->value <= 7) {
			temp -= 4;
			printf("$a%d", temp);
		}
		else if (param->value >= 8 && param->value <= 15) {
			temp -= 8;
			printf("$t%d", temp);
		}
		else if (param->value >= 16 && param->value <= 23) {
			temp -= 16;
			printf("$s%d", temp);
		}
		else if (param->value == 24 || param->value == 25) {
			temp -= 16;
			printf("$t%d", temp);
		}
		else if (param->value == 28) {
			printf("$gp");
		}
		else if (param->value == 29) {
			printf("$sp");
		}
		else if (param->value == 30) {
			printf("$fp");
		}
		else if (param->value == 31) {
			printf("$ra");
		}
		break;
	}
	case IMMEDIATE: {
		printf("#0x%X", param->value);
		break;
	}
	default: {
		printf("<unknown: %d, %d>", param->type, param->value);
		break;
	}
	}
}

/*
	Purpose: prints thebinary instruction
	Params: none
	Return: none
*/
void printMachine(void) {

	printf("Hex: 0x%08X\tBinary:", instruct);

	// prints the binary instrution in binary form
	for (int i = 31; i > -1; i--) {
		printf("%d", (BIN32 >> i) & 1);

		if (i % 4 == 0) {
			printf(" ");
		}
	}

	printf("\n");
}


/*----------------------------\
		   Parsing
\----------------------------*/
/*
	reads the assembly instruction into the instruction struct
*/
void parseAssem(char* line) {
	// checks that parameters are valid
	if (line == NULL || strlen(line) == 0) {
		state = UNDEF_ERROR;
		return;
	}

	// clears instruction values
	initInstructs();

	// reads op code into the instruction op code
	if (startswith(line, "ADDI") == 1) { setOp("ADDI"); line += 4; }
	else if (startswith(line, "ADD") == 1) { setOp("ADD"); line += 3;}
	else if (startswith(line, "ANDI") == 1) { setOp("ANDI"); line += 4; }
	else if (startswith(line, "AND") == 1) { setOp("AND"); line += 3;}
	else if (startswith(line, "BEQ") == 1) { setOp("BEQ"); line += 3;}
	else if (startswith(line, "BNE") == 1) { setOp("BNE"); line += 3;}
	else if (startswith(line, "DIV") == 1) { setOp("DIV"); line += 3;}
	else if (startswith(line, "LUI") == 1) { setOp("LUI"); line += 3;}
	else if (startswith(line, "LW") == 1) { setOp("LW"); line += 2; }
	else if (startswith(line, "MFHI") == 1) { setOp("MFHI"); line += 4;}
	else if (startswith(line, "MFLO") == 1) { setOp("MFLO"); line += 4;}
	else if (startswith(line, "MULT") == 1) { setOp("MULT"); line += 4;}
	else if (startswith(line, "ORI") == 1) { setOp("ORI"); line += 3; }
	else if (startswith(line, "OR") == 1) { setOp("OR"); line += 2;}
	else if (startswith(line, "SLTI") == 1) { setOp("SLTI"); line += 4; }
	else if (startswith(line, "SLT") == 1) { setOp("SLT"); line += 3;}
	else if (startswith(line, "SUB") == 1) { setOp("SUB"); line += 3;}
	else if (startswith(line, "SW") == 1) { setOp("SW"); line += 2; }
	else { state = UNRECOGNIZED_COMMAND; return; }
	

	if (*line != ' ') {
		state = MISSING_SPACE;
		return;
	}

	// eat any whitespace
	while (*line == ' ') { line++; }

	/*
		Param 1
	*/

	// tries to read a parameter
	line = readParam(line, &PARAM1);

	// checks if there was an error or if the line is empty
	if ((state != NO_ERROR) || (*line == '\0')) {
		return;
	}

	/*
		Param 2
	*/

	// tries to read a parameter
	line = readParam(line, &PARAM2);

	// checks if there was an error or if the line is empty
	if ((state != NO_ERROR) || (*line == '\0')) {
		return;
	}

	// checks if there was an error
	if (state != NO_ERROR) {
		return;
	}

	// tries to read a parameter
	line = readParam(line, &PARAM3);

	// checks if there was an error or if the line is empty
	if ((state != NO_ERROR) || (*line == '\0')) {
		return;
	}

	// checks if there was an error
	if (state != NO_ERROR) {
		return;
	}

	// tries to read a parameter
	line = readParam(line, &PARAM4);

}


/*
	Purpose: reads a parameter from a given line
	Params: char* line - the line to read
			Param* param - the parameter to fill
	Return: char* - the ptr to after the param
*/
char* readParam(char* line, struct Param* param) {
	// eat any whitespace
	while (*line == ' ') { line++; }

	uint8_t comma_flag;

	// checks for a comma at the front, eats it if present
	if (*line != ',') {
		comma_flag = 0;
	}
	else {
		line++;
		comma_flag = 1;
	}
	if (toupper(*line) == '(' ) {
		line++;
	}
	

	// eat any whitespace
	while (*line == ' ') { line++; }

	if (*line == '\0') {
		state = MISSING_PARAM;
		return NULL;
	}
	

	// check parameter type and save value
	if (toupper(*line) == '$') {
		line++; // Move past the '$'
		char reg_name[5] = { 0 };
		int i = 0;

		// Read the register name (up to 4 characters, e.g., "t1")
		while (isalpha(*line) || isdigit(*line)) {
			reg_name[i++] = *line++;
		}
		param->type = REGISTER;
		// Convert register name to the appropriate register number
		param->value = reg2num(reg_name);
	}
	else if (toupper(*line) == '#') {
		line++;
		param->type = IMMEDIATE;
		line = immd2num(line, &param->value);
	}
	else {
		state = INVALID_PARAM;
		return NULL;
	}
	if (toupper(*line) == ')' ) {
		line++;
	}
	// eat any whitespace
	while (*line == ' ') { line++; }

	// check for comma if there wasn't one at the beginning
	if (strcmp(OP_CODE, "LW") == 0 || strcmp(OP_CODE, "SW") == 0 || strcmp(OP_CODE, "MFLO") == 0 || strcmp(OP_CODE, "MFHI") == 0) {
		comma_flag = 1;
	}
	if ((comma_flag == 0) ) {
		if (*line != ',') {
			state = MISSING_COMMA;
		}
	}


	// updated line ptr
	return line;
}

/*
	Purpose: converts a string into a integer number
	Params: char* reg - the string to convert
	Return: uint32_t - value of register
*/
uint32_t reg2num(char* reg) {
	// Convert register name to the appropriate register number
	uint32_t num = 32;
	if (strcmp(reg, "zero") == 0) { num = 0; }  // $zero is register 0 
	else if (strcmp(reg, "v0") == 0) { num = 2; }  // $v0 is register 2
	else if (strcmp(reg, "v1") == 0) { num = 3; }  // $v1 is register 3
	else if (strcmp(reg, "a0") == 0) { num = 4; }  // $a0 is register 4
	else if (strcmp(reg, "a1") == 0) { num = 5; }  // $a1 is register 5
	else if (strcmp(reg, "a2") == 0) { num = 6; }  // $a2 is register 6
	else if (strcmp(reg, "a3") == 0) { num = 7; }  // $a3 is register 7
	else if (strcmp(reg, "t0") == 0) { num = 8; }  // $t0 is register 8
	else if (strcmp(reg, "t1") == 0) { num = 9; }  // $t1 is register 9
	else if (strcmp(reg, "t2") == 0) { num = 10; }  // $t2 is register 10
	else if (strcmp(reg, "t3") == 0) { num = 11; }  // $t3 is register 11
	else if (strcmp(reg, "t4") == 0) { num = 12; }  // $t4 is register 12
	else if (strcmp(reg, "t5") == 0) { num = 13; }  // $t5 is register 13
	else if (strcmp(reg, "t6") == 0) { num = 14; }  // $t6 is register 14
	else if (strcmp(reg, "t7") == 0) { num = 15; }  // $t7 is register 15
	else if (strcmp(reg, "s0") == 0) { num = 16; }  // $s0 is register 16
	else if (strcmp(reg, "s1") == 0) { num = 17; }  // $s1 is register 17
	else if (strcmp(reg, "s2") == 0) { num = 18; }  // $s2 is register 18
	else if (strcmp(reg, "s3") == 0) { num = 19; }  // $s3 is register 19
	else if (strcmp(reg, "s4") == 0) { num = 20; }  // $s4 is register 20 
	else if (strcmp(reg, "s5") == 0) { num = 21; }  // $s5 is register 21
	else if (strcmp(reg, "s6") == 0) { num = 22; }  // $s6 is register 22 
	else if (strcmp(reg, "s7") == 0) { num = 23; }  // $s7 is register 23
	else if (strcmp(reg, "t8") == 0) { num = 24; }  // $t8 is register 24
	else if (strcmp(reg, "t9") == 0) { num = 25; }  // $t9 is register 25
	else if (strcmp(reg, "gp") == 0) { num = 28; }  // $gp is register 28
	else if (strcmp(reg, "sp") == 0) { num = 29; }  // $sp is register 29
	else if (strcmp(reg, "fp") == 0) { num = 30; }  // $fp is register 30
	else if (strcmp(reg, "ra") == 0) { num = 31; }  // $ra is register 31
	else { return -1; }
	return num;
}


/*
	Purpose: converts a string into either a hex or decimal number
	Params: char* line - the string to convert
			uint32_t* value - the number to fill
	Return: char* - the ptr to after the number
*/
char* immd2num(char* line, uint32_t* value) {
	uint32_t num = 0;

	// checks if the number is prefixed for hex
	if ((*line == '0') && (toupper(*(line + 1)) == 'X')) {
		line += 2;

		// as long as there are valid digits, they are added to the running number
		while (isxdigit(*line)) {
			if (isdigit(*line)) {
				num = (num * 16) + (*line - 48);
			}
			else {
				num = (num * 16) + (toupper(*line) - 55);
			}

			line++;
		}
	}
	else {
		// as long as there are valid digits, they are added to the running number
		while (isdigit(*line)) {
			num = (num * 10) + (*line - 48);
			line++;
		}
	}

	// sets the gven number ptr
	*value = num;

	// updates line ptr
	return line;
}


/*
	Purpose: parses the given hex line into into the binary instruction
	Params: char* line - the line to convert
	Return: none
*/
void parseHex(char* line) {
	// checks that parameters are valid
	if (line == NULL || strlen(line) == 0) {
		state = UNDEF_ERROR;
		return;
	}

	// clears instruction values
	initInstructs();

	uint32_t num = 0;

	// checks if there is a hex prefix
	if ((*line == '0') && (toupper(*(line + 1)) == 'X')) {
		line += 2;
	}

	// as long as there are valid digits, they are added to the running number
	while (isxdigit(*line)) {
		if (isdigit(*line)) {
			num = (num * 16) + (*line - 48);
		}
		else {
			num = (num * 16) + (toupper(*line) - 55);
		}

		line++;
	}

	// sets the binary instruction to the converted number
	BIN32 = num;
}


/*
	Purpose: parses the given binary line into into the binary instruction
	Params: char* line - the line to convert
	Return: none
*/
void parseBin(char* line) {
	// checks that parameters are valid
	if (line == NULL || strlen(line) == 0) {
		state = UNDEF_ERROR;
		return;
	}

	// clears instruction values
	initInstructs();

	uint32_t num = 0;

	// checks if there is a binary prefix
	if ((*line == '0') && (toupper(*(line + 1)) == 'b')) {
		line += 2;
	}

	// as long as there are valid digits, they are added to the running number
	while (*line != '\0') {
		if ((*line == '0') || (*line == '1')) {
			num = (num * 2) + (*line - 48);
		}
		line++;
	}

	// sets the binary instruction to the converted number
	BIN32 = num;
}



/*----------------------------\
		   Set Bits
\----------------------------*/
/*
	Purpose: sets bits in the binary instruction given a number and a number of bits
	Params: uint32_t start - the bit to start at
			uint32_t num - the number to use as a source of bits
			uint32_t size - the number of bits to set
	Return: none
*/
void setBits_num(uint32_t start, uint32_t num, uint32_t size) {
	// temp string for conversion purposes
	char str[40] = { '\0' };

	// converts the number to a string of the needed size
	num2bin(str, num, size);

	// sets the bits in the binary instruction
	setBits_str(start, str);
}


/*
	Purpose: sets bits in the binary instruction given a string
	Params: uint32_t start - the bit to start at
			const char* str - the string to use as a source of bits, skips any x or X characters
	Return: none
*/
void setBits_str(uint32_t start, const char* str) {
	// loops through the sting ad sets the bits in the binary instruction
	for (int i = 0; i < strlen(str); i++) {
		if ((str[i] == '0') || (str[i] == '1')) {
			BIN32 |= (str[i] - 48) << (start - i);
		}
	}
}


/*----------------------------\
		  Check Bits
\----------------------------*/
/*
	Purpose: checks if the given series of bits is in the binary instruction
	Params: uint32_t start - the bit to start at
			const char* str - the series of bits to look for, skips any x or X characters
	Return: int - 0 for present, 1 for not present
*/
int checkBits(uint32_t start, const char* str) {
	// loops thorugh and checks each bit in the bianry instruction
	for (int i = 0; i < strlen(str); i++) {
		// skips anything that isn't a 1 or 0
		if ((str[i] != '0') && (str[i] != '1')) {
			continue;
		}

		if ((str[i] - 48) != ((BIN32 >> (start - i)) & 0x1)) {
			return 1;
		}
	}

	// no error
	return 0;
}


/*----------------------------\
		   Get Bits
\----------------------------*/
/*
	Purpose: gets a group of bits from the binary instruction
	Params: uint32_t start - the bit to strt grabbing from
			uint32_t the number of bits to grab
	Return: int - the number represented from the bits
*/
uint32_t getBits(uint32_t start, uint32_t size) {
	uint32_t num = 0;

	// finds the last bit to grab, non-inclusive
	int end = start - size;

	// loops through each bit and adds it to the running num
	for (int i = start; i > end; i--) {
		num = (num * 2) + ((BIN32 >> i) & 0x1);
	}

	// returns the extracted number
	return num;
}


/*----------------------------\
	 Set Instruction Parts
\----------------------------*/
/*
	Purpose: sets the specified parameter to the specified type and value
	Params: uint32_t param_num - which parameter to change
			Param_Type type - what type to set the parameter to
			uint32_t value - what value to set the parameter to
	Return: 0 for no error
*/
int setParam(uint32_t param_num, Param_Type type, uint32_t value) {
	// finds which parameter is being set and set the type and value
	switch (param_num) {
	case 1: {
		PARAM1.type = type;
		PARAM1.value = value;
		break;
	}
	case 2: {
		PARAM2.type = type;
		PARAM2.value = value;
		break;
	}
	case 3: {
		PARAM3.type = type;
		PARAM3.value = value;
		break;
	}
	case 4: {
		PARAM4.type = type;
		PARAM4.value = value;
		break;
	}
	default: {
		return 1;
		break;
	}
	}

	// no error
	return 0;
}

/*
	Purpose: sets the opcode field in the instruction
	Params: char* opCode - string to set the op code to
	Return: none
*/
void setOp(char* opCode) {
	for (int i = 0; i < OP_SIZE; i++) {
		OP_CODE[i] = *opCode++;

		if (*opCode == '\0') {
			OP_CODE[i + 1] = '\0';
			break;
		}
	}
}


/*----------------------------\
			 Misc
\----------------------------*/
/*
	Purpose: fills a string with a binary version of a number, and insures a minimum length
	Params: char* str - the string to fill, uint32_t num - the number to convert, uint32_t size - the minimum size
	Return: char* - the same as the str pointer
*/
char* num2bin(char* str, uint32_t num, uint32_t size) {
	int index = 0;

	// extracts the LSB until the numebr is zero
	while (num > 0) {
		str[index++] = (num % 2) + 48;
		num /= 2;
	}

	// makes sure that the string is terminated
	str[index] = '\0';

	// zeros to fill to the minimum size
	while (strlen(str) < size) {
		str[index++] = '0';
		str[index] = '\0';
	}

	// swaps the bits to reverse the string
	index--;
	for (int i = 0; i < index; i++, index--) {
		char c = str[index];
		str[index] = str[i];
		str[i] = c;
	}

	// returns the str ptr
	return str;
}

/*
	Purpose: checks if the given prefix is at the beginning of the given string
	Params: char* line - the string to search in
			char* prefix - the string to search for
	Return: 0 if they don't match, 1 if they do
*/
int startswith(char* line, char* prefix) {
	while (*prefix != '\0') {
		char c1 = *line++;
		char c2 = *prefix++;

		if ((c1 <= 'z') && (c1 >= 'a')) {
			c1 -= 32;
		}

		if ((c2 <= 'z') && (c2 >= 'a')) {
			c2 -= 32;
		}

		if (c2 != c1) {
			return 0;
		}
	}
	return 1;
}
